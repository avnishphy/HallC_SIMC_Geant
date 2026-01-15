//
// TDoubleArray.cxx, v1.0, Thu Dec  5 14:42:50
// Author: C. Mu�oz Camacho
//
#include <cstdlib>
#include <cassert>

#include "TDoubleArray.h"
#include "TRandom.h"

using namespace std;

ClassImp(TDoubleArray)

  Int_t TDoubleArray::fNumber=0;
//  int TDoubleArray::fNumero=0;

//_____________________________________________________________________________
TDoubleArray::TDoubleArray()
{
  //  cout << "Construct " << ClassName() << "   " << this << endl;
  Init();
  //  cout << "Finished constructor" << endl;
}

//_____________________________________________________________________________
TDoubleArray::TDoubleArray(Int_t length)
{
  //  cout << "Construct " << ClassName() << " len=" << length << "   " << this << endl;
  Init(length);
  //  cout << "Finished constructor" << endl;
}

//_____________________________________________________________________________
void TDoubleArray::Clear()
{
  //  cout << "Clearing " << ClassName() << "   " <<  this << endl;
#ifndef DOUBLE_WITH_CLONESARRAY
  memset(fDarray, 0, fN*sizeof(*fDarray));
  fN=0;
#else
#endif
  //  fData->Clear("C");
}

//_____________________________________________________________________________
TDoubleArray::TDoubleArray(int length,Double_t * data)
{
  //  cout << "Construct " << ClassName() << " len=" << length << " with data  " << this << endl;
  fHisto=0; fCanvas=0;
  //fLength=length;meters.so"); gSystem->Load("libTCaloTrigger.so"); gSystem->Load("libTDoubleArray
  fNumber++;
  
  Init(length);
  for (int i=0; i<length; i++) {
    SetValue(i,data[i]);
  }
  
  //  fData = new TClonesArray("TDouble",length);
  //  for (int i=0;i<length;i++){ 
  //    new((*fData)[i]) TDouble(data[i]);
  //  }
  //  cout << "Finished constructor" << endl;
}

//_____________________________________________________________________________
TDoubleArray::TDoubleArray(const TDoubleArray & copy) : fHisto(0), fCanvas(0)
{
  //  cout << "Copy Construct " << ClassName() << "   " << this << " from " << &copy << endl;
#ifndef DOUBLE_WITH_CLONESARRAY
  fSz = copy.fN;
  fDarray = new Double_t[fSz];
  fN=copy.fN;
  memcpy(fDarray,copy.fDarray,fN*(sizeof(*fDarray)));
#else
  fData = new TClonesArray(copy.fData->GetClass());
  for (UInt_t i=0; i<=copy.fData->GetLast(); i++) {
    TDouble *d = (TDouble*)copy.fData->UncheckedAt(i);
    if (d)
      SetValue(i,d->GetValue());
    else
      SetValue(i,-99999.);
  }
#endif
  
  /*fData->ExpandCreate(fLength);
    for (UInt_t i=0;i<fLength;i++)
     {
       Double_t * val=(Double_t *)(copy.fData->UncheckedAt(i));
       SetValue(i,*val);
       }
   */
  //  cout << "Finished constructor" << endl;
}


//_____________________________________________________________________________
void TDoubleArray::Draw(const char* opt="")
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
//        TDouble * v = (TDouble *) fData->UncheckedAt(i);
//        //cout<<"Draw "<<i<<endl;
//        if (v)
//  	fHisto->Fill(i,v->GetValue());
//      }
//    //cout<<"Draw 3"<<endl;
//    fHisto->Draw(opt); 
}

//_____________________________________________________________________________
//  Double_t TDoubleArray::SetLength(UInt_t l)
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
void TDoubleArray::RandomFill(UInt_t seed, Double_t max)
{
  TRandom ran(seed);

#ifndef DOUBLE_WITH_CLONESARRAY
  Int_t length=fN;
#else
  Int_t length=fData->GetLast()+1;
#endif
  
  for (int i=0; i<length; i++) {
    SetValue(i,ran.Uniform(max));
  }
//   for(Int_t i=0;i<fData->GetLast();i++){
//     Double_t val=ran.Uniform(max);
//     SetValue(i,val);
//   }

}

