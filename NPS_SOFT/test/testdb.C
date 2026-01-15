{
//gSystem->Load("libDVCS.so");
gSystem->Load("./libDVCS.so");
gROOT->SetStyle("Plain");
//gdvcs->SetWF(0) //If you don't need waveform analysis

TH1F *h1=new TH1F("h1","Energy resolution",100,-1,1);
TH1F *h2=new TH1F("h2","Energy resolution",100,-1,1);
h2->SetLineColor(kRed);

//Sets WF analysis parameters (not in database yet)
TARSWave *wt=new TARSWave(128);
wt->SetFirstWindow(-10,10,"data");
wt->SetSecondWindow(-10,10,-50,50,"data");
wt->SetChi20(0.1);wt->SetChi21(180);wt->SetChi22(1e10);

TCanvas *can=new TCanvas();
/////////////////////////////////////////////////////
//My DVCS chain//////////////////////////////////////
TDVCSChain *tree=new TDVCSChain("T");
tree->Add("/work/dvcs/carlos/elas/dvcs_*.root");
tree->Add("/work/dvcs/carlos/dvcs_4995_0.root");
tree->Add("/work/dvcs/carlos/dvcs_4996_0.root");
tree->Add("/work/dvcs/carlos/dvcs_4997_0.root");

TDVCSEvent *ev=new TDVCSEvent();
THRS *hrs;tree->SetBranchAddress("event_spectro.",&hrs);
TCaloEvent *caloev;tree->SetBranchAddress("event_calo.",&caloev);
Double_t v;tree->SetBranchAddress("rpl.z",&v);
Int_t nev=tree->GetEntries();
//nev=1000;
Double_t ebeam=5.767;
TLorentzVector pini(0.,0.,0.,0.938272);
TLorentzVector eini(0.,0.,ebeam,ebeam);
for(Int_t i=0;i<nev;i++){
  Int_t ObjectNumber=TProcessID::GetObjectCount();
  if(i%1000==0) cout<<i<<"/"<<nev<<endl;
  tree->GetEntry(i);
  //if(i%100==0) gObjectTable->Print();

  TLorentzVector *proton=hrs->GetParticle();  
  TLorentzVector theovec=(eini+pini-(*proton));
			  
  Int_t nb=caloev->GetNbBlocks();
  for(Int_t j=0;j<nb;j++){
    TCaloBlock *block=caloev->GetBlock(j);
    TARSWave *wave=caloev->GetWave(j);
    wave->SubstractPedestalDB(block->GetBlockNumber(),"CALO");
    wave->SetNbChannel(block->GetBlockNumber(),"CALO");
    wave->Analyze("data");
    //Visualization
//  if(caloev->GetCaloTrigger()->GetADCValue(block->GetBlockNumber())>20){
//  cout<<"Arrival time : "<<wave->GetArrivalTime1()<<endl;
//  cout<<"Amplitude : "<<wave->GetAmplitude1()<<endl;
//  wave->GetFit("data")->Draw(can,-2000,200);
//  wave->DrawSignal(can,"same");
//  wave->GetFit("data")->GetHisto()->SetLineColor(kRed);
//  wave->GetFit("data")->GetHisto()->SetDrawOption("same");
//  cout<<"Chi2="<<wave->GetChi2()<<endl;
//  cout<<"Amp 1 "<<wave->GetAmplitude1()<<"    Time1 "<<wave->GetArrivalTime1()<<endl;
//  if(wave->GetNbPulses()>1) cout<<"Amp 2 "<<wave->GetAmplitude2()<<"    Time2 "<<wave->GetArrivalTime2()<<endl;
//         	}
    //End visualization
    if(wave->GetNbPulses()>0 && wave->GetAmplitude1()>0.){
      if(abs(wave->GetArrivalTime1())<8) 
	block->SetBlockEnergy(wave->GetAmplitude1()*caloev->GetCalibration()->GetCalib(block->GetBlockNumber()));
    }
  }
  ev->SetVertex(0.,0.,v*100.);
  ev->SetCaloEvent(caloev);
  caloev->DoClustering();
  
  if(caloev->GetNbClusters()==1){
    caloev->GetCluster(0)->Analyze();//Force if necessary
    //Here's your photon if you need it! :
    TLorentzVector phot=ev->GetPhoton(0,2.,0);
    //At any moment after the first call to TDVCSChain::GetEntry(int)
    //you can access the current run number of the event
    if(gdvcs->GetRun(tree->GetFile()->GetName())<4995){
      h1->Fill(phot.E()-theovec.E());//First elastic calibration
    }else{
      h2->Fill(phot.E()-theovec.E());//Second elastic calibration
    }
  }
  if(i%1000==0){
    h1->Draw();h2->Draw("same");
    can->Update();
  }
  ev->Reset();//Resets the event
  TProcessID::SetObjectCount(ObjectNumber);
}	  		  
can->Print("res.ps");
}			  
  
			  


			      

      
