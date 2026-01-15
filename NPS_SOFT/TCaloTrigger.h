//
// TCaloTrigger.h, v1.0, Thu Jan  30 14:42:50
// Author: C. Munoz Camacho
//

#ifndef __TCaloTrigger__
#define __TCaloTrigger__

#ifndef __TCaloBase__
#include "TCaloBase.h"
#endif

#ifndef __TFloat__
#include "TFloat.h"
#endif

#ifndef __TBool__
#include "TBool.h"
#endif

#ifndef __THCalo__
#include "THCalo.h"
#endif

#ifndef ROOT_TObject
#include "TObject.h"
#endif

#ifndef ROOT_TClonesArray
#include "TClonesArray.h"
#endif

#ifndef __triggermap__
#include "trigger/triggermap.h"
#endif

////////////////////////////////////////////////////////////////////////////////
//
// TCaloTrigger.h
//
// Calorimeter Trigger class
//
// 
////////////////////////////////////////////////////////////////////////////////

class TCaloTrigger : public TCaloBase
{

  private :

  TClonesArray* fADCValue;                      //->ADC Values from ARS's
  TClonesArray* fTowerBit;                      //->Tower bit
  static TClonesArray* fgADCValue;             //ADC Values from ARS's
  static TClonesArray* fgTowerBit;             //Tower bit
  //Eventually we could set Short_t here, but we need floats for testing

  TCaloTrigger (const TCaloTrigger&);  
  THCalo *fHCalo; //!
  
  

  protected :

  static Bool_t           fgIsInit;             //Initialized ?

  public :

  TCaloTrigger();
  // TCaloTrigger (const TCaloTrigger&);
  virtual ~TCaloTrigger();

  virtual void Copy(TObject&);

  virtual void Init(void);

  void Clear(char* opt="");
  void Display(TPad *display, Float_t HistMax=-1., Float_t BlockThreshold=0.,char *opt="coltext");
  THCalo* GetHCalo(void) {return fHCalo ; }
  Int_t Decode(int *);
  void SetADCValue(Int_t nb, Float_t val);
  void SetTowerBit(Int_t nb, Bool_t val);
  //void SetADCValue(Short_t val[fgGeometry.GetNBlocks()]);
  Float_t GetADCValue(Int_t nb);
  Bool_t GetTowerBit(Int_t nb);
  //  Bool_t SetTowerBit(Int_t nb);
  TClonesArray* GetADCValue(void) { return fADCValue ; } 

  virtual void Print(char* opt="");

  ClassDef(TCaloTrigger,1) // Calorimeter Trigger Class


}; // End of TCaloTrigger class definition

#endif






