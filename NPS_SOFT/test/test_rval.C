{
  gSystem->Load("../libDVCS.so");
  TDVCSEvent *ev=new TDVCSEvent();
  
  TFile *f = new TFile("/sps/clas/carlos/DVCS2/rval.root");
  TTree *t1 = (TTree*)f->Get("ntu");
  Int_t nentries = (Int_t)t1->GetEntries();
  
  Float_t y,dp,theta,phi,rval;
  t1->SetBranchAddress("y",&y);
  t1->SetBranchAddress("dp",&dp);
  t1->SetBranchAddress("theta",&theta);
  t1->SetBranchAddress("phi",&phi);
  t1->SetBranchAddress("rval",&rval);
	
  TH1F *diff   = new TH1F("diff","(rval_ntuple - rval_new)",100,-0.00000001,0.00000001);
  
  cout << "N = " << nentries << endl;
  
  for (Int_t i=0;i<nentries;i++) { // trop long si on prend nentries ;-)
	  if(i%100000==0) cout<<i<<"/"<<nentries<<endl;
    t1->GetEntry(i);
    Double_t val=rval - ev->rfunction(y,dp,theta,phi);
    if(val>0.00000001||val<-0.00000001) cout<<" ===== > "<<val<<" "<<rval<<" "<<rval-val<<endl;
    diff->Fill(rval - ev->rfunction(y,dp,theta,phi));
  }
  
  diff->Draw();
  
}
