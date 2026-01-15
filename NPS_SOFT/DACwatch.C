{
TFile *f=new TFile("/adaql5/work1/dvcs_CaloSet_1849.dat.0.root");
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

TProfile *dacprofile;
TH1D *dachisto;
dacprofile=new TProfile("Channel profile","Channel profile",132,0,131,1800,2000,"s");
dachisto=new TH1D("Value histo","Value histo",200,1800,2000);

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
    dacprofile->Draw();
    can1->Modified();
    can1->Update();
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
      dacprofile->Fill(j,mean);
  }
  caloev->Reset();
  TProcessID::SetObjectCount(ObjectNumber);
  }

ofstream dacfile("DAC.txt");
double a, b, error;
int maxsetting=255, setting, level;

TF1* fit;

for(Int_t i=0;i<132;i++) {
  dachisto->Fill(dacprofile->GetBinContent(i));
}

canscat->cd();
dachisto->Draw();
}