//_____________________________________________________________________________
Double_t TDoubleArray::GetIntegral(Int_t nmin, Int_t nmax)
{
  //Returns the sum of the bin contents between bin number nmin
  //and bin number nmax. If these parameters are not specified, it loops over
  //the whole array.

  Double_t val=0;
#ifndef DOUBLE_WITH_CLONESARRAY
  Int_t maxcnt = fN;
#else
  Int_t maxcnt = fData->GetLast()+1;
#endif

  if (nmax==-1) nmax=maxcnt;
  if (nmax>maxcnt) nmax=maxcnt;
  if (nmin<0 || nmin>nmax) {
     cout<<"ERROR : Check limits of TDoubleArray : "<<this<<endl;
     assert(0);
     exit(1);
   }
  for (int i=nmin; i<nmax; i++) {
#ifndef DOUBLE_WITH_CLONESARRAY
    val+=fDarray[i];
#else
    TDouble* v=(TDouble*)fData->UncheckedAt(i);
    val+=v->GetValue();
#endif    
  }
//   if(nmax==-1) nmax=fData->GetLast()+1;
//   if(nmin<0 || nmin>fData->GetLast() || nmax>fData->GetLast()+1){
//     cout<<"ERROR : Check limits of TDoubleArray : "<<this<<endl;
//     exit(1);
//   }
//   for(Int_t i=nmin;i<nmax;i++){
//     TDouble* v=(TDouble*)fData->UncheckedAt(i);
//     val+=v->GetValue();
//   }
  return val;
}

//_____________________________________________________________________________
Int_t TDoubleArray::GetMinimumBin(Int_t nmin, Int_t nmax)
{
  //Returns the number of the bin with a minimum content between bin number nmin
  //and bin number nmax. If these parameters are not specified, it loops over
  //the whole array.
  
  Int_t min=0; 
  Double_t val;

#ifndef DOUBLE_WITH_CLONESARRAY
  Int_t maxcnt = fN;
#else
  Int_t maxcnt = fData->GetLast()+1;
#endif

  if (nmax==-1) nmax=maxcnt;
  if (nmax>maxcnt) nmax=maxcnt;
  if (nmin<0 || nmin>nmax) {
     cout<<"ERROR : Check limits of TDoubleArray : "<<this<<endl;
     assert(0);
     exit(1);
   }
  for (int i=nmin; i<nmax; i++) {
#ifndef DOUBLE_WITH_CLONESARRAY
    if (i==nmin) {
      val=fDarray[i]; min=i;
    }
    if (fDarray[i]<val) {
      val=fDarray[i]; min=i;
    }
#else
    TDouble* v=(TDouble*)fData->UncheckedAt(i);
    if(i==0) val=v->GetValue();
    if(v->GetValue()<val) {
      val=v->GetValue();
      min=i;
    }
#endif
  }
//   if(nmax==-1) nmax=fData->GetLast()+1;
//   if(nmin<0 || nmin>fData->GetLast() || nmax>fData->GetLast()+1){
//     cout<<"ERROR : Check limits of TDoubleArray : "<<this<<endl;
//     exit(1);
//   }
//   for(Int_t i=nmin;i<nmax;i++){
//     TDouble* v=(TDouble*)fData->UncheckedAt(i);
//     if(i==0) val=v->GetValue();
//     if(v->GetValue()<val) {
//       val=v->GetValue();
//       min=i;
//     }
//   }
  return min;
}


//_____________________________________________________________________________
Int_t TDoubleArray::GetMaximumBin(Int_t nmin, Int_t nmax)
{
  //Returns the number of the bin with a maximum content between bin number nmin
  //and bin number nmax. If these parameters are not specified, it loops over
  //the whole array.

  Int_t max=0; 
  Double_t val;

#ifndef DOUBLE_WITH_CLONESARRAY
  Int_t maxcnt = fN;
#else
  Int_t maxcnt = fData->GetLast()+1;
#endif

  if (nmax==-1) nmax=maxcnt;
  if (nmax>maxcnt) nmax=maxcnt;
  if (nmin<0 || nmin>nmax) {
     cout<<"ERROR : Check limits of TDoubleArray : "<<this<<endl;
     assert(0);
     exit(1);
   }
  for (int i=nmin; i<nmax; i++) {
#ifndef DOUBLE_WITH_CLONESARRAY
    if (i==nmin) {
      val=fDarray[i]; max=i;
    }
    if (fDarray[i]>val) {
      val=fDarray[i]; max=i;
    }
#else
    TDouble* v=(TDouble*)fData->UncheckedAt(i);
    if(i==0) val=v->GetValue();
    if(v->GetValue()>val) {
      val=v->GetValue();
      max=i;
    }
#endif
  }

//   if(nmax==-1) nmax=fData->GetLast()+1;
//   if(nmin<0 || nmin>fData->GetLast() || nmax>fData->GetLast()+1){
//     cout<<"ERROR : Check limits of TDoubleArray : "<<this<<endl;
//     exit(1);
//   }
//   for(Int_t i=nmin;i<nmax;i++){
//     TDouble* v=(TDouble*)fData->UncheckedAt(i);
//     if(i==0) val=v->GetValue();
//     if(v->GetValue()>val) {
//       val=v->GetValue();
//       max=i;
//     }
//   }
  return max;
}

