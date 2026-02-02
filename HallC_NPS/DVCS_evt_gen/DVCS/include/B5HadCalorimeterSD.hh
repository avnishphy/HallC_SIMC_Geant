//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B5HadCalorimeterSD.hh 76474 2013-11-11 10:36:34Z gcosmo $
//
/// \file B5HadCalorimeterSD.hh
/// \brief Definition of the B5HadCalorimeterSD class

// #ifndef B5HadCalorimeterSD_h
// #define B5HadCalorimeterSD_h 1

// #include "G4VSensitiveDetector.hh"

// #include "B5HadCalorimeterHit.hh"

// class G4Step;
// class G4HCofThisEvent;
// class G4TouchableHistory;

// /// Hadron calorimeter sensitive detector

// class B5HadCalorimeterSD : public G4VSensitiveDetector
// {    
// public:
//     B5HadCalorimeterSD(G4String name);
//     virtual ~B5HadCalorimeterSD();
    
//     virtual void Initialize(G4HCofThisEvent*HCE);
//     virtual G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
    
// private:
//     B5HadCalorimeterHitsCollection* fHitsCollection;
//     G4int fHCID;
// };

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// #endif


// B5HadCalorimeterSD.hh
#ifndef B5HadCalorimeterSD_h
#define B5HadCalorimeterSD_h

#include "G4VSensitiveDetector.hh"
#include "G4THitsCollection.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

class B5HadCalorimeterHit;
class G4HCofThisEvent;

class B5HadCalorimeterSD : public G4VSensitiveDetector {
public:
  explicit B5HadCalorimeterSD(const G4String& name);
  virtual ~B5HadCalorimeterSD();

  virtual void Initialize(G4HCofThisEvent* hce) override;
  virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
  virtual void EndOfEvent(G4HCofThisEvent* hce) override {}

  // Per-event photon info: reset at BeginOfEvent (called from Initialize)
  static void ResetPhotonInfo();

  // getters for EventAction / HistoManager
  static G4bool Phot1Hit()   { return fPhot1HitFlag; }
  static G4bool Phot2Hit()   { return fPhot2HitFlag; }

  // Local hit position on the crystal front face (Geant4 local coordinates, in mm)
  static G4ThreeVector Phot1Pos() { return fPhot1Pos; }
  static G4ThreeVector Phot2Pos() { return fPhot2Pos; }

  // Block indices for the hit crystal
  static G4int Phot1Col() { return fPhot1Col; }
  static G4int Phot1Row() { return fPhot1Row; }
  static G4int Phot2Col() { return fPhot2Col; }
  static G4int Phot2Row() { return fPhot2Row; }

  static G4double Phot1Edep() { return fPhot1Edep; }
  static G4double Phot2Edep() { return fPhot2Edep; }

  static G4int Phot1TrackID() { return fPhot1TrackID; }
  static G4int Phot2TrackID() { return fPhot2TrackID; }

private:
  G4THitsCollection<B5HadCalorimeterHit>* fHitsCollection;
  G4int fHCID;

  // Static per-event variables (cleared each event)
  static G4int    fPhot1TrackID;
  static G4int    fPhot2TrackID;
  static G4bool   fPhot1HitFlag;
  static G4bool   fPhot2HitFlag;
  static G4ThreeVector fPhot1Pos;
  static G4ThreeVector fPhot2Pos;
  static G4int fPhot1Col;
  static G4int fPhot1Row;
  static G4int fPhot2Col;
  static G4int fPhot2Row;
  static G4double fPhot1Edep;
  static G4double fPhot2Edep;
};

#endif // B5HadCalorimeterSD_h
