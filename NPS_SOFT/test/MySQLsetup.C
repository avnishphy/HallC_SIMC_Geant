{
TDVCSDB *db=new TDVCSDB("mysql","localhost",3306,"root");

db->GetServer()->Query("CREATE DATABASE dvcs");

db->GetServer()->Query("GRANT ALL PRIVILEGES ON dvcs TO cmunoz@'%'");
db->GetServer()->Query("GRANT ALL PRIVILEGES ON dvcs TO munoz@'%'");
db->GetServer()->Query("GRANT ALL PRIVILEGES ON dvcs TO camsonne@'%'");
db->GetServer()->Query("GRANT ALL PRIVILEGES ON dvcs TO fsabatie@'%'");
db->GetServer()->Query("GRANT ALL PRIVILEGES ON dvcs TO sabatie@'%'");
db->GetServer()->Query("GRANT ALL PRIVILEGES ON dvcs TO bertin@'%'");
db->GetServer()->Query("GRANT ALL PRIVILEGES ON dvcs TO ferdi@'%'");
db->GetServer()->Query("GRANT ALL PRIVILEGES ON dvcs TO cmunoz@'localhost'");
db->GetServer()->Query("GRANT ALL PRIVILEGES ON dvcs TO munoz@'localhost'");
db->GetServer()->Query("GRANT ALL PRIVILEGES ON dvcs TO camsonne@'localhost'");
db->GetServer()->Query("GRANT ALL PRIVILEGES ON dvcs TO fsabatie@'localhost'");
db->GetServer()->Query("GRANT ALL PRIVILEGES ON dvcs TO sabatie@'localhost'");
db->GetServer()->Query("GRANT ALL PRIVILEGES ON dvcs TO bertin@'localhost'");
db->GetServer()->Query("GRANT ALL PRIVILEGES ON dvcs TO ferdi@'localhost'");

db->GetServer()->Query("FLUSH PRIVILEGES");

}
