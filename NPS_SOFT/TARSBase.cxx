//
// TCaloBase.cxx, v1.0, Thu Sep 12 11:13:57
// Author: F. Sabatie
//

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "TARSBase.h"
#include "TDVCSDB.h"
#ifndef ROOT_TSQLServer
#include <TSQLServer.h>
#endif
#ifndef ROOT_TSQLResult
#include <TSQLResult.h>
#endif
#ifndef ROOT_TSQLRow
#include <TSQLRow.h>
#endif

ClassImp(TARSBase)

////////////////////////////////////////////////////////////////////////////////
//
// DVCS ARS base class
// 
////////////////////////////////////////////////////////////////////////////////
  
UInt_t           TARSBase::fgSize=128;
Int_t            TARSBase::fNbChanels=-1;
UInt_t           TARSBase::fNbChannelsCalo=0;
UInt_t           TARSBase::fNbChannelsPA=0;
UInt_t           TARSBase::fNbChannelsVeto=0;
UInt_t           TARSBase::fNbChannels=0;
Int_t            TARSBase::fNbSamples=-1;
Int_t            TARSBase::fksp=-1;
Int_t            TARSBase::fkled=-1;
Int_t            TARSBase::fk1=-1;
Int_t            TARSBase::fk2=-1;
Int_t*            TARSBase::fmin=0;
Int_t*            TARSBase::fmax=0;
Int_t            TARSBase::fk1max=-1;
Int_t            TARSBase::fk1max2=-1;
Int_t            TARSBase::fk2max=-1;
Int_t            TARSBase::fk1min=-1;
Int_t            TARSBase::fk1min2=-1;
Int_t            TARSBase::fk2min=-1;
Int_t            TARSBase::fgk1max=-1;
Int_t            TARSBase::fgk1max2=-1;
Int_t            TARSBase::fgk2max=-1;
Int_t            TARSBase::fgk1min=-1;
Int_t            TARSBase::fgk1min2=-1;
Int_t            TARSBase::fgk2min=-1;
Double_t*         TARSBase::fchi20=0;
Double_t*         TARSBase::fchi21=0;
Double_t*         TARSBase::fchi22=0;
Bool_t           TARSBase::fgWarnings = kTRUE;
Bool_t           TARSBase::fgErrors = kTRUE;
Bool_t           TARSBase::fgIsInit = kFALSE;
TARSParameters*  TARSBase::fgARSParameters=0 ;//Shape analysis parameters
TARSConst*       TARSBase::fgARSConst=0;//Shape analysis constants
TARSCalibration* TARSBase::fgARSCalib=0;//Calibration constants
TClonesArray*    TARSBase::fgRefShapes=0;
TClonesArray*    TARSBase::fgRefShapesLED=0;
TMatrixD***      TARSBase::fgM1=0;
TMatrixD****     TARSBase::fgM2=0;
TMatrixD***      TARSBase::fgM1LED=0;
Double_t**       TARSBase::fgpedsigma2=0;
Double_t*        TARSBase::fnval1=0;
Double_t*        TARSBase::fnval2=0;
Double_t**       TARSBase::fgRunningwei=0;
Bool_t           TARSBase::fgRunningIsInit=kFALSE;
Bool_t           TARSBase::fgIsInitShapeAnalysisBase=kFALSE;
Bool_t           TARSBase::fgCaloWF=kTRUE;
Bool_t           TARSBase::fgPAWF=kTRUE;
Bool_t           TARSBase::fgVetoWF=kTRUE;
Bool_t           TARSBase::fgbfixed=kFALSE;
Int_t*            TARSBase::fgReso=0;
Int_t            TARSBase::fminfixed=0;
Int_t            TARSBase::fmaxfixed=0;
Int_t            TARSBase::fminacc=0;
Int_t            TARSBase::fmaxacc=0;
Int_t*           TARSBase::fgminref=0;
//_____________________________________________________________________________
 TARSBase::TARSBase(Int_t nbchannels)
{
  //
  fNbChannels=nbchannels;
  if(!fgIsInit) Init();
  fgIsInit = kTRUE;
  // Default constructor
  //  gTARSBase = this;
}

//_____________________________________________________________________________
 TARSBase::TARSBase(const TARSBase& TARSbase)
{
  // Copy constructor
  //((TARSBase&)TARSbase).Copy(*this);
}

//  //_____________________________________________________________________________
//   void TARSBase::Copy(TARSBase & obj)
//  {
//    // Copy routine. Used by copy ctor.

//  //    TObject::Copy(obj);

//  //    fgParameters.Copy(((TARSBase&)obj).fgParameters);
//  //    ((TARSBase&)obj).fgIsInit = fgIsInit;

