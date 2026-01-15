//
// THCalo.h, v1.0, Sat May  24 14:42:50
// Author: C. Munoz Camacho

#ifndef __THCalo__
#define __THCalo__

#ifndef ROOT_TH2
#include "TH2.h"
#endif

#ifndef ROOT_TText
#include "TText.h"
#endif

#ifndef ROOT_TPolyLine
#include "TPolyLine.h"
#endif

#ifndef ROOT_TCanvas
#include "TCanvas.h"
#endif

#ifndef __TCaloBase__
#include "TCaloBase.h"
#endif

#include <iostream>

////////////////////////////////////////////////////////////////////////////////
//
// THCalo.h
//
// Proton Array histogram class
//
// 
////////////////////////////////////////////////////////////////////////////////

using namespace std;

class THCalo : public TCaloBase
{

  private :

    static Int_t fNumber;//!
  TH2F *h;                  //! Histo              
  TPolyLine ***fPolyLine;         //! Polylines
  TText **fText;            //! The text
  TPad *fCanvas;         //! The Canvas
  Float_t fMax;             //! Maximum value of the histogram
  Float_t fMin;

  public :
    
  THCalo(Float_t max=-1.);
  THCalo(TPad *canvas,Float_t max=-1);
  THCalo (const THCalo&);
  void Clear(void);
  void SetMinimum(Float_t min) {fMin=min;}
  void SetMaximum(Float_t max) {fMax=max;}
  void InitDisplay(void);
  void Draw(const char* opt="colztext");
  void SetBinContent(Int_t x, Int_t y, Float_t val);
  void HighlightBin(Int_t tower, Int_t ring);
  void UnHighlightBin(Int_t tower, Int_t ring);
  void SetMax(Float_t max) { fMax=max ; }
  TH2F* GetHisto(void){return h;}
  TPad* GetPad(void) {return fCanvas ;}
  void SetPad(TPad* pad) { fCanvas=pad ; }
  void Update(void);
  virtual ~THCalo();

  ClassDef(THCalo,1) // HCalo Class

}; // End of THCalo class definition

#endif






