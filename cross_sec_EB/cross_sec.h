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


template<typename T,int N> 
//template argument deduction
int size(T (&arr1)[N]) //Passing the array by reference 
{
   size_t size;
   size=sizeof(arr1)/sizeof(arr1[0]);  

   //std::cout<<size<<std::endl; //Correctly prints the size of arr

   //EDIT

   //std::cout<<N; //Correctly prints the size too [cool trick ;-)]
	return N;
}


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
	
	// 0< Q2 < 350
		/*OLD
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
					*/
		//NEW
			//pT_cut in center-of-mass frame = 0.5 GeV/c
				Double_t font_xgamma_pt05_Q2full[number_xgamma_bins] = {1.27, 3.04, 5.45, 8.86, 18.54, 49.39};
				Double_t font_xp_pt05_Q2full[number_xp_bins] = 	{380., 761., 446., 152., 29.13, 2.90};
				//Double_t font_dphi_pt05_Q2full[number_dphi_bins] = 
				Double_t font_deta_pt05_Q2full[number_deta_bins] = {0.884, 3.457, 3.743, 3.318, 2.180, 0.435};
				Double_t font_dphi_e_gamma_pt05_Q2full[number_dphi_e_ph_bins] = {0.0185, 0.024, 0.037, 0.064, 0.106, 0.133};
				//Double_t font_deta_e_gamma_pt05_Q2full[number_deta_e_ph_bins] =
				

				//e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
				//e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
				//e = [0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.1044030650891055, 0.1044030650891055, 0.1044030650891055]//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]
				//e = [0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.1044030650891055, 0.1044030650891055]//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]
					/*
						Double_t font_xgamma_pos_pt05_Q2full[number_xgamma_bins] = {0.12700, 0.30400, 0.54500, 0.88600, 1.85400, 4.93900};
						Double_t font_xp_pos_pt05_Q2full[number_xp_bins] = {38.00000, 76.10000, 44.60000, 15.20000, 2.91300, 0.29000};
						Double_t font_deta_pos_pt05_Q2full[number_deta_bins] = {0.19767, 0.77301, 0.83696, 0.34641, 0.22760, 0.04542};
						Double_t font_dphi_e_gamma_pos_pt05_Q2full[number_dphi_e_ph_bins] = {0.00414, 0.00537, 0.00827, 0.01431, 0.01107, 0.01389};// DONE

						Double_t font_xgamma_neg_pt05_Q2full[number_xgamma_bins] = {0.12700, 0.30400, 0.54500, 0.88600, 1.85400, 4.93900};
						Double_t font_xp_neg_pt05_Q2full[number_xp_bins] = {38.00000, 76.10000, 44.60000, 15.20000, 2.91300, 0.29000};
						Double_t font_deta_neg_pt05_Q2full[number_deta_bins] = {0.19767, 0.77301, 0.83696, 0.34641, 0.22760, 0.04542};
						Double_t font_dphi_e_gamma_neg_pt05_Q2full[number_dphi_e_ph_bins] = {0.00414, 0.00537, 0.00827, 0.01431, 0.01107, 0.01389};// DONE
					*/

				// //e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
					// 	Double_t font_xgamma_pos_pt05_Q2full[number_xgamma_bins] = {0.12700, 0.30400, 0.54500, 0.88600, 1.85400, 4.93900};
					// 	Double_t font_xp_pos_pt05_Q2full[number_xp_bins] = {38.00000, 76.10000, 44.60000, 15.20000, 2.91300, 0.29000};
					// 	Double_t font_deta_pos_pt05_Q2full[number_deta_bins] = {0.08840, 0.34570, 0.37430, 0.33180, 0.21800, 0.04350};
					// 	Double_t font_dphi_e_gamma_pos_pt05_Q2full[number_dphi_e_ph_bins] = {0.00185, 0.00240, 0.00370, 0.00640, 0.01060, 0.01330};
					// 	Double_t * font_xgamma_neg_pt05_Q2full = font_xgamma_pos_pt05_Q2full;
					// 	Double_t * font_xp_neg_pt05_Q2full = font_xp_pos_pt05_Q2full;
					// 	Double_t * font_deta_neg_pt05_Q2full = font_deta_pos_pt05_Q2full;
					// 	Double_t * font_dphi_e_gamma_neg_pt05_Q2full = font_dphi_e_gamma_pos_pt05_Q2full;


				//e = [0.08, 0.08, 0.08, 0.08, 0.08, 0.08]; print [ format(l[i] * (0.08), '.5f') for i in range(len(l)) ]
					Double_t font_xgamma_pos_pt05_Q2full[number_xgamma_bins] = {0.10160, 0.24320, 0.43600, 0.70880, 1.48320, 3.95120};
					Double_t font_xp_pos_pt05_Q2full[number_xp_bins] = {30.40000, 60.88000, 35.68000, 12.16000, 2.33040, 0.23200};
					Double_t font_deta_pos_pt05_Q2full[number_deta_bins] = {0.07072, 0.27656, 0.29944, 0.26544, 0.17440, 0.03480};
					Double_t font_dphi_e_gamma_pos_pt05_Q2full[number_dphi_e_ph_bins] = {0.00148, 0.00192, 0.00296, 0.00512, 0.00848, 0.01064};
						Double_t font_xgamma_neg_pt05_Q2full[number_xgamma_bins];
						Double_t font_xp_neg_pt05_Q2full[number_xp_bins];
						Double_t font_deta_neg_pt05_Q2full[number_dphi_bins];
						Double_t font_dphi_e_gamma_neg_pt05_Q2full[number_deta_bins];
			//pT_cut in center-of-mass frame = 2.5 GeV/c - ADDITIONAL 8% unc added everywhere - for now: only this 10 % included!!!!
				Double_t font_xgamma_pt25_Q2full[number_xgamma_bins] = {1.2178, 2.8124, 4.7374, 7.3692, 14.5175, 45.1021};//l=[1.2178, 2.8124, 4.7374, 7.3692, 14.5175, 45.1021]
				Double_t font_xp_pt25_Q2full[number_xp_bins] = {326.7, 605.4, 344.1, 130.3, 26.76, 2.865};//l=[326.7, 605.4, 344.1, 130.3, 26.76, 2.865]
				Double_t font_dphi_pt25_Q2full[number_dphi_bins] = {0.0181, 0.0546, 0.0720, 0.0829, 0.0951, 0.1006, 0.0778};// Before the July2017 email {0.0118, 0.0455, 0.0639, 0.0711, 0.0849, 0.113, 0.188}; // l = [0.0118, 0.0455, 0.0639, 0.0711, 0.0849, 0.113, 0.188]
				Double_t font_deta_pt25_Q2full[number_deta_bins] = {0.593, 2.121, 3.167, 3.116, 2.095, 0.461};//l=[0.593, 2.121, 3.167, 3.116, 2.095, 0.461]
				Double_t font_dphi_e_gamma_pt25_Q2full[number_dphi_e_ph_bins] = {0.0180, 0.0235, 0.0363, 0.0628, 0.0936, 0.0798};//l=[0.0180, 0.0235, 0.0363, 0.0628, 0.0936, 0.0798]
				Double_t font_deta_e_gamma_pt25_Q2full[number_deta_e_ph_bins] = {1.451, 3.545, 4.476, 3.019, 1.070}; // l = [1.451, 3.545, 4.476, 3.019, 1.070]
				
				//e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
				//e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
				//e = [0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.1044030650891055, 0.1044030650891055, 0.1044030650891055]//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]
				//e = [0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.1044030650891055, 0.1044030650891055]//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]
					/*
						Double_t font_xgamma_pos_pt25_Q2full[number_xgamma_bins] = {0.12178, 0.28124, 0.47374, 0.73692, 1.45175, 4.51021};//e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
						Double_t font_xp_pos_pt25_Q2full[number_xp_bins] = {32.67000, 60.54000, 34.41000, 13.03000, 2.67600, 0.28650};//e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
						Double_t font_deta_pos_pt25_Q2full[number_deta_bins] = {0.13260, 0.47427, 0.70816, 0.32532, 0.21872, 0.04813};//e = [0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.1044030650891055, 0.1044030650891055, 0.1044030650891055]//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]
						Double_t font_dphi_e_gamma_pos_pt25_Q2full[number_dphi_e_ph_bins] = {0.00402, 0.00525, 0.00812, 0.01404, 0.00977, 0.00833};//e = [0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.1044030650891055, 0.1044030650891055]//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]

						Double_t font_xgamma_neg_pt25_Q2full[number_xgamma_bins] = {0.12178, 0.28124, 0.47374, 0.73692, 1.45175, 4.51021};//e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
						Double_t font_xp_neg_pt25_Q2full[number_xp_bins] = {32.67000, 60.54000, 34.41000, 13.03000, 2.67600, 0.28650};//e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
						Double_t font_deta_neg_pt25_Q2full[number_deta_bins] = {0.13260, 0.47427, 0.70816, 0.32532, 0.21872, 0.04813};//e = [0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.1044030650891055, 0.1044030650891055, 0.1044030650891055]//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]
						Double_t font_dphi_e_gamma_neg_pt25_Q2full[number_dphi_e_ph_bins] = {0.00402, 0.00525, 0.00812, 0.01404, 0.00977, 0.00833};//e = [0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.1044030650891055, 0.1044030650891055]//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]
					*/

				// //e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
					// 	Double_t font_xgamma_pos_pt25_Q2full[number_xgamma_bins] = {0.12178, 0.28124, 0.47374, 0.73692, 1.45175, 4.51021};//e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1] 
					// 	Double_t font_xp_pos_pt25_Q2full[number_xp_bins] = {32.67000, 60.54000, 34.41000, 13.03000, 2.67600, 0.28650};//e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1] 
					// 	Double_t font_dphi_pos_pt25_Q2full[number_dphi_bins] ={0.00118, 0.00455, 0.00639, 0.00711, 0.00849, 0.01130, 0.01880};// e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
					// 	Double_t font_deta_pos_pt25_Q2full[number_deta_bins] = {0.05930, 0.21210, 0.31670, 0.31160, 0.20950, 0.04610};
					// 	Double_t font_dphi_e_gamma_pos_pt25_Q2full[number_dphi_e_ph_bins] = {0.00180, 0.00235, 0.00363, 0.00628, 0.00936, 0.00798};
					// 	Double_t font_deta_e_gamma_pos_pt25_Q2full[number_deta_e_ph_bins] = {0.14510, 0.35450, 0.44760, 0.30190, 0.10700};
					// 	Double_t * font_xgamma_neg_pt25_Q2full = font_xgamma_pos_pt25_Q2full;
					// 	Double_t * font_xp_neg_pt25_Q2full = font_xp_pos_pt25_Q2full;
					// 	Double_t * font_deta_neg_pt25_Q2full = font_deta_pos_pt25_Q2full;
					// 	Double_t * font_dphi_e_gamma_neg_pt25_Q2full = font_dphi_e_gamma_pos_pt25_Q2full;
					// 	Double_t * font_dphi_neg_pt25_Q2full = font_dphi_pos_pt25_Q2full;
					// 	Double_t * font_deta_e_gamma_neg_pt25_Q2full = font_deta_e_gamma_pos_pt25_Q2full;

				//e = [0.08, 0.08, 0.08, 0.08, 0.08, 0.08]; print [ format(l[i] * (0.08), '.5f') for i in range(len(l)) ]
					Double_t font_xgamma_pos_pt25_Q2full[number_xgamma_bins] = {0.09742, 0.22499, 0.37899, 0.58954, 1.16140, 3.60817};
					Double_t font_xp_pos_pt25_Q2full[number_xp_bins] = {26.13600, 48.43200, 27.52800, 10.42400, 2.14080, 0.22920};
					Double_t font_dphi_pos_pt25_Q2full[number_dphi_bins] ={0.00094, 0.00364, 0.00511, 0.00569, 0.00679, 0.00904, 0.01504};
					Double_t font_deta_pos_pt25_Q2full[number_deta_bins] = {0.04744, 0.16968, 0.25336, 0.24928, 0.16760, 0.03688};
					Double_t font_dphi_e_gamma_pos_pt25_Q2full[number_dphi_e_ph_bins] = {0.00144, 0.00188, 0.00290, 0.00502, 0.00749, 0.00638};
					Double_t font_deta_e_gamma_pos_pt25_Q2full[number_deta_e_ph_bins] = {0.11608, 0.28360, 0.35808, 0.24152, 0.08560};
						Double_t font_xgamma_neg_pt25_Q2full[number_xgamma_bins];
						Double_t font_xp_neg_pt25_Q2full[number_xp_bins];
						Double_t font_deta_neg_pt25_Q2full[number_dphi_bins];
						Double_t font_dphi_e_gamma_neg_pt25_Q2full[number_deta_bins];
						Double_t font_dphi_neg_pt25_Q2full[number_dphi_e_ph_bins];
						Double_t font_deta_e_gamma_neg_pt25_Q2full[number_deta_e_ph_bins];		
			//Combined - This is what was used before - Old!!!!!!!!!!
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
	
	// 0 < Q2 < 30 range
		//OLD
		/*
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
		*/
		//NEW
			//pT_cut in  in center-of-mass frame = 0.5 GeV/c
				// l1  = [[0.64, 1.85, 2.51, 3.47, 6.33, 20.60], [171.62, 306.68, 157.94, 52.04, 10.13, 0.861], [0.342, 1.070, 1.654, 1.464, 0.897, 0.252], [0.0106, 0.0134, 0.0195, 0.0291, 0.0356, 0.0367]]
				Double_t font_xgamma_pt05_Q2lt30[number_xgamma_bins] = {0.64, 1.85, 2.51, 3.47, 6.33, 20.60}; // l = [0.64, 1.85, 2.51, 3.47, 6.33, 20.60]
				Double_t font_xp_pt05_Q2lt30[number_xp_bins] = {171.62, 306.68, 157.94, 52.04, 10.13, 0.963}; // l = [171.62, 306.68, 157.94, 52.04, 10.13, 0.861]
				Double_t font_deta_pt05_Q2lt30[number_deta_bins] = {0.342, 1.070, 1.654, 1.464, 0.897, 0.252}; // l = [0.342, 1.070, 1.654, 1.464, 0.897, 0.252]
				Double_t font_dphi_e_gamma_pt05_Q2lt30[number_dphi_e_ph_bins] = {0.0106, 0.0134, 0.0195, 0.0291, 0.0356, 0.0367}; // l = [0.0106, 0.0134, 0.0195, 0.0291, 0.0356, 0.0367]

				//e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
				//e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
				//e = [0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.1044030650891055, 0.1044030650891055, 0.1044030650891055]//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]
				//e = [0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.1044030650891055, 0.1044030650891055]//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]
					/*
						Double_t font_xgamma_pos_pt05_Q2lt30[number_xgamma_bins] = {0.06400, 0.18500, 0.25100, 0.34700, 0.63300, 2.06000};  //e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
						Double_t font_xp_pos_pt05_Q2lt30[number_xp_bins] = {17.16200, 30.66800, 15.79400, 5.20400, 1.01300, 0.08610}; //e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
						Double_t font_deta_pos_pt05_Q2lt30[number_deta_bins] = {0.07647, 0.23926, 0.36985, 0.15285, 0.09365, 0.02631}; //e = [0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.1044030650891055, 0.1044030650891055, 0.1044030650891055]//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]
						Double_t font_dphi_e_gamma_pos_pt05_Q2lt30[number_dphi_e_ph_bins] = {0.00237, 0.00300, 0.00436, 0.00651, 0.00372, 0.00383};  //e = [0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.1044030650891055, 0.1044030650891055]//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]

						Double_t font_xgamma_neg_pt05_Q2lt30[number_xgamma_bins]  = {0.06400, 0.18500, 0.25100, 0.34700, 0.63300, 2.06000};  //e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
						Double_t font_xp_neg_pt05_Q2lt30[number_xp_bins]  = {17.16200, 30.66800, 15.79400, 5.20400, 1.01300, 0.08610}; //e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
						Double_t font_deta_neg_pt05_Q2lt30[number_deta_bins]  = {0.07647, 0.23926, 0.36985, 0.15285, 0.09365, 0.02631}; //e = [0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.1044030650891055, 0.1044030650891055, 0.1044030650891055]//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]
						Double_t font_dphi_e_gamma_neg_pt05_Q2lt30[number_dphi_e_ph_bins]  = {0.00237, 0.00300, 0.00436, 0.00651, 0.00372, 0.00383};  //e = [0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.1044030650891055, 0.1044030650891055]//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]
					*/

				// //e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
					// 	Double_t font_xgamma_pos_pt05_Q2lt30[number_xgamma_bins] = {0.06400, 0.18500, 0.25100, 0.34700, 0.63300, 2.06000};  //e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
					// 	Double_t font_xp_pos_pt05_Q2lt30[number_xp_bins] = {17.16200, 30.66800, 15.79400, 5.20400, 1.01300, 0.08610}; //e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
					// 	Double_t font_deta_pos_pt05_Q2lt30[number_deta_bins] = {0.03420, 0.10700, 0.16540, 0.14640, 0.08970, 0.02520};
					// 	Double_t font_dphi_e_gamma_pos_pt05_Q2lt30[number_dphi_e_ph_bins] = {0.00106, 0.00134, 0.00195, 0.00291, 0.00356, 0.00367};

					// 	Double_t * font_xgamma_neg_pt05_Q2lt30 = font_xgamma_pos_pt05_Q2lt30;
					// 	Double_t * font_xp_neg_pt05_Q2lt30 = font_xp_pos_pt05_Q2lt30;
					// 	Double_t * font_deta_neg_pt05_Q2lt30 = font_deta_pos_pt05_Q2lt30;
					// 	Double_t * font_dphi_e_gamma_neg_pt05_Q2lt30 = font_dphi_e_gamma_pos_pt05_Q2lt30;

				//e = [0.08, 0.08, 0.08, 0.08, 0.08, 0.08]; print [ format(l[i] * (0.08), '.5f') for i in range(len(l)) ]
				//dl1 = [[0.08, 0.08, 0.08, 0.08, 0.08, 0.08], [0.08, 0.08, 0.08, 0.08, 0.08, 0.08], [0.08, 0.08, 0.08, 0.08, 0.08, 0.08], [0.08, 0.08, 0.08, 0.08, 0.08, 0.08]]
					Double_t font_xgamma_pos_pt05_Q2lt30[number_xgamma_bins] = {0.05120, 0.14800, 0.20080, 0.27760, 0.50640, 1.64800};
					Double_t font_xp_pos_pt05_Q2lt30[number_xp_bins] = {13.72960, 24.53440, 12.63520, 4.16320, 0.81040, 0.06888};
					Double_t font_deta_pos_pt05_Q2lt30[number_deta_bins] = {0.02736, 0.08560, 0.13232, 0.11712, 0.07176, 0.02016};
					Double_t font_dphi_e_gamma_pos_pt05_Q2lt30[number_dphi_e_ph_bins] = {0.00085, 0.00107, 0.00156, 0.00233, 0.00285, 0.00294};
						Double_t font_xgamma_neg_pt05_Q2lt30[number_xgamma_bins];
						Double_t font_xp_neg_pt05_Q2lt30[number_xp_bins];
						Double_t font_deta_neg_pt05_Q2lt30[number_dphi_bins];
						Double_t font_dphi_e_gamma_neg_pt05_Q2lt30[number_deta_bins];
			//pT_cut in center-of-mass frame = 2.5 GeV/c
				// l2 =[[0.613, 1.80, 2.43, 3.26, 5.68, 18.78], [158.89, 281.51, 146.03, 49.92, 9.6153, 0.899], [0.296, 0.921, 1.419, 1.396, 0.871, 0.259], [0.0105, 0.0132, 0.0190, 0.0286, 0.0327, 0.0302]]
				Double_t font_xgamma_pt25_Q2lt30[number_xgamma_bins] = {0.613, 1.80, 2.43, 3.26, 5.68, 18.78}; // l = [0.613, 1.80, 2.43, 3.26, 5.68, 18.78]
				Double_t font_xp_pt25_Q2lt30[number_xp_bins] = {158.89, 281.51, 146.03, 49.92, 9.6153, 0.899}; // l = [158.89, 281.51, 146.03, 49.92, 9.6153, 0.899]
				Double_t font_dphi_pt25_Q2lt30[number_dphi_bins] = {0.00265, 0.0208, 0.0389, 0.0476, 0.0572, 0.0659, 0.0515}; // l = [0.00265, 0.0208, 0.0389, 0.0476, 0.0572, 0.0659, 0.0515]
				Double_t font_deta_pt25_Q2lt30[number_deta_bins] = {0.296, 0.921, 1.419, 1.396, 0.871, 0.259}; // l = [0.296, 0.921, 1.419, 1.396, 0.871, 0.259]
				Double_t font_dphi_e_gamma_pt25_Q2lt30[number_dphi_e_ph_bins] = {0.0105, 0.0132, 0.0190, 0.0286, 0.0327, 0.0302}; // l = [0.0105, 0.0132, 0.0190, 0.0286, 0.0327, 0.0302]
				Double_t font_deta_e_gamma_pt25_Q2lt30[number_deta_e_ph_bins] = {1.408, 2.236, 1.875, 0.512, 0.017}; // l = [1.408, 2.236, 1.875, 0.512, 0.017]
				
				//e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
				//e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
				//e = [0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.1044030650891055, 0.1044030650891055, 0.1044030650891055]//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]
				//e = [0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.22360679774997899, 0.1044030650891055, 0.1044030650891055]//e = [0.2, 0.2, 0.2, 0.03, 0.03, 0.03]
					/*
						Double_t font_xgamma_pos_pt25_Q2lt30[number_xgamma_bins] = {0.06130, 0.18000, 0.24300, 0.32600, 0.56800, 1.87800};
						Double_t font_xp_pos_pt25_Q2lt30[number_xp_bins] = {15.88900, 28.15100, 14.60300, 4.99200, 0.96153, 0.08990};
						Double_t font_deta_pos_pt25_Q2lt30[number_deta_bins] = {0.06619, 0.20594, 0.31730, 0.14575, 0.09094, 0.02704};
						Double_t font_dphi_e_gamma_pos_pt25_Q2lt30[number_dphi_e_ph_bins] = {0.00235, 0.00295, 0.00425, 0.00640, 0.00341, 0.00315};

						Double_t font_xgamma_neg_pt25_Q2lt30[number_xgamma_bins] = {0.06130, 0.18000, 0.24300, 0.32600, 0.56800, 1.87800};
						Double_t font_xp_neg_pt25_Q2lt30[number_xp_bins] = {15.88900, 28.15100, 14.60300, 4.99200, 0.96153, 0.08990};
						Double_t font_deta_neg_pt25_Q2lt30[number_deta_bins] = {0.06619, 0.20594, 0.31730, 0.14575, 0.09094, 0.02704};
						Double_t font_dphi_e_gamma_neg_pt25_Q2lt30[number_dphi_e_ph_bins] = {0.00235, 0.00295, 0.00425, 0.00640, 0.00341, 0.00315};
					*/

				//e = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
					// Double_t font_xgamma_pos_pt25_Q2lt30[number_xgamma_bins] = {0.06130, 0.18000, 0.24300, 0.32600, 0.56800, 1.87800};
					// Double_t font_xp_pos_pt25_Q2lt30[number_xp_bins] = {15.88900, 28.15100, 14.60300, 4.99200, 0.96153, 0.08990};
					// Double_t font_deta_pos_pt25_Q2lt30[number_deta_bins] = {0.02960, 0.09210, 0.14190, 0.13960, 0.08710, 0.02590};
					// Double_t font_dphi_e_gamma_pos_pt25_Q2lt30[number_dphi_e_ph_bins] = {0.00105, 0.00132, 0.00190, 0.00286, 0.00327, 0.00302};

					// Double_t * font_xgamma_neg_pt25_Q2lt30 = font_xgamma_pos_pt25_Q2lt30;
					// Double_t * font_xp_neg_pt25_Q2lt30 = font_xp_pos_pt25_Q2lt30;
					// Double_t * font_deta_neg_pt25_Q2lt30 = font_deta_pos_pt25_Q2lt30;
					// Double_t * font_dphi_e_gamma_neg_pt25_Q2lt30 = font_dphi_e_gamma_pos_pt25_Q2lt30;

				//e = [0.08, 0.08, 0.08, 0.08, 0.08, 0.08]; print [ format(l[i] * (0.08), '.5f') for i in range(len(l)) ]
				//dl2 = [[0.08, 0.08, 0.08, 0.08, 0.08, 0.08], [0.08, 0.08, 0.08, 0.08, 0.08, 0.08], [0.08, 0.08, 0.08, 0.08, 0.08, 0.08], [0.08, 0.08, 0.08, 0.08, 0.08, 0.08]]
					Double_t font_xgamma_pos_pt25_Q2lt30[number_xgamma_bins] = {0.04904, 0.14400, 0.19440, 0.26080, 0.45440, 1.50240};
					Double_t font_xp_pos_pt25_Q2lt30[number_xp_bins] = {12.71120, 22.52080, 11.68240, 3.99360, 0.76922, 0.07192};
					Double_t font_dphi_pos_pt25_Q2lt30[number_dphi_bins] = {0.00021, 0.00166, 0.00311, 0.00381, 0.00458, 0.00527, 0.00412};
					Double_t font_deta_pos_pt25_Q2lt30[number_deta_bins] = {0.02368, 0.07368, 0.11352, 0.11168, 0.06968, 0.02072};
					Double_t font_dphi_e_gamma_pos_pt25_Q2lt30[number_dphi_e_ph_bins] = {0.00084, 0.00106, 0.00152, 0.00229, 0.00262, 0.00242};
					Double_t font_deta_pos_e_gamma_pt25_Q2lt30[number_deta_e_ph_bins] = {0.11264, 0.17888, 0.15000, 0.04096, 0.00136};
						Double_t font_xgamma_neg_pt25_Q2lt30[number_xgamma_bins];
						Double_t font_xp_neg_pt25_Q2lt30[number_xp_bins];
						Double_t font_dphi_neg_pt25_Q2lt30[number_dphi_bins];
						Double_t font_deta_neg_pt25_Q2lt30[number_dphi_bins];
						Double_t font_dphi_e_gamma_neg_pt25_Q2lt30[number_deta_bins];	
						Double_t font_deta_neg_e_gamma_pt25_Q2lt30[number_deta_e_ph_bins];
			//Combined - For Fig.7 
				// for j in range(0,len(l1)):
				//    print [format((l1[j][i]+l2[j][i])/2,'.5f') for i in range(len(l1[j]))]
				//print [format((l1[i]+l2[i])/2,'.5f') for i in range(len(l1))]
				//OlD
					// l12 = [[0.87850, 1.93600, 2.55250, 3.47900, 6.12150, 19.78450],[165.25500, 294.09500, 151.98500, 50.98000, 9.87265, 0.88000],[0.32700, 1.03500, 1.60250, 1.48700, 0.92700, 0.26250],[0.01132, 0.01413, 0.02025, 0.02975, 0.03525, 0.03442]]
					// Double_t font_xgamma_Q2lt30[number_xgamma_bins] = {0.87850, 1.93600, 2.55250, 3.47900, 6.12150, 19.78450};
					// Double_t font_xp_Q2lt30[number_xp_bins] = {165.25500, 294.09500, 151.98500, 50.98000, 9.87265, 0.88000};
					// Double_t font_deta_Q2lt30[number_deta_bins] = {0.32700, 1.03500, 1.60250, 1.48700, 0.92700, 0.26250};
					// Double_t font_dphi_e_gamma_Q2lt30[number_dphi_e_ph_bins] = {0.01132, 0.01413, 0.02025, 0.02975, 0.03525, 0.03442};
				//New
					// l12 = [[0.62650, 1.82500, 2.47000, 3.36500, 6.00500, 19.69000], [165.25500, 294.09500, 151.98500, 50.98000, 9.87265, 0.88000], [0.31900, 0.99550, 1.53650, 1.43000, 0.88400, 0.25550], [0.01055, 0.01330, 0.01925, 0.02885, 0.03415, 0.03345]]
					Double_t font_xgamma_Q2lt30[number_xgamma_bins] = {0.62650, 1.82500, 2.47000, 3.36500, 6.00500, 19.69000};
					Double_t font_xp_Q2lt30[number_xp_bins] = {165.25500, 294.09500, 151.98500, 50.98000, 9.87265, 0.88000};
					Double_t font_deta_Q2lt30[number_deta_bins] = {0.31900, 0.99550, 1.53650, 1.43000, 0.88400, 0.25550};
					Double_t font_dphi_e_gamma_Q2lt30[number_dphi_e_ph_bins] = {0.01055, 0.01330, 0.01925, 0.02885, 0.03415, 0.03345};


				//Errors - absolute offset from the center
					// for j in range(0,len(l1)):
					//    print [format( (l1[j][i]*(1 + dl1[j][i]) - l12[j][i])  ,'.5f') for i in range(len(l1[j]))]
					// print [format( (l1[i]*(1 + dl1[i]) - l12[i])  ,'.5f') for i in range(len(l1))]
					//OLD
						// Double_t font_xgamma_pos_Q2lt30[number_xgamma_bins] = {0.01750, 0.02200, 0.04550, 0.10300, 0.29550, 0.88350};// RECALCULATE WHEN FONT PROVIDES ERRORS
						// Double_t font_xp_pos_Q2lt30[number_xp_bins] = {23.52700, 43.25300, 21.74900, 6.26400, 1.27035, 0.06710};
						// Double_t font_deta_pos_Q2lt30[number_deta_bins] = {0.05663, 0.31132, 0.70580, 0.08813, 0.03845, 0.00461};
						// Double_t font_dphi_e_gamma_pos_Q2lt30[number_dphi_e_ph_bins] = {0.00011, 0.00013, 0.00035, 0.00037, 0.00145, 0.00321};
					//NEW
						Double_t font_xgamma_pos_Q2lt30[number_xgamma_bins] = {0.06470, 0.17300, 0.24080, 0.38260, 0.83140, 2.55800};
						Double_t font_xp_pos_Q2lt30[number_xp_bins] = {20.09460, 37.11940, 18.59020, 5.22320, 1.06775, 0.04988};
						Double_t font_deta_pos_Q2lt30[number_deta_bins] = {0.05036, 0.16010, 0.24982, 0.15112, 0.08476, 0.01666};
						Double_t font_dphi_e_gamma_pos_Q2lt30[number_dphi_e_ph_bins] = {0.00090, 0.00117, 0.00181, 0.00258, 0.00430, 0.00619};

					// for j in range(0,len(l1)):
					//    print [format( (l12[j][i] - l2[j][i]*(1 - dl2[j][i]))   ,'.5f') for i in range(len(l1[j]))]
					//print [format( (l12[i] - l2[i]*(1 - dl2[i]))   ,'.5f') for i in range(len(l1))]
					//OLD
						// Double_t font_xgamma_neg_Q2lt30[number_xgamma_bins] = {0.01750, 0.02200, 0.04550, 0.10300, 0.29550, 0.88350};// RECALCULATE WHEN FONT PROVIDES ERRORS
						// Double_t font_xp_neg_Q2lt30[number_xp_bins] = {22.25400, 40.73600, 20.55800, 6.05200, 1.21888, 0.07090};
						// Double_t font_deta_neg_Q2lt30[number_deta_bins] = {0.04852, 0.25502, 0.55773, 0.08456, 0.03712, 0.00453};
						// Double_t font_dphi_e_gamma_neg_Q2lt30[number_dphi_e_ph_bins] = {0.00010, 0.00012, 0.00035, 0.00036, 0.00144, 0.00319};
					//New
						Double_t font_xgamma_neg_Q2lt30[number_xgamma_bins] = {0.06254, 0.16900, 0.23440, 0.36580, 0.77940, 2.41240};
						Double_t font_xp_neg_Q2lt30[number_xp_bins] = {19.07620, 35.10580, 17.63740, 5.05360, 1.02657, 0.05292};
						Double_t font_deta_neg_Q2lt30[number_deta_bins] = {0.04668, 0.14818, 0.23102, 0.14568, 0.08268, 0.01722};
						Double_t font_dphi_e_gamma_neg_Q2lt30[number_dphi_e_ph_bins] = {0.00089, 0.00116, 0.00177, 0.00254, 0.00407, 0.00567};

	// 30 < Q2 < 350 range - EMPTY and is filled later
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
				Double_t font_dphi_pt25_Q2gt30[number_dphi_bins] = {0, 0, 0, 0, 0, 0, 0};
				Double_t font_deta_pt25_Q2gt30[number_deta_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_dphi_e_gamma_pt25_Q2gt30[number_dphi_e_ph_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_deta_e_gamma_pt25_Q2gt30[number_deta_e_ph_bins] = {0, 0, 0, 0, 0};

				Double_t font_xgamma_pos_pt25_Q2gt30[number_xgamma_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_xp_pos_pt25_Q2gt30[number_xp_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_dphi_pos_pt25_Q2gt30[number_dphi_bins] = {0, 0, 0, 0, 0, 0, 0};
				Double_t font_deta_pos_pt25_Q2gt30[number_deta_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_dphi_e_gamma_pos_pt25_Q2gt30[number_dphi_e_ph_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_deta_pos_e_gamma_pt25_Q2gt30[number_deta_e_ph_bins] = {0, 0, 0, 0, 0};

				Double_t font_xgamma_neg_pt25_Q2gt30[number_xgamma_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_xp_neg_pt25_Q2gt30[number_xp_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_dphi_neg_pt25_Q2gt30[number_dphi_bins] = {0, 0, 0, 0, 0, 0, 0};
				Double_t font_deta_neg_pt25_Q2gt30[number_deta_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_dphi_e_gamma_neg_pt25_Q2gt30[number_dphi_e_ph_bins] = {0, 0, 0, 0, 0, 0};
				Double_t font_deta_neg_e_gamma_pt25_Q2gt30[number_deta_e_ph_bins] = {0, 0, 0, 0, 0};
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
		Double_t * all_theory_cs_font_pt25_Q2gt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pt25_Q2gt30, font_xp_pt25_Q2gt30, font_dphi_pt25_Q2gt30, font_deta_pt25_Q2gt30, font_dphi_e_gamma_pt25_Q2gt30, font_deta_e_gamma_pt25_Q2gt30};
		Double_t * all_theory_cs_font_pt25_pos_Q2gt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pos_pt25_Q2gt30, font_xp_pos_pt25_Q2gt30, font_dphi_pos_pt25_Q2gt30, font_deta_pos_pt25_Q2gt30, font_dphi_e_gamma_pos_pt25_Q2gt30, font_deta_pos_e_gamma_pt25_Q2gt30};
		Double_t * all_theory_cs_font_pt25_neg_Q2gt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_neg_pt25_Q2gt30, font_xp_neg_pt25_Q2gt30, font_dphi_neg_pt25_Q2gt30, font_deta_neg_pt25_Q2gt30, font_dphi_e_gamma_neg_pt25_Q2gt30, font_deta_neg_e_gamma_pt25_Q2gt30};
		//pT_cut in center-of-mass frame = 0.5 GeV/c
		Double_t * all_theory_cs_font_pt05_Q2gt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pt05_Q2gt30, font_xp_pt05_Q2gt30, 0, font_deta_pt05_Q2gt30, font_dphi_e_gamma_pt05_Q2gt30, 0};
		Double_t * all_theory_cs_font_pt05_pos_Q2gt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pos_pt05_Q2gt30, font_xp_pos_pt05_Q2gt30, 0, font_deta_pos_pt05_Q2gt30, font_dphi_e_gamma_pos_pt05_Q2gt30, 0};
		Double_t * all_theory_cs_font_pt05_neg_Q2gt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_neg_pt05_Q2gt30, font_xp_neg_pt05_Q2gt30, 0, font_deta_neg_pt05_Q2gt30, font_dphi_e_gamma_neg_pt05_Q2gt30, 0};
		//Combined for pt 2.5 and 0.5 region
		Double_t * all_theory_cs_font_Q2gt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_Q2gt30, font_xp_Q2gt30, 0, font_deta_Q2gt30, font_dphi_e_gamma_Q2gt30, 0};
		Double_t * all_theory_cs_font_pos_Q2gt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pos_Q2gt30, font_xp_pos_Q2gt30, 0, font_deta_pos_Q2gt30, font_dphi_e_gamma_pos_Q2gt30, 0};
		Double_t * all_theory_cs_font_neg_Q2gt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_neg_Q2gt30, font_xp_neg_Q2gt30, 0, font_deta_neg_Q2gt30, font_dphi_e_gamma_neg_Q2gt30, 0};
		// see the hist_crosses_draw where I fill it in
	// Q2lt30
		//pT_cut in center-of-mass frame = 2.5 GeV/c
		Double_t * all_theory_cs_font_pt25_Q2lt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pt25_Q2lt30, font_xp_pt25_Q2lt30, font_dphi_pt25_Q2lt30, font_deta_pt25_Q2lt30, font_dphi_e_gamma_pt25_Q2lt30, font_deta_e_gamma_pt25_Q2lt30};
		Double_t * all_theory_cs_font_pt25_pos_Q2lt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pos_pt25_Q2lt30, font_xp_pos_pt25_Q2lt30, font_dphi_pos_pt25_Q2lt30, font_deta_pos_pt25_Q2lt30, font_dphi_e_gamma_pos_pt25_Q2lt30, font_deta_pos_e_gamma_pt25_Q2lt30};
		Double_t * all_theory_cs_font_pt25_neg_Q2lt30[12] = {0, 0, 0, 0, 0, 0, font_xgamma_neg_pt25_Q2lt30, font_xp_neg_pt25_Q2lt30, font_dphi_neg_pt25_Q2lt30, font_deta_neg_pt25_Q2lt30, font_dphi_e_gamma_neg_pt25_Q2lt30, font_deta_neg_e_gamma_pt25_Q2lt30};
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
		Double_t * all_theory_cs_font_pt25[12] 	   = {0, 0, 0, 0, 0, 0, font_xgamma_pt25_Q2full, font_xp_pt25_Q2full, font_dphi_pt25_Q2full, font_deta_pt25_Q2full, font_dphi_e_gamma_pt25_Q2full, font_deta_e_gamma_pt25_Q2full};
		Double_t * all_theory_cs_font_pt25_pos[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pos_pt25_Q2full, font_xp_pos_pt25_Q2full, font_dphi_pos_pt25_Q2full, font_deta_pos_pt25_Q2full, font_dphi_e_gamma_pos_pt25_Q2full, font_deta_e_gamma_pos_pt25_Q2full};
		Double_t * all_theory_cs_font_pt25_neg[12] = {0, 0, 0, 0, 0, 0, font_xgamma_neg_pt25_Q2full, font_xp_neg_pt25_Q2full, font_dphi_neg_pt25_Q2full, font_deta_neg_pt25_Q2full, font_dphi_e_gamma_neg_pt25_Q2full, font_deta_e_gamma_neg_pt25_Q2full};
		//pT_cut in center-of-mass frame = 0.5 GeV/c
		Double_t * all_theory_cs_font_pt05[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pt05_Q2full, font_xp_pt05_Q2full, 0, font_deta_pt05_Q2full, font_dphi_e_gamma_pt05_Q2full, 0};
		Double_t * all_theory_cs_font_pt05_pos[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pos_pt05_Q2full, font_xp_pos_pt05_Q2full, 0, font_deta_pos_pt05_Q2full, font_dphi_e_gamma_pos_pt05_Q2full, 0};
		Double_t * all_theory_cs_font_pt05_neg[12] = {0, 0, 0, 0, 0, 0, font_xgamma_neg_pt05_Q2full, font_xp_neg_pt05_Q2full, 0, font_deta_neg_pt05_Q2full, font_dphi_e_gamma_neg_pt05_Q2full, 0};
		//Combined for pt 2.5 and 0.5 region
		Double_t * all_theory_cs_font[12] = {0, 0, 0, 0, 0, 0, font_xgamma, font_xp, 0, font_deta, font_dphi_e_gamma, 0};
		Double_t * all_theory_cs_font_pos[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pos, font_xp_pos, 0, font_deta_pos, font_dphi_e_gamma_pos, 0};
		Double_t * all_theory_cs_font_neg[12] = {0, 0, 0, 0, 0, 0, font_xgamma_neg, font_xp_neg, 0, font_deta_neg, font_dphi_e_gamma_neg, 0};


