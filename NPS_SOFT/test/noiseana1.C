#include "TDVCSEventMC.h"
#include "TTree.h"
#include "TFile.h"
#include "TCaloEvent.h"
#include "TObjectTable.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TCaloCluster.h"
#include "TProcessID.h"
#include "TH2.h"
#include "TBranch.h"
#include "TStyle.h"
#include "TPaveText.h"
#include "TF1.h"
#include "TDVCSEvent.h"
void ana()
 {
  TH1F *mm=new TH1F("mm","Missing mass",100,0,2);
  TH1F *nbclusters=new TH1F("nbclusters","Number of clusters",100,0,10);
  TLorentzVector eini(0.,0.,5.75,5.75);
  TLorentzVector pini(0.,0.,0.,0.938271998);
  TH1D *htime=new TH1D("htime","Time of sum",100,-5,5);
  TCanvas *can=new TCanvas();
  TH1F *nbofblocks=new TH1F("nbofblocks","Number of blocks in the good cluster",100,0,50);
  TH1F *nbofblocksb=new TH1F("nbofblocksb","Number of blocks to read",100,0,50);
gStyle->SetOptFit(1010);
 gStyle->SetPalette(1); 
TCaloEvent *caloev;
TDVCSEventMC *mcevent;
TDVCSEvent *dvcsev;
//TFile *f=new TFile("treewall.root");
TFile *f=new TFile("treeonlyinshower.root");
TTree *tree = (TTree*)f->Get("treew");
//TBranch *branchcalo=tree->GetBranch("event_calo2.");
TBranch *branchmc=tree->GetBranch("event_mc2.");
TBranch *branchdvcs=tree->GetBranch("event_dvcs2.");
//branchcalo->SetAddress(&caloev);
branchmc->SetAddress(&mcevent);
branchdvcs->SetAddress(&dvcsev);
 TARSWave *total=new TARSWave(128); 
  total->SetFirstWindow(-100,70,"data");
  total->SetSecondWindow(-2,2,-100,70,"data");
//This is the tree to write
 TH2D *hclusene=new TH2D("hclusene","Energy of highest energy cluster vs Energy of 'second hightest energy' clusters",100,0.5,4,100,0.5,4);
 TH1D *hreso=new TH1D("hreso","Energy with waveforme analysis - genereted energy",100,-2,2);
 TH1D *hresot=new TH1D("hresot","Energy with waveforme total analysis - genereted energy",100,-2,2);
 TH1D *hint=new TH1D("hint","Energy with trigger - genereted energy",100,-2,2);
 TH1D *hchi2mean=new TH1D("chi2mean","Mean chi2 in shower",50,0,30);
 TH1D *hchi2max=new TH1D("chi2max","chi2 of max energy block",50,0,30);
 TH1D *hchi2t=new TH1D("chi2t","chi2 with sum",50,0,3000);
 TH1D *hintp[16];
 TH1D *hresop[16];
 TH1D *hresopt[16];
 TH1D *hchi2meanp[16];
 TH1D *hchi2maxp[16];
 TH1D *hchi2tp[16];

 for(Int_t i=0;i<16;i++){
   TString title1("hreso");title1+=i;
   TString title6("hresot");title6+=i;
   TString title2("int");title2+=i;
   TString title3("chi2mean");title3+=i;
   TString title4("chi2max");title4+=i;
   TString title5("chi2sum");title5+=i;
   hresop[i]=new TH1D(title1.Data(),"Energy with waveforme analysis - genereted energy",100,-2,2);
   hresopt[i]=new TH1D(title6.Data(),"Energy with waveforme total analysis - genereted energy",100,-2,2);
   hintp[i]=new TH1D(title2.Data(),"Energy with trigger - genereted energy",100,-2,2);
   hchi2meanp[i]=new TH1D(title3.Data(),"Mean chi2 in shower",50,0,30);
   hchi2maxp[i]=new TH1D(title4.Data(),"chi2 of max energy block",50,0,30);
   hchi2tp[i]=new TH1D(title5.Data(),"chi2 of sum",50,0,3000);
 }

 Double_t mmsq,mmsqtmp;
TFile tf("treewallanalyzedwave.root","RECREATE");
TTree tree2("treew","My tree");
tree2.Branch("event_calo2.","TCaloEvent",&caloev,16000,2); //We write
tree2.Branch("event_mc2.","TDVCSEventMC",&mcevent,16000,2); //We write
Int_t nevent=tree->GetEntries();
// nevent=20;
 Double_t energy1,energy2,energyint,energywave,amptmp,chi2mean,chi2max,energytotal;
 Double_t x1=-1000.,y1=-10000.;
 Int_t yes=0,no=0;
for(Int_t i=0;i<nevent;i++) {
  Int_t goodclus=-1;
  Int_t ObjectNumber=TProcessID::GetObjectCount();
  tree->GetEntry(i);
  caloev=dvcsev->GetCaloEvent();
  energy1=0.;energy2=0.;
  if(i%100==0) cout<<i<<"/"<<nevent<<endl;

  y1=-1000.;x1=-1000.;
  Bool_t good=kTRUE;

//   cout<<"BEFORE------------------------------"<<endl;
//   caloev->Print();

  for(Int_t nb=0;nb<caloev->GetNbBlocks();nb++){
    TCaloBlock* block=(TCaloBlock*)(caloev->GetBlocks()->UncheckedAt(nb));
    TARSWave *wave=caloev->GetWave(nb);
    block->Clear("");
    if(wave->GetNbPulses()>0){
      if(wave->GetArrivalTime1()<3 && wave->GetArrivalTime1()>-3){
	block->SetBlockEnergy(-(wave->GetAmplitude1()));
      }else{
	block->SetBlockEnergy(0.);
      }
    }else{
      	block->SetBlockEnergy(0.);
    }
  }
  //  caloev->TriggerSimulation();
  caloev->DoClustering();
  nbclusters->Fill(caloev->GetNbClusters());
//   cout<<"AFTER------------------------------"<<endl;
//   caloev->Print();

      nbofblocksb->Fill(caloev->GetNbBlocks());

  mmsqtmp=10000;goodclus=-1.;
  for(Int_t j=0;j<caloev->GetNbClusters();j++){
    TCaloCluster* clus=caloev->GetCluster(j);
    clus->Analyze();
    clus->SetEnergy(1.058*clus->GetEnergy());
    
    TLorentzVector ph=dvcsev->GetPhoton(j);
    TLorentzVector efin=dvcsev->GetElectron();
    mmsq=(eini+pini-efin-ph).Mag2();
    Double_t ecart=TMath::Abs(mmsq-8.80354342230912135e-01);
    if(ecart<mmsqtmp && ecart<0.2) {
      mmsqtmp=ecart;
      goodclus=j;
      x1=clus->GetX();
      y1=clus->GetY();
    }
  }

  /////////////////////////////////////////////

//   if(caloev->GetNbClusters()>0){
//     TCaloCluster* clus=caloev->GetCluster(clusmax);
//     for(Int_t k=0;k<clus->GetClusSize();k++){
//       amptmp=0.;
//       TRef* ref=(TRef*)(clus->GetClusBlock())->UncheckedAt(k);
//       TCaloBlock* block=(TCaloBlock*)ref->GetObject();
//       Int_t pos=caloev->GetBlockPosition(block->GetBlockNumber());
//       TARSWave *wave=caloev->GetWave(pos);
//       block->Clear("");
//       block->SetBlockEnergy(0.);
//       if(wave->GetNbPulses()>0){
// 	if(wave->GetArrivalTime1()<3 && wave->GetArrivalTime1()>-3){
// 	  if((-(wave->GetAmplitude1()))>amptmp) {
// 	    chi2max=wave->GetChi2();
// 	    amptmp=wave->GetAmplitude1();
// 	  }
// 	  block->Clear("");
// 	  block->SetBlockEnergy(-(wave->GetAmplitude1()));
// 	}
//       }
//     }
  

//     clus->Analyze(kTRUE);
//     clus->SetEnergy(1.058*clus->GetEnergy());
    
//     TLorentzVector ph=dvcsev->GetPhoton(clusmax);
//     TLorentzVector efin=dvcsev->GetElectron();
//     mm->Fill((eini+pini-efin-ph).Mag2());
//   }
  /////////////////////////////////////////////



  //  if(energy1>(2.7/1.058)){
  if(goodclus>-1){
  if(caloev->GetNbClusters()>0){
    if(x1<13.5 && x1>-13.5 && y1<15 && y1>-15){
    if(goodclus==0) {
      yes+=1;
    }else{
      no+=1;
    }
    }
  }
    energyint=0.;
    //if(clusmax>-1){
    energytotal=0.;energywave=0.;
      chi2mean=0.;chi2max=0.;
      TCaloCluster* clus=caloev->GetCluster(goodclus);
//       if(goodclus>-1&& x1>-13.5 && x1<13.5 && y1<15 && y1>-15 && good==kTRUE) nbofblocks->Fill(clus->GetClusSize());
//       nbofblocksb->Fill(caloev->GetNbBlocks());

      for(Int_t kk=0;kk<128;kk++) total->SetValue(kk,0.);
      for(Int_t k=0;k<clus->GetClusSize();k++){
	amptmp=0.;
	TRef* ref=(TRef*)(clus->GetClusBlock())->UncheckedAt(k);
	TCaloBlock* block=(TCaloBlock*)ref->GetObject();
	Int_t pos=caloev->GetBlockPosition(block->GetBlockNumber());
	TARSWave *wave=caloev->GetWave(pos);
	for(Int_t jj=0;jj<128;jj++) total->SetValue(jj,total->GetArray()->GetValue(jj)+wave->GetArray()->GetValue(jj));
	energyint+=(wave->GetArray()->GetIntegral(25,85))/(-12836.3);
	chi2mean+=wave->GetChi2();
	if(wave->GetNbPulses()>0){
	  if(wave->GetArrivalTime1()<3 && wave->GetArrivalTime1()>-3){
	    if((-(wave->GetAmplitude1()))>amptmp) {
	      chi2max=wave->GetChi2();
	      amptmp=wave->GetAmplitude1();
	    }
	    energywave+=-(wave->GetAmplitude1());
	  }
	  if(wave->GetNbPulses()>1 && wave->GetArrivalTime2()<3 && wave->GetArrivalTime2()>-3){
	    good=kFALSE;
	  }
	}
      }

      if(goodclus>-1&& x1>-13.5 && x1<13.5 && y1<15 && y1>-15 && good==kTRUE) nbofblocks->Fill(clus->GetClusSize());


      total->Analyze("datawave");
      if(total->GetNbPulses()>0){
	if(total->GetArrivalTime1()<3 && total->GetArrivalTime1()>-3){
	  energytotal=-(total->GetAmplitude1());
	}
// 	    cout<<energytotal<<endl;
// 	    total->DrawRaw(can);
//   total->GetFit("data")->Draw(can);
//   total->DrawRaw(can,"same");
//   total->GetFit("data")->GetHisto()->SetLineColor(kRed);
//   total->GetFit("data")->GetHisto()->SetDrawOption("same");
      }
      
      if(clus->GetClusSize()>0) chi2mean=chi2mean/(clus->GetClusSize());
      //}
    if(x1>-13.5 && x1<13.5 && y1<15 && y1>-15 && good==kTRUE){
      hreso->Fill(1.058*energywave-mcevent->GetPhoton()->E());
      hresot->Fill(1.058*energytotal-mcevent->GetPhoton()->E());
      //      cout<<1.058*energywave-mcevent->GetPhoton()->E()<<endl;
      hclusene->Fill(1.058*energy1,1.058*energy2);
      hint->Fill(1.058*energyint-mcevent->GetPhoton()->E());
      hchi2mean->Fill(chi2mean);
      hchi2max->Fill(chi2max);
      if(energytotal>0.) hchi2t->Fill(total->GetChi2());

      if(x1>-13.5 && x1<-6.75 && y1<15 && y1>7.5 && good==1){
	hresop[0]->Fill(1.058*energywave-mcevent->GetPhoton()->E());
	hresopt[0]->Fill(1.058*energytotal-mcevent->GetPhoton()->E());
	hintp[0]->Fill(1.058*energyint-mcevent->GetPhoton()->E());
	hchi2meanp[0]->Fill(chi2mean);
	hchi2maxp[0]->Fill(chi2max);
	if(energytotal>0.) hchi2tp[0]->Fill(total->GetChi2());
      }
      if(x1>-6.75 && x1<0 && y1<15 && y1>7.5 && good==1){
	hresop[1]->Fill(1.058*energywave-mcevent->GetPhoton()->E());
	hresopt[1]->Fill(1.058*energytotal-mcevent->GetPhoton()->E());
	hintp[1]->Fill(1.058*energyint-mcevent->GetPhoton()->E());
	hchi2meanp[1]->Fill(chi2mean);
	hchi2maxp[1]->Fill(chi2max);
 	if(energytotal>0.) hchi2tp[1]->Fill(total->GetChi2());
     }
      if(x1>0 && x1<6.75 && y1<15 && y1>7.5 && good==1){
	hresop[2]->Fill(1.058*energywave-mcevent->GetPhoton()->E());
	hresopt[2]->Fill(1.058*energytotal-mcevent->GetPhoton()->E());
	hintp[2]->Fill(1.058*energyint-mcevent->GetPhoton()->E());
	hchi2meanp[2]->Fill(chi2mean);
	hchi2maxp[2]->Fill(chi2max);
	if(energytotal>0.) hchi2tp[2]->Fill(total->GetChi2());
      }
      if(x1>6.75 && x1<13.5 && y1<15 && y1>7.5 && good==1){
	hresop[3]->Fill(1.058*energywave-mcevent->GetPhoton()->E());
	hresopt[3]->Fill(1.058*energytotal-mcevent->GetPhoton()->E());
	hintp[3]->Fill(1.058*energyint-mcevent->GetPhoton()->E());
	hchi2meanp[3]->Fill(chi2mean);
	hchi2maxp[3]->Fill(chi2max);
 	if(energytotal>0.) hchi2tp[3]->Fill(total->GetChi2());
     }
      if(x1>-13.5 && x1<-6.75 && y1<7.5 && y1>0 && good==1){
	hresop[4]->Fill(1.058*energywave-mcevent->GetPhoton()->E());
	hresopt[4]->Fill(1.058*energytotal-mcevent->GetPhoton()->E());
	hintp[4]->Fill(1.058*energyint-mcevent->GetPhoton()->E());
	hchi2meanp[4]->Fill(chi2mean);
	hchi2maxp[4]->Fill(chi2max);
	if(energytotal>0.) hchi2tp[4]->Fill(total->GetChi2());
      }
      if(x1>-6.75 && x1<0 && y1<7.5 && y1>0 && good==1){
	hresop[5]->Fill(1.058*energywave-mcevent->GetPhoton()->E());
	hresopt[5]->Fill(1.058*energytotal-mcevent->GetPhoton()->E());
	hintp[5]->Fill(1.058*energyint-mcevent->GetPhoton()->E());
	hchi2meanp[5]->Fill(chi2mean);
	hchi2maxp[5]->Fill(chi2max);
	if(energytotal>0.) hchi2tp[5]->Fill(total->GetChi2());
      }
      if(x1>0 && x1<6.75 && y1<7.5 && y1>0 && good==1){
	hresop[6]->Fill(1.058*energywave-mcevent->GetPhoton()->E());
	hresopt[6]->Fill(1.058*energytotal-mcevent->GetPhoton()->E());
	hintp[6]->Fill(1.058*energyint-mcevent->GetPhoton()->E());
	hchi2meanp[6]->Fill(chi2mean);
	hchi2maxp[6]->Fill(chi2max);
	if(energytotal>0.) hchi2tp[6]->Fill(total->GetChi2());
      }
      if(x1>6.75 && x1<13.5 && y1<7.5 && y1>0 && good==1){
	hresop[7]->Fill(1.058*energywave-mcevent->GetPhoton()->E());
	hresopt[7]->Fill(1.058*energytotal-mcevent->GetPhoton()->E());
	hintp[7]->Fill(1.058*energyint-mcevent->GetPhoton()->E());
	hchi2meanp[7]->Fill(chi2mean);
	hchi2maxp[7]->Fill(chi2max);
	if(energytotal>0.) hchi2tp[7]->Fill(total->GetChi2());
      }
      if(x1>-13.5 && x1<-6.75 && y1<0 && y1>-7.5 && good==1){
	hresop[8]->Fill(1.058*energywave-mcevent->GetPhoton()->E());
	hresopt[8]->Fill(1.058*energytotal-mcevent->GetPhoton()->E());
	hintp[8]->Fill(1.058*energyint-mcevent->GetPhoton()->E());
	hchi2meanp[8]->Fill(chi2mean);
	hchi2maxp[8]->Fill(chi2max);
	if(energytotal>0.) hchi2tp[8]->Fill(total->GetChi2());
      }
      if(x1>-6.75 && x1<0 && y1<0 && y1>-7.5 && good==1){
	hresop[9]->Fill(1.058*energywave-mcevent->GetPhoton()->E());
	hresopt[9]->Fill(1.058*energytotal-mcevent->GetPhoton()->E());
	hintp[9]->Fill(1.058*energyint-mcevent->GetPhoton()->E());
	hchi2meanp[9]->Fill(chi2mean);
	hchi2maxp[9]->Fill(chi2max);
	if(energytotal>0.) hchi2tp[9]->Fill(total->GetChi2());
      }
      if(x1>0 && x1<6.75 && y1<0 && y1>-7.5 && good==1){
	hresop[10]->Fill(1.058*energywave-mcevent->GetPhoton()->E());
	hresopt[10]->Fill(1.058*energytotal-mcevent->GetPhoton()->E());
	hintp[10]->Fill(1.058*energyint-mcevent->GetPhoton()->E());
	hchi2meanp[10]->Fill(chi2mean);
	hchi2maxp[10]->Fill(chi2max);
	if(energytotal>0.) hchi2tp[10]->Fill(total->GetChi2());
      }
      if(x1>6.75 && x1<13.5 && y1<0 && y1>-7.5 && good==1){
	hresop[11]->Fill(1.058*energywave-mcevent->GetPhoton()->E());
	hresopt[11]->Fill(1.058*energytotal-mcevent->GetPhoton()->E());
	hintp[11]->Fill(1.058*energyint-mcevent->GetPhoton()->E());
	hchi2meanp[11]->Fill(chi2mean);
	hchi2maxp[11]->Fill(chi2max);
	if(energytotal>0.) hchi2tp[11]->Fill(total->GetChi2());
      }
      if(x1>-13.5 && x1<-6.75 && y1<-7.5 && y1>-15 && good==1){
	hresop[12]->Fill(1.058*energywave-mcevent->GetPhoton()->E());
	hresopt[12]->Fill(1.058*energytotal-mcevent->GetPhoton()->E());
	hintp[12]->Fill(1.058*energyint-mcevent->GetPhoton()->E());
	hchi2meanp[12]->Fill(chi2mean);
	hchi2maxp[12]->Fill(chi2max);
	if(energytotal>0.) hchi2tp[12]->Fill(total->GetChi2());
      }
      if(x1>-6.75 && x1<0 && y1<-7.5 && y1>-15 && good==1){
	hresop[13]->Fill(1.058*energywave-mcevent->GetPhoton()->E());
	hresopt[13]->Fill(1.058*energytotal-mcevent->GetPhoton()->E());
	hintp[13]->Fill(1.058*energyint-mcevent->GetPhoton()->E());
	hchi2meanp[13]->Fill(chi2mean);
	hchi2maxp[13]->Fill(chi2max);
	if(energytotal>0.) hchi2tp[13]->Fill(total->GetChi2());
      }
      if(x1>0 && x1<6.75 && y1<-7.5 && y1>-15 && good==1){
	hresop[14]->Fill(1.058*energywave-mcevent->GetPhoton()->E());
	hresopt[14]->Fill(1.058*energytotal-mcevent->GetPhoton()->E());
	hintp[14]->Fill(1.058*energyint-mcevent->GetPhoton()->E());
	hchi2meanp[14]->Fill(chi2mean);
	hchi2maxp[14]->Fill(chi2max);
	if(energytotal>0.) hchi2tp[14]->Fill(total->GetChi2());
      }
      if(x1>6.75 && x1<13.5 && y1<-7.5 && y1>-15 && good==1){
	hresop[15]->Fill(1.058*energywave-mcevent->GetPhoton()->E());
	hresopt[15]->Fill(1.058*energytotal-mcevent->GetPhoton()->E());
	hintp[15]->Fill(1.058*energyint-mcevent->GetPhoton()->E());
	hchi2meanp[15]->Fill(chi2mean);
	hchi2maxp[15]->Fill(chi2max);
	if(energytotal>0.) hchi2tp[15]->Fill(total->GetChi2());
      }

    }
    tree2.Fill();
  }
  //    caloev->Reset();//We do reset here and not clear !!
    dvcsev->Reset();//We do reset here and not clear !!
    mcevent->Clear();
    TProcessID::SetObjectCount(ObjectNumber);
}
 TCanvas *c=new TCanvas(); 
 hclusene->Draw("colz");
 TCanvas *c2=new TCanvas();
 c2->Divide(3,2);
 c2->cd(1);
 hint->SetMaximum(700);
 hint->Draw();
 c2->cd(2);
 hreso->SetMaximum(700);
 hreso->Draw();
 c2->cd(3);
 hresot->SetMaximum(700);
 hresot->Draw();
 c2->cd(4);
 hchi2mean->SetMaximum(900);
 hchi2mean->Draw();
 c2->cd(5);
 hchi2max->SetMaximum(900);
 hchi2max->Draw();
 c2->cd(6);
 hchi2t->SetMaximum(900);
 hchi2t->Draw();

TCanvas *c3=new TCanvas();
TCanvas *c4=new TCanvas();
TCanvas *c5=new TCanvas();
TCanvas *c6=new TCanvas();
TCanvas *c7=new TCanvas();
TCanvas *c8=new TCanvas();
c3->Divide(4,4,0,0);
c4->Divide(4,4,0,0);
c5->Divide(4,4,0,0);
c6->Divide(4,4,0,0);
c7->Divide(4,4,0,0);
c8->Divide(4,4,0,0);
c3->SetBorderMode(0);
c4->SetBorderMode(0);
c5->SetBorderMode(0);
c6->SetBorderMode(0);
c7->SetBorderMode(0);
c8->SetBorderMode(0);
gStyle->SetCanvasBorderMode(0);
Int_t n=16,col=4,row=4;

for(Int_t i=0;i<16;i++){
  c3->cd(i+1);
  if(i/col<row-1) gPad->SetBottomMargin(0);
  if(i/col>0) gPad->SetTopMargin(0);
  if((i+1)%col>0) gPad->SetRightMargin(0);
  if(i%col>0)gPad->SetLeftMargin(0);
  gPad->SetTickx(2);
  gPad->SetTicky(2);
  hintp[i]->SetMaximum(30);
  hintp[i]->Fit("gaus");
  hintp[i]->Draw();  
  c4->cd(i+1);
  if(i/col<row-1) gPad->SetBottomMargin(0);
  if(i/col>0) gPad->SetTopMargin(0);
  if((i+1)%col>0) gPad->SetRightMargin(0);
  if(i%col>0)gPad->SetLeftMargin(0);
  gPad->SetTickx(2);
  gPad->SetTicky(2);
  hresop[i]->SetMaximum(70);
  hresop[i]->Fit("gaus");
  hresop[i]->Draw();
  c5->cd(i+1);
  if(i/col<row-1) gPad->SetBottomMargin(0);
  if(i/col>0) gPad->SetTopMargin(0);
  if((i+1)%col>0) gPad->SetRightMargin(0);
  if(i%col>0)gPad->SetLeftMargin(0);
  gPad->SetTickx(2);
  gPad->SetTicky(2);
  hchi2meanp[i]->SetMaximum(70);
  hchi2meanp[i]->Draw();
  c6->cd(i+1);
  if(i/col<row-1) gPad->SetBottomMargin(0);
  if(i/col>0) gPad->SetTopMargin(0);
  if((i+1)%col>0) gPad->SetRightMargin(0);
  if(i%col>0)gPad->SetLeftMargin(0);
  gPad->SetTickx(2);
  gPad->SetTicky(2);
  hchi2maxp[i]->SetMaximum(185);
  hchi2maxp[i]->Draw();
  c7->cd(i+1);
  if(i/col<row-1) gPad->SetBottomMargin(0);
  if(i/col>0) gPad->SetTopMargin(0);
  if((i+1)%col>0) gPad->SetRightMargin(0);
  if(i%col>0)gPad->SetLeftMargin(0);
  gPad->SetTickx(2);
  gPad->SetTicky(2);
  hresopt[i]->SetMaximum(45);
  hresopt[i]->Fit("gaus");
  hresopt[i]->Draw();
  c8->cd(i+1);
  if(i/col<row-1) gPad->SetBottomMargin(0);
  if(i/col>0) gPad->SetTopMargin(0);
  if((i+1)%col>0) gPad->SetRightMargin(0);
  if(i%col>0)gPad->SetLeftMargin(0);
  gPad->SetTickx(2);
  gPad->SetTicky(2);
  hchi2tp[i]->SetMaximum(60);
  hchi2tp[i]->Draw();
}


 cout<<"YES : "<<yes<<"  "<<" NO : "<<no<<endl;


TF1 *ff[16];
TPaveText *p[16];
 for (Int_t i=0;i<16;i++){
  ff[i]= (TF1*)hresop[i]->GetFunction("gaus");
  ff[i]->SetLineWidth(1.5);
  ff[i]->SetLineColor(kRed);
  p[i]=new TPaveText();
p[i]->SetX1NDC(0);
p[i]->SetY1NDC(0.8);
p[i]->SetX2NDC(0.3);
p[i]->SetY2NDC(1);
char *pp; pp=new char[10];sprintf(pp,"%1.3f",ff[i]->GetParameter(2));
TString a=pp;
p[i]->AddText(a.Data());
p[i]->SetTextAlign(22);
p[i]->SetTextFont(63);
p[i]->SetTextSize(12);
 c4->cd(i+1);
p[i]->Draw();
}
TF1 *ff2[16];
TPaveText *p2[16];
for (Int_t i=0;i<16;i++){
  ff2[i]= (TF1*)hintp[i]->GetFunction("gaus");
  ff2[i]->SetLineWidth(1.5);
  ff2[i]->SetLineColor(kRed);
  p2[i]=new TPaveText();
p2[i]->SetX1NDC(0);
p2[i]->SetY1NDC(0.8);
p2[i]->SetX2NDC(0.3);
p2[i]->SetY2NDC(1);
char *pp2; pp2=new char[10];sprintf(pp2,"%1.3f",ff2[i]->GetParameter(2));
TString a2=pp2;
p2[i]->AddText(a2.Data());
p2[i]->SetTextAlign(22);
p2[i]->SetTextFont(63);
p2[i]->SetTextSize(12);
 c3->cd(i+1);
p2[i]->Draw();
}
TF1 *ff3[16];
TPaveText *p3[16];
for (Int_t i=0;i<16;i++){
  ff3[i]= (TF1*)hresopt[i]->GetFunction("gaus");
  ff3[i]->SetLineWidth(1.5);
  ff3[i]->SetLineColor(kRed);
  p3[i]=new TPaveText();
p3[i]->SetX1NDC(0);
p3[i]->SetY1NDC(0.8);
p3[i]->SetX2NDC(0.3);
p3[i]->SetY2NDC(1);
char *pp3; pp3=new char[10];sprintf(pp3,"%1.3f",ff3[i]->GetParameter(2));
TString a3=pp3;
p3[i]->AddText(a3.Data());
p3[i]->SetTextAlign(22);
p3[i]->SetTextFont(63);
p3[i]->SetTextSize(12);
 c7->cd(i+1);
p3[i]->Draw();
}
 TCanvas *ee=new TCanvas();
 ee->Divide(2,2);
 ee->cd(1);
 nbofblocksb->Draw();
 ee->cd(2);
 nbofblocks->Draw();
 ee->cd(3);
 nbclusters->Draw();

 c2->Print("allnoisewave.ps(");
 c3->Print("allnoisewave.ps");
 c4->Print("allnoisewave.ps");
 c5->Print("allnoisewave.ps");
 c6->Print("allnoisewave.ps");
 c7->Print("allnoisewave.ps");
 c8->Print("allnoisewave.ps");
//  TCanvas *ee=new TCanvas();
//  ee->Divide(1,2);
//  ee->cd(1);
//  nbofblocksb->Draw();
//  ee->cd(2);
//  nbofblocks->Draw();
 
 ee->Print("allnoisewave.ps)");

 }
