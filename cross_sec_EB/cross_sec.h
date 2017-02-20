#include <iostream>
#include <iomanip>
#include <fstream>
#include <initializer_list>
#include <vector>
#include <limits>
#include <math.h>       /* isnan, sqrt */
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
#include <TMarker.h>

#include "TH1.h"
#include "TArrayD.h"

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
Double_t * all_bins[12] = {et_bin, eta_bin_crosssec, Q2_bin, x_bin, et_jet_bin, eta_jet_bin, \
							xgamma_bin, xp_bin, dphi_bin, deta_bin, dphi_e_ph_bin, deta_e_ph_bin};
Int_t all_nbins[12] = {number_etbins, number_etabins, number_Q2bins, number_xbins, number_et_jetbins, number_eta_jetbins, \
						number_xgamma_bins, number_xp_bins, number_dphi_bins, number_deta_bins, number_dphi_e_ph_bins, number_deta_e_ph_bins};
char * cs_y_names[12] = {"d#sigma/dE_{T}^{#gamma} (pb/GeV)", "d#sigma/d#eta^{#gamma} (pb)", \
							"d#sigma/dQ^{2} (pb/GeV^{2})","d#sigma/dx (pb)", \
							"d#sigma/dE_{T}^{jet} (pb/GeV)", "d#sigma/d#eta^{jet} (pb)", \
							"d#sigma/dx_{#gamma}(pb)", "d#sigma/dx_{p} (pb)", \
							"d#sigma/d#Delta#phi (pb/deg)", "d#sigma/d#Delta#eta (pb)", \
							"d#sigma/d#Delta#phi_{e,#gamma} (pb/deg)", "d#sigma/d#Delta#eta_{e,#gamma} (pb)"};							
TString cs_x_names[12] = {(TString)"E_{T}^{#gamma} (GeV)", (TString)"#eta^{#gamma}", \
							(TString)"Q^{2} (GeV^{2})", (TString)"x", \
							(TString)"E_{T}^{jet} (GeV)", (TString)"#eta^{jet}", \
							(TString)"x_{#gamma}", (TString)"x_{p}", \
							(TString)"#Delta#phi (deg.)", (TString)"#Delta#eta", \
							(TString)"#Delta#phi_{e,#gamma} (deg.)", (TString)"#Delta#eta_{e,#gamma}"};
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

Double_t et_sys[number_etbins] = { 0.184748088962 , 0.0747882871846 , 0.0393969631127 , 0.0189854576321 };
Double_t eta_sys[number_etabins] = { 0.423800275071 , 0.487878132196 , 0.443901265232 , 0.50381661763 };
Double_t Q2_sys[number_Q2bins] = { 0.0224260999674 , 0.00858689466571 , 0.00546653392059 , 0.00153660969264 , 0.000131106853558 };
Double_t x_sys[number_xbins] = { 360.382971365 , 122.067943478 , 18.6493130436 , 2.25300333056 };
Double_t et_jet_sys[number_et_jetbins] = { 0.108318547235 , 0.100885556201 , 0.0714368538361 , 0.0487568174771 , 0.0138301869655 , 0.00597986020342 };
Double_t eta_jet_sys[number_eta_jetbins] = { 0.192704209412 , 0.263347347765 , 0.20624684943 , 0.231590873849 };
Double_t xgamma_sys[number_xgamma_bins] = { 0.0958724424535 , 0.348822002567 , 0.513479401899 , 0.684521871729 , 3.26698095112 , 6.57912883747 };
Double_t xp_sys[number_xp_bins] = { 28.6815313617 , 54.3743682607 , 38.2238214305 , 14.2267986121 , 2.72588289092 , 1.63156 };
Double_t dphi_sys[number_dphi_bins] = { 0.00315450409811 , 0.00418652170602 , 0.00643482151112 , 0.00715958301003 , 0.00367540256299 , 0.00406340294581 , 0.00708797555724 };
Double_t deta_sys[number_deta_bins] = { 0.06389627191 , 0.155134712589 , 0.257191703161 , 0.13611338619 , 0.251034054562 , 0.103070566725 };
Double_t dphi_e_ph_sys[number_dphi_e_ph_bins] = { 0.00209223921194 , 0.00280451047912 , 0.00306385384116 , 0.00620919694324 , 0.00778832094581 , 0.00740004707434 };
Double_t deta_e_ph_sys[number_deta_e_ph_bins] = { 0.161600574024 , 0.292377084259 , 0.424532749031 , 0.266773829067 , 0.0907841245758 };

Double_t et_sys_q2_lt_30[number_etbins] = { 0.0873800261788 , 0.0359524634413 , 0.103934435985 , 0.0448841278717 };
Double_t eta_sys_q2_lt_30[number_etabins] = { 0.227531133144 , 0.258713625608 , 0.14135951321 , 0.245774027869 };
Double_t Q2_sys_q2_lt_30[number_Q2bins] = { 0.022258717444 , 0.00457414323562 , 0.0 , 0.0 , 0.0 };
Double_t x_sys_q2_lt_30[number_xbins] = { 297.069577919 , 47.1125031653 , 0.0 , 0.0 };
Double_t et_jet_sys_q2_lt_30[number_et_jetbins] = { 0.0745106849301 , 0.0445490188192 , 0.0566381556109 , 0.0187250253538 , 0.0403897254261 , 0.0003580265 };
Double_t eta_jet_sys_q2_lt_30[number_eta_jetbins] = { 0.0897535506916 , 0.11713394587 , 0.108261271238 , 0.117786845085 };
Double_t xgamma_sys_q2_lt_30[number_xgamma_bins] = { 0.0723119903336 , 0.156555055651 , 0.536401598571 , 0.595125094644 , 1.50559447915 , 3.63639673337 };
Double_t xp_sys_q2_lt_30[number_xp_bins] = { 14.4094289443 , 25.7535872987 , 20.8578469946 , 10.5516138689 , 13.1736525427 , 0.0 };
Double_t dphi_sys_q2_lt_30[number_dphi_bins] = { 0.000846280181116 , 0.00164609328563 , 0.00613685824058 , 0.00600115737712 , 0.00404420052328 , 0.00190648765404 , 0.00617560027933 };
Double_t deta_sys_q2_lt_30[number_deta_bins] = { 0.0853179493937 , 0.0844413952499 , 0.108654401199 , 0.0888257458454 , 0.128199442179 , 0.0608815561459 };
Double_t dphi_e_ph_sys_q2_lt_30[number_dphi_e_ph_bins] = { 0.00170564225294 , 0.000982490992325 , 0.00223967701354 , 0.00347644090558 , 0.00126011407718 , 0.0037915591051 };
Double_t deta_e_ph_sys_q2_lt_30[number_deta_e_ph_bins] = { 0.157405649756 , 0.156471999492 , 0.181081287134 , 0.0604269828016 , 0.0 };

