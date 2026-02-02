// B5HadCalorimeterSD.cc
#include "B5HadCalorimeterSD.hh"
#include "B5HadCalorimeterHit.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "G4Gamma.hh"
#include "G4StepPoint.hh"
#include "G4SystemOfUnits.hh"

#include "G4OpticalPhoton.hh"
#include "G4VProcess.hh"

#include <unordered_map>
#include <vector>

// Static member definitions (class members)
G4int  B5HadCalorimeterSD::fPhot1TrackID = 0;
G4int  B5HadCalorimeterSD::fPhot2TrackID = 0;
G4bool B5HadCalorimeterSD::fPhot1HitFlag = false;
G4bool B5HadCalorimeterSD::fPhot2HitFlag = false;
G4ThreeVector B5HadCalorimeterSD::fPhot1Pos = G4ThreeVector(0,0,0);
G4ThreeVector B5HadCalorimeterSD::fPhot2Pos = G4ThreeVector(0,0,0);
G4double B5HadCalorimeterSD::fPhot1Edep = 0.0;
G4double B5HadCalorimeterSD::fPhot2Edep = 0.0;
G4int B5HadCalorimeterSD::fPhot1Col = -1;
G4int B5HadCalorimeterSD::fPhot1Row = -1;
G4int B5HadCalorimeterSD::fPhot2Col = -1;
G4int B5HadCalorimeterSD::fPhot2Row = -1;

// File-scope parent map: trackID -> parentID
// NOTE: We keep this as a file-scope container so we do NOT need to modify header files.
static std::unordered_map<G4int, G4int> sParentMap;

// Constructor
B5HadCalorimeterSD::B5HadCalorimeterSD(const G4String& name)
: G4VSensitiveDetector(name), fHitsCollection(0), fHCID(-1)
{
    collectionName.insert("HadCalorimeterColl");
}

// Destructor
B5HadCalorimeterSD::~B5HadCalorimeterSD() {}

// Reset per-event photon bookkeeping
void B5HadCalorimeterSD::ResetPhotonInfo()
{
    fPhot1TrackID = 0;
    fPhot2TrackID = 0;
    fPhot1HitFlag = false;
    fPhot2HitFlag = false;
    fPhot1Pos = G4ThreeVector(0,0,0);
    fPhot2Pos = G4ThreeVector(0,0,0);
    fPhot1Edep = 0.0;
    fPhot2Edep = 0.0;
    fPhot1Col = -1;
    fPhot1Row = -1;
    fPhot2Col = -1;
    fPhot2Row = -1;

    // Clear the parent map for the next event
    sParentMap.clear();
}

void B5HadCalorimeterSD::Initialize(G4HCofThisEvent* hce)
{
    // Create hits collection
    fHitsCollection = new B5HadCalorimeterHitsCollection(SensitiveDetectorName, collectionName[0]);
    if (fHCID < 0) {
        fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    }
    hce->AddHitsCollection(fHCID, fHitsCollection);

    // Initialize all hits to zero energy deposition
    for (G4int iColumn=0; iColumn<36; ++iColumn) {
        for (G4int iRow=0; iRow<30; ++iRow) {
            B5HadCalorimeterHit* hit = new B5HadCalorimeterHit();
            fHitsCollection->insert(hit);
        }
    }

    // Reset per-event photon info (also clears parent map)
    ResetPhotonInfo();
}

