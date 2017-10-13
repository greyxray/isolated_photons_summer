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
Double_t ScaleX(Double_t x, Double_t tot_width);
Double_t ScaleY(Double_t y, Double_t tot_width);
Double_t ScaleZ(Double_t z, Double_t tot_width);
void ScaleAxis(TAxis *a, Double_t (*Scale)(Double_t, Double_t));
void ScaleXaxis(TH1 *h, Double_t (*Scale)(Double_t, Double_t));
void ScaleYaxis(TH1 *h, Double_t (*Scale)(Double_t, Double_t));
void ScaleZaxis(TH1 *h, Double_t (*Scale)(Double_t, Double_t));

  void Init();
  void SetFigure3Style(TH1D* h_data, TH1D* h_qq_ll, TH1D* h_qq, TH1D* h_ll, TH1D* h_bg);
  void PlotControlPlot(Double_t * a, Double_t * a_err, Double_t number_bins, Double_t * array_bin, Int_t index, TString variable, TString canvas_name,\
          TString title, TString xaxis_name, TString yaxis_name, TString legend_possition);
  void DoParamScale(TH1D* h, Double_t *a, Double_t *a_err, Int_t nbins, bool qq);
  void set_hist_atributes(Int_t number, TString name, TString dir, TString xaxis, Double_t xmin, Double_t xmax, Double_t ymin, Bool_t logy, Int_t rebin);
  void SetVioletStyle(TH1D* h_data,TH1D*  h_res,TH1D*  h_qq,TH1D*  h_ll,TH1D*  h_bg);
  void PlotAcceptance();
  void PlotPurity();
  void PlotFitInBinsOfCrossSec();
  void PlotCrossSec();
  void CalculateCrossSec(TH1D* data, TH1D* ll_det, TH1D* ll_had, TH1D* ll_hd, TH1D *det, TH1D* had, TH1D* hd, TH1D *ll_acc, TH1D *acc, Double_t Lumi, TH1D **res, TString name, Double_t* param,
			 Double_t* param_err, TH1D **res_copy ,TH1D* ll_det_copy , TH1D* det_copy
       /*, Double_t integral_data, Double_t integral_ll, Double_t integral_data_err, Double_t integral_ll_err*/);
  void CalculateCrossSecQQfit0(TH1D* data, TH1D* ll_det, TH1D* ll_had, TH1D* ll_hd, TH1D *det, TH1D* had, TH1D* hd, TH1D *ll_acc, TH1D *acc, Double_t Lumi, TH1D **res, TString name, Double_t* param,
       Double_t* param_err, TH1D **res_copy ,TH1D* ll_det_copy , TH1D* det_copy
       /*, Double_t integral_data, Double_t integral_ll, Double_t integral_data_err, Double_t integral_ll_err*/);
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
  //Hist();
  ~Hist();
  TF1* f_unity;
  ofstream fout;

  Double_t sys_acc, sys_fit;
  TString q2_cut;

  TString correctiontype, str_selectedoutput;
  ofstream selectedoutput;//Stream class to write on files


  TString s_periods[n_periods];
  TString s_file_data[n_periods];
  TString s_file_norad[n_periods];
  TString s_file_rad[n_periods];
  TString s_file_prph[n_periods];
  TString s_var[n_cross];
  TString s_title[n_cross];
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

  TH1D* h_deltaz_xgamma_data[number_xgamma_bins][n_periods];
  TH1D* h_deltaz_xgamma_norad[number_xgamma_bins][n_periods];
  TH1D* h_deltaz_xgamma_rad[number_xgamma_bins][n_periods];
  TH1D* h_deltaz_xgamma_prph[number_xgamma_bins][n_periods];
 
  TH1D* h_deltaz_xp_data[number_xp_bins][n_periods];
  TH1D* h_deltaz_xp_norad[number_xp_bins][n_periods];
  TH1D* h_deltaz_xp_rad[number_xp_bins][n_periods];
  TH1D* h_deltaz_xp_prph[number_xp_bins][n_periods];
 
  TH1D* h_deltaz_dphi_data[number_dphi_bins][n_periods];
  TH1D* h_deltaz_dphi_norad[number_dphi_bins][n_periods];
  TH1D* h_deltaz_dphi_rad[number_dphi_bins][n_periods];
  TH1D* h_deltaz_dphi_prph[number_dphi_bins][n_periods];
 
  TH1D* h_deltaz_deta_data[number_deta_bins][n_periods];
  TH1D* h_deltaz_deta_norad[number_deta_bins][n_periods];
  TH1D* h_deltaz_deta_rad[number_deta_bins][n_periods];
  TH1D* h_deltaz_deta_prph[number_deta_bins][n_periods];
 
  TH1D* h_deltaz_dphi_e_ph_data[number_dphi_e_ph_bins][n_periods];
  TH1D* h_deltaz_dphi_e_ph_norad[number_dphi_e_ph_bins][n_periods];
  TH1D* h_deltaz_dphi_e_ph_rad[number_dphi_e_ph_bins][n_periods];
  TH1D* h_deltaz_dphi_e_ph_prph[number_dphi_e_ph_bins][n_periods];
 
  TH1D* h_deltaz_deta_e_ph_data[number_deta_e_ph_bins][n_periods];
  TH1D* h_deltaz_deta_e_ph_norad[number_deta_e_ph_bins][n_periods];
  TH1D* h_deltaz_deta_e_ph_rad[number_deta_e_ph_bins][n_periods];
  TH1D* h_deltaz_deta_e_ph_prph[number_deta_e_ph_bins][n_periods];

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