// Hadronisation correction
	// full Q2
		/* No xgamma correction
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
		*/

		//xgamma reweighted to AFG predictions
			Double_t  hadcor_et[number_etbins] = {0.782285, 0.830105, 0.876333, 0.913968 }; 
			Double_t  hadcor_et_err[number_etbins] = {0.00182122, 0.00235935, 0.00310353, 0.00188195 }; 
			Double_t  hadcor_eta[number_etabins] = {0.896763, 0.838314, 0.814762, 0.766552 }; 
			Double_t  hadcor_eta_err[number_etabins] = {0.00593943, 0.00534207, 0.00527444, 0.00524079 }; 
			Double_t  hadcor_Q2[number_Q2bins] = {0.85212, 0.818244, 0.804978, 0.796162, 0.834903 }; 
			Double_t  hadcor_Q2_err[number_Q2bins] = {0.00103527, 0.000759896, 0.000564962, 0.000505501, 0.000433222 }; 
			Double_t  hadcor_x[number_xbins] = {0.865702, 0.80817, 0.774931, 0.881496 }; 
			Double_t  hadcor_x_err[number_xbins] = {0.0949938, 0.0619448, 0.0439372, 0.116027 }; 
			Double_t  hadcor_et_jet[number_et_jetbins] = {0.685204, 0.768953, 0.85739, 0.985656, 1.15869, 1.23249 }; 
			Double_t  hadcor_et_jet_err[number_et_jetbins] = {0.00377697, 0.00336545, 0.00484118, 0.00732696, 0.00468168, 0.00557255 }; 
			Double_t  hadcor_eta_jet[number_eta_jetbins] = {0.794268, 0.740215, 0.847225, 0.944778 }; 
			Double_t  hadcor_eta_jet_err[number_eta_jetbins] = {0.00591706, 0.00447077, 0.00557416, 0.00695629 }; 
			Double_t  hadcor_xgamma[number_xgamma_bins] = {0.490983, 0.717931, 0.731104, 0.990843, 1.20053, 0.729601 }; 
			Double_t  hadcor_xgamma_err[number_xgamma_bins] = {0.0109449, 0.0192922, 0.0349982, 0.037574, 0.0370611, 0.00976538 }; 
			Double_t  hadcor_xp[number_xp_bins] = {0.719313, 0.791258, 0.868899, 0.955265, 1.04786, 0.968409 }; 
			Double_t  hadcor_xp_err[number_xp_bins] = {0.0646815, 0.0516918, 0.087205, 0.0791642, 0.152979, 0.241388 }; 
			Double_t  hadcor_dphi[number_dphi_bins] = {0.655171, 0.799951, 0.851947, 0.900588, 0.932538, 0.953798, 0.928882 }; 
			Double_t  hadcor_dphi_err[number_dphi_bins] = {0.000486266, 0.000668267, 0.00326667, 0.00321581, 0.00321947, 0.00314716, 0.00265549 }; 
			Double_t  hadcor_deta[number_deta_bins] = {0.851765, 0.712391, 0.752777, 0.850402, 0.932922, 0.875954 }; 
			Double_t  hadcor_deta_err[number_deta_bins] = {0.015275, 0.00659912, 0.00526877, 0.00628249, 0.00918253, 0.0157729 }; 
			Double_t  hadcor_dphi_e_gamma[number_dphi_e_ph_bins] = {0.930843, 0.920093, 0.901301, 0.836295, 0.781368, 0.719477 }; 
			Double_t  hadcor_dphi_e_gamma_err[number_dphi_e_ph_bins] = {0.000638215, 0.000736594, 0.000691982, 0.000710571, 0.000857671, 0.000823337 }; 
			Double_t  hadcor_deta_e_gamma[number_deta_e_ph_bins] = {0.783578, 0.79837, 0.817683, 0.843716, 0.879996 }; 
			Double_t  hadcor_deta_e_gamma_err[number_deta_e_ph_bins] = {0.00711316, 0.00449311, 0.00388066, 0.00464087, 0.00782341 };
		// BLZ rew.
				Double_t hadcor_et_BLZ_rew[number_etbins] = {0.811705, 0.853263, 0.894891, 0.921827 }; 
				Double_t hadcor_et_err_BLZ_rew[number_etbins] = {0.00184393, 0.00239845, 0.00307917, 0.00176398 }; 
				Double_t hadcor_eta_BLZ_rew[number_etabins] = {0.89919, 0.866039, 0.840612, 0.797391 }; 
				Double_t hadcor_eta_err_BLZ_rew[number_etabins] = {0.0055982, 0.0052957, 0.00533548, 0.00546816 }; 
				Double_t hadcor_Q2_BLZ_rew[number_Q2bins] = {0.873922, 0.856346, 0.837811, 0.815785, 0.836612 }; 
				Double_t hadcor_Q2_err_BLZ_rew[number_Q2bins] = {0.00108796, 0.000801649, 0.00058185, 0.000484061, 0.000364633 }; 
				Double_t hadcor_x_BLZ_rew[number_xbins] = {0.917323, 0.843035, 0.78755, 0.844528 }; 
				Double_t hadcor_x_err_BLZ_rew[number_xbins] = {0.114639, 0.0640007, 0.0373938, 0.0801969 }; 
				Double_t hadcor_et_jet_BLZ_rew[number_et_jetbins] = {0.782897, 0.774246, 0.842899, 0.915295, 1.05146, 1.05532 }; 
				Double_t hadcor_et_jet_err_BLZ_rew[number_et_jetbins] = {0.00479696, 0.0034833, 0.00446966, 0.00592, 0.00339901, 0.0034833 }; 
				Double_t hadcor_eta_jet_BLZ_rew[number_eta_jetbins] = {0.696294, 0.743043, 0.890622, 1.12674 }; 
				Double_t hadcor_eta_jet_err_BLZ_rew[number_eta_jetbins] = {0.00604562, 0.00432852, 0.00532267, 0.00774744 }; 
				Double_t hadcor_xgamma_BLZ_rew[number_xgamma_bins] = {0.957092, 1.34979, 2.46903, 6.99034, 29.5416, 0.609606 }; 
				Double_t hadcor_xgamma_err_BLZ_rew[number_xgamma_bins] = {0.199868, 0.179351, 0.574937, 1.4192, 6.07255, 0.0057993 }; 
				Double_t hadcor_xp_BLZ_rew[number_xp_bins] = {0.692625, 0.814319, 0.928516, 0.993314, 1.05401, 0.995093 }; 
				Double_t hadcor_xp_err_BLZ_rew[number_xp_bins] = {0.0651929, 0.0532752, 0.0894929, 0.0738086, 0.123277, 0.178762 }; 
				Double_t hadcor_dphi_BLZ_rew[number_dphi_bins] = {0.687925, 0.829559, 0.887033, 0.926647, 0.965415, 0.955596, 0.954501 }; 
				Double_t hadcor_dphi_err_BLZ_rew[number_dphi_bins] = {0.000465718, 0.000686034, 0.00336899, 0.00329499, 0.00324582, 0.00314873, 0.0027552 }; 
				Double_t hadcor_deta_BLZ_rew[number_deta_bins] = {0.733339, 0.649603, 0.74041, 0.874131, 1.06781, 1.20872 }; 
				Double_t hadcor_deta_err_BLZ_rew[number_deta_bins] = {0.0182944, 0.00687653, 0.00508487, 0.00573111, 0.0092204, 0.0227038 }; 
				Double_t hadcor_dphi_e_gamma_BLZ_rew[number_dphi_e_ph_bins] = {0.960889, 0.959727, 0.93128, 0.862776, 0.799992, 0.73493 }; 
				Double_t hadcor_dphi_e_gamma_err_BLZ_rew[number_dphi_e_ph_bins] = {0.000649543, 0.000737584, 0.000698219, 0.000706291, 0.00081395, 0.00087395 }; 
				Double_t hadcor_deta_e_gamma_BLZ_rew[number_deta_e_ph_bins] = {0.818371, 0.828194, 0.842706, 0.86111, 0.890993 }; 
				Double_t hadcor_deta_e_gamma_err_BLZ_rew[number_deta_e_ph_bins] = {0.00750308, 0.00462464, 0.00389284, 0.00457508, 0.00725434 };  
	//To disable hadcor correction
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
	// Q2<30
		/* No xgamma correction
			Double_t hadcor_et_q2_lt_30[number_etbins] = {0.814789, 0.881715, 0.942218, 0.981211};
			Double_t hadcor_eta_q2_lt_30[number_etabins] = {0.906642, 0.87793, 0.857126, 0.80847};
			Double_t hadcor_Q2_q2_lt_30[number_Q2bins] = {0.864872, 0.849457, 0, 0, 0};
			Double_t hadcor_x_q2_lt_30[number_xbins] = {0.895876, 0.792864, 0.606061, 0};
			Double_t hadcor_et_jet_q2_lt_30[number_et_jetbins] = {0.776819, 0.82294, 0.916796, 0.966992, 1.04494, 1.10435};
			Double_t hadcor_eta_jet_q2_lt_30[number_eta_jetbins] = {0.680929, 0.786099, 0.913864, 1.10639};
			Double_t hadcor_xgamma_q2_lt_30[number_xgamma_bins] = {0.675347, 1.00113, 1.29781, 2.02066, 2.11408, 0.628354};
			Double_t hadcor_xp_q2_lt_30[number_xp_bins] = {0.710108, 0.840846, 0.980352, 1.02746, 1.07797, 0.953271};
			Double_t hadcor_dphi_q2_lt_30[number_dphi_bins] = {0.675952, 0.781953, 0.787725, 0.854512, 0.914414, 0.92687, 0.930594};
			Double_t hadcor_deta_q2_lt_30[number_deta_bins] = {0.626016, 0.675044, 0.771932, 0.896552, 1.07915, 1.06815};
			Double_t hadcor_dphi_e_gamma_q2_lt_30[number_dphi_e_ph_bins] = {0.948911, 0.936677, 0.907617, 0.847112, 0.780708, 0.798657};
			Double_t hadcor_deta_e_gamma_q2_lt_30[number_deta_e_ph_bins] = {0.80882, 0.851826, 0.892594, 0.921073, 1};
				Double_t hadcor_et_err_q2_lt_30[number_etbins] = {0.00279824, 0.0036523, 0.00443284, 0.00256727};
				Double_t hadcor_eta_err_q2_lt_30[number_etabins] = {0.00881101, 0.00838129, 0.00829214, 0.0087034};
				Double_t hadcor_Q2_err_q2_lt_30[number_Q2bins] = {0.00106809, 0.00102338, 0, 0, 0};
				Double_t hadcor_x_err_q2_lt_30[number_xbins] = {0.114363, 0.111417, 0.320606, 0};
				Double_t hadcor_et_jet_err_q2_lt_30[number_et_jetbins] = {0.00662771, 0.00555732, 0.00778652, 0.0111592, 0.00673736, 0.0114272};
				Double_t hadcor_eta_jet_err_q2_lt_30[number_eta_jetbins] = {0.00873094, 0.00720485, 0.00914245, 0.0130542};
				Double_t hadcor_xgamma_err_q2_lt_30[number_xgamma_bins]  = {0.0536555, 0.0844329, 0.194479, 0.217758, 0.123102, 0.0110927};
				Double_t hadcor_xp_err_q2_lt_30[number_xp_bins] = {0.0937616, 0.0856511, 0.159483, 0.140487, 0.251182, 0.514285};
				Double_t hadcor_dphi_err_q2_lt_30[number_dphi_bins] = {0.00249219, 0.0013657, 0.00467537, 0.00435872, 0.004156, 0.00382881, 0.00330441};
				Double_t hadcor_deta_err_q2_lt_30[number_deta_bins] = {0.0227603, 0.0109434, 0.00835811, 0.00981999, 0.0161107, 0.0325483};
				Double_t hadcor_dphi_e_gamma_err_q2_lt_30[number_dphi_e_ph_bins] = {0.000889983, 0.00103713, 0.00105236, 0.00118019, 0.00157391, 0.00145562};
				Double_t hadcor_deta_e_gamma_err_q2_lt_30[number_deta_e_ph_bins] = {0.00745095, 0.0058458, 0.00612644, 0.0114812, 0.26082};
		*/

		//xgamma reweighted to AFG predictions
			Double_t hadcor_et_q2_lt_30[number_etbins] = {0.802755, 0.872851, 0.929315, 0.978185 }; 
			Double_t hadcor_et_err_q2_lt_30[number_etbins] = {0.00274163, 0.00363974, 0.0045831, 0.00288248 }; 
			Double_t hadcor_eta_q2_lt_30[number_etabins] = {0.914631, 0.867824, 0.840576, 0.785591 }; 
			Double_t hadcor_eta_err_q2_lt_30[number_etabins] = {0.00910769, 0.00844727, 0.00820116, 0.00849584 }; 
			Double_t hadcor_Q2_q2_lt_30[number_Q2bins] = {0.856694, 0.829501, 0, 0, 0 }; 
			Double_t hadcor_Q2_err_q2_lt_30[number_Q2bins] = {0.0010728, 0.00101227, 0, 0, 0 }; 
			Double_t hadcor_x_q2_lt_30[number_xbins] = {0.874952, 0.779784, 0.608634, 0 }; 
			Double_t hadcor_x_err_q2_lt_30[number_xbins] = {0.106456, 0.128524, 0.424415, 0 }; 
			Double_t hadcor_et_jet_q2_lt_30[number_et_jetbins] = {0.72708, 0.825856, 0.938911, 1.03758, 1.1318, 1.36585 }; 
			Double_t hadcor_et_jet_err_q2_lt_30[number_et_jetbins] = {0.00573678, 0.00547058, 0.00856711, 0.0138388, 0.00892367, 0.0170041 }; 
			Double_t hadcor_eta_jet_q2_lt_30[number_eta_jetbins] = {0.805908, 0.802336, 0.864832, 0.927297 }; 
			Double_t hadcor_eta_jet_err_q2_lt_30[number_eta_jetbins] = {0.00915216, 0.00760603, 0.00931507, 0.0110523 }; 
			Double_t hadcor_xgamma_q2_lt_30[number_xgamma_bins] = {0.520029, 0.691453, 0.750917, 1.14335, 1.41811, 0.707298 }; 
			Double_t hadcor_xgamma_err_q2_lt_30[number_xgamma_bins] = {0.0166666, 0.0239318, 0.0538246, 0.0683773, 0.0751145, 0.0164357 }; 
			Double_t hadcor_xp_q2_lt_30[number_xp_bins] = {0.76253, 0.827672, 0.905357, 0.971829, 1.05393, 0.872634 }; 
			Double_t hadcor_xp_err_q2_lt_30[number_xp_bins] = {0.0974023, 0.0840167, 0.152661, 0.143232, 0.290103, 0.615625 }; 
			Double_t hadcor_dphi_q2_lt_30[number_dphi_bins] = {0.555373, 0.770886, 0.760789, 0.860684, 0.929228, 0.950307, 0.932088 }; 
			Double_t hadcor_dphi_err_q2_lt_30[number_dphi_bins] = {0.00157335, 0.00129612, 0.00466612, 0.00454765, 0.00439832, 0.00413512, 0.00346247 }; 
			Double_t hadcor_deta_q2_lt_30[number_deta_bins] = {0.77688, 0.766032, 0.798985, 0.876415, 0.911329, 0.853298 }; 
			Double_t hadcor_deta_err_q2_lt_30[number_deta_bins] = {0.0219363, 0.0110189, 0.00891847, 0.0105556, 0.0146107, 0.0232277 }; 
			Double_t hadcor_dphi_e_gamma_q2_lt_30[number_dphi_e_ph_bins] = {0.938281, 0.921114, 0.897424, 0.84324, 0.775962, 0.778518 }; 
			Double_t hadcor_dphi_e_gamma_err_q2_lt_30[number_dphi_e_ph_bins] = {0.000914965, 0.00107661, 0.00108028, 0.00120549, 0.00156955, 0.00133944 }; 
			Double_t hadcor_deta_e_gamma_q2_lt_30[number_deta_e_ph_bins] = {0.789178, 0.836014, 0.885959, 0.91457, 0.956035 }; 
			Double_t hadcor_deta_e_gamma_err_q2_lt_30[number_deta_e_ph_bins] = {0.00756671, 0.0058364, 0.00615942, 0.010661, 0.168206 }; 
	// Q2>30
		
		Double_t hadcor_et_q2_gt_30[number_etbins] = {0.767027, 0.80723, 0.852627, 0.891731 }; 
		Double_t hadcor_et_err_q2_gt_30[number_etbins] = {0.00243393, 0.00306098, 0.00395695, 0.00229697 }; 
		Double_t hadcor_eta_q2_gt_30[number_etabins] = {0.889251, 0.82069, 0.800784, 0.752896 }; 
		Double_t hadcor_eta_err_q2_gt_30[number_etabins] = {0.00782917, 0.00689749, 0.0068379, 0.00661664 }; 
		Double_t hadcor_Q2_q2_gt_30[number_Q2bins] = {0, 0.806914, 0.804469, 0.793676, 0.831452 }; 
		Double_t hadcor_Q2_err_q2_gt_30[number_Q2bins] = {0, 0.00118084, 0.000554522, 0.000495297, 0.000421101 }; 
		Double_t hadcor_x_q2_gt_30[number_xbins] = {0.843608, 0.819389, 0.775454, 0.874698 }; 
		Double_t hadcor_x_err_q2_gt_30[number_xbins] = {0.243476, 0.070294, 0.0427846, 0.111591 }; 
		Double_t hadcor_et_jet_q2_gt_30[number_et_jetbins] = {0.655882, 0.729236, 0.812007, 0.953277, 1.16681, 1.20188 }; 
		Double_t hadcor_et_jet_err_q2_gt_30[number_et_jetbins] = {0.00507677, 0.00426358, 0.0058354, 0.0084962, 0.00539041, 0.00569182 }; 
		Double_t hadcor_eta_jet_q2_gt_30[number_eta_jetbins] = {0.781628, 0.704699, 0.837684, 0.965418 }; 
		Double_t hadcor_eta_jet_err_q2_gt_30[number_eta_jetbins] = {0.00765494, 0.00549146, 0.0069617, 0.00906785 }; 
		Double_t hadcor_xgamma_q2_gt_30[number_xgamma_bins] = {0.467137, 0.806144, 0.722442, 0.892445, 1.07443, 0.741364 }; 
		Double_t hadcor_xgamma_err_q2_gt_30[number_xgamma_bins] = {0.0148872, 0.0351027, 0.0477097, 0.0442089, 0.040553, 0.0120299 }; 
		Double_t hadcor_xp_q2_gt_30[number_xp_bins] = {0.689128, 0.767255, 0.844421, 0.949706, 1.06672, 1.00444 }; 
		Double_t hadcor_xp_err_q2_gt_30[number_xp_bins] = {0.0870556, 0.0653476, 0.10551, 0.0948987, 0.183246, 0.26036 }; 
		Double_t hadcor_dphi_q2_gt_30[number_dphi_bins] = {0.662398, 0.812959, 0.942889, 0.954072, 0.948604, 0.968903, 0.950563 }; 
		Double_t hadcor_dphi_err_q2_gt_30[number_dphi_bins] = {0.000499121, 0.000766573, 0.00460862, 0.00466491, 0.00490652, 0.00510732, 0.00442899 }; 
		Double_t hadcor_deta_q2_gt_30[number_deta_bins] = {0.884292, 0.678453, 0.723844, 0.837352, 0.950802, 0.922782 }; 
		Double_t hadcor_deta_err_q2_gt_30[number_deta_bins] = {0.0204463, 0.00814855, 0.00649404, 0.00783328, 0.0118575, 0.022046 }; 
		Double_t hadcor_dphi_e_gamma_q2_gt_30[number_dphi_e_ph_bins] = {0.924132, 0.918593, 0.906903, 0.835071, 0.783674, 0.688462 }; 
		Double_t hadcor_dphi_e_gamma_err_q2_gt_30[number_dphi_e_ph_bins] = {0.000905738, 0.00102307, 0.000902713, 0.00087619, 0.00101472, 0.00103167 }; 
		Double_t hadcor_deta_e_gamma_q2_gt_30[number_deta_e_ph_bins] = {0.699632, 0.748921, 0.782672, 0.830701, 0.879227 }; 
		Double_t hadcor_deta_e_gamma_err_q2_gt_30[number_deta_e_ph_bins] = {0.0380661, 0.00708311, 0.00487972, 0.00503345, 0.00771938 }; 
	Double_t * all_hadcort[12] = {hadcor_et, hadcor_eta, hadcor_Q2, hadcor_x, hadcor_et_jet, hadcor_eta_jet, hadcor_xgamma, hadcor_xp, hadcor_dphi, hadcor_deta, hadcor_dphi_e_gamma, hadcor_deta_e_gamma};
	Double_t * all_hadcort_err[12] = {hadcor_et_err, hadcor_eta_err, hadcor_Q2_err, hadcor_x_err, hadcor_et_jet_err, hadcor_eta_jet_err, hadcor_xgamma_err, hadcor_xp_err, hadcor_dphi_err, hadcor_deta_err, hadcor_dphi_e_gamma_err, hadcor_deta_e_gamma_err};
	Double_t * all_hadcort_BLZ_rew[12] = {hadcor_et_BLZ_rew, hadcor_eta_BLZ_rew, hadcor_Q2_BLZ_rew, hadcor_x_BLZ_rew, hadcor_et_jet_BLZ_rew, hadcor_eta_jet_BLZ_rew, hadcor_xgamma_BLZ_rew, hadcor_xp_BLZ_rew, hadcor_dphi_BLZ_rew, hadcor_deta_BLZ_rew, hadcor_dphi_e_gamma_BLZ_rew, hadcor_deta_e_gamma_BLZ_rew};
	Double_t * all_hadcort_err_BLZ_rew[12] = {hadcor_et_err_BLZ_rew, hadcor_eta_err_BLZ_rew, hadcor_Q2_err_BLZ_rew, hadcor_x_err_BLZ_rew, hadcor_et_jet_err_BLZ_rew, hadcor_eta_jet_err_BLZ_rew, hadcor_xgamma_err_BLZ_rew, hadcor_xp_err_BLZ_rew, hadcor_dphi_err_BLZ_rew, hadcor_deta_err_BLZ_rew, hadcor_dphi_e_gamma_err_BLZ_rew, hadcor_deta_e_gamma_err_BLZ_rew};
	Double_t * all_hadcort_q2_lt_30[12] = {hadcor_et_q2_lt_30, hadcor_eta_q2_lt_30, hadcor_Q2_q2_lt_30, hadcor_x_q2_lt_30, hadcor_et_jet_q2_lt_30, hadcor_eta_jet_q2_lt_30, hadcor_xgamma_q2_lt_30, hadcor_xp_q2_lt_30, hadcor_dphi_q2_lt_30, hadcor_deta_q2_lt_30, hadcor_dphi_e_gamma_q2_lt_30, hadcor_deta_e_gamma_q2_lt_30};
	Double_t * all_hadcort_err_q2_lt_30[12] = {hadcor_et_err_q2_lt_30, hadcor_eta_err_q2_lt_30, hadcor_Q2_err_q2_lt_30, hadcor_x_err_q2_lt_30, hadcor_et_jet_err_q2_lt_30, hadcor_eta_jet_err_q2_lt_30, hadcor_xgamma_err_q2_lt_30, hadcor_xp_err_q2_lt_30, hadcor_dphi_err_q2_lt_30, hadcor_deta_err_q2_lt_30, hadcor_dphi_e_gamma_err_q2_lt_30, hadcor_deta_e_gamma_err_q2_lt_30};
	Double_t * all_hadcort_q2_gt_30[12] = {hadcor_et_q2_gt_30, hadcor_eta_q2_gt_30, hadcor_Q2_q2_gt_30, hadcor_x_q2_gt_30, hadcor_et_jet_q2_gt_30, hadcor_eta_jet_q2_gt_30, hadcor_xgamma_q2_gt_30, hadcor_xp_q2_gt_30, hadcor_dphi_q2_gt_30, hadcor_deta_q2_gt_30, hadcor_dphi_e_gamma_q2_gt_30, hadcor_deta_e_gamma_q2_gt_30};
	Double_t * all_hadcort_err_q2_gt_30[12] = {hadcor_et_err_q2_gt_30, hadcor_eta_err_q2_gt_30, hadcor_Q2_err_q2_gt_30, hadcor_x_err_q2_gt_30, hadcor_et_jet_err_q2_gt_30, hadcor_eta_jet_err_q2_gt_30, hadcor_xgamma_err_q2_gt_30, hadcor_xp_err_q2_gt_30, hadcor_dphi_err_q2_gt_30, hadcor_deta_err_q2_gt_30, hadcor_dphi_e_gamma_err_q2_gt_30, hadcor_deta_e_gamma_err_q2_gt_30};

