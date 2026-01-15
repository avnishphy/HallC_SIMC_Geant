//
// TCaloGeometry.cxx, v1.0, Thu Sep 12 11:13:57
// Author: F. Sabatie
//

#include <iostream>
#include <fstream>
#include "TCaloGeometry.h"
#include "TDVCSDB.h"
using namespace std;

ClassImp(TCaloGeometry)

////////////////////////////////////////////////////////////////////////////////
//
// DVCS calorimeter geometry class
// 
////////////////////////////////////////////////////////////////////////////////

Bool_t   TCaloGeometry::fgIsInit = kFALSE;
Int_t    TCaloGeometry::fNBlocks;           // Number of blocks
Int_t    TCaloGeometry::fNX;                // Number of colums
Int_t    TCaloGeometry::fNY;                // Number of rows
Int_t*   TCaloGeometry::fBlockX;            // X(Block Id)
Int_t*   TCaloGeometry::fBlockY;            // Y(Block Id)
Int_t**  TCaloGeometry::fBlockId;           // Block Id(X,Y)
Float_t* TCaloGeometry::fBlockXPos;         // measured block X position
Float_t* TCaloGeometry::fBlockYPos;         // measured block Y position
Float_t  TCaloGeometry::fCenterXPos;        // measured center X position
Float_t  TCaloGeometry::fCenterYPos;        // measured center Y position
Int_t*** TCaloGeometry::fNeighboursTable;   // NeighbourId[X][Y][1...8]
Int_t**  TCaloGeometry::fNeighbours;        // NeighbourId[Id][1...8]
TString  TCaloGeometry::fConfig;            // Config file

//____________________________________________________________________________
 TCaloGeometry::TCaloGeometry(Int_t run)
{
  // void constructor of TCaloGeometry
  if (!fgIsInit) {
    fNBlocks         = 0;
    fNX              = 0;
    fNY              = 0;
    fNeighboursTable = 0;
    fNeighbours      = 0;
    fRun=run;
  }
}

//____________________________________________________________________________
 TCaloGeometry::TCaloGeometry(const char* geom)
{
  fRun=0;
  Init(geom);
}

//____________________________________________________________________________
 void TCaloGeometry::Reset(void)
{
  // Does nothing for the moment. Should de-allocate everything

  fgIsInit = kFALSE;
}

//____________________________________________________________________________
 void TCaloGeometry::InitPositions(const char* geom)
{
    ifstream inifile(geom);
    inifile>>fNBlocks;
    inifile>>fNX;
    inifile>>fNY;

    fBlockXPos = new Float_t[fNX*fNY];            // X(Block Id)
    fBlockYPos = new Float_t[fNX*fNY];            // Y(Block Id)
    //    for(Int_t iy=0;iy<fNY;iy++){
    for(Int_t ix=0;ix<fNX;ix++){
      for(Int_t iy=0;iy<fNY;iy++){
	inifile>>fBlockXPos[ix*fNY+iy]; //measured X-position of blocks
  	inifile>>fBlockYPos[ix*fNY+iy]; //measured Y-position of blocks
      }
    }
    inifile>>fCenterXPos;
    inifile>>fCenterYPos;
}

//____________________________________________________________________________
 void TCaloGeometry::InitPositionsDB()
{
   TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,"munoz","");
   TString name=("CALO_geom_X");
   fBlockXPos=new Float_t[1156];         
   fBlockYPos=new Float_t[1156];
   fBlockXPos=db->GetEntry_f(name.Data(),fRun);
   TString name2=("CALO_geom_Y");
   fBlockYPos=db->GetEntry_f(name2.Data(),fRun);
   TString name3=("CALO_geom_X0");
   Float_t* coef=db->GetEntry_f(name3.Data(),fRun);
   fCenterXPos=coef[0];
   delete coef;
   TString name4=("CALO_geom_Y0");
   coef=db->GetEntry_f(name4.Data(),fRun);
   fCenterYPos=coef[0];
   delete coef;
   TString name5=("CALO_geom_NCol");
   coef=db->GetEntry_f(name5.Data(),fRun);
   fNX=coef[0];
   delete coef;
   TString name6=("CALO_geom_NRow");
   coef=db->GetEntry_f(name6.Data(),fRun);
   fNY=coef[0];
   delete coef;
   fNBlocks=fNX*fNY;
   delete db;
}

