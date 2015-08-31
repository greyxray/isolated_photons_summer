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
#include <TObjArray.h>
#include <TFractionFitter.h>
#include "plot_style_utils.h"
#include "../inc/constants.h"
//#include "plot_style_utils.h"
TString fit_method = "deltaz";//fmax, deltaz
Bool_t g_include_04p_data = kFALSE;
Int_t g_index_fmax = 0;
//Int_t g_index_fmax = 16;
//Int_t g_index_deltaz = 1;
Int_t g_index_deltaz= 1;

const Int_t n_hist = 2;
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

TH1D *hist_mc_sum_2param[n_hist];
TH1D *hist_mc_norad_sum_2param[n_hist];
TH1D *hist_mc_rad_sum_2param[n_hist];
TH1D *hist_data_sum_2param[n_hist];
TH1D *hist_mc_photon_sum_2param[n_hist];
TH1D *hist_ratio_2param[n_hist];
TH1D *hist_res_2param[n_hist];

TH1D *hist_mc_sum_frfitter[n_hist];
TH1D *hist_mc_norad_sum_frfitter[n_hist];
TH1D *hist_mc_rad_sum_frfitter[n_hist];
TH1D *hist_data_sum_frfitter[n_hist];
TH1D *hist_mc_photon_sum_frfitter[n_hist];
TH1D *hist_ratio_frfitter[n_hist];
TH1D *hist_res_frfitter[n_hist];

TH1D *hist_mc_sum_frfitter_after[n_hist];
TH1D *hist_mc_norad_sum_frfitter_after[n_hist];
TH1D *hist_mc_rad_sum_frfitter_after[n_hist];
TH1D *hist_data_sum_frfitter_after[n_hist];
TH1D *hist_mc_photon_sum_frfitter_after[n_hist];
TH1D *hist_ratio_frfitter_after[n_hist];
TH1D *hist_res_frfitter_after[n_hist];


TH1D *hist_mc_sum_ian;
TH1D *hist_mc_norad_sum_ian;
TH1D *hist_mc_rad_sum_ian;
TH1D *hist_data_sum_ian;
TH1D *hist_ratio[n_hist];
TH1D *hist_res[n_hist];

void set_hist_atributes(Int_t number, TString name, TString dir, TString xaxis, Double_t xmin, Double_t xmax, Double_t ymin, Bool_t logy, Int_t rebin);
void minuitFunctionBarlowBeeston2(int& nDim, double* gout, double& result, double par[], int flg);
void minuitFunctionBarlowBeeston1(int& nDim, double* gout, double& result, double par[], int flg);
void minuitFunctionGauss(int& nDim, double* gout, double& result, double par[], int flg);
Double_t chi2_2(double* par, Int_t& ndf, Double_t& left, Double_t& right, TString s_method);
Double_t chi2_1(double* par, Int_t& ndf, Double_t& left, Double_t& right, TString s_method);

