//
// TARSArray.h, v1.0, Thu Dec  5 14:42:50
// Author: C. Munoz Camacho
//

#ifndef __TARSArray__
#define __TARSArray__

#ifndef __TARSWave__
#include "TARSWave.h"
#endif

#ifndef ROOT_TClonesArray
#include "TClonesArray.h"
#endif

#ifndef ROOT_TObject
#include "TObject.h"
#endif

////////////////////////////////////////////////////////////////////////////////
//
// TARSArray.h
//
// ARS Array class
// 
////////////////////////////////////////////////////////////////////////////////

class TARSArray : public TObject
{

  private : 

  TARSArray(const TARSArray&);
  //virtual void Copy(TObject&);

  TClonesArray *fWave;                     //->Waves
  Int_t fNbWaves;                          // Real number of waves
  Int_t fNwave;                            //! Number of waves (for testing)

  static TClonesArray *fgWave;

  protected :
    
  static Bool_t           fgWarnings;          // Display warnings ?
  static Bool_t           fgErrors;            // Display errors ?

  public :

  TARSArray(Int_t size=1);
  //TARSArray(const TARSArray&);
  virtual ~TARSArray();

  //virtual void Copy(TObject&);

  virtual void Print(const char* opt="");

  TARSWave* AddWave(void);
  TARSWave* AddWave(Int_t size);
  
  void Clear(void);
  void Reset(void);
  
  TClonesArray* GetWaves(void) {return fWave ; }
  Int_t GetNbWaves(void) { return fNbWaves ; }
  TARSWave* GetWave(Int_t i) {
    TARSWave* wave = (TARSWave*)fWave->UncheckedAt(i);
    return wave;
  }
  void SetWarnings(Bool_t val) { fgWarnings = val; }
  void SetErrors(Bool_t val) { fgErrors = val; }
  
  ClassDef(TARSArray,1) // ARS Array Class

}; // End of TARSArray class definition

#endif










