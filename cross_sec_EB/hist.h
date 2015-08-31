#ifndef HIST_h
#define HIST_h
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile.h>
#include <TDirectory.h>
#include "../inc/constants.h"
class Hist
{
 public:
  //void Init();
  void PlotAcceptance();
  void PlotPurity();
  void PlotFitInBinsOfCrossSec();
  void PlotCrossSec();
  void CalculateCrossSec(TH1D* data, TH1D* ll_det, TH1D* ll_had, TH1D* ll_hd, TH1D *det, TH1D* had, TH1D* hd, TH1D *ll_acc, TH1D *acc, Double_t Lumi, TH1D **res, TString name, Double_t* param,
			 Double_t* param_err/*, Double_t integral_data, Double_t integral_ll, Double_t integral_data_err, Double_t integral_ll_err*/);
  void CalculateCrossSec(TH1D *h_Data, TH1D *h_Lepto_det,
			       TH1D *h_Lepto_had, TH1D *h_Lepto_hd,
			       Double_t Lumi, Int_t Linecolor, TH1D **h_Cross_Sec);
  void Compare1st2nd(Int_t i, TH1D** h_1st, TH1D** h_2nd);
  void SetSystematicErrors(Int_t n, TH1D** h_1st, TH1D** h_2nd, TGraphAsymmErrors** gr_1st);
  void RelativeToAbsolute(TGraphAsymmErrors* rel, TGraphAsymmErrors** abs, TGraphAsymmErrors* cross);
  void SystPlusStat(TGraphAsymmErrors* syst_abs, TGraphAsymmErrors* stat_abs, TGraphAsymmErrors** array);
  void plot_box(Int_t n, Double_t* x, Double_t* xe_left, Double_t* xe_right,
		Double_t* y, Double_t* ye_up, Double_t* ye_down);
  void plot_box_posele(Int_t n, Double_t* x, Double_t* xe_left, Double_t* xe_right,
		       Double_t* y_ele, Double_t* ye_ele_down, Double_t* ye_ele_up,
		       Double_t* y_pos, Double_t* ye_pos_down, Double_t* ye_pos_up);
  void plot_box_posele_ra(Int_t n, Double_t* x, Double_t* xe_left, Double_t* xe_right,
		       Double_t* y_ele, Double_t* ye_ele_down, Double_t* ye_ele_up,
		       Double_t* y_pos, Double_t* ye_pos_down, Double_t* ye_pos_up);
  void plot_box_posele_ra(Int_t n, Double_t* x, Double_t* xe_left, Double_t* xe_right,
		       Double_t* y_ele, Double_t* ye_ele_down, Double_t* ye_ele_up,
			  Double_t* y_pos, Double_t* ye_pos_down, Double_t* ye_pos_up, Int_t Color);
  void apply_hadronisation_corrections();
  Hist();
  ~Hist();
  TF1* f_unity;
  ofstream fout;
  TString s_periods[n_periods];
  TString s_file_data[n_periods];
  TString s_file_norad[n_periods];
  TString s_file_rad[n_periods];
  TString s_file_prph[n_periods];
  TString s_var[n_cross];
  TFile *file_data[n_periods];
  TFile *file_norad[n_periods];
  TFile *file_rad[n_periods];
  TFile *file_prph[n_periods];
  Double_t lumi_data[n_periods];
  Double_t lumi_mc_bg[n_periods];
  Double_t total_luminosity_data;
  Double_t lumi_mc_prph;
  TH1D* h_acceptance_rad[n_cross];
  TH1D* h_acceptance_prph[n_cross];
  TH1D* h_purity_rad[n_cross];
  TH1D* h_purity_prph[n_cross];
  //
  // deltaz in bins of X 
  // 
  TH1D* h_deltaz_et_data[number_etbins][n_periods];
  TH1D* h_deltaz_et_norad[number_etbins][n_periods];
  TH1D* h_deltaz_et_rad[number_etbins][n_periods];
  TH1D* h_deltaz_et_prph[number_etbins][n_periods];
 
TH1D* h_deltaz_eta_data[number_etabins][n_periods];
TH1D* h_deltaz_eta_norad[number_etabins][n_periods];
TH1D* h_deltaz_eta_rad[number_etabins][n_periods];
TH1D* h_deltaz_eta_prph[number_etabins][n_periods];

TH1D* h_deltaz_q2_data[number_Q2bins][n_periods];
TH1D* h_deltaz_q2_norad[number_Q2bins][n_periods];
TH1D* h_deltaz_q2_rad[number_Q2bins][n_periods];
TH1D* h_deltaz_q2_prph[number_Q2bins][n_periods];

TH1D* h_deltaz_x_data[number_xbins][n_periods];
TH1D* h_deltaz_x_norad[number_xbins][n_periods];
TH1D* h_deltaz_x_rad[number_xbins][n_periods];
TH1D* h_deltaz_x_prph[number_xbins][n_periods];

TH1D* h_deltaz_et_jet_data[number_et_jetbins][n_periods];
TH1D* h_deltaz_et_jet_norad[number_et_jetbins][n_periods];
TH1D* h_deltaz_et_jet_rad[number_et_jetbins][n_periods];
TH1D* h_deltaz_et_jet_prph[number_et_jetbins][n_periods];

TH1D* h_deltaz_eta_jet_data[number_eta_jetbins][n_periods];
TH1D* h_deltaz_eta_jet_norad[number_eta_jetbins][n_periods];
TH1D* h_deltaz_eta_jet_rad[number_eta_jetbins][n_periods];
TH1D* h_deltaz_eta_jet_prph[number_eta_jetbins][n_periods];

//**********************************************************************

TH1D* h_deltaz_et_data_sum[number_etbins];
TH1D* h_deltaz_et_norad_sum[number_etbins];
TH1D* h_deltaz_et_rad_sum[number_etbins];
TH1D* h_deltaz_et_prph_sum[number_etbins];
TH1D* h_deltaz_et_photon_sum[number_etbins];
TH1D* h_deltaz_et_res[number_etbins];

TH1D* h_deltaz_eta_data_sum[number_etabins];
TH1D* h_deltaz_eta_norad_sum[number_etabins];
TH1D* h_deltaz_eta_rad_sum[number_etabins];
TH1D* h_deltaz_eta_prph_sum[number_etabins];
TH1D* h_deltaz_eta_photon_sum[number_etabins];
TH1D* h_deltaz_eta_res[number_etabins];

TH1D* h_deltaz_q2_data_sum[number_Q2bins];
TH1D* h_deltaz_q2_norad_sum[number_Q2bins];
TH1D* h_deltaz_q2_rad_sum[number_Q2bins];
TH1D* h_deltaz_q2_prph_sum[number_Q2bins];
TH1D* h_deltaz_q2_photon_sum[number_Q2bins];
TH1D* h_deltaz_q2_res[number_Q2bins];

TH1D* h_deltaz_x_data_sum[number_xbins];
TH1D* h_deltaz_x_norad_sum[number_xbins];
TH1D* h_deltaz_x_rad_sum[number_xbins];
TH1D* h_deltaz_x_prph_sum[number_xbins];
TH1D* h_deltaz_x_photon_sum[number_xbins];
TH1D* h_deltaz_x_res[number_xbins];

TH1D* h_deltaz_et_jet_data_sum[number_et_jetbins];
TH1D* h_deltaz_et_jet_norad_sum[number_et_jetbins];
TH1D* h_deltaz_et_jet_rad_sum[number_et_jetbins];
TH1D* h_deltaz_et_jet_prph_sum[number_et_jetbins];
TH1D* h_deltaz_et_jet_photon_sum[number_et_jetbins];
TH1D* h_deltaz_et_jet_res[number_et_jetbins];

TH1D* h_deltaz_eta_jet_data_sum[number_eta_jetbins];
TH1D* h_deltaz_eta_jet_norad_sum[number_eta_jetbins];
TH1D* h_deltaz_eta_jet_rad_sum[number_eta_jetbins];
TH1D* h_deltaz_eta_jet_prph_sum[number_eta_jetbins];
TH1D* h_deltaz_eta_jet_photon_sum[number_eta_jetbins];
TH1D* h_deltaz_eta_jet_res[number_eta_jetbins];

