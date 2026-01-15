// HistoManager.cc

#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TLeaf.h>
#include <TBranch.h>
#include <TObjArray.h>
#include <TObjString.h>
#include <TClass.h>
#include <TROOT.h>
#include <TSystem.h>

#include <CLHEP/Units/SystemOfUnits.h>

#include "HistoManager.hh"
#include "G4UnitsTable.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4ios.hh"

#include <iostream>
#include <sstream>
#include <cstring>
#include <map>
#include <string>
#include <cmath>
#include <vector>

// helper to allocate typed buffer
static void* AllocBufferForLeafType(const std::string& typetag)
{
    if(typetag.find("Float") != std::string::npos || typetag.find("float") != std::string::npos) {
        return new Float_t(0.);
    } else if(typetag.find("Double") != std::string::npos || typetag.find("double") != std::string::npos) {
        return new Double_t(0);
    } else if(typetag.find("Int") != std::string::npos || typetag.find("int") != std::string::npos) {
        return new Int_t(0);
#if defined(Long64_t)
    } else if(typetag.find("Long64") != std::string::npos || typetag.find("long") != std::string::npos) {
        return new Long64_t(0);
#endif
    } else if(typetag.find("Bool") != std::string::npos || typetag.find("bool") != std::string::npos) {
        return new Bool_t(kFALSE);
    }
    return nullptr;
}

// helper leaf format code (for Branch leaflist)
static std::string LeafFormatForType(const std::string& typetag)
{
    if(typetag.find("Float") != std::string::npos || typetag.find("float") != std::string::npos) {
        return "/F";
    } else if(typetag.find("Double") != std::string::npos || typetag.find("double") != std::string::npos) {
        return "/D";
    } else if(typetag.find("Int") != std::string::npos || typetag.find("int") != std::string::npos) {
        return "/I";
#if defined(Long64_t)
    } else if(typetag.find("Long64") != std::string::npos || typetag.find("long") != std::string::npos) {
        return "/L";
#endif
    } else if(typetag.find("Bool") != std::string::npos || typetag.find("bool") != std::string::npos) {
        return "/O";
    }
    return "";
}

// -----------------------------------------------------------------------------
// File-static cluster buffers (persist across Fill() calls). These are used
// as addresses for the TTree branches so we don't need to change the class
// layout in the header.
static Int_t sNbClusters = 0;
static std::vector<Double_t> sClust_E;
static std::vector<Double_t> sClust_X;
static std::vector<Double_t> sClust_Y;
static std::vector<Int_t> sClust_Size;
// -----------------------------------------------------------------------------

