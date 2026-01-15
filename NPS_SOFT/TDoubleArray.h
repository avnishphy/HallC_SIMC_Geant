#ifndef __TDoubleArray__
#define __TDoubleArray__

#include "TDouble.h"
#include "TObject.h"
#include "TClonesArray.h"
#include "TH1.h"
#include "TPad.h"
#include "TCanvas.h"

#include <Rtypes.h>
#include <iostream>

//using namespace std;

#undef DOUBLE_WITH_CLONESARRAY
class TDoubleArray: public TObject
{

 private:

  //  static int fNumero;
  static Int_t fNumber;//!
  //  UInt_t fLength;
  TH1F * fHisto;//!
  TCanvas *fCanvas;//!
#ifndef DOUBLE_WITH_CLONESARRAY
  Int_t      fSz;     // size-of the array in question
  Int_t      fN;      // number of dynamic array of doubles -- index of NEXT entry
  Double_t  *fDarray; //[fN]  array of doubles
#else
  TClonesArray * fData;   //->
#endif

 public:

  TDoubleArray();
  TDoubleArray(int,Double_t *);
  TDoubleArray(const TDoubleArray &);
  ~TDoubleArray();
  void Init(Int_t length=128);
   void Draw(const char* opt);
  void Draw(TPad *pad=0,Float_t min=-10000, Float_t max=-10000,const char* opt="");
  void Clear();
  void RandomFill(UInt_t seed=123, Double_t max=10.);
  Double_t AddValue(Double_t val);
  Double_t FindValue(Double_t thres);
  Int_t Minimum(Int_t & pos);
  Int_t Minimum();
  Int_t GetMinimumBin(Int_t nmin=0, Int_t nmax=-1);
  Int_t GetMaximumBin(Int_t nmin=0, Int_t nmax=-1);
  Double_t GetIntegral(Int_t nmin=0, Int_t nmax=-1);
  TH1F* GetHisto(void) { return fHisto ; }
  //  void SetLineColor(Color_t col) { fHisto->SetLineColor(col) ; }
  //TDoubleArray(const TDoubleArray &);
  TDoubleArray & operator = (const TDoubleArray &);
  Double_t & operator [] (UInt_t);
  Double_t SetValue(UInt_t,Double_t);
  Double_t  & GetValue(UInt_t);
/*    Double_t SetLength(UInt_t l); */
/*    Double_t GetLength(){return fLength;}; */
  TDoubleArray(int length);
  void Print();
  //  TClonesArray* GetArray(void) { return fData ; }

#ifndef DOUBLE_WITH_CLONESARRAY
  ClassDef(TDoubleArray,1)
#else
  ClassDef(TDoubleArray,2)
#endif
}
;
#endif


