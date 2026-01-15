//
// TDVCSDB.cxx, v1.0, Thu Mar  25 14:42:50
// Author: C. Munoz
//

#include "TDVCSDB.h"
#include <stdio.h>
#include <stdlib.h>
#include "/usr/include/mysql/mysql.h"

using namespace std;

ClassImp(TDVCSDB)

////////////////////////////////////////////////////////////////////////////////
//
// DVCS database class
// 
////////////////////////////////////////////////////////////////////////////////

//_____________________________________________________________________________
 TDVCSDB::TDVCSDB(const char* host, Int_t port, const char* user)
{
  TString connect="mysql://"; 
  TString shost=host;
  connect+=shost;
  connect+=":";
  connect+=port;
  fUser=user;

  ///////////////////
  //We ask user for password
  ///////////////////
  char line[100];
  int i = 0, in;
  cout<<"Type mysql password for user "<<user<<" : "<<endl;
  system("stty -echo");
  while ((in = getchar()) != '\n'){
    line[i] = (char)in;
    i++;
  }
  line[i] = '\0';
  system("stty echo");
  //////////////////
  fServer = TSQLServer::Connect(connect.Data(),fUser.Data(),line);
  
}

//_____________________________________________________________________________
 TDVCSDB::TDVCSDB(const char* db, const char* host, Int_t port, const char* user)
{
  TString connect="mysql://"; 
  TString shost=host;
  connect+=shost;
  connect+="/"; 
  TString sdb=db;
  connect+=sdb;
  fUser=user;
  ///////////////////
  //We ask user for password
  ///////////////////
  char line[100];
  int i = 0, in;
  cout<<"Type mysql password for user "<<user<<" : "<<endl;
  system("stty -echo");
  while ((in = getchar()) != '\n'){
    line[i] = (char)in;
    i++;
  }
  line[i] = '\0';
  system("stty echo");
  //////////////////
  fServer = TSQLServer::Connect(connect.Data(),fUser.Data(),line);
  
}

//_____________________________________________________________________________
 TDVCSDB::TDVCSDB(const char* db, const char* host, Int_t port, const char* user, const char* passwd)
{
  TString realhost;
  MYSQL *connection,mysql;mysql_init(&mysql);
  connection = mysql_real_connect(&mysql,"jmysql.jlab.org","dvcs","BE;3EECe","nps",3306,0,0);
  if( connection != NULL ) {
    realhost="jmysql.jlab.org";
  }else{
    connection = mysql_real_connect(&mysql,"127.0.0.1","munoz","","dvcs",3306,0,0);
    if( connection != NULL ) {
      realhost="127.0.0.1";
    }else{
    connection = mysql_real_connect(&mysql,"localhost","munoz","","dvcs",3306,0,0);
    if( connection != NULL ){
      realhost="localhost";
    }else{
      ////////////////////
      // If error, we retry up to 5 times, with 30s delay
      ////////////
      for(Int_t i=0;i<5;i++){
	cout<<"Retrying database connection "<<i<<endl;
	gSystem->Exec("sleep 30");
	connection = mysql_real_connect(&mysql,"jmysql.jlab.org","dvcs","BE;3EECe","nps",3306,0,0);
	if( connection != NULL ) {
	  realhost="jmysql.jlab.org";
	  i=5;
	}
      }
      ////////////////
      if(!connection) cout<<"ERROR : No Database server found (condider doing a ssh tunnel to clrlpc.jlab.org)."<<endl;
    }
    }
  }
  
  mysql_close(&mysql);
  mysql_close(connection);

  TString connect="mysql://"; 
  //  TString shost=host;
  connect+=realhost;
  connect+=":3306/"; 
  TString sdb=db;
  // connect+=sdb;
  // Force database to be dvcs2
  connect+="nps";
  fUser=user;
  fServer = TSQLServer::Connect(connect.Data(),"dvcs","BE;3EECe");
  if(!fServer){
    for(Int_t i=0;i<5;i++){
      cout<<"Retrying database connection "<<i<<endl;
      gSystem->Exec("sleep 30");
      fServer = TSQLServer::Connect(connect.Data(),"dvcs","BE;3EECe");
      if(fServer) i=5;
    }
  }

}