Double_t et_sys_q2_gt_30[number_etbins] = { 0.0956202717785 , 0.0455392501832 , 0.0323157809437 , 0.0114465688527 };
Double_t eta_sys_q2_gt_30[number_etabins] = { 0.203852062965 , 0.265116784927 , 0.401972508419 , 0.278488481764 };
Double_t Q2_sys_q2_gt_30[number_Q2bins] = { 0.0 , 0.00417396424458 , 0.00551459806899 , 0.00154111419191 , 0.000145203468106 };
Double_t x_sys_q2_gt_30[number_xbins] = { 51.599703066 , 105.031258085 , 18.2498971367 , 2.57086083492 };
Double_t et_jet_sys_q2_gt_30[number_et_jetbins] = { 0.0588628201032 , 0.0684403313971 , 0.046826907935 , 0.0397784008068 , 0.014646681049 , 0.00742861997177 };
Double_t eta_jet_sys_q2_gt_30[number_eta_jetbins] = { 0.0988193161596 , 0.127191474164 , 0.109275981007 , 0.144385654325 };
Double_t xgamma_sys_q2_gt_30[number_xgamma_bins] = { 0.105471475775 , 0.214567109607 , 0.396375992209 , 0.451463004354 , 2.28976479141 , 4.24581077122 };
Double_t xp_sys_q2_gt_30[number_xp_bins] = { 11.4239738817 , 23.8696713373 , 18.1808082947 , 7.41759841863 , 3.16510179892 , 2.88131 };
Double_t dphi_sys_q2_gt_30[number_dphi_bins] = { 0.0020906252701 , 0.00265903907549 , 0.00293707040178 , 0.00362287989657 , 0.00566121805334 , 0.00609364510023 , 0.00216021776564 };
Double_t deta_sys_q2_gt_30[number_deta_bins] = { 0.0415088567356 , 0.0956664887421 , 0.133992838428 , 0.0675427566435 , 0.217649285262 , 0.0602232527766 };
Double_t dphi_e_ph_sys_q2_gt_30[number_dphi_e_ph_bins] = { 0.000962084136134 , 0.00216454727715 , 0.000949713369917 , 0.00283942147585 , 0.0074585417199 , 0.00408260250392 };
Double_t deta_e_ph_sys_q2_gt_30[number_deta_e_ph_bins] = { 0.0 , 0.119830244447 , 0.288300384625 , 0.200686397397 , 0.0966201877198 };


Double_t * all_syst[12] = {et_sys, eta_sys, Q2_sys, x_sys, et_jet_sys, eta_jet_sys, xgamma_sys, xp_sys, dphi_sys, deta_sys, dphi_e_ph_sys, deta_e_ph_sys};


Double_t xgamma_theor[number_xgamma_bins] = {1.556799/ 10,5.848120/ 10,6.985698/ 10,7.665373/ 10,8.140512/ 10,1.828429* 10};
Double_t xp_theor[number_xp_bins] = {6.089192 * 100, 9.719590 * 100, 4.831771 * 100, 1.778382 * 100, 4.668674 * 10, 6.017276};
Double_t dphi_theor[number_dphi_bins] = {3.686592 / 100,  7.791403 / 100, 1.249631 / 10,   1.433854 / 10,  1.480789 / 10,  1.305700 / 10,  1.080152 / 10};
Double_t deta_theor[number_deta_bins] = {1.715301, 3.166015, 4.144682, 4.433577, 3.577533, 1.187959};
Double_t dphi_e_ph_theor[number_dphi_e_ph_bins] = {2.387177 / 100, 3.478839 / 100, 5.966719 / 100, 1.021914 / 10, 1.458710 / 10, 1.372228 / 10};

Double_t * all_theory[12] = {0, 0, 0, 0, 0, 0, xgamma_theor, xp_theor, dphi_theor, deta_theor, dphi_e_ph_theor, 0};

//BLZ
Double_t theor_xgamma[number_xgamma_bins] = { 0.1564726 , 0.5829751 , 0.7100769 , 0.7371457 , 0.8159014 , 125.7932 };
Double_t theor_xp[number_xp_bins] = { 608.9192 , 971.959 , 483.1771 , 177.8382 , 46.68674 , 6.017276 };
Double_t theor_dphi[number_dphi_bins] = { 0.03686592 , 0.07791403 , 0.1249631 , 0.1433854 , 0.1480789 , 0.13057 , 0.1080152 };
Double_t theor_deta[number_deta_bins] = { 1.715301 , 3.166015 , 4.144682 , 4.433577 , 3.577533 , 1.187959 };
Double_t theor_dphi_e_gamma[number_dphi_e_ph_bins] = { 0.02387177 , 0.03478839 , 0.05966719 , 0.1021914 , 0.145871 , 0.1372228 };
Double_t theor_deta_e_gamma[number_deta_e_ph_bins] = { 1.45014 , 4.229818 , 6.370512 , 5.772007 , 3.372212 };

Double_t theor_xgamma_pos_error[number_xgamma_bins] = { 0.099934 , 0.5553299 , 0.7494451 , 0.9207533 , 1.0267256 , 10.9787 };
Double_t theor_xp_pos_error[number_xp_bins] = { 92.9838 , 104.714 , 73.7316 , 35.4135 , 7.20303 , 1.56039 };
Double_t theor_dphi_pos_error[number_dphi_bins] = { 0.00640039 , 0.01550074 , 0.016768 , 0.0153724 , 0.0136855 , 0.0163622 , 0.0100834 };
Double_t theor_deta_pos_error[number_deta_bins] = { 0.255486 , 0.378529 , 0.343385 , 0.466079 , 0.458352 , 0.213107 };
Double_t theor_dphi_e_gamma_pos_error[number_dphi_e_ph_bins] = { 0.00827339 , 0.0093863 , 0.01062202 , 0.0081597 , 0.0130729 , 0.0123545 };
Double_t theor_deta_e_gamma_pos_error[number_deta_e_ph_bins] = { 0.54098 , 0.961131 , 0.898709 , 0.524189 , 0.304116 };

