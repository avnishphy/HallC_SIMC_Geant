//
// TARSWave.cxx, v1.0, Thu Dec  5 14:42:50
// Author: C. Mu�oz Camacho

#ifndef __TARSWave__
#include "TARSWave.h"
#endif
#ifndef __TDVCSDB__
#include "TDVCSDB.h"
#endif

#include "TDVCSGlobal2h"

//#define DEBUG
ClassImp(TARSWave)

TDoubleArray    *TARSWave::fgWave = 0;
TDoubleArray    *TARSWave::fgData = 0;
TDoubleArray   **TARSWave::fgPedCalo=0;
TDoubleArray   **TARSWave::fgPedPA=0;
TDoubleArray   **TARSWave::fgPedVeto=0;
Bool_t           TARSWave::fgPedIsInit=0;
TMatrixD        *TARSWave::fgX1=0;
TMatrixD        *TARSWave::fgP1=0;
TMatrixD        *TARSWave::fgX2=0;
TMatrixD        *TARSWave::fgP2=0;
Double_t        *TARSWave::fgval1=0;
Double_t        *TARSWave::fgsol1=0;
Double_t        *TARSWave::fgval2=0;
Double_t        *TARSWave::fgsol2=0;
Int_t        TARSWave::fminchi2=0;
Int_t        TARSWave::fmaxchi2=128;
Bool_t           TARSWave::fgIsInitShapeAnalysis = kFALSE;
Bool_t           TARSWave::fgIsInitShapeAnalysisLED = kFALSE;
TDoubleArray    *TARSWave::fFit=0;
Double_t        *TARSWave::fga=0;
Double_t        *TARSWave::fgt=0;

//_____________________________________________________________________________
 Double_t & TARSWave::operator [](UInt_t k)
{
  if (fSubstracted==0)
    SubstractPedestal();
    return (*fData)[k];
}

//_____________________________________________________________________________
  void TARSWave:: SubstractPedestal(int ch)
{
  fSubstracted=1;
  for(int i=0;i<fgSize;i++){
    //cout<<i<<" "<<fWave<<" "<<fPedestal<<endl;
    //cout<<i<<" "<<(*fWave)[i]-fgARSParameters[ch].GetBase(i+fgSize)<<endl;
    fData->SetValue(i,(*fWave)[i]-fgARSParameters[ch].GetBase(i+fgSize)) ;
    //   cout<<(*fRaw)[i]<<"-"<<fgARSParameters[fNumber].GetBase(i)<<"="<<(*fData)[i]<<endl;
  }
}

//_____________________________________________________________________________
  void TARSWave::SubstractPedestalDB(Int_t chan, Int_t run, const char* dec)
{
  if(!fgPedIsInit) InitPedDB(run);
  fSubstracted=1;
  Int_t samples=this->GetNbSamples();
  samples=128;

  TString dect=dec;
  for(int i=0;i<samples;i++){
    if(dect.Contains("CALO")) fData->SetValue(i,fWave->GetValue(i)-fgPedCalo[chan]->GetValue(i));
    if(dect.Contains("PA")) fData->SetValue(i,fWave->GetValue(i)-fgPedPA[chan]->GetValue(i));
    if(dect.Contains("Veto")) fData->SetValue(i,fWave->GetValue(i)-fgPedVeto[chan]->GetValue(i));
  }
}

//_____________________________________________________________________________
  void TARSWave::SubstractPedestalDB(Int_t chan, const char* dec)
{
  SubstractPedestalDB(chan, 4000, dec);
}
//_____________________________________________________________________________
  void TARSWave:: SubstractPedestal(Int_t chan, Int_t run, const char* dec)
{
  //This method is to be used if you have a slow connection to the database (eg. 
  //working offsite) and are not interested in latest pedestals. Pedestals are read
  //from a text file and then are no necessarily up to date. Parameter run is then
  //not used and only there for easy swithing with SubstractPedestalDB method.

  Int_t ch=GetNbChannel(chan,dec);
  if(!fgPedIsInit) InitPed(run);
  fSubstracted=1;
  Int_t samples=this->GetNbSamples();
  samples=128;
  for(int i=0;i<samples;i++){
    if(ch<132) fData->SetValue(i,fWave->GetValue(i)-fgPedCalo[chan]->GetValue(i));
    if(ch>131 && ch<232) fData->SetValue(i,fWave->GetValue(i)-fgPedPA[chan]->GetValue(i));
    if(ch>231) fData->SetValue(i,fWave->GetValue(i)-fgPedVeto[chan]->GetValue(i));
  }
}

//_____________________________________________________________________________
  void TARSWave::InitPedDB(Int_t run)
{
//   TString username;
//   cout<<"Type mysql username : ";
//   cin>>username;
//   cout<<"If you get a crash now, remeber to forward port 3306 to a valid database"<<endl;
  TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,"munoz","");
//   TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,(char*)username.Data());
  Int_t *val=db->GetEntry_i("CALO_geom_NRow",run);
  fNbChannelsCalo=val[0];
  delete val;
  val=db->GetEntry_i("CALO_geom_NCol",run);
  fNbChannelsCalo*=val[0];
  delete val;

  Int_t samples=GetNbSamples();
  fgPedCalo=new TDoubleArray*[fNbChannelsCalo];
  fgPedPA=new TDoubleArray*[fNbChannelsPA];
  fgPedVeto=new TDoubleArray*[fNbChannelsVeto];
  cout<<"Initializing pedestals from database..."<<endl;
  for(Int_t i=0;i<fNbChannelsCalo;i++){
    if(i%10==0) cout<<i<<"/"<<fNbChannelsCalo<<endl;
    TString name=("CALO_calib_ARSPed");name+=i;
    Float_t* coef=db->GetEntry_f(name.Data(),run);
    fgPedCalo[i]=new TDoubleArray(samples);
    for(Int_t j=0;j<samples;j++) fgPedCalo[i]->SetValue(j,coef[j]);
    delete coef;
  }
  for(Int_t i=0;i<fNbChannelsPA;i++){
    if(i%10==0) cout<<i<<"/"<<fNbChannelsPA<<endl;
    TString name=("PA_calib_ARSPed");name+=i;
    Float_t* coef=db->GetEntry_f(name.Data(),run);
    fgPedPA[i]=new TDoubleArray(samples);
    for(Int_t j=0;j<samples;j++) fgPedPA[i]->SetValue(j,coef[j]);
    delete coef;
  }
  for(Int_t i=0;i<fNbChannelsVeto;i++){
    if(i%10==0) cout<<i<<"/"<<fNbChannelsVeto<<endl;
    TString name=("VETO_calib_ARSPed");name+=i;
    Float_t* coef=db->GetEntry_f(name.Data(),run);
    fgPedVeto[i]=new TDoubleArray(samples);
    for(Int_t j=0;j<samples;j++) fgPedVeto[i]->SetValue(j,coef[j]);
    delete coef;
  }
  delete db;
  fgPedIsInit=kTRUE;
}

