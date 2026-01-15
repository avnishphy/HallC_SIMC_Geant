#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"
#include "G4ThreeVector.hh"

#include <string>
#include <map>
#include <vector>
#include "Rtypes.h"


class TFile;
class TTree;
class TH1D;

const G4int MaxHisto = 4;
const G4int MaxNtuple = 1080;

class HistoManager
{
public:
  HistoManager();
  ~HistoManager();

  // Book now optionally takes simcRootPath and simcTreeName.
  // If simcRootPath=="" then no SIMC branches are mirrored.
  void Book(const std::string& outFileName,
            const std::string& simcRootPath = "",
            const std::string& simcTreeName = "h10");

  void Save();

  // existing fills (you'll still call FillNtupleDVCS() after EventAction sets
  // Geant quantities and after the SIMC entry has been copied with CopySIMCEntry())
  void FillNtuple();
  void FillNtupleDVCS();
  void FillNtupleClust();
  void FillNtuple2();
  void FillNtupleFluxSphere(G4int);
  void FillNtupleFluxOptFiber(G4int);
  void SetEnergyandPID(G4int , G4int, G4double, G4int, G4int, G4int, G4int, G4int);

  void SetEvtNb(G4int);
  void SetCaloData1(G4double, G4double, G4double, G4int);
  void SetCaloData2(G4double, G4double, G4double, G4int);
  void SetClustW2(G4double);
  void SetInitElecRec(G4double, G4double, G4double);
  void SetInitElecGen(G4double, G4double, G4double);
  void SetScatElecRec(G4double, G4double, G4double);
  void SetScatElecGen(G4double, G4double, G4double);
  void SetPhotRec1(G4double, G4double, G4double);
  void SetPhotGen1(G4double, G4double, G4double);
  void SetPhotRec2(G4double, G4double, G4double);
  void SetPhotGen2(G4double, G4double, G4double);
  void SetMpi0Gen(G4double);
  void SetMpi0Rec(G4double);
  void SetVertexz(G4double, G4double);
  void SetVertexGen(G4double, G4double, G4double);
  void SetKineRec(G4double, G4double, G4double, G4double);
  void SetKineGen(G4double, G4double, G4double, G4double);
  void SetWeights(G4double, G4double, G4double, G4double);
  void SetRvalRec(G4double);
  void SetRvalGen(G4double);

  void SetClusterPositionandMomentum(G4int, G4double, G4double, G4double, G4double, G4double, G4double);
  void SetFluxEnergyandPID(G4int , G4int, G4double);
  void SetFluxSphereEnergyandPID(G4int , G4double, G4ThreeVector);
  void SetFluxOptFiberEnergyandPID(G4int, G4int , G4double, G4ThreeVector, G4ThreeVector, G4ThreeVector);

  void SetOP(G4int , G4int );
  void PrintStatistic();

  // --- new API for SIMC mirroring ---
  // Copy the given SIMC entry into the internal SIMC buffers (then call FillNtupleDVCS())
  // Returns true on success.
  bool CopySIMCEntry(Long64_t entry);

  // --- NEW: per-photon *hit* setters (first-impact hit info from SD)
  // hit: whether photon reached the calorimeter (true if hit)
  // v_x/v_y/v_z: generator vertex (cm) for that photon (or -999 if not provided)
  // hit_x/hit_y/hit_z: exact impact coordinates on calorimeter (cm) as measured by SD
  // Ecal: energy attributed to photon by calorimeter (same units you store; e.g. GeV)
  // clustSize: cluster size if available (or -1)
  void SetPhotHit1(bool hit,
                   G4double v_x, G4double v_y, G4double v_z,
                   G4double hit_x, G4double hit_y, G4double hit_z,
                   G4double clust_x, G4double clust_y,
                   G4double Ecal, G4int clustSize);