//_____________________________________________________________________________
void TDoubleArray::Draw(TPad * pad, Float_t min, Float_t max, const char* opt)
{
  //   Draws a display of the TDoubleArray in a TH1F.
  //If a pointer to a pad is provided it is display in that pad. Otherwise
  //it is display in its own TCanvas (which will be created if it does not
  //exist yet).

  if (!pad) {
    if(!fCanvas) fCanvas=new TCanvas();  
    pad=fCanvas;
  }
#ifndef DOUBLE_WITH_CLONESARRAY
  Int_t length=fN;
  length=128;
#else
  Int_t length=fData->GetLast()+1;
#endif
  
  if (fHisto==0){
      TString name("Doublearray");
      name+=(Int_t)(gRandom->Rndm()*10000);
      fHisto = new TH1F(name.Data(),"DoubleArray Display",length,0,length);
    }
  fHisto->Reset();
  if(max!=-10000 || min!=-10000){
    fHisto->SetMinimum(min);
    fHisto->SetMaximum(max);
  }
  for (int i=0;i<length;i++) {
#ifndef DOUBLE_WITH_CLONESARRAY
    fHisto->Fill(i,fDarray[i]);
#else
    TDouble * v = (TDouble *) fData->UncheckedAt(i);
    if (v) fHisto->Fill(i,v->GetValue());
#endif
  }
  //  pad->cd();
  fHisto->Draw(opt);
  pad->Update();
  pad->Modified();
}

//_____________________________________________________________________________
TDoubleArray & TDoubleArray::operator = (const TDoubleArray & copy)
{
  //  cout << "Assignment " << ClassName() << endl;
  if (&copy!=this){
#ifndef DOUBLE_WITH_CLONESARRAY
    if (fSz<copy.fN) {
      delete [] fDarray;
      fSz=copy.fN;
      fDarray = new Double_t[fSz];
    }
    fN=copy.fN;
    memcpy(fDarray,copy.fDarray,fN*(sizeof(*(copy.fDarray))));
#else
    //fData->ExpandCreateFast(fLength);
    for (int i=0;i<=copy.fData->GetLast();i++){
      Double_t * val=(Double_t *)(copy.fData->UncheckedAt(i));
      SetValue(i,*val);
    }
#endif
  }

  fHisto=copy.fHisto;
  fCanvas=copy.fCanvas;
  //  cout << "Finished " << ClassName() << endl;
  return (*this);
}

//_____________________________________________________________________________
Double_t & TDoubleArray::operator [] (UInt_t n)
{
  //  if (n<fLength)
  return GetValue(n);
}

//_____________________________________________________________________________
Double_t TDoubleArray::AddValue(Double_t val)
{ // simplify
#ifndef DOUBLE_WITH_CLONESARRAY
  Int_t i=fN-1;
#else
  Int_t i=fData->GetLast();
#endif
  return SetValue(i+1,val);

//   TClonesArray &data = *fData;
//   if (i>=fData->GetSize()) {
//     fData->Expand(i+100);
//   }
//   new(data[i]) TDouble(val); 

//   return val;

/*
//   if (fData->GetEntries()<fLength)
//      {
//        if ((*fData)[fData->GetEntries()])
//  	new((*fData)[fData->GetEntries()]) TDouble(val);
//        else
//  	((TDouble *)(*fData)[fData->GetEntries()])->SetValue(val);
	  
//      }
//    else 
//      cout<<"Array already full "<<endl;
//    return(fData->GetEntries());
*/
}

