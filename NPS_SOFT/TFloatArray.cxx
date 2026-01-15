//
// TFloatArray.cxx, v1.0, Thu Dec  5 14:42:50
// Author: C. Mu�oz Camacho
//

#ifndef __TFloatArray__
#include "TFloatArray.h"
#endif

#ifndef ROOT_TRandom
#include "TRandom.h"
#endif

ClassImp(TFloatArray)

  int TFloatArray::fNumber=0;
//  int TFloatArray::fNumero=0;

//_____________________________________________________________________________
TFloatArray::TFloatArray()
{
  Init(1);
}

//_____________________________________________________________________________
TFloatArray::TFloatArray(Int_t length)
{
  Init(length);
}

//_____________________________________________________________________________
void TFloatArray::Clear()
{
  fData->Clear("C");
}

//_____________________________________________________________________________
TFloatArray::TFloatArray(int length,Float_t * data)
{
  fHisto=0;
  //fLength=length;
  //fNumber++;
  if (!fData) fData = new TClonesArray("TFloat",length);
  for (int i=0;i<length;i++){ 
    TClonesArray &data = *fData;
    new(data[i]) TFloat(*((Float_t*)data[i]));      
  }
}

//_____________________________________________________________________________
TFloatArray::TFloatArray(const TFloatArray & copy)
{
  fHisto=0;
  fCanvas=0;
  fData=new TClonesArray(*((TClonesArray*)copy.fData));
}

//_____________________________________________________________________________
void TFloatArray::Draw(const char* opt="")
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
//        TFloat * v = (TFloat *) fData->UncheckedAt(i);
//        //cout<<"Draw "<<i<<endl;
//        if (v)
//  	fHisto->Fill(i,v->GetValue());
//      }
//    //cout<<"Draw 3"<<endl;
//    fHisto->Draw(opt); 
}

//_____________________________________________________________________________
//  Float_t TFloatArray::SetLength(UInt_t l)
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
void TFloatArray::RandomFill(UInt_t seed, Float_t max)
{
  TRandom ran(seed);

  for(Int_t i=0;i<fData->GetLast();i++){
    Float_t val=ran.Uniform(max);
    SetValue(i,val);
  }

}

//_____________________________________________________________________________
Float_t TFloatArray::GetIntegral(void)
{
  Float_t val=0;
  for(Int_t i=0;i<fData->GetLast();i++){
    TFloat* v=(TFloat*)fData->UncheckedAt(i);
    val+=v->GetValue();
  }
  return val;
}

//_____________________________________________________________________________
Int_t TFloatArray::GetMinimumBin(void)
{
  Int_t min=0; 
  Float_t val;
  for(Int_t i=0;i<fData->GetLast();i++){
    TFloat* v=(TFloat*)fData->UncheckedAt(i);
    if(i==0) val=v->GetValue();
    if(v->GetValue()<val) {
      val=v->GetValue();
      min=i;
    }
  }
  return min;
}


//_____________________________________________________________________________
Int_t TFloatArray::GetMaximumBin(void)
{
  Int_t max=0; 
  Float_t val;
  for(Int_t i=0;i<fData->GetLast();i++){
    TFloat* v=(TFloat*)fData->UncheckedAt(i);
    if(i==0) val=v->GetValue();
    if(v->GetValue()>val) {
      val=v->GetValue();
      max=i;
    }
  }
  return max;
}

//_____________________________________________________________________________
void TFloatArray::Draw(TPad * pad)
{
  //   Draws a display of the TFloatArray in a TH1F.
  //If a pointer to a pad is provided it is display in that pad. Otherwise
  //it is display in its own TCanvas (which will be created if it does not
  //exist yet).

  if (!pad) {
    if(!fCanvas) fCanvas=new TCanvas();  
    pad=fCanvas;
  }
  Int_t length=fData->GetLast();
  if (fHisto==0){
      TString name("Floatarray");
      name+=fNumber++;
      fHisto = new TH1F(name.Data(),"FloatArray Display",length,0,length);
    }
  fHisto->Reset();
  for (int i=0;i<length;i++){
    TFloat * v = (TFloat *) fData->UncheckedAt(i);
    if (v) fHisto->Fill(i,v->GetValue());
  }
  pad->cd();
  fHisto->Draw();
  pad->Update();
  pad->Modified();
}

//_____________________________________________________________________________
TFloatArray & TFloatArray::operator = (const TFloatArray & copy)
{
  if (&copy!=this){
    //      fLength=copy.fLength;
    //fData->ExpandCreateFast(fLength);
    for (int i=0;i<fData->GetLast();i++){
      Float_t * val=(Float_t *)(copy.fData->UncheckedAt(i));
      SetValue(i,*val);
    }
  }
  return (*this);
}

//_____________________________________________________________________________
Float_t & TFloatArray::operator [] (UInt_t n)
{
  //  if (n<fLength)
  return GetValue(n);
}

//_____________________________________________________________________________
Float_t TFloatArray::AddValue(Float_t val)
{
  Int_t i=fData->GetLast();
  TClonesArray &data = *fData;
  new(data[i]) TFloat(val); 

  return val;
  
//   if (fData->GetEntries()<fLength)
//      {
//        if ((*fData)[fData->GetEntries()])
//  	new((*fData)[fData->GetEntries()]) TFloat(val);
//        else
//  	((TFloat *)(*fData)[fData->GetEntries()])->SetValue(val);
	  
//      }
//    else 
//      cout<<"Array already full "<<endl;
//    return(fData->GetEntries());

}

//_____________________________________________________________________________
Float_t TFloatArray::SetValue(UInt_t n,Float_t val)
{
    TFloat * v = (TFloat *) fData->UncheckedAt(n);
    if (!v) {
      TClonesArray &data = *fData;
      new(data[n]) TFloat(val); 
    }else{
      v->SetValue(val);
    }
    return val ;
}

//_____________________________________________________________________________
Float_t & TFloatArray::GetValue(UInt_t n)
{
  TFloat * v = (TFloat *) fData->UncheckedAt(n);
  return v->GetValue();
}

//_____________________________________________________________________________
void TFloatArray::Print ()
{
  Int_t length=fData->GetLast();
  cout<<"Array length : "<<length<<endl;
  for (int n=0;n<length;n++){
    TFloat * v = (TFloat *) fData->UncheckedAt(n);
    if(v) cout<<v->GetValue()<<" ";
  }
  cout<<endl;
}

//_____________________________________________________________________________
TFloatArray::~TFloatArray()
{
  if (fHisto) delete fHisto;
  if (fCanvas) delete fCanvas;
  fData->Delete();
  delete fData;
  fData=0;
  //fNumber--;
}

//_____________________________________________________________________________
void TFloatArray::Init(Int_t length=1)
{
  fHisto=0;
  fCanvas=0;
  //  fNumber++;
  fData = new TClonesArray("TFloat",length); 
  fData->BypassStreamer(kFALSE);
  for (int i=0;i<length;i++){
    TClonesArray &data = *fData;
    new(data[i]) TFloat();      
  }
}



























