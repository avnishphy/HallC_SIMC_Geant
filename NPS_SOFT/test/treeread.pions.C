#include "TTree.h"
#include "TFile.h"
#include "TClassTable.h"
#include "TDVCSEvent.h"
#include "TDVCSEventMC.h"
#include "TCaloEvent.h"
#include "TCanvas.h"
#include "TH1.h"
#ifndef ROOT_TProcessID
#include "TProcessID.h"
#endif

void tree()
{  
  TCanvas *display3 = new TCanvas("display3","Cluster 2",455,380,450,350);

  TH1F *h = new TH1F("h","Energy resolution",100, -.3, .3 );

  Float_t e1=0.,e2=0.;

  TLorentzVector pho1rec, pho2rec;
  TLorentzVector *pho1gen=new TLorentzVector();
  TLorentzVector *pho2gen=new TLorentzVector();

  Float_t thetagen1, thetagen2, thetarec1, thetarec2, phigen1, phigen2, phirec1, phirec2;
  Float_t resg1, resg2, resphi1, resphi2, restheta1, restheta2;
  TVector3 imprec1,imprec2, impgen1,impgen2;


  TH1F *hresg1 = new TH1F("hresg1", "Energy resolution photon 1", 100, -1, 0.5);
  TH1F *hresg2 = new TH1F("hresg2", "Energy resolution photon 2", 100, -1, 0.5);
  TH1F *hrestheta1 = new TH1F("hrestheta1", "Theta resolution photon 1", 100, -2, 2);
  TH1F *hrestheta2 = new TH1F("hrestheta2", "Theta resolution photon 2", 100, -2, 2);
  TH1F *hresphi1 = new TH1F("hresphi1", "Phi resolution photon 1", 100, -2, 2);
  TH1F *hresphi2 = new TH1F("hresphi2", "Phi resolution photon 2", 100, -2, 2);

  TFile *f=new TFile("tree.root");
  TTree *tree = (TTree*)f->Get("tree");

  TDVCSEvent *event=new TDVCSEvent();
  TDVCSEventMC *mcevent=new TDVCSEventMC();
  TCaloEvent *caloev=new TCaloEvent();
  TPAEvent *paev=new TPAEvent();

  TBranch *branchcalo=tree->GetBranch("event_calo.");
   TBranch *branchpa=tree->GetBranch("event_pa.");
 TBranch *branchmc=tree->GetBranch("event_mc.");
  TBranch *branchdvcs=tree->GetBranch("event_dvcs");
  branchmc->SetAddress(&mcevent);
  branchcalo->SetAddress(&caloev);
  branchpa->SetAddress(&paev);
  branchdvcs->SetAddress(&event);
  
  Int_t nevent=tree->GetEntries();

  Float_t radtodeg=180/TMath::Pi();

  //  nevent=1000;

  for(Int_t i=0;i<nevent;i++) {

    Int_t ObjectNumber=TProcessID::GetObjectCount();

    thetagen1=thetagen2=thetarec1=thetarec2=phigen1=phigen2=phirec1=phirec2=-3.14;
    resg1=resg2=resphi1=resphi2=restheta1=restheta2=-10000;

    if(i%1000==0) cout<<i<<endl;
    //branch->GetEntry(i);
    tree->GetEntry(i);
    if (caloev->GetNbClusters()>0) {
      TCaloEvent *evcalo=event->GetCaloEvent();
      //cout<<evcalo->GetEnergy()<<endl;
      TCaloCluster *caloclus=evcalo->GetCluster(0);
      //      caloev->GetCluster(0)->Display(display3,3);
      //caloclus->Display(display3,3);
      //TLorentzVector phot=caloev->GetCluster(0)->GetPhoton();
      //      for(Int_t i=0;i<1000000000;i++);
      //cout<<"Cluster 1 : "<<phot.Py()<<endl;

      event->GetCaloEvent()->GetCluster(0)->Analyze();

      pho1gen=mcevent->GetPhoton();
      pho2gen=mcevent->GetPhoton(1);
      pho1rec=1.058*(event->GetPhoton());

      imprec1=pho1rec.Vect();
      impgen1=pho1gen->Vect();
      impgen2=pho2gen->Vect();

      thetagen1=TMath::ASin(-impgen1(0)/impgen1.Mag());
      phigen1=TMath::ASin(impgen1(1)/impgen1.Mag());
      thetagen2=TMath::ASin(-impgen2(0)/impgen2.Mag());
      phigen2=TMath::ASin(impgen2(1)/impgen2.Mag());

      if(imprec1.Mag()!=0) thetarec1=TMath::ASin(-imprec1(0)/imprec1.Mag());
      if(imprec1.Mag()!=0) phirec1=TMath::ASin(imprec1(1)/imprec1.Mag());

      Float_t dtheta1=TMath::Sqrt((thetarec1-thetagen1)*(thetarec1-thetagen1));
      Float_t dtheta2=TMath::Sqrt((thetarec1-thetagen2)*(thetarec1-thetagen2));
      Float_t dphi1=TMath::Sqrt((phirec1-phigen1)*(phirec1-phigen1));
      Float_t dphi2=TMath::Sqrt((phirec1-phigen2)*(phirec1-phigen2));
    
      Float_t dis=TMath::Max(TMath::Max(dtheta1,dtheta2),TMath::Max(dphi1,dphi2));
      
      if(dis==dtheta2 || dis==dphi2){
	resg1=(pho1rec.E()-pho1gen->E());
	restheta1=(thetarec1-thetagen1)*radtodeg;
	resphi1=(phirec1-phigen1)*radtodeg;
	//eg1rap=photonrec1.E()/(genev->_photon1).E();
      }
      else{
	resg1=(pho1rec.E()-pho2gen->E());
	restheta1=(thetarec1-thetagen2)*radtodeg;
	resphi1=(phirec1-phigen2)*radtodeg;
	//eg1rap=photonrec1.E()/(genev->_photon2).E();
      }
     if(thetagen1*radtodeg>9 && thetagen1*radtodeg<20 && phigen1*radtodeg>-6.5 &&phigen1<6.5){

	hresg1->Fill(resg1);
	hrestheta1->Fill(restheta1);
	hresphi1->Fill(resphi1);
	//cout<<"photon1 "<<resg1<<" "<<restheta1<<" "<<resphi1<<" "<<pho1gen->E()<<endl;
     }
    }
    if (caloev->GetNbClusters()==2) {
      TCaloEvent *evcalo=event->GetCaloEvent();
      //cout<<evcalo->GetEnergy()<<endl;
      TCaloCluster *caloclus=evcalo->GetCluster(0);
      TCaloCluster *caloclus2=evcalo->GetCluster(1);
      //      caloev->GetCluster(0)->Display(display3,3);
      //caloclus->Display(display3,3);
      //TLorentzVector phot=caloev->GetCluster(0)->GetPhoton();
      //      for(Int_t i=0;i<1000000000;i++);
      //cout<<"Cluster 1 : "<<phot.Py()<<endl;

      event->GetCaloEvent()->GetCluster(0)->Analyze();
      event->GetCaloEvent()->GetCluster(1)->Analyze();

      pho1gen=mcevent->GetPhoton();
      pho2gen=mcevent->GetPhoton(1);
      pho1rec=1.058*(event->GetPhoton());
      pho2rec=1.058*(event->GetPhoton(1));

      imprec1=pho1rec.Vect();
      imprec2=pho2rec.Vect();
      impgen1=pho1gen->Vect();
      impgen2=pho2gen->Vect();

      thetagen1=TMath::ASin(-impgen1(0)/impgen1.Mag());
      phigen1=TMath::ASin(impgen1(1)/impgen1.Mag());
      thetagen2=TMath::ASin(-impgen2(0)/impgen2.Mag());
      phigen2=TMath::ASin(impgen2(1)/impgen2.Mag());

      if(imprec1.Mag()!=0) thetarec1=TMath::ASin(-imprec1(0)/imprec1.Mag());
      if(imprec1.Mag()!=0) phirec1=TMath::ASin(imprec1(1)/imprec1.Mag());
      if(imprec2.Mag()!=0) thetarec2=TMath::ASin(-imprec2(0)/imprec2.Mag());
      if(imprec2.Mag()!=0) phirec2=TMath::ASin(imprec2(1)/imprec2.Mag());

      Float_t dtheta1=TMath::Sqrt((thetarec2-thetagen1)*(thetarec2-thetagen1));
      Float_t dtheta2=TMath::Sqrt((thetarec2-thetagen2)*(thetarec2-thetagen2));
      Float_t dphi1=TMath::Sqrt((phirec2-phigen1)*(phirec2-phigen1));
      Float_t dphi2=TMath::Sqrt((phirec2-phigen2)*(phirec2-phigen2));
    
      Float_t dis=TMath::Max(TMath::Max(dtheta1,dtheta2),TMath::Max(dphi1,dphi2));
      
      if(dis==dtheta2 || dis==dphi2){
	resg2=(pho2rec.E()-pho1gen->E());
	restheta2=(thetarec2-thetagen1)*radtodeg;
	resphi2=(phirec2-phigen1)*radtodeg;
	//eg1rap=photonrec1.E()/(genev->_photon1).E();
      }
      else{
	resg2=(pho2rec.E()-pho2gen->E());
	restheta2=(thetarec2-thetagen2)*radtodeg;
	resphi2=(phirec2-phigen2)*radtodeg;
	//eg1rap=photonrec1.E()/(genev->_photon2).E();
     }

      if(thetagen2*radtodeg>9 && thetagen2*radtodeg<20 && phigen2*radtodeg>-6.5 &&phigen2<6.5){
	hresg2->Fill(resg2);
	hrestheta2->Fill(restheta2);
	hresphi2->Fill(resphi2);
	//cout<<"photon2 "<<resg2<<" "<<restheta2<<" "<<resphi2<<" "<<pho2gen->E()<<endl;
      }
    }


    caloev->Reset();
    paev->Reset();
    TProcessID::SetObjectCount(ObjectNumber);
  }

  TCanvas *canvas= new TCanvas();
  canvas->Divide(2,3);
  canvas->cd(1);
  hresg1->Draw();
  canvas->cd(2);
  hresg2->Draw();
  canvas->cd(3);
  hrestheta1->Draw();
  canvas->cd(4);
  hrestheta2->Draw();
  canvas->cd(5);
  hresphi1->Draw();
  canvas->cd(6);
  hresphi2->Draw();

  //  h->Draw();
  
}






