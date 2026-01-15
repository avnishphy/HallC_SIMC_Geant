//
// TCaloCluster.cxx, v1.0, Thu Dec  5 14:42:50
// Author: C. Mu�oz Camacho
//

#include <iostream>
#include "TCaloCluster.h"

#ifndef ROOT_TStyle
#include "TStyle.h"
#endif

#ifndef ROOT_TH2
#include "TH2.h"
#endif

#ifndef ROOT_TVector3
#include "TVector3.h"
#endif
using namespace std;

ClassImp(TCaloCluster)

////////////////////////////////////////////////////////////////////////////////
//
// Calorimeter cluster class
// 
////////////////////////////////////////////////////////////////////////////////

Bool_t           TCaloCluster::fgWarnings = kTRUE;
Bool_t           TCaloCluster::fgErrors = kTRUE;

//_____________________________________________________________________________
TCaloCluster::TCaloCluster()//:fClusBlock(fgGeometry.GetNBlocks())
{
  //    Default constructor

  //The TRefArray size is equal to the total number of blocks in the calorimeter

  //  cout<<"TCaloCluster constructor "<<" "<<fClusBlock<<endl;
  fClusBlock=new TClonesArray("TRef",fgGeometry.GetNBlocks());
  fClusBlock->BypassStreamer(kFALSE); //Otherwise TClones of TRef doesn't work
  fClusSize=0;
  fEnergy=0;
  fX=0.;
  fY=0.;
  fAnalyzed = kFALSE;
  fHCalo2=0;
}

//_____________________________________________________________________________
void TCaloCluster::Clear(Option_t *option)
{ 
  fClusBlock->Clear("C");
  fClusSize=0;
  fAnalyzed=kFALSE;
  if(fHCalo2) fHCalo2->Clear();
}

//_____________________________________________________________________________
/* TCaloCluster::TCaloCluster(const TCaloCluster& TCalocluster)
  // Copy constructor
{
  ((TCaloCluster&)TCalocluster).Copy(*this);
}

//_____________________________________________________________________________
 void TCaloCluster::Copy(TObject& obj)
{
  // Copy routine. Used by copy ctor.

  TObject::Copy(obj);

  //  fgParameters.Copy(((TCaloCluster&)obj).fgParameters);


}
*/
//_____________________________________________________________________________
 TCaloCluster::~TCaloCluster()
{
  //    Default destructor
  //It deletes the TRefArray
  
  if(fHCalo2) delete fHCalo2;
  //The following line crushes when called from TCaloEvent::Clear(), but
  //it might produce a memory leak... To be checked!

  //fClusBlock->Delete(); 
  delete fClusBlock;
  fClusBlock=0;
  fClusSize=0;
  //  if(fHCalo2) delete fHCalo2;
  //cout<<"TCaloCluster destructor "<<endl;

}

//_____________________________________________________________________________
void TCaloCluster::AddBlock(TCaloBlock * block)
{
  //    It adds a block to the TClonesArray of cluster blocks. The size of the cluster is incremented by one.

  TClonesArray &blocks = *fClusBlock;
  new(blocks[fClusSize++]) TRef(block);
//    TRef* ref=new(blocks[fClusSize++]) TRef(block);
//    ref->SetObject(block);
}

