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

void write_histos_for_combine(double width, double alpha_true, char type[1024]){

char width_name[1024];
if (width==0.015) sprintf(width_name,"0p015");
if (width==0.05) sprintf(width_name,"0p05");
if (width==0.1) sprintf(width_name,"0p1");

char alpha_true_name[1024];
double alphap = alpha_true*100.;
sprintf(alpha_true_name, "0p%.0f",alphap);


char input_filename[1024];
char input_histoname[1024];
char output_filename[1024];

for(int alphabin=0; alphabin<=13; alphabin++)
{

	if(alphabin!=0) sprintf(input_filename,"/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/interpolation/outputs/alpha%s/ResonanceShapes_%s_alpha%s_W-%s_alphabin%d.root", alpha_true_name, type, alpha_true_name, width_name, alphabin);
	if(alphabin==0) sprintf(input_filename,"/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/interpolation/outputs/alpha%s/ResonanceShapes_%s_alpha%s_W-%s_alphagt0p1.root", alpha_true_name, type, alpha_true_name, width_name);
		
	TFile *fin = new TFile(input_filename,"READ");

	//cout << "Input file : " << input_filename << endl;


	for(int Suu=2000; Suu<=11000; Suu=Suu+100)
	{
	
		//if(Suu==2000 || Suu==3000 || Suu==4000 || Suu==5000 || Suu==6000 || Suu==7000 || Suu==8000 || Suu==8400 || Suu==8600 || Suu==9000 || Suu==10000 || Suu==11000) continue;
		if(Suu==2000 || Suu==3000 || Suu==4000 || Suu==5000 || Suu==6000 || Suu==7000 || Suu==8000 || Suu==9000 || Suu==10000 || Suu==11000) continue;

		//cout << "Processing " << type << " signal with width = " << width << ", Suu Mass = " << Suu << " GeV, Chi Mass = " << Suu*alpha_true << " GeV for alphabin " << alphabin << "." << endl;
		
		fin->cd();
		sprintf(input_histoname, "h_qq_Suu%d_Chi%.0f", Suu, Suu*alpha_true);
		TH1D *h = (TH1D*)fin->Get(input_histoname);

		if(alphabin!=0) sprintf(output_filename,"/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha%s/ResonanceShapes_%s_Suu-Diquark_W-%s_S-%d_chi-%.0f_alphabin%d.root", alpha_true_name, type, width_name, Suu, Suu*alpha_true*1., alphabin);
		if(alphabin==0) sprintf(output_filename,"/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha%s/ResonanceShapes_%s_Suu-Diquark_W-%s_S-%d_chi-%.0f_alphagt0p1.root", alpha_true_name, type, width_name, Suu, Suu*alpha_true*1.);
		
		TFile *fout = new TFile(output_filename,"RECREATE");
		fout->cd();
		
		h->SetName("h_FourjetMass");
		h->SetTitle("");
		h->Write();
		fout->Close();
		delete h;
	}

	fin->Close();

}



}
