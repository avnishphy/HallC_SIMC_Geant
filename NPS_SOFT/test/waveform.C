/////////////////////////////////////////////////////////////////////////////
//
// This macro shows how to use shape analysis methods
// Reads simulated pulses from a text file, fills a TARSWave, analyzes it and
// fills histograms with fit values found (amplitudes and arrival times
//
// C. Munoz
//
/////////////////////////////////////////////////////////////////////////////


// If you want to compile the macro :


// #include "TCanvas.h"
// #include "TH1.h"
// #include <iostream>
// #include "TARSWave.h"

// void ana(void)
{

// ifstream f("initdata/refshape.txt");
// Double_t val=0.;
// TARSWave *w=new TARSWave(128);
// w->SetNbChannel(0);
// for (Int_t j=0;j<20;j++) w->SetValue(j,200);
// for(Int_t j=0;j<128;j++){
//   f>>val;
//   //  cout<<val<<endl;
//   if(j+20<128) 
// w->SetValue(j+20,-val*3.56+200);
// }
// TCanvas *c=new TCanvas();
// w->DrawRaw(c);
// c->Update();
// c->Modified();
// w->Analyze();
// //TCanvas *d=new TCanvas();
// w->GetFit("data")->Draw();

TCanvas *can=new TCanvas();

Int_t p0=0,p1=0,p2=0;
Double_t t1s,t2s,a1s,a2s;

TH1F* chi0=new TH1F("chi0","Chi0 when 0 pulses",100,0,10000);
TH1F* chi1=new TH1F("chi1","Chi0 when 1 pulse",100,0,10000);
TH1F* chi2=new TH1F("chi2","Chi0 when 2 pulses",100,0,10000);
TH1F* chi100=new TH1F("chi100","Chi0 when more than 2 pulses",100,0,10000);
TH1F* a=new TH1F("a","One pulse found: Fit amplitude - Simulated amplitude",100,-0.04,0.04);
TH1F* b=new TH1F("b","One pulse found: Fit b",100,-1,2);

TH1F* t=new TH1F("t","One pulse found: Fit time - simulated time",100,-2,2);
TH1F* a1=new TH1F("a1","Two pulses found: Fit amplitude 1 - Simulated amplitude 1",100,-0.04,0.04);
TH1F* a2=new TH1F("a2","Two pulses found: Fit amplitude 2 - Simulated amplitude 2",100,-0.04,0.04);
TH1F* b2=new TH1F("b2","Two pulse found: Fit b",100,-1,2);
TH1F* t1=new TH1F("t1","Two pulses found: Fit time 1 - simulated time 1",100,-2,2);
TH1F* t2=new TH1F("t2","Two pulses found: Fit time 2 - simulated time 2",100,-2,2);


// The input textfile 

ifstream f("initdata/simbruit.txt");
//ifstream f("initdata/waveform.dat");
//ifstream f("initdata/simnobruit.txt");
//ifstream f("initdata/simbruit.txt");

Double_t val=0.;
TARSWave *w=new TARSWave(128);
w->SetNbChannel(0);

for(Int_t nev=0;nev<9000;nev++){
  if(nev%10==0) cout<<nev<<endl;
  f>>t1s; f>>a1s; f>>t2s; f>>a2s;
  for(Int_t j=0;j<128;j++){
    f>>val;f>>val;
    w->SetValue(j,val);
  }
  w->Analyze("datawave");
//   w->SetFirstWindow(28,38,"data");
//   w->SetSecondWindow(-20,20,"data");
  if(w->GetNbPulses()==0) {
    p0++;
     chi0->Fill(w->GetChi2());     
  }
  if(w->GetNbPulses()==1){
    p1++;
    chi1->Fill(w->GetChi2());
    a->Fill(2.966*w->GetAmplitude1()-a1s);
    t->Fill(-w->GetArrivalTime1()-t1s);
    b->Fill(w->GetB());
  }
    
  if(w->GetNbPulses()==2){
    p2++;
    chi2->Fill(w->GetChi2());
    a1->Fill(2.966*w->GetAmplitude1()-a1s);
    a2->Fill(2.966*w->GetAmplitude2()-a2s);
    t1->Fill(-w->GetArrivalTime1()-t1s);
    t2->Fill(-w->GetArrivalTime2()-t2s);
    b2->Fill(w->GetB());
  }

  // To visualize pulses one by one in a canvas:

  if(w->GetNbPulses()>0){
  w->GetFit("data")->Draw(can);
  w->DrawRaw(can,"same");
  w->GetFit("data")->GetHisto()->SetLineColor(kRed);
  w->GetFit("data")->GetHisto()->SetDrawOption("same");
  
   }
   if(w->GetNbPulses()==1){
     cout<<"Time theorique : "<<t1s<<endl;
     cout<<"Time fit         "<<-w->GetArrivalTime1()<<endl;
     cout<<endl;
     cout<<"Amplitude theorique : "<<a1s<<endl;
     cout<<"Amplitude fit       : "<<2.966*w->GetAmplitude1()<<endl;
   }
   if(w->GetNbPulses()>1){
     cout<<"Time 1 theorique : "<<t1s<<endl;
     cout<<"Time 1 fit         "<<-w->GetArrivalTime1()<<endl;
     cout<<"Time 2 theorique : "<<t2s<<endl;
     cout<<"Time 2 fit         "<<-w->GetArrivalTime2()<<endl;
     cout<<endl;
     cout<<"Amplitude theorique 1 : "<<a1s<<endl;
     cout<<"Amplitude fit 1       : "<<2.966*w->GetAmplitude1()<<endl;
     cout<<"Amplitude theorique 2 : "<<a2s<<endl;
     cout<<"Amplitude fit 2       : "<<2.966*w->GetAmplitude2()<<endl;
   }
 
 // A pause:
   for(Int_t kkk=0;kkk<10000000;kkk++);
  cout<<"-----------------------------------------------------"<<endl;

}

//Drawing results

TCanvas *c=new TCanvas();
c->Divide(1,3);
c->cd(1);
chi0->Draw();
c->cd(2);
chi1->Draw();
c->cd(3);
chi2->Draw();
TCanvas *c2=new TCanvas();
c2->Divide(2,4);
c2->cd(1);
a->Draw();
a->GetXaxis()->SetTitle("GeV");
a->Draw();
c2->cd(2);
t->Draw();
t->GetXaxis()->SetTitle("ns");
t->Draw();
c2->cd(3);
a1->Draw();
a1->GetXaxis()->SetTitle("GeV");
a1->Draw();
c2->cd(4);
a2->Draw();
a2->GetXaxis()->SetTitle("GeV");
a2->Draw();
c2->cd(5);
t1->Draw();
t1->GetXaxis()->SetTitle("ns");
t1->Draw();
c2->cd(6);
t2->Draw();
t2->GetXaxis()->SetTitle("ns");
t2->Draw();
c2->cd(7);
b->Draw();
c2->cd(8);
b2->Draw();

cout<<p0<<" "<<p1<<" "<<p2<<endl;

}
