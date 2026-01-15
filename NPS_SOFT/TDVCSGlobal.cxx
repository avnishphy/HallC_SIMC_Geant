

#include "TDVCSGlobal.h"
//#include "./THaRun.h"
#include "TROOT.h"
#include "TString.h"
#include "TChain.h"
#include <iostream>
#include "TDVCSDB.h"
#include "TObjArray.h"
#include "TChainElement.h"


using namespace std;

Bool_t           TDVCSGlobal::fgTimeCorInit = kFALSE;
Bool_t           TDVCSGlobal::fgNoTimeCor = kTRUE;
TLeaf*        TDVCSGlobal::fgdp=0;
TLeaf*        TDVCSGlobal::fgs2y=0;
TLeaf*        TDVCSGlobal::fgs2rt=0;
TLeaf*        TDVCSGlobal::fgth=0;
TLeaf*        TDVCSGlobal::fgt6=0;
TLeaf*        TDVCSGlobal::fgtdcval=0;
Float_t*        TDVCSGlobal::fgcor0=0;
Float_t*        TDVCSGlobal::fgcor1=0;
Float_t*        TDVCSGlobal::fgcor1pa=0;
Float_t*        TDVCSGlobal::fgcor1veto=0;
Float_t*        TDVCSGlobal::fgcor2=0;
Float_t*        TDVCSGlobal::fgcor3=0;
Float_t*        TDVCSGlobal::fgcor4=0;
Float_t*       TDVCSGlobal::fgHRSCor_DVCS2;
Float_t*       TDVCSGlobal::fgCaloCor_DVCS2;
Float_t*       TDVCSGlobal::fgHRSCor_DVCS3;
Float_t*       TDVCSGlobal::fgCaloCor_DVCS3;
Float_t*       TDVCSGlobal::fgcor1_DVCS3;
Bool_t*         TDVCSGlobal::fgstatusCalo=0;
Bool_t*         TDVCSGlobal::fgstatusPA=0;
Bool_t*         TDVCSGlobal::fgstatusVeto=0;

TChain*     TDVCSGlobal::fgTree=0;

TDVCSGlobal::TDVCSGlobal(int v):run(v)
{
  if(!wave) wave=new TARSWave(128);
  //  wave->InitAnalysisWindowDB();
  fgTimeCorInit=kFALSE;
  caloev=0;
  ev=0;
  ha2=0;
  wave=0;
  //  vetoev=0;
  gTree=0;
  harun=0;
  currentfile="toto";
  run=9000;
  //  run=8015;
  kWF=kTRUE;
  minanawin=0;//default
  maxanawin=128;//default
  fgNoTimeCor=kTRUE;
  fgstatusCalo=new Bool_t[132];
  fgstatusPA=new Bool_t[100];
  fgstatusVeto=new Bool_t[57];
}

void TDVCSGlobal::GetStatusCALO(void){

  TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,"munoz","");
  Int_t *val=db->GetEntry_i("CALO_status",run);
  for(Int_t i=0;i<132;i++) fgstatusCalo[i]=val[i];
  delete val;
  delete db;
}
void TDVCSGlobal::GetStatusPA(void){

  TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,"munoz","");
  Int_t *val=db->GetEntry_i("PA_status",run);
  for(Int_t i=0;i<100;i++) fgstatusPA[i]=val[i];
  delete val;
  delete db;
}
void TDVCSGlobal::GetStatusVETO(void){

  TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,"munoz","");
  Int_t *val=db->GetEntry_i("VETO_status",run);
  for(Int_t i=0;i<57;i++) fgstatusVeto[i]=val[i];
  delete val;
  delete db;
}


void TDVCSGlobal::UpdateTimeCor(void){

  fgdp=fgTree->FindLeaf("L.tr.tg_dp");
  fgs2y=fgTree->FindLeaf("L.s2.try");
  fgs2rt=fgTree->FindLeaf("L.s2.rt");

  TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,"munoz","");
  Float_t *coef;  
  coef=db->GetEntry_f("HRS_calib_S2TDCCor",run);
  for(Int_t i=0;i<16;i++) fgcor0[i]=coef[i];
  delete coef;
  coef=db->GetEntry_f("CALO_calib_ARSTimeOffset",run);
  for(Int_t i=0;i<132;i++) fgcor1[i]=coef[i];
  delete coef;
  coef=db->GetEntry_f("HRS_calib_S2Cor",run);
  for(Int_t i=0;i<16;i++) fgcor2[i]=coef[i];
  delete coef;
  coef=db->GetEntry_f("HRS_calib_S2YCor",run);
  for(Int_t i=0;i<16;i++) fgcor3[i]=coef[i];
  delete coef;
  coef=db->GetEntry_f("HRS_calib_dPCor",run);
  for(Int_t i=0;i<16;i++) fgcor4[i]=coef[i];
  delete coef;
  delete db;

}


