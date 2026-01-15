//
// TDVCSBase.h, v1.0, Thu Jan 17 11:13:57
// Author: C. Munoz Camacho
//

#ifndef __TDVCSBase__
#define __TDVCSBase__

#ifndef __TDVCSGeometry__
#include "TDVCSGeometry.h"
#endif

#ifndef __TDVCSParameters__
#include "TDVCSParameters.h"
#endif

#ifndef ROOT_TObject
#include "TObject.h"
#endif


////////////////////////////////////////////////////////////////////////////////
//
// TDVCSBase.h
//
// DVCS base class
// 
////////////////////////////////////////////////////////////////////////////////

class TDVCSBase : public TObject
{
  protected :

  static TDVCSGeometry    fgGeometry;          // DVCS geometry
  static TDVCSParameters  fgParameters;        // DVCS parameters
  static Bool_t           fgIsInit;            // Is TDVCSBase initialized ?
  static Bool_t           fgGeometryIsInit;    // Is geometry initialized ?
  static Bool_t           fgParametersIsInit;  // Are parameters initialized ?

  static Bool_t           fgWarnings;          // Display warnings ?
  static Bool_t           fgErrors;            // Display errors ?

  public :

  TDVCSBase(Int_t run=0);
  TDVCSBase(const TDVCSBase&);
  virtual ~TDVCSBase();

  virtual void Copy(TObject&);
  virtual void Init(void);
  virtual void InitDB(void);

  virtual void Print(const char* opt="");

  void InitGeometry(void);
  void InitGeometryDB(void);
  void InitParameters(void);

  void SetParameters(TDVCSParameters* th) { th->Copy(fgParameters); }

  void SetWarnings(Bool_t val) { fgWarnings = val; }
  void SetErrors(Bool_t val) { fgErrors = val; }

  TDVCSParameters* GetParameters(void) const { return &fgParameters; }
  TDVCSGeometry* GetGeometry(void) const { return &fgGeometry; }

  ClassDef(TDVCSBase,1) // DVCS Base Class

}; // End of TDVCSBase class definition

// EXTERN TDVCSBase* gTDVCSBase;

#endif