//_____________________________________________________________________________
 Int_t TDVCSDB::GetLastValueId(const char* nametable, Int_t run)
{
  //Returns the ValueId (primary key) of the last entry corresponding to run
  //'run'. If there is not such an entry it returns -1 and prints an error
  //message.

  TString sql("SELECT ValueId FROM ");sql+=nametable;
  sql+=" where minRun <= ";sql+=run;sql+=" AND maxRun >= ";sql+=run;
  sql+=" ORDER BY time DESC";
  TSQLResult *res=fServer->Query(sql);
  if(res->GetRowCount()==0) {
    cout<<"There's no entry for run: "<<run<<", returning -1"<<endl;
    return -1;
  }
  TSQLRow* row=res->Next();
  Int_t val=atof(row->GetField(0));
  delete res; delete row;
  return val;

}

//_____________________________________________________________________________
 Int_t TDVCSDB::CreateTable(const char* nametable, const char* type, Int_t number)
{
  // Comments
  
  TString query="CREATE TABLE ";
  query += nametable;
  query +=" (";
  for(Int_t i=0;i<number;i++){
    query+=nametable;
    query+="_";
    query+=i;
    query+=" ";
    query+=type;
    query+=",";
      }
  if(number>990){
    query+=" minRun INT, maxRun INT, user VARCHAR(20), time DATETIME, Comment VARCHAR (100), ValueId INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (ValueId)) engine=MyISAM;";}
  else{
  query+=" minRun INT, maxRun INT, user VARCHAR(20), time DATETIME, Comment VARCHAR (100), ValueId INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (ValueId));";
  }
  
  TSQLResult *res=fServer->Query(query.Data());
  delete res;
  
  return 1;
}

//20190410(start)
//_____________________________________________________________________________
Int_t TDVCSDB::DeleteTable(const char* nametable)
{
  TString query="DROP TABLE ";
  query += nametable;

  TSQLResult *res=fServer->Query(query.Data());
  delete res;

  return 1;
}//20190410(finish)

//_____________________________________________________________________________
Int_t TDVCSDB::CopyEntry(const char* tablename, Int_t run, Int_t runmin, Int_t runmax, const char* comment)
{
  //Copy values of run 'run' for runs between 'runmin' and 'runmax'

  TString sql("select max(ValueId) AS ValueId FROM ");sql+=tablename;
  TSQLResult *res1=fServer->Query(sql);
  TSQLRow* row1=res1->Next();
  Int_t last=atof(row1->GetField(0));

  TString sql2("select * from ");sql2+=tablename;
  sql2+=" where ValueId=";sql2+=GetLastValueId(tablename,run);
  TSQLResult *res2=fServer->Query(sql2);
  Int_t ncol=res2->GetFieldCount();
  TSQLRow *row2=res2->Next();
  TString query("INSERT INTO ");query+=tablename;query+=" VALUES (";
  for(Int_t i=0;i<ncol-6;i++){
    query+=atof(row2->GetField(i));
    query+=",";
  }
  query+=" ";query+=runmin;query+=", ";query+=runmax;query+=", '";query+=fUser;query+="' , NOW(), '";
  TString scomment=comment; query+=scomment.Data();query+="',";query+=last+1;query+=")";
  TSQLResult *res3=fServer->Query(query);
  
  delete row1;delete row2;
  delete res1;delete res2;delete res3;

}

