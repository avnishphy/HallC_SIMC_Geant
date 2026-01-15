//
// TShortArray.cxx, v1.0, Thu Dec  5 14:42:50
// Author: C. Mu�oz Camacho
//

#ifndef __TShortArray__
#include "TShortArray.h"
#endif

#ifndef ROOT_TRandom
#include "TRandom.h"
#endif

ClassImp(TShortArray)

  int TShortArray::fNumber=0;
//  int TShortArray::fNumero=0;

//_____________________________________________________________________________
TShortArray::TShortArray()
{
  Init(1);
}

//_____________________________________________________________________________
TShortArray::TShortArray(Int_t length)
{
  Init(length);
}

//_____________________________________________________________________________
void TShortArray::Clear()
{
  fData->Clear("C");
}

//_____________________________________________________________________________
TShortArray::TShortArray(int length,Short_t * data)
{
  fHisto=0;
  //fLength=length;
  //fNumber++;
  if (!fData) fData = new TClonesArray("TShort",length);
  for (int i=0;i<length;i++){ 
    TClonesArray &data = *fData;
    new(data[i]) TShort(*((Short_t*)data[i]));      
  }
}

//_____________________________________________________________________________
TShortArray::TShortArray(const TShortArray & copy)
{
  //fLength=copy.fLength;
//    fData = new TClonesArray("TShort",fLength);
//    fData->ExpandCreate(fLength);
//    for (UInt_t i=0;i<fLength;i++)
//      {
//        Short_t * val=(Short_t *)(copy.fData->UncheckedAt(i));
//        SetValue(i,*val);
//      }

}

//_____________________________________________________________________________
void TShortArray::Draw(const char* opt="")
{
  TPad* pad=0;
  Draw(pad);

   //cout<<"Draw 1"<<endl;
//    Int_t length=fData->GetLast();
//    if (fHisto==0)
//      {
//        //cout<<"Draw hist "<<endl;
//        TString name("Data");
//        name+=fNumber++;
//        fHisto = new TH1F(name.Data(),name.Data(),length,0,length);
//      }
//    fHisto->Reset();
//    //cout<<"Draw 2"<<endl;
//    for (int i=0;i<length;i++)
//      {
//        TShort * v = (TShort *) fData->UncheckedAt(i);
//        //cout<<"Draw "<<i<<endl;
//        if (v)
//  	fHisto->Fill(i,v->GetValue());
//      }
//    //cout<<"Draw 3"<<endl;
//    fHisto->Draw(opt); 
}

//_____________________________________________________________________________
//  Short_t TShortArray::SetLength(UInt_t l)
//  {
//    fLength=l;
//    fData->ExpandCreateFast(fLength);
//    if (fHisto)
//      {
//        fHisto->Delete();
//        TString name("Data");
//        name+=fNumero++;
//        fHisto = new TH1F(name.Data(),name.Data(),fLength,0,fLength);
//      }
//    return fLength;
//  }

//_____________________________________________________________________________
void TShortArray::RandomFill(UInt_t seed, Short_t max)
{
  TRandom ran(seed);

  for(Int_t i=0;i<fData->GetLast();i++){
    Short_t val=ran.Uniform(max);
    SetValue(i,val);
  }

}

//_____________________________________________________________________________
Short_t TShortArray::GetIntegral(void)
{
  Short_t val=0;
  for(Int_t i=0;i<fData->GetLast();i++){
    TShort* v=(TShort*)fData->UncheckedAt(i);
    val+=v->GetValue();
  }
  return val;
}

//_____________________________________________________________________________
Int_t TShortArray::GetMinimumBin(void)
{
  Int_t min=0; 
  Short_t val;
  for(Int_t i=0;i<fData->GetLast();i++){
    TShort* v=(TShort*)fData->UncheckedAt(i);
    if(i==0) val=v->GetValue();
    if(v->GetValue()<val) {
      val=v->GetValue();
      min=i;
    }
  }
  return min;
}


