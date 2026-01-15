//
// TShort.h, v1.0, Thu Feb  2 14:42:50
// Author: C. Munoz Camacho
// Modified by A.Camsonne March 24th 2003 

#ifndef __TShort__
#define __TShort__

#ifndef ROOT_TObject
#include "TObject.h"
#endif


////////////////////////////////////////////////////////////////////////////////
//
// TShort.h
//
// Short Wrapper class
//
// 
////////////////////////////////////////////////////////////////////////////////

using namespace std;

class TShort : public TObject
{

  private :

  Short_t fValue;                  // Value              
  
  public :
    
  TShort();
  TShort(Short_t val);
  TShort (const TShort&);
  void Clear(void);
  virtual ~TShort();
  void SetValue(Short_t val) { fValue = val ; }
  Short_t & GetValue(void) { return fValue ; }

  ClassDef(TShort,1) // Short Class

}; // End of TShort class definition

#endif






