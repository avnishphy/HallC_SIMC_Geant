//
// TCaloEvent.cxx, v1.0, Wed Jan  8 10:42:50
// Author: C. Munoz Camacho
//

#include <iostream>

#ifndef __TDVCSEvent__
#include "TDVCSEvent.h"
#endif

using namespace std;

ClassImp(TDVCSEvent)

////////////////////////////////////////////////////////////////////////////////
//
// DVCS event class
// 
////////////////////////////////////////////////////////////////////////////////

Bool_t           TDVCSEvent::fgWarnings = kTRUE;
Bool_t           TDVCSEvent::fgErrors = kTRUE;
TCaloEvent*      TDVCSEvent::fgCaloEvent = 0 ;

//_____________________________________________________________________________
TDVCSEvent::TDVCSEvent(Int_t run, TString col):TDVCSBase(run)
{
  // Default constructor

  cout<<"TDVCS constructor"<<endl;
  
  if (!fgIsInit) InitDB();

  if(!fgCaloEvent) fgCaloEvent = new TCaloEvent(run);
  fCaloEvent=fgCaloEvent;
  narray=1361;//r-function
  init_rfunc(col);//Initializes r-function
}

//_____________________________________________________________________________
Bool_t TDVCSEvent::ThereIsAProton(void)
{
  Bool_t val=kFALSE;
  //  if(fPAEvent->GetNbBlocks()>0) val=kTRUE;
  return val;
  }

/*
//_____________________________________________________________________________
 TCaloEvent::TCaloEvent(const TCaloEvent& TCaloevent)
  // Copy constructor
{
  ((TCaloEvent&)TCaloevent).Copy(*this);
}

//_____________________________________________________________________________
 void TCaloEvent::Copy(TObject& obj)
{
  // Copy routine. Used by copy ctor.

  //  TObject::Copy(obj);

  //  fgParameters.Copy(((TCaloBase&)obj).fgParameters);
  //  ((TCaloBase&)obj).fgIsInit = fgIsInit;

}
*/
//_____________________________________________________________________________
 void TDVCSEvent::Clear(void)
{
  fCaloEvent->Clear();
  //  fPAEvent->Clear();
}

//_____________________________________________________________________________
 void TDVCSEvent::Reset(void)
{
  fCaloEvent->GetClusters()->Delete();
  fCaloEvent->Reset();

}

//_____________________________________________________________________________
 TDVCSEvent::~TDVCSEvent()
{
  // Default destructor
  cout<<"TDVCS destructor"<<endl;
}

