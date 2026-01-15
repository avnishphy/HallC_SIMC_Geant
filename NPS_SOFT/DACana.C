{
TFile *f=new TFile("/adaql5/work1/dvcs_CaloSet_1777.dat.0.root");
TTree *tree = (TTree*)f->Get("T");
TARSWave* wt=new TARSWave();
TARSWave* wave=new TARSWave();

TCaloEvent *caloev;
TBranch *branchcalo=tree->GetBranch("event_calo.");
branchcalo->SetAddress(&caloev);

Int_t nevent=tree->GetEntries();
Int_t dac;
cout<<"Number of events: "<<nevent<<endl;
TCanvas *canwave = new TCanvas();
TCanvas *can1 = new TCanvas();
TCanvas *canscat = new TCanvas;

TProfile *dacprofile[132];
TH2D *dachisto[132];
for(Int_t i=0;i<132;i++){
  TString name("Profile");
  TString name2("Histo");
  name+=i;
  name2+=i;
  dacprofile[i]=new TProfile(name.Data(),name.Data(),128,128,255,"s");
  dachisto[i]=new TH2D(name2.Data(),name2.Data(),128,128,255,2000,0,2000);
}

Int_t cmpt = 0;
double mean = 0;
for(Int_t i=1000; i<nevent-100; i++) {
  tree->GetEntry(i);
  cmpt++;
  if (cmpt > 800) {
    printf("\n%5d: mean=%3f, dac=%3d", i, mean, dac);
    //    wave->DrawRaw(canwave);
    //canwave->Modified();
    //canwave->Update();
    can1->cd();
    dacprofile[0]->Draw();
    can1->Modified();
    can1->Update();
    canscat->cd();
    dachisto[0]->Draw();
    canscat->Modified();
    canscat->Update();
    cmpt = 0;
  }
  Int_t ObjectNumber=TProcessID::GetObjectCount();
  
  Int_t nb=caloev->GetNbBlocks();
  for(Int_t j=0;j<nb;j++){
    TCaloBlock *block=caloev->GetBlock(j);
    wave=caloev->GetWave(j);
    //wave->SetNbChannel(0);
    dac = wave->GetDAC();
    TDoubleArray* values = wave->GetArray();
    mean = 0;
    Int_t k=64;
      //for(Int_t k=0; k<128; k++) {
      mean += values->GetValue(k);
    //}
    //mean /= (double) 128;
      if (mean > 200) {
	dacprofile[j]->Fill(dac,mean);
	dachisto[j]->Fill(dac,mean);
      }
  }
  caloev->Reset();
  TProcessID::SetObjectCount(ObjectNumber);
  }

ofstream dacfile("DAC.txt");
float a, b, error;
int maxsetting=255, setting, level;

TF1* fit;

for(Int_t i=0;i<132;i++){
  dacprofile[i]->Fit("pol1");
  fit = dacprofile[i]->GetFunction("pol1");
  a = fit->GetParameter(1);
  b = fit->GetParameter(0);

  setting = (2000 - b)/a + 0.5;
  if (maxsetting < setting) {
    maxsetting=setting;
    level= 255*a + b;
  }
}

  cout << "Maximum level: " << level << endl;

for(Int_t i=0;i<132;i++){
  fit = dacprofile[i]->GetFunction("pol1");
  a = fit->GetParameter(1);
  b = fit->GetParameter(0);
  setting = (level - b)/a + 0.5;
  dacfile << i << " " << a << " " << b << " " << setting << endl; 

  error = abs((a*dac +b) - (dacprofile[i]->GetBinContent(dac-127)));
  if ( error > 10)
    cout << "Questionable linerarity on channel " << i << endl << "Error is " << error << endl;
  
}
}
