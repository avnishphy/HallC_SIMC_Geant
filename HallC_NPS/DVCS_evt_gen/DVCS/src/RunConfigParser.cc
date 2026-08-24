#include "RunConfigParser.hh"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <unordered_map>
#include "G4SystemOfUnits.hh"

#include "dvcsGlobals.hh"

namespace RunConfig {

static inline std::string trim(const std::string& s) {
    auto b = s.find_first_not_of(" \t\r\n");
    if(b==std::string::npos) return "";
    auto e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e-b+1);
}

static std::vector<std::string> parseCsvRow(const std::string& line) {
    std::vector<std::string> fields;
    std::string field;
    bool quoted = false;
    for (std::size_t i = 0; i < line.size(); ++i) {
        const char c = line[i];
        if (c == '"') {
            if (quoted && i + 1 < line.size() && line[i + 1] == '"') {
                field.push_back('"');
                ++i;
            } else {
                quoted = !quoted;
            }
        } else if (c == ',' && !quoted) {
            fields.push_back(trim(field));
            field.clear();
        } else {
            field.push_back(c);
        }
    }
    fields.push_back(trim(field));
    return fields;
}

RunConfigParser::RunConfigParser(const std::string& path) {
    valid_ = parseFile(path);
}

bool RunConfigParser::IsValid() const { return valid_; }

bool RunConfigParser::parseFile(const std::string& path) {
    std::ifstream ifs(path);
    if(!ifs.is_open()){
        errorMsg_ = "Cannot open config file: " + path;
        return false;
    }

    const auto dot = path.find_last_of('.');
    const bool isCsv = dot != std::string::npos && path.substr(dot) == ".csv";
    return isCsv ? parseCsvFile(ifs) : parseKinCFile(ifs);
}

bool RunConfigParser::parseCsvFile(std::ifstream& ifs) {
    std::string headerLine;
    if (!std::getline(ifs, headerLine)) {
        errorMsg_ = "Empty CSV config file";
        return false;
    }

    const auto headers = parseCsvRow(headerLine);
    std::unordered_map<std::string, std::size_t> column;
    for (std::size_t i = 0; i < headers.size(); ++i) column[headers[i]] = i;

    const std::vector<std::string> required = {
        "new_kin", "kin_old", "target", "ebeam_gev", "hms_p_gev",
        "hms_theta_deg", "nps_theta_deg", "nps_target_distance_cm", "source_run"
    };
    for (const auto& name : required) {
        if (column.find(name) == column.end()) {
            errorMsg_ = "CSV config missing required column: " + name;
            return false;
        }
    }

    std::string line;
    int lineNo = 1;
    while (std::getline(ifs, line)) {
        ++lineNo;
        if (trim(line).empty()) continue;
        const auto fields = parseCsvRow(line);
        if (fields.size() != headers.size()) {
            std::cerr << "RunConfigParser: skipping ragged CSV row " << lineNo
                      << " (expected " << headers.size() << " fields, got "
                      << fields.size() << ")\n";
            continue;
        }

        const auto value = [&](const std::string& name) -> const std::string& {
            return fields[column.at(name)];
        };

        Entry e;
        e.name = value("kin_old");
        e.displayName = value("new_kin");
        e.target = value("target");
        try {
            e.runBegin = std::stoi(value("source_run"));
            e.runEnd = e.runBegin; // CSV contains one authoritative source run per setting.
            e.E_GeV = std::stod(value("ebeam_gev"));
            e.hms_p_GeV = std::stod(value("hms_p_gev"));
            e.hms_angle_deg = std::stod(value("hms_theta_deg"));
            e.nps_angle_deg = std::stod(value("nps_theta_deg"));
            e.calo_distance = std::stod(value("nps_target_distance_cm"));
        } catch (const std::exception& ex) {
            std::cerr << "RunConfigParser: CSV parse error on line " << lineNo
                      << ": " << ex.what() << "\n";
            continue;
        }
        entries_.push_back(e);
    }

    if (entries_.empty()) {
        errorMsg_ = "No valid CSV entries parsed";
        return false;
    }
    return true;
}

