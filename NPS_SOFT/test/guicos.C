{
//  TRint rint("ro",0,0);

//TFile f("../initdata/trigcosm.546.dat.root");
TFile f("/home/cmunoz/local/cvs/dvcs/soft/initdata/trigcosm546.dat.root");
TGCalo *gcalo=new TGCalo(&f);

TGMainFrame *fMain = new TGMainFrame(gClient->GetRoot(), 500, 500);
//TRootEmbeddedCanvas *c = new TRootEmbeddedCanvas("Canvas", fMain, 400, 400);
//TRootEmbeddedCanvas *c = new TRootEmbeddedCanvas("Canvas", fMain, 600,550);

fLbut = new TGLayoutHints(kLHintsCenterX, 0, 0, 25, 0);
fLbut2 = new TGLayoutHints(kLHintsCenterX, 0, 0, 5, 0);
fLcan = new TGLayoutHints(kLHintsCenterX|kLHintsCenterY|kLHintsExpandX|kLHintsExpandY,0,0,0,0);
fLhorz = new TGLayoutHints(kLHintsExpandX, 0, 0, 0, 0);
fHorz2 = new TGHorizontalFrame(fMain, 10, 10);
fHorz1 = new TGHorizontalFrame(fMain, 100, 100);
//  fHorz3 = new TGHorizontalFrame(fMain, 2000, 1000);


fHorz3 = new TGHorizontalFrame(fMain, 2000, 1000);
TRootEmbeddedCanvas *c1 = new TRootEmbeddedCanvas("Canvas1", fHorz3, 400,550);
TPad *p3=new TPad("p3","",0.01,0.01,0.99,0.79);
p3->Draw();
TPad *caloinfo=new TPad("painfo","",0.01,0.81,0.99,0.99);
caloinfo->Draw();

TRootEmbeddedCanvas *c2 = new TRootEmbeddedCanvas("Canvas2", fHorz3, 400,550);
TPad *p4b=new TPad("p4b","",0.01,0.81,0.99,0.99);
TPad *p4=new TPad("p4","",0.01,0.01,0.99,0.79);
p4->Draw();
p4b->Draw();

fHorz3->AddFrame(c1, fLcan);
fHorz3->AddFrame(c2, fLcan);

fHorz4 = new TGHorizontalFrame(fMain, 2000, 1000);
TRootEmbeddedCanvas *c3 = new TRootEmbeddedCanvas("Canvas3", fHorz4, 400,550);
TPad *p1=new TPad("p1","",0.01,0.01,0.99,0.79);
p1->Draw();
TPad *painfo=new TPad("painfo","",0.01,0.81,0.99,0.99);
painfo->Draw();

TRootEmbeddedCanvas *c4 = new TRootEmbeddedCanvas("Canvas4", fHorz4, 400,550);
TPad *p2=new TPad("p2","",0.01,0.01,0.99,0.99);
p2->Draw();

fHorz4->AddFrame(c3, fLcan);
fHorz4->AddFrame(c4, fLcan);


TString titletmp="File : ";
TString evnb="Event Number : ";
titletmp+=f->GetName();
evnb+=gcalo->GetEventNumber();
TGString title(titletmp);
TGString evnumber(evnb);
Titre=new TGLabel(fMain,&title);
Number=new TGLabel(fMain,&evnumber);

//  fMain->AddFrame(fHorz2, fLhorz);
//  fMain->AddFrame(fHorz1, fLhorz);
//  fMain->AddFrame(fHorz3, fLhorz);
fConnect = new TGTextButton(fHorz2, " Next event ");
fConnect->Connect("Clicked()", "TGCalo", gcalo, "ShowNext()");
fHorz2->AddFrame(fConnect, fLbut);
//  fHorz3->AddFrame(c1, fLbut);
//  fHorz3->AddFrame(c2, fLbut);
fHorz1->AddFrame(Titre,fLbut2);
fHorz1->AddFrame(Number,fLbut2);

fMain->AddFrame(fHorz2, fLhorz);
fMain->AddFrame(fHorz1, fLhorz);
fMain->AddFrame(fHorz3, fLcan);
fMain->AddFrame(fHorz4, fLcan);

//fMain->AddFrame(c, fLcan);
fMain->MapSubwindows();
fMain->Resize(fMain->GetDefaultSize());
fMain->SetWindowName("DVCS Online Display");
fMain->MapWindow();



//p1->Draw();p2->Draw();p3->Draw();p4->Draw();p5->Draw();
//  painfo->Draw();
//  caloinfo->Draw();

gcalo->SetPAPad(p1);
gcalo->SetCaloPad(p3);
gcalo->SetCaloPadInfo(caloinfo);
gcalo->SetPAARSPad(p2);
gcalo->SetCaloARSPad(p4);
//gcalo->SetControlPad(p5);
gcalo->SetPAPadInfo(painfo);
gcalo->SetCaloARSPadInfo(p4b);

c1->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "TGCalo", gcalo, "ExecuteEvent(Int_t,Int_t,Int_t,TObject*)");
c2->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "TGCalo", gcalo, "ExecuteEvent(Int_t,Int_t,Int_t,TObject*)");
c3->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "TGCalo", gcalo, "ExecuteEvent(Int_t,Int_t,Int_t,TObject*)");
c4->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "TGCalo", gcalo, "ExecuteEvent(Int_t,Int_t,Int_t,TObject*)");


}

