#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include <TH1D.h>
#include <TFitter.h>
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

const Int_t n_hist = 7;
const Int_t n_periods = 3;
TH1D *hist_mc[n_periods][n_hist];
TH1D *hist_mc_norad[n_periods][n_hist];
TH1D *hist_mc_rad[n_periods][n_hist];
TH1D *hist_data[n_periods][n_hist];
TH1D *hist_mc_sum[n_hist];
TH1D *hist_mc_norad_sum[n_hist];
TH1D *hist_mc_rad_sum[n_hist];
TH1D *hist_data_sum[n_hist];
//copies to rebin
TH1D *hist_mc_sum_copy[n_hist];
TH1D *hist_mc_norad_sum_copy[n_hist];
TH1D *hist_mc_rad_sum_copy[n_hist];
TH1D *hist_data_sum_copy[n_hist];

TH1D *hist_ratio[n_hist];
TH1D *hist_res[n_hist];
void minuitFunctionBarlowBeeston(int& nDim, double* gout, double& result, double par[], int flg);
void minuitFunctionGauss(int& nDim, double* gout, double& result, double par[], int flg);
Double_t chi2(double* par, Int_t& ndf, Double_t& left, Double_t& right, TString s_method);
TString fit_method = "deltaz";
Int_t left_bin_fmax = 1;
Int_t right_bin_fmax = 300;

