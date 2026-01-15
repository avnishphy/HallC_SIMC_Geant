//
// TDVCSEventMC.h, v1.0, Wed Jan 17 10:42:50
// Author: C. Munoz Camacho
//

#ifndef __TDVCSEventMC__
#define __TDVCSEventMC__

#ifndef ROOT_TObject
#include "TObject.h"
#endif

#ifndef ROOT_TVector3
#include "TVector3.h"
#endif

#ifndef ROOT_TLorentzVector
#include "TLorentzVector.h"
#endif

#ifndef ROOT_TClonesArray
#include "TClonesArray.h"
#endif


////////////////////////////////////////////////////////////////////////////////
//
// TDVCSEventMC.h
//
// DVCS Monte Carlo event class
// 
////////////////////////////////////////////////////////////////////////////////

class TDVCSEventMC : public TObject
{

  private : 

  TDVCSEventMC (const TDVCSEventMC&);
  // virtual void Copy(TObject&);

  TClonesArray *fElectron;                    //->Electrons 4-vectors
  TClonesArray *fPhoton;                      //->Photons 4-vectors
  TClonesArray *fProton;                      //->Protons 4-vectors

  TVector3    fVertex;                        //Event vertex
  Float_t     fSigmaP;                        //Sigma Plus
  Float_t     fSigmaM;                        //Sigma Minus
  Float_t     fPSF;                           //Phase Space Factor

  Int_t fNelectrons;                          //Number of electrons
  Int_t fNphotons;                            //Number of photons
  Int_t fNprotons;                            //Number of protons

  static TClonesArray* fgElectron;
  static TClonesArray* fgPhoton;
  static TClonesArray* fgProton;

  protected :
    
  static Bool_t           fgWarnings;          // Display warnings ?
  static Bool_t           fgErrors;            // Display errors ?

  public :

  TDVCSEventMC();
  virtual ~TDVCSEventMC();

  void SetVertex(TVector3 vertex) { fVertex=vertex ; }
  void SetVertex(Double_t vx, Double_t vy, Double_t vz) {
    fVertex.SetXYZ(vx,vy,vz) ;
  }
  TVector3 GetVertex(void) { return fVertex ; }
  void SetSigmaP(Float_t sigmap) { fSigmaP=sigmap ; }
  Float_t GetSigmaP (void) { return fSigmaP ; }
  void SetSigmaM(Float_t sigmam) { fSigmaM=sigmam ; }
  Float_t GetSigmaM (void) { return fSigmaM ; }
  void SetPSF(Float_t psf) { fPSF=psf ; }
  Float_t GetPSF (void) { return fPSF ; }
  Int_t GetNbPhotons(void) { return fNphotons ; }

  TLorentzVector* AddElectron(TVector3 *electron);
  TLorentzVector* AddPhoton(TVector3 *photon);
  TLorentzVector* AddProton(TVector3 *proton);

  TLorentzVector* GetElectron(Int_t Nel=0) {
    TLorentzVector* electron = (TLorentzVector*)fElectron->UncheckedAt(Nel);
    return electron;
  }
  TLorentzVector* GetPhoton(Int_t Nph=0) {
    TLorentzVector* photon = (TLorentzVector*)fPhoton->UncheckedAt(Nph);
    return photon;
  }
  TLorentzVector* GetProton(Int_t Npr=0) {
    TLorentzVector* proton = (TLorentzVector*)fProton->UncheckedAt(Npr);
    return proton;
  }

  void Clear(void);

  virtual void Print(char* opt="");

  void SetWarnings(Bool_t val) { fgWarnings = val; }
  void SetErrors(Bool_t val) { fgErrors = val; }

  ClassDef(TDVCSEventMC,1) // DVCS Monte Carlo Event Class

}; // End of TDVCSEventMC class definition

#endif










