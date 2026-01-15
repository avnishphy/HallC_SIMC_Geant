{
  gSystem->Load("libDVCS.so");

  Int_t run=7001;
  TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,"munoz","");

  Float_t *coef=db->GetEntry_f("CALO_geom_Yaw",run);
  Double_t calo_angle=coef[0]; //absolute value (in radians)
  delete coef;

  Float_t *coef=db->GetEntry_f("CALO_geom_Dist",run);
  Double_t calo_distance=coef[0]; //absolute value (in cm)
  delete coef;

  //  cout<<calo_angle<<" "<<calo_distance<<endl;

  delete db;

}
