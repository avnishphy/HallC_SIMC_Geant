#include <iostream>
#include "TCaloEventXY.h"
#include <TString.h>
#include <TTree.h>
#include "THaCodaFile.h"
#include <string>
//#include <THaEvData.h>

////////////////////////////////////////////////////////
//
//Example of use of the decode method of TCaloEvent
//with ADC data (and LED scaler)
//
////////////////////////////////////////////////////////
using namespace std;

int  main(int argc,char * argv[])
{
  TString outputname(argv[1]);
  //  THaEvData codaev;
  Int_t nb=0,adcb,adcc;
  Int_t x=0,y=0,z=0;
  Float_t adc[132];for(Int_t i=0;i<132;i++) adc[i]=0;
  char * adcn;
  adcn=new char[255];

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
      TCaloEventXY * ev = new TCaloEventXY;
      cout<<"branch"<<endl; 
      //I increased the number of splitting from 2 to 3. If you ever get a crash, try split=2. (Carlos)
      fTree->Branch("event_calo.","TCaloEventXY",&ev,32000,3);
      int * fBuffer;
      THaCodaFile f(argv[1]);
      f.codaRead();
      f.codaRead();
      f.codaRead();
      f.codaRead();
      while(f.codaRead()==0)
	{
	  fBuffer=f.getEvBuffer();
	  int len = fBuffer[0] + 1;
	  int evtype = fBuffer[1]>>16;
	  //cout<<evtype<<endl;
	  int evnum = fBuffer[4];
	  switch (evtype)
	    {
	    case 1:
	      {
		int index=0;
		while ((fBuffer[index]&0xffff)!=0xfade&&((index<len)))
		  {
		    //cout<<"skip : "<<hex<<fBuffer[index]<<endl;
		    index++;
		  }
		if ((fBuffer[index]&0xffff)==0xfade)
		  {
		    ev->Decode(&fBuffer[index]);
		    ev->SetXPos(x);
		    ev->SetYPos(y);
		    for (int i=0;i<132;i++)
		      		      ev->SetADC(i,adc[i]);
		    fTree->Fill();
		    nb++;
		    if (nb%1000==0)
		      cout<<evnum<<" "<<nb++<<" events decoded"<<endl;
		  }
	      }
	      break;
	    case 131:
	      int b,c;
	       char *ch;
	      char *chaine,*sb;
	      float valeur;
	      char nom[255];
	      int off=45;
	      int pos;
	      string arf2;
	      char st[255],mv[255];
	      if (fBuffer!=0)
	      {
	      ch =(char *)&(fBuffer[11]);
	      //for(int i=0;i<(4*len);i++)
	      //cout<<ch[i];
	      TString RT(ch);
	      string stri=ch;
	      //cout<<RT.Data()<<endl;
	      int start=1,prev=1;
	      //cout<<RT.Index("\n",start)<<endl;
	      while (RT.Index("\n",start)>0)
	      {
		arf2=stri.substr(prev,start-prev);
 		if (arf2.c_str()[0]=='f')
 		  {
 		    sscanf(arf2.c_str(),"%s %d",&mv,&pos);
		    //  cout<<mv<<": "<<pos<<endl;
		    
		    if (strstr(mv,"festo_xpos")!=NULL)
 		      x=pos;
		    
 		    if (strstr(mv,"festo_ypos")!=NULL)
 			   y=pos;
			
 		    if(strstr(mv,"festo_zpos")!=NULL)
		    z=pos;
			//cout<<x<<" "<<y<<" "<<z<<" "<<endl;
 		  }
 		else
		  {
		    sscanf(arf2.c_str(),"haVMI3128_%d_AI%d %f",&b,&c,&valeur);
		    //cout<<arf2.c_str()<<"nyark"<<b<<" "<<c<<" "<<valeur<<endl;
		    //cout<<(b-1)*60+(c-1)<<endl;
		    if((b-1)*60+(c-1)<132 && (b-1)*60+(c-1)>-1) 
		      adc[(b-1)*60+(c-1)]=valeur;
		    
		  }
		prev=start;
		start=RT.Index("\n",start)+1;
   
	      }
	      }
	      break;
	    }
	}
      fTree->Write("T");
      delete ev;
      delete fTree; 
      delete adcn;    
}