  void SetPhotHit2(bool hit,
                   G4double v_x, G4double v_y, G4double v_z,
                   G4double hit_x, G4double hit_y, G4double hit_z,
                   G4double clust_x, G4double clust_y,
                   G4double Ecal, G4int clustSize);

  void SetClusters(const std::vector<Double_t>& clust_x,
                 const std::vector<Double_t>& clust_y,
                 const std::vector<Double_t>& clust_E,
                 const std::vector<Int_t>& clustSize);

private:
  // internal helpers
  bool SetupSIMCBranches(); // called from Book() if simc file provided
  void CreateGeantBranches(); // create the existing geant branches in fNtuple_DVCS

private:
  TFile*   fRootFile;
  TTree*   fNtuple;
  TTree*   fNtuple_DVCS;
  TTree*   fNtuple_Clust;
  TTree*   fNtuple2;

  // For SIMC mirroring:
  TFile*   fSimcFile;   // opened SIMC file (if any)
  TTree*   fSimcTree;   // SIMC tree (if any)
  std::string fSimcPath;
  std::string fSimcTreeName;

  // dynamic buffers for SIMC branches (name -> pointer to allocated scalar)
  std::map<std::string, void*> fSimcBuffers;
  // store type codes: "F" "D" "I" "L" etc. (leaf descriptor suffix)
  std::map<std::string, std::string> fSimcLeafFormat;

  // Existing member variables (kept, unchanged)
  TTree*   fNtuple_gamma;
  TTree*   fNtuple_pos;
  TTree*   fNtuple_elec;
  TTree*   fNtuple_unknown;
  TTree*   fNtuple_OptFiber_gamma;
  TTree*   fNtuple_OptFiber_pos;
  TTree*   fNtuple_OptFiber_elec;
  TTree*   fNtuple_OptFiber_unknown;
  G4double fEdep[MaxNtuple];
  G4int    fPID[MaxNtuple];
  G4int    fOP_sc[MaxNtuple];
  G4int    fOP_ce[MaxNtuple];
  G4int    fOP_cover[MaxNtuple];
  G4int    fOP_frontcover[MaxNtuple];
  G4int    fOP_pmtcover[MaxNtuple];

  G4double fFluxEne[MaxNtuple];
  G4int    fFluxPID[MaxNtuple];

  G4int    fEvtNb;
  G4double fClust_Ene1;
  G4double fClust_X1;
  G4double fClust_Y1;
  G4int    fClust_size1;
  G4double fClust_Ene2;
  G4double fClust_X2;
  G4double fClust_Y2;
  G4int    fClust_size2;
  G4double fClust_W2;
  G4double fPSF;
  G4double fRIE_Px;
  G4double fRIE_Py;
  G4double fRIE_Pz;
  G4double fGIE_Px;
  G4double fGIE_Py;
  G4double fGIE_Pz;
  G4double fRSE_Px;
  G4double fRSE_Py;
  G4double fRSE_Pz;
  G4double fGSE_Px;
  G4double fGSE_Py;
  G4double fGSE_Pz;
  G4double fRP_Px1;
  G4double fRP_Py1;
  G4double fRP_Pz1;
  G4double fGP_Px1;
  G4double fGP_Py1;
  G4double fGP_Pz1;
  G4double fRP_Px2;
  G4double fRP_Py2;
  G4double fRP_Pz2;
  G4double fGP_Px2;
  G4double fGP_Py2;
  G4double fGP_Pz2;
  G4double fRM;
  G4double fGM;
  G4double fRV_Z;
  G4double fGV_X;
  G4double fGV_Y;
  G4double fGV_Z;
  G4double fRt;
  G4double fGt;
  G4double fRxB;
  G4double fGxB;
  G4double fRQ2;
  G4double fGQ2;
  G4double fRphi;
  G4double fGphi;
  G4double fX_sum;
  G4double fX_diff;
  G4double fX_BH;
  G4double fRr_val;
  G4double fGr_val;

