// //Comment-out the following lines to compile the macro
// //Then do .L Cosmics2.C++ in a ROOT session
// //and execute it by doing ana()

// #include "TTree.h"
// #include "TFile.h"
// #include "TClassTable.h"
// #include "TDVCSEvent.h"
// #include "TDVCSEventMC.h"
// #include "TCaloEvent.h"
// #include "TObjectTable.h"
// #include "TCanvas.h"
// #include "TH1.h"
// #include "TProcessID.h"
// #include "TStyle.h"
// #include "TF1.h"
// #include "TGraphErrors.h"

//  void ana()
{ 
  //This is all you would usually need to change : 
  /////////////////////////////////////////////////////////////////////////
  TString file="initdata/newcosm3482.dat.root";
  Int_t nev=-1;    //The number of event to analyze (or -1 for all)
  Double_t cut=20.;//This is the trigger ADC value of the top and bottom
                   //blocks (for the vertical cut) 
  Int_t ref=39;//PMT of block 39 is taken as the reference one
  /////////////////////////////////////////////////////////////////////////

  Int_t row=12,col=11;
  Int_t n=row*col;//Number of blocks
  Bool_t throughcol[col];// This will be useful for vertical cut
  Double_t triggerADC[n];
  TARSWave* wt=new TARSWave();
  wt->SetPedestalProfileFile("initdata/prof-09-03-03.root");

  //Reading in trigger pedestals (calculated the previous time)
  ifstream pedtrue("pedf.txt");
  Double_t pedestal[n];
  for(Int_t i=0;i<n;i++) pedtrue>>pedestal[i];

  //Declaration of histograms
  TH1F *h[n];
  TH1F *hnocut[n];
  TH1F *lin[n];
  TH2F *h2[n];
  TString title[n],title2[n],title3[n],title4[n];
  TH1F *hlin=new TH1F("hlin","hlin",100,0,500);
  for(Int_t i=0;i<n;i++){
    title[i]="h";title2[i]="hh";title3[i]="lin";title4[i]="hnocut";
    title[i]+=i;title2[i]+=i;title3[i]+=i;title4[i]+=i;
    h[i]=new TH1F(title[i].Data(),title[i].Data(),100,-20000,100);
    hnocut[i]=new TH1F(title4[i].Data(),title4[i].Data(),100,-20000,100);
    h2[i]=new TH2F(title2[i].Data(),title2[i].Data(),100,-10000,100,100,0,130);
    lin[i]=new TH1F(title3[i].Data(),title3[i].Data(),100,0,500);
  }
  
  //Retrieving and setting up file
  TFile *f=new TFile(file.Data());
  TTree *tree = (TTree*)f->Get("fTree");
  TCaloEvent *caloev;
  TBranch *branchcalo=tree->GetBranch("event_calo.");
  branchcalo->SetAddress(&caloev);
  
  Int_t nevent=tree->GetEntries();
  if(nev!=-1) nevent=nev;
  
  cout<<"Number of events : "<<nevent<<endl;

  Double_t ped[n];
  Int_t pedcp[n];
  for(Int_t k=0;k<n;k++){
    ped[k]=0.;
    pedcp[k]=0;
  }

  /////////////////////////////////////////////////////
  // Begin loops on events
  //.............................
  for(Int_t i=0;i<nevent;i++) {

    if(i==1){
      cout<<"WARNING : ARS/Trigger linearity plots are only reliable after the second"<<endl;
      cout<<"          execution of the macro with the same file, as trigger pedestals "<<endl;
      cout<<"          need to be calculated beforehand."<<endl;
    }

   if(i%10000==0) {
      gObjectTable->Print();
    }
    Int_t ObjectNumber=TProcessID::GetObjectCount();
    //   cout<<"____________________________________"<<endl;
    if(i%1000==0) cout<<i<<"/"<<nevent<<endl;
    tree->GetEntry(i);
    for(Int_t k=0;k<n;k++) triggerADC[k]=0.;

    //Calculating trigger pedestals
    if(caloev->GetNbBlocks()>0){
      for(Int_t k=0;k<n;k++){
	if((caloev->GetBlockPosition(k))==-1) {
	  ped[k]+=caloev->GetCaloTrigger()->GetADCValue(k);
	  pedcp[k]++;
	}
      }
    }

    //Getting trigger ADC information
    for(Int_t j=0;j<caloev->GetNbBlocks();j++){
      TClonesArray* blocks=caloev->GetBlocks();
      TCaloBlock* block=(TCaloBlock*)blocks->UncheckedAt(j);
      if(block->GetBlockNumber()<n){
	caloev->GetWave(j)->SubstractPedestal(block->GetBlockNumber());
	if(block->GetBlockNumber()<n){
	  triggerADC[block->GetBlockNumber()]=caloev->GetCaloTrigger()->GetADCValue(block->GetBlockNumber());
	}
      }
    }

    //Testing for a vertical cosmic with trigger information
    Bool_t verticalcosmic=kFALSE;
    for(Int_t p=0;p<11;p++) {
      if (triggerADC[p*row]>cut  && triggerADC[p*row+col]>cut) {
	throughcol[p]=kTRUE;
	verticalcosmic=kTRUE;
      }else{
	throughcol[p] =kFALSE;
      }
    }

    //Filling histograms
    for(Int_t j=0;j<caloev->GetNbBlocks();j++){
      TClonesArray* blocks=caloev->GetBlocks();
      TCaloBlock* block=(TCaloBlock*)blocks->UncheckedAt(j);
      if(block->GetBlockNumber()<n){
	caloev->GetWave(j)->SubstractPedestal(block->GetBlockNumber());
	if(verticalcosmic && throughcol[block->GetBlockNumber()/row]==kTRUE)
	  h[block->GetBlockNumber()]->Fill(caloev->GetWave(j)->GetSignal()->GetIntegral());
	hnocut[block->GetBlockNumber()]->Fill(caloev->GetWave(j)->GetSignal()->GetIntegral());
	if(verticalcosmic && throughcol[block->GetBlockNumber()/row]==kTRUE){
	  if(caloev->GetWave(j)->GetSignal()->GetMinimumBin()>30 && caloev->GetWave(j)->GetSignal()->GetMinimumBin()<(128-30)) {
	    h2[block->GetBlockNumber()]->Fill(caloev->GetWave(j)->GetSignal()->GetIntegral(),triggerADC[block->GetBlockNumber()]);
	    if(triggerADC[block->GetBlockNumber()]-pedestal[block->GetBlockNumber()]!=0){
	      lin[block->GetBlockNumber()]->Fill(-caloev->GetWave(j)->GetSignal()->GetIntegral()/(triggerADC[block->GetBlockNumber()]-pedestal[block->GetBlockNumber()])); 
	      if(triggerADC[block->GetBlockNumber()]>40.) hlin->Fill(-caloev->GetWave(j)->GetSignal()->GetIntegral()/(triggerADC[block->GetBlockNumber()]-pedestal[block->GetBlockNumber()]));
	    }										    
	    //if(-caloev->GetWave(j)->GetSignal()->GetIntegral()/(triggerADC[block->GetBlockNumber()]-pedestal[block->GetBlockNumber()])>400) cout<<"Event "<<i<<" "<<block->GetBlockNumber()<<endl;
	  }
	}
      }
    }
    caloev->Reset();//We do reset here and not clear !!
    TProcessID::SetObjectCount(ObjectNumber);
  }//End loop on events
  
  
  //Finding maximum value of all histograms
  Double_t max=0.,maxnocut=0.;
  for(Int_t i=0;i<n;i++) {
    if(h[i]->GetMaximum()>max) max=h[i]->GetMaximum();
    if(h[i]->GetMaximum()>maxnocut) maxnocut=hnocut[i]->GetMaximum();
  }
  
  //Starting drawing plots
  Double_t mean[n],sigma[n],meaner[n],sigmaer[n],x[n],ex[n],corfactor[n];
  TCanvas *c0=new TCanvas();//Histograms without the vertical cut
  TCanvas *c=new TCanvas();//Histograms in linear scale (with cut)
  TCanvas *c2=new TCanvas();//Histograms in log scale (with cut)
  TCanvas *c3=new TCanvas();
  TCanvas *c5=new TCanvas();
  gStyle->SetPadBorderMode(0);
  c->Divide(col,row,0,0);
  c0->Divide(col,row,0,0);
  c2->Divide(col,row,0,0);
  c3->Divide(col,row,0,0);
  c5->Divide(col,row,0,0);
  for(Int_t i=0;i<n;i++){
    c0->cd(i+1);
    if(i/col<row-1) gPad->SetBottomMargin(0);
    if(i/col>0) gPad->SetTopMargin(0);
    if((i+1)%col>0) gPad->SetRightMargin(0);
    if(i%col>0)gPad->SetLeftMargin(0);
    gPad->SetLogy();
    hnocut[col-i/col+row*(i%col)]->SetMaximum(maxnocut);
    hnocut[col-i/col+row*(i%col)]->Draw();
    /////////////////////////////////////////
    c->cd(i+1);
    if(i/col<row-1) gPad->SetBottomMargin(0);
    if(i/col>0) gPad->SetTopMargin(0);
    if((i+1)%col>0) gPad->SetRightMargin(0);
    if(i%col>0)gPad->SetLeftMargin(0);
    h[col-i/col+row*(i%col)]->SetMaximum(max);
    h[col-i/col+row*(i%col)]->Draw();
    /////////////////////////////////////////
    c2->cd(i+1);
    if(i/col<row-1) gPad->SetBottomMargin(0);
    if(i/col>0) gPad->SetTopMargin(0);
    if((i+1)%col>0) gPad->SetRightMargin(0);
    if(i%col>0)gPad->SetLeftMargin(0);
    gPad->SetLogy();
    h[col-i/col+row*(i%col)]->SetMaximum(max);
    h[col-i/col+row*(i%col)]->Fit("gaus");
    TF1* func=(TF1*)h[col-i/col+row*(i%col)]->GetFunction("gaus");
    //    mean[col-i/col+row*(i%col)]=h[col-i/col+row*(i%col)]->GetMean();
    mean[col-i/col+row*(i%col)]=func->GetParameter(1);
    //corfactor[col-i/col+row*(i%col)]=h[col-i/col+row*(i%col)]->GetMean()/h[ref]->GetMean();
    sigma[col-i/col+row*(i%col)]=func->GetParameter(2);
    delete func; 
    meaner[col-i/col+row*(i%col)]=h[col-i/col+row*(i%col)]->GetRMS();
    //sigmaer[col-i/col+row*(i%col)]=func->GetParError(2);
    ex[col-i/col+row*(i%col)]=0;
    x[col-i/col+row*(i%col)]=col-i/col+row*(i%col);
    h[col-i/col+row*(i%col)]->Draw();
    //////////////////
    c3->cd(i+1);
    if(i/col<row-1) gPad->SetBottomMargin(0);
    if(i/col>0) gPad->SetTopMargin(0);
    if((i+1)%col>0) gPad->SetRightMargin(0);
    if(i%col>0)gPad->SetLeftMargin(0);
    h2[col-i/col+row*(i%col)]->Draw();
    ///////////////////////////////////
    c5->cd(i+1);
    if(i/col<row-1) gPad->SetBottomMargin(0);
    if(i/col>0) gPad->SetTopMargin(0);
    if((i+1)%col>0) gPad->SetRightMargin(0);
    if(i%col>0)gPad->SetLeftMargin(0);
    lin[col-i/col+row*(i%col)]->Draw();
  }

  for(Int_t i=0;i<132;i++) corfactor[i]=mean[i]/mean[ref];

  //We output to the terminal the corrective factor to
  //each PMT in order to calculate the new HV
  ofstream fHT("lastfactor.txt");
  for(Int_t i=0;i<n;i++) {
    cout<<corfactor[i]<<endl;
    fHT<<corfactor[i]<<endl;
  }
  //We output to a file the trigger pedestal
  //Next time we will read them in, to calculate linearity plots
  ofstream pedf("pedf.txt");
  for(Int_t k=0;k<n;k++){
    pedf<<ped[k]/Double_t(pedcp[k])<<endl;
  }
  
  //Finally, mean and rms of each histogram (with cut)
  //to check dispersion
  Double_t disx[n],disy[n],xaxis[n];
  for(Int_t i=0;i<n;i++){
    disx[i]=lin[i]->GetMean();
    disy[i]=lin[i]->GetRMS();
    xaxis[i]=i;
  }
  TCanvas *c6=new TCanvas();
  TGraph *meandis=new TGraph(n,xaxis,disx);
  TGraph *rmsdis=new TGraph(n,xaxis,disy);
  c6->Divide(1,2);
  c6->cd(1);
  meandis->Draw("A*");
  c6->cd(2);
  rmsdis->Draw("A*");

  //Linearity histogram (all blocks together)
  TCanvas *c4=new TCanvas();
  hlin->Draw();
  
  //The text file for Pierre
  ofstream fpierre ("out.txt");
  for(Int_t i=0;i<n;i++){
    fpierre<<i<<" "<<h[i]->GetEntries()<<" "<<h[i]->GetMean()<<" "<<h[i]->GetRMS()<<" "<<sigma[i]<<endl;
  }

}//The happy end



