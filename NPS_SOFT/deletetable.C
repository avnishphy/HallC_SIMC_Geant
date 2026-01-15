{
  //  gSystem->Load("./libDVCS.so");
  //Connecting to a database in the server
  TDVCSDB *db=new TDVCSDB("dvcs","server",3306,"user","");

  //Creatinging a tables in the database

  // db->DeleteTable("CALO_geom_NRow");
  // db->DeleteTable("CALO_geom_NCol");
  // db->DeleteTable("CALO_geom_X");
  // db->DeleteTable("CALO_geom_Y");
  // db->DeleteTable("CALO_geom_X0");
  // db->DeleteTable("CALO_geom_Y0");
  // db->DeleteTable("CALO_geom_Roll");
  // db->DeleteTable("CALO_geom_Pitch");
  // db->DeleteTable("CALO_calib_coef");
  // db->DeleteTable("CALO_geom_Yaw");
  // db->DeleteTable("CALO_geom_Dist");


  // db->DeleteTable("BEAM_param_Energy");
  // db->DeleteTable("SIMU_param_HMSmomentum");
  // db->DeleteTable("SIMU_param_HMSangle");

  // double *x = db->GetEntry_d("CALO_geom_X",0);
  // cout<<x[0]<<endl;

}
