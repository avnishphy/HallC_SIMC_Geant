//
// TCaloBase.cxx, v1.0, Thu Sep 12 11:13:57
// Author: F. Sabatie
//

#include <iostream>
#include <stdlib.h>
#include "TCaloBase.h"
#include "TCaloGeometry.h"
#include "TCaloParameters.h"
#include "TCaloCalibration.h"

//TCaloBase* gTCaloBase = 0;
using namespace std;

ClassImp(TCaloBase)

////////////////////////////////////////////////////////////////////////////////
//
// DVCS calorimeter base class
// 
////////////////////////////////////////////////////////////////////////////////

TCaloGeometry    TCaloBase::fgGeometry;
TCaloParameters  TCaloBase::fgParameters;
TCaloCalibration TCaloBase::fgCalibration;
Bool_t           TCaloBase::fgIsInit = kFALSE;
Bool_t           TCaloBase::fgGeometryIsInit = kFALSE;
Bool_t           TCaloBase::fgParametersIsInit = kFALSE;
Bool_t           TCaloBase::fgCalibrationIsInit = kFALSE;
Bool_t           TCaloBase::fgWarnings = kTRUE;
Bool_t           TCaloBase::fgErrors = kTRUE;

//_____________________________________________________________________________
TCaloBase::TCaloBase(Int_t run)
{
  fgGeometry.SetRun(run);
  // Default constructor
  //  gTCaloBase = this;
}

//_____________________________________________________________________________
 TCaloBase::TCaloBase(const TCaloBase& TCalobase)
{
  // Copy constructor
  ((TCaloBase&)TCalobase).Copy(*this);
}

//_____________________________________________________________________________
 void TCaloBase::Copy(TObject& obj)
{
  // Copy routine. Used by copy ctor.

  TObject::Copy(obj);

  fgParameters.Copy(((TCaloBase&)obj).fgParameters);
  ((TCaloBase&)obj).fgIsInit = fgIsInit;

}

//_____________________________________________________________________________
 TCaloBase::~TCaloBase()
{
  // Default destructor
}

//_____________________________________________________________________________
 void TCaloBase::Init(Int_t run)
{
  // Init the data members (only once)
  if (fgGeometryIsInit == kFALSE) InitGeometry(run);
  if (fgParametersIsInit == kFALSE) InitParameters();
  if (fgCalibrationIsInit == kFALSE) InitCalibration();
  fgIsInit = fgGeometryIsInit && fgParametersIsInit && fgCalibrationIsInit;
  if (fgIsInit == kFALSE) {
    if (fgErrors == kTRUE) {
      cout << "TCaloBase::Init failed"<<endl;
      cout << "GeometryIsInit="<<fgGeometryIsInit<<endl;
      cout << "ParametersIsInit="<<fgParametersIsInit<<endl;
      cout << "CalibrationIsInit="<<fgCalibrationIsInit<<endl;
      cout << "Aborting"<<endl;
    }
    exit(1);
  }
}

//____________________________________________________________________________
 void TCaloBase::InitGeometry(Int_t run)
{
  TString geomfile(getenv("NPS_SOFT"));
  geomfile+="/initdata/calogeom.txt";

  if (fgGeometryIsInit==kFALSE) {
    fgGeometry.Init(geomfile.Data());
    fgGeometryIsInit = kTRUE;
  }
}

//____________________________________________________________________________
 void TCaloBase::InitParameters(void)
{
  TString paramfile(getenv("NPS_SOFT"));
  paramfile+="/initdata/caloparam.txt";

  if (fgIsInit==kFALSE) {
    fgParameters.Init(paramfile.Data());
    fgParametersIsInit = kTRUE;
  }
}

//____________________________________________________________________________
 void TCaloBase::InitCalibration(void)
{

  TString calibfile(getenv("NPS_SOFT"));
  calibfile+="/initdata/calocalib.txt";

  if (fgCalibrationIsInit==kFALSE) {
    fgCalibration.Init(calibfile.Data());
    fgCalibrationIsInit = kTRUE;
  }
}

//_____________________________________________________________________________
 void TCaloBase::Print(const char* opt)
{
  // Output on screen

  fgGeometry.Print(opt);
  fgParameters.Print(opt);
  //  fgCalibration.Print(opt);
}
