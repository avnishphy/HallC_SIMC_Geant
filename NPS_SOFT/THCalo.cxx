//
// THCalo.cxx, v1.0, Thu Feb  2 14:42:50
// Author: C. Munoz Camacho
//

#include <iostream>

#ifndef __THCalo__
#include "THCalo.h"
#endif

#ifndef ROOT_TStyle
#include "TStyle.h"
#endif

ClassImp(THCalo)

////////////////////////////////////////////////////////////////////////////////
//
// Proton Array Histogram Class
//
//
// 
////////////////////////////////////////////////////////////////////////////////

  Int_t THCalo::fNumber=0;

//_____________________________________________________________________________
 THCalo::THCalo(Float_t max)
{
  // Default constructor.

  // TCanvas d;
  
  if(!fgIsInit) Init();

  fMax=max;
  fNumber++;

  TString name=("HCalo");
  name+=fNumber;
  
  h=new TH2F(name.Data(),"Calo Histogram",fgGeometry.GetNX(),0,fgGeometry.GetNX(),fgGeometry.GetNY(),0,fgGeometry.GetNY());
 
  InitDisplay();

  fCanvas=0;
  fMin=0;

  cout<<"THCalo constructor"<<endl;
}
//_____________________________________________________________________________
 THCalo::THCalo(TPad* canvas, Float_t max)
{
  // Constructor pointing to a certain canvas.

  if(!fgIsInit) Init();

  fMax=max;
  fNumber++;

  TString name=("HCalo");
  name+=fNumber;
  
  h=new TH2F(name.Data(),"Calo Histogram",fgGeometry.GetNX(),0,fgGeometry.GetNX(),fgGeometry.GetNY(),0,fgGeometry.GetNY());

  InitDisplay();

  fCanvas=canvas;
  cout<<"THCalo constructor in a pad"<<endl;

}

//_____________________________________________________________________________
 void THCalo::InitDisplay(void)
{

  Float_t ***x,***y;
  fPolyLine=new TPolyLine ** [fgGeometry.GetNX()];
  x=new Float_t**[fgGeometry.GetNX()];
  y=new Float_t**[fgGeometry.GetNX()];

  for(Int_t i=0;i<fgGeometry.GetNX();i++) {
    fPolyLine[i]=new TPolyLine * [fgGeometry.GetNY()];
    x[i]=new Float_t*[fgGeometry.GetNY()];
    y[i]=new Float_t*[fgGeometry.GetNY()];
  }
    
  fText=new TText* [fgGeometry.GetNY()*fgGeometry.GetNX()];
  for(Int_t i=0;i<fgGeometry.GetNX();i++) {
    for(Int_t j=0;j<fgGeometry.GetNY();j++) {
      Float_t xl=0.05+i*(0.9/fgGeometry.GetNX())+(0.9/fgGeometry.GetNX())*0.5;
      Float_t yl=0.05+j*(0.9/fgGeometry.GetNY())+(0.9/fgGeometry.GetNY())*0.5;

      x[i][j]=new Float_t[5];y[i][j]=new Float_t[5];      
      Float_t k[5]={0.05+i*(0.9/fgGeometry.GetNX()),0.05+(i+1)*(0.9/fgGeometry.GetNX()),0.05+(i+1)*(0.9/fgGeometry.GetNX()),0.05+i*(0.9/fgGeometry.GetNX()),0.05+i*(0.9/fgGeometry.GetNX())};
      Float_t kk[5]={0.05+j*(0.9/fgGeometry.GetNY()),0.05+j*(0.9/fgGeometry.GetNY()),0.05+(j+1)*(0.9/fgGeometry.GetNY()),0.05+(j+1)*(0.9/fgGeometry.GetNY()),0.05+j*(0.9/fgGeometry.GetNY())};
      for(Int_t jk=0;jk<5;jk++){
	x[i][j][jk]=k[jk];
	y[i][j][jk]=kk[jk];
      }
      fPolyLine[i][j]=new TPolyLine(5,x[i][j],y[i][j]);
      fPolyLine[i][j]->SetLineWidth(1);
      fText[j*fgGeometry.GetNY()+i] = new TText();
      fText[j*fgGeometry.GetNY()+i]->SetTextFont(40);
      fText[j*fgGeometry.GetNY()+i]->SetTextSize(0.05);
      fText[j*fgGeometry.GetNY()+i]->SetTextColor(kBlack);
      fText[j*fgGeometry.GetNY()+i]->SetTextAlign(22);
      fText[j*fgGeometry.GetNY()+i]->SetX(xl);
      fText[j*fgGeometry.GetNY()+i]->SetY(yl);
    }
  }

  //I don't know why the hell we must tell it again:
  Float_t xt[5]={0.05,0.05+0.9/fgGeometry.GetNX(),0.05+0.9/fgGeometry.GetNX(),0.05,0.05};
  Float_t yt[5]={0.05,0.05,0.05+0.9/fgGeometry.GetNY(),0.05+0.9/fgGeometry.GetNY(),0.05};
  fPolyLine[0][0]=new TPolyLine(5,xt,yt);

}

//_____________________________________________________________________________
 THCalo::THCalo(const THCalo& shortval)
{
  // Copy constructor
  //  fValue = shortval.fValue;
}

//_____________________________________________________________________________
 void THCalo::SetBinContent(Int_t x, Int_t y, Float_t val)
{
  //
  h->SetBinContent(x,y,val);
}

