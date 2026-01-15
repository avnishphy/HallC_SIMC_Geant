{
  gSystem.Load("libDVCS.so");
  gdvcs->SetWF(0);
  gdvcs->SetRun(12);
  gdvcs->ForceUpdate();
  TDVCSEvent e;
  e.GetGeometry()->SetRun(12);
  e.GetGeometry()->InitDB();
  cout<<e.GetGeometry()->GetCaloDist()<<endl;
  TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,"munoz","");
 
  TString name4=("CALO_geom_Dist");
  db->GetServer()->Query("select * from CALO_geom_Dist;");
  Float_t *coef=db->GetEntry_f(name4.Data(),12);
  cout<<coef[0]<<endl;
  cout<<db->GetLastValueId("CALO_geom_Dist",12)<<endl;

  TString name5=("CALO_geom_X");
  db->GetServer()->Query("select * from CALO_geom_X;");
  Float_t *x = new Float_t[1080];
  x=db->GetEntry_f(name5.Data(),12);
  TString name6=("CALO_geom_Y");
  db->GetServer()->Query("select * from CALO_geom_Y;");
  Float_t *y = new Float_t[1080];
  y=db->GetEntry_f(name6.Data(),12);

  TString name7=("CALO_geom_X0");
  db->GetServer()->Query("select * from CALO_geom_X0;");
  Float_t *x0 = new Float_t[1];
  x0=db->GetEntry_f(name7.Data(),12);
  TString name8=("CALO_geom_Y0");
  db->GetServer()->Query("select * from CALO_geom_Y0;");
  Float_t *y0 = new Float_t[1];
  y0=db->GetEntry_f(name8.Data(),12);


  //  cout<<db->GetLastValueId("CALO_geom_X",12)<<endl;
  TString name9=("CALO_geom_Yaw");
  db->GetServer()->Query("select * from CALO_geom_Yaw;");
  Float_t *angle = new Float_t[1];
  angle=db->GetEntry_f(name9.Data(),12);
  TString name10=("CALO_geom_Dist");
  db->GetServer()->Query("select * from CALO_geom_Dist;");
  Float_t *dist = new Float_t[1];
  dist=db->GetEntry_f(name10.Data(),12);


  // for(Int_t i=0;i<30;i++) {
  //   for(Int_t j=0;j<36;j++) {
  //     cout<<"x : "<<x[j+36*i] - x0[0]<<",\t y : "<<y[j+36*i] - y0[0]<<endl;
  //   }
  // }

  cout<<"distance[cm] : "<<dist[0]<<", \t angle[deg] : "<<angle[0]*TMath::RadToDeg()<<endl;


}
