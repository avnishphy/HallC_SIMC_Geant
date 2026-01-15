///////////////////////////////////////////////////////////////
// 
// This macro allows to compare two fixed runs (in front of a 
// single block). Spectra are fitted by several gaussien (3).
//
///////////////////////////////////////////////////////////////

{

TFile *f=new TFile("initdata/newled3473.dat.root");
TTree *tree = (TTree*)f->Get("fTree");
TFile *f2=new TFile("initdata/newled3474.dat.root");
TTree *tree2 = (TTree*)f2->Get("fTree");
TARSWave* wt=new TARSWave();
wt->SetPedestalProfileFile("initdata/prof-09-03-03.root");

TCaloEvent *caloev=0;
Int_t sc;
TBranch *branchcalo=tree->GetBranch("event_calo.");
TBranch *branchscaler=tree->GetBranch("scaler");
TBranch *branchcalo2=tree2->GetBranch("event_calo.");
TBranch *branchscaler2=tree2->GetBranch("scaler");
branchcalo->SetAddress(&caloev);
branchscaler->SetAddress(&sc);
branchcalo2->SetAddress(&caloev);
branchscaler2->SetAddress(&sc);
Int_t nevent=tree->GetEntries();
Int_t nevent2=tree->GetEntries();
nevent=TMath::Min(nevent,nevent2);
cout<<nevent<<endl;
//nevent=15000;

TH1F *h[8];
TH1F *h2[8];
for(Int_t i=0;i<8;i++){
  TString name("h");name+=i;
  h[i]=new TH1F(name.Data(),name.Data(),1000,0,25000);
  TString name2("hbis");name2+=i;
  h2[i]=new TH1F(name2.Data(),name2.Data(),1000,0,25000);
}

for(Int_t i=10000;i<nevent;i++) {
  if(i%1000==0) {
    gObjectTable->Print();
  }
  Int_t ObjectNumber=TProcessID::GetObjectCount();
  if(i%1000==0) cout<<i<<"/"<<nevent<<endl;
  tree->GetEntry(i);
  if(caloev->GetBlockPosition(11)>-1){
    TARSWave *wave=caloev->GetWave(caloev->GetBlockPosition(11));
    wave->SubstractPedestal(11);
    h[sc%8]->Fill(-wave->GetSignal()->GetIntegral());
  }
  caloev->Reset();//We reset the read event
  tree2->GetEntry(i);
  if(caloev->GetBlockPosition(11)>-1){
    TARSWave *wave=caloev->GetWave(caloev->GetBlockPosition(11));
    wave->SubstractPedestal(11);
    h2[sc%8]->Fill(-wave->GetSignal()->GetIntegral());
  }
  caloev->Reset();//We reset the read event
  TProcessID::SetObjectCount(ObjectNumber);
}
TCanvas *c=new TCanvas();
c->Divide(4,2);
for(Int_t i=0;i<8;i++){
  c->cd(i+1);
  h[i]->Draw();
}

TCanvas *c2=new TCanvas();

Double_t par[9];
Double_t par2[9];
g1    = new TF1("g1","gaus",3000,8000);
g2    = new TF1("g2","gaus",8000,15000);
g3    = new TF1("g3","gaus",15000,24000);
total = new TF1("total","gaus(0)+gaus(3)+gaus(6)",0,25000);
total->SetLineColor(kRed);
h2[0]->Fit(g1,"R");
h2[0]->Fit(g2,"R+");
h2[0]->Fit(g3,"R+");
g1->GetParameters(&par[0]);
g2->GetParameters(&par[3]);
g3->GetParameters(&par[6]);
total->SetParameters(par);
h2[0]->Fit(total,"R+");
h2[0]->SetLineColor(kRed);
 h[0]->Draw("same");
gb1    = new TF1("g1b","gaus",3000,8000);
gb2    = new TF1("g2b","gaus",8000,15000);
gb3    = new TF1("g3b","gaus",15000,24000);
totalb = new TF1("totalb","gaus(0)+gaus(3)+gaus(6)",0,25000);
totalb->SetLineColor(kBlack);
totalb->SetLineWidth(0.5)
h[0]->Fit(g1b,"R");
h[0]->Fit(g2b,"R+");
h[0]->Fit(g3b,"R+");
gb1->GetParameters(&par2[0]);
gb2->GetParameters(&par2[3]);
gb3->GetParameters(&par2[6]);
totalb->SetParameters(par2);
h[0]->Fit(totalb,"R+same");

h[0]->Draw();
h2[0]->Draw("same");

}