//  }

//_____________________________________________________________________________
void TARSBase::InitAnalysisWindowDB(Int_t* min, Int_t* max, Int_t run)
{
  Int_t cp=0;
  if(!fmin) fmin=new Int_t[fNbChannels];
  if(!fmax) fmax=new Int_t[fNbChannels];
  TDVCSDB *db=new TDVCSDB("dvcs","clrlpc.jlab.org",3306,"munoz","");
  if(fgCaloWF){
    Float_t *val=db->GetEntry_f("CALO_calib_ARSTimeOffset",run);
    for(Int_t i=0;i<fNbChannelsCalo;i++){
      fmin[cp]=TMath::Max(Int_t(min[cp]-val[i]+0.5),0);
      fmax[cp]=TMath::Min(Int_t(max[cp]-val[i]+0.5),128);
      cp++;
    }
  delete val;
  }
  if(fgPAWF){
    Float_t *val=db->GetEntry_f("PA_calib_ARSTimeOffset",run);
    for(Int_t i=0;i<fNbChannelsPA;i++){
      fmin[cp]=TMath::Max(Int_t(min[cp]-val[i]+0.5),0);
      fmax[cp]=TMath::Min(Int_t(max[cp]-val[i]+0.5),128);
      cp++;
    }
  delete val;
  }
  if(fgVetoWF){
    Float_t *val=db->GetEntry_f("VETO_calib_ARSTimeOffset",run);
    for(Int_t i=0;i<fNbChannelsVeto;i++){
      fmin[cp]=TMath::Max(Int_t(min[cp]-val[i]+0.5),0);
      fmax[cp]=TMath::Min(Int_t(max[cp]-val[i]+0.5),128);
      cp++;
    }
  delete val;
  }
  delete db;
}

//_____________________________________________________________________________
 TARSBase::~TARSBase()
{
  // Default destructor
}

//____________________________________________________________________________                                                                                                                                
void TARSBase::ActivateOnly(const char* opt)
{

  TString option=opt;
  if(!option.Contains("CALO")) fgCaloWF=kFALSE;
  if(!option.Contains("PA")) fgPAWF=kFALSE;
  if(!option.Contains("Veto")) fgVetoWF=kFALSE;

}

//____________________________________________________________________________
void TARSBase::InitShapeAnalysis(const char* opt)
{
  //It initializes all shape analysis parameters (all matrices...)
  
  cout<<"Initializing all shape analysis parameters... Please wait..."<<endl;
  Double_t dum=0;
  TString option=opt;
  TString arsfile(getenv("NPS_SOFT"));
  arsfile+="/initdata/arsbase.txt";
  ifstream inifile(arsfile.Data());
  inifile>>dum;
  inifile>>fNbChannelsCalo;
  inifile>>fNbChannelsPA;
  inifile>>fNbChannelsVeto;
  inifile>>fNbSamples;
  inifile>>dum;
  inifile>>dum;
  inifile>>dum;
  inifile>>fksp;

  fNbChannels=0;
  if(fgCaloWF) fNbChannels+=132; if(fgPAWF) fNbChannels+=100; if(fgVetoWF) fNbChannels+=57;
  
  TDVCSDB *db=new TDVCSDB("dvcs","clrlpc.jlab.org",3306,"munoz","");
  Int_t* valmin=new Int_t[fNbChannels];
  Int_t* valmax=new Int_t[fNbChannels];
  for(Int_t i=0;i<fNbChannels;i++) {valmin[i]=0;valmax[i]=128;}
  InitAnalysisWindowDB(valmin,valmax,4000);
  delete valmin; delete valmax;
  if(!fchi20) fchi20=new Double_t[fNbChannels];
  if(!fchi21) fchi21=new Double_t[fNbChannels];
  if(!fchi22) fchi22=new Double_t[fNbChannels];

  //if(fNbChannels==-1) 
//     fNbChannels=dum;

//     fNbChannels=0;
//    if(fgCaloWF) fNbChannels+=132; if(fgPAWF) fNbChannels+=100; if(fgVetoWF) fNbChannels+=57;


  TString arsfile2(getenv("NPS_SOFT"));
  arsfile2+="/initdata/refshape.txt";
  ifstream refshape(arsfile2.Data());
  if(option.Contains("data")){
    fk1=7;
    fk1min=-127;
    fk1max=80;
    fk1min2=fksp-3;
    fk1max2=fksp+3;
    fk2=128+80;
    fk2min=-127;
    fk2max=80;
  }
  
  InitPedSigma();

  //  cout<<"Pedestals should be initialized"<<endl;
  
  Double_t val=0.;
  
  fgM1=new TMatrixD**[fNbChannels];
  fgM2=new TMatrixD***[fNbChannels];
  
  if(!fnval1) fnval1=new Double_t[4];
  if(!fnval2) fnval2=new Double_t[9];
  
  for(Int_t ii1=0;ii1<4;ii1++) fnval1[ii1]=0.;
  for(Int_t ii1=0;ii1<9;ii1++) fnval2[ii1]=0.;
  
  fgRefShapes=new TClonesArray("TDoubleArray",fNbChannels);
  TClonesArray &shapes=*fgRefShapes;
  for(Int_t i=0;i<fNbChannels;i++){
    fgM1[i]=new TMatrixD*[2*fNbSamples+1];
    fgM2[i]=new TMatrixD**[2*fNbSamples+1];
    TDoubleArray *shaperef=new(shapes[i]) TDoubleArray(fNbSamples);
    for(Int_t j=0;j<fNbSamples;j++){
      refshape>>val;
      shaperef->SetValue(j,-val);
    }
    for(Int_t k=0;k<2*fNbSamples+1;k++) {
      fgM2[i][k]=new TMatrixD*[2*fNbSamples+1];
      for(Int_t j=0;j<2*fNbSamples+1;j++) fgM2[i][k][j]=0;
      fgM1[i][k]=0;
    }
  }
  SetFirstWindow(fk1min,fk1max,"data");
  SetSecondWindow(fk1min2,fk1max2,fk2min,fk2max,"data");
  fgIsInitShapeAnalysisBase=kTRUE;
}

