// main.cc
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip> // for setw
#include <cstdlib>
#include <cmath>
#include <optional>

// ROOT
#include "TFile.h"
#include "TTree.h"
#include "Rtypes.h"

// Geant4
#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4ios.hh"

// Project
#include "RunConfigParser.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "HistoManager.hh"
#include "dvcsGlobals.hh"

#ifndef DVCS_SOURCE_DIR
#define DVCS_SOURCE_DIR "."
#endif

#ifndef DVCS_BINARY_DIR
#define DVCS_BINARY_DIR "."
#endif

#ifndef DVCS_REPOSITORY_DIR
#define DVCS_REPOSITORY_DIR "."
#endif

// ------------------------------------------------------------
// Print already-parsed values so CSV and KinC users see the same units/columns.
static void PrintRunConfigs(const RunConfig::RunConfigParser& config,
                            std::size_t maxPrint = 200)
{
    const auto& entries = config.Entries();
    std::cout << "\nAvailable kinematic settings:\n";
    std::cout << std::left << std::setw(13) << "Run(s)"
              << std::setw(18) << "KinC" << std::setw(15) << "New kin"
              << "Ebeam  HMS_P  HMS_deg  NPS_deg  Dist_cm\n";
    std::cout << "-------------------------------------------------------------------------------\n";
    std::size_t printed = 0;
    for (const auto& e : entries) {
        std::ostringstream runs;
        runs << e.runBegin;
        if (e.runEnd != e.runBegin) runs << "-" << e.runEnd;
        std::cout << std::left << std::setw(13) << runs.str()
                  << std::setw(18) << e.name << std::setw(15) << e.displayName
                  << std::fixed << std::setprecision(3)
                  << std::setw(7) << e.E_GeV << std::setw(7) << e.hms_p_GeV
                  << std::setw(9) << e.hms_angle_deg << std::setw(9) << e.nps_angle_deg
                  << e.calo_distance << "\n";
        if (++printed >= maxPrint) break;
    }
    if (entries.size() > printed) std::cout << "... " << entries.size() - printed << " more\n";
    std::cout << "\n";
}

void print_usage(const char* prog)
{
    std::cout
        << "Usage:\n"
        << "  " << prog
        << " <simc.root> [tree] [nEvents] [out.root] "
        << "[--batch] [--vis|--vis-single|--vis-seq] "
        << "[--config-source csv|kinc] [--config-file PATH] [--run RUN] [--sweeper-material DEG]\n"
        << "\n"
        << "Visualization options:\n"
        << "  --vis         : open UI with detector view, event stepping manual via /run/beamOn 1\n"
        << "  --vis-single  : open UI and run exactly one event automatically\n"
        << "  --vis-seq     : open UI in sequential stepping mode (one event at a time)\n"
        << "  --config-source: choose shared CSV or legacy KinC list (prompted if omitted)\n"
        << "  --config-file : override selected configuration path\n"
        << "  --sweeper-material DEG : place sweep magnet at this angle relative to the NPS arm (degrees)\n"
        << "  --run         : select run without the run-number prompt\n";
}

static void ConfigureMacroSearchPath(G4UImanager* uiManager)
{
    std::vector<std::string> macroPaths = {
        ".",
        "./macros",
        "../macros",
        std::string(DVCS_BINARY_DIR),
        std::string(DVCS_BINARY_DIR) + "/macros",
        std::string(DVCS_SOURCE_DIR) + "/macros"
    };

    std::ostringstream path;
    for (std::size_t i = 0; i < macroPaths.size(); ++i) {
        if (i != 0) path << ":";
        path << macroPaths[i];
    }

    uiManager->ApplyCommand("/control/macroPath " + path.str());
}

static bool ExecuteFirstAvailableMacro(
    G4UImanager* uiManager,
    const std::vector<std::string>& candidateMacros)
{
    for (const auto& macro : candidateMacros) {
        if (uiManager->ApplyCommand("/control/execute " + macro) == 0) {
            G4cout << "Loaded visualization macro: " << macro << G4endl;
            return true;
        }
    }
    return false;
}

