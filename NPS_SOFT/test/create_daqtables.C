{

//Connecting to a database in the server
gSystem.Load("../libTDVCSDB.so");
TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,"sabatie","");

//Creatinging a tables in the database
TString start,t0,t1,t2,t3,t4,t5;
char*titi;

  start="DAQ_Config";

  t0=start;
//  t0+="Param";
//  t1=start;
//  t1+="Freq";
//  t2=start;
//  t2+="Prescale";

// for (Int_t i=0;i<10;i++) {
//   t0=start;
//   t0+=i;
//   t0+="_Thres";
// //   t1+="Thres";
// //   t2+="Freq";
// //   t3+="Ped";
// //   t4+="Gain";
// //   t5+="Mode";

  titi=t0.Data();
  cout << titi << " -> 1  OK" << endl;
  db->CreateTable(titi,"varchar(32)",1);
// }
//  titi=t1.Data();
// cout << titi << " -> 1 OK" << endl;
//  db->CreateTable(titi,"int",1);

//   titi=t2.Data();
//   cout << titi << " -> 1 OK" << endl;
//   db->CreateTable(titi,"int",1);

//   titi=t3.Data();
//   cout << titi << " -> 168 OK" << endl;
//   db->CreateTable(titi,"int",168);

//   titi=t4.Data();
//   cout << titi << " -> 168 OK" << endl;
//   db->CreateTable(titi,"int",168);

//   titi=t5.Data();
//   cout << titi << " -> 1 OK" << endl;
//   db->CreateTable(titi,"int",1);



}
