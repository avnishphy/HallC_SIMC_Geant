//
// TDVCSGeometry.h, v1.0, Thu Jan 17 11:13:57
// Author: C. Munoz Camacho
//

#ifndef __TDVCSGeometry__
#define __TDVCSGeometry__

#ifndef ROOT_TObject
#include "TObject.h"
#endif

#ifndef ROOT_TString
#include "TString.h"
#endif

#ifndef ROOT_TDVCSDB
#include "TDVCSDB.h"
#endif

////////////////////////////////////////////////////////////////////////////////
//
// TGeometry
//
// DVCS geometry class
//
////////////////////////////////////////////////////////////////////////////////

class TDVCSGeometry : public TObject
{
  private:

  static Bool_t fgIsInit;             // Is the Geometry initialized?
  void Reset(void);

  protected:

  static Float_t  fCaloDist;          // Calo distance from target center
  static Float_t  fCaloTheta;         // Calo angle with respect to Oz
  static Float_t  fCaloPitch;         // Calo Pitch in Hall A ref. frame
  static Float_t  fCaloRoll;         // Calo Roll in Hall A ref. frame
  static Float_t  fPATheta;           // Proton array angle with respect to Oz
  Int_t fRun;//!
  static TString  fConfig;            // Config file

  public:

  TDVCSGeometry();
  TDVCSGeometry(char *);              // Constructor with data file
  virtual ~TDVCSGeometry();

  void Init(const char*);                   // Read Geometry from file
  void InitDB(void);                   // Read Geometry from DB

  Float_t GetCaloDist(void) { return fCaloDist ; }
  Float_t GetCaloTheta(void) { return fCaloTheta ; }
  Float_t GetCaloPitch(void) { return fCaloPitch ; }
  Float_t GetCaloRoll(void) { return fCaloRoll ; }
  Float_t GetPATheta(void) { return fPATheta ; }
  void SetCaloDist(Float_t val) { fCaloDist=val ; }
  void SetCaloTheta(Float_t val) { fCaloTheta=val ; }
  void SetCaloRoll(Float_t val) { fCaloRoll=val ; }
  void SetCaloPitch(Float_t val) { fCaloPitch=val ; }
  void SetPATheta(Float_t val) { fPATheta=val ; }
  void SetRun(Int_t run) {fRun=run;}
  virtual void Print(const char*);

  ClassDef(TDVCSGeometry,1)           // DVCS Geometry Class

}; // End of TDVCSGeometry class definition

#endif