//******************************sum*************************************
  TH1D* h_deltaz_xgamma_data_sum[number_xgamma_bins];
  TH1D* h_deltaz_xgamma_norad_sum[number_xgamma_bins];
  TH1D* h_deltaz_xgamma_rad_sum[number_xgamma_bins];
  TH1D* h_deltaz_xgamma_prph_sum[number_xgamma_bins];
  TH1D* h_deltaz_xgamma_photon_sum[number_xgamma_bins];
  TH1D* h_deltaz_xgamma_res[number_xgamma_bins];
 
  TH1D* h_deltaz_xp_data_sum[number_xp_bins];
  TH1D* h_deltaz_xp_norad_sum[number_xp_bins];
  TH1D* h_deltaz_xp_rad_sum[number_xp_bins];
  TH1D* h_deltaz_xp_prph_sum[number_xp_bins];
  TH1D* h_deltaz_xp_photon_sum[number_xp_bins];
  TH1D* h_deltaz_xp_res[number_xp_bins];
 
  TH1D* h_deltaz_dphi_data_sum[number_dphi_bins];
  TH1D* h_deltaz_dphi_norad_sum[number_dphi_bins];
  TH1D* h_deltaz_dphi_rad_sum[number_dphi_bins];
  TH1D* h_deltaz_dphi_prph_sum[number_dphi_bins];
  TH1D* h_deltaz_dphi_photon_sum[number_dphi_bins];
  TH1D* h_deltaz_dphi_res[number_dphi_bins];
 
  TH1D* h_deltaz_deta_data_sum[number_deta_bins];
  TH1D* h_deltaz_deta_norad_sum[number_deta_bins];
  TH1D* h_deltaz_deta_rad_sum[number_deta_bins];
  TH1D* h_deltaz_deta_prph_sum[number_deta_bins];
  TH1D* h_deltaz_deta_photon_sum[number_deta_bins];
  TH1D* h_deltaz_deta_res[number_deta_bins];
 
  TH1D* h_deltaz_dphi_e_ph_data_sum[number_dphi_e_ph_bins];
  TH1D* h_deltaz_dphi_e_ph_norad_sum[number_dphi_e_ph_bins];
  TH1D* h_deltaz_dphi_e_ph_rad_sum[number_dphi_e_ph_bins];
  TH1D* h_deltaz_dphi_e_ph_prph_sum[number_dphi_e_ph_bins];
  TH1D* h_deltaz_dphi_e_ph_photon_sum[number_dphi_e_ph_bins];
  TH1D* h_deltaz_dphi_e_ph_res[number_dphi_e_ph_bins];
 
  TH1D* h_deltaz_deta_e_ph_data_sum[number_deta_e_ph_bins];
  TH1D* h_deltaz_deta_e_ph_norad_sum[number_deta_e_ph_bins];
  TH1D* h_deltaz_deta_e_ph_rad_sum[number_deta_e_ph_bins];
  TH1D* h_deltaz_deta_e_ph_prph_sum[number_deta_e_ph_bins];
  TH1D* h_deltaz_deta_e_ph_photon_sum[number_deta_e_ph_bins];
  TH1D* h_deltaz_deta_e_ph_res[number_deta_e_ph_bins];

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
  TH1D* h_chi2_perbin_xgamma[number_xgamma_bins];
  TH1D* h_chi2_perbin_xp[number_xp_bins];
  TH1D* h_chi2_perbin_dphi[number_dphi_bins];
  TH1D* h_chi2_perbin_deta[number_deta_bins];
  TH1D* h_chi2_perbin_dphi_e_ph[number_dphi_e_ph_bins];
  TH1D* h_chi2_perbin_deta_e_ph[number_deta_e_ph_bins];

//*********************************profile, det had, hd*********************************

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

 TH1D* h_det_rad_sum_copy[n_cross];  
 TH1D* h_det_prph_sum_copy[n_cross]; 

enum {n_hist = 7};//take care 7 - if dZ is already implemented

  Int_t g_index_fmax ;
  Int_t g_index_deltaz ;
//const Int_t n_hist = 6;//enum {kNumcs = 6};class ClassName{ public: enum {kNumcs = 6}; .... };
//enum Heights{kPeter = 190, kVasia = 175};
//Heights — назва енумерація
TString s_hist[n_hist]; 
TString s_xaxis[n_hist];
Double_t hist_xmin[n_hist];
Double_t hist_xmax[n_hist];
Double_t hist_ymin[n_hist];
Bool_t hist_logy[n_hist];
Int_t hist_rebin[n_hist];

TH1D *hist_mc_control[n_periods][n_hist];
TH1D *hist_mc_norad_control[n_periods][n_hist];
TH1D *hist_mc_rad_control[n_periods][n_hist];
TH1D *hist_data_control[n_periods][n_hist];

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

TH1D *hist_ratio[n_hist];
TH1D *hist_res[n_hist];
//TGraphAsymmErrors* gr_acceptance_rad[n_cross][n_periods];
//TGraphAsymmErrors* gr_acceptance_prph[n_cross][n_periods];

Double_t param_dphi[number_dphi_bins];
Double_t param_err_dphi[number_dphi_bins];
Double_t param_deta_e_ph[number_deta_e_ph_bins];
Double_t param_err_deta_e_ph[number_deta_e_ph_bins];


 TString s_cross_x[n_cross];// = {"", "", "", ""};
 TString s_cross_y[n_cross];// = {"", "", "", ""};

};

#endif
