//
// TDouble.h, v1.0, Thu Feb  2 14:42:50
// Author: C. Munoz Camacho
// Modified by A.Camsonne March 24th 2003 

#ifndef __TDouble__
#define __TDouble__

#ifndef ROOT_TObject
#include "TObject.h"
#endif


////////////////////////////////////////////////////////////////////////////////
//
// TDouble.h
//
// Double Wrapper class
//
// 
////////////////////////////////////////////////////////////////////////////////

using namespace std;

class TDouble : public TObject
{

  private :

  Double_t fValue;// Data member : value              

  public :

  TDouble();// ctor
  TDouble(Double_t val);// ctor initialized to val
  TDouble (const TDouble&);// copy ctor
  virtual ~TDouble();// dtor
  TDouble & operator = (const TDouble& copy ){fValue = copy.fValue; return *this;};
  TDouble & operator = (Double_t v){fValue = v; return *this;};
  void SetValue(Double_t val) { fValue = val ; }
  Double_t & GetValue(void) { return fValue ; }
  void Clear();
  ClassDef(TDouble,1) // Double Class

}; // End of TDouble class definition

#endif






