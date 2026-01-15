 {
   TRandom3 *rand = new TRandom3();
   rand->SetSeed(0);
   Int_t run=0;
   Int_t nev=1;
   struct event_dvcs {
     Float_t ene;Float_t qx;Float_t qy;Float_t qz;Float_t v;
   };
   event_dvcs evt;
   TFile *fout=new TFile(Form("./ntu_%d.root",run),"recreate");
   TNtuple *ntu=new TNtuple("ntu","ntu","ene:qx:qy:qz:v");

   TDVCSEvent *ev=new TDVCSEvent();
   TCaloEvent *caloev=new TCaloEvent(run);
  
   for(Int_t i=0;i<nev;i++){//Loop over events
     Int_t ObjectNumber=TProcessID::GetObjectCount();
     TCaloBlock* block;
     block=caloev->AddBlock(558);
     block->AddPulse(5.,0.);//energy and time
     block->AddPulse(5.,4.);//energy (GeV) and time (ns)
  
     block=caloev->AddBlock(559);
     block->AddPulse(2.,0.);//energy and time
     //etc

     for(Int_t j = 0 ; j < 1080 ; j++){
       block=caloev->AddBlock(j);

       block->AddPulse(rand->Gaus(0.01,10),0.);//energy and time
     }
     // caloev->TriggerSim(threshold);// if too many blocks in the event
     caloev->TriggerSim(0.5);// if too many blocks in the event
     caloev->DoClustering(-3.,3.);
     Int_t nb=caloev->GetNbClusters();
    
     for(Int_t j=0;j<nb;j++){
       TCaloCluster *clus=caloev->GetCluster(j);
       clus->Analyze(1,-3.,3.);
       Double_t x=clus->GetX();
       Double_t y=clus->GetY();
       cout<<x<<" "<<y<<endl;
     }
    
     ev->SetCaloEvent(caloev);
     ev->SetVertex(0.,0.,0.*100.);//Assumes cm
     TLorentzVector photon;
     if(nb>0) {
       photon=ev->GetPhoton(0);
       cout<<photon.E()<<" "<<photon.Px()<<" "<<photon.Py()<<" "<<photon.Pz()<<endl;
     }
    
     evt.ene=photon.E();
     evt.qx=photon.Px();
     evt.qy=photon.Py();
     evt.qz=photon.Pz();
     if(nb==1) ntu->Fill(&evt.ene);
     ev->Reset();//Resets the event
     TProcessID::SetObjectCount(ObjectNumber);
   }//Loop over events
   fout->Write();

 }