void TDVCSGlobal::Init(void){
  if(!caloev) caloev=new TCaloEvent();
  if(!ev) ev=new TDVCSEvent();
  if(!wave) wave=new TARSWave(128);
  //  wave->InitShapeAnalysis();

  //  harun=0;
}

void TDVCSGlobal::Print() {
  cout << "This is working "<< endl;
  cout<<fgdp->GetValue(0)<<endl;
}

Bool_t TDVCSGlobal::RunChange(const char*  filename) {

  //20190403(start)
  //temporarily commented out
  //
  // //  cout<<" init tme corr" <<fgTimeCorInit<<" "<<run<<" "<<filename<<endl;
  // if(run<6000){
  //   if(run!=GetRun(filename) && fgTimeCorInit==kTRUE) UpdateTimeCor();
  // }
  // else if(run>10000){
  //   if(run!=GetRun(filename) && fgTimeCorInit==kTRUE) UpdateTimeCor_DVCS3();
  // }
  // else{
  //   if(run!=GetRun(filename) && fgTimeCorInit==kTRUE) UpdateTimeCor_DVCS2();
  // }

  // //  cout<<"OK "<<GetRun(filename)<<endl;

  // if(GetRun(filename)!=-1 && run!=GetRun(filename)){
  //   run=GetRun(filename);
  //   return kTRUE;
  // }else{
  //   return kFALSE;
  // }
  //20190403(finish)
  
}

Double_t TDVCSGlobal::GetTimeCor3(Int_t block, Bool_t quiet){
  //Time corrections for DVCS3 (by Frederic)

  //Double_t corr=fgCaloCor_DVCS3[block]+0.5;//Correction to be substracted
  Double_t corr=fgCaloCor_DVCS3[block];//Correction to be substracted
  corr -=fgcor1_DVCS3[block];//ARS time offset to be added
  corr+=(Double_t(fgtdcval->GetValue(3)-fgtdcval->GetValue(7))/10.);

  // Determine s2ln : the number of the first hit paddle in S2 right
  Int_t s2lmult=0;
  Int_t s2ln=-1;
  Double_t x=1000.;

  for(Int_t i=0;i<16;i++){
    if(fgs2rt->GetValue(i)>80){
      s2lmult++;
    }
  }
  if(s2lmult>0){
    for(Int_t i=0;i<16;i++){
      if(TMath::Abs(fgs2rt->GetValue(i)-fgHRSCor_DVCS3[16*0+i])<x){
        s2ln=i;x=TMath::Abs(fgs2rt->GetValue(i)-fgHRSCor_DVCS3[16*0+i]);
      }
    }
  }
  
  if(s2ln>-1){
    corr+=fgHRSCor_DVCS3[16*3+s2ln]+fgHRSCor_DVCS3[16*2+s2ln]*fgs2y->GetValue(0);
    corr+=fgHRSCor_DVCS3[16*5+s2ln]+fgHRSCor_DVCS3[16*4+s2ln]*fgth->GetValue(0);
    corr+=fgHRSCor_DVCS3[16*7+s2ln]+fgHRSCor_DVCS3[16*6+s2ln]*fgdp->GetValue(0);
    corr+=fgHRSCor_DVCS3[16*8+s2ln]+fgHRSCor_DVCS3[16*1+s2ln];
  }

  if(TMath::Abs(corr)>5. && !quiet) {
    cout<<"Warning: time correction looks big: "<<corr<<" ns"<<endl;
    cout << "s2ln : " << s2ln << endl;
    cout<<"S2y : "<<fgs2y->GetValue(0)<<endl;
    cout<<"dP : "<<fgdp->GetValue(0)<<endl;
    cout<<"dth : "<<fgth->GetValue(0)<<endl;
    cout<<"(tdcval(3) - tdcval(7)) / 10. : " << (fgtdcval->GetValue(3)-fgtdcval->GetValue(7))/10.<<endl;
  }

  return corr;//to be substracted

}

