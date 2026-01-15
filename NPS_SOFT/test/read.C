{
TFile *f=new TFile("tree.root");
TTree *tree = (TTree*)f->Get("t");
TBranch *branch=tree->GetBranch("bl");
TARSArray *blarray=new TARSArray();
branch->SetAddress(&blarray);
TCanvas *canvas = new TCanvas();
Int_t nevent=tree->GetEntries();

for(Int_t i=0;i<nevent;i++) {
  cout<<"____________________________________"<<endl;
  if(i%1000==0) cout<<i<<endl;
  tree->GetEntry(i);
  blarray->Print("C");
  blarray->GetWave(0)->SubstractPedestal();
  blarray->GetWave(0)->DrawSignal("");
}

}
