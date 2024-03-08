#include "TF1.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TH2F.h"
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
#include "TH1.h"

void Plot_2D_Shapes(){

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

TPaveText *s1 = new TPaveText(0.25,0.82,0.7,0.87,"NDC");
s1->AddText("#it{Signal with M_{S_{uu}}} = 2 TeV, M_{#chi} = 0.5 TeV, #alpha_{True} = 0.25");
s1->SetBorderSize(0);
s1->SetFillColor(0);
s1->SetTextSize(0.03);

TPaveText *s2 = new TPaveText(0.25,0.82,0.7,0.87,"NDC");
s2->AddText("#it{Signal with M_{S_{uu}}} = 4 TeV, M_{#chi} = 1 TeV, #alpha_{True} = 0.25");
s2->SetBorderSize(0);
s2->SetFillColor(0);
s2->SetTextSize(0.03);

TFile *f = new TFile("inputs_2D/InputShapes_alpha0p25_2and4TeV.root", "READ");
f->cd();

TCanvas *c1 = new TCanvas("c","",1000,1000);
c1->cd();

TH2D *h_Mass_Suu2000_Chi500 = (TH2D*)f->Get("h_Mass_Suu2000_Chi500");

h_Mass_Suu2000_Chi500->GetXaxis()->SetTitle("Fourjet Mass [GeV]");
h_Mass_Suu2000_Chi500->GetYaxis()->SetTitle("#alpha");
h_Mass_Suu2000_Chi500->GetZaxis()->SetTitle("Probability");
h_Mass_Suu2000_Chi500->GetYaxis()->SetRangeUser(0.,0.5);
h_Mass_Suu2000_Chi500->GetXaxis()->SetRangeUser(0.,5000.);
h_Mass_Suu2000_Chi500->GetXaxis()->SetTitleOffset(1.2);
h_Mass_Suu2000_Chi500->GetZaxis()->SetTitleOffset(1.2);
h_Mass_Suu2000_Chi500->SetStats(0);
h_Mass_Suu2000_Chi500->Draw("colz");

cms1->Draw();
cms2->Draw();
s1->Draw();

TCanvas *c2 = new TCanvas("c2","",1000,1000);
c2->cd();

TH2D *h_Mass_Suu4000_Chi1000 = (TH2D*)f->Get("h_Mass_Suu4000_Chi1000");

h_Mass_Suu4000_Chi1000->GetXaxis()->SetTitle("Fourjet Mass [GeV]");
h_Mass_Suu4000_Chi1000->GetYaxis()->SetTitle("#alpha");
h_Mass_Suu4000_Chi1000->GetZaxis()->SetTitle("Probability");
h_Mass_Suu4000_Chi1000->GetYaxis()->SetRangeUser(0.,0.5);
h_Mass_Suu4000_Chi1000->GetXaxis()->SetRangeUser(0.,7000.);
h_Mass_Suu4000_Chi1000->GetXaxis()->SetTitleOffset(1.2);
h_Mass_Suu4000_Chi1000->GetZaxis()->SetTitleOffset(1.2);
h_Mass_Suu4000_Chi1000->SetStats(0);
h_Mass_Suu4000_Chi1000->Draw("colz");

cms1->Draw();
cms2->Draw();
s2->Draw();

c1->SaveAs("/afs/cern.ch/user/i/izisopou/private/PairedDijetAN/AN-20-190/plots_interpolation/2D_Shape_alpha0p25_2TeV.png");
c2->SaveAs("/afs/cern.ch/user/i/izisopou/private/PairedDijetAN/AN-20-190/plots_interpolation/2D_Shape_alpha0p25_4TeV.png");
}