G4bool B5HadCalorimeterSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
    G4double edep = step->GetTotalEnergyDeposit();
    G4StepPoint* prePoint = step->GetPreStepPoint();
    G4StepPoint* postPoint = step->GetPostStepPoint();

    G4TouchableHistory* touchable = (G4TouchableHistory*)(prePoint->GetTouchable());

    // Determine hit ID based on crystal's row and column
    G4VPhysicalVolume* cellPhysical = touchable->GetVolume(2);
    G4int rowNo = cellPhysical->GetCopyNo();         // 0 - 29
    G4VPhysicalVolume* columnPhysical = touchable->GetVolume(1);
    G4int columnNo = columnPhysical->GetCopyNo();   // 0 - 35
    G4int hitID = columnNo + 36 * rowNo;            // 0 - 1079

    B5HadCalorimeterHit* hit = (*fHitsCollection)[hitID];
    if (!hit) return false;

    // Count optical photons from scintillation/cerenkov and record parent mapping
    G4int sc = 0;
    G4int ce = 0;

    // Current track and parent mapping
    G4Track* track = step->GetTrack();
    if (!track) return false;
    G4int tid = track->GetTrackID();
    G4int parent = track->GetParentID();

    // Record mapping for current track (overwrite is harmless)
    sParentMap[tid] = parent;

    // secondaries recorded in this step (may be nullptr)
    const std::vector<const G4Track*>* secondaries = step->GetSecondaryInCurrentStep();
    if (secondaries) {
        for (size_t i = 0; i < secondaries->size(); ++i) {
            const G4Track* sec = secondaries->at(i);
            if (!sec) continue;
            G4int secID = sec->GetTrackID();
            G4int secParent = sec->GetParentID();
            // record mapping for secondary
            sParentMap[secID] = secParent;

            // optical photon counting as before
            if (secParent > 0 &&
                sec->GetDynamicParticle()->GetParticleDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
                G4String creator = "Unknown";
                if (sec->GetCreatorProcess()) creator = sec->GetCreatorProcess()->GetProcessName();
                if (creator == "Scintillation") sc++;
                else if (creator == "Cerenkov") ce++;
            }
        }
    }

    G4int PID = track->GetDynamicParticle()->GetParticleDefinition()->GetPDGEncoding();

    // Detect first entry of a primary gamma
    if (track && PID == 22 && track->GetParentID() == 0 && prePoint->GetStepStatus() == fGeomBoundary) {
        G4ThreeVector entryWorld = prePoint->GetPosition();
        G4ThreeVector entryLocal(0.,0.,0.);

        // Convert world -> local
        G4TouchableHandle touch = prePoint->GetTouchableHandle();
        if (touch && touch->GetHistory()->GetDepth() > 0) {
            entryLocal = touch->GetHistory()->GetTopTransform().TransformPoint(entryWorld);
        } else if (touch) {
            G4int depth = touch->GetHistory()->GetDepth();
            if (depth >= 1) {
                G4AffineTransform trans = touch->GetHistory()->GetTransform(depth-1);
                trans.Invert();
                entryLocal = trans.TransformPoint(entryWorld);
            } else {
                entryLocal = entryWorld;
            }
        }

        // Adjust coordinates for recording
        // z: move to crystal front face (+10cm)
        G4double dz = 100*mm; // half-length of crystal along z
        G4double zFront = entryLocal.z() + dz;

        // Assign photon hit info
        if (fPhot1TrackID == 0) {
            fPhot1TrackID = tid;
            fPhot1HitFlag  = true;
            // Store local hit position on the crystal front face (mm) + block indices
            fPhot1Pos = G4ThreeVector(entryLocal.x(), entryLocal.y(), zFront);
            // Extract actual column/row from hitID (since touchable copy number is the full hitID at boundary)
            fPhot1Col = hitID % 36;
            fPhot1Row = hitID / 36;
        } else if (fPhot2TrackID == 0 && tid != fPhot1TrackID) {
            fPhot2TrackID = tid;
            fPhot2HitFlag  = true;
            fPhot2Pos = G4ThreeVector(entryLocal.x(), entryLocal.y(), zFront);
            // Extract actual column/row from hitID
            fPhot2Col = hitID % 36;
            fPhot2Row = hitID / 36;
        }
    }

    // Save transform/pos for rendering on first touch
    if (hit->GetColumnID() < 0) {
        hit->SetColumnID(columnNo);
        hit->SetRowID(rowNo);
        G4int depth = touchable->GetHistory()->GetDepth();
        G4AffineTransform transform = touchable->GetHistory()->GetTransform(depth-2);
        transform.Invert();
        hit->SetRot(transform.NetRotation());
        hit->SetPos(transform.NetTranslation());
    }

    // Add energy deposition to the per-cell hit record
    if (edep > 0.) {
        hit->AddEdep(edep);
        hit->SetPID(PID);
        hit->AddOPInt_sc(sc);
        hit->AddOPInt_ce(ce);
    }

    // Helper lambda: test whether candidate trackID is a descendant of ancestorID
    auto isDescendantOf = [&](G4int candidate, G4int ancestorID) -> bool {
        if (ancestorID == 0) return false;
        if (candidate == ancestorID) return true;
        G4int cur = candidate;
        const int MAX_DEPTH = 500; // safety guard
        int depth = 0;
        while (depth++ < MAX_DEPTH) {
            auto it = sParentMap.find(cur);
            if (it == sParentMap.end()) {
                // We don't have parent info for 'cur' (maybe it never stepped in SD); cannot climb further.
                return false;
            }
            cur = it->second; // climb to parent
            if (cur == 0) return false; // reached primary (no further parent)
            if (cur == ancestorID) return true;
        }
        return false;
    };

    // Attribute energy deposition to phot1/phot2 using ancestry-aware test
    if (edep > 0.) {
        if (fPhot1TrackID != 0 && isDescendantOf(tid, fPhot1TrackID)) {
            fPhot1Edep += edep;
        } else if (fPhot2TrackID != 0 && isDescendantOf(tid, fPhot2TrackID)) {
            fPhot2Edep += edep;
        }
    }

    return true;
}