Double_t theor_xgamma_neg_error[number_xgamma_bins] = { 0.10682828 , 0.4435552 , 0.5474051 , 0.560472 , 0.6077246 , 17.0 };
Double_t theor_xp_neg_error[number_xp_bins] = { 119.1916 , 157.8043 , 67.6632 , 18.823 , 4.73124 , 0.579717 };
Double_t theor_dphi_neg_error[number_dphi_bins] = { 0.00535148 , 0.012263 , 0.0185595 , 0.0192699 , 0.0200292 , 0.0217651 , 0.02344284 };
Double_t theor_deta_neg_error[number_deta_bins] = { 0.25026 , 0.429392 , 0.559737 , 0.692839 , 0.655773 , 0.2194166 };
Double_t theor_dphi_e_gamma_neg_error[number_dphi_e_ph_bins] = { 0.00716782 , 0.00886361 , 0.01054127 , 0.01103255 , 0.013411 , 0.0203905 };
Double_t theor_deta_e_gamma_neg_error[number_deta_e_ph_bins] = { 0.323534 , 0.832212 , 1.107124 , 0.758223 , 0.28614 };

Double_t * all_theory_cs[12] = {0, 0, 0, 0, 0, 0, theor_xgamma, theor_xp, theor_dphi, theor_deta, theor_dphi_e_gamma, theor_deta_e_gamma};
Double_t * all_theory_pos[12] = {0, 0, 0, 0, 0, 0, theor_xgamma_pos_error, theor_xp_pos_error, theor_dphi_pos_error, theor_deta_pos_error, theor_dphi_e_gamma_pos_error, theor_deta_e_gamma_pos_error};
Double_t * all_theory_neg[12] = {0, 0, 0, 0, 0, 0, theor_xgamma_neg_error, theor_xp_neg_error, theor_dphi_neg_error, theor_deta_neg_error, theor_dphi_e_gamma_neg_error, theor_deta_e_gamma_neg_error};