//____________________________________________________________________________
 void TCaloGeometry::Init(const char* geom)
{
  // 1. Read geometry data
  // 2. Init. all the tables

  if (fgIsInit==kFALSE) {
 
    //    InitPositions(geom);
    InitPositionsDB();

  fBlockX = new Int_t[fNX*fNY];            // X(Block Id)
  fBlockY = new Int_t[fNX*fNY];           // Y(Block Id)
  fBlockId = new Int_t * [fNX];        // Block Id(X,Y)
     
  for (int i = 0;i<fNX;i++)
    fBlockId[i] = new Int_t [fNY];
  TCaloGeometry::fNeighboursTable = new Int_t **[fNX];   // NeighbourId[X][Y][1...8]
  for (int i = 0;i<fNX;i++)
    {
      fNeighboursTable[i] = new Int_t *[fNY];
      for (int j=0;j<fNY;j++)
	fNeighboursTable[i][j] = new Int_t [8];
    }
  fNeighbours = new Int_t * [fNBlocks];        // NeighbourId[Id][1...8]
  for (int i = 0;i<fNBlocks;i++)
    fNeighbours[i] = new Int_t [8];

    // Initialize fBlockX,fBlockY,fBlockId
  for (int col=0;col<fNX;col++)
    {
      for (int row=0;row<fNY;row++)
	{
	  fBlockX[row+col*fNY]=col;
	  fBlockY[row+col*fNY]=row;
	  fBlockId[col][row]=row+col*fNY;
	}
    }
  FillNeighbourTables();
  fgIsInit=kTRUE;
  }
  
}

//____________________________________________________________________________
 TCaloGeometry::~TCaloGeometry(void)
{
//  Reset();
}

//____________________________________________________________________________
 void TCaloGeometry::FillNeighbourTables(void)
{
  // Neighbours numbering
  //012
  //3 4
  //567
  Int_t i,j;
  for (int row=0;row<fNY;row++){
    for (int col=0;col<fNX;col++){
      for (int neighbour=0;neighbour<9;neighbour++){
	i=neighbour%3;
	j=neighbour/3;
	if (neighbour<4){
	  fNeighboursTable[col][row][neighbour]=(col+i-1<0||col+i>fNX||row-j+1<0||row-j+2>fNY)?-1:fBlockId[col-1+i][row+1-j];
	  fNeighbours[col*fNY+row][neighbour]=fNeighboursTable[col][row][neighbour];
	}
	if (neighbour>4){
	  fNeighboursTable[col][row][neighbour-1]=(col+i-1<0||col+i>fNX||row-j+1<0||row-j+2>fNY)?-1:fBlockId[col-1+i][row+1-j];
	  fNeighbours[col*fNY+row][neighbour-1]=fNeighboursTable[col][row][neighbour-1];
	}
      }	
    }
  }
}

//_____________________________________________________________________________
 void TCaloGeometry::Print(const char* opt)
{
  // Simple printout method, should give more interesting information

  if (fgIsInit==kTRUE) {
    cout << "TCaloGeometry initialized" << endl;
    cout << "Number of blocks=" << fNBlocks;
    cout << "  Number of colums=" << fNX;
    cout << "  Number of rows=" << fNY<<endl;
    //    for(Int_t iy=0;iy<fNY;iy++){
    for(Int_t ix=0;ix<fNX;ix++){
      for(Int_t iy=0;iy<fNY;iy++){
	cout<<"Block number="<<iy+fNY*ix<<"  X="<<fBlockXPos[iy+fNY*ix]<<"  Y="<<fBlockYPos[iy+fNY*ix]<<endl;
      }
    }
    
    
  } else {
    cout << "TCaloGeometry NOT initialized" << endl;
  }
}




















