//
// TCaloGeometry.h, v1.0, Thu Sep 12 11:13:57
// Author: F. Sabatie
//
//
// Modified by A. Camsonne Dec 2 19;26
// added Calorimeter geometry

#ifndef __TCaloGeometry__
#define __TCaloGeometry__

#include "TObject.h"
#include "TString.h"

////////////////////////////////////////////////////////////////////////////////
//
// TGeometry
//
// DVCS calorimeter geometry class
//
// Contains information on geometry (amazing right!), like angle, distance
// from target, but also fills in the neighbour tables used in the clustering
// algorithm
// 
////////////////////////////////////////////////////////////////////////////////

class TCaloGeometry : public TObject
{
  private:

  static Bool_t fgIsInit;             // Is the Geometry initialized?

  protected:

  static Int_t    fNBlocks;           // Number of blocks
  static Int_t    fNX;                // Number of colums
  static Int_t    fNY;                // Number of rows

  static Int_t**  fBlockPosition;     // measured block position

  static Float_t* fBlockXPos;         // measured block X position
  static Float_t* fBlockYPos;         // measured block Y position
  static Float_t  fCenterXPos;        // measured center X position
  static Float_t  fCenterYPos;        // measured center Y position

  static Int_t*   fBlockX;            // X[Id]
  static Int_t*   fBlockY;            // Y[Id]
  static Int_t**  fBlockId;           // Block Id[X][Y]

  static Int_t*** fNeighboursTable;   // NeighbourId[X][Y][1...8]
  static Int_t**  fNeighbours;        // NeighbourId[Id][1...8]

  static TString  fConfig;            // Config file
  Int_t fRun;//!

  private:

  void FillNeighbourTables(void);
  void Reset(void);

  public:

  TCaloGeometry(Int_t run=0);
  TCaloGeometry(const char*);              // Constructor with data file
  virtual ~TCaloGeometry();

  void Init(const char*);                   // Read Geometry from file
  void InitPositions(const char*);   
  void InitPositionsDB(void);   
  void SetRun(Int_t run) {fRun=run;}
  const Int_t GetNX(void) { return fNX; }
  const Int_t GetNY(void) { return fNY; }
  const Int_t GetNBlocks(void) { return fNBlocks; }
  Int_t GetNeighbour(Int_t id, Int_t k) { return fNeighbours[id][k] ; }
  Float_t GetBlockXPos(Int_t id) { return fBlockXPos[id] ; }
  Float_t GetBlockYPos(Int_t id) { return fBlockYPos[id] ; }
  Float_t GetCenterXPos(void) { return fCenterXPos ; }
  Float_t GetCenterYPos(void) { return fCenterYPos ; }
  void SetCenterXPos(Float_t val) { fCenterXPos=val ; }
  void SetCenterYPos(Float_t val) { fCenterYPos=val ; }
  Int_t GetBlockX(Int_t block) { return fBlockX[block] ; }
  Int_t GetBlockY(Int_t block) { return fBlockY[block] ; }

  virtual void Print(const char*);

  ClassDef(TCaloGeometry,1)           // DVCS Calorimeter Geometry Class

}; // End of TCaloGeometry class definition

#endif





