//
// TGCalo.cxx, v1.0, Sun May 25 14:42:50
// Author: C. Munoz Camacho
//

#include <iostream>

#ifndef __TGCalo__
#include "TGCalo.h"
#endif

#ifndef ROOT_TTree
#include "TTree.h"
#endif

#ifndef ROOT_TPaveText
#include "TPaveText.h"
#endif

using namespace std;

ClassImp(TGCalo)

////////////////////////////////////////////////////////////////////////////////
//
// GUI DVCS Class
// 
////////////////////////////////////////////////////////////////////////////////

//_____________________________________________________________________________
TGCalo::TGCalo(TFile *file)
{
  //Default constructor

  cout<<"GUI constructor"<<endl;
  
  fCaloEvent = new TCaloEvent();
  //  fTrigger=new TCaloTrigger();
  //  fPAEvent = new TPAEvent();
  TARSWave *wt=new TARSWave();
  wt->SetPedestalProfileFile("initdata/pro-run169-0.root");
  cout<<"begin init"<<endl;
  Init(file);
  //ut<<"end constructor"<<endl;
  ftcalo=0;
}

//_____________________________________________________________________________
 TGCalo::~TGCalo()
{
  // Default destructor

  cout<<"GUI destructor"<<endl;
  
  delete fCaloEvent;
  //  delete fPAEvent;

}

//_____________________________________________________________________________
void TGCalo::Init(TFile *file)
{
  //Initializes
  fNevent=100;
  fFile=file;
  fTree=(TTree*)fFile->Get("tree");
  //  fBranchPA=fTree->GetBranch("event_pa");
  fBranchCalo=fTree->GetBranch("event_calo.");
  cout<<"test1"<<endl;
  // fBranchPA->SetAddress(&fPAEvent);
  fBranchCalo->SetAddress(&fCaloEvent);
  cout<<"test2"<<endl;
  //fBranchPA->GetEntry(fNevent);
  

}

//_____________________________________________________________________________
void TGCalo::ExecuteEvent(Int_t event, Int_t px, Int_t py, TObject *sel)
{
  //
  
  TCanvas *c = (TCanvas *) gTQSender;
  TPad *pad = (TPad *) c->GetSelectedPad();
  if (!pad) return;
  if (fNevent==-1) return;
    
  if(pad==fPAPad){
    pad->SetEditable(kFALSE);
    //HandlePA(pad,event,px,py,sel);
  }
  if(pad==fCaloPad){
    //cout<<"You're over the Calorimeter Pad"<<endl;
    HandleCalo(pad,event,px,py,sel);
  }
  if(pad==fPAPadInfo){
    //cout<<"You're over the PA Info Pad"<<endl;
  }
  if(pad==fCaloPadInfo){
    //cout<<"You're over the Calorimeter Info Pad"<<endl;
  }
  if(pad==fPAARSPad){
    //cout<<"You're over the PA ARS Pad"<<endl;
  }
  if(pad==fCaloARSPad){
    //cout<<"You're over the Calorimeter ARS Pad"<<endl;
  }

}