HistoManager::HistoManager()
    : fRootFile(nullptr),
      fNtuple_DVCS(nullptr),
      fSimcFile(nullptr),
      fSimcTree(nullptr),
      fSimcPath(""),
      fSimcTreeName("")
{
    // initialize default values
    fEvtNb = -1;
    fClust_Ene1 = -999.;
    fClust_X1 = -999.;
    fClust_Y1 = -999.;
    fClust_size1 = -1;
    fClust_Ene2 = -999.;
    fClust_X2 = -999.;
    fClust_Y2 = -999.;
    fClust_size2 = -1;
    fClust_W2 = -999.;
    fPSF = -999.;
    fRIE_Px = fRIE_Py = fRIE_Pz = -999.;
    fGIE_Px = fGIE_Py = fGIE_Pz = -999.;
    fRSE_Px = fRSE_Py = fRSE_Pz = -999.;
    fGSE_Px = fGSE_Py = fGSE_Pz = -999.;
    fRP_Px1 = fRP_Py1 = fRP_Pz1 = -999.;
    fGP_Px1 = fGP_Py1 = fGP_Pz1 = -999.;
    fRP_Px2 = fRP_Py2 = fRP_Pz2 = -999.;
    fGP_Px2 = fGP_Py2 = fGP_Pz2 = -999.;
    fRM = fGM = -999.;
    fRV_Z = -999.;
    fGV_X = fGV_Y = fGV_Z = -999.;
    fRt = fGt = fRxB = fGxB = fRQ2 = fGQ2 = fRphi = fGphi = -999.;
    fX_sum = fX_diff = fX_BH = -999.;
    fRr_val = fGr_val = -999.;

    fEvtNb_ = -1;
    fClust_X_ = fClust_Y_ = fClust_Ene_ = fClust_Px_ = fClust_Py_ = fClust_Pz_ = -999.;

    fFluxEnergy_gamma = fTheta_gamma = fPhi_gamma = -999.;
    fFluxEnergy_pos = fTheta_pos = fPhi_pos = -999.;
    fFluxEnergy_elec = fTheta_elec = fPhi_elec = -999.;
    fFluxEnergy_unknown = -999.;
    fFluxPID_unknown = -999;

    fFluxEvtNb = -1;
    fFluxMomX_OptFiber_gamma = fFluxMomY_OptFiber_gamma = fFluxMomZ_OptFiber_gamma = -999.;
    fFluxMomX_OptFiber_pos = fFluxMomY_OptFiber_pos = fFluxMomZ_OptFiber_pos = -999.;
    fFluxMomX_OptFiber_elec = fFluxMomY_OptFiber_elec = fFluxMomZ_OptFiber_elec = -999.;
    fFluxMomX_OptFiber_unknown = fFluxMomY_OptFiber_unknown = fFluxMomZ_OptFiber_unknown = -999.;

    fFluxEnergy_OptFiber_gamma = fGlobalX_OptFiber_gamma = fGlobalY_OptFiber_gamma = fGlobalZ_OptFiber_gamma = -999.;
    fLocalX_OptFiber_gamma = fLocalY_OptFiber_gamma = fLocalZ_OptFiber_gamma = -999.;

    // zero arrays
    for(int i=0;i<MaxNtuple;i++){
        fEdep[i] = 0.;
        fPID[i] = 0;
        fOP_sc[i] = 0;
        fOP_ce[i] = 0;
        fOP_cover[i] = 0;
        fOP_frontcover[i] = 0;
        fOP_pmtcover[i] = 0;
        fFluxEne[i] = 0.;
        fFluxPID[i] = 0;
    }

    // photon hit defaults
    fPhot1Hit = false;
    fPhot2Hit = false;
    fPhot1_vx = fPhot1_vy = fPhot1_vz = -999.;
    fPhot2_vx = fPhot2_vy = fPhot2_vz = -999.;
    fPhot1_hitx = fPhot1_hity = fPhot1_hitz = -999.;
    fPhot2_hitx = fPhot2_hity = fPhot2_hitz = -999.;
    fPhot1_clustx = fPhot1_clusty = fPhot1_clustz = -999.;
    fPhot2_clustx = fPhot2_clusty = fPhot2_clustz = -999.;
    fPhot1_Ecal = fPhot2_Ecal = -999.;
    fPhot1_clustSize = fPhot2_clustSize = -1;
}

HistoManager::~HistoManager()
{
    // free dynamic simc buffers
    for(auto &kv : fSimcBuffers){
        void* p = kv.second;
        if(!p) continue;
        // delete by guessed type
        std::string fmt = fSimcLeafFormat[kv.first];
        if(fmt == "/F") delete static_cast<Float_t*>(p);
        else if(fmt == "/D") delete static_cast<Double_t*>(p);
        else if(fmt == "/I") delete static_cast<Int_t*>(p);
#if defined(Long64_t)
        else if(fmt == "/L") delete static_cast<Long64_t*>(p);
#endif
        else if(fmt == "/O") delete static_cast<Bool_t*>(p);
        else delete static_cast<char*>(p); // fallback
    }
    fSimcBuffers.clear();
    fSimcLeafFormat.clear();

    if (fSimcFile){
        if (fSimcFile->IsOpen()) fSimcFile->Close();
        delete fSimcFile;
        fSimcFile = nullptr;
    }

    if (fRootFile) {
        delete fRootFile;
        fRootFile = nullptr;
    }
}