bool RunConfigParser::parseKinCFile(std::ifstream& ifs) {
    std::string header;
    if (!std::getline(ifs, header)) {
        errorMsg_ = "Empty KinC config file";
        return false;
    }

    std::string line;
    std::string last_name;
    int lineNo = 1;
    while(std::getline(ifs, line)){
        ++lineNo;
        line = trim(line);
        if(line.empty()) continue;
        // replace tabs with spaces so we can use stringstream
        for(auto &c : line) if(c=='\t') c = ' ';
        // collapse multiple spaces into single space (for robust parsing)
        std::string tmp;
        bool lastWasSpace = false;
        for(char c: line){
            if(std::isspace((unsigned char)c)){
                if(!lastWasSpace){
                    tmp.push_back(' ');
                    lastWasSpace = true;
                }
            } else {
                tmp.push_back(c);
                lastWasSpace = false;
            }
        }
        std::istringstream ss(tmp);
        std::vector<std::string> cols;
        std::string tok;
        while(ss >> tok) cols.push_back(tok);

        // file format (based on provided sample):
        // 0: Simulation name (may be absent/blank)
        // 1: begin of run
        // 2: end of run
        // 3: SHMS angle
        // 4: E
        // 5: HMS P
        // 6: HMS angle
        // 7: NPS angle
        // 8: calo distance
        // 9: HMS_pol
        // Some lines in your sample are missing the name and rely on previous name; we handle that.

        if(cols.size() < 10){
            // allow lines where first column (name) is omitted: then cols.size()==9
            // or malformed: skip with warning
            if(cols.size() >= 9) {
                // prepend last_name so we can parse uniformly
                if(last_name.empty()){
                    // can't resolve name; skip
                    std::cerr << "RunConfigParser: skipping line " << lineNo << " (no simulation name available earlier)\n";
                    continue;
                }
                cols.insert(cols.begin(), last_name);
            } else {
                std::cerr << "RunConfigParser: skipping malformed line " << lineNo << " : '" << line << "'\n";
                continue;
            }
        }

        Entry e;
        e.name = cols[0];
        e.displayName = e.name;
        try {
            e.runBegin = std::stoi(cols[1]);
            e.runEnd   = std::stoi(cols[2]);
            e.shms_angle_deg = std::stod(cols[3]);
            e.E_GeV = std::stod(cols[4]);
            e.hms_p_GeV = std::stod(cols[5]);
            e.hms_angle_deg = std::stod(cols[6]);
            e.nps_angle_deg = std::stod(cols[7]);
            e.calo_distance = std::stod(cols[8]);
            e.hms_pol = std::stoi(cols[9]);
        } catch(const std::exception& ex) {
            std::cerr << "RunConfigParser: parse error on line " << lineNo << " : " << ex.what() << "\n";
            continue;
        }
        last_name = e.name;
        entries_.push_back(e);
    } // end lines

    if(entries_.empty()){
        errorMsg_ = "No valid KinC entries parsed";
        return false;
    }
    return true;
}

std::optional<Entry> RunConfigParser::FindByRun(int run) const {
    for(const auto &e : entries_){
        if(run >= e.runBegin && run <= e.runEnd) return e;
    }
    return std::nullopt;
}

std::optional<Entry> RunConfigParser::FindByName(const std::string& name) const {
    for(const auto &e : entries_){
        if(e.name == name) return e;
    }
    return std::nullopt;
}

bool RunConfigParser::ApplyConfigToGlobals(const Entry& e) const {
    // Both supported files store GeV, degrees, and calorimeter distance in cm.
    dvcsGlobals::Ebeam = e.E_GeV;
    dvcsGlobals::HMS_angle = e.hms_angle_deg * CLHEP::degree; 
    dvcsGlobals::HMS_momentum = e.hms_p_GeV;
    dvcsGlobals::Calo_angle = e.nps_angle_deg * CLHEP::degree;
    dvcsGlobals::Calo_distance = e.calo_distance * CLHEP::cm; 

    // Target is present in the CSV. Legacy KinC has no target column, so its
    // empty value deliberately preserves the existing global defaults.
    std::string target = e.target;
    std::transform(target.begin(), target.end(), target.begin(),
                   [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
    if (target == "LH2") {
        dvcsGlobals::target_type = 0;
        dvcsGlobals::target_gen_proc_type = 0;
    } else if (target == "LD2") {
        dvcsGlobals::target_type = 1;
        dvcsGlobals::target_gen_proc_type = 2;
    } else if (!target.empty()) {
        std::cerr << "RunConfigParser: unsupported target '" << e.target << "'\n";
        return false;
    }

    // Echo applied physics values for user verification before transport starts.
    std::cout << "RunConfigParser: applied '" << e.name << "' (" << e.displayName
              << ") runs " << e.runBegin << "-" << e.runEnd
              << " E=" << e.E_GeV << " HMS_p=" << e.hms_p_GeV << " HMS_angle(deg)=" << e.hms_angle_deg
              << " NPS_angle(deg)=" << e.nps_angle_deg << " calo_dist (cm)=" << e.calo_distance << "\n";

    return true;
}

bool RunConfigParser::LoadAndApplyByRun(int run) const {
    auto maybe = FindByRun(run);
    if(!maybe) return false;
    if (!ApplyConfigToGlobals(*maybe)) return false;
    // Keep exact requested run for NPS_SOFT database validity. Interval lookup
    // still uses inclusive KinC bounds; CSV entries have begin == end.
    dvcsGlobals::run_number = run;
    return true;
}

bool RunConfigParser::LoadAndApplyByName(const std::string& name) const {
    auto maybe = FindByName(name);
    if(!maybe) return false;
    if (!ApplyConfigToGlobals(*maybe)) return false;
    dvcsGlobals::run_number = maybe->runBegin;
    return true;
}

} // namespace RunConfig