//_____________________________________________________________________________
void TGCalo::ShowNext(void)
{
  //

  fNevent++;
 
  //  fBranchPA->GetEntry(fNevent);
  //  fBranchCalo->GetEntry(fNevent);
  if(ftcalo){
      ftcalo->Clear();
      ftcalo=0;
      fCaloARSPadInfo->Update();
      fCaloARSPadInfo->Modified();
  }
 
  // if(fPAEvent->GetHPA()) fPAEvent->GetHPA()->Clear();
  // if(fCaloEvent->GetHCalo()) fCaloEvent->GetHCalo()->Clear();
  //if(fTrigger->GetHCalo()) fTrigger->GetHCalo()->Clear();
  //  cout<<"avant clear"<<endl;
  //  if(fCaloEvent->GetCaloTrigger()->GetHCalo()) fCaloEvent->GetCaloTrigger()->GetHCalo()->Clear();
  //  cout<<"avant fill"<<endl;
  FillEvent(fNevent);

  //  cout<<"Event filled"<<endl;
  //  fCaloEvent->Print();
  //fPAPad->SetEditable(kTRUE);
  //fPAEvent->Display(fPAPad,0.2,0.);
  //fPAPad->SetEditable(kFALSE);
  fCaloPad->SetEditable(kTRUE);
  fCaloEvent->Print();
  cout<<"TCaloEvent original : "<<endl;
  cout<<fCaloEvent->GetCaloTrigger()<<endl;
  fCaloEvent->GetCaloTrigger()->Print();
    for(Int_t i=0;i<fCaloEvent->GetGeometry()->GetNBlocks();i++){
      //         fCaloEvent->GetCaloTrigger()->SetADCValue(i,0.);
      TCaloBlock* b=fCaloEvent->AddBlock(i);
      b->SetBlockEnergy((fCaloEvent->GetCaloTrigger()->GetADCValue(i))/1000.);
      //    fTrigger->SetADCValue(i,fCaloEvent->GetCaloTrigger()->GetADCValue(i));;
    }
    //  fTrigger=fCaloEvent->GetCaloTrigger();
  cout<<"CaloTrigger :"<<endl;
  fCaloEvent->GetCaloTrigger()->Print();
  for(Int_t n=0;n<fCaloEvent->GetNbBlocks();n++){
    TClonesArray *array=fCaloEvent->GetBlocks();
    TCaloBlock* block=(TCaloBlock*)array->UncheckedAt(n);
    // fTrigger->SetADCValue(block->GetBlockNumber(),fCaloEvent->GetCaloTrigger()->GetADCValue((block->GetBlockNumber())));
    //  fCaloEvent->GetCaloTrigger()->SetADCValue(block->GetBlockNumber(),fCaloEvent->GetCaloTrigger()->GetADCValue((block->GetBlockNumber())));
   //      fTrigger->SetADCValue(block->GetBlockNumber(),fCaloEvent->GetWave(n)->GetArray()->GetIntegral());
    //cout<<n<<"===="<<fCaloEvent->GetWave(n)->GetArray()->GetIntegral()<<endl;
    //TCanvas *c=new TCanvas();
    //fCaloEvent->GetWave(n)->GetArray()->Draw(c);
    //cout<<"->"<<fCaloEvent->GetWave(n)->GetArray()->GetMaximumBin()<<endl;
  }
  // fTrigger->Display(fCaloPad,0.128);
  //fCaloEvent->GetCaloTrigger()->Display(fCaloPad,0.128);
  fCaloEvent->Display(fCaloPad,0.128,0.);
  //    cout<<"CaloEvent :"<<endl;
  //    fCaloEvent->Print();
  //fTrigger->Print();
    //fCaloEvent->Clear(); //To be checked======================>
    //    cout<<"apres clear caloevent"<<endl;
  fCaloPad->SetEditable(kFALSE);
  fTest=kTRUE;  
  //  delete fhCalo;
  //delete fhPA;
  //fhCalo=0; 
  //fhPA=0;
  fCaloARSPad->Clear();
  //fPAARSPad->Clear();
  fCaloARSPad->Update();
  fCaloARSPad->Modified();
  //fPAARSPad->Update();
  //fPAARSPad->Modified();


}


//_____________________________________________________________________________
void TGCalo::FillEvent(Int_t nevent)
{
  //fBranchPA->GetEntry(nevent);
    fBranchCalo->GetEntry(nevent);
}


