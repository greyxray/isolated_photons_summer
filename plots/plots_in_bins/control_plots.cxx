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
#include "../../inc/constants.h"
//#include "plot_style_utils.h"
TString fit_method = "deltaz";//fmax, deltaz
Bool_t g_include_04p_data = kFALSE;
Int_t g_index_fmax = 0;
//Int_t g_index_fmax = 16;
//Int_t g_index_deltaz = 1;
Int_t g_index_deltaz= 1;

const Int_t n_hist = 57;
TString s_hist[n_hist];
TString s_xaxis[n_hist];
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
  set_hist_atributes(1, "h_deltaz_eta_0", "Cross_Sections_Histograms"/*"Photon_with_jet"*/, "#delta z", 0, 1.5, 0.1, kFALSE, 10);
  set_hist_atributes(2,  "h_prph_energy", "Photon_with_jet", "E_{T, photon} (GeV)", 2, 16, 0.1, kFALSE, 10);

  set_hist_atributes(3,  "h_comp_Q2", "Photon_with_jet", "Q^{2} (GeV^{2})", 0, 400, 0.1, kTRUE, 10);
  set_hist_atributes(4,  "h_comp_x", "Photon_with_jet", "x", 0.0002, 0.02, 0.1, kTRUE, 5);
  set_hist_atributes(5,  "h_comp_y", "Photon_with_jet", "y", 0.0, 0.7, 0.1, kTRUE, 5);
  //  set_hist_atributes(5, "h_phjet_zvtx", "Photon_with_jet", "Z_{vtx} (cm)", -50., 50., 0.1, kFALSE, 10);

  set_hist_atributes(6,  "h_phjet_electron_e", "Photon_with_jet", "E_{electron} (GeV)", 9, 35, 0.1, kFALSE, 10);
  set_hist_atributes(7,  "h_phjet_electron_theta", "Photon_with_jet", "#theta_{electron}", 130, 180, 0.1, kFALSE, 10);
  set_hist_atributes(8,  "h_phjet_electron_phi", "Photon_with_jet", "#phi_{electron}", -3.5, 3.5, 0.1, kFALSE, 5);

  set_hist_atributes(9,  "h_phjet_cal_empz", "Photon_with_jet", "cal E-P_{z} (GeV)", 30, 70, 0.1, kFALSE, 10);
  set_hist_atributes(10, "h_phjet_zvtx", "Photon_with_jet", "Z_{vtx} (cm)", -50., 50., 0.1, kFALSE, 10);
  set_hist_atributes(11, "h_x_gamma", "Photon_with_jet", "x_{#gamma}", 0, 1.2, 0.1, kFALSE, 10);

  set_hist_atributes(12,  "h_prph_energy", "Photon_with_jet", "E_{T, photon} (GeV)", 2, 16, 0.1, kFALSE, 10);
  set_hist_atributes(13, "h_prph_eta", "Photon_with_jet", "#eta_{photon}", -0.8, 1, 0.1, kFALSE, 10);
  set_hist_atributes(14, "h_prph_phi", "Photon_with_jet", "#phi_{photon}", -3.5, 3.5, 0.1, kFALSE, 10);

  set_hist_atributes(15, "h_comp_jet_e", "Photon_with_jet", "E_{T, jet} (GeV)", 0, 45, 0.1, kTRUE, 20);
  set_hist_atributes(16, "h_phjet_jet_eta", "Photon_with_jet", "#eta_{jet}", -1.6, 1.9, 0.1, kFALSE, 10);
  set_hist_atributes(17, "h_phjet_jet_phi", "Photon_with_jet", "#phi_{jet}", -3.5, 3.5, 0.1, kFALSE, 10);

  set_hist_atributes(18, "h_et_jet_photon_ratio", "Photon_with_jet", "E_{T, jet} / E_{T, photon}", 0., 8., 0.1, kTRUE, 5);
  set_hist_atributes(19,  "h_prph_cell_energy_frac", "Photon_with_jet", "EMC energy fraction", 0.89, 1.01, 0.1, kTRUE, 10);
  set_hist_atributes(20, "h_prph_jet_energy_frac", "Photon_with_jet", "jet energy fraction", 0.89, 1.01, 0.1, kTRUE, 10);

  set_hist_atributes(21, "h_phjet_dphi", "Photon_with_jet", "#phi_{jet} - #phi_{photon}", 0., 3.4, 0.1, kFALSE, 10);
  set_hist_atributes(22, "h_et_3system_event_ratio", "Photon_with_jet", "(E_{T, #gamma} + E_{T, jet} + E_{T, electron}) / E_{T, event}", 0., 1., 0.1, kFALSE, 10);
  set_hist_atributes(23,  "h_phjet_electron_probability", "Photon_with_jet", "Sinistra Probability", 0.89, 1, 0.1, kTRUE, 10);

  set_hist_atributes(24,  "h_phjet_q2_dz_gt_035", "Photon_with_jet", "Q^{2} (GeV^{2}) (#delta z > 0.35)", 10., 400., 0.1, kTRUE, 20);
  set_hist_atributes(25,  "h_phjet_q2_dz_lt_035", "Photon_with_jet", "Q^{2} (GeV^{2}) (#delta z < 0.35)", 10., 400., 0.1, kTRUE, 20);
  set_hist_atributes(26,  "h_phjet_q2_dz_full", "Photon_with_jet", "Q^{2} (GeV^{2})", 10., 400., 0.1, kTRUE, 20);

  set_hist_atributes(27,  "h_phjet_y_dz_gt_035", "Photon_with_jet", "y (#delta z > 0.35)", 0., 1., 0.1, kFALSE, 20);
  set_hist_atributes(28,  "h_phjet_y_dz_lt_035", "Photon_with_jet", "y (#delta z < 0.35)", 0., 1., 0.1, kFALSE, 20);
  set_hist_atributes(29,  "h_phjet_y_dz_full", "Photon_with_jet", "y", 0., 1., 0.1, kFALSE, 20);

  set_hist_atributes(30,  "h_phjet_etaph_dz_gt_035", "Photon_with_jet", "#eta^{#gamma} (#delta z > 0.35)", -0.7, 0.9, 0.1, kFALSE, 80);
  set_hist_atributes(31,  "h_phjet_etaph_dz_lt_035", "Photon_with_jet", "#eta^{#gamma} (#delta z < 0.35)", -0.7, 0.9, 0.1, kFALSE, 80);
  set_hist_atributes(32,  "h_phjet_etaph_dz_full", "Photon_with_jet", "#eta^{#gamma}", -0.7, 0.9, 0.1, kFALSE, 80);

  set_hist_atributes(33,  "h_phjet_eph_dz_gt_035", "Photon_with_jet", "E^{#gamma} (GeV) (#delta z > 0.35)", 4., 25., 0.1, kFALSE, 80);
  set_hist_atributes(34,  "h_phjet_eph_dz_lt_035", "Photon_with_jet", "E^{#gamma} (GeV) (#delta z < 0.35)", 4., 25., 0.1, kFALSE, 80);
  set_hist_atributes(35,  "h_phjet_eph_dz_full", "Photon_with_jet", "E^{#gamma} (GeV)", 4., 25., 0.1, kFALSE, 80);

  set_hist_atributes(36,  "h_phjet_eel_dz_gt_035", "Photon_with_jet", "E^{el} (GeV) (#delta z > 0.35)", 10., 30., 0.1, kFALSE, 80);
  set_hist_atributes(37,  "h_phjet_eel_dz_lt_035", "Photon_with_jet", "E^{el} (GeV) (#delta z < 0.35)", 10., 30., 0.1, kFALSE, 80);
  set_hist_atributes(38,  "h_phjet_eel_dz_full", "Photon_with_jet", "E^{el} (GeV)", 10., 30., 0.1, kFALSE, 80);

  set_hist_atributes(39,  "phjet_y_y_gt_05", "Photon_with_jet", "y (y > 0.5)", 0., 1., 0.1, kFALSE, 1);
  set_hist_atributes(40,  "phjet_y_y_lt_05", "Photon_with_jet", "y (y < 0.5)", 0., 1., 0.1, kFALSE, 1);
  set_hist_atributes(41,  "phjet_y_y_lt_05", "Photon_with_jet", "y (y < 0.5)", 0., 1., 0.1, kFALSE, 1);

  set_hist_atributes(42,  "phjet_eel_y_gt_05", "Photon_with_jet", "E^{el} (GeV) (y > 0.5)", 10., 30., 0.1, kFALSE, 1);
  set_hist_atributes(43,  "phjet_eel_y_lt_05", "Photon_with_jet", "E^{el} (GeV) (y < 0.5)", 10., 30., 0.1, kFALSE, 1);
  set_hist_atributes(44,  "phjet_eel_y_lt_05", "Photon_with_jet", "E^{el} (GeV) (y < 0.5)", 10., 30., 0.1, kFALSE, 1);

  set_hist_atributes(45,  "phjet_phiph_phij_y_gt_05", "Photon_with_jet", "#phi^{#gamma} - #phi^{jet} (y > 0.5)", 0., 3.2, 0.1, kFALSE, 1);
  set_hist_atributes(46,  "phjet_phiph_phij_y_lt_05", "Photon_with_jet", "#phi^{#gamma} - #phi^{jet} (y < 0.5)", 0., 3.2, 0.1, kFALSE, 1);
  set_hist_atributes(47,  "phjet_phiph_phij_y_lt_05", "Photon_with_jet", "#phi^{#gamma} - #phi^{jet} (y < 0.5)", 0., 3.2, 0.1, kFALSE, 1);

  set_hist_atributes(48,  "phjet_thetael_y_gt_05", "Photon_with_jet", "#theta^{el} (y > 0.5)", 2., 3.2, 0.1, kFALSE, 1);
  set_hist_atributes(49,  "phjet_thetael_y_lt_05", "Photon_with_jet", "#theta^{el} (y < 0.5)", 2., 3.2, 0.1, kFALSE, 1);
  set_hist_atributes(50,  "phjet_thetael_y_lt_05", "Photon_with_jet", "#theta^{el} (y < 0.5)", 2., 3.2, 0.1, kFALSE, 1);

  set_hist_atributes(51,  "phjet_etaph_y_gt_05", "Photon_with_jet", "#eta^{#gamma} (y > 0.5)", -0.7, 0.9, 0.1, kFALSE, 1);
  set_hist_atributes(52,  "phjet_etaph_y_lt_05", "Photon_with_jet", "#eta^{#gamma} (y < 0.5)", -0.7, 0.9, 0.1, kFALSE, 1);
  set_hist_atributes(53,  "phjet_etaph_y_lt_05", "Photon_with_jet", "#eta^{#gamma} (y < 0.5)", -0.7, 0.9, 0.1, kFALSE, 1);

  set_hist_atributes(54,  "phjet_etph_y_gt_05", "Photon_with_jet", "E_{T}^{#gamma} (GeV) (y > 0.5)", 4., 15., 0.1, kFALSE, 1);
  set_hist_atributes(55,  "phjet_etph_y_lt_05", "Photon_with_jet", "E_{T}^{#gamma} (GeV) (y < 0.5)", 4., 15., 0.1, kFALSE, 1);
  set_hist_atributes(56,  "phjet_etph_y_lt_05", "Photon_with_jet", "E_{T}^{#gamma} (GeV) (y < 0.5)", 4., 15., 0.1, kFALSE, 1);

  TString s_period[n_periods] = {"0405e", "06e", "0607p"};
  TFile *file[n_periods][4];
  TFile *file_data04p;
  
  //  TString s_hist[n_hist] = {"h_fmax", "h_deltaz", "h_prph_energy", "h_comp_jet_e",  "h_comp_x", "h_comp_Q2", "h_phjet_electron_e", "h_phjet_electron_probability", "h_phjet_electron_theta", "h_prph_cell_energy_frac", "h_prph_jet_energy_frac", "h_prph_phi", "h_prph_eta", "h_x_gamma", "h_incl_phot_deltaz", "h_incl_phot_fmax"};

  //  TString s_yaxis[n_hist] = {"a", "Events", "Events", "Events"};
  //  TString s_path = "/data/zenith234b/kuprash/analyses/prompt_photons/Run_zarah/0001716767/";
  //  TString s_process = "norew_incl_prph.root";

  //  TString s_path = "/data/zenith234b/kuprash/analyses/prompt_photons/Run_zarah/0001772109/";
  //  TString s_process = "xgamma.gt.075.root";

  //TString s_path = "/data/zenith234b/kuprash/analyses/prompt_photons/Run_zarah/0001772114/";
  //TString s_process = "xgamma.lt.075.root";

  //  TString s_path = "/data/zenith234b/kuprash/analyses/prompt_photons/Run_zarah/0001718938/";
  TString s_path = "/data/zenith234b/kuprash/analyses/prompt_photons/";
  //  TString s_process = "_rew_prph_2nd_morehistos.root";
  //  TString s_process = "_rew_y.root";
  //  TString s_process = "_rew_y_binbybin.root";
  TString s_process = "_norew.root";
  //  TString s_process = "_rew_eph.root";  
  //  TString s_process = "_rew_q2_ybbb_eph.root";
  //  TString s_process = "_rew_q2_y_2nd.root";
  for(Int_t p=0; p<n_periods; p++) {
    cout << "opening file data " <<  s_period[p] << endl;
    file[p][0] =  new TFile(s_path + "data" + s_period[p] + s_process);
    cout << "opening file mc_bg_norad " <<  s_period[p] << endl;
    file[p][1] =  new TFile(s_path + "mc_bg_norad" + s_period[p] + s_process);
    cout << "opening file mc_bg_rad " <<  s_period[p] << endl;
    file[p][2] =  new TFile(s_path + "mc_bg_rad" + s_period[p] + s_process);
    if(s_period[p]!="0607p") {
      cout << "opening file mc_prph " <<  s_period[p] << endl;
      file[p][3] =  new TFile(s_path + "mc_prph" + s_period[p] + s_process);
    }
    cout << s_period[p] << " files attached" << endl;
    for(Int_t i=0; i<n_hist; i++)
      {
	cout << "reading " << s_hist[i] << endl;
	if(s_period[p]!="0607p") {
	  file[p][3]->cd();
	  cout << "reading mc_prph "  << i << " ..." << endl;
	  cout << s_path + "mc_prph" + s_period[p] + s_process << endl;
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

	if(s_period[p]!="0607p")
	  hist_mc[p][i]->Sumw2();
	hist_mc_rad[p][i]->Sumw2();
	hist_mc_norad[p][i]->Sumw2();
	hist_data[p][i]->Sumw2();
	//	hist_ratio[i]->Sumw2();
	//      hist_res[i]->Sumw2();
      }
  }
  cout << "histos succesfully read" << endl;

  hist_mc_sum_ian = (TH1D*)hist_mc[0][g_index_deltaz]->Clone();
  hist_mc_sum_ian->SetName(s_hist[g_index_deltaz]+"_mc_signal_ian");
  hist_mc_rad_sum_ian = (TH1D*)hist_mc_rad[0][g_index_deltaz]->Clone();
  hist_mc_rad_sum_ian->SetName(s_hist[g_index_deltaz]+"_mc_rad_ian");
  hist_mc_norad_sum_ian = (TH1D*)hist_mc_norad[0][g_index_deltaz]->Clone();
  hist_mc_norad_sum_ian->SetName(s_hist[g_index_deltaz]+"_mc_norad_ian");
  hist_data_sum_ian = (TH1D*)hist_data[0][g_index_deltaz]->Clone();
  hist_data_sum_ian->SetName(s_hist[g_index_deltaz]+"_data_ian");

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

  Double_t lumi_data[n_periods] = {134.15997, 54.79574, 142.93778};
  Double_t lumi_data04p = 38.68392;
  Double_t lumi_mc_bg[n_periods] = {271.36, 165.26, 364.6};

  cout << "data: " << hist_data_sum[0]->Integral() << ", rad mc: " << hist_mc_rad_sum[0]->Integral() << endl;
  for(Int_t i=0; i<n_periods; i++)
    {
      cout << s_period[i] << ", data: " << hist_data[i][0]->Integral() << " " << hist_mc_rad[i][0]->Integral() << endl;
      cout << "lumi data: " << lumi_data[i] << ", lumi mc: " << lumi_mc_bg[i] << endl;
    }
  //scale first period monte carlo to data luminosity
  for(Int_t i=0; i<n_hist; i++)
    {
      hist_mc_rad_sum[i]->Scale(lumi_data[0]/lumi_mc_bg[0]);
      hist_mc_norad_sum[i]->Scale(lumi_data[0]/lumi_mc_bg[0]);
    }
  cout << "data: " << hist_data_sum[0]->Integral() << ", rad mc: " << hist_mc_rad_sum[0]->Integral() << endl;
  //sum histogramms for all periods
  for(Int_t i=0; i<n_hist; i++)
    {
      for(Int_t p=1; p<n_periods; p++)
	{
	  cerr << i << " " << p << " adding :" << hist_data[p][i]->GetName() << endl;
	  hist_data_sum[i]->Add(hist_data[p][i]);
	  cerr << hist_data[p][i]->GetNbinsX() << endl;
	  cerr << "data - ok" << endl;
	  hist_mc_rad_sum[i]->Add(hist_mc_rad[p][i], lumi_data[p]/lumi_mc_bg[p]);
	  cerr << hist_mc_rad[p][i]->GetNbinsX() << endl;
	  cerr << "mc_rad - ok" << endl;
	  hist_mc_norad_sum[i]->Add(hist_mc_norad[p][i], lumi_data[p]/lumi_mc_bg[p]);
	  cerr << hist_mc_norad[p][i]->GetNbinsX() << endl;
	  cerr << "mc_norad - ok" << endl;
	  if(s_period[p]!= "0607p") {
	    hist_mc_sum[i]->Add(hist_mc[p][i]);
	    cerr << hist_mc[p][i]->GetNbinsX() << endl;
	    cerr << "mc_prph - ok" << endl;
	  }
	}
      if(g_include_04p_data) {
	hist_data_sum[i]->Add(hist_data04p[i]);
      }
      hist_mc_photon_sum[i] = (TH1D*)hist_mc_rad_sum[i]->Clone();
      hist_mc_photon_sum[i]->SetName(s_hist[i]+"_mc_photon");
      hist_mc_photon_sum[i]->Add(hist_mc_sum[i]);
    }



  cerr << "ADDING : OK" << endl;
  if(g_include_04p_data) {
    Double_t Lumi_tot = 0.;
    for(Int_t i=0; i<n_periods; i++)
      Lumi_tot += lumi_data[i];
    for(Int_t i=0; i<n_hist; i++)
      hist_mc_rad_sum[i]->Scale( (Lumi_tot+lumi_data04p) / Lumi_tot );
  }

  cout << "After summing: " << endl;
  cout << hist_data_sum[1]->GetName() << endl;
  cout << "total events in data: " << hist_data_sum[1]->GetEntries() << " " << hist_data_sum[1]->Integral() << " " << hist_data_sum[1]->GetSum() << endl;
  cout << "data: " << endl;
  for(Int_t i=0; i<hist_data_sum[1]->GetNbinsX(); i++) {
    cout << i << "   " << hist_data_sum[1]->GetBinContent(i+1) << "   " << hist_data_sum[1]->GetBinError(i+1) << endl;
  };
  cout << "mc_sum: " << endl;
  for(Int_t i=0; i<hist_mc_sum[1]->GetNbinsX(); i++) {
    cout << i << "   " << hist_mc_sum[1]->GetBinContent(i+1) << "   " << hist_mc_sum[1]->GetBinError(i+1) << endl;
  };
  cout << "mc_rad: " << endl;
  for(Int_t i=0; i<hist_mc_rad_sum[1]->GetNbinsX(); i++) {
    cout << i << "   " << hist_mc_rad_sum[1]->GetBinContent(i+1) << "   " << hist_mc_rad_sum[1]->GetBinError(i+1) << endl;
  };
  cout << "mc_norad: " << endl;
  for(Int_t i=0; i<hist_mc_norad_sum[1]->GetNbinsX(); i++) {
    cout << i << "   " << hist_mc_norad_sum[1]->GetBinContent(i+1) << "   " << hist_mc_norad_sum[1]->GetBinError(i+1) << endl;
  };
  cout << "mc_photon: " << endl;
  for(Int_t i=0; i<hist_mc_photon_sum[1]->GetNbinsX(); i++) {
    cout << i << "   " << hist_mc_photon_sum[1]->GetBinContent(i+1) << "   " << hist_mc_photon_sum[1]->GetBinError(i+1) << endl;
  };

  cout << "data: " << hist_data_sum[0]->Integral() << ", rad mc: " << hist_mc_rad_sum[0]->Integral() << endl;
  cout << "mc signal: " << hist_mc_sum[0]->Integral() << " " << hist_mc[0][0]->Integral() << " "  << hist_mc[1][0]->Integral() << endl;//" " << hist_mc[2][0]->Integral() << endl;
  for(Int_t i=0; i<n_hist; i++)
    {
      //      hist_data[i]->Scale(1./134.15997);
      //      hist_mc_rad[i]->Scale( (134.15997 + 54.79574 + 142.93778)/(134.52 + 54.71 + 364.6) ); //0405e
      //all: (134.15997 + 54.79574 + 142.93778)/(134.52 + 54.71 + 364.6)
      //0607p: 142.93778/364.6
      //0405e: 134.15997*1./134.52
     hist_mc_sum[i]->Scale((hist_data_sum[i]->Integral()- hist_mc_rad_sum[i]->Integral())/hist_mc_sum[i]->Integral());
      //      hist_mc_rad[i]->Scale(hist_data[i]->Integral()/hist_mc_rad[i]->Integral());
     hist_mc_norad_sum[i]->Scale((hist_data_sum[i]->Integral()-hist_mc_rad_sum[i]->Integral())/hist_mc_norad_sum[i]->Integral());
    } 

  // ====================================================================================================
  //
  // This is only for comparison with Ian! Comment it out when fit as usually
  //
  // ====================================================================================================
  for(Int_t i=0; i<n_hist; i++) {
    //    hist_data_sum[i]->Scale(1./hist_data_sum[i]->Integral());
    //    hist_mc_photon_sum[i]->Scale(1./hist_mc_photon_sum[i]->Integral());
    //    hist_mc_norad_sum[i]->Scale(1./hist_mc_norad_sum[i]->Integral());
  }
  //
  // ====================================================================================================
  //

  for(Int_t i=0; i<n_hist; i++) {
    hist_data_sum[i]->Rebin(hist_rebin[i]);
    hist_mc_sum[i]->Rebin(hist_rebin[i]);
    hist_mc_rad_sum[i]->Rebin(hist_rebin[i]);
    hist_mc_norad_sum[i]->Rebin(hist_rebin[i]);
    hist_ratio[i]->Rebin(hist_rebin[i]);
    hist_mc_photon_sum[i]->Rebin(hist_rebin[i]);
  }

  TFitter* minimizer = new TFitter(1);
  // MAKE IT QUIET!!
  {
    //    double p1 = -1;
    //    minimizer->ExecuteCommand("SET PRINTOUT",&p1,1);
  }
  Double_t param[1] = {0.};
  Double_t param_err[1] = {0.};
  //
  // Here is Barlow-Beeston chi2 function
  //
  // Tell the minimizer about the function to be minimzed
  cout << "Before fitting: " << endl;
  cout << hist_data_sum[1]->GetName() << endl;
  cout << "data: " << endl;
  for(Int_t i=0; i<hist_data_sum[1]->GetNbinsX(); i++) {
    cout << i << "   " << hist_data_sum[1]->GetBinContent(i+1) << "   " << hist_data_sum[1]->GetBinError(i+1) << endl;
  };
  cout << "mc_sum: " << endl;
  for(Int_t i=0; i<hist_mc_sum[1]->GetNbinsX(); i++) {
    cout << i << "   " << hist_mc_sum[1]->GetBinContent(i+1) << "   " << hist_mc_sum[1]->GetBinError(i+1) << endl;
  };
  cout << "mc_rad: " << endl;
  for(Int_t i=0; i<hist_mc_rad_sum[1]->GetNbinsX(); i++) {
    cout << i << "   " << hist_mc_rad_sum[1]->GetBinContent(i+1) << "   " << hist_mc_rad_sum[1]->GetBinError(i+1) << endl;
  };
  cout << "mc_norad: " << endl;
  for(Int_t i=0; i<hist_mc_norad_sum[1]->GetNbinsX(); i++) {
    cout << i << "   " << hist_mc_norad_sum[1]->GetBinContent(i+1) << "   " << hist_mc_norad_sum[1]->GetBinError(i+1) << endl;
  };
  cout << "mc_photon: " << endl;
  for(Int_t i=0; i<hist_mc_photon_sum[1]->GetNbinsX(); i++) {
    cout << i << "   " << hist_mc_photon_sum[1]->GetBinContent(i+1) << "   " << hist_mc_photon_sum[1]->GetBinError(i+1) << endl;
  };

  minimizer->SetFCN(minuitFunctionBarlowBeeston);
  minimizer->SetParameter(0, "ALPHA", 0.3648, 0.05, 0., 0.5);
  minimizer->ExecuteCommand("SIMPLEX", 0, 0);
  cout << "after simplex" << endl;

  //
  // create copies
  //
  /*  hist_mc_sum_copy[g_index_deltaz] = (TH1D*)hist_mc_sum[g_index_deltaz]->Clone();
  hist_mc_sum_copy[g_index_deltaz]->SetName(s_hist[g_index_deltaz]+"_mc_signal_copy");

  hist_mc_norad_sum_copy[g_index_deltaz] = (TH1D*)hist_mc_norad_sum[g_index_deltaz]->Clone();
  hist_mc_norad_sum_copy[g_index_deltaz]->SetName(s_hist[g_index_deltaz]+"_mc_norad_copy");

  hist_mc_rad_sum_copy[g_index_deltaz] = (TH1D*)hist_mc_rad_sum[g_index_deltaz]->Clone();
  hist_mc_rad_sum_copy[g_index_deltaz]->SetName(s_hist[g_index_deltaz]+"_mc_rad_copy");

  hist_data_sum_copy[g_index_deltaz] = (TH1D*)hist_data_sum[g_index_deltaz]->Clone();
  hist_data_sum_copy[g_index_deltaz]->SetName(s_hist[g_index_deltaz]+"_data_copy");

  hist_mc_photon_sum_copy[g_index_deltaz] = (TH1D*)hist_mc_photon_sum[g_index_deltaz]->Clone();
  hist_mc_photon_sum_copy[g_index_deltaz]->SetName(s_hist[g_index_deltaz]+"_mc_photon_copy");
  */
  for(Int_t i=0; i<1; i++) {
    /*    hist_mc_sum[g_index_deltaz] = (TH1D*)hist_mc_sum_copy[g_index_deltaz]->Clone();
    hist_mc_sum[g_index_deltaz]->SetName(s_hist[g_index_deltaz]+"_mc_signal");

    hist_mc_norad_sum[g_index_deltaz] = (TH1D*)hist_mc_norad_sum_copy[g_index_deltaz]->Clone();
    hist_mc_norad_sum[g_index_deltaz]->SetName(s_hist[g_index_deltaz]+"_mc_norad");

    hist_mc_rad_sum[g_index_deltaz] = (TH1D*)hist_mc_rad_sum_copy[g_index_deltaz]->Clone();
    hist_mc_rad_sum[g_index_deltaz]->SetName(s_hist[g_index_deltaz]+"_mc_rad");

    hist_data_sum[g_index_deltaz] = (TH1D*)hist_data_sum_copy[g_index_deltaz]->Clone();
    hist_data_sum[g_index_deltaz]->SetName(s_hist[g_index_deltaz]+"_data");

    hist_mc_photon_sum[g_index_deltaz] = (TH1D*)hist_mc_photon_sum_copy[g_index_deltaz]->Clone();
    hist_mc_photon_sum[g_index_deltaz]->SetName(s_hist[g_index_deltaz]+"_mc_photon");
    */
    //    variate_bin_content_Gaus(hist_mc_norad_sum[g_index_deltaz]);
    //    variate_bin_content_Gaus(hist_mc_photon_sum[g_index_deltaz]);
    //    variate_bin_content_Gaus(hist_data_sum[g_index_deltaz]);
    cout << "====== NUMBER OF ENTRIES ======" << endl;
    cout << "data: " << hist_data_sum[g_index_deltaz]->GetEntries() << endl;
    cout << "mc_norad: "<< hist_mc_norad_sum[g_index_deltaz]->GetEntries() << endl;
    cout << "mc_rad: " << hist_mc_rad_sum[g_index_deltaz]->GetEntries() << endl;
    cout << "mc_signal: " << hist_mc_sum[g_index_deltaz]->GetEntries() << endl;
    minimizer->ExecuteCommand("MIGRAD",0,0);
    cout << "after migrad" << endl;
    minimizer->ExecuteCommand("HESSE",0,0);
    cout << "after hesse" << endl;
    minimizer->ExecuteCommand("MINOS",0,0);
    cout << "after minos" << endl;
    param[0] = minimizer->GetParameter(0);
    param_err[0] = minimizer->GetParError(0);
    //    cout << "fit result: " << param[0] << " +- " << param_err[0] << endl;
    if(i%1000 == 0) cerr << "fitting " << i << endl;
    hist_check_fit_error->Fill(param[0]);
  }

  Int_t ndf;
  Double_t chi_squared, left_bound, right_bound;

  chi_squared = chi2(param, ndf, left_bound, right_bound, "Barlow-Beeston") / (ndf - 1);
  cout << "Barlow-Beeston chi2 approach: " << endl;
  cout << "param = " << param[0] << " +- " << param_err[0] << endl;
  cout << "with chi2 / " << ndf << "-1 = " << chi_squared << endl;
  //  param[0] = 0.42584;
  //  cout << "Ians param: " << chi2(param, ndf, left_bound, right_bound, "Barlow-Beeston") / (ndf - 1);
  //
  // Here is Gauss chi2 function
  //
  // Tell the minimizer about the function to be minimzed
  minimizer->SetFCN(minuitFunctionGauss);
  minimizer->SetParameter(0, "ALPHA_GAUSS", 0.35, 0.1, 0., 1.);
  minimizer->ExecuteCommand("SIMPLEX", 0, 0);
  minimizer->ExecuteCommand("MIGRAD",0,0);
  minimizer->ExecuteCommand("MINOS",0,0);
  Double_t param_Gauss[1] = {0.};
  Double_t param_err_Gauss[1] = {0.};
  Double_t chi_squared_Gauss;
  param_Gauss[0] = minimizer->GetParameter(0);
  param_err_Gauss[0] = minimizer->GetParError(0);
  chi_squared_Gauss = chi2(param_Gauss, ndf, left_bound, right_bound, "Gauss") / (ndf-1);
  cout << "Gauss chi2 approach: " << endl;
  cout << "param = " << param_Gauss[0] << " +- " << param_err_Gauss[0] << endl;
  cout << "with chi2 / " << ndf << "-1 = " << chi_squared_Gauss / (ndf - 1)<< endl;

  //
  // calculate chi2 as function of fit parameter (prph fraction)
  //
  const Int_t n_graph = 100;
  TGraph* chi2_off_par;
  TGraph* chi2_off_par_Gauss;
  Double_t x_chi2_off_par[n_graph];
  Double_t y_chi2_off_par[n_graph];
  Double_t y_chi2_off_par_Gauss[n_graph];
  Double_t x_par_start = param[0] - 5.*param_err[0];
  Double_t x_par_end = param[0] + 5.*param_err[0];
  for(Int_t i=0; i<n_graph; i++)
    {
      x_chi2_off_par[i] = x_par_start + (x_par_end - x_par_start) * (i+0.5)/float(n_graph);
      Double_t x[1]; x[0] = x_chi2_off_par[i];
      y_chi2_off_par_Gauss[i] = chi2(x, ndf, left_bound, right_bound, "Gauss") / (ndf-1);
      y_chi2_off_par[i] = chi2(x, ndf, left_bound, right_bound, "Barlow-Beeston") / (ndf-1);
      cout << "param " << i << ": " << x[0] << " " << y_chi2_off_par[i] << " " << y_chi2_off_par_Gauss[i] << endl;
    }
  chi2_off_par = new TGraph(n_graph, x_chi2_off_par, y_chi2_off_par);
  chi2_off_par->SetLineColor(kBlue);
  chi2_off_par_Gauss = new TGraph(n_graph, x_chi2_off_par, y_chi2_off_par_Gauss);
  TCanvas *c_chi2 = new TCanvas("c_chi2" + fit_method, fit_method, 800, 600);
  c_chi2->Divide(1, 1);
  make_clean_pads(c_chi2, 1, 1, 1);
  TH2D *h_window_chi2 = new TH2D("h_window_chi2" + fit_method, fit_method, 10, 0., 1., 10, 1.5, y_chi2_off_par_Gauss[n_graph-1]);
  sign_window(c_chi2->GetPad(1), h_window_chi2, "mc prph fraction", "#chi^{2}/d.o.f.", "blue - Barlow-Beeston", "middle");
  c_chi2->GetPad(1)->cd();
  h_window_chi2->Draw();
  chi2_off_par->DrawClone("L SAME");
  chi2_off_par_Gauss->DrawClone("L SAME");
  c_chi2->Print("chi2_" + fit_method + ".eps");

  //histograms copies to plot Gauss method
  TH1D *hist_res_Gauss[n_hist];
  TH1D *hist_mc_rad_sum_Gauss[n_hist];
  TH1D *hist_mc_norad_sum_Gauss[n_hist];
  TH1D *hist_mc_sum_Gauss[n_hist];
  for(Int_t i=0; i<n_hist; i++)
    {
      //      hist_res_Gauss[i] = (TH1D*)hist_res[i]->Clone();
      //      hist_res_Gauss[i]->SetName(hist_res[i]->GetName() + "_Gauss");
      hist_mc_sum_Gauss[i] = (TH1D*)hist_mc_sum[i]->Clone();
      hist_mc_sum_Gauss[i]->SetName((TString)hist_mc_sum[i]->GetName() + "_Gauss");
      hist_mc_norad_sum_Gauss[i] = (TH1D*)hist_mc_norad_sum[i]->Clone();
      hist_mc_norad_sum_Gauss[i]->SetName((TString)hist_mc_norad_sum[i]->GetName() + "_Gauss");
      hist_mc_rad_sum_Gauss[i] = (TH1D*)hist_mc_rad_sum[i]->Clone();
      hist_mc_rad_sum_Gauss[i]->SetName((TString)hist_mc_rad_sum[i]->GetName() + "_Gauss");
    }

  for(Int_t i=0; i<n_hist; i++)
    {
      //
      // Barlow-Beeston
      //
      hist_res[i] = (TH1D*)hist_mc_rad_sum[i]->Clone();
      hist_res[i]->SetName(s_hist[i]+"_res");
      
      hist_mc_sum[i]->Scale(param[0]);
      for(Int_t j=0; j<hist_mc_sum[i]->GetNbinsX(); j++)
	{
	  //	  cout << "err before: " << i << " " << j << " " << hist_mc_sum[i]->GetBinError(j+1) << endl;
	  Double_t err = hist_mc_sum[i]->GetBinError(j+1)/param[0];
	  Double_t add_err1 = param_err[0]*hist_mc_sum[i]->GetBinContent(j+1)/param[0];
	  add_err1 *= add_err1;
	  Double_t add_err2 = err*param[0];
	  add_err2 *= add_err2;
	  hist_mc_sum[i]->SetBinError(j+1, TMath::Sqrt(add_err1 + add_err2));
	  //	  cout << "err after: " << i << " " << j << " " << hist_mc_sum[i]->GetBinError(j+1) << endl;
	}
      hist_mc_norad_sum[i]->Scale(1.-param[0]);
      for(Int_t j=0; j<hist_mc_norad_sum[i]->GetNbinsX(); j++)
	{
	  Double_t err = hist_mc_norad_sum[i]->GetBinError(j+1)/(1.-param[0]);
	  Double_t add_err1 = param_err[0]*hist_mc_norad_sum[i]->GetBinContent(j+1)/(1.-param[0]);
	  add_err1 *= add_err1;
	  Double_t add_err2 = err*(1.-param[0]);
	  add_err2 *= add_err2;
	  hist_mc_norad_sum[i]->SetBinError(j+1, TMath::Sqrt(add_err1 + add_err2));
	}
    }

  Double_t int_data_dz_gt_035 = hist_data_sum[1]->Integral(hist_data_sum[1]->FindBin(0.35), hist_data_sum[1]->FindBin(1.5));
  Double_t int_data_dz_lt_035 = hist_data_sum[1]->Integral(hist_data_sum[1]->FindBin(0.), hist_data_sum[1]->FindBin(0.35));
  Double_t int_data_dz_full = hist_data_sum[1]->Integral(hist_data_sum[1]->FindBin(0.), hist_data_sum[1]->FindBin(1.5));
  Double_t int_mc_dz_gt_035 = hist_mc_sum[1]->Integral(hist_data_sum[1]->FindBin(0.35), hist_data_sum[1]->FindBin(1.5));
  Double_t int_mc_dz_lt_035 = hist_mc_sum[1]->Integral(hist_data_sum[1]->FindBin(0.), hist_data_sum[1]->FindBin(0.35));
  Double_t int_mc_dz_full = hist_mc_sum[1]->Integral(hist_data_sum[1]->FindBin(0.), hist_data_sum[1]->FindBin(1.5));
  Double_t int_mc_norad_dz_gt_035 = hist_mc_norad_sum[1]->Integral(hist_data_sum[1]->FindBin(0.35), hist_data_sum[1]->FindBin(1.5));
  Double_t int_mc_norad_dz_lt_035 = hist_mc_norad_sum[1]->Integral(hist_data_sum[1]->FindBin(0.), hist_data_sum[1]->FindBin(0.35));
  Double_t int_mc_norad_dz_full = hist_mc_norad_sum[1]->Integral(hist_data_sum[1]->FindBin(0.), hist_data_sum[1]->FindBin(1.5));
  Double_t int_mc_rad_dz_gt_035 = hist_mc_rad_sum[1]->Integral(hist_data_sum[1]->FindBin(0.35), hist_data_sum[1]->FindBin(1.5));
  Double_t int_mc_rad_dz_lt_035 = hist_mc_rad_sum[1]->Integral(hist_data_sum[1]->FindBin(0.), hist_data_sum[1]->FindBin(0.35));
  Double_t int_mc_rad_dz_full = hist_mc_rad_sum[1]->Integral(hist_data_sum[1]->FindBin(0.), hist_data_sum[1]->FindBin(1.5));

  cout << "in the region dz < 0.35 QQ fraction is higher in " << (int_mc_dz_lt_035 / int_data_dz_lt_035) / (int_mc_dz_full / int_data_dz_full) << " times than in full region " << endl;
  cout << "in the region dz > 0.35 QQ fraction is lower in " << (int_mc_dz_gt_035 / int_data_dz_gt_035) / (int_mc_dz_full / int_data_dz_full) << " times than in full region " << endl;

  cout << "in the region dz < 0.35 LL fraction is higher in " << (int_mc_rad_dz_lt_035 / int_data_dz_lt_035) / (int_mc_rad_dz_full / int_data_dz_full) << " times than in full region " << endl;
  cout << "in the region dz > 0.35 LL fraction is lower in " << (int_mc_rad_dz_gt_035 / int_data_dz_gt_035) / (int_mc_rad_dz_full / int_data_dz_full) << " times than in full region " << endl;

  cout << "in the region dz < 0.35 bg fraction is higher in " << (int_mc_norad_dz_lt_035 / int_data_dz_lt_035) / (int_mc_norad_dz_full / int_data_dz_full) << " times than in full region " << endl;
  cout << "in the region dz > 0.35 bg fraction is lower in " << (int_mc_norad_dz_gt_035 / int_data_dz_gt_035) / (int_mc_norad_dz_full / int_data_dz_full) << " times than in full region " << endl;

  Double_t scale_mc = 1.;
  Double_t scale_mc_rad = 1.;
  Double_t scale_mc_norad = 1.;

  for(Int_t i=0; i<n_hist; i++)
    {
      scale_mc = 1.; scale_mc_norad = 1.; scale_mc_rad = 1.;
      if(i==25 || i==28 || i==31 || i==34 || i==37) {
	scale_mc = (int_mc_dz_lt_035 / int_data_dz_lt_035) / (int_mc_dz_full / int_data_dz_full);
	scale_mc_norad = (int_mc_norad_dz_lt_035 / int_data_dz_lt_035) / (int_mc_norad_dz_full / int_data_dz_full);
	scale_mc_rad = (int_mc_rad_dz_lt_035 / int_data_dz_lt_035) / (int_mc_rad_dz_full / int_data_dz_full);
      }
      if(i==24 || i==27 || i==30 || i==33 || i==36) {
	scale_mc = (int_mc_dz_gt_035 / int_data_dz_gt_035) / (int_mc_dz_full / int_data_dz_full);
	scale_mc_norad = (int_mc_norad_dz_gt_035 / int_data_dz_gt_035) / (int_mc_norad_dz_full / int_data_dz_full);
	scale_mc_rad = (int_mc_rad_dz_gt_035 / int_data_dz_gt_035) / (int_mc_rad_dz_full / int_data_dz_full);
      }
      hist_res[i]->Scale(scale_mc_rad);
      hist_mc_sum[i]->Scale(scale_mc);
      hist_mc_norad_sum[i]->Scale(scale_mc_norad);
      hist_res[i]->Add(hist_mc_sum[i], 1.);
      hist_res[i]->Add(hist_mc_norad_sum[i], 1.);
      hist_res[i]->SetLineColor(kBlack);
      hist_res[i]->SetLineWidth(1);
      hist_res[i]->SetFillColor(kYellow);

      //      hist_res[i]->SetFillStyle(kFillSolid);


      //
      // Gauss
      //
      hist_res_Gauss[i] = (TH1D*)hist_mc_rad_sum[i]->Clone();
      hist_res_Gauss[i]->SetName((TString)hist_res[i]->GetName() + "_Gauss");
      hist_mc_sum_Gauss[i]->Scale(param_Gauss[0]);
      hist_mc_norad_sum_Gauss[i]->Scale(1.-param_Gauss[0]);
      hist_res_Gauss[i]->Add(hist_mc_sum_Gauss[i]);
      hist_res_Gauss[i]->Add(hist_mc_norad_sum_Gauss[i]);
      hist_res_Gauss[i]->SetLineColor(97);
      hist_res_Gauss[i]->SetLineWidth(2);
    }

  
  for(Int_t i=0; i<n_hist; i++)
    {

    }


      cout << "After fitting: " << endl;
      cout << "data: " << endl;
      for(Int_t i=0; i<hist_data_sum[1]->GetNbinsX(); i++) {
	cout << i << "   " << hist_data_sum[1]->GetBinContent(i+1) << "   " << hist_data_sum[1]->GetBinError(i+1) << endl;
      };
      cout << "mc_sum: " << endl;
      for(Int_t i=0; i<hist_mc_sum[1]->GetNbinsX(); i++) {
	cout << i << "   " << hist_mc_sum[1]->GetBinContent(i+1) << "   " << hist_mc_sum[1]->GetBinError(i+1) << endl;
      };
      cout << "mc_rad: " << endl;
      for(Int_t i=0; i<hist_mc_rad_sum[1]->GetNbinsX(); i++) {
	cout << i << "   " << hist_mc_rad_sum[1]->GetBinContent(i+1) << "   " << hist_mc_rad_sum[1]->GetBinError(i+1) << endl;
      };
      cout << "mc_norad: " << endl;
      for(Int_t i=0; i<hist_mc_norad_sum[1]->GetNbinsX(); i++) {
	cout << i << "   " << hist_mc_norad_sum[1]->GetBinContent(i+1) << "   " << hist_mc_norad_sum[1]->GetBinError(i+1) << endl;
      };
      cout << "mc_result: " << endl;
      for(Int_t i=0; i<hist_res[1]->GetNbinsX(); i++) {
	cout << i << "   " << hist_res[1]->GetBinContent(i+1) << "   " << hist_res[1]->GetBinError(i+1) << endl;
      };


  cout << "There are " << hist_mc_sum[1]->Integral() << " + " << hist_mc_rad_sum[1]->Integral() << " fitted photons" << endl;
  Double_t hist_mc_sum_integral = 0;
  Double_t hist_mc_sum_integral_err = 0;
  for(Int_t i=0; i<hist_mc_sum[1]->GetNbinsX(); i++){
    hist_mc_sum_integral += hist_mc_sum[1]->GetBinContent(i+1);
    hist_mc_sum_integral_err += hist_mc_sum[1]->GetBinError(i+1) * hist_mc_sum[1]->GetBinError(i+1);
  }
  hist_mc_sum_integral_err = TMath::Sqrt(hist_mc_sum_integral_err);
  cout << hist_mc_sum_integral << " +- " << hist_mc_sum_integral_err << endl;
  Double_t hist_mc_rad_sum_integral = 0;
  Double_t hist_mc_rad_sum_integral_err = 0;
  for(Int_t i=0; i<hist_mc_rad_sum[1]->GetNbinsX(); i++){
    hist_mc_rad_sum_integral += hist_mc_rad_sum[1]->GetBinContent(i+1);
    hist_mc_rad_sum_integral_err += hist_mc_rad_sum[1]->GetBinError(i+1) * hist_mc_rad_sum[1]->GetBinError(i+1);
  }
  hist_mc_rad_sum_integral_err = TMath::Sqrt(hist_mc_rad_sum_integral_err);
  cout << hist_mc_rad_sum_integral << " +- " << hist_mc_rad_sum_integral_err << endl;
  cout << "There are " << hist_res[1]->Integral() << " events in total in fitted MC" << endl;
  cout << "There are " << hist_mc_norad_sum[1]->Integral() << " fitted background events" << endl;
  Double_t hist_mc_norad_sum_integral = 0;
  Double_t hist_mc_norad_sum_integral_err = 0;
  for(Int_t i=0; i<hist_mc_norad_sum[1]->GetNbinsX(); i++){
    hist_mc_norad_sum_integral += hist_mc_norad_sum[1]->GetBinContent(i+1);
    hist_mc_norad_sum_integral_err += hist_mc_norad_sum[1]->GetBinError(i+1) * hist_mc_norad_sum[1]->GetBinError(i+1);
  }
  hist_mc_norad_sum_integral_err = TMath::Sqrt(hist_mc_norad_sum_integral_err);
  cout << hist_mc_norad_sum_integral << " +- " << hist_mc_norad_sum_integral_err << endl;
  TH2D *h_window[n_hist];
  TH2D *h_window_ratio[n_hist];
  TF1 *f1 = new TF1("f1", "1.", -10000., 10000.);
  f1->SetLineColor(39);
  f1->SetLineWidth(1);
  for(Int_t i=0; i<n_hist; i++) {
    Double_t y_max = 1.2*hist_data_sum[i]->GetMaximum();
    cout << "if(i == " << i << ") y_max = " << y_max << ";" << endl;
    /*    if(i == 0) y_max = 1221.6;
    if(i == 1) y_max = 979.2;
    if(i == 2) y_max = 2232;
    if(i == 3) y_max = 1780.8;
    if(i == 4) y_max = 3730.8;
    if(i == 5) y_max = 3375.6;
    if(i == 6) y_max = 968.4;
    if(i == 7) y_max = 1434;
    if(i == 8) y_max = 6699.6;
    if(i == 9) y_max = 3001.2;
    if(i == 10) y_max = 828;
    if(i == 11) y_max = 550.8;
    if(i == 12) y_max = 2248.8;
    if(i == 13) y_max = 576;
    if(i == 14) y_max = 729.6;
    if(i == 15) y_max = 3514.8;
    if(i == 16) y_max = 1119.6;
    if(i == 17) y_max = 3375.6;*/
    TString s; s.Form("h_window%i", i);
    h_window[i] = new TH2D(s, "", 10, hist_xmin[i], hist_xmax[i], 10, hist_ymin[i], y_max);
    s.Form("h_window_ratio%i", i);
    h_window_ratio[i] = new TH2D(s, "", 10, hist_xmin[i], hist_xmax[i], 10, 0., 3.);
  }

  for(Int_t i=0; i<n_hist; i++)
    {
      for(Int_t j=0; j<hist_mc_sum[i]->GetNbinsX(); j++)
	{
	  //	  cout << i << " " << j << endl;
	  if(hist_res[i]->GetBinContent(j+1) != 0.) {	    
	    hist_ratio[i]->SetBinContent(j+1, hist_data_sum[i]->GetBinContent(j+1)/hist_res[i]->GetBinContent(j+1));
	    Double_t err1, err2, err;
	    //	    cout << "ok" << endl;
	    Double_t x = hist_data_sum[i]->GetBinContent(j+1);
	    Double_t y = hist_res[i]->GetBinContent(j+1);
	    Double_t x_err = hist_data_sum[i]->GetBinError(j+1);
	    Double_t y_err = hist_res[i]->GetBinError(j+1);
	    //	    cout << "ok" << endl;
	    err1 = x_err/y;
	    err2 = x*y_err/(y*y);
	    err = TMath::Sqrt(err1*err1 + err2*err2);
	    //	    err = x/(y*y) + x*x*y/(y*y*y*y);
	    //	    err = TMath::Sqrt(err);
	    hist_ratio[i]->SetBinError(j+1, err);
	  }
	}
    }

  TCanvas* c1[n_hist/3+1];
  for(Int_t i=0; i<n_hist/3+1; i++) {
    TString s; s.Form("c%i", i);
    c1[i] = new TCanvas(s, s, 1200, 800);
  }
  //  c1[1] = new TCanvas("c11", "c11", 1000, 800);

  for(Int_t i=0; i<n_hist/3+1; i++)
    {
      c1[i]->Divide(3, 2);
      make_clean_pads(c1[i], 6, 0, 0);
    }
  for(Int_t i=0; i<n_hist; i++) {
    sign_window(c1[i/3]->GetPad(i%3 + 1), h_window[i], s_xaxis[i], "Events", "", "middle");
    sign_window(c1[i/3]->GetPad(i%3 + 4), h_window_ratio[i], s_xaxis[i], "data / mc", "", "middle");
  }

  TLegend *leg = new TLegend(0.45, 0.6, 0.86, 0.91);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(hist_data_sum[0], "data", "pe");
  leg->AddEntry(hist_mc_sum[0], "signal mc", "l");
  leg->AddEntry(hist_mc_rad_sum[0], "rad bg mc", "l");
  leg->AddEntry(hist_mc_norad_sum[0], "norad bg mc", "l");
  leg->AddEntry(hist_res[0], "signal + bg", "f");

  for(Int_t i=0; i<n_hist; i++)
    {
      if(i!= 23) {
      cout << " cd " << i/3 << " " << i%3+1 << endl;
      c1[i/3]->GetPad(i%3+1)->cd();
      c1[i/3]->GetPad(i%3+1)->SetLogy(hist_logy[i]);
      ((TGaxis*)h_window[i]->GetYaxis())->SetMaxDigits(2);
      ((TGaxis*)h_window[i]->GetXaxis())->SetMaxDigits(3);
      h_window[i]->DrawClone();      
      hist_res[i]->DrawClone("HIST SAME");
      hist_res[i]->DrawClone("F SAME");
      hist_mc_sum[i]->DrawClone("HIST SAME");  
      hist_mc_rad_sum[i]->DrawClone("HIST SAME");  
      hist_mc_norad_sum[i]->DrawClone("HIST SAME");
      //      Shift(hist_data_sum[i], 0.2);
      Double_t xmin = hist_data_sum[i]->GetXaxis()->GetXmin();
      Double_t xmax = hist_data_sum[i]->GetXaxis()->GetXmax();
      Double_t deltax = xmax-xmin;
      hist_data_sum[i]->GetXaxis()->SetLimits(xmin + 0.01*deltax, xmax+0.01*deltax);
      hist_data_sum[i]->SetMarkerColor(kRed);
      hist_data_sum[i]->SetLineColor(kRed);
      hist_data_sum[i]->DrawClone("P E X0 SAME");  

      c1[i/3]->GetPad(i%3+1)->RedrawAxis();

      c1[i/3]->GetPad(i%3+4)->cd();
      h_window_ratio[i]->DrawClone();
      f1->Draw("SAME");
      hist_ratio[i]->SetLineColor(kBlack);
      //      hist_ratio[i]->SetLin
      hist_ratio[i]->SetLineColor(kBlue);
      hist_ratio[i]->SetLineWidth(2);
      hist_ratio[i]->SetMarkerStyle(20);
      hist_ratio[i]->SetMarkerSize(0.5);
      hist_ratio[i]->SetMarkerColor(kBlue);
      hist_ratio[i]->DrawClone("P E X0 HIST  SAME");  
      if(i%3 == 0)
	leg->DrawClone();
      }
      //      hist_ratio[i]->DrawClone("HIST C SAME");  
    }

  for(Int_t i=0; i<n_hist/3+1; i++) {
    TString s; s.Form("c%i_after_eph_rew.eps", i);
    c1[i]->Print(s);
    s.Form("c%i.png", i);
    c1[i]->Print(s);
  }

  //
  // plot x_gamma separately
  //
  TCanvas* c_xgamma = new TCanvas("c_xgamma", "c_xgamma", 800, 600);
  c_xgamma->Divide(1,1);
  make_clean_pads(c_xgamma, 1, 0, 0);
  c_xgamma->GetPad(1)->cd();
  h_window[11]->DrawClone();
  hist_res[11]->DrawClone("HIST SAME");
  hist_res[11]->DrawClone("F SAME");
  hist_mc_sum[11]->DrawClone("HIST SAME");  
  hist_mc_rad_sum[11]->DrawClone("HIST SAME");  
  hist_mc_norad_sum[11]->DrawClone("HIST SAME");
  //      Shift(hist_data_sum[i], 0.2);
  Double_t xmin = hist_data_sum[11]->GetXaxis()->GetXmin();
  Double_t xmax = hist_data_sum[11]->GetXaxis()->GetXmax();
  Double_t deltax = xmax-xmin;
  hist_data_sum[11]->GetXaxis()->SetLimits(xmin + 0.01*deltax, xmax+0.01*deltax);
  hist_data_sum[11]->SetMarkerColor(kRed);
  hist_data_sum[11]->SetLineColor(kRed);
  hist_data_sum[11]->DrawClone("P E X0 SAME");  
  c_xgamma->GetPad(1)->RedrawAxis();

  TLegend *legx = new TLegend(0.2, 0.63, 0.55, 0.91);
  legx->SetBorderSize(0);
  legx->SetFillColor(0);
  legx->AddEntry(hist_data_sum[0], "data", "pe");
  legx->AddEntry(hist_mc_sum[0], "signal mc", "l");
  legx->AddEntry(hist_mc_rad_sum[0], "rad bg mc", "l");
  legx->AddEntry(hist_mc_norad_sum[0], "norad bg mc", "l");
  legx->AddEntry(hist_res[0], "signal + bg", "f");

  legx->Draw();
  c_xgamma->Print("c_xgamma.eps");

  //plot fmax or deltaz on separate canvas
  TPaveText* inform;// = new TPaveText(0.6, 0.61, 0.94, 0.92, "NDC");
  TCanvas *c_method = new TCanvas("c_" + fit_method, fit_method, 800, 600);
  c_method->Divide(1, 1);
  make_clean_pads(c_method, 1, 0, 0);
  c_method->GetPad(1)->cd();
  Int_t index;
  if(fit_method == "fmax") {
    leg->SetX1(0.2000256);
    leg->SetY1(0.6671052);
    leg->SetX2(0.5128141);
    leg->SetY2(0.9102069);
    inform = new TPaveText(0.2003341,0.5444429,0.5112768,0.6564389, "NDC");
    index = g_index_fmax;
  } else
    if(fit_method == "deltaz") {
      index = g_index_deltaz;
      //      0.6346016,0.7044372,0.9345708,0.9302069;
      leg->SetX1(0.5);
      leg->SetY1(0.65);
      leg->SetX2(0.85);
      leg->SetY2(0.9105708);
      inform = new TPaveText(0.45,0.574664,0.85,0.64, "NDC");
    }
  TText *t1, *t2;
  TString s1; s1.Form("fit range: bins %i .. %i", int(left_bound), int(right_bound));
  TString s2; s2.Form("#chi^{2} / %i-1 = %.2f", ndf, chi_squared);
  t1 = inform->AddText(s1); t1->SetTextSize(0.04);
  t2 = inform->AddText(s2); t2->SetTextSize(0.04);
  inform->SetFillColor(0);
  inform->SetBorderSize(0);
  h_window[index]->DrawClone();
  hist_res[index]->DrawClone("HIST E1 SAME");
  hist_mc_sum[index]->DrawClone("HIST SAME");
  hist_mc_rad_sum[index]->DrawClone("HIST SAME");
  hist_mc_norad_sum[index]->DrawClone("HIST SAME");
  hist_data_sum[index]->DrawClone("P E1 SAME");
  c_method->GetPad(1)->RedrawAxis();
  leg->DrawClone();
  inform->Draw();
  TLine *line035 = new TLine();
  line035->SetLineWidth(2);
  line035->SetLineStyle(2);
  line035->DrawLine(0.35, 0., 0.35, h_window[index]->GetYaxis()->GetXmax());
  c_method->Print(fit_method + ".eps");
  c_method->Print(fit_method + ".png");
  c_method->Print(fit_method + ".C");
  //
  // on this canvas plot fit results with different methods
  //
  TCanvas *c_chi2_method = new TCanvas("c_" + fit_method + "_diff_chi2", fit_method + "_diff_chi2", 800, 600);
  c_chi2_method->Divide(1, 1);
  make_clean_pads(c_chi2_method, 1, 1, 1);
  TLegend *leg_chi2_method = new TLegend(0.25, 0.67, 0.56, 0.93);
  leg_chi2_method->SetFillColor(0);
  leg_chi2_method->SetBorderSize(0);
  if(fit_method == "fmax") {
    leg_chi2_method->SetX1(0.2500256);
    leg_chi2_method->SetY1(0.6671052);
    leg_chi2_method->SetX2(0.5628141);
    leg_chi2_method->SetY2(0.9302069);
    inform = new TPaveText(0.2423341,0.5444429,0.5512768,0.6564389, "NDC");
    index = g_index_fmax;
  } else
    if(fit_method == "deltaz") {
      index = g_index_deltaz;
      //      0.6346016,0.7044372,0.9345708,0.9302069;
      leg_chi2_method->SetX1(0.6346016);
      leg_chi2_method->SetY1(0.7044372);
      leg_chi2_method->SetX2(0.9345708);
      leg_chi2_method->SetY2(0.9345708);
      inform = new TPaveText(0.6140909,0.574664,0.9230335,0.68666, "NDC");
    }
  leg_chi2_method->AddEntry(hist_res[index], "Barlow-Beeston", "l");
  leg_chi2_method->AddEntry(hist_res_Gauss[index], "Gauss", "l");
  c_chi2_method->GetPad(1)->cd();
  h_window[index]->DrawClone();
  //  hist_mc_sum[index]->DrawClone("HIST SAME");
  //  hist_mc_rad_sum[index]->DrawClone("HIST SAME");
  //  hist_mc_norad_sum[index]->DrawClone("HIST SAME");
  hist_res[index]->DrawClone("HIST SAME");
  //  cerr << " prompt photons: " << 
  Double_t N_prph[2] = {0.}, N_rad[2] = {0.}, N_norad[2] = {0.}, N_data[2] = {0.};
  Double_t N_prph_err[2] = {0.}, N_rad_err[2] = {0.}, N_norad_err[2] = {0.}, N_data_err[2] = {0.};
  for(Int_t i=0; i<hist_res[index]->GetNbinsX(); i++)
    {
      N_prph[0] += hist_mc_sum[index]->GetBinContent(i+1);
      N_prph[1] += hist_mc_sum_Gauss[index]->GetBinContent(i+1);

      N_rad[0] += hist_mc_rad_sum[index]->GetBinContent(i+1);
      N_rad[1] += hist_mc_rad_sum_Gauss[index]->GetBinContent(i+1);

      N_norad[0] += hist_mc_norad_sum[index]->GetBinContent(i+1);
      N_norad[1] += hist_mc_norad_sum_Gauss[index]->GetBinContent(i+1);

      N_data[0] += hist_data_sum[index]->GetBinContent(i+1);

      //
      // errors
      //      N_data[1] += hist_mc_sum_Gauss[index]->GetBinContent(i+1);
      N_prph_err[0] += hist_mc_sum[index]->GetBinError(i+1)*hist_mc_sum[index]->GetBinError(i+1);
      N_prph_err[1] += hist_mc_sum_Gauss[index]->GetBinError(i+1) * hist_mc_sum_Gauss[index]->GetBinError(i+1);

      N_rad_err[0] += hist_mc_rad_sum[index]->GetBinError(i+1) * hist_mc_rad_sum[index]->GetBinError(i+1);
      N_rad_err[1] += hist_mc_rad_sum_Gauss[index]->GetBinError(i+1) * hist_mc_rad_sum_Gauss[index]->GetBinError(i+1);

      N_norad_err[0] += hist_mc_norad_sum[index]->GetBinError(i+1) * hist_mc_norad_sum[index]->GetBinError(i+1);
      N_norad_err[1] += hist_mc_norad_sum_Gauss[index]->GetBinError(i+1) * hist_mc_norad_sum_Gauss[index]->GetBinError(i+1);

      N_data_err[0] += hist_data_sum[index]->GetBinError(i+1) * hist_data_sum[index]->GetBinError(i+1);
    }
  for(Int_t i=0; i<2; i++) {
    N_prph_err[i] = TMath::Sqrt(N_prph_err[i]);
    N_rad_err[i] = TMath::Sqrt(N_rad_err[i]);
    N_norad_err[i] = TMath::Sqrt(N_norad_err[i]);
    N_data_err[i] = TMath::Sqrt(N_data_err[i]);
  }
  cerr << "Barlow-Beeston: " << endl;
  cerr << "=== N prph = " << N_prph[0] << " +- " << N_prph_err[0] << endl;
  cerr << "=== N rad = " << N_rad[0] << " +- " << N_rad_err[0] << endl;
  cerr << "=== N norad = " << N_norad[0] << " +- " << N_norad_err[0] << endl;
  cerr << "=== N data = " << N_data[0] << " +- " << N_data_err[0] << endl;
  cerr << "Gauss: " << endl;
  cerr << "=== N prph = " << N_prph[1] << " +- " << N_prph_err[1] << endl;
  cerr << "=== N rad = " << N_rad[1] << " +- " << N_rad_err[1] << endl;
  cerr << "=== N norad = " << N_norad[1] << " +- " << N_norad_err[1] << endl;
  cerr << "=== N data = " << N_data[0] << " +- " << N_data_err[0] << endl;

  hist_res_Gauss[index]->DrawClone("HIST SAME");
  hist_data_sum[index]->DrawClone("P E1 SAME");
  leg_chi2_method->DrawClone();
  //  inform->Draw();
  c_chi2_method->Print(fit_method + "_diff_chi2.eps");
  c_chi2_method->Print(fit_method + "_diff_chi2.png");

  TCanvas *c_fit_err = new TCanvas("c_fit_err", "c_fit_err", 800, 600);
  c_fit_err->Divide(1, 1);
  make_clean_pads(c_fit_err, 1, 0, 0);
  c_fit_err->GetPad(1)->cd();
  hist_check_fit_error->DrawClone();
  c_fit_err->Print("fit_err.eps");

  return 0;
}


