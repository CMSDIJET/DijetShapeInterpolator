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

void create_Signal_shape_histos(){

/*
	TCanvas *c1 = new TCanvas("c1","",1000,1000);
	TCanvas *c2 = new TCanvas("c2","",1000,1000);

	TLegend *l1 = new TLegend(0.15,0.2,0.45,0.8,"");
	l1->SetTextSize(0.035);
	l1->SetFillColor(0);
	l1->SetBorderSize(0);

	TLegend *l2 = new TLegend(0.15,0.2,0.45,0.8,"");
	l2->SetTextSize(0.035);
	l2->SetFillColor(0);
	l2->SetBorderSize(0);
*/
	double FourjetMass, Maverage, Masymmetry, DeltaEtaJJAK4, DeltaRAK4_First, DeltaRAK4_Second, alpha;


	TH1D *h_m2j, *h_m4j;

	Char_t shape_name_Suu[1024];
	Char_t shape_name_Chi[1024];
	Char_t leg1[1024];
	Char_t leg2[1024];
	char Suu_Resonance_Mass[11][10] = {"2000", "3000", "4000", "5000", "6000", "7800", "8000", "8100", "8400", "8700", "9000"};
	char Chi_Resonance_Mass[10][10] = {"500", "750", "1000", "1800", "1900", "2000", "2100", "2200", "2300", "2900"};

	double resonance_mass_Suu[11] = {2000, 3000, 4000, 5000, 6000, 7800, 8000, 8100, 8400, 8700, 9000};
	double resonance_mass_Chi[10] = {500, 750, 1000, 1800, 1900, 2000, 2100, 2200, 2300, 2900};
  	
	TFile *fout_Suu = new TFile ("inputs/InputShapes_Suu.root","recreate");
	TFile *fout_Chi = new TFile ("inputs/InputShapes_Chi.root","recreate");

	Char_t filechain[1024];
	TFile *f1;
	TTree *tree; 
	for (int j1 = 0; j1 < 11; j1++)
	{
		for (int j2=0; j2<10; j2++)
		{ 

			h_m2j = new TH1D("h_m2j","",75,0,1.5);
			h_m4j = new TH1D("h_m4j","",75,0,1.5);

			sprintf(filechain,"root:://eoscms//eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/4jets/Signal/MC2017/MC2017_Suu_Diquark_S%s_chi%s_reduced_skim.root", Suu_Resonance_Mass[j1], Chi_Resonance_Mass[j2]); 

			f1 = new TFile(filechain,"READ");

			if(f1->IsOpen())
			{
				cout << "File used: " << filechain << endl;
				cout << "Suu = " << resonance_mass_Suu[j1] <<" GeV , "<< " Chi = " << resonance_mass_Chi[j2] << " GeV " << endl;

				f1->cd();

				TTree *tree = (TTree*)(f1->Get("rootTupleTree/tree"));

				tree->SetBranchAddress("FourjetMass",&FourjetMass);
  				tree->SetBranchAddress("Maverage",&Maverage);
  				tree->SetBranchAddress("Masymmetry",&Masymmetry);
  				tree->SetBranchAddress("DeltaEtaJJAK4",&DeltaEtaJJAK4);
  				tree->SetBranchAddress("DeltaRAK4_First",&DeltaRAK4_First);
  				tree->SetBranchAddress("DeltaRAK4_Second",&DeltaRAK4_Second);
	   
				int nentries=(Int_t)tree->GetEntries(); 
				std::cout<<"Number of entries =  "<<nentries<<std::endl;
				for (int i=0; i<nentries; i++)    //event loop
		 		{     
					tree->GetEntry(i);

					if(Masymmetry<0.1 && DeltaEtaJJAK4<1.1 && DeltaRAK4_First<2.0 && DeltaRAK4_Second<2.0) 
					{
						alpha=Maverage/FourjetMass; 
	  					if(alpha>0.10 && alpha<0.34)
						{
							h_m2j->Fill(Maverage/resonance_mass_Chi[j2]);
							h_m4j->Fill(FourjetMass/resonance_mass_Suu[j1]);
						}
					}
		

		 		}// end of event loop
			

			//f1->Close();
		
			sprintf(shape_name_Suu,"h_FourjetMass_Suu%s_Chi%s", Suu_Resonance_Mass[j1], Chi_Resonance_Mass[j2]);
			sprintf(shape_name_Chi,"h_Maverage_Suu%s_Chi%s", Suu_Resonance_Mass[j1], Chi_Resonance_Mass[j2]);
			h_m4j->SetName(shape_name_Suu);
			h_m2j->SetName(shape_name_Chi);
			
			fout_Suu->cd();
			h_m4j->Write();

			fout_Chi->cd();
			h_m2j->Write();


/*			c1->cd();
			h_m4j->SetLineColor(j1+1);
			h_m4j->GetXaxis()->SetTitle("X = M_{4j} / M_{Res}");
			h_m4j->Scale(1./h_m4j->Integral());
			h_m4j->Draw("histo same");

			sprintf(leg1,"Suu = %s GeV , Chi = %s GeV", Suu_Resonance_Mass[j1], Chi_Resonance_Mass[j2]);
			l1->AddEntry(h_m4j,leg1,"L");
			l1->Draw();

			c2->cd();
			h_m2j->SetLineColor(j2+1);
			h_m2j->GetXaxis()->SetTitle("X = <M_{2j}> / M_{Res}");
			h_m2j->Scale(1./h_m2j->Integral());
			h_m2j->Draw("histo same");

			sprintf(leg2,"Suu = %s GeV , Chi = %s GeV", Suu_Resonance_Mass[j1], Chi_Resonance_Mass[j2]);
			l2->AddEntry(h_m2j,leg2,"L");
			l2->Draw();
*/
			delete h_m4j;
			delete h_m2j;
			}//end of if f1
		}
	}





}