//____________________________________________________________________________
void TARSBase::InitShapeAnalysisDB(Int_t run, const char* opt)
{
  //It initializes all shape analysis parameters (all matrices...)

  if(!fgIsInitShapeAnalysisBase) InitShapeAnalysis(opt);
  TString option=opt;

  fNbChannels=0;
  if(fgCaloWF) fNbChannels+=132; if(fgPAWF) fNbChannels+=100; if(fgVetoWF) fNbChannels+=57;
  InitPedSigmaDB(run);
 
  if(!fgReso) fgReso=new Int_t[fNbChannels];
  if(!fgminref) fgminref=new Int_t[fNbChannels];

  Int_t *valmin=new Int_t[fNbChannels]; Int_t *valmax=new Int_t[fNbChannels]; Int_t *reso=new Int_t[fNbChannels];

  TDVCSDB *db=new TDVCSDB("dvcs","clrlpc.jlab.org",3306,"munoz","");

  Int_t cp2=0;
  for(Int_t i=0;i<fNbChannelsCalo+fNbChannelsPA+fNbChannelsVeto;i++){
    
    if((i<fNbChannelsCalo && fgCaloWF) || (i<(fNbChannelsCalo+fNbChannelsPA)&&i>(fNbChannelsCalo-1)&&fgPAWF) || (i>(fNbChannelsCalo+fNbChannelsPA-1)&&fgVetoWF)){
      if(i<fNbChannelsCalo){
	Int_t vmin=db->GetEntry_i("CALO_calib_WFAnaWinMin",run,0);
	Int_t vmax=db->GetEntry_i("CALO_calib_WFAnaWinMax",run,0);
	Int_t reso1=db->GetEntry_i("CALO_calib_WFReso",run,i);
	valmin[cp2]=vmin; valmax[cp2]=vmax; reso[cp2]=reso1;
      }
      if(i<(fNbChannelsCalo+fNbChannelsPA)&&i>(fNbChannelsCalo-1)){
	Int_t vmin=db->GetEntry_i("PA_calib_WFAnaWinMin",run,0);
	Int_t vmax=db->GetEntry_i("PA_calib_WFAnaWinMax",run,0);
	Int_t reso2=db->GetEntry_i("PA_calib_WFReso",run,i-fNbChannelsCalo);
	valmin[cp2]=vmin; valmax[cp2]=vmax; reso[cp2]=reso2;
      }
      if(i>(fNbChannelsCalo+fNbChannelsPA-1)&&i<(fNbChannelsCalo+fNbChannelsPA+fNbChannelsVeto)){
	Int_t vmin=db->GetEntry_i("VETO_calib_WFAnaWinMin",run,0);
	Int_t vmax=db->GetEntry_i("VETO_calib_WFAnaWinMax",run,0);
	Int_t reso3=db->GetEntry_i("VETO_calib_WFReso",run,i-fNbChannelsCalo-fNbChannelsPA);
	valmin[cp2]=vmin;valmax[cp2]=vmax; reso[cp2]=reso3;
      }
      cp2++;
    }
  }
   
  InitAnalysisWindowDB(valmin,valmax,run);
  if(fminfixed!=0||fmaxfixed!=0) {
    for(Int_t i=0;i<fNbChannels;i++) {fmin[i]=fminfixed; fmax[i]=fmaxfixed;}
  }
  //For accidentals... Use method SetAnalysisWindowAcc
  if(fminacc!=0||fmaxacc!=0) {
    for(Int_t i=0;i<fNbChannels;i++) {valmin[i]=fminacc; valmax[i]=fmaxacc;}
  }
  InitAnalysisWindowDB(valmin,valmax,run);

  for(Int_t i=0;i<fNbChannels;i++) fgReso[i]=reso[i];
  delete valmin; delete valmax; delete reso;
  TDoubleArray *refshape=0;

  Int_t cp=0;

  for(Int_t i=0;i<fNbChannelsCalo+fNbChannelsPA+fNbChannelsVeto;i++){
    
    if((i<fNbChannelsCalo && fgCaloWF) || (i<(fNbChannelsCalo+fNbChannelsPA)&&i>(fNbChannelsCalo-1)&&fgPAWF) || (i>(fNbChannelsCalo+fNbChannelsPA-1)&&fgVetoWF)){

      if(option.Contains("data")) refshape=(TDoubleArray*)fgRefShapes->UncheckedAt(cp);
      if(option.Contains("LED")) refshape=(TDoubleArray*)fgRefShapesLED->UncheckedAt(cp);
      Float_t *coef=0;
      
      if(i<fNbChannelsCalo){
	fchi20[cp]=db->GetEntry_d("CALO_calib_WFChi20",run,i);
	fchi21[cp]=db->GetEntry_d("CALO_calib_WFChi21",run,i);
	fchi22[cp]=db->GetEntry_d("CALO_calib_WFChi22",run,i);
	TString name("CALO_calib_ARSRefShape");name+=i;
	coef=db->GetEntry_f(name.Data(),run);
      }
      if(i<(fNbChannelsCalo+fNbChannelsPA)&&i>(fNbChannelsCalo-1)){
	fchi20[cp]=db->GetEntry_d("PA_calib_WFChi20",run,i-fNbChannelsCalo);
	fchi21[cp]=db->GetEntry_d("PA_calib_WFChi21",run,i-fNbChannelsCalo);
	fchi22[cp]=db->GetEntry_d("PA_calib_WFChi22",run,i-fNbChannelsCalo);
	TString name("PA_calib_ARSRefShape");name+=i-fNbChannelsCalo;
	coef=db->GetEntry_f(name.Data(),run);
      }
      if(i>(fNbChannelsCalo+fNbChannelsPA-1)&&i<(fNbChannelsCalo+fNbChannelsPA+fNbChannelsVeto)){
	fchi20[cp]=db->GetEntry_d("VETO_calib_WFChi20",run,i-fNbChannelsCalo-fNbChannelsPA);
	fchi21[cp]=db->GetEntry_d("VETO_calib_WFChi21",run,i-fNbChannelsCalo-fNbChannelsPA);
	fchi22[cp]=db->GetEntry_d("VETO_calib_WFChi22",run,i-fNbChannelsCalo-fNbChannelsPA);
	TString name("VETO_calib_ARSRefShape");name+=i-fNbChannelsCalo-fNbChannelsPA;
	coef=db->GetEntry_f(name.Data(),run);
      }
      
      for(Int_t j=0;j<fNbSamples;j++) refshape->SetValue(j,-coef[j]);
      fgminref[cp]=refshape->GetMinimumBin(10,118);

      delete coef;
      if(option.Contains("data")){
	for(Int_t ii=fgk1min;ii<fgk1max+1;ii++) InitMatrix1(fgM1[cp],ii,cp,opt,kTRUE);    
	
	for(Int_t k=fgk1min2;k<fgk1max2+1;k++) {
	  for(Int_t j=fgk2min;j<fgk2max+1;j++) InitMatrix2(fgM2[cp][k+fmax[cp]],k,j,cp,opt,kTRUE);
	}
      }
      if(option.Contains("LED")){
	for(Int_t ii=fgk1min;ii<fgk1max+1;ii++) InitMatrix1(fgM1LED[cp],ii,cp,opt,kTRUE);
      }
      cp++;
    }
  }
  delete db;
}

