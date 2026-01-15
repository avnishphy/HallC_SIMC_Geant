///////////////////////////////////////////////////////////////////////////////
//
//
//             class TARSParam
//             simple class to hold data for one ARS channel
//             shape analysis
//             all data are protected and will be accessed by inheritance
//              
//
///////////////////////////////////////////////////////////////////////////////


#include <TObject.h>
#include <Rtypes.h>
#include <iostream> 

using namespace std;


class TARSConst : public TObject
{
 public:
  TARSConst();
  TARSConst(const TARSConst &);
  ~TARSConst();
 protected:
  Double_t fChi2[3];// limit of Chi square value
  Double_t fTime[2][2];//time windows first index for pulse second begin and end
  Double_t fAmpLim[2];//lower limit and upper limit on amplitude to update shape
 public:
  void Compute();
  void SetChi(UInt_t,Double_t);// load shape from a file
  Double_t GetChi(Int_t);// Get chi limit
  void SetTimeWin1(Int_t,Int_t);//Set the time window
  void SetTimeWin2(Int_t,Int_t);//Set the time window
  void SetAmpLim(Double_t,Double_t);//Set the amplitude limits for the updated shape
  Double_t GetAmpLow();// get lower amplitude limit to keep for updating shape
  Double_t GetAmpUp();// get upper amplitude limit to keep for updating shape
  void Init();// Initialize pointers
  ClassDef(TARSConst,1)
};
