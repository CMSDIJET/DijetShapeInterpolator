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

void Plot_X_Shapes(){

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

TFile *f = new TFile("inputs_1D/InputShapes_alpha0p25_2and4TeV_forAN_plus3TeV.root", "READ");
f->cd();

TCanvas *c = new TCanvas("c","",1000,1000);
c->cd();

TH1D *h_Mass_Suu2000_Chi500 = (TH1D*)f->Get("h_Mass_Suu2000_Chi500");
TH1D *h_Mass_Suu3000_Chi750 = (TH1D*)f->Get("h_Mass_Suu3000_Chi750");
TH1D *h_Mass_Suu4000_Chi1000 = (TH1D*)f->Get("h_Mass_Suu4000_Chi1000");

h_Mass_Suu2000_Chi500->SetLineColor(kBlack);
h_Mass_Suu2000_Chi500->SetLineWidth(3);
h_Mass_Suu2000_Chi500->GetXaxis()->SetTitle("X #equiv M_{4j} / M_{S_{uu}}");
h_Mass_Suu2000_Chi500->GetYaxis()->SetTitle("Probability");
h_Mass_Suu2000_Chi500->GetYaxis()->SetRangeUser(0.,0.18);
h_Mass_Suu2000_Chi500->GetXaxis()->SetRangeUser(0.,1.5);
h_Mass_Suu2000_Chi500->GetXaxis()->SetTitleOffset(1.2);
h_Mass_Suu2000_Chi500->SetStats(0);
h_Mass_Suu2000_Chi500->Draw("hist");

h_Mass_Suu3000_Chi750->SetLineColor(kBlue);
h_Mass_Suu3000_Chi750->SetLineWidth(3);
h_Mass_Suu3000_Chi750->Draw("hist same");

h_Mass_Suu4000_Chi1000->SetLineColor(kRed);
h_Mass_Suu4000_Chi1000->SetLineWidth(3);
h_Mass_Suu4000_Chi1000->Draw("hist same");

TLegend *l = new TLegend(0.15,0.6,0.4,0.8);
l->SetBorderSize(0);
l->SetTextSize(0.03);
l->AddEntry(h_Mass_Suu2000_Chi500,"M_{S_{uu}} = 2 TeV, M_{#chi} = 0.5 TeV, #alpha_{True} = 0.25","L");
l->AddEntry(h_Mass_Suu3000_Chi750,"M_{S_{uu}} = 3 TeV, M_{#chi} = 0.75 TeV, #alpha_{True} = 0.25","L");
l->AddEntry(h_Mass_Suu4000_Chi1000,"M_{S_{uu}} = 4 TeV, M_{#chi} = 1 TeV, #alpha_{True} = 0.25","L");
l->AddEntry((TObject*)0,"#alpha > 0.1","");
l->Draw();

cms1->Draw();
cms2->Draw();

c->SaveAs("/afs/cern.ch/user/i/izisopou/private/PairedDijetAN/AN-20-190/plots_interpolation/1D_Shapes_alpha0p25.png");
}
