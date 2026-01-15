//
// TCaloCalibration.h, v1.0, Thu Sep 12 11:13:57
// Author: F. Sabatie
//

#ifndef __TCaloCalibration__
#define __TCaloCalibration__

#include "TObject.h"
#include "TString.h"

////////////////////////////////////////////////////////////////////////////////
//
// TCalibration
//
// DVCS calorimeter calibration class
//
// Fills in calibration table
// 
////////////////////////////////////////////////////////////////////////////////

class TCaloCalibration : public TObject
{
  private:

  static Bool_t fgIsInit;          // Is Calibration initialized?

  protected:

  static Float_t** fECalXY;        // ARS Integral to Energy [X][Y]
  static Float_t*  fECalId;        // ARS Integral to Energy [Id]

  static TString   fConfig;        // Calibration file

  private:

  void Reset(void);

  public:

  TCaloCalibration();
  TCaloCalibration(char *);
  virtual ~TCaloCalibration();

  void Init(const char*);
  virtual void Print(char*);
  void InitDB(Int_t run);
  Float_t GetCalib(Int_t blocknb) { return fECalId[blocknb] ; }
  ClassDef(TCaloCalibration,1)  // DVCS Calorimeter Parameter Class

}; // End of TCaloCalibration class definition

#endif
