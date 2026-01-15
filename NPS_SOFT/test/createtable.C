{
gSystem->Load("libDVCS.so");
//Connecting to a database in the server
TDVCSDB *db=new TDVCSDB("dvcs","clrlpc",3306,"munoz","");

//Creatinging a tables in the database
db->CreateTable("CALO_geom_NRow","int",1);
db->CreateTable("CALO_geom_NCol","int",1);
db->CreateTable("CALO_geom_X","float",132);
db->CreateTable("CALO_geom_Y","float",132);
db->CreateTable("CALO_geom_X0","float",1);
db->CreateTable("CALO_geom_Y0","float",1);



}