void minuitFunctionBarlowBeeston(int& nDim, double* gout, double& result, double par[], int flg) 
{
  Int_t ndf;
  Double_t left, right;
  result = chi2(par, ndf, left, right, "Barlow-Beeston");
}

void minuitFunctionGauss(int& nDim, double* gout, double& result, double par[], int flg) 
{
  Int_t ndf;
  Double_t left, right;
  result = chi2(par, ndf, left, right, "Gauss");
}

Double_t chi2(double* par, Int_t& ndf, Double_t& left, Double_t& right, TString s_method)
{
  Double_t res = 0.;
  ndf = 0;
  Int_t index;
  //  Double_t left, right;
  if(fit_method == "deltaz") {
    index = g_index_deltaz;
    left = 2.;
    right = 30.;
  }
  else
    if(fit_method == "fmax") {
      index = g_index_fmax;
      left = 1.;//0.2
      right = 20.;//1.
    }
    else {
      cerr << "wrong fit method: " << fit_method << endl;
      exit(-1);
    }
      
  for(Int_t i=int(left)/*hist_data_sum[index]->FindBin(left)-1*/; i<int(right)/*hist_data_sum[index]->FindBin(right)*//*GetNbinsX()*/; i++)
    {
      //      cout << i << " " << hist_data_sum[1]->GetBinContent(i+1) << endl;
      Double_t diff;

      Double_t s_d = hist_data_sum[index]->GetBinError(i+1);
      Double_t s_l = hist_mc_rad_sum[index]->GetBinError(i+1);
      Double_t s_q = hist_mc_sum[index]->GetBinError(i+1);
      Double_t s_bg = hist_mc_norad_sum[index]->GetBinError(i+1);
      Double_t s_photon = hist_mc_photon_sum[index]->GetBinError(i+1);

      Double_t v_d = hist_data_sum[index]->GetBinContent(i+1);
      Double_t v_l = hist_mc_rad_sum[index]->GetBinContent(i+1);
      Double_t v_q = hist_mc_sum[index]->GetBinContent(i+1);
      Double_t v_bg = hist_mc_norad_sum[index]->GetBinContent(i+1);
      Double_t v_photon = hist_mc_photon_sum[index]->GetBinContent(i+1);
      //
      // Ian's page
      //
      //      ebb = sdd**2*(param(1)**2*ggn(i)/sgg+(1.-param(1))**2*aan(i)/saa)
      //	edd(i) = sqrt(dd(i) + ebb)
      Double_t dd_i = v_d;
      Double_t sdd = hist_data_sum[index]->Integral();
      //      dd_i /= sdd;
      Double_t ggn_i = v_photon;
      Double_t sgg = hist_mc_photon_sum[index]->Integral();
      //      ggn_i *= sdd/sgg;
      Double_t aan_i = v_bg;
      Double_t saa = hist_mc_norad_sum[index]->Integral();
      //      aan_i *= sdd/saa;
      Double_t ebb = sdd*sdd*(par[0]*par[0]*ggn_i/(sgg*sgg) + (1-par[0])*(1-par[0])*aan_i/(saa*saa));


      // Oleg
      //
      // ====================================================================================================
      diff = hist_data_sum[index]->GetBinContent(i+1) - hist_mc_rad_sum[index]->GetBinContent(i+1) - par[0]*hist_mc_sum[index]->GetBinContent(i+1) - (1-par[0])*hist_mc_norad_sum[index]->GetBinContent(i+1);
      // ====================================================================================================
      //
      // Ian
      //
      // ====================================================================================================
      //      diff = v_d/sdd - par[0]/sgg - (1-par[0])*aan_i/saa;
      //diff = dd_i - par[0]*ggn_i*sdd/sgg - (1-par[0])*aan_i*sdd/saa;
      // ====================================================================================================
      Double_t denom = 0.;
      if(s_method == "Barlow-Beeston") {
	//	denom = 1.;//s_d*s_d + s_l*s_l + par[0]*par[0]*s_q*s_q + (1.-par[0])*(1.-par[0])*s_bg*s_bg;
	//	denom = v_d - v_l + par[0]*par[0]*v_q + (1.-par[0])*(1.-par[0])*v_bg;
	//	denom = (s_d + s_l)*(s_d + s_l) + par[0]*par[0]*s_q*s_q + (1.-par[0])*(1.-par[0])*s_bg*s_bg; //this sent to Ian
	//
	// Oleg
	//
	// ====================================================================================================
	denom = s_d*s_d + s_l*s_l + par[0]*par[0]*s_q*s_q + (1.-par[0])*(1.-par[0])*s_bg*s_bg;
	// ====================================================================================================
	//
	// Ian
	//
	// ====================================================================================================
	//	denom = s_d*s_d + par[0]*par[0]*s_photon*s_photon + (1.-par[0])*(1.-par[0])*s_bg*s_bg;
	//denom = dd_i + ebb;
	//	cout << dd_i << " - " << par[0] << "*" << ggn_i << "*" <<  sdd << "/" << sgg << " - (1-" << par[0] << ")*" << aan_i << "*" << sdd << "/ " << saa << endl;
	//	cout << 
	// ====================================================================================================
	//denom = (s_d )*(s_d ) + par[0]*par[0]*s_q*s_q + (1.-par[0])*(1.-par[0])*s_bg*s_bg;
      }
      else
	if(s_method == "Gauss") {
	  denom = s_d*s_d;
	  //	  cout << "Gauss " << i << " " << denom << endl;
	}
	else
	  {
	    cerr << "Unknown fit method: " << s_method << ". Exiting" << endl;
	    exit(-1);
	  }
      //cout << "errs: " << i << " " << par[0] << " " << s_d << " " << s_l << " " << s_q << " " << s_bg << " " << diff << " " << denom << endl;	
      //      cout << "bin " << i+1  << " " << diff << " " << denom << " " << diff*diff/denom << " " << res << endl;
      res += diff*diff/denom;
      ndf++;
    }
  //  res /= float(ndf-1);
  //  cout << float(hist_data_sum[index]->GetNbinsX() - 1) << endl;
  //  cout << "calling chi2: " << res << endl << endl << endl;
  return res;
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

void variate_bin_content_Gaus(TH1D* h)
{
  for(Int_t i=0; i<h->GetNbinsX(); i++)
    {
      Double_t old_value = h->GetBinContent(i+1);
      Double_t old_error = h->GetBinError(i+1);
      Double_t new_value = random_gen->Gaus(old_value, old_error);
      Double_t new_error;// = TMath::Sqrt(new_value);
      if(new_value < 0)
	{
	  new_value = old_value;
	  new_error = old_error;
	}
      else
	new_error = TMath::Sqrt(new_value);
      h->SetBinContent(i+1, new_value);
      h->SetBinError(i+1, new_error);
      //      cout << "old: " << old_value << " " << old_error << ", new: " << new_value << " " << new_error << endl;
    }
}
