// //
// // ********************************************************************
// // * License and Disclaimer                                           *
// // *                                                                  *
// // * The  Geant4 software  is  copyright of the Copyright Holders  of *
// // * the Geant4 Collaboration.  It is provided  under  the terms  and *
// // * conditions of the Geant4 Software License,  included in the file *
// // * LICENSE and available at  http://cern.ch/geant4/license .  These *
// // * include a list of copyright holders.                             *
// // *                                                                  *
// // * Neither the authors of this software system, nor their employing *
// // * institutes,nor the agencies providing financial support for this *
// // * work  make  any representation or  warranty, express or implied, *
// // * regarding  this  software system or assume any liability for its *
// // * use.  Please see the license in the file  LICENSE  and URL above *
// // * for the full disclaimer and the limitation of liability.         *
// // *                                                                  *
// // * This  code  implementation is the result of  the  scientific and *
// // * technical work of the GEANT4 collaboration.                      *
// // * By using,  copying,  modifying or  distributing the software (or *
// // * any work based  on the software)  you  agree  to acknowledge its *
// // * use  in  resulting  scientific  publications,  and indicate your *
// // * acceptance of all terms of the Geant4 Software license.          *
// // ********************************************************************
// //
// /// \file electromagnetic/TestEm4/include/PrimaryGeneratorAction.hh
// /// \brief Definition of the PrimaryGeneratorAction class
// //
// //
// // $Id: PrimaryGeneratorAction.hh 66241 2012-12-13 18:34:42Z gunter $
// //
// // 

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// #ifndef PrimaryGeneratorAction_h
// #define PrimaryGeneratorAction_h 1

// #include "G4VUserPrimaryGeneratorAction.hh"
// #include "globals.hh"
// #include "G4ParticleGun.hh"

// #include "TGenPi0.h"
// #include "TGenGeo.h"
// #include <TObject.h>

// #include "TVector3.h"

// #include "TLorentzVector.h"

// class EventAction;
// class G4Event;
// class G4ParticleGun;
// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
// {
//   public:
//   PrimaryGeneratorAction(EventAction*, long, long);    
//    ~PrimaryGeneratorAction();

//   public:
//     virtual void GeneratePrimaries(G4Event*);
//   G4ParticleGun* GetParticleGun() {return fParticleGun;};

//   private:
//   EventAction*    fEventAction;

//   G4double M_targ;
//   G4ParticleGun*  fParticleGun;
//   TGenPi0* gEv;

//   TLorentzVector* L_elec_init;
//   TLorentzVector* L_elec_scat;
//   TLorentzVector* L_phot1_final;
//   TLorentzVector* L_phot2_final;
//   TLorentzVector* L_prot_final;

//   G4int target_gen_proc_type;
// };

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// #endif

// PrimaryGeneratorAction.hh
// Modified to use SIMC scattered electron + SIMC gammas; initial electron built from beam.

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleGun.hh"
#include "EventAction.hh"

#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <TString.h>

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction(EventAction* evt, const TString& simcFile = "", const TString& treeName = "h10");
    virtual ~PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* anEvent) override;

private:
    EventAction* fEventAction;
    G4ParticleGun* fParticleGun;

    // class-member TLVs (safe to pass pointer or reference)
    TLorentzVector L_phot1_final;
    TLorentzVector L_phot2_final;

    // SIMC reading members
    bool useSIMC;                 
    TString simcFilePath;         
    TString simcTreeName;         
    TFile* simcFile;
    TTree* simcTree;
    Long64_t simcNEntries;
    Long64_t simcEntryIdx;

    // Branch variables (change to match your SIMC TTree)
    Float_t Pgamma1x; // momentum x (SIMC units)
    Float_t Pgamma1y;
    Float_t Pgamma1z;
    Float_t Egamma1;

    Float_t Pgamma2x;
    Float_t Pgamma2y;
    Float_t Pgamma2z;
    Float_t Egamma2;

    Float_t vtx_x; // vertex coords (SIMC units)
    Float_t vtx_y;
    Float_t vtx_z;

    // helper: transform vector from NPS frame -> hall frame
    TVector3 NpsToHall(const TVector3& v_nps) const;

    // disable copy
    PrimaryGeneratorAction(const PrimaryGeneratorAction&) = delete;
    PrimaryGeneratorAction& operator=(const PrimaryGeneratorAction&) = delete;
};

#endif // PrimaryGeneratorAction_h