//_____________________________________________________________________________
Double_t TDoubleArray::SetValue(UInt_t n,Double_t val)
{
  //  TDouble * v = (TDouble *) fData->UncheckedAt(n);
  //  if (!v) {
  
#ifndef DOUBLE_WITH_CLONESARRAY
  if (n>=fSz) {
    fSz += 10;
    Double_t *tmp = new Double_t[fSz];
    memcpy(tmp,fDarray,fN*(sizeof(*fDarray)));
    delete [] fDarray;
    fDarray = tmp;
  }
  fDarray[n] = val;
  fN = (n>=fN ? n+1 : fN);
#else
  if(n>fData->GetLast()){
    TClonesArray &data = *fData;
    if (n>=fData->GetSize()) fData->Expand(n+100);
    new(data[n]) TDouble(val); 
  }  else {
    TDouble * v = (TDouble *) fData->UncheckedAt(n);
    v->SetValue(val);
  }
#endif
  return val ;
}

//_____________________________________________________________________________
Double_t & TDoubleArray::GetValue(UInt_t n)
{
  static Double_t zero=0; // must be persistent since returning a reference
#ifndef DOUBLE_WITH_CLONESARRAY
  if (n<fN) 
    return fDarray[n];
#else
  if(n<=fData->GetLast()){
    TDouble * v = (TDouble *) fData->UncheckedAt(n);
    if (v) return v->GetValue();
  }
#endif
  return zero;

//   else{
//     TDouble v(0.);   // won't work -- goes out of scope before return
//     return v.GetValue();
//   }
}

//_____________________________________________________________________________
void TDoubleArray::Print ()
{
#ifndef DOUBLE_WITH_CLONESARRAY
  cout << "Array length : " << fN << endl;
  for (int n=0; n<fN; n++) {
    cout << fDarray[n] << " ";
  }
#else

  Int_t length=fData->GetLast()+1;
  cout<<"Array length : "<<length<<endl;
  for (int n=0;n<length;n++){
    TDouble * v = (TDouble *) fData->UncheckedAt(n);
    if(v) cout<<v->GetValue()<<" ";
  }
#endif
  cout<<endl;
}

//_____________________________________________________________________________
TDoubleArray::~TDoubleArray()
{
  //  cout <<"Destroying " << ClassName() << "  " << this << endl;
  if (fHisto) delete fHisto;
  if (fCanvas) delete fCanvas;

#ifndef DOUBLE_WITH_CLONESARRAY
  delete [] fDarray;
#else
  fData->Delete();
  delete fData;
  fData=0;
#endif
  
  fNumber--;
}

//_____________________________________________________________________________
void TDoubleArray::Init(Int_t length)
{
  fHisto=0;
  fCanvas=0;
  fNumber++;

#ifndef DOUBLE_WITH_CLONESARRAY
  fSz = length;
  fN = 0;
  fDarray = new Double_t[fSz];
  fN = fSz;
  memset(fDarray, 0, fN*sizeof(*fDarray));
#else
  fData = new TClonesArray("TDouble",length); 
  fData->BypassStreamer(kFALSE);
  for (int i=0;i<length;i++){
    TClonesArray &data = *fData;
    new(data[i]) TDouble();      
  }
#endif
}


Double_t  TDoubleArray::FindValue(Double_t thres)
    {
      Int_t lim=128;
#ifndef DOUBLE_WITH_CLONESARRAY
      if (fN>lim) lim=fN;
#else
      if (fData->GetLast()>=lim) lim=fData->GetLast()+1;
#endif
      Int_t good=1;
      int i=0;
//       while ((i<128)&&(good))
      while ((i<lim)&&(good))
	{
	  good = GetValue(i)>thres;
// 	  TDouble * value;
// 	  value=(TDouble *)fData->At(i);
// 	  good=value->GetValue()>thres;
	  i++;
	}
      if (i<lim)
	return i-1;
      else
	return -1;
    }

Int_t TDoubleArray::Minimum(Int_t & pos)
{
  Int_t p,i;

  p = GetMinimumBin();
  pos = p;

#ifndef DOUBLE_WITH_CLONESARRAY
  Int_t length=fN;
#else
  Int_t length=fData->GetLast()+1;
#endif
  if (pos<length) return GetValue(pos);
  return 0;

//   Double_t min= ((TDouble *)fData->At(0))->GetValue();
//   for (i=1;i<128;i++)
//     {
//       if (((TDouble *)fData->At(i))->GetValue()<min)
// 	{
// 	min=((TDouble *)fData->At(i))->GetValue();
// 	p=i;
// 	}
//     }
//   pos=p;
//   return min;
}


Int_t TDoubleArray::Minimum()
{
  int pos;
  return Minimum(pos);
}