// Book: now optionally accepts simc file & tree name
void HistoManager::Book(const std::string& fileName,
                        const std::string& simcRootPath,
                        const std::string& simcTreeName)
{
    fRootFile = TFile::Open(fileName.c_str(), "RECREATE");
    if(!fRootFile || fRootFile->IsZombie()){
        G4cerr << "HistoManager::Book: cannot create output file " << fileName << G4endl;
        fRootFile = nullptr;
        return;
    }

    // create DVCS ntuple (this will hold SIMC branches (if any) + GEANT branches)
    fNtuple_DVCS = new TTree("nerd", "pi0 events generated and reconstructed (merged SIMC + GEANT)");

    // --- Minimal GEANT branches requested by user --- 
    // event number
    fNtuple_DVCS->Branch("evtNb", &fEvtNb, "evtNb/I");

    // per-crystal energy deposition (1080 crystals) - existing array in the class
    fNtuple_DVCS->Branch("edep", fEdep, "edep[1080]/D");

    // --- Photon 1 ---
    fNtuple_DVCS->Branch("phot1_hit", &fPhot1Hit, "phot1_hit/O");
    fNtuple_DVCS->Branch("phot1_vx", &fPhot1_vx, "phot1_vx/D");
    fNtuple_DVCS->Branch("phot1_vy", &fPhot1_vy, "phot1_vy/D");
    fNtuple_DVCS->Branch("phot1_vz", &fPhot1_vz, "phot1_vz/D");

    fNtuple_DVCS->Branch("phot1_hit_x", &fPhot1_hitx, "phot1_hit_x/D");
    fNtuple_DVCS->Branch("phot1_hit_y", &fPhot1_hity, "phot1_hit_y/D");
    fNtuple_DVCS->Branch("phot1_hit_z", &fPhot1_hitz, "phot1_hit_z/D");

    fNtuple_DVCS->Branch("phot1_clust_x", &fPhot1_clustx, "phot1_clust_x/D");
    fNtuple_DVCS->Branch("phot1_clust_y", &fPhot1_clusty, "phot1_clust_y/D");
    fNtuple_DVCS->Branch("phot1_clust_z", &fPhot1_clustz, "phot1_clust_z/D");

    fNtuple_DVCS->Branch("phot1_Ecal", &fPhot1_Ecal, "phot1_Ecal/D");
    fNtuple_DVCS->Branch("phot1_clustSize", &fPhot1_clustSize, "phot1_clustSize/I");

    // fNtuple_DVCS->Branch("phot1_gen_px", &fGP_Px1, "phot1_gen_px/D");
    // fNtuple_DVCS->Branch("phot1_gen_py", &fGP_Py1, "phot1_gen_py/D");
    // fNtuple_DVCS->Branch("phot1_gen_pz", &fGP_Pz1, "phot1_gen_pz/D");

    // --- Photon 2 ---
    fNtuple_DVCS->Branch("phot2_hit", &fPhot2Hit, "phot2_hit/O");
    fNtuple_DVCS->Branch("phot2_vx", &fPhot2_vx, "phot2_vx/D");
    fNtuple_DVCS->Branch("phot2_vy", &fPhot2_vy, "phot2_vy/D");
    fNtuple_DVCS->Branch("phot2_vz", &fPhot2_vz, "phot2_vz/D");

    fNtuple_DVCS->Branch("phot2_hit_x", &fPhot2_hitx, "phot2_hit_x/D");
    fNtuple_DVCS->Branch("phot2_hit_y", &fPhot2_hity, "phot2_hit_y/D");
    fNtuple_DVCS->Branch("phot2_hit_z", &fPhot2_hitz, "phot2_hit_z/D");

    fNtuple_DVCS->Branch("phot2_clust_x", &fPhot2_clustx, "phot2_clust_x/D");
    fNtuple_DVCS->Branch("phot2_clust_y", &fPhot2_clusty, "phot2_clust_y/D");
    fNtuple_DVCS->Branch("phot2_clust_z", &fPhot2_clustz, "phot2_clust_z/D");

    fNtuple_DVCS->Branch("phot2_Ecal", &fPhot2_Ecal, "phot2_Ecal/D");
    fNtuple_DVCS->Branch("phot2_clustSize", &fPhot2_clustSize, "phot2_clustSize/I");

    // fNtuple_DVCS->Branch("phot2_gen_px", &fGP_Px2, "phot2_gen_px/D");
    // fNtuple_DVCS->Branch("phot2_gen_py", &fGP_Py2, "phot2_gen_py/D");
    // fNtuple_DVCS->Branch("phot2_gen_pz", &fGP_Pz2, "phot2_gen_pz/D");

    // Useful generator-level vertex (kept)
    // fNtuple_DVCS->Branch("GV_x", &fGV_X, "GV_x/D");
    // fNtuple_DVCS->Branch("GV_y", &fGV_Y, "GV_y/D");
    // fNtuple_DVCS->Branch("GV_z", &fGV_Z, "GV_z/D");

    // --- NEW: cluster vectors and count ---
    // note: using file-static sClust_* buffers defined above
    fNtuple_DVCS->Branch("nClusters", &sNbClusters, "nClusters/I");
    // Branch std::vector<double> and std::vector<int> directly.
    // ROOT understands std::vector by class name automatically.
    fNtuple_DVCS->Branch("clust_E", &sClust_E);
    fNtuple_DVCS->Branch("clust_X", &sClust_X);
    fNtuple_DVCS->Branch("clust_Y", &sClust_Y);
    fNtuple_DVCS->Branch("clust_Size", &sClust_Size);

    // If user supplied a SIMC file, open it and mirror branches
    if(!simcRootPath.empty()){
        fSimcPath = simcRootPath;
        fSimcTreeName = simcTreeName;
        fSimcFile = TFile::Open(fSimcPath.c_str(), "READ");
        if(!fSimcFile || fSimcFile->IsZombie()){
            G4cerr << "HistoManager::Book: cannot open SIMC file " << fSimcPath << G4endl;
            if(fSimcFile){ fSimcFile->Close(); delete fSimcFile; fSimcFile = nullptr; }
        } else {
            fSimcTree = dynamic_cast<TTree*>(fSimcFile->Get(fSimcTreeName.c_str()));
            if(!fSimcTree){
                G4cerr << "HistoManager::Book: cannot find tree '" << fSimcTreeName << "' in " << fSimcPath << G4endl;
                fSimcFile->Close(); delete fSimcFile; fSimcFile = nullptr; fSimcTree = nullptr;
            } else {
                // create mirror branches dynamically
                if(!SetupSIMCBranches()){
                    G4cerr << "HistoManager::Book: failed to setup SIMC branch mirroring." << G4endl;
                } else {
                    G4cout << "HistoManager::Book: mirrored SIMC branches from " << fSimcPath << ":" << fSimcTreeName << G4endl;
                }
            }
        }
    }

    G4cout << "\n----> Output file is open in " << fileName << G4endl;
}