int main(int argc, char *argv[])
{
  gROOT->SetStyle("Plain");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleH(0.08);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleY(0.99);
  gStyle->SetTitleX(0.15);
  set_hist_atributes(0, "h_fmax", "Photon_with_jet", "f_{max}", 0, 1, 0.1, kFALSE, 10);
  set_hist_atributes(1, "h_deltaz", "Photon_with_jet", "#delta z", 0, 1.5, 0.1, kFALSE, 10);
  TString s_period[n_periods] = {"0405e", "06e", "0607p"};
  TFile *file[n_periods][4];
  TFile *file_data04p;
  
  TString s_path = "/data/zenith234b/kuprash/analyses/prompt_photons/";
  //  TString s_process = "_rew_prph_2nd_morehistos.root";
  //  TString s_process = "_rew_y.root";
  //  TString s_process = "_rew_y_binbybin.root";
  //  TString s_process = "_norew.root";
  TString s_process = "_norew.root";  
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
      }
  }
  cout << "histos succesfully read" << endl;

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

  for(Int_t i=0; i<n_hist; i++) {
    cout << "1" << endl;
    hist_data_sum_frfitter[i] = (TH1D*)hist_data_sum[i]->Clone();
    hist_data_sum_frfitter[i]->SetName((TString)hist_data_sum[i]->GetName() + "_frfitter");
    hist_mc_sum_frfitter[i] = (TH1D*)hist_mc_sum[i]->Clone();
    hist_mc_sum_frfitter[i]->SetName((TString)hist_mc_sum[i]->GetName() + "_frfitter");
    hist_mc_norad_sum_frfitter[i] = (TH1D*)hist_mc_norad_sum[i]->Clone();
    hist_mc_norad_sum_frfitter[i]->SetName((TString)hist_mc_norad_sum[i]->GetName() + "_frfitter");
    cout << "1" << endl;
    hist_mc_rad_sum_frfitter[i] = (TH1D*)hist_mc_rad_sum[i]->Clone();
    hist_mc_rad_sum_frfitter[i]->SetName((TString)hist_mc_rad_sum[i]->GetName() + "_frfitter");
    //    hist_mc_photon_sum_frfitter[i] = (TH1D*)hist_mc_photon_sum[i]->Clone();
    //    hist_mc_photon_sum_frfitter[i]->SetName((TString)hist_mc_photon_sum[i]->GetName() + "_frfitter");
    cout << "1" << endl;
    hist_ratio_frfitter[i] = (TH1D*)hist_ratio[i]->Clone();
    hist_ratio_frfitter[i]->SetName((TString)hist_ratio[i]->GetName() + "_frfitter");
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
	  hist_data_sum_frfitter[i]->Add(hist_data[p][i]);
	  cerr << hist_data[p][i]->GetNbinsX() << endl;
	  cerr << "data - ok" << endl;
	  hist_mc_rad_sum[i]->Add(hist_mc_rad[p][i], lumi_data[p]/lumi_mc_bg[p]);
	  hist_mc_rad_sum_frfitter[i]->Add(hist_mc_rad[p][i]);
	  cerr << hist_mc_rad[p][i]->GetNbinsX() << endl;
	  cerr << "mc_rad - ok" << endl;
	  hist_mc_norad_sum[i]->Add(hist_mc_norad[p][i], lumi_data[p]/lumi_mc_bg[p]);
	  hist_mc_norad_sum_frfitter[i]->Add(hist_mc_rad[p][i]);
	  cerr << hist_mc_norad[p][i]->GetNbinsX() << endl;
	  cerr << "mc_norad - ok" << endl;
	  if(s_period[p]!= "0607p") {
	    hist_mc_sum[i]->Add(hist_mc[p][i]);
	    hist_mc_sum_frfitter[i]->Add(hist_mc[p][i]);
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

  //p (1-p)
  for(Int_t i=0; i<n_hist; i++)
    {
      hist_mc_sum[i]->Scale((hist_data_sum[i]->Integral()- hist_mc_rad_sum[i]->Integral())/hist_mc_sum[i]->Integral());
      hist_mc_norad_sum[i]->Scale((hist_data_sum[i]->Integral()-hist_mc_rad_sum[i]->Integral())/hist_mc_norad_sum[i]->Integral());
    } 
  cerr << "SCALE : OK" << endl;

  for(Int_t i=0; i<n_hist; i++) {
    hist_data_sum[i]->Rebin(hist_rebin[i]);
    hist_mc_sum[i]->Rebin(hist_rebin[i]);
    hist_mc_rad_sum[i]->Rebin(hist_rebin[i]);
    hist_mc_norad_sum[i]->Rebin(hist_rebin[i]);
    hist_ratio[i]->Rebin(hist_rebin[i]);
    hist_mc_photon_sum[i]->Rebin(hist_rebin[i]);

    hist_data_sum_frfitter[i]->Rebin(2*hist_rebin[i]);
    hist_mc_sum_frfitter[i]->Rebin(2*hist_rebin[i]);
    hist_mc_rad_sum_frfitter[i]->Rebin(2*hist_rebin[i]);
    hist_mc_norad_sum_frfitter[i]->Rebin(2*hist_rebin[i]);
    hist_ratio_frfitter[i]->Rebin(2*hist_rebin[i]);
    //    hist_mc_photon_sum_frfitter[i]->Rebin(hist_rebin[i]);
  }

  cerr << "REBIN : OK" << endl;

  for(Int_t i=0; i<n_hist; i++) {
    hist_data_sum_2param[i] = (TH1D*)hist_data_sum[i]->Clone();
    hist_data_sum_2param[i]->SetName((TString)hist_data_sum[i]->GetName() + "_2param");
    hist_mc_sum_2param[i] = (TH1D*)hist_mc_sum[i]->Clone();
    hist_mc_sum_2param[i]->SetName((TString)hist_mc_sum[i]->GetName() + "_2param");
    hist_mc_norad_sum_2param[i] = (TH1D*)hist_mc_norad_sum[i]->Clone();
    hist_mc_norad_sum_2param[i]->SetName((TString)hist_mc_norad_sum[i]->GetName() + "_2param");
    hist_mc_rad_sum_2param[i] = (TH1D*)hist_mc_rad_sum[i]->Clone();
    hist_mc_rad_sum_2param[i]->SetName((TString)hist_mc_rad_sum[i]->GetName() + "_2param");
    hist_mc_photon_sum_2param[i] = (TH1D*)hist_mc_photon_sum[i]->Clone();
    hist_mc_photon_sum_2param[i]->SetName((TString)hist_mc_photon_sum[i]->GetName() + "_2param");
    hist_ratio_2param[i] = (TH1D*)hist_ratio[i]->Clone();
    hist_ratio_2param[i]->SetName((TString)hist_ratio[i]->GetName() + "_2param");
  }

  for(Int_t i=0; i<n_hist; i++)
    {
      hist_res[i] = (TH1D*)hist_mc_rad_sum[i]->Clone();
      hist_res[i]->SetName(s_hist[i]+"_res");
      hist_res_2param[i] = (TH1D*)hist_mc_rad_sum_2param[i]->Clone();
      hist_res_2param[i]->SetName(s_hist[i]+"_2param_res");
      hist_res_frfitter[i] = (TH1D*)hist_mc_rad_sum_frfitter[i]->Clone();
      hist_res_frfitter[i]->SetName(s_hist[i]+"_frfitter_res");
    }
  

  //fit with two parameters
  {
    TFitter* minimizer2 = new TFitter(2);
    // MAKE IT QUIET!!
    {
      //    double p1 = -1;
      //    minimizer->ExecuteCommand("SET PRINTOUT",&p1,1);
    }
    Double_t param2[2] = {0.};
    Double_t param2_err[2] = {0.};

    minimizer2->SetFCN(minuitFunctionBarlowBeeston2);
    minimizer2->SetParameter(0, "ALPHA", 0.325636, 0.05, 0., 1.);
    minimizer2->SetParameter(1, "BETA", 0.667929, 0.05, 0., 1.);
    minimizer2->ExecuteCommand("SIMPLEX", 0, 0);
    cout << "after simplex" << endl;

    cout << "====== NUMBER OF ENTRIES ======" << endl;
    cout << "data: " << hist_data_sum[g_index_deltaz]->GetEntries() << endl;
    cout << "mc_norad: "<< hist_mc_norad_sum[g_index_deltaz]->GetEntries() << endl;
    cout << "mc_rad: " << hist_mc_rad_sum[g_index_deltaz]->GetEntries() << endl;
    cout << "mc_signal: " << hist_mc_sum[g_index_deltaz]->GetEntries() << endl;
    minimizer2->ExecuteCommand("MIGRAD",0,0);
    cout << "after migrad" << endl;
    minimizer2->ExecuteCommand("HESSE",0,0);
    cout << "after hesse" << endl;
    minimizer2->ExecuteCommand("MINOS",0,0);
    cout << "after minos" << endl;
    for(Int_t i=0; i<2; i++) {
      param2[i] = minimizer2->GetParameter(i);
      param2_err[i] = minimizer2->GetParError(i);
      cout << "par " << i << " = " << param2[i] << " +- " << param2_err[i] << endl;
    }
    //  hist_check_fit_error->Fill(param[0]);

    Int_t ndf;
    Double_t chi_squared, left_bound, right_bound;

    chi_squared = chi2_2(param2, ndf, left_bound, right_bound, "Barlow-Beeston") / (ndf - 1);
    cout << "Barlow-Beeston chi2 approach: " << endl;
    cout << "param 0 = " << param2[0] << " +- " << param2_err[0] << endl;
    cout << "param 1 = " << param2[1] << " +- " << param2_err[1] << endl;
    cout << "with chi2 / " << ndf << "-1 = " << chi_squared << endl;

    for(Int_t i=0; i<n_hist; i++)
      {
	//
	// Barlow-Beeston
	//
      
      hist_mc_sum_2param[i]->Scale(param2[0]);
      for(Int_t j=0; j<hist_mc_sum_2param[i]->GetNbinsX(); j++)
	{
	  //	  cout << "err before: " << i << " " << j << " " << hist_mc_sum_2param[i]->GetBinError(j+1) << endl;
	  Double_t err = hist_mc_sum_2param[i]->GetBinError(j+1)/param2[0];
	  Double_t add_err1 = param2_err[0]*hist_mc_sum_2param[i]->GetBinContent(j+1)/param2[0];
	  add_err1 *= add_err1;
	  Double_t add_err2 = err*param2[0];
	  add_err2 *= add_err2;
	  hist_mc_sum_2param[i]->SetBinError(j+1, TMath::Sqrt(add_err1 + add_err2));
	  //	  cout << "err after: " << i << " " << j << " " << hist_mc_sum_2param[i]->GetBinError(j+1) << endl;
	}
      hist_mc_norad_sum_2param[i]->Scale(param2[1]);
      for(Int_t j=0; j<hist_mc_norad_sum_2param[i]->GetNbinsX(); j++)
	{
	  Double_t err = hist_mc_norad_sum_2param[i]->GetBinError(j+1)/param2[1];
	  Double_t add_err1 = param2_err[1]*hist_mc_norad_sum_2param[i]->GetBinContent(j+1)/(param2[1]);
	  add_err1 *= add_err1;
	  Double_t add_err2 = err*(param2[1]);
	  add_err2 *= add_err2;
	  hist_mc_norad_sum_2param[i]->SetBinError(j+1, TMath::Sqrt(add_err1 + add_err2));
	}
      hist_res_2param[i]->Add(hist_mc_sum_2param[i], 1.);
      hist_res_2param[i]->Add(hist_mc_norad_sum_2param[i], 1.);
      hist_res_2param[i]->SetLineColor(kBlue);
      hist_res_2param[i]->SetLineWidth(1);
      //      hist_res_2param[i]->SetFillColor(kYellow);
      for(Int_t j=0; j<hist_mc_sum_2param[i]->GetNbinsX(); j++)
	{
	  if(hist_res_2param[i]->GetBinContent(j+1) != 0.) {	    
	    hist_ratio_2param[i]->SetBinContent(j+1, hist_data_sum_2param[i]->GetBinContent(j+1)/hist_res_2param[i]->GetBinContent(j+1));
	    Double_t err1, err2, err;
	    //	    cout << "ok" << endl;
	    Double_t x = hist_data_sum_2param[i]->GetBinContent(j+1);
	    Double_t y = hist_res_2param[i]->GetBinContent(j+1);
	    Double_t x_err = hist_data_sum_2param[i]->GetBinError(j+1);
	    Double_t y_err = hist_res_2param[i]->GetBinError(j+1);
	    //	    cout << "ok" << endl;
	    err1 = x_err/y;
	    err2 = x*y_err/(y*y);
	    err = TMath::Sqrt(err1*err1 + err2*err2);
	    //	    err = x/(y*y) + x*x*y/(y*y*y*y);
	    //	    err = TMath::Sqrt(err);
	    hist_ratio_2param[i]->SetBinError(j+1, err);
	  }
	}
    }      
  }


  //fit with one parameter
  {
    TFitter* minimizer1 = new TFitter(1);
    // MAKE IT QUIET!!
    {
      //    double p1 = -1;
      //    minimizer->ExecuteCommand("SET PRINTOUT",&p1,1);
    }
    Double_t param1[1] = {0.};
    Double_t param1_err[1] = {0.};

    minimizer1->SetFCN(minuitFunctionBarlowBeeston1);
    minimizer1->SetParameter(0, "ALPHA", 0.325636, 0.05, 0., 1.);
    minimizer1->ExecuteCommand("SIMPLEX", 0, 0);
    cout << "after simplex" << endl;

    cout << "====== NUMBER OF ENTRIES ======" << endl;
    cout << "data: " << hist_data_sum[g_index_deltaz]->GetEntries() << endl;
    cout << "mc_norad: "<< hist_mc_norad_sum[g_index_deltaz]->GetEntries() << endl;
    cout << "mc_rad: " << hist_mc_rad_sum[g_index_deltaz]->GetEntries() << endl;
    cout << "mc_signal: " << hist_mc_sum[g_index_deltaz]->GetEntries() << endl;
    minimizer1->ExecuteCommand("MIGRAD",0,0);
    cout << "after migrad" << endl;
    minimizer1->ExecuteCommand("HESSE",0,0);
    cout << "after hesse" << endl;
    minimizer1->ExecuteCommand("MINOS",0,0);
    cout << "after minos" << endl;
    for(Int_t i=0; i<1; i++) {
      param1[i] = minimizer1->GetParameter(i);
      param1_err[i] = minimizer1->GetParError(i);
      cout << "par " << i << " = " << param1[i] << " +- " << param1_err[i] << endl;
    }
    //  hist_check_fit_error->Fill(param[0]);

    Int_t ndf;
    Double_t chi_squared, left_bound, right_bound;

    chi_squared = chi2_1(param1, ndf, left_bound, right_bound, "Barlow-Beeston") / (ndf - 1);
    cout << "Barlow-Beeston chi2 approach: " << endl;
    cout << "param 0 = " << param1[0] << " +- " << param1_err[0] << endl;
    cout << "with chi2 / " << ndf << "-1 = " << chi_squared << endl;
    for(Int_t i=0; i<n_hist; i++)
      {
	//
	// Barlow-Beeston
	//
      
      hist_mc_sum[i]->Scale(param1[0]);
      for(Int_t j=0; j<hist_mc_sum[i]->GetNbinsX(); j++)
	{
	  //	  cout << "err before: " << i << " " << j << " " << hist_mc_sum[i]->GetBinError(j+1) << endl;
	  Double_t err = hist_mc_sum[i]->GetBinError(j+1)/param1[0];
	  Double_t add_err1 = param1_err[0]*hist_mc_sum[i]->GetBinContent(j+1)/param1[0];
	  add_err1 *= add_err1;
	  Double_t add_err2 = err*param1[0];
	  add_err2 *= add_err2;
	  hist_mc_sum[i]->SetBinError(j+1, TMath::Sqrt(add_err1 + add_err2));
	  //	  cout << "err after: " << i << " " << j << " " << hist_mc_sum[i]->GetBinError(j+1) << endl;
	}
      hist_mc_norad_sum[i]->Scale(1.-param1[0]);
      for(Int_t j=0; j<hist_mc_norad_sum[i]->GetNbinsX(); j++)
	{
	  Double_t err = hist_mc_norad_sum[i]->GetBinError(j+1)/(1.-param1[0]);
	  Double_t add_err1 = param1_err[0]*hist_mc_norad_sum[i]->GetBinContent(j+1)/(1.-param1[0]);
	  add_err1 *= add_err1;
	  Double_t add_err2 = err*(1.-param1[0]);
	  add_err2 *= add_err2;
	  hist_mc_norad_sum[i]->SetBinError(j+1, TMath::Sqrt(add_err1 + add_err2));
	}
      hist_res[i]->Add(hist_mc_sum[i], 1.);
      hist_res[i]->Add(hist_mc_norad_sum[i], 1.);
      hist_res[i]->SetLineColor(kBlack);
      hist_res[i]->SetLineWidth(1);
      hist_res[i]->SetFillColor(kYellow);

      for(Int_t j=0; j<hist_mc_sum[i]->GetNbinsX(); j++)
	{
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
  }

  //fit with TFractionFitter
  {
    TObjArray *mc_array = new TObjArray(3);
    for(Int_t i=0; i<hist_mc_rad_sum_frfitter[1]->GetNbinsX(); i++) {
      //      hist_mc_rad_sum_frfitter[g_index_deltaz]->SetBinError(i+1, 0);
      //      hist_mc_norad_sum_frfitter[g_index_deltaz]->SetBinError(i+1, 0);
      //      hist_mc_sum_frfitter[g_index_deltaz]->SetBinError(i+1, 0);
    }

    cout << "bins before fit" << endl;
    for(Int_t i=0; i<hist_res_frfitter[g_index_deltaz]->GetNbinsX(); i++) {
      cout << i << ": " << hist_mc_rad_sum_frfitter[g_index_deltaz]->GetBinContent(i+1) << " \t"
	   << hist_mc_sum_frfitter[g_index_deltaz]->GetBinContent(i+1) << " \t"
	   << hist_mc_norad_sum_frfitter[g_index_deltaz]->GetBinContent(i+1) << " \t"
	   <<  hist_res_frfitter[g_index_deltaz]->GetBinContent(i+1) << " \t"
	   <<  hist_data_sum[g_index_deltaz]->GetBinContent(i+1) <<  endl ;
    }

    cout << "before fit: " << hist_mc_rad_sum_frfitter[g_index_deltaz]->Integral() << " "
	 << hist_mc_sum_frfitter[g_index_deltaz]->Integral() << " "
	 << hist_mc_norad_sum_frfitter[g_index_deltaz]->Integral() << " "
	 << hist_data_sum_frfitter[g_index_deltaz]->Integral() << endl;
    mc_array->Add(hist_mc_rad_sum_frfitter[g_index_deltaz]);
    mc_array->Add(hist_mc_sum_frfitter[g_index_deltaz]);
    mc_array->Add(hist_mc_norad_sum_frfitter[g_index_deltaz]);
    cout << "How are you?" << endl;
    TFractionFitter* fit = new TFractionFitter(hist_data_sum_frfitter[g_index_deltaz], mc_array);
    fit->Constrain(0, 0., 1.);
    fit->Constrain(1, 0., 1.);
    fit->Constrain(2, 0., 1.);
    //    fit->SetRangeX(2, 5);
    cout << "Fit!" << endl;
    Int_t status = fit->Fit();
    cout << "fit status: " << status << endl;
    if(status != 0) { exit(-1);}
    Int_t parm[3] = {0, 1, 2};
    Double_t value1 = 0.;
    Double_t error1 = 0.;
    Double_t value2 = 0.;
    Double_t error2 = 0.;
    Double_t value3 = 0.;
    Double_t error3 = 0.;
    Double_t value4 = 0.;
    Double_t error4 = 0.;
    fit->GetResult(0, value1, error1);
    fit->GetResult(1, value2, error2);
    fit->GetResult(2, value3, error3);
    fit->GetResult(3, value4, error4);
    cout << "chi2 = " << fit->GetChisquare() << ", ndf = " << fit->GetNDF() << ", prob = " << fit->GetProb() << endl;
      cout << "value1 = " << value1 << " +- " << error1 << endl;
      cout << "value2 = " << value2 << " +- " << error2 << endl;
      cout << "value3 = " << value3 << " +- " << error3 << endl;
      cout << "value4 = " << value4 << " +- " << error4 << endl;
    hist_res_frfitter_after[g_index_deltaz] = (TH1D*)fit->GetPlot();
    hist_res_frfitter_after[g_index_deltaz]->SetLineColor(kRed);
    hist_mc_rad_sum_frfitter_after[g_index_deltaz] = (TH1D*)fit->GetMCPrediction(0);
    hist_mc_sum_frfitter_after[g_index_deltaz] = (TH1D*)fit->GetMCPrediction(1);
    hist_mc_norad_sum_frfitter_after[g_index_deltaz] = (TH1D*)fit->GetMCPrediction(2);

    cout << "before \tafter" << endl;
    cout << "norad" << endl;
    for(Int_t i=0; i<hist_res_frfitter[g_index_deltaz]->GetNbinsX(); i++) {
      cout << i << ": " << hist_mc_norad_sum_frfitter[1]->GetBinContent(i+1) << " \t" << hist_mc_norad_sum_frfitter_after[1]->GetBinContent(i+1) << endl;
      }
    hist_mc_rad_sum_frfitter_after[g_index_deltaz]->Scale(value1);
    hist_mc_sum_frfitter_after[g_index_deltaz]->Scale(value2);
    hist_mc_norad_sum_frfitter_after[g_index_deltaz]->Scale(value3);

    cout << "result" << endl;
    for(Int_t i=0; i<hist_res_frfitter[g_index_deltaz]->GetNbinsX(); i++) {
      cout << i << ": " << hist_mc_rad_sum_frfitter_after[g_index_deltaz]->GetBinContent(i+1) << " \t"
	   << hist_mc_sum_frfitter_after[g_index_deltaz]->GetBinContent(i+1) << " \t"
	   << hist_mc_norad_sum_frfitter_after[g_index_deltaz]->GetBinContent(i+1) << " \t"
	   <<  hist_res_frfitter_after[g_index_deltaz]->GetBinContent(i+1) << " \t"
	   <<  hist_data_sum[g_index_deltaz]->GetBinContent(i+1) <<  endl ;
    }

    cout << "after fit: " << hist_mc_rad_sum_frfitter[g_index_deltaz]->Integral() << " "
	 << hist_mc_sum_frfitter[g_index_deltaz]->Integral() << " "
	 << hist_mc_norad_sum_frfitter[g_index_deltaz]->Integral() << " "
	 << hist_data_sum_frfitter[g_index_deltaz]->Integral() << endl;
  }



  TH2D *h_window[n_hist];
  TH2D *h_window_ratio[n_hist];
  TF1 *f1 = new TF1("f1", "1.", -10000., 10000.);
  f1->SetLineColor(39);
  f1->SetLineWidth(1);
  for(Int_t i=0; i<n_hist; i++) {
    Double_t y_max = 1.2*hist_data_sum[i]->GetMaximum();
    cout << "if(i == " << i << ") y_max = " << y_max << ";" << endl;
    TString s; s.Form("h_window%i", i);
    h_window[i] = new TH2D(s, "", 10, hist_xmin[i], hist_xmax[i], 10, -1000, y_max);
    s.Form("h_window_ratio%i", i);
    h_window_ratio[i] = new TH2D(s, "", 10, hist_xmin[i], hist_xmax[i], 10, 0., 3.);
  }

  for(Int_t i=0; i<n_hist; i++)
    {

    }

  TCanvas* c1[n_hist];
  for(Int_t i=0; i<n_hist; i++) {
    TString s; s.Form("c%i", i);
    c1[i] = new TCanvas(s, s, 600, 1000);
  }
  //  c1[1] = new TCanvas("c11", "c11", 1000, 800);

  for(Int_t i=0; i<n_hist; i++)
    {
      c1[i]->Divide(1, 2);
      make_clean_pads(c1[i], 2, 0, 0);
    }
  for(Int_t i=0; i<n_hist; i++) {
    sign_window(c1[i]->GetPad(1), h_window[i], s_xaxis[i], "Events", "", "middle");
    sign_window(c1[i]->GetPad(2), h_window_ratio[i], s_xaxis[i], "data / mc", "", "middle");
  }

  TLegend *leg = new TLegend(0.45, 0.6, 0.86, 0.91);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(hist_data_sum[0], "data", "pe");
  leg->AddEntry(hist_mc_sum[0], "signal mc", "l");
  leg->AddEntry(hist_mc_rad_sum[0], "rad bg mc", "l");
  leg->AddEntry(hist_mc_norad_sum[0], "norad bg mc", "l");
  leg->AddEntry(hist_res[0], "signal + bg", "f");

  for(Int_t i=1; i<n_hist; i++)
    {
      c1[i]->GetPad(1)->cd();
      ((TGaxis*)h_window[i]->GetYaxis())->SetMaxDigits(2);
      ((TGaxis*)h_window[i]->GetXaxis())->SetMaxDigits(3);
      h_window[i]->DrawClone();      

      //      hist_mc_sum[i]->DrawClone("HIST SAME");  
      //      hist_mc_rad_sum[i]->DrawClone("HIST SAME");  
      //      hist_mc_norad_sum[i]->DrawClone("HIST SAME");
      //      Shift(hist_data_sum[i], 0.2);
      //      hist_res[i]->DrawClone("F SAME");
      Double_t xmin = hist_data_sum[i]->GetXaxis()->GetXmin();
      Double_t xmax = hist_data_sum[i]->GetXaxis()->GetXmax();
      Double_t deltax = xmax-xmin;
      hist_res[i]->DrawClone("HIST SAME");
      hist_res[i]->DrawClone("SAME");
      hist_res_2param[i]->DrawClone("HIST SAME");
      hist_res_2param[i]->GetXaxis()->SetLimits(xmin - 0.01*deltax, xmax-0.01*deltax);
      hist_res_2param[i]->DrawClone("P E X0 SAME");
      hist_res_frfitter_after[i]->DrawClone("HIST SAME");
      hist_res_frfitter_after[i]->DrawClone("P E1 X0 SAME");

      hist_mc_sum_frfitter_after[i]->SetLineColor(kGreen);
      hist_mc_sum_frfitter_after[i]->SetLineWidth(2);
      hist_mc_sum_frfitter_after[i]->DrawClone("HIST SAME");
      //      hist_mc_sum_frfitter[i]->DrawClone("HIST SAME");
      hist_mc_norad_sum_frfitter_after[i]->SetLineColor(kGreen);
      hist_mc_norad_sum_frfitter_after[i]->SetLineWidth(2);
      hist_mc_norad_sum_frfitter_after[i]->DrawClone("HIST SAME");
      //      hist_mc_norad_sum_frfitter[i]->DrawClone("HIST SAME");

      hist_mc_rad_sum_frfitter_after[i]->SetLineColor(kGreen);
      hist_mc_rad_sum_frfitter_after[i]->SetLineWidth(2);
      hist_mc_rad_sum_frfitter_after[i]->DrawClone("HIST SAME");
      //      hist_mc_rad_sum_frfitter[i]->DrawClone("HIST SAME");
      hist_data_sum[i]->GetXaxis()->SetLimits(xmin + 0.01*deltax, xmax+0.01*deltax);
      hist_data_sum[i]->SetMarkerColor(kRed);
      hist_data_sum[i]->SetLineColor(kRed);
      hist_data_sum[i]->DrawClone("P E X0 SAME");  
      


      c1[i]->GetPad(1)->RedrawAxis();

      c1[i]->GetPad(2)->cd();
      h_window_ratio[i]->DrawClone();
      f1->Draw("SAME");
      hist_ratio[i]->SetLineColor(kBlack);
      hist_ratio[i]->SetLineWidth(2);
      hist_ratio[i]->SetMarkerStyle(20);
      hist_ratio[i]->SetMarkerSize(0.7);
      hist_ratio[i]->SetMarkerColor(kBlack);


      hist_ratio_2param[i]->SetLineColor(kBlue);
      hist_ratio_2param[i]->SetLineWidth(2);
      hist_ratio_2param[i]->SetMarkerStyle(20);
      hist_ratio_2param[i]->SetMarkerSize(0.5);
      hist_ratio_2param[i]->SetMarkerColor(kBlue);

      hist_ratio[i]->DrawClone("P E1  HIST  SAME");  
      hist_ratio_2param[i]->DrawClone("P E1 X0 HIST  SAME");  

      if(i == 0)
	leg->DrawClone();

    }

  for(Int_t i=0; i<n_hist; i++) {
    TString s; s.Form("fit%i.eps", i);
    c1[i]->Print(s);
    s.Form("fit%i.png", i);
    c1[i]->Print(s);
  }

  return 0;
}

void minuitFunctionBarlowBeeston1(int& nDim, double* gout, double& result, double par[], int flg) 
{
  Int_t ndf;
  Double_t left, right;
  result = chi2_1(par, ndf, left, right, "Barlow-Beeston");
}


void minuitFunctionBarlowBeeston2(int& nDim, double* gout, double& result, double par[], int flg) 
{
  Int_t ndf;
  Double_t left, right;
  result = chi2_2(par, ndf, left, right, "Barlow-Beeston");
}

void minuitFunctionGauss(int& nDim, double* gout, double& result, double par[], int flg) 
{
  Int_t ndf;
  Double_t left, right;
  result = chi2_1(par, ndf, left, right, "Gauss");
}

Double_t chi2_2(double* par, Int_t& ndf, Double_t& left, Double_t& right, TString s_method)
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
      diff = hist_data_sum[index]->GetBinContent(i+1) - hist_mc_rad_sum[index]->GetBinContent(i+1) - par[0]*hist_mc_sum[index]->GetBinContent(i+1) - par[1]*hist_mc_norad_sum[index]->GetBinContent(i+1);
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
	denom = s_d*s_d + s_l*s_l + par[0]*par[0]*s_q*s_q + par[1]*par[1]*s_bg*s_bg;
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



Double_t chi2_1(double* par, Int_t& ndf, Double_t& left, Double_t& right, TString s_method)
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
      diff = hist_data_sum[index]->GetBinContent(i+1) - hist_mc_rad_sum[index]->GetBinContent(i+1) - par[0]*hist_mc_sum[index]->GetBinContent(i+1) - (1.-par[0])*hist_mc_norad_sum[index]->GetBinContent(i+1);
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
