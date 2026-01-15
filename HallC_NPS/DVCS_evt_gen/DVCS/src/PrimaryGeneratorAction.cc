// PrimaryGeneratorAction.cc
#include "PrimaryGeneratorAction.hh"
#include "EventAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PrimaryParticle.hh"
#include "G4PrimaryVertex.hh"
#include "G4SystemOfUnits.hh"
#include "G4Exception.hh"
#include "G4UnitsTable.hh"
#include "G4ThreeVector.hh"

#include "dvcsGlobals.hh"

#include "TFile.h"
#include "TTree.h"
#include "TVector3.h"
#include "TLorentzVector.h"

#include <cmath>
#include <iostream>

// =====================
// Unit conversion
// =====================
constexpr double MeV_to_GeV = 1.0e-3;

// ============================================================
PrimaryGeneratorAction::PrimaryGeneratorAction(EventAction* evt,
                                               const TString& simcFileName,
                                               const TString& treeName)
  : G4VUserPrimaryGeneratorAction(),
    fEventAction(evt),
    fParticleGun(nullptr),
    useSIMC(false),
    simcFilePath(simcFileName),
    simcTreeName(treeName),
    simcFile(nullptr),
    simcTree(nullptr),
    simcNEntries(0),
    simcEntryIdx(0)
{
    if (simcFilePath.Length() == 0) {
        G4cerr << "PrimaryGeneratorAction: no SIMC file path provided.\n";
        return;
    }

    simcFile = TFile::Open(simcFilePath.Data(), "READ");
    if (!simcFile || simcFile->IsZombie()) {
        G4cerr << "PrimaryGeneratorAction: Cannot open SIMC file "
               << simcFilePath << G4endl;
        if (simcFile && simcFile->IsOpen()) { simcFile->Close(); }
        simcFile = nullptr;
        return;
    }

    simcTree = dynamic_cast<TTree*>(simcFile->Get(simcTreeName.Data()));
    if (!simcTree) {
        G4cerr << "PrimaryGeneratorAction: Cannot find tree "
               << simcTreeName << " in file " << simcFilePath << G4endl;
        simcFile->Close();
        delete simcFile;
        simcFile = nullptr;
        return;
    }

    // ---- Branch addresses (VERIFY NAMES) ----
    simcTree->SetBranchAddress("Pgamma1x", &Pgamma1x);
    simcTree->SetBranchAddress("Pgamma1y", &Pgamma1y);
    simcTree->SetBranchAddress("Pgamma1z", &Pgamma1z);
    simcTree->SetBranchAddress("Egamma1",  &Egamma1);

    simcTree->SetBranchAddress("Pgamma2x", &Pgamma2x);
    simcTree->SetBranchAddress("Pgamma2y", &Pgamma2y);
    simcTree->SetBranchAddress("Pgamma2z", &Pgamma2z);
    simcTree->SetBranchAddress("Egamma2",  &Egamma2);

    simcTree->SetBranchAddress("vtx_x", &vtx_x);
    simcTree->SetBranchAddress("vtx_y", &vtx_y);
    simcTree->SetBranchAddress("vtx_z", &vtx_z);

    simcNEntries = simcTree->GetEntries();
    simcEntryIdx = 0;
    useSIMC = true;

    G4cout << "PrimaryGeneratorAction: Loaded SIMC file "
           << simcFilePath << " with "
           << simcNEntries << " entries" << G4endl;
}

// ============================================================
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    if (simcFile) {
        if (simcFile->IsOpen()) simcFile->Close();
        delete simcFile;
        simcFile = nullptr;
    }
}

// ============================================================
// Rotate NPS → Hall (about +Y). dvcsGlobals::Calo_angle is in radians.
// ============================================================
TVector3 PrimaryGeneratorAction::NpsToHall(const TVector3& v) const
{
    const double theta = dvcsGlobals::Calo_angle; // radians
    const double c = std::cos(theta);
    const double s = std::sin(theta);

    return TVector3(
        c * v.X() - s * v.Z(),
        v.Y(),
        s * v.X() + c * v.Z()
    );
}