// SetupSIMCBranches implementation remains unchanged (omitted here to keep snippet short).
// It's the same as in the file you supplied earlier, creating buffers and branches for SIMC leaves.

bool HistoManager::SetupSIMCBranches()
{
    if(!fSimcTree) return false;

    TObjArray* branches = fSimcTree->GetListOfBranches();
    if(!branches) return false;

    int nB = branches->GetEntries();
    for(int i=0;i<nB;i++){
        TBranch* br = dynamic_cast<TBranch*>(branches->At(i));
        if(!br) continue;
        TObjArray* leaves = br->GetListOfLeaves();
        if(!leaves) continue;
        TLeaf* leaf = dynamic_cast<TLeaf*>(leaves->At(0));
        if(!leaf) continue;
        std::string leafName = leaf->GetName();
        std::string leafType = leaf->GetTypeName();

        if(leaf->GetLen() > 1){
            G4cout << "HistoManager::SetupSIMCBranches: skipping array leaf '" << leafName
                   << "' (len=" << leaf->GetLen() << "). Extend this if you need arrays." << G4endl;
            continue;
        }

        void* buffer = AllocBufferForLeafType(leafType);
        std::string fmt = LeafFormatForType(leafType);
        if(!buffer || fmt.empty()){
            G4cout << "HistoManager::SetupSIMCBranches: unsupported SIMC leaf type '" << leafType
                   << "' for leaf '" << leafName << "' — skipping." << G4endl;
            continue;
        }

        fSimcBuffers[leafName] = buffer;
        fSimcLeafFormat[leafName] = fmt;

        fSimcTree->SetBranchAddress(leafName.c_str(), buffer);

        std::string leafSpec = leafName + fmt;
        fNtuple_DVCS->Branch(leafName.c_str(), buffer, leafSpec.c_str());
    }

    return true;
}

