
#include "TDVCSELoss.h"
using namespace std;

ClassImp (TDVCSELoss)

TDVCSELoss::TDVCSELoss()
{
}

TDVCSELoss::~TDVCSELoss()
{}

//_____________________________________________________________________________

 Double_t TDVCSELoss::ExEnerg( Double_t z_med, Double_t d_med )
{
  Double_t EXEN;

//---- Some Z=1 isotopes

  if( TMath::Abs(z_med-1.0)<0.5) {
    //-    Gaseous hydrogen
    if(d_med<0.01)
      EXEN = 19.2;
    //-    Liquid Hydrogen
    else if(d_med<0.1)
      EXEN = 21.8;
    //---- Liquid Deuterium
    else
      EXEN = 21.8;
  }
  //---- Some Z=2 isotopes

  //-    Gaseous/Liquid Helium

  else if( TMath::Abs(z_med-2.0)<0.1 )
    EXEN = 41.8;

  //---- Plastic scintillator (Polyvinyltolulene 2-CH[3]C[6]H[4]CH=CH[2])
  //     
  //     z_eff = 3.36842    a_eff =  6.21996    d_med = 1.03200

  else if( TMath::Abs(z_med-3.37)<0.1 )
    EXEN = 64.7;

  //---- Kapton (Polymide film C[22]H[10]N[2]O[5])
  //     
  //     z_eff = 5.02564    a_eff =  9.80345    d_med = 1.42000

  else if( TMath::Abs(z_med-5.03)<0.1 )
    EXEN = 79.6;

  //---- Some Z=6 isotopes

  else if( TMath::Abs(z_med-6.0)<0.1 )
    EXEN = 78.0;

  //---- Air (dry, near sea level, 78% N2 + 22% O2)
  //     
  //     z_eff = 7.22000    a_eff = 14.46343    d_med = 1.20480E-03

  else if( TMath::Abs(z_med-7.22)<0.1 )
    EXEN = 85.7;

//---- Aluminum

  else if( TMath::Abs(z_med-13.0)<0.1 )
    EXEN = 166.0;

//---- Copper

  else if( TMath::Abs(z_med-29.0)<0.1 )
    EXEN = 322.0;

//---- Titanium

  else if( TMath::Abs(z_med-22.0)<0.1 )
    EXEN = 233.0;
//---- Iron

  else if( TMath::Abs(z_med-26.0)<0.1 )
    EXEN = 286.0;

//---- Table overflow

  else {
    cout << endl;
    cout << "Warning... Unknown selected material !!" << endl;
    cout << "z_med = " << z_med << " d_med = " << d_med << endl;
    cout << "Implement TElossCorrection::ExEnerg routine for proper use." 
	 << endl << endl;
    EXEN = 0.0;
  }

  return EXEN;
}

 Double_t TDVCSELoss::ElossHadron( Int_t Z_hadron, Double_t beta, 
					   Double_t z_med, Double_t a_med, 
					   Double_t d_med, 
					   Double_t pathlength )
{
  //-----------------------------------------------------------------------
  //
  // Energy loss of hadrons taking into account the  usual  Bethe-Bloch
  // stopping power + the Density Effect Corrections (important at high
  // energy) + the Shell Corrections (important at small energy). 
  // The approximation 2 * gamma * m_e / M << 1 is used for the  Bethe-
  // Bloch formulae: for a 4 GeV/c pion, this leads to an effect about
  // 0.5-0.7 % on the total stopping power.
  // 
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  //
  // Passed variables
  //
  //        Z_hadron     hadron charge 
  //            beta     hadron velocity                (relative to light) 
  //
  //           z_med     effective charge of the medium
  //           a_med     effective atomic mass          (AMU)
  //           d_med     medium density                 (g/cm^3)
  //      pathlength     flight path through medium     (m)
  //
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  //
  // Return value
  //
  //                     Energy loss of hadron          (GeV)
  //
  //-----------------------------------------------------------------------


  Double_t BETA2,GAMA2,GAMA,PLAS,ETA,ETA2,ETA4,ETA6;
  Double_t BETH,DENS,SHE0,SHE1,SHEL,HSTP;
  Double_t X,X0,X1,M,EXEN,C,A;

  //---- Constant factor corresponding to 4*pi*N_a*(r_e)^2*m_e*c^2
  //     Its units are MeV.cm2/g          

  static const Double_t COEF = 0.3070749162;

  //---- Electron mass (MeV)

  static const Double_t EMAS = 0.5109989020;

  //---- Numerical constants

  static const Double_t log100 = TMath::Log(1e2);

  //---- Input variables consistency check

  if( Z_hadron == 0 || beta <= 0.0 || beta >= 1.0 || z_med == 0.0 ||
      a_med == 0.0 || pathlength == 0.0 )
    return 0.0;

  pathlength *= 1e2;  // internal units are cm

  BETA2 = beta * beta;
  GAMA2 = 1.0 / (1.0 - BETA2);
  GAMA  = TMath::Sqrt( GAMA2 );
  ETA  = beta * GAMA ;

  //---- Reduced Bethe-Bloch stopping power

  EXEN = ExEnerg(z_med,d_med);  // in eV!
  //-    Tabulated material check
  if( EXEN == 0.0 ) 
    return 0.0;

  BETH = TMath::Log(2e6*EMAS*BETA2*GAMA2/EXEN) - BETA2;

  //---- Reduced density correction

  PLAS = 28.8084 * TMath::Sqrt(d_med*z_med/a_med);
  C = 2.0*TMath::Log(PLAS) - 2.0*TMath::Log(EXEN) - 1.0;
  X = TMath::Log10(ETA);
  HaDensi(z_med,d_med,X0,X1,M);
  //-    Tabulated density consistency
  if((X0+X1+M) == 0.0)
    return 0.0;
  A = -1.0 * ( C + log100*X0 ) / TMath::Power(X1-X0,M);
  if(X<X0)
    DENS = 0.0;
  else if(X<X1)
    DENS = log100*X + C + A*TMath::Power(X1-X,M);
  else
    DENS = log100*X + C;
  DENS *= 0.5;

  ETA2 = 1.0 / (ETA*ETA) ;
  ETA4 = ETA2 * ETA2 ;
  ETA6 = ETA4 * ETA2 ;

  //---- Reduced shell correction

  SHE0 = 4.2237e-1*ETA2 + 3.040e-2*ETA4 - 3.80e-4*ETA6;
  SHE1 = 3.8580e0 *ETA2 - 1.668e-1*ETA4 + 1.58e-3*ETA6;
  SHEL = 1e-6 * EXEN * EXEN * (SHE0 + 1e-3*SHE1*EXEN) / z_med;

  //---- Total hadron stopping power
   
  HSTP = COEF * z_med * Double_t(Z_hadron*Z_hadron) / a_med;
  HSTP = HSTP * ( BETH - DENS - SHEL ) / BETA2;

  //---- Electron energy loss

  Double_t eloss = HSTP * d_med * pathlength * 1e-3; // in GeV

  return eloss;
}

