//
// TARSWave.h, v1.1, Thu April 8th 2003
// Author: C. Mu�oz Camacho
//         A.Camsonne

#ifndef __TARSWave__
#define __TARSWave__

#include <iostream>
#include <fstream>

#ifndef ROOT_TObject
#include "TObject.h"
#endif

#ifndef ROOT_TCanvas
#include "TCanvas.h"
#endif

#ifndef __TARSBase__
#include "TARSBase.h"
#endif

#ifndef __TDoubleArray__
#include "TDoubleArray.h"
#endif

#ifndef __TShortArray__
#include "TShortArray.h"
#endif


////////////////////////////////////////////////////////////////////////////////
//
// TARSWave.h
//
// ARS Wave class
//
// Makes ARS Wave analysis
// 
////////////////////////////////////////////////////////////////////////////////

class TARSWave : public TARSBase
{
  protected :
  TDoubleArray * fWave; //->
  static TDoubleArray * fFit; //!
  TDoubleArray * fData;//! pedestal substracted
  TDoubleArray * fPedestal;//!
  Int_t fNbChannel;
  TH1D *fH; //!
  TCanvas *fCanvas;//!
  Bool_t fSubstracted;
  Bool_t fAnalyzed;
  static TDoubleArray* fgWave;
  static TDoubleArray* fgData;
  static TMatrixD*  fgX1;
  static TMatrixD*  fgP1;
  static TMatrixD*  fgX2;
  static TMatrixD*  fgP2;
  static Double_t* fgval1;//!
  static Double_t* fgval2;//!
  static Double_t* fgsol1;//!
  static Double_t* fgsol2;//!
  static Int_t fmaxchi2;//!
  static Int_t fminchi2;//!
  static TDoubleArray** fgPedCalo;//!
  static TDoubleArray** fgPedPA;//!
  static TDoubleArray** fgPedVeto;//!
 //  TARSWave(TARSWave* wave);
  Int_t fNPulse; //Number of pulses
  static Double_t* fga; //!
  static Double_t* fgt; //!
  Double_t* fa; //[fNPulse]
  Double_t* ft; //[fNPulse]
  Double_t  fb; 
  Double_t  fchi2;
  UInt_t fDAC;
  UInt_t fVME;
  UInt_t fChan;
  static Bool_t           fgPedIsInit;//Are pedestals initialized from DB?
  static Bool_t           fgIsInitShapeAnalysis;// Shape analysis initialized ? */
  static Bool_t           fgIsInitShapeAnalysisLED;// Shape analysis initialized ? */
  
  public :

  TARSWave();
  TARSWave(Int_t size, Int_t nbchannels=-1);
  TARSWave(TARSWave* wave);
  TARSWave(const TARSWave&);
  void Reset(void);
  void Clear(Option_t *option);
  void DrawRaw(TPad* canvas, const char* opt="", Float_t min=-10000, Float_t max=-10000);
  void DrawSignal(TPad* canvas, const char* opt="", Float_t min=-10000, Float_t max=-10000);
  //  TDouble* SetValue(Int_t n,Double_t v);
  TDoubleArray* GetArray(void) { return fWave ; }
  TDoubleArray* GetSignal(void) { return fData ; }
  Double_t SetValue(Int_t n,Double_t v);
  void SetPedestal(TARSParameters * par){fPedestal=par->GetBase();};
  void SetPedestal(UInt_t chan){SetPedestal(&TARSBase::fgARSParameters[chan]);};
  Bool_t IsAnalyzed(void) {return fAnalyzed ; }
  
  TDouble* AddValue(Int_t n,Double_t v);
  virtual ~TARSWave(); 
  void SubstractPedestal();
  void SubstractPedestal(int);
  UInt_t GetDAC()
  {return fDAC;}
//   UInt_t GetVME()
//   {return fVME;}
//   UInt_t GetChan()
//   {return fChan;}
  Double_t GetARSCor(void);
  void InitPedDB(Int_t run);
  void InitPed(Int_t run);
  void SubstractPedestalDB(Int_t ch, Int_t run, const char* dec);
  void SubstractPedestalDB(Int_t ch, const char* dec);
  void SubstractPedestal(Int_t ch, Int_t run, const char* dec);
  Int_t Analyze(const char* opt, Double_t *rawtimes=0);
  void Fit0Pulse(Double_t& b, Double_t& chi2, const char* opt);
  void Fit1Pulse(Double_t& a, Double_t& t, Double_t& b, Double_t& chi2, const char* opt, Double_t *rawtimes=0);
  Int_t Fit2Pulses(Double_t& a1, Double_t& a2, Double_t& t1, Double_t& t2, Double_t& b, Double_t& chi2, const char* opt, Double_t *rawtimes=0);
  void SetNbChannel(Int_t n, const char* detector);
  Int_t GetNbChannel(Int_t n, const char* detector);
  Int_t GetNbPulses(void) { return fNPulse ; }
  Double_t GetAmplitude1(void);
  Double_t GetAmplitude2(void);
  Double_t GetArrivalTime1(void);
  Double_t GetArrivalTime2(void);
  Double_t GetB(void);
  void SetWavePar(Double_t amp1, Double_t amp2, Double_t t1, Double_t t2, Double_t b){
    fAnalyzed=kTRUE;
    if(!fa) fa=new Double_t[2];
    if(!ft) ft=new Double_t[2];
    fa[0]=amp1; fa[1]=amp2; ft[0]=t1; ft[1]=t2; fb=b;
    fNPulse=2;
  }
  Double_t GetChi2(void);
  Int_t Decode(Int_t *);
  Int_t Decode(const int *);
  Int_t Decode(Int_t *,Int_t length);
  void SetChi20(Double_t val) { fchi20[fNbChannel]=val ;}
  void SetChi21(Double_t val) { fchi21[fNbChannel]=val ;}
  void SetChi22(Double_t val) { fchi22[fNbChannel]=val ;}
  Double_t GetChi20(void) { return fchi20[fNbChannel] ;}
  Double_t GetChi21(void) { return fchi21[fNbChannel] ;}
  Double_t GetChi22(void) { return fchi22[fNbChannel] ;}
  void SetResolution(Int_t reso) {fgReso[fNbChannel]=reso;}
  Double_t & operator [] (UInt_t );// access to data
  void SetFirstWindow(Int_t min, Int_t max, const char* opt, Bool_t kFORCE=kFALSE);
  void SetChi2Window(Int_t min, Int_t max) {fminchi2=min;fmaxchi2=max;}
  void SetSecondWindow(Int_t min1, Int_t max1, Int_t min2, Int_t max2, const char* opt, Bool_t kFORCE=kFALSE);
  void InitShapeAnalysis(void);
  void InitShapeAnalysisLED(void);
  Double_t Fraction(Double_t fraction)
{
  Double_t min=fData->Minimum();
  return fData->FindValue(fraction*min);
}

/*   void DrawSignal(TPad *p,Float_t min=-10000, Float_t max=-10000) */
/*     { */
/*       fData->Draw(p,min,max); */
/*     }; */

  TDoubleArray *GetFit(const char* opt);

 private:
  ClassDef(TARSWave,3)

};
#endif






