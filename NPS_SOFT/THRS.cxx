//
// THRS.cxx, v1.0, Thu Feb  2 14:42:50
// Author: C. Munoz Camacho
//

#include <iostream>

#ifndef __THRS__
#include "THRS.h"
#endif

ClassImp(THRS)

////////////////////////////////////////////////////////////////////////////////
//
// Double_t Wrapper Class
//
// It wraps a Double_t in an object inheriting from TObject
// 
////////////////////////////////////////////////////////////////////////////////

//_____________________________________________________________________________
 THRS::THRS()
{
  // Default constructor. Initial value set to zero.
  // cout<<"THRS constructor "<<this<<endl;
  fScattered=0;
  fScattered_c=0;
}

//_____________________________________________________________________________
void THRS::Clear(void)
{
  //Sets value to zero
//   fScattered=0;
//   fScattered_c=0;
}

//_____________________________________________________________________________
 THRS::~THRS()
{
  // Default destructor
  delete fScattered;
  delete fScattered_c;
}