//_____________________________________________________________________________
 void TDVCSELoss::HaDensi( Double_t z_med, Double_t d_med,
				  Double_t& X0, Double_t& X1, Double_t& M )
{

  //---- Some Z=1 isotopes

  if( TMath::Abs( z_med-1.0 ) < 0.1 ) {
    //-    Gaseous hydrogen
    if( d_med < 0.01 ) {
      X0 =  1.8639;
      X1 =  3.2718;
      M  =  5.7273;
    }
    //-    Liquid Hydrogen
    else if( d_med < 0.1 ) {
      X0 =  0.4759;
      X1 =  1.9215;
      M  =  5.6249;
    }
    //---- Liquid Deuterium
    else if( d_med >= 0.1 ) {
      X0 =  0.4759;
      X1 =  1.9215;
      M  =  5.6249;
    }
  }
  //---- Some Z=2 isotopes

  else if( TMath::Abs( z_med-2.0 ) < 0.1 ) {
    //-    Gaseous/Liquid Helium
    X0 =   2.2017;
    X1 =   3.6122;
    M  =   5.8347;
  }

  //---- Plastic scintillator (Polyvinyltolulene 2-CH[3]C[6]H[4]CH=CH[2])
  //     
  //     z_eff = 3.36842    a_eff =  6.21996    d_med = 1.03200

  else if( TMath::Abs( z_med-3.37 ) < 0.1 ) {
    X0 =  0.1464;
    X1 =  2.4855;
    M  =  3.2393;
  }

  //---- Kapton (Polymide film C[22]H[10]N[2]O[5])
  //     
  //     z_eff = 5.02564    a_eff =  9.80345    d_med = 1.42000

  else if( TMath::Abs( z_med-5.03 ) < 0.1 ) {
    X0 =  0.1509;
    X1 =  2.5631;
    M  =  3.1921;
  }

  //---- Some Z=6 isotopes

  else if( TMath::Abs( z_med-6.0 ) < 0.1 ) {
    //-    Carbon (graphite, density 1.700 g/cm3)
    if( d_med < 1.750) {
      X0 =  0.0480;
      X1 =  2.5387;
      M  =  2.9532;
    }
    //-    Carbon (graphite, density 2.000 g/cm3)
    else if( d_med < 2.050) {
      X0 = -0.0351;
      X1 =  2.4860;
      M  =  3.0036;
    }
    //-    Carbon (graphite, density 2.265 g/cm3)
    else if( d_med < 2.270) {
      X0 = -0.0178;
      X1 =  2.3415;
      M  =  2.8697;
    }
  }

//---- Air (dry, near sea level, 78% N2 + 22% O2)
//     
//     z_eff = 7.22000    a_eff = 14.46343    d_med = 1.20480E-03

  else if( TMath::Abs( z_med-7.22 ) < 0.1 ) {
    X0 =   1.7418;
    X1 =   4.2759;
    M  =   3.3994;
  }

//---- Aluminum

  else if( TMath::Abs( z_med-13.0 ) < 0.1 ) {
    X0 =  0.1708;
    X1 =  3.0127;
    M  =  3.6345;
  }

//---- Iron

  else if( TMath::Abs( z_med-26.0 ) < 0.1 ) {
    X0 =  0.10;
    X1 =  3.0;
    M  =  3.29;
  }

//---- Titanium

  else if( TMath::Abs( z_med-22.0 ) < 0.1 ) {
    X0 =  0.0957;
    X1 =  3.0386;
    M  =  3.0302;
  }

//---- Table overflow

  else {
    cout << endl;
    cout << "Warning... Inconsistent material density... " << endl;
    cout << "z_med = " << z_med << " d_med = " << d_med << endl;
    cout << "Implement THaElossCorrection::HaDensi routine for proper use."
	 << endl << endl;
    X0 =  0.;
    X1 =  0.;
    M  =  0.;
  }
     
  return;
}

