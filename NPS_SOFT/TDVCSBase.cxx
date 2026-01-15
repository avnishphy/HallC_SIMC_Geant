//
// TDVCSBase.cxx, v1.0, Thu Jan 17 11:13:57
// Author: C. Munoz Camacho
//

#include <iostream>
#include <stdlib.h>

#ifndef __TDVCSBase__
#include "TDVCSBase.h"
#endif
using namespace std;

//TDVCSBase* gTDVCSBase = 0;

ClassImp(TDVCSBase)

////////////////////////////////////////////////////////////////////////////////
//
// DVCS base class
// 
////////////////////////////////////////////////////////////////////////////////

TDVCSGeometry    TDVCSBase::fgGeometry;
TDVCSParameters  TDVCSBase::fgParameters;
Bool_t           TDVCSBase::fgIsInit = kFALSE;
Bool_t           TDVCSBase::fgGeometryIsInit = kFALSE;
Bool_t           TDVCSBase::fgParametersIsInit = kFALSE;
Bool_t           TDVCSBase::fgWarnings = kTRUE;
Bool_t           TDVCSBase::fgErrors = kTRUE;

//_____________________________________________________________________________
 TDVCSBase::TDVCSBase(Int_t run)
{
  // Default constructor
  //  gTDVCSBase = this;
  fgGeometry.SetRun(run);
}

//_____________________________________________________________________________
 TDVCSBase::TDVCSBase(const TDVCSBase& TDVCSbase)
{
  // Copy constructor
  ((TDVCSBase&)TDVCSbase).Copy(*this);
}

//_____________________________________________________________________________
 void TDVCSBase::Copy(TObject& obj)
{
  // Copy routine. Used by copy ctor.

  TObject::Copy(obj);

  fgParameters.Copy(((TDVCSBase&)obj).fgParameters);
  ((TDVCSBase&)obj).fgIsInit = fgIsInit;

}

//_____________________________________________________________________________
 TDVCSBase::~TDVCSBase()
{
  // Default destructor
}

//_____________________________________________________________________________
 void TDVCSBase::Init(void)
{
  // Init the data members (only once)
  if (fgGeometryIsInit == kFALSE) InitGeometry();
  if (fgParametersIsInit == kFALSE) InitParameters();
  fgIsInit = fgGeometryIsInit && fgParametersIsInit;
  if (fgIsInit == kFALSE) {
    if (fgErrors == kTRUE) {
      cout << "TDVCSBase::Init failed"<<endl;
      cout << "GeometryIsInit="<<fgGeometryIsInit<<endl;
      cout << "ParametersIsInit="<<fgParametersIsInit<<endl;
      cout << "Aborting"<<endl;
    }
    exit(1);
  }
}
//_____________________________________________________________________________
 void TDVCSBase::InitDB(void)
{
  // Init the data members (only once)
  if (fgGeometryIsInit == kFALSE) InitGeometryDB();
  if (fgParametersIsInit == kFALSE) InitParameters();
  fgIsInit = fgGeometryIsInit && fgParametersIsInit;
  if (fgIsInit == kFALSE) {
    if (fgErrors == kTRUE) {
      cout << "TDVCSBase::Init failed"<<endl;
      cout << "GeometryIsInit="<<fgGeometryIsInit<<endl;
      cout << "ParametersIsInit="<<fgParametersIsInit<<endl;
      cout << "Aborting"<<endl;
    }
    exit(1);
  }
}

//____________________________________________________________________________
 void TDVCSBase::InitGeometry(void)
{
  //Initializes DVCS geometry

  TString geomfile(getenv("NPS_SOFT"));
  geomfile+="/initdata/dvcsgeom.txt";

  if (fgGeometryIsInit==kFALSE) {
    fgGeometry.Init(geomfile.Data());
    fgGeometryIsInit = kTRUE;
  }
}

//____________________________________________________________________________
 void TDVCSBase::InitGeometryDB(void)
{
  //Initializes DVCS geometry

  if (fgGeometryIsInit==kFALSE) {
    fgGeometry.InitDB();
    fgGeometryIsInit = kTRUE;
 }
}
//____________________________________________________________________________
 void TDVCSBase::InitParameters(void)
{
  //Initializes DVCS parameters

  TString paramfile(getenv("NPS_SOFT"));
  paramfile+="/initdata/dvcsgeom.txt";

  if (fgIsInit==kFALSE) {
    fgParameters.Init(paramfile.Data());
    fgParametersIsInit = kTRUE;
  }
}

//_____________________________________________________________________________
 void TDVCSBase::Print(const char* opt)
{
  // Output on screen

  fgGeometry.Print(opt);
  fgParameters.Print(opt);
}
