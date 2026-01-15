//
// TCaloBlock.h, v1.0, Thu Dec  5 14:42:50
// Author: C. Muñoz Camacho
//

#ifndef __TCaloBlock__
#define __TCaloBlock__

#ifndef __TCaloBase__
#include "TCaloBase.h"
#endif

#ifndef __TFloatArray__
#include "TFloatArray.h"
#endif

#ifndef __TDouble__
#include "TDouble.h"
#endif

#ifndef ROOT_TObject
#include "TObject.h"
#endif

////////////////////////////////////////////////////////////////////////////////
//
// TCaloBlock.h
//
// DVCS calorimeter block class
// 
////////////////////////////////////////////////////////////////////////////////

class TCaloBlock : public TCaloBase
{
  
  private :
    //    Float_t fEnergy;
    Int_t fBlockNb;
    Int_t fNPulse; //Number of pulses
    TClonesArray *fEnergy; //-> Energies
    TClonesArray *fTime;  //-> Times
    TClonesArray *fChi2;  //-> Chi2
    Double_t fBase;  //Baseline
    //    TARSWave arswave;
    //    TCaloBlock(const TCaloBlock&);
    Bool_t fAnalyzed;

  public :

  TCaloBlock();
  TCaloBlock(const TCaloBlock&);
  virtual ~TCaloBlock();

  virtual void Copy(TObject&);

  //  void SetBlockEnergy(Float_t Blockenergy) { fEnergy=Blockenergy ; }
  void SetBlockEnergy(Float_t Blockenergy) { AddPulse(Blockenergy,0.); }
  void SetBlockNumber(Int_t blocknb) { fBlockNb=blocknb ; }
  Int_t GetBlockNumber(void) { return fBlockNb ; }
  Int_t GetPulseNumber(void) { return fNPulse ; }
  void AddPulse(Float_t energy, Float_t time);
  void SetChi2(Double_t chi2);
  void SetBaseline(Double_t base){fBase=base;}
  void Clear(Option_t* option);
  void Erase(Option_t* option);
  void Reset(void);
  Double_t GetBase(void){return fBase;}
  Float_t GetBlockEnergy(void) {
    if(fNPulse>0) {
      return ((TFloat*)fEnergy->UncheckedAt(0))->GetValue() ;
    }else{
      return 0.;
    } 
  }
  Float_t GetTime(Int_t i) {
    if(i<fNPulse) {
      return ((TFloat*)fTime->UncheckedAt(i))->GetValue() ;
    }else{
      return 0.;
    } 
  }
  Float_t GetEnergy(Int_t i) {
    if(i<fNPulse) {
      return ((TFloat*)fEnergy->UncheckedAt(i))->GetValue() ;
    }else{
      return 0.;
    }
  }
  Double_t GetChi2(Int_t i=0) {
      return ((TDouble*)fChi2->UncheckedAt(0))->GetValue() ;
  }

  Bool_t IsAnalyzed(void) { return fAnalyzed ; }
  virtual void Print(char* opt="");

  ClassDef(TCaloBlock,1) // DVCS Calorimeter Block Class

}; // End of TCaloBlock class definition

#endif






