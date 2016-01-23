#include <iostream>
#include <iomanip>
#include <fstream>
#include <initializer_list>
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
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TROOT.h>
#include <TPaveLabel.h>
void dout();
template <typename Head, typename... Tail>
void dout(Head , Tail... );


#include "plot_style_utils.h"
#include "../inc/constants.h"

TString fit_method = "deltaz";
TString chi_method = "Barlow-Beeston";//Gauss


Bool_t g_include_04p_data = kFALSE;
const Int_t n_data_type = 4;// data norad rad prph
const Int_t n_cross = 12; //et, eta, q2, x, et_jet, eta_jet, xgamma, xp, dphi, deta, dphi_e_ph, deta_e_ph
const Int_t n_periods = 3; //0405e, 06e, 0607p

Double_t param_xgamma_PhotonsFit[number_xgamma_bins] = {0.};
Double_t param_xgamma_PhotonsFitforQQ[number_xgamma_bins] = {0.};
Double_t param_err_xgamma_PhotonsFit[number_xgamma_bins] = {0.};
Double_t param_err_xgamma_PhotonsFitforQQ[number_xgamma_bins] = {0.};
Double_t param_xgamma[number_xgamma_bins] = {0.};
Double_t param_err_xgamma[number_xgamma_bins] = {0.};
Double_t chi2_xgamma[number_xgamma_bins] = {0.};
Int_t    dof_xgamma[number_xgamma_bins] = {0};
Int_t    left_xgamma[number_xgamma_bins] = {0};
Int_t    right_xgamma[number_xgamma_bins] = {0};

Double_t param_xp_PhotonsFit[number_xp_bins] = {0.};
Double_t param_xp_PhotonsFitforQQ[number_xp_bins] = {0.};
Double_t param_err_xp_PhotonsFit[number_xp_bins] = {0.};
Double_t param_err_xp_PhotonsFitforQQ[number_xp_bins] = {0.};
Double_t param_xp[number_xp_bins] = {0.};
Double_t param_err_xp[number_xp_bins] = {0.};
Double_t chi2_xp[number_xp_bins] = {0.};
Int_t    dof_xp[number_xp_bins] = {0};
Int_t    left_xp[number_xp_bins] = {0};
Int_t    right_xp[number_xp_bins] = {0};

Double_t param_dphi_PhotonsFit[number_dphi_bins] = {0.};
Double_t param_dphi_PhotonsFitforQQ[number_dphi_bins] = {0.};
Double_t param_err_dphi_PhotonsFit[number_dphi_bins] = {0.};
Double_t param_err_dphi_PhotonsFitforQQ[number_dphi_bins] = {0.};
Double_t param_dphi[number_dphi_bins] = {0.};
Double_t param_err_dphi[number_dphi_bins] = {0.};
Double_t chi2_dphi[number_dphi_bins] = {0.};
Int_t    dof_dphi[number_dphi_bins] = {0};
Int_t    left_dphi[number_dphi_bins] = {0};
Int_t    right_dphi[number_dphi_bins] = {0};

Double_t param_deta_PhotonsFit[number_deta_bins] = {0.};
Double_t param_deta_PhotonsFitforQQ[number_deta_bins] = {0.};
Double_t param_err_deta_PhotonsFit[number_deta_bins] = {0.};
Double_t param_err_deta_PhotonsFitforQQ[number_deta_bins] = {0.};
Double_t param_deta[number_deta_bins] = {0.};
Double_t param_err_deta[number_deta_bins] = {0.};
Double_t chi2_deta[number_deta_bins] = {0.};
Int_t    dof_deta[number_deta_bins] = {0};
Int_t    left_deta[number_deta_bins] = {0};
Int_t    right_deta[number_deta_bins] = {0};

Double_t param_dphi_e_ph_PhotonsFit[number_dphi_e_ph_bins] = {0.};
Double_t param_dphi_e_ph_PhotonsFitforQQ[number_dphi_e_ph_bins] = {0.};
Double_t param_err_dphi_e_ph_PhotonsFit[number_dphi_e_ph_bins] = {0.};
Double_t param_err_dphi_e_ph_PhotonsFitforQQ[number_dphi_e_ph_bins] = {0.};
Double_t param_dphi_e_ph[number_dphi_e_ph_bins] = {0.};
Double_t param_err_dphi_e_ph[number_dphi_e_ph_bins] = {0.};
Double_t chi2_dphi_e_ph[number_dphi_e_ph_bins] = {0.};
Int_t    dof_dphi_e_ph[number_dphi_e_ph_bins] = {0};
Int_t    left_dphi_e_ph[number_dphi_e_ph_bins] = {0};
Int_t    right_dphi_e_ph[number_dphi_e_ph_bins] = {0};

