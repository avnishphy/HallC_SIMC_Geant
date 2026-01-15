//
// TCaloCluster.h, v1.0, Thu Dec  5 14:42:50
// Author: C. Mu�oz Camacho
//

#ifndef __TCaloCluster__
#define __TCaloCluster__

#include "TCaloBase.h"
#include "TCaloBlock.h"
#include <iostream>

#ifndef ROOT_TCanvas
#include "TCanvas.h"
#endif

#ifndef ROOT_TLorentzVector
#include "TLorentzVector.h"
#endif

#ifndef ROOT_TClonesArray
#include "TClonesArray.h"
#endif

#ifndef ROOT_TRef
#include "TRef.h"
#endif

#ifndef __THCalo__
#include "THCalo.h"
#endif


////////////////////////////////////////////////////////////////////////////////
//
// TCaloCluster.h
//
// Calorimeter cluster class
// 
////////////////////////////////////////////////////////////////////////////////

class TCaloCluster : public TCaloBase
{

  private : 

  //TCaloCluster(const TCaloCluster&);
  //virtual void Copy(TObject&);

  TClonesArray* fClusBlock;                  //-> Array of TRef to blocks 
  Int_t fClusSize;                           // Number of blocks in the cluster
  Float_t fEnergy;                           // Cluster energy
  Float_t fX;                                // Photon X-position
  Float_t fY;                                // Photon Y-position

  Bool_t  fAnalyzed;                           //Is analyzed ?

  THCalo *fHCalo2; //!

  protected :
    
  static Bool_t           fgWarnings;          // Display warnings ?
  static Bool_t           fgErrors;            // Display errors ?

  public :

  TCaloCluster();
  //  TCaloCluster(const TCaloCluster&);
  virtual ~TCaloCluster();
  void Clear(Option_t *option);
  //  virtual void Copy(TObject&);

  virtual void Print(char* opt="");
  
  void AddBlock(TCaloBlock * block);

  
  Float_t GetEnergy(void);
  Float_t SetEnergy(Float_t energy) { fEnergy=energy ; }
  Int_t GetClusSize (void) {return fClusSize ; }
  void SetClusSize (Int_t size) { fClusSize = size ; }
  void Display(TCanvas *display, Float_t HistMax=-1., Float_t BlockThreshold=0.);
  TClonesArray* GetClusBlock (void) {return fClusBlock ; }
  TCaloBlock *GetBlock(Int_t i);

  void Analyze(Bool_t kFORCE=kFALSE, Float_t timemin=-1000, Float_t timemax=-1000, Float_t wei0=4.3, Float_t &wei_out=*(new Float_t));

  Float_t GetX(void) { return fX ; }
  Float_t GetY(void) { return fY ; }
  Float_t GetE(void) { return fEnergy ; }

  THCalo* GetHCalo(void) { return fHCalo2 ; }
  void SetAnalyzed(Bool_t val) { fAnalyzed = val; }
  void SetWarnings(Bool_t val) { fgWarnings = val; }
  void SetErrors(Bool_t val) { fgErrors = val; }
  
  ClassDef(TCaloCluster,1) // Calorimeter cluster class

}; // End of TCaloCluster class definition

#endif