//____________________________________________________________________________
void TARSBase::SetRefShape(const char* file)
{
//   //It initializes all shape analysis parameters (all matrices...)
  
//   cout<<"Initializing all shape analysis parameters... Please wait..."<<endl;

//   ifstream refshape(file);
  
//   Double_t val=0.;
  
//   fgM1=new TMatrixD**[fNbChannels];
//   fgM2=new TMatrixD***[fNbChannels];
  
//   if(!fnval1) fnval1=new Double_t[4];
//   if(!fnval2) fnval2=new Double_t[9];
  
//   for(Int_t ii1=0;ii1<4;ii1++) fnval1[ii1]=0.;
//   for(Int_t ii1=0;ii1<9;ii1++) fnval2[ii1]=0.;
  
//   fgRefShapes=new TClonesArray("TDoubleArray",fNbChannels);
//   TClonesArray &shapes=*fgRefShapes;
//   for(Int_t i=0;i<fNbChannels;i++){
//     fgM1[i]=new TMatrixD*[2*fNbSamples+1];
//     fgM2[i]=new TMatrixD**[2*fNbSamples+1];
//     TDoubleArray *shaperef=new(shapes[i]) TDoubleArray(fNbSamples);
//     for(Int_t j=0;j<fNbSamples;j++){
//       refshape>>val;
//       shaperef->SetValue(j,-val);
//     }
//     for(Int_t k=0;k<2*fNbSamples+1;k++) {
//       fgM2[i][k]=new TMatrixD*[2*fNbSamples+1];
//       for(Int_t j=0;j<2*fNbSamples+1;j++) fgM2[i][k][j]=0;
//       fgM1[i][k]=0;
//     }
//   }
//   SetFirstWindow(fk1min,fk1max,"data",kTRUE);
//   SetSecondWindow(fk1min2,fk1max2,fk2min,fk2max,"data",kTRUE);
//   cout<<"tot "<<fgM1[0][0]<<endl;
}

