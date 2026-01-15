//
// TCaloParameters.cxx, v1.0, Thu Sep 12 11:13:57
// Author: F. Sabatie
//

#include <iostream>
#include <fstream>
#include "TCaloParameters.h"

#ifndef __TDVCSDB__
#include "TDVCSDB.h"
#endif

using namespace std;

ClassImp(TCaloParameters)

////////////////////////////////////////////////////////////////////////////////
//
// DVCS calorimeter parameter class
// 
////////////////////////////////////////////////////////////////////////////////

Bool_t   TCaloParameters::fgIsInit = kFALSE;

Float_t  TCaloParameters::fClustWo;
Float_t  TCaloParameters::fClustEth;

TString  TCaloParameters::fConfig;

//____________________________________________________________________________
 TCaloParameters::TCaloParameters(void)
{
  // void constructor of TCaloParameters

  fClustWo  = 0.;
  fClustEth = 0.;

  fgIsInit  = kFALSE;
}

//____________________________________________________________________________
 TCaloParameters::TCaloParameters(const char* param)
{
  Init(param);
}

//____________________________________________________________________________
 void TCaloParameters::Reset(void)
{
  // Does nothing for the moment. Should de-allocate everything

  fgIsInit = kFALSE;
}

//____________________________________________________________________________
 void TCaloParameters::Init(const char* param)
{
  // 1. Read parameter data
  // 2. Init. all the tables
  // Nothing here yet

  if (fgIsInit==kFALSE) {
    fgIsInit=kTRUE;
    ifstream inifile(param);
    inifile>>fClustWo;
    inifile>>fClustEth;
  }
}

//____________________________________________________________________________
void TCaloParameters::InitDB(Int_t run)
{
  TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,"munoz","");
  TString name=("CALO_calib_W0");
  Float_t *coef=db->GetEntry_f(name.Data(),run);
  fClustWo=coef[0];
  delete coef;
  delete db;
}

//____________________________________________________________________________
 TCaloParameters::~TCaloParameters(void)
{
//  Reset();
}

//_____________________________________________________________________________
 void TCaloParameters::Print(const char* opt)
{
  // Simple printout method, should give more interesting information

  if (fgIsInit==kTRUE) {
    cout << "TCaloParameters initialized" << endl;
    cout << "ClustWo="<< fClustWo << "  ClustEth=" << fClustEth;
  } else {
    cout << "TCaloParameters NOT initialized" << endl;
  }
}