//_____________________________________________________________________________
  void TARSWave::InitPed(Int_t run)
{
  //Method used in SubstractPedestal(int, int, char*). Parameter run is dummy.

//   TString username;
//   cout<<"Type mysql username : ";
//   cin>>username;
//   cout<<"If you get a crash now, remeber to forward port 3306 to a valid database"<<endl;

  TString geomfile(getenv("NPS_SOFT"));
  geomfile+="/initdata/pedfile.txt";
  ifstream fped(geomfile.Data());

  Int_t samples=GetNbSamples();
  fgPedCalo=new TDoubleArray*[fNbChannelsCalo];
  fgPedPA=new TDoubleArray*[fNbChannelsPA];
  fgPedVeto=new TDoubleArray*[fNbChannelsVeto];
  cout<<"Initializing pedestals from file..."<<endl;
  for(Int_t i=0;i<fNbChannelsCalo;i++){
    if(i%10==0) cout<<i<<"/"<<fNbChannelsCalo<<endl;
    TString name=("CALO_calib_ARSPed");name+=i;
    Float_t* coef=new Float_t[132];
    fgPedCalo[i]=new TDoubleArray(samples);
    for(Int_t j=0;j<samples;j++) {fped>>coef[j];fgPedCalo[i]->SetValue(j,coef[j]);}
    delete coef;
  }
  for(Int_t i=0;i<fNbChannelsPA;i++){
    if(i%10==0) cout<<i<<"/"<<fNbChannelsPA<<endl;
    TString name=("PA_calib_ARSPed");name+=i;
    Float_t* coef=new Float_t[100];
    fgPedPA[i]=new TDoubleArray(samples);
    for(Int_t j=0;j<samples;j++) {fped>>coef[j];fgPedPA[i]->SetValue(j,coef[j]);}
    delete coef;
  }
  for(Int_t i=0;i<fNbChannelsVeto;i++){
    if(i%10==0) cout<<i<<"/"<<fNbChannelsVeto<<endl;
    TString name=("VETO_calib_ARSPed");name+=i;
    Float_t* coef=new Float_t[57];
    fgPedVeto[i]=new TDoubleArray(samples);
    for(Int_t j=0;j<samples;j++) {fped>>coef[j];fgPedVeto[i]->SetValue(j,coef[j]);}
    delete coef;
  }
  fgPedIsInit=kTRUE;
}


//_____________________________________________________________________________
  void TARSWave:: SubstractPedestal()
{
  fSubstracted=1;
  for(int i=0;i<fgSize;i++){
    //cout<<i<<" "<<fWave<<" "<<fPedestal<<endl;
    //cout<<i<<" "<<(*fWave)[i]-fgARSParameters[ch].GetBase(i+fgSize)<<endl;
    fData->SetValue(i,(*fWave)[i]-(*fPedestal)[i+fgSize]) ;
    //   cout<<(*fRaw)[i]<<"-"<<fgARSParameters[fNumber].GetBase(i)<<"="<<(*fData)[i]<<endl;
  }
}

//_____________________________________________________________________________
Int_t TARSWave:: Decode(Int_t * fBuffer)
{
  Int_t  index=0;
  Int_t chan,voie,valeur;
  Int_t width=128;
  // cout<<fBuffer<<endl;
  if (fBuffer!=0)
  {
  if ((fBuffer[index]&0x0000ffff)==0x0000cafe)
    {
      index++;
#ifdef DEBUG
      //      cout<<hex<<fBuffer[index]<<" "<<fBuffer[index+1]<<endl;
#endif
      chan=fBuffer[index];
      index++;
      fDAC=fBuffer[index]&0x000000ff;
      //   fChan=(fBuffer[index]&0x00000f00)>>8;
      //fVME=fBuffer[index]&0xffff0000;

#ifdef DEBUG
      //cout<<hex<<fBuffer[index]<<" "<<fBuffer[index+1]<<":"<<(fBuffer[index+1]!=0x0000bad2)<<0x0000bad2<<endl;
#endif
      if ((fBuffer[index+1]!=0x00000bad)&&index<128&&(fBuffer[index+1]!=0x0000bad2))
	{
	for (int s=0;(s<width/2);s++)
		  {
		    index++;
		    int valeur=(fBuffer[index]&0xfff);
		    voie = (fBuffer[index]&0xf000)>>12;   
		    fWave->SetValue(2*s+1,valeur);
		    valeur=(fBuffer[index]>>16)&0xfff;
		    voie = ((fBuffer[index]>>16)&0xf000)>>12;
		    fWave->SetValue(2*s,valeur);
		  }
	return chan;
	}
    }
  else {cout<<"arf bad2"<<endl;return -2;};
  }
  else {cout<<"no ARS Data"<<endl;return -1;};
}