//_____________________________________________________________________________
void TGCalo::HandlePA(TPad* pad, Int_t event, Int_t px, Int_t py, TObject* sel)
{
  /*
  Int_t ring,tower;
  Float_t x = pad->AbsPixeltoX(px);
  Float_t y = pad->AbsPixeltoY(py);
  x = pad->PadtoX(x);
  y = pad->PadtoY(y);
  Float_t r=TMath::Sqrt(TMath::Power(x-0.5,2.)+TMath::Power(y-0.5,2.));
  Float_t phi=TMath::ATan2((y-0.5),(x-0.5));

  if(r<=.15+(0.25/5.)*(4.+1) &&
     r>=.15 &&
     phi<=135*TMath::Pi()/180. && phi >=-135*TMath::Pi()/180.){
    
    ring=Int_t(4-((r-0.15)/0.05)+1);
    
    if(phi>0){
      tower=10+Int_t(phi*180./TMath::Pi()/13.5);
    }else{
      tower=9+Int_t(phi*180./TMath::Pi()/13.5);
    }
    
    fPAPadInfo->cd();
    TPaveText* t=new TPaveText(0.,0.,1.,1.);
    t->SetFillColor(kWhite);
    t->SetBorderSize(0);
    char t1[50];
    sprintf(t1,"Block ring %i tower %i",ring,tower);
    t->AddText(t1);
    t->SetTextSize(0.4);
    t->Draw();
    fPAPadInfo->Modified();
    fPAPadInfo->Update();
    if(fTest){
      fBranchPA->GetEntry(fNevent);
      fPAEvent->Display(fPAPad,0.2,0.);
      fTest=kFALSE;
    }
  delete t;
    pad->cd();
  }else{
    fPAPadInfo->cd();
    //TPaveText* t=new TPaveText(x,y,x+0.4,y+0.06);
    TPaveText* t=new TPaveText(1-0.4,1,1,1-0.06);
    t->SetFillColor(kWhite);
    t->SetBorderSize(0);
    char t1[50];
    sprintf(t1," ",ring,tower);
    t->AddText(t1);
    t->SetTextSize(0.04);
    t->Draw();
    fPAPadInfo->Update();
    fPAPadInfo->Modified();
    if(fTest){
      fBranchPA->GetEntry(fNevent);
      fPAEvent->Display(fPAPad,0.2,0.);
      fTest=kFALSE;
    }
    delete t;
  }
  pad->cd();
  
  if ((event == kButton1Down) ||
      (event == kButton1Double) 
      //	||       ((event == kButton1Motion) && (sel == fHist))) {
      ||       ((event == kButton1Motion))) {
    
    //TCanvas *c=new TCanvas("disp",t1,455,380,450,350);
    if(r<=.15+(0.25/5.)*(4.+1) &&
       r>=.15 &&
       phi<=135*TMath::Pi()/180. && phi >=-135*TMath::Pi()/180.){

      ring=Int_t(4-((r-0.15)/0.05)+1);
      if(phi>0){
	tower=10+Int_t(phi*180./TMath::Pi()/13.5);
      }else{
	tower=9+Int_t(phi*180./TMath::Pi()/13.5);
      }	
      char t1[50];
      sprintf(t1,"Block ring %i tower %i",ring,tower);
      if(!fhPA) fhPA=new TH1F("fhPA",t1,128,0,128);
      fhPA->SetTitle(t1);
      fPAARSPad->cd();
      fhPA->Draw();
      fPAARSPad->Update();
      fPAARSPad->Modified();
    }  
    pad->Modified();
    if (event == kButton1Motion) pad->Update(); //force update
  }
  if (event == kButton3Down) {
      pad->Modified();
      pad->Update();
  }
  */
}

