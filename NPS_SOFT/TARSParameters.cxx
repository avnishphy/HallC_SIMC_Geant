#include "TARSParameters.h"

ClassImp(TARSParameters)
  //////////////////////////////////////////////////////////////////////
  //                 Class TARSParameters 
  // 
//BEGIN_HTML
/*
</pre>
<P>
<H2><A NAME=H2Basic-concepts-of-MINUIT.html>Parameters to be computed</A></H2>
<P>
The <A HREF=allcases/index.html> Minimizations cases </A>
<P>
*/
//END_HTML
  // since indexes are positive in C++
  // index = fSize equivalent to time 0
  // index = 0 equivalent to time -fSize
  // index = fSize equivalent to time +fSize
  // somme sums are needed and can be computed all in one pass
  // sum of the translated shape
  // sum of product of two tranlasted shape
  /////////////////////////////////////////////////////////////////////

TARSParameters::TARSParameters()
{
  //default constructor 
  // 128 samples by default
  fSize =128;
  Init();
  //Compute();
}

TARSParameters::TARSParameters(UInt_t size)
{
  //constructor with size defined
  fSize =size;
  Init();
  //  Compute();
}

TARSParameters::TARSParameters(UInt_t size,Double_t * shape)
{
  fSize = size;
  Init();
  //  Compute();
}


TARSParameters::TARSParameters(const TARSParameters & copy)
{
  //copy constructor
  fSize = copy.fSize;
  Init();// create pointers
  for(Int_t k=0; k<2*fSize ; k++)// copy reference shape
    {
      for(Int_t kprim=0; kprim<2*fSize ; kprim++)
	{
	  (*fShape2)(k,kprim)=(*(copy.fShape2))(k,kprim);
	}
    }
  //  Compute();
}



TARSParameters::~TARSParameters()
{
  delete fBase;
  delete fShape;
  delete fSum;
  delete fShape2;
}

void TARSParameters::Init()
{
  //cout<<"Init TARSParameters"<<endl;
  // pointers initializations
  // pedestal
    fBase = new TDoubleArray(fSize);
  //  cout<<"base"<<endl;
  //fShape = new TDoubleArray(3*fSize);// waveform centered in [128,256] allows computing after the shape
  // cout<<"shape"<<endl;
  //fSum = new TDoubleArray(2*fSize);// fSum[t]=sum (k=0,k=fSize) Shape(k-t)
  //cout<<"sum"<<endl;
  //fShape2 = new TMatrixD (2*fSize,2*fSize);//fShape2(i,j) =(k=0,k=fSize) Shape(k-i)Shape(k-j)
    //  SetShape("shape.dat");
  SetPedestal("base.dat");
}

