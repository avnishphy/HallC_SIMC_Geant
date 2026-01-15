//
// TARSBase.h, v1.0, Thu Sep 12 11:13:57
// Author: C. Mu�oz Camacho
//

#ifndef __TARSBase__
#define __TARSBase__

#include "TObject.h"
#include "TARSParameters.h"
#include "TARSConst.h"
#include "TARSCalibration.h"
#include "TFile.h"
////////////////////////////////////////////////////////////////////////////////
//
// TARSBase.h
//
// ARS base class
// 
////////////////////////////////////////////////////////////////////////////////

using namespace std;

class TARSBase : public TObject
{
/*    private : */
   
  Int_t             nbchanels; //!

 protected :
  static Bool_t fgIsInitShapeAnalysisBase;//!
  static UInt_t fNbChannels; //!
  static UInt_t fNbChannelsCalo; //!
  static UInt_t fNbChannelsPA; //!
  static UInt_t fNbChannelsVeto; //!
  static UInt_t fgSize; 
  static Int_t            fNbChanels; 
  static Int_t            fNbSamples; 
  static Int_t            fksp;
  static Int_t            fkled;
  static Int_t            fk1;
  static Int_t            fk2;
  static Int_t            fk1min;
  static Int_t            fk1min2;
  static Int_t            fk2min;
  static Int_t            fk1max;
  static Int_t            fk1max2;
  static Int_t            fk2max;
  static Int_t            fgk1min;
  static Int_t            fgk1min2;
  static Int_t            fgk2min;
  static Int_t            fgk1max;
  static Int_t            fgk1max2;
  static Int_t            fgk2max;
  static Int_t* fgReso;
  static Int_t* fgminref; 
  static Int_t*            fmin;
  static Int_t*            fmax;
  static Int_t             fminfixed;
  static Int_t             fmaxfixed;
  static Int_t             fminacc;
  static Int_t             fmaxacc;

  static Double_t*         fchi20;
  static Double_t*         fchi21;
  static Double_t*         fchi22;
  static Double_t**       fgRunningwei;
  static Bool_t           fgIsInit;             //Initialized ? */
  static Bool_t           fgRunningIsInit;             //Initialized ? */
  static Bool_t           fgWarnings;          // Display warnings ?
  static Bool_t           fgErrors;            // Display errors ?
  static Bool_t           fgCaloWF;
  static Bool_t           fgPAWF;
  static Bool_t           fgVetoWF;
  static Bool_t           fgbfixed;

  static TARSParameters  * fgARSParameters ;//Shape analysis parameters 
  static TARSConst * fgARSConst;//Shape analysis constants 
  static TARSCalibration * fgARSCalib;//Calibration constants 

  static TClonesArray *fgRefShapes;   //Reference shapes (one per block for the moment)
  static TClonesArray *fgRefShapesLED;   //Reference shapes (one per block for the moment)
  static TMatrixD ***fgM1;//!
  static TMatrixD ****fgM2;//!
  static TMatrixD ***fgM1LED;//!
  static Double_t **fgpedsigma2;//!
  static Double_t *fnval1;//!
  static Double_t *fnval2;//!

  TARSBase(const TARSBase&);

  public :

  TARSBase(Int_t nbchannels=-1);
  //  TARSBase(const TARSBase&);
  virtual ~TARSBase();

  //  virtual void Copy(TARSBase&);
  virtual void Init(const char*  opt="");
  virtual void InitShapeAnalysis(const char*  opt="data");
  void InitAnalysisWindowDB(Int_t* min, Int_t* max, Int_t run);
  virtual void InitShapeAnalysisDB(Int_t run,const char*  opt="data");
  virtual void InitShapeAnalysisLED(const char*  opt="data");
  virtual void Print(const char* opt="");
  TARSParameters * GetParam(int i){return &fgARSParameters[i];};
  void ActivateOnly(const char*  opt);
  void SetWarnings(Bool_t val) { fgWarnings = val; };
  void SetErrors(Bool_t val) { fgErrors = val; };
  // TARSParameters method
  void PrintParam(Int_t m){fgARSParameters[m].Print();};
  void PrintShape(Int_t m){fgARSParameters[m].PrintShape();};
  void PrintShape2(Int_t m){fgARSParameters[m].PrintShape2();};
  //  void Compute(){for (Int_t i=0;i<fNbChannels;i++) fgARSParameters[i].Compute();};
  void SetNewFirstWindow(Int_t min, Int_t max) {fk1min=min;fk1max=max;}
  void SetNewSecondWindow(Int_t min1, Int_t max1, Int_t min2, Int_t max2) { fk1min2=min1; fk1max2=max1; fk2min=min2; fk2max=max2;}
  void SetShape(Int_t m,const char*   fname){fgARSParameters[m].SetShape(fname);};// load shape from a file
  Double_t  GetBase(Int_t m,Int_t n){return fgARSParameters[m].GetBase(n);};// return value of baseline for sample n
  Double_t  GetShape(Int_t m,Int_t n){return fgARSParameters[m].GetShape(n);};// return value of baseline for sample n
  Double_t  GetSum(Int_t m,Int_t n){return fgARSParameters[m]. GetSum(n);};// return value of baseline for sample n
  Double_t  GetShape2(Int_t m,Int_t i,Int_t j){return fgARSParameters[m].GetShape2(i,j);};// return value of crossproduct sum
  void SetRefShape(const char*  file);
  void SetPedestal(Int_t m,const char*   fname){ fgARSParameters[m].SetPedestal(fname);};// load pedestal
  void SetPedestalProfileFile(const char*  );
  void DrawShape(Int_t i, const char* opt="");
  void DrawBase(Int_t m){fgARSParameters[m].DrawBase();};
  TMatrixD * GetMatrix1(Int_t m,Int_t i){return fgARSParameters[m].GetMatrix1(i);};
  TMatrixD * GetMatrix2(Int_t m,Int_t i,Int_t j){return fgARSParameters[m].GetMatrix2(i,j);};
  void InitPedSigma(void);
  void PrintPedSigma(const char*   opt);
  void InitMatrix1(TMatrixD** matrix1, Int_t k, Int_t ch, const char*  opt, Bool_t kFORCE=kFALSE);
  void InitMatrix2(TMatrixD** matrix2, Int_t k, Int_t j, Int_t ch, const char*  opt, Bool_t kFORCE=kFALSE);
  void SetFirstWindow(Int_t min, Int_t max, const char*  opt, Bool_t kFORCE=kFALSE);
  void SetSecondWindow(Int_t min1, Int_t max1, Int_t min2, Int_t max2, const char*  opt, Bool_t kFORCE=kFALSE);
  //  void SetAnalysisWindow(Int_t min, Int_t max) {fmin=min;fmax=max;}
  void Add2RunningShape(TDoubleArray *wave, Int_t channel, Double_t amp, Double_t time, const char* opt);
 Int_t GetNbSamples(void) { return fNbSamples ; }
  TClonesArray* GetRefShapes(char) { return fgRefShapes; }
  TClonesArray* GetRefShapesLED(void) { return fgRefShapesLED; }
  void InitPedSigmaDB(Int_t run);
  void FixB(Bool_t val=kTRUE) { fgbfixed=val ; }
  void SetAnalysisWindowFixed(Int_t min, Int_t max) { fminfixed=min; fmaxfixed=max; }
  void SetAnalysisWindowAcc(Int_t min, Int_t max) { fminacc=min; fmaxacc=max; }
  ClassDef(TARSBase,4) // ARS Base Class 

}; // End of TARSBase class definition

#endif











