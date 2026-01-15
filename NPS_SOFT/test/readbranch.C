/////////////////////////////////////////////////////////
// 
// This macro shows how to read only a branch of a tree
//
/////////////////////////////////////////////////////////

// #include "TCaloEvent.h"
// #include "TObjectTable.h"
// #include "TTree.h"
// #include "TBranch.h"
// #include "TProcessID.h"

// void read()
{
  TFile *f=new TFile("initdata/newled3490.dat.root");
  TTree *tree = (TTree*)f->Get("fTree");
  TARSWave* wt=new TARSWave();
  wt->SetPedestalProfileFile("initdata/prof-09-03-03.root");
  
  TCaloEvent *caloev=0;
  TBranch *branchcalo=tree->GetBranch("event_calo.");
  //We need to set the address of the branch holding the whole event
  branchcalo->SetAddress(&caloev);
  //We declare the branch we are going to read
  TBranch *branchtrig=tree->GetBranch("event_calo.fCaloTrigger");
  Int_t nevent=tree->GetEntries();
  nevent=15000;
 
  for(Int_t i=2;i<nevent;i++) {//We start at event number 2 because the first
                               //two events contain no trigger
    Int_t ObjectNumber=TProcessID::GetObjectCount();
    if(i%100) cout<<i<<"/"<<nevent<<endl;
    
    branchtrig->GetEntry(i);//We read only this branch!!
                            //The info can be found in the event :
    if(caloev->GetCaloTrigger()) 
      cout<<caloev->GetCaloTrigger()->GetADCValue(0)<<endl;
    caloev->Reset();//We reset the event as usual (not clear!)
    TProcessID::SetObjectCount(ObjectNumber);
  }
}