//_____________________________________________________________________________
//_____________________________________________________________________________
Int_t TARSWave:: Decode(const int * fBuffer)
{
  Int_t  index=0;
  Int_t chan,voie,valeur;
  Int_t width=128;
  // cout<<fBuffer<<endl;
  if (fBuffer!=0)
  {
  if ((fBuffer[index]&0x0000ffff)==0x0000cafe)
    {
      index++;
#ifdef DEBUG
      //cout<<hex<<fBuffer[index]<<" "<<fBuffer[index+1]<<endl;
#endif
      chan=fBuffer[index];
      index++;
      fDAC=fBuffer[index]&0x000000ff;
      //   fChan=(fBuffer[index]&0x00000f00)>>8;
      //fVME=fBuffer[index]&0xffff0000;

#ifdef DEBUG
      //cout<<hex<<fBuffer[index]<<" "<<fBuffer[index+1]<<":"<<(fBuffer[index+1]!=0x0000bad2)<<0x0000bad2<<endl;
#endif
      if ((fBuffer[index+1]!=0x00000bad)&&index<128&&(fBuffer[index+1]!=0x0000bad2))
	{
	for (int s=0;(s<width/2);s++)
		  {
		    index++;
		    int valeur=(fBuffer[index]&0xfff);
		    voie = (fBuffer[index]&0xf000)>>12;   
		    fWave->SetValue(2*s+1,valeur);
		    valeur=(fBuffer[index]>>16)&0xfff;
		    voie = ((fBuffer[index]>>16)&0xf000)>>12;
		    fWave->SetValue(2*s,valeur);
		  }
	return chan;
	}
    }
  else {cout<<"arf bad2"<<endl;return -2;};
  }
  else {cout<<"no ARS Data"<<endl;return -1;};
}

//_____________________________________________________________________________
//_____________________________________________________________________________
Int_t TARSWave:: Decode(Int_t * fBuffer,Int_t length)
{
  Int_t  index=0;
  Int_t chan,voie,valeur;
  Int_t width=length;
  if (fBuffer!=0)
    {
      for (int s=0;(s<width/2);s++)
	{
	  int valeur=(fBuffer[index]&0xfff);
	  voie = (fBuffer[index]&0xf000)>>12; 
	  //cout<<s<<" "<<voie<<" "<<valeur<<endl;
	  fWave->SetValue(2*s+1,valeur);
	  valeur=(fBuffer[index]>>16)&0xfff;
	  voie = ((fBuffer[index]>>16)&0xf000)>>12;
	  fWave->SetValue(2*s,valeur);
	  index++;
	}
      return voie;
    }
else return -1;
}

//_____________________________________________________________________________

TARSWave::TARSWave()
{
  //cout<<"TARSWave default constructor "<<this<<endl;

  //  fWave = new TClonesArray("TDouble");
  //  fWave->BypassStreamer(kFALSE);
  fgWave=new TDoubleArray();
  fWave=fgWave;
  fgData = new TDoubleArray(fgSize);
  fData=fgData;
  fNbChannel=0;
  //  fgReso=5;
//    for(Int_t i=0;i<128;i++){
//      AddValue(i,0.);
//    }
  fH=0;
  fCanvas=0;
  fPedestal=0;
  fFit=0;
  fNPulse=0;
  fchi2=-1;
  fa=0;
  ft=0;
  fAnalyzed=kFALSE;
}

//_____________________________________________________________________________
TARSWave::TARSWave(TARSWave* wave)
{
  //NEVER USE yourself this constructor. For experts only...

  //    cout<<"Pointing constructor"<<this<<endl;

  //  fWave = new TClonesArray("TDouble");
  //  fWave->BypassStreamer(kFALSE);
  fWave=wave->fWave;
  fData=wave->fData;
//    for(Int_t i=0;i<128;i++){
//      AddValue(i,0.);
//    }
  fH=wave->fH;
  fCanvas=wave->fCanvas;
  fPedestal=wave->fPedestal;
  fFit=wave->fFit;
  fNbChannel=wave->fNbChannel;
  fNPulse=wave->fNPulse;
  fchi2=wave->fchi2;
  fa=wave->fa;
  ft=wave->ft;
  fb=wave->fb;
  fAnalyzed=wave->fAnalyzed;
  fgIsInitShapeAnalysis=wave->fgIsInitShapeAnalysis;
  fgIsInitShapeAnalysisLED=wave->fgIsInitShapeAnalysisLED;

}

//_____________________________________________________________________________
TARSWave::TARSWave(const TARSWave& wave)
{
  //Copy constructor

  //  cout<<"Warning: copy constructor not fully tested"<<endl;

  fWave=0; fData=0;
   if(wave.fWave) fWave=fgWave;
   if(wave.fData) fData=fgData;
  fNbChannel=wave.fNbChannel;
  fFit=0;
  fH=0;
  fPedestal=0;
  fCanvas=0;
  fAnalyzed=wave.fAnalyzed;
  fNPulse=wave.fNPulse;
  fa=fga;
  ft=fgt;
  fb=wave.fb;
  fchi2=wave.fchi2;
  fgIsInitShapeAnalysis=wave.fgIsInitShapeAnalysis;
  fgIsInitShapeAnalysisLED=wave.fgIsInitShapeAnalysisLED;

  //  cout<<"end of copy constructor "<<&wave<<"->"<<this<<endl;
}

//_____________________________________________________________________________
TARSWave::TARSWave(Int_t size, Int_t nbchannels):TARSBase(nbchannels)
{
  //cout<<"TARSWave constructor with size "<<this<<endl;
  //cout<<"TARSWave constructor with size "<<size<<" "<<this<<endl;
  
  //    fWave = new TClonesArray("TDouble",size);
  //    fWave->BypassStreamer(kFALSE);
  //  fgReso=5;
  fga=0;fgt=0;
  fgWave=new TDoubleArray(size);
  fWave=fgWave;
  fgData = new TDoubleArray(fgSize);
  fData=fgData;
  //     for(Int_t i=0;i<128;i++){
  //      AddValue(i,0.);
  //    }
  fH=0;
  fCanvas=0;
  fPedestal=0;
  fWave = new TDoubleArray(fgSize);
  fData = new TDoubleArray(fgSize);
  ft=0;
  fa=0;
  fNPulse=0;
}

//_____________________________________________________________________________
void TARSWave::InitShapeAnalysisLED(void)
{
  TARSBase::InitShapeAnalysisLED();

  if(!fga) fga=new Double_t[2];
  if(!fgt) fgt=new Double_t[2];
  fa=fga;
  ft=fgt;

  if(!fgval1) fgval1=new Double_t[2];
  if(!fgsol1) fgsol1=new Double_t[2];

  if(!fgX1) fgX1=new TMatrixD(2,1);
  if(!fgP1) fgP1=new TMatrixD(2,1);

  fgIsInitShapeAnalysisLED=kTRUE;
}

