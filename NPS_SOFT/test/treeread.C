#include "TTree.h"
#include "TFile.h"
#include "TClassTable.h"
#include "TDVCSEvent.h"
#include "TDVCSEventMC.h"
#include "TCaloEvent.h"
#include "TObjectTable.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TNtuple.h"
#ifndef ROOT_TProcessID
#include "TProcessID.h"
#endif

void tree()
{  
  //  TCanvas *display3 = new TCanvas("display3","Cluster 2",455,380,450,350);
  TNtuple *ntuple=new TNtuple("ntuple","My ntuple","energyrec:energyint:energywave:energymc:x:y:nbblocks:chi2m:chi2:nbpulsesm:nbpulses:good:a1m:a1:a2m:a2:t1m:t1:t2m:t2");
  TFile *f=new TFile("treenewbruitwph.root");
  TTree *tree = (TTree*)f->Get("tree");

  TDVCSEventMC *mcevent=new TDVCSEventMC();
  TCaloEvent *caloev=new TCaloEvent();
  TARSWave *t=new TARSWave(128);
  t->SetFirstWindow(-2,2,"data");
  t->SetSecondWindow(-128,100,"data");

  TBranch *branchcalo=tree->GetBranch("event_calo.");
  TBranch *branchmc=tree->GetBranch("event_mc.");
  branchcalo->SetAddress(&caloev);
  branchmc->SetAddress(&mcevent);
  TCanvas *can=new TCanvas();

  TH1F *hint=new TH1F("hint","Reso with integral",100,-1.5,.5);
  TH1F *hwonoise=new TH1F("hwonoise","Reso without noise",100,-1.5,.5);
  TH1F *hwf=new TH1F("hwf","Reso with shape analysis",100,-1.5,.5);

  Float_t *w=new Float_t[20];
  Double_t energyrec, energywave, energymc, energyint,x,y,nbblocks,chi2m,chi2,nbpulsesm, nbpulses,a1m,a1,a2m,a2,t1m,t1,t2m,t2,energytmp,energytmp2,energytmp3,good;

  Int_t nevent=tree->GetEntries();
  cout<<nevent<<endl;
  //  nevent=10000;
  for(Int_t i=0;i<nevent;i++) {
    if(i%1000==0) {
      gObjectTable->Print();
    }
    Int_t ObjectNumber=TProcessID::GetObjectCount();
    //cout<<"____________________________________"<<endl;
    if(i%100==0) cout<<i<<endl;
    //branch->GetEntry(i);
    tree->GetEntry(i);
    
    energyrec=0.;energywave=0.;energyint=0.,nbblocks=0.;chi2m=0.;chi2=0.;a1m=0.;a1=0.;a2m=0.;a2=0.;t1m=-1000.;t1=-1000.;t2m=-1000.;t2=-1000.,energytmp=0.,energytmp2=0.,energytmp3=0.,nbpulses=0.;good=1.;
    if(mcevent->GetNbPhotons()>0) energymc=mcevent->GetPhoton()->E();
    if(caloev->GetNbBlocks()>0){
      caloev->GetCluster(0)->Analyze();
      x=caloev->GetCluster(0)->GetX();
      y=caloev->GetCluster(0)->GetY();
      //      caloev->Print();
      for(Int_t k=0;k<caloev->GetNbBlocks();k++){
        TARSWave *wave=caloev->GetWave(k);
        TCaloBlock *block=(TCaloBlock*)(caloev->GetBlocks()->UncheckedAt(k));
	energyrec+=block->GetBlockEnergy();
	energyint+=(wave->GetArray()->GetIntegral(25,85))/(-12836.3);//Calibration
	//	if(block->GetBlockEnergy()>0.2){
	  wave->SetNbChannel(0);
	  wave->Analyze("datawave");
	  chi2m+=wave->GetChi2();
	  nbpulsesm+=wave->GetNbPulses();
	  if(block->GetBlockEnergy()>energytmp) {
	    chi2=wave->GetChi2();
	    energytmp=block->GetBlockEnergy();
	    nbpulses=wave->GetNbPulses();
	  }
	  if(wave->GetNbPulses()>0){
	    t1=0.;t1m=0.;
// 	    wave->GetFit("data")->Draw(can);
// 	    wave->DrawRaw(can,"same");
// 	    wave->GetFit("data")->GetHisto()->SetLineColor(kRed);
// 	    wave->GetFit("data")->GetHisto()->SetDrawOption("same");
	    //	    cout<<"energy 1 "<<wave->GetAmplitude1()<<"   time1 "<<wave->GetArrivalTime1()<<endl;
	    Double_t time=wave->GetArrivalTime1();
	    if(time<3 && time>-3) {
	      energywave+=-(wave->GetAmplitude1());
	      t1m+=time;
	      a1m+=-(wave->GetAmplitude1());
	      if(block->GetBlockEnergy()>energytmp2) {
		t1=time;
		a1=-(wave->GetAmplitude1());
		energytmp2=block->GetBlockEnergy();
	      }
	    }
	    if(wave->GetNbPulses()>1) {
	      t2=0.;t2m=0.;
	      //cout<<"energy 2 "<<wave->GetAmplitude2()<<"   time2 "<<wave->GetArrivalTime2()<<endl;
	      Double_t time2=wave->GetArrivalTime2();
	      if(time<3 && time>-3 && time2<3 && time2>-3) {
		cout<<"Warning: counting 2 pulses in one"<<endl;
		good=0.;
	      }
	      if(time2<3 && time2>-3) {
		energywave+=-(wave->GetAmplitude2());
		t1m+=time2;
		t2m+=time;
		a1m+=-(wave->GetAmplitude2());
		a2m+=-(wave->GetAmplitude1());
		if(block->GetBlockEnergy()>energytmp3) {
		  t1=time2;
		  t2=time;
		  a1+=-(wave->GetAmplitude2());
		  a2+=-(wave->GetAmplitude1());
		  energytmp3=block->GetBlockEnergy();
		}

	      }
	    }
	    //	    cout<<"Block energy "<<block->GetBlockEnergy()<<endl;
	    //	    for(Int_t kk=0;kk<10000;kk++);
	    //	  }
	}
      }
      w[0]=energyrec;
      w[1]=energyint;
      w[2]=energywave;
      w[4]=x;
      w[5]=y;
      w[6]=caloev->GetNbBlocks();
      w[7]=chi2m;
      w[8]=chi2;
      w[9]=nbpulsesm;
      w[10]=nbpulses;
      w[11]=good;
      w[12]=a1m;
      w[13]=a1;
      w[14]=a2m;
      w[15]=a2;
      w[16]=t1m;
      w[17]=t1;
      w[18]=t2m;
      w[19]=t2;
      w[3]=energymc;

      //      ntuple->Fill(energyrec,energyint,energywave,energymc,x,y,caloev->GetNbBlocks(),chi2m,chi2,nbpulsesm,nbpulses,good,a1m,a1,a2m,a2,t1m,t1,t2m,t2);
      ntuple->Fill(w);
    }
    //    cout<<"ENERGY : "<<energymc<<" "<<energyint<<" "<<energyrec<<" "<<energywave<<endl;
    hint->Fill(energyint-energymc);
    hwf->Fill(energywave-energymc);
    hwonoise->Fill(energyrec-energymc);

    caloev->Reset();//We do reset here and not clear !!
    mcevent->Clear();
    TProcessID::SetObjectCount(ObjectNumber);
  }
  TCanvas *res=new TCanvas();
  res->Divide(2,2);
  res->cd(1);
  hwonoise->Draw();
  res->cd(2);
  hint->Draw();
  res->cd(3);
  hwf->Draw();
  TFile ntu("tnuple5.root","RECREATE");
  ntuple->Write();
}



