{
  gSystem->Load("/afs/in2p3.fr/home/throng/clas/alex/soft/soft-2/libDVCS.so");
  gdvcs->SetWF(0);gdvcs->SetRun(7000);gdvcs->ForceUpdate();

  TFile *fout=new TFile("sim.root","recreate");
  TTree *tree=new TTree("T","DVCS tree");
  TCaloEvent *caloev=new TCaloEvent();

  TDVCSEvent *ev=new TDVCSEvent();
  cout<<"Caloriemeter angle (deg): "<<ev->GetGeometry()->GetCaloTheta()*TMath::RadToDeg()<<endl;
  cout<<"Calorimter distance (cm): "<<ev->GetGeometry()->GetCaloDist()<<endl;
  cout<<"Calorimter X offset (cm): "<<caloev->GetGeometry()->GetCenterXPos()<<endl;
  cout<<"Calorimter Y offset (cm): "<<caloev->GetGeometry()->GetCenterYPos()<<endl;
  cout<<"Calo block position (cm): "<<caloev->GetGeometry()->GetBlockXPos(5)<<endl;
  
  tree->Branch("event_calo.","TCaloEvent",&caloev,32000,2);
  
  Int_t nev=10;//Number of events
  for(Int_t i=0;i<nev;i++){//Event loop
    Int_t ObjectNumber=TProcessID::GetObjectCount();
    
    for(Int_t j=0;j<208;j++){//Calorimeter block loop
      TCaloBlock *block=caloev->AddBlock(j);// j is block number
      block->SetBlockEnergy(3.*gRandom->Rndm());
    }
    ev->SetVertex(0.,0.,-7+14*gRandom->Rndm());// (Random) vertex
    caloev->TriggerSim(1.);//Energy threshold at 1 GeV
    caloev->DoClustering(); //Clustering
    Int_t nclus=caloev->GetNbClusters();
    for(Int_t k=0;k<nclus;k++){//Clusters loop
      caloev->GetCluster(k)->Analyze();
      //      caloev->GetCluster(k)->Print();
      TLorentzVector photon=ev->GetPhoton(k,7.,0.);
      //cout<<"photon "<<k<<" : "<<photon.Px()<<" "<<photon.Py()<<" "<<photon.Pz()<<" "<<photon.E()<<endl;
    }
    tree->Fill();
    caloev->Reset(); 
    TProcessID::SetObjectCount(ObjectNumber);
   }
  tree->Write();
}