//_____________________________________________________________________________
void TARSWave::InitShapeAnalysis(void)
{
  TARSBase::InitShapeAnalysis();
  if(!fga) fga=new Double_t[2];
  if(!fgt) fgt=new Double_t[2];
  fa=fga;
  ft=fgt;

  if(!fgX1) fgX1=new TMatrixD(2,1);
  if(!fgP1) fgP1=new TMatrixD(2,1);
  if(!fgX2) fgX2=new TMatrixD(3,1);
  if(!fgP2) fgP2=new TMatrixD(3,1);

  if(!fgval1) fgval1=new Double_t[2];
  if(!fgsol1) fgsol1=new Double_t[2];
  if(!fgval2) fgval2=new Double_t[3];
  if(!fgsol2) fgsol2=new Double_t[3];
  
  fgIsInitShapeAnalysis=kTRUE;
}

//_____________________________________________________________________________
Double_t TARSWave::GetARSCor(void)
{
  Double_t cor=0.;

    if(fNbChannel<fNbChannelsCalo && fgCaloWF==kTRUE) cor-=gdvcs->GetARSCor(fNbChannel);
    if(fNbChannel<fNbChannelsPA && fgPAWF==kTRUE && fgCaloWF==kFALSE) cor-=gdvcs->GetARSCorPA(fNbChannel);
    if(fNbChannel>(fNbChannelsCalo-1)&&fNbChannel<(fNbChannelsPA+fNbChannelsCalo)&& fgCaloWF==kTRUE && fgPAWF==kTRUE) cor-=gdvcs->GetARSCorPA(fNbChannel-fNbChannelsCalo);
    if(fNbChannel>(fNbChannelsCalo+fNbChannelsPA-1)) cor-=gdvcs->GetARSCorVETO(fNbChannel-fNbChannelsCalo-fNbChannelsPA);
    if(fgPAWF==kFALSE && fgCaloWF==kFALSE) cor-=gdvcs->GetARSCorVETO(fNbChannel);
    if(fgPAWF==kTRUE && fgCaloWF==kFALSE && fNbChannel>(fNbChannelsPA-1)) cor-=gdvcs->GetARSCorVETO(fNbChannel-fNbChannelsPA);
    if(fgPAWF==kFALSE && fgCaloWF==kTRUE && fNbChannel>(fNbChannelsCalo-1)) cor-=gdvcs->GetARSCorVETO(fNbChannel-fNbChannelsCalo);

    return -cor;
}

//_____________________________________________________________________________
Int_t TARSWave::Analyze(const char* opt, Double_t *rawtimes)
{
  // Shape analysis method. It analyses the waveform. It returns the number of pulses 
  //found. This number can also be accessed by TARSWave::GetNbPulses(). 
  //Amplitudes and arrival time of each pulse are obtained by TARSWave::GetAmplitude1(),
  //TARSWave::GetAmplitude2(), TARSWave::GetArrivalTime1() et
  //TARSWave::GetArrivalTime2(). If more than two pulses are found, the number
  //of pulses is set to 3 and the amplitudes and arrival times are unaccesible.
  //
  // If opt contains :
  //    "LED" : LED reference shape used
  //    "data": data reference shape used
  //    "wave": to analyze wave with no pedestal substraction 
  //    "bfixed" : not to fit a constant level b (b=0 fixed)
  //    "opt": timing interpolation are made following P.Bertins's method 
  //
  // If rawtimes is non null (default variable), raw times of the waveform analysis
  //can be found as follows :
  //  rawtimes[0]=raw fit time of first pulse (integer) //-999 if 0 pulses found
  //  rawtimes[1]=t1+P.Bertin's corrections //-999 if rawtimes[0]=-999 and rawtimes[1]=rawtimes[0] 
  //              if at one of the FirstWindow edges
  //  rawtimes[2]=t1+P.Bertin's corrections+HRS corrections//=rawtimes[1] if HRS
  //              corrections not available
  //  rawtimes[3]=raw fit time of second pulse (integer) //-999 if no second pulse fit
  //  rawtimes[4]=t2+P.Bertin's corrections //-999 if rawtimes[3]=-999 and rawtimes[4]=rawtimes[3] 
  //              is at one of the SecondWindow edges
  //  rawtimes[5]=t2+P.Bertin's corrections+HRS corrections//=rawtimes[4] if HRS
  //              corrections not available
  //The array rawtimes must be allocated by the user before calling this method, and must have at
  //least dimension 6 (beware of a potential memory leak if you allocate the array within the event
  //loop). The difference between TARSWave::GetArrivalTime1() and rawtimes[2],
  //and between TARSWave::GetArrivalTime2() and rawtimes[5] is due to block by block corrections
  //(only implemented for the calorimeter at this moment).
  //  
  // NB1: For the moment, the option "bfixed" is only implemented when fitting one pulse.
  //      If this option is used and the fit of one pulse is not good enough, the fit
  //      of two pulses will fit a constant level b also.
  // NB2: For the moment, the option "bfixed" computes the determinant of a 2x2 every
  //      time the method is called. If this option is to be used in production mode,
  //      the determinant should be saved in a data member.

  TString option=opt;

  if(option.Contains("data")){
    if(!fgIsInitShapeAnalysis) InitShapeAnalysis();
    //I don't know why we need to do that everytime. To be removed...
    if(!fa) {
      fga=new Double_t[2];
      fa=fga;
    }
    if(!ft) {
      fgt=new Double_t[2];
      ft=fgt;
    }
  }

  if(option.Contains("LED")){
    if(!fgIsInitShapeAnalysisLED) InitShapeAnalysisLED();

    //I don't know why we need to do that everytime. To be removed...
    if(!fa) fa=new Double_t[2];
    if(!ft) ft=new Double_t[2];
    //////////////////////////////
  }

//   if(!fa) fa=new Double_t[2];
//   if(!ft) ft=new Double_t[2];

//We correct timing of WF analysis windows
  
  Double_t fk1maxini=fk1max, fk1minini=fk1min, fk1max2ini=fk1max2, fk1min2ini=fk1min2, fk2maxini=fk2max, fk2minini=fk2min;
  Double_t fminchi2ini=fminchi2, fmaxchi2ini=fmaxchi2; 
  
  if(gdvcs->TimeCorIsInit()) {
    Double_t cor=gdvcs->GetTimeCor();
    cor-=GetARSCor();

    fk1max=TMath::Min(TMath::Max(Int_t(fk1max-cor+0.5),fgk1min),fgk1max); 
    fk1max2=TMath::Min(TMath::Max(Int_t(fk1max2-cor+0.5),fgk1min2),fgk1max2); 
    fk2max=TMath::Min(TMath::Max(Int_t(fk2max-cor+0.5),fgk2min),fgk2max); 

    fk1min=TMath::Max(TMath::Min(Int_t(fk1min-cor+0.5),fgk1max),fgk1min); 
    fk1min2=TMath::Max(TMath::Min(Int_t(fk1min2-cor+0.5),fgk1max2),fgk1min2); 
    fk2min=TMath::Max(TMath::Min(Int_t(fk2min-cor+0.5),fgk2max),fgk2min); 
    
    fminchi2=TMath::Max(0,TMath::Min(Int_t(fgminref[fNbChannel]+fminchi2+cor+0.5),128)); 
    fmaxchi2=TMath::Min(128,TMath::Max(Int_t(fgminref[fNbChannel]+fmaxchi2+cor+0.5),0));
  }
  
  if(rawtimes) {for(Int_t i=0;i<6;i++) rawtimes[i]=-999;}
  fAnalyzed=kTRUE;

//   cout<<"Checks "<<fNbChannel<<endl;
//   cout<<"First window "<<fk1min<<" "<<fk1max<<endl;
//   cout<<"Second window "<<fk1min2<<" "<<fk1max2<<" "<<fk2min<<" "<<fk2max<<endl;
//   cout<<"Chi2window "<<fminchi2<<" "<<fmaxchi2<<endl;
//   cout<<"Resolution "<<fgReso[fNbChannel]<<endl;
//   cout<<"Analysis window "<<fmin[fNbChannel]<<" "<<fmax[fNbChannel]<<endl;
//   cout<<"Cor "<<gdvcs->GetTimeCor()<<" "<<gdvcs->GetARSCor(fNbChannel)<<endl;

  Fit0Pulse(fb,fchi2,option.Data());
  //cout<<fchi2<<endl;
  if(fchi2<fchi20[fNbChannel]){
    // cout<<"There are no pulses"<<endl;
    //cout<<fchi2<<endl;
    fNPulse=0;
  }else{
    Fit1Pulse(fa[0],ft[0],fb,fchi2,option.Data(),rawtimes);
    if(fchi2<fchi21[fNbChannel]){
      // cout<<"There is 1 pulse"<<endl;
      //cout<<fchi2<<endl;
      fNPulse=1;
    }else{
      if(option.Contains("data")){
	Int_t test=Fit2Pulses(fa[0],fa[1],ft[0],ft[1],fb,fchi2,option.Data(),rawtimes);
	if(test==1) {fNPulse=1;
	fk1max=fk1maxini; fk1min=fk1minini; fk1max2=fk1max2ini; fk1min2=fk1min2ini; fk2max=fk2maxini;fk2min=fk2minini;fmaxchi2=fmaxchi2ini;fminchi2=fminchi2ini;
	return 1;
	}
	if(fchi2<fchi22[fNbChannel]){
	  //	  cout<<"There are 2 pulses"<<endl;
	  // cout<<fchi2<<endl;
	  fNPulse=2;
	}else{
	  //	  cout<<"There are MORE than 2 pulses"<<endl;
	  fNPulse=3;
	}
      }else{
	//cout<<"There are MORE than 1 pulses"<<endl;
	  fNPulse=3;
      }
    }
  }
  //  fAnalyzed=kTRUE;
  fk1max=fk1maxini; fk1min=fk1minini; fk1max2=fk1max2ini; fk1min2=fk1min2ini; fk2max=fk2maxini; fk2min=fk2minini; fmaxchi2=fmaxchi2ini;fminchi2=fminchi2ini;
  return 0;
}

 //_____________________________________________________________________________
