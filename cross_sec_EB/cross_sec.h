#include <iostream>
#include <iomanip>
#include <fstream>
#include <initializer_list>
#include <vector>
#include <limits>
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
							"d#sigma/d#Delta#phi (pb)", "d#sigma/d#Delta#eta (pb)", \
							"d#sigma/d#Delta#phi_{e,#gamma} (pb)", "d#sigma/d#Delta#eta_{e,#gamma} (pb)"};							
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

/*here for sys acc.sys. was not included
 Double_t et_sys[number_etbins] = {0.18456602172393502, 0.07460343742080522, 0.03925699400743772, 0.018984808466244785};
 Double_t eta_bin_crosssys[number_etabins ] = {0.41118579286011336, 0.4800574984832548, 0.42759479554246216, 0.5032745383734409};//?number_etabins + 1
 Double_t Q2_sys[number_Q2bins] = {0.022350406679745208, 0.00849133403830046, 0.005464485152555544, 0.0015176088222924912, 0.00012664832035996388};
 Double_t x_sys[number_xbins] = {358.18128849089794, 120.05990306925949, 17.75976903002965, 1.9981629775871648};
 Double_t et_jet_sys[number_et_jetbins] = {0.10575416197483675, 0.09917295674729076, 0.06735052839993165, 0.048137500851726855, 0.013816947799713195, 0.005973781955344539};
 Double_t eta_jet_sys[number_eta_jetbins] = {0.19263881209403258, 0.2630744863151879, 0.1988375383950424, 0.22731733683333522};
 Double_t xgamma_sys[number_xgamma_bins] = {0.0864280896453809, 0.34881740979343334, 0.5055126963539096, 0.676767822281024, 3.2182005115436794, 6.57912537481237};
 Double_t xp_sys[number_xp_bins] = {27.94329169944013, 52.62978581326362, 36.62227290188309, 14.17469317128241, 2.545125993934288, 1.63156};
 Double_t dphi_sys[number_dphi_bins] = {0.0031466367890972103, 0.004184844291607516, 0.006076230761746953, 0.007159539536520488, 0.003017081868295921, 0.003960653923280855, 0.007087410475625071};
 Double_t deta_sys[number_deta_bins] = {0.0, 0.15505411652065232, 0.2551994703658298, 0.11749219335768647, 0.24348487951000145, 0.10291449278405836};
 Double_t dphi_e_ph_sys[number_dphi_e_ph_bins] = {0.002090808909848051, 0.002802851481081365, 0.002977835379936241, 0.006207801137077444, 0.007782115100183242, 0.007070914151826479};
 Double_t deta_e_ph_sys[number_deta_e_ph_bins] = {0.1582997804799489, 0.2923727336380736, 0.4238569239436818, 0.26605835872980965, 0.09077920604411563};
*/
 /* 070416
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
*/
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
/*
Double_t font_xgamma[number_xgamma_bins] = {1.7294306, 2.832685, 4.934913, 7.821229, 15.333007, 45.400156};
Double_t font_xp[number_xp_bins] = {344.73588, 633.82886, 368.86532, 135.94088, 27.95856, 3.03148333};
Double_t font_deta[number_deta_bins] = {0.63377, 2.25852, 3.34801, 3.24973, 2.16528, 0.46162};
Double_t font_dphi_e_gamma[number_dphi_e_ph_bins] = {0.019395463, 0.025020163, 0.037863148, 0.064914172, 0.098684485, 0.085195744};

Double_t font_xgamma_pos[number_xgamma_bins] = {0, 0, 0, 0, 0, 0};
Double_t font_xp_pos[number_xp_bins] = {0, 0, 0, 0, 0, 0};
Double_t font_deta_pos[number_deta_bins] = {0, 0, 0, 0, 0, 0};
Double_t font_dphi_e_gamma_pos[number_dphi_e_ph_bins] = {0, 0, 0, 0, 0, 0};

Double_t font_xgamma_neg[number_xgamma_bins] = {0, 0, 0, 0, 0, 0};
Double_t font_xp_neg[number_xp_bins] = {0, 0, 0, 0, 0, 0};
Double_t font_deta_neg[number_deta_bins] = {0, 0, 0, 0, 0, 0};
Double_t font_dphi_e_gamma_neg[number_dphi_e_ph_bins] = {0, 0, 0, 0, 0, 0};
*/
//For the meanwhile mean variables are just center between predictions of pt 2.5 and pt 0.5 so the errors would be semmetric - boundaries
Double_t font_xgamma[number_xgamma_bins] = {1.77864105, 2.9388162475, 5.29177594, 8.597595365, 17.44771155, 48.0353915};
Double_t font_xp[number_xp_bins] = {372.92281, 699.69313, 417.862304, 146.5044075, 29.5121153335, 3.060679665};
Double_t font_deta[number_deta_bins] = {0.8041835715, 2.9169913569999997, 3.6937328569999996, 3.336542057, 2.2211529715, 0.4495153855};
Double_t font_dphi_e_gamma[number_dphi_e_ph_bins] = {0.019395463, 0.025020163, 0.037863148, 0.064914172, 0.098684485, 0.085195744};

Double_t font_xgamma_pos[number_xgamma_bins] = {0.049210449999999906, 0.10613124750000003, 0.3568629400000001, 0.7763663649999994, 2.114704549999999, 2.6352355000000003};
Double_t font_xp_pos[number_xp_bins] = {28.18692999999996, 65.86427000000003, 48.996984, 10.563527499999992, 1.5535553335000003, 0.029196334999999962};
Double_t font_deta_pos[number_deta_bins] = {0.17041357150000003, 0.6584713570000003, 0.34572285700000016, 0.08681205699999994, 0.055872971499999924, -0.0121046145};
Double_t font_dphi_e_gamma_pos[number_dphi_e_ph_bins] = {0, 0, 0, 0, 0, 0};

Double_t font_xgamma_neg[number_xgamma_bins] = {0.04921045000000013, 0.10613124750000003, 0.3568629400000001, 0.7763663650000003, 2.114704550000001, 2.6352355000000003};
Double_t font_xp_neg[number_xp_bins] = {28.186930000000018, 65.86427000000003, 48.996984, 10.56352750000002, 1.5535553335000003, 0.029196334999999962};
Double_t font_deta_neg[number_deta_bins] = {0.17041357150000003, 0.6584713569999998, 0.3457228569999997, 0.08681205699999994, 0.055872971499999924, -0.0121046145};
Double_t font_dphi_e_gamma_neg[number_dphi_e_ph_bins] = {0, 0, 0, 0, 0, 0};

Double_t * all_theory_cs_font[12] = {0, 0, 0, 0, 0, 0, font_xgamma, font_xp, 0, font_deta, font_dphi_e_gamma, 0};
Double_t * all_theory_cs_font_pos[12] = {0, 0, 0, 0, 0, 0, font_xgamma_pos, font_xp_pos, 0, font_deta_pos, font_dphi_e_gamma_pos, 0};
Double_t * all_theory_cs_font_neg[12] = {0, 0, 0, 0, 0, 0, font_xgamma_neg, font_xp_neg, 0, font_deta_neg, font_dphi_e_gamma_neg, 0};
 
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
