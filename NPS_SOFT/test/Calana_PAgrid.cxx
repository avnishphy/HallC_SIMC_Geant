#include <fstream>
#include <iostream>

#ifndef __TCaloBlock__
#include "TCaloBlock.h"
#endif

#ifndef __TARSParameters__
#include "TARSParameters.h"
#endif

#ifndef __TARSBase__
#include "TARSBase.h"
#endif

#ifndef __THPA__
#include "THPA.h"
#endif

#ifndef __TCaloBlock__
#include "TCaloBlock.h"
#endif

#ifndef __TDVCSEvent__
#include "TDVCSEvent.h"
#endif

#ifndef __TDVCSEventMC__
#include "TDVCSEventMC.h"
#endif

#ifndef __TCaloEvent__
#include "TCaloEvent.h"
#endif

#ifndef __TCaloTrigger__
#include "TCaloTrigger.h"
#endif

#ifndef __TPAEvent__
#include "TPAEvent.h"
#endif

#ifndef __TARSArray__
#include "TARSArray.h"
#endif

#ifndef __TARSWave__
#include "TARSWave.h"
#endif

#ifndef ROOT_TObject
#include "TObject.h"
#endif

#ifndef ROOT_TCanvas
#include "TCanvas.h"
#endif

#ifndef ROOT_TObjectTable
#include "TObjectTable.h"
#endif

#ifndef ROOT_TRandom
#include "TRandom.h"
#endif

#ifndef ROOT_TTree
#include "TTree.h"
#endif

#ifndef ROOT_TFile
#include "TFile.h"
#endif

#ifndef ROOT_TProcessID
#include "TProcessID.h"
#endif

#ifndef ROOT_TRint
#include "TRint.h"
#endif

#ifndef ROOT_TRandom2
#include "TRandom2.h"
#endif

#ifndef ROOT_TStyle
#include "TStyle.h"
#endif