void TARSWave::SetFirstWindow(Int_t min, Int_t max, const char* opt, Bool_t kFORCE)
{
  TString option=opt;

  if(option.Contains("data")){
    if(!fgIsInitShapeAnalysis) InitShapeAnalysis();
  }

  if(option.Contains("LED")){
    if(!fgIsInitShapeAnalysisLED) InitShapeAnalysisLED();
  }

  TARSBase::SetFirstWindow(min,max,opt,kFORCE);

  if(!fgX1) fgX1=new TMatrixD(2,1);
  if(!fgP1) fgP1=new TMatrixD(2,1);
}

 //_____________________________________________________________________________
void TARSWave::SetSecondWindow(Int_t min1, Int_t max1, Int_t min2, Int_t max2, const char* opt, Bool_t kFORCE)
{
  TString option=opt;

  if(option.Contains("data")){
    if(!fgIsInitShapeAnalysis) InitShapeAnalysis();
  }
  
  if(option.Contains("LED")){
    if(!fgIsInitShapeAnalysisLED) InitShapeAnalysisLED();
  }
  
  TARSBase::SetSecondWindow(min1,max1,min2,max2,opt,kFORCE);
  if(!fgX2) fgX2=new TMatrixD(3,1);
  if(!fgP2) fgP2=new TMatrixD(3,1);
}

//_____________________________________________________________________________
TDoubleArray* TARSWave::GetFit(const char* opt)
{
  //It returns an array with the fit waveform.
  //We need to specify the opt "data" or "LED" according to the analyze
  //method used.

  TString option=opt;
  if(fAnalyzed){
    TDoubleArray *ref=0;
    if(option.Contains("data")) {
      ref=(TDoubleArray*)fgRefShapes->UncheckedAt(fNbChannel);
    }
    if(option.Contains("LED")) {
      ref=(TDoubleArray*)fgRefShapesLED->UncheckedAt(fNbChannel);
    }
    if(!fFit) fFit=new TDoubleArray(fNbSamples);
    Double_t b=GetB();
    Double_t a1=GetAmplitude1();
    Double_t a2=GetAmplitude2();
    Double_t t1=GetArrivalTime1();
    Double_t t2=GetArrivalTime2();
    if(fNPulse>0) {
      if(gdvcs->TimeCorIsInit()) t1-=gdvcs->GetTimeCor();
      t1+=GetARSCor();
      t1=Int_t(t1+0.5);
    }
    if(fNPulse>1) {
      if(gdvcs->TimeCorIsInit()) t2-=gdvcs->GetTimeCor();
      t2+=GetARSCor();
      t2=Int_t(t2+0.5);
    }
    for(Int_t i=0;i<fNbSamples;i++){
      Double_t val=b;
      if(i+t1>-1 && i+t1<128) val+=ref->GetValue(i+t1)*a1;
      if(i+t2>-1 && i+t2<128) val+=ref->GetValue(i+t2)*a2;
      fFit->SetValue(i,val);
    }
    return fFit;
  }else{
    cout<<"This TARSWave is not analyzed"<<endl;
    return 0;
  }
}

