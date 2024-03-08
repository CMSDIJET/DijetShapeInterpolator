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

void Write_Histos(double alpha){

char alpha_true[1024];

if (alpha==0.11) sprintf(alpha_true,"0p11");
if (alpha==0.13) sprintf(alpha_true,"0p13");
if (alpha==0.15) sprintf(alpha_true,"0p15");
if (alpha==0.17) sprintf(alpha_true,"0p17");
if (alpha==0.19) sprintf(alpha_true,"0p19");
if (alpha==0.21) sprintf(alpha_true,"0p21");
if (alpha==0.23) sprintf(alpha_true,"0p23");
if (alpha==0.25) sprintf(alpha_true,"0p25");
if (alpha==0.27) sprintf(alpha_true,"0p27");
if (alpha==0.29) sprintf(alpha_true,"0p29");
if (alpha==0.31) sprintf(alpha_true,"0p31");
if (alpha==0.33) sprintf(alpha_true,"0p33");
if (alpha==0.42) sprintf(alpha_true,"0p42");

char input_filename[1024];
char input_histoname[1024];
char output_filename[1024];

for(int slice=6; slice<=10; slice++)
{

	sprintf(input_filename,"output_test/ResonanceShapes_alpha%s_slice%d.root", alpha_true, slice);
	TFile *fin = new TFile(input_filename,"READ");

	for(int i=2000; i<=4000; i=i+100)
	{
		cout << "Processing Signal with Suu Mass = " << i << " GeV and alpha = " << alpha << " for slice " << slice << "." << endl;
		fin->cd();
		sprintf(input_histoname, "h_qq_Suu%d_alpha0.25",i);
		TH1D *h = (TH1D*)fin->Get(input_histoname);

		sprintf(output_filename,"output_for_combine/ResonanceShapes_Suu%d_alpha%s_SR_alphabin%d.root", i, alpha_true, slice);
		TFile *fout = new TFile(output_filename,"RECREATE");
		fout->cd();
		h->SetName("h_FourjetMass1GeV");
		h->SetTitle("");
		h->Write();
		fout->Close();
		delete h;
	}

	fin->Close();

}

}
