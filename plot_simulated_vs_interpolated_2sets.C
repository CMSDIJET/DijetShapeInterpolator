#include "TH1F.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TF1.h"
#include "TDirectory.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TMath.h"
#include "Math/MinimizerOptions.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"

void plot_simulated_vs_interpolated_2sets(double width, double alpha_true, double Suu, int alphabin){

double xmin = 0.1*Suu;
//double xmax = Suu*1.2;
double xmax = 11179;

char width_name[1024];
if (width==0.0043) sprintf(width_name,"0p0043");
if (width==0.015) sprintf(width_name,"0p015");
if (width==0.05) sprintf(width_name,"0p05");
if (width==0.1) sprintf(width_name,"0p1");

char alpha_true_name[1024];
if (alpha_true==0.11) sprintf(alpha_true_name,"0p11");
if (alpha_true==0.13) sprintf(alpha_true_name,"0p13");
if (alpha_true==0.15) sprintf(alpha_true_name,"0p15");
if (alpha_true==0.17) sprintf(alpha_true_name,"0p17");
if (alpha_true==0.19) sprintf(alpha_true_name,"0p19");
if (alpha_true==0.21) sprintf(alpha_true_name,"0p21");
if (alpha_true==0.23) sprintf(alpha_true_name,"0p23");
if (alpha_true==0.25) sprintf(alpha_true_name,"0p25");
if (alpha_true==0.27) sprintf(alpha_true_name,"0p27");
if (alpha_true==0.29) sprintf(alpha_true_name,"0p29");
if (alpha_true==0.31) sprintf(alpha_true_name,"0p31");
if (alpha_true==0.33) sprintf(alpha_true_name,"0p33");
if (alpha_true==0.42) sprintf(alpha_true_name,"0p42");

char alphabin_name[1024], alphaleg[1024];
if (alphabin==1) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.10 < #alpha^{rec} < 0.12}");}
if (alphabin==2) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.12 < #alpha^{rec} < 0.14}");}
if (alphabin==3) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.14 < #alpha^{rec} < 0.16}");}
if (alphabin==4) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.16 < #alpha^{rec} < 0.18}");}
if (alphabin==5) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.18 < #alpha^{rec} < 0.20}");}
if (alphabin==6) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.20 < #alpha^{rec} < 0.22}");}
if (alphabin==7) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.22 < #alpha^{rec} < 0.24}");}
if (alphabin==8) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.24 < #alpha^{rec} < 0.26}");}
if (alphabin==9) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.26 < #alpha^{rec} < 0.28}");}
if (alphabin==10) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.28 < #alpha^{rec} < 0.30}");}
if (alphabin==11) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.30 < #alpha^{rec} < 0.32}");}
if (alphabin==12) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.32 < #alpha^{rec} < 0.34}");}
if (alphabin==13) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{#alpha^{rec} > 0.34}");}
if (alphabin==0) {sprintf(alphabin_name,"alphagt0p1"); sprintf(alphaleg,"#bf{#alpha^{rec} > 0.10}");}


cout << "Width = " << width*100. << "%" << endl;
cout << "M(S) = " << Suu << " GeV, M(chi) = " << Suu*alpha_true << " GeV" << endl;
cout << "Alpha bin: " << alphaleg << endl;


char fsimulated_name[1024], finterpolated1_name[1024], finterpolated2_name[1024];
if(width==0.0043)
{
	sprintf(fsimulated_name,"/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/signals_13bins/alpha%s/nominal/Rebinned_ResonanceShapes_NOMINAL_Suu-Diquark_W-%s_S-%.0f_chi-%.0f_%s.root", alpha_true_name, width_name, Suu, Suu*alpha_true, alphabin_name);
}
else
{
	sprintf(fsimulated_name,"/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha%s/Rebinned_ResonanceShapes_NOMINAL_Suu-Diquark_W-%s_S-%.0f_chi-%.0f_%s.root", alpha_true_name, width_name, Suu, Suu*alpha_true, alphabin_name);
}

sprintf(finterpolated1_name,"/eos/user/i/izisopou/4jets_WideResonances/CMSSW_10_2_13/src/CMSDIJET/DijetShapeInterpolator/output/performance_testing_1TeVstep/Rebinned_ResonanceShapes_alpha%s_W-%s_%s.root", alpha_true_name, width_name, alphabin_name);
sprintf(finterpolated2_name,"/eos/user/i/izisopou/4jets_WideResonances/CMSSW_10_2_13/src/CMSDIJET/DijetShapeInterpolator/output/performance_testing_2TeVstep/Rebinned_ResonanceShapes_alpha%s_W-%s_excluding_8_8p4_8p6_TeV_%s.root", alpha_true_name, width_name, alphabin_name);


TFile *fsimulated = new TFile(fsimulated_name,"read");
TFile *finterpolated1 = new TFile(finterpolated1_name,"read");
TFile *finterpolated2 = new TFile(finterpolated2_name,"read");

char hinterpolated_name[1024];
sprintf(hinterpolated_name,"h_qq_Suu%.0f_Chi%.0f", Suu, Suu*alpha_true);


TH1D *h_simulated = (TH1D*)fsimulated->Get("h_FourjetMass");;
TH1D *h_interpolated1 = (TH1D*)finterpolated1->Get(hinterpolated_name);
TH1D *h_interpolated2 = (TH1D*)finterpolated2->Get(hinterpolated_name);

TCanvas *c = new TCanvas("c","c",700,800);
c->cd();
c->Draw();

TPad *main_panel = new TPad("main_panel", "main_panel", 0, 0.42, 1, 0.95);
main_panel->SetTickx(1);
main_panel->SetTicky(1);
main_panel->SetLogy(1);
main_panel->SetRightMargin(0.02);
main_panel->SetLeftMargin(0.12);
main_panel->SetTopMargin(0.08);
main_panel->SetBottomMargin(0.001);
main_panel->Draw();

TPad *ratio_panel = new TPad("ratio_panel", "ratio_panel", 0, 0., 1, 0.4);
ratio_panel->SetTickx(1);
ratio_panel->SetTicky(1);
ratio_panel->SetRightMargin(0.02);
ratio_panel->SetLeftMargin(0.12);
ratio_panel->SetTopMargin(0.);
ratio_panel->SetBottomMargin(0.24);
ratio_panel->Draw();


main_panel->cd();

h_simulated->SetTitle("");
h_interpolated1->SetTitle("");
h_interpolated2->SetTitle("");

h_simulated->GetXaxis()->SetRangeUser(xmin,xmax);
h_simulated->GetYaxis()->SetRangeUser(0.00005,99);
h_interpolated1->GetXaxis()->SetRangeUser(xmin,xmax);
h_interpolated1->GetYaxis()->SetRangeUser(0.00005,99);
h_interpolated2->GetXaxis()->SetRangeUser(xmin,xmax);
h_interpolated2->GetYaxis()->SetRangeUser(0.00005,99);

h_simulated->GetYaxis()->SetTitle("Probability");
h_simulated->GetYaxis()->SetTitleOffset(0.85);
h_simulated->GetYaxis()->SetTitleSize(0.07);
h_simulated->GetYaxis()->SetLabelSize(0.06);

h_simulated->SetMarkerColor(kBlack);
h_simulated->SetLineColor(kBlack);
h_simulated->SetMarkerStyle(22);
h_simulated->SetMarkerSize(1.2);
h_simulated->SetLineWidth(3);

h_interpolated1->SetMarkerColor(kRed-4);
h_interpolated1->SetLineColor(kRed-4);
h_interpolated1->SetMarkerStyle(21);
h_interpolated1->SetMarkerSize(0.9);
h_interpolated1->SetLineWidth(3);

h_interpolated2->SetMarkerColor(kGreen-3);
h_interpolated2->SetLineColor(kGreen-3);
h_interpolated2->SetMarkerStyle(21);
h_interpolated2->SetMarkerSize(0.9);
h_interpolated2->SetLineWidth(3);

h_simulated->SetStats(0);
h_interpolated1->SetStats(0);
h_interpolated2->SetStats(0);

h_simulated->Draw("hist");
h_interpolated1->Draw("hist SAME");
h_interpolated2->Draw("hist SAME");

char legname1[1024], legname2[1024];
sprintf(legname1,"#bf{M_{S} = %.0f GeV, M_{#chi} = %.0f GeV}", Suu, Suu*alpha_true);
if(width==0.0043) sprintf(legname2,"#bf{#Gamma / M_{S} = %.2f %%}", width*100.);
if(width==0.015) sprintf(legname2,"#bf{#Gamma / M_{S} = %.1f %%}", width*100.);
if(width!=0.0043 && width!=0.015) sprintf(legname2,"#bf{#Gamma / M_{S} = %.0f %%}", width*100.);

TLegend *l = new TLegend(0.15,0.57,0.35,0.87,"");
l->SetBorderSize(0);
l->SetTextSize(0.05);
l->SetTextFont(42);
l->AddEntry((TObject*)0, legname1,"");
l->AddEntry((TObject*)0, legname2,"");
l->AddEntry(h_simulated,"Simulated shape","L");
l->AddEntry(h_interpolated1, "Interpolated shape with 8 and 9 TeV inputs","L");
l->AddEntry(h_interpolated2, "Interpolated shape with 7 and 9 TeV inputs","L");
l->AddEntry((TObject*)0, alphaleg,"");
l->Draw();


TPaveText *cms1 = new TPaveText(0.11,0.955,0.46,0.975,"NDC");
cms1->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms1->SetFillColor(0);
cms1->SetBorderSize(0);
cms1->SetTextSize(0.065);
cms1->SetTextFont(42);
cms1->Draw();

TPaveText *cms2 = new TPaveText(0.895,0.955,0.945,0.975,"NDC");
cms2->AddText("13 TeV");
cms2->SetFillColor(0);
cms2->SetBorderSize(0);
cms2->SetTextSize(0.065);
cms2->SetTextFont(42);
cms2->Draw();



ratio_panel->cd();

double ymin = 0.51;
double ymax = 1.79;

TH1F *h_ratio_1 = (TH1F*)h_interpolated1->Clone();
h_ratio_1->Divide(h_simulated);

TH1F *h_ratio_2 = (TH1F*)h_interpolated2->Clone();
h_ratio_2->Divide(h_simulated);

h_ratio_1->GetYaxis()->SetRangeUser(ymin, ymax);
h_ratio_1->GetXaxis()->SetRangeUser(xmin,xmax);
h_ratio_1->GetYaxis()->SetTitle("Interpolated / Simulated");
h_ratio_1->GetXaxis()->SetTitle("Four-jet mass [GeV]");
h_ratio_1->GetYaxis()->SetTitleOffset(0.75);
h_ratio_1->GetYaxis()->SetTitleSize(0.075);
h_ratio_1->GetXaxis()->SetTitleSize(0.12);
h_ratio_1->GetYaxis()->SetLabelSize(0.08);
h_ratio_1->GetXaxis()->SetLabelSize(0.08);
h_ratio_1->GetXaxis()->SetTitleOffset(0.78);
h_ratio_1->GetXaxis()->SetTickLength(0.08);
h_ratio_1->GetYaxis()->SetNdivisions(310);
h_ratio_1->GetYaxis()->CenterTitle(1);
h_ratio_1->SetMarkerStyle(21);
h_ratio_1->SetMarkerColor(kRed-4);
h_ratio_1->SetLineColor(kRed-4);
h_ratio_1->SetMarkerSize(0.8);
h_ratio_1->SetLineWidth(2);
h_ratio_2->SetMarkerStyle(21);
h_ratio_2->SetMarkerColor(kGreen-3);
h_ratio_2->SetLineColor(kGreen-3);
h_ratio_2->SetMarkerSize(0.8);
h_ratio_2->SetLineWidth(2);

h_ratio_1->Draw("hist E");
h_ratio_2->Draw("hist E same");

TLine *line = new TLine(xmin,1.,xmax,1.);
line->SetLineColor(kBlack);
line->SetLineStyle(kDashed);
line->Draw("same");

char cname1[1024], cname2[1024];
sprintf(cname1,"plots/Rebinned_SimulatedVSInterpolated2TeVStepVSInterpolated1TeVStep_alpha%s_Suu%.0f_W-%s_%s.png", alpha_true_name, Suu, width_name, alphabin_name);
sprintf(cname2,"plots/Rebinned_SimulatedVSInterpolated2TeVStepVSInterpolated1TeVStep_alpha%s_Suu%.0f_W-%s_%s.pdf", alpha_true_name, Suu, width_name, alphabin_name);
c->SaveAs(cname1);
c->SaveAs(cname2);

}















