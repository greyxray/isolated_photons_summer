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
TString fit_method = "deltaz";
Bool_t g_include_04p_data = kFALSE;
const Int_t n_data_type = 4;// data norad rad prph
const Int_t n_cross = 6; //et, eta, q2, x, et_jet, eta_jet
const Int_t n_periods = 3; //0405e, 06e, 0607p

Double_t param_eta[number_etabins] = {0.};
Double_t param_err_eta[number_etabins] = {0.};
Double_t chi2_eta[number_etabins] = {0.};
Int_t    dof_eta[number_etabins] = {0};
Int_t    left_eta[number_etabins] = {0};
Int_t    right_eta[number_etabins] = {0};

Double_t param_et[number_etbins] = {0.};
Double_t param_err_et[number_etbins] = {0.};
Double_t chi2_et[number_etbins] = {0.};
Int_t    dof_et[number_etbins] = {0};
Int_t    left_et[number_etbins] = {0};
Int_t    right_et[number_etbins] = {0};

Double_t param_q2[number_Q2bins] = {0.};
Double_t param_err_q2[number_Q2bins] = {0.} ;
Double_t chi2_q2[number_Q2bins] = {0.};
Int_t    dof_q2[number_Q2bins] = {0};
Int_t    left_q2[number_Q2bins] = {0};
Int_t    right_q2[number_Q2bins] = {0};

Double_t param_x[number_xbins] = {0.};
Double_t param_err_x[number_xbins] = {0.}; 
Double_t chi2_x[number_xbins] = {0.};
Int_t    dof_x[number_xbins] = {0};
Int_t    left_x[number_xbins] = {0};
Int_t    right_x[number_xbins] = {0};

Double_t param_et_jet[number_et_jetbins] = {0.};
Double_t param_err_et_jet[number_et_jetbins] = {0.}; 
Double_t chi2_et_jet[number_et_jetbins] = {0.};
Int_t    dof_et_jet[number_et_jetbins] = {0};
Int_t    left_et_jet[number_et_jetbins] = {0};
Int_t    right_et_jet[number_et_jetbins] = {0};

Double_t param_eta_jet[number_eta_jetbins] = {0.};
Double_t param_err_eta_jet[number_eta_jetbins] = {0.}; 
Double_t chi2_eta_jet[number_eta_jetbins] = {0.};
Int_t    dof_eta_jet[number_eta_jetbins] = {0};
Int_t    left_eta_jet[number_eta_jetbins] = {0};
Int_t    right_eta_jet[number_eta_jetbins] = {0};

TFile *f;// = new TFile("cross_sec_histos.root", "recreate", "root file with histohrams");
//f->cd();
#include "hist.c"

Hist hist;
TH1D* hist_data[2];
TH1D* hist_mc[2];
TH1D* hist_mc_rad[2];
TH1D* hist_mc_norad[2];
TH1D* hist_mc_photon[2];
//TH1D* hist_res[2];
Int_t g_index_fmax = 1;
Int_t g_index_deltaz = 0;
void minuitFunctionBarlowBeeston(int& nDim, double* gout, double& result, double par[], int flg);
//void minuitFunctionGauss(int& nDim, double* gout, double& result, double par[], int flg);
Double_t chi2(double* par, Int_t& ndf, Int_t& left, Int_t& right, TString s_method);



