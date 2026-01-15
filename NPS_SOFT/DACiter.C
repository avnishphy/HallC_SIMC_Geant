{
TFile *f=new TFile("/adaql5/work1/dvcs_CaloSet_1855.dat.0.root");
TTree *tree = (TTree*)f->Get("T");
TARSWave* wt=new TARSWave();
TARSWave* wave=new TARSWave();

TCaloEvent *caloev;
TBranch *branchcalo=tree->GetBranch("event_calo.");
branchcalo->SetAddress(&caloev);

Int_t nevent=tree->GetEntries();
cout<<"Number of events: "<<nevent<<endl;
TCanvas *canwave = new TCanvas();
TCanvas *can1 = new TCanvas();
TCanvas *canscat = new TCanvas;

TProfile *dacprofile;
TH1D *dachisto;
dacprofile=new TProfile("Channel profile","Channel profile",132,0,132,1800,2000,"s");
dachisto=new TH1D("Value histo","Value histo",200,1800,2000);
Int_t* daclist = new Int_t[132];

Int_t cmpt = 0;
double mean = 0;
Double_t target = 0;

for(Int_t i=1000; i<nevent-100; i++) {
  tree->GetEntry(i);
  cmpt++;
  if (cmpt > 800) {
    printf("\n%5d: mean=%3f\n", i, mean);
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
    daclist[j] = wave->GetDAC();
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

ofstream dacofile("DACiter.txt");
FILE* dacifile;
dacifile = fopen("DAC.txt","r");

float a, b, error;
int maxsetting=255, setting, level;

for(Int_t i=0;i<nb;i++) {
  dachisto->Fill(dacprofile->GetBinContent(i+1));
  target += dacprofile->GetBinContent(i+1);
}
target /= nb;
target = (int) (target + 0.5);
cout << "Target value: " << target << endl;

Int_t diff, dac, newdac, channel;
for(Int_t i=0;i<nb;i++) {

  fscanf(dacifile,"%d %f %f %d\n", &channel, &a, &b, &dac);

  diff = dacprofile->GetBinContent(i+1) - target;
  if (diff > 8) {
    newdac = daclist[i]-1;
    cout << "Adjusting channel " << i << " - difference= " << diff <<endl;
    cout << "Current DAC: " << daclist[i] << endl;
    cout << "New DAC: " << newdac << endl;
    dacofile << i << " " << a << " " << b << " " << newdac << endl; 
  }
  else if (diff < -8) {
    newdac = daclist[i]+1;
    cout << "Adjusting channel " << i << " - difference= " << diff <<endl;
    cout << "Current DAC: " << daclist[i] << endl;
    cout << "New DAC: " << newdac << endl;
    dacofile << i << " " << a << " " << b << " " << newdac << endl; 
  }
  else {
    dacofile << i << " " << a << " " << b << " " << dac << endl; 
  }
}
canscat->cd();
dachisto->Draw();
}
