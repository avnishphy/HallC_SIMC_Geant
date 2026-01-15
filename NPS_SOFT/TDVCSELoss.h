#include <Rtypes.h>
#include <iostream>
#include <TMath.h>
#include <TObject.h>

using namespace std;

class TDVCSELoss
{
public:
  // THaDVCSELoss();
  TDVCSELoss();
static Double_t ElossHadron( Int_t Z_hadron, Double_t beta, 
		       Double_t z_med, Double_t a_med, 
		       Double_t d_med, 
		       Double_t pathlength );
static void HaDensi( Double_t z_med, Double_t d_med,
			   Double_t& X0, Double_t& X1, Double_t& M );
  ~TDVCSELoss();
static  Double_t ExEnerg( Double_t z_med, Double_t d_med );
  ClassDef(TDVCSELoss,0)
}
;
