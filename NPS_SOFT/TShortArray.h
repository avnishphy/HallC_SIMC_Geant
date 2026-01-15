#ifndef __TShortArray__
#define __TShortArray__

#ifndef __TShort__
#include "TShort.h"
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

class TShortArray: public TObject
{

 private:

  //  static int fNumero;
  static int fNumber;
  //  UInt_t fLength;
  TH1F * fHisto;//!
  TCanvas *fCanvas;//!
  TClonesArray * fData;   //->

  TShortArray(const TShortArray &);

 public:

  TShortArray();
  TShortArray(int,Short_t *);
  ~TShortArray();
  void Init(Int_t lenght);
  void Draw(const char* opt);
  void Draw(TPad *pad=0);
  void Clear();
  void RandomFill(UInt_t seed=123, Short_t max=10);
  Short_t AddValue(Short_t val);
  Int_t GetMinimumBin(void);
  Int_t GetMaximumBin(void);
  Short_t GetIntegral(void);
  TH1F* GetHisto(void) { return fHisto ; }
  //TShortArray(const TShortArray &);
  TShortArray & operator = (const TShortArray &);
  Short_t & operator [] (UInt_t);
  Short_t SetValue(UInt_t,Short_t);
  Short_t  & GetValue(UInt_t);
/*    Short_t SetLength(UInt_t l); */
/*    Short_t GetLength(){return fLength;}; */
  TShortArray(int length);
  void Print();

  ClassDef(TShortArray,1)
}
;
#endif







