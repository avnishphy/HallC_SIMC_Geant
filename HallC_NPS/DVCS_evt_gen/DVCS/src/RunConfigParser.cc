#include "RunConfigParser.hh"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>
#include "TMath.h"
#include "G4SystemOfUnits.hh"

// include your dvcsGlobals header
#include "dvcsGlobals.hh" // adjust path if different

namespace RunConfig {

static inline std::string trim(const std::string& s) {
    auto b = s.find_first_not_of(" \t\r\n");
    if(b==std::string::npos) return "";
    auto e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e-b+1);
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

    std::string header;
    if(!std::getline(ifs, header)){
        errorMsg_ = "Empty config file";
        return false;
    }
    // we accept header line (ignored). Now parse rows.
    std::string line;
    std::string last_name = "";
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
        errorMsg_ = "No valid entries parsed";
        return false;
    }
    valid_ = true;
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
    // NOTE: adjust variable names if your dvcsGlobals uses different names
    // convert angles from degrees -> radians for Geant4 usage
    dvcsGlobals::Ebeam = e.E_GeV;
    dvcsGlobals::HMS_angle = e.hms_angle_deg * CLHEP::degree; 
    dvcsGlobals::HMS_momentum = e.hms_p_GeV;
    dvcsGlobals::Calo_angle = e.nps_angle_deg * CLHEP::degree;
    // Calo_distance units: assume file value is [cm]. dvcsGlobals used earlier expects [cm].
    dvcsGlobals::Calo_distance = e.calo_distance * CLHEP::cm; 
    // store run number for convenience
    dvcsGlobals::run_number = e.runBegin; // or pick a canonical value (begin). You could store the full entry in dvcsGlobals if desired.

    // optional: print to console for confirmation
    std::cout << "RunConfigParser: Applied config '" << e.name << "' runs " << e.runBegin << "-" << e.runEnd
              << " E=" << e.E_GeV << " HMS_p=" << e.hms_p_GeV << " HMS_angle(deg)=" << e.hms_angle_deg
              << " NPS_angle(deg)=" << e.nps_angle_deg << " calo_dist (cm)=" << e.calo_distance << "\n";

    return true;
}

bool RunConfigParser::LoadAndApplyByRun(int run) const {
    auto maybe = FindByRun(run);
    if(!maybe) return false;
    return ApplyConfigToGlobals(*maybe);
}

bool RunConfigParser::LoadAndApplyByName(const std::string& name) const {
    auto maybe = FindByName(name);
    if(!maybe) return false;
    return ApplyConfigToGlobals(*maybe);
}

} // namespace RunConfig
