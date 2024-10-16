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

void create_input_histos_for_interpolation(double width, double alpha_true, char type[1024]){

char width_name[1024];
if (width==0.015) sprintf(width_name,"0p015");
if (width==0.05) sprintf(width_name,"0p05");
if (width==0.1) sprintf(width_name,"0p1");

char alpha_name[1024];
double alphap = alpha_true*100.;
sprintf(alpha_name, "0p%.0f",alphap);
  	
char foutname[1024], foutname1[1024], foutname2[1024], foutname3[1024], foutname4[1024], foutname5[1024], foutname6[1024], foutname7[1024], foutname8[1024], foutname9[1024], foutname10[1024], foutname11[1024], foutname12[1024], foutname13[1024];

sprintf(foutname, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/interpolation/inputs/alpha%s/InputShapes_%s_alpha%s_W-%s_alphagt0p1.root", alpha_name, type, alpha_name, width_name);
sprintf(foutname1, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/interpolation/inputs/alpha%s/InputShapes_%s_alpha%s_W-%s_alphabin1.root", alpha_name, type, alpha_name, width_name);
sprintf(foutname2, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/interpolation/inputs/alpha%s/InputShapes_%s_alpha%s_W-%s_alphabin2.root", alpha_name, type, alpha_name, width_name);
sprintf(foutname3, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/interpolation/inputs/alpha%s/InputShapes_%s_alpha%s_W-%s_alphabin3.root", alpha_name, type, alpha_name, width_name);
sprintf(foutname4, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/interpolation/inputs/alpha%s/InputShapes_%s_alpha%s_W-%s_alphabin4.root", alpha_name, type, alpha_name, width_name);
sprintf(foutname5, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/interpolation/inputs/alpha%s/InputShapes_%s_alpha%s_W-%s_alphabin5.root", alpha_name, type, alpha_name, width_name);
sprintf(foutname6, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/interpolation/inputs/alpha%s/InputShapes_%s_alpha%s_W-%s_alphabin6.root", alpha_name, type, alpha_name, width_name);
sprintf(foutname7, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/interpolation/inputs/alpha%s/InputShapes_%s_alpha%s_W-%s_alphabin7.root", alpha_name, type, alpha_name, width_name);
sprintf(foutname8, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/interpolation/inputs/alpha%s/InputShapes_%s_alpha%s_W-%s_alphabin8.root", alpha_name, type, alpha_name, width_name);
sprintf(foutname9, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/interpolation/inputs/alpha%s/InputShapes_%s_alpha%s_W-%s_alphabin9.root", alpha_name, type, alpha_name, width_name);
sprintf(foutname10, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/interpolation/inputs/alpha%s/InputShapes_%s_alpha%s_W-%s_alphabin10.root", alpha_name, type, alpha_name, width_name);
sprintf(foutname11, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/interpolation/inputs/alpha%s/InputShapes_%s_alpha%s_W-%s_alphabin11.root", alpha_name, type, alpha_name, width_name);
sprintf(foutname12, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/interpolation/inputs/alpha%s/InputShapes_%s_alpha%s_W-%s_alphabin12.root", alpha_name, type, alpha_name, width_name);
sprintf(foutname13, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/interpolation/inputs/alpha%s/InputShapes_%s_alpha%s_W-%s_alphabin13.root", alpha_name, type, alpha_name, width_name);

TFile *fout = new TFile (foutname,"recreate");
TFile *fout1 = new TFile (foutname1,"recreate");
TFile *fout2 = new TFile (foutname2,"recreate");
TFile *fout3 = new TFile (foutname3,"recreate");
TFile *fout4 = new TFile (foutname4,"recreate");
TFile *fout5 = new TFile (foutname5,"recreate");
TFile *fout6 = new TFile (foutname6,"recreate");
TFile *fout7 = new TFile (foutname7,"recreate");
TFile *fout8 = new TFile (foutname8,"recreate");
TFile *fout9 = new TFile (foutname9,"recreate");
TFile *fout10 = new TFile (foutname10,"recreate");
TFile *fout11 = new TFile (foutname11,"recreate");
TFile *fout12 = new TFile (foutname12,"recreate");
TFile *fout13 = new TFile (foutname13,"recreate");

double FourjetMass, Maverage, Masymmetry, DeltaEtaJJAK4, DeltaRAK4_First, DeltaRAK4_Second, alpha;

//const int Suu_masses_length = 12;
//double Suu_masses[Suu_masses_length] = {2000, 3000, 4000, 5000, 6000, 7000, 8000, 8400, 8600, 9000, 10000, 11000};

const int Suu_masses_length = 10;
double Suu_masses[Suu_masses_length] = {2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000};

Char_t filechain[1024];
	
for (int mass_idx = 0; mass_idx < Suu_masses_length; mass_idx++)
{

	sprintf(filechain,"/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/reduced_trees/Suu_Diquarks/RunIISummer20UL18MiniAODv2/JEC_Summer20UL18_MC_%s/RunIISummer20UL18_Suu-Diquark_W-%s_S-%.0f_chi-%.0f__AK4CHS_reduced_skim.root", type, width_name, Suu_masses[mass_idx], Suu_masses[mass_idx]*alpha_true); 	


	TFile *f = new TFile(filechain,"READ");

	if(f->IsOpen())
	{

		TH1D *h_mass = new TH1D("h_mass","",100,0.,2.);
		TH1D *h_mass1 = new TH1D("h_mass1","",100,0.,2.);
		TH1D *h_mass2 = new TH1D("h_mass2","",100,0.,2.);
		TH1D *h_mass3 = new TH1D("h_mass3","",100,0.,2.);
		TH1D *h_mass4 = new TH1D("h_mass4","",100,0.,2.);
		TH1D *h_mass5 = new TH1D("h_mass5","",100,0.,2.);
		TH1D *h_mass6 = new TH1D("h_mass6","",100,0.,2.);
		TH1D *h_mass7 = new TH1D("h_mass7","",100,0.,2.);
		TH1D *h_mass8 = new TH1D("h_mass8","",100,0.,2.);
		TH1D *h_mass9 = new TH1D("h_mass9","",100,0.,2.);
		TH1D *h_mass10 = new TH1D("h_mass10","",100,0.,2.);
		TH1D *h_mass11 = new TH1D("h_mass11","",100,0.,2.);
		TH1D *h_mass12 = new TH1D("h_mass12","",100,0.,2.);
		TH1D *h_mass13 = new TH1D("h_mass13","",100,0.,2.);
		h_mass->Sumw2();
		h_mass1->Sumw2();
		h_mass2->Sumw2();
		h_mass3->Sumw2();
		h_mass4->Sumw2();
		h_mass5->Sumw2();
		h_mass6->Sumw2();
		h_mass7->Sumw2();
		h_mass8->Sumw2();
		h_mass9->Sumw2();
		h_mass10->Sumw2();
		h_mass11->Sumw2();
		h_mass12->Sumw2();
		h_mass13->Sumw2();

		cout << "File used: " << filechain << endl;
		cout << "Suu mass = " << Suu_masses[mass_idx] <<" GeV , "<< " Chi mass = " << Suu_masses[mass_idx]*alpha_true << " GeV " << endl;

		TTree *tree = (TTree*)(f->Get("rootTupleTree/tree"));

		tree->SetBranchAddress("FourjetMassAK4CHS",&FourjetMass);
  		tree->SetBranchAddress("MaverageAK4CHS",&Maverage);
  		tree->SetBranchAddress("MasymmetryAK4CHS",&Masymmetry);
  		tree->SetBranchAddress("DeltaEtaJJAK4CHS",&DeltaEtaJJAK4);
  		tree->SetBranchAddress("DeltaRAK4CHS_First",&DeltaRAK4_First);
  		tree->SetBranchAddress("DeltaRAK4CHS_Second",&DeltaRAK4_Second);
	   	

		int nentries=(Int_t)tree->GetEntries(); 
		std::cout<<"Number of entries =  "<<nentries<<std::endl;
		
		for (int i=0; i<nentries; i++)    //event loop
		{     
			tree->GetEntry(i);

			alpha=Maverage/FourjetMass;

			if(Masymmetry<0.1 && DeltaEtaJJAK4<1.1 && DeltaRAK4_First<2.0 && DeltaRAK4_Second<2.0) 
			{ 
				if(alpha>0.10) 		     h_mass->Fill(FourjetMass/Suu_masses[mass_idx]);
				if(alpha>0.10 && alpha<0.12) h_mass1->Fill(FourjetMass/Suu_masses[mass_idx]);
				if(alpha>0.12 && alpha<0.14) h_mass2->Fill(FourjetMass/Suu_masses[mass_idx]);
				if(alpha>0.14 && alpha<0.16) h_mass3->Fill(FourjetMass/Suu_masses[mass_idx]);
				if(alpha>0.16 && alpha<0.18) h_mass4->Fill(FourjetMass/Suu_masses[mass_idx]);
				if(alpha>0.18 && alpha<0.20) h_mass5->Fill(FourjetMass/Suu_masses[mass_idx]);
				if(alpha>0.20 && alpha<0.22) h_mass6->Fill(FourjetMass/Suu_masses[mass_idx]);
				if(alpha>0.22 && alpha<0.24) h_mass7->Fill(FourjetMass/Suu_masses[mass_idx]);
				if(alpha>0.24 && alpha<0.26) h_mass8->Fill(FourjetMass/Suu_masses[mass_idx]);
				if(alpha>0.26 && alpha<0.28) h_mass9->Fill(FourjetMass/Suu_masses[mass_idx]);
				if(alpha>0.28 && alpha<0.30) h_mass10->Fill(FourjetMass/Suu_masses[mass_idx]);
				if(alpha>0.30 && alpha<0.32) h_mass11->Fill(FourjetMass/Suu_masses[mass_idx]);
				if(alpha>0.32 && alpha<0.34) h_mass12->Fill(FourjetMass/Suu_masses[mass_idx]);
				if(alpha>0.34) 		     h_mass13->Fill(FourjetMass/Suu_masses[mass_idx]);
			}

		}// end of event loop
			
		char shape_name[1024];
		sprintf(shape_name,"h_Mass_Suu%.0f_Chi%.0f", Suu_masses[mass_idx], Suu_masses[mass_idx]*alpha_true);

		fout->cd();
		h_mass->SetName(shape_name);
		h_mass->Scale(1./h_mass->Integral());
		h_mass->Write();

		fout1->cd();
		h_mass1->SetName(shape_name);
		h_mass1->Scale(1./h_mass1->Integral());
		h_mass1->Write();

		fout2->cd();
		h_mass2->SetName(shape_name);
		h_mass2->Scale(1./h_mass2->Integral());
		h_mass2->Write();

		fout3->cd();
		h_mass3->SetName(shape_name);
		h_mass3->Scale(1./h_mass3->Integral());
		h_mass3->Write();

		fout4->cd();
		h_mass4->SetName(shape_name);
		h_mass4->Scale(1./h_mass4->Integral());
		h_mass4->Write();

		fout5->cd();
		h_mass5->SetName(shape_name);
		h_mass5->Scale(1./h_mass5->Integral());
		h_mass5->Write();

		fout6->cd();
		h_mass6->SetName(shape_name);
		h_mass6->Scale(1./h_mass6->Integral());
		h_mass6->Write();

		fout7->cd();
		h_mass7->SetName(shape_name);
		h_mass7->Scale(1./h_mass7->Integral());
		h_mass7->Write();

		fout8->cd();
		h_mass8->SetName(shape_name);
		h_mass8->Scale(1./h_mass8->Integral());
		h_mass8->Write();

		fout9->cd();
		h_mass9->SetName(shape_name);
		h_mass9->Scale(1./h_mass9->Integral());
		h_mass9->Write();

		fout10->cd();
		h_mass10->SetName(shape_name);
		h_mass10->Scale(1./h_mass10->Integral());
		h_mass10->Write();

		fout11->cd();
		h_mass11->SetName(shape_name);
		h_mass11->Scale(1./h_mass11->Integral());
		h_mass11->Write();

		fout12->cd();
		h_mass12->SetName(shape_name);
		h_mass12->Scale(1./h_mass12->Integral());
		h_mass12->Write();

		fout13->cd();
		h_mass13->SetName(shape_name);
		h_mass13->Scale(1./h_mass13->Integral());
		h_mass13->Write();

		delete h_mass;
		delete h_mass1;
		delete h_mass2;
		delete h_mass3;
		delete h_mass4;
		delete h_mass5;
		delete h_mass6;
		delete h_mass7;
		delete h_mass8;
		delete h_mass9;
		delete h_mass10;
		delete h_mass11;
		delete h_mass12;
		delete h_mass13;
	}
}
	





}
