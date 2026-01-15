//
// TARSArray.cxx, v1.0, Thu Dec 29 14:42:50
// Author: C. Munoz Camacho
//

#include <iostream>
#include <new>

#ifndef ROOT_TObjectTable
#include "TObjectTable.h"
#endif

#ifndef __TARSArray__
#include "TARSArray.h"
#endif

using namespace std;

ClassImp(TARSArray)

////////////////////////////////////////////////////////////////////////////////
//
// ARS Array class
// 
////////////////////////////////////////////////////////////////////////////////

Bool_t           TARSArray::fgWarnings = kTRUE;
Bool_t           TARSArray::fgErrors = kTRUE;
TClonesArray    *TARSArray::fgWave = 0;

//_____________________________________________________________________________
TARSArray::TARSArray(Int_t size)
{
  // Default constructor

  cout<<"TARSArray constructor"<<endl;

  if (!fgWave) fgWave = new TClonesArray("TARSWave",size);

  fWave=fgWave;
  fNwave=0;
  fNbWaves=0;

}

/*
//_____________________________________________________________________________
 TARSArray::TARSArray(const TARSArray& TCaloevent)
  // Copy constructor
{
  ((TARSArray&)TCaloevent).Copy(*this);
}

//_____________________________________________________________________________
 void TARSArray::Copy(TObject& obj)
{
  // Copy routine. Used by copy ctor.

  //  TObject::Copy(obj);

  //  fgParameters.Copy(((TCaloBase&)obj).fgParameters);
  //  ((TCaloBase&)obj).fgIsInit = fgIsInit;


}
*/
//_____________________________________________________________________________
 TARSArray::~TARSArray()
{
  // Default destructor

  cout<<"TARSArray destructor"<<endl;

  Clear();
}

//_____________________________________________________________________________
void TARSArray::Clear(void)
{
  //Clears the event

  //  fWave->Clear();//We delete because waves allocate memory
  for (Int_t i=0;i<fNwave;i++){
    TARSWave* wave=(TARSWave*)fWave->UncheckedAt(i);
    delete wave;
  }
  fWave->Clear();

  fNwave=0;
  fNbWaves=0;
}

//_____________________________________________________________________________
void TARSArray::Reset(void)
{
  //Clears the event, but don't call clusters destructors

  for (Int_t i=0;i<fNwave;i++){
    TARSWave* wave=(TARSWave*)fWave->UncheckedAt(i);
    wave->Reset();
  }
  fNbWaves=0;
}

//_____________________________________________________________________________
TARSWave* TARSArray::AddWave(void)
{
  //It adds the TCaloBlock to the TClonesArray of waves after the last one.
  
  // new with placement operator
  TARSWave* wave=0;
  //  if(fNbWaves<fNwave){
//      wave=(TARSWave*)fWave->UncheckedAt(fNbWaves);
//      fNbWaves++;
//    }else{
    TClonesArray &waves = *fWave;
    wave = new(waves[fNwave++]) TARSWave();
    fNbWaves++;
    //  }
  return wave;
}

//_____________________________________________________________________________
TARSWave* TARSArray::AddWave(Int_t size)
{
  //It adds the TCaloWave to the TClonesArray of waves after the last one.
  
  // new with placement operator
  TARSWave* wave=0;
 //   if(fNbWaves<fNwave){
//      wave=(TARSWave*)fWave->UncheckedAt(fNbWaves);
//      fNbWaves++;
//    }else{
    TClonesArray &waves = *fWave;
    wave = new(waves[fNwave++]) TARSWave(size);
    fNbWaves++;
    //}
  cout<<"We have created wave number "<<fNbWaves-1<<endl;
  return wave;  
}

//_____________________________________________________________________________
 void TARSArray::Print(const char* opt)
{
  //    Output on screen: number of waves in the array.
  //If option "C" is specified the method Print() of each of the wave is called.

  cout<<"============================================================"<<endl;
  cout<<"  Number of waves in the array : "<<fNbWaves<<endl;
  if(opt[0]=='C'){
    for(Int_t i=0;i<fNbWaves;i++){
      TARSWave *wave=(TARSWave*)fWave->UncheckedAt(i);
      wave->Print();
    }
  }
  cout<<"============================================================"<<endl;
}
















