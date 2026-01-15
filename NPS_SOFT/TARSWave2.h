//
// TARSBase2.h, v1.0, 14/7/10
// Author: C. Muñoz Camacho
//

#ifndef __TARSWave2__
#define __TARSWave2__

#include "TObject.h"
#include "TMatrixD.h"

using namespace std;

class TARSWave2 : public TObject
{
 private:
    Double_t* refshape;//[128]
  Double_t* shape;//[128]
  Double_t* fit;//!
  Double_t fb;//Fitted base line
  Double_t fa1;//First pulse amplitude
  Double_t fa2;//Second pulse amplitude
  Double_t ft1;//First pulse arrival time
  Double_t ft1n;//First pulse arrival time no correction applied
  Double_t ft2;//Second pulse arrival time
  Double_t ft2n;//Second pulse arrival time no correction applied
  Double_t *matrix0;//!
  TMatrixD **matrix1;//!
  TMatrixD ***matrix2;//!
  TMatrixD ***matrix2nb;//!
  Bool_t fRunningIsInit;//!
  Double_t *fRunningwei;//!
  Double_t fEnergy2Chan;//!
  //Parameters
  Int_t imin;//!
  Int_t imax;//!
  Int_t chi2min;//!
  Int_t chi2max;//!
  Int_t t1min;//!
  Int_t t1max;//!
  Int_t t1minb;//!
  Int_t t1maxb;//!
  Int_t t2min;//!
  Int_t t2max;//!
  
  Double_t dtau;//!
  Double_t chi20;//!
  Double_t chi21;//!
  Double_t chi22;//!
  Int_t fChan;//Channel number
  Int_t fRun;//Run number
  Float_t *timecorr;//!ARS time correction
  void SetPars(void);

 public:

  TARSWave2();
  TARSWave2(Int_t Nchan, Int_t run);
  virtual ~TARSWave2();
  Double_t* GetRefShape(void){return refshape;}
  Double_t* GetShape(void){return shape;}
  void SetShape(Int_t i,Double_t val){shape[i]=val;}
  void SetRefShape(Int_t i,Double_t val){refshape[i]=val;}
  void Init(void);
  void Initnobase(void);
  Double_t* GetFit(void);
  Double_t* GetFit1(void);
  Double_t* GetFit2(void);
  Double_t Baseline(void);
  Double_t Fit0Pulse(void);
  Double_t Fit1Pulse(void);
  Double_t Fit1Pulsenobase(void);
  Double_t Fit2Pulses(void);
  Double_t Fit2Pulsesnobase(void);
  Double_t GetAmplitude1(void){return fa1;}
  Double_t GetAmplitude2(void){return fa2;}
  Double_t GetTime1(void){return ft1;}
  Double_t GetTime2(void){return ft2;}
  Double_t GetBaseline(void){return fb;}
  Double_t Analyze(Double_t thres0, Double_t thres1, Int_t option);
  Double_t GetChi20(void) {return chi20;}
  Double_t GetChi21(void) {return chi21;}
  Double_t GetChi22(void) {return chi22;}
  void Reinit();
  void Add2RunningShape(Double_t amp, Int_t time);

  ClassDef(TARSWave2,1)

}; // End of TARSWave2 class definition

#endif
