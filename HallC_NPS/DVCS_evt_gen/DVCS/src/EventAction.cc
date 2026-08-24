// EventAction.cc

#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "RunAction.hh"
#include "HistoManager.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4Run.hh"

#include "B5HadCalorimeterHit.hh"
#include "B5HadCalorimeterSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "CrystalCoverHit.hh"
#include "CrystalFrontCoverHit.hh"
#include "PMTcoverHit.hh"
#include "FluxHit.hh"

#include "dvcsGlobals.hh"

#include "TProcessID.h"

#include <TRandom2.h>
#include <TMath.h>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>

#include "G4SystemOfUnits.hh"                // Geant4 units (mm, cm, GeV, etc.)
#include "CLHEP/Units/SystemOfUnits.h"      // CLHEP::cm used elsewhere in code

time_t t_int = time(0); // initial time stamp

namespace {
// Historical NPS reconstruction compensation. Applied to block energies before
// trigger/clustering; SIMC truth and ancestry-tagged phot{1,2}_Ecal stay raw.
constexpr G4double kCaloEnergyScale = 1.04;
}

EventAction::EventAction(RunAction* run, HistoManager* histo,
                         const DetectorConstruction* detector)
    : G4UserEventAction(),
      fRunAct(run),
      fHistoManager(histo),
      fDetector(detector),
      fEvtNb(-1),
      fHCHCID(-1),
      fHadCalEdep(),
      fPID(),
      fOP_sc(),
      fOP_ce(),
      fCrystCoverHCID(-1),
      fCrystCoverOP(),
      fCrystFrontCoverHCID(-1),
      fCrystFrontCoverOP(),
      fPMTcoverHCID(-1),
      fPMTcoverOP(),
      fFluxEne(),
      fFlxHCID(-1),
      fFluxEnergy(-999),
      fFluxPID(-999),
      fPos(-999),
      hit_HMS(0),
      M_targ(-999.),
      fSmeared_vertex_z(-999.),
      fVertex_z(-999.),
      fEnergyAbs(0.), fEnergyGap(0.),
      fTrackLAbs(0.), fTrackLGap(0.),
      fPrintModulo(0)
{
    fPrintModulo = 100;
    fHadCalEdep.resize(1080,0.0);
    fPID.resize(1080,0);
    fOP_sc.resize(1080,0);
    fOP_ce.resize(1080,0);
    fCrystCoverOP.resize(1080,0);
    fCrystFrontCoverOP.resize(1080,0);
    fPMTcoverOP.resize(1080,0);
    fFluxEne = 0.;

    G4int run_number = dvcsGlobals::run_number;
    dvcs_evt = new TDVCSEvent(run_number);
    calo_evt = new TCaloEvent(run_number);

    // initialize TLVs to zero
    L_calo_phot1.SetPxPyPzE(0,0,0,0);
    L_calo_phot2.SetPxPyPzE(0,0,0,0);

    dvcs_evt->SetCaloEvent(calo_evt);
    G4cout<<"Calorimeter distance (cm): "<<dvcs_evt->GetGeometry()->GetCaloDist()<<G4endl;
    G4cout<<"Calorimeter angle (deg): "<<dvcs_evt->GetGeometry()->GetCaloTheta()*TMath::RadToDeg()<<G4endl;

    G4int target_gen_proc_type = dvcsGlobals::target_gen_proc_type;
    if( target_gen_proc_type == 0 || target_gen_proc_type == 1 || target_gen_proc_type ==2){
        if(target_gen_proc_type == 0) {M_targ = 0.9383;}
        else if( target_gen_proc_type == 1 ) {M_targ = 0.939565378;}
        else if( target_gen_proc_type == 2 ) {M_targ = 1.875612859;}
    } else {
        G4cerr << "EventAction: wrong target mass type; exiting" << G4endl;
        exit(1);
    }

    // initialize arrays with sentinel values
    for (int i=0;i<6;++i) { fPx[i] = fPy[i] = fPz[i] = fE[i] = -999.; }
}