//_____________________________________________________________________________
Int_t TDVCSDB::AddEntry(const char* tablename, Int_t runmin, Int_t runmax, Int_t col, Double_t val, const char* comment)
{
  //    It adds an entry to table 'tablename' with value 'val' to column 'col'.
  // Values for other columns are copied from the precedent entry. This method
  // is to be use when only a parameter of a block is changed.
  //


  TSQLResult *res1=0;
  TSQLRow *row1=0;
  TString sql0=("SELECT COUNT(*) FROM ");sql0+=tablename;
  TSQLResult *res0=fServer->Query(sql0);
  TSQLRow *row0=res0->Next();
  Int_t nbofrows=atof(row0->GetField(0));
  Int_t last;
  if(nbofrows>0){
    TString sql("select max(ValueId) AS ValueId FROM ");sql+=tablename;
    res1=fServer->Query(sql);
    row1=res1->Next();
    last=atof(row1->GetField(0));
  }else{
    last=-1;
  }

  if(last==-1){
    cout<<"Error: This is the fist entry of the table. You can't use this method"<<endl;
    cout<<"Read data from a file for the first entry"<<endl;
  }
  
  TString sql2("select * from ");sql2+=tablename;
  sql2+=" where ValueId=";sql2+=last;
  TSQLResult *res2=fServer->Query(sql2);
  Int_t ncol=res2->GetFieldCount();
  TSQLRow *row2=res2->Next();
  TSQLResult *res3;
  TString query("INSERT INTO ");query+=tablename;query+=" VALUES (";
  for(Int_t i=0;i<ncol-6;i++){
    if(i==col){
      query+=val;
    }else{
      query+=atof(row2->GetField(i));
    }
    query+=",";
  }
  query+=" ";query+=runmin;query+=", ";query+=runmax;query+=", '";query+=fUser;query+="' , NOW(), '";
  TString scomment=comment; query+=scomment.Data();query+="',";query+=last+1;query+=")";
  res3=fServer->Query(query);
  
  if(row1) delete row1;delete row2;
  if(res1) delete res1;delete res2;delete res3;
  
}
//_____________________________________________________________________________
Int_t TDVCSDB::AddOneEntry(const char* tablename, Int_t runmin, Int_t runmax, Double_t val, const char* comment)
{
  //    It adds an entry to one-column table 'tablename' with value 'val'.

  TSQLResult *res1=0;
  TSQLRow *row1=0;
  TString sql0=("SELECT COUNT(*) FROM ");sql0+=tablename;
  TSQLResult *res0=fServer->Query(sql0);
  TSQLRow *row0=res0->Next();
  Int_t nbofrows=atof(row0->GetField(0));
  Int_t last;
  if(nbofrows>0){
    TString sql("select max(ValueId) AS ValueId FROM ");sql+=tablename;
    res1=fServer->Query(sql);
    row1=res1->Next();
    last=atof(row1->GetField(0));
  }else{
    last=-1;
  }
  
  TString sql2("select * from ");sql2+=tablename;
  sql2+=" where ValueId=";sql2+=last;
  TSQLResult *res2=fServer->Query(sql2);
  Int_t ncol=res2->GetFieldCount();

  TString query("INSERT INTO ");query+=tablename;query+=" VALUES (";
  for(Int_t i=0;i<ncol-6;i++){
    query+=val;
    query+=",";
  }
  query+=" ";query+=runmin;query+=" ,";query+=runmax;query+=", '";query+=fUser;query+="' , NOW(), '";
  TString scomment=comment; query+=scomment.Data();query+="',";query+=last+1;query+=")";
  TSQLResult *res3=fServer->Query(query);
  
  if(row1) delete row1;delete row0;
  if(res1) delete res1;delete res2;delete res3;delete res0;

}