bool HistoManager::CopySIMCEntry(Long64_t entry)
{
    if(!fSimcTree){
        G4cout << "HistoManager::CopySIMCEntry: no SIMC tree open" << G4endl;
        return false;
    }
    Long64_t n = fSimcTree->GetEntries();
    if(entry < 0 || entry >= n){
        G4cout << "HistoManager::CopySIMCEntry: entry " << entry << " out of range (0.." << n-1 << ")" << G4endl;
        return false;
    }
    Long64_t got = fSimcTree->GetEntry(entry);
    if(got <= 0){
        G4cout << "HistoManager::CopySIMCEntry: failed to read entry " << entry << G4endl;
        return false;
    }
    // buffers are now populated by simcTree->GetEntry
    return true;
}

void HistoManager::Save()
{
    if (! fRootFile) return;
    fRootFile->Write();       // Writing the histograms to the file
    fRootFile->Close();       // and closing the tree (and the file)

    G4cout << "\n----> Histograms and ntuples are saved\n" << G4endl;
}

void HistoManager::FillNtupleDVCS()
{
    // ensure sNbClusters and sClust_* are written as-is by ROOT (they must be up to date)
    if(fNtuple_DVCS) fNtuple_DVCS->Fill();
}

// Existing small helpers left unchanged (FillNtuple, FillNtupleClust etc.)
// ...

void HistoManager::FillNtupleFluxOptFiber(G4int) {}
void HistoManager::SetFluxEnergyandPID(G4int, G4int, G4double) {}
void HistoManager::FillNtuple2() {}
void HistoManager::FillNtupleFluxSphere(G4int) {}

// Existing SetEnergyandPID / SetEvtNb / SetCaloData1 / SetCaloData2 omitted for brevity,
// assume they remain exactly as in your supplied file.

void HistoManager::SetEnergyandPID(G4int id, G4int PID, G4double edep, G4int sc, G4int ce, G4int opc, G4int opfc, G4int oppc)
{
    if(id < 0 || id >= MaxNtuple) return;
    fEdep[id] = edep;
    // keep PID/op arrays if needed
}

void HistoManager::SetVertexGen(G4double gv_x, G4double gv_y, G4double gv_z) { fGV_X = gv_x; fGV_Y = gv_y; fGV_Z = gv_z; }

// // simple setters
void HistoManager::SetEvtNb(G4int evtNb) { fEvtNb = evtNb; }
void HistoManager::SetCaloData1(G4double clust_ene, G4double clust_x, G4double clust_y, G4int clust_size)
{
    fClust_Ene1 = clust_ene; fClust_X1 = clust_x; fClust_Y1 = clust_y; fClust_size1 = clust_size;
}
void HistoManager::SetCaloData2(G4double clust_ene, G4double clust_x, G4double clust_y, G4int clust_size)
{
    fClust_Ene2 = clust_ene; fClust_X2 = clust_x; fClust_Y2 = clust_y; fClust_size2 = clust_size;
}

void HistoManager::SetPhotRec1(G4double px, G4double py, G4double pz) { fRP_Px1 = px; fRP_Py1 = py; fRP_Pz1 = pz; }
void HistoManager::SetPhotRec2(G4double px, G4double py, G4double pz) { fRP_Px2 = px; fRP_Py2 = py; fRP_Pz2 = pz; }
void HistoManager::SetPhotGen1(G4double px, G4double py, G4double pz) { fGP_Px1 = px; fGP_Py1 = py; fGP_Pz1 = pz; }
void HistoManager::SetPhotGen2(G4double px, G4double py, G4double pz) { fGP_Px2 = px; fGP_Py2 = py; fGP_Pz2 = pz; }

