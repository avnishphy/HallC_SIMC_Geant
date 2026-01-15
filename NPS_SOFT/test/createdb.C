//
// Create database. Takes db parameters from initdata/mysql.conf
//

{
  ifstream mysqlconf("initdata/mysql.conf");
  TString val;
  TString connect("mysql://");
  mysqlconf>>val;
  connect+=val;
  connect+="/";
  mysqlconf>>val;
  connect+=val;
  TString user;
  mysqlconf>>user;
  TString passwd;
  mysqlconf>>passwd;
  
  TSQLServer *db = TSQLServer::Connect(connect.Data(),user.Data(),passwd.Data());


  TSQLResult *res;
  
  TString query("CREATE TABLE pedestal (channel INT, sample INT, detector ENUM('Calorimeter', 'Proton Array'), pedestal DOUBLE, sigma DOUBLE, date DATE, time TIME)");
  
  res=db->Query(query.Data());
  delete res;
  delete db;
  

}