//_____________________________________________________________________________
Int_t TDVCSDB::AddEntry(const char* tablename, Int_t run, Int_t runmin, Int_t runmax, Int_t col, Double_t val,const char* comment)
{
  //    It adds an entry to table 'tablename' with value 'val' to column 'col'.
  // Values for other columns are copied from run 'run'. This method
  // is to be use when only a parameter of a block is changed.
  //


  TSQLResult *res1=0;
  TSQLRow *row1=0;
  TString sql0=("SELECT COUNT(*) FROM ");sql0+=tablename;
  TSQLResult *res0=fServer->Query(sql0);
  TSQLRow *row0=res0->Next();
  Int_t nbofrows=atof(row0->GetField(0));
  Int_t last;
  if(nbofrows>0){
    TString sql("select max(ValueId) AS ValueId FROM ");sql+=tablename;
    res1=fServer->Query(sql);
    row1=res1->Next();
    last=atof(row1->GetField(0));
  }else{
    last=-1;
  }

  if(last==-1){
    cout<<"Error: This is the fist entry of the table. You can't use this method"<<endl;
    cout<<"Read data from a file for the first entry"<<endl;
  }
  
  TString sql2("select * from ");sql2+=tablename;
  sql2+=" where ValueId=";sql2+=GetLastValueId(tablename,run);
  TSQLResult *res2=fServer->Query(sql2);
  Int_t ncol=res2->GetFieldCount();
  TSQLRow *row2=res2->Next();
  TSQLResult *res3;
  TString query("INSERT INTO ");query+=tablename;query+=" VALUES (";
  for(Int_t i=0;i<ncol-6;i++){
    if(i==col){
      query+=val;
    }else{
      query+=atof(row2->GetField(i));
    }
    query+=",";
  }
  query+=" ";query+=runmin;query+=", ";query+=runmax;query+=", '";query+=fUser;query+="' , NOW(), '";
  TString scomment=comment; query+=scomment.Data();query+="',";query+=last+1;query+=")";
  res3=fServer->Query(query);
  
  if(row1) delete row1;delete row2;
  if(res1) delete res1;delete res2;delete res3;
  
}

//_____________________________________________________________________________
Int_t TDVCSDB::AddEntry(const char* tablename, Int_t runmin, Int_t runmax, const char* filename, const char* comment)
{
  //    It adds an entry to table 'tablename' reading values from 'filename;
  //
  
  TSQLResult *res1=0;
  TSQLRow *row1=0;
  TString sql0=("SELECT COUNT(*) FROM ");sql0+=tablename;
  TSQLResult *res0=fServer->Query(sql0);
  TSQLRow *row0=res0->Next();
  Int_t nbofrows=atof(row0->GetField(0));
  Int_t last;
  if(nbofrows>0){
    TString sql("select max(ValueId) AS ValueId FROM ");sql+=tablename;
    res1=fServer->Query(sql);
    row1=res1->Next();
    last=atof(row1->GetField(0));
  }else{
    last=-1;
  }
  
  TString file=filename;
  ifstream f(file.Data());

  TString sql2("select * from ");sql2+=tablename;
  sql2+=" where ValueId=";sql2+=last;
  TSQLResult *res2=fServer->Query(sql2);
  Int_t ncol=res2->GetFieldCount();

  TString query("INSERT INTO ");query+=tablename;query+=" VALUES (";
  for(Int_t i=0;i<ncol-6;i++){
    Double_t val;
    f>>val;
    query+=val;
    query+=",";
  }
  query+=" ";query+=runmin;query+=" ,";query+=runmax;query+=", '";query+=fUser;query+="' , NOW(), '";
  TString scomment=comment; query+=scomment.Data();query+="',";query+=last+1;query+=")";
  TSQLResult *res3=fServer->Query(query);
  
  if(row1) delete row1;delete row0;
  if(res1) delete res1;delete res2;delete res3;delete res0;
  
}