void TARSParameters::Compute()
{

 fMatrix1 = new TClonesArray("TMatrixD",2*fSize);// inverted matrixes 
 fMatrix2 = new TClonesArray("TMatrixD",4*fSize*fSize);// inverted matrixes
  for (int i=0;i<4*fSize*fSize;i++)
    {
      //  cout<<i<<endl;
      TMatrixD * mat = new ((*fMatrix1)[i]) TMatrixD(2,2);
      mat = new ((*fMatrix2)[i]) TMatrixD(3,3);
    //  mat->Print();
    }
  // for the 2 pulses case
  // two sums are needed  
  // compute the sums needed to do  the minimization
  // fSum(i) i in  [0,2fSize] : sum_{k=0}^{k=fSize} Shape(k-i)
  // 
  // cout<<"sum "<<endl;
  for(Int_t k=0; k<2*fSize ; k++)
    {
      (*fSum)[k]=0.;
      //cout<<"sum "<<" "<<k<<" "<<(*fSum)[k]<<endl;
      for(Int_t nu=0; nu<fSize ; nu++)
	{
       // cout<<"sum "<<nu<<" "<<k<<" "<<(*fSum)[k]<<" "<<(*fShape)[nu+k]<<endl;
	  (*fSum)[k]+=(*fShape)[nu+k]; 
	  }
    }
  //cout<<"shape2"<<endl;
  
// fShape(i,j) i and j in [0,2fSize] : sum_{k=0}^{k=fSize} Shape(k-i) Shape(k-j)
  // fShape2->Print();
  for(Int_t k=0; k<2*fSize ; k++)
    {
      for(Int_t kprim=0; kprim<2*fSize ; kprim++)
	{
	  //  cout<<kprim<<endl;
	   (*fShape2)(k,kprim)=0.;
	  for(Int_t nu=0; nu<fSize ; nu++)
	    {
	      // cout<<"shape2"<<nu<<endl;
	       (*fShape2)(k,kprim)+=fShape->GetValue(nu+k)*fShape->GetValue(nu+kprim);
	    }
	}
    }
  //Matrix to invert to solve the system for 1 pulse and background
  //Matrix are symetric, numbering is followeing over diagonal numbering
  // 0 1          2   ...      fSize-1
  //   (n/fSize)*(n/fSize-1)+1  ...        2*fSize-1
  //             
  //(*Shape2)(i,i)   (*Shape2)(i,j)    (*fSum)[i] | a1 |   |sum (A_i*S(i-t1) |
  //(*Shape2)(i,j)   (*fSum)[j]        (*fSum)[j] | a2 | = |sum (A_i*S(i-t2)  |
  //(*fSum)[i];      (*fSum)[j];       fSize      |  b |   |sum (A_i)  |
 
 for (int i=0;i<(2*fSize);i++)
    {
      TMatrixD * matrix = (TMatrixD *) (*fMatrix1)[i];
      (*matrix)(0,0)=(*fShape2)(i,i);
      (*matrix)(1,0)=(*fSum)[i];
      (*matrix)(0,1)=(*fSum)[i];
      (*matrix)(1,1)=fSize;
      //matrix->Print();
      if (matrix->Determinant()!=0)
	matrix->Invert();
      else
	{
	  cout<<"Matrix " <<i<<" is singular"<<endl;
	}
    }
  //Matrix to invert to solve the system
  //Matrix are symetric, numbering is followeing over diagonal numbering
  // 0 1          2   ...      fSize-1
  //   (n/fSize)*(n/fSize-1)+1  ...        2*fSize-1
  //             
  //(*Shape2)(i,i)   (*Shape2)(i,j)    (*fSum)[i] | a1 |   |sum (A_i*S(i-t1) |
  //(*Shape2)(i,j)   (*fSum)[j]        (*fSum)[j] | a2 | = |sum (A_i*S(i-t2)  |
  //(*fSum)[i];      (*fSum)[j];       fSize      |  b |   |sum (A_i)  |
 
 for (int i=0;i<(2*fSize);i++)
    {
      for (int j=i;j<(2*fSize);j++)
	{ 
	  TMatrixD * matrix = (TMatrixD *) (*fMatrix2)[i*fSize+j];
	  
	  (*matrix)(0,0)=(*fShape2)(i,i);
	  (*matrix)(1,0)=(*fShape2)(i,j);
	  (*matrix)(2,0)=(*fSum)[i];
	  (*matrix)(0,1)=(*fShape2)(i,j);
	  (*matrix)(1,1)=(*fSum)[j];
	  (*matrix)(2,1)=(*fSum)[j];
	  (*matrix)(0,2)=(*fSum)[i];
	  (*matrix)(1,2)=(*fSum)[j]; 
	  (*matrix)(2,2)=fSize;
	  //matrix->Print();
	  if (matrix->Determinant()!=0)
	  matrix->Invert();
	  else
	    {
	      cout<<"Matrix " <<i<<" "<<j<<" is singular"<<endl;
	    }
	}
    }
}

TMatrixD * TARSParameters::GetMatrix1(Int_t i)
{
    return  (TMatrixD *)(*fMatrix1)[i];
}

TMatrixD * TARSParameters::GetMatrix2(Int_t i,Int_t j)
{
  // return inverted matrix corresponding to time i and time j
  if (i<=j)
    return  (TMatrixD *)(*fMatrix2)[i*fSize+j];
  else
     return  (TMatrixD *)(*fMatrix2)[j*fSize+i];
}
	 
 void TARSParameters::SetShape(const char* name )
{
  Double_t r;
  ifstream input(name);
  for (int i=0;i<fSize;i++)
    {
      input>>r;
      fShape->SetValue(i+fSize,r);
      //cout<<r<<" "<<(*fShape)[i+fSize]<<endl;
    }
}


void TARSParameters::SetPedestal(const char* name )
{
  // load pedestal file
   Double_t r;
  ifstream input(name);
  for (int i=0;i<fSize;i++)
    {
      input>>r;
      fBase->SetValue(i+fSize,r);
      //cout<<r<<" "<<(*fBase)[i]<<endl;
    }
}

void TARSParameters::SetPedestal(TProfile * prof )
{
  // load pedestal file
  for (int i=0;i<fSize;i++)
    {
      fBase->SetValue(i+fSize,prof->GetBinContent(i+1));
      //cout<<" "<<(*fBase)[i]<<endl;
    }
}


Double_t TARSParameters::GetBase(int n)
{
  //return sample n from the base
  return ((*fBase)[n]);
}

Double_t TARSParameters::GetShape(int n)
{
//return sample n from the shape
  return ((*fShape)[n]);
}

Double_t TARSParameters::GetShape2(Int_t n,Int_t m)
{
//return sample n from the shape
  return ((*fShape2)(n,m));
}


Double_t TARSParameters::GetSum(int n)
{
//return sum translated in time by n nanoseconds
  return ((*fSum)[n]);
}


void TARSParameters::Print()
{
  cout<<"Base line"<<endl;
  fBase->Print();
 cout<<"Shape"<<endl;
 fShape->Print();
 cout<<"Sum"<<endl;
 fSum->Print();

}

void TARSParameters::PrintShape2()
{
  cout<<"Shape2"<<endl;
  fShape2->Print();
}

void TARSParameters::PrintShape()
{
  cout<<"Shape"<<endl;
  fShape->Print();
}


