//
// TDVCSEvent.h, v1.0, Wed Jan  8 10:42:50
// Author: C. Munoz Camacho
//

#ifndef __TDVCSEvent__
#define __TDVCSEvent__

#ifndef ROOT_TObject
#include "TObject.h"
#endif

#ifndef ROOT_TVector3
#include "TVector3.h"
#endif

#ifndef __TDVCSBase__
#include "TDVCSBase.h"
#endif

#ifndef __TCaloEvent__
#include "TCaloEvent.h"
#endif

////////////////////////////////////////////////////////////////////////////////
//
// TDVCSEvent.h
//
// DVCS event class
// 
////////////////////////////////////////////////////////////////////////////////

class TDVCSEvent : public TDVCSBase
{

  private : 

  TDVCSEvent(const TDVCSEvent&);
  // virtual void Copy(TObject&);

  TCaloEvent   *fCaloEvent;                  //->Calorimeter event

  TVector3      fVertex;                     //Event vertex

  TLorentzVector fElectron;                  //This is temporary, waiting for TSpectro...

  static TCaloEvent    *fgCaloEvent;        

  //R-function tables
  double rline[13][1362][7];  //! Keeping FORTRAN numbering (starting at 1)
  double tmin[1362];//!
  double tmax[1362];//!
  double phimin[1362];//!
  double phimax[1362];//!
  double dy,dd;//!
  int narray;//!=1361; // We use the actual number of points in grids
  void init_rfunc(TString col);
  int getindex(double y, double d);
  
  

  protected :
    
  static Bool_t           fgWarnings;          // Display warnings ?
  static Bool_t           fgErrors;            // Display errors ?

  public :

  TDVCSEvent(Int_t run=1, TString col="no-collimator");
  virtual ~TDVCSEvent();

  void SetVertex(TVector3 vertex) { 
    if(TMath::Abs(vertex.Px())>100.||TMath::Abs(vertex.Py())>100.||TMath::Abs(vertex.Pz())>100.)
      cout<<"Warning : vertex value(s) look(s) too big. Please check!"<<endl;
    fVertex=vertex ; 
  }
  void SetVertex(Double_t vx, Double_t vy, Double_t vz, Bool_t quiet=kFALSE) {
    if(TMath::Abs(vx)>100.||TMath::Abs(vy)>100.||TMath::Abs(vz)>100.)
      if(!quiet) cout<<"Warning : vertex value(s) look(s) too big. Please check!"<<endl;
    fVertex.SetXYZ(vx,vy,vz) ;
  }
  TVector3 GetVertex(void) { return fVertex ; }
  
  TCaloEvent* GetCaloEvent(void) { return fCaloEvent ; }
  void SetCaloEvent(TCaloEvent *caloevent) {fCaloEvent=caloevent ;}
  virtual void Print(const char*  opt="");

  Bool_t ThereIsAProton(void); 

  TLorentzVector GetPhoton(Int_t clus=0, Float_t a=7., Float_t b=0., Float_t &a_out =*(new Float_t), Float_t &x_corr =*(new Float_t), Float_t &y_corr =*(new Float_t));

  TLorentzVector GetPhotonDirect(Int_t clus=0, Float_t a=7., Float_t b=0., Float_t &a_out =*(new Float_t), Float_t &x_corr =*(new Float_t), Float_t &y_corr =*(new Float_t));

  TVector3 GetProtonDirFast(void);

  TLorentzVector GetElectron(void) { return fElectron ; }
  void SetElectron (TLorentzVector electron) { fElectron=electron ; }

  void Clear(void);
  void Reset(void);

  void SetWarnings(Bool_t val) { fgWarnings = val; }
  void SetErrors(Bool_t val) { fgErrors = val; }
  
  Double_t rfunction(double y,double d,double theta,double phi);

  ClassDef(TDVCSEvent,1) // DVCS Event Class

}; // End of TDVCSEvent class definition

#endif










