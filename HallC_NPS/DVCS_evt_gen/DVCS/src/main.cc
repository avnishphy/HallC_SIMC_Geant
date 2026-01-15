// // main.cc
// #include <iostream>
// #include <string>
// #include <memory>
// #include <limits> // *** ADDED for std::numeric_limits

// // ROOT
// #include "TFile.h"
// #include "TTree.h"
// #include "Rtypes.h"

// // Geant4
// #include "G4RunManagerFactory.hh"
// #include "G4UImanager.hh"
// #include "G4UIExecutive.hh"
// #include "G4VisExecutive.hh"
// #include "G4SystemOfUnits.hh"
// #include "G4RunManager.hh"
// #include "G4ios.hh"

// // Project
// #include "RunConfigParser.hh"
// #include "DetectorConstruction.hh"
// #include "PhysicsList.hh"
// #include "PrimaryGeneratorAction.hh"
// #include "RunAction.hh"
// #include "EventAction.hh"
// #include "HistoManager.hh"
// #include "dvcsGlobals.hh"

// // ------------------------------------------------------------
// void print_usage(const char* prog)
// {
//     std::cout
//         << "Usage:\n"
//         << "  " << prog
//         << " <simc.root> [tree] [nEvents] [out.root] [--batch] [--vis]\n";
// }


// // ------------------------------------------------------------
// int main(int argc, char** argv)
// {
//     std::string simc_path;
//     std::string simc_tree = "h10";
//     long        nEventsToRun = -1;
//     std::string output_root = "geant_output.root";
//     bool        batch_mode  = false;
//     bool        visualize   = false;

//     // ------------------- Parse run config -------------------
//     RunConfig::RunConfigParser cfg("../../../../KinC_list.txt");
//     if (!cfg.IsValid()) {
//         std::cerr << "RunConfigParser failed: " << cfg.ErrorMessage() << "\n";
//         return 4;
//     }

//     // Ask user for run number
//     int runNumber = 0;
//     std::cout << "Enter run number to simulate: ";
//     if(!(std::cin >> runNumber)) {
//         std::cerr << "Failed to read run number.\n";
//         return 6;
//     }

//     // *** IMPORTANT FIX: consume the leftover newline so getline works below ***
//     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

//     // Load and apply the config
//     if (!cfg.LoadAndApplyByRun(runNumber)) {
//         std::cerr << "ERROR: run number " << runNumber << " not found in KinC list\n";
//         return 5;
//     }

//     //bool   dvcsGlobals::SM_field_flag = true;
//     dvcsGlobals::SM_field_flag = false;
//     dvcsGlobals::SM_field_str  = 1.;

//     // ---------------- Argument parsing ----------------
//     if (argc < 2) {
//         print_usage(argv[0]);
//         // Prompt interactively for the SIMC file. Keep prompting until non-empty or EOF.
//         while (true) {
//             std::cout << "Enter SIMC ROOT file: ";
//             if (!std::getline(std::cin, simc_path)) {
//                 // EOF or error
//                 std::cerr << "\nNo input provided. Exiting.\n";
//                 return 1;
//             }
//             // trim leading/trailing whitespace (simple)
//             if (!simc_path.empty()) break;
//             std::cout << "Empty input; please enter the path to the SIMC ROOT file.\n";
//         }
//     } else {
//         simc_path = argv[1];
//         if (argc >= 3) simc_tree = argv[2];
//         if (argc >= 4) nEventsToRun = std::stol(argv[3]);
//         if (argc >= 5) output_root = argv[4];
//         for (int i = 5; i < argc; i++) {
//             std::string a = argv[i];
//             if (a == "--batch") batch_mode = true;
//             if (a == "--vis")   visualize  = true;
//         }
//     }

//     // ---------------- SIMC sanity check ----------------
//     TFile* tf = TFile::Open(simc_path.c_str(), "READ");
//     if (!tf || tf->IsZombie()) {
//         std::cerr << "ERROR: cannot open SIMC file " << simc_path << "\n";
//         return 2;
//     }

//     TTree* t = dynamic_cast<TTree*>(tf->Get(simc_tree.c_str()));
//     if (!t) {
//         std::cerr << "ERROR: tree " << simc_tree << " not found\n";
//         tf->Close();
//         delete tf;
//         return 3;
//     }

//     Long64_t simcEntries = t->GetEntries();
//     tf->Close();
//     delete tf;

//     if (nEventsToRun <= 0 || nEventsToRun > simcEntries)
//         nEventsToRun = simcEntries;

