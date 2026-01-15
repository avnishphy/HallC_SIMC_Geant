
void newcalo ()
{
  TDVCSDB *db=new TDVCSDB("dvcs2","localhost",3306,"root","");


Double_t nbcol=13;
Double_t nbrow=16;
Double_t nbblocks=nbcol*nbrow;

Double_t *x=new Double_t [nbblocks];
Double_t *y=new Double_t [nbblocks];
Double_t *r=new Double_t [1];
Double_t *c=new Double_t [1];
Double_t *xo=new Double_t [1];
Double_t *yo=new Double_t [1];

//for(Int_t i=0;i<nbblocks;i++)
// {
for(Int_t i=0;i<nbcol;i++)
  {
    for (Int_t j=0;j<nbrow;j++)
      {
  
	x[i*nbrow+j]=1.5+3*(Double_t)(i);
	y[i*nbrow+j]=1.5+3*(Double_t)(j);
      }
 
  }
// for (Int_t j=0;j<nbrow;j++)
// {
//   cout<<x[j+nbrow]<<" "<<y[j+nbrow]<<endl;
// }
 
 c[0]=13;
 r[0]=16;
 xo[0]=((nbcol*3)/2.)+4.5;
 yo[0]=(nbrow*3)/2.;
 db->GetServer()->Query("show tables;");
  db->AddEntry_d("CALO_geom_X",0,999999,x,"");
  db->AddEntry_d("CALO_geom_Y",0,999999,y,"");
//  db->AddEntry_d("CALO_geom_NCol",0,999999,c,"");
//  db->AddEntry_d("CALO_geom_NRow",0,999999,r,"");
 db->AddEntry_d("CALO_geom_X0",0,999999,xo,"");
// db->AddEntry_d("CALO_geom_Y0",0,999999,yo,"");

}