int main(int argc,char* argv[])
{
  TRint rint("ro",0,0);
  TFile tf("treenewbruitwph.root","RECREATE");
  TTree t("tree","My tree");

  TH2I *htour[110];
  for(Int_t i=0;i<110;i++){
    TString name("h");
    name+=i;
    htour[i]=new TH2I(name.Data(),name.Data(),20,0,20,5,0,5);
  }

  THPA *hPA[110];
  for(Int_t i=0;i<110;i++){
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


  int Max_Block_X, Max_Block_Y;
  float Max_E = 0;


  int Max_Block_X2, Max_Block_Y2;
  float Max_E2 = 0;


  t.SetAutoSave(1000000000);

  TH2F BlockOffset("BlockOffset", "Block offset",9,-4.5,4.5,7,-3.5,3.5);

  TH2F Energy("Energy", "Energy", 100,0,0.2,100,0,0.2);

  TH1F *hblsim[100];
  //  TString hblsimname="hsim";
  for(Int_t i=0;i<100;i++) {
  TString hblsimname="hsim";
    hblsimname+=i;
    hblsim[i]=new TH1F(hblsimname.Data(),"histo",100,-.3,0.3);
  }

  Int_t nev,nb,nbx,nby,blocknb;
  //  Int_t n1;
  Float_t x1,x2,x3,energy;

  TH1I *hBlockNb = new TH1I("BlockNb","BlockNb",15,0,15);
  Int_t blockcount;

  TH1F *hEnj    = new TH1F("Enj","Enj",100,-.6,.3);
  TH1F *hEnj128 = new TH1F("Enj128","Enj128",100,-.1,4);
  TH1F *hEnj30  = new TH1F("Enj30","Enj30",100,-.1,4);
  TH2F *hEnj2   = new TH2F("Enj2","Enj2",100,-.1,4,100,-.1,4);
  TH1F *hENJ    = new TH1F("ENJ","ENJ",100,-1,.3);


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
  //  TARSArray *bl = new TARSArray(128);
    TARSWave* wave=new TARSWave();

  //TDVCSEvent branch doesn't split properly automatically.
  //The fCaloEvent which it contains does not split at all, whatever 
  //splitting we set for the branch.

  //Manual splitting seems to work. From ROOT 3.04 on, a splitting of 
  //TCaloEvent higher than 2 crashes. Previous versions of ROOT could manage 
  //higher splitting (thanks Rene for this new feature). Two is at this 
  //moment the maximum level of splitting that can be made to TCaloEvent 
  //anyway. Hopefully, we'll be able to split higher when TCaloEvent becomes
  //more complex (TClonesArray of energies, for example).
  //We can always comment line 1609 of TBranchElement.cxx, comment-out
  //line 1610 and recompile ROOT to make splitting work for TCaloEvent.
  
       t.Branch("event_calo.","TCaloEvent",&caloev,16000,2);
       //       t.Branch("event_pa.","TPAEvent",&paev,16000,99);
    t.Branch("event_mc.","TDVCSEventMC",&mcevent,16000,99);
  //Comment-out the following line to run test/copla.C
  t.Branch("fElectron","TLorentzVector",&eelectron,16000,99);
  t.Branch("fVertex","TVector3",&vvertex,16000,99);

  ifstream f("initdata/output.txt");
  f>>x1;
  f>>nev;
  TRandom2 ran2(4325);
  nev=5000;
  TRandom ran(543);
  
  for(Int_t i=0;i<6;i++) f>>x1;
  
  TCanvas *display = new TCanvas("display","Event Display",0,0,450,350);
  TCanvas *display2 = new TCanvas("display2","Event After Trigger",455,0,450,350);
  TCanvas *display3 = new TCanvas("display3","Cluster 1",0,380,450,350);
  TCanvas *display4 = new TCanvas("display4","Cluster 2",455,380,450,350);
 
  TCaloCluster *caloclus=0;

// We use this empty cluster to "erase" the cluster canvas when there 
//is no cluster
  TCaloCluster *clustest=new TCaloCluster(); 

  Float_t Nmoy=0;
  Int_t nbb128=0;  
  Int_t nbb60 =0;  
  Int_t nbb50 =0;  
  Int_t nbb40 =0;  
  Int_t nbb30 =0;  

  Double_t valenj=1.5;



  for(Int_t j=0;j<nev;j++){               //for1
    blockcount=0;

    if(j%100==0) cout<<j<<" "<<TProcessID::GetObjectCount()<<endl;

    Int_t ObjectNumber=TProcessID::GetObjectCount();

    if(j%1000==0) {
      // gObjectTable->Print();
    }

    for(Int_t i=0;i<132;i++) trigger->SetADCValue(i,1000.);


    f>>nb;
    //    cout<<"BEGINNING OF THE LOOP"<<endl;
    for(Int_t i=0;i<nb;i++){             // for2
      blocknb=0;
      energy=0.;
      f>>blocknb;
      f>>energy;
      TCaloBlock* block=caloev->AddBlock(blocknb);
      //cout<<"block "<<i<<endl;
      //block->SetBlockNumber(blocknb-1);
      //      cout<<"avant"<<endl;
      block->SetBlockEnergy(energy);
      //cout<<"apres"<<endl;
      trigger->SetADCValue(blocknb,energy*1000.);
      //      cout<<energy<<endl;
      //  }

                          caloev->AddSimPulse("initdata/refshapenew.dat",energy*(ran2.Gaus(1.,1./TMath::Sqrt(1000.*energy))),128);

	    //           caloev->AddSimPulse("initdata/refshapenew.dat",energy,128);

       //       caloev->AddNoise("initdata/noisecalo.txt");
    ////////////////////////////////
      /*     
      // for(Int_t i=0;i<nb;i++){
//        //     cout<<"before addwave "<<j<<endl;
       wave=caloev->AddWave(128);
//       //cout<<"Voila wave number "<<i<<endl;
        for(Int_t j=0;j<128;j++) {
	  Short_t val=j*ran.Gaus(0,3.);
	  wave->SetValue(j,val);
//  	//	wave->SetValue(i+64,64-val);
        }
      */ 
    }                                // end for2
    //    caloev->Print();

    //    caloev->JitterSimulation(0,2);
                                 
     // cout<<"BEFORE NOISE "<<endl;
//      caloev->Print();
     //caloev->AddNoise("initdata/noisecalo.txt"); 
//      cout<<"AFTER NOISE "<<endl;
//      caloev->Print();
    //    caloev->SetARSArray(bl);
    //cout<<"number of waves"<<bl->GetNbWaves()<<endl;

    //////////////////////////////////

     caloev->SetCaloTrigger(trigger);
//     caloev->SetTriggerValues();
//        cout<<"AVANT"<<endl;
    //caloev->Print();
      //       caloev->Display(display,3000.,0.);
      //  trigger->Display(display,3000.,0.);
  

     //   if(j>1600) caloev->Print();
     caloev->TriggerSimulation(0,128,.5,kTRUE);
              caloev->DoClustering(0.);
     if(caloev->GetNbWaves()>0){
     Float_t enjrec128=0;     
     if(caloev->GetNbClusters()>0){
       TCaloCluster* clus=caloev->GetCluster(0);
       for(Int_t i=0;i<clus->GetClusSize();i++){
         TCaloBlock* bloc=clus->GetBlock(i);
	 Int_t pos=caloev->GetBlockPosition(bloc->GetBlockNumber());
	 TARSWave* wave;
	 wave=caloev->GetWave(pos);
	 enjrec128+=wave->GetArray()->GetIntegral();
       }
	 enjrec128=enjrec128/(-4832.04);
        caloev->GetCluster(0)->Analyze();
//        enjrec128=caloev->GetCluster(0)->GetEnergy();
//        TCaloCluster* clus=caloev->GetCluster(0);
     }  
     Int_t tmp128=caloev->GetNbBlocks();
     
     if(caloev->GetNbClusters()>0){
       if((caloev->GetCluster(0)->GetX()<13.5) && (caloev->GetCluster(0)->GetX()>-13.5) && (caloev->GetCluster(0)->GetY()<15.) && (caloev->GetCluster(0)->GetY()>-15.) &&  tmp128>0) nbb128++;
     }
    

     Float_t enjrec30=0;

        caloev->TriggerSimulation(45,95,1.,kTRUE);
     caloev->DoClustering(0.);
     if(caloev->GetNbClusters()>0){
       TCaloCluster* clus=caloev->GetCluster(0);
       for(Int_t i=0;i<clus->GetClusSize();i++){
         TCaloBlock* bloc=clus->GetBlock(i);
	 Int_t pos=caloev->GetBlockPosition(bloc->GetBlockNumber());
	 TARSWave* wave;
	 wave=caloev->GetWave(pos);
	 enjrec30+=wave->GetArray()->GetIntegral();
       }
       enjrec30=enjrec30/(-4832.04);
        caloev->GetCluster(0)->Analyze();
//        enjrec30=caloev->GetCluster(0)->GetEnergy();
//         TCaloCluster* clus=caloev->GetCluster(0);
     }

     
     Int_t tmp30=caloev->GetNbBlocks();
     // if(tmp128>0 && (tmp128-tmp30)<1) nbb30++;

     if(caloev->GetNbClusters()>0){
       if((caloev->GetCluster(0)->GetX()<13.5) && (caloev->GetCluster(0)->GetX()>-13.5) && (caloev->GetCluster(0)->GetY()<15.) && (caloev->GetCluster(0)->GetY()>-15.) && tmp30>0) nbb30++;
     }

//      if(tmp128>0 && tmp30==0){
//        cout <<"ev a regarder " << j << endl;    
//      }



//       caloev->Display(display2,3,0.);
    //    display2->Update();display2->Modified();
	 //   cout<<"APRES"<<endl;
    // caloev->Print();
  //   caloev->DoClustering(0.);
//     cout<<"AFTER TRIGGER"<<endl;
//     caloev->Print();

	 // caloev->DoClustering(0.);
    /*
       
    if (caloev->GetNbClusters()>0) {
      caloclus=caloev->GetCluster(0);
      //  caloclus->Print();
                  caloclus->Display(display3,3);
//        TCanvas *d=new TCanvas();
//              caloclus->Display(d);
      //TLorentzVector phot=caloev->GetCluster(0)->GetPhoton();
      //cout<<"Cluster 1 : "<<phot.Py()<<endl;
    }else{
      clustest->Display(display3,3);
    }
    if (caloev->GetNbClusters()>1) {
     //caloev->GetCluster(1)->Display(display4,3);
    }else{
//        display4->Update();
//        display4->Modified();
    }      
    */
//    for (Int_t i=0;i<150000000;i++);
    
     }    

     //  char fff; 
     //  cin>>fff; 

    event->SetCaloEvent(caloev);

//       f>>n1;
//       for(Int_t i=0;i<n1;i++){
//         f>>x1;
//         f>>x1;
//         f>>x1;
//       }

     Max_E = 0;
     Max_E2 = 0;


     f>>nb;
     for(Int_t i=0;i<nb;i++)          //for3
     {
       blocknb=0;
       energy=0.;
       f>>nby;
       f>>nbx;
       f>>energy;
       for(Int_t hi=0;hi<110;hi++){   //for4
	 if((caloev->GetCaloTrigger()->GetTowerBit(hi))==kTRUE && energy>0.05){ 
           htour[hi]->Fill(nbx-1,nby-1);
           if(Ttab[hi][nbx-1][nby-1]=-1){
	     Ttab[hi][nbx-1][nby-1]=1;
	   }
         }
       }                              //end for4
       if(energy>.05)   blockcount++;
       if (energy>Max_E)
         {
           Max_E2 = Max_E;
           Max_E = energy;
           Max_Block_X = nbx;
           Max_Block_Y = nby;
         }



       Int_t xx=paev->GetGeometry()->GetNX();
       Int_t bn=(nby-1)*xx+nbx-1;//This is the block number out of the MC block and cell number
       TPABlock* blockpa=paev->AddBlock();
       blockpa->SetBlockNumber(bn);
       blockpa->SetBlockEnergy(energy);
       
       /*
       Int_t pos=paev->GetSimBlockPos(nbx,nby);


       Float_t energysim=0.;
       if(pos!=-1)
       {
	 energysim=((TPASimBlock*)(paev->GetPASimBlocks()->UncheckedAt(pos)))->GetBlockEnergy();
         cout << nbx << "    " << nby << endl;
	 cout << energysim << "    " << energy << endl;
         hblsim[bn]->Fill(energy-energysim);
       }
       */

     }                               // end for3
     hBlockNb->Fill(blockcount);
     Nmoy+=blockcount;

       
      //     paev->TriggerSimulation(0.01);
     
     //paev->TriggerSimulation();
     //    paev->Display(display4,200,0.);
     //display4->SetEditable(kFALSE);
     // for(Int_t i=0;i<1000000000;i++);
 

     if(paev->GetNbBlocks()>0){
       TVector3 protonrec=event->GetProtonDirFast();
     }
//       caloev->Print();

     //    for(Int_t i=0;i<17;i++){

     f>>x1 ; f>>x2 ; f>>x3 ;
     electron->SetXYZ(x1,x2,x3);
     mcevent->AddElectron(electron);
     f>>x1 ; f>>x2 ; f>>x3 ;
     //     cout<<x1<<" "<<x2<<" "<<x3<<endl;
     photon->SetXYZ(x1,x2,x3);
     //photon->SetE(x1*x1+x2*x2+x3*x3);
     mcevent->AddPhoton(photon);
     Float_t enjgen=mcevent->GetPhoton()->E();

//       f>>x1 ; f>>x2 ; f>>x3 ;
//       photon->SetXYZ(x1,x2,x3);
//       mcevent->AddPhoton(photon);
     f>>x1 ; f>>x2 ; f>>x3 ;
     proton->SetXYZ(x1,x2,x3);
     mcevent->AddProton(proton);


     f>>x1;
     mcevent->SetVertex(0.,0.,x1);
     Float_t P_Vertex = x1;

     /*
     int BX,BY;

     TLorentzVector P_Proton;
     P_Proton.SetVectMag(*proton, 0.93828);
     if (Max_E > 0.010)
     { 
       paev->AnalyzeSim(P_Vertex*10.0, P_Proton);
       if (paev->GetPASimBlocks()->GetEntries() == 1)
	 {
	   BX = ((TPASimBlock*)(paev->GetPASimBlocks()->UncheckedAt(0)))->GetBlockX();
	   BY = ((TPASimBlock*)(paev->GetPASimBlocks()->UncheckedAt(0)))->GetBlockY();
	   BlockOffset.Fill(BX-Max_Block_X, BY-Max_Block_Y);
	 }

       Int_t pos=paev->GetSimBlockPos(Max_Block_X, Max_Block_Y);
       Float_t energysim=0.;
       if(pos!=-1)
       {
         energysim=((TPASimBlock*)(paev->GetPASimBlocks()->UncheckedAt(pos)))->GetBlockEnergy();
         hblsim[0]->Fill(Max_E+Max_E2-energysim);
         if (paev->GetPASimBlocks()->GetEntries() == 1)
           Energy.Fill(Max_E,energysim);
       }
     }

*/
          event->SetPAEvent(paev);

     f>>x1;
     mcevent->SetSigmaP(x1);
     f>>x1;
     mcevent->SetSigmaM(x1);
     f>>x1;
     mcevent->SetPSF(x1);

     //     for(Int_t i=0;i<19;i++){//Fichier pi0

       f>>x1; //Smeared electron
       f>>x2;
       f>>x3;
       elrec.SetPxPyPzE(x1,x2,x3,TMath::Sqrt(TMath::Power(x1,2.)+TMath::Power(x2,2.)+TMath::Power(x3,2.)));
       event->SetElectron(elrec);

     f>>x1;
     event->SetVertex(0.,0.,x1);

     //event->SetDVCSEventMC(mcevent);
     
     //if(caloev->GetNbClusters()>0) caloev->GetCluster(0)->Print();

//       if(caloev->GetNbClusters()>0)cout<<"===> "<<j<<" "<<caloev->GetCluster(0)->GetClusBlock()->GetEntriesFast()<<endl;
//       if(caloev->GetNbClusters()>0) caloev->GetCluster(0)->Print();
//       cout<<"===> "<<j<<" "<<caloev->GetClusters()->GetEntriesFast()<<endl;
//       caloev->Print();
//     cout<<j<<" before filling"<<endl;
     vvertex=&(event->GetVertex());
     eelectron->SetPxPyPzE(elrec.Px(),elrec.Py(),elrec.Pz(),elrec.E());


     // cout<<eelectron->Px()<<" "<<eelectron->Py()<<" "<<eelectron->Pz()<<" "<<eelectron->E()<<endl;

     //    cout<<enjrec<<" "<<enjgen<<" "<<enjrec-enjgen<<endl;
  
     //    if(enjrec128-enjrec30<-0.1) cout<<" event "<<j<<endl;
  
/*   hEnj   ->Fill(enjrec30-enjrec128);
   hEnj128->Fill(enjrec128);
   hEnj30 ->Fill(enjrec30);
   hEnj2  ->Fill(enjrec128,enjrec30);
*/  

   if(caloev->GetNbClusters()>0){
     if((caloev->GetCluster(0)->GetX()<13.5) && (caloev->GetCluster(0)->GetX()>-13.5) && (caloev->GetCluster(0)->GetY()<15.) && (caloev->GetCluster(0)->GetY()>-15.)){   
       //   hENJ->Fill(1.058*enjrec30-enjgen);
     }
   }

   t.Fill();
     //  cout<<j<<" after filling"<<endl;
     event->Clear();
      mcevent->Clear();
     //caloev->Reset();
     TProcessID::SetObjectCount(ObjectNumber);
     
  }                                      //end for1


  //  tf.Write("0",TObject::kOverwrite);

//   tf.Write();
//   t.Print();
  
//   tf.Close();



  // Histo des tours du proton array sur les blocks du calo

  Float_t max=0;
  for(Int_t i=0;i<110;i++){
    Float_t maxtmp=htour[i]->GetMaximum();
    if(maxtmp>max) max=maxtmp;
  }

  gStyle->SetPadBorderMode(0);
  TCanvas *c=new TCanvas();
  c->Divide(10,11,0,0);
  for(Int_t i=0;i<110;i++){
    c->cd(i+1);
    for(Int_t j=0;j<20;j++){
      for(Int_t k=0;k<5;k++){
	Int_t val=htour[10-i/10+11*(i%10)]->GetBinContent(j+1,k+1);
        hPA[10-i/10+11*(i%10)]->SetBinContent(j+1,k+1,val);
      }
    }
    gPad->SetTopMargin(0);
    gPad->SetBottomMargin(0);
    gPad->SetLeftMargin(0);
    gPad->SetRightMargin(0);
    hPA[10-i/10+11*(i%10)]->SetPad((TPad*)gPad);
    hPA[10-i/10+11*(i%10)]->SetMaximum(max/1000.);
    hPA[10-i/10+11*(i%10)]->Draw();
  }
 

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

  /* TCanvas *cc=new TCanvas();
  hBlockNb->Draw();
  */

  /*  TCanvas *dd=new TCanvas();
  dd->Divide(2,3,0,0);
  dd->cd(1);  
  hEnj128->Draw(); 
  dd->cd(3);  
  hEnj30->Draw(); 
  dd->cd(5);  
  hEnj->Draw();   
  dd->cd(2);  
  hEnj2->Draw();
   */

  TCanvas *dd2=new TCanvas();
  hENJ->Draw();                 //E30-Egen

  cout << "nbb128 "<< nbb128 <<endl;
  cout << "nbb30 " << nbb30 <<endl;
  cout << "efficacite " << Double_t(nbb30)/2942. <<endl;
                                           // ->code pour 5000ev, 128ns;.5GeV
  cout << "pour 128  " << Double_t(nbb128)/2942. <<endl;

     rint.Run();

//   delete event;
//   delete mcevent;
//   delete paev;
//   //cout<<"PAEvent correctly deleted"<<endl;
//   delete caloev;

//   delete clustest;

//   delete display;
//   delete display2;
//   delete display3;
//   delete display4;

  /*    
	TCaloBase *calobase=new TCaloBase();
        //   calobase->Init();
        calobase->Print("test");
        //    TCaloBlock *block=new TCaloBlock();
        TARSWave *wavears = new TARSWave();
        wavears->Init();
        Float_t ene=wavears->GetEnergy();
        cout<<ene<<endl;
  */

}       //end main
