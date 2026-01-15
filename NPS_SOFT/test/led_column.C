///////////////////////////////////////////////////////////
//
// Macro to analyze one column LED scan
//
///////////////////////////////////////////////////////////

#include "TMultiGraph.h"
#include "TGraph.h"
#include "TCaloEvent.h"
#include "TObjectTable.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TBranch.h"
#include "TProcessID.h"

void ana()
{
TFile *f=new TFile("initdata/newled3490.dat.root");
TTree *tree = (TTree*)f->Get("fTree");
TARSWave* wt=new TARSWave();
wt->SetPedestalProfileFile("initdata/prof-09-03-03.root");
 
TCaloEvent *caloev=0;
Int_t sc;
TBranch *branchcalo=tree->GetBranch("event_calo.");
TBranch *branchscaler=tree->GetBranch("scaler");
branchcalo->SetAddress(&caloev);
branchscaler->SetAddress(&sc);
Int_t nevent=tree->GetEntries();
// nevent=15000;

Double_t **y=new Double_t*[12];
 for(Int_t i=0;i<12;i++) y[i]=new Double_t[701175];
Double_t x[701175];
for(Int_t i=0;i<12;i++){
  for(Int_t j=0;j<701175;j++){
    if(i==0) x[j]=j;
    y[i][j]=0.;
  }
}

for(Int_t i=0;i<nevent;i++) {
  if(i%10000==0) {
    gObjectTable->Print();
  }
  Int_t ObjectNumber=TProcessID::GetObjectCount();
  if(i%5000==0) cout<<i<<"/"<<nevent<<endl;
  tree->GetEntry(i);
  for(Int_t j=0;j<caloev->GetNbBlocks();j++){
    TCaloBlock* block=(TCaloBlock*)caloev->GetBlocks()->UncheckedAt(j);
    if(block->GetBlockNumber()<12){
      TARSWave *wave=caloev->GetWave(j);
      wave->SubstractPedestal(block->GetBlockNumber());
      y[block->GetBlockNumber()][sc-3726521]=wave->GetSignal()->GetIntegral();
    }
  }
  caloev->Reset();//We reset the read event
  TProcessID::SetObjectCount(ObjectNumber);
}
 TMultiGraph *gmulti=new TMultiGraph();
 TGraph *g[12];
 for(Int_t i=0;i<12;i++){
   g[i]=new TGraph(701175,x,y[i]);
   g[i]->SetMarkerColor((i%7)+1);
   gmulti->Add(g[i],"P");
 }
 TCanvas *c=new TCanvas();
 gmulti->Draw("A");
}