//____________________________________________________________________________
void TARSBase::InitShapeAnalysisLED(const char* opt)
{
  //It initializes all shape analysis parameters (all matrices...) for LED
  
  cout<<"Initializing all LED shape analysis parameters... Please wait..."<<endl;

  TString option=opt;

  if(!fnval1) fnval1=new Double_t[4];
  if(!fnval2) fnval2=new Double_t[9];
  for(Int_t ii1=0;ii1<4;ii1++) fnval1[ii1]=0.;
  for(Int_t ii1=0;ii1<9;ii1++) fnval2[ii1]=0.;

  Double_t dum=0;

  TString arsfile(getenv("NPS_SOFT"));
  arsfile+="/initdata/arsbase.txt";
  ifstream inifile(arsfile.Data());
  inifile>>dum;
  inifile>>fNbSamples;
  inifile>>fchi20[0];
  inifile>>fchi21[0];
  inifile>>fchi22[0];
  inifile>>fksp;
  inifile>>fkled;
  if(fNbChannels==-1) fNbChannels=dum;

  TString arsfile2(getenv("NPS_SOFT"));
  arsfile2+="/initdata/refshape.txt";
  ifstream refshape(arsfile2.Data());
  
  if(option.Contains("data")){
    fk1=7;
    fk1min=fkled-3;

    fk1max=fkled+3;
  }
  
  InitPedSigma();
  
  Double_t val=0.;
  fgM1LED=new TMatrixD**[fNbChannels];
  fgRefShapesLED=new TClonesArray("TDoubleArray",fNbChannels);
  TClonesArray &shapes=*fgRefShapesLED;
  for(Int_t i=0;i<fNbChannels;i++){
    fgM1LED[i]=new TMatrixD*[2*fNbSamples+1];
    TDoubleArray *shaperef=new(shapes[i]) TDoubleArray(fNbSamples);
    for(Int_t j=0;j<fNbSamples;j++){
      refshape>>val;
      shaperef->SetValue(j,-val);
    }
    for(Int_t k=0;k<2*fNbSamples+1;k++) fgM1LED[i][k]=0;
  }
  SetFirstWindow(fk1min,fk1max,"LED");
}

//____________________________________________________________________________
void TARSBase::SetFirstWindow(Int_t min, Int_t max, const char* opt, Bool_t kFORCE)
{
  //   It sets a different window to look for the first pulse.
  //It does not recalculate matrices if already done, unless we force it to
  //do it via kFORCE

  TString option=opt;
  fk1min=min;
  fk1max=max;
  fgk1min=min;
  fgk1max=max;
  for(Int_t ch=0;ch<fNbChannels;ch++){
    for(Int_t i=min;i<max+1;i++){
      if(option.Contains("LED")) InitMatrix1(fgM1LED[ch],i,ch,"LED",kFORCE);
      if(option.Contains("data")) InitMatrix1(fgM1[ch],i,ch,"data",kFORCE);
    }
  }
  
  //  cout<<"Changing first window in TARSBase..."<<option.Data()<<endl;
  
}