//_____________________________________________________________________________
void TDVCSDB::AddEntry_f(const char* tablename, Int_t runmin, Int_t runmax, Float_t * val, const char* comment)
{
  //    It adds an entry to table 'tablename' reading values from 'filename;
  //
  
  TSQLResult *res1=0;
  TSQLRow *row1=0;
  TString sql0=("SELECT COUNT(*) FROM ");sql0+=tablename;
  TSQLResult *res0=fServer->Query(sql0);
  TSQLRow *row0=res0->Next();
  Int_t nbofrows=atof(row0->GetField(0));
  Int_t last;
  if(nbofrows>0){
    TString sql("select max(ValueId) AS ValueId FROM ");sql+=tablename;
    res1=fServer->Query(sql);
    row1=res1->Next();
    last=atof(row1->GetField(0));
  }else{
    last=-1;
  }

  TString sql2("select * from ");sql2+=tablename;
  sql2+=" where ValueId=";sql2+=last;
  TSQLResult *res2=fServer->Query(sql2);
  Int_t ncol=res2->GetFieldCount();

  TString query("INSERT INTO ");query+=tablename;query+=" VALUES (";
  for(Int_t i=0;i<ncol-6;i++){
    Float_t valt=val[i];
    query+=valt;
    query+=",";
  }
  query+=" ";query+=runmin;query+=" ,";query+=runmax;query+=", '";query+=fUser;query+="' , NOW(), '";
  TString scomment=comment; query+=scomment.Data();query+="',";query+=last+1;query+=")";
  TSQLResult *res3=fServer->Query(query);
  
  if(row1) delete row1;delete row0;
  if(res1) delete res1;delete res2;delete res3;delete res0;
  
}
//_____________________________________________________________________________
void TDVCSDB::AddEntry_i(const char* tablename, Int_t runmin, Int_t runmax, Int_t * val, const char* comment)
{
  //    It adds an entry to table 'tablename' reading values from 'filename;
  //
  
  TSQLResult *res1=0;
  TSQLRow *row1=0;
  TString sql0=("SELECT COUNT(*) FROM ");sql0+=tablename;
  TSQLResult *res0=fServer->Query(sql0);
  TSQLRow *row0=res0->Next();
  Int_t nbofrows=atof(row0->GetField(0));
  Int_t last;
  if(nbofrows>0){
    TString sql("select max(ValueId) AS ValueId FROM ");sql+=tablename;
    res1=fServer->Query(sql);
    row1=res1->Next();
    last=atof(row1->GetField(0));
  }else{
    last=-1;
  }

  TString sql2("select * from ");sql2+=tablename;
  sql2+=" where ValueId=";sql2+=last;
  TSQLResult *res2=fServer->Query(sql2);
  Int_t ncol=res2->GetFieldCount();

  TString query("INSERT INTO ");query+=tablename;query+=" VALUES (";
  for(Int_t i=0;i<ncol-6;i++){
    Int_t valt=val[i];
    query+=valt;
    query+=",";
  }
  query+=" ";query+=runmin;query+=" ,";query+=runmax;query+=", '";query+=fUser;query+="' , NOW(), '";
  TString scomment=comment; query+=scomment.Data();query+="',";query+=last+1;query+=")";
  TSQLResult *res3=fServer->Query(query);
  
  if(row1) delete row1;delete row0;
  if(res1) delete res1;delete res2;delete res3;delete res0;
  
}
//_____________________________________________________________________________
void TDVCSDB::AddEntry_d(const char* tablename, Int_t runmin, Int_t runmax, Double_t * val, const char* comment)
{
  //    It adds an entry to table 'tablename' reading values from 'filename;
  //
  
  TSQLResult *res1=0;
  TSQLRow *row1=0;
  TString sql0=("SELECT COUNT(*) FROM ");sql0+=tablename;
  TSQLResult *res0=fServer->Query(sql0);
  TSQLRow *row0=res0->Next();
  Int_t nbofrows=atof(row0->GetField(0));
  Int_t last;
  if(nbofrows>0){
    TString sql("select max(ValueId) AS ValueId FROM ");sql+=tablename;
    res1=fServer->Query(sql);
    row1=res1->Next();
    last=atof(row1->GetField(0));
  }else{
    last=-1;
  }

  TString sql2("select * from ");sql2+=tablename;
  sql2+=" where ValueId=";sql2+=last;
  TSQLResult *res2=fServer->Query(sql2);
  Int_t ncol=res2->GetFieldCount();

  TString query("INSERT INTO ");query+=tablename;query+=" VALUES (";
  for(Int_t i=0;i<ncol-6;i++){
    Double_t valt=val[i];
    query+=valt;
    query+=",";
  }
  query+=" ";query+=runmin;query+=" ,";query+=runmax;query+=", '";query+=fUser;query+="' , NOW(), '";
  TString scomment=comment; query+=scomment.Data();query+="',";query+=last+1;query+=")";
  TSQLResult *res3=fServer->Query(query);
  
  if(row1) delete row1;delete row0;
  if(res1) delete res1;delete res2;delete res3;delete res0;
  
}

