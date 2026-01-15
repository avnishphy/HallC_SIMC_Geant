/////////////////////////////////////////////////////////////////////////////
//
// Just a macro to plot results from PAgrid_ana.C
//
/////////////////////////////////////////////////////////////////////////////

{
Int_t n=9;
// Double_t blocks[n]={14472.7,11827.3,9972.73,8381.82,7154.55,6172.73,5236.36,4472.73,3754.55};
// Double_t realblocks[n]={17.866,15.4,13.518,11.885,10.446,9.421,8.304,7.337,6.385};
// Double_t eff[n]={0.998261,0.996522,0.996522,0.984348,0.972174,0.958261,0.935652,0.893913,0.838261};

// 10.000 ev
// Double_t eff[n]={0.998937,0.998582,0.997164,0.989897,0.979617,0.965083,0.935838,0.897554,0.83995};
// Double_t blocks[n]={144727,118273,99727.3,83818.2,71545.5,61727.3,52363.6,44727.3,37545.5};
// Double_t realblocks[n]={17.6944,15.2223,13.411,11.7784,10.4225,9.3913,8.2543,7.2733,6.2726};
///

//100.000 ev
Double_t eff[n]={0.998968,0.998026,0.995731,0.98915,0.97942,0.962735,0.922802,0.867483,0.825166};
Double_t blocks[n]={1.50091e+06,1.20545e+06,1.02636e+06,849091,720000,610000,513636,426364,364545};
Double_t realblocks[n]={18.2911,15.4151,13.7647,11.9055,10.5237,9.24855,8.00096,6.83258,6.00634};

// Double_t blocks[n]={1,2,3,4,5,6,7,8,9};
// Double_t realblocks[n]={1,2,3,4,5,6,7,8,9};
// Double_t eff[n]={1,2,3,4,5,6,7,8,9};
Double_t x[n]={1,2,3,4,5,6,7,8,9};

for(Int_t i=0;i<n;i++) {
  eff[i]=eff[i]*100.;
  blocks[i]=blocks[i]/100000.;
}
TGraph *gblocks=new TGraph(n,x,blocks);
TGraph *grealblocks=new TGraph(n,x,realblocks);
TGraph *geff=new TGraph(n,x,eff);

gblocks->SetLineColor(kRed);
gblocks->SetMarkerColor(kRed);
grealblocks->SetLineColor(kBlue);
grealblocks->SetMarkerColor(kBlue);
TMultiGraph *gmulti=new TMultiGraph();
gmulti->Add(gblocks,"*L");
gmulti->Add(grealblocks,"*L");

TCanvas *c=new TCanvas();
c->Divide(1,2);
c->cd(1);
gPad->SetGridx();
gPad->SetGridy();
geff->Draw("A*L");
geff->SetTitle("");
geff->GetXaxis()->SetTitle("Relative weight of neglected PA blocks [%]");
geff->GetYaxis()->SetTitle("Efficiency [%]");
geff->GetXaxis()->SetLabelFont(63);
geff->GetXaxis()->SetLabelSize(12);
geff->GetYaxis()->SetLabelFont(63);
geff->GetYaxis()->SetLabelSize(12);
geff->GetXaxis()->SetTitleFont(63);
geff->GetXaxis()->SetTitleSize(12);
geff->GetYaxis()->SetTitleFont(63);
geff->GetYaxis()->SetTitleSize(12);
geff->GetXaxis()->SetTitleOffset(1.8);
geff->GetXaxis()->SetRangeUser(0,10);
c->cd(2);
gPad->SetGridx();
gPad->SetGridy();
gmulti->Draw("A");
gmulti->GetXaxis()->SetTitle("Relative weight of neglected PA blocks [%]");
gmulti->GetXaxis()->SetLabelFont(63);
gmulti->GetXaxis()->SetLabelSize(12);
gmulti->GetYaxis()->SetLabelFont(63);
gmulti->GetYaxis()->SetLabelSize(12);
gmulti->GetXaxis()->SetTitleFont(63);
gmulti->GetXaxis()->SetTitleSize(12);
gmulti->GetYaxis()->SetTitleFont(63);
gmulti->GetYaxis()->SetTitleSize(12);
gmulti->GetXaxis()->SetTitleOffset(1.8);
gmulti->GetXaxis()->SetRangeUser(0,10);

TLegend *leg = new TLegend(0.4,0.6,0.89,0.89);
leg->SetFillColor(kWhite);
leg->SetBorderSize(0);
leg->AddEntry(gblocks,"Average number of PA blocks per calo tower","l");
leg->AddEntry(grealblocks,"Average number of PA blocks per event","l");
leg->Draw();
}
