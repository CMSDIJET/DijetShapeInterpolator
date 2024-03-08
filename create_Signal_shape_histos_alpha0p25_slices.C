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

void create_Signal_shape_histos_alpha0p25_slices(){

	double FourjetMass, Maverage, Masymmetry, DeltaEtaJJAK4, DeltaRAK4_First, DeltaRAK4_Second, alpha;

	Char_t shape_name[1024];
	Char_t shape_name_Distr[1024];
	char Suu_Resonance_Mass[11][10] = {"2000", "3000", "4000", "5000", "6000", "7800", "8000", "8100", "8400", "8700", "9000"};
	char Chi_Resonance_Mass[10][10] = {"500", "750", "1000", "1800", "1900", "2000", "2100", "2200", "2300", "2900"};

	double resonance_mass_Suu[11] = {2000, 3000, 4000, 5000, 6000, 7800, 8000, 8100, 8400, 8700, 9000};
	double resonance_mass_Chi[10] = {500, 750, 1000, 1800, 1900, 2000, 2100, 2200, 2300, 2900};
 
	TFile *fout6 = new TFile ("inputs_slices/InputShapes_alpha0p25_3and8TeV_slice6.root","recreate"); 	
	TFile *fout7 = new TFile ("inputs_slices/InputShapes_alpha0p25_3and8TeV_slice7.root","recreate");
	TFile *fout8 = new TFile ("inputs_slices/InputShapes_alpha0p25_3and8TeV_slice8.root","recreate");
	TFile *fout9 = new TFile ("inputs_slices/InputShapes_alpha0p25_3and8TeV_slice9.root","recreate");
	TFile *fout10 = new TFile ("inputs_slices/InputShapes_alpha0p25_3and8TeV_slice10.root","recreate");
	//TFile *fout_distr = new TFile ("inputs_2D/Distribution.root","recreate");

	Char_t filechain[1024];
	
	for (int j1 = 0; j1 < 11; j1++)
	{
		for (int j2=0; j2<10; j2++)
		{ 

			sprintf(filechain,"root:://eoscms//eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/4jets/Signal/MC2017/MC2017_Suu_Diquark_S%s_chi%s_reduced_skim.root", Suu_Resonance_Mass[j1], Chi_Resonance_Mass[j2]); 

			TFile *f1 = new TFile(filechain,"READ");

			if( f1->IsOpen() && ( (j1==1 && j2==1) ||  (j1==6 && j2==5) ) )
			{

				TH1D *h_mass6 = new TH1D("h_mass6","",100,0.,2.);
				TH1D *h_mass7 = new TH1D("h_mass7","",100,0.,2.);
				TH1D *h_mass8 = new TH1D("h_mass8","",100,0.,2.);
				TH1D *h_mass9 = new TH1D("h_mass9","",100,0.,2.);
				TH1D *h_mass10 = new TH1D("h_mass10","",100,0.,2.);

				h_mass6->Sumw2();
				h_mass7->Sumw2();
				h_mass8->Sumw2();
				h_mass9->Sumw2();
				h_mass10->Sumw2();

				//TH2D *h_mass = new TH2D("h_mass","",90,0,9000,50,0,0.5);

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

					if(Masymmetry<0.1 && DeltaEtaJJAK4>0 && DeltaEtaJJAK4<1.1 && DeltaRAK4_First<2.0 && DeltaRAK4_Second<2.0) 
					{
						alpha=Maverage/FourjetMass;
						if (alpha>0.20 && alpha<0.22) h_mass6->Fill(FourjetMass/resonance_mass_Suu[j1]); 
						if (alpha>0.22 && alpha<0.24) h_mass7->Fill(FourjetMass/resonance_mass_Suu[j1]);
						if (alpha>0.24 && alpha<0.26) h_mass8->Fill(FourjetMass/resonance_mass_Suu[j1]);
						if (alpha>0.26 && alpha<0.28) h_mass9->Fill(FourjetMass/resonance_mass_Suu[j1]);
						if (alpha>0.28 && alpha<0.30) h_mass10->Fill(FourjetMass/resonance_mass_Suu[j1]);
						//h_mass->Fill(FourjetMass, alpha);
					}
		

		 		}// end of event loop
			

			//f1->Close();

			fout6->cd();
			sprintf(shape_name,"h_Mass_Suu%s_Chi%s", Suu_Resonance_Mass[j1], Chi_Resonance_Mass[j2]);
			h_mass6->SetName(shape_name);
			h_mass6->Scale(1./h_mass6->Integral());
			h_mass6->Write();

			fout7->cd();
			sprintf(shape_name,"h_Mass_Suu%s_Chi%s", Suu_Resonance_Mass[j1], Chi_Resonance_Mass[j2]);
			h_mass7->SetName(shape_name);
			h_mass7->Scale(1./h_mass7->Integral());
			h_mass7->Write();

			fout8->cd();
			sprintf(shape_name,"h_Mass_Suu%s_Chi%s", Suu_Resonance_Mass[j1], Chi_Resonance_Mass[j2]);
			h_mass8->SetName(shape_name);
			h_mass8->Scale(1./h_mass8->Integral());
			h_mass8->Write();

			fout9->cd();
			sprintf(shape_name,"h_Mass_Suu%s_Chi%s", Suu_Resonance_Mass[j1], Chi_Resonance_Mass[j2]);
			h_mass9->SetName(shape_name);
			h_mass9->Scale(1./h_mass9->Integral());
			h_mass9->Write();

			fout10->cd();
			sprintf(shape_name,"h_Mass_Suu%s_Chi%s", Suu_Resonance_Mass[j1], Chi_Resonance_Mass[j2]);
			h_mass10->SetName(shape_name);
			h_mass10->Scale(1./h_mass10->Integral());
			h_mass10->Write();

/*
			fout_distr->cd();
			sprintf(shape_name_Distr,"h_Distr_Suu%s_Chi%s", Suu_Resonance_Mass[j1], Chi_Resonance_Mass[j2]);
			h_mass->SetName(shape_name_Distr);
			h_mass->Scale(1./h_mass->Integral());
			h_mass->Write();
*/
			delete h_mass6;
			delete h_mass7;
			delete h_mass8;
			delete h_mass9;
			delete h_mass10;
			//delete h_mass;
			}//end of if f1
		}
	}





}
