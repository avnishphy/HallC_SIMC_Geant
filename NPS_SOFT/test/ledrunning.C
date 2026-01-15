{
//////////////////////////////////////
//
// This macro compares waveanalysis and ARS integral
// on LED data and shows how to use the Rrnning average
// method to calculate the reference shape
//
// Carlos (6 Aug 2004)
//
/////////////////////////////////////////

gStyle->SetOptFit(1111);
TFile *f=new TFile("/scratch/munoz/newled3800.dat.root");
TTree *tree = (TTree*)f->Get("fTree");
TARSWave* wt=new TARSWave();
wt->SetPedestalProfileFile("initdata/ped-06-15-2004.root");
wt->SetFirstWindow(-5,5,"LED"); 
wt->SetChi20(1.);
wt->SetChi21(1e10);
wt->SetChi22(1e10);

TCanvas *can=new TCanvas();

TCaloEvent *caloev;
TBranch *branchcalo=tree->GetBranch("event_calo.");
branchcalo->SetAddress(&caloev);

Int_t nevent=tree->GetEntries();
cout<<nevent<<endl;
nevent=4000;

TProfile *prof[8];
for(Int_t i=0;i<8;i++){
  TString name("prof");name+=i;
  prof[i]=new TProfile(name.Data(),name.Data(),128,0,128);
  prof[i]->SetMarkerColor(i+1);
  prof[i]->SetLineColor(i+1);
}

TH1F *hamp=new TH1F("hamp","hamp",100,-800,-500);
TH1F *hampwf=new TH1F("hampwf","hampwf",100,0.,2);
TH1F *hint=new TH1F("hint","hint",100,-20000,-13000);
TH1F *hb=new TH1F("hb","hb",100,-50,50);
       
for(Int_t i=1000;i<nevent;i++) {
  if(i%1000==0) {
    gObjectTable->Print();
  }
  Int_t ObjectNumber=TProcessID::GetObjectCount();
  if(i%1000==0) cout<<i<<endl;
  tree->GetEntry(i);
  ///////////////////
  Int_t nb=caloev->GetNbBlocks();
  for(Int_t j=0;j<nb;j++){
    TCaloBlock *block=caloev->GetBlock(j);
    if(block->GetBlockNumber()==78) {
      TARSWave *wave=caloev->GetWave(j);
      wave->SetNbChannel(0);
      wave->SubstractPedestal(block->GetBlockNumber());
      wave->Analyze("LED");
      wave->Add2RunningShape(wave->GetSignal(),0,wave->GetAmplitude1(),wave->GetArrivalTime1(),"LED");
//       cout<<"Arrival time : "<<wave->GetArrivalTime1()<<endl;
//       cout<<"Amplitude : "<<wave->GetAmplitude1()<<endl;
//       wave->GetFit("LED")->Draw(can);
//       if(i==1000)   wave->DrawSignal(can);
//       if(i>1000)   wave->DrawSignal(can,"same");
//       wave->GetFit("LED")->GetHisto()->SetLineColor(kRed);
//       wave->GetFit("LED")->GetHisto()->SetDrawOption("same");
      hampwf->Fill(-(wave->GetAmplitude1()));
      hb->Fill(wave->GetB());
      Int_t min=wave->GetSignal()->GetMinimumBin();
      hamp->Fill(wave->GetSignal()->GetValue(min));
      hint->Fill(wave->GetSignal()->GetIntegral());
      for(Int_t k=0;k<128;k++){
	prof[(caloev->GetScaler())%8]->Fill(k,wave->GetSignal()->GetValue(k));
      }
    }
  }
  ///////////////////////////
  caloev->Reset();//We do reset here and not clear !!
  TProcessID::SetObjectCount(ObjectNumber);
  
}//End of loop on events

TCanvas *c=new TCanvas();
c->Divide(4,2);
for(Int_t i=0;i<8;i++){
  c->cd(i+1);
  prof[i]->Draw();
}

TCanvas *c2=new TCanvas();
prof[0]->Draw();
for(Int_t i=1;i<8;i++){
  prof[i]->Draw("same");
}

ofstream fout("refshapeled.txt");
for(Int_t i=0;i<128;i++){
  fout<<prof[0]->GetBinContent(i+1)<<endl;
}

TCanvas *c3=new TCanvas();
c3->Divide(2,2);
c3->cd(1);hamp->Fit("gaus");hamp->Draw();
c3->cd(2);hint->Fit("gaus");hint->Draw();
c3->cd(3);hampwf->Fit("gaus");hampwf->Draw();
c3->cd(4);hb->Fit("gaus");hb->Draw();

cout<<"Waveform : "<<TMath::Abs(hampwf->GetFunction("gaus")->GetParameter(2)/hampwf->GetFunction("gaus")->GetParameter(1))<<endl;
cout<<"Integral : "<<TMath::Abs( hint->GetFunction("gaus")->GetParameter(2)/hint->GetFunction("gaus")->GetParameter(1))<<endl;
cout<<"Amplitude : "<<TMath::Abs(hamp->GetFunction("gaus")->GetParameter(2)/hamp->GetFunction("gaus")->GetParameter(1))<<endl;

ofstream fout2("refshapelednew.txt");
for(Int_t i=0;i<128;i++){
  fout2<< ( (TDoubleArray*) (wt->GetRefShapesLED()->UncheckedAt(0)))->GetValue(i)<<endl;
}

TCanvas* canv = new TCanvas();
TDoubleArray* newarray = new TDoubleArray();
TDoubleArray* oldarray = new TDoubleArray();
for(Int_t i=0;i<128;i++){
  oldarray->SetValue(i,prof[0]->GetBinContent(i+1));
  newarray->SetValue(i,-((TDoubleArray*)(wt->GetRefShapesLED()->UncheckedAt(0)))->GetValue(i));
}

oldarray->Draw(canv);
oldarray->GetHisto()->SetLineColor(kRed);
newarray->Draw(canv,-800,100);
oldarray->Draw(canv,-800,100,"same");

}
