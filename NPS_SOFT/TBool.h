//
// TBool.h, v1.0, Thu Feb  2 14:42:50
// Author: C. Munoz Camacho
//

#ifndef __TBool__
#define __TBool__

#ifndef ROOT_TObject
#include "TObject.h"
#endif


////////////////////////////////////////////////////////////////////////////////
//
// TBool.h
//
// Float Wrapper class
//
// 
////////////////////////////////////////////////////////////////////////////////

using namespace std;

class TBool : public TObject
{

  private :

  Float_t fValue;              

  public :

  TBool();
  TBool(Bool_t val);
  TBool (const TBool&);
  //  void Clear(Option_t *option) {fValue=0.;}
  virtual ~TBool();

  void SetValue(Float_t val) { fValue = val ; }
  Float_t & GetValue(void) { return fValue ; }

  ClassDef(TBool,1) // Float Class

}; // End of TBool class definition

#endif






