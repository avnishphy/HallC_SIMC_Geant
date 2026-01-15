{
 gSystem->Load("libDVCS.so");
 Int_t nrun;
 char rootfile[100];
 cout << "Run number?\n";
 cin >> nrun;
 if( nrun<0 ) break;
 
	 sprintf( 
rootfile,"/adaql3/work1/adaq/onlroot/dvcs_%d.root",nrun);
TFile f(rootfile);


TGDVCS *gdvcs=new TGDVCS(&f,gClient->GetRoot(), 400, 220);
//  TGMainFrame *fMain = new TGMainFrame(gClient->GetRoot(), 500, 500);

//  //  fLbut = new TGLayoutHints(kLHintsCenterX|kLHintsCenterY, 0, 0, 25, 0);
//  fLbut2 = new TGLayoutHints(kLHintsCenterX, 0, 0, 5, 0);
//  //  fLcan = new TGLayoutHints(kLHintsCenterX|kLHintsCenterY|kLHintsExpandX|kLHintsExpandY,0,0,0,0);
//  fLhorz = new TGLayoutHints(kLHintsExpandX, 0, 0, 0, 0);
//  //  fHorz2 = new TGHorizontalFrame(fMain, 10, 10);
//  fHorz1 = new TGHorizontalFrame(fMain, 100, 100);

//  //  fHorz3 = new TGHorizontalFrame(fMain, 2000, 1000);
//  //  TRootEmbeddedCanvas *c1 = new TRootEmbeddedCanvas("Canvas1", fHorz3, 400,550);
//  //  TPad *p3=new TPad("p3","",0.01,0.01,0.99,0.99);
//  //  p3->Draw();

//  //  TRootEmbeddedCanvas *c2 = new TRootEmbeddedCanvas("Canvas2", fHorz3, 400,550);
//  //  TPad *p4=new TPad("p4","",0.01,0.01,0.99,0.99);
//  //  p4->Draw();

//  //  fHorz3->AddFrame(c1, fLcan);
//  //  fHorz3->AddFrame(c2, fLcan);

//  //  fHorz4 = new TGHorizontalFrame(fMain, 2000, 1000);
//  //  TRootEmbeddedCanvas *c3 = new TRootEmbeddedCanvas("Canvas3", fHorz4, 400,550);
//  //  TPad *p1=new TPad("p1","",0.01,0.01,0.99,0.99);
//  //  p1->Draw();

//  //  TRootEmbeddedCanvas *c4 = new TRootEmbeddedCanvas("Canvas4", fHorz4, 400,550);
//  //  TPad *p2=new TPad("p2","",0.01,0.01,0.99,0.99);
//  //  p2->Draw();

//  //  fHorz4->AddFrame(c3, fLcan);
//  //  fHorz4->AddFrame(c4, fLcan);

//  //  fConnect = new TGTextButton(fHorz2, " &Next event ");
//  //  fConnect->SetToolTipText("Shows next event");

//  //  fExit = new TGTextButton(fHorz2, " &Exit ", "gApplication->Terminate(0)");
//  //  fConnect->Connect("Clicked()", "TGDVCS", gdvcs, "ShowNext()");
//  //  fHorz2->AddFrame(fConnect, fLbut);
//  //  fHorz2->AddFrame(fExit, fLbut);

//  fMenuFile=new TGPopupMenu(gClient->GetRoot());
//  fMenuFile->AddEntry("Show &Next",1);
//  fMenuFile->AddSeparator();
//  fMenuFile->AddEntry("E&xit ROOT",0);
//  fMenuBarItemLayout=new TGLayoutHints(kLHintsTop|kLHintsLeft,0,4,0,0);
//  fMenuBar=new TGMenuBar(fMain,100,20,kHorizontalFrame);
//  fMenuBar->AddPopup("&File",fMenuFile,fMenuBarItemLayout);
//  TGHorizontal3DLine *lh=new TGHorizontal3DLine(fMain);
//  fMain->AddFrame(fMenuBar,fLhorz);
//  fMain->AddFrame(lh,new TGLayoutHints(kLHintsTop|kLHintsExpandX));
//  fMenuFile->Associate(gdvcs);

//  fMain->AddFrame(fHorz2, fLhorz);
//  fMain->AddFrame(fHorz3, fLcan);
//  fMain->AddFrame(fHorz4, fLcan);

//  Int_t parts[]={20,20,40,20};
//  fStatusBar=new TGStatusBar(fMain,50,10,kHorizontalFrame);
//  fStatusBar->SetParts(parts,4);
//  fMain->AddFrame(fStatusBar,new TGLayoutHints(kLHintsBottom | kLHintsLeft | kLHintsExpandX, 0, 0, 2, 0 ));
//  TString name("File : ");
//  name+=gdvcs->GetFile()->GetName();

//  fStatusBar->SetText(name.Data(),0);
//  gdvcs->SetStatusBar(fStatusBar);

//  fMain->MapSubwindows();
//  fMain->Resize(fMain->GetDefaultSize());
//  fMain->SetWindowName(" DVCS Online Display");
//  fMain->MapWindow();

//  gdvcs->SetPAPad(p1);
//  gdvcs->SetCaloPad(p3);
//  gdvcs->SetPAARSPad(p2);
//  gdvcs->SetCaloARSPad(p4);

//  c1->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "TGDVCS", gdvcs, "ExecuteEvent(Int_t,Int_t,Int_t,TObject*)");
//  c2->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "TGDVCS", gdvcs, "ExecuteEvent(Int_t,Int_t,Int_t,TObject*)");
//  c3->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "TGDVCS", gdvcs, "ExecuteEvent(Int_t,Int_t,Int_t,TObject*)");
//  c4->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "TGDVCS", gdvcs, "ExecuteEvent(Int_t,Int_t,Int_t,TObject*)");

}

