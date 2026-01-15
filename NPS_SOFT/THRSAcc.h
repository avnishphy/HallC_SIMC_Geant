#include <iostream>
#include <TObject.h>
#include <TVector3.h>

using namespace std;

//20190403(start)
//temporarily commented out because when using in geant4, it gives error
/* extern "C" */
/* { */
/* extern void hrse_acceptance_maps2__(float*,bool*); */
/* } */
//20190403(finish)

class THRSAcc
{
 public:
  THRSAcc();
  static Bool_t InHRS(TVector3* part,TVector3* vertex, Double_t HRSangle, Double_t HRSmom);
  ClassDef(THRSAcc,0)
 };