Double_t TDVCSGlobal::GetTimeCor2(Int_t block, Bool_t quiet){
  //Time corrections for DVCS2
  

  //  cout<<fgCaloCor_DVCS2<<endl;
  Double_t corr=fgCaloCor_DVCS2[block];//Correction to be substracted

  // Determine s2ln : the number of the first hit paddle in S2 left
  Int_t s2lmult=0;
  for(Int_t i=0;i<16;i++){if(fgs2rt->GetValue(i)>50) s2lmult++;}
  //  cout<<"titi 2 time core"<<endl;
  Int_t s2ln=-1; Double_t x=1000;
  if(s2lmult>0){for(Int_t i=0;i<16;i++){if(TMath::Abs(fgs2rt->GetValue(i)-fgHRSCor_DVCS2[i])<x){
	s2ln=i;x=TMath::Abs(fgs2rt->GetValue(i)-fgHRSCor_DVCS2[i]);
      }}}

  if(s2ln>-1) {
    corr+=fgHRSCor_DVCS2[16+s2ln];
    corr+=fgHRSCor_DVCS2[16*2+s2ln*2+1]+fgHRSCor_DVCS2[16*2+s2ln*2]*fgs2y->GetValue(0);
    corr+=fgHRSCor_DVCS2[16*4+s2ln*2+1]+fgHRSCor_DVCS2[16*4+s2ln*2]*fgdp->GetValue(0);
    corr+=fgHRSCor_DVCS2[16*6+s2ln*2+1]+fgHRSCor_DVCS2[16*6+s2ln*2]*fgth->GetValue(0);
    corr+=fgHRSCor_DVCS2[16*8+s2ln*2+1]+fgHRSCor_DVCS2[16*8+s2ln*2]*fgt6->GetValue(0);
  }
  

  // cout<<"==================================================== "<<endl;
  // for(Int_t i=0;i<208;i++) cout<<fgCaloCor_DVCS2[i]<<endl;
  // for(Int_t i=0;i<160;i++) cout<<fgHRSCor_DVCS2[i]<<endl;

  if(TMath::Abs(corr)>5. && !quiet) {
    cout<<"Warning: time correction looks big: "<<corr<<" ns"<<endl;
    cout<<"S2y : "<<fgs2y->GetValue(0)<<endl;
    cout<<"dP : "<<fgdp->GetValue(0)<<endl;
    cout<<"dth : "<<fgth->GetValue(0)<<endl;
    cout<<"T6 : "<<fgt6->GetValue(0)<<endl;
  }

  return corr;//to be substracted
}

Double_t TDVCSGlobal::GetTimeCor(void){

  Int_t nbs2=-1; // S2 paddle number                                                                                     
  Float_t time=0; // time correction                                                                                     
  Int_t S2_mult=0; //S2 multiplicity                                                                                     
  Int_t min=100000;
  
  for(Int_t i=0;i<16;i++) {if(fgs2rt->GetValue(i)>100.) S2_mult++;}

  if(S2_mult>0){
    for(Int_t i=0;i<16;i++) {
      if (TMath::Abs(fgs2rt->GetValue(i)-fgcor0[i])<min) { nbs2=i; min=TMath::Abs(fgs2rt->GetValue(i)-fgcor0[i]);}
    }
    
    if(nbs2==-1) {cout<<"PROBLEM in calotimecor.h !!!!"<<endl;exit(1);}
    //    time-=fgcor1[nbc]; //ARS correction                                                                                      
    time-=fgcor2[nbs2]; // S2 paddle number correction                                                                       
    time-=fgcor3[nbs2]*(fgs2y->GetValue(0)); // y position in S2 paddles correction.                                                          
    time-=fgcor4[nbs2]*(fgdp->GetValue(0)); // dp correction                                                                                  
    
    return time;
  }
  
  if(S2_mult==0){
    //    time-=fgcor1[nbc];
    time-=150;
    
    return time;
  }
}

Int_t TDVCSGlobal::GetTree(const char*  treename){
  
  TString tree=treename;
  Bool_t kcaloev=0,kpaev=0,kvetoev=0,ktree=0;
  TKey *key;TBranch *br;
  TIter next(gFile->GetListOfKeys());
  TString sol="TTree";
  while ((key = (TKey *) next())) {
    TString s = key->GetClassName();
    if(s==sol) {
      TString name;
      if(tree=="all") {
	name=key->GetName();
      }else{
	name=tree;
      }
      TIter next2(((TTree*)gFile->Get(name.Data()))->GetListOfBranches());
      TString solcalo="TCaloEvent";
      TString solpa="TPAEvent";
      TString solveto="TVEvent";
      while ((br = (TBranch *) next2())) {
	TString s2 = br->GetClassName();
	if(s2==solcalo) {
	  caloev=(TCaloEvent*)br->GetAddress();
	  cout<<"TCaloEvent found at "<<caloev<<endl;
	  kcaloev=kTRUE;ktree=kTRUE;
	}
	if(s2==solpa) {
	  //	  paev=(TPAEvent*)br->GetAddress();
	  //	  cout<<"TPAEvent found at "<<paev<<endl;
	  kpaev=kTRUE;ktree=kTRUE;
	}
	if(s2==solveto) {
	  //	  vetoev=(TVEvent*)br->GetAddress();
	  //	  cout<<"TVEvent found at "<<vetoev<<endl;
	  kvetoev=kTRUE;ktree=kTRUE;
	}
      }
    }
  }
  if(!ktree) cout<<"ERROR: No tree found"<<endl;
  if(!kcaloev) cout<<"Warning: No TCaloEvent found in this file"<<endl;
  if(!kpaev) cout<<"Warning: No TPAEvent found in this file"<<endl;
  if(!kvetoev) cout<<"Warning: No TVEvent found in this file"<<endl;

}

