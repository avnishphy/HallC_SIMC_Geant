//
// THRS.h, v1.0, Thu Feb  2 14:42:50
// Author: C. Munoz Camacho

#ifndef __THRS__
#define __THRS__

#ifndef ROOT_TObject
#include "TObject.h"
#endif

#ifndef ROOT_TLorentzVector
#include "TLorentzVector.h"
#endif


////////////////////////////////////////////////////////////////////////////////
//
// THRS.h
//
// Double Wrapper class
//
// 
////////////////////////////////////////////////////////////////////////////////

using namespace std;

class THRS : public TObject
{

  private :

  TLorentzVector *fScattered; //->Scattered particle (non corrected);
  TLorentzVector *fScattered_c; //->Scattered particle (corrected);
  Double_t fP;
  Double_t fTheta;
  Double_t fPhi;

  public :

  THRS();// ctor
  virtual ~THRS();// dtor
  TLorentzVector *GetParticle(void) { return fScattered ; }
  TLorentzVector *GetParticleCorrected(void) { return fScattered_c ; }
  void SetParticle(TLorentzVector *e) { fScattered=e ; }
  void SetParticleCorrected(TLorentzVector *e) { fScattered_c=e ; }
  Double_t GetTheta(void) {return fTheta;}
  Double_t GetPhi(void) {return fPhi;}
  Double_t GetP(void) {return fP;}
  void SetTheta(Double_t *val) {fTheta=(*val);}
  void SetPhi(Double_t *val) {fPhi=(*val);}
  void SetP(Double_t *val) {fP=(*val);}
  void Clear();
  ClassDef(THRS,1) // Double Class

}; // End of THRS class definition

#endif