  G4int     fEvtNb_;
  G4double  fClust_X_;
  G4double  fClust_Y_;
  G4double  fClust_Ene_;
  G4double  fClust_Px_;
  G4double  fClust_Py_;
  G4double  fClust_Pz_;

  G4double fFluxEnergy_gamma;
  G4double fTheta_gamma;
  G4double fPhi_gamma;
  G4double fFluxEnergy_pos;
  G4double fTheta_pos;
  G4double fPhi_pos;
  G4double fFluxEnergy_elec;
  G4double fTheta_elec;
  G4double fPhi_elec;
  G4double fFluxEnergy_unknown;
  G4int    fFluxPID_unknown;
  G4double fTheta_unknown;
  G4double fPhi_unknown;

  G4int    fFluxEvtNb;
  G4double fFluxMomX_OptFiber_gamma;
  G4double fFluxMomY_OptFiber_gamma;
  G4double fFluxMomZ_OptFiber_gamma;
  G4double fFluxMomX_OptFiber_pos;
  G4double fFluxMomY_OptFiber_pos;
  G4double fFluxMomZ_OptFiber_pos;
  G4double fFluxMomX_OptFiber_elec;
  G4double fFluxMomY_OptFiber_elec;
  G4double fFluxMomZ_OptFiber_elec;
  G4double fFluxMomX_OptFiber_unknown;
  G4double fFluxMomY_OptFiber_unknown;
  G4double fFluxMomZ_OptFiber_unknown;
  G4double fFluxEnergy_OptFiber_gamma;
  G4double fGlobalX_OptFiber_gamma;
  G4double fGlobalY_OptFiber_gamma;
  G4double fGlobalZ_OptFiber_gamma;
  G4double fLocalX_OptFiber_gamma;
  G4double fLocalY_OptFiber_gamma;
  G4double fLocalZ_OptFiber_gamma;
  G4double fFluxEnergy_OptFiber_pos;
  G4double fGlobalX_OptFiber_pos;
  G4double fGlobalY_OptFiber_pos;
  G4double fGlobalZ_OptFiber_pos;
  G4double fLocalX_OptFiber_pos;
  G4double fLocalY_OptFiber_pos;
  G4double fLocalZ_OptFiber_pos;
  G4double fFluxEnergy_OptFiber_elec;
  G4double fGlobalX_OptFiber_elec;
  G4double fGlobalY_OptFiber_elec;
  G4double fGlobalZ_OptFiber_elec;
  G4double fLocalX_OptFiber_elec;
  G4double fLocalY_OptFiber_elec;
  G4double fLocalZ_OptFiber_elec;
  G4double fFluxEnergy_OptFiber_unknown;
  G4int    fFluxPID_OptFiber_unknown;
  G4double fGlobalX_OptFiber_unknown;
  G4double fGlobalY_OptFiber_unknown;
  G4double fGlobalZ_OptFiber_unknown;
  G4double fLocalX_OptFiber_unknown;
  G4double fLocalY_OptFiber_unknown;
  G4double fLocalZ_OptFiber_unknown;

  // per-photon reach flags
  Bool_t fPhot1Hit;
  Bool_t fPhot2Hit;

  // per-photon vertex
  Double_t fPhot1_vx, fPhot1_vy, fPhot1_vz;
  Double_t fPhot2_vx, fPhot2_vy, fPhot2_vz;

  // per-photon calorimeter hit position
  Double_t fPhot1_hitx, fPhot1_hity, fPhot1_hitz;
  Double_t fPhot2_hitx, fPhot2_hity, fPhot2_hitz;

  Double_t fPhot1_clustx, fPhot1_clusty, fPhot1_clustz;
  Double_t fPhot2_clustx, fPhot2_clusty, fPhot2_clustz;

  // per-photon energy seen by calo
  Double_t fPhot1_Ecal;
  Double_t fPhot2_Ecal;

  // per-photon cluster size
  Int_t    fPhot1_clustSize;
  Int_t    fPhot2_clustSize;

};

#endif