// NEW: accept per-photon hit info (kept unchanged)
void HistoManager::SetPhotHit1(bool hit,
                              G4double v_x, G4double v_y, G4double v_z,
                              G4double hit_x, G4double hit_y, G4double hit_z,
                              G4double clust_x, G4double clust_y,
                              G4double Ecal, G4int clustSize)
{
    fPhot1Hit = hit;
    fPhot1_vx = v_x; fPhot1_vy = v_y; fPhot1_vz = v_z;
    fPhot1_hitx = hit_x; fPhot1_hity = hit_y; fPhot1_hitz = hit_z;
    fPhot1_clustx = clust_x; fPhot1_clusty = clust_y;
    fPhot1_Ecal = Ecal;
    fPhot1_clustSize = clustSize;
}

void HistoManager::SetPhotHit2(bool hit,
                              G4double v_x, G4double v_y, G4double v_z,
                              G4double hit_x, G4double hit_y, G4double hit_z,
                              G4double clust_x, G4double clust_y,
                              G4double Ecal, G4int clustSize)
{
    fPhot2Hit = hit;
    fPhot2_vx = v_x; fPhot2_vy = v_y; fPhot2_vz = v_z;
    fPhot2_hitx = hit_x; fPhot2_hity = hit_y; fPhot2_hitz = hit_z;
    fPhot2_clustx = clust_x; fPhot2_clusty = clust_y;
    fPhot2_Ecal = Ecal;
    fPhot2_clustSize = clustSize;
}

// NEW: SetClusters implementation
void HistoManager::SetClusters(const std::vector<Double_t>& clust_x,
                               const std::vector<Double_t>& clust_y,
                               const std::vector<Double_t>& clust_E,
                               const std::vector<Int_t>& clustSize)
{
    // copy into file-static buffers
    sClust_X = clust_x;
    sClust_Y = clust_y;
    sClust_E = clust_E;
    sClust_Size = clustSize;
    sNbClusters = static_cast<Int_t>(sClust_E.size());

    // also keep a convenience copy in member vars if needed elsewhere in code
    // (optional, but harmless)
    if(sNbClusters > 0){
        fClust_Ene1 = sClust_E.size() > 0 ? sClust_E[0] : -999.;
        fClust_X1   = sClust_X.size() > 0 ? sClust_X[0] : -999.;
        fClust_Y1   = sClust_Y.size() > 0 ? sClust_Y[0] : -999.;
        fClust_size1= sClust_Size.size() > 0 ? sClust_Size[0] : -1;
    } else {
        fClust_Ene1 = fClust_X1 = fClust_Y1 = -999.;
        fClust_size1 = -1;
    }
    if(sNbClusters > 1){
        fClust_Ene2 = sClust_E.size() > 1 ? sClust_E[1] : -999.;
        fClust_X2   = sClust_X.size() > 1 ? sClust_X[1] : -999.;
        fClust_Y2   = sClust_Y.size() > 1 ? sClust_Y[1] : -999.;
        fClust_size2= sClust_Size.size() > 1 ? sClust_Size[1] : -1;
    } else {
        fClust_Ene2 = fClust_X2 = fClust_Y2 = -999.;
        fClust_size2 = -1;
    }
}

