#ifndef __TFloatArray__
#define __TFloatArray__

#ifndef __TFloat__
#include "TFloat.h"
#endif

#ifndef ROOT_TObject
#include "TObject.h"
#endif

#ifndef ROOT_TClonesArray
#include "TClonesArray.h"
#endif

#ifndef ROOT_TH1
#include "TH1.h"
#endif

#ifndef ROOT_TPad
#include "TPad.h"
#endif

#ifndef ROOT_TCanvas
#include "TCanvas.h"
#endif

#include <Rtypes.h>
#include <iostream>

using namespace std;

class TFloatArray: public TObject
{

 private:

  //  static int fNumero;
  static int fNumber;
  //  UInt_t fLength;
  TH1F * fHisto;//!
  TCanvas *fCanvas;//!
  TClonesArray * fData;   //->

  //  TFloatArray(const TFloatArray &);

 public:

  TFloatArray();
  TFloatArray(int,Float_t *);
  TFloatArray(const TFloatArray &);
  ~TFloatArray();
  void Init(Int_t lenght);
  void Draw(const char* opt);
  void Draw(TPad *pad=0);
  void Clear();
  void RandomFill(UInt_t seed=123, Float_t max=10.);
  Float_t AddValue(Float_t val);
  Int_t GetMinimumBin(void);
  Int_t GetMaximumBin(void);
  Float_t GetIntegral(void);
  TH1F* GetHisto(void) { return fHisto ; }
  TClonesArray* GetData(void) { return fData ; }
  //TFloatArray(const TFloatArray &);
  TFloatArray & operator = (const TFloatArray &);
  Float_t & operator [] (UInt_t);
  Float_t SetValue(UInt_t,Float_t);
  Float_t  & GetValue(UInt_t);
/*    Float_t SetLength(UInt_t l); */
/*    Float_t GetLength(){return fLength;}; */
  TFloatArray(int length);
  void Print();

  ClassDef(TFloatArray,1)
}
;
#endif







