#include "TF1.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TH3I.h"
#include "TTree.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include "TMath.h"
#include "TLatex.h"
#include "TGraph.h"

void Plot_Shapes_Comparison(){

TPaveText *cms1 = new TPaveText(0.05,0.92,0.45,0.97,"NDC");
cms1->AddText("CMS #it{Simulation}");
cms1->SetBorderSize(0);
cms1->SetFillColor(0);
cms1->SetTextSize(0.04);

TPaveText *cms2 = new TPaveText(0.65,0.92,0.95,0.97,"NDC");
cms2->AddText("(13 TeV)");
cms2->SetBorderSize(0);
cms2->SetFillColor(0);
cms2->SetTextSize(0.04);

Char_t filechain[1024];

const int nMassBins = 103;
   
double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,  //<--48th bin
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, //<--71st bin
     4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,  //<-94th bin
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

TCanvas *c = new TCanvas("c","",800,1200);
c->cd();
//c->SetLogy(1);

TFile *f = new TFile("/afs/cern.ch/user/i/izisopou/public/4jets/CMSSW_10_2_13/src/CMSDIJET/DijetRootTreeAnalyzer/rootfiles/Test_alpha0p13_7and9TeV/ResonanceShapes_Suu8000_Chi1040_SR_alphabin9.root");

TH1D *h_FourjetMass = (TH1D*)(f->Get("h_FourjetMass1GeV"));
//TH1D *h_FourjetMass = new TH1D("h_FourjetMass","",nMassBins,massBoundaries);
//h_FourjetMass->Sumw2();

/*double val, xval;

for(unsigned int i=1; i<=h->GetNbinsX(); i++)
{
 	val  = h->GetBinContent(i);
 	xval = h->GetBinCenter(i);
 	h_FourjetMass->Fill(xval,val);		
}
*/

TFile *finter = new TFile("/afs/cern.ch/work/i/izisopou/public/Interpolation_Final/output_alpha0p13_test/ResonanceShapes_alpha0p13_slice9_stdbin.root");

TH1D *hinter = (TH1D*)(finter->Get("h_qq_Suu8000_Chi1040"));
hinter->SetLineColor(kBlue);
hinter->SetLineWidth(3);
hinter->GetXaxis()->SetRangeUser(3000.,10000.);
hinter->GetYaxis()->SetRangeUser(0.,0.4);
hinter->GetXaxis()->SetTitleSize(0.5);
//hinter->GetYaxis()->SetRangeUser(0.,0.35);
hinter->SetStats(0);
hinter->SetTitle("");
hinter->SetMarkerColor(kBlue);
hinter->SetMarkerStyle(8);
hinter->SetMarkerSize(0.6);
hinter->Draw("E1 P");

h_FourjetMass->SetLineColor(kRed);
h_FourjetMass->SetLineWidth(3);
h_FourjetMass->SetMarkerColor(kRed);
h_FourjetMass->SetMarkerStyle(8);
h_FourjetMass->SetMarkerSize(1);
h_FourjetMass->Draw("E1 P same");

TLegend *l = new TLegend(0.55,0.6,0.85,0.8,"");
l->SetBorderSize(0);
l->SetTextSize(0.035);
l->AddEntry((TObject*)0,"M_{Suu} = 8 TeV, M_{#chi} = 1.04 TeV","");
l->AddEntry((TObject*)0,"0.26 < #alpha < 0.28","");
l->AddEntry(hinter,"Predicted Shape","L");
l->AddEntry(h_FourjetMass, "Generated Shape","LPE");

TRatioPlot *rp = new TRatioPlot(hinter, h_FourjetMass,"divsym");
rp->Draw();
rp->GetLowerRefYaxis()->SetRangeUser(0.7,1.3);
rp->GetLowerRefYaxis()->SetTitle("Predicted / Generated");
rp->GetLowerRefYaxis()->SetTitleSize(0.025);
rp->GetUpperRefYaxis()->SetTitleSize(0.025);
rp->GetLowerRefXaxis()->SetTitleSize(0.035);
rp->GetLowerRefYaxis()->SetLabelSize(0.025);
rp->GetUpperPad()->cd();
l->Draw();
cms1->Draw();
cms2->Draw();
c->Update();

c->SaveAs("PredvsGen_alpha0p13_7and9TeV_slice9.png");

}