int main(int argc, char *argv[])
{
  gROOT->SetStyle("Plain");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleH(0.08);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleY(0.99);
  gStyle->SetTitleX(0.15);
  
  //plot acceptance
  hist.PlotAcceptance();
  hist.PlotPurity();

  
  TFitter* minimizer = new TFitter(1);
  minimizer->SetFCN(minuitFunctionBarlowBeeston);
  {
    double p1 = -1;
    minimizer->ExecuteCommand("SET PRINTOUT",&p1,1);
  }


  //
  // fit in bins of et
  //
  ofstream data_file("data.dat");
  ofstream llqq_file("llqq.dat");
  ofstream hadronic_file("hadronic.dat");
  //  ofstream data_file("data.dat");
  for(Int_t i=0; i<number_etbins; i++)
    {      
      hist_data[0] = (TH1D*)hist.h_deltaz_et_data_sum[i]->Clone(); hist_data[0]->SetName("data");
      hist_mc[0] = (TH1D*)hist.h_deltaz_et_prph_sum[i]->Clone(); hist_mc[0]->SetName("prph");
      hist_mc_rad[0] = (TH1D*)hist.h_deltaz_et_rad_sum[i]->Clone(); hist_mc_rad[0]->SetName("rad");
      hist_mc_norad[0] = (TH1D*)hist.h_deltaz_et_norad_sum[i]->Clone(); hist_mc_norad[0]->SetName("norad");
      hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); hist_mc_photon[0]->SetName("photon");
      hist_mc[0]->Scale(hist.total_luminosity_data/hist.lumi_mc_prph);
      hist_mc_photon[0]->Add(hist_mc[0]);
      

      Double_t n_mc_photon, n_mc_photon_err, n_data, n_data_err;
      
      calc_integral_err(hist_mc_photon[0], n_mc_photon, n_mc_photon_err);
      scale_hist_to_hist_with_err(hist_mc_photon[0], hist_data[0]);
      scale_hist_to_hist_with_err(hist_mc_norad[0], hist_data[0]);

      //      hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/n_mc_photon);

      hist_mc[0]->Scale(hist_data[0]->GetSum()/n_mc_photon);
      hist_mc_rad[0]->Scale(hist_data[0]->GetSum()/n_mc_photon);
      //hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());
      if(i==0)
	for(Int_t j=0; j<hist_mc[0]->GetNbinsX(); j++) {
	  data_file << hist_data[0]->GetBinContent(j+1) << " " << hist_data[0]->GetBinError(j+1) << endl;
	  llqq_file << hist_mc_photon[0]->GetBinContent(j+1) << " " << hist_mc_photon[0]->GetBinError(j+1) << endl;
	  hadronic_file << hist_mc_norad[0]->GetBinContent(j+1) << " " << hist_mc_norad[0]->GetBinError(j+1) << endl;
	}

      minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
      //      minimizer->SetParameter(1, "BETA", 0.7, 0.05, 0., 1.);
      minimizer->ExecuteCommand("SIMPLEX", 0, 0);
      minimizer->ExecuteCommand("MIGRAD",0,0);
      minimizer->ExecuteCommand("HESSE",0,0);
      minimizer->ExecuteCommand("MINOS",0,0);    
      param_et[i] = minimizer->GetParameter(0);
      param_err_et[i] = minimizer->GetParError(0);
      Double_t par[1]; par[0] = param_et[i];
      chi2_et[i] = chi2(par, dof_et[i], left_et[i], right_et[i], "Barlow-Beeston") / dof_et[i];
      left_et[i]++;
      hist.h_deltaz_et_norad_sum[i]->Scale(0.);
      hist.h_deltaz_et_norad_sum[i]->Add(hist_mc_norad[0], 1-param_et[i]);
      hist.h_deltaz_et_photon_sum[i] = (TH1D*)hist.h_deltaz_et_prph_sum[i]->Clone(); 
      hist.h_deltaz_et_photon_sum[i]->SetName((TString)hist.h_deltaz_et_prph_sum[i]->GetName()+"photon");
      hist.h_deltaz_et_photon_sum[i]->Scale(0.);
      hist.h_deltaz_et_photon_sum[i]->Add(hist_mc_photon[0], param_et[i]);
      hist.h_deltaz_et_rad_sum[i]->Scale(0.);
      hist.h_deltaz_et_rad_sum[i]->Add(hist_mc_rad[0], param_et[i]);
      hist.h_deltaz_et_prph_sum[i]->Scale(0.);
      hist.h_deltaz_et_prph_sum[i]->Add(hist_mc[0], param_et[i]);
      hist.h_deltaz_et_res[i]->Scale(0.);//Add(hist.h_deltaz_et_norad_sum[i]);
      hist.h_deltaz_et_res[i]->Add(hist_mc_photon[0], param_et[i]);
      hist.h_deltaz_et_res[i]->Add(hist_mc_norad[0], 1-param_et[i]);
      cout << "After fit in Et bins: n_data = " << hist_data[0]->GetSum()  
	   << ", n_photon = " << hist_mc_photon[0]->GetSum() * param_et[i] 
	   << ", n_bg = " << hist_mc_norad[0]->GetSum() * (1-param_et[i]) 
	   << ", h.n_bg = " << hist.h_deltaz_et_norad_sum[i]->GetSum() 
	   << ", h.n_rad = " << hist.h_deltaz_et_rad_sum[i]->GetSum() 
	   << ", h.n_prph = " << hist.h_deltaz_et_prph_sum[i]->GetSum() 
	   << ", n_res = " << hist.h_deltaz_et_res[i]->GetSum() << endl;
      cout << "par in bin et " << i << ": " << param_et[i] << " +- " << param_err_et[i] << ", chi2/dof = " << chi2_et[i]  << endl;
    }
  data_file.close();
  llqq_file.close();
  hadronic_file.close();
  //
  // fit in bins of eta
  //

  for(Int_t i=0; i<number_etabins; i++)
    {      
      hist_data[0] = (TH1D*)hist.h_deltaz_eta_data_sum[i]->Clone(); hist_data[0]->SetName("data");
      hist_mc[0] = (TH1D*)hist.h_deltaz_eta_prph_sum[i]->Clone(); hist_mc[0]->SetName("prph");
      hist_mc_rad[0] = (TH1D*)hist.h_deltaz_eta_rad_sum[i]->Clone(); hist_mc_rad[0]->SetName("rad");
      hist_mc_norad[0] = (TH1D*)hist.h_deltaz_eta_norad_sum[i]->Clone(); hist_mc_norad[0]->SetName("norad");
      hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); hist_mc_photon[0]->SetName("photon");
      hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
      hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

      hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum());
      //      hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
      hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());
      hist.h_deltaz_eta_prph_sum[i]->Scale((hist.h_deltaz_eta_data_sum[i]->GetSum()-hist.h_deltaz_eta_rad_sum[i]->GetSum())/hist.h_deltaz_eta_prph_sum[i]->GetSum());
      hist.h_deltaz_eta_norad_sum[i]->Scale((hist.h_deltaz_eta_data_sum[i]->GetSum()-hist.h_deltaz_eta_rad_sum[i]->GetSum())/hist.h_deltaz_eta_norad_sum[i]->GetSum());
      minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
      minimizer->ExecuteCommand("SIMPLEX", 0, 0);
      minimizer->ExecuteCommand("MIGRAD",0,0);
      minimizer->ExecuteCommand("HESSE",0,0);
      minimizer->ExecuteCommand("MINOS",0,0);   
      param_eta[i] = minimizer->GetParameter(0);
      param_err_eta[i] = minimizer->GetParError(0);
      Double_t par[1]; par[0] = param_eta[i];
      chi2_eta[i] = chi2(par, dof_eta[i], left_eta[i], right_eta[i], "Barlow-Beeston") / dof_eta[i];
      left_eta[i]++;
      hist.h_deltaz_eta_norad_sum[i]->Scale(1-param_eta[i]);
      hist.h_deltaz_eta_prph_sum[i]->Scale(param_eta[i]);
      hist.h_deltaz_eta_res[i]->Add(hist.h_deltaz_eta_norad_sum[i]);
      hist.h_deltaz_eta_res[i]->Add(hist.h_deltaz_eta_prph_sum[i]);
      cout << "par in bin eta " << i << ": " << param_eta[i] << " +- " << param_err_eta[i] << ", chi2/dof = " << chi2_eta[i]  << endl;
    }

  //
  // fit in bins of q2
  //

  for(Int_t i=0; i<number_Q2bins; i++)
    {      
      hist_data[0] = (TH1D*)hist.h_deltaz_q2_data_sum[i]->Clone(); hist_data[0]->SetName("data");
      hist_mc[0] = (TH1D*)hist.h_deltaz_q2_prph_sum[i]->Clone(); hist_mc[0]->SetName("prph");
      hist_mc_rad[0] = (TH1D*)hist.h_deltaz_q2_rad_sum[i]->Clone(); hist_mc_rad[0]->SetName("rad");
      hist_mc_norad[0] = (TH1D*)hist.h_deltaz_q2_norad_sum[i]->Clone(); hist_mc_norad[0]->SetName("norad");
      hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); hist_mc_photon[0]->SetName("photon");
      hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
      hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

      hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum());
      //      hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
      hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());

      hist.h_deltaz_q2_prph_sum[i]->Scale((hist.h_deltaz_q2_data_sum[i]->GetSum()-hist.h_deltaz_q2_rad_sum[i]->GetSum())/hist.h_deltaz_q2_prph_sum[i]->GetSum());
      hist.h_deltaz_q2_norad_sum[i]->Scale((hist.h_deltaz_q2_data_sum[i]->GetSum()-hist.h_deltaz_q2_rad_sum[i]->GetSum())/hist.h_deltaz_q2_norad_sum[i]->GetSum());
      minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
      minimizer->ExecuteCommand("SIMPLEX", 0, 0);
      minimizer->ExecuteCommand("MIGRAD",0,0);
      minimizer->ExecuteCommand("HESSE",0,0);
      minimizer->ExecuteCommand("MINOS",0,0);    
      param_q2[i] = minimizer->GetParameter(0);
      param_err_q2[i] = minimizer->GetParError(0);
      Double_t par[1]; par[0] = param_q2[i];
      chi2_q2[i] = chi2(par, dof_q2[i], left_q2[i], right_q2[i], "Barlow-Beeston") / dof_q2[i];
      left_q2[i]++;
      hist.h_deltaz_q2_norad_sum[i]->Scale(1-param_q2[i]);
      hist.h_deltaz_q2_prph_sum[i]->Scale(param_q2[i]);
      hist.h_deltaz_q2_res[i]->Add(hist.h_deltaz_q2_norad_sum[i]);
      hist.h_deltaz_q2_res[i]->Add(hist.h_deltaz_q2_prph_sum[i]);
      cout << "par in bin q2 " << i << ": " << param_q2[i] << " +- " << param_err_q2[i] << ", chi2/dof = " << chi2_q2[i] << endl;
    }

  //
  // fit in bins of x
  //

  for(Int_t i=0; i<number_xbins; i++)
    {      
      hist_data[0] = (TH1D*)hist.h_deltaz_x_data_sum[i]->Clone(); hist_data[0]->SetName("data");
      hist_mc[0] = (TH1D*)hist.h_deltaz_x_prph_sum[i]->Clone(); hist_mc[0]->SetName("prph");
      hist_mc_rad[0] = (TH1D*)hist.h_deltaz_x_rad_sum[i]->Clone(); hist_mc_rad[0]->SetName("rad");
      hist_mc_norad[0] = (TH1D*)hist.h_deltaz_x_norad_sum[i]->Clone(); hist_mc_norad[0]->SetName("norad");
      hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); hist_mc_photon[0]->SetName("photon");
      hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
      hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

      hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum());
      //      hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
      hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());

      hist.h_deltaz_x_prph_sum[i]->Scale((hist.h_deltaz_x_data_sum[i]->GetSum()-hist.h_deltaz_x_rad_sum[i]->GetSum())/hist.h_deltaz_x_prph_sum[i]->GetSum());
      hist.h_deltaz_x_norad_sum[i]->Scale((hist.h_deltaz_x_data_sum[i]->GetSum()-hist.h_deltaz_x_rad_sum[i]->GetSum())/hist.h_deltaz_x_norad_sum[i]->GetSum());
      minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
      minimizer->ExecuteCommand("SIMPLEX", 0, 0);
      minimizer->ExecuteCommand("MIGRAD",0,0);
      minimizer->ExecuteCommand("HESSE",0,0);
      minimizer->ExecuteCommand("MINOS",0,0);    
      param_x[i] = minimizer->GetParameter(0);
      param_err_x[i] = minimizer->GetParError(0);
      Double_t par[1]; par[0] = param_x[i];
      chi2_x[i] = chi2(par, dof_x[i], left_x[i], right_x[i], "Barlow-Beeston") / dof_x[i];
      left_x[i]++;
      hist.h_deltaz_x_norad_sum[i]->Scale(1-param_x[i]);
      hist.h_deltaz_x_prph_sum[i]->Scale(param_x[i]);
      hist.h_deltaz_x_res[i]->Add(hist.h_deltaz_x_norad_sum[i]);
      hist.h_deltaz_x_res[i]->Add(hist.h_deltaz_x_prph_sum[i]);
      cout << "par in bin x " << i << ": " << param_x[i] << " +- " << param_err_x[i] << ", chi2/dof = " << chi2_x[i]  << endl;
    }

  //
  // fit in bins of et_jet
  //

  for(Int_t i=0; i<number_et_jetbins; i++)
    {      
      hist_data[0] = (TH1D*)hist.h_deltaz_et_jet_data_sum[i]->Clone(); hist_data[0]->SetName("data");
      hist_mc[0] = (TH1D*)hist.h_deltaz_et_jet_prph_sum[i]->Clone(); hist_mc[0]->SetName("prph");
      hist_mc_rad[0] = (TH1D*)hist.h_deltaz_et_jet_rad_sum[i]->Clone(); hist_mc_rad[0]->SetName("rad");
      hist_mc_norad[0] = (TH1D*)hist.h_deltaz_et_jet_norad_sum[i]->Clone(); hist_mc_norad[0]->SetName("norad");
      hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); hist_mc_photon[0]->SetName("photon");
      hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
      hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

      hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum());
      //      hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
      hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());
      hist.h_deltaz_et_jet_prph_sum[i]->Scale((hist.h_deltaz_et_jet_data_sum[i]->GetSum()-hist.h_deltaz_et_jet_rad_sum[i]->GetSum())/hist.h_deltaz_et_jet_prph_sum[i]->GetSum());
      hist.h_deltaz_et_jet_norad_sum[i]->Scale((hist.h_deltaz_et_jet_data_sum[i]->GetSum()-hist.h_deltaz_et_jet_rad_sum[i]->GetSum())/hist.h_deltaz_et_jet_norad_sum[i]->GetSum());
      minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
      minimizer->ExecuteCommand("SIMPLEX", 0, 0);
      minimizer->ExecuteCommand("MIGRAD",0,0);
      minimizer->ExecuteCommand("HESSE",0,0);
      minimizer->ExecuteCommand("MINOS",0,0);   
      param_et_jet[i] = minimizer->GetParameter(0);
      param_err_et_jet[i] = minimizer->GetParError(0);
      Double_t par[1]; par[0] = param_et_jet[i];
      chi2_et_jet[i] = chi2(par, dof_et_jet[i], left_et_jet[i], right_et_jet[i], "Barlow-Beeston") / dof_et_jet[i];
      left_et_jet[i]++;
      hist.h_deltaz_et_jet_norad_sum[i]->Scale(1-param_et_jet[i]);
      hist.h_deltaz_et_jet_prph_sum[i]->Scale(param_et_jet[i]);
      hist.h_deltaz_et_jet_res[i]->Add(hist.h_deltaz_et_jet_norad_sum[i]);
      hist.h_deltaz_et_jet_res[i]->Add(hist.h_deltaz_et_jet_prph_sum[i]);
      cout << "par in bin et_jet " << i << ": " << param_et_jet[i] << " +- " << param_err_et_jet[i] << ", chi2/dof = " << chi2_et_jet[i]  << endl;
    }

  //
  // fit in bins of eta_jet
  //

  for(Int_t i=0; i<number_eta_jetbins; i++)
    {      
      hist_data[0] = (TH1D*)hist.h_deltaz_eta_jet_data_sum[i]->Clone(); hist_data[0]->SetName("data");
      hist_mc[0] = (TH1D*)hist.h_deltaz_eta_jet_prph_sum[i]->Clone(); hist_mc[0]->SetName("prph");
      hist_mc_rad[0] = (TH1D*)hist.h_deltaz_eta_jet_rad_sum[i]->Clone(); hist_mc_rad[0]->SetName("rad");
      hist_mc_norad[0] = (TH1D*)hist.h_deltaz_eta_jet_norad_sum[i]->Clone(); hist_mc_norad[0]->SetName("norad");
      hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); hist_mc_photon[0]->SetName("photon");
      hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
      hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

      hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum());
      //      hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
      hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());
      hist.h_deltaz_eta_jet_prph_sum[i]->Scale((hist.h_deltaz_eta_jet_data_sum[i]->GetSum()-hist.h_deltaz_eta_jet_rad_sum[i]->GetSum())/hist.h_deltaz_eta_jet_prph_sum[i]->GetSum());
      hist.h_deltaz_eta_jet_norad_sum[i]->Scale((hist.h_deltaz_eta_jet_data_sum[i]->GetSum()-hist.h_deltaz_eta_jet_rad_sum[i]->GetSum())/hist.h_deltaz_eta_jet_norad_sum[i]->GetSum());
      minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
      minimizer->ExecuteCommand("SIMPLEX", 0, 0);
      minimizer->ExecuteCommand("MIGRAD",0,0);
      minimizer->ExecuteCommand("HESSE",0,0);
      minimizer->ExecuteCommand("MINOS",0,0);   
      param_eta_jet[i] = minimizer->GetParameter(0);
      param_err_eta_jet[i] = minimizer->GetParError(0);
      Double_t par[1]; par[0] = param_eta_jet[i];
      chi2_eta_jet[i] = chi2(par, dof_eta_jet[i], left_eta_jet[i], right_eta_jet[i], "Barlow-Beeston") / dof_eta_jet[i];
      left_eta_jet[i]++;
      hist.h_deltaz_eta_jet_norad_sum[i]->Scale(1-param_eta_jet[i]);
      hist.h_deltaz_eta_jet_prph_sum[i]->Scale(param_eta_jet[i]);
      hist.h_deltaz_eta_jet_res[i]->Add(hist.h_deltaz_eta_jet_norad_sum[i]);
      hist.h_deltaz_eta_jet_res[i]->Add(hist.h_deltaz_eta_jet_prph_sum[i]);
      cout << "par in bin eta_jet " << i << ": " << param_eta_jet[i] << " +- " << param_err_eta_jet[i] << ", chi2/dof = " << chi2_eta_jet[i]  << endl;
    }


  hist.PlotFitInBinsOfCrossSec();
  hist.PlotCrossSec(); 
  cout << "return to main" << endl;
  cout << "Finish" << endl;
  f->Write();
  cerr << "Finish" << endl;
  return 0;
}


