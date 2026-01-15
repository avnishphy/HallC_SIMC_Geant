
#include <iostream>
#include <stdlib.h>
#include "TARSWave2.h"
#include "TMath.h"
#include "TDVCSDB.h"

ClassImp(TARSWave2)

 TARSWave2::TARSWave2()
{
  //
  /*fChan=Nchan;
  fRun=run;
  //
  TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,"munoz","");
  refshape=db->GetEntry_d(Form("CALO_calib_ARSRefShape%d",Nchan),run);
  shape=new Double_t[128];
  fit=new Double_t[128];

  // Converting energy thresholds to channel thresholds
  // (Carlos 02/11/11)
  Float_t *coef=db->GetEntry_f("CALO_calib_ARSWaveCalib",run);
  Double_t area=0.;
  for(Int_t i=0;i<128;i++) area+=TMath::Power(refshape[i],2.);
  fEnergy2Chan=area/(coef[Nchan]*coef[Nchan]);
  ////////////////////////

  delete db;
  fRunningIsInit=kFALSE;
  *///Carlos


  refshape=new Double_t[128];
  shape=new Double_t[128];
  for(Int_t i=0;i<128;i++) refshape[i]=1.;
  for(Int_t i=30;i<40;i++) refshape[i]=-100.;
  fRunningIsInit=kFALSE;
  
} 
TARSWave2::TARSWave2(Int_t Nchan, Int_t run)
{

  fChan=Nchan;
  fRun=run;

  //Block mix correction
  if(Nchan==73) fChan=77;
  if(Nchan==77) fChan=73;


  //
  TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,"munoz","");
  //The reference shapes are already mixed for blocks 73 and 77. No need to undothe change.
  refshape=db->GetEntry_d(Form("CALO_calib_ARSRefShape%d",Nchan),run);
  shape=new Double_t[128];
  fit=new Double_t[128];

  
 // Converting energy thresholds to channel thresholds
  // (Carlos 02/11/11)
  Float_t *coef=db->GetEntry_f("CALO_calib_ARSWaveCalib",run);
  Double_t *coef2=db->GetEntry_d("CALO_calib_Pi0calib",run);
  Double_t cotemp=0, cotemp2=0;

  //cotemp=coef[77];
  //coef[77]=coef[73];
  //coef[73]=cotemp;
 
  //cotemp2=coef2[77];
  //coef2[77]=coef2[73];
  //coef2[73]=cotemp2;

  for(Int_t i=0;i<208;i++){
    coef[i]=coef[i]*coef2[i];
  }

  Double_t area=0.;
  for(Int_t i=0;i<128;i++) area+=TMath::Power(refshape[i],2.);
  fEnergy2Chan=area/(coef[fChan]*coef[fChan]);

  ///////////////////////
  //Double_t thres0=0, thres1=0;
  
  //thres0=0.021*0.021*fEnergy2Chan;
  //thres1=0.283*0.283*fEnergy2Chan;

  //cout<<thres1<<endl;

  delete db;
  fRunningIsInit=kFALSE;


} 

void TARSWave2::SetPars(void){

  
  TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,"munoz","");
  Double_t min=10000;
  Int_t mini=-1;
  for(Int_t i=5;i<123;i++) {
    if(refshape[i]<min) {
      min=refshape[i];
      mini=i;
    }
  }

  timecorr=db->GetEntry_f("CALO_calib_ARSTimeOffset",fRun); 
  Double_t  ftcorr=timecorr[fChan];
  //ftcorr=0;
  //for(Int_t y=0;y<208;y++) timecorr[y]=0;
  //if(fChan==73)cout<<ftcorr<<endl;
  //if(fChan==77)cout<<ftcorr<<endl;
  //ftcorr=0;
  Float_t half=0.5;
  if(ftcorr<0) half=-0.5;
 
  imin=TMath::Max(5,20+Int_t(ftcorr+half));//Check sign of ftcorr
  imax=TMath::Min(123,100+Int_t(ftcorr+half));//Check sign of ftcorr

  chi2min=TMath::Max(5,mini-20+Int_t(ftcorr+half));//Check sign of ftcorr
  chi2max=TMath::Min(123,mini+20+Int_t(ftcorr+half));//Check sign of tfcorr
 
  /*t1min=-40;
  t1max=40;
  t1minb=-40;
  t1maxb=40;*/
  
  t1min=-20+Int_t(ftcorr+half);
  t1max=25+Int_t(ftcorr+half);
  t1minb=-20+Int_t(ftcorr+half);
  t1maxb=25+Int_t(ftcorr+half);
  
  //We broaden second pulse fitting window
  //t2min=-20+Int_t(ftcorr+half);
  //t2max=25+Int_t(ftcorr+half);
  t2min=-40+Int_t(ftcorr+half);
  t2max=40+Int_t(ftcorr+half);
  //cout<<imin<<" "<<imax<<" "<<chi2min<<" "<<chi2max<<" "<<mini<<" "<<refshape[mini]<<endl;
  //cout<<t1min<<" "<<t1max<<" "<<t1minb<<" "<<t1maxb<<" "<<t2min<<" "<<t2max<<endl;
  
  delete db;

}