//____________________________________________________________________________
void TARSBase::SetSecondWindow(Int_t min1, Int_t max1, Int_t min2, Int_t max2, const char* opt, Bool_t kFORCE)
{
  //   It sets a different window to look for the second pulse.
  //It does not recalculate matrices if already done, unless we force it to
  //do it via kFORCE

  TString option=opt;
  fk1min2=min1;
  fk1max2=max1;
  fk2min=min2;
  fk2max=max2;
  fgk1min2=min1;
  fgk1max2=max1;
  fgk2min=min2;
  fgk2max=max2;
  for(Int_t ch=0;ch<fNbChannels;ch++){
    for(Int_t k=min1;k<max1+1;k++) {
      for(Int_t j=min2;j<max2+1;j++) InitMatrix2(fgM2[ch][k+fmax[ch]],k,j,ch,"data",kFORCE);
    }
  }
}

//____________________________________________________________________________
void TARSBase::InitMatrix2(TMatrixD** matrix2, Int_t k, Int_t j, Int_t i, const char* opt, Bool_t kFORCE)
{
  // Computes matrix for shift k for a channel i and inverts it
 
  if(!matrix2[j+fmax[i]] || kFORCE==kTRUE){
    TString option=opt;
    TDoubleArray* shaperef=0;
    if(option.Contains("data")) shaperef=(TDoubleArray*)fgRefShapes->UncheckedAt(i);
    if(option.Contains("LED")) shaperef=(TDoubleArray*)fgRefShapesLED->UncheckedAt(i);
    
    for(Int_t i1=0;i1<8;i1++) fnval2[i1]=0.;
    for(Int_t s=fmin[i];s<fmax[i];s++){
      if(s+k<128 && s+k>-1) fnval2[0]+=shaperef->GetValue(s+k)/fgpedsigma2[i][s];
      fnval2[2]+=1./fgpedsigma2[i][s];
      if(s+k<128 && s+k>-1) fnval2[6]+=shaperef->GetValue(s+k)*shaperef->GetValue(s+k)/fgpedsigma2[i][s];
      if(s+j<128 && s+j>-1) fnval2[1]+=shaperef->GetValue(s+j)/fgpedsigma2[i][s];
      if(s+k<128 && s+k>-1 && s+j<128 && s+j>-1) fnval2[3]+=shaperef->GetValue(s+k)*shaperef->GetValue(s+j)/fgpedsigma2[i][s];
      if(s+j<128 && s+j>-1) fnval2[4]+=shaperef->GetValue(s+j)*shaperef->GetValue(s+j)/fgpedsigma2[i][s];
    }	

    if(fgbfixed){
      fnval2[0]=0.;
      fnval2[1]=0.;
      fnval2[2]=1.;
    }

    fnval2[5]=fnval2[1];
    fnval2[7]=fnval2[3];
    fnval2[8]=fnval2[0];

    if(!matrix2[j+fmax[i]]) matrix2[j+fmax[i]]=new TMatrixD(3,3);
    matrix2[j+fmax[i]]->SetMatrixArray(fnval2);
    if(matrix2[j+fmax[i]]->Determinant()!=0) {
      matrix2[j+fmax[i]]->Invert();
    }
  }
}

//____________________________________________________________________________
void TARSBase::InitMatrix1(TMatrixD** matrix1, Int_t k, Int_t i, const char* opt, Bool_t kFORCE)
{
  // Computes matrix for shift k for a channel i and inverts it
  if((!matrix1[k+fmax[i]]) || kFORCE==kTRUE)
    {
    TString option=opt;
    TDoubleArray* shaperef=0;
    if(option.Contains("data")) shaperef=(TDoubleArray*)fgRefShapes->UncheckedAt(i);
    if(option.Contains("LED")) shaperef=(TDoubleArray*)fgRefShapesLED->UncheckedAt(i);
    
    for(Int_t i1=0;i1<4;i1++) fnval1[i1]=0.;
    for(Int_t s=fmin[i];s<fmax[i];s++){
      if(s+k<128 && s+k>-1) fnval1[0]+=shaperef->GetValue(s+k)/fgpedsigma2[i][s];
      fnval1[1]+=1./fgpedsigma2[i][s];
      if(s+k<128 && s+k>-1) fnval1[2]+=shaperef->GetValue(s+k)*shaperef->GetValue(s+k)/fgpedsigma2[i][s];
    }
    fnval1[3]=fnval1[0];
    if(!matrix1[k+fmax[i]]) {
      matrix1[k+fmax[i]]=new TMatrixD(2,2);
    }
    matrix1[k+fmax[i]]->SetMatrixArray(fnval1);
    if(matrix1[k+fmax[i]]->Determinant()!=0) {
      matrix1[k+fmax[i]]->Invert();
    }
    }
}

