//
// TBool.cxx, v1.0, Thu Feb  2 14:42:50
// Author: C. Munoz Camacho
//

#include <iostream>

#ifndef __TBool__
#include "TBool.h"
#endif

ClassImp(TBool)

////////////////////////////////////////////////////////////////////////////////
//
// Bool_t Wrapper Class
//
// It wraps a Bool_t in an object inheriting from TObject
// 
////////////////////////////////////////////////////////////////////////////////

//_____________________________________________________________________________
 TBool::TBool()
{
  // Default constructor. Initial value set to zero.
  //  cout<<"TBool constructor"<<endl;
  fValue=0.;
}

//_____________________________________________________________________________
 TBool::TBool(Bool_t val)
{
  // Constructor with initial value
  fValue=val;
}

//_____________________________________________________________________________
 TBool::TBool(const TBool& floatval)
{
  // Copy constructor
  fValue = floatval.fValue;
}

//_____________________________________________________________________________
 TBool::~TBool()
{
  // Default destructor
  //   cout<<"TBool destructor"<<endl;
}













