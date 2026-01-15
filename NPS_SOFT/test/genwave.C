//////////////////////////////////////////////////////////////////////////////
//
// This macro generates a file with simulated pulses: 0, 1 and 2 pulses
//
// C. Munoz
//
//////////////////////////////////////////////////////////////////////////////

{
  ofstream f("initdata/simbruit.txt");
  Int_t nev=3000;
  Int__t t2,t1=0;Double_t a2,a2=1.,zero=0.;
  Double_t dum;
  Double_t val[128+52+128];
  ifstream ini("initdata/refshape.txt");
  for(Int_t i=0;i<129;i++){
    val[i]=0;
  }
  for(Int_t i=129;i<128+129;i++){
       ini>>val[i];
  }
  for(Int_t i=128+129;i<128+129+51;i++){
    val[i]=0.;
  }

  for(Int_t i=0;i<nev;i++){
    f<<zero<<" "<<zero<<" "<<zero<<" "<<zero<<endl;
    for(Int_t c=0;c<128;c++){
      f<<c<<" "<<val[c+129-40]*0.<<endl;
    }
    a1=(gRandom->Rndm());
    f<<"40"<<" "<<a1*2.966<<" "<<zero<<" "<<zero<<endl;
    for(Int_t c=0;c<128;c++){
      f<<c<<" "<<(-val[c+129-40])*a1/1.+gRandom->Gaus(0.,3.)<<endl;
    }
   t2=Int_t(Int_t((gRandom->Rndm())*(128+51))-50.);
   a1=(gRandom->Rndm())*3.;
   a2=(gRandom->Rndm())/2.;
   f<<"40"<<" "<<a1*2.966<<" "<<t2<<" "<<a2*2.966<<endl;
   for(Int_t c=0;c<128;c++){
     //f<<c<<" "<<((val[c+129-40]*a1*(-1.))-(val[c-t2+129]*a2))<<endl;
     f<<c<<" "<<(gRandom->Gaus(0.,3.))+((val[c+129-40]*a1*(-1.))-(val[c-t2+129]*a2))<<endl;
     if(c-t2+129>128+129+90-1 || c-t2+129<0) cout<<"warning : "<<c-t2+129<<" "<<t2<<endl;
   }
  }
}
