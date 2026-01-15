{
////////////////////////////////////////////////////////////////////////////
// 
// This macro shows how to read a raw tree with ARS LED data and analyze it
//
// C Munoz (26 Dec 2003)
//
////////////////////////////////////////////////////////////////////////////
  
TFile *f=new TFile("initdata/trigcol0_1132.dat.root");
TTree *tree = (TTree*)f->Get("fTree");
TARSWave* wt=new TARSWave();
wt->SetPedestalProfileFile("initdata/prof-09-03-03.root");
Double_t x[12][10000],y[12][10000],y2[12][10000];
for(Int_t j=0;j<12;j++){
for(Int_t i=0;i<10000;i++){
  x[j][i]=0;
  y[j][i]=0;
  y2[j][i]=0;
}
}
cout<<"end initialization"<<endl;
TH1F *h[12];
TH1F *p[8];
TProfile *prof[8];
for(Int_t i=0;i<8;i++){
  TString name("hh");
  name+=i;
  p[i]=new TH1F(name.Data(),name.Data(),10000,0,10000);
  name+=i;
  prof[i]=new TProfile(name.Data(),name.Data(),128,0,128);
}
TString title[12];
for(Int_t i=0;i<12;i++){
  title[i]="h";
  title[i]+=i;
  h[i]=new TH1F(title[i].Data(),title[i].Data(),100,0,20000);
}
TCanvas *can=new TCanvas();
Int_t cp=0,cpm=0;
Double_t cpt=0.;
TCaloEvent *caloev;
Int_t sc;
TBranch *branchcalo=tree->GetBranch("event_calo.");
TBranch *branchscaler=tree->GetBranch("scaler");
branchcalo->SetAddress(&caloev);
branchscaler->SetAddress(&sc);
Int_t nevent=tree->GetEntries();
cout<<nevent<<endl;
//  nevent=10;
for(Int_t i=3000;i<nevent;i++) {
  if(i%1000==0) {
    gObjectTable->Print();
  }
  Int_t ObjectNumber=TProcessID::GetObjectCount();
  if(i%1000==0) cout<<i<<endl;
  tree->GetEntry(i);
  //  for(Int_t j=0;j<caloev->GetNbBlocks();j++){
  for(Int_t j=0;j<1;j++){
    TCaloBlock* block=caloev->GetBlock(j);
    Int_t blocknb=block->GetBlockNumber();
    TARSWave *wave=caloev->GetWave(j);
    wave->SetNbChannel(0);
    wave->SubstractPedestal(blocknb);
    wave->Analyze("LED");
    //We look in a bigger time window for the first events
    if(i==3000) wave->SetFirstWindow(-10,10,"LED"); 
    if(i<6000){
      cpt+=wave->GetArrivalTime1();
      cpm+=1;
    }
    // Now we narrow the window with the mean arrival time found in the first events
    if(i==6000) {
      cout<<"The mean arrival time found is "<<cpt/cpm<<endl;
      wave->SetFirstWindow(Int_t(cpt/cpm)-1,Int_t(cpt/cpm)+1,"LED");
    }
//     if(i%2==0) wave->SetFirstWindow(-120,-40,"LED");
//     if(i%2!=0) wave->SetFirstWindow(-1,1,"LED");

    //Visualization
//     cout<<"Arrival time : "<<wave->GetArrivalTime1()<<endl;
//     wave->GetFit("LED")->Draw(can);
//     wave->DrawSignal(can,"same");
//     wave->GetFit("LED")->GetHisto()->SetLineColor(kRed);
//     wave->GetFit("LED")->GetHisto()->SetDrawOption("same");
    
    h[blocknb]->Fill(-wave->GetSignal()->GetIntegral());
    y[j][i]=-wave->GetSignal()->GetIntegral();
    y2[j][i]=wave->GetAmplitude1();
    x[j][i]=sc;
    cp+=1;
    if(j==0) p[i%8]->Fill(x[j][i],y[j][i]);
    if(j==0) {
      for(Int_t k=0;k<wave->GetArray()->GetArray()->GetArray()->GetLast();k++){
	
	prof[i%8]->Fill(k,wave->GetSignal()->GetValue(k));
      }
    }
  }
  caloev->Reset();//We do reset here and not clear !!
  TProcessID::SetObjectCount(ObjectNumber);
  
}
TCanvas *c=new TCanvas();
c->Divide(4,3);
TCanvas *c2=new TCanvas();
c2->Divide(4,3);
TGraph *g[12];
TGraph *g2[12];
for(Int_t i=0;i<12;i++){
  g[i]=new TGraph(10000,x[i],y[i]);
  c->cd(i+1);
  g[i]->Draw("A*");
}
for(Int_t i=0;i<12;i++){
  g2[i]=new TGraph(10000,x[i],y2[i]);
  c2->cd(i+1);
  g2[i]->Draw("A*");
}
TCanvas *d=new TCanvas();
d->Divide(4,2);
for(Int_t i=0;i<8;i++){
  d->cd(i+1);
  p[i]->Draw();
}
TCanvas *e=new TCanvas();
e->Divide(4,2);
for(Int_t i=0;i<8;i++){
  e->cd(i+1);
  prof[i]->Draw();
}
}