//////////////////////////////////////////////////////////////////////////////////////////////////

void TARSWave2::Initnobase(void){

  SetPars();

  fa1=0.;
  fa2=0.;
 matrix0=new Double_t[t1max-t1min];
  for(Int_t t1=t1min;t1<t1max;t1++){
    matrix0[t1-t1min]=0.;
    for(Int_t i=imin;i<imax;i++){
    if(i-t1<128 && i-t1>-1) matrix0[t1-t1min]+=refshape[i-t1]*refshape[i-t1];
    }
    if(matrix0[t1-t1min]!=0) matrix0[t1-t1min]=1/matrix0[t1-t1min];
  }
 
  //Matrix2
  matrix2nb=new TMatrixD**[t1maxb-t1minb];
    for(Int_t t1=t1minb;t1<t1maxb;t1++){
    matrix2nb[t1-t1minb]=new TMatrixD*[t2max-t2min];
    for(Int_t t2=t2min;t2<t2max;t2++){
      Double_t val[4];
      for(Int_t j=0;j<4;j++) val[j]=0.;
      matrix2nb[t1-t1minb][t2-t2min]=new TMatrixD(2,2);
      for(Int_t i=imin;i<imax;i++){
	if(i-t1<128 && i-t1>-1 && i-t2<128 && i-t2>-1) val[0]+=refshape[i-t1]*refshape[i-t2];
	if(i-t2<128 && i-t2>-1) val[1]+=refshape[i-t2]*refshape[i-t2];
 	if(i-t1<128 && i-t1>-1) val[2]+=refshape[i-t1]*refshape[i-t1];
      }//i
      val[3]=val[0];

      matrix2nb[t1-t1minb][t2-t2min]->SetMatrixArray(val); 
     
      if(matrix2nb[t1-t1minb][t2-t2min]->Determinant()!=0) matrix2nb[t1-t1minb][t2-t2min]->Invert();
    }//t2
  }
}


