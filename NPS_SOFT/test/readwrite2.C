{
//////////////////////////////////////////////////////////////////////////
//
// This macro shows how to read a tree and write another one _at the same
// time_ using the same event in reading and writing. LED ARSWaves are 
// read from a raw tree. They are analyzed and the analyzed wave is 
// written to a different tree.
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
TCaloEvent *caloev=new TCaloEvent();
TBranch *branchcalo=tree->GetBranch("event_calo.");
branchcalo->SetAddress(&caloev);
Int_t nevent=tree->GetEntries();

//This is the tree to write
TFile tf("treew.root","RECREATE");
TTree t("treew","My tree");
t.Branch("event_calo2.","TCaloEvent",&caloev,16000,2); //We write
//the same event to a different tree
///

TCanvas *can=new TCanvas();

for(Int_t i=5000;i<nevent;i++) {
  Int_t ObjectNumber=TProcessID::GetObjectCount();
  tree->GetEntry(i);
  if(i%100==0) cout<<i<<endl;
  if(caloev->GetNbBlocks()>0){
    TARSWave* wave=caloev->GetWave(0);
    wave->SetNbChannel(0);
    wave->SubstractPedestal(0);
    wave->Analyze("LED");
//     cout<<"chi2 "<<wave->GetChi2()<<endl;

   //Visualization
//     cout<<"Arrival time : "<<wave->GetArrivalTime1()<<endl;
//     wave->GetFit("LED")->Draw(can);
//     wave->DrawSignal(can,"same");
//     wave->GetFit("LED")->GetHisto()->SetLineColor(kRed);
//     wave->GetFit("LED")->GetHisto()->SetDrawOption("same");

  }
  t.Fill();
  caloev->Reset();//We reset the event
  TProcessID::SetObjectCount(ObjectNumber);
}
tf.Write();
//tf.Close();
}
