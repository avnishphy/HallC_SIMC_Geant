//
// TFloat.h, v1.0, Thu Feb  2 14:42:50
// Author: C. Munoz Camacho
//

#ifndef __TFloat__
#define __TFloat__

#ifndef ROOT_TObject
#include "TObject.h"
#endif


////////////////////////////////////////////////////////////////////////////////
//
// TFloat.h
//
// Float Wrapper class
//
// 
////////////////////////////////////////////////////////////////////////////////

using namespace std;

class TFloat : public TObject
{

  private :

  Float_t fValue;              

  public :

  TFloat();
  TFloat(Float_t val);
  TFloat (const TFloat&);
  //  void Clear(Option_t *option) {fValue=0.;}
  virtual ~TFloat();

  void SetValue(Float_t val) { fValue = val ; }
  Float_t & GetValue(void) { return fValue ; }

  ClassDef(TFloat,1) // Float Class

}; // End of TFloat class definition

#endif






