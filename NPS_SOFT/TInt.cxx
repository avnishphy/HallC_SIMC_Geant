//
// TInt.cxx, v1.0, Sat Jun  12 14:42:50
// Author: C. Munoz Camacho
//

#include <iostream>

#ifndef __TInt__
#include "TInt.h"
#endif

ClassImp(TInt)

////////////////////////////////////////////////////////////////////////////////
//
// Int_t Wrapper Class
//
// It wraps a Int_t in an object inheriting from TObject
// 
////////////////////////////////////////////////////////////////////////////////

//_____________________________________________________________________________
 TInt::TInt()
{
  // Default constructor. Initial value set to zero.
  //  cout<<"TInt constructor"<<endl;
  fValue=0.;
}

//_____________________________________________________________________________
 TInt::TInt(Int_t val)
{
  // Constructor with initial value
  fValue=val;
}

//_____________________________________________________________________________
 TInt::TInt(const TInt& intval)
{
  // Copy constructor
  fValue = intval.fValue;
}

//_____________________________________________________________________________
 TInt::~TInt()
{
  // Default destructor
  //   cout<<"TInt destructor"<<endl;
}













