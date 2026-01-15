#include "TARSConst.h"

TARSConst::TARSConst():TObject()
{

}

TARSConst::TARSConst(const TARSConst & copy)
{
  for (int i=0;i<2;i++)
    {
      fChi2[i]=copy.fChi2[i];
    }
 for (int i=0;i<1;i++)
    {
      for (int j=0;j<1;j++)
	fTime[i][j]=copy.fTime[i][j];
      fAmpLim[i]=copy.fAmpLim[i];
    }
}

TARSConst::~TARSConst()
{
  
    
}

void TARSConst::Init()
{
  
    
}

void TARSConst::Compute()
{
  
    
}

void TARSConst::SetChi(UInt_t n ,Double_t value)
{
//Set the time window
  if (n<3)
    {
      fChi2[n]=value;
    }
}// load shape from a file

Double_t TARSConst::GetChi(Int_t n)
{
// Get chi limit
 if (n<3)
    {
  return fChi2[n];
    }
}// Get chi limit

  void TARSConst::SetTimeWin1(Int_t k1,Int_t k2)
{
   fTime[0][0]=k1;
   fTime[0][1]=k2;
}//Set the time window

  void TARSConst::SetTimeWin2(Int_t k1,Int_t k2)
{
   fTime[1][0]=k1;
   fTime[1][1]=k2;
}//Set the time window

  void TARSConst::SetAmpLim(Double_t a1,Double_t a2)
{
  fAmpLim[0]=a1;
  fAmpLim[0]=a2;

}//Set the amplitude limits for the updated shape
  Double_t TARSConst::GetAmpLow()
{
  return fAmpLim[0];
}//


  Double_t TARSConst::GetAmpUp()
{
  return fAmpLim[1];
}//
