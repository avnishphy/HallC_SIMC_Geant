//
// TDouble.cxx, v1.0, Thu Feb  2 14:42:50
// Author: C. Munoz Camacho
//

#include <iostream>

#ifndef __TDouble__
#include "TDouble.h"
#endif

ClassImp(TDouble)

////////////////////////////////////////////////////////////////////////////////
//
// Double_t Wrapper Class
//
// It wraps a Double_t in an object inheriting from TObject
// 
////////////////////////////////////////////////////////////////////////////////

//_____________________________________________________________________________
 TDouble::TDouble()
{
  // Default constructor. Initial value set to zero.
  // cout<<"TDouble constructor "<<this<<endl;
  fValue=0;
}
//_____________________________________________________________________________
 TDouble::TDouble(Double_t val)
{
  // Constructor with initial value
//  cout<<"TDouble constructor with value "<<val<<" ";
  fValue=val;
}

//_____________________________________________________________________________
 TDouble::TDouble(const TDouble& Doubleval)
{
  // Copy constructor
  fValue = Doubleval.fValue;
}

//_____________________________________________________________________________
void TDouble::Clear(void)
{
  //Sets value to zero
  fValue = 0;
}

//_____________________________________________________________________________
 TDouble::~TDouble()
{
  // Default destructor
  // cout<<"TDouble destructor ";
}













