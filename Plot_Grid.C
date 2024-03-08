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

void Plot_Grid(){

TPaveText *cms1 = new TPaveText(0.16,0.92,0.45,0.97,"NDC");
cms1->AddText("CMS #it{Simulation}");
cms1->SetBorderSize(0);
cms1->SetFillColor(0);
cms1->SetTextSize(0.04);

TPaveText *cms2 = new TPaveText(0.7,0.92,0.95,0.97,"NDC");
cms2->AddText("(13 TeV)");
cms2->SetBorderSize(0);
cms2->SetFillColor(0);
cms2->SetTextSize(0.04);

TCanvas *c = new TCanvas("c","",800,1000);
c->cd();
TGraph *g = new TGraph();

for (int i=0; i<8; i++)
{
	for (int j=0; j<12; j++)
	{
		g->SetPoint(j+12*i, 2000+i*1000, 0.11+j*0.02);
	}
}

g->SetMarkerStyle(8);
g->SetMarkerColor(kBlack);
g->GetYaxis()->SetRangeUser(0., 0.5);
g->GetXaxis()->SetTitle("M_{S_{uu}} [GeV]");
g->GetYaxis()->SetTitle("#alpha_{True}");
g->GetYaxis()->SetTitleSize(0.05);
g->GetXaxis()->SetTitleSize(0.04);
g->GetYaxis()->SetTitleOffset(1.2);
g->GetXaxis()->SetTitleOffset(1.1);
g->Draw("AP");

TGraph *g2 = new TGraph();

/*g2->SetPoint(0, 2000, 0.25);
g2->SetPoint(1, 2000, 0.375);
g2->SetPoint(2, 2000, 0.5);
g2->SetPoint(3, 3000, 0.1666667);
g2->SetPoint(4, 3000, 0.25);
g2->SetPoint(5, 3000, 0.3333333);
g2->SetPoint(6, 4000, 0.125);
g2->SetPoint(7, 4000, 0.25);
g2->SetPoint(8, 4000, 0.5);
g2->SetPoint(9, 5000, 0.2);
g2->SetPoint(10, 5000, 0.4);
g2->SetPoint(11, 6000, 0.3333333);
g2->SetPoint(12, 6000, 0.4833333);
g2->SetPoint(13, 7800, 0.2692308);
g2->SetPoint(14, 8000, 0.125);
g2->SetPoint(15, 8000, 0.225);
g2->SetPoint(16, 8000, 0.25);
g2->SetPoint(17, 8100, 0.2592593);
g2->SetPoint(18, 8400, 0.2261905);
g2->SetPoint(19, 8400, 0.2380952);
*/g2->SetPoint(0, 8400, 0.25);
/*g2->SetPoint(21, 8400, 0.2619048);
g2->SetPoint(22, 8400, 0.2738095);
g2->SetPoint(23, 8700, 0.2413793);
g2->SetPoint(24, 9000, 0.2333333);
*/
g2->SetMarkerStyle(8);
g2->SetMarkerColor(kBlack);

g2->Draw("P");

TGraph *g3 = new TGraph();

for(int i=0; i<8; i++)
{
	g3->SetPoint(i, 2000+i*1000, 0.42);
}

g3->SetMarkerStyle(8);
g3->SetMarkerColor(kBlack);

g3->Draw("P");

cms1->Draw();
cms2->Draw();

c->SaveAs("/afs/cern.ch/user/i/izisopou/private/PairedDijetAN/AN-20-190/plots_interpolation/2DGrid.png");
}
