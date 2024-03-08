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

void create_Signal_shape_histos_1D(){

	double FourjetMass, Maverage, Masymmetry, DeltaEtaJJAK4, DeltaRAK4_First, DeltaRAK4_Second, alpha;

	Char_t shape_name[1024];
	Char_t shape_name_Distr[1024];
	char Suu_Resonance_Mass[11][10] = {"2000", "3000", "4000", "5000", "6000", "7800", "8000", "8100", "8400", "8700", "9000"};
	char Chi_Resonance_Mass[10][10] = {"500", "750", "1000", "1800", "1900", "2000", "2100", "2200", "2300", "2900"};

	double resonance_mass_Suu[11] = {2000, 3000, 4000, 5000, 6000, 7800, 8000, 8100, 8400, 8700, 9000};
	double resonance_mass_Chi[10] = {500, 750, 1000, 1800, 1900, 2000, 2100, 2200, 2300, 2900};
  	
	TFile *fout = new TFile ("inputs_1D/InputShapes_alpha0p25_2and4TeV_forAN_plus3TeV.root","recreate");
	//TFile *fout_distr = new TFile ("inputs_2D/Distribution.root","recreate");

	Char_t filechain[1024];
	
	for (int j1 = 0; j1 < 11; j1++)
	{
		for (int j2=0; j2<10; j2++)
		{ 

			sprintf(filechain,"root:://eoscms//eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/4jets/Signal/MC2017/MC2017_Suu_Diquark_S%s_chi%s_reduced_skim.root", Suu_Resonance_Mass[j1], Chi_Resonance_Mass[j2]); 

			TFile *f1 = new TFile(filechain,"READ");

			if( f1->IsOpen() && ( (j1==0 && j2==0) ||  (j1==2 && j2==2) || (j1==1 && j2==1) ) )
			{

				TH1D *h_mass = new TH1D("h_mass","",100,0.,2.);
				h_mass->Sumw2();

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
						if (alpha>0.1) h_mass->Fill(FourjetMass/resonance_mass_Suu[j1]);
						//h_mass->Fill(FourjetMass, alpha);
					}
		

		 		}// end of event loop
			

			//f1->Close();
			fout->cd();
			sprintf(shape_name,"h_Mass_Suu%s_Chi%s", Suu_Resonance_Mass[j1], Chi_Resonance_Mass[j2]);
			h_mass->SetName(shape_name);
			h_mass->Scale(1./h_mass->Integral());
			h_mass->Write();
/*
			fout_distr->cd();
			sprintf(shape_name_Distr,"h_Distr_Suu%s_Chi%s", Suu_Resonance_Mass[j1], Chi_Resonance_Mass[j2]);
			h_mass->SetName(shape_name_Distr);
			h_mass->Scale(1./h_mass->Integral());
			h_mass->Write();
*/
			delete h_mass;
			//delete h_mass;
			}//end of if f1
		}
	}





}