Double_t param_deta_e_ph_PhotonsFit[number_deta_e_ph_bins] = {0.};
Double_t param_deta_e_ph_PhotonsFitforQQ[number_deta_e_ph_bins] = {0.};
Double_t param_err_deta_e_ph_PhotonsFit[number_deta_e_ph_bins] = {0.};
Double_t param_err_deta_e_ph_PhotonsFitforQQ[number_deta_e_ph_bins] = {0.};
Double_t param_deta_e_ph[number_deta_e_ph_bins] = {0.};
Double_t param_err_deta_e_ph[number_deta_e_ph_bins] = {0.};
Double_t chi2_deta_e_ph[number_deta_e_ph_bins] = {0.};
Int_t    dof_deta_e_ph[number_deta_e_ph_bins] = {0};
Int_t    left_deta_e_ph[number_deta_e_ph_bins] = {0};
Int_t    right_deta_e_ph[number_deta_e_ph_bins] = {0};


Double_t param_et_PhotonsFit[number_etbins] = {0.};
Double_t param_et_PhotonsFitforQQ[number_etbins] = {0.};
Double_t param_err_et_PhotonsFit[number_etbins] = {0.};
Double_t param_err_et_PhotonsFitforQQ[number_etbins] = {0.};
Double_t param_et[number_etbins] = {0.};
Double_t param_err_et[number_etbins] = {0.};
Double_t chi2_et[number_etbins] = {0.};
Int_t    dof_et[number_etbins] = {0};
Int_t    left_et[number_etbins] = {0};
Int_t    right_et[number_etbins] = {0};

Double_t param_eta_PhotonsFit[number_etabins] = {0.};
Double_t param_eta_PhotonsFitforQQ[number_etabins] = {0.};
Double_t param_err_eta_PhotonsFit[number_etabins] = {0.};
Double_t param_err_eta_PhotonsFitforQQ[number_etabins] = {0.};
Double_t param_eta[number_etabins] = {0.};
Double_t param_err_eta[number_etabins] = {0.};
Double_t chi2_eta[number_etabins] = {0.};
Int_t    dof_eta[number_etabins] = {0};
Int_t    left_eta[number_etabins] = {0};
Int_t    right_eta[number_etabins] = {0};

Double_t param_q2_PhotonsFit[number_Q2bins] = {0.};
Double_t param_q2_PhotonsFitforQQ[number_Q2bins] = {0.};
Double_t param_err_q2_PhotonsFit[number_Q2bins] = {0.};
Double_t param_err_q2_PhotonsFitforQQ[number_Q2bins] = {0.};
Double_t param_q2[number_Q2bins] = {0.};
Double_t param_err_q2[number_Q2bins] = {0.} ;
Double_t chi2_q2[number_Q2bins] = {0.};
Int_t    dof_q2[number_Q2bins] = {0};
Int_t    left_q2[number_Q2bins] = {0};
Int_t    right_q2[number_Q2bins] = {0};

Double_t param_x_PhotonsFit[number_xbins] = {0.};
Double_t param_x_PhotonsFitforQQ[number_xbins] = {0.};
Double_t param_err_x_PhotonsFit[number_xbins] = {0.};
Double_t param_err_x_PhotonsFitforQQ[number_xbins] = {0.};
Double_t param_x[number_xbins] = {0.};
Double_t param_err_x[number_xbins] = {0.}; 
Double_t chi2_x[number_xbins] = {0.};
Int_t    dof_x[number_xbins] = {0};
Int_t    left_x[number_xbins] = {0};
Int_t    right_x[number_xbins] = {0};