//Fontannaz

	//Full Q2 range with self-definition of errors
		//For the meanwhile mean variables are just center between predictions of pt 2.5 and pt 0.5 so the errors would be semmetric - boundaries
		// Double_t font_xgamma[number_xgamma_bins] = {1.77864105, 2.9388162475, 5.29177594, 8.597595365, 17.44771155, 48.0353915};
		// Double_t font_xp[number_xp_bins] = {372.92281, 699.69313, 417.862304, 146.5044075, 29.5121153335, 3.060679665};
		// Double_t font_deta[number_deta_bins] = {0.8041835715, 2.9169913569999997, 3.6937328569999996, 3.336542057, 2.2211529715, 0.4495153855};
		// Double_t font_dphi_e_gamma[number_dphi_e_ph_bins] = {0.019395463, 0.025020163, 0.037863148, 0.064914172, 0.098684485, 0.085195744};

		// Double_t font_xgamma_pos[number_xgamma_bins] = {0.049210449999999906, 0.10613124750000003, 0.3568629400000001, 0.7763663649999994, 2.114704549999999, 2.6352355000000003};
		// Double_t font_xp_pos[number_xp_bins] = {28.18692999999996, 65.86427000000003, 48.996984, 10.563527499999992, 1.5535553335000003, 0.029196334999999962};
		// Double_t font_deta_pos[number_deta_bins] = {0.17041357150000003, 0.6584713570000003, 0.34572285700000016, 0.08681205699999994, 0.055872971499999924, -0.0121046145};
		// Double_t font_dphi_e_gamma_pos[number_dphi_e_ph_bins] = {0, 0, 0, 0, 0, 0};

		// Double_t font_xgamma_neg[number_xgamma_bins] = {0.04921045000000013, 0.10613124750000003, 0.3568629400000001, 0.7763663650000003, 2.114704550000001, 2.6352355000000003};
		// Double_t font_xp_neg[number_xp_bins] = {28.186930000000018, 65.86427000000003, 48.996984, 10.56352750000002, 1.5535553335000003, 0.029196334999999962};
		// Double_t font_deta_neg[number_deta_bins] = {0.17041357150000003, 0.6584713569999998, 0.3457228569999997, 0.08681205699999994, 0.055872971499999924, -0.0121046145};
		// Double_t font_dphi_e_gamma_neg[number_dphi_e_ph_bins] = {0, 0, 0, 0, 0, 0};

	//Fontanaz errors
	//after M.Fontannaz provided some error definitions:
	// deta errors: 3% ? deta > -0.1 : 20%
	// dphi_e_gamma errors: 3% ? dphi_e_gamma < 135 : 20%
	
		//print [ format(l[i] * (e[i]), '.5f') for i in range(len(l)) ]  ---python 2.7
		// 0< Q2< 320
			//pT_cut in center-of-mass frame = 0.5 GeV/c
				Double_t font_xgamma_pt05_Q2full[number_xgamma_bins] = {1.8278515, 3.044947495, 5.64863888, 9.37396173, 19.5624161, 50.670627};
				Double_t font_xp_pt05_Q2full[number_xp_bins] = {401.10974, 765.5574, 466.859288, 157.067935, 31.065670667, 3.089876};
				Double_t font_deta_pt05_Q2full[number_deta_bins] = {0.974597143, 3.575462714, 4.039455714, 3.423354114, 2.277025943, 0.437410771};
				Double_t font_dphi_e_gamma_pt05_Q2full[number_dphi_e_ph_bins] = {0.01997915, 0.025773689, 0.039274816, 0.066393259, 0.109853939, 0.142112183};

				Double_t font_xgamma_pos_pt05_Q2full[number_xgamma_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_xp_pos_pt05_Q2full[number_xp_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_deta_pos_pt05_Q2full[number_deta_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_dphi_e_gamma_pos_pt05_Q2full[number_dphi_e_ph_bins] = {0.00225, 0.00281, 0.00400, 0.00089, 0.00102, 0.00094};// DONE

				Double_t font_xgamma_neg_pt05_Q2full[number_xgamma_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_xp_neg_pt05_Q2full[number_xp_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_deta_neg_pt05_Q2full[number_deta_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_dphi_e_gamma_neg_pt05_Q2full[number_dphi_e_ph_bins] = {0, 0, 0, 0, 0, 0};
			//pT_cut in center-of-mass frame = 2.5 GeV/c - ADDITIONAL 10% unc added everywhere - for now: only this 10 % included!!!!
				Double_t font_xgamma_pt25_Q2full[number_xgamma_bins] = {1.7294306, 2.832685, 4.934913, 7.821229, 15.333007, 45.400156};
				Double_t font_xp_pt25_Q2full[number_xp_bins] = {344.73588, 633.82886, 368.86532, 135.94088, 27.95856, 3.03148333};
				Double_t font_deta_pt25_Q2full[number_deta_bins] = {0.63377, 2.25852, 3.34801, 3.24973, 2.16528, 0.46162};
				Double_t font_dphi_e_gamma_pt25_Q2full[number_dphi_e_ph_bins] = {0.019395463, 0.025020163, 0.037863148, 0.064914172, 0.098684485, 0.085195744};

				Double_t font_xgamma_pos_pt25_Q2full[number_xgamma_bins] = {0.17294, 0.28327, 0.49349, 0.78212, 1.53330, 4.54002};//e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
				Double_t font_xp_pos_pt25_Q2full[number_xp_bins] = {34.47359, 63.38289, 36.88653, 13.59409, 2.79586, 0.30315};//e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
				Double_t font_deta_pos_pt25_Q2full[number_deta_bins] = {0.06338, 0.22585, 0.33480, 0.32497, 0.21653, 0.04616};//e = [0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.1044030650891055, 0.1044030650891055, 0.1044030650891055]//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]
				Double_t font_dphi_e_gamma_pos_pt25_Q2full[number_dphi_e_ph_bins] = {0.00194, 0.00250, 0.00379, 0.00649, 0.00987, 0.00852};//e = [0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.1044030650891055, 0.1044030650891055]//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]

				Double_t font_xgamma_neg_pt25_Q2full[number_xgamma_bins] = {0.17294, 0.28327, 0.49349, 0.78212, 1.53330, 4.54002};//e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
				Double_t font_xp_neg_pt25_Q2full[number_xp_bins] = {34.47359, 63.38289, 36.88653, 13.59409, 2.79586, 0.30315};//e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
				Double_t font_deta_neg_pt25_Q2full[number_deta_bins] = {0.06338, 0.22585, 0.33480, 0.32497, 0.21653, 0.04616};//e = [0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.1044030650891055, 0.1044030650891055, 0.1044030650891055]//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]
				Double_t font_dphi_e_gamma_neg_pt25_Q2full[number_dphi_e_ph_bins] = {0.00194, 0.00250, 0.00379, 0.00649, 0.00987, 0.00852};//e = [0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.1044030650891055, 0.1044030650891055]//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]
			//Combined - This is what was used before
				//For the meanwhile mean variables are just center between predictions of pt 2.5 and pt 0.5 so the errors would be semmetric - boundaries
				Double_t font_xgamma[number_xgamma_bins] = {1.77864105, 2.9388162475, 5.29177594, 8.597595365, 17.44771155, 48.0353915};
				Double_t font_xp[number_xp_bins] = {372.92281, 699.69313, 417.862304, 146.5044075, 29.5121153335, 3.060679665};
				Double_t font_deta[number_deta_bins] = {0.8041835715, 2.9169913569999997, 3.6937328569999996, 3.336542057, 2.2211529715, 0.4495153855};
				Double_t font_dphi_e_gamma[number_dphi_e_ph_bins] = {0.019687306500000001, 0.025396926, 0.038568982000000002, 0.065653715500000001, 0.104269212, 0.11365396350000001};

				Double_t font_xgamma_pos[number_xgamma_bins] = {0.049210449999999906, 0.10613124750000003, 0.3568629400000001, 0.7763663649999994, 2.114704549999999, 2.6352355000000003};//NEED TO SMEAR
				Double_t font_xp_pos[number_xp_bins] = {28.18692999999996, 65.86427000000003, 48.996984, 10.563527499999992, 1.5535553335000003, 0.029196334999999962};//NEED TO SMEAR
				Double_t font_deta_pos[number_deta_bins] = {0.17041357150000003, 0.6584713569999998, 0.3457228569999997, 0.08681205699999994, 0.055872971499999924, -0.0121046145};//NEED TO SMEAR// this error was additionaly smeared up by e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03], last el set to 0 since neg '-0.01247'
				Double_t font_dphi_e_gamma_pos[number_dphi_e_ph_bins] = {0.0002918434999999997, 0.00037676299999999871, 0.00070583399999999893, 0.00073954349999999502, 0.0055847269999999977, 0.0284582195};//NEED TO SMEAR

				Double_t font_xgamma_neg[number_xgamma_bins] = {0.04921045000000013, 0.10613124750000003, 0.3568629400000001, 0.7763663650000003, 2.114704550000001, 2.6352355000000003};//NEED TO SMEAR
				Double_t font_xp_neg[number_xp_bins] = {28.186930000000018, 65.86427000000003, 48.996984, 10.56352750000002, 1.5535553335000003, 0.029196334999999962};//NEED TO SMEAR
				Double_t font_deta_neg[number_deta_bins] = {0.17041357150000003, 0.6584713569999998, 0.3457228569999997, 0.08681205699999994, 0.055872971499999924, -0.0121046145};//NEED TO SMEAR// this error was additionaly smeared doun by e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03], last el set to 0 since neg '-0.01174'
				Double_t font_dphi_e_gamma_neg[number_dphi_e_ph_bins] = {0.0002918434999999997, 0.00037676299999999871, 0.00070583399999999893, 0.00073954349999999502, 0.0055847269999999977, 0.0284582195};//NEED TO SMEAR

		// 0<Q2<30 range
			//pT_cut in  in center-of-mass frame = 0.5 GeV/c
				Double_t font_xgamma_pt05_Q2lt30[number_xgamma_bins] = {0.896, 1.958, 2.598, 3.582, 6.417, 20.668};
				Double_t font_xp_pt05_Q2lt30[number_xp_bins] = {0, 0, 0, 0, 0, 0}; 
				Double_t font_deta_pt05_Q2lt30[number_deta_bins] = {0.358, 1.103, 1.718, 1.507, 0.939, 0.265};
				Double_t font_dphi_e_gamma_pt05_Q2lt30[number_dphi_e_ph_bins] = {0.01140, 0.01422, 0.02052, 0.02994, 0.03666, 0.03759};

				Double_t font_xgamma_pos_pt05_Q2lt30[number_xgamma_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_xp_pos_pt05_Q2lt30[number_xp_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_deta_pos_pt05_Q2lt30[number_deta_bins] = {0.07160, 0.22060, 0.34360, 0.04521, 0.02817, 0.00795};// DONE
				Double_t font_dphi_e_gamma_pos_pt05_Q2lt30[number_dphi_e_ph_bins] = {0.00228, 0.00284, 0.00410, 0.00599, 0.00110, 0.00113};// DONE

				Double_t font_xgamma_neg_pt05_Q2lt30[number_xgamma_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_xp_neg_pt05_Q2lt30[number_xp_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_deta_neg_pt05_Q2lt30[number_deta_bins] = {0.07160, 0.22060, 0.34360, 0.04521, 0.02817, 0.00795};// DONE
				Double_t font_dphi_e_gamma_neg_pt05_Q2lt30[number_dphi_e_ph_bins] = {0.00228, 0.00284, 0.00410, 0.00599, 0.00110, 0.00113};// DONE
			//pT_cut in center-of-mass frame = 2.5 GeV/c
				Double_t font_xgamma_pt25_Q2lt30[number_xgamma_bins] = {0.861, 1.914, 2.507, 3.376, 5.826, 18.901};
				Double_t font_xp_pt25_Q2lt30[number_xp_bins] = {0, 0, 0, 0, 0, 0}; 
				Double_t font_deta_pt25_Q2lt30[number_deta_bins] = {0.296, 0.967, 1.487, 1.467, 0.915, 0.260};//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]
				Double_t font_dphi_e_gamma_pt25_Q2lt30[number_dphi_e_ph_bins] = {0.01125, 0.01405, 0.01998, 0.02956, 0.03384, 0.03126};//e = [0.2, 0.2, 0.2, 0.2, 0.03, 0.03]

				Double_t font_xgamma_pos_pt25_Q2lt30[number_xgamma_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_xp_pos_pt25_Q2lt30[number_xp_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_deta_pos_pt25_Q2lt30[number_deta_bins] = {0.05920, 0.19340, 0.29740, 0.04401, 0.02745, 0.00780};// DONE//
				Double_t font_dphi_e_gamma_pos_pt25_Q2lt30[number_dphi_e_ph_bins] = {0.00225, 0.00281, 0.00400, 0.00591, 0.00102, 0.00094};// DONE//

				Double_t font_xgamma_neg_pt25_Q2lt30[number_xgamma_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_xp_neg_pt25_Q2lt30[number_xp_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_deta_neg_pt25_Q2lt30[number_deta_bins] = {0.05920, 0.19340, 0.29740, 0.04401, 0.02745, 0.00780};// DONE
				Double_t font_dphi_e_gamma_neg_pt25_Q2lt30[number_dphi_e_ph_bins] = {0.00225, 0.00281, 0.00400, 0.00591, 0.00102, 0.00094};// DONE
			//Combined  
				//print [format((l1[i]+l2[i])/2,'.5f') for i in range(len(l1))]
				Double_t font_xgamma_Q2lt30[number_xgamma_bins] = {0.87850, 1.93600, 2.55250, 3.47900, 6.12150, 19.78450};
				Double_t font_xp_Q2lt30[number_xp_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_deta_Q2lt30[number_deta_bins] = {0.32700, 1.03500, 1.60250, 1.48700, 0.92700, 0.26250};
				Double_t font_dphi_e_gamma_Q2lt30[number_dphi_e_ph_bins] = {0.01132, 0.01413, 0.02025, 0.02975, 0.03525, 0.03442};

				// print [format( (l1[i]*(1 + dl1[i]) - l12[i])  ,'.5f') for i in range(len(l1))]
				Double_t font_xgamma_pos_Q2lt30[number_xgamma_bins] = {0.01750, 0.02200, 0.04550, 0.10300, 0.29550, 0.88350};// RECALCULATE WHEN FONT PROVIDES ERRORS
				Double_t font_xp_pos_Q2lt30[number_xp_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_deta_pos_Q2lt30[number_deta_bins] = {0.05663, 0.31132, 0.70580, 0.08813, 0.03845, 0.00461};
				Double_t font_dphi_e_gamma_pos_Q2lt30[number_dphi_e_ph_bins] = {0.00011, 0.00013, 0.00035, 0.00037, 0.00145, 0.00321};

				//print [format( (l12[i] - l2[i]*(1 - dl2[i]))   ,'.5f') for i in range(len(l1))]
				Double_t font_xgamma_neg_Q2lt30[number_xgamma_bins] = {0.01750, 0.02200, 0.04550, 0.10300, 0.29550, 0.88350};// RECALCULATE WHEN FONT PROVIDES ERRORS
				Double_t font_xp_neg_Q2lt30[number_xp_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_deta_neg_Q2lt30[number_deta_bins] = {0.04852, 0.25502, 0.55773, 0.08456, 0.03712, 0.00453};
				Double_t font_dphi_e_gamma_neg_Q2lt30[number_dphi_e_ph_bins] = {0.00010, 0.00012, 0.00035, 0.00036, 0.00144, 0.00319};

		// Q2>30 range
			//pT_cut in  in center-of-mass frame = 0.5 GeV/c
				Double_t font_xgamma_pt05_Q2gt30[number_xgamma_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_xp_pt05_Q2gt30[number_xp_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_deta_pt05_Q2gt30[number_deta_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_dphi_e_gamma_pt05_Q2gt30[number_dphi_e_ph_bins] = {0, 0, 0, 0, 0, 0};

				Double_t font_xgamma_pos_pt05_Q2gt30[number_xgamma_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_xp_pos_pt05_Q2gt30[number_xp_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_deta_pos_pt05_Q2gt30[number_deta_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_dphi_e_gamma_pos_pt05_Q2gt30[number_dphi_e_ph_bins] = {0, 0, 0, 0, 0, 0};

				Double_t font_xgamma_neg_pt05_Q2gt30[number_xgamma_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_xp_neg_pt05_Q2gt30[number_xp_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_deta_neg_pt05_Q2gt30[number_deta_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_dphi_e_gamma_neg_pt05_Q2gt30[number_dphi_e_ph_bins] = {0, 0, 0, 0, 0, 0};
			//pT_cut in center-of-mass frame = 2.5 GeV/c
				Double_t font_xgamma_pt25_Q2gt30[number_xgamma_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_xp_pt25_Q2gt30[number_xp_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_deta_pt25_Q2gt30[number_deta_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_dphi_e_gamma_pt25_Q2gt30[number_dphi_e_ph_bins] = {0, 0, 0, 0, 0, 0};

				Double_t font_xgamma_pos_pt25_Q2gt30[number_xgamma_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_xp_pos_pt25_Q2gt30[number_xp_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_deta_pos_pt25_Q2gt30[number_deta_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_dphi_e_gamma_pos_pt25_Q2gt30[number_dphi_e_ph_bins] = {0, 0, 0, 0, 0, 0};

				Double_t font_xgamma_neg_pt25_Q2gt30[number_xgamma_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_xp_neg_pt25_Q2gt30[number_xp_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_deta_neg_pt25_Q2gt30[number_deta_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_dphi_e_gamma_neg_pt25_Q2gt30[number_dphi_e_ph_bins] = {0, 0, 0, 0, 0, 0};
			//Combined
				Double_t font_xgamma_Q2gt30[number_xgamma_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_xp_Q2gt30[number_xp_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_deta_Q2gt30[number_deta_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_dphi_e_gamma_Q2gt30[number_dphi_e_ph_bins] = {0, 0, 0, 0, 0, 0};

				Double_t font_xgamma_pos_Q2gt30[number_xgamma_bins] = {0, 0, 0, 0, 0, 0};//NEED TO SMEAR
				Double_t font_xp_pos_Q2gt30[number_xp_bins] = {0, 0, 0, 0, 0, 0};//NEED TO SMEAR
				Double_t font_deta_pos_Q2gt30[number_deta_bins] = {0, 0, 0, 0, 0, 0};//NEED TO SMEAR
				Double_t font_dphi_e_gamma_pos_Q2gt30[number_dphi_e_ph_bins] = {0, 0, 0, 0, 0, 0};//NEED TO SMEAR

				Double_t font_xgamma_neg_Q2gt30[number_xgamma_bins] = {0, 0, 0, 0, 0, 0};//NEED TO SMEAR
				Double_t font_xp_neg_Q2gt30[number_xp_bins] = {0, 0, 0, 0, 0, 0};//NEED TO SMEAR
				Double_t font_deta_neg_Q2gt30[number_deta_bins] = {0, 0, 0, 0, 0, 0};//NEED TO SMEAR
				Double_t font_dphi_e_gamma_neg_Q2gt30[number_dphi_e_ph_bins] = {0, 0, 0, 0, 0, 0};//NEED TO SMEAR
			

// Q2gt30
	//pT_cut in center-of-mass frame = 2.5 GeV/c
	Double_t * all_theory_cs_font_pt25_Q2gt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pt25_Q2gt30, font_xp_pt25_Q2gt30, 0, font_deta_pt25_Q2gt30, font_dphi_e_gamma_pt25_Q2gt30, 0};
	Double_t * all_theory_cs_font_pt25_pos_Q2gt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pos_pt25_Q2gt30, font_xp_pos_pt25_Q2gt30, 0, font_deta_pos_pt25_Q2gt30, font_dphi_e_gamma_pos_pt25_Q2gt30, 0};
	Double_t * all_theory_cs_font_pt25_neg_Q2gt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_neg_pt25_Q2gt30, font_xp_neg_pt25_Q2gt30, 0, font_deta_neg_pt25_Q2gt30, font_dphi_e_gamma_neg_pt25_Q2gt30, 0};
	//pT_cut in center-of-mass frame = 0.5 GeV/c
	Double_t * all_theory_cs_font_pt05_Q2gt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pt05_Q2gt30, font_xp_pt05_Q2gt30, 0, font_deta_pt05_Q2gt30, font_dphi_e_gamma_pt05_Q2gt30, 0};
	Double_t * all_theory_cs_font_pt05_pos_Q2gt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pos_pt05_Q2gt30, font_xp_pos_pt05_Q2gt30, 0, font_deta_pos_pt05_Q2gt30, font_dphi_e_gamma_pos_pt05_Q2gt30, 0};
	Double_t * all_theory_cs_font_pt05_neg_Q2gt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_neg_pt05_Q2gt30, font_xp_neg_pt05_Q2gt30, 0, font_deta_neg_pt05_Q2gt30, font_dphi_e_gamma_neg_pt05_Q2gt30, 0};
	//Combined for pt 2.5 and 0.5 region
	Double_t * all_theory_cs_font_Q2gt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_Q2gt30, font_xp_Q2gt30, 0, font_deta_Q2gt30, font_dphi_e_gamma_Q2gt30, 0};
	Double_t * all_theory_cs_font_pos_Q2gt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pos_Q2gt30, font_xp_pos_Q2gt30, 0, font_deta_pos_Q2gt30, font_dphi_e_gamma_pos_Q2gt30, 0};
	Double_t * all_theory_cs_font_neg_Q2gt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_neg_Q2gt30, font_xp_neg_Q2gt30, 0, font_deta_neg_Q2gt30, font_dphi_e_gamma_neg_Q2gt30, 0};

// Q2lt30
	//pT_cut in center-of-mass frame = 2.5 GeV/c
	Double_t * all_theory_cs_font_pt25_Q2lt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pt25_Q2lt30, font_xp_pt25_Q2lt30, 0, font_deta_pt25_Q2lt30, font_dphi_e_gamma_pt25_Q2lt30, 0};
	Double_t * all_theory_cs_font_pt25_pos_Q2lt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pos_pt25_Q2lt30, font_xp_pos_pt25_Q2lt30, 0, font_deta_pos_pt25_Q2lt30, font_dphi_e_gamma_pos_pt25_Q2lt30, 0};
	Double_t * all_theory_cs_font_pt25_neg_Q2lt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_neg_pt25_Q2lt30, font_xp_neg_pt25_Q2lt30, 0, font_deta_neg_pt25_Q2lt30, font_dphi_e_gamma_neg_pt25_Q2lt30, 0};
	//pT_cut in center-of-mass frame = 0.5 GeV/c
	Double_t * all_theory_cs_font_pt05_Q2lt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pt05_Q2lt30, font_xp_pt05_Q2lt30, 0, font_deta_pt05_Q2lt30, font_dphi_e_gamma_pt05_Q2lt30, 0};
	Double_t * all_theory_cs_font_pt05_pos_Q2lt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pos_pt05_Q2lt30, font_xp_pos_pt05_Q2lt30, 0, font_deta_pos_pt05_Q2lt30, font_dphi_e_gamma_pos_pt05_Q2lt30, 0};
	Double_t * all_theory_cs_font_pt05_neg_Q2lt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_neg_pt05_Q2lt30, font_xp_neg_pt05_Q2lt30, 0, font_deta_neg_pt05_Q2lt30, font_dphi_e_gamma_neg_pt05_Q2lt30, 0};
	//Combined for pt 2.5 and 0.5 region
	Double_t * all_theory_cs_font_Q2lt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_Q2lt30, font_xp_Q2lt30, 0, font_deta_Q2lt30, font_dphi_e_gamma_Q2lt30, 0};
	Double_t * all_theory_cs_font_pos_Q2lt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pos_Q2lt30, font_xp_pos_Q2lt30, 0, font_deta_pos_Q2lt30, font_dphi_e_gamma_pos_Q2lt30, 0};
	Double_t * all_theory_cs_font_neg_Q2lt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_neg_Q2lt30, font_xp_neg_Q2lt30, 0, font_deta_neg_Q2lt30, font_dphi_e_gamma_neg_Q2lt30, 0};

// Full region
	//pT_cut in center-of-mass frame = 2.5 GeV/c
	Double_t * all_theory_cs_font_pt25[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pt25_Q2full, font_xp_pt25_Q2full, 0, font_deta_pt25_Q2full, font_dphi_e_gamma_pt25_Q2full, 0};
	Double_t * all_theory_cs_font_pt25_pos[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pos_pt25_Q2full, font_xp_pos_pt25_Q2full, 0, font_deta_pos_pt25_Q2full, font_dphi_e_gamma_pos_pt25_Q2full, 0};
	Double_t * all_theory_cs_font_pt25_neg[12] = {0, 0, 0, 0, 0, 0, font_xgamma_neg_pt25_Q2full, font_xp_neg_pt25_Q2full, 0, font_deta_neg_pt25_Q2full, font_dphi_e_gamma_neg_pt25_Q2full, 0};
	//pT_cut in center-of-mass frame = 0.5 GeV/c
	Double_t * all_theory_cs_font_pt05[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pt05_Q2full, font_xp_pt05_Q2full, 0, font_deta_pt05_Q2full, font_dphi_e_gamma_pt05_Q2full, 0};
	Double_t * all_theory_cs_font_pt05_pos[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pos_pt05_Q2full, font_xp_pos_pt05_Q2full, 0, font_deta_pos_pt05_Q2full, font_dphi_e_gamma_pos_pt05_Q2full, 0};
	Double_t * all_theory_cs_font_pt05_neg[12] = {0, 0, 0, 0, 0, 0, font_xgamma_neg_pt05_Q2full, font_xp_neg_pt05_Q2full, 0, font_deta_neg_pt05_Q2full, font_dphi_e_gamma_neg_pt05_Q2full, 0};
	//Combined for pt 2.5 and 0.5 region
	Double_t * all_theory_cs_font[12] = {0, 0, 0, 0, 0, 0, font_xgamma, font_xp, 0, font_deta, font_dphi_e_gamma, 0};
	Double_t * all_theory_cs_font_pos[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pos, font_xp_pos, 0, font_deta_pos, font_dphi_e_gamma_pos, 0};
	Double_t * all_theory_cs_font_neg[12] = {0, 0, 0, 0, 0, 0, font_xgamma_neg, font_xp_neg, 0, font_deta_neg, font_dphi_e_gamma_neg, 0};


// Hadronisation correction

	Double_t hadcor_et[number_etbins] = {0.80089, 0.8436, 0.8889, 0.920169};//{ 1 , 1 , 1 , 1 };
	Double_t hadcor_eta[number_etabins] = {	0.897217, 0.856589, 0.831106, 0.786123};//{ 1 , 1 , 1 , 1  };
	Double_t hadcor_Q2[number_Q2bins] = { 0.864872, 0.84278, 0.82571, 0.80850, 0.836009};//{ 1 , 1 , 1 , 1 ,1};
	Double_t hadcor_x[number_xbins] = {	0.896322, 0.83105, 0.782931, 0.853225};//{ 1 , 1 , 1 , 1  };
	Double_t hadcor_et_jet[number_et_jetbins] = { 0.743404, 0.770444, 0.847409, 0.934409, 1.08148, 1.10222 };//{ 1 , 1 , 1 , 1 ,1 ,1};
	Double_t hadcor_eta_jet[number_eta_jetbins] = {	0.713228, 0.739034, 0.881313, 1.08716 };//{ 1 , 1 , 1 , 1  };
	Double_t hadcor_xgamma[number_xgamma_bins] = { 0.626939, 0.89639, 1.26588, 1.9319, 2.05619, 0.643178 };
	Double_t hadcor_xp[number_xp_bins] = { 0.691671, 0.805629, 0.913111, 0.990287, 1.06323, 0.996296 };//last bin manually set to 1
	Double_t hadcor_dphi[number_dphi_bins] = { 0.677041, 0.81817, 0.875374, 0.915694, 0.953324, 0.954095, 0.943792 };
	Double_t hadcor_deta[number_deta_bins] = { 0.755721, 0.65941, 0.740169, 0.870975, 1.04352, 1.10866 };
	Double_t hadcor_dphi_e_gamma[number_dphi_e_ph_bins] = {	0.948884, 0.944103, 0.91829, 0.852325, 0.792186, 0.730761 };
	Double_t hadcor_deta_e_gamma[number_deta_e_ph_bins] = {	0.804829, 0.817935, 0.83285, 0.85489, 0.887841 };

	Double_t hadcor_et_err[number_etbins] = { 0.00183595, 0.002383, 0.00308931, 0.00180418 };
	Double_t hadcor_eta_err[number_etabins] = {0.0057262, 0.00532276, 0.00531591, 0.00536681 };
	Double_t hadcor_Q2_err[number_Q2bins] = {0.00106809, 0.000787114, 0.000576308, 0.000491361, 0.000385195};
	Double_t hadcor_x_err[number_xbins] = {0.107403, 0.0632892, 0.0392608, 0.0896211};
	Double_t hadcor_et_jet_err[number_et_jetbins] = {0.0044137, 0.00343492, 0.00456749, 0.00630348, 0.00374265, 0.00401438};
	Double_t hadcor_eta_jet_err[number_eta_jetbins] = {0.00588159, 0.00432966, 0.00543222, 0.00774054 };
	Double_t hadcor_xgamma_err[number_xgamma_bins]  = {0.0326688, 0.0502385, 0.126718, 0.13838, 0.0770724, 0.00676406 };
	Double_t hadcor_xp_err[number_xp_bins] = {0.0642579, 0.0525744, 0.0892017, 0.0766185, 0.134542, 0.200497 };
	Double_t hadcor_dphi_err[number_dphi_bins] = {0.000474113, 0.000678834, 0.00333124, 0.00325289, 0.00323925, 0.00315134, 0.0027131 };
	Double_t hadcor_deta_err[number_deta_bins] = {0.0168032, 0.00665623, 0.00507899, 0.00591916, 0.00948652, 0.0210241 };
	Double_t hadcor_dphi_e_gamma_err[number_dphi_e_ph_bins] = {0.000641616, 0.000731633, 0.000692594, 0.000705054, 0.000828641, 0.000865265 };
	Double_t hadcor_deta_e_gamma_err[number_deta_e_ph_bins] = {0.00731033, 0.00456975, 0.00388988, 0.00460632, 0.0074846 };

	// Double_t hadcor_et[number_etbins] = { 1 , 1 , 1 , 1 };
	// Double_t hadcor_eta[number_etabins] = { 1 , 1 , 1 , 1  };
	// Double_t hadcor_Q2[number_Q2bins] = { 1 , 1 , 1 , 1 ,1};
	// Double_t hadcor_x[number_xbins] = { 1 , 1 , 1 , 1  };
	// Double_t hadcor_et_jet[number_et_jetbins] = { 1 , 1 , 1 , 1 ,1 ,1};
	// Double_t hadcor_eta_jet[number_eta_jetbins] = { 1 , 1 , 1 , 1  };
	// Double_t hadcor_xgamma[number_xgamma_bins] = { 1 , 1 , 1 , 1 ,1 ,1};
	// Double_t hadcor_xp[number_xp_bins] = { 1 , 1 , 1 , 1 ,1 ,1};
	// Double_t hadcor_dphi[number_dphi_bins] = { 1 , 1 , 1 , 1 ,1 ,1, 1};
	// Double_t hadcor_deta[number_deta_bins] = { 1 , 1 , 1 , 1 ,1 ,1};
	// Double_t hadcor_dphi_e_gamma[number_dphi_e_ph_bins] = { 1 , 1 , 1 , 1 ,1 ,1};
	// Double_t hadcor_deta_e_gamma[number_deta_e_ph_bins] = { 1 , 1 , 1 , 1 ,1 };

	// Double_t hadcor_et_err[number_etbins] = { 0 , 0 , 0 , 0 };
	// Double_t hadcor_eta_err[number_etabins] = { 0 , 0 , 0 , 0  };
	// Double_t hadcor_Q2_err[number_Q2bins] = { 0 , 0 , 0 , 0 ,0};
	// Double_t hadcor_x_err[number_xbins] = { 0 , 0 , 0 , 0  };
	// Double_t hadcor_et_jet_err[number_et_jetbins] = { 0 , 0 , 0 , 0 ,0 ,0};
	// Double_t hadcor_eta_jet_err[number_eta_jetbins] = { 0 , 0 , 0 , 0  };
	// Double_t hadcor_xgamma_err[number_xgamma_bins] = { 0 , 0 , 0 , 0 ,0 ,0};
	// Double_t hadcor_xp_err[number_xp_bins] = { 0 , 0 , 0 , 0 ,0 ,0};
	// Double_t hadcor_dphi_err[number_dphi_bins] = { 0 , 0 , 0 , 0 ,0 ,0, 0};
	// Double_t hadcor_deta_err[number_deta_bins] = { 0 , 0 , 0 , 0 ,0 ,0};
	// Double_t hadcor_dphi_e_gamma_err[number_dphi_e_ph_bins] = { 0 , 0 , 0 , 0 ,0 ,0};
	// Double_t hadcor_deta_e_gamma_err[number_deta_e_ph_bins] = { 0 , 0 , 0 , 0 ,0 };

Double_t * all_hadcort[12] = {hadcor_et, hadcor_eta, hadcor_Q2, hadcor_x, hadcor_et_jet, hadcor_eta_jet, hadcor_xgamma, hadcor_xp, hadcor_dphi, hadcor_deta, hadcor_dphi_e_gamma, hadcor_deta_e_gamma};
Double_t * all_hadcort_err[12] = {hadcor_et_err, hadcor_eta_err, hadcor_Q2_err, hadcor_x_err, hadcor_et_jet_err, hadcor_eta_jet_err, hadcor_xgamma_err, hadcor_xp_err, hadcor_dphi_err, hadcor_deta_err, hadcor_dphi_e_gamma_err, hadcor_deta_e_gamma_err};


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
