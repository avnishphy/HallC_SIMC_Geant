// To use it, rename the output file of Calana.cxx, tree.root, to clus1.root,
// create .so (.L copla.C+), and execute (tree())

#include "TTree.h"
#include "TFile.h"
#include "TClassTable.h"
#include "TDVCSEvent.h"
#include "TDVCSEventMC.h"
#include "TCaloEvent.h"
#include "TPAEvent.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TBranch.h"

void tree()
{  
  //  TCanvas *display3 = new TCanvas("display3","Cluster 2",455,380,450,350);

  TH1F *h = new TH1F("h","Energy resolution",100, -0.3, .3 );
TH1F *hx = new TH1F("hx","",100, -10,10 );
TH1F *hy = new TH1F("hy","",100, -10, 10 );
TH1F *hz = new TH1F("hz","",100, -10, 10 );

  Float_t e1=0.,e2=0.;

  TFile *f=new TFile("tree.root");
  TTree *tree = (TTree*)f->Get("t");

  TDVCSEvent *event=new TDVCSEvent();
  TDVCSEventMC *mcevent=new TDVCSEventMC();
  TCaloEvent *caloev=new TCaloEvent();
  TPAEvent *paev=new TPAEvent();

  TBranch *branchcalo=tree->GetBranch("event_calo");
  TBranch *branchpa=tree->GetBranch("event_pa");
  TBranch *branchmc=tree->GetBranch("event_mc");
  TBranch *branchdvcs=tree->GetBranch("event_dvcs");
  branchmc->SetAddress(&mcevent);
  branchcalo->SetAddress(&caloev);
  branchpa->SetAddress(&paev);
  branchdvcs->SetAddress(&event);
  
  Int_t nevent=tree->GetEntries();

  //    nevent=10000;

  TLorentzVector q,elprime,p,g,gmc,pmc;
  TLorentzVector el(0.,0.,5.75,5.75);
  for(Int_t i=0;i<nevent;i++) {

    if(i%1000==0) cout<<i<<endl;
    //branch->GetEntry(i);
    tree->GetEntry(i);
    if (caloev->GetNbClusters()>0 && event->ThereIsAProton()) {

      TCaloEvent *evcalo=event->GetCaloEvent();
      TCaloCluster *caloclus=evcalo->GetCluster(0);
      caloclus->Analyze();
      g=event->GetPhoton();
      //p=event->GetProtonDirFast();
      gmc=*(mcevent->GetPhoton());
      pmc=*(mcevent->GetProton());
      elprime=*(mcevent->GetElectron());
      q=elprime-el;

      TVector3 v1=event->GetProtonDirFast();//p.Vect();//.Cross(photonvirtimp);
     TVector3 v2=(g.Vect()).Cross(q.Vect());

      if(v1.Mag()!=0.){
 	v1=v1*(1./v1.Mag());
      }
      v2=v2*(1./v2.Mag());

      Double_t anglevec=v1*v2;

      if(v1.Mag()>0 && v2.Mag()>0) h->Fill(anglevec);
      
      TVector3 impgen=pmc.Vect();
      TVector3 imprec=event->GetProtonDirFast();//p.Vect();
      imprec*=1.4;

      Float_t thetagen=TMath::ASin(-impgen(0)/impgen.Mag());
      Float_t phigen=TMath::ASin(impgen(1)/impgen.Mag());
      Float_t thetarec=TMath::ASin(-imprec(0)/imprec.Mag());
      Float_t phirec=TMath::ASin(imprec(1)/imprec.Mag());

      Float_t radtodeg=180/TMath::Pi();

//        if( v1.Mag()>0 && v2.Mag()>0) hx->Fill((imprec.Phi()-impgen.Phi())*radtodeg);
//        if( v1.Mag()>0 && v2.Mag()>0) hy->Fill((imprec.Theta()-impgen.Theta())*radtodeg);
      if( v1.Mag()>0 && v2.Mag()>0) hx->Fill((imprec.Phi()-impgen.Phi())*radtodeg);
      if( v1.Mag()>0 && v2.Mag()>0) hy->Fill((imprec.Theta()-impgen.Theta())*radtodeg);
    }
    event->Reset();
    mcevent->Clear();
    //    caloev->Clear();
  }

    h->Draw();
  
    TCanvas *toto=new TCanvas();
    toto->Divide(1,2);
    toto->cd(1);
    hx->Draw();
    toto->cd(2);
    hy->Draw();


}