EventAction::~EventAction()
{
    if(dvcs_evt) { delete dvcs_evt; dvcs_evt = nullptr; }
    if(calo_evt) { delete calo_evt; calo_evt = nullptr; }
}

void EventAction::BeginOfEventAction(const G4Event* evt)
{
    fEvtNb = evt->GetEventID();

    G4Run* run = static_cast<G4Run*>( G4RunManager::GetRunManager()->GetNonConstCurrentRun() );
    G4int nOfEvents = 0;
    if (run) nOfEvents = run->GetNumberOfEventToBeProcessed();

    // Print status safely (avoid fmod / division by zero)
    if (nOfEvents > 0) {
        // print every 10% or at least every event 1 when run < 10
        G4int step = std::max(1, nOfEvents / 10);
        if ((fEvtNb % step) == 0) {
            time_t t_now = time(0);
            time_t t_diff = t_now - t_int;
            // produce a friendly elapsed time format (hh:mm:ss)
            int hours = static_cast<int>(t_diff / 3600);
            int mins  = static_cast<int>((t_diff % 3600) / 60);
            int secs  = static_cast<int>(t_diff % 60);
            G4double status = 100.0 * (double(fEvtNb) / double(nOfEvents));
            std::cout << "=> Event " << fEvtNb << " starts ( " << status << "%, "
                      << hours << ":" << mins << ":" << secs << " passed )" << std::endl;
        }
    }

    if (fEvtNb % fPrintModulo == 0){
        fEnergyAbs = fEnergyGap = 0.;
        fTrackLAbs = fTrackLGap = 0.;
        fFluxEne = 0.;
    }
    if (fHCHCID==-1){
        G4SDManager* sdManager = G4SDManager::GetSDMpointer();
        fHCHCID = sdManager->GetCollectionID("HadCalorimeter/HadCalorimeterColl");
    }
    if (fCrystCoverHCID==-1){
        G4SDManager* sdManager = G4SDManager::GetSDMpointer();
        fCrystCoverHCID = sdManager->GetCollectionID("CrystalCover/CrystalCoverColl");
    }
    if (fCrystFrontCoverHCID==-1){
        G4SDManager* sdManager = G4SDManager::GetSDMpointer();
        fCrystFrontCoverHCID = sdManager->GetCollectionID("CrystalFrontCover/CrystalFrontCoverColl");
    }
    if (fPMTcoverHCID==-1){
        G4SDManager* sdManager = G4SDManager::GetSDMpointer();
        fPMTcoverHCID = sdManager->GetCollectionID("PMTcover/PMTcoverColl");
    }
    if (fFlxHCID==-1){
        G4SDManager* sdManager = G4SDManager::GetSDMpointer();
        fFlxHCID = sdManager->GetCollectionID("Flux/FluxColl");
    }

    if( dvcsGlobals::hit_HMS_CALO_flag ){
        for (int i=0;i<6;++i){ fPx[i]=0.; fPy[i]=0.; fPz[i]=0.; fE[i]=0.; }
    }
    fHistoManager->SetEvtNb(fEvtNb);
}

