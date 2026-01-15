//
// TCaloBase.h, v1.0, Thu Sep 12 11:13:57
// Author: F. Sabatie
//

#ifndef __TCaloBase__
#define __TCaloBase__

#include "TCaloGeometry.h"
#include "TCaloParameters.h"
#include "TCaloCalibration.h"
#include "TObject.h"

////////////////////////////////////////////////////////////////////////////////
//
// TCaloBase.h
//
// DVCS calorimeter base class
// 
////////////////////////////////////////////////////////////////////////////////

class TCaloBase : public TObject
{
  protected :

  static TCaloGeometry    fgGeometry;          // Calo geometry
  static TCaloParameters  fgParameters;        // Calo parameters
  static TCaloCalibration fgCalibration;       // Calo calibration
  static Bool_t           fgIsInit;            // Is TCaloBase initialized ?
  static Bool_t           fgGeometryIsInit;    // Is geometry initialized ?
  static Bool_t           fgParametersIsInit;  // Is parameters initialized ?
  static Bool_t           fgCalibrationIsInit; // Is calibration initialized ?
  static Bool_t           fgWarnings;          // Display warnings ?
  static Bool_t           fgErrors;            // Display errors ?
  
  public :

  TCaloBase(Int_t run=0);
  TCaloBase(const TCaloBase&);
  virtual ~TCaloBase();

  virtual void Copy(TObject&);
  virtual void Init(Int_t run=0);

  virtual void Print(const char* opt="");

  TCaloGeometry* GetGeometry(void) { return &fgGeometry ; }
  TCaloCalibration* GetCalibration(void) { return &fgCalibration ; }
  void InitGeometry(Int_t run);
  void InitParameters(void);
  void InitCalibration(void);

  void SetParameters(TCaloParameters* th) { th->Copy(fgParameters); }

  void SetWarnings(Bool_t val) { fgWarnings = val; }
  void SetErrors(Bool_t val) { fgErrors = val; }

  TCaloParameters* GetParameters(void) const { return &fgParameters; }

  ClassDef(TCaloBase,1) // DVCS Calorimeter Base Class

}; // End of TCaloBase class definition

// EXTERN TCaloBase* gTCaloBase;

#endif
