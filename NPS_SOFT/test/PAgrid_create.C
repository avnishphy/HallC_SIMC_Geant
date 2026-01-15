/////////////////////////////////////////////////////////////////////
//
// This generates the PA block list which match the photon kinematics
// It generates 9 different text files as a function of the neglected
// blocks.
// The results can be analyzed with PAgrid_ana.C.
//
/////////////////////////////////////////////////////////////////////

#include "TH2.h"
#include "TLorentzVector.h"
#include "TH1.h"
#include "THPA.h"
#include "TVector3.h"
#include "TCanvas.h"
#include <iostream.h>
#include "TARSWave.h"
#include "TCaloEvent.h"
#include "TPAEvent.h"
#include "TCaloTrigger.h"
#include "TDVCSEvent.h"
#include "TDVCSEventMC.h"
#include "TProcessID.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TObjectTable.h"

void ana()
{

Int_t blockcount;
TH1F *hper=new TH1F("hper","hper",100,0,40);
 TH1F *hBlockNb = new TH1F("BlockNb","BlockNb",15,0,15);
TH2F *htour[110];
THPA *hPA[110];
for(Int_t i=0;i<110;i++){
  TString name("hpa");
  name+=i;
  htour[i]=new TH2F(name.Data(),name.Data(),20,0,20,5,0,5);
  hPA[i]=new THPA();
}
Int_t Ttab[110][20][5];
for(Int_t hi=0;hi<110;hi++){
  for(Int_t ix=0;ix<20;ix++){
    for(Int_t iy=0;iy<5;iy++){
      Ttab[hi][ix][iy]=-1;
    }
  }
}
Int_t norm[110];
Int_t realnorm[110];
for(Int_t i=0;i<110;i++) {norm[i]=0;realnorm[i]=0;}

TH1F *hproton=new TH1F("hproton","hproton",100,-180,180);

ifstream fin("liste.txt");
Bool_t toread[110][100];
for(Int_t i=0;i<110;i++){
  Int_t tower;
  fin>>tower;
  for(Int_t j=0;j<100;j++){
    Bool_t tmp;
    fin>>tmp;
    toread[tower][j]=tmp;
  }
}

Int_t nev,nb,nbx,nby,blocknb;
Float_t x1,x2,x3,energy;

TVector3* electron=new TVector3(0.,0.,0.);
TVector3* photon=new TVector3(0.,0.,0.);
TVector3* proton=new TVector3(0.,0.,0.);
TLorentzVector elrec(0.,0.,0.,0.);
TCaloEvent *caloev=new TCaloEvent();
TPAEvent *paev=new TPAEvent();
TDVCSEventMC *mcevent=new TDVCSEventMC();
TDVCSEvent *event=new TDVCSEvent();
TCaloTrigger *trigger=new TCaloTrigger();
TVector3 *vvertex=new TVector3();
TLorentzVector *eelectron=new TLorentzVector();
TARSWave* wave=new TARSWave();

ifstream f("initdata/output.txt");
f>>x1;
f>>nev;
TRandom2 ran2(4325);
nev=10000;
TRandom ran(543);
  
for(Int_t i=0;i<6;i++) f>>x1;

TCaloCluster *caloclus=0;
TCaloCluster *clustest=new TCaloCluster(); 

for(Int_t j=0;j<nev;j++){               //for1
  blockcount=0;
  if(j%100==0) cout<<j<<" "<<TProcessID::GetObjectCount()<<endl;
  Int_t ObjectNumber=TProcessID::GetObjectCount();
  if(j%1000==0) {
    gObjectTable->Print();
  }
  for(Int_t i=0;i<132;i++) trigger->SetADCValue(i,1000.);
  f>>nb;
  for(Int_t i=0;i<nb;i++){             // for2
    blocknb=0;
    energy=0.;
    f>>blocknb;
    f>>energy;
    TCaloBlock* block=caloev->AddBlock(blocknb);
    block->SetBlockEnergy(energy);
    trigger->SetADCValue(blocknb,energy*1000.);
  }                                // end for2
  
  caloev->SetCaloTrigger(trigger);
  caloev->TriggerSimulation(0,128,.5,kTRUE);
  caloev->DoClustering(0.);
  event->SetCaloEvent(caloev);
  f>>nb;
  for(Int_t i=0;i<nb;i++){//for3
    blocknb=0;
    energy=0.;
    f>>nby;
    f>>nbx;
    f>>energy;
    for(Int_t hi=0;hi<110;hi++){   //for4
      if((caloev->GetCaloTrigger()->GetTowerBit(hi))==1 && energy>0.02){ 
	if(toread[hi][(nbx-1)*5+nby-1])
	  realnorm[hi]++;
	htour[hi]->Fill(nbx-1,nby-1);
	if(Ttab[hi][nbx-1][nby-1]=-1){
	  Ttab[hi][nbx-1][nby-1]=1;
	}
      }
    }                              //end for4
    if(energy>.05)   blockcount++;
    Int_t xx=paev->GetGeometry()->GetNX();
    Int_t bn=(nby-1)*xx+nbx-1;//This is the block number out of the MC block and cell number
    TPABlock* blockpa=paev->AddBlock();
    blockpa->SetBlockNumber(bn);
    blockpa->SetBlockEnergy(energy);
     }                              // end for3
  for(Int_t hi=0;hi<110;hi++){   //for4
    if((caloev->GetCaloTrigger()->GetTowerBit(hi))==1 && paev->GetEnergy()>0.02) {
      norm[hi]++;
    }
  }


  hBlockNb->Fill(blockcount);
  f>>x1 ; f>>x2 ; f>>x3 ;
  electron->SetXYZ(x1,x2,x3);
  mcevent->AddElectron(electron);
  f>>x1 ; f>>x2 ; f>>x3 ;
  photon->SetXYZ(x1,x2,x3);
  mcevent->AddPhoton(photon);
  
  f>>x1 ; f>>x2 ; f>>x3 ;
  proton->SetXYZ(x1,x2,x3);
  mcevent->AddProton(proton);
  TLorentzVector *mcproton=mcevent->GetProton();
  mcproton->RotateY(0.258527011);
  if(paev->GetEnergy()>0.05 && caloev->GetNbBlocks()>0) hproton->Fill(180.*mcproton->Phi()/TMath::Pi());
  
  f>>x1;
  mcevent->SetVertex(0.,0.,x1);
  
  event->SetPAEvent(paev);
  
  f>>x1;
  mcevent->SetSigmaP(x1);
  f>>x1;
  mcevent->SetSigmaM(x1);
  f>>x1;
  mcevent->SetPSF(x1);
  f>>x1; //Smeared electron
  f>>x2;
  f>>x3;
  elrec.SetPxPyPzE(x1,x2,x3,TMath::Sqrt(TMath::Power(x1,2.)+TMath::Power(x2,2.)+TMath::Power(x3,2.)));
  event->SetElectron(elrec);
  
  f>>x1;
  event->SetVertex(0.,0.,x1);
  vvertex=&(event->GetVertex());
  eelectron->SetPxPyPzE(elrec.Px(),elrec.Py(),elrec.Pz(),elrec.E());
  event->Clear();
  mcevent->Clear();
  //caloev->Reset();
  TProcessID::SetObjectCount(ObjectNumber);
  
}                                     //end for1
Float_t max=0;
for(Int_t i=0;i<110;i++){
  Float_t maxtmp=htour[i]->GetMaximum();
  if(maxtmp>max) max=maxtmp;
}

 ofstream *fout[10];
 TString *filename[10];
 for(Int_t i=0;i<10;i++){
   filename[i]=new TString("liste");
   (*filename[i])+=i;
   fout[i]=new ofstream(filename[i]->Data());
 }

 //ofstream fout("liste.txt");
Int_t lowblock[110];
 Int_t combien[10]; 
 for(Int_t cp=0;cp<10;cp++)   combien[cp]=0;


gStyle->SetPadBorderMode(0);
TCanvas *c=new TCanvas();
gPad->Print("canvas.ps[");
c->Divide(10,11,0,0);
for(Int_t i=0;i<110;i++){
  lowblock[10-i/10+11*(i%10)]=0;
  //  TCanvas *d=new TCanvas();
  c->cd(i+1);
  for(Int_t cp=0;cp<10;cp++) {
    (*fout[cp])<<10-i/10+11*(i%10)<<" ";
//     combien[cp]=0;
  }
  //for(Int_t j=0;j<20;j++){
    for(Int_t k=0;k<5;k++){
      for(Int_t j=0;j<20;j++){
      Int_t val=htour[10-i/10+11*(i%10)]->GetBinContent(j+1,k+1);
      hPA[10-i/10+11*(i%10)]->SetBinContent(j+1,k+1,val);
      if(val>0 && val<0.5*norm[10-i/10+11*(i%10)]) lowblock[10-i/10+11*(i%10)]++;
      if(val>0) hper->Fill(100.*Double_t(val)/Double_t(norm[10-i/10+11*(i%10)]));
      Bool_t value[10];
      for(Int_t cp=0;cp<10;cp++){
	if(100.*Double_t(val)/Double_t(norm[10-i/10+11*(i%10)])>(Double_t(cp))){
	  value[cp]=kTRUE;
	  combien[cp]++;
	}else{
	  value[cp]=kFALSE;
	}
      
      (*fout[cp])<<value[cp]<<" ";
      } 
   }
  }
  for(Int_t cp=0;cp<10;cp++) (*fout[cp])<<endl;
  
  gPad->SetTopMargin(0);
  gPad->SetBottomMargin(0);
  gPad->SetLeftMargin(0);
  gPad->SetRightMargin(0);
  hPA[10-i/10+11*(i%10)]->SetPad((TPad*)gPad);
  hPA[10-i/10+11*(i%10)]->SetMaximum(max/1000.);
  hPA[10-i/10+11*(i%10)]->SetPad((TPad*)gPad);
 

  //-----> hPA[10-i/10+11*(i%10)]->Draw();


  //  d->cd();
  hPA[10-i/10+11*(i%10)]->SetPad((TPad*)gPad);
//   hPA[10-i/10+11*(i%10)]->Draw();
//   d->Print("canvas.ps");
//   delete d;
}
c->Print("canvas.ps");
c->Print("canvas.ps]");
/*  // List des blocks et des tours
    
ofstream fout("ListBlock.txt");
fout << "average nb of hit blocks : " << Nmoy/nev << endl;
fout << "Calo Tower    PA Block" << endl; 

for(Int_t hi=0;hi<110;hi++){
for(Int_t ix=0;ix<20;ix++){
for(Int_t iy=0;iy<5;iy++){
if(Ttab[hi][ix][iy]!=-1){ 
fout <<hi << "             " << ix+1 << "     " << iy+1 << endl;
}
}
}
}
*/


  cout<<"COMBIEN" <<endl;
  for(Int_t i=0;i<10;i++){
    cout<<i<<" "<<Double_t(combien[i])/110.<<endl;
  }


 cout<<"TEST"<<endl;

ofstream fres("res2.txt");
ofstream ftot("tot.txt");
Int_t xaxis[110];
for(Int_t i=0;i<110;i++) {
  cout<<i<<" "<<norm[i]<<" "<<lowblock[i]<<endl;
  xaxis[i]=i;
  lowblock[i]=100.*Double_t(lowblock[i])/Double_t(norm[i]);
  fres<<realnorm[i]<<endl;
  ftot<<norm[i]<<endl;
}
TGraph *gnorm=new TGraph(110,xaxis,norm);
TGraph *gnormreal=new TGraph(110,xaxis,realnorm);
TGraph *glowblock=new TGraph(110,xaxis,lowblock);

 cout<<"TEST2"<<endl;

TCanvas *r=new TCanvas();
r->Divide(1,3);
r->cd(1);
//gnorm->Draw("A*");
r->cd(2);
//gnormreal->Draw("A*");
r->cd(3);
// glowblock->Draw("A*");
TCanvas *ee=new TCanvas();
hproton->Draw();
TCanvas *eee=new TCanvas();
hper->Draw();

}
