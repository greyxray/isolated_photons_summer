#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TAxis.h>
#include <TFrame.h>
#include <TF1.h>
#include <TStyle.h>
#include <TString.h>
#include <TMath.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TProfile.h>
#include <TText.h>
#include <TGraphAsymmErrors.h>
#include <TLorentzVector.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TROOT.h>
#include "plot_style_utils.h"
#include "../inc/constants.h"
//#include "plot_style_utils.h"
void AddAllPeriods(TH2D* h, Int_t histogram_index, TString data_type, TString s_hist);

const Int_t n_files = 10;
TFile *file[n_files];


int main(int argc, char *argv[])
{
  gROOT->SetStyle("Plain");
  gStyle->SetTitleBorderSize(1);
  gStyle->SetTitleH(0.08);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleY(0.99);
  gStyle->SetTitleX(0.15);
  gStyle->SetPalette(1, 0);

  file[0] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/data0405e_nocorr.root");
  file[1] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_bg_norad0405e_nocorr.root");
  file[2] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_bg_rad0405e_nocorr.root");
  file[3] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_prph_nocorr.root");

  file[4] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/data06e_nocorr.root");
  file[5] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_bg_norad06e_nocorr.root");
  file[6] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_bg_rad06e_nocorr.root");

  file[7] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/data0607p_nocorr.root");
  file[8] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_bg_norad0607p_nocorr.root");
  file[9] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_bg_rad0607p_nocorr.root");

  //  file[1] = new TFile("/afs/desy.de/user/z/zhmak/public/oleg/dataall.root");
  cout << "file attached" << endl;
  
  const Int_t n_hist = 8 + 9 + 9 + 9 + 16 + 4;
  const Int_t n_wind = 8 + 9 + 9 + 9 + 16 + 4;
  TString s_hist[n_hist] = 
    {"Photon_with_jet/h2d_fmax_deltaz", "Photon_with_jet/h2d_fmax_deltaz", "Photon_with_jet/h2d_fmax_deltaz", "Photon_with_jet/h2d_fmax_deltaz", 
     "Photon_with_jet/h2d_phjet_dphi_deta", "Photon_with_jet/h2d_phjet_dphi_deta", "Photon_with_jet/h2d_phjet_dphi_deta", "Photon_with_jet/h2d_phjet_dphi_deta",
     "MC_gen_recon_corel/h2d_q2_da",  "MC_gen_recon_corel/h2d_q2_da", "MC_gen_recon_corel/h2d_q2_da", 
     "MC_gen_recon_corel/h2d_q2_e",  "MC_gen_recon_corel/h2d_q2_e", "MC_gen_recon_corel/h2d_q2_e", 
     "MC_gen_recon_corel/h2d_q2_jb",  "MC_gen_recon_corel/h2d_q2_jb", "MC_gen_recon_corel/h2d_q2_jb",

     "MC_gen_recon_corel/h2d_x_da",  "MC_gen_recon_corel/h2d_x_da", "MC_gen_recon_corel/h2d_x_da", 
     "MC_gen_recon_corel/h2d_x_e",  "MC_gen_recon_corel/h2d_x_e", "MC_gen_recon_corel/h2d_x_e", 
     "MC_gen_recon_corel/h2d_x_jb",  "MC_gen_recon_corel/h2d_x_jb", "MC_gen_recon_corel/h2d_x_jb",

     "MC_gen_recon_corel/h2d_y_da",  "MC_gen_recon_corel/h2d_y_da", "MC_gen_recon_corel/h2d_y_da", 
     "MC_gen_recon_corel/h2d_y_e",  "MC_gen_recon_corel/h2d_y_e", "MC_gen_recon_corel/h2d_y_e", 
     "MC_gen_recon_corel/h2d_y_jb",  "MC_gen_recon_corel/h2d_y_jb", "MC_gen_recon_corel/h2d_y_jb",
     
     "Photon_with_jet/h2d_et_jet_et_photon", "Photon_with_jet/h2d_et_jet_et_photon", "Photon_with_jet/h2d_et_jet_et_photon", "Photon_with_jet/h2d_et_jet_et_photon",
     "Photon_with_jet/h2d_phijet_phigamma", "Photon_with_jet/h2d_phijet_phigamma", "Photon_with_jet/h2d_phijet_phigamma", "Photon_with_jet/h2d_phijet_phigamma", 
     "Photon_with_jet/h2d_dphijet_dphigamma", "Photon_with_jet/h2d_dphijet_dphigamma", "Photon_with_jet/h2d_dphijet_dphigamma", "Photon_with_jet/h2d_dphijet_dphigamma", 
     "Inclusive_DIS/h2d_Q2_x", "Inclusive_DIS/h2d_Q2_x", "Inclusive_DIS/h2d_Q2_x", "Inclusive_DIS/h2d_Q2_x",
     "Photon_with_jet/h2d_dphijet_dphigamma_sharp", "Photon_with_jet/h2d_dphijet_dphigamma_sharp", "Photon_with_jet/h2d_dphijet_dphigamma_sharp", "Photon_with_jet/h2d_dphijet_dphigamma_sharp" 
    };
  TString s_name[n_hist] = {"h2d_fmax_deltaz_data", "h2d_fmax_deltaz_norad", "h2d_fmax_deltaz_rad", "h2d_fmax_deltaz_prph",
			    "h2d_phjet_dphi_deta_data", "h2d_phjet_dphi_deta_norad", "h2d_phjet_dphi_deta_rad", "h2d_phjet_dphi_deta_prph",

			    "h2d_q2_da_signal",  "h2d_q2_da_norad", "h2d_q2_da_rad", 
			    "h2d_q2_e_signal",  "h2d_q2_e_norad", "h2d_q2_e_rad", 
			    "h2d_q2_jb_signal",  "h2d_q2_jb_norad", "h2d_q2_jb_rad",

			    "h2d_x_da_signal",  "h2d_x_da_norad", "h2d_x_da_rad", 
			    "h2d_x_e_signal",  "h2d_x_e_norad", "h2d_x_e_rad", 
			    "h2d_x_jb_signal",  "h2d_x_jb_norad", "h2d_x_jb_rad",

			    "h2d_y_da_signal",  "h2d_y_da_norad", "h2d_y_da_rad", 
			    "h2d_y_e_signal",  "h2d_y_e_norad", "h2d_y_e_rad", 
			    "h2d_y_jb_signal",  "h2d_y_jb_norad", "h2d_y_jb_rad",

			    "h2d_et_jet_et_photon_data", "h2d_et_jet_et_photon_norad", "h2d_et_jet_et_photon_rad", "h2d_et_jet_et_photon_prph",
			    "h2d_phijet_phigamma_data", "h2d_phijet_phigamma_norad", "h2d_phijet_phigamma_rad", "h2d_phijet_phigamma_prph",
			    "h2d_dphijet_dphigamma_data", "h2d_dphijet_dphigamma_norad", "h2d_dphijet_dphigamma_rad", "h2d_dphijet_dphigamma_prph",
			    "dis_Q2_x_data", "dis_Q2_x_norad", "dis_Q2_x_rad", "dis_Q2_x_prph",
			    "h2d_dphijet_dphigamma_data_sharp", "h2d_dphijet_dphigamma_norad_sharp", "h2d_dphijet_dphigamma_rad_sharp", "h2d_dphijet_dphigamma_prph_sharp"
  };
  TString s_xaxis[n_wind] = {"f_{max}", "f_{max}", "f_{max}", "f_{max}", 
			     "#phi_{jet}-#phi_{photon}", "#phi_{jet}-#phi_{photon}", "#phi_{jet}-#phi_{photon}", "#phi_{jet}-#phi_{photon}",

			     "Q^{2}_{da} - Q^{2}_{gen} (GeV^2)",   "Q^{2}_{da} - Q^{2}_{gen} (GeV^2)",   "Q^{2}_{da} - Q^{2}_{gen} (GeV^2)", 
			     "Q^{2}_{el} - Q^{2}_{gen} (GeV^2)",   "Q^{2}_{el} - Q^{2}_{gen} (GeV^2)",   "Q^{2}_{el} - Q^{2}_{gen} (GeV^2)", 
			     "Q^{2}_{jb} - Q^{2}_{gen} (GeV^2)",   "Q^{2}_{jb} - Q^{2}_{gen} (GeV^2)",   "Q^{2}_{jb} - Q^{2}_{gen} (GeV^2)", 

			     "x_{da} - x_{gen}", "x_{da} - x_{gen}", "x_{da} - x_{gen}", 
			     "x_{el} - x_{gen}", "x_{el} - x_{gen}", "x_{el} - x_{gen}", 
			     "x_{jb} - x_{gen}", "x_{jb} - x_{gen}", "x_{jb} - x_{gen}", 

			     "y_{da} - y_{gen}", "y_{da} - y_{gen}", "y_{da} - y_{gen}", 
			     "y_{el} - y_{gen}", "y_{el} - y_{gen}", "y_{el} - y_{gen}", 
			     "y_{jb} - y_{gen}", "y_{jb} - y_{gen}", "y_{jb} - y_{gen}",
			     
			     "E_{T, jet} (GeV)", "E_{T, jet} (GeV)", "E_{T, jet} (GeV)", "E_{T, jet} (GeV)", 
			     "#phi_{jet}", "#phi_{jet}", "#phi_{jet}", "#phi_{jet}", 
			     "#phi_{jet}-#phi_{electron}", "#phi_{jet}-#phi_{electron}", "#phi_{jet}-#phi_{electron}", "#phi_{jet}-#phi_{electron}", 
			     "Q^{2} (GeV)", "Q^{2} (GeV)", "Q^{2} (GeV)", "Q^{2} (GeV)",
			     "#phi_{jet}-#phi_{electron}", "#phi_{jet}-#phi_{electron}", "#phi_{jet}-#phi_{electron}", "#phi_{jet}-#phi_{electron}", 
  };

  TString s_yaxis[n_wind] = {"#delta z", "#delta z", "#delta z", "#delta z", 
			     "#eta_{jet}-#eta_{photon}", "#eta_{jet}-#eta_{photon}", "#eta_{jet}-#eta_{photon}", "#eta_{jet}-#eta_{photon}",

			     "Q^{2}_{gen} (GeV^2)",   "Q^{2}_{gen} (GeV^2)",   "Q^{2}_{gen} (GeV^2)", 
			     "Q^{2}_{gen} (GeV^2)",   "Q^{2}_{gen} (GeV^2)",   "Q^{2}_{gen} (GeV^2)", 
			     "Q^{2}_{gen} (GeV^2)",   "Q^{2}_{gen} (GeV^2)",   "Q^{2}_{gen} (GeV^2)", 

			     "x_{gen}", "x_{gen}", "x_{gen}", 
			     "x_{gen}", "x_{gen}", "x_{gen}", 
			     "x_{gen}", "x_{gen}", "x_{gen}", 

			     "y_{gen}", "y_{gen}", "y_{gen}", 
			     "y_{gen}", "y_{gen}", "y_{gen}", 
			     "y_{gen}", "y_{gen}", "y_{gen}",

			     "E_{T, photon} (GeV)", "E_{T, photon} (GeV)", "E_{T, photon} (GeV)", "E_{T, photon} (GeV)", 
			     "#phi_{photon}", "#phi_{photon}", "#phi_{photon}", "#phi_{photon}", 
			     "#phi_{photon}-#phi_{electron}", "#phi_{photon}-#phi_{electron}", "#phi_{photon}-#phi_{electron}", "#phi_{photon}-#phi_{electron}", 
			     "x_{Bj}", "x_{Bj}", "x_{Bj}", "x_{Bj}",
			     "#phi_{photon}-#phi_{electron}", "#phi_{photon}-#phi_{electron}", "#phi_{photon}-#phi_{electron}", "#phi_{photon}-#phi_{electron}", 
  };
  TString s_title[n_wind] = {"Data", "MC HH", "MC LL", "MC SIGNAL",
			     "Data", "MC HH", "MC LL", "MC SIGNAL",
			     "MC SIGNAL", "MC HH", "MC LL", 
			     "MC SIGNAL", "MC HH", "MC LL", 
			     "MC SIGNAL", "MC HH", "MC LL", 
			     "MC SIGNAL", "MC HH", "MC LL", 
			     "MC SIGNAL", "MC HH", "MC LL", 
			     "MC SIGNAL", "MC HH", "MC LL", 
			     "MC SIGNAL", "MC HH", "MC LL", 
			     "MC SIGNAL", "MC HH", "MC LL", 
			     "MC SIGNAL", "MC HH", "MC LL",
			     "Data", "MC HH", "MC LL", "MC SIGNAL",
			     "Data", "MC HH", "MC LL", "MC SIGNAL",
			     "Data", "MC HH", "MC LL", "MC SIGNAL",
			     "Data", "MC HH", "MC LL", "MC SIGNAL",
			     "Data", "MC HH", "MC LL", "MC SIGNAL"
  };
  // = {"Inclusive photon and photon + jet signal, data",
  //   "Inclusive photon and photon + jet signal, data",
  //   "Inclusive photon and photon + jet signal, MC HH",
  //   "Inclusive photon and photon + jet signal, MC HH",
  //   "Inclusive photon and photon + jet signal, MC LL",
  //  "Inclusive photon and photon + jet signal, MC LL",
  //			     "Inclusive photon and photon + jet signal, MC SIGNAL",
  //		     "Inclusive photon and photon + jet signal, MC SIGNAL"

  Double_t hist_xmin[n_wind] = {0., 0., 0., 0., -6.4, -6.4, -6.4, -6.4, 
				-200., -200., -200., -200., -200., -200., -200., -200., -200., 
				-0.015, -0.015, -0.015, -0.015, -0.015, -0.015, -0.015, -0.015, -0.015, 
				-0.36, -0.36, -0.36, -0.36, -0.36, -0.36, -0.36, -0.36, -0.36,
				2., 2., 2., 2., 
				-3.2, -3.2, -3.2, -3.2, 
				-6.4, -6.4, -6.4, -6.4, 
				5., 5., 5., 5.,
				-0.1, -0.1, -0.1, -0.1
  };
  Double_t hist_xmax[n_wind] = {1., 1., 1., 1., 6.4, 6.4, 6.4, 6.4,
				200., 200., 200., 200., 200., 200., 200., 200., 200.,
				0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015,
				0.36, 0.36, 0.36, 0.36, 0.36, 0.36, 0.36, 0.36, 0.36,
				30., 30., 30., 30., 
				3.2, 3.2, 3.2, 3.2, 
				6.4, 6.4, 6.4, 6.4, 
				400., 400., 400., 400.,
				3.2, 3.2, 3.2, 3.2
  };
  Double_t hist_ymin[n_wind] = {0., 0., 0., 0., -5., -5., -5., -5.,
				0., 0., 0., 0., 0., 0., 0., 0., 0.,
				0., 0., 0., 0., 0., 0., 0., 0., 0.,
				0., 0., 0., 0., 0., 0., 0., 0., 0. ,
				3, 3, 3, 3, 
				-3.2, -3.2, -3.2, -3.2, 
				-6.4, -6.4, -6.4, -6.4, 
				2.e-5, 2.e-5, 2.e-5, 2.e-5,
				-0.1, -0.1, -0.1, -0.1
  };
  Double_t hist_ymax[n_wind] = {1.5, 1.5, 1.5, 1.5, 5., 5., 5., 5.,
				400., 400., 400., 400., 400., 400., 400., 400., 400.,
				0.026, 0.026, 0.026, 0.026, 0.026, 0.026, 0.026, 0.026, 0.026,
 				0.72, 0.72, 0.72, 0.72, 0.72, 0.72, 0.72, 0.72, 0.72,
				16., 16., 16., 16., 
				3.2, 3.2, 3.2, 3.2, 
				6.4, 6.4, 6.4, 6.4, 
				2.e-1, 2e-1, 2.e-1, 2.e-1 ,
				3.2, 3.2, 3.2, 3.2
  };
  Int_t hist_line_width[n_hist];// = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
  Int_t hist_line_color[n_hist];// = {kBlue, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kBlack};
  Double_t hist_marker_size[n_hist];// = {0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7};
  Int_t hist_marker_style[n_hist];// = {20, 21, 20, 21, 20, 21, 20, 21, 20, 21, 20, 21, 20, 21, 20, 21};
  Int_t hist_marker_color[n_hist];// = {kBlue, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kBlack};
  
  TH2D *hist[n_hist];
  //  TH1D *hist1st[n_hist];
  TH1D *hist_ratio[n_hist];
  for(Int_t i=0; i<8; i++) {
    Int_t index = i%4;
    cout << "trying to read " << s_hist[i] << " from " << file[index]->GetName() << endl;
    file[index]->cd();
    hist[i] = (TH2D*)file[index]->Get(s_hist[i])->Clone();
    hist[i]->SetName(s_name[i]);
    hist[i]->SetLineWidth(hist_line_width[i]);
    hist[i]->SetLineColor(hist_line_color[i]);
    hist[i]->Sumw2();
  }
  for(Int_t i=0; i<8; i++)
    {
      if((i%4)!=3) {
      cout << "goto " << i << endl; 
      TString s;
      if(i%4 == 0) s = "data";
      if(i%4 == 1) s = "norad";
      if(i%4 == 2) s = "rad";
      if(i%4 == 3) s = "prph";
      AddAllPeriods(hist[i], i, s, s_hist[i]);
      }
    }
  for(Int_t i=8; i<8+27; i++) {
    Int_t index = 1;
    if((i-8)%3 == 0)
      index = 3;
    if((i-8)%3 == 1)
      index = 1;
    if((i-8)%3 == 2)
      index = 2;
    cout << "trying to read " << s_hist[i] << " from " << file[index]->GetName() << endl;
    file[index]->cd();
    hist[i] = (TH2D*)file[index]->Get(s_hist[i])->Clone();
    hist[i]->SetName(s_name[i]);
    cout << i << " " << hist[i]->GetName() << " " << hist[i]->Integral() << endl;
    hist[i]->SetLineWidth(hist_line_width[i]);
    hist[i]->SetLineColor(hist_line_color[i]);
    hist[i]->Sumw2();
  }

  for(Int_t i=8; i<8+27; i++)
    {
      if((i%3)!=2) {
      cout << "goto " << i << endl; 
      TString s;
      if(i%3 == 0) s = "norad";
      if(i%3 == 1) s = "rad";
      AddAllPeriods(hist[i], i, s, s_hist[i]);
      }
    }
  for(Int_t i=35; i<35+20; i++) {
    Int_t index = (i+1)%4;
    cout << "trying to read " << s_hist[i] << " from " << file[index]->GetName() << endl;
    file[index]->cd();
    hist[i] = (TH2D*)file[index]->Get(s_hist[i])->Clone();
    hist[i]->SetName(s_name[i]);
    hist[i]->SetLineWidth(hist_line_width[i]);
    hist[i]->SetLineColor(hist_line_color[i]);
    hist[i]->Sumw2();
  }
  for(Int_t i=35; i<35+20; i++)
    {
      if(((i+1)%4)!=3) {
      cout << "goto " << i << endl; 
      TString s;
      if(i%3 == 0) s = "data";
      if(i%3 == 1) s = "norad";
      if(i%3 == 2) s = "rad";
      AddAllPeriods(hist[i], i, s, s_hist[i]);
      }
    }
  cout << "histos succesfully read " << endl;

  cout << "going into histograms drawing " << endl;
  TH2D *h_window[n_wind];
  TH2D *h_window_ratio[n_wind];
  TF1 *f1 = new TF1("f1", "1.", 0., 1000.);
  f1->SetLineColor(39);
  f1->SetLineWidth(1);
  for(Int_t i=0; i<n_wind; i++) {
    TString s; s.Form("h_window%i", i);
    h_window[i] = new TH2D(s, "", 10, hist_xmin[i], hist_xmax[i], 10, hist_ymin[i], hist_ymax[i]);
    h_window_ratio[i] = new TH2D(s + "_ratio", "", 10, hist_xmin[i], hist_xmax[i], 10, 0., 2.);
  }

  const Int_t n_canv = 2 + 3 + 5;
  TCanvas* c1[n_canv];
  for(Int_t i=0; i<n_canv; i++) {
    TString s; s.Form("canvas_%i", i);
    c1[i] = new TCanvas(s, s, 1000, 1000);
  }
  for(Int_t i=0; i<2; i++) {
    c1[i]->Divide(2, 2);
    make_clean_pads(c1[i], 4, 0, 0);
  }
  for(Int_t i=2; i<2+3; i++) {
    c1[i]->Divide(3, 3);
    make_clean_pads(c1[i], 9, 0, 0);
  }
  for(Int_t i=5; i<5+5; i++) {
    c1[i]->Divide(2, 2);
    make_clean_pads(c1[i], 4, 0, 0);
  }
  for(Int_t i=0; i<8; i++)
    sign_window(c1[i/4]->GetPad(i%4 + 1), h_window[i], s_xaxis[i], s_yaxis[i], s_title[i], "middle");
  for(Int_t i=8; i<8+27; i++)
    sign_window(c1[2 + (i-8)/9]->GetPad((i-8)%9 + 1), h_window[i], s_xaxis[i], s_yaxis[i], s_title[i], "middle");
  for(Int_t i=35; i<35+20; i++)
    sign_window(c1[5 + (i-35)/4]->GetPad((i-35)%4 + 1), h_window[i], s_xaxis[i], s_yaxis[i], s_title[i], "middle");

  /*  const Int_t n_legs = n_wind; // :)
      TLegend *leg[n_legs];
      for(Int_t i=0; i<4; i++) {
      leg[2*i] = new TLegend(0.2, 0.6, 0.59, 0.87);
      leg[2*i+1] = new TLegend(0.5, 0.6, 0.86, 0.87);
      }
      for(Int_t i=0; i<n_legs; i++) {
      leg[i]->SetBorderSize(0);
      leg[i]->SetFillColor(0);
      }
      for(Int_t i=0; i<4; i++) {
      leg[2*i]->AddEntry(hist[0], "f_{max}, Photon + Jet", "l");
      leg[2*i]->AddEntry(hist[1], "f_{max}, Inclusive Photon", "l");
    
      leg[2*i+1]->AddEntry(hist[2], "#delta z, Photon + Jet", "l");
      leg[2*i+1]->AddEntry(hist[3], "#delta z, Inclusive Photon", "l");
      }*/
  //
  // data
  //
  for(Int_t i=0; i<8; i++) {
    c1[i/4]->GetPad(i%4 + 1)->cd();
    h_window[i]->DrawClone();
    hist[i]->Rebin2D(5, 5);
    hist[i]->DrawClone("COLZ SAME");  
  }

  for(Int_t i=8; i<8+27; i++) {
    c1[2 + (i-8)/9]->GetPad((i-8)%9 + 1)->cd();
    h_window[i]->DrawClone();
    hist[i]->DrawClone("COLZ SAME");  
  }

  

  for(Int_t i=35; i<35+20; i++) {
    c1[5 + (i-35)/4]->GetPad((i-35)%4 + 1)->cd();
    hist[i]->Rebin2D(10, 10);
    h_window[i]->DrawClone();
    hist[i]->DrawClone("COLZ SAME");  
  }

  for(Int_t i=0; i<n_canv; i++) {
    TString s; s.Form("%i", i);
    c1[i]->Print("prepare_plots2d"+s+".eps");
    c1[i]->Print("prepare_plots2d"+s+".png");
  }


  return 0;
}
void AddAllPeriods(TH2D* h, Int_t histogram_index, TString data_type, TString s_hist){
  cout << "here" << endl;
  Int_t index[2] = {0};
  TH2D* h_temp[2];
  if(data_type == "data") {
    index[0] = 4;
    index[1] = 7;
  }
  else
    if(data_type == "norad") {
      index[0] = 5;
      index[1] = 8;
    }
    else
      if(data_type == "rad") {
	index[0] = 6;
	index[1] = 9;
      }
      else {
	cerr << "in AddAllHistograms: Wrong data_type: " << data_type << endl;
	exit(-1);
      }
  
  for(Int_t i=0; i<2; i++) {
    cout << "cding to " << file[index[i]]->GetName() << endl;
    file[index[i]]->cd();
    h_temp[i] = (TH2D*)file[index[i]]->Get(s_hist)->Clone();
    h->Add(h_temp[i]);
  }
    
}
