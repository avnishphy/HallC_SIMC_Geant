//
// TCaloEventMC.cxx, v1.0, Wed Jan 16 10:42:50
// Author: C. Munoz Camacho
//

#include <iostream>

#ifndef __TDVCSEventMC__
#include "TDVCSEventMC.h"
#endif

using namespace std;

ClassImp(TDVCSEventMC)

////////////////////////////////////////////////////////////////////////////////
//
// DVCS Monte Carlo event class
//
// This class is to be used with simulated data. It allows to keep (and get)
// the relevant variables of the event at the vertex of interaction:  
// 4-vectors of generated particles, vertex position, cross-sections and phase
// phase space factor.
// 
////////////////////////////////////////////////////////////////////////////////

Bool_t           TDVCSEventMC::fgWarnings = kTRUE;
Bool_t           TDVCSEventMC::fgErrors = kTRUE;
TClonesArray*    TDVCSEventMC::fgElectron = 0;
TClonesArray*    TDVCSEventMC::fgPhoton = 0;
TClonesArray*    TDVCSEventMC::fgProton = 0;


//_____________________________________________________________________________
TDVCSEventMC::TDVCSEventMC()
{
  // Default constructor

  cout<<"TDVCS MC constructor"<<endl;
  
  if(!fgElectron) fgElectron = new TClonesArray ("TLorentzVector",1);
  if(!fgPhoton) fgPhoton = new TClonesArray ("TLorentzVector",1);
  if(!fgProton) fgProton = new TClonesArray ("TLorentzVector",1);

  fElectron=fgElectron;
  fPhoton=fgPhoton;
  fProton=fgProton;

  fVertex.SetXYZ(0.,0.,0.);
  fSigmaP=0.;
  fSigmaM=0.;
  fPSF=0.;

  fNelectrons = fNphotons = fNprotons = 0 ;

}

/*
//_____________________________________________________________________________
 TCaloEvent::TCaloEvent(const TCaloEvent& TCaloevent)
  // Copy constructor
{
  ((TCaloEvent&)TCaloevent).Copy(*this);
}

//_____________________________________________________________________________
 void TCaloEvent::Copy(TObject& obj)
{
  // Copy routine. Used by copy ctor.

  //  TObject::Copy(obj);

  //  fgParameters.Copy(((TCaloBase&)obj).fgParameters);
  //  ((TCaloBase&)obj).fgIsInit = fgIsInit;

}
*/
//_____________________________________________________________________________
 TDVCSEventMC::~TDVCSEventMC()
{
  // Default destructor

  cout<<"TDVCS MCdestructor"<<endl;
}

//_____________________________________________________________________________
 TLorentzVector* TDVCSEventMC::AddElectron(TVector3 *electron)
{
  // Adds an electron
  TClonesArray &electrons = *fElectron;
  TLorentzVector *el = new (electrons[fNelectrons++])
    TLorentzVector(electron->Px(),electron->Py(),electron->Pz(),electron->Mag());

  return el;
}

//_____________________________________________________________________________
 TLorentzVector* TDVCSEventMC::AddPhoton(TVector3 *photon)
{
  // Adds a photon
  TClonesArray &photons = *fPhoton;
  TLorentzVector *ph = new (photons[fNphotons++])
    TLorentzVector(photon->Px(),photon->Py(),photon->Pz(),photon->Mag());

  return ph;
}

//_____________________________________________________________________________
 TLorentzVector* TDVCSEventMC::AddProton(TVector3 *proton)
{
  // Adds a proton
  TClonesArray &protons = *fProton;
  TLorentzVector *pr = new (protons[fNprotons++])
    TLorentzVector(proton->Px(),proton->Py(),proton->Pz(),TMath::Sqrt(proton->Mag2()+TMath::Power(0.938271998,2)));

  return pr;
}

//_____________________________________________________________________________
 void TDVCSEventMC::Clear(void)
{

  fElectron->Clear("C"); fNelectrons = 0;
  fPhoton->Clear("C"); fNphotons = 0 ;
  fProton->Clear("C"); fNprotons = 0 ;
  
}

//_____________________________________________________________________________
 void TDVCSEventMC::Print(char* opt)
{
  // Output on screen
}