//____________________________________________________________________________
void TARSBase::Init(const char* opt)
{
  //It initializes the number of channels and the number of samples

  TString option=opt;
  //  cout<<"Init TARSBase"<<endl;
  Int_t dum;
  // Initialization
  if (fgIsInit == kFALSE) {
    TString arsfile(getenv("NPS_SOFT"));
    arsfile+="/initdata/arsbase.txt";
    ifstream inifile(arsfile.Data());
    inifile>>dum;
    inifile>>fNbChannelsCalo;
    inifile>>fNbChannelsPA;
    inifile>>fNbChannelsVeto;
    inifile>>fNbSamples;
    if(fNbChannels==-1) fNbChannels=dum;
  }
  
  fgARSParameters= new TARSParameters[fNbChannels];//Shape analysis parameters
  //fgARSConst= new  TARSConst[fNbChannels];//Shape analysis constants
  //fgARSCalib = new TARSCalibration[fNbChannels];//Calibration constants

  fgIsInit=kTRUE;
  
  if (fgIsInit == kFALSE) {
    if (fgErrors == kTRUE) {
      cout << "TARSBase::Init failed"<<endl;
      cout << "Aborting"<<endl;
    exit(1);
    }
  }
}

//_____________________________________________________________________________
 void TARSBase::Print(const char* opt)
{
  // Output on screen


}

//_____________________________________________________________________________
 void TARSBase::DrawShape(Int_t i, const char* opt)
{
  //
  TString option=opt;
  if(i<0 || i>fNbChannels-1) cout<<"Value of shape out of bounds"<<endl;
  
  TDoubleArray* shape=(TDoubleArray*)fgRefShapes->UncheckedAt(i);
  shape->Draw();

}

//_____________________________________________________________________________

void TARSBase::SetPedestalProfileFile(const char*  fname)
{
  TFile * f = new TFile(fname);
  cout<<fname<<" "<<f<<(f!=0)<<endl;
  if (f!=0)
  for (int i=0;i<fNbChannels;i++)
    {
      TString pname("ARS");
      pname+=i;
      TProfile *prof = (TProfile *) f->Get(pname.Data());
      cout<<pname.Data()<<" : "<<prof<<endl;
      if (prof!=0x0)
	fgARSParameters[i].SetPedestal(prof);
    }
  f->Close();
  delete f;
}
//_____________________________________________________________________________

void TARSBase::PrintPedSigma(const char*  opt)
{
  //Prints pedestal sigma

  for(Int_t i=0;i<fNbChannels;i++){
    for(Int_t j=0;j<fNbSamples;j++){
      cout<<i<<" "<<j<<" "<<fgpedsigma2[i][j]<<endl;
    }
  }
}

//_____________________________________________________________________________

void TARSBase::Add2RunningShape(TDoubleArray *wave, Int_t channel, Double_t amp, Double_t time, const char* opt)
{
  //Adds wave to the running shape of channel
  //Doesn't allow to analyze LED TARSWaves and data together (same channel number)
  //but this will never be neccessary, I think.

  TString option=opt;
  TDoubleArray *refshape=0;
  if(option.Contains("data")) refshape=(TDoubleArray*)fgRefShapes->UncheckedAt(channel);
  if(option.Contains("LED")) refshape=(TDoubleArray*)fgRefShapesLED->UncheckedAt(channel);

  cout<<"Befofe :"<<endl;
  for(Int_t i=0;i<128;i++) cout<<refshape->GetValue(i)<<" ";
  cout<<endl;

  if(time<fNbSamples && time>-(fNbSamples-1)){
    if(!fgRunningIsInit) {
      fgRunningwei=new Double_t*[fNbChannels];
      for(Int_t j=0;j<fNbChannels;j++){
	fgRunningwei[j]=new Double_t[fNbSamples];
	for(Int_t i=0;i<fNbSamples;i++) fgRunningwei[j][i]=1;
      }
      fgRunningIsInit =kTRUE;
    }
    if(time>=0){
      for(Int_t i=0;i<fNbSamples-time;i++){
	Double_t current=refshape->GetValue(i);
	refshape->SetValue(i,(current*(fgRunningwei[channel][i]-1.)+amp*wave->GetValue(i+time))/fgRunningwei[channel][i]);
	fgRunningwei[channel][i]+=1.;
      }
    }else{
      for(Int_t i=-time;i<fNbSamples;i++){
	Double_t current=refshape->GetValue(i);
	refshape->SetValue(i,(current*(fgRunningwei[channel][i]-1.)+amp*wave->GetValue(i+time))/fgRunningwei[channel][i]);
	fgRunningwei[channel][i]+=1.;
      }
    }
    if(option.Contains("data")){
      for(Int_t i=fk1min;i<fk1max+1;i++) InitMatrix1(fgM1[channel],i,channel,opt,kTRUE);
      for(Int_t k=fk1min2;k<fk1max2+1;k++) {
	for(Int_t j=fk2min;j<fk2max+1;j++) InitMatrix2(fgM2[channel][k+fmax[channel]],k,j,channel,opt,kTRUE);
      }
    }
    if(option.Contains("LED")){
      for(Int_t i=fk1min;i<fk1max+1;i++) InitMatrix1(fgM1LED[channel],i,channel,opt,kTRUE);
    }
  }

  cout<<"After :"<<endl;
  for(Int_t i=0;i<128;i++) cout<<refshape->GetValue(i)<<" ";
  cout<<endl;

}  

