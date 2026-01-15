#include "TTree.h"
#include "TFile.h"
#include "TClassTable.h"
#include "TDVCSEvent.h"
#include "TDVCSEventMC.h"
#include "TCaloEvent.h"
#include "TObjectTable.h"
#include "TCanvas.h"
#include "TH1.h"
#ifndef ROOT_TProcessID
#include "TProcessID.h"
#endif

void tree()
{  
  TCanvas *display3 = new TCanvas("display3","Cluster 2",455,380,450,350);
  TARSWave* wt=new TARSWave();
  wt->SetPedestalProfileFile("initdata/pro-run169-0.root");

  TH1F *h[132];
  TString title[132];
  for(Int_t i=0;i<132;i++){
    title[i]="h";
    title[i]+=i;
    h[i]=new TH1F(title[i].Data(),title[i].Data(),100,0,20000);
  }
  TFile *f=new TFile("/scratch/munoz/trigcosm418last.dat.root");
  TTree *tree = (TTree*)f->Get("tree");

  TCaloEvent *caloev;

  TBranch *branchcalo=tree->GetBranch("event_calo.");
  branchcalo->SetAddress(&caloev);
  
  Int_t nevent=tree->GetEntries();
  cout<<nevent<<endl;
  //  nevent=10;
  for(Int_t i=0;i<nevent;i++) {
    if(i%1000==0) {
      gObjectTable->Print();
    }
    Int_t ObjectNumber=TProcessID::GetObjectCount();
    cout<<"____________________________________"<<endl;
    if(i%100==0) cout<<i<<endl;
    tree->GetEntry(i);
    for(Int_t j=0;j<caloev->GetNbBlocks();j++){
      TClonesArray* blocks=caloev->GetBlocks();
      TCaloBlock* block=(TCaloBlock*)blocks->UncheckedAt(j);
      if(block->GetBlockNumber()<132){
	caloev->GetWave(j)->SubstractPedestal(((block->GetBlockNumber())/11)+12*((block->GetBlockNumber())%11));
	h[block->GetBlockNumber()]->Fill(-caloev->GetWave(j)->GetSignal()->GetIntegral());
      }
    }
    //    caloev->TriggerSimulation();
    //        caloev->DoClustering();
    //caloev->Print();

    caloev->Reset();//We do reset here and not clear !!
    TProcessID::SetObjectCount(ObjectNumber);
  }
    TCanvas *c=new TCanvas();
    c->Divide(4,3);
    for(Int_t i=0;i<12;i++){
      c->cd(i+1);
      h[11*i+5]->Draw();
    }
    
}