Double_t param_et_jet_PhotonsFit[number_et_jetbins] = {0.};
Double_t param_et_jet_PhotonsFitforQQ[number_et_jetbins] = {0.};
Double_t param_err_et_jet_PhotonsFit[number_et_jetbins] = {0.};
Double_t param_err_et_jet_PhotonsFitforQQ[number_et_jetbins] = {0.};
Double_t param_et_jet[number_et_jetbins] = {0.};
Double_t param_err_et_jet[number_et_jetbins] = {0.}; 
Double_t chi2_et_jet[number_et_jetbins] = {0.};
Int_t    dof_et_jet[number_et_jetbins] = {0};
Int_t    left_et_jet[number_et_jetbins] = {0};
Int_t    right_et_jet[number_et_jetbins] = {0};

Double_t param_eta_jet_PhotonsFit[number_eta_jetbins] = {0.};
Double_t param_eta_jet_PhotonsFitforQQ[number_eta_jetbins] = {0.};
Double_t param_err_eta_jet_PhotonsFit[number_eta_jetbins] = {0.};
Double_t param_err_eta_jet_PhotonsFitforQQ[number_eta_jetbins] = {0.};
Double_t param_eta_jet[number_eta_jetbins] = {0.};
Double_t param_err_eta_jet[number_eta_jetbins] = {0.}; 
Double_t chi2_eta_jet[number_eta_jetbins] = {0.};
Int_t    dof_eta_jet[number_eta_jetbins] = {0};
Int_t    left_eta_jet[number_eta_jetbins] = {0};
Int_t    right_eta_jet[number_eta_jetbins] = {0};
  
TH1D* hist_data[2];
TH1D* hist_mc[2];
TH1D* hist_mc_rad[2];
TH1D* hist_mc_norad[2];
TH1D* hist_mc_photon[2];
TH1D* hist_res[2];

Int_t g_index_fmax = 1;
Int_t g_index_deltaz = 0;

Double_t b_scale, d_scale;//for the reparam

Double_t * PhotonsFits[6+6] = {param_xp_PhotonsFit, param_xgamma_PhotonsFit, param_deta_PhotonsFit, param_dphi_PhotonsFit, param_dphi_e_ph_PhotonsFit, param_deta_e_ph_PhotonsFit,\
							 param_et_PhotonsFit, param_eta_PhotonsFit, param_q2_PhotonsFit, param_x_PhotonsFit, param_et_jet_PhotonsFit, param_eta_jet_PhotonsFit};
Double_t * PhotonsFits_err[6+6] = {param_err_xp_PhotonsFit, param_err_xgamma_PhotonsFit, param_err_deta_PhotonsFit, param_err_dphi_PhotonsFit, param_err_dphi_e_ph_PhotonsFit, param_err_deta_e_ph_PhotonsFit,\
								 param_err_et_PhotonsFit, param_err_eta_PhotonsFit, param_err_q2_PhotonsFit, param_err_x_PhotonsFit, param_err_et_jet_PhotonsFit, param_err_eta_jet_PhotonsFit};
Double_t * PhotonsFitsforQQ[6+6] = {param_xp_PhotonsFitforQQ, param_xgamma_PhotonsFitforQQ, param_deta_PhotonsFitforQQ, param_dphi_PhotonsFitforQQ, param_dphi_e_ph_PhotonsFitforQQ, param_deta_e_ph_PhotonsFitforQQ,\
								  param_et_PhotonsFitforQQ, param_eta_PhotonsFitforQQ, param_q2_PhotonsFitforQQ, param_x_PhotonsFitforQQ, param_et_jet_PhotonsFitforQQ, param_eta_jet_PhotonsFitforQQ};
Double_t * PhotonsFitsforQQ_err[6+6] = {param_err_xp_PhotonsFitforQQ, param_err_xgamma_PhotonsFitforQQ, param_err_deta_PhotonsFitforQQ, param_err_dphi_PhotonsFitforQQ, param_err_dphi_e_ph_PhotonsFitforQQ, param_err_deta_e_ph_PhotonsFitforQQ,\
									  param_err_et_PhotonsFitforQQ, param_err_eta_PhotonsFitforQQ, param_err_q2_PhotonsFitforQQ, param_err_x_PhotonsFitforQQ, param_err_et_jet_PhotonsFitforQQ, param_err_eta_jet_PhotonsFitforQQ};
TFile *f;// = new TFile("cross_sec_histos.root", "recreate", "root file with histohrams");
//f->cd();

void dout() 
{
    cout << endl; 
}
template <typename Head, typename... Tail>
void dout(Head H, Tail... T) 
{
  cout << H << ' ';
  dout(T...);
}