//     std::cout << "SIMC entries: " << simcEntries << "\n";
//     std::cout << "Will run     : " << nEventsToRun << " events\n";

//     // --- Print dvcsGlobals for debugging ---
//     std::cout << "\n===== dvcsGlobals =====\n";
//     std::cout << "run_number           : " << dvcsGlobals::run_number << "\n";
//     std::cout << "Ebeam (GeV)         : " << dvcsGlobals::Ebeam << "\n";
//     std::cout << "HMS_angle (rad)     : " << dvcsGlobals::HMS_angle << "\n";
//     std::cout << "HMS_momentum (GeV)  : " << dvcsGlobals::HMS_momentum << "\n";
//     std::cout << "Calo_distance (mm)  : " << dvcsGlobals::Calo_distance << "\n";
//     std::cout << "Calo_angle (rad)    : " << dvcsGlobals::Calo_angle << "\n";
//     std::cout << "target_type          : " << dvcsGlobals::target_type << "\n";
//     std::cout << "target_gen_proc_type : " << dvcsGlobals::target_gen_proc_type << "\n";
//     std::cout << "target_density       : " << dvcsGlobals::target_density << "\n";
//     std::cout << "target_offset        : " << dvcsGlobals::target_offset << "\n";
//     std::cout << "target_length        : " << dvcsGlobals::target_length << "\n";
//     std::cout << "hit_HMS_CALO_flag    : " << dvcsGlobals::hit_HMS_CALO_flag << "\n";
//     std::cout << "SM_field_flag        : " << dvcsGlobals::SM_field_flag << "\n";
//     std::cout << "SM_field_str         : " << dvcsGlobals::SM_field_str << "\n";
//     std::cout << "SM_angle             : " << dvcsGlobals::SM_angle << "\n";
//     std::cout << "=======================\n\n";


//     // ---------------- RunManager ----------------
//     auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Serial);

//     // ---------------- Detector ----------------
//     const G4bool   useSIMCGeometry = true;
//     const G4double targetZ         = 0.0 * CLHEP::cm;

//     auto* detector = new DetectorConstruction(
//         dvcsGlobals::Calo_distance,
//         dvcsGlobals::Calo_angle,
//         dvcsGlobals::SM_field_flag,
//         dvcsGlobals::SM_field_str
//     );
//     runManager->SetUserInitialization(detector);

//     // ---------------- Physics ----------------
//     runManager->SetUserInitialization(new PhysicsList());

//     // ---------------- Histogram manager ----------------
//     auto* histo = new HistoManager();
//     histo->Book(output_root, simc_path, simc_tree);

//     // ---------------- RunAction ----------------
//     auto* runAction = new RunAction(
//         histo,
//         "DVCS",
//         0,
//         0,
//         nEventsToRun
//     );
//     runManager->SetUserAction(runAction);

//     // ---------------- EventAction ----------------
//     auto* eventAction = new EventAction(runAction, histo);
//     runManager->SetUserAction(eventAction);

//     // ---------------- Primary generator ----------------
//     auto* primary = new PrimaryGeneratorAction(
//         eventAction,
//         TString(simc_path),
//         TString(simc_tree)
//     );
//     runManager->SetUserAction(primary);

//     // ---------------- Initialize ----------------
//     runManager->Initialize();

//     auto* uiManager = G4UImanager::GetUIpointer();

//     // ---------------- Visualization / Batch ----------------
//     if (visualize) {
//         auto* visManager = new G4VisExecutive();
//         visManager->Initialize();

//         auto* uiExec = new G4UIExecutive(argc, argv);
//         uiManager->ApplyCommand("/control/execute ../macros/vis.mac");
//         uiExec->SessionStart();

//         delete uiExec;
//         delete visManager;
//     } else {
//         uiManager->ApplyCommand("/run/initialize");

//         G4cout << "Requesting /run/beamOn " << nEventsToRun << G4endl;
//         uiManager->ApplyCommand("/run/beamOn " + std::to_string(nEventsToRun));
//     }

//     delete histo;

//     std::cout << "DONE. Output: " << output_root << "\n";
//     return 0;
// }


// main.cc
#include <iostream>
#include <string>
#include <memory>
#include <limits> // for std::numeric_limits
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip> // for setw

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