//_____________________________________________________________________________
 TLorentzVector TDVCSEvent::GetPhoton(Int_t clus, Float_t a, Float_t b, Float_t &a_out, Float_t &x_corr, Float_t &y_corr)
{
  //    It returns the photon 4-vector for the cluster number "clus". 
  //Vertex (assuming no rastering) and shower depth corrections are implemented.
  //    The reconstruction algorithm depends on 3 parameters:
  //wei0 (in TCaloParameters)  tunes relative block weighting, a and b 
  //(in TDVCSParameters) correct for shower depth.
  //For the moment, the default parameters provided have been optimized for the
  //highest Q^2 setting (using simulated data). They may change slightly for the 
  //other settings.

  Float_t thphot,phphot;
  Float_t vert_dist=fgGeometry.GetCaloDist();
  Float_t calo_pitch=fgGeometry.GetCaloPitch();
  Float_t calo_roll=fgGeometry.GetCaloRoll();
  Float_t calo_yaw=fgGeometry.GetCaloTheta();
  TVector3 recphotvect(0.,0.,0.);
  TLorentzVector recphot(0.,0.,0.,0.);
  Float_t energy=fCaloEvent->GetCluster(clus)->GetE();
  Float_t xphot=fCaloEvent->GetCluster(clus)->GetX();
  Float_t yphot=fCaloEvent->GetCluster(clus)->GetY();
  if(energy==0) {
    return recphot;
  } else {

    // Get corrected distance to calorimeter
    vert_dist-=fVertex(2)*TMath::Cos(-calo_yaw);//fVertex(2) = smeared vertex z //[cm]
    vert_dist-=fVertex(0)*TMath::Sin(-calo_yaw);//fvertex(0) = smeared vertex x ( = 0 cm)

    a = 5.385+(2.554*0.001/(1-6.398*0.0001-TMath::Exp(0.4769*0.001*energy)));// Study using HallC NPS-Gean4 simulation(fit-v2)
    a_out = a; // output shower depth to the Tree
	// a=0.823561*TMath::Power(energy*1000,0.197725)+1.11053e-11; // Study using HallC NPS-Gean4 simulation(fit-v1)
	// a = 9.316+(5.079*0.001/(1-7.62*0.0001-TMath::Exp(1.07*0.001*energy))); // according Malek's study (NPS ELog#196)
    //addendum according to Malek, to optimize shower depth a //14-Nov-2017, used in HallA DVCS
    // a = 0.30*TMath::Power(energy*1000.0,0.28)+4.862;//energy of photons needs to be converted in MeV
    //
    //correct cluster position for shower depth and vertex
    xphot-=xphot*a*TMath::Power(energy,b)/TMath::Sqrt(vert_dist*vert_dist+xphot*xphot);
	
    //moving the cluster position according to the vertex position
    xphot+=fVertex(2)*TMath::Sin(-calo_yaw);
    xphot-=fVertex(0)*TMath::Cos(-calo_yaw);
    
    yphot-=yphot*a*TMath::Power(energy,b)/TMath::Sqrt(vert_dist*vert_dist+yphot*yphot);

    yphot-=fVertex(1);

    x_corr=xphot; // output for the Tree
	  y_corr=yphot; // output for the Tree

    //photon angles
    thphot= -calo_yaw+ TMath::ATan(xphot/vert_dist);
    phphot= TMath::ATan(yphot/TMath::Sqrt(vert_dist*vert_dist+xphot*xphot));
	// Here phphot is defined as the angle between the photon direction and the x–z plane (not the usual azimuthal angle).

    // Correct for pitch (assuming we point right at target center)

//    phphot-=calo_pitch;
 
    recphotvect(0)=energy*TMath::Cos(phphot)*TMath::Sin(thphot);
    recphotvect(1)=energy*TMath::Sin(phphot);
    recphotvect(2)=energy*TMath::Cos(phphot)*TMath::Cos(thphot);

    recphot.SetVect(recphotvect);
    recphot.SetE(energy);

    return recphot;
  }
}