//_____________________________________________________________________________
void TDVCSDB::AddEntry_s(const char* tablename, Int_t runmin, Int_t runmax, const char** val, const char* comment)
{
  TSQLResult *res1 = 0;
  TSQLRow    *row1 = 0;

  // count rows
  TString sql0 = "SELECT COUNT(*) FROM ";
  sql0 += tablename;
  TSQLResult *res0 = fServer->Query(sql0);
  TSQLRow *row0 = res0->Next();
  Int_t nbofrows = atoi(row0->GetField(0));

  Int_t last;
  if(nbofrows > 0){
    TString sql = "SELECT MAX(ValueId) AS ValueId FROM ";
    sql += tablename;
    res1 = fServer->Query(sql);
    row1 = res1->Next();
    last = atoi(row1->GetField(0));
  } else {
    last = -1;
  }

  // get number of columns
  TString sql2 = "SELECT * FROM ";
  sql2 += tablename;
  sql2 += " WHERE ValueId=";
  sql2 += last;
  TSQLResult *res2 = fServer->Query(sql2);
  Int_t ncol = res2->GetFieldCount();

  // build INSERT query
  TString query = "INSERT INTO ";
  query += tablename;
  query += " VALUES (";

  // string values
  for(Int_t i = 0; i < ncol-6; i++){
    query += "'";
    query += val[i];
    query += "',";
  }

  // metadata
  query += runmin;
  query += ",";
  query += runmax;
  query += ",'";
  query += fUser;
  query += "',NOW(),'";
  query += comment;
  query += "',";
  query += last + 1;
  query += ")";

  TSQLResult *res3 = fServer->Query(query);

  // cleanup
  if(row1) delete row1;
  delete row0;
  if(res1) delete res1;
  delete res2;
  delete res3;
  delete res0;
}

//_____________________________________________________________________________
  void TDVCSDB::GetEntry(const char* tablename, Int_t run, const char* filename){

  ofstream f(filename);
  TString sql("SELECT * FROM ");
  sql+=tablename;sql+=" WHERE ValueId = ";sql+=GetLastValueId(tablename,run);
  TSQLResult *res=fServer->Query(sql);
  Int_t col=res->GetFieldCount();
  TSQLRow *row=res->Next();
  for(Int_t i=0;i<col-6;i++){
    Double_t val=atof(row->GetField(i));
    f<<val<<endl;
  }
  delete res; delete row;

}

//_____________________________________________________________________________
  Float_t* TDVCSDB::GetEntry_f(const char* tablename, Int_t run)
{
  // Returns the whole entry as an array.
  //
  //Warning : This method allocates dynamically a new array in memory.
  //YOU'RE RESPONSIBLE of deleting this array when you don't need it anymore
  //

  TString sql("SELECT * FROM ");
  sql+=tablename;sql+=" WHERE ValueId = ";sql+=GetLastValueId(tablename,run);
  TSQLResult *res=fServer->Query(sql);
  Int_t col=res->GetFieldCount();
  Float_t *val=new Float_t[col-6];
  TSQLRow *row=res->Next();
  for(Int_t i=0;i<col-6;i++){
    if(row->GetFieldLength(i)) val[i]=atof(row->GetField(i));
  }
  delete res; delete row;
  return val;

}
//_____________________________________________________________________________
  Double_t* TDVCSDB::GetEntry_d(const char* tablename, Int_t run)
{
  // Returns the whole entry as an array.
  //
  //Warning : This method allocates dynamically a new array in memory.
  //YOU'RE RESPONSIBLE of deleting this array when you don't need it anymore
  //

  TString sql("SELECT * FROM ");
  sql+=tablename;sql+=" WHERE ValueId = ";sql+=GetLastValueId(tablename,run);
  TSQLResult *res=fServer->Query(sql);
  Int_t col=res->GetFieldCount();
  Double_t *val=new Double_t[col-6];
  TSQLRow *row=res->Next();
  for(Int_t i=0;i<col-6;i++){
    if(row->GetFieldLength(i)) val[i]=atof(row->GetField(i));
  }
  delete res; delete row;
  return val;
}
//_____________________________________________________________________________
  Int_t* TDVCSDB::GetEntry_i(const char* tablename, Int_t run)
{
  // Returns the whole entry as an array.
  //
  //Warning : This method allocates dynamically a new array in memory.
  //YOU'RE RESPONSIBLE of deleting this array when you don't need it anymore
  //

  TString sql("SELECT * FROM ");
  sql+=tablename;sql+=" WHERE ValueId = ";sql+=GetLastValueId(tablename,run);
  TSQLResult *res=fServer->Query(sql);
  Int_t col=res->GetFieldCount();
  Int_t *val=new Int_t[col-6];
  TSQLRow *row=res->Next();
  for(Int_t i=0;i<col-6;i++){
    if(row->GetFieldLength(i)) val[i]=atof(row->GetField(i));
  }
  delete res; delete row;
  return val;
}