//_____________________________________________________________________________

void TARSBase::InitPedSigmaDB(Int_t run){

  if(!fgpedsigma2) fgpedsigma2=new Double_t*[fNbChannels];
  for(Int_t i=0;i<fNbChannels;i++) fgpedsigma2[i]=new Double_t[fNbSamples];
  
  TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,"munoz","");
  cout<<"Number of channels "<<fNbChannels<<endl;

  Int_t cp=0;
  for(Int_t i=0;i<fNbChannelsCalo+fNbChannelsPA+fNbChannelsVeto;i++){
    if((i<fNbChannelsCalo && fgCaloWF) || (i<(fNbChannelsCalo+fNbChannelsPA)&&i>(fNbChannelsCalo-1)&&fgPAWF) || (i>(fNbChannelsCalo+fNbChannelsPA-1)&&fgVetoWF)){
      Float_t *coef=0;
      if(i<fNbChannelsCalo){
	TString name("CALO_calib_ARSSigma");name+=i;
	coef=db->GetEntry_f(name.Data(),run);
      }
      if(i<(fNbChannelsCalo+fNbChannelsPA)&&i>(fNbChannelsCalo-1)){
	TString name("PA_calib_ARSSigma");name+=i-fNbChannelsCalo;
	coef=db->GetEntry_f(name.Data(),run);
      }
      if(i>(fNbChannelsCalo+fNbChannelsPA-1)&&i<(fNbChannelsCalo+fNbChannelsPA+fNbChannelsVeto)){
	TString name("VETO_calib_ARSSigma");name+=i-fNbChannelsPA-fNbChannelsCalo;
	coef=db->GetEntry_f(name.Data(),run);
      }
      for(Int_t j=0;j<fNbSamples;j++) fgpedsigma2[cp][j]=coef[j];
      cp++;
      delete coef;
    }
  }
  delete db;
}

//_____________________________________________________________________________

void TARSBase::InitPedSigma(void)
{
   //Init pedestal sigma tables

    if(!fgpedsigma2) fgpedsigma2=new Double_t*[fNbChannels];
    for(Int_t i=0;i<fNbChannels;i++){
      fgpedsigma2[i]=new Double_t[fNbSamples];
    }
    //TSQLServer *db = TSQLServer::Connect("mysql://localhost/dvcs","carlos", "cebaF111");
    //    if(db==0) {
    //      cout<<"Pedestals sigmas successfully read from textfile"<<endl;
      TString pedsig(getenv("NPS_SOFT"));
      pedsig+="/initdata/sigma.txt";
      ifstream pedsigma(pedsig.Data());
      Double_t val=0.;
      //      cout<<"Number of channels "<<fNbChannels<<endl;
      for(Int_t i=0;i<fNbChannels;i++){
	for(Int_t j=0;j<fNbSamples;j++){
	  pedsigma>>val;
   	  fgpedsigma2[i][j]=val;//we assume one row
	  //	  cout<<i<<" "<<j<< " "<<fgpedsigma2[i][j]<<endl;
	}
      }
//     }else{
//       TSQLRow *row;
//       TSQLResult *res;
//       for(Int_t i=0;i<fNbChannels;i++){
// 	  TString sql("select sigma from dvcs.pedestalsigma WHERE channel=");
// 	  sql+=i;
// 	  res = db->Query(sql);
// 	  Int_t nrows = res->GetRowCount();
// 	  for (int j = 0; j < nrows; j++) {
// 	    row = res->Next();
// 	    fgpedsigma2[i][j]=TMath::Power(atof(row->GetField(0)),2.);//we assume one column
// 	  }
//       }
//       delete row;
//       delete res;
//       delete db;
//     }
}








