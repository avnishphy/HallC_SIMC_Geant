{
  //  gSystem->Load("./libDVCS.so");
  //Connecting to a database in the server
  TDVCSDB *db=new TDVCSDB("dvcs","server",3306,"user","");

  //Creatinging a tables in the database

  // db->CreateTable("CALO_geom_NRow","int",1);//"CreateTable" only once to create table. Once created, use "AddEntry" only.
  Int_t *rows=new Int_t[1]; rows[0]=36;
  // db->AddEntry_i("CALO_geom_NRow",0,999999,rows,"Pseudo Run Number");
  
  // db->CreateTable("CALO_geom_NCol","int",1);
  Int_t *columns=new Int_t[1]; columns[0]=30;
  // db->AddEntry_i("CALO_geom_NCol",0,999999,columns,"Pseudo Run Number");
  
  // X coordinates of each crystal: 1, 3, 5... cm
  // db->CreateTable("CALO_geom_X","double",1080);
  Double_t *x=new Double_t[1080];
  // for(Int_t i=0;i<1080;i++) x[i]=i/36*2+1.;
  //20191210(start)
  // for(Int_t i=0;i<1080;i++) x[i] = i/36*2.163 + 0.5*2.163;//cm //One block size : 2.05cm(crystal) + 2*65*10e-4mm(2 VM2000 wrapper thickness) + 0.1cm (carbon material)
  for(Int_t i=0;i<1080;i++) x[i] = i/36*2.113 + 0.5*2.113;//cm //One block size : 2.05cm(crystal) + 2*6.5e-3cm(2 VM2000 wrapper thickness) + 0.05cm (carbon material)
  //20191210(finish)
  // db->AddEntry_d("CALO_geom_X",0,999999,x,"Pseudo Run Number");
  
  // Y coordinates of each crystal: 1, 3, 5... cm
  // db->CreateTable("CALO_geom_Y","double",1080);
  Double_t *y=new Double_t[1080];
  // for(Int_t i=0;i<1080;i++) y[i]=i%36*2+1.;
  //20191210(start)
  // for(Int_t i=0;i<1080;i++) y[i] = i%36*2.163 + 0.5*2.163;//cm
  for(Int_t i=0;i<1080;i++) y[i] = i%36*2.113 + 0.5*2.113;//cm
  //20191210(finish)
  // db->AddEntry_d("CALO_geom_Y",0,999999,y,"Pseudo Run Number");
  
  // db->CreateTable("CALO_geom_X0","double",1);
  // Double_t *xcenter=new Double_t[1]; xcenter[0]=30.;//cm
  //20191211(start)
  // Double_t *xcenter=new Double_t[1]; xcenter[0]=32.445;//cm // x-center of 30 blocks
  Double_t *xcenter=new Double_t[1]; xcenter[0]=31.695;//cm // x-center of 30 blocks with carbon frame 0.05cm
  //20191211(finish)
  // db->AddEntry_d("CALO_geom_X0",0,999999,xcenter,"Pseudo Run Number");

  // db->CreateTable("CALO_geom_Y0","double",1);
  // Double_t *ycenter=new Double_t[1]; ycenter[0]=36.;//cm
  //20191211(start)
  // Double_t *ycenter=new Double_t[1]; ycenter[0]=38.934;//cm // y-center of 36 blocks
  Double_t *ycenter=new Double_t[1]; ycenter[0]=38.034;//cm // y-center of 36 blocks with carbon frame 0.05cm
  //20191211(finish)
  // db->AddEntry_d("CALO_geom_Y0",0,999999,ycenter,"Pseudo Run Number");

  // db->CreateTable("CALO_geom_Roll","double",1);
  Double_t *roll=new Double_t[1]; roll[0]=0.;//Ideal position
  // db->AddEntry_d("CALO_geom_Roll",0,999999,roll,"Pseudo Run Number");

  // db->CreateTable("CALO_geom_Pitch","double",1);
  Double_t *pitch=new Double_t[1]; pitch[0]=0.;//Ideal position
  // db->AddEntry_d("CALO_geom_Pitch",0,999999,pitch,"Pseudo Run Number");

  // db->CreateTable("CALO_calib_coef","double",1080);
  Double_t *coef=new Double_t[1080];
  for(Int_t i=0;i<1080;i++) coef[i]=1.;//Pseudo Run Number
  // db->AddEntry_d("CALO_calib_coef",0,999999,coef,"Pseudo Run Number");

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Variables depending on run
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////


  // db->CreateTable("CALO_geom_Yaw","double",1);
  Double_t *angle=new Double_t[1]; 
  angle[0] = 11.7*TMath::DegToRad();//11.7 deg
  // db->AddEntry_d("CALO_geom_Yaw",0,0,angle,"Pseudo Run Number");//("name", min_run_#, man_run_#, value, "description")

  angle[0] = 14.7*TMath::DegToRad();
  // db->AddEntry_d("CALO_geom_Yaw", 1, 1, angle, "Pseudo Run Number");
  angle[0] = 16.2*TMath::DegToRad();
  // db->AddEntry_d("CALO_geom_Yaw", 2, 2, angle, "Pseudo Run Number");
  angle[0] = 10.3*TMath::DegToRad();
  // db->AddEntry_d("CALO_geom_Yaw", 3, 3, angle, "Pseudo Run Number");
  angle[0] = 12.4*TMath::DegToRad();
  // db->AddEntry_d("CALO_geom_Yaw", 4, 4, angle, "Pseudo Run Number");
  angle[0] = 20.2*TMath::DegToRad();
  // db->AddEntry_d("CALO_geom_Yaw", 5, 5, angle, "Pseudo Run Number");
  angle[0] = 21.7*TMath::DegToRad();
  // db->AddEntry_d("CALO_geom_Yaw", 6, 6, angle, "Pseudo Run Number");
  angle[0] = 16.6*TMath::DegToRad();
  // db->AddEntry_d("CALO_geom_Yaw", 7, 7, angle, "Pseudo Run Number");
  angle[0] = 13.8*TMath::DegToRad();
  // db->AddEntry_d("CALO_geom_Yaw", 8, 8, angle, "Pseudo Run Number");
  angle[0] = 17.8*TMath::DegToRad();
  // db->AddEntry_d("CALO_geom_Yaw", 9, 9, angle, "Pseudo Run Number");
  angle[0] = 19.8*TMath::DegToRad();
  // db->AddEntry_d("CALO_geom_Yaw", 10, 10, angle, "Pseudo Run Number");
  angle[0] = 17.2*TMath::DegToRad();
  // db->AddEntry_d("CALO_geom_Yaw", 11, 11, angle, "Pseudo Run Number");
  angle[0] = 6.3*TMath::DegToRad();
  // db->AddEntry_d("CALO_geom_Yaw", 12, 12, angle, "Pseudo Run Number");
  angle[0] = 9.2*TMath::DegToRad();
  // db->AddEntry_d("CALO_geom_Yaw", 13, 13, angle, "Pseudo Run Number");
  angle[0] = 10.6*TMath::DegToRad();
  // db->AddEntry_d("CALO_geom_Yaw", 14, 14, angle, "Pseudo Run Number");
  angle[0] = 6.3*TMath::DegToRad();
  // db->AddEntry_d("CALO_geom_Yaw", 15, 15, angle, "Pseudo Run Number");
  angle[0] = 7.9*TMath::DegToRad();
  // db->AddEntry_d("CALO_geom_Yaw", 16, 16, angle, "Pseudo Run Number");
  angle[0] = 8.0*TMath::DegToRad();
  // db->AddEntry_d("CALO_geom_Yaw", 17, 18, angle, "Pseudo Run Number");

  //20191210(start)
  //for energy resolution simulation
  angle[0] = 0.0*TMath::DegToRad();
  // db->AddEntry_d("CALO_geom_Yaw", 19, 20, angle, "Pseudo Run Number");
  //20191210(finish)

  //20200120(start)
  //for background dose calculation with extreme setting
  angle[0] = 8.5*TMath::DegToRad();
  // db->AddEntry_d("CALO_geom_Yaw", 21, 21, angle, "Pseudo Run Number");
  angle[0] = 6.0*TMath::DegToRad();
  // db->AddEntry_d("CALO_geom_Yaw", 22, 22, angle, "Pseudo Run Number");
  //20200120(finish)

  // db->CreateTable("CALO_geom_Dist","double",1);
  Double_t *distance=new Double_t[1];
  distance[0] = 300.;//mm //3m
  // db->AddEntry_d("CALO_geom_Dist", 0, 2, distance, "Pseudo Run Number");

  distance[0] = 400.;
  // db->AddEntry_d("CALO_geom_Dist", 3, 3, distance, "Pseudo Run Number");
  distance[0] = 300.;
  // db->AddEntry_d("CALO_geom_Dist", 4, 11, distance, "Pseudo Run Number");
  distance[0] = 600.;
  // db->AddEntry_d("CALO_geom_Dist", 12, 12, distance, "Pseudo Run Number");
  distance[0] = 400.;
  // db->AddEntry_d("CALO_geom_Dist", 13, 14, distance, "Pseudo Run Number");
  distance[0] = 600.;
  // db->AddEntry_d("CALO_geom_Dist", 15, 15, distance, "Pseudo Run Number");
  distance[0] = 400.;
  // db->AddEntry_d("CALO_geom_Dist", 16, 18, distance, "Pseudo Run Number");

  //20191210(start)
  //for energy resolution simulation
  distance[0] = 300.;
  // db->AddEntry_d("CALO_geom_Dist", 19, 19, distance, "Pseudo Run Number");
  distance[0] = 400.;
  // db->AddEntry_d("CALO_geom_Dist", 20, 20, distance, "Pseudo Run Number");
  //20191210(finish)

  //20200120(start)
  //for background dose calculation with extreme setting
  distance[0] = 300.;
  // db->AddEntry_d("CALO_geom_Dist", 21, 21, distance, "Pseudo Run Number");
  distance[0] = 400.;
  // db->AddEntry_d("CALO_geom_Dist", 22, 22, distance, "Pseudo Run Number");
  //20200120(finish)

  ////////////////////////////////////////////////////////////////////////
  //SM parameters
  ////////////////////////////////////////////////////////////////////////
  // db->CreateTable("SM_geom_Yaw","double",1);//SM's angle from the calorimeter
  Double_t *SM_angle=new Double_t[1];
  SM_angle[0] = 5.5*TMath::DegToRad();
  // db->AddEntry_d("SM_geom_Yaw", 0, 11, SM_angle, "Pseudo Run Number");
  // db->AddEntry_d("SM_geom_Yaw", 13, 14, SM_angle, "Pseudo Run Number");
  // db->AddEntry_d("SM_geom_Yaw", 16, 16, SM_angle, "Pseudo Run Number");

  SM_angle[0] = 4.0*TMath::DegToRad();
  // db->AddEntry_d("SM_geom_Yaw", 12, 12, SM_angle, "Pseudo Run Number");
  // db->AddEntry_d("SM_geom_Yaw", 15, 15, SM_angle, "Pseudo Run Number");

  ////////////////////////////////////////////////////////////////////////
  //Beam parameters
  ////////////////////////////////////////////////////////////////////////

  // db->CreateTable("BEAM_param_Energy", "double",1);
  Double_t *BeamEnergy = new Double_t[1]; 
  BeamEnergy[0] = 6.6;//GeV
  // db->AddEntry_d("BEAM_param_Energy", 0, 0, BeamEnergy, "Pseudo Run Number");
  BeamEnergy[0] = 8.8;
  // db->AddEntry_d("BEAM_param_Energy", 1, 1, BeamEnergy, "Pseudo Run Number");
  BeamEnergy[0] = 11;
  // db->AddEntry_d("BEAM_param_Energy", 2, 2, BeamEnergy, "Pseudo Run Number");
  BeamEnergy[0] = 8.8;
  // db->AddEntry_d("BEAM_param_Energy", 3, 3, BeamEnergy, "Pseudo Run Number");
  BeamEnergy[0] = 11;
  // db->AddEntry_d("BEAM_param_Energy", 4, 4, BeamEnergy, "Pseudo Run Number");
  BeamEnergy[0] = 8.8;
  // db->AddEntry_d("BEAM_param_Energy", 5, 5, BeamEnergy, "Pseudo Run Number");
  BeamEnergy[0] = 11;
  // db->AddEntry_d("BEAM_param_Energy", 6, 7, BeamEnergy, "Pseudo Run Number");
  BeamEnergy[0] = 6.6;
  // db->AddEntry_d("BEAM_param_Energy", 8, 8, BeamEnergy, "Pseudo Run Number");
  BeamEnergy[0] = 8.8;
  // db->AddEntry_d("BEAM_param_Energy", 9, 9, BeamEnergy, "Pseudo Run Number");
  BeamEnergy[0] = 11;
  // db->AddEntry_d("BEAM_param_Energy", 10, 11, BeamEnergy, "Pseudo Run Number");
  BeamEnergy[0] = 6.6;
  // db->AddEntry_d("BEAM_param_Energy", 12, 12, BeamEnergy, "Pseudo Run Number");
  BeamEnergy[0] = 8.8;
  // db->AddEntry_d("BEAM_param_Energy", 13, 13, BeamEnergy, "Pseudo Run Number");
  BeamEnergy[0] = 11;
  // db->AddEntry_d("BEAM_param_Energy", 14, 18, BeamEnergy, "Pseudo Run Number");

  //20200120(start)
  //for background dose calculation with extreme setting
  //put any value, it is for background anyway
  BeamEnergy[0] = 11;
  // db->AddEntry_d("BEAM_param_Energy", 19, 22, BeamEnergy, "Pseudo Run Number");
  //20200120(finish)

  ////////////////////////////////////////////////////////////////////////
  //HMS parameters
  ////////////////////////////////////////////////////////////////////////

  // db->CreateTable("SIMU_param_HMSangle", "double",1);// for now, it is being calculated in the simulation
  Double_t *HMSangle = new Double_t[1];
  HMSangle[0] = TMath::ACos( 1 - (3.0)/(2*6.6*2.2) );//[rad]
  // db->AddEntry_d("SIMU_param_HMSangle", 0, 0, HMSangle, "Pseudo Run Number");
  HMSangle[0] = TMath::ACos( 1 - (3.0)/(2*8.8*4.4) );
  // db->AddEntry_d("SIMU_param_HMSangle", 1, 1, HMSangle, "Pseudo Run Number");
  HMSangle[0] = TMath::ACos( 1 - (3.0)/(2*11*6.6) );
  // db->AddEntry_d("SIMU_param_HMSangle", 2, 2, HMSangle, "Pseudo Run Number");
  HMSangle[0] = TMath::ACos( 1 - (4.0)/(2*8.8*2.9) );
  // db->AddEntry_d("SIMU_param_HMSangle", 3, 3, HMSangle, "Pseudo Run Number");
  HMSangle[0] = TMath::ACos( 1 - (4.0)/(2*11*5.1) );
  // db->AddEntry_d("SIMU_param_HMSangle", 4, 4, HMSangle, "Pseudo Run Number");
  HMSangle[0] = TMath::ACos( 1 - (3.4)/(2*8.8*5.2) );
  // db->AddEntry_d("SIMU_param_HMSangle", 5, 5, HMSangle, "Pseudo Run Number");
  HMSangle[0] = TMath::ACos( 1 - (3.4)/(2*11*7.4) );
  // db->AddEntry_d("SIMU_param_HMSangle", 6, 6, HMSangle, "Pseudo Run Number");
  HMSangle[0] = TMath::ACos( 1 - (4.8)/(2*11*5.9) );
  // db->AddEntry_d("SIMU_param_HMSangle", 7, 7, HMSangle, "Pseudo Run Number");
  HMSangle[0] = TMath::ACos( 1 - (5.1)/(2*6.6*2.1) );
  // db->AddEntry_d("SIMU_param_HMSangle", 8, 8, HMSangle, "Pseudo Run Number");
  HMSangle[0] = TMath::ACos( 1 - (5.1)/(2*8.8*4.3) );
  // db->AddEntry_d("SIMU_param_HMSangle", 9, 9, HMSangle, "Pseudo Run Number");
  HMSangle[0] = TMath::ACos( 1 - (5.1)/(2*11*6.5) );
  // db->AddEntry_d("SIMU_param_HMSangle", 10, 10, HMSangle, "Pseudo Run Number");
  HMSangle[0] = TMath::ACos( 1 - (6.0)/(2*11*5.7) );
  // db->AddEntry_d("SIMU_param_HMSangle", 11, 11, HMSangle, "Pseudo Run Number");
  HMSangle[0] = TMath::ACos( 1 - (2.0)/(2*6.6*1.3) );
  // db->AddEntry_d("SIMU_param_HMSangle", 12, 12, HMSangle, "Pseudo Run Number");
  HMSangle[0] = TMath::ACos( 1 - (2.0)/(2*8.8*3.5) );
  // db->AddEntry_d("SIMU_param_HMSangle", 13, 13, HMSangle, "Pseudo Run Number");
  HMSangle[0] = TMath::ACos( 1 - (2.0)/(2*11*5.7) );
  // db->AddEntry_d("SIMU_param_HMSangle", 14, 14, HMSangle, "Pseudo Run Number");
  HMSangle[0] = TMath::ACos( 1 - (3.0)/(2*11*3.0) );
  // db->AddEntry_d("SIMU_param_HMSangle", 15, 15, HMSangle, "Pseudo Run Number");
  HMSangle[0] = TMath::ACos( 1 - (5.5)/(2*11*2.9) );
  // db->AddEntry_d("SIMU_param_HMSangle", 16, 16, HMSangle, "Pseudo Run Number");
  HMSangle[0] = TMath::ACos( 1 - (8.1)/(2*11*2.4) );
  // db->AddEntry_d("SIMU_param_HMSangle", 17, 17, HMSangle, "Pseudo Run Number");
  HMSangle[0] = TMath::ACos( 1 - (10)/(2*11*2.1) );
  // db->AddEntry_d("SIMU_param_HMSangle", 18, 18, HMSangle, "Pseudo Run Number");

  //20200120(start)
  //for background dose calculation with extreme setting
  //put any value, it is for background anyway
  HMSangle[0] = TMath::ACos( 1 - (10)/(2*11*2.1) );
  // db->AddEntry_d("SIMU_param_HMSangle", 19, 22, HMSangle, "Pseudo Run Number");
  //20200120(finish)

  // db->CreateTable("SIMU_param_HMSmomentum", "double",1);
  Double_t *HMSmomentum = new Double_t[1]; 
  HMSmomentum[0] = 2.2;//GeV
  // db->AddEntry_d("SIMU_param_HMSmomentum", 0, 0, HMSmomentum, "Pseudo Run Number");
  HMSmomentum[0] = 4.4;
  // db->AddEntry_d("SIMU_param_HMSmomentum", 1, 1, HMSmomentum, "Pseudo Run Number");
  HMSmomentum[0] = 6.6;
  // db->AddEntry_d("SIMU_param_HMSmomentum", 2, 2, HMSmomentum, "Pseudo Run Number");
  HMSmomentum[0] = 2.9;
  // db->AddEntry_d("SIMU_param_HMSmomentum", 3, 3, HMSmomentum, "Pseudo Run Number");
  HMSmomentum[0] = 5.1;
  // db->AddEntry_d("SIMU_param_HMSmomentum", 4, 4, HMSmomentum, "Pseudo Run Number");
  HMSmomentum[0] = 5.2;
  // db->AddEntry_d("SIMU_param_HMSmomentum", 5, 5, HMSmomentum, "Pseudo Run Number");
  HMSmomentum[0] = 7.4;
  // db->AddEntry_d("SIMU_param_HMSmomentum", 6, 6, HMSmomentum, "Pseudo Run Number");
  HMSmomentum[0] = 5.9;
  // db->AddEntry_d("SIMU_param_HMSmomentum", 7, 7, HMSmomentum, "Pseudo Run Number");
  HMSmomentum[0] = 2.1;
  // db->AddEntry_d("SIMU_param_HMSmomentum", 8, 8, HMSmomentum, "Pseudo Run Number");
  HMSmomentum[0] = 4.3;
  // db->AddEntry_d("SIMU_param_HMSmomentum", 9, 9, HMSmomentum, "Pseudo Run Number");
  HMSmomentum[0] = 6.5;
  // db->AddEntry_d("SIMU_param_HMSmomentum", 10, 10, HMSmomentum, "Pseudo Run Number");
  HMSmomentum[0] = 5.7;
  // db->AddEntry_d("SIMU_param_HMSmomentum", 11, 11, HMSmomentum, "Pseudo Run Number");
  HMSmomentum[0] = 1.3;
  // db->AddEntry_d("SIMU_param_HMSmomentum", 12, 12, HMSmomentum, "Pseudo Run Number");
  HMSmomentum[0] = 3.5;
  // db->AddEntry_d("SIMU_param_HMSmomentum", 13, 13, HMSmomentum, "Pseudo Run Number");
  HMSmomentum[0] = 5.7;
  // db->AddEntry_d("SIMU_param_HMSmomentum", 14, 14, HMSmomentum, "Pseudo Run Number");
  HMSmomentum[0] = 3.0;
  // db->AddEntry_d("SIMU_param_HMSmomentum", 15, 15, HMSmomentum, "Pseudo Run Number");
  HMSmomentum[0] = 2.9;
  // db->AddEntry_d("SIMU_param_HMSmomentum", 16, 16, HMSmomentum, "Pseudo Run Number");
  HMSmomentum[0] = 2.4;
  // db->AddEntry_d("SIMU_param_HMSmomentum", 17, 17, HMSmomentum, "Pseudo Run Number");
  HMSmomentum[0] = 2.1;
  // db->AddEntry_d("SIMU_param_HMSmomentum", 18, 18, HMSmomentum, "Pseudo Run Number");

  //20200120(start)
  //for background dose calculation with extreme setting
  //put any value, it is for background anyway
  HMSmomentum[0] = 2.1;
  // db->AddEntry_d("SIMU_param_HMSmomentum", 19, 22, HMSmomentum, "Pseudo Run Number");
  //20200120(finish)

  Double_t *x0_test = new Double_t[1];
  Double_t *y0_test = new Double_t[1];
  x0_test = db->GetEntry_d("CALO_geom_X0", 0);
  y0_test = db->GetEntry_d("CALO_geom_Y0", 0);
  Double_t *x_test = new Double_t[1080];
  Double_t *y_test = new Double_t[1080];
  for(Int_t i = 0 ; i < 1080 ; i++){
    x_test = db->GetEntry_d("CALO_geom_X", i);
    y_test = db->GetEntry_d("CALO_geom_Y", i);
    cout<<"Block No.["<<i<<"]"<<", block pos x [cm]: "<<x_test[i]-x0_test[0]<<", block pos y [cm]: "<<y_test[i]-y0_test[0]<<endl;
  }

  // Double_t *angle_test = new Double_t[0];
  // Double_t *dist_test = new Double_t[0];
  // for(Int_t i = 0 ; i < 23 ; i++){
  //   angle_test = db->GetEntry_d("CALO_geom_Yaw", i);
  //   dist_test = db->GetEntry_d("CALO_geom_Dist", i);
  //   cout<<i<<", angle : "<<angle_test[0]*TMath::RadToDeg()<<", dist : "<<dist_test[0]<<endl;
  // }

  // Double_t *HMS_angle_test = new Double_t[0];
  // for(Int_t i = 0 ; i < 18 ; i++){
  //   HMS_angle_test = db->GetEntry_d("SIMU_param_HMSangle", i);
  //   cout<<i<<", HMS_angle : "<<HMS_angle_test[0]*TMath::RadToDeg()<<endl;
  // }

  // Double_t *center_X = new Double_t[0];
  // Double_t *center_Y = new Double_t[0];
  // for(Int_t i = 0 ; i < 21 ; i++){
  //   center_X = db->GetEntry_d("CALO_geom_X0", i);
  //   center_Y = db->GetEntry_d("CALO_geom_Y0", i);
  //   cout<<i<<", center X : "<<center_X[0]<<", center Y : "<<center_Y[0]<<endl;
  // }

  // Float_t *center_X = new Float_t[0];
  // Float_t *center_Y = new Float_t[0];
  // for(Int_t i = 0 ; i < 21 ; i++){
  //   center_X = db->GetEntry_f("CALO_geom_X0", i);
  //   center_Y = db->GetEntry_f("CALO_geom_Y0", i);
  //   cout<<i<<", center X : "<<center_X[0]<<", center Y : "<<center_Y[0]<<endl;
  // }

  Double_t *SM_angle_test = new Double_t[0];
  for(Int_t i = 0 ; i < 17 ; i++){
    SM_angle_test = db->GetEntry_d("SM_geom_Yaw", i);
    cout<<"DVCS setting No. ["<<i<<"]"<<", SM angle: "<<SM_angle_test[0]*TMath::RadToDeg()<<" deg"<<endl;
  }

}
