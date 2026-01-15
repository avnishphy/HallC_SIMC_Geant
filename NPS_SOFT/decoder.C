#include <iostream>
#include "TCaloEvent.h"
#include <TString.h>
#include <TTree.h>
#include "THaCodaFile.h"

////////////////////////////////////////////////////////
//
//Example of use of the decode method of TCaloEvent
//     
//
////////////////////////////////////////////////////////
using namespace std;

int  main(int argc,char * argv[])
{
 TString outputname(argv[1]);
 Int_t nb=0;
  for (int i=0;i<argc;i++)
    //cout<<argc<<" "<<argv[i]<<endl;
  switch (argc)
    {
      case 2 :
	{
	  //  cout<<argv[1]<<endl;
	  outputname=argv[1];
	  outputname+=".root";
	}
      break;
      case 3 :
	{
	  //cout<<argv[2]<<endl;
	  outputname=argv[2];
	}
      break;
    default :
      {
	cout<<"To decode a CODA file use the following syntax"<<endl;
	cout<<"Syntax :"<<endl;
	cout<<"decoder codafilename [output name]"<<endl;
	cout<<"If used with one argument the decoded file will have the same name as the codafile with a .root extension appended to it"<<endl;
       return -1;
       
      }
    }
      TFile * fFile = new TFile(outputname.Data(),"RECREATE");
      cout<<"tree"<<endl; 
      TTree * fTree = new TTree("fTree","ARSEvent",99);
      cout<<"caloev"<<endl; 
      TCaloEvent * ev = new TCaloEvent;
      cout<<"branch"<<endl; 
      fTree->Branch("event_calo.","TCaloEvent",&ev,32000,2);
      int * fBuffer;
      THaCodaFile f(argv[1]);
      f.codaRead();
      f.codaRead();
      
      while(f.codaRead()==0)
	{
	  fBuffer=f.getEvBuffer();
	  int len = fBuffer[0] + 1;
	  int evtype = fBuffer[1]>>16;
	  int evnum = fBuffer[4];
	  int index=0;
	  while ((fBuffer[index]&0xffff)!=0xfade&&((index<len)))
	    {
	      //cout<<"skip : "<<hex<<fBuffer[index]<<endl;
	      index++;
	    }
	  if ((fBuffer[index]&0xffff)==0xfade)
		{
		  ev->Decode(&fBuffer[index]);
		  fTree->Fill();
		  nb++;
		  if (nb%1000==0)
		  cout<<evnum<<" "<<nb++<<" events decoded"<<endl;
		}
	}
      fTree->Write("T");
      delete fTree;     
      fFile->Close();
      delete ev;
        
}
