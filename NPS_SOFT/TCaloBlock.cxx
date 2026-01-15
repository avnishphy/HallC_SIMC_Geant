//
// TCaloBlock.cxx, v1.0, Thu Dec  5 14:42:50
// Author: C. Muñoz
//

#include <iostream>
#include "TCaloBlock.h"
#include "TCaloBase.h"
using namespace std;

ClassImp(TCaloBlock)

////////////////////////////////////////////////////////////////////////////////
//
// DVCS calorimeter block class
// 
////////////////////////////////////////////////////////////////////////////////

//_____________________________________________________________________________
 TCaloBlock::TCaloBlock()
{
  // Default constructor
  //  gTCaloBlock = this;
  //  cout<<"TCaloBlock constructor"<<endl;
  fEnergy=new TClonesArray("TFloat",1);
  fEnergy->BypassStreamer(kFALSE);
  fTime=new TClonesArray("TFloat",1);
  fTime->BypassStreamer(kFALSE);
  fChi2=new TClonesArray("TDouble",1);
  fChi2->BypassStreamer(kFALSE);
  fBase=0;
  fNPulse=0;
  fBlockNb=0;
  fAnalyzed=kFALSE;
}

//_____________________________________________________________________________
 TCaloBlock::TCaloBlock(const TCaloBlock& block)
{
  // Copy constructor
  //  fEnergy = block.fEnergy;
  fBlockNb=block.fBlockNb;
  fNPulse=0;
  fAnalyzed=block.fAnalyzed;
//    fEnergy=new TClonesArray(*((TClonesArray*)(block.fEnergy)));  
//    fTime=new TClonesArray(*((TClonesArray*)(block.fTime)));
  fEnergy=new TClonesArray("TFloat",1);
  fTime=new TClonesArray("TFloat",1);
  fEnergy->BypassStreamer(kFALSE);
  fTime->BypassStreamer(kFALSE);
  for(Int_t i=0;i<block.fNPulse;i++){
    Float_t energy=((TFloat*)(block.fEnergy)->UncheckedAt(i))->GetValue();
    Float_t time=((TFloat*)(block.fTime)->UncheckedAt(i))->GetValue();
    TClonesArray &energies = *fEnergy;
    new (energies[fNPulse]) TFloat(energy);
    TClonesArray &times = *fTime;
    new (times[fNPulse]) TFloat(time);
    fNPulse++;
  }

  //    AddPulse(energy,time);
  
  //  arswave= block.arswave;
  //((TCaloBlock&)TCaloblock).Copy(*this);
}

//_____________________________________________________________________________
 void TCaloBlock::Clear(Option_t* option)
{
  fNPulse=0;
  fEnergy->Delete();
  fTime->Delete();
  fChi2->Delete();
  delete fEnergy;
  delete fTime;
  delete fChi2;
  fEnergy=0;
  fTime=0;
  fChi2=0;
  fBase=0;
  //fEnergy->Clear("C");
  //fTime->Clear("C");
  fAnalyzed=kFALSE;
}

//_____________________________________________________________________________
 void TCaloBlock::Erase(Option_t* option)
{
  fNPulse=0;
  fBase=0;
  fEnergy->Delete();
  fTime->Delete();
  fChi2->Delete();
//    delete fEnergy;
//    delete fTime;
//    fEnergy=0;
//    fTime=0;
  //fEnergy->Clear("C");
  //fTime->Clear("C");
  fAnalyzed=kFALSE;
}

//_____________________________________________________________________________
 void TCaloBlock::Reset(void)
{
  fNPulse=0;
  fBase=0;
  fEnergy->Delete();
  fTime->Delete();
  fChi2->Delete();
    fAnalyzed=kFALSE;
//    fNPulse=0;
//    fEnergy->Clear("C");
//    fTime->Clear("C");

 //   fNPulse=0;
//    fEnergy->Clear();
//    fTime->Clear();

}
//_____________________________________________________________________________
 void TCaloBlock::Copy(TObject& obj)
{

  // Copy routine. Used by copy ctor.

  //  TObject::Copy(obj);
  
  //  fgParameters.Copy(((TCaloBase&)obj).fgParameters);
  //  ((TCaloBase&)obj).fgIsInit = fgIsInit;

}


//_____________________________________________________________________________
void TCaloBlock::SetChi2(Double_t chi2)
{
  TClonesArray &chi2s = *fChi2;
  new (chi2s[0]) TDouble(chi2);
}


//_____________________________________________________________________________
 void TCaloBlock::AddPulse(Float_t energy, Float_t time)
{
  //  if (!fEnergy) fEnergy=new TFloatArray();
  //    if (!fTime) fTime=new TFloatArray();
  TClonesArray &energies = *fEnergy;
  new (energies[fNPulse]) TFloat(energy);
  TClonesArray &times = *fTime;
  new (times[fNPulse]) TFloat(time);
 //   fEnergy->SetValue(fNPulse,energy);
//    fTime->SetValue(fNPulse,time);
  
  fNPulse++;
  fAnalyzed=kTRUE;
}

//_____________________________________________________________________________
 TCaloBlock::~TCaloBlock()
{
  // Default destructor
  //  cout<<"TCaloBlock destructor"<<endl;
  if (fEnergy) {
    fEnergy->Delete();
    delete fEnergy;
    fEnergy=0;
  }
  if (fTime) {
    fTime->Delete();
    delete fTime;
    fTime=0;
  }
  fNPulse=0;
}

//_____________________________________________________________________________
 void TCaloBlock::Print(char* opt)
{
  // Output on screen
//    cout<<"Energy : "<<endl;
//    if (fEnergy) fEnergy->Print();
//    cout<<endl<<"Time : "<<endl;
//    if (fTime) fTime->Print();
//    cout<<endl;

//    cout<<"Block energy = "<<fEnergy<<endl;
//    cout<<"Block number = "<<fBlockNb<<endl;
}













