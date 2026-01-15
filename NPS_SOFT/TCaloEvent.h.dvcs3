//
// TCaloEvent.h, v1.0, Thu Dec  5 14:42:50
// Author: C. Munoz Camacho
//

#ifndef __TCaloEvent__
#define __TCaloEvent__


#ifndef __TCaloBlock__
#include "TCaloBlock.h"
#endif

#ifndef __TCaloBase__
#include "TCaloBase.h"
#endif

#ifndef __TCaloCluster__
#include "TCaloCluster.h"
#endif

#ifndef __TCaloTrigger__
#include "TCaloTrigger.h"
#endif

#ifndef __THCalo__
#include "THCalo.h"
#endif

#ifndef __TARSArray__
#include "TARSArray.h"
#endif

#ifndef ROOT_TClonesArray
#include "TClonesArray.h"
#endif

#ifndef ROOT_TObject
#include "TObject.h"
#endif

#ifndef ROOT_TCanvas
#include "TCanvas.h"
#endif

#ifndef ROOT_TRandom2
#include "TRandom2.h"
#endif

////////////////////////////////////////////////////////////////////////////////
//
// TCaloEvent.h
//
// DVCS calorimeter event class
// 
////////////////////////////////////////////////////////////////////////////////

class TCaloEvent : public TCaloBase
{

  private : 

  TCaloEvent(const TCaloEvent&);
  //virtual void Copy(TObject&);

  TClonesArray *fCluster;                     //->Event clusters
  TClonesArray *fCaloBlocks;                  //->Calorimeter blocks participating to the event
  TCaloTrigger* fCaloTrigger;                 //->Calorimeter trigger information
  Int_t fNbClusters;                          //Number of clusters in the event
  Int_t fNbBlocks; //Number of blocks in the event
  Int_t fNWave;
  Int_t fLogicType;
    Double_t fDTScalers[4];
  THCalo *fHCalo; //!
  //TARSArray *fARSArray; //->
  TClonesArray *fScalers;//->
  TClonesArray *fARSWaves; //->
  TClonesArray *fADC;//->
  TARSWave** fTestWaves;//!
  Float_t *fRefShapeMC;//!
  Double_t **fNoiseHisto;//!
  TRandom2 *fRan;//!
  Int_t fNoiseTime;//!
  Float_t fRefShapeInt;//!
  char *fScalerName;//!
  Int_t *fScalerNameLength;//!

  void GetMax(Float_t enei[8],Int_t nei[8], Int_t &virusbl ,Float_t &max);

  protected :
    
  static Bool_t           fgWarnings;          // Display warnings ?
  static Bool_t           fgErrors;            // Display errors ?

  static TClonesArray *fgCaloBlocks;
  static TClonesArray *fgCluster;
  static TCaloTrigger *fgCaloTrigger;
  static TClonesArray *fgARSWaves;
  static TClonesArray *fgADC;
  static TClonesArray *fgScalers;  
  static Int_t fgNNamedScalers;

  public :

  TCaloEvent(Int_t run=1);
  //TCaloEvent(const TCaloEvent&);
  virtual ~TCaloEvent();

  //virtual void Copy(TObject&);

  virtual void Print(char* opt="");

  TCaloBlock* AddBlock(Int_t nb);
  void AddBlock(TCaloBlock* block);
  TCaloCluster* AddCluster(void);
  TARSWave* AddWave(void);
  TARSWave* AddWave(Int_t size);
  TARSWave* AddWave(TARSWave* wave);
  THCalo* GetHCalo(void) { return fHCalo ; }
  void SetScaler(Int_t id, Int_t val);
  void SetScaler(char *name, Int_t val);
  Int_t GetScaler(Int_t id=0);
  Int_t GetScaler(char *name);
  void SetScalersNames(const char *names);
  void Clear(void);
  void Reset(void);

