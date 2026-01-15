{

//Connecting to a database in the server
TDVCSDB *db=new TDVCSDB("dvcs","localhost",3306,"root");

//Creating a table in the database
db->CreateTable("example","float",132);

//Adding entries
db->AddEntry("example",0,100,"initdata/sampledata.dat","Filling from text file");
db->AddEntry("example",101,101,25,10.,"Changing on block");
db->AddEntry("example",50,200,250,30,15.,"Copying constants from one run to a run range changing one of them");

db->CopyEntry("example",215,400,500,"Copying constants from one run to a run range");

//Retreving information from tables
Float_t val=db->GetEntry_f("example",51,100);//Coefficient of block 100 in run 51
Float_t * coef=db->GetEntry_f("example",210);// Coefficients of all blocks. coef NEEDS to be deleted
db->GetEntry("example",216,"output.txt");//Writing to a file

delete coef;//Important !!

}