//_____________________________________________________________________________
Int_t TShortArray::GetMaximumBin(void)
{
  Int_t max=0; 
  Short_t val;
  for(Int_t i=0;i<fData->GetLast();i++){
    TShort* v=(TShort*)fData->UncheckedAt(i);
    if(i==0) val=v->GetValue();
    if(v->GetValue()>val) {
      val=v->GetValue();
      max=i;
    }
  }
  return max;
}

//_____________________________________________________________________________
void TShortArray::Draw(TPad * pad)
{
  //   Draws a display of the TShortArray in a TH1F.
  //If a pointer to a pad is provided it is display in that pad. Otherwise
  //it is display in its own TCanvas (which will be created if it does not
  //exist yet).

  if (!pad) {
    if(!fCanvas) fCanvas=new TCanvas();  
    pad=fCanvas;
  }
  Int_t length=fData->GetLast();
  if (fHisto==0){
      TString name("Shortarray");
      name+=fNumber++;
      fHisto = new TH1F(name.Data(),"ShortArray Display",length,0,length);
    }
  fHisto->Reset();
  for (int i=0;i<length;i++){
    TShort * v = (TShort *) fData->UncheckedAt(i);
    if (v) fHisto->Fill(i,v->GetValue());
  }
  pad->cd();
  fHisto->Draw();
  pad->Update();
  pad->Modified();
}

//_____________________________________________________________________________
TShortArray & TShortArray::operator = (const TShortArray & copy)
{
  if (&copy!=this){
    //      fLength=copy.fLength;
    //fData->ExpandCreateFast(fLength);
    for (int i=0;i<fData->GetLast();i++){
      Short_t * val=(Short_t *)(copy.fData->UncheckedAt(i));
      SetValue(i,*val);
    }
  }
  return (*this);
}

//_____________________________________________________________________________
Short_t & TShortArray::operator [] (UInt_t n)
{
  //  if (n<fLength)
  return GetValue(n);
}

//_____________________________________________________________________________
Short_t TShortArray::AddValue(Short_t val)
{
  Int_t i=fData->GetLast();
  TClonesArray &data = *fData;
  new(data[i]) TShort(val); 

  return val;
  
//   if (fData->GetEntries()<fLength)
//      {
//        if ((*fData)[fData->GetEntries()])
//  	new((*fData)[fData->GetEntries()]) TShort(val);
//        else
//  	((TShort *)(*fData)[fData->GetEntries()])->SetValue(val);
	  
//      }
//    else 
//      cout<<"Array already full "<<endl;
//    return(fData->GetEntries());

}

//_____________________________________________________________________________
Short_t TShortArray::SetValue(UInt_t n,Short_t val)
{
    TShort * v = (TShort *) fData->UncheckedAt(n);
    if (!v) {
      TClonesArray &data = *fData;
      new(data[n]) TShort(val); 
    }else{
      v->SetValue(val);
    }
    return val ;
}

//_____________________________________________________________________________
Short_t & TShortArray::GetValue(UInt_t n)
{
  TShort * v = (TShort *) fData->UncheckedAt(n);
  return v->GetValue();
}

//_____________________________________________________________________________
void TShortArray::Print ()
{
  Int_t length=fData->GetLast();
  cout<<"Array length : "<<length<<endl;
  for (int n=0;n<length;n++){
    TShort * v = (TShort *) fData->UncheckedAt(n);
    if(v) cout<<v->GetValue()<<" ";
  }
  cout<<endl;
}

//_____________________________________________________________________________
TShortArray::~TShortArray()
{
  if (fHisto) delete fHisto;
  if (fCanvas) delete fCanvas;
  fData->Delete();
  delete fData;
  fData=0;
  //fNumber--;
}

//_____________________________________________________________________________
void TShortArray::Init(Int_t length=1)
{
  fHisto=0;
  fCanvas=0;
  //  fNumber++;
  fData = new TClonesArray("TShort",length); 
  fData->BypassStreamer(kFALSE);
  for (int i=0;i<length;i++){
    TClonesArray &data = *fData;
    new(data[i]) TShort();      
  }
}