  void JitterSimulation(Float_t sigma, UInt_t seed1=65539, UInt_t seed2=34651);
  void TriggerSimulationReal(Double_t FourBlocksThreshold);
  void TriggerSim(Double_t FourBlocksThreshold);
  void TriggerSimulation(Int_t tmin, Int_t tmax, Float_t FourBlocksThreshold=1., Bool_t kFORCE=kFALSE, Float_t ClockFreq=0.05, UInt_t seed1=65539, UInt_t seed2=34651);  
  TClonesArray* GetBlocks(void) {return fCaloBlocks ; }
  TCaloBlock* GetBlock(Int_t n) {return (TCaloBlock*)fCaloBlocks->UncheckedAt(n) ; }
  Double_t SetADC(Int_t i, Double_t val);
  Double_t GetADC(Int_t n) {return((TDouble*)fADC->UncheckedAt(n))->GetValue();}  TClonesArray* GetClusters(void) {return fCluster ; }
  Int_t GetLogicType(void) { return fLogicType ; }
  Int_t GetNbBlocks(void) { return fNbBlocks ; }
  Int_t GetNbWaves(void) { return fNWave ; }
  Double_t GetDeadTime(int i);
  Float_t GetEnergy(void);
  Int_t GetNbClusters(void) { return fNbClusters ; }
  Int_t DoClustering(Double_t timemin=-1000, Double_t timemax=-1000, Float_t BlockThreshold=0.);
  Int_t DoClustering(Double_t timemin1, Double_t timemax1, Double_t timemin2, Double_t timemax2, Float_t BlockThreshold=0.);
  TCaloCluster* GetCluster(Int_t i) {
    TCaloCluster* cluster = (TCaloCluster*)fCluster->UncheckedAt(i);
    //TCaloCluster* cluster=(TCaloCluster*)(*fCluster)[i];
    return cluster;
  }
  TARSWave* GetWave(Int_t i) {
    TARSWave* wave = (TARSWave*)fARSWaves->UncheckedAt(i);
    return wave;
  }
 /*   TARSWave* GetARSWave(Int_t i) { */
/*      TARSWave* wave = (TARSWave*)fARSArray->GetWaves()->UncheckedAt(i); */
/*      return wave; */
/*    } */

  TClonesArray* GetWaves(void) { return fARSWaves ; }
  void SetWaves(TClonesArray* waves) { fARSWaves=waves ; }
  TCaloBlock* AnalyzeBlockFast(Int_t nblock, Int_t nmin=0, Int_t nmax=-1);
  void AnalyzeFast(Int_t nmin=0, Int_t nmax=-1);
  Int_t GetBlockPosition(Int_t nb);
  void SetTriggerValues(void);
  void SetCaloTrigger(TCaloTrigger* trig) {fCaloTrigger=trig ; }
  TCaloTrigger* GetCaloTrigger(void) {return fCaloTrigger ; }
  //  void SetARSArray (TARSArray *arsarray) {fARSArray=arsarray ; }
  //  TARSArray* GetARSArray(void) {return fARSArray;}
  void AddSimPulse(char* filename, Double_t energy, Int_t samples=128);
  void Display(TPad *display, Float_t HistMax=-1., Float_t BlockThreshold=0.);
  void SetWarnings(Bool_t val) { fgWarnings = val; }
  void SetErrors(Bool_t val) { fgErrors = val; }
  void InitRefShapeMC(char* filename, Int_t samples=128);
  void AddNoise(char* filename, UInt_t seed1=65539, UInt_t seed2=34651);
  void InitNoise(char* filenam, UInt_t seed1, UInt_t seed2);
  Int_t Decode(int * buf);
  Double_t GetDT(int i)
  {
    if (i<4)
      return fDTScalers[i];
    else
      return 0;
  }
  Int_t DecodeZS(int * buf);
  ClassDef(TCaloEvent,1) // DVCS Calorimeter Event Class

}; // End of TCaloEvent class definition

#endif










