
#include "TCaloEvent.h"
#include "TDVCSEvent.h"
#include "TARSWave.h"
#include "TChain.h"
#include "TTree.h"
#include "TFile.h"
#include "TKey.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "THaRun.h"
#include "/work/hallc/nps/hosan/analyzer-1.5.22/src/THaEvent.h"

class TDVCSGlobal {

 public:
  TDVCSGlobal(int v);

  void Print();
  Int_t GetTree(const char*  treename="all");
  //20190403(start)
  //temporarily commented out
  /* Int_t GetRun(const char*  filename); */
  //20190403(finish)
  TARSWave* GetWave(void) {return wave;}
  Bool_t RunChange(const char*  filename);
  void UpdateCalo(void);
  void UpdatePA(void);
  void UpdateVeto(void);
  void UpdateDVCS(void);
  void UpdatePedestals(void);
  void UpdateWFAna(void);
  void Update(const char*  filename);
  void UpdateTimeCor(void);
  //20190403(start)
  //temporarily commented out because when using in geant4, it gives error
  /* void UpdateTimeCor_DVCS2(void); */
  /* void UpdateTimeCor_DVCS3(void); */
  //20190403(finish)
  void Init(void);
  void SetWF(Bool_t val) {kWF=val;}
  void SetHRSCor(Bool_t val) {kHRSCor=val;}
  Bool_t TimeCorIsInit(void) { return fgTimeCorInit; }
  void SetTimeCor(Bool_t val=kFALSE) { fgNoTimeCor=val;}
  Double_t GetTimeCor(void);
  Double_t GetTimeCor2(Int_t block, Bool_t quiet=kFALSE);
  Double_t GetTimeCor3(Int_t block, Bool_t quiet=kFALSE);
  Double_t GetARSCor(Int_t blocknb) { return fgcor1[blocknb] ; }
  Double_t GetARSCorPA(Int_t blocknb) { return fgcor1pa[blocknb] ; }
  Double_t GetARSCorVETO(Int_t blocknb) { return fgcor1veto[blocknb] ; }
  void SetAnalysisWindow(Int_t min,Int_t max) { minanawin=min;maxanawin=max;}
  void SetRun(Int_t n) {run=n;}
  void ForceUpdate(void);
  void GetStatusCALO(void);
  void GetStatusPA(void);
  void GetStatusVETO(void);
  Bool_t GetPAStatus(Int_t n) {return fgstatusPA[n];}
  Bool_t GetCaloStatus(Int_t n) {return fgstatusCalo[n];}
  Bool_t GetVetoStatus(Int_t n) {return fgstatusVeto[n];}

 private:

  static Bool_t fgTimeCorInit;
  static Bool_t fgNoTimeCor;
  static TLeaf *fgdp;
  static TLeaf *fgs2y;
  static TLeaf *fgs2rt;
  static TLeaf *fgt6;
  static TLeaf *fgth;
  static TLeaf *fgtdcval;
  static Float_t *fgcor0;
  static Float_t *fgcor1;
  static Float_t *fgcor1pa;
  static Float_t *fgcor1veto;
  static Float_t *fgcor2;
  static Float_t *fgcor3;
  static Float_t *fgcor4;
  static Float_t *fgHRSCor_DVCS2;
  static Float_t *fgCaloCor_DVCS2;
  static Float_t *fgHRSCor_DVCS3;
  static Float_t *fgCaloCor_DVCS3;
  static Float_t *fgcor1_DVCS3;//ARS time offset
  static Bool_t *fgstatusCalo;
  static Bool_t *fgstatusPA;
  static Bool_t *fgstatusVeto;

  char*  currentfile;
  THaEvent *ha2;
  THaRun *harun;
  TCaloEvent *caloev;
  TDVCSEvent *ev;
  TARSWave *wave;
  TTree *gTree;
  Bool_t kWF;
  Bool_t kHRSCor;
  Int_t run;
  Int_t minanawin;
  Int_t maxanawin;

  static TChain *fgTree;
};

