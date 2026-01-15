//
// TInt.h, v1.0, Sat Jun  12 14:42:50
// Author: C. Munoz Camacho
//

#ifndef __TInt__
#define __TInt__

#ifndef ROOT_TObject
#include "TObject.h"
#endif


////////////////////////////////////////////////////////////////////////////////
//
// TInt.h
//
// Float Wrapper class
//
// 
////////////////////////////////////////////////////////////////////////////////

using namespace std;

class TInt : public TObject
{

  private :

  Int_t fValue;              

  public :

  TInt();
  TInt(Int_t val);
  TInt (const TInt&);
  //  void Clear(Option_t *option) {fValue=0.;}
  virtual ~TInt();

  void SetValue(Int_t val) { fValue = val ; }
  Int_t & GetValue(void) { return fValue ; }

  ClassDef(TInt,1) // Float Class

}; // End of TInt class definition

#endif