//_____________________________________________________________________________
void TARSWave::SetNbChannel(Int_t n, const char* detector="CALO")
{
  TString dec=detector;
  fNbChannel=n;
  if(dec.Contains("PA")&&fgCaloWF==kTRUE) fNbChannel+=fNbChannelsCalo;
  if(dec.Contains("Veto")&&fgPAWF==kTRUE) fNbChannel+=fNbChannelsPA;

}

//_____________________________________________________________________________
Int_t TARSWave::GetNbChannel(Int_t n, const char* detector="CALO")
{

  TString dec=detector;
  Int_t val=n;
  if(dec.Contains("PA")&&fgCaloWF==kTRUE) val+=fNbChannelsCalo;
  if(dec.Contains("Veto")&&fgPAWF==kTRUE) val+=fNbChannelsPA;
  return val;

}

//_____________________________________________________________________________
Int_t TARSWave::Fit2Pulses(Double_t& a1, Double_t& a2, Double_t& t1, Double_t& t2, Double_t& b, Double_t& chi2, const char* opt, Double_t *rawtimes)
{
  // Fits 2 pulses...
  Double_t a1tmp,a2tmp,t1tmp,t2tmp,btmp,chi2tmp;

  TString option=opt;

  if(!fgIsInitShapeAnalysis && !fgIsInitShapeAnalysisLED) {
    cout<<"ERROR : Neither shape analysis parameters or shape analysis LED parameters are initialized"<<endl;
  }

  chi2tmp=10e10;t1tmp=-1000.;t2tmp=-1000.;a1tmp=-1000.;a2tmp=-1000.;btmp=-1000.;
  Double_t shift1=0.,shift2=0.;

  Double_t chi2ar[fk1max2-fk1min2+1][fk2max-fk2min+1], aar[fk1max2-fk1min2+1][fk2max-fk2min+1];

  TDoubleArray *ref=0;
  TDoubleArray *array=fData;
  if(option.Contains("data")) {
    ref=(TDoubleArray*)fgRefShapes->UncheckedAt(fNbChannel);
  }
  if(option.Contains("LED")) {
    ref=(TDoubleArray*)fgRefShapesLED->UncheckedAt(fNbChannel);
  }
  if(option.Contains("wave")) array=fWave;

  for(Int_t k=fk1min2;k<fk1max2+1;k++){//////////////////////////
    for(Int_t m=fk2min;m<fk2max+1;m++){////////////////////////
      for(Int_t i=0;i<3;i++) fgval2[i]=0.;
      for(Int_t i=fmin[fNbChannel];i<fmax[fNbChannel];i++){
	fgval2[0]+=array->GetValue(i)/fgpedsigma2[fNbChannel][i];
	if(i+m<128 && i+m>-1) fgval2[1]+=array->GetValue(i)*ref->GetValue(i+m)/fgpedsigma2[fNbChannel][i];
	if(i+k<128 && i+k>-1) fgval2[2]+=array->GetValue(i)*ref->GetValue(i+k)/fgpedsigma2[fNbChannel][i];
      }
      if(fgbfixed) fgval2[0]=0.;
      fgX2->SetMatrixArray(fgval2);
      //      cout<<"dd "<<fgM2[fNbChannel][k+fmax][m+fmax]<<endl;
      fgP2->Mult(*fgM2[fNbChannel][k+fmax[fNbChannel]][m+fmax[fNbChannel]],*fgX2);
      fgsol2=fgP2->GetMatrixArray();
      Double_t chitmp=0.;
      for(Int_t is=fmin[fNbChannel];is<fmax[fNbChannel];is++){
	if((is+k)<fNbSamples && (is+k)>-1) {
	  shift1=ref->GetValue(is+k);
	}else{
	  shift1=0.;
	}
	if((is+m)<fNbSamples && (is+m)>-1) {
	  shift2=ref->GetValue(is+m);
	}else{
	  shift2=0.;
	}
	if(is>(fminchi2-1) && is<fmaxchi2) chitmp+=TMath::Power(array->GetValue(is)-fgsol2[0]*shift1-fgsol2[1]*shift2-fgsol2[2],2.)/fgpedsigma2[fNbChannel][is];
      }
      chi2ar[k-fk1min2][m-fk2min]=chitmp;
      //???????      aar[k-fk1min][m-fk2min]=;

      if(chitmp<chi2tmp) {
	chi2tmp=chitmp;    
	t1tmp=k;
	t2tmp=m;
	a1tmp=fgsol2[0];
	a2tmp=fgsol2[1];
	btmp=fgsol2[2];
      }
    }
  }

  if(TMath::Abs(t1tmp-t2tmp)<fgReso[fNbChannel]) return 1;

  chi2=chi2tmp;t1=t1tmp;t2=t2tmp;a1=a1tmp;a2=a2tmp;b=btmp;
  if(t1==fk1min2||t1==fk1max2) a1=0; //If pulse at the edge of window, returns amplitude 0
  if(t2==fk2min||t2==fk2max) a2=0; //If pulse at the edge of window, returns amplitude 0

  Double_t eps1=0,eps2=0;
  if(t1>fk1min2 && t1<fk1max2){
    eps1=0.5*(chi2ar[Int_t(t1)-fk1min2+1][Int_t(t2)-fk2min]-chi2ar[Int_t(t1)-fk1min2-1][Int_t(t2)-fk2min])/(chi2ar[Int_t(t1)-fk1min2+1][Int_t(t2)-fk2min]+chi2ar[Int_t(t1)-fk1min2-1][Int_t(t2)-fk2min]-2.*chi2);
  }
  if(t2>fk2min && t2<fk2max){
    eps2=0.5*(chi2ar[Int_t(t1)-fk1min2][Int_t(t2)-fk2min+1]-chi2ar[Int_t(t1)-fk1min2][Int_t(t2)-fk2min-1])/(chi2ar[Int_t(t1)-fk1min2][Int_t(t2)-fk2min+1]+chi2ar[Int_t(t1)-fk1min2][Int_t(t2)-fk2min-1]-2.*chi2);
  }
  if(rawtimes) {rawtimes[0]=t1;rawtimes[3]=t2;}
  if(option.Contains("opt")) {
    t1-=eps1;
    t2-=eps2;
  }
  if(rawtimes) {rawtimes[1]=t1;rawtimes[4]=t2;}
  if(gdvcs->TimeCorIsInit()){
    t1+=gdvcs->GetTimeCor();
    if(rawtimes) rawtimes[2]=t1;
    t1-=GetARSCor();
    
    t2+=gdvcs->GetTimeCor();
    if(rawtimes) rawtimes[5]=t2;
    t2-=GetARSCor();
  }else{
    if(rawtimes){rawtimes[2]=0;rawtimes[5]=0;}
  }
  chi2=chi2/(fmax[fNbChannel]-fmin[fNbChannel]-3);
  return 0;
}

