//////////////////////
//
// Analysis of a DVCS pedestal run (calo+PA+veto)
// Fills MySQL database with new values.
//                            Carlos (8 Oct 2004)
//
//////////////////////

Int_t pedestals(Int_t run)
{
gSystem->Load("libDVCS.so");
TChain *tree=new TChain("T");
TString location("/adaql3/work1/adaq/onlroot/dvcs_");location+=run;location+=".root";
tree->Add(location.Data());
TCaloEvent *caloev;
TPAEvent *paev;
TVEvent *vetoev;

TProfile *calo[132],*pa[100],*veto[57];

//TFile *f=new TFile("pedestals.root","RECREATE");

for(Int_t i=0;i<132;i++){
  TString name("calo");name+=i;
  calo[i]=new TProfile(name.Data(),name.Data(),128,0,128,"s");
}
TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,"munoz","");
for(Int_t i=0;i<100;i++){
  TString query("select trig from PA_Trig_Cabling where block=");
  query+=i;
  TSQLResult *res=db->GetServer()->Query(query.Data());
  TSQLRow* row=res->Next();
  Int_t k=atoi(row->GetField(0));
  TString name("pa");name+=k;
  TString name2("pa2_");name2+=k;
  pa[i]=new TProfile(name.Data(),name.Data(),128,0,128,"s");
}
for(Int_t i=0;i<57;i++){
  TString name("veto");name+=i;
  veto[i]=new TProfile(name.Data(),name.Data(),128,0,128,"s");
}

tree->SetBranchAddress("event_calo.",&caloev);
tree->SetBranchAddress("event_veto.",&vetoev);
tree->SetBranchAddress("event_pa.",&paev);
Int_t nev=tree->GetEntries();
//nev=400;

for(Int_t i=0;i<nev;i++){
  //  i+=10;
  if(i%1000==0) cout<<i<<"/"<<nev<<endl;
  tree->GetEntry(i);

  Int_t nb=caloev->GetNbBlocks();
  for(Int_t j=0;j<nb;j++){
    TCaloBlock *block=caloev->GetBlock(j);
    TARSWave *wave=caloev->GetWave(j);
    for(Int_t k=0;k<128;k++) calo[block->GetBlockNumber()]->Fill(k,wave->GetArray()->GetValue(k));
  }
  nb=paev->GetNbBlocks();
  for(Int_t j=0;j<nb;j++){
    TPABlock *blockpa=(TPABlock*)paev->GetPABlocks()->UncheckedAt(j);
    TARSWave *wave=paev->GetWave(j);
    for(Int_t k=0;k<128;k++) pa[blockpa->GetBlockNumber()]->Fill(k,wave->GetArray()->GetValue(k));
  }
  nb=vetoev->GetNbBlocks();
  for(Int_t j=0;j<nb;j++){
    TVBlock *blockv=(TVBlock*)vetoev->GeTVBlocks()->UncheckedAt(j);
    TARSWave *wave=vetoev->GetWave(j);
    for(Int_t k=0;k<128;k++) veto[blockv->GetBlockNumber()]->Fill(k,wave->GetArray()->GetValue(k));
  }
  caloev->Reset();
  paev->Reset();
  vetoev->Reset();
}
//f->Write();
 cout<<endl<<endl<<nev<<" events processed."<<endl<<endl; 
 cout<<"Filling database with pedestals..."<<endl;

TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,"munoz","");
Float_t *pedcalo[132],*pedpa[100],*pedveto[57];
for(Int_t i=0;i<132;i+){
  pedcalo[i]=new Float_t[128];
  for(Int_t j=0;j<128;j++) pedcalo[i][j]=calo[i]->GetBinContent(j+1);
  TString name("CALO_calib_ARSPed");name+=i;
  db->AddEntry_f(name.Data(),run,999999,pedcalo[i],"Automatic entry of pedestals");
}
for(Int_t i=0;i<100;i+){
  pedpa[i]=new Float_t[128];
  for(Int_t j=0;j<128;j++) pedpa[i][j]=pa[i]->GetBinContent(j+1);
  TString name("PA_calib_ARSPed");name+=i;
  db->AddEntry_f(name.Data(),run,999999,pedpa[i],"Automatic entry of pedestals");
}
for(Int_t i=0;i<57;i+){
  pedveto[i]=new Float_t[128];
  for(Int_t j=0;j<128;j++) pedveto[i][j]=veto[i]->GetBinContent(j+1);
  TString name("VETO_calib_ARSPed");name+=i;
  db->AddEntry_f(name.Data(),run,999999,pedveto[i],"Automatic entry of pedestals");
}
 cout<<"Analysis succesfully completed! Congratulations."<<endl;
return nev;
}