//_____________________________________________________________________________
 void THCalo::Clear(void)
{
  //
   for(Int_t i=0;i<fgGeometry.GetNX();i++) {
     for(Int_t j=0;j<fgGeometry.GetNY();j++) {
       //       if(fPolyLine[i][j]){
	 fPolyLine[i][j]->SetFillColor(kWhite);
	 fPolyLine[i][j]->Draw("f");
	 UnHighlightBin(i,j);
	 //       }
       h->SetBinContent(i+1,j+1,0.);
       fText[j*fgGeometry.GetNY()+i]->Clear();
      }
   }
}

//_____________________________________________________________________________
 void THCalo::Update(void)
{
  //
  fCanvas->SetEditable(kTRUE);
  fCanvas->Update();
  fCanvas->Modified();
  fCanvas->SetEditable(kFALSE);

}
//_____________________________________________________________________________
 void THCalo::HighlightBin(Int_t tower, Int_t ring)
{
  //
  fPolyLine[tower][ring]->SetLineColor(kRed);
  fPolyLine[tower][ring]->SetLineWidth(3);
//   fCanvas->SetEditable(kTRUE);
//   fCanvas->Update();
//   fCanvas->Modified();
//   fCanvas->SetEditable(kFALSE);

}

//_____________________________________________________________________________
 void THCalo::UnHighlightBin(Int_t tower, Int_t ring)
{
  //
  fPolyLine[tower][ring]->SetLineColor(kBlack);
  fPolyLine[tower][ring]->SetLineWidth(1);
  //fCanvas->SetEditable(kTRUE);
  //  fCanvas->Update();
  //  fCanvas->Modified();
  //fCanvas->SetEditable(kFALSE);

}

//_____________________________________________________________________________
 void THCalo::Draw(const char* opt)
{
  //Draw the THCalo. Two options are supported : "colz" and "text".
  //Default option is "colztext"

  gStyle->SetPalette(1);
  TString option=opt;

  if(!fCanvas) fCanvas=new TCanvas();
  if(fCanvas) fCanvas->cd();
  fCanvas->SetEditable(kTRUE);

  Int_t ncolors = gStyle->GetNumberOfColors();
  Int_t ndiv = gStyle->GetNumberContours();
  Double_t dz = ((h->GetMaximum() - fMin)*1.01);//*1000.;  
  if(fMax!=-1) dz=(fMax-fMin)*1.01;//*1000.;
  //  if(HistMax!=-1) dz=HistMax*1.01;
  Int_t ndivz  = TMath::Abs(ndiv);
  Double_t scale = ndivz/dz;
  for(Int_t i=0;i<fgGeometry.GetNX();i++) {
    for(Int_t j=0;j<fgGeometry.GetNY();j++) {
      //We calculate the color of the crown according to the histo content
      Int_t color=Int_t(0.01+(h->GetBinContent(i+1,j+1)-fMin)*scale);
      Int_t theColor = Int_t((color+0.99)*Float_t(ncolors)/Float_t(ndivz));
      if(h->GetBinContent(i+1,j+1)>0. && option.Contains("colz")) {
	fPolyLine[i][j]->SetFillColor(gStyle->GetColorPalette(theColor));//Setting color
      }else{
	fPolyLine[i][j]->SetFillColor(kWhite);//Background color
      }
      fPolyLine[i][j]->Draw("f");
      fPolyLine[i][j]->Draw();
    }
  }
  if(option.Contains("force")) InitDisplay();
  //The text
  if(option.Contains("text")){
    for(Int_t i=0;i<fgGeometry.GetNX();i++) {
      for(Int_t j=0;j<fgGeometry.GetNY();j++) {
	char t1[50];
	Int_t cont=Int_t(h->GetBinContent(i+1,j+1));
	sprintf(t1,"%i",cont);
	if(h->GetBinContent(i+1,j+1)>0) {
	  fText[j*fgGeometry.GetNY()+i]->SetTitle("tiit");
	  fText[j*fgGeometry.GetNY()+i]->SetTitle(t1);
	  fText[j*fgGeometry.GetNY()+i]->Draw();
	}
      }
    }
  }
  //The text
  if(option.Contains("blocknumbers")){
    for(Int_t i=0;i<fgGeometry.GetNX();i++) {
      for(Int_t j=0;j<fgGeometry.GetNY();j++) {
	char t1[50];
	//	Int_t cont=Int_t(h->GetBinContent(i+1,j+1));
	Int_t cont=j+i*fgGeometry.GetNY();
	sprintf(t1,"%i",cont);
	if(h->GetBinContent(i+1,j+1)>0) {
	  fText[j*fgGeometry.GetNY()+i]->SetTitle(t1);
	  fText[j*fgGeometry.GetNY()+i]->Draw();
	}
      }
    }
  }
  fCanvas->Update();
  fCanvas->Modified();

  //  HighlightBin(3,3);

  fCanvas->SetEditable(kFALSE);


}

//_____________________________________________________________________________
 THCalo::~THCalo()
{
  // Default destructor
  cout<<"THCalo destructor"<<endl;
  //The following line crashes... apparently histograms are owned by gDirectory
  //and not the user (p. 107 User's Guide).
  //  if (h) delete h; 

  //We choose not to delete the canvas just in case it is not owned by the 
  //object, i.e. THCalo is created via the THCalo::THCalo(TCanvas*) constructor.
  //  delete fCanvas;

  for(Int_t i=0;i<fgGeometry.GetNX();i++) {
    for(Int_t j=0;j<fgGeometry.GetNY();j++) {
      //Why the next lines generates a crash is also a mystery...
      //This is the cause of a small memory leak when display clusters out 
      //of a TCaloEvent.

//        delete fPolyLine[i][j];
//        if(fText[j*fgGeometry.GetNY()+i]) delete fText[j*fgGeometry.GetNY()+i];
    } 
  }
}