void EventAction::EndOfEventAction(const G4Event* evt)
{
    // accumulate statistics
    if (fRunAct) fRunAct->fillPerEvent(fEnergyAbs, fEnergyGap, fTrackLAbs, fTrackLGap);

    G4HCofThisEvent* hce = evt->GetHCofThisEvent();
    if (!hce){
        G4ExceptionDescription msg;
        msg << "No hits collection of this event found." << G4endl;
        G4Exception("EventAction::EndOfEventAction()", "Code001", JustWarning, msg);
        return;
    }

    // Retrieve hit collections safely
    auto* hcHC = dynamic_cast<B5HadCalorimeterHitsCollection*>( hce->GetHC(fHCHCID) );
    if (!hcHC){
        G4ExceptionDescription msg;
        msg << "Had calorimeter hits collection not found." << G4endl;
        G4Exception("EventAction::EndOfEventAction()", "Code001", JustWarning, msg);
        return;
    }

    auto* CrystCoverHC = dynamic_cast<CrystalCoverHitsCollection*>( hce->GetHC(fCrystCoverHCID) );
    if (!CrystCoverHC) {
        G4ExceptionDescription msg;
        msg << "Crystal cover hits collection not found." << G4endl;
        G4Exception("EventAction::EndOfEventAction()", "Code001", JustWarning, msg);
        return;
    }

    auto* CrystFrontCoverHC = dynamic_cast<CrystalFrontCoverHitsCollection*>( hce->GetHC(fCrystFrontCoverHCID) );
    if (!CrystFrontCoverHC) {
        G4ExceptionDescription msg;
        msg << "Crystal front cover hits collection not found." << G4endl;
        G4Exception("EventAction::EndOfEventAction()", "Code001", JustWarning, msg);
        return;
    }

    auto* PMTcoverHC = dynamic_cast<PMTcoverHitsCollection*>( hce->GetHC(fPMTcoverHCID) );
    if (!PMTcoverHC) {
        G4ExceptionDescription msg;
        msg << "PMT cover hits collection not found." << G4endl;
        G4Exception("EventAction::EndOfEventAction()", "Code001", JustWarning, msg);
        return;
    }

    // --------------------------
    // 1) Fill per-crystal arrays & histograms (keeps existing behavior)
    // --------------------------
    const size_t nCrystalsSim = static_cast<size_t>(hcHC->entries());
    const size_t toLoop = std::min<size_t>(1080, nCrystalsSim);
    for (size_t ii = 0; ii < toLoop; ++ii) {
        G4int i = static_cast<G4int>(ii);
        B5HadCalorimeterHit* hit = (*hcHC)[i];
        if (!hit) continue;
        G4double eDep = hit->GetEdep();           // Geant4 energy units (MeV)
        G4int PID = hit->GetPID();
        fHadCalEdep[i] = eDep * kCaloEnergyScale; // corrected MeV written to edep[]
        fPID[i] = PID;

        CrystalCoverHit* CChit = nullptr;
        CrystalFrontCoverHit* CFChit = nullptr;
        PMTcoverHit* PMTChit = nullptr;
        if (static_cast<size_t>(CrystCoverHC->entries()) > ii) CChit = (*CrystCoverHC)[i];
        if (static_cast<size_t>(CrystFrontCoverHC->entries()) > ii) CFChit = (*CrystFrontCoverHC)[i];
        if (static_cast<size_t>(PMTcoverHC->entries()) > ii) PMTChit = (*PMTcoverHC)[i];

        G4double sc = hit->GetOPInt_sc();
        G4double ce = hit->GetOPInt_ce();
        fOP_sc[i] = sc;
        fOP_ce[i] = ce;

        fCrystCoverOP[i] = (CChit ? CChit->GetOPInt() : 0);
        fCrystFrontCoverOP[i] = (CFChit ? CFChit->GetOPInt() : 0);
        fPMTcoverOP[i] = (PMTChit ? PMTChit->GetOPInt() : 0);

        // send to histogram manager
        fHistoManager->SetEnergyandPID(i, fPID[i], fHadCalEdep[i],
                                      fOP_sc[i], fOP_ce[i],
                                      fCrystCoverOP[i], fCrystFrontCoverOP[i], fPMTcoverOP[i]);
    }

    // --------------------------
    // 2) Fill TCaloEvent (per-block) — safe & consistent
    // --------------------------
    if (!calo_evt) {
        G4cerr << "EventAction::EndOfEventAction: calo_evt is null, skipping TCaloEvent filling." << G4endl;
    } else {
        // Clear previous event contents (TCaloEvent keeps state across events)
        calo_evt->Clear();

        const G4int kNTotalBlocks = 1080;
        // Fill blocks 0..1079. If hcHC doesn't contain that many entries, treat missing blocks as zero energy.
        for (G4int ib = 0; ib < kNTotalBlocks; ++ib) {
            G4double eDep_mev = 0.0;
            if (static_cast<size_t>(ib) < nCrystalsSim) {
                B5HadCalorimeterHit* hit = (*hcHC)[ib];
                if (hit) eDep_mev = hit->GetEdep();
            }
            // NPS_SOFT receives corrected GeV, so trigger and clust_E use same scale.
            G4double energy_GeV = eDep_mev * kCaloEnergyScale * 1e-3;

            // Add block and populate
            TCaloBlock* block = calo_evt->AddBlock(ib);
            if (block) {
                block->AddPulse(energy_GeV, 0.0);   // energy in GeV, time in ns (0 default)
                block->SetBlockEnergy(energy_GeV);  // ensure GetBlockEnergy() returns the same energy
            }
        }

        // Run trigger simulation and clustering using TCaloEvent API
        const G4double triggerThreshold_GeV = 0.5; // threshold in GeV
        calo_evt->TriggerSim(triggerThreshold_GeV); // may modify internal block selection
        calo_evt->DoClustering(-5.0, 5.0);          // time window [-5, +5] ns

        // Analyze each cluster (compute centers etc.)
        G4int Nb_clust = calo_evt->GetNbClusters();
        for (G4int ic = 0; ic < Nb_clust; ++ic) {
            TCaloCluster* clus = calo_evt->GetCluster(ic);
            if (clus) {
                clus->Analyze(1.0, -5.0, 5.0);
            }
        }

        // collect vectors for all clusters
        std::vector<Double_t> clust_x;
        std::vector<Double_t> clust_y;
        std::vector<Double_t> clust_E;
        std::vector<Int_t>   clustSize;

        for (G4int ic = 0; ic < Nb_clust; ++ic) {
            TCaloCluster* cl = calo_evt->GetCluster(ic);
            if (!cl) continue;
            clust_x.push_back(cl->GetX());
            clust_y.push_back(cl->GetY());
            clust_E.push_back(cl->GetEnergy());   // energy in GeV (as returned by TCaloCluster)
            clustSize.push_back(cl->GetClusSize());
        }

        // send vectors to histogram manager for storage in ntuple
        fHistoManager->SetClusters(clust_x, clust_y, clust_E, clustSize);

        // If you still want to preserve existing behaviour for first two clusters in dedicated branches:
        if (Nb_clust >= 2 && hit_HMS) {
            TCaloCluster* c0 = calo_evt->GetCluster(0);
            TCaloCluster* c1 = calo_evt->GetCluster(1);
            if (c0) fHistoManager->SetCaloData1(c0->GetEnergy(), c0->GetX(), c0->GetY(), c0->GetClusSize());
            if (c1) fHistoManager->SetCaloData2(c1->GetEnergy(), c1->GetX(), c1->GetY(), c1->GetClusSize());
        }
    }

    // --------------------------
    // 3) Per-photon SD info and fill photon ntuple
    // --------------------------
    // TRUE HIT POSITIONS (Geant4):
    // - Use the exact Geant4 local hit position on the crystal front face.
    // - Add block centers from DetectorConstruction's physical placement/pitch.
    // - No clustering weights or cluster-derived positions are used here.
    // --------------------------
    bool phot1_hit = B5HadCalorimeterSD::Phot1Hit();
    bool phot2_hit = B5HadCalorimeterSD::Phot2Hit();

    // default values if SD not set
    double phot1_vx = -999., phot1_vy = -999., phot1_vz = -999.;
    double phot2_vx = -999., phot2_vy = -999., phot2_vz = -999.;
    double phot1_hitx = -999., phot1_hity = -999., phot1_hitz = -999.;
    double phot2_hitx = -999., phot2_hity = -999., phot2_hitz = -999.;
    double phot1_Ecal = -999., phot2_Ecal = -999.;
    int    phot1_clustSize = -1, phot2_clustSize = -1;

    if (phot1_hit && fDetector) {
        auto p1_local = B5HadCalorimeterSD::Phot1Pos();
        const int columnNo = B5HadCalorimeterSD::Phot1Col();
        const int rowNo = B5HadCalorimeterSD::Phot1Row();

        if (columnNo >= 0 && rowNo >= 0) {
            // Local hit position on the crystal face (mm -> cm)
            const double localX_cm = p1_local.x() / CLHEP::cm;
            const double localY_cm = p1_local.y() / CLHEP::cm;

            // Match DetectorConstruction placement exactly:
            // X=(14.5-row)*pitchX, Y=(column-17.5)*pitchY. The pitch getters
            // include crystal, both wrapper layers, and inter-crystal gap.
            const double pitchX_cm = fDetector->GetCrystalPitchX() / CLHEP::cm;
            const double pitchY_cm = fDetector->GetCrystalPitchY() / CLHEP::cm;
            phot1_hitx = (14.5 - rowNo) * pitchX_cm + localX_cm;
            phot1_hity = (columnNo - 17.5) * pitchY_cm + localY_cm;
            phot1_hitz = p1_local.z() / CLHEP::cm;  // front-face z in cm
        } else {
            G4cout << "WARNING: phot1 hit missing block indices; using local position only" << G4endl;
            phot1_hitx = p1_local.x() / CLHEP::cm;
            phot1_hity = p1_local.y() / CLHEP::cm;
            phot1_hitz = p1_local.z() / CLHEP::cm;
        }

        phot1_Ecal = B5HadCalorimeterSD::Phot1Edep() / CLHEP::GeV;
        phot1_vx = fVertex_x;
        phot1_vy = fVertex_y;
        phot1_vz = fVertex_z;
    } else if (phot1_hit && !fDetector) {
        G4cout << "WARNING: phot1 hit but DetectorConstruction not available" << G4endl;
        auto p1 = B5HadCalorimeterSD::Phot1Pos();
        phot1_hitx = p1.x() / CLHEP::cm;
        phot1_hity = p1.y() / CLHEP::cm;
        phot1_hitz = p1.z() / CLHEP::cm;
        phot1_Ecal = B5HadCalorimeterSD::Phot1Edep() / CLHEP::GeV;
        phot1_vx = fVertex_x;
        phot1_vy = fVertex_y;
        phot1_vz = fVertex_z;
    }

    if (phot2_hit && fDetector) {
        auto p2_local = B5HadCalorimeterSD::Phot2Pos();
        const int columnNo = B5HadCalorimeterSD::Phot2Col();
        const int rowNo = B5HadCalorimeterSD::Phot2Row();

        if (columnNo >= 0 && rowNo >= 0) {
            const double localX_cm = p2_local.x() / CLHEP::cm;
            const double localY_cm = p2_local.y() / CLHEP::cm;

            const double pitchX_cm = fDetector->GetCrystalPitchX() / CLHEP::cm;
            const double pitchY_cm = fDetector->GetCrystalPitchY() / CLHEP::cm;
            phot2_hitx = (14.5 - rowNo) * pitchX_cm + localX_cm;
            phot2_hity = (columnNo - 17.5) * pitchY_cm + localY_cm;
            phot2_hitz = p2_local.z() / CLHEP::cm;
        } else {
            G4cout << "WARNING: phot2 hit missing block indices; using local position only" << G4endl;
            phot2_hitx = p2_local.x() / CLHEP::cm;
            phot2_hity = p2_local.y() / CLHEP::cm;
            phot2_hitz = p2_local.z() / CLHEP::cm;
        }

        phot2_Ecal = B5HadCalorimeterSD::Phot2Edep() / CLHEP::GeV;
        phot2_vx = fVertex_x;
        phot2_vy = fVertex_y;
        phot2_vz = fVertex_z;
    } else if (phot2_hit && !fDetector) {
        G4cout << "WARNING: phot2 hit but DetectorConstruction not available" << G4endl;
        auto p2 = B5HadCalorimeterSD::Phot2Pos();
        phot2_hitx = p2.x() / CLHEP::cm;
        phot2_hity = p2.y() / CLHEP::cm;
        phot2_hitz = p2.z() / CLHEP::cm;
        phot2_Ecal = B5HadCalorimeterSD::Phot2Edep() / CLHEP::GeV;
        phot2_vx = fVertex_x;
        phot2_vy = fVertex_y;
        phot2_vz = fVertex_z;
    }

    // // --- Cluster info (first two clusters) preserved for compatibility ---
    // G4int    clust_size1 = -1, clust_size2 = -1;
    // G4double clust_x1 = 0, clust_y1 = 0, clust_e1 = 0;
    // G4double clust_x2 = 0, clust_y2 = 0, clust_e2 = 0;

    // if (calo_evt && calo_evt->GetNbClusters() > 0) {
    //     auto c1 = calo_evt->GetCluster(0);
    //     if (c1) {
    //         clust_size1 = c1->GetClusSize();
    //         clust_x1    = c1->GetX();
    //         clust_y1    = c1->GetY();
    //         clust_e1    = c1->GetEnergy();
    //     }
    // }

    // if (calo_evt && calo_evt->GetNbClusters() > 1) {
    //     auto c2 = calo_evt->GetCluster(1);
    //     if (c2) {
    //         clust_size2 = c2->GetClusSize();
    //         clust_x2    = c2->GetX();
    //         clust_y2    = c2->GetY();
    //         clust_e2    = c2->GetEnergy();
    //     }
    // }

    // phot1_clustSize = clust_size1;
    // phot2_clustSize = clust_size2;

    // // Pass values to HistoManager via setters (these fill the members that are branched)
    // fHistoManager->SetPhotHit1(phot1_hit, phot1_vx, phot1_vy, phot1_vz,
    //                            phot1_hitx, phot1_hity, phot1_hitz,
    //                            clust_x1, clust_y1,
    //                            phot1_Ecal, phot1_clustSize);

    // fHistoManager->SetPhotHit2(phot2_hit, phot2_vx, phot2_vy, phot2_vz,
    //                            phot2_hitx, phot2_hity, phot2_hitz,
    //                            clust_x2, clust_y2,
    //                            phot2_Ecal, phot2_clustSize);

    // --- Cluster info (first two clusters) preserved for compatibility ---
    G4int    clust_size1 = -1, clust_size2 = -1;
    G4double clust_x1 = 0, clust_y1 = 0, clust_e1 = 0;
    G4double clust_x2 = 0, clust_y2 = 0, clust_e2 = 0;

    if (calo_evt && calo_evt->GetNbClusters() > 0) {
        auto c1 = calo_evt->GetCluster(0);
        if (c1) {
            clust_size1 = c1->GetClusSize();
            clust_x1    = c1->GetX();
            clust_y1    = c1->GetY();
            clust_e1    = c1->GetEnergy();
        }
    }

    if (calo_evt && calo_evt->GetNbClusters() > 1) {
        auto c2 = calo_evt->GetCluster(1);
        if (c2) {
            clust_size2 = c2->GetClusSize();
            clust_x2    = c2->GetX();
            clust_y2    = c2->GetY();
            clust_e2    = c2->GetEnergy();
        }
    }

    // Prepare per-photon cluster outputs (defaults)
    double phot1_clust_x = -999., phot1_clust_y = -999.;
    double phot2_clust_x = -999., phot2_clust_y = -999.;
    // int    phot1_clustSize = -1, phot2_clustSize = -1;

    // Helper: absolute difference. Uses <cmath>
    auto diff = [](double a, double b){ return std::fabs(a - b); };

    // Case classification based on hits & cluster availability
    int nclusters = 0;
    if (clust_size1 >= 0) ++nclusters;
    if (clust_size2 >= 0) ++nclusters;

    if (nclusters == 0) {
        // no clusters: leave defaults
    }
    else if (nclusters == 1) {
        // single cluster present -> decide which photon it's closest to
        // prefer the photon that actually registered a hit; if no photons hit, default to phot1
        double e = (clust_size1 >= 0) ? clust_e1 : clust_e2;
        if (phot1_hit && !phot2_hit) {
            // assign to phot1
            phot1_clust_x = (clust_size1 >= 0) ? clust_x1 : clust_x2;
            phot1_clust_y = (clust_size1 >= 0) ? clust_y1 : clust_y2;
            phot1_clustSize = (clust_size1 >= 0) ? clust_size1 : clust_size2;
        } else if (phot2_hit && !phot1_hit) {
            // assign to phot2
            phot2_clust_x = (clust_size1 >= 0) ? clust_x1 : clust_x2;
            phot2_clust_y = (clust_size1 >= 0) ? clust_y1 : clust_y2;
            phot2_clustSize = (clust_size1 >= 0) ? clust_size1 : clust_size2;
        } else if (phot1_hit && phot2_hit) {
            // both photons hit -> pick closer
            double d1 = diff(e, phot1_Ecal);
            double d2 = diff(e, phot2_Ecal);
            if (d1 <= d2) {
                phot1_clust_x = (clust_size1 >= 0) ? clust_x1 : clust_x2;
                phot1_clust_y = (clust_size1 >= 0) ? clust_y1 : clust_y2;
                phot1_clustSize = (clust_size1 >= 0) ? clust_size1 : clust_size2;
            } else {
                phot2_clust_x = (clust_size1 >= 0) ? clust_x1 : clust_x2;
                phot2_clust_y = (clust_size1 >= 0) ? clust_y1 : clust_y2;
                phot2_clustSize = (clust_size1 >= 0) ? clust_size1 : clust_size2;
            }
        } else {
            // no photons hit -> default to phot1
            phot1_clust_x = (clust_size1 >= 0) ? clust_x1 : clust_x2;
            phot1_clust_y = (clust_size1 >= 0) ? clust_y1 : clust_y2;
            phot1_clustSize = (clust_size1 >= 0) ? clust_size1 : clust_size2;
        }
    }
    else { // nclusters == 2
        // Both clusters present. Three possibilities:
        // - both photons hit -> choose assignment (1->p1,2->p2) or (1->p2,2->p1) minimizing total |ΔE|
        // - only one photon hit -> assign the cluster closest to that photon
        // - no photons hit -> default mapping clust1->phot1, clust2->phot2
        if (phot1_hit && phot2_hit) {
            double opt1 = diff(clust_e1, phot1_Ecal) + diff(clust_e2, phot2_Ecal); // c1->p1, c2->p2
            double opt2 = diff(clust_e1, phot2_Ecal) + diff(clust_e2, phot1_Ecal); // c1->p2, c2->p1
            if (opt1 <= opt2) {
                // assign c1->phot1, c2->phot2
                phot1_clust_x = clust_x1; phot1_clust_y = clust_y1; phot1_clustSize = clust_size1;
                phot2_clust_x = clust_x2; phot2_clust_y = clust_y2; phot2_clustSize = clust_size2;
            } else {
                // assign c1->phot2, c2->phot1
                phot2_clust_x = clust_x1; phot2_clust_y = clust_y1; phot2_clustSize = clust_size1;
                phot1_clust_x = clust_x2; phot1_clust_y = clust_y2; phot1_clustSize = clust_size2;
            }
        } else if (phot1_hit && !phot2_hit) {
            // only phot1 hit: pick cluster closer to phot1
            double d1 = diff(clust_e1, phot1_Ecal);
            double d2 = diff(clust_e2, phot1_Ecal);
            if (d1 <= d2) {
                phot1_clust_x = clust_x1; phot1_clust_y = clust_y1; phot1_clustSize = clust_size1;
                // leave phot2 defaults (unassigned)
            } else {
                phot1_clust_x = clust_x2; phot1_clust_y = clust_y2; phot1_clustSize = clust_size2;
            }
        } else if (phot2_hit && !phot1_hit) {
            // only phot2 hit: pick cluster closer to phot2
            double d1 = diff(clust_e1, phot2_Ecal);
            double d2 = diff(clust_e2, phot2_Ecal);
            if (d1 <= d2) {
                phot2_clust_x = clust_x1; phot2_clust_y = clust_y1; phot2_clustSize = clust_size1;
            } else {
                phot2_clust_x = clust_x2; phot2_clust_y = clust_y2; phot2_clustSize = clust_size2;
            }
        } else {
            // no photon SD hits -> default mapping
            phot1_clust_x = clust_x1; phot1_clust_y = clust_y1; phot1_clustSize = clust_size1;
            phot2_clust_x = clust_x2; phot2_clust_y = clust_y2; phot2_clustSize = clust_size2;
        }
    }

    // Now set the values that the HistoManager expects (keep compatibility)
    // If you prefer to keep the original variable names clust_x1/clust_y1 etc.
    // you can overwrite them here — but we pass the assigned per-photon cluster coords below.
    fHistoManager->SetPhotHit1(phot1_hit, phot1_vx, phot1_vy, phot1_vz,
                            phot1_hitx, phot1_hity, phot1_hitz,
                            phot1_clust_x, phot1_clust_y,
                            phot1_Ecal, phot1_clustSize);

    fHistoManager->SetPhotHit2(phot2_hit, phot2_vx, phot2_vy, phot2_vz,
                            phot2_hitx, phot2_hity, phot2_hitz,
                            phot2_clust_x, phot2_clust_y,
                            phot2_Ecal, phot2_clustSize);


    // Fill ntuple (photons + cluster vectors)
    fHistoManager->FillNtupleDVCS();

    // --------------------------
    // 4) Flux hit (if present)
    // --------------------------
    auto* fluxHC = dynamic_cast<FluxHitsCollection*>( hce->GetHC(fFlxHCID) );
    if (!fluxHC) {
        // It's acceptable to not have a flux collection for some setups; warn but do not abort.
        G4ExceptionDescription msg;
        msg << "Flux hits collection not found for this event." << G4endl;
        G4Exception("EventAction::EndOfEventAction()", "Code002", JustWarning, msg);
        return;
    }
    if (fluxHC->entries() > 0) {
        FluxHit* fluxhit = (*fluxHC)[0];
        if (fluxhit) {
            G4double energy = fluxhit->GetEdep();
            G4int fluxPID = fluxhit->GetPID();
            G4ThreeVector position = fluxhit->GetPos();
            fFluxEnergy = energy;
            fFluxPID = fluxPID;
            fPos = position;
            // store for histograms if desired
            fHistoManager->SetFluxSphereEnergyandPID(fluxPID, energy, position);
        }
    }
}