//_____________________________________________________________________________
const char** TDVCSDB::GetEntry_s(const char* tablename, Int_t run)
{
  // Returns the whole entry as an array.
  //
  //Warning : This method allocates dynamically a new array in memory.
  //YOU'RE RESPONSIBLE of deleting this array when you don't need it anymore
  //

  TString sql("SELECT * FROM ");
  sql+=tablename;sql+=" WHERE ValueId = ";
  sql+=GetLastValueId(tablename,run);
  TSQLResult *res=fServer->Query(sql);
  Int_t col=res->GetFieldCount();
  const char** val = new const char*[col-6];
  TSQLRow *row=res->Next();
  for(Int_t i=0;i<col-6;i++){
    if(row->GetFieldLength(i)) val[i]=strdup(row->GetField(i));
  }
  delete res; delete row;
  return val;
}

//_____________________________________________________________________________
  Double_t TDVCSDB::GetEntry_d(const char* tablename, Int_t run, Int_t col)
{
  //  It returns the last entry of the column 'col' for run 'run' in the table
  //'tablename'.

  TString sql("SELECT ");sql+=tablename;sql+="_";sql+=col;sql+=" FROM ";
  sql+=tablename;sql+=" WHERE ValueId = ";sql+=GetLastValueId(tablename,run);
  TSQLResult *res=fServer->Query(sql);
  TSQLRow *row=res->Next();
  Double_t val=atof(row->GetField(0));
  delete res; delete row;
  return val;
}
//_____________________________________________________________________________
  Float_t TDVCSDB::GetEntry_f(const char* tablename, Int_t run, Int_t col)
{
  //  It returns the last entry of the column 'col' for run 'run' in the table
  //'tablename'.

  TString sql("SELECT ");sql+=tablename;sql+="_";sql+=col;sql+=" FROM ";
  sql+=tablename;sql+=" WHERE ValueId = ";sql+=GetLastValueId(tablename,run);
  TSQLResult *res=fServer->Query(sql);
  TSQLRow *row=res->Next();
  Float_t val=atof(row->GetField(0));
  delete res; delete row;
  return val;
}
//_____________________________________________________________________________
 Int_t TDVCSDB::GetEntry_i(const char* tablename, Int_t run, Int_t col)
{
  //  It returns the last entry of the column 'col' for run 'run' in the table
  //'tablename'.

  TString sql("SELECT ");sql+=tablename;sql+="_";sql+=col;sql+=" FROM ";
  sql+=tablename;sql+=" WHERE ValueId = ";sql+=GetLastValueId(tablename,run);
  TSQLResult *res=fServer->Query(sql);
  TSQLRow *row=res->Next();
  Int_t val=atof(row->GetField(0));
  delete res; delete row;
  return val;
}
//_____________________________________________________________________________
  TString TDVCSDB::GetEntry_c(const char* tablename, Int_t run, Int_t col)
{
  //  It returns the last entry of the column 'col' for run 'run' in the table
  //'tablename'.

  TString sql("SELECT ");sql+=tablename;sql+="_";sql+=col;sql+=" FROM ";
  sql+=tablename;sql+=" WHERE ValueId = ";sql+=GetLastValueId(tablename,run);
  TSQLResult *res=fServer->Query(sql);
  TSQLRow *row=res->Next();
  TString val=row->GetField(0);
  delete res; delete row;
  return val;
}