//_____________________________________________________________________________
TLorentzVector TDVCSEvent::GetPhotonDirect(Int_t clus, Float_t a, Float_t b, Float_t &a_out, Float_t &x_corr, Float_t &y_corr)
{
    //    It returns the photon 4-vector for the cluster number "clus". 
    //Vertex (assuming no rastering) and shower depth corrections are implemented.
    //    The reconstruction algorithm depends on 3 parameters:
    //wei0 (in TCaloParameters)  tunes relative block weighting, a and b 
    //(in TDVCSParameters) correct for shower depth.

    Float_t thphot,phphot;
    Float_t vert_dist=fgGeometry.GetCaloDist();
    Float_t calo_pitch=fgGeometry.GetCaloPitch();
    Float_t calo_roll=fgGeometry.GetCaloRoll();
    Float_t calo_yaw=fgGeometry.GetCaloTheta();
    TVector3 recphotvect(0.,0.,0.);
    TLorentzVector recphot(0.,0.,0.,0.);
    Float_t energy=fCaloEvent->GetCluster(clus)->GetE();
    Float_t xphot=fCaloEvent->GetCluster(clus)->GetX();
    Float_t yphot=fCaloEvent->GetCluster(clus)->GetY();
    if(energy==0) {
        return recphot;
    } 
    else {
        TMatrixD Mt(3,3),A(3,3),B(3,1),C(3,1);
        for(Int_t i=0;i<3;i++){
            for(Int_t j=0;j<3;j++){
                Mt(i,j)=0.;
            }
        }
        TVector3 v1,v2,v3,OV,OC,CC,VM,VMM,CM;

        a = 5.478+(2.542*0.001/(1-6.477*0.0001-TMath::Exp(0.4197*0.001*energy)));// Study using HallC NPS-Gean4 simulation(fit-v2)
        // a=0.823561*TMath::Power(energy*1000,0.197725)+1.11053e-11; // Study using HallC NPS-Gean4 simulation
        // a = 9.316+(5.079*0.001/(1-7.62*0.0001-TMath::Exp(1.07*0.001*energy))); // according Malek's study (NPS ELog#196)
        //addendum according to Malek, to optimize shower depth a //14-Nov-2017, used in HallA DVCS
        // a = 0.30*TMath::Power(energy*1000.0,0.28)+4.862;//energy of photons needs to be converted in MeV
        //
        a_out = a;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Intersection coordinates (x_corr,y_corr) of a particule (known 4-vector photonA) with NPS front face//
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        Mt(0,0)=TMath::Cos(calo_yaw); Mt(0,2)=-TMath::Sin(calo_yaw); // calo_yaw is already negative!!!!!!!!
        Mt(2,0)=TMath::Sin(calo_yaw); Mt(2,2)=TMath::Cos(calo_yaw);
        Mt(1,1)=1;
        v1.SetXYZ(Mt(0,0),Mt(1,0),Mt(2,0));
        v2.SetXYZ(Mt(0,1),Mt(1,1),Mt(2,1));
        v3.SetXYZ(Mt(0,2),Mt(1,2),Mt(2,2));

        OC.SetXYZ(-vert_dist*TMath::Sin(calo_yaw),0,vert_dist*TMath::Cos(calo_yaw));
        OV.SetXYZ(fVertex(0),fVertex(1),fVertex(2)); //vertex coordinates

        // VM=photonA.Vect();
        // B(0,0)=OV.X()-OC.X()-a*v3.X(); //a : shower depth (what we want to adjust)
        // B(1,0)=OV.Y()-OC.Y()-a*v3.Y();
        // B(2,0)=OV.Z()-OC.Z()-a*v3.Z();
        // A(0,0)=-VM.X(); A(1,0)=-VM.Y(); A(2,0)=-VM.Z();
        // A(0,1)=v1.X(); A(1,1)=v1.Y(); A(2,1)=v1.Z();
        // A(0,2)=v2.X(); A(1,2)=v2.Y(); A(2,2)=v2.Z();
        // A.Invert();
        // C=A*B;
        // x_corr=C(1,0);
        // y_corr=C(2,0);

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Calculation of a photon 4-vector detected in NPS by taking into account the shower depth correction "a"//
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////

        CM=xphot*v1+yphot*v2+a*v3; //v1, v2, v3 already defined above
        VMM=-OV+OC+CM; // OV and OC already defined above
        VMM=(energy/VMM.Mag())*VMM;
        recphot.SetPxPyPzE(VMM.X(),VMM.Y(),VMM.Z(),energy);

        return recphot;
    }
}

//_____________________________________________________________________________
TVector3 TDVCSEvent::GetProtonDirFast(void)
{
  //    It returns a unitary TVector3 in the direction of the proton assuming
  //it hits the center of the block with a maximum energy loss. 
  //It makes 3-D vertex correction.

  //  TVector3 proton=fPAEvent->GetProtonDir();
  //proton.RotateY(-fgGeometry.GetPATheta());
  //proton-=fVertex; //Vertex correction
  //proton*=1./(proton.Mag());//Normalization
  //return proton;
  
}

//_____________________________________________________________________________
 void TDVCSEvent::Print(const char*  opt)
{
  // Output on screen
}