//_____________________________________________________________________________
void TARSWave::Fit1Pulse(Double_t& a, Double_t& t, Double_t& b, Double_t& chi2, const char* opt, Double_t *rawtimes)
{
  // Fits one pulse...
  //
  // If opt contains :
  //    "LED" : LED reference shape used
  //    "data": data reference shape used
  //    "wave": to analyze wave with no pedestal substraction 
  //    "bfixed" : not to fit a constant level b (b=0 fixed)
  //
  // NB : For the moment, the option "bfixed" computes the determinant of a 2x2 every
  //      time the method is called. If this option is to be used in production mode,
  //      the determinant should be saved in a data member.

  TString option=opt;
  if(!fgIsInitShapeAnalysis && !fgIsInitShapeAnalysisLED) {
    cout<<"ERROR : Neither shape analysis parameters or shape analysis LED parameters are initialized"<<endl;
  }
  chi2=10e10;
  t=-1000.;
  a=-1000.;
  b=-1000.;

  Double_t chi2ar[fk1max-fk1min+1], aar[fk1max-fk1min+1];

  Double_t shift1=0.,amp=0.;
  TDoubleArray *ref=0;
  TDoubleArray *array=fData;
  if(option.Contains("data")) {
    ref=(TDoubleArray*)fgRefShapes->UncheckedAt(fNbChannel);
  }
  if(option.Contains("LED")) {
    ref=(TDoubleArray*)fgRefShapesLED->UncheckedAt(fNbChannel);
  }
  if(option.Contains("wave")) array=fWave;
  
  for(Int_t k=fk1min;k<fk1max+1;k++){//////////////////////////
    for(Int_t i=0;i<2;i++) fgval1[i]=0.;
    for(Int_t i=fmin[fNbChannel];i<fmax[fNbChannel];i++){
      fgval1[0]+=array->GetValue(i)/fgpedsigma2[fNbChannel][i];
      if(i+k<128 && i+k>-1) fgval1[1]+=array->GetValue(i)*ref->GetValue(i+k)/fgpedsigma2[fNbChannel][i];
    }
    fgX1->SetMatrixArray(fgval1);
    if(option.Contains("data")) fgP1->Mult(*fgM1[fNbChannel][k+fmax[fNbChannel]],*fgX1);
    if(option.Contains("LED")) fgP1->Mult(*fgM1LED[fNbChannel][k+fmax[fNbChannel]],*fgX1);
    fgsol1=fgP1->GetMatrixArray();
    Double_t chitmp=0.;

    for(Int_t is=fmin[fNbChannel];is<fmax[fNbChannel];is++){
      if((is+k)<fNbSamples && (is+k)>-1) {
	shift1=ref->GetValue(is+k);
      }else{
	shift1=0.;
      }
      if(option.Contains("bfixed")==kFALSE || fgbfixed==kFALSE){
	if(is>(fminchi2-1) && is<fmaxchi2) chitmp+=TMath::Power(array->GetValue(is)-fgsol1[0]*shift1-fgsol1[1],2.)/fgpedsigma2[fNbChannel][is];
      }
      if(option.Contains("bfixed")||fgbfixed==kTRUE){
	if(option.Contains("LED")){
	  Double_t x=fgval1[1];
	  Double_t *mele=fgM1LED[fNbChannel][k+fmax[fNbChannel]]->GetMatrixArray();
	  amp=-x*fgM1LED[fNbChannel][k+fmax[fNbChannel]]->Determinant()/mele[2];
	  if(is>(fminchi2-1) && is<fmaxchi2) chitmp+=TMath::Power(array->GetValue(is)-amp*shift1,2.)/fgpedsigma2[fNbChannel][is];
	}
	if(option.Contains("data")){
	  Double_t x=fgval1[1];
	  Double_t *mele=fgM1[fNbChannel][k+fmax[fNbChannel]]->GetMatrixArray();
	  amp=-x*fgM1[fNbChannel][k+fmax[fNbChannel]]->Determinant()/mele[2];
	  if(is>(fminchi2-1) && is<fmaxchi2) chitmp+=TMath::Power(array->GetValue(is)-amp*shift1,2.)/fgpedsigma2[fNbChannel][is];
	}     
      }
    }
    chi2ar[k-fk1min]=chitmp;
    aar[k-fk1min]=fgsol1[0];
    if(chitmp<chi2) {
      chi2=chitmp;    
      t=k;
      a=fgsol1[0];
      b=fgsol1[1];
      if(option.Contains("bfixed") || fgbfixed==kTRUE) {a=amp;b=0.;}
    }
  }
  if(t==fk1min||t==fk1max) a=0.; //If result at window edges, returns 0 amplitude
  Double_t eps=0;
  if(t>fk1min && t<fk1max){
    eps=0.5*(chi2ar[Int_t(t)-fk1min+1]-chi2ar[Int_t(t)-fk1min-1])/(chi2ar[Int_t(t)-fk1min+1]+chi2ar[Int_t(t)-fk1min-1]-2.*chi2);
  }
  if(rawtimes) rawtimes[0]=t;
  if(option.Contains("opt")) t-=eps;
  if(rawtimes) rawtimes[1]=t;
  if(gdvcs->TimeCorIsInit()){
  t+=gdvcs->GetTimeCor();
  if(rawtimes) rawtimes[2]=t;
  //  cout<<fNbChannel<<endl;
  t-=GetARSCor();
  }else{
    if(rawtimes) rawtimes[2]=0;
  }
  chi2=chi2/(fmax[fNbChannel]-fmin[fNbChannel]-2);
}