// ------------------------------------------------------------
// Print a simple kinclist showing: run_number   <kinematic description>
// - skips blank lines and comment lines (starting with # or //)
// - assumes the kinclist entries are one-per-line; the first token is treated
//   as the run number, and the remainder of the line as a kinematic descriptor.
// - prints up to maxPrint lines (default 200), and shows a count of total non-empty entries.
static void PrintKinCList(const std::string& kinclistPath, std::size_t maxPrint = 200)
{
    std::ifstream in(kinclistPath);
    if (!in.is_open()) {
        std::cerr << "Warning: cannot open KinC list file: " << kinclistPath << "\n";
        return;
    }

    std::string line;
    std::size_t printed = 0;
    std::size_t totalNonEmpty = 0;

    // First pass counts non-empty, non-comment lines so we can display total.
    // (We re-open the file for actual printing.)
    {
        std::ifstream in2(kinclistPath);
        while (std::getline(in2, line)) {
            // trim leading whitespace
            std::string tmp = line;
            auto pos = tmp.find_first_not_of(" \t\r\n");
            if (pos == std::string::npos) continue; // blank
            tmp = tmp.substr(pos);
            if (tmp.rfind("#", 0) == 0) continue;   // comment starting with #
            if (tmp.rfind("//", 0) == 0) continue;  // comment starting with //
            totalNonEmpty++;
        }
    }

    // Print header
    std::cout << "\n===== KinC list (showing up to " << maxPrint << " entries) =====\n";
    std::cout << std::left << std::setw(12) << "RunNumber" << "  " << "Kinematic (rest of line)\n";
    std::cout << "--------------------------------------------------------\n";

    // Re-open and print entries
    in.clear();
    in.seekg(0);
    while (std::getline(in, line)) {
        // trim leading whitespace
        auto pos = line.find_first_not_of(" \t\r\n");
        if (pos == std::string::npos) continue; // blank
        std::string tmp = line.substr(pos);
        if (tmp.rfind("#", 0) == 0) continue;   // comment
        if (tmp.rfind("//", 0) == 0) continue;  // comment

        // parse first token as run number, remainder as kinematic description
        std::istringstream iss(tmp);
        std::string runToken;
        if (!(iss >> runToken)) continue;
        std::string kinDesc;
        std::getline(iss, kinDesc);
        // trim leading spaces from kinDesc
        auto kinPos = kinDesc.find_first_not_of(" \t");
        if (kinPos != std::string::npos) kinDesc = kinDesc.substr(kinPos);
        else kinDesc = "";

        // print
        std::cout << std::left << std::setw(12) << runToken << "  " << kinDesc << "\n";

        printed++;
        if (printed >= maxPrint) break;
    }
    std::cout << "--------------------------------------------------------\n";
    std::cout << "Displayed " << printed << " entries";
    if (totalNonEmpty > printed) std::cout << " (of " << totalNonEmpty << " total non-empty entries)";
    std::cout << ".\n\n";
    in.close();
}

void print_usage(const char* prog)
{
    std::cout
        << "Usage:\n"
        << "  " << prog
        << " <simc.root> [tree] [nEvents] [out.root] [--batch] [--vis]\n";
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

    // ------------------- Parse run config -------------------
    // KinC list location (same relative path you've been using)
    const std::string kinclist_path = "../../../../KinC_list.txt";
    RunConfig::RunConfigParser cfg(kinclist_path);
    if (!cfg.IsValid()) {
        std::cerr << "RunConfigParser failed: " << cfg.ErrorMessage() << "\n";
        // still try to print the KinC file directly so user can inspect it
        PrintKinCList(kinclist_path, 200);
        return 4;
    }

    // Print a compact kinclist to let the user choose a run number
    PrintKinCList(kinclist_path, 200);

    // Ask user for run number
    int runNumber = 0;
    std::cout << "Enter run number to simulate: ";
    if(!(std::cin >> runNumber)) {
        std::cerr << "Failed to read run number.\n";
        return 6;
    }

    // consume leftover newline so getline works below
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Load and apply the config
    if (!cfg.LoadAndApplyByRun(runNumber)) {
        std::cerr << "ERROR: run number " << runNumber << " not found in KinC list\n";
        return 5;
    }

    // set dvcsGlobals flags as before
    dvcsGlobals::SM_field_flag = false;
    dvcsGlobals::SM_field_str  = 1.;

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
        simc_path = argv[1];
        if (argc >= 3) simc_tree = argv[2];
        if (argc >= 4) nEventsToRun = std::stol(argv[3]);
        if (argc >= 5) output_root = argv[4];
        for (int i = 5; i < argc; i++) {
            std::string a = argv[i];
            if (a == "--batch") batch_mode = true;
            if (a == "--vis")   visualize  = true;
        }
    }

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
        dvcsGlobals::SM_field_str
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
    auto* eventAction = new EventAction(runAction, histo);
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
        uiManager->ApplyCommand("/control/execute ../macros/vis.mac");
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