//_____________________________________________________________________________
void TCaloCluster::Display(TCanvas *display, Float_t HistMax, Float_t BlockThreshold)
{
  //    This method gets a TCanvas* and plots inside a display of the cluster.
  //A TH2 with bins simulating each calorimeter block is displayed.
  //The number shown in each block correspond to the energy loss in the block
  //(in MeV if original energy is in GeV).
  //Coloring is also implemented for easy visualisation.
  //    Two optional parameters are implemented : HistMax and BlockThreshold.
  //HistMax allows to set a maximum to the TH2. This is especially useful for
  //comparisons as it allows to set a unique color scale. If it is not 
  //specified, color scale maximum will be calculated automatically using the
  //value of the block of maximum energy loss.
  //BlockThreshold sets an energy threshold for a block to be displayed.
  //It is set to zero by default. In any case, even if color is displayed,
  //energy loss will not be shown if it is less than 0.001

  if (!fHCalo2) {
    fHCalo2=new THCalo(display,HistMax);
  }else{
    fHCalo2->Clear();
    fHCalo2->SetPad(display);
  }
  //if (!fHCalo2) fHCalo2=new THCalo();
  //Data filling
  for(Int_t k=0;k<fClusSize;k++){
    TRef *ref=(TRef*)fClusBlock->UncheckedAt(k);
    TCaloBlock *block=(TCaloBlock*)ref->GetObject();
    if (block->GetBlockEnergy()>BlockThreshold) {
      fHCalo2->SetBinContent(Int_t((block->GetBlockNumber())/fgGeometry.GetNY()+0.5)+1,Int_t((block->GetBlockNumber())%fgGeometry.GetNY()+0.5)+1,block->GetBlockEnergy()*1000.);
    }
  }
  cout<<fHCalo2<<endl;
  fHCalo2->Draw();

  /*  
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);
  display->cd();

  //Histos declaration
  TH2F *calotmp = new TH2F("calotmp","Calorimeter Display",fgGeometry.GetNX(),0.5,fgGeometry.GetNX()+0.5,fgGeometry.GetNY(),0.5,fgGeometry.GetNY()+0.5);
  TH2F *calo = new TH2F("calo","Calorimeter Display",fgGeometry.GetNX(),0.5,fgGeometry.GetNX()+0.5,fgGeometry.GetNY(),0.5,fgGeometry.GetNY()+0.5);
  TH2F *hcalo = new TH2F("hcalo","Calorimeter Display",fgGeometry.GetNX(),0.5,fgGeometry.GetNX()+0.5,fgGeometry.GetNY(),0.5,fgGeometry.GetNY()+0.5);

  //Data filling
  for(Int_t k=0;k<fClusSize;k++){
    TRef *ref=(TRef*)fClusBlock->UncheckedAt(k);
    TCaloBlock *block=(TCaloBlock*)ref->GetObject();
    if (block->GetBlockEnergy()>BlockThreshold) 
      calotmp->Fill((block->GetBlockNumber())%fgGeometry.GetNX()+0.5,(block->GetBlockNumber())/fgGeometry.GetNX()+0.5,block->GetBlockEnergy());
  }

  //Histos filling and arrangement
  for(Int_t kf=1;kf<fgGeometry.GetNX()+1;kf++){
    for(Int_t kf2=1;kf2<fgGeometry.GetNY()+1;kf2++){
      Float_t tmp=calotmp->GetBinContent(kf,kf2);
      calo->SetBinContent(kf,fgGeometry.GetNY()+1-kf2,tmp);
      hcalo->SetBinContent(kf,fgGeometry.GetNY()+1-kf2,int(tmp*1000.));
      //Conversion GeV->MeV for text display
    }
  }

  //Making display look beautiful...
  hcalo->SetMarkerSize(1.6);
  display->SetGridx();
  display->SetGridy();

  (calo->GetYaxis())->SetNdivisions(fgGeometry.GetNY(),kFALSE); 
  (calo->GetXaxis())->SetNdivisions(fgGeometry.GetNX(),kFALSE); 
  (calo->GetYaxis())->SetLabelColor(kWhite);
  (calo->GetXaxis())->SetLabelColor(kWhite);
  
  calo->SetMinimum(0);
  hcalo->SetMinimum(0);
  if(HistMax!=-1.) {
    calo->SetMaximum(HistMax);
    hcalo->SetMaximum(HistMax*1000);
    //Setting of maximum histogram value. Automatically calculated if not specified.
  }

  //Drawing...
  calo->Draw("colz");
  hcalo->Draw("textsame");
  display->Update();
  display->Modified();

  //We delete everything
  delete calotmp;
  delete calo;
  delete hcalo;
  */
}

//_____________________________________________________________________________
 Float_t TCaloCluster::GetEnergy(void)
{
  //    It returns the energy of the cluster. 
  //It just sums over the energy of all blocks in the cluster. 

  Float_t energy=0.;
  for(Int_t i=0;i<fClusSize;i++){
    TRef *ref=(TRef*)fClusBlock->UncheckedAt(i);
    TCaloBlock *block=(TCaloBlock*)ref->GetObject();
    energy+=block->GetBlockEnergy();
  }
  return energy;
}

//_____________________________________________________________________________
 TCaloBlock* TCaloCluster::GetBlock(Int_t i)
{
  //It returns a pointer to the block number i in the cluster.

  if(i>=fClusSize) cout<<"ERROR: Cluster size is smaller than the block requested"<<endl;

  TRef *ref=(TRef*)fClusBlock->UncheckedAt(i);
  TCaloBlock *block=(TCaloBlock*)ref->GetObject();
  return block;

}

