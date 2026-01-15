////////////////////////////////////////////////////////////////////
//
// This is a slightly sophisticated macro (not for beginners...).
// It deals with 3 Monte Carlo files with simulated and analyzed 
// waveforms (noise simulation included), each of which has fitted
// zero, one and two pulses to each ARS wave respectively.
//
// Energy and position resolutions are studied as a function of 
// the calorimeter trigger threshold.
// 
//
// C. Munoz (13 Mar 2004)
//
/////////////////////////////////////////////////////////////////////

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
#include "TPaveStats.h"
#include "TGraph.h"
#include "TF1.h"
#include "TDVCSEvent.h"
#include "TCanvas.h"
#include "TMultiGraph.h"
#include "TLegend.h"
void ana()
{
  TCanvas *can=new TCanvas();
  TH1F *hmm=new TH1F("hmm","Histo",100,-1,6);
  gStyle->SetLabelFont(63);
  gStyle->SetLabelSize(12);
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(111111);
  Int_t lookup[132];
  Bool_t good=kFALSE;
  TCaloEvent *caloev=0;
  TDVCSEventMC *mcevent=0;
  TDVCSEvent *dvcsev=new TDVCSEvent();
  TClonesArray *arswaves;
  TLorentzVector electron;
  TVector3 vertex;
  TFile *f[3]; TTree *tree[3]; TBranch *branchcalo[3];TBranch *branchars[3];
  f[0]=new TFile("pulses0.root");
  f[1]=new TFile("pulses1.root");
  f[2]=new TFile("pulses2.root");
  for(Int_t i=0;i<3;i++){
    tree[i]= (TTree*)f[i]->Get("treew");
    branchcalo[i]=tree[i]->GetBranch("event_calo2.");
    branchcalo[i]->SetAddress(&caloev);
    branchars[i]=tree[i]->GetBranch("event_calo2.fARSWaves");
    branchars[i]->SetAddress(&arswaves);
  }
  TBranch *branchmc=tree[0]->GetBranch("event_mc2.");
  branchmc->SetAddress(&mcevent);
  TBranch *branchele=tree[0]->GetBranch("event_dvcs2.fElectron");
  branchele->SetAddress(&electron);
  TBranch *branchver=tree[0]->GetBranch("event_dvcs2.fVertex");
  branchver->SetAddress(&vertex);

  Int_t nevent=tree[0]->GetEntries();
  //nevent=5;
  /////////Put your code here/////////////////////////
  Int_t ntrig=6, parts=16;
  TH1D **he[parts];
  TH1D **hphi[parts];
  TH1D **htheta[parts];
  TH1D **hmmsq[parts];
  TH1F **hnpulave[parts];
  TH1F **hnpulmax[parts];
  TH1F *hblock[ntrig];
  //  Double_t chi2[9]={1.5,4.1,11.2,30.3,82.4,224.,609.,1656.,4501.};
  Double_t valtrig[6]={.77,1.,1.5,2.,2.5,3.};
  //Double_t valtrig[6]={.77,2.5,3.};
    
  for(Int_t i=0;i<parts;i++){
    he[i]=new TH1D*[ntrig];
    hphi[i]=new TH1D*[ntrig];
    htheta[i]=new TH1D*[ntrig];
    hmmsq[i]=new TH1D*[ntrig];
    hnpulave[i]=new TH1F*[ntrig];
    hnpulmax[i]=new TH1F*[ntrig];
   for(Int_t j=0;j<ntrig;j++){
      TString titlee("he_");;titlee+=i;titlee+="_";titlee+=j;
      TString titlephi("hphi_");titlephi+=i;titlephi+="_";titlephi+=j;
      TString titletheta("htheta_");titletheta+=i;
      titletheta+="_";titletheta+=j;
      TString titlemm("mmsq_");titlemm+=i;titlemm+="_";titlemm+=j;
      TString titlenp("mpulave_");titlenp+=i;titlenp+="_";titlenp+=j;
      TString titlenpm("mpulmax_");titlenpm+=i;titlenpm+="_";titlenpm+=j;
      if(i==0){
      TString titleb("hblock_");titleb+=j;
      hblock[j]=new TH1F(titleb.Data(),"Number of blocks in cluster",20,0,20);
      }
      he[i][j]=new TH1D(titlee.Data(),"Reso Energy",100,-2,2);
      hphi[i][j]=new TH1D(titlephi.Data(),"Reso Phi",100,-0.03,0.03);
      htheta[i][j]=new TH1D(titletheta.Data(),"Reso Theta",100,-0.03,0.03);
      hmmsq[i][j]=new TH1D(titlemm.Data(),"Missing mass squared",100,0,3);
      hnpulave[i][j]=new TH1F(titlenp.Data(),"Average number of pulses in shower",50,-1,5);
      hnpulmax[i][j]=new TH1F(titlenpm.Data(),"Number of pulses in max block",15,-1,5);
    }
  }
  TLorentzVector eini(0.,0.,5.75,5.75);
  TLorentzVector pini(0.,0.,0.,0.938271998);
  Double_t mmsq,mmsqtmp,energywave,energytmp,energy,npulseave,npulsemax;
  Double_t x1=-1000.,y1=-10000.,x1t=-1000.,y1t=-10000.,cpgood=0.,cpbords=0.,cpmm=0.,cpene=0.,cpclus=0.;
  Double_t eff[ntrig],effbords[ntrig],effmm[ntrig],effene[ntrig],effclus[ntrig];
  Int_t goodclus;
  
  /////////Put your code here/////////////////////////

  for(Int_t trig=0;trig<ntrig;trig++){  
    cout<<trig<<"/"<<ntrig<<endl;
    cout<<"===================================="<<endl;
    cout<<"===================================="<<endl;
    cpgood=0.,cpbords=0.,cpmm=0.,cpene=0.,cpclus=0.;
    Double_t chi2thres=1.5;
    Double_t trigger=valtrig[trig];
    for(Int_t i=0;i<nevent;i++) {
      if(i%100==0) cout<<i<<"/"<<nevent<<endl;
      if(i%1000==0) gObjectTable->Print();
      // cout<<"-------------------------"<<endl;
      Int_t ObjectNumber=TProcessID::GetObjectCount();
      branchmc->GetEntry(i);
      branchele->GetEntry(i);
      branchver->GetEntry(i);
      branchcalo[0]->GetEntry(i);
      for(Int_t ii=0;ii<caloev->GetNbBlocks();ii++) lookup[ii]=-1;
      for(Int_t ii=0;ii<caloev->GetNbBlocks();ii++){
	TCaloBlock *btmp=(TCaloBlock*)caloev->GetBlocks()->UncheckedAt(ii);
	lookup[btmp->GetBlockNumber()]=ii;
      }
      branchars[0]->GetEntry(i);
      caloev->SetWaves(arswaves);
      //  if(trig==1 ) caloev->Print();
      //     caloev->FillTestWaves();//We must call this method before RE-simulating the trigger when the event is read from a file.
      caloev->TriggerSimulation(trigger);
      caloev->DoClustering();
      //cout<<"Event number "<<i<<endl;
      //caloev->Print();
      //Build up DVCS event
      dvcsev->SetCaloEvent(caloev);
      dvcsev->SetVertex(vertex);
      dvcsev->SetElectron(electron);
       
      //Look for best cluster
      mmsqtmp=10000;goodclus=-1.;energytmp=0.;
      Bool_t ktest=kFALSE;
      Bool_t ktest2=kFALSE;
      good=kFALSE;
      Int_t cp=0;
      for(Int_t j=0;j<caloev->GetNbClusters();j++){
	TCaloCluster* clus=caloev->GetCluster(j);
	clus->Analyze();
	clus->SetEnergy(1.058*clus->GetEnergy());
 	TLorentzVector ph=dvcsev->GetPhoton(j);
 	mmsq=(eini+pini-electron-ph).Mag2();
	Double_t ecart=TMath::Abs(mmsq-8.80354342230912135e-01);
	x1t=clus->GetX();
	y1t=clus->GetY();

	if(x1t<13.5 && x1t>-13.5 && y1t<15 && y1t>-15 && ktest==kFALSE) {
	  cpbords+=1.;
	  ktest=kTRUE;
	}
	if(ecart<1.){
	  cp++;
	  x1=clus->GetX();
	  y1=clus->GetY();
	  if(x1<13.5 && x1>-13.5 && y1<15 && y1>-15) {
	    goodclus=j;
	  }
	}
      }//Best cluster = j

      if(cp>0 && goodclus>-1) cpmm+=1.;
      if(cp==1 && goodclus>-1) good=kTRUE;
      if(good==kTRUE) {
	cpclus+=1.;
// 	hmmsq[Int_t((x1+13.5)/6.75)+4*Int_t((-y1+15)/7.5)][chi]->
// 	    Fill((eini+pini-electron-(dvcsev->GetPhoton(goodclus))).Mag2());
	hmm->Fill(cp);
	TCaloCluster *clus=caloev->GetCluster(goodclus);
// 	cout<<"BEFORE ANALISIS"<<endl;
// 	clus->Print();
	energy=0.;npulseave=0.;npulsemax=0.;
	Float_t nbl=0.;
	for(Int_t k=0;k<clus->GetClusSize();k++){
	  Int_t pos;TCaloBlock* block;
	  for(Int_t t=0;t<3;t++){//Loop on trees
	    branchars[t]->GetEntry(i);
	    caloev->SetWaves(arswaves);
	    //clus=caloev->GetCluster(goodclus);
	    //	  cout<<"clus energy "<<clus->GetEnergy()<<endl;
	    TRef* ref=(TRef*)(clus->GetClusBlock())->UncheckedAt(k);
	    block=(TCaloBlock*)ref->GetObject();
	    //pos=caloev->GetBlockPosition(block->GetBlockNumber());
	    pos=lookup[block->GetBlockNumber()];
	    if(pos>-1){
	      TARSWave *wave=caloev->GetWave(pos);
// 		wave->DrawRaw(can);
// 		wave->GetFit("data")->Draw(can);
// 		wave->DrawRaw(can,"same");
// 		wave->GetFit("data")->GetHisto()->SetLineColor(kRed);
// 		can->Update();
// 		can->Modified();

	      if(wave->GetChi2()<chi2thres || t==2){
		t=3;
		block->Erase("");
		if(wave->GetNbPulses()>0){
		  if(wave->GetArrivalTime1()<3 && wave->GetArrivalTime1()>-3){
		    energy+=-(wave->GetAmplitude1());
		    npulseave+=wave->GetNbPulses();
		    block->SetBlockEnergy(-(wave->GetAmplitude1()));
		    if(-(wave->GetAmplitude1())>0) nbl+=1.;
		    if(-(wave->GetAmplitude1())>energytmp){
		      npulsemax=wave->GetNbPulses();
		      energytmp=-(wave->GetAmplitude1());
		      //block->SetBlockEnergy(-(wave->GetAmplitude1()));
		    }
		  }else{
		    block->SetBlockEnergy(0.);
		  }
		}else{
		  block->SetBlockEnergy(0.);
		} 
	      }
	    }else{//endif (pos>-1)
	      block->Erase("");
	      block->SetBlockEnergy(0.);
	    }
	  }//End loop on trees
	}//End loop on cluster blocks

	hblock[trig]->Fill(nbl);
		clus->Analyze(kTRUE);
// 	cout<<"AFTER ANALISIS"<<endl;
// 	clus->Print();
	if(clus->GetEnergy()>2.7) cpgood+=1.;
	hmmsq[Int_t((x1+13.5)/6.75)+4*Int_t((-y1+15)/7.5)][trig]->
	  Fill((eini+pini-electron-(dvcsev->GetPhoton(goodclus))).Mag2());
	he[Int_t((x1+13.5)/6.75)+4*Int_t((-y1+15)/7.5)][trig]->
	  Fill(1.058*energy-mcevent->GetPhoton()->E());
	hnpulave[Int_t((x1+13.5)/6.75)+4*Int_t((-y1+15)/7.5)][trig]->Fill(npulseave/clus->GetClusSize());
	hnpulmax[Int_t((x1+13.5)/6.75)+4*Int_t((-y1+15)/7.5)][trig]->Fill(npulsemax);
	
	if((dvcsev->GetPhoton(goodclus)).P()>0){
	  Float_t thetagen=TMath::ASin(-(mcevent->GetPhoton()->Px())/mcevent->GetPhoton()->P());
	  Float_t phigen=TMath::ASin(mcevent->GetPhoton()->Py()/mcevent->GetPhoton()->P());
	  Float_t theta=TMath::ASin(-((dvcsev->GetPhoton(goodclus)).Px())/(dvcsev->GetPhoton(goodclus)).P());
	  Float_t phi=TMath::ASin((dvcsev->GetPhoton(goodclus)).Py()/(dvcsev->GetPhoton(goodclus)).P());
	  hphi[Int_t((x1+13.5)/6.75)+4*Int_t((-y1+15)/7.5)][trig]->Fill(phi-phigen);	
	  htheta[Int_t((x1+13.5)/6.75)+4*Int_t((-y1+15)/7.5)][trig]->Fill(theta-thetagen);
// 	  cout<<endl<<thetagen<<" "<<theta<<" "<<theta-thetagen<<endl;
// 	  cout<<-(dvcsev->GetPhoton(goodclus)).Px()<<" "<<(dvcsev->GetPhoton(goodclus)).P()<<" "<<-(mcevent->GetPhoton())->Px()<<" "<<mcevent->GetPhoton()->P()<<endl<<endl;
	}
      }
      dvcsev->Reset();//We do reset here and not clear !!
      //caloev->Reset();
      mcevent->Clear();
      TProcessID::SetObjectCount(ObjectNumber);
    }//End loop on events
    eff[trig]=100.*cpgood/nevent;
    effbords[trig]=100.*cpbords/nevent;
    effmm[trig]=100.*cpmm/nevent;
    effclus[trig]=100.*cpclus/nevent;
  }//Loop on trigval

  TCanvas **c[6];
  gStyle->SetCanvasBorderMode(0);
  Int_t n=16,col=4,row=4;
  can->Print("results.ps[");

  Double_t maxe=0.,maxphi=0.,maxtheta=0.,maxmm=0.,maxpulseave=0.,maxpulsemax=0.;
  for(Int_t i=0;i<16;i++){
    for(Int_t k=0;k<ntrig;k++){
      if(he[i][k]->GetMaximum()>maxe) maxe=he[i][k]->GetMaximum();
      if(htheta[i][k]->GetMaximum()>maxtheta) maxtheta=htheta[i][k]->GetMaximum();
      if(hphi[i][k]->GetMaximum()>maxphi) maxphi=hphi[i][k]->GetMaximum();
      if(hmmsq[i][k]->GetMaximum()>maxmm) maxmm=hmmsq[i][k]->GetMaximum();
      if(hnpulave[i][k]->GetMaximum()>maxpulseave) maxpulseave=hnpulave[i][k]->GetMaximum();
      if(hnpulmax[i][k]->GetMaximum()>maxpulsemax) maxpulsemax=hnpulmax[i][k]->GetMaximum();
    }
  }
  Double_t X[ntrig],YE[parts][ntrig],Yphi[parts][ntrig],Ytheta[parts][ntrig],Ymm[parts][ntrig];
  for(Int_t j=0;j<6;j++){
    c[j]=new TCanvas*[ntrig];
    for(Int_t k=0;k<ntrig;k++){
      X[k]=valtrig[k];
      c[j][k]=new TCanvas();
      c[j][k]->Divide(4,4,0,0);
      c[j][k]->SetBorderMode(0);
      for(Int_t i=0;i<parts;i++){
	c[j][k]->cd(i+1);
	if(i/col<row-1) gPad->SetBottomMargin(0);
	if(i/col>0) gPad->SetTopMargin(0);
	if((i+1)%col>0) gPad->SetRightMargin(0);
	if(i%col>0)gPad->SetLeftMargin(0);
	gPad->SetTickx(2);
	gPad->SetTicky(2);
	if(j==0) {
	  he[i][k]->SetMaximum(maxe);
	  he[i][k]->Fit("gaus");
	  he[i][k]->GetFunction("gaus")->SetLineColor(kRed);
	  he[i][k]->GetFunction("gaus")->SetLineWidth(1);
	  YE[i][k]=he[i][k]->GetFunction("gaus")->GetParameter(2);
	  he[i][k]->Draw();
	  gPad->Update();gPad->Modified();
	  TPaveStats *p=(TPaveStats*) (he[i][k]->GetFunction("stats"));
	  p->SetX1NDC(0.55);p->SetY1NDC(0.5);
	  he[i][k]->Draw();
	}
	if(j==1) {
	  htheta[i][k]->SetMaximum(maxtheta);
	  htheta[i][k]->Fit("gaus");
	  htheta[i][k]->GetFunction("gaus")->SetLineColor(kRed);
	  htheta[i][k]->GetFunction("gaus")->SetLineWidth(1);
	  Ytheta[i][k]=htheta[i][k]->GetFunction("gaus")->GetParameter(2);
	  htheta[i][k]->Draw();  
	  gPad->Update();gPad->Modified();
	  TPaveStats *p=(TPaveStats*) htheta[i][k]->GetFunction("stats");
	  p->SetX1NDC(0.55);p->SetY1NDC(0.5);
	  htheta[i][k]->Draw();  
	}
	if(j==2) {
	  hphi[i][k]->SetMaximum(maxphi);
	  hphi[i][k]->Fit("gaus");
	  hphi[i][k]->GetFunction("gaus")->SetLineColor(kRed);
	  hphi[i][k]->GetFunction("gaus")->SetLineWidth(1);
	  Yphi[i][k]=hphi[i][k]->GetFunction("gaus")->GetParameter(2);
	  hphi[i][k]->Draw();  
	  gPad->Update();gPad->Modified();
	  TPaveStats *p=(TPaveStats*) hphi[i][k]->GetFunction("stats");
	  p->SetX1NDC(0.55);p->SetY1NDC(0.5);
	  hphi[i][k]->Draw();  
	}
	if(j==3) {
	  hmmsq[i][k]->SetMaximum(maxmm);
	  Ymm[i][k]=hmmsq[i][k]->GetRMS();
	  hmmsq[i][k]->Draw();  
	  gPad->Update();gPad->Modified();
	  TPaveStats *p=(TPaveStats*) hmmsq[i][k]->GetFunction("stats");
	  p->SetX1NDC(0.55);p->SetY1NDC(0.5);
	  hmmsq[i][k]->Draw();  
	}
	if(j==4) {
	  hnpulave[i][k]->SetMaximum(maxpulseave);
	  hnpulave[i][k]->Draw();  
	  gPad->Update();gPad->Modified();
	  TPaveStats *p=(TPaveStats*) hnpulave[i][k]->GetFunction("stats");
	  p->SetX1NDC(0.55);p->SetY1NDC(0.5);
	  hnpulave[i][k]->Draw();  
	}
	if(j==5) {
	  hnpulmax[i][k]->SetMaximum(maxpulsemax);
	  hnpulmax[i][k]->Draw();  
	  gPad->Update();gPad->Modified();
	  TPaveStats *p=(TPaveStats*) hnpulmax[i][k]->GetFunction("stats");
	  p->SetX1NDC(0.55);p->SetY1NDC(0.5);
	  hnpulmax[i][k]->Draw();  
	}
      }//End i=0...16
      c[j][k]->Print("results.ps");
    }//End k=0...ntrig
  }//End j=0...4
  c[3][0]->Print("results.ps]");

  TGraph **g[parts];
  for(Int_t i=0;i<parts;i++){
    g[i]=new TGraph*[4];
    g[i][0]=new TGraph(ntrig,X,YE[i]);
    g[i][1]=new TGraph(ntrig,X,Ytheta[i]);
    g[i][2]=new TGraph(ntrig,X,Yphi[i]);
    g[i][3]=new TGraph(ntrig,X,Ymm[i]);
  }
  can->Print("summary.ps[");
  TCanvas *d[4];
  for(Int_t i=0;i<4;i++){
    d[i]=new TCanvas();
    d[i]->Divide(4,4);
    for(Int_t j=0;j<parts;j++){
      d[i]->cd(j+1);
      gPad->SetLogx();
      g[j][i]->Draw("A*");
    }
    d[i]->Print("summary.ps");
  }
  TGraph *geff=new TGraph(ntrig,X,eff);
  geff->SetMarkerColor(kRed);
  geff->SetLineColor(kRed);
  TGraph *geffbords=new TGraph(ntrig,X,effbords);
  geffbords->SetMarkerColor(kBlue);
  geffbords->SetLineColor(kBlue);
  TGraph *geffmm=new TGraph(ntrig,X,effmm);
  geffmm->SetMarkerColor(kGreen);
  geffmm->SetLineColor(kGreen);
  TGraph *geffclus=new TGraph(ntrig,X,effclus);
  TMultiGraph *multig=new TMultiGraph();
  multig->Add(geff,"*L");
  multig->Add(geffbords,"*L");
  multig->Add(geffmm,"*L");
  multig->Add(geffclus,"*L");
  TCanvas *ceff=new TCanvas();
  gPad->SetLogx();
  multig->Draw("A");
  TLegend *leg = new TLegend(0.11,0.15,0.52,0.25);
  leg->AddEntry(geffbords,"Cut on edges","l");
  leg->AddEntry(geffmm,"Cut on edges and MM<1 GeV2","l");
  leg->AddEntry(geffclus,"Cut on edges and MM<1 GeV2 and only one clus with MM<1 GeV2","l");
  leg->AddEntry(geff,"All above plus energy_clus>2.7 GeV","l");
  leg->Draw();



  TCanvas *cblocks=new TCanvas();
  cblocks->Divide(3,3);
  for(Int_t i=0;i<ntrig;i++){
    cblocks->cd(i+1);
    hblock[i]->Draw();
  }
  ceff->Print("summary.ps");
  cblocks->Print("summary.ps");
  
  can->Print("summary.ps]");
}
