#include "THRSAcc.h"
#include "TMath.h"

ClassImp(THRSAcc)

  THRSAcc::THRSAcc()
{

}

Bool_t THRSAcc::InHRS(TVector3* part,TVector3* vertex, Double_t HRSangle, Double_t HRSmom)
{
  part->RotateY(-HRSangle);
  
  float xt[5];
  xt[3]=TMath::ATan2(part->Px(),part->Pz());
  xt[1]=TMath::ATan2(-(part->Py()),part->Pz());
  xt[2]=-10.*vertex->Pz()*TMath::Sin(HRSangle+xt[3])/TMath::Cos(xt[3]);
  xt[0]=-10.*vertex->Pz()*TMath::Cos(HRSangle)*TMath::Tan(xt[1])/TMath::Cos(xt[3]);
  xt[4]=(part->Mag()-HRSmom)/HRSmom;

  bool v;
  //20190403(start)
  //temporarily commented out because when using in geant4, it gives error
  // hrse_acceptance_maps2__(xt,&v);
  //20190403(finish)
  return (Bool_t)v;

}
