//
// TDVCSGeometry.cxx, v1.0, Thu Jan 17 11:13:57
// Author: C. Munoz Camacho
//

#include <iostream>
#include <fstream>
#include "TDVCSGeometry.h"
using namespace std;

ClassImp(TDVCSGeometry)

////////////////////////////////////////////////////////////////////////////////
//
// DVCS geometry class
//
// It contains information about the position of detectors in space:
// distances, angles...
// 
////////////////////////////////////////////////////////////////////////////////

Bool_t   TDVCSGeometry::fgIsInit = kFALSE;
Float_t  TDVCSGeometry::fCaloDist;          // Calo distance from target center
Float_t  TDVCSGeometry::fCaloTheta;         // Calo angle with respect to Oz
Float_t  TDVCSGeometry::fCaloPitch;         // Calo Pitch in Hall A ref. frame
Float_t  TDVCSGeometry::fCaloRoll;         // Calo Roll in Hall A ref. frame
Float_t  TDVCSGeometry::fPATheta;  
TString  TDVCSGeometry::fConfig;            // Config file

//____________________________________________________________________________
 TDVCSGeometry::TDVCSGeometry(void)
{
  // void constructor of TDVCSGeometry
  if (!fgIsInit) {
    fCaloDist        = 0.;
    fCaloTheta       = 0.;
  }
}

//____________________________________________________________________________
 TDVCSGeometry::TDVCSGeometry(char* geom)
{
  Init(geom);
}

//____________________________________________________________________________
 void TDVCSGeometry::Reset(void)
{
  // Does nothing for the moment. Should de-allocate everything

  fgIsInit = kFALSE;
}

//____________________________________________________________________________
 void TDVCSGeometry::InitDB(void)
{
  //Initiatizes geometry

  //  if (fgIsInit==kFALSE) 
{
   TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,"munoz","");
   TString name=("CALO_geom_Yaw");
   Float_t *coef=db->GetEntry_f(name.Data(),fRun);
   //20190419(start)
   //calorimeter is on the left  side of the beam-direction in Hall C
   //calorimeter is on the right side of the beam-direction in Hall A
   //This code was made for Hall A.
   //It is the easiest way to switch the calorimeter's position.
   // fCaloTheta=coef[0];//For Hall A
   // fPATheta=coef[0];//For Hall A
   fCaloTheta = -1.*coef[0];//For Hall C
   fPATheta = -1.*coef[0];//For Hall C
   //20190419(finish)
   delete coef;
   TString name2=("CALO_geom_Roll");
   coef=db->GetEntry_f(name2.Data(),fRun);
   fCaloRoll=coef[0];
   delete coef;
   TString name3=("CALO_geom_Pitch");
   coef=db->GetEntry_f(name3.Data(),fRun);
   fCaloPitch=coef[0];
   delete coef;
   TString name4=("CALO_geom_Dist");
   coef=db->GetEntry_f(name4.Data(),fRun);
   fCaloDist=coef[0];
   delete coef;
   fgIsInit=kTRUE;
   delete db;

  }
}

//____________________________________________________________________________
 void TDVCSGeometry::Init(const char* geom)
{
  //Initiatizes geometry

  if (fgIsInit==kFALSE) {
    ifstream inifile(geom);
    inifile>>fCaloDist;
    inifile>>fCaloTheta;
    inifile>>fPATheta;
    fgIsInit=kTRUE;
  }
}

//____________________________________________________________________________
 TDVCSGeometry::~TDVCSGeometry(void)
{
  //Default destructor

//  Reset();
}

//_____________________________________________________________________________
 void TDVCSGeometry::Print(const char* opt)
{
  // Simple printout method, should give more interesting information

  if (fgIsInit==kTRUE) {
    cout << "TDVCSGeometry initialized" << endl;
    cout << "Calo distance=" << fCaloDist;
    cout << "  Calo theta=" << fCaloTheta<<endl;
  } else {
    cout << "TCaloGeometry NOT initialized" << endl;
  }
}




















