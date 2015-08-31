#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include <TH1D.h>
#include <TFitter.h>
#include <TRandom3.h>
#include <TH2D.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TAxis.h>
#include <TGaxis.h>
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
TString fit_method = "fmax";//fmax, deltaz
Bool_t g_include_04p_data = kFALSE;
Int_t g_index_fmax = 0;
//Int_t g_index_fmax = 16;
//Int_t g_index_deltaz = 1;
Int_t g_index_deltaz= 1;

const Int_t n_hist = 50;
TString s_hist[n_hist];// = {/*"h_fmax", "h_deltaz",*/"h_incl_phot_fmax", "h_incl_phot_deltaz", "h_prph_energy", "h_comp_jet_e",  "h_comp_x", "h_comp_Q2", "h_phjet_electron_e", "h_phjet_electron_probability", "h_phjet_electron_theta", "h_prph_cell_energy_frac", "h_prph_jet_energy_frac", "h_prph_phi", "h_prph_eta", "h_x_gamma", /*"h_incl_phot_deltaz", "h_incl_phot_fmax"*/"h_deltaz", "h_fmax", "h_phjet_jet_phi", "h_phjet_jet_eta", "h_phjet_dphi", "h_phjet_deta"};
//for(Int_t i=2; i<16; i++)
//  s_hist[i] = "Photon_with_jet/" + s_hist[i];
//for(Int_t i=0; i<2; i++)
//  s_hist[i] = "Inclusive_Photon/" + s_hist[i];

TString s_xaxis[n_hist];// = {"f_{max}", "#delta z", "E_{T, photon} (GeV)", "E_{T, jet} (GeV)", "x_{Bj}", "Q^{2} (GeV^{2})", 
//   "E_{electron} (GeV)", "Sinistra Probability", "#theta_{electron}", "EMC energy fraction", "jet energy fraction",
//			     "#phi_{photon}", "#eta_{photon}", "x_{gamma}", "#delta z", "f_{max}",
//		     "#phi_{jet}", "#eta_{jet}", "#phi_{jet} - #phi_{photon}", "#eta_{jet} - #eta_{photon}"};
Double_t hist_xmin[n_hist];// = {0., 0., 2., 0., 2.e-4, 0., 9., 0.89, 130., 0.89, 0.89, -3.5, -0.8, 0., 0., 0.};
Double_t hist_xmax[n_hist];// = {1., 1.5, 16., 35.,2.e-2, 400., 35., 1., 180., 1.01, 1.01, 3.5, 1., 1.2, 1.5, 1.};
Double_t hist_ymin[n_hist];// = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
Bool_t hist_logy[n_hist];
Int_t hist_rebin[n_hist];
TRandom3 *random_gen;
const Int_t n_periods = 3;
TH1D *hist_mc[n_periods][n_hist];
TH1D *hist_mc_norad[n_periods][n_hist];
TH1D *hist_mc_rad[n_periods][n_hist];
TH1D *hist_data[n_periods][n_hist];
TH1D *hist_data04p[n_hist];
TH1D *hist_mc_sum[n_hist];
TH1D *hist_mc_norad_sum[n_hist];
TH1D *hist_mc_rad_sum[n_hist];
TH1D *hist_data_sum[n_hist];
TH1D *hist_mc_photon_sum[n_hist];
TH1D *hist_mc_sum_copy[n_hist];
TH1D *hist_mc_norad_sum_copy[n_hist];
TH1D *hist_mc_rad_sum_copy[n_hist];
TH1D *hist_data_sum_copy[n_hist];
TH1D *hist_mc_photon_sum_copy[n_hist];
TH1D *hist_mc_sum_ian;
TH1D *hist_mc_norad_sum_ian;
TH1D *hist_mc_rad_sum_ian;
TH1D *hist_data_sum_ian;
TH1D *hist_ratio[n_hist];
TH1D *hist_res[n_hist];
void variate_bin_content_Gaus(TH1D* h);
void set_hist_atributes(Int_t number, TString name, TString dir, TString xaxis, Double_t xmin, Double_t xmax, Double_t ymin, Bool_t logy, Int_t rebin);
void minuitFunctionBarlowBeeston(int& nDim, double* gout, double& result, double par[], int flg);
void minuitFunctionGauss(int& nDim, double* gout, double& result, double par[], int flg);
Double_t chi2(double* par, Int_t& ndf, Double_t& left, Double_t& right, TString s_method);

