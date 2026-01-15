#ifndef TReckon_h
#define TReckon_h
#include <TObject.h>
#include <Rtypes.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "TReckPhy.h"
#include "TReckPhysEx.h"
#include "TReckStat.h"
#include "TReckon_Ini.h"
#include "TReckon_Sor.h"
#include "TReckConst.h"
#include "TReckStart.h"
#include "TReckVisu.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TBenchmark.h"

//___________________________________________________________________________
//
//   Class TReckon : core class for shape analysis
//   
//
//

//double un_sur_x(double u,double a,double b);

class TReckon:public TObject
{
  friend class TReckVisu;
  friend class TReckAna;
 public:
  TReckon();// default constructor
  ~TReckon();  //destructor
  int Reckon(UInt_t *);// shape analysis function 
  int Reckon2(UInt_t *);// shape analysis function 
  int Init(TReckPhy *,TReckConst *, TReckStat * ,TReckon_Ini *, TReckon_Sor *);// set the different input and output objects
  int GetMin();
 private:
  TBenchmark * fBReckon;
  // methode associated
  double bruit_seul(double &);// look for background
  double OnePulse(int,double &);//look for one pulse, return position and amplitude
  double OnePulseBckg(int,double &,double &);//look for one pulse with background, return position and amplitude
  double TwoPulses(int,int,double &,double &);// same with two pulses
  double TwoPulsesBckg (int,int,double &,double &,double &);//same with background
  double Analyze( int & , int & , int & , double & , double & , double & ); // check for the different cases on the data
  double coeur2( int & , int & , int & , double & , double & , double & ); // check for the different cases on the data
  void  UpdateProfile(double,int,double);// update the new reference profile
  void  BaseSub();//soustraction de la base et profil de l'evenement
  void  MakeRunningBase(int & );//construit la running base
 protected:
  double fData[2*128];   //  a_x[i ]==>  da_[i+128] data signal
  double fRec[2*128];   // reconstructed shape array  
  double fThreshold;// Threshold on the first case background only ( If there is a pulse the b must be lower )
  //variables d'initialisations
  TReckon_Ini *fIni;//object holding initialisation parameter
  //variable physique  de sortie de l'evenement
  TReckPhysEx * fPhyOut;//physic output : background, first and second pulse amplitude and time
  // variable de control et constante  de control
  TReckConst * fConst;//pointer on an object holding the constants parameters
  //variables statistiques. construites par  TReckon. Utilisees par TReckon_Sor. Initialise par TReckon_Ini
    TReckStat * fStat;// count the number of each cases
  //variables sorties 
  TReckon_Sor * fSort;// updated parameters ( baseline and pulse and sigma on these values )
  ClassDef(TReckon,0)
};
#endif





