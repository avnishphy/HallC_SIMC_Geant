{
////////////////////////////////////////////////////////////////////////
// 
// This macro shows how to read the tree created by readwrite.C
//
// C Munoz (26 Dec 2003)
//
///////////////////////////////////////////////////////////////////////

TCaloEvent *caloevread;
TFile *f=new TFile("treew.root");
TTree *tree = (TTree*)f->Get("treew");
TBranch *branchcalo=tree->GetBranch("event_calo2.");
branchcalo->SetAddress(&caloevread);
Int_t nevent=tree->GetEntries();

for(Int_t i=0;i<nevent;i++) {
  Int_t ObjectNumber=TProcessID::GetObjectCount();
  tree->GetEntry(i);
  cout<<i<<endl;
  if(caloevread->GetNbWaves()>0 )//&& i%100==0)
    cout<<caloevread->GetWave(0)->GetChi2()<<endl;
  caloevread->Reset();//We do reset here and not clear !!
  TProcessID::SetObjectCount(ObjectNumber);
}
}
