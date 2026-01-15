#include <iostream>
////////////////////////////////////////////////////////
//
//Example of use of the decode method of TCaloEvent
//     
//
////////////////////////////////////////////////////////
using namespace std;

void decode()
{
  TString outputname("decode.root");
  TFile * fFile = new TFile(outputname.Data(),"RECREATE");
  cout<<"tree"<<endl; 
  TTree * fTree = new TTree("fTree","ARSEvent",99);
  cout<<"caloev"<<endl; 
  TCaloEvent * ev = new TCaloEvent;
  cout<<"branch"<<endl; 
  fTree->Branch("event_calo.","TCaloEvent",&ev,32000,2);
  int * buf;
  THaCodaFile f("../trigcosm38.dat");
  f.codaRead();
  f.codaRead();
  while(f.codaRead()==0)
    {
      f.codaRead();
      buf=f.getEvBuffer();
      cout<<hex<<buf[10]<<endl;
      // if buffer is on the header "0xfade" marking the start of a calorimeter
      //event the calorimeter the Decode methode will
      // fill the TCaloEvent 
      // ideally you have to look for the 0xfade header but for the test
      // stand data structure is fix
      ev->Decode(&buf[10]);
      fTree->Fill();
    }
  fTree->Write("T");
  fFile->Close();
  // delete ev;
  //delete fTree;
}