//_____________________________________________________________________________
void TARSWave::Fit0Pulse(Double_t& b, Double_t& chi2, const char* opt)
{
  // Fits a baseline

  TString option=opt;
  chi2=0.;

  if(!fgIsInitShapeAnalysis && !fgIsInitShapeAnalysisLED) {
    cout<<"ERROR : Neither shape analysis parameters or shape analysis LED parameters are initialized"<<endl;
  }

  Double_t num=0.,dem=0.;
  TDoubleArray *array=fData;
  if(option.Contains("wave")) array=fWave;
    for(Int_t i=fmin[fNbChannel];i<fmax[fNbChannel];i++){
      num+=array->GetValue(i)/fgpedsigma2[fNbChannel][i];
      dem+=1./fgpedsigma2[fNbChannel][i];
    }
    b=num/dem;
    for(Int_t is=fminchi2;is<fmaxchi2;is++){
      chi2+=TMath::Power(array->GetValue(is)-b,2.)/fgpedsigma2[fNbChannel][is];
    }
    chi2=chi2/(fmax[fNbChannel]-fmin[fNbChannel]-1);
}

//_____________________________________________________________________________
Double_t TARSWave::GetChi2(void)
{
  // Returns the current chi2 of the fit (in the case where more than 2 pulses
  //are found a information message is printed)

  if(!fAnalyzed) {
    cout<<"This TARSWave is not analyzed"<<endl;
    return 0.;
  }else{
    if(fNPulse==3)
      cout<<"There are more than 2 pulses in this TARSWave!"<<endl;
    return fchi2;
  }
}

//_____________________________________________________________________________
Double_t TARSWave::GetB(void)
{
  // Returns the baseline of the fit (in the case where more than 2 pulses
  //are found a information message is printed)

  if(!fAnalyzed) {
    cout<<"This TARSWave is not analyzed"<<endl;
    return 0.;
  }else{
    if(fNPulse>=0) {
      return fb;
      if(fNPulse==3){
	cout<<"There are more than 2 pulses in this TARSWave!"<<endl;
	cout<<"This value is of b is not confident"<<endl;
      }
    }
  }
}

//_____________________________________________________________________________
Double_t TARSWave::GetAmplitude1(void)
{
  // Returns the amplitude of the first pulse found (when there is one)
  if(!fAnalyzed) {
    cout<<"This TARSWave is not analyzed"<<endl;
    return 0.;
  }else{
    if(fNPulse>0) {
      return fa[0];
    }else{
      //      cout<<"There is 0 pulse found ! -> No amplitude "<<endl;
      return 0.;
    }
  } 
}


//_____________________________________________________________________________
Double_t TARSWave::GetArrivalTime1(void)
{
  // Returns the arrival time of the first pulse found (when there is one)

  if(!fAnalyzed) {
    cout<<"This TARSWave is not analyzed"<<endl;
    return 0.;
  }else{
    if(fNPulse>0){ 
      return ft[0];
    }else{
      //      cout<<"There is 0 pulse found ! -> No arrival time "<<endl;
      return 0.;
    }
  } 
}

//_____________________________________________________________________________
Double_t TARSWave::GetAmplitude2(void)
{

  // Returns the amplitude of the second pulse found (when there is one)

  if(!fAnalyzed) {
    cout<<"This TARSWave is not analyzed"<<endl;
    return 0.;
  }else{
    if(fNPulse>1) {
      return fa[1];
    }else{
      //     cout<<"This TARSWave does not have 2 pulses !"<<endl;
      return 0.;
  }
  }
  
}
//_____________________________________________________________________________
Double_t TARSWave::GetArrivalTime2(void)
{

  // Return the arrival time of the second pulse found (when there is one)

  if(!fAnalyzed) {
    cout<<"This TARSWave is not analyzed"<<endl;
    return 0.;
  }else{
    if(fNPulse>1) {
      return ft[1];
    }else{
      //cout<<"This TARSWave does not have 2 pulses !"<<endl;
      return 0.;
  }
  }
  
}

//_____________________________________________________________________________
TDouble* TARSWave::AddValue(Int_t n, Double_t v)
{
//    TClonesArray &waves = *fWave;
//    TDouble *val = new(waves[n]) TDouble(v);
//    return val;
}

//_____________________________________________________________________________
Double_t TARSWave::SetValue(Int_t n, Double_t v)
{
//    TDouble* val = (TDouble*)fWave->UncheckedAt(n);
//    val->SetValue(v);
//    return val;
  Double_t val=fWave->SetValue(n,v);
  return val;
}

//_____________________________________________________________________________
void TARSWave::Reset(void)
{
  //  fWave->Clear("C");
  //  fWave->Delete();
  delete fWave;
  delete fData;
//    for(Int_t i=0;i<fWave->GetEntries();i++){
//      TDouble* val = (TDouble*)fWave->UncheckedAt(i);
//      delete val;
//    }
//    fWave->Clear();
}

//_____________________________________________________________________________
void TARSWave::Clear(Option_t *option)
{
  //  fWave->Clear("C");
  fWave->Clear();
  fData->Clear();
  //  delete fWave;
//    for(Int_t i=0;i<fWave->GetEntries();i++){
//      TDouble* val = (TDouble*)fWave->UncheckedAt(i);
//      delete val;
//    }
//    fWave->Clear();
}

//_____________________________________________________________________________
void TARSWave::DrawRaw(TPad *canvas, const char* opt, Float_t min, Float_t max)
{
  // Draws the ARSWave (without the pedestal substraction) in canvas

  fWave->Draw(canvas,min,max,opt);
}
//_____________________________________________________________________________
void TARSWave::DrawSignal(TPad *canvas, const char* opt, Float_t min, Float_t max)
{
  // Draws the ARSWave (without the pedestal substraction) in canvas

  fData->Draw(canvas,min,max,opt);
}

//_____________________________________________________________________________
 TARSWave::~TARSWave()
{
  cout<<"ARSWave destructor "<<this<<endl; 
//   delete fWave;
//   delete fData;
}

