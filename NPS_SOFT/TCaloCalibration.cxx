//
// TCaloCalibration.cxx, v1.0, Thu Sep 12 11:13:57
// Author: F. Sabatie
//

#include <iostream>
#include <fstream>
#include "TCaloCalibration.h"
#include "TCaloGeometry.h"
#include "TDVCSDB.h"
using namespace std;

ClassImp(TCaloCalibration)

////////////////////////////////////////////////////////////////////////////////
//
// DVCS calorimeter calibration class
// 
////////////////////////////////////////////////////////////////////////////////

Bool_t    TCaloCalibration::fgIsInit = kFALSE;
Float_t** TCaloCalibration::fECalXY;            // ARS Integral to Energy [X][Y]
Float_t*  TCaloCalibration::fECalId;            // ARS Integral to Energy [Id]
TString   TCaloCalibration::fConfig;            // Config file

//____________________________________________________________________________
 TCaloCalibration::TCaloCalibration(void)
{
  // void constructor of TCaloCalibration

  fECalXY   = 0;
  fECalId   = 0;
  fgIsInit  = kFALSE;
}

//____________________________________________________________________________
 TCaloCalibration::TCaloCalibration(char* calib)
{
  Init(calib);
}

//____________________________________________________________________________
 void TCaloCalibration::Reset(void)
{
  // Does nothing for the moment. Should de-allocate everything

  fgIsInit = kFALSE;
}

//____________________________________________________________________________
 void TCaloCalibration::Init(const char* calib)
{
  // 1. Read calibration data
  // 2. Init. the tables
  // Nothing here yet

  TCaloGeometry *geom = new TCaloGeometry();
  fECalXY = new Float_t * [geom->GetNX()];
  for (int i=0;i< geom->GetNX();i++)
    fECalXY[i] = new Float_t[geom->GetNY()];
  fECalId = new Float_t [geom->GetNBlocks()];
 
  if (fgIsInit==kFALSE) {
    fgIsInit=kTRUE;
    ifstream inifile(calib);
    for(Int_t ix=0;ix<geom->GetNX();ix++){
      for(Int_t iy=0;iy<geom->GetNY();iy++){
	Float_t calcoef;
	inifile>>calcoef;
	fECalXY[ix][iy]=calcoef;
	fECalId[(geom->GetNX())*iy+ix]=calcoef;
      }
    }
  }
  delete geom; fgIsInit  = kTRUE;
}


//____________________________________________________________________________
 void TCaloCalibration::InitDB(Int_t run)
{
  //Init from DB

  TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,"munoz","");

  TCaloGeometry *geom = new TCaloGeometry();
  Float_t *coef=db->GetEntry_f("CALO_calib_ARSWaveCalib",run);
  for(Int_t i=0;i<geom->GetNBlocks();i++) fECalId[i] = coef[i];
  
  delete coef;
  delete db;
  delete geom;
}

//____________________________________________________________________________
 TCaloCalibration::~TCaloCalibration(void)
{
  TCaloGeometry *geom = new TCaloGeometry();

  for (int i=0;i< geom->GetNX();i++)
    delete fECalXY[i];
  delete fECalXY;
  delete fECalId;
  delete geom;
}

//_____________________________________________________________________________
 void TCaloCalibration::Print(char* opt)
{
  // Simple printout method, should give more interesting information
  
  TCaloGeometry *geom = new TCaloGeometry();

  if (fgIsInit==kTRUE) {
    cout << "TCaloCalibration initialized" << endl;
    cout << "Calibration coefficients : "<<endl;
    for(Int_t i=0;i<geom->GetNBlocks();i++){
      cout<<fECalId[i]<<" ";
    }
    cout<<endl;
  } else {
    cout << "TCaloCalibration NOT initialized" << endl;
  }
  delete geom;
}