//_____________________________________________________________________________
void TDVCSEvent::init_rfunc(TString col)
{
	ifstream f[13],f23,f30,f31;
	double ndum,ydum,ddum;

	char date[2048];
	
	cout << "Initializing R-FUNCTION arrays, opening files ..."<<endl;
	
	TString path(getenv("NPS_SOFT"));
	path+="/New-Left/";
	path+=col; //We choose here between collimator and no-collimator
	           //default is no-collimator (as defined in TDVCSEvent.h)
	f[1].open((path+"/line1.dat").Data());
	f[2].open((path+"/line2.dat").Data());
	f[3].open((path+"/line3.dat").Data());
	f[4].open((path+"/line4.dat").Data());
	f[5].open((path+"/line5.dat").Data());
	f[6].open((path+"/line6.dat").Data());
	f[7].open((path+"/line7.dat").Data());
	f[8].open((path+"/line8.dat").Data());
	f[9].open((path+"/line9.dat").Data());
	f[10].open((path+"/line10.dat").Data());
	f[11].open((path+"/line11.dat").Data());
	f[12].open((path+"/line12.dat").Data());
	f23.open((path+"/dy-dd.dat").Data());  // Keeping FORTRAN numbering
	f30.open((path+"/min-max.dat").Data());
	f31.open((path+"/information.dat").Data());
	
	cout << " done." << endl<<endl;

	cout << "Files generated on : " << endl;
	
	f23>>dy>>dd;
	f23.close();
	
	f31.getline(date,2048);
	cout << date << endl<<endl;
	cout << "With following specifications :" << endl;
	f31.getline(date,2048);
	cout <<date << endl;
	f31.getline(date,2048);
	cout << date << endl<<endl;
	
	f31.close();
	
	
	for(int i=1;i<=narray;i++) { // Keeping FORTRAN arrays (starting at 1)
		for(int n=1;n<=12;n++) {
			f[n] >> ndum>>rline[n][i][1] >> rline[n][i][2] >> rline[n][i][3] >>
			rline[n][i][4] >> rline[n][i][5] >> rline[n][i][6];
		}
		f30 >> ydum >> ddum >> tmin[i] >> tmax[i] >> phimin[i] >> phimax[i];
	}
	
	cout << "Initialization done." << endl;

}


//_____________________________________________________________________________
int TDVCSEvent::getindex(double y, double d)
{
	double ddummy=100000.;
	double testa,a;
	int index=0;
	
	for(int i=1;i<=narray;i++) {
		a=TMath::Power(y-rline[1][i][1],2.) + TMath::Power(d-rline[1][i][2],2.);
		if(a<ddummy) {
			index=i;
			ddummy=a;
		}
	}
	ddummy=TMath::Sqrt(ddummy);
	testa=TMath::Sqrt(dd*dd+dy*dy)/2.;
	if(ddummy>testa) index=0;
	return index;

}

//_____________________________________________________________________________
Double_t TDVCSEvent::rfunction(double y,double d,double theta,double phi)
{
	double dline[17];
	double dumreturn=100000.;
//	double em;
	int index=-1;
	int isign;
	
	index=getindex(y,d);
	if(tmax[index]<=0 || tmin[index]>=0) return -1000.; // FORTRAN tests this at i=1 in the following for loop
														// but we might as well do it before the loop.
	
	if(index>0) {
		for(int i=1;i<=12;i++) {
			if(rline[i][index][4]!=0. && rline[i][index][6]!=3.) {
//				em=-rline[i][index][3]/rline[i][index][4]; // Appears not used in FORTRAN
				isign=+1;
				dline[i]=isign*(
					rline[i][index][3]*theta
					+rline[i][index][4]*phi
					+rline[i][index][5])/
					TMath::Sqrt(rline[i][index][3]*rline[i][index][3]+rline[i][index][4]*rline[i][index][4]);
				if(dline[i]<dumreturn) dumreturn=dline[i];
			}
		}
		dline[13]=tmax[index]-theta;
		if(dline[13]<dumreturn) dumreturn=dline[13];
		dline[14]=theta-tmin[index];
		if(dline[14]<dumreturn) dumreturn=dline[14];
		dline[15]=phimax[index]-phi;
		if(dline[15]<dumreturn) dumreturn=dline[15];
		dline[16]=phi-phimin[index];
		if(dline[16]<dumreturn) dumreturn=dline[16];
	} else {
		dumreturn=-1000.;
	}
	
	return dumreturn;

}