void minuitFunctionBarlowBeeston(int& nDim, double* gout, double& result, double par[], int flg) 
{
  Int_t ndf;
  Int_t left, right;
  result = chi2(par, ndf, left, right, "Barlow-Beeston");
}

/*
void minuitFunctionGauss(int& nDim, double* gout, double& result, double par[], int flg) 
{
  Int_t ndf;
  Double_t left, right;
  result = chi2(par, ndf, left, right, "Gauss");
}
*/
Double_t chi2(double* par, Int_t& ndf, Int_t& left, Int_t& right, TString s_method)
{
  Double_t res = 0.;
  ndf = 0;
  Int_t index;
  //  Double_t left, right;
  if(fit_method == "deltaz") {
    index = g_index_deltaz;
    left = hist_data[index]->FindBin(0.)-1;//hist_data[index]->FindBin(0.) - 1;
    right = hist_data[index]->FindBin(0.6)+4; // 5;//20;//hist_data[index]->FindBin(0.8);//18;//hist_data[index]->FindBin(0.8); //0.8 / 0.05
  }
  else
    if(fit_method == "fmax") {
      index = g_index_fmax;
      left = 1;//0.2
      right = 20;//1.
    }
    else {
      cerr << "wrong fit method: " << fit_method << endl;
      exit(-1);
    }
      
   for(Int_t i=left/*hist_data_sum[index]->FindBin(left)-1*/; i<right/*hist_data_sum[index]->FindBin(right)*//*GetNbinsX()*/; i++)
     {
      Double_t diff;

      Double_t s_d = hist_data[index]->GetBinError(i+1);
      Double_t s_l = hist_mc_rad[index]->GetBinError(i+1);
      Double_t s_q = hist_mc[index]->GetBinError(i+1);
      Double_t s_ph = hist_mc_photon[index]->GetBinError(i+1);
      Double_t s_bg = hist_mc_norad[index]->GetBinError(i+1);
      //      Double_t s_photon = hist_mc_photon[index]->GetBinError(i+1);

      Double_t v_d = hist_data[index]->GetBinContent(i+1);
      Double_t v_l = hist_mc_rad[index]->GetBinContent(i+1);
      Double_t v_q = hist_mc[index]->GetBinContent(i+1);
      Double_t v_ph = hist_mc_photon[index]->GetBinContent(i+1);
      Double_t v_bg = hist_mc_norad[index]->GetBinContent(i+1);
      //      Double_t v_photon = hist_mc_photon[index]->GetBinContent(i+1);
      //
      // Ian's page
      //
      //      ebb = sdd**2*(param(1)**2*ggn(i)/sgg+(1.-param(1))**2*aan(i)/saa)
      //	edd(i) = sqrt(dd(i) + ebb)
      Double_t dd_i = v_d;
      Double_t sdd = hist_data[index]->GetSum();
      //      dd_i /= sdd;
      //      Double_t ggn_i = v_photon;
      //      Double_t sgg = hist_mc_photon[index]->GetSum();
      //      ggn_i *= sdd/sgg;
      Double_t aan_i = v_bg;
      Double_t saa = hist_mc_norad[index]->GetSum();
      //      aan_i *= sdd/saa;
      //      Double_t ebb = sdd*sdd*(par[0]*par[0]*ggn_i/(sgg*sgg) + (1-par[0])*(1-par[0])*aan_i/(saa*saa));


      // Oleg
      //
      // ====================================================================================================
      //      diff = hist_data[index]->GetBinContent(i+1) - hist_mc_rad[index]->GetBinContent(i+1) - par[0]*hist_mc[index]->GetBinContent(i+1) - (1-par[0])*hist_mc_norad[index]->GetBinContent(i+1);
      //EB:
      diff = hist_data[index]->GetBinContent(i+1) - par[0]*hist_mc_photon[index]->GetBinContent(i+1) - (1-par[0])*hist_mc_norad[index]->GetBinContent(i+1);
      cout << "par[0] = " << par[0] ;
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
	//	denom = s_d*s_d + s_l*s_l + par[0]*par[0]*s_q*s_q + (1.-par[0])*(1.-par[0])*s_bg*s_bg;
	if(denom==0)
	  {
	    cerr << "denom = 0 in cross_sec.cxx. Exiting" << endl;
	    //	    exit(-1);
	  }
	//	denom = (s_d + s_l)*(s_d + s_l) + par[0]*par[0]*s_q*s_q + (1.-par[0])*(1.-par[0])*s_bg*s_bg;
	denom = s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg;
	//	cout << "min: " << i << " " << s_d << " " << s_l << " " << s_q << " " << s_bg << " " << par[0] << " " << denom << endl;
	//	cout << " denom = " << denom << endl;
	cout << "dz " << i << "\t" << "numer=" << diff*diff << "\tdenom=" << denom << "\tndf=" << ndf << " " << diff*diff/denom << endl;
	cout <<i+1 << " yhDat=" << v_d << "\tyh1= " << v_q << "\tyh2= " << v_bg  << "\tyhDatE=" << s_d << "\tyh1E= " << s_q << "\tyh2E= " << s_bg << "\t sl = " << s_l << endl;
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
	if(s_method == "Gauss")
	  denom = s_d*s_d;
	else
	  {
	    cerr << "Unknown fit method: " << s_method << ". Exiting" << endl;
	    exit(-1);
	  }
      ///cout << "errs: " << i << " " << par[0] << " " << s_d << " " << s_l << " " << s_q << " " << s_bg << " " << diff << " " << denom << endl;	
      //      cout << "bin " << i+1  << " " << diff << " " << denom << " " << diff*diff/denom << " " << res << endl;

      if(par[0]!=par[0])
	res += 1000.;
      else
	res += diff*diff/denom;
      ndf++;
    }
   ndf = ndf - 1;
   //   cout << "ndf = " << ndf << endl;
   //  res /= float(ndf-1);
  //  cout << float(hist_data[index]->GetNbinsX() - 1) << endl;
   //   cout << "calling chi2: " << res << endl << endl << endl;
  return res;
}