void EventAction::DefinePrimaries(const TLorentzVector& L_phot1_final,
                                  const TLorentzVector& L_phot2_final,
                                  G4double vertex_x, G4double vertex_y, G4double vertex_z, Long64_t simcEntryIndex)
{
    // Store TLVs by value
    L_calo_phot1 = L_phot1_final;
    L_calo_phot2 = L_phot2_final;

    // Fill only photon-related indices (legacy layout uses indices 2 and 3)
    fPx[2] = L_calo_phot1.Px();
    fPy[2] = L_calo_phot1.Py();
    fPz[2] = L_calo_phot1.Pz();
    fE[2]  = L_calo_phot1.E();

    fPx[3] = L_calo_phot2.Px();
    fPy[3] = L_calo_phot2.Py();
    fPz[3] = L_calo_phot2.Pz();
    fE[3]  = L_calo_phot2.E();

    // Vertex (unit is mm; converted from SIMC cm to Geant mm in PrimaryGeneratorAction.cc)
    fVertex_x = vertex_x / CLHEP::cm;
    fVertex_y = vertex_y / CLHEP::cm;
    fVertex_z = vertex_z / CLHEP::cm;

    // Copy the SIMC entry into histo buffers (so the output row contains simc fields)
    if(simcEntryIndex >= 0) {
        if(!fHistoManager->CopySIMCEntry(simcEntryIndex)) {
            G4cout << "EventAction::DefinePrimaries: warning - CopySIMCEntry failed for index " << simcEntryIndex << G4endl;
        }
    }

    // // Fill histogram manager photon & vertex related information
    // fHistoManager->SetVertexGen(fVertex_x, fVertex_y, fVertex_z);
    // fHistoManager->SetPhotGen1(fPx[2], fPy[2], fPz[2]);
    // fHistoManager->SetPhotGen2(fPx[3], fPy[3], fPz[3]);
}

G4int EventAction::GetEventNb()
{
    return fEvtNb;
}