int main(int argc, char *argv[])
{
  gROOT->SetStyle("Plain");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleH(0.08);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleY(0.99);
  gStyle->SetTitleX(0.15);
  /*
  -rw-r--r--  1 kuprash zeus 30191157 Oct  1 22:35 ../data0405e_nocorr.root
    -rw-r--r--  1 kuprash zeus 77797487 Oct  1 08:42 ../dataall_nocorr.root
    lrwxrwxrwx  1 kuprash zeus       22 Sep 30 16:00 ../file.root -> mc_bg0405e_nocorr.root
    -rw-r--r--  1 kuprash zeus 43117289 Oct  1 15:55 ../mc_bg0405e_nocorr.root
    -rw-r--r--  1 kuprash zeus 32664395 Oct  1 22:37 ../mc_bg_norad0405e_nocorr.root
    -rw-r--r--  1 kuprash zeus  2959431 Oct  1 22:21 ../mc_bg_rad0405e_nocorr.root
    -rw-r--r--  1 kuprash zeus      458 Oct  1 07:01 ../mc_bgall_nocorr.root
    -rw-r--r--  1 kuprash zeus 19139829 Oct  1 21:58 ../mc_prph_nocorr.root

  */
  TString s_period[n_periods] = {"0405e", "06e", "0607p"};
  TFile *file[n_periods][4];
  //  TFile *file1 = new TFile("../dataall_nocorr_our_trig_study.root");
  //  TFile *file2 = new TFile("../mc_bg_noradall_nocorr_our_trig_study.root");
  //  TFile *file3 = new TFile("../mc_bg_radall_nocorr_our_trig_study.root");
  //  TFile *file4 = new TFile("../mc_prph_nocorr_our_trig_study.root");
  
  TString s_hist[n_hist] = {"h_fmax", "h_deltaz", "h_prph_energy", "h_comp_jet_e",  "h_comp_x", "h_comp_Q2", "h_jet_deltaR"};
  TString s_xaxis[n_hist] = {"f_{max}", "#delta z", "E_{T, photon} (GeV)", "E_{T, jet} (GeV)", "x_{Bj}", "Q^{2} (GeV^{2})", "#delta r"};
  Double_t hist_xmin[n_hist] = {0., 0., 2., 0., 2.e-4, 0.,  0.};
  Double_t hist_xmax[n_hist] = {1., 1.5, 16., 35.,2.e-2, 400., 10.};
  Double_t hist_ymin[n_hist] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
  //  TString s_yaxis[n_hist] = {"a", "Events", "Events", "Events"};

  for(Int_t p=0; p<n_periods; p++) {
    file[p][0] =  new TFile("../data" + s_period[p] + "_nocorr.root");
    file[p][1] =  new TFile("../mc_bg_norad" + s_period[p] + "_nocorr.root");
    file[p][2] =  new TFile("../mc_bg_rad" + s_period[p] + "_nocorr.root");
    file[p][3] =  new TFile("../mc_prph_nocorr.root");
    cout << s_period[p] << " files attached" << endl;
    for(Int_t i=0; i<n_hist; i++)
      {

	file[p][3]->cd();
	cout << "reading "  << i << " ..." << endl;
	hist_mc[p][i] = (TH1D*)file[p][3]->Get(s_hist[i])->Clone();
	hist_mc[p][i]->SetName(s_hist[i]+"_mc_signal" + s_period[p]);

	file[p][2]->cd();
	cout << "reading "  << i << " ..." << endl;
	hist_mc_rad[p][i] = (TH1D*)file[p][2]->Get(s_hist[i])->Clone();
	hist_mc_rad[p][i]->SetName(s_hist[i]+"_mc_rad" + s_period[p]);
	file[p][1]->cd();
	cout << "reading "  << i << " ..." << endl;
	hist_mc_norad[p][i] = (TH1D*)file[p][1]->Get(s_hist[i])->Clone();
	hist_mc_norad[p][i]->SetName(s_hist[i]+"_mc_norad" + s_period[p]);
	cout << "1 - OK, " ;
	file[p][0]->cd();
	hist_data[p][i] = (TH1D*)file[p][0]->Get(s_hist[i])->Clone();
	hist_data[p][i]->SetName(s_hist[i]+"_data" + s_period[p]);

	hist_mc[p][i]->Sumw2();
	hist_mc_rad[p][i]->Sumw2();
	hist_mc_norad[p][i]->Sumw2();
	hist_data[p][i]->Sumw2();
	//	hist_ratio[i]->Sumw2();
	//      hist_res[i]->Sumw2();
      }
  }
  cout << "histos succesfully read" << endl;

  for(Int_t i=0; i<n_hist; i++)
    {      
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
	hist_mc_norad_sum[i]->SetLineColor(kGreen);

	hist_data_sum[i] = (TH1D*) hist_data[0][i]->Clone();
	hist_data_sum[i]->SetName(s_hist[i]+"_data");
	hist_data_sum[i]->SetMarkerStyle(20);
	hist_data_sum[i]->SetMarkerSize(0.5);
    }

  Double_t lumi_data[n_periods] = {134.15997, 54.79574, 142.93778};
  Double_t lumi_mc_bg[n_periods] = {134.52, 54.71, 364.6};

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
	  hist_data_sum[i]->Add(hist_data[p][i]);
	  hist_mc_rad_sum[i]->Add(hist_mc_rad[p][i], lumi_data[p]/lumi_mc_bg[p]);
	  hist_mc_norad_sum[i]->Add(hist_mc_norad[p][i], lumi_data[p]/lumi_mc_bg[p]);
	}

    }

  cout << "data: " << hist_data_sum[0]->Integral() << ", rad mc: " << hist_mc_rad_sum[0]->Integral() << endl;
  cout << "mc signal: " << hist_mc_sum[0]->Integral() << " " << hist_mc[0][0]->Integral() << " "  << hist_mc[1][0]->Integral() << " " << hist_mc[2][0]->Integral() << endl;
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

  /*  hist_data_sum[0]->Rebin(2);
  hist_mc_sum[0]->Rebin(2);
  hist_mc_rad_sum[0]->Rebin(2);
  hist_mc_norad_sum[0]->Rebin(2);
  hist_ratio[0]->Rebin(2);
  
  hist_data_sum[1]->Rebin(2);
  hist_mc_sum[1]->Rebin(2);
  hist_mc_rad_sum[1]->Rebin(2);
  hist_mc_norad_sum[1]->Rebin(2);
  hist_ratio[1]->Rebin(2);
 */ 
  hist_data_sum[2]->Rebin(10);
  hist_mc_sum[2]->Rebin(10);
  hist_mc_rad_sum[2]->Rebin(10);
  hist_mc_norad_sum[2]->Rebin(10);
  hist_ratio[2]->Rebin(10);

  hist_data_sum[3]->Rebin(2);
  hist_mc_sum[3]->Rebin(2);
  hist_mc_rad_sum[3]->Rebin(2);
  hist_mc_norad_sum[3]->Rebin(2);
  hist_ratio[3]->Rebin(2);

  hist_data_sum[4]->Rebin(5);
  hist_mc_sum[4]->Rebin(5);
  hist_mc_rad_sum[4]->Rebin(5);
  hist_mc_norad_sum[4]->Rebin(5);
  hist_ratio[4]->Rebin(5);

  hist_data_sum[5]->Rebin(10);
  hist_mc_sum[5]->Rebin(10);
  hist_mc_rad_sum[5]->Rebin(10);
  hist_mc_norad_sum[5]->Rebin(10);
  hist_ratio[5]->Rebin(10);

  hist_mc_sum_copy[0] = (TH1D*)hist_mc_sum[0]->Clone();
  hist_mc_rad_sum_copy[0] = (TH1D*)hist_mc_rad_sum[0]->Clone();
  hist_mc_norad_sum_copy[0] = (TH1D*)hist_mc_norad_sum[0]->Clone();
  hist_data_sum_copy[0] = (TH1D*)hist_data_sum[0]->Clone();

  hist_mc_sum_copy[1] = (TH1D*)hist_mc_sum[1]->Clone();
  hist_mc_rad_sum_copy[1] = (TH1D*)hist_mc_rad_sum[1]->Clone();
  hist_mc_norad_sum_copy[1] = (TH1D*)hist_mc_norad_sum[1]->Clone();
  hist_data_sum_copy[1] = (TH1D*)hist_data_sum[1]->Clone();

  //  hist_ratio[0]->Rebin(2);


  //  hist_ratio[1]->Rebin(2);


    TFitter* minimizer = new TFitter(1);
    // MAKE IT QUIET!!
    {
      double p1 = -1;
      //    minimizer->ExecuteCommand("SET PRINTOUT",&p1,1);
    }
    Double_t param[1] = {0.};
    Double_t param_err[1] = {0.};
    Int_t ndf;
    Double_t chi_squared, left_bound, right_bound;

    Double_t param_Gauss[1] = {0.};
    Double_t param_err_Gauss[1] = {0.};
    Double_t chi_squared_Gauss;
    
  vector <Double_t> chi2_binning;
  vector <Double_t> param_binning;
  vector <Double_t> param_err_binning;
  const Int_t n_bound = 115;//100
  Int_t rebin_bound[n_bound];// = {1, 2, 4, 5, 8, 10, 20, 25, 40};

  Double_t x_bound[n_bound];
  Double_t y_bound[n_bound];
  Double_t y_bound_Gauss[n_bound];
  Double_t y_err_bound[n_bound];
  Double_t y_err_bound_Gauss[n_bound];
  Double_t x_err_bound[n_bound] = {0.};

  Double_t y_par_bound[n_bound];
  Double_t y_par_bound_Gauss[n_bound];
  Double_t y_par_err_bound[n_bound];
  Double_t y_par_err_bound_Gauss[n_bound];

  for(Int_t i=0; i<n_bound; i++) {
    //    Int_t nbins = 
    x_bound[i] = hist_data_sum[1]->GetBinLowEdge(215 - i) + hist_data_sum[1]->GetBinWidth(215 - i);
    right_bin_fmax = 215 -i ;//100;
    left_bin_fmax = 1;//i+1;
    /*hist_mc_sum[0] = (TH1D*)hist_mc_sum_copy[0]->Clone();
    hist_mc_rad_sum[0] = (TH1D*)hist_mc_rad_sum_copy[0]->Clone();
    hist_mc_norad_sum[0] = (TH1D*)hist_mc_norad_sum_copy[0]->Clone();
    hist_data_sum[0] = (TH1D*)hist_data_sum_copy[0]->Clone();

    hist_mc_sum[1] = (TH1D*)hist_mc_sum_copy[1]->Clone();
    hist_mc_rad_sum[1] = (TH1D*)hist_mc_rad_sum_copy[1]->Clone();
    hist_mc_norad_sum[1] = (TH1D*)hist_mc_norad_sum_copy[1]->Clone();
    hist_data_sum[1] = (TH1D*)hist_data_sum_copy[1]->Clone();*/

    /*    hist_data_sum[0]->Rebin(rebin_bound[i]);
    hist_mc_sum[0]->Rebin(rebin_bound[i]);
    hist_mc_rad_sum[0]->Rebin(rebin_bound[i]);
    hist_mc_norad_sum[0]->Rebin(rebin_bound[i]);
    //    hist_ratio[0]->Rebin(2);

    hist_data_sum[1]->Rebin(rebin_bound[i]);
    hist_mc_sum[1]->Rebin(rebin_bound[i]);
    hist_mc_rad_sum[1]->Rebin(rebin_bound[i]);
    hist_mc_norad_sum[1]->Rebin(rebin_bound[i]);
    cout << hist_data_sum[0]->GetNbinsx();*/
    //    hist_ratio[1]->Rebin(2);    
    
    //
    // Here is Barlow-Beeston chi2 function
    //
    // Tell the minimizer about the function to be minimzed
    minimizer->SetFCN(minuitFunctionBarlowBeeston);
    minimizer->SetParameter(0, "ALPHA", 0.35, 0.5, 1.e-2, 1.);
    minimizer->ExecuteCommand("SIMPLEX", 0, 0);
    minimizer->ExecuteCommand("MIGRAD",0,0);
    param[0] = minimizer->GetParameter(0);

    param_err[0] = minimizer->GetParError(0);

    chi_squared = chi2(param, ndf, left_bound, right_bound, "Barlow-Beeston");
    y_bound[i] = chi_squared;//param[0];
    y_par_bound[i] = param[0];
    y_err_bound[i] = 0.;//param_err[0];
    y_par_err_bound[i] = param_err[0];
    cout << "Barlow-Beeston chi2 approach: " << endl;
    cout << "param = " << param[0] << " +- " << param_err[0] << endl;
    cout << "with chi2 / " << ndf << "-1 = " << chi_squared << endl;
    cout << "--> " << i << " left_bin_fmax = " << left_bin_fmax << " " << param[0] << " " << chi_squared << endl;
    minimizer->SetFCN(minuitFunctionGauss);
    minimizer->SetParameter(0, "ALPHA_GAUSS", 0.35, 0.5, 1.e-2, 1.);
    minimizer->ExecuteCommand("SIMPLEX", 0, 0);
    minimizer->ExecuteCommand("MIGRAD",0,0);
    param_Gauss[0] = minimizer->GetParameter(0);
    param_err_Gauss[0] = minimizer->GetParError(0);
    chi_squared_Gauss = chi2(param_Gauss, ndf, left_bound, right_bound, "Gauss");
    cout << "Gauss chi2 approach: " << endl;
    cout << "param = " << param_Gauss[0] << " +- " << param_err_Gauss[0] << endl;
    cout << "with chi2 / " << ndf << "-1 = " << chi_squared_Gauss << endl;
    y_bound_Gauss[i] = chi_squared_Gauss;//param_Gauss[0];
    y_err_bound_Gauss[i] = 0.;//param_err_Gauss[0];
    y_par_bound_Gauss[i] = param_Gauss[0];
    y_par_err_bound_Gauss[i] = param_err_Gauss[0];
  }
  //
  // chi2
  //
  TGraphErrors *tge = new TGraphErrors(n_bound, x_bound, y_bound, x_err_bound, y_err_bound);
  TGraphErrors *tge_Gauss = new TGraphErrors(n_bound, x_bound, y_bound_Gauss, x_err_bound, y_err_bound_Gauss);
  tge_Gauss->SetLineColor(kBlue);
  tge->SetMarkerStyle(20);
  tge->SetMarkerSize(0.7);
  tge_Gauss->SetMarkerStyle(20);
  tge_Gauss->SetMarkerSize(0.7);
  tge_Gauss->SetMarkerColor(kBlue);
  tge_Gauss->SetLineColor(kBlue);
  TLegend *leg_bound = new TLegend(0.4, 0.75, 0.9, 0.9);
  leg_bound->SetFillColor(0);
  leg_bound->SetBorderSize(0);
  leg_bound->AddEntry(tge, "Barlow-Beeston fit", "lp");
  leg_bound->AddEntry(tge_Gauss, "Gauss approach", "lp");
  TCanvas *cc = new TCanvas("cc", "cc", 800, 600);
  cc->Divide(1, 1);
  make_clean_pads(cc, 1, 0, 0);
  TH2D* h_window_bound = new TH2D("h_window_bound", "", 10, 0., 1.4, 10, 0., 3.);
  sign_window(cc->GetPad(1), h_window_bound, "Right bound of fit range, #delta z", "#chi^{2}", "");
  cc->Draw();
  cc->GetPad(1)->cd();
  h_window_bound->DrawClone();
  tge->DrawClone("SAME LP");
  tge_Gauss->DrawClone("SAME LP");
  leg_bound->DrawClone();
  cc->Print("chi2.eps");
  cc->Print("chi2.C");
  //
  // fit parameter
  //
  TGraphErrors *tge_par = new TGraphErrors(n_bound, x_bound, y_par_bound, x_err_bound, y_par_err_bound);
  TGraphErrors *tge_par_Gauss = new TGraphErrors(n_bound, x_bound, y_par_bound_Gauss, x_err_bound, y_par_err_bound_Gauss);
  tge_par_Gauss->SetLineColor(kBlue);
  tge_par->SetMarkerStyle(20);
  tge_par->SetMarkerSize(0.7);
  tge_par_Gauss->SetMarkerStyle(20);
  tge_par_Gauss->SetMarkerSize(0.7);
  tge_par_Gauss->SetLineColor(kBlue);
  TCanvas *cc1 = new TCanvas("cc1", "cc1", 800, 600);
  cc1->Divide(1, 1);
  make_clean_pads(cc1, 1, 0, 0);
  sign_window(cc1->GetPad(1), h_window_bound, "Right bound of fit range, #delta z", "fit parameter", "");
  cc1->Draw();
  cc1->GetPad(1)->cd();
  h_window_bound->GetYaxis()->SetRangeUser(0., 1.);
  h_window_bound->DrawClone();
  tge_par->DrawClone("SAME LP");
  tge_par_Gauss->DrawClone("SAME LP");
  leg_bound->DrawClone();
  cc1->Print("parameter.eps");
  cc1->Print("parameter.C");
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
      hist_mc_norad_sum[i]->Scale(1.-param[0]);
      hist_res[i]->Add(hist_mc_sum[i], 1.);
      hist_res[i]->Add(hist_mc_norad_sum[i], 1.);
      hist_res[i]->SetLineColor(28);
      hist_res[i]->SetLineWidth(4);


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
  cout << "There are " << hist_mc_sum[0]->Integral() << " + " << hist_mc_rad_sum[0]->Integral() << " fitted photons" << endl;
  TH2D *h_window[n_hist];
  TH2D *h_window_ratio[n_hist];
  TF1 *f1 = new TF1("f1", "1.", 0., 1000.);
  f1->SetLineColor(39);
  f1->SetLineWidth(1);
  for(Int_t i=0; i<n_hist; i++) {
    Double_t y_max = 1.2*hist_data_sum[i]->GetMaximum();
    TString s; s.Form("h_window%i", i);
    h_window[i] = new TH2D(s, "", 10, hist_xmin[i], hist_xmax[i], 10, hist_ymin[i], y_max);
    s.Form("h_window_ratio%i", i);
    h_window_ratio[i] = new TH2D(s, "", 10, hist_xmin[i], hist_xmax[i], 10, 0., 2.);
  }

  for(Int_t i=0; i<n_hist; i++)
    {
      for(Int_t j=0; j<hist_mc_sum[i]->GetNbinsX(); j++)
	{
	  //	  cout << i << " " << j << endl;
	  if(hist_res[i]->GetBinContent(j+1) != 0.) {	    
	    hist_ratio[i]->SetBinContent(j+1, hist_data_sum[i]->GetBinContent(j+1)/hist_res[i]->GetBinContent(j+1));
	    Double_t err;
	    //	    cout << "ok" << endl;
	    Double_t x = hist_data_sum[i]->GetBinContent(j+1);
	    Double_t y = hist_res[i]->GetBinContent(j+1);
	    //	    cout << "ok" << endl;
	    err = x/(y*y) + x*x*y/(y*y*y*y);
	    err = TMath::Sqrt(err);
	    hist_ratio[i]->SetBinError(j+1, err);
	  }
	}
    }

  TCanvas* c1[n_hist/2+n_hist%2];
  for(Int_t i=0; i<n_hist/2+n_hist%2; i++) {
    TString s; s.Form("c%i", i);
    c1[i] = new TCanvas(s, s, 1000, 800);
  }
  //  c1[1] = new TCanvas("c11", "c11", 1000, 800);

  for(Int_t i=0; i<n_hist/2+n_hist%2; i++)
    {
      c1[i]->Divide(2, 2);
      make_clean_pads(c1[i], 4, 1, 1);
    }
  for(Int_t i=0; i<n_hist; i++) {
    sign_window(c1[i/2]->GetPad(i%2 + 1), h_window[i], s_xaxis[i], "Events", "", "m");
    sign_window(c1[i/2]->GetPad(i%2 + 3), h_window_ratio[i], s_xaxis[i], "data / mc", "", "m");
  }

  TLegend *leg = new TLegend(0.5, 0.21, 0.89, 0.4);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(hist_data_sum[0], "data", "pe");
  leg->AddEntry(hist_mc_sum[0], "signal mc", "l");
  leg->AddEntry(hist_mc_rad_sum[0], "rad bg mc", "l");
  leg->AddEntry(hist_mc_norad_sum[0], "norad bg mc", "l");
  leg->AddEntry(hist_res[0], "signal + bg", "l");

  for(Int_t i=0; i<n_hist; i++)
    {
      cout << " cd " << i/2 << " " << i%2+1 << endl;
      c1[i/2]->GetPad(i%2+1)->cd();
      h_window[i]->DrawClone();      
      
      hist_data_sum[i]->DrawClone("P E1 SAME");  
      hist_res[i]->DrawClone("HIST SAME");
      hist_mc_sum[i]->DrawClone("HIST SAME");  
      hist_mc_rad_sum[i]->DrawClone("HIST SAME");  
      hist_mc_norad_sum[i]->DrawClone("HIST SAME");
      if(i%2 == 0)
	leg->DrawClone();
      c1[i/2]->GetPad(i%2+3)->cd();
      h_window_ratio[i]->DrawClone();
      f1->Draw("SAME");
      hist_ratio[i]->SetLineColor(kBlack);
      //      hist_ratio[i]->SetLin
      hist_ratio[i]->SetLineColor(kBlue);
      hist_ratio[i]->SetLineWidth(2);
      hist_ratio[i]->DrawClone("E1 HIST  SAME");  

      //      hist_ratio[i]->DrawClone("HIST C SAME");  
    }

  for(Int_t i=0; i<n_hist/2+n_hist%2; i++) {
    TString s; s.Form("c%i.eps", i);
    c1[i]->Print(s);
    s.Form("c%i.png", i);
    c1[i]->Print(s);
  }

  //plot fmax or deltaz on separate canvas
  TPaveText* inform;// = new TPaveText(0.6, 0.61, 0.94, 0.92, "NDC");
  TCanvas *c_method = new TCanvas("c_" + fit_method, fit_method, 800, 600);
  c_method->Divide(1, 1);
  make_clean_pads(c_method, 1, 1, 1);
  c_method->GetPad(1)->cd();
  Int_t index;
  if(fit_method == "fmax") {
    leg->SetX1(0.2500256);
    leg->SetY1(0.6671052);
    leg->SetX2(0.5628141);
    leg->SetY2(0.9302069);
    inform = new TPaveText(0.2423341,0.5444429,0.5512768,0.6564389, "NDC");
    
    index = 0;
  } else
    if(fit_method == "deltaz") {
      index = 1;
      //      0.6346016,0.7044372,0.9345708,0.9302069;
      leg->SetX1(0.6346016);
      leg->SetY1(0.7044372);
      leg->SetX2(0.9345708);
      leg->SetY2(0.9345708);
      inform = new TPaveText(0.6140909,0.574664,0.9230335,0.68666, "NDC");
    }
  TText *t1, *t2;
  TString s1; s1.Form("fit range: %.2f .. %.2f", left_bound, right_bound);
  TString s2; s2.Form("#chi^{2} / %i-1 = %.2f", ndf, chi_squared);
  t1 = inform->AddText(s1); t1->SetTextSize(0.04);
  t2 = inform->AddText(s2); t2->SetTextSize(0.04);
  inform->SetFillColor(0);
  inform->SetBorderSize(0);
  h_window[index]->DrawClone();
  hist_mc_sum[index]->DrawClone("HIST SAME");
  hist_mc_rad_sum[index]->DrawClone("HIST SAME");
  hist_mc_norad_sum[index]->DrawClone("HIST SAME");
  hist_res[index]->DrawClone("HIST E1 SAME");
  hist_data_sum[index]->DrawClone("P E1 SAME");
  leg->DrawClone();
  inform->Draw();
  c_method->Print(fit_method + ".eps");
  c_method->Print(fit_method + ".png");
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
    
    index = 0;
  } else
    if(fit_method == "deltaz") {
      index = 1;
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
  hist_res_Gauss[index]->DrawClone("HIST SAME");
  hist_data_sum[index]->DrawClone("P E1 SAME");
  leg_chi2_method->DrawClone();
  //  inform->Draw();
  c_chi2_method->Print(fit_method + "_diff_chi2.eps");
  c_chi2_method->Print(fit_method + "_diff_chi2.png");

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
    index = 1;
    left = 0.05;
    right = 0.8;
  }
  else
    if(fit_method == "fmax") {
      index = 0;
      left = 0.3;//0.2
      //      left = left_bin_fmax;
      right = 0.95;//1.
    }
    else {
      cerr << "wrong fit method: " << fit_method << endl;
      exit(-1);
    }
      
  for(Int_t i=hist_data_sum[index]->FindBin(left)/*left_bin_fmax*/; i<right_bin_fmax/*hist_data_sum[index]->FindBin(right)*/; i++)
    {
      //      cout << i << " " << hist_data_sum[1]->GetBinContent(i+1) << endl;
      Double_t diff;
      diff = hist_data_sum[index]->GetBinContent(i+1) - hist_mc_rad_sum[index]->GetBinContent(i+1) - par[0]*hist_mc_sum[index]->GetBinContent(i+1) - (1-par[0])*hist_mc_norad_sum[index]->GetBinContent(i+1);
      Double_t s_d = hist_data_sum[index]->GetBinError(i+1);
      Double_t s_l = hist_mc_rad_sum[index]->GetBinError(i+1);
      Double_t s_q = hist_mc_sum[index]->GetBinError(i+1);
      Double_t s_bg = hist_mc_norad_sum[index]->GetBinError(i+1);
      Double_t denom = 0.;
      if(s_method == "Barlow-Beeston")
	denom = s_d*s_d + s_l*s_l + par[0]*par[0]*s_q*s_q + (1.-par[0])*(1.-par[0])*s_bg*s_bg;
      else
	if(s_method == "Gauss")
	  denom = s_d*s_d;
	else
	  {
	    cerr << "Unknown fit method: " << s_method << ". Exiting" << endl;
	    exit(-1);
	  }
      //cout << "errs: " << i << " " << par[0] << " " << s_d << " " << s_l << " " << s_q << " " << s_bg << " " << diff << " " << denom << endl;	
      //      cout << "bin " << i  << " " << diff << " " << denom << " " << diff*diff/denom << " " << res << endl;
      res += diff*diff/denom;
      ndf++;
    }
  res /= float(ndf-1);
  //  cout << float(hist_data_sum[index]->GetNbinsX() - 1) << endl;
  //  cout << "calling chi2: " << res << endl << endl << endl;
  return res;
}
