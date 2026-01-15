//
// TCaloTrigger.cxx, v1.0, Thu Jan  30 14:42:50
// Author: C. Munoz Camacho
//

#include <iostream>
#include <fstream>

#ifndef __TCaloTrigger__
#include "TCaloTrigger.h"
#endif

#include "TBool.h"

using namespace std;

ClassImp(TCaloTrigger)

////////////////////////////////////////////////////////////////////////////////
//
// Calorimeter Trigger Class
//
// It contains the ADC values from ARS's
// 
////////////////////////////////////////////////////////////////////////////////
Bool_t           TCaloTrigger::fgIsInit = kFALSE;
TClonesArray    *TCaloTrigger::fgADCValue=0; 
TClonesArray    *TCaloTrigger::fgTowerBit=0; 

//_____________________________________________________________________________
 TCaloTrigger::TCaloTrigger()
{
  // Default constructor
  // cout<<"TCaloTrigger constructor"<<endl;
  if (!fgADCValue) fgADCValue = new TClonesArray("TBool",fgGeometry.GetNBlocks());
  if (!fgTowerBit) fgTowerBit = new TClonesArray("TBool",fgGeometry.GetNBlocks()-fgGeometry.GetNX()-fgGeometry.GetNY());
  fADCValue=fgADCValue;
  fTowerBit=fgTowerBit;
  fgIsInit = kFALSE;
  fHCalo=0;

  // cout<<fNbBlocks<<endl;
}

//_____________________________________________________________________________
 TCaloTrigger::TCaloTrigger(const TCaloTrigger& TCalotrigger)
{
  // Copy constructor
  // ((TCaloTrigger&)TCalotrigger).Copy(*this);
}

//_____________________________________________________________________________
 void TCaloTrigger::Copy(TObject& obj)
{
  // Copy routine. Used by copy ctor.

  //  TObject::Copy(obj);

  //  fgParameters.Copy(((TCaloBase&)obj).fgParameters);
  //  ((TCaloBase&)obj).fgIsInit = fgIsInit;

}
/*
//_____________________________________________________________________________
 void TCaloTrigger::SetADCValue(Short_t val[fgGeometry.GetNBlocks()])
{
  //Comments

  for(Int_t i=0;i<fgGeometry.GetNBlocks();i++) fADCValue[i]=val[i];
  
}
*/

//_____________________________________________________________________________
 void TCaloTrigger::SetADCValue(Int_t nb, Float_t val)
{
  //Sets ADC value of block nb with value val.

  TClonesArray &adc = *fADCValue;
  new(adc[nb]) TFloat(val);
  
}

// //_____________________________________________________________________________
 void TCaloTrigger::SetTowerBit(Int_t nb, Bool_t val)
{
  //Sets block bit number nb with value val.

  TClonesArray &tourbit = *fTowerBit;
  new(tourbit[nb]) TBool(val);
  
}

//_____________________________________________________________________________
 Float_t TCaloTrigger::GetADCValue(Int_t nb)
{
  //Returns the ADC value of block nb.

  TFloat* adc=(TFloat*)fADCValue->UncheckedAt(nb);
  return adc->GetValue();
  
}

//_____________________________________________________________________________
 Bool_t TCaloTrigger::GetTowerBit(Int_t nb)
{
  //Returns the bit of block nb.

  TBool* bit=(TBool*)fTowerBit->UncheckedAt(nb);
  return bit->GetValue();
  
}

//_____________________________________________________________________________
 void TCaloTrigger::Clear(char* opt)
{
  //Clears the TClonesArray of ADC values.

  fADCValue->Clear("C");
  //  fBlockBit->Clear("C");
  //   cout<<"avant clear hcalo de trigger"<<endl;
  if(fHCalo) fHCalo->Clear();

}

//_____________________________________________________________________________
 TCaloTrigger::~TCaloTrigger()
{
  // Default destructor
  cout<<"TCaloTrigger destructor"<<endl;
  fADCValue->Delete();
  delete fHCalo;

  //if(fADCValue) fADCValue=0;
}

//_____________________________________________________________________________
 void TCaloTrigger::Init(void)
{
  //Does nothing for the moment.

  //  char arsfile[]="initdata/ars.txt";
  if (fgIsInit==kFALSE){
    //    ifstream inifile(arsfile);
    //    for(Int_t i=0;i<nbchanels;i++){
    //    inifile>>wave[i];
    // }
  }
}

//_____________________________________________________________________________
 void TCaloTrigger::Display(TPad *display, Float_t HistMax, Float_t BlockThreshold, char* opt)
{
  cout<<"INIT"<<endl;
  if (!fHCalo) {
    fHCalo=new THCalo(display,HistMax);
  }else{
    fHCalo->Clear();
    fHCalo->SetPad(display);
  }
  fHCalo->SetMax(HistMax);

  //if (!fHCalo) fHCalo=new THCalo();
  //Data filling
  for(Int_t k=0;k<fgGeometry.GetNBlocks();k++){
    //    TCaloBlock* block = (TCaloBlock*)fCaloBlocks->UncheckedAt(k);
    //    if (block->GetBlockEnergy()>BlockThreshold) {
    fHCalo->SetBinContent(Int_t(k/fgGeometry.GetNY()+0.5)+1,Int_t(k%fgGeometry.GetNY()+0.5)+1,GetADCValue(k));
    //block->GetBlockEnergy()*1000.);
      //}
  }
  cout<<"Starting drawing..."<<endl;
  fHCalo->Draw(opt);
  cout<<"Drawing done!"<<endl;
}

//_____________________________________________________________________________
 void TCaloTrigger::Print(char* opt)
{
  // Prints out ADC values for each block.

  cout<<"  ADC Values : "<<endl;
  cout<<"___________________________________________"<<endl;
  for(Int_t i=0;i<fgGeometry.GetNBlocks();i++) {
    TFloat* adc=(TFloat*)fADCValue->UncheckedAt(i);
    cout<<"Block number : "<<i<<"    ADC : "<<adc->GetValue()<<endl;
  }
  cout<<"___________________________________________"<<endl;

}
//_____________________________________________________________________________
 int TCaloTrigger::Decode(int * buf)
{
  TriggerEv *trigev=(TriggerEv *) &buf[1];
  if (buf[0]==0xfade)
    {
      //First threshold
      Int_t cp=0;
      for(Int_t j=0;j<7*32-1;j++)
	{
	  if (cp==44 || cp==88 || cp==132) j+=20;
	  if (cp==143) j+=21;
	  Int_t val=trigev->THit1[j/32]>>j&0x1;
	  //	htrig->SetBinContent((cp+1)/13+1,(cp+1)%13+1,val);
	  if (cp<=143) SetTowerBit(cp,val);
	  cp++;
// 	  if ((j%32)==0) cout << " ---------- \n " << endl;
// 	  cout<<"block = "<<j<<" "<<cp<<"  value = "<<val<<endl;
	}
      //Second threshold
      cp=0;
      for(Int_t j=0;j<7*32-1;j++)
	{
	  if (cp==44 || cp==88 || cp==132) j+=20;
	  if (cp==143) j+=21;
	  Int_t val=trigev->THit2[j/32]>>j&0x1;
	  if (cp<=143) SetTowerBit(cp,val);
	  cp++;
	  
	}
      //	      index+=92;
      for(Int_t j=0;j<132;j++) 
	//fTrigger->SetADCValue((j%12)*11+j/12,trigev->PMT[j]);
	SetADCValue(j,(trigev->PMT[j]&0x7f));
     // increase the pointer of the right length of the event
      return 93;
    }
  else return 0;
}














