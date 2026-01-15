//
// TDVCSParameters.cxx, v1.0, Thu Jan 17 11:13:57
// Author: C. Munoz Camacho
//

#include <iostream>
#include <fstream>

#ifndef __TDVCSParameters__
#include "TDVCSParameters.h"
#endif

#ifndef __TDVCSDB__
#include "TDVCSDB.h"
#endif

using namespace std;

ClassImp(TDVCSParameters)

////////////////////////////////////////////////////////////////////////////////
//
// DVCS parameter class
//
// Contains information on parameters for the clustering algorithm, etc.
// 
////////////////////////////////////////////////////////////////////////////////

Bool_t   TDVCSParameters::fgIsInit = kFALSE;
Float_t  TDVCSParameters::fClusA;
Float_t  TDVCSParameters::fClusB;
TString  TDVCSParameters::fConfig;

//____________________________________________________________________________
 TDVCSParameters::TDVCSParameters(void)
{
  // void constructor of TDVCSParameters

  fClusA   = 0.;
  fClusB   = 0.;

  fgIsInit  = kFALSE;
}

//____________________________________________________________________________
 TDVCSParameters::TDVCSParameters(char* param)
{
  Init(param);
}

//____________________________________________________________________________
 void TDVCSParameters::Reset(void)
{
  // Does nothing for the moment. Should de-allocate everything

  fgIsInit = kFALSE;
}

//____________________________________________________________________________
 void TDVCSParameters::Init(const char* param)
{
  if (fgIsInit==kFALSE) {
    fgIsInit=kTRUE;
    ifstream inifile(param);
    inifile>>fClusA;
    inifile>>fClusB;
  }
}

//____________________________________________________________________________
void TDVCSParameters::InitDB(Int_t run)
{
  TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,"munoz","");
  TString name=("CALO_calib_ClusA");
  Float_t *coef=db->GetEntry_f(name.Data(),run);
  fClusA=coef[0];
  delete coef;
  TString name2=("CALO_calib_ClusB");
  coef=db->GetEntry_f(name2.Data(),run);
  delete coef;
  fgIsInit=kTRUE;
  delete db;

}

//____________________________________________________________________________
 TDVCSParameters::~TDVCSParameters(void)
{
//  Reset();
}

//_____________________________________________________________________________
 void TDVCSParameters::Print(const char* opt)
{
  // Simple printout method, should give more interesting information

  if (fgIsInit==kTRUE) {
    cout << "TDVCSParameters initialized" << endl;
    cout << "  A=" << fClusA <<"  B=" << fClusB << endl;
  } else {
    cout << "TDVCSParameters NOT initialized" << endl;
  }
}
