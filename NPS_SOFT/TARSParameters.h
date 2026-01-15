#ifndef __TARSParameters__
#define __TARSParameters__

///////////////////////////////////////////////////////////////////////////////
//
//
//             class TARSParam
//             simple class to hold data for one ARS channel
//             shape analysis
//            
//            
//
///////////////////////////////////////////////////////////////////////////////


#include <TObject.h>
#include <Rtypes.h>
#include <iostream> 
#include <fstream>
#include "TDouble.h"
#include "TDoubleArray.h"
#include <TClonesArray.h>
#include <TMatrixD.h>
#include <TProfile.h>

using namespace std;

class TARSParameters : public TObject
{
 public:
  TARSParameters();
  TARSParameters(UInt_t);
  TARSParameters(UInt_t Size,Double_t *);
  TARSParameters(const TARSParameters &);
  ~TARSParameters();
  void Print();
  void PrintShape();
  void PrintShape2();
  void Compute();
  void SetShape(const char*);// load shape from a file
  Double_t  GetBase(Int_t n);// return value of baseline for sample n
  TDoubleArray *  GetBase(){return fBase;};// return value of baseline for sample n
  Double_t  GetShape(Int_t n);// return value of baseline for sample n
  Double_t  GetSum(Int_t n);// return value of baseline for sample n
  Double_t  GetShape2(Int_t n,Int_t m);// return value of crossproduct sum
  void SetPedestal(const char*);// load pedestal
  void SetPedestal(TProfile *);// load pedestal
  void DrawShape(const char* opt=""){fShape->Draw(opt);};
  void DrawBase(const char* opt=""){fBase->Draw(opt);};
  TMatrixD * GetMatrix1(Int_t i);
  TMatrixD * GetMatrix2(Int_t i,Int_t j);
 protected:
  void Init();
  Int_t fSize;// number of sample
  TClonesArray * fMatrix1;// Matrixes for system solving one pulse + background 
  TClonesArray * fMatrix2;// Matrixes for system solving two pulses + background 
  TDoubleArray * fBase ; // [fSize] 3*fSize Pedestal data
  TDoubleArray * fShape;//[fSize] 3*fSize Signal profile
  TDoubleArray * fSum;//[fSize] [2*fSize]Sum of the shape 
  TMatrixD * fShape2;//[2*fSize][2*fSize] table of products of shape samples
  ClassDef(TARSParameters,1)
};

#endif