//_____________________________________________________________________________
 void TCaloCluster::Analyze(Bool_t kFORCE, Float_t timemin, Float_t timemax, Float_t wei0, Float_t &wei_out)
{
  //    It calculates the fX and fY of the cluster in coordinates in the surface
  //of the calorimeter and sets the cluster energy fEnergy. 
  //It does not make vertex and shower depth correction.

  if(!fAnalyzed || kFORCE==kTRUE){

    Float_t wei,sumwei;
    Float_t d, RM; // for calculation of wei0 (Malek & Wassim's study)
    Float_t xclust=0.;
    Float_t yclust=0.;
    sumwei=0.;
    d=2.05; // NPS crystal size in cm
    RM=2.19; //Moliere Radius of PbWO4 in cm
    
    fEnergy=0.;//GetEnergy();
    Double_t blocksenergy[fgGeometry.GetNBlocks()];
    for(Int_t i=0;i<fgGeometry.GetNBlocks();i++) blocksenergy[i]=0.;
    for(Int_t i=0;i<fClusSize;i++) {
      TRef *ref=(TRef*)fClusBlock->UncheckedAt(i);
      TCaloBlock *block=(TCaloBlock*)ref->GetObject();
      blocksenergy[block->GetBlockNumber()]=block->GetBlockEnergy();

      if(timemin>-1000||timemax>-1000){
        if(block->GetEnergy(0)>0.&&(block->GetTime(0)<timemin||block->GetTime(0)>timemax)
          &&block->GetEnergy(1)>0.&&(block->GetTime(1)<timemin||block->GetTime(1)>timemax)) {
          blocksenergy[block->GetBlockNumber()]=0.;
        }
        if(!(block->GetEnergy(1)>0.) &&(block->GetTime(0)<timemin||block->GetTime(0)>timemax))
          blocksenergy[block->GetBlockNumber()]=0.;

        if(block->GetEnergy(0)>0.&&block->GetTime(0)>=timemin&&block->GetTime(0)<=timemax)
          blocksenergy[block->GetBlockNumber()]=block->GetEnergy(0);

        if(block->GetEnergy(1)>0.&&block->GetTime(1)>=timemin&&block->GetTime(1)<=timemax
          && (TMath::Abs( (block->GetTime(1) )-( (timemax+timemin)/2.) ) <
              TMath::Abs( (block->GetTime(0) )-( (timemax+timemin)/2.) ) )   )
          blocksenergy[block->GetBlockNumber()]=block->GetEnergy(1);
      }
      fEnergy+=blocksenergy[block->GetBlockNumber()];
    }

    for(Int_t i=0;i<fClusSize;i++) {
      TRef *ref=(TRef*)fClusBlock->UncheckedAt(i);
      TCaloBlock *block=(TCaloBlock*)ref->GetObject();
      if(blocksenergy[block->GetBlockNumber()]<=0.) blocksenergy[block->GetBlockNumber()]=0.000000001;
      if(fEnergy>0){
        wei0=3.6;  // Study using HallC NPS-Gean4 simulation
        // wei0=TMath::Log(100*fEnergy/(2.02*TMath::Exp(-1*d/RM)+(4.98*TMath::Exp(-1*d/RM)+0.30)*fEnergy)); // based on the study from Malek
        // wei0=4.3;  // HallA
        wei_out = wei0;
	      wei=TMath::Max(0.,wei0+TMath::Log(blocksenergy[block->GetBlockNumber()]/fEnergy));
      }
      else{
	      wei=0.;
      }
      xclust+=wei*fgGeometry.GetBlockXPos(block->GetBlockNumber());
      yclust+=wei*fgGeometry.GetBlockYPos(block->GetBlockNumber());
      sumwei+=wei;
      //cout<<wei<<" "<<block->GetBlockNumber()<<" "<<block->GetBlockEnergy()<<" "<<fgGeometry.GetBlockXPos(block->GetBlockNumber())<<" "<<fgGeometry.GetBlockYPos(block->GetBlockNumber())<<endl;
    }
    if(sumwei>0.) {
      //20190424(start)
      // xclust=(xclust/sumwei)-fgGeometry.GetCenterXPos();
      xclust=+fgGeometry.GetCenterXPos()-(xclust/sumwei);
      //20190424(finish)
      yclust=-fgGeometry.GetCenterYPos()+(yclust/sumwei);
    } else {
      xclust=-100000.;
      yclust=-100000.;
    }
    fX=xclust;
    fY=yclust;

    //    cout<<wei<<" "<<fX<<" "<<fY<<endl;

    fAnalyzed = kTRUE ;
  }

}

//_____________________________________________________________________________
 void TCaloCluster::Print(char* opt)
{
  //    Output on screen: number of blocks in the cluster,
  //list of blocks with corresponding energy, cluster energy and
  //cluster X and Y positions at the surface of the calorimeter 
  //(no vertex or shower depth corrections).
  
  cout<<"===================================================="<<endl;
  if(fAnalyzed){
    cout<<"Cluster analyzed : "<<endl;
  }else{
    cout<<"Cluster NOT analyzed : "<<endl;
  }
  cout<<"____________________________________________________"<<endl;
  cout<<"Number of blocks in the cluster : "<<fClusSize<<endl<<endl;
  for(Int_t i=0;i<fClusSize;i++){
    TRef *ref=(TRef*)fClusBlock->UncheckedAt(i);
    TCaloBlock *block=(TCaloBlock*)ref->GetObject();
    Int_t blocknb=block->GetBlockNumber();
    cout<<"Block "<<blocknb<<" (column "<<fgGeometry.GetBlockX(blocknb);
    cout<<", row "<<fgGeometry.GetBlockY(blocknb);
    cout<<") : Energy="<<block->GetBlockEnergy()<<endl;    
  }
  cout<<endl;
  if(fAnalyzed){
    cout<<"____________________________________________________"<<endl;
    cout<<"Cluster energy : "<<fEnergy<<endl;
    if(fX==-100000){
      cout<<"No X or Y available"<<endl;
    }else{
      cout<<"Cluster X (no vertex or shower depth correction) : "<<fX<<endl;
      cout<<"Cluster Y (no vertex or shower depth correction) : "<<fY<<endl;
    }
    cout<<endl;
  }
  
}



