void TDVCSGlobal::UpdateCalo(void){

  caloev->GetGeometry()->SetRun(run);
  caloev->GetGeometry()->InitPositionsDB();
  caloev->GetCalibration()->InitDB(run);
  caloev->GetParameters()->InitDB(run);
  GetStatusCALO();
  cout<<"Calorimeter geometry, parameters and calibration coefficients for run "<<run<<" loaded from mysql database."<<endl;

}

void TDVCSGlobal::UpdatePA(void){
  //  paev->GetCalibration()->InitDB(run);
  //paev->GetGeometry()->InitDB(run);
  cout<<"PA calibration and geometry for run "<<run<<" updated."<<endl;
  GetStatusPA();
}

void TDVCSGlobal::UpdateVeto(void){
  //  vetoev->GetCalibration()->InitDB(run);
  cout<<"Veto calibration for run "<<run<<" updated."<<endl;
  GetStatusVETO();
}

void TDVCSGlobal::UpdatePedestals(void){

  wave->InitPedDB(run);
  cout<<"ARS pedestals for run "<<run<<" loaded from mysql database."<<endl;

}

void TDVCSGlobal::UpdateDVCS(void){

  ev->GetGeometry()->SetRun(run);
  ev->GetGeometry()->InitDB();
  ev->GetParameters()->InitDB(run);
  cout<<"DVCS geometry and parameters for run "<<run<<" loaded from mysql database."<<endl;
}

void TDVCSGlobal::Update(const char*  filename){
 
  //20190403(start)
  //temporarily commented out
  //
  // Init();
  // //  cout<<"=======qdsfqd ===== "<<endl;
  // //RunChange(filename);
  // //cout<<" QQQQQQQ "<<endl;
  // if(RunChange(filename)) {
  //   cout<<"updating"<<endl;
  //   UpdatePedestals();
  //   UpdateDVCS();
  //   UpdateCalo();
  //   if(run<6000 && run>0){
  //   UpdatePA();
  //   UpdateVeto();
  //   }
  //   if(kWF) UpdateWFAna();
  //   if(run<6000 && run>0){
  //     if(fgTimeCorInit) UpdateTimeCor();
  //   }
  //   else if(run>10000){
  //     if(fgTimeCorInit) UpdateTimeCor_DVCS3();
  //   }
  //   else{
  //     if(fgTimeCorInit) UpdateTimeCor_DVCS2();
  //   }
  // }
  //20190403(finish)
}

void TDVCSGlobal::ForceUpdate(void){
  //20190403(start)
  //temporarily commented out because when using in geant4, it gives error
  //
  // Init();
  
  // UpdatePedestals();
  // UpdateDVCS();
  // UpdateCalo();
  // //  UpdatePA();
  // //UpdateVeto();
  // if(kWF) UpdateWFAna();
  // if(run<6000){
  //   if(fgTimeCorInit) UpdateTimeCor();
  // }
  // else if(run>10000){
  //   if(fgTimeCorInit) UpdateTimeCor_DVCS3();
  //   //UpdateTimeCor_DVCS3();
  // }
  // else{
  //   if(fgTimeCorInit) UpdateTimeCor_DVCS2();
  // }
  //20190403(finish)
}

void TDVCSGlobal::UpdateWFAna(void){
//   Double_t chi20=wave->GetChi20();
//   Double_t chi21=wave->GetChi21();
//   Double_t chi22=wave->GetChi22();
//  wave->SetAnalysisWindow(minanawin,maxanawin);
  TString line("garswave->InitShapeAnalysisDB(");line+=run;line+=");";
  gROOT->ProcessLine(line.Data());

//   wave->SetFirstWindow(-10,10,"data",kTRUE);
//   wave->SetSecondWindow(-10,10,-10,10,"data",kTRUE);
  wave->InitPedSigmaDB(run);
//   wave->SetChi20(chi20);
//   wave->SetChi21(chi21);
//   wave->SetChi22(chi22);

}