 TH1D* h_chi2_perbin_eta[number_etabins];
 TH1D* h_chi2_perbin_et[number_etbins];
 TH1D* h_chi2_perbin_x[number_xbins];
 TH1D* h_chi2_perbin_Q2[number_Q2bins];
 TH1D* h_chi2_perbin_et_jet[number_et_jetbins];
 TH1D* h_chi2_perbin_eta_jet[number_eta_jetbins];

//***********************************************************************

TProfile* prof_det_data[n_cross][n_periods];
TProfile* prof_det_rad[n_cross][n_periods];
TProfile* prof_det_norad[n_cross][n_periods];
TProfile* prof_det_prph[n_cross][n_periods];

TProfile* prof_had_rad[n_cross][n_periods];
TProfile* prof_had_norad[n_cross][n_periods];
TProfile* prof_had_prph[n_cross][n_periods];

TProfile* prof_hd_rad[n_cross][n_periods];
TProfile* prof_hd_norad[n_cross][n_periods];
TProfile* prof_hd_prph[n_cross][n_periods];

TProfile* prof_det_data_sum[n_cross];
TProfile* prof_det_rad_sum[n_cross];
TProfile* prof_det_norad_sum[n_cross];
TProfile* prof_det_prph_sum[n_cross];

TProfile* prof_had_rad_sum[n_cross];
TProfile* prof_had_norad_sum[n_cross];
TProfile* prof_had_prph_sum[n_cross];

TProfile* prof_hd_rad_sum[n_cross];
TProfile* prof_hd_norad_sum[n_cross];
TProfile* prof_hd_prph_sum[n_cross];

 TH1D* h_det_data[n_cross][n_periods]; 
 TH1D* h_det_rad[n_cross][n_periods]; 
 TH1D* h_det_norad[n_cross][n_periods]; 
 TH1D* h_det_prph[n_cross][n_periods]; 
 TH1D* h_had_prph[n_cross][n_periods];
 TH1D* h_had_rad[n_cross][n_periods];
 TH1D* h_hd_prph[n_cross][n_periods];
 TH1D* h_hd_rad[n_cross][n_periods];

 TH1D* h_det_data_sum[n_cross]; 
 TH1D* h_det_rad_sum[n_cross]; 
 TH1D* h_det_norad_sum[n_cross]; 
 TH1D* h_det_prph_sum[n_cross]; 
 TH1D* h_had_prph_sum[n_cross];
 TH1D* h_had_rad_sum[n_cross];
 TH1D* h_hd_prph_sum[n_cross];
 TH1D* h_hd_rad_sum[n_cross];

//TGraphAsymmErrors* gr_acceptance_rad[n_cross][n_periods];
//TGraphAsymmErrors* gr_acceptance_prph[n_cross][n_periods];


 TString s_cross_x[n_cross];// = {"", "", "", ""};
 TString s_cross_y[n_cross];// = {"", "", "", ""};

};

#endif
