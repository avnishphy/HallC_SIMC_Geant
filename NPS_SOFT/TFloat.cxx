//
// TFloat.cxx, v1.0, Thu Feb  2 14:42:50
// Author: C. Munoz Camacho
//

#include <iostream>

#ifndef __TFloat__
#include "TFloat.h"
#endif

ClassImp(TFloat)

////////////////////////////////////////////////////////////////////////////////
//
// Float_t Wrapper Class
//
// It wraps a Float_t in an object inheriting from TObject
// 
////////////////////////////////////////////////////////////////////////////////

//_____________________________________________________________________________
 TFloat::TFloat()
{
  // Default constructor. Initial value set to zero.
  //  cout<<"TFloat constructor"<<endl;
  fValue=0.;
}

//_____________________________________________________________________________
 TFloat::TFloat(Float_t val)
{
  // Constructor with initial value
  fValue=val;
}

//_____________________________________________________________________________
 TFloat::TFloat(const TFloat& floatval)
{
  // Copy constructor
  fValue = floatval.fValue;
}

//_____________________________________________________________________________
 TFloat::~TFloat()
{
  // Default destructor
  //   cout<<"TFloat destructor"<<endl;
}