//_____________________________________________________________________________
void TGCalo::HandleCalo(TPad* pad, Int_t event, Int_t px, Int_t py, TObject* sel)
{
  
  //
  Int_t xb,yb;
  Float_t x = pad->AbsPixeltoX(px);
  Float_t y = pad->AbsPixeltoY(py);
  x = pad->PadtoX(x);
  y = pad->PadtoY(y);
  if(x>1 || x<0 || y>1 || y<0) return;

  //  cout<<"================>"<<x<<" "<<y<<endl;

  if(x>=0.05 && x<=0.95 && y>=0.05 && y<=0.95){
    
    //    cout<<"YES"<<endl;
    //    cout<<fCaloEvent->GetGeometry()->GetNX()<<endl;
    xb=Int_t((x-0.05)*fCaloEvent->GetGeometry()->GetNX());
    yb=Int_t((y-0.05)*fCaloEvent->GetGeometry()->GetNY());

    //    cout<<"ok2 "<<xb<<" "<<yb<<endl;

    fCaloPadInfo->cd();
    TPaveText* t=new TPaveText(0.,0.,1.,1.);
    t->SetFillColor(kWhite);
    t->SetBorderSize(0);
    char t1[50];
    sprintf(t1,"Block column %i row %i",xb,yb);
    t->AddText(t1);
    t->SetTextSize(0.4);
    t->Draw();
    fCaloPadInfo->Modified();
    fCaloPadInfo->Update();
    if(fTest){
      fBranchCalo->GetEntry(fNevent);
      //fCaloEvent->Display(fCaloPad,0.2,0.);
      fTest=kFALSE;
    }
    //    cout<<"ok3"<<endl;
  delete t;
    pad->cd();
  }else{
    fCaloPadInfo->cd();
    //TPaveText* t=new TPaveText(x,y,x+0.4,y+0.06);
    TPaveText* t=new TPaveText(1-0.4,1,1,1-0.06);
    t->SetFillColor(kWhite);
    t->SetBorderSize(0);
    char t1[50];
    sprintf(t1," ",xb,yb);
    t->AddText(t1);
    t->SetTextSize(0.04);
    t->Draw();
    fCaloPadInfo->Update();
    fCaloPadInfo->Modified();
    //cout<<"NO"<<endl;
   if(fTest){
      fBranchCalo->GetEntry(fNevent);
      //fCaloEvent->Display(fCaloPad,0.2,0.);
      fTest=kFALSE;
    }
   // delete t;
  }
  pad->cd();
  
  if ((event == kButton1Down) ||
      (event == kButton1Double) 
      //	||       ((event == kButton1Motion) && (sel == fHist))) {
      ||       ((event == kButton1Motion))) {

    if(x>=0.05 && x<=0.95 && y>=0.05 && y<=0.95){
      
      xb=Int_t((x-0.05)*fCaloEvent->GetGeometry()->GetNX()/0.9);
      yb=Int_t((y-0.05)*fCaloEvent->GetGeometry()->GetNY()/0.9);
      
      //      Int_t blnb=xb+1+(yb+1)*fCaloEvent->GetGeometry()->GetNX();
      Int_t blnb=xb+(yb)*fCaloEvent->GetGeometry()->GetNX();
      Int_t pos=fCaloEvent->GetBlockPosition(blnb);
      cout<<"POSITION "<<pos<<" blocknb "<<blnb<<endl;
      if(pos!=-1) {
	fCaloARSPad->cd();
//  	TARSArray *ar=fCaloEvent->GetARSArray();
//  	  cout<<"ok jusque ici"<<endl;
//  	  cout<<ar->GetNbWaves()<<endl;
//  	  	  TARSWave *wave=ar->GetWave(pos);
//  	  cout<<"ok jusque la "<<wave<<endl;
//  	  wave->Print();
//  	  wave->DrawRaw("");
//  	  cout<<"et enfin..."<<endl;
	TARSWave *wave=fCaloEvent->GetWave(pos);
	wave->SubstractPedestal((blnb/11)+12*(blnb%11));
	cout<<"Pedestal sustracted : "<<(blnb-5)/11<<endl;
	wave->DrawSignal(fCaloARSPad,"",-1000,100);
	fCaloARSPadInfo->cd();
	ftcalo=new TPaveText(0.,0.,1.,1.);
	ftcalo->SetFillColor(kWhite);
	ftcalo->SetBorderSize(0);
	char t1calo[50];
	//	wave->SubstractPedestal();
	Int_t en=wave->GetSignal()->GetIntegral();
	Int_t ti=wave->GetSignal()->GetMinimumBin();
	sprintf(t1calo,"Energy: %i     Time %i ",en,ti);
	ftcalo->AddText(t1calo);
	ftcalo->SetTextSize(0.3);
	ftcalo->Draw();
	fCaloARSPad->Update();
	fCaloARSPad->Modified();
      }

//        char t1[50];
//        sprintf(t1,"Block column %i row %i",xb,yb);
//        //      TH1F *h=new TH1F("h",t1,128,0,128);
//        if(!fhCalo) fhCalo=new TH1F("fhCalo",t1,128,0,128);
//        fhCalo->SetTitle(t1);
//        fCaloARSPad->cd();
//        fhCalo->Draw();
//        fCaloARSPad->Update();
//        fCaloARSPad->Modified();
    }  
    pad->Modified();
    if (event == kButton1Motion) pad->Update(); //force update
  }
  if (event == kButton3Down) {
      pad->Modified();
      pad->Update();
  }
  
}