// ------------------------------------------------------------
int main(int argc, char** argv)
{
    std::string simc_path;
    std::string simc_tree = "h10";
    long        nEventsToRun = -1;
    std::string output_root = "geant_output.root";
    bool        batch_mode  = false;
    bool        visualize   = false;
    std::string vis_macro   = "vis_setup.mac";
    std::string configSource;
    std::string configFile;
    int         runNumber = -1;
    std::optional<double> sweeperAngleDeg;

    // ---------------- Argument parsing ----------------
    if (argc < 2) {
        print_usage(argv[0]);
        // Prompt interactively for the SIMC file. Keep prompting until non-empty or EOF.
        while (true) {
            std::cout << "Enter SIMC ROOT file: ";
            if (!std::getline(std::cin, simc_path)) {
                // EOF or error
                std::cerr << "\nNo input provided. Exiting.\n";
                return 1;
            }
            // trim leading/trailing whitespace (simple)
            if (!simc_path.empty()) break;
            std::cout << "Empty input; please enter the path to the SIMC ROOT file.\n";
        }
    } else {
        std::vector<std::string> positional;
        positional.reserve(static_cast<std::size_t>(argc));

        for (int i = 1; i < argc; ++i) {
            std::string a = argv[i];
            if (a == "--help" || a == "-h") {
                print_usage(argv[0]);
                return 0;
            }
            if (a == "--config-source" || a == "--config-file" || a == "--run") {
                if (i + 1 >= argc) {
                    std::cerr << "ERROR: " << a << " requires a value.\n";
                    return 1;
                }
                const std::string value = argv[++i];
                if (a == "--config-source") {
                    configSource = value;
                } else if (a == "--config-file") {
                    configFile = value;
                } else {
                    try {
                        runNumber = std::stoi(value);
                    } catch (const std::exception&) {
                        std::cerr << "ERROR: --run requires an integer, got '" << value << "'.\n";
                        return 1;
                    }
                }
                continue;
            }
            if (a == "--sweeper-material") {
                double angle;
                std::istringstream value(i + 1 < argc ? argv[++i] : "");
                if (!(value >> angle) || !value.eof() || !std::isfinite(angle)) {
                    std::cerr << "ERROR: --sweeper-material requires a finite angle in degrees.\n";
                    return 1;
                }
                sweeperAngleDeg = angle;
                continue;
            }
            if (a == "--batch") {
                batch_mode = true;
                continue;
            }
            if (a == "--vis") {
                visualize = true;
                vis_macro = "vis_setup.mac";
                continue;
            }
            if (a == "--vis-single") {
                visualize = true;
                vis_macro = "vis_single.mac";
                continue;
            }
            if (a == "--vis-seq" || a == "--vis-sequential") {
                visualize = true;
                vis_macro = "vis_sequential.mac";
                continue;
            }
            positional.push_back(a);
        }

        if (positional.empty()) {
            print_usage(argv[0]);
            std::cerr << "ERROR: missing required SIMC ROOT file argument.\n";
            return 1;
        }

        simc_path = positional[0];
        if (positional.size() >= 2) simc_tree = positional[1];
        if (positional.size() >= 3) {
            try {
                nEventsToRun = std::stol(positional[2]);
            } catch (const std::exception&) {
                std::cerr << "ERROR: nEvents must be an integer, got '" << positional[2] << "'.\n";
                return 1;
            }
        }
        if (positional.size() >= 4) output_root = positional[3];
        if (positional.size() > 4) {
            print_usage(argv[0]);
            std::cerr << "ERROR: too many positional arguments were provided.\n";
            return 1;
        }

        if (batch_mode && visualize) {
            std::cout << "Note: both --batch and visualization flags were set; running in visualization mode.\n";
        }
    }

    // ---------------- Kinematic configuration ----------------
    const char* csvEnv = std::getenv("NPS_SIMULATION_KINEMATICS_CSV");
    const std::string csvPath = csvEnv && *csvEnv
        ? csvEnv
        : std::string(DVCS_REPOSITORY_DIR)
          + "/../nps_analysis/pi0_analysis/root_analysis_env_main/config/"
            "nps_simulation_kinematics.csv";
    const std::string kincPath = std::string(DVCS_REPOSITORY_DIR) + "/KinC_list.txt";

    if (configSource.empty()) {
        std::cout
            << "\nSelect kinematic configuration source:\n"
            << "  1. nps_simulation_kinematics.csv [default]\n"
            << "     " << csvPath << "\n"
            << "  2. KinC_list.txt (legacy)\n"
            << "     " << kincPath << "\n"
            << "Selection [1]: ";
        std::string selection;
        if (!std::getline(std::cin, selection)) {
            std::cin.clear();
            selection.clear();
        }
        if (selection.empty() || selection == "1") {
            configSource = "csv";
        } else if (selection == "2") {
            configSource = "kinc";
        } else {
            std::cerr << "ERROR: selection must be 1 or 2.\n";
            return 4;
        }
    }

    if (configSource != "csv" && configSource != "kinc") {
        std::cerr << "ERROR: --config-source must be 'csv' or 'kinc'.\n";
        return 4;
    }
    if (configFile.empty()) configFile = configSource == "csv" ? csvPath : kincPath;

    RunConfig::RunConfigParser cfg(configFile);
    if (!cfg.IsValid()) {
        std::cerr << "ERROR: configuration load failed: " << cfg.ErrorMessage() << "\n";
        if (configSource == "csv") {
            std::cerr << "Set NPS_SIMULATION_KINEMATICS_CSV or pass --config-file PATH.\n";
        }
        return 4;
    }
    std::cout << "Using configuration: " << configFile << "\n";
    PrintRunConfigs(cfg);

    if (runNumber < 0) {
        std::cout << "Enter run number to simulate: ";
        std::string runText;
        if (!std::getline(std::cin, runText)) {
            std::cerr << "Failed to read run number.\n";
            return 6;
        }
        try {
            runNumber = std::stoi(runText);
        } catch (const std::exception&) {
            std::cerr << "Run number must be an integer.\n";
            return 6;
        }
    }

    if (!cfg.LoadAndApplyByRun(runNumber)) {
        std::cerr << "ERROR: run " << runNumber << " not found in " << configFile << "\n";
        return 5;
    }

    // Material placement and field strength are independent.
    if (sweeperAngleDeg) dvcsGlobals::SM_angle = *sweeperAngleDeg * CLHEP::degree;
    dvcsGlobals::SM_field_flag = false;
    dvcsGlobals::SM_field_str  = 1.;

    // ---------------- SIMC sanity check ----------------
    TFile* tf = TFile::Open(simc_path.c_str(), "READ");
    if (!tf || tf->IsZombie()) {
        std::cerr << "ERROR: cannot open SIMC file " << simc_path << "\n";
        return 2;
    }

    TTree* t = dynamic_cast<TTree*>(tf->Get(simc_tree.c_str()));
    if (!t) {
        std::cerr << "ERROR: tree " << simc_tree << " not found\n";
        tf->Close();
        delete tf;
        return 3;
    }

    Long64_t simcEntries = t->GetEntries();
    tf->Close();
    delete tf;

    if (nEventsToRun <= 0 || nEventsToRun > simcEntries)
        nEventsToRun = simcEntries;

    std::cout << "SIMC entries: " << simcEntries << "\n";
    std::cout << "Will run     : " << nEventsToRun << " events\n";

    // --- Print dvcsGlobals for debugging ---
    std::cout << "\n===== dvcsGlobals =====\n";
    std::cout << "run_number           : " << dvcsGlobals::run_number << "\n";
    std::cout << "Ebeam (GeV)         : " << dvcsGlobals::Ebeam << "\n";
    std::cout << "HMS_angle (rad)     : " << dvcsGlobals::HMS_angle << "\n";
    std::cout << "HMS_momentum (GeV)  : " << dvcsGlobals::HMS_momentum << "\n";
    std::cout << "Calo_distance (mm)  : " << dvcsGlobals::Calo_distance << "\n";
    std::cout << "Calo_angle (rad)    : " << dvcsGlobals::Calo_angle << "\n";
    std::cout << "target_type          : " << dvcsGlobals::target_type << "\n";
    std::cout << "target_gen_proc_type : " << dvcsGlobals::target_gen_proc_type << "\n";
    std::cout << "target_density       : " << dvcsGlobals::target_density << "\n";
    std::cout << "target_offset        : " << dvcsGlobals::target_offset << "\n";
    std::cout << "target_length        : " << dvcsGlobals::target_length << "\n";
    std::cout << "hit_HMS_CALO_flag    : " << dvcsGlobals::hit_HMS_CALO_flag << "\n";
    std::cout << "SM_field_flag        : " << dvcsGlobals::SM_field_flag << "\n";
    std::cout << "SM_field_str         : " << dvcsGlobals::SM_field_str << "\n";
    std::cout << "SM_material_placed   : " << (sweeperAngleDeg.has_value() || dvcsGlobals::SM_field_flag) << "\n";
    std::cout << "SM_angle             : " << dvcsGlobals::SM_angle << "\n";
    std::cout << "=======================\n\n";

    // ---------------- RunManager ----------------
    auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Serial);

    // ---------------- Detector ----------------
    const G4bool   useSIMCGeometry = true;
    const G4double targetZ         = 0.0 * CLHEP::cm;

    auto* detector = new DetectorConstruction(
        dvcsGlobals::Calo_distance,
        dvcsGlobals::Calo_angle,
        dvcsGlobals::SM_field_flag,
        dvcsGlobals::SM_field_str,
        sweeperAngleDeg.has_value()
    );
    runManager->SetUserInitialization(detector);

    // ---------------- Physics ----------------
    runManager->SetUserInitialization(new PhysicsList());

    // ---------------- Histogram manager ----------------
    auto* histo = new HistoManager();
    histo->Book(output_root, simc_path, simc_tree);

    // ---------------- RunAction ----------------
    auto* runAction = new RunAction(
        histo,
        "DVCS",
        0,
        0,
        nEventsToRun
    );
    runManager->SetUserAction(runAction);

    // ---------------- EventAction ----------------
    auto* eventAction = new EventAction(runAction, histo, detector);
    runManager->SetUserAction(eventAction);

    // ---------------- Primary generator ----------------
    auto* primary = new PrimaryGeneratorAction(
        eventAction,
        TString(simc_path),
        TString(simc_tree)
    );
    runManager->SetUserAction(primary);

    // ---------------- Initialize ----------------
    runManager->Initialize();

    auto* uiManager = G4UImanager::GetUIpointer();

    // ---------------- Visualization / Batch ----------------
    if (visualize) {
        auto* visManager = new G4VisExecutive();
        visManager->Initialize();

        auto* uiExec = new G4UIExecutive(argc, argv);
        ConfigureMacroSearchPath(uiManager);

        std::vector<std::string> macroCandidates = {
            vis_macro,
            "./macros/" + vis_macro,
            "macros/" + vis_macro,
            "../macros/" + vis_macro,
            std::string(DVCS_BINARY_DIR) + "/" + vis_macro,
            std::string(DVCS_BINARY_DIR) + "/macros/" + vis_macro,
            std::string(DVCS_SOURCE_DIR) + "/macros/" + vis_macro
        };
        if (vis_macro != "vis.mac") {
            macroCandidates.push_back("vis.mac");
            macroCandidates.push_back("./macros/vis.mac");
            macroCandidates.push_back("macros/vis.mac");
            macroCandidates.push_back("../macros/vis.mac");
            macroCandidates.push_back(std::string(DVCS_BINARY_DIR) + "/vis.mac");
            macroCandidates.push_back(std::string(DVCS_BINARY_DIR) + "/macros/vis.mac");
            macroCandidates.push_back(std::string(DVCS_SOURCE_DIR) + "/macros/vis.mac");
        }

        if (!ExecuteFirstAvailableMacro(uiManager, macroCandidates)) {
            G4cerr << "WARNING: could not load any visualization macro candidate for mode '"
                   << vis_macro
                   << "'. Use /control/execute <path-to-macro> manually." << G4endl;
        }

        uiExec->SessionStart();

        delete uiExec;
        delete visManager;
    } else {
        uiManager->ApplyCommand("/run/initialize");

        G4cout << "Requesting /run/beamOn " << nEventsToRun << G4endl;
        uiManager->ApplyCommand("/run/beamOn " + std::to_string(nEventsToRun));
    }

    delete histo;

    std::cout << "DONE. Output: " << output_root << "\n";
    return 0;
}
