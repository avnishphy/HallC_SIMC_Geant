{
TFile f("initdata/trigcosm546.dat.root");
TGDVCS *gdvcs=new TGDVCS(&f,gClient->GetRoot(), 400, 220);
gdvcs->SetCaloHistMax(128.);
}

