{
TPAEvent *paevent=new TPAEvent();
TDVCSEvent *event=new TDVCSEvent();
TPABlock *block=new TPABlock();

block->SetBlockEnergy(0.1);
block->SetBlockNumber(49);
paevent->AddBlock(block);
//paevent->SetNbBlocks(1);
event->SetPAEvent(paevent);
event->SetVertex(0.,0.,0.);

cout<<block->GetBlockEnergy()<<endl;

TLorentzVector proton=event->GetProtonFast();
cout<<"Energy proton : "<<proton.E()<<" Px="<<proton.Px()<<" Py="<<proton.Py()<<" Pz="<<proton.Pz()<<endl;

TVector3 imp=proton.Vect();
Float_t theta=TMath::ASin(-imp(0)/imp.Mag());
Float_t phi=TMath::ASin(imp(1)/imp.Mag());
Float_t radtodeg=180./TMath::Pi();

cout<<"Theta : "<<theta*radtodeg<<"    Phi : "<<phi*radtodeg<<endl;

}
