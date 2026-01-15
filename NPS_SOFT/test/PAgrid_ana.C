/////////////////////////////////////////////////////////////////////
//
// This macro analyzes the results of PAgrid_create.C
// Results can be plotted with plotPAgrid.C
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
  Int_t normev=0;
  Int_t nmax=10;
  Int_t realnumber[nmax];
  Int_t number[nmax];
  for(Int_t i=0;i<10;i++) {realnumber[i]=0;number[i]=0;}
  Double_t x1,energy,x2,x3;
  Int_t nev,nb,blocknb,nby,nbx;
  TCaloEvent *caloev=new TCaloEvent();
  TCaloTrigger *trigger=new TCaloTrigger();
  TDVCSEvent *event=new TDVCSEvent();
  TPAEvent *paev=new TPAEvent();
  TDVCSEventMC *mcevent=new TDVCSEventMC();
  TVector3* photon=new TVector3(0.,0.,0.);
TVector3* proton=new TVector3(0.,0.,0.);
TLorentzVector *eelectron=new TLorentzVector();
TARSWave* wave=new TARSWave();
TVector3 *vvertex=new TVector3();
TVector3* electron=new TVector3(0.,0.,0.);
TLorentzVector elrec(0.,0.,0.,0.);


  Bool_t grille[100][110][nmax];//[block][tour][%]
  ifstream *infile[nmax];
  TString *namefile[nmax];
  for(Int_t i=0;i<nmax;i++){
    namefile[i]=new TString("liste");
    (*namefile[i])+=i;
    infile[i]=new ifstream(namefile[i]->Data());
  }
  Int_t dum;
  for(Int_t i=0;i<nmax;i++){
    for(Int_t j=0;j<110;j++){
      (*infile[i])>>dum;
      for(Int_t k=0;k<100;k++){
	Bool_t val;
	(*infile[i])>>val;
	grille[k][dum][i]=val;
	//if(i==1 && val==kTRUE) cout<<"tour "<<j<<"  block "<<k<<endl;
	//cout<<dum<<" "<<val<<endl;
      }
    }
  }
  

Int_t cp[10];
for(Int_t i=0;i<10;i++) cp[i]=0;
ifstream f("initdata/output.txt");
f>>x1;
f>>nev;
nev=10000;
for(Int_t i=0;i<6;i++) f>>x1;
for(Int_t j=0;j<nev;j++){               //for1

  if(j%100==0) cout<<j<<" "<<TProcessID::GetObjectCount()<<endl;
  Int_t ObjectNumber=TProcessID::GetObjectCount();
  if(j%1000==0) {
    gObjectTable->Print();
  }
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
  caloev->TriggerSimulation(0,128,.77,kTRUE);
  caloev->DoClustering(0.);
  event->SetCaloEvent(caloev);
  f>>nb;
  for(Int_t i=0;i<nb;i++){//for3
    blocknb=0;
    energy=0.;
    f>>nby;
    f>>nbx;
    f>>energy;
    Int_t xx=paev->GetGeometry()->GetNX();
    Int_t bn=(nby-1)*xx+nbx-1;//This is the block number out of the MC block and cell number
    TPABlock* blockpa=paev->AddBlock();
    blockpa->SetBlockNumber(bn);
    blockpa->SetBlockEnergy(energy);
  }                              // end for3

  
  if(paev->GetEnergy()>0.02 && caloev->GetNbBlocks()>0) {
    // cp[0]++;
    normev++;
  }
  for(Int_t i=1;i<nmax;i++){
    Bool_t toread[100];
    for(Int_t k=0;k<100;k++) {
      toread[k]=kFALSE;
      for(Int_t tour=0;tour<110;tour++){
	if(grille[k][tour][i]) number[i]++;
	if(caloev->GetCaloTrigger()->GetTowerBit(tour)==1){
	  //	  cout<<j<<" Tower "<<tour<<endl;
	  if(grille[k][tour][i]) toread[k]=kTRUE;
	}
      }
    }
    for(Int_t real=0;real<100;real++) {
      // cout<<j<<" "<<i<<" "<<real<<" "<<toread[real]<<endl;
      if(toread[real]) realnumber[i]++;
    }
    Double_t energypa=0.;
    for(Int_t bl=0;bl<paev->GetNbBlocks();bl++){
      TPABlock *pablock=(TPABlock*)(paev->GetPABlocks()->UncheckedAt(bl));
      Int_t nbx=pablock->GetBlockNumber()%20;
      Int_t nby=pablock->GetBlockNumber()/20;
      if(toread[pablock->GetBlockNumber()]) {
	energypa+=pablock->GetBlockEnergy();
      }else{
	//	cout<<j<<" "<<i<<" Block number "<<pablock->GetBlockNumber()<<"... I don't read it! "<<pablock->GetBlockEnergy()<<endl;
     //if(toread[pablock->GetBlockNumber()]) energypa+=pablock->GetBlockEnergy();
      }
     }
    if(energypa>0.02) cp[i]++;
  }
    
  f>>x1 ; f>>x2 ; f>>x3 ;
  electron->SetXYZ(x1,x2,x3);
  mcevent->AddElectron(electron);
  f>>x1 ; f>>x2 ; f>>x3 ;
  photon->SetXYZ(x1,x2,x3);
  mcevent->AddPhoton(photon);
  
  f>>x1 ; f>>x2 ; f>>x3 ;
  proton->SetXYZ(x1,x2,x3);
  mcevent->AddProton(proton);

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

 for(Int_t i=0;i<nmax;i++){
   cout<<i<<" "<<Double_t(cp[i])/Double_t(normev)<<" "<<Double_t(realnumber[i])/Double_t(nev)<<" "<<Double_t(number[i])/110.<<endl;
 }


}