int main(int argc, char *argv[])
{
  gROOT->SetStyle("Plain");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleH(0.08);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleY(0.99);
  gStyle->SetTitleX(0.15);
  random_gen = new TRandom3();
  TH1D*  hist_check_fit_error = new TH1D("hist_check_fit_error", "photon fraction", 500, 0., 1.);
  set_hist_atributes(0, "h_fmax", "Photon_with_jet", "f_{max}", 0, 1, 0.1, kFALSE, 10);
  set_hist_atributes(1, "h_deltaz", "Photon_with_jet", "#delta z", 0, 1.5, 0.1, kFALSE, 10);
  set_hist_atributes(2,  "h_prph_energy", "Photon_with_jet", "E_{T, photon} (GeV)", 2, 16, 0.1, kFALSE, 10);

  set_hist_atributes(3,  "h_comp_Q2", "Photon_with_jet", "Q^{2} (GeV^{2})", 0, 400, 0.1, kTRUE, 10);
  set_hist_atributes(4,  "h_comp_x", "Photon_with_jet", "x_{Bj}", 0.0002, 0.02, 0.1, kTRUE, 5);
  set_hist_atributes(5,  "h_comp_y", "Photon_with_jet", "y", 0.0, 0.7, 0.1, kTRUE, 5);

  set_hist_atributes(6,  "h_phjet_electron_e", "Photon_with_jet", "E_{electron} (GeV)", 9, 35, 0.1, kFALSE, 10);
  set_hist_atributes(7,  "h_phjet_electron_theta", "Photon_with_jet", "#theta_{electron}", 130, 180, 0.1, kFALSE, 10);
  set_hist_atributes(8,  "h_phjet_electron_phi", "Photon_with_jet", "#phi_{electron}", -3.5, 3.5, 0.1, kFALSE, 5);

  set_hist_atributes(9,  "h_phjet_zufo_empz", "Photon_with_jet", "E-P_{z} (GeV)", 30, 70, 0.1, kFALSE, 10);
  set_hist_atributes(10, "h_phjet_zvtx", "Photon_with_jet", "Z_{vtx} (cm)", -50., 50., 0.1, kFALSE, 10);
  set_hist_atributes(11, "h_x_gamma", "Photon_with_jet", "x_{#gamma}", 0, 1.2, 0.1, kFALSE, 10);

  set_hist_atributes(12,  "h_prph_energy", "Photon_with_jet", "E_{T, photon} (GeV)", 2, 16, 0.1, kFALSE, 10);
  set_hist_atributes(13, "h_prph_eta", "Photon_with_jet", "#eta_{photon}", -0.8, 1, 0.1, kFALSE, 10);
  set_hist_atributes(14, "h_prph_phi", "Photon_with_jet", "#phi_{photon}", -3.5, 3.5, 0.1, kFALSE, 10);

  set_hist_atributes(15, "h_comp_jet_e", "Photon_with_jet", "E_{T, jet} (GeV)", 0, 45, 0.1, kTRUE, 1);
  set_hist_atributes(16, "h_phjet_jet_eta", "Photon_with_jet", "#eta_{jet}", -1.6, 1.9, 0.1, kFALSE, 10);
  set_hist_atributes(17, "h_phjet_jet_phi", "Photon_with_jet", "#phi_{jet}", -3.5, 3.5, 0.1, kFALSE, 10);

  set_hist_atributes(18, "h_et_jet_photon_ratio", "Photon_with_jet", "E_{T, jet} / E_{T, photon}", 0., 20., 0.1, kTRUE, 5);
  set_hist_atributes(19,  "h_prph_cell_energy_frac", "Photon_with_jet", "EMC energy fraction", 0.89, 1.01, 0.1, kTRUE, 10);
  set_hist_atributes(20, "h_prph_jet_energy_frac", "Photon_with_jet", "jet energy fraction", 0.89, 1.01, 0.1, kTRUE, 10);

  set_hist_atributes(21, "h_phjet_dphi", "Photon_with_jet", "#phi_{jet} - #phi_{photon}", -6.3, 6.3, 0.1, kFALSE, 10);
  set_hist_atributes(22, "h_et_3system_event_ratio", "Photon_with_jet", "(E_{T, #gamma} + E_{T, jet} + E_{T, electron}) / E_{T, event}", 0., 1., 0.1, kFALSE, 10);
  set_hist_atributes(23,  "h_phjet_electron_probability", "Photon_with_jet", "Sinistra Probability", 0.89, 1, 0.1, kTRUE, 10);
  //inclusive photon
  //  set_hist_atributes(18,  "h_incl_phot_deltaz", "Inclusive_Photon", "#delta z", 0, 1.5, 0.1, kFALSE, 10);
  //  set_hist_atributes(19,  "h_incl_phot_fmax",  "Inclusive_Photon", "f_{max}", 0, 1, 0.1, kFALSE, 10);
  //  set_hist_atributes(20, "h_incl_phot_phi", "Inclusive_Photon", "#phi_{photon}", -3.5, 3.5, 0.1, kFALSE, 10);
  //  set_hist_atributes(21, "h_incl_phot_eta", "Inclusive_Photon", "#eta_{photon}", -1., 1., 0.1, kFALSE, 5);
  //  set_hist_atributes(20, "h_incl_phot_elphot_deta", "Inclusive_Photon", "#phi_{photon} - #phi_{electron}", -6.4, 6.4, 0.1, kFALSE, 10);
  //  set_hist_atributes(22, "h_incl_phot_elphot_dphi", "Inclusive_Photon", "#eta_{photon} - #eta_{electron}", 0., 4., 0.1, kFALSE, 4);
  //  set_hist_atributes(23, "h_incl_phot_elphot_dphi", "Inclusive_Photon", "#eta_{photon} - #eta_{electron}", 0., 4., 0.1, kFALSE, 4);
  //inclusive DIS
  //  set_hist_atributes(24, "h_Q2_da", "Inclusive_DIS", "Q^{2}_{da} (GeV^{2})", 0., 400., 0.1, kTRUE, 10);

  /*  set_hist_atributes(24, "h_det_cross_et", "Cross_Sections_Histograms", "", 0., 1., 0.1, kTRUE, 1);
  set_hist_atributes(25, "h_det_cross_eta", "Cross_Sections_Histograms", "", 0., 1., 0.1, kTRUE, 1);
  set_hist_atributes(26, "h_det_cross_Q2", "Cross_Sections_Histograms", "", 0., 1., 0.1, kTRUE, 1);
  set_hist_atributes(27, "h_det_cross_x", "Cross_Sections_Histograms", "", 0., 1., 0.1, kTRUE, 1);
  set_hist_atributes(28, "h_det_cross_et_jet", "Cross_Sections_Histograms", "", 0., 1., 0.1, kTRUE, 1);
  set_hist_atributes(29, "h_det_cross_eta_jet", "Cross_Sections_Histograms", "", 0., 1., 0.1, kTRUE, 1);*/
  set_hist_atributes(24, "h_y_el", "Inclusive_DIS", "y_{el}", 0., 1., 0.1, kTRUE, 1);
  set_hist_atributes(25, "h_Q2_el", "Inclusive_DIS", "Q^{2}_{el} (GeV^{2})", 0., 400., 0.1, kTRUE, 10);
  set_hist_atributes(26, "h_Q2_jb", "Inclusive_DIS", "Q^{2}_{jb} (GeV^{2})", 0., 400., 0.1, kTRUE, 10);
  set_hist_atributes(27, "h_elec_zufo_dr_min", "Inclusive_DIS", "#delta r(#eta, #phi) betw. elec. and clos. zufo", 0., 1., 0.1, kTRUE, 5);
  set_hist_atributes(28, "h_cal_empz", "Inclusive_DIS", "E - p_{z} (GeV)", 34., 65., 0.1, kFALSE, 10);
  set_hist_atributes(29, "h_dis_electron_e", "Inclusive_DIS", "E_{e} (GeV)", 8., 35., 0.1, kFALSE, 10);
  set_hist_atributes(30, "h_dis_electron_theta", "Inclusive_DIS", "#theta_{electron}", 135., 180., 0.1, kFALSE, 10);
  set_hist_atributes(31, "h_dis_electron_probability", "Inclusive_DIS", "Sinistra Probability", 0.89, 1.01, 0.1, kTRUE, 10);
  set_hist_atributes(32, "h_n_vtx_tracks", "Inclusive_DIS", "N_{vertex tracks}", 0., 50., 0.1, kTRUE, 10);
  set_hist_atributes(33, "h_siyjb", "Inclusive_DIS", "Siyjb", 0., 0.8, 0.1, kTRUE, 10);
  set_hist_atributes(34, "h_x_el", "Inclusive_DIS", "x_{el}", 0., 1., 0.1, kTRUE, 20);
  set_hist_atributes(35, "h_zvtx", "Inclusive_DIS", "Z_{vtx}", -45., 45., 0.1, kTRUE, 5);
  set_hist_atributes(36, "h_zufos_near_electron", "Inclusive_DIS", "N. of zufos in cone r=0.2 near elec.", 0., 7., 0.1, kTRUE, 10);
  set_hist_atributes(37, "h_dis_px_event", "Inclusive_DIS", "P_{x, event} (zufos) (GeV)", -30., 30., 0.1, kTRUE, 1);
  set_hist_atributes(38, "h_dis_py_event", "Inclusive_DIS", "P_{y, event} (zufos) (GeV)", -30., 30., 0.1, kTRUE, 1);
  set_hist_atributes(39, "h_dis_pz_event", "Inclusive_DIS", "P_{z, event} (zufos) (GeV)", -100., 800., 0.1, kTRUE, 1);
  set_hist_atributes(40, "h_dis_pt_event", "Inclusive_DIS", "P_{T, event} (zufos) (GeV)", 0., 200., 0.1, kTRUE, 1);
  set_hist_atributes(41, "h_dis_e_event", "Inclusive_DIS", "E_{event} (zufos) (GeV)", 0., 1.e3, 0.1, kTRUE, 1);
  set_hist_atributes(42, "h_dis_et_event", "Inclusive_DIS", "E_{T} of event (zufos) (GeV)", 0., 300., 0.1, kTRUE, 1);
  set_hist_atributes(43, "h_pt_sqrtet", "Inclusive_DIS", "P_{T}/#sqrt{E_{T}} (GeV^{1/2})", 0., 20., 0.1, kTRUE, 5);
  set_hist_atributes(44, "h_dis_n_zufos", "Inclusive_DIS", "N_{zufos}", 0., 200., 0.1, kTRUE, 1);
  set_hist_atributes(45, "h_dis_cal", "Inclusive_DIS", "Total Cal. Energy (zufos) (GeV)", 0., 700., 0.1, kTRUE, 5);
  set_hist_atributes(46, "h_dis_emc", "Inclusive_DIS", "EMC Cal. Energy (zufos) (GeV)", 0., 700., 0.1, kTRUE, 5);
  set_hist_atributes(47, "h_dis_had", "Inclusive_DIS", "HAD Cal. Energy (zufos) (GeV)", 0., 700., 0.1, kTRUE, 5);
  set_hist_atributes(48, "h_dis_had_tot_ratio", "Inclusive_DIS", "E_{HAD}/(E_{HAD}+E_{EMC})", 0., 1., 0.1, kTRUE, 5);
  set_hist_atributes(49, "h_dis_zufo_type", "Inclusive_DIS", "tufo", 0., 42., 0.1, kTRUE, 1);
  //  set_hist_atributes(50, "h_zufos_near_electron", "Inclusive_DIS", "N. of zufos in cone r=0.2 near elec.", 0., 7., 0.1, kTRUE, 10);
  //  set_hist_atributes(31, "h_x_el", "Inclusive_DIS", "x_{el}", 0., 1., 0.1, kTRUE, 10);
  //  set_hist_atributes(32, "h_x_el", "Inclusive_DIS", "x_{el}", 0., 1., 0.1, kTRUE, 10);
  //  set_hist_atributes(19, "h_phjet_deta", "Photon_with_jet", "#eta_{jet} - #eta_{photon}", -2.8, 2.8, 0.1);

  //  "h_phjet_jet_phi", "h_phjet_jet_eta", "h_phjet_dphi", "h_phjet_deta"};
  // "#phi_{jet}", "#eta_{jet}", "#phi_{jet} - #phi_{photon}", "#eta_{jet} - #eta_{photon}"}

  TString s_period[n_periods] = {"0405e", "06e", "0607p"};
  TFile *file[n_periods][4];
  TFile *file_data04p;
  
  //  TString s_hist[n_hist] = {"h_fmax", "h_deltaz", "h_prph_energy", "h_comp_jet_e",  "h_comp_x", "h_comp_Q2", "h_phjet_electron_e", "h_phjet_electron_probability", "h_phjet_electron_theta", "h_prph_cell_energy_frac", "h_prph_jet_energy_frac", "h_prph_phi", "h_prph_eta", "h_x_gamma", "h_incl_phot_deltaz", "h_incl_phot_fmax"};

  //  TString s_yaxis[n_hist] = {"a", "Events", "Events", "Events"};
  for(Int_t p=0; p<n_periods; p++) {
    cout << "opening file data " <<  s_period[p] << endl;
    file[p][0] =  new TFile("../data" + s_period[p] + ".root");
    cout << "opening file mc_bg_norad " <<  s_period[p] << endl;
    file[p][1] =  new TFile("../mc_bg_norad" + s_period[p] + ".root");
    cout << "opening file mc_bg_rad " <<  s_period[p] << endl;
    file[p][2] =  new TFile("../mc_bg_rad" + s_period[p] + ".root");
    if(s_period[p]!="0607p") {
      cout << "opening file mc_prph " <<  s_period[p] << endl;
      file[p][3] =  new TFile("../mc_prph" + s_period[p] + ".root");
    }
    cout << s_period[p] << " files attached" << endl;
    for(Int_t i=0; i<n_hist; i++)
      {
	cout << "reading " << s_hist[i] << endl;
	if(s_period[p]!="0607p") {
	  file[p][3]->cd();
	  cout << "reading mc_prph "  << i << " ..." << endl;
	  hist_mc[p][i] = (TH1D*)file[p][3]->Get(s_hist[i])->Clone();
	  hist_mc[p][i]->SetName(s_hist[i]+"_mc_signal" + s_period[p]);
	}
	file[p][2]->cd();
	cout << "reading mc_rad "  << i << " ..." << endl;
	hist_mc_rad[p][i] = (TH1D*)file[p][2]->Get(s_hist[i])->Clone();
	hist_mc_rad[p][i]->SetName(s_hist[i]+"_mc_rad" + s_period[p]);

	file[p][1]->cd();
	cout << "reading mc_norad "  << i << " ..." << endl;
	hist_mc_norad[p][i] = (TH1D*)file[p][1]->Get(s_hist[i])->Clone();
	hist_mc_norad[p][i]->SetName(s_hist[i]+"_mc_norad" + s_period[p]);

	file[p][0]->cd();
	cout << "reading data "  << i << " ..." << endl;
	hist_data[p][i] = (TH1D*)file[p][0]->Get(s_hist[i])->Clone();
	hist_data[p][i]->SetName(s_hist[i]+"_data" + s_period[p]);

	/*	if(s_period[p]!="0607p")
		hist_mc[p][i]->Sumw2();
		hist_mc_rad[p][i]->Sumw2();
		hist_mc_norad[p][i]->Sumw2();
		hist_data[p][i]->Sumw2();*/
	//	hist_ratio[i]->Sumw2();
	//      hist_res[i]->Sumw2();
      }
  }
  cout << "histos succesfully read" << endl;

  //sum histograms for periods

  for(Int_t i=0; i<n_hist; i++)
    {      
      if(g_include_04p_data) {
	file_data04p->cd();
	hist_data04p[i] = (TH1D*)file_data04p->Get(s_hist[i])->Clone();
	hist_data04p[i]->SetName(s_hist[i]+"_data04p");    
	hist_data04p[i]->Sumw2();
      }
      
      hist_ratio[i] = (TH1D*) hist_data[0][i]->Clone();
      hist_ratio[i]->SetName(s_hist[i]+"_ratio");
      hist_ratio[i]->SetLineColor(kBlue);

      hist_mc_sum[i] = (TH1D*) hist_mc[0][i]->Clone();
      //	hist_mc_sum[i]->Sumw2();
      hist_mc_sum[i]->SetName(s_hist[i]+"_mc_signal");
      hist_mc_sum[i]->SetLineColor(kBlue);

      hist_mc_rad_sum[i] = (TH1D*) hist_mc_rad[0][i]->Clone();
      hist_mc_rad_sum[i]->SetName(s_hist[i]+"_mc_rad");
      hist_mc_rad_sum[i]->SetLineColor(kRed);

      hist_mc_norad_sum[i] = (TH1D*) hist_mc_norad[0][i]->Clone();
      hist_mc_norad_sum[i]->SetName(s_hist[i]+"_mc_norad");
      hist_mc_norad_sum[i]->SetLineColor(40);

      hist_data_sum[i] = (TH1D*) hist_data[0][i]->Clone();
      hist_data_sum[i]->SetName(s_hist[i]+"_data");
      hist_data_sum[i]->SetMarkerStyle(24);
      hist_data_sum[i]->SetMarkerSize(0.2);
    }

  for(Int_t i=0; i<n_hist; i++)
    {
      for(Int_t p=1; p<n_periods; p++)
	{
	  cerr << i << " " << p << " adding :" << hist_data[p][i]->GetName() << endl;
	  hist_data_sum[i]->Add(hist_data[p][i]);
	  cerr << hist_data[p][i]->GetNbinsX() << endl;
	  cerr << "data - ok" << endl;
	}
    }

  //  Int_t n_parts[6] = {4, 4, 4, 4, 4, 4};
  Int_t n_parts[6] = {6, 6, 6, 6, 6, 6};
  Int_t index[6] = {3, 4, 12, 13, 15, 16};
  //  Int_t index[6] = {24, 25, 26, 27, 28, 29};
  for(Int_t i=0; i<6; i++) {
    //  if(i==3 || i==4 || i==12 || i==13 || i==15 || i==16) {
    cout << "================================================" << s_hist[index[i]] << "==========================" << endl;
    cout << "define binning for " << s_hist[index[i]] << endl;
    Int_t nbins = hist_data_sum[index[i]]->GetNbinsX();
    //    for(Int_t h=0; h<nbins; h++)
    //      cout << "bin content " << h+1 << ": " << hist_data_sum[index[i]]->GetBinContent(h+1) << " with low edge " 
    //	   << hist_data_sum[index[i]]->GetBinLowEdge(h+1) << endl;
    cout << nbins << " bins from " << hist_data_sum[index[i]]->GetBinLowEdge(1) << " to " 
	 << hist_data_sum[index[i]]->GetBinLowEdge(nbins) + hist_data_sum[index[i]]->GetBinWidth(nbins) << endl;
    cout << "0th bin: " << hist_data_sum[index[i]]->GetBinContent(0) << ", overlast: " << hist_data_sum[index[i]]->GetBinContent(nbins+1) << endl;
    cout << "N entries = " << hist_data_sum[index[i]]->GetEntries() << ", Integral = " << hist_data_sum[index[i]]->Integral() << endl;
    cout << "maximum stored = " << hist_data_sum[index[i]]->GetMaximumBin() << endl;
    for(Int_t j=1; j<n_parts[i]; j++)
      {
	Double_t accum = double(j)/double(n_parts[i]);
	for(Int_t b=1; b<nbins; b++) {
	  Double_t integral = hist_data_sum[index[i]]->Integral(1, 1+b)/hist_data_sum[index[i]]->Integral();
	  Double_t next_integral = hist_data_sum[index[i]]->Integral(1, 1+1+b)/hist_data_sum[index[i]]->Integral();
	  //	  cout << "iter " << b << " " << integral << " " << next_integral << endl;
	  if(accum >= integral && accum < next_integral){
	    cout << "j = " << j << ", b = " << b << endl;
	    cout << "bins: " << hist_data_sum[index[i]]->GetBinLowEdge(1+b+1)
		 << " " << accum << " " << integral << " " << next_integral << endl;
	    break;
	  }
	}
      }
    //  }
  }
  cerr << "done" << endl;
  return 0;
}

void set_hist_atributes(Int_t number, TString name, TString dir, TString xaxis, Double_t xmin, Double_t xmax, Double_t ymin, Bool_t logy, Int_t rebin)
{
  if(dir!= "")
    s_hist[number] = dir + "/" + name;
  else
    s_hist[number] = name;

  s_xaxis[number] = xaxis;
  hist_xmin[number] = xmin;
  hist_xmax[number] = xmax;
  hist_ymin[number] = ymin;
  hist_logy[number] = logy;
  hist_rebin[number] = rebin;
}