// ============================================================
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    if (!useSIMC || !simcTree) {
        G4Exception("PrimaryGeneratorAction::GeneratePrimaries",
                    "SIMC_DISABLED",
                    JustWarning,
                    "SIMC input not configured - no primaries will be produced.");
        event->SetEventAborted();
        return;
    }

    // Bounds check: if we've run out of entries, abort gracefully.
    if (simcEntryIdx >= simcNEntries) {
        G4cerr << "PrimaryGeneratorAction::GeneratePrimaries: reached end of SIMC entries ("
               << simcEntryIdx << " >= " << simcNEntries << "). Aborting remaining events." << G4endl;
        event->SetEventAborted();
        return;
    }

    const Long64_t entryToRead = simcEntryIdx;
    Long64_t got = simcTree->GetEntry(entryToRead);
    if (got <= 0) {
        G4cerr << "PrimaryGeneratorAction::GeneratePrimaries: failed to read SIMC entry " << entryToRead << G4endl;
        event->SetEventAborted();
        return;
    }
    simcEntryIdx++;
    const Long64_t thisEntry = entryToRead;

    G4cout << "PrimaryGeneratorAction::GeneratePrimaries called for entry "
           << thisEntry << " (simcEntryIdx now " << simcEntryIdx << ")" << G4endl;

    // ---- Momentum vectors (SIMC frame, SIMC provides MeV) ----
    // Convert MeV -> GeV for TLorentzVector storage.
    // TVector3 p1_nps_mev(Pgamma1x, Pgamma1y, Pgamma1z);
    // TVector3 p2_nps_mev(Pgamma2x, Pgamma2y, Pgamma2z);

    TVector3 p1_nps_mev(Pgamma1y, -Pgamma1x, Pgamma1z);
    TVector3 p2_nps_mev(Pgamma2y, -Pgamma2x, Pgamma2z);

    TVector3 p1_nps = p1_nps_mev * MeV_to_GeV; // now in GeV
    TVector3 p2_nps = p2_nps_mev * MeV_to_GeV; // now in GeV

    // ---- Rotate to Hall (still in GeV) ----
    // TVector3 p1_hall = NpsToHall(p1_nps);
    // TVector3 p2_hall = NpsToHall(p2_nps);

    TVector3 p1_hall = (p1_nps);
    TVector3 p2_hall = (p2_nps);

    // ---- Energies: prefer Egamma* branch if > 0 (SIMC gives MeV), otherwise compute from momentum.
    const double mag1_GeV = p1_hall.Mag(); // already in GeV
    const double mag2_GeV = p2_hall.Mag(); // already in GeV
    const double E1_GeV = (Egamma1 > 0.0 ? (Egamma1 * MeV_to_GeV) : mag1_GeV);
    const double E2_GeV = (Egamma2 > 0.0 ? (Egamma2 * MeV_to_GeV) : mag2_GeV);

    // ---- Store TLorentzVectors (GeV) ----
    L_phot1_final.SetPxPyPzE(
        p1_hall.X(),
        p1_hall.Y(),
        p1_hall.Z(),
        E1_GeV
    );

    L_phot2_final.SetPxPyPzE(
        p2_hall.X(),
        p2_hall.Y(),
        p2_hall.Z(),
        E2_GeV
    );

    // ---- Vertex (SIMC vertex is in cm) -> convert to internal units (CLHEP::cm)
    // main%target%x = beam right looking along beam direction
    // main%target%y = up, towards hall ceiling
    // main%target%z = along beam direction
    const double vx = -1*vtx_x * CLHEP::cm; // SIMC target coordinates left handed
    const double vy = vtx_y * CLHEP::cm;
    const double vz = vtx_z * CLHEP::cm;

    // ---- Inform EventAction (TLorentzVectors are in GeV; vertex in CLHEP units (mm)) ----
    if (fEventAction) {
        fEventAction->DefinePrimaries(
            L_phot1_final,
            L_phot2_final,
            vx, vy, vz,
            thisEntry
        );
    }

    // ---- Geant4 primary vertex (Geant4 expects momenta in internal units) ----
    auto* vertex = new G4PrimaryVertex(G4ThreeVector(vx, vy, vz), 0.0);

    auto* gamma = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
    if (!gamma) {
        G4Exception("PrimaryGeneratorAction",
                    "NO_GAMMA",
                    FatalException,
                    "Gamma particle not found in G4ParticleTable.");
        delete vertex;
        return;
    }

    // Convert momenta from GeV -> internal units using CLHEP::GeV when constructing G4PrimaryParticle.
    const double g1_px = L_phot1_final.Px() * CLHEP::GeV;
    const double g1_py = L_phot1_final.Py() * CLHEP::GeV;
    const double g1_pz = L_phot1_final.Pz() * CLHEP::GeV;

    const double g2_px = L_phot2_final.Px() * CLHEP::GeV;
    const double g2_py = L_phot2_final.Py() * CLHEP::GeV;
    const double g2_pz = L_phot2_final.Pz() * CLHEP::GeV;

    auto* g1 = new G4PrimaryParticle(gamma, g1_px, g1_py, g1_pz);
    auto* g2 = new G4PrimaryParticle(gamma, g2_px, g2_py, g2_pz);

    vertex->SetPrimary(g1);
    vertex->SetPrimary(g2);

    event->AddPrimaryVertex(vertex);

    // Debug print (momentum magnitudes in GeV)
    G4cout << "  Produced two gammas: |p1|=" << L_phot1_final.Vect().Mag()
           << " GeV, |p2|=" << L_phot2_final.Vect().Mag()
           << " GeV, vertex(cm)=(" << vtx_x << "," << vtx_y << "," << vtx_z << ")" << G4endl;
}