void TARSWave2::Init(void){

  SetPars();

  fa1=0.;
  fa2=0.;

  //Matrix 1
  matrix1=new TMatrixD*[t1max-t1min];
  matrix2=new TMatrixD**[t1maxb-t1minb];
   for(Int_t t1=t1min;t1<t1max;t1++){
    Double_t val[4];
    matrix1[t1-t1min]=new TMatrixD(2,2);
    for(Int_t j=0;j<4;j++) val[j]=0.;
    for(Int_t i=imin;i<imax;i++){
      if(i-t1<128 && i-t1>-1) val[0]+=refshape[i-t1];
      if(i-t1<128 && i-t1>-1) val[2]+=refshape[i-t1]*refshape[i-t1];
    }
    val[1]=imax-imin;
    val[3]=val[0];
    matrix1[t1-t1min]->SetMatrixArray(val);
    if(matrix1[t1-t1min]->Determinant()!=0) matrix1[t1-t1min]->Invert();
  }
  

   /*
  //Matrix2 this is the nobase matrix. 
  matrix2=new TMatrixD**[t1maxb-t1minb];
    for(Int_t t1=t1minb;t1<t1maxb;t1++){
    matrix2[t1-t1minb]=new TMatrixD*[t2max-t2min];
    for(Int_t t2=t2min;t2<t2max;t2++){
      Double_t val[4];
      for(Int_t j=0;j<4;j++) val[j]=0.;
      matrix2[t1-t1minb][t2-t2min]=new TMatrixD(2,2);
      for(Int_t i=imin;i<imax;i++){
	if(i-t1<128 && i-t1>-1 && i-t2<128 && i-t2>-1) val[0]+=refshape[i-t1]*refshape[i-t2];
	if(i-t2<128 && i-t2>-1) val[1]+=refshape[i-t2]*refshape[i-t2];
 	if(i-t1<128 && i-t1>-1) val[2]+=refshape[i-t1]*refshape[i-t1];
      }//i
      val[3]=val[0];

      matrix2[t1-t1minb][t2-t2min]->SetMatrixArray(val); 
     
      if(matrix2[t1-t1minb][t2-t2min]->Determinant()!=0) matrix2[t1-t1minb][t2-t2min]->Invert();
    }//t2
  }
   */

    
  for(Int_t t1=t1minb;t1<t1maxb;t1++){
    //Matrix 2
    matrix2[t1-t1minb]=new TMatrixD*[t2max-t2min];
    for(Int_t t2=t2min;t2<t2max;t2++){
      Double_t val2[9];
      for(Int_t j=0;j<9;j++) val2[j]=0.;
      matrix2[t1-t1minb][t2-t2min]=new TMatrixD(3,3);
      for(Int_t i=imin;i<imax;i++){
	//	if(i+t1<128 && i+t1+t1minb>-1) val2[0]+=refshape[i-t1];
	if(i-t1<128 && i-t1>-1) val2[0]+=refshape[i-t1];
	if(i-t1<128 && i-t1>-1) val2[6]+=refshape[i-t1]*refshape[i-t1];
	if(i-t2<128 && i-t2>-1) val2[1]+=refshape[i-t2];
	if(i-t1<128 && i-t1>-1 && i-t2<128 && i-t2>-1) val2[3]+=refshape[i-t1]*refshape[i-t2];
	//	if(i-t1<128 && i-t1>-1 && i+t2<128 && i+t2>-1) val2[3]+=refshape[i-t1]*refshape[i-t2];
	if(i-t2<128 && i-t2>-1) val2[4]+=refshape[i-t2]*refshape[i-t2]; 
      }//i
      val2[2]=imax-imin;
      val2[5]=val2[1];
      val2[7]=val2[3];
      val2[8]=val2[0];
    
      //val2[0]=0;
      //val2[1]=0;
      //val2[5]=0;
      //val2[8]=0;
      
      matrix2[t1-t1minb][t2-t2min]->SetMatrixArray(val2);

      if(matrix2[t1-t1minb][t2-t2min]->Determinant()!=0) matrix2[t1-t1minb][t2-t2min]->Invert();
    }//t2
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void TARSWave2::Reinit(){


  fa1=0.;
  fa2=0.;

  //Matrix 1
  for(Int_t t1=t1min;t1<t1max;t1++){
    Double_t val[4];
    for(Int_t j=0;j<4;j++) val[j]=0.;
    for(Int_t i=imin;i<imax;i++){
      if(i-t1<128 && i-t1>-1) val[0]+=refshape[i-t1];
      if(i-t1<128 && i-t1>-1) val[2]+=refshape[i-t1]*refshape[i-t1];
    }
    val[1]=imax-imin;
    val[3]=val[0];
    if(val[0]<1e99&&val[1]<1e99&&val[2]<1e99&&val[3]<1e99){
      matrix1[t1-t1min]->SetMatrixArray(val);
      if(matrix1[t1-t1min]->Determinant()!=0) matrix1[t1-t1min]->Invert();
    }
  }
  for(Int_t t1=t1minb;t1<t1maxb;t1++){
    //Matrix 2
    for(Int_t t2=t2min;t2<t2max;t2++){
      Double_t val2[9];
      for(Int_t j=0;j<9;j++) val2[j]=0.;
      for(Int_t i=imin;i<imax;i++){
	//	if(i+t1<128 && i+t1+t1minb>-1) val2[0]+=refshape[i-t1];
	if(i-t1<128 && i-t1>-1) val2[0]+=refshape[i-t1];
	if(i-t1<128 && i-t1>-1) val2[6]+=refshape[i-t1]*refshape[i-t1];
	if(i-t2<128 && i-t2>-1) val2[1]+=refshape[i-t2];
	//	if(i-t1<128 && i-t1>-1 && i+t2<128 && i+t2>-1) val2[3]+=refshape[i-t1]*refshape[i-t2];
	if(i-t1<128 && i-t1>-1 && i-t2<128 && i-t2>-1) val2[3]+=refshape[i-t1]*refshape[i-t2];
	if(i-t2<128 && i-t2>-1) val2[4]+=refshape[i-t2]*refshape[i-t2]; 
      }//i
      val2[2]=imax-imin;
      val2[5]=val2[1];
      val2[7]=val2[3];
      val2[8]=val2[0];
      if(val2[0]<1e99&&val2[1]<1e99&&val2[2]<1e99&&val2[3]<1e99&&val2[4]<1e99&&val2[5]<1e99&&val2[6]<1e99&&val2[7]<1e99&&val2[8]<1e99){
	matrix2[t1-t1minb][t2-t2min]->SetMatrixArray(val2);
	if(matrix2[t1-t1minb][t2-t2min]->Determinant()!=0) matrix2[t1-t1minb][t2-t2min]->Invert();
      }
   }//t2
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////

void TARSWave2::Add2RunningShape(Double_t amp, Int_t time)
{
  //Adds wave to the running shape of channel
 
//   cout<<"Befofe :"<<endl;
//   for(Int_t i=0;i<128;i++) cout<<refshape->GetValue(i)<<" ";
//   cout<<endl;

  if(time<128 && time>-127){
    if(!fRunningIsInit) {
      fRunningwei=new Double_t[128];
      for(Int_t i=0;i<128;i++) fRunningwei[i]=1;
    }
    fRunningIsInit =kTRUE;
  
    amp=1/amp;
    for(Int_t i=0;i<128;i++){
      Double_t current=refshape[i];
      Double_t sh=0.;
      if((i-time)>-1&&(i-time)<128) sh=shape[i-time];
      refshape[i]=(current*(fRunningwei[i]-1.)+amp*sh)/fRunningwei[i];
      fRunningwei[i]+=1.;
    }


    /*
    if(time>=0){
      for(Int_t i=0;i<128-time;i++){
	Double_t current=refshape[i];
	refshape[i]=(current*(fRunningwei[i]-1.)+amp*shape[i-time])/fRunningwei[i];
	fRunningwei[i]+=1.;
      }
    }else{
      for(Int_t i=-time;i<128;i++){
	Double_t current=refshape[i];
	refshape[i]=(current*(fRunningwei[i]-1.)+amp*shape[i-time])/fRunningwei[i];
	fRunningwei[i]+=1.;
      }
    }
    */
    Reinit();
  }
  
//   cout<<"After :"<<endl;
//   for(Int_t i=0;i<128;i++) cout<<refshape->GetValue(i)<<" ";
//   cout<<endl;

}  


/////////////////////////////////////////////////////////////////////////////////////////////////

Double_t TARSWave2::Fit0Pulse(void){

 Double_t chi2=0;

 for(Int_t i=0;i<128;i++){ 
 if(i>= imin && i<=imax) fb=fb+shape[i];
 }
 fb=fb/(imax-imin);

 for(Int_t i=0;i<128;i++){ 
 if(i>= chi2min && i<=chi2max) chi2+=TMath::Power(shape[i]-fb,2.);
 }
 return chi2;
}


Double_t TARSWave2::Fit1Pulsenobase(void){
  
        ft1=0;
        ft1n=0;
	ft2=0;
        ft2n=0;
	fa1=0;
        fa2=0;
        fb=0;
  Double_t chi2s[128];
  Int_t cont=0, tc=0;
  for(Int_t i=0;i<128;i++) chi2s[i]=0;

  Double_t chi2=1e100;
  for(Int_t t1=t1min;t1<t1max;t1++){//////////////////////////
    Double_t val=0;
    for(Int_t i=imin;i<imax;i++){
      if(i-t1<128 && i-t1>-1) val+=shape[i]*refshape[i-t1];
    }
    Double_t sol=val*matrix0[t1-t1min];
    Double_t chitmp=0.;
    for(Int_t i=imin;i<imax;i++){
      Double_t shift=0.;
      if(i-t1<128 && i-t1>-1) shift=refshape[i-t1];
      if(i>chi2min && i<chi2max) chitmp+=TMath::Power(shape[i]-sol*shift,2.);
    }

    chi2s[cont]=chitmp;
    if(chitmp<chi2) {
      chi2=chitmp;    
      ft1=t1;
      ft1n=t1;
      fa1=sol;
      tc=cont;
    }
    cont++;
  }///


  if(ft1==t1min||ft1==(t1max-1)){
     fa1=0.; //If result at window edges, returns 0 amplitude
     ft1=0.;
  }
  else{
  //Time interpolation
  if(chi2s[tc-1]!=0 || chi2s[tc+1]!=0){
  ft1=ft1+(chi2s[tc-1]-chi2s[tc+1])/(2*(chi2s[tc+1]+chi2s[tc-1]-2*chi2s[tc]));
  }
  }

  // cout<<fa1<<" "<<ft1<<" "<<fa2<<" "<<ft2<<" "<<fb<<" "<<chi2<<endl;
  return chi2;
  

}

Double_t TARSWave2::Fit2Pulsesnobase(void){
  
        ft1=0;
        ft1n=0;
        ft2=0;
        ft2n=0;
	fa1=0;
        fa2=0;
        fb=0;
        

  Double_t chi2s[128][128];
  Int_t cont=0, cont2=0, tc=0, tc2=0;
 
  for(Int_t i=0;i<128;i++){
    for(Int_t j=0;j<128;j++) chi2s[i][j]=0;
    }

  Double_t chi2=1e10;
  TMatrixD X2(2,1);
  TMatrixD P2(2,1);
  Double_t val[2];
  for(Int_t t1=t1minb;t1<t1maxb;t1++){//////////////////////////
    cont2=0;
     for(Int_t t2=t2min;t2<t2max;t2++){////////////////////////
      for(Int_t i=0;i<2;i++) val[i]=0.;
      for(Int_t i=imin;i<imax;i++){
	if(i-t2<128 && i-t2>-1) val[0]+=shape[i]*refshape[i-t2];
	if(i-t1<128 && i-t1>-1) val[1]+=shape[i]*refshape[i-t1];
      }
      X2.SetMatrixArray(val);
      P2.Mult(*matrix2nb[t1-t1minb][t2-t2min],X2);
      Double_t *sol=P2.GetMatrixArray();
      Double_t chitmp=0.;
      for(Int_t i=imin;i<imax;i++){
	Double_t shift1=0.,shift2=0.;
	if(i-t1<128 && i-t1>-1) shift1=refshape[i-t1];
	if(i-t2<128 && i-t2>-1) shift2=refshape[i-t2];
	if(i>chi2min && i<chi2max) chitmp+=TMath::Power(shape[i]-sol[0]*shift1-sol[1]*shift2,2.);
      }
      //      cout<<chitmp<<endl;

      chi2s[cont][cont2]=chitmp;
      //if(t1==29 && t2==9){
      if(chitmp<chi2) {
	//cout<<X2(2,0)<<endl;
        //cout<<X2(1,0)<<endl;
        //cout<<X2(0,0)<<endl;
        
        //cout<<(*matrix2[t1-t1minb][t2-t2min])(0,2)<<"  "<<(*matrix2[t1-t1minb][t2-t2min])(1,2)<<"  "<<(*matrix2[t1-t1minb][t2-t2min])(2,2)<<endl;
        //cout<<(*matrix2[t1-t1minb][t2-t2min])(0,1)<<"  "<<(*matrix2[t1-t1minb][t2-t2min])(1,1)<<"  "<<(*matrix2[t1-t1minb][t2-t2min])(2,1)<<endl;
        //cout<<(*matrix2[t1-t1minb][t2-t2min])(0,0)<<"  "<<(*matrix2[t1-t1minb][t2-t2min])(1,0)<<"  "<<(*matrix2[t1-t1minb][t2-t2min])(2,0)<<endl;

	chi2=chitmp;    
	ft1=t1;
        ft1n=t1;
	ft2=t2;
        ft2n=t2;
	fa1=sol[0];
	fa2=sol[1];
	tc=cont;
        tc2=cont2;
      }
      cont2++; 
    }
    cont++;
  }

  if(ft1==t1min||ft1==(t1max-1)){
     fa1=0.; //If result at window edges, returns 0 amplitude
     ft1=0.;
  }
  else{
  //Time interpolation
  if(chi2s[tc-1][tc2]!=0 || chi2s[tc+1][tc2]!=0){
  ft1=ft1+(chi2s[tc-1][tc2]-chi2s[tc+1][tc2])/(2*(chi2s[tc+1][tc2]+chi2s[tc-1][tc2]-2*chi2s[tc][tc2]));
  }
  }
  if(ft2==t2min||ft2==(t2max-1)){
    fa2=0.;//If result at window edges, returns 0 amplitude
    ft2=ft1;
  }
  else{
   //Time interpolation
   if(chi2s[tc][tc2-1]!=0 || chi2s[tc][tc2+1]!=0){
  ft2=ft2+(chi2s[tc][tc2-1]-chi2s[tc][tc2+1])/(2*(chi2s[tc][tc2+1]+chi2s[tc][tc2-1]-2*chi2s[tc][tc2]));
  }
  }
  // cout<<fa1<<" "<<ft1<<" "<<fa2<<" "<<ft2<<" "<<fb<<" "<<chi2<<endl;
  return chi2;
}


Double_t TARSWave2::Fit1Pulse(void){
   ft1=0;
   ft1n=0;
   fa1=0;
   fb=0;

  Double_t chi2s[128];
  Int_t cont=0, tc=0;
  for(Int_t i=0;i<128;i++) chi2s[i]=0;

  Double_t chi2=1e100;
  TMatrixD X1(2,1);
  TMatrixD P1(2,1);
  for(Int_t t1=t1min;t1<t1max;t1++){//////////////////////////
    Double_t val[2];
    for(Int_t j=0;j<2;j++) val[j]=0.;
    for(Int_t i=imin;i<imax;i++){
      val[0]+=shape[i];
      if(i-t1<128 && i-t1>-1) val[1]+=shape[i]*refshape[i-t1];
    }
    X1.SetMatrixArray(val);
    P1.Mult(*matrix1[t1-t1min],X1);
    Double_t *sol=P1.GetMatrixArray();
    Double_t chitmp=0.;
    for(Int_t i=imin;i<imax;i++){
      Double_t shift=0.;
      if(i-t1<128 && i-t1>-1) shift=refshape[i-t1];
      if(i>chi2min && i<chi2max) chitmp+=TMath::Power(shape[i]-sol[0]*shift-sol[1],2.);
    }
    //if(t1==0){
    chi2s[cont]=chitmp;
    if(chitmp<chi2) {
      chi2=chitmp;    
      ft1=t1;
      ft1n=t1;
      fa1=sol[0];
      fb=sol[1];
      tc=cont;
      // }
    }
    cont++;
    }

if(ft1==t1min||ft1==(t1max-1)){
     fa1=0.; //If result at window edges, returns 0 amplitude
     ft1=0.;
  }
  else{
    //Time interpolation
    if(chi2s[tc-1]!=0 || chi2s[tc+1]!=0){
  ft1=ft1+(chi2s[tc-1]-chi2s[tc+1])/(2*(chi2s[tc+1]+chi2s[tc-1]-2*chi2s[tc]));
  }
  }
 
  //cout<<fa1<<" "<<ft1<<" "<<fa2<<" "<<ft2<<" "<<fb<<" "<<chi2<<endl;
  return chi2;

}


Double_t TARSWave2::Fit2Pulses(void){
  
        ft1=0;
        ft1n=0;
        ft2=0;
        ft2n=0;
	fa1=0;
        fa2=0;
        fb=0;

 Double_t chi2s[128][128];
  Int_t cont=0, cont2=0, tc=0, tc2=0;


  for(Int_t i=0;i<128;i++){
    for(Int_t j=0;j<128;j++) chi2s[i][j]=0;
    }

  Double_t chi2=1e10;
  TMatrixD X2(3,1);
  TMatrixD P2(3,1);
  Double_t val[3];
  for(Int_t t1=t1minb;t1<t1maxb;t1++){//////////////////////////
    cont2=0;
     for(Int_t t2=t2min;t2<t2max;t2++){////////////////////////
      for(Int_t i=0;i<3;i++) val[i]=0.;
      for(Int_t i=imin;i<imax;i++){
	val[0]+=shape[i];
	if(i-t2<128 && i-t2>-1) val[1]+=shape[i]*refshape[i-t2];
	if(i-t1<128 && i-t1>-1) val[2]+=shape[i]*refshape[i-t1];
      }
      X2.SetMatrixArray(val);
      P2.Mult(*matrix2[t1-t1minb][t2-t2min],X2);
      Double_t *sol=P2.GetMatrixArray();
      //sol[2]=0;
      Double_t chitmp=0.;
      for(Int_t i=imin;i<imax;i++){
	Double_t shift1=0.,shift2=0.;
	if(i-t1<128 && i-t1>-1) shift1=refshape[i-t1];
	if(i-t2<128 && i-t2>-1) shift2=refshape[i-t2];
	if(i>chi2min && i<chi2max) chitmp+=TMath::Power(shape[i]-sol[0]*shift1-sol[1]*shift2-sol[2],2.);
      }
      //      cout<<chitmp<<endl;
      // cout<<cont<<" cont "<<cont2<<" cont2 "<<endl;
      chi2s[cont][cont2]=chitmp;
      //if(t1==29 && t2==9){
      if(chitmp<chi2) {
       // cout<<X2(2,0)<<endl;
       // cout<<X2(1,0)<<endl;
       // cout<<X2(0,0)<<endl;
        
       // cout<<(*matrix2[t1-t1minb][t2-t2min])(0,2)<<"  "<<(*matrix2[t1-t1minb][t2-t2min])(1,2)<<"  "<<(*matrix2[t1-t1minb][t2-t2min])(2,2)<<endl;
       // cout<<(*matrix2[t1-t1minb][t2-t2min])(0,1)<<"  "<<(*matrix2[t1-t1minb][t2-t2min])(1,1)<<"  "<<(*matrix2[t1-t1minb][t2-t2min])(2,1)<<endl;
       // cout<<(*matrix2[t1-t1minb][t2-t2min])(0,0)<<"  "<<(*matrix2[t1-t1minb][t2-t2min])(1,0)<<"  "<<(*matrix2[t1-t1minb][t2-t2min])(2,0)<<endl;

	chi2=chitmp;    
	ft1=t1;
        ft1n=t1;
	ft2=t2;
        ft2n=t2;
	fa1=sol[0];
	fa2=sol[1];
	fb=sol[2];
	tc=cont;
        tc2=cont2;
      }
      cont2++; 
    }
    cont++;
  }
if(ft1==t1min||ft1==(t1max-1)){
     fa1=0.; //If result at window edges, returns 0 amplitude
     ft1=0.;

  }
  else{
    //Time interpolation
  if(chi2s[tc-1][tc2]!=0 || chi2s[tc+1][tc2]!=0){
  ft1=ft1+(chi2s[tc-1][tc2]-chi2s[tc+1][tc2])/(2*(chi2s[tc+1][tc2]+chi2s[tc-1][tc2]-2*chi2s[tc][tc2]));
  }
  }
if(ft2==t2min||ft2==(t2max-1)){
    fa2=0.;//If result at window edges, returns 0 amplitude
    ft2=ft1;
   }
 else{
   //Time interpolation
   if(chi2s[tc][tc2-1]!=0 || chi2s[tc][tc2+1]!=0){
  ft2=ft2+(chi2s[tc][tc2-1]-chi2s[tc][tc2+1])/(2*(chi2s[tc][tc2+1]+chi2s[tc][tc2-1]-2*chi2s[tc][tc2]));
  }
 }
   //cout<<fa1<<" "<<ft1<<" "<<fa2<<" "<<ft2<<" "<<fb<<" "<<chi2<<endl;
  return chi2;
}


Double_t TARSWave2::Baseline(void){
 
Double_t b=0.;

for(Int_t i=0;i<128;i++){ 
if((i>= imin)&&(i<=imax)){
   b=b+shape[i];
 }
 }
 b=b/(imax-imin);
 return b;
}


Double_t TARSWave2::Analyze(Double_t thres0,Double_t thres1, Int_t option){
  
// Converting energy thresholds to channel thresholds
  // (Carlos 02/11/11)
  thres0=thres0*thres0*fEnergy2Chan;
  thres1=thres1*thres1*fEnergy2Chan;
 
        ft1=0;
        ft1n=0;
	ft2=0;
        ft2n=0;
	fa1=0;
	fa2=0;
        fb=0;
        Double_t chi2bak=0, amp1=0, tim1=0, tim1n=0, tau=0, base=0;
	Int_t cho=0;

  Double_t chi2=Fit0Pulse();
 

  if(chi2>thres0){
    if(option==0) chi2=Fit1Pulse();
    if(option==1) chi2=Fit1Pulsenobase();
    if(option==2) chi2=Fit1Pulse();
 
  cho=1;
  amp1=fa1;
  //cout<<timecorr[fChan]<<" "<<fChan<<" "<<ft1<<endl;
  ft1=ft1-timecorr[fChan];//time correction
  tim1=ft1;
  tim1n=ft1n;
  base=fb;
  chi2bak=chi2;
  if(chi2>thres1){
     if(option==1) chi2=Fit2Pulses();
     if(option==0) chi2=Fit2Pulsesnobase();
     if(option==2) chi2=Fit2Pulses();

     //cout<<timecorr[fChan]<<" "<<fChan<<endl;
     ft1=ft1-timecorr[fChan];//Time correction
     ft2=ft2-timecorr[fChan];//Time correction
  
  cho=2;
   tau=ft1-ft2;
   if(tau<0) tau=-tau;
   if(tau<4){
     fa1=amp1;
     ft1=tim1;
     ft1n=tim1n;
     fa2=0;
     ft2=0;
     ft2n=0;
     fb=base;
     chi2=chi2bak;
    }
   }
  }
  return chi2;

}

Double_t* TARSWave2::GetFit(void){
  for(Int_t i=0;i<128;i++) fit[i]=0.;
  for(Int_t i=imin;i<imax;i++){
    Double_t shift1=0.; 
    if((i-ft1n<128) && (i-ft1n>-1)) shift1=refshape[i-Int_t(ft1n)];
    Double_t shift2=0.;
    if((i-ft2n<128) && (i-ft2n>-1)) shift2=refshape[i-Int_t(ft2n)];
    fit[i]=fa1*shift1+fa2*shift2+fb;
  }
  //cout<<fa1<<" "<<ft1<<" "<<fa2<<" "<<ft2<<" "<<fb<<" "<<"fit"<<endl;
  return fit;
}
Double_t* TARSWave2::GetFit1(void){
  Double_t *fit1=new Double_t[128];
  for(Int_t i=0;i<128;i++) fit1[i]=0.;
  for(Int_t i=imin;i<imax;i++){
    Double_t shift1=0.; 
    if((i-ft1n<128) && (i-ft1n>-1)) shift1=refshape[i-Int_t(ft1n)];
    Double_t shift2=0.;
    if((i-ft2n<128) && (i-ft2n>-1)) shift2=refshape[i-Int_t(ft2n)];
    fit1[i]=fa1*shift1;
  }
  //cout<<fa1<<" "<<ft1<<" "<<fa2<<" "<<ft2<<" "<<fb<<" "<<"fit"<<endl;
  return fit1;
}
Double_t* TARSWave2::GetFit2(void){
  Double_t *fit2=new Double_t[128];
  for(Int_t i=0;i<128;i++) fit2[i]=0.;
  for(Int_t i=imin;i<imax;i++){
    Double_t shift1=0.; 
    if((i-ft1n<128) && (i-ft1n>-1)) shift1=refshape[i-Int_t(ft1n)];
    Double_t shift2=0.;
    if((i-ft2n<128) && (i-ft2n>-1)) shift2=refshape[i-Int_t(ft2n)];
    fit2[i]=fa2*shift2;
  }
  //cout<<fa1<<" "<<ft1<<" "<<fa2<<" "<<ft2<<" "<<fb<<" "<<"fit"<<endl;
  return fit2;
}


TARSWave2::~TARSWave2()
{
  // Default destructor
}