//_____________________________________________________________________________
 TDVCSDB::TDVCSDB(const TDVCSDB& block)
{
  // Copy constructor

}

//_____________________________________________________________________________
 void TDVCSDB::AddNewShift(const char* date, const char* shift, const char* job)
{
  // Adds a new slot
  TString query("INSERT INTO latestshifts VALUES ('");
  query+=date;query+="',NULL,NULL,'";
  query+=job;query+="','";query+=shift;query+="', NOW())";
  TSQLResult *res=fServer->Query(query);
  delete res;

}

//_____________________________________________________________________________
 void TDVCSDB::ClearLatest(const char* date, const char* shift, const char* job)
{
  // Clears a shift in the latestshifts table
  TString query("UPDATE latestshifts SET username=NULL, name=NULL, job='");
  query+=job;query+="',shift='";query+=shift;query+="',time=NOW() where (date='";
  query+=date;query+="'and shift='";query+=shift;query+="'and job='";query+=job;query+="')";
  TSQLResult *res=fServer->Query(query);
  delete res;

}

//_____________________________________________________________________________
 void TDVCSDB::UpdateLatest(const char* name, const char* username, const char* date, const char* shift, const char* job)
{
  // Updates the latestshift table
  TString query("UPDATE latestshifts SET username='");
  query+=username;query+="',name='";query+=name;
  query+="',job='";query+=job;query+="',shift='";query+=shift;query+="',time=NOW() where (date='";
  query+=date;query+="'and shift='";query+=shift;query+="'and job='";query+=job;query+="')";
  TSQLResult *res=fServer->Query(query);
  delete res;


}

//_____________________________________________________________________________
 void TDVCSDB::AddShift(const char* name, char * username, const char* date, const char* shift, const char* job)
{
  // Assocites someone to a shift slot
  TSQLResult *res1=0;
  TSQLRow *row1=0;
  TString sql0=("SELECT COUNT(*) FROM shifts");
  TSQLResult *res0=fServer->Query(sql0);
  TSQLRow *row0=res0->Next();
  Int_t nbofrows=atof(row0->GetField(0));
  Int_t last;

  if(nbofrows>0){
    TString sql("select max(ValueId) AS ValueId FROM shifts");
    res1=fServer->Query(sql);
    row1=res1->Next();
    last=atof(row1->GetField(0));
  }else{
    last=-1;
  }
  TString query("INSERT INTO shifts VALUES ('");
  query+=date;query+="','";query+=username;query+="','";query+=name;
  query+="','";query+=job;query+="','";query+=shift;query+="', NOW(),";
  query+="'Automatic entry',";query+=last+1;query+=")";
  TSQLResult *res3=fServer->Query(query);

  UpdateLatest(name, username, date, shift, job);

  if(row1) delete row1;delete row0;
  if(res1) delete res1;delete res3;delete res0;
  
}

//_____________________________________________________________________________
 void TDVCSDB::ClearShift(const char* date, const char* shift, const char* job)
{
  // Makes a shift slot available again
  TSQLResult *res1=0;
  TSQLRow *row1=0;
  TString sql0=("SELECT COUNT(*) FROM shifts");
  TSQLResult *res0=fServer->Query(sql0);
  TSQLRow *row0=res0->Next();
  Int_t nbofrows=atof(row0->GetField(0));
  Int_t last;

  if(nbofrows>0){
    TString sql("select max(ValueId) AS ValueId FROM shifts");
    res1=fServer->Query(sql);
    row1=res1->Next();
    last=atof(row1->GetField(0));
  }else{
    last=-1;
  }
  TString query("INSERT INTO shifts VALUES ('");
  query+=date;query+="',NULL,NULL,'";query+=job;query+="','";query+=shift;query+="', NOW(),";
  query+="'Automatic entry',";query+=last+1;query+=")";
  TSQLResult *res3=fServer->Query(query);

  ClearLatest(date, shift, job);

  if(row1) delete row1;delete row0;
  if(res1) delete res1;delete res3;delete res0;
  
}

//_____________________________________________________________________________
 TDVCSDB::~TDVCSDB()
{
  // Default destructor
  delete fServer;
}