// Flux setters (unchanged)
void HistoManager::SetFluxSphereEnergyandPID(G4int FluxPID, G4double energy, G4ThreeVector position)
{
    const double pi = M_PI;
    if(FluxPID == 22){
        fFluxEnergy_gamma = energy;
        fTheta_gamma = (180./pi)*(acos(position.z()/sqrt(position.x()*position.x() + position.y()*position.y() + position.z()*position.z())));
        fPhi_gamma = (180./pi)*(atan2(position.y(), position.x()));
    }
    else if(FluxPID == -11){
        fFluxEnergy_pos = energy;
        fTheta_pos = (180./pi)*(acos(position.z()/sqrt(position.x()*position.x() + position.y()*position.y() + position.z()*position.z())));
        fPhi_pos = (180./pi)*(atan2(position.y(), position.x()));
    }
    else if(FluxPID == 11){
        fFluxEnergy_elec = energy;
        fTheta_elec = (180./pi)*(acos(position.z()/sqrt(position.x()*position.x() + position.y()*position.y() + position.z()*position.z())));
        fPhi_elec = (180./pi)*(atan2(position.y(), position.x()));
    }
    else{
        fFluxEnergy_unknown = energy;
        fFluxPID_unknown = FluxPID;
        fTheta_unknown = (180./pi)*(acos(position.z()/sqrt(position.x()*position.x() + position.y()*position.y() + position.z()*position.z())));
        fPhi_unknown = (180./pi)*(atan2(position.y(), position.x()));
    }
}

void HistoManager::SetFluxOptFiberEnergyandPID(G4int evtNb, G4int FluxPID, G4double energy, G4ThreeVector mom, G4ThreeVector position, G4ThreeVector localPosition)
{
    fFluxEvtNb = evtNb;
    if(FluxPID == 22){
        fFluxEnergy_OptFiber_gamma = energy;
        fFluxMomX_OptFiber_gamma = mom.x();
        fFluxMomY_OptFiber_gamma = mom.y();
        fFluxMomZ_OptFiber_gamma = mom.z();
        fGlobalX_OptFiber_gamma = position.x(); fGlobalY_OptFiber_gamma = position.y(); fGlobalZ_OptFiber_gamma = position.z();
        fLocalX_OptFiber_gamma = localPosition.x(); fLocalY_OptFiber_gamma = localPosition.y(); fLocalZ_OptFiber_gamma = localPosition.z();
    }
    else if(FluxPID == -11){
        fFluxEnergy_OptFiber_pos = energy;
        fFluxMomX_OptFiber_pos = mom.x();
        fFluxMomY_OptFiber_pos = mom.y();
        fFluxMomZ_OptFiber_pos = mom.z();
        fGlobalX_OptFiber_pos = position.x(); fGlobalY_OptFiber_pos = position.y(); fGlobalZ_OptFiber_pos = position.z();
        fLocalX_OptFiber_pos = localPosition.x(); fLocalY_OptFiber_pos = localPosition.y(); fLocalZ_OptFiber_pos = localPosition.z();
    }
    else if(FluxPID == 11){
        fFluxEnergy_OptFiber_elec = energy;
        fFluxMomX_OptFiber_elec = mom.x();
        fFluxMomY_OptFiber_elec = mom.y();
        fFluxMomZ_OptFiber_elec = mom.z();
        fGlobalX_OptFiber_elec = position.x(); fGlobalY_OptFiber_elec = position.y(); fGlobalZ_OptFiber_elec = position.z();
        fLocalX_OptFiber_elec = localPosition.x(); fLocalY_OptFiber_elec = localPosition.y(); fLocalZ_OptFiber_elec = localPosition.z();
    }
    else{
        fFluxEnergy_OptFiber_unknown = energy;
        fFluxMomX_OptFiber_unknown = mom.x();
        fFluxMomY_OptFiber_unknown = mom.y();
        fFluxMomZ_OptFiber_unknown = mom.z();
        fFluxPID_OptFiber_unknown = FluxPID;
        fGlobalX_OptFiber_unknown = position.x(); fGlobalY_OptFiber_unknown = position.y(); fGlobalZ_OptFiber_unknown = position.z();
        fLocalX_OptFiber_unknown = localPosition.x(); fLocalY_OptFiber_unknown = localPosition.y(); fLocalZ_OptFiber_unknown = localPosition.z();
    }
}

void HistoManager::SetOP(G4int a, G4int b){ /*stub*/ }
void HistoManager::PrintStatistic(){ /*stub*/ }
