////////////////////////////////////////////////////////////////////////////
//
// This macro shows how to analyze a pedestal run. It reads information 
// from a raw data tree and computes the pedestal for each sample of each
// ARS as well as its dispersion sigma.
// If access to a database is provided, it writes theses values to the
// database.
//
// C Munoz (26 Dec 2003)
//
////////////////////////////////////////////////////////////////////////////

// #include "TTree.h"
// #include "TFile.h"
// #include "TClassTable.h"
// #include "TDVCSEvent.h"
// #include "TDVCSEventMC.h"
// #include "TCaloEvent.h"
// #include "TObjectTable.h"
// #include "TCanvas.h"
// #include "TH1.h"
// #include "TF1.h"
// #include "TGraph.h"
// #include "TRandom.h"
// #include <iostream.h>
// #include "TSQLServer.h"
// #include "TSQLResult.h"

// #ifndef ROOT_TProcessID
// #include "TProcessID.h"
// #endif

// void tree()
{ 
 //////////////////////////////////////////////////////
 TFile *f=new TFile("initdata/cosmpad3548.dat.root");
 Int_t run=3548;
 TString username="munoz";
 /////////////////////////////////////////////////////

 TH2D *ped[132];
 TH1D *hsigma[132];
 TTree *tree = (TTree*)f->Get("fTree");
 TCaloEvent *caloev;
 TBranch *branchcalo=tree->GetBranch("event_calo.");
 branchcalo->SetAddress(&caloev);
 ofstream out("sigma.txt");
 ofstream pedes("pedestal.txt");
 ofstream *fout[132];
 TString *filename[132];
 ofstream *foutsigma[132];
 TString *filenamesigma[132];
 for(Int_t i=0;i<132;i++){
   filename[i]=new TString("pedfile");
   (*filename[i])+=i;
   fout[i]=new ofstream(filename[i]->Data());
   filenamesigma[i]=new TString("pedfilesigma");
   (*filenamesigma[i])+=i;
   foutsigma[i]=new ofstream(filenamesigma[i]->Data());
 }

 Double_t *sigmab=new Double_t[132];
 Double_t *sigmabdis=new Double_t[132];
 Double_t *cp=new Double_t[132];
 Int_t nevent=tree->GetEntries();
 cout<<nevent<<endl;

 Int_t max[132],min[132];
 for(Int_t i=0;i<132;i++){
   max[i]=-1;
   min[i]=3000;
 }
 for(Int_t i=100;i<100+nevent;i++) {
   if(i%1000==0) {
     gObjectTable->Print();
   }
   Int_t ObjectNumber=TProcessID::GetObjectCount();

   if(i%1000==0) cout<<i<<endl;
   //branch->GetEntry(i);
   tree->GetEntry(i-1);
   for(Int_t j=0;j<132;j++){
     TARSWave* t=caloev->GetWave(j);
     for(Int_t k=0;k<128;k++){
       TDoubleArray *ar=t->GetArray();
       Double_t val=ar->GetValue(k);
       if(val<min[j]) min[j]=val;
       if(val>max[j]) max[j]=val;
     }
   }
   caloev->Reset();//We do reset here and not clear !!
   TProcessID::SetObjectCount(ObjectNumber);
 }
 
 cout<<"calcul min et max finished"<<endl;
 Double_t sigmin=2.5,sigmax=5.0;
 TH1D *hproj[132];

 for(Int_t i=0;i<132;i++){
   TString name("Channel"); name+=i;
   TString name2("Sigma");name2+=i;
   ped[i]=new TH2D(name.Data(),name.Data(),128,0,128,max[i]-min[i]+2,min[i]-1,max[i]+1);
   hsigma[i]=new TH1D(name2.Data(),name2.Data(),40,sigmin,sigmax);
 }
 
 for(Int_t i=100;i<100+nevent;i++) {
   if(i%1000==0) {
     gObjectTable->Print();
   }
   
   Int_t ObjectNumber=TProcessID::GetObjectCount();
   
   if(i%1000==0) cout<<i<<endl;
   tree->GetEntry(i);
   for(Int_t j=0;j<132;j++){
     TARSWave* t=caloev->GetWave(j);
     for(Int_t k=0;k<128;k++){
       TDoubleArray *ar=t->GetArray();
       Double_t val=ar->GetValue(k);
       ped[j]->Fill(k,val);
     }
   }
   caloev->Reset();//We do reset here and not clear !!
   TProcessID::SetObjectCount(ObjectNumber);
 }
 
 for(Int_t i=0;i<132;i++){
   ped[i]->FitSlicesY();
   TString name("proj");name+=i;
   Int_t bin=Int_t(128.*gRandom->Rndm())+1;
   TString title("Profile sample ");title+=bin-1;title+="  block ";title+=i;
   hproj[i]=ped[i]->ProjectionY(name.Data(),bin,bin);
   hproj[i]->SetTitle(title.Data());
   cout<<i<<endl;
 }

 
 TCanvas *csigma[11];
 TCanvas *cmean[11];
 TCanvas *cssigma[11];
 TCanvas *cproj[11];
 for(Int_t i=0;i<11;i++){
   csigma[i]=new TCanvas();
   csigma[i]->Divide(4,3);
   cmean[i]=new TCanvas();
   cmean[i]->Divide(4,3);
   cssigma[i]=new TCanvas();
   cssigma[i]->Divide(4,3);
   cproj[i]=new TCanvas();
   cproj[i]->Divide(4,3);
  }

 // Double_t sigmab[132],sigmabdis[132],cp[132];
    TF1 *f1 = new TF1("f1","gaus",sigmin,sigmax);
 for(Int_t i=0;i<132;i++){
   TString name("Channel");name+=i;name+="_1";
   cmean[i/12]->cd(i%12+1);
   TH1D* h=(TH1D*)gDirectory->Get(name.Data());
   h->SetMinimum(min[i]);
   TString title("Mean Block ");title+=i;
   h->SetTitle(title.Data());
   h->Draw();
   name=("Channel");name+=i;name+="_2";
   csigma[i/12]->cd(i%12+1);
   TH1D* h2=(TH1D*)gDirectory->Get(name.Data());
   TString title2("Sigma Block ");title2+=i;
   h2->SetTitle(title.Data());
   h2->Draw();
   cproj[i/12]->cd(i%12+1);
   hproj[i]->Draw();
   for(Int_t j=0;j<128;j++) {
     hsigma[i]->Fill(h2->GetBinContent(j+1));
     pedes<<h->GetBinContent(j+1)<<endl;
     *(fout[i])<<h->GetBinContent(j+1)<<endl;
     *(foutsigma[i])<<h->GetBinContent(j+1)<<endl;
     out<<h2->GetBinContent(j+1)<<endl;

   }
   cssigma[i/12]->cd(i%12+1);
   TString title3("Sigma distribution block ");title3+=i;
   hsigma[i]->SetTitle(title3.Data());
   hsigma[i]->Fit("f1","R");
   hsigma[i]->Draw();
   sigmab[i]=f1->GetParameter(1);
   sigmabdis[i]=f1->GetParameter(2);
   cp[i]=i;
}

 cmean[0]->Print("mean.ps(");
 csigma[0]->Print("sigma.ps(");
 cssigma[0]->Print("ssigma.ps(");
 cproj[0]->Print("proj.ps(");
 for(Int_t i=1;i<10;i++){
   cmean[i]->Print("mean.ps");
   csigma[i]->Print("sigma.ps");
   cssigma[i]->Print("ssigma.ps");
   cproj[i]->Print("proj.ps");
 }
 cmean[10]->Print("mean.ps)");
 csigma[10]->Print("sigma.ps)");
 cssigma[10]->Print("ssigma.ps)");
 cproj[10]->Print("proj.ps)");

 TCanvas *csigmares=new TCanvas();
 csigmares->Divide(1,2);
 TGraph *gsigma=new TGraph(132,cp,sigmab);
 gsigma->SetTitle("Sigma vs block number");
 gsigma->SetMarkerStyle(20);
 gsigma->SetMarkerSize(0.5);
 TGraph *gsigmadis=new TGraph(132,cp,sigmabdis);
 gsigmadis->SetTitle("Sigma of sigma vs block number");
 gsigmadis->SetMarkerStyle(20);
 gsigmadis->SetMarkerSize(0.5);
 csigmares->cd(1);
 gsigma->Draw("AP");
 csigmares->cd(2);
 gsigmadis->Draw("AP");
 csigmares->Print("res.ps");

 out.close();
 pedes.close();

 TDVCSDB *db=new TDVCSDB("dvcs","127.0.0.1",3306,username.Data());
for(Int_t i=0;i<132;i++){
  TString name("CALO_calib_ARSPed");name+=i;
  TString name2("CALO_calib_ARSSigma");name2+=i;
  db->AddEntry(name.Data(),run,9999999,filename[i]->Data(),"");
  db->AddEntry(name2.Data(),run,9999999,filenamesigma[i]->Data(),"");
}
}




