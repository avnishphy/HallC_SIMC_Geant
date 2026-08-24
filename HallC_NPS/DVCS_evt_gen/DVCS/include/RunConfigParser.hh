#pragma once
#include <iosfwd>
#include <string>
#include <vector>
#include <optional>

namespace RunConfig {

struct Entry {
    std::string name;
    std::string displayName;
    std::string target;
    int runBegin = -1;
    int runEnd = -1;
    double shms_angle_deg = 0.0;
    double E_GeV = 0.0;
    double hms_p_GeV = 0.0;
    double hms_angle_deg = 0.0;
    double nps_angle_deg = 0.0;
    double calo_distance = 0.0; // cm in both supported formats
    int hms_pol = 0;
};

class RunConfigParser {
public:
    // Format is selected from the file extension: .csv uses the shared
    // simulation table; other files use the legacy whitespace KinC format.
    explicit RunConfigParser(const std::string& path);
    bool IsValid() const;

    const std::vector<Entry>& Entries() const { return entries_; }

    // find entry covering given run number (runBegin <= run <= runEnd)
    // returns std::nullopt if not found
    std::optional<Entry> FindByRun(int run) const;

    // find by simulation name (exact match)
    std::optional<Entry> FindByName(const std::string& name) const;

    // Convenience: apply the entry to dvcsGlobals (does the mapping)
    // returns true if applied
    bool ApplyConfigToGlobals(const Entry& e) const;

    // Convenience: load & apply by run number (FindByRun + Apply)
    bool LoadAndApplyByRun(int run) const;

    // Convenience: load & apply by name
    bool LoadAndApplyByName(const std::string& name) const;

    // if parsing failed, this returns an error message
    std::string ErrorMessage() const { return errorMsg_; }

private:
    bool parseFile(const std::string& path);
    bool parseCsvFile(std::ifstream& input);
    bool parseKinCFile(std::ifstream& input);
    std::vector<Entry> entries_;
    bool valid_ = false;
    std::string errorMsg_;
};

} // namespace RunConfig
