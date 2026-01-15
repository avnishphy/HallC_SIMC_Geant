//
// TShort.cxx, v1.0, Thu Feb  2 14:42:50
// Author: C. Munoz Camacho
//

#include <iostream>

#ifndef __TShort__
#include "TShort.h"
#endif

ClassImp(TShort)

////////////////////////////////////////////////////////////////////////////////
//
// Short_t Wrapper Class
//
// It wraps a Short_t in an object inheriting from TObject
// 
////////////////////////////////////////////////////////////////////////////////

//_____________________________________________________________________________
 TShort::TShort()
{
  // Default constructor. Initial value set to zero.
  cout<<"TShort constructor"<<endl;
  fValue=0;
}

//_____________________________________________________________________________
 TShort::TShort(Short_t val)
{
  // Constructor with initial value
  cout<<"TShort constructor with value "<<val<<endl;
  fValue=val;
}

//_____________________________________________________________________________
 TShort::TShort(const TShort& shortval)
{
  // Copy constructor
  fValue = shortval.fValue;
}

//_____________________________________________________________________________
void TShort::Clear(void)
{
  //Sets value to zero
  fValue = 0;
}

//_____________________________________________________________________________
 TShort::~TShort()
{
  // Default destructor
  cout<<"TShort destructor"<<endl;
}













