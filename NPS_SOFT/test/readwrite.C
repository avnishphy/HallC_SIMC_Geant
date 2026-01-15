{
//////////////////////////////////////////////////////////////////////////
//
// This macro shows how to read a tree and write another one _at the same
// time_. LED ARSWaves are read from a raw tree. They are analyzed and 
// the analyzed wave is written to a different tree.
//
// Carlos Munoz (26 Dec 2003)
//
//////////////////////////////////////////////////////////////////////////

//Pedestals
TARSWave* wt=new TARSWave();
wt->SetPedestalProfileFile("initdata/prof-09-03-03.root");

//This is the tree to read  
TFile *f=new TFile("initdata/trigcol0_1132.dat.root");
TTree *tree = (TTree*)f->Get("fTree");
TCaloEvent *caloevread;
TBranch *branchcalo=tree->GetBranch("event_calo.");
branchcalo->SetAddress(&caloevread);
Int_t nevent=tree->GetEntries();

//This is the tree to write
TCaloEvent *caloevwrite=new TCaloEvent();
TFile tf("treew.root","RECREATE");
TTree t("treew","My tree");
t.Branch("event_calo2.","TCaloEvent",&caloevwrite,16000,2);
///

TCanvas *can=new TCanvas();

for(Int_t i=5000;i<nevent;i++) {
  Int_t ObjectNumber=TProcessID::GetObjectCount();
  tree->GetEntry(i);
  if(i%100==0) cout<<i<<endl;
  if(caloevread->GetNbBlocks()>0){
    TARSWave* waveread=caloevread->GetWave(0);
    //TARSWave* wavewrite=caloevwrite->AddWave(waveread);
    waveread->SetNbChannel(0);
    waveread->SubstractPedestal(0);
    waveread->Analyze("LED");
    cout<<"chi2 "<<waveread->GetChi2()<<endl;

    //We add the analyzed wave to the event to write
    TARSWave* wavewrite=caloevwrite->AddWave(waveread);
    //We could have added it just after reading waveread and then analyze
    //wavewrite.

   //Visualization
    cout<<"Arrival time : "<<waveread->GetArrivalTime1()<<endl;
    waveread->GetFit("LED")->Draw(can);
    waveread->DrawSignal(can,"same");
    waveread->GetFit("LED")->GetHisto()->SetLineColor(kRed);
    waveread->GetFit("LED")->GetHisto()->SetDrawOption("same");

  }
  t.Fill();
  caloevwrite->Clear();//We clear the write event
  caloevread->Reset();//We reset the read event
  TProcessID::SetObjectCount(ObjectNumber);
}
tf.Write();
//tf.Close();
}