Int_t numberAllBins[12] = {number_etbins, number_etabins, number_Q2bins, number_xbins, number_et_jetbins, number_eta_jetbins, number_xgamma_bins, number_xp_bins, number_dphi_bins, number_deta_bins, number_dphi_e_ph_bins, number_deta_e_ph_bins};
string numberAllBins_names[12] = {"number_etbins", "number_etabins", "number_Q2bins", "number_xbins", "number_et_jetbins", "number_eta_jetbins", "number_xgamma_bins", "number_xp_bins", "number_dphi_bins", "number_deta_bins", "number_dphi_e_ph_bins", "number_deta_e_ph_bins"};
string simple_names[12] = {"et", "eta", "Q2", "x", "et_jet", "eta_jet", "xgamma", "xp", "dphi", "deta", "dphi_e_gamma", "deta_e_gamma"};

//For AFG prediction I need to know the LL components on different Q2 ranges - therefore I will store it ere but also check the numbers during runtime
	//Full Q2 LL:
		//values
			Double_t ll_for_CrossectionDrawer_fullQ2_et[number_etbins] = {0.443895, 0.232685, 0.147586, 0.066698}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_eta[number_etabins] = {3.05646, 1.26393, 0.483622, 0.150535}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_Q2[number_Q2bins] = {0.0164184, 0.0136856, 0.0141255, 0.00759072, 0.00223778}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_x[number_xbins] = {433.239, 380.975, 111.076, 9.1287}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_et_jet[number_et_jetbins] = {0.167331, 0.182392, 0.170189, 0.143358, 0.0996073, 0.0119876}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_eta_jet[number_eta_jetbins] = {0.115556, 0.383922, 0.734153, 1.10546}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_xgamma[number_xgamma_bins] = {0.0608075, 0.292987, 0.650206, 1.16983, 3.67424, 13.3175}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_xp[number_xp_bins] = {35.2067, 110.846, 79.9728, 46.6066, 18.7175, 3.26312}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_dphi[number_dphi_bins] = {0.00440007, 0.0116922, 0.0168088, 0.0207089, 0.0214065, 0.0265637, 0.0263247}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_deta[number_deta_bins] = {0, 0.057517, 0.205457, 0.445189, 0.867186, 0.923844}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_dphi_e_gamma[number_dphi_e_ph_bins] = {0.00887713, 0.0104117, 0.00991759, 0.0117813, 0.0149356, 0.0130867}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_deta_e_gamma[number_deta_e_ph_bins] = {0.0161368, 0.0822515, 0.452799, 1.32649, 1.24083}; 
		//errors
			Double_t ll_for_CrossectionDrawer_fullQ2_err_et[number_etbins]= {0.0325426, 0.0226715, 0.0182417, 0.0077551}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_err_eta[number_etabins]= {0.186327, 0.11942, 0.0762862, 0.0429462}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_err_Q2[number_Q2bins]= {0.00285604, 0.00179724, 0.00126781, 0.000688276, 0.00022807}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_err_x[number_xbins]= {51.0052, 30.2091, 8.5214, 1.8366}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_err_et_jet[number_et_jetbins]= {0.0235232, 0.0209336, 0.02076, 0.0188189, 0.00987448, 0.00174953}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_err_eta_jet[number_eta_jetbins]= {0.0257831, 0.0475255, 0.0672583, 0.0710958}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_err_xgamma[number_xgamma_bins]= {0.0231167, 0.0743926, 0.176373, 0.24729, 0.431854, 0.845889}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_err_xp[number_xp_bins]= {5.74872, 10.4284, 9.39924, 4.75493, 2.621, 0.921409}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_err_dphi[number_dphi_bins]= {0.000473172, 0.00118295, 0.00273054, 0.00305023, 0.00328571, 0.00347719, 0.00344003}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_err_deta[number_deta_bins]= {0, 0.0202616, 0.0373065, 0.0559662, 0.0733786, 0.0719886}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_err_dphi_e_gamma[number_dphi_e_ph_bins]= {0.000982481, 0.00120602, 0.00127158, 0.00144991, 0.00191115, 0.00148467}; 
			Double_t ll_for_CrossectionDrawer_fullQ2_err_deta_e_gamma[number_deta_e_ph_bins]= {0.0112354, 0.0268842, 0.0595152, 0.100239, 0.0944947}; 
		Double_t * all_ll_for_CrossectionDrawer_fullQ2[12] = {ll_for_CrossectionDrawer_fullQ2_et, ll_for_CrossectionDrawer_fullQ2_eta, ll_for_CrossectionDrawer_fullQ2_Q2, ll_for_CrossectionDrawer_fullQ2_x, ll_for_CrossectionDrawer_fullQ2_et_jet, ll_for_CrossectionDrawer_fullQ2_eta_jet, ll_for_CrossectionDrawer_fullQ2_xgamma, ll_for_CrossectionDrawer_fullQ2_xp, ll_for_CrossectionDrawer_fullQ2_dphi, ll_for_CrossectionDrawer_fullQ2_deta, ll_for_CrossectionDrawer_fullQ2_dphi_e_gamma, ll_for_CrossectionDrawer_fullQ2_deta_e_gamma};
		Double_t * all_ll_for_CrossectionDrawer_fullQ2_err[12] = {ll_for_CrossectionDrawer_fullQ2_err_et, ll_for_CrossectionDrawer_fullQ2_err_eta, ll_for_CrossectionDrawer_fullQ2_err_Q2, ll_for_CrossectionDrawer_fullQ2_err_x, ll_for_CrossectionDrawer_fullQ2_err_et_jet, ll_for_CrossectionDrawer_fullQ2_err_eta_jet, ll_for_CrossectionDrawer_fullQ2_err_xgamma, ll_for_CrossectionDrawer_fullQ2_err_xp, ll_for_CrossectionDrawer_fullQ2_err_dphi, ll_for_CrossectionDrawer_fullQ2_err_deta, ll_for_CrossectionDrawer_fullQ2_err_dphi_e_gamma, ll_for_CrossectionDrawer_fullQ2_err_deta_e_gamma};
	// Q2<30
		//values
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_et[number_etbins] = {0.0710728, 0.0373514, 0.0222808, 0.00733068}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_eta[number_etabins] = {0.470214, 0.172605, 0.0747445, 0.0275945}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_Q2[number_Q2bins] = {0.015435, 0.00674198, 0, 0, 0}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_x[number_xbins] = {283.224, 32.2567, 0, 0.0069704};// last bin  was inf 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_et_jet[number_et_jetbins] = {0.0251026, 0.0374274, 0.0290021, 0.0291238, 0.0122824, 0.000394537}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_eta_jet[number_eta_jetbins] = {0.0191717, 0.075597, 0.101816, 0.156439}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_xgamma[number_xgamma_bins] = {0.00289495, 0.0627275, 0.225142, 0.151625, 0.557742, 1.88395}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_xp[number_xp_bins] = {7.88449, 18.673, 13.5166, 6.11513, 1.98726, 0.224425}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_dphi[number_dphi_bins] = {9.66554e-05, 0.00073813, 0.0026249, 0.00384165, 0.00493281, 0.0075187, 0.00706585}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_deta[number_deta_bins] = {0, 0.00305871, 0.0433335, 0.071091, 0.149216, 0.122761}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_dphi_e_gamma[number_dphi_e_ph_bins] = {0.00180439, 0.00184643, 0.00155675, 0.00180688, 0.00118677, 0.00146522}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_deta_e_gamma[number_deta_e_ph_bins] = {0.0142069, 0.062398, 0.211347, 0.19148, 0}; 
		//errors
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_err_et[number_etbins]= {0.0128833, 0.00884758, 0.00704684, 0.00272089}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_err_eta[number_etabins]= {0.0725888, 0.0445145, 0.0299507, 0.0170511}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_err_Q2[number_Q2bins]= {0.00270834, 0.00123502, 0, 0, 0}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_err_x[number_xbins]= {40.8289, 8.66137, 0, 0}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_err_et_jet[number_et_jetbins]= {0.00887658, 0.00949396, 0.00806052, 0.00831591, 0.00336269, 0.000536039}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_err_eta_jet[number_eta_jetbins]= {0.00948459, 0.0220338, 0.0247706, 0.0260371}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_err_xgamma[number_xgamma_bins]= {0.0101344, 0.0334819, 0.0947196, 0.0989056, 0.16329, 0.313274}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_err_xp[number_xp_bins]= {2.82483, 4.11839, 3.76001, 1.64634, 0.886559, 0.362323}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_err_dphi[number_dphi_bins]= {8.26094e-05, 0.000312656, 0.00111259, 0.00122394, 0.00160394, 0.00185961, 0.00172581}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_err_deta[number_deta_bins]= {0, 0.00491381, 0.0171558, 0.0228664, 0.0294159, 0.0263918}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_err_dphi_e_gamma[number_dphi_e_ph_bins]= {0.000427006, 0.0004887, 0.00049094, 0.000558293, 0.000682757, 0.000492133}; 
			Double_t ll_for_CrossectionDrawer_fullQ2lt30_err_deta_e_gamma[number_deta_e_ph_bins]= {0.0104812, 0.0218171, 0.0405504, 0.0389986, 0}; 
		Double_t * all_ll_for_CrossectionDrawer_Q2lt30[12] = {ll_for_CrossectionDrawer_fullQ2lt30_et, ll_for_CrossectionDrawer_fullQ2lt30_eta, ll_for_CrossectionDrawer_fullQ2lt30_Q2, ll_for_CrossectionDrawer_fullQ2lt30_x, ll_for_CrossectionDrawer_fullQ2lt30_et_jet, ll_for_CrossectionDrawer_fullQ2lt30_eta_jet, ll_for_CrossectionDrawer_fullQ2lt30_xgamma, ll_for_CrossectionDrawer_fullQ2lt30_xp, ll_for_CrossectionDrawer_fullQ2lt30_dphi, ll_for_CrossectionDrawer_fullQ2lt30_deta, ll_for_CrossectionDrawer_fullQ2lt30_dphi_e_gamma, ll_for_CrossectionDrawer_fullQ2lt30_deta_e_gamma};
		Double_t * all_ll_for_CrossectionDrawer_Q2lt30_err[12] = {ll_for_CrossectionDrawer_fullQ2lt30_err_et, ll_for_CrossectionDrawer_fullQ2lt30_err_eta, ll_for_CrossectionDrawer_fullQ2lt30_err_Q2, ll_for_CrossectionDrawer_fullQ2lt30_err_x, ll_for_CrossectionDrawer_fullQ2lt30_err_et_jet, ll_for_CrossectionDrawer_fullQ2lt30_err_eta_jet, ll_for_CrossectionDrawer_fullQ2lt30_err_xgamma, ll_for_CrossectionDrawer_fullQ2lt30_err_xp, ll_for_CrossectionDrawer_fullQ2lt30_err_dphi, ll_for_CrossectionDrawer_fullQ2lt30_err_deta, ll_for_CrossectionDrawer_fullQ2lt30_err_dphi_e_gamma, ll_for_CrossectionDrawer_fullQ2lt30_err_deta_e_gamma};
	// Q2>30
		//values
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_et[number_etbins] = {0.368298, 0.194175, 0.125305, 0.0581348}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_eta[number_etabins] = {2.55494, 1.08171, 0.408878, 0.120045}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_Q2[number_Q2bins] = {0, 0.00694362, 0.0140872, 0.00746927, 0.0022051}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_x[number_xbins] = {137.723, 346.795, 110.056, 8.97564}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_et_jet[number_et_jetbins] = {0.140436, 0.144386, 0.139537, 0.112704, 0.0866301, 0.0114008}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_eta_jet[number_eta_jetbins] = {0.0963845, 0.303051, 0.621957, 0.943463}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_xgamma[number_xgamma_bins] = {0.0579126, 0.230259, 0.413484, 0.995046, 3.10119, 11.3083}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_xp[number_xp_bins] = {27.0161, 91.2072, 65.5298, 40.0696, 16.5759, 3.03869}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_dphi[number_dphi_bins] = {0.00429055, 0.0108579, 0.013854, 0.0168673, 0.0161676, 0.0186604, 0.0190272}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_deta[number_deta_bins] = {0, 0.0544583, 0.162123, 0.36423, 0.711602, 0.79228}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_dphi_e_gamma[number_dphi_e_ph_bins] = {0.00690179, 0.00856532, 0.00827122, 0.00982756, 0.0136909, 0.0115288}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_deta_e_gamma[number_deta_e_ph_bins] = {0, 0.0198535, 0.228922, 1.13308, 1.21708}; 
		//errors
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_err_et[number_etbins]= {0.0292593, 0.0204938, 0.0164336, 0.00715481}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_err_eta[number_etabins]= {0.168189, 0.108189, 0.0688341, 0.0385989}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_err_Q2[number_Q2bins]= {0, 0.00129826, 0.00126067, 0.000682627, 0.000224772}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_err_x[number_xbins]= {26.7476, 28.1984, 8.70734, 1.83477}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_err_et_jet[number_et_jetbins]= {0.0211371, 0.0180907, 0.018388, 0.0169175, 0.00919705, 0.00159225}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_err_eta_jet[number_eta_jetbins]= {0.0235758, 0.0409122, 0.0608371, 0.0656814}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_err_xgamma[number_xgamma_bins]= {0.0240394, 0.0660719, 0.139462, 0.21659, 0.378909, 0.775507}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_err_xp[number_xp_bins]= {4.80898, 9.35826, 8.47024, 4.41108, 2.3631, 0.807975}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_err_dphi[number_dphi_bins]= {0.000476045, 0.00112409, 0.00234373, 0.00276715, 0.00278395, 0.00260973, 0.00296087}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_err_deta[number_deta_bins]= {0, 0.0189514, 0.0325881, 0.0498575, 0.0659075, 0.0667587}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_err_dphi_e_gamma[number_dphi_e_ph_bins]= {0.000858184, 0.00109928, 0.00114592, 0.00129534, 0.0017895, 0.00137233}; 
			Double_t ll_for_CrossectionDrawer_fullQ2gt30_err_deta_e_gamma[number_deta_e_ph_bins]= {0, 0.0149269, 0.0423717, 0.0914336, 0.092994}; 
		Double_t * all_ll_for_CrossectionDrawer_Q2gt30[12] = {ll_for_CrossectionDrawer_fullQ2gt30_et, ll_for_CrossectionDrawer_fullQ2gt30_eta, ll_for_CrossectionDrawer_fullQ2gt30_Q2, ll_for_CrossectionDrawer_fullQ2gt30_x, ll_for_CrossectionDrawer_fullQ2gt30_et_jet, ll_for_CrossectionDrawer_fullQ2gt30_eta_jet, ll_for_CrossectionDrawer_fullQ2gt30_xgamma, ll_for_CrossectionDrawer_fullQ2gt30_xp, ll_for_CrossectionDrawer_fullQ2gt30_dphi, ll_for_CrossectionDrawer_fullQ2gt30_deta, ll_for_CrossectionDrawer_fullQ2gt30_dphi_e_gamma, ll_for_CrossectionDrawer_fullQ2gt30_deta_e_gamma};
		Double_t * all_ll_for_CrossectionDrawer_Q2gt30_err[12] = {ll_for_CrossectionDrawer_fullQ2gt30_err_et, ll_for_CrossectionDrawer_fullQ2gt30_err_eta, ll_for_CrossectionDrawer_fullQ2gt30_err_Q2, ll_for_CrossectionDrawer_fullQ2gt30_err_x, ll_for_CrossectionDrawer_fullQ2gt30_err_et_jet, ll_for_CrossectionDrawer_fullQ2gt30_err_eta_jet, ll_for_CrossectionDrawer_fullQ2gt30_err_xgamma, ll_for_CrossectionDrawer_fullQ2gt30_err_xp, ll_for_CrossectionDrawer_fullQ2gt30_err_dphi, ll_for_CrossectionDrawer_fullQ2gt30_err_deta, ll_for_CrossectionDrawer_fullQ2gt30_err_dphi_e_gamma, ll_for_CrossectionDrawer_fullQ2gt30_err_deta_e_gamma};
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
