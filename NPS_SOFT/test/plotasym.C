#include "TTree.h"
#include "TFile.h"
#include "TClassTable.h"
#include "TDVCSEvent.h"
#include "TDVCSEventMC.h"
#include "TCaloEvent.h"
#include "TPAEvent.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TBranch.h"
#include "TFrame.h"
#include "TGraphErrors.h"

void as()
{  


  TFile *f=new TFile("no3rings.root");
  TTree *tree = (TTree*)f->Get("t");

  TDVCSEvent *event=new TDVCSEvent();
  TDVCSEventMC *mcevent=new TDVCSEventMC();
  TCaloEvent *caloev=new TCaloEvent();
  TPAEvent *paev=new TPAEvent();
  
  TBranch *branchcalo=tree->GetBranch("event_calo");
  TBranch *branchpa=tree->GetBranch("event_pa");
  TBranch *branchmc=tree->GetBranch("event_mc");
  TBranch *branchdvcs=tree->GetBranch("event_dvcs");
  branchmc->SetAddress(&mcevent);
  branchcalo->SetAddress(&caloev);
  branchpa->SetAddress(&paev);
  branchdvcs->SetAddress(&event);
  

  //Histos declaration
//    TH1F *ht[20];
//    TString title="t Spectrum for bin ";
//    TString nom="ht";
//    for(Int_t i=0;i<20;i++) {
//      title+=i;
//      nom+=i;
//      ht[i]=new TH1F(nom.Data(),title.Data(),100,-2,2);
//    }
  Int_t nevent=tree->GetEntries();

  //  nevent=500;

  TH1F *mmsqhist = new TH1F ("mmsq","Mx2-Mp2",100,-1.,2.);
  
  Float_t radtodeg=180./TMath::Pi();
  Float_t protonmass=0.938271998;
  Float_t luminosity=200.*60.*60.*10000.;  // in nb-1
  
  // Initialize initial kinematics
  
  TLorentzVector elecini(0.,0.,5.75,5.75);
  TVector3 impelecini=elecini.Vect();
  TLorentzVector protini(0.,0.,0.,protonmass);
  
  // Initialize arrays for results
  
  Float_t num[20],den[20],norm[20],eventbin[20];
  Float_t eventbinplus[20],eventbinminus[20],sigma[20];
  Float_t sigmaplus[20],sigmaminus[20];
  Float_t anglebin[20],anglebinexact[20];
  Float_t asy[20],dasy[20],ey[20],subin[20];
  
  for(Int_t iii=0;iii<20;iii++){
    num[iii]=0.;
    den[iii]=0.;
    norm[iii]=0;
    eventbin[iii]=0;
    eventbinplus[iii]=0;
    eventbinminus[iii]=0;
    sigma[iii]=0;
    sigmaplus[iii]=0;
    sigmaminus[iii]=0;
    subin[iii]=0;
    ey[iii]=0;
    anglebin[iii]=0;
    asy[iii]=0;
  }
  
  // Loop on events

  for(Int_t i=0;i<nevent;i++){

    if(i%1000==0) cout<<i<<endl;

    tree->GetEvent(i);
    if (caloev->GetNbClusters()>0 && event->ThereIsAProton()) {
      TCaloEvent *evcalo=event->GetCaloEvent();
      TCaloCluster *caloclus=evcalo->GetCluster(0);
      caloclus->Analyze();
      TLorentzVector photonrec=event->GetPhoton();
      TLorentzVector photongen=*(mcevent->GetPhoton());

      
      // An "energy calibration" is necessary to correct for leakage

      photonrec*=1.058;   // Factor to be checked... looks pretty constant
      
      // A cut in photon energy is probably necessary. At some level,
      // it's a cut on the edge of the calorimeter.
      
      if(photonrec.E()>0.8*photongen.E()) {

	// A cut on the proton energy is also necessary
	// This is set at 10 MeV
	
	if(event->GetProtonEnergyLoss()>0.02) {
	  
	  // Should put a cut on the missing mass spectrum to be honest
	  
	  TLorentzVector elecfin=event->GetElectron();//Waiting for TSpectro...

	 TLorentzVector misspart=elecini+protini-elecfin-photonrec;

	 Float_t mmsq=misspart.M2();

	 mmsqhist->Fill(mmsq-protonmass*protonmass);

	 if ((mmsq-protonmass*protonmass)>-0.5 && (mmsq-protonmass*protonmass)<0.5) {

	   TVector3 impelecfin=elecfin.Vect();

	   TLorentzVector protfin=*(mcevent->GetProton());
	   
	   TVector3 impgen=photongen.Vect();

	   Float_t thetagen=TMath::ASin(-impgen(0)/impgen.Mag());
	   Float_t phigen=TMath::ASin(impgen(1)/impgen.Mag());

	   TVector3 imprec=photonrec.Vect();

	   Float_t thetarec=TMath::ASin(-imprec(0)/imprec.Mag());
	   Float_t phirec=TMath::ASin(imprec(1)/imprec.Mag());

	   TLorentzVector virtphot=elecini-elecfin;
	   TVector3 impvirtphot=virtphot.Vect();

	   // Calculate phi with the right convention

	   TVector3 v3=impelecini.Cross(impelecfin);
	   TVector3 v4=-impvirtphot.Cross(imprec);
	   
	   Float_t anglephi;

	   if(v4(2)>0.){
	     anglephi=v3.Angle(v4);
	   }
	   else{
	     anglephi=-v3.Angle(v4);
	   }
	   anglephi=anglephi+TMath::Pi();

	   // Calculate bins in phi

	   double inte=0;
	   Int_t bin=0;
	   modf(20.*anglephi/(2.*TMath::Pi()),&inte);
	   bin=inte;

	   // We choose to use all events for both helicity states 
	   // rather than deviding the sample into helicity + and - 
	   // (which would be the right way to go).

	   eventbinplus[bin]+=mcevent->GetSigmaP()*mcevent->GetPSF();
	   eventbinminus[bin]+=mcevent->GetSigmaM()*mcevent->GetPSF();
	   sigmaplus[bin]+=mcevent->GetSigmaP();
	   sigmaminus[bin]+=mcevent->GetSigmaM();
	   norm[bin]++;
	   anglebin[bin]+=anglephi;

	   // Some kinematical variable calculations

	   Double_t q2=-(elecini-elecfin).Mag2();
	   Double_t minust=-(elecini-elecfin-photonrec).Mag2();
	   Double_t s=(elecini-elecfin+protini).Mag2();
	   Double_t xb=q2/(2.*((elecini-elecfin)*protini));
	   Double_t su=-4.*(elecini*photonrec)*(elecfin*photonrec);

	   //   ht[bin]->Fill(minust);

	   subin[bin]+=su;
	   
	 }
	}
      }
    }
  }

   cout << "Luminosity=" << luminosity << endl;

   Float_t plotasym[16];   // Forget about the 4 central bins
   Float_t dplotasym[16];   // Forget about the 4 central bins
   Float_t plotangle[16];   // Forget about the 4 central bins

   for (Int_t bin=0;bin<20;bin++){
     eventbinplus[bin]*=(luminosity/2.)/7000000;
     eventbinminus[bin]*=(luminosity/2.)/7000000;
     if (norm[bin]>0.) {
       anglebin[bin]=(180.*anglebin[bin]/TMath::Pi())/norm[bin];
     } else {
       anglebin[bin]=anglebin[bin-1]+18.;
     }
     num[bin]=eventbinplus[bin]-eventbinminus[bin];
     den[bin]=eventbinplus[bin]+eventbinminus[bin];
     if (den[bin]>0.) {
       cout<<bin<<" "<<eventbinplus[bin]<<" "<<eventbinminus[bin]<<" "<<num[bin]/den[bin]<<endl;
       asy[bin]=num[bin]/den[bin];
       dasy[bin]=2.*TMath::Sqrt(eventbinplus[bin]*eventbinminus[bin]*(eventbinplus[bin]+eventbinminus[bin]));
       dasy[bin]*=TMath::Power(eventbinplus[bin]+eventbinminus[bin],-2.);
     } else {
      cout<<bin<<" "<<eventbinplus[bin]<<" "<<eventbinminus[bin]<<"0.0"<<endl;
       asy[bin]=0.;
       dasy[bin]=0.;
     }

     if (bin<8) {
       plotasym[bin]=asy[bin];
       dplotasym[bin]=dasy[bin];
       plotangle[bin]=anglebin[bin];       
     } else{
       if (bin>11) {
	 plotasym[bin-4]=asy[bin];
	 dplotasym[bin-4]=dasy[bin];       
	 plotangle[bin-4]=anglebin[bin];       
       }
     } 
   }

   // Binning starts at 0 !!!!!
// Special case for central bins (9,10,11,12), set to zero because of low counting rates

   TCanvas *c1 = new TCanvas();

   TH2F *hr = new TH2F("hr","Single Spin Asymmetry",2,0,360,2,-0.5,0.5);
   hr->SetXTitle("#varphi (deg.)");
   c1->SetGrid();
   hr->Draw();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);

   TGraphErrors *asymgraph = new TGraphErrors(16,plotangle,plotasym,ey,dplotasym);
   asymgraph->SetMarkerColor(kRed);
   asymgraph->SetMarkerStyle(20);
   asymgraph->Draw("P");
   /*
   TCanvas *tspec=new TCanvas();
   tspec->Divide(5,2);
   for(Int_t i=3;i<16;i++){
     tspec->cd(i);
     ht[i]->Draw();
     if(i==7) i=11;
   }
   */
}


