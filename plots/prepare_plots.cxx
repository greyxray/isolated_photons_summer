#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include <TH1D.h>
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
void AddAllPeriods(TH1D* h, Int_t histogram_index, TString data_type, TString s_hist);

const Int_t n_files = 11;
const Int_t n_periods = 3;
TFile *file[n_files];

int main(int argc, char *argv[])
{
  gROOT->SetStyle("Plain");
  gStyle->SetTitleBorderSize(1);
  gStyle->SetTitleH(0.08);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleY(0.99);
  gStyle->SetTitleX(0.15);

  file[0] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/data0405e.root");
  file[1] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_bg_norad0405e.root");
  file[2] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_bg_rad0405e.root");

  file[3] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_prph0405e.root");

  file[4] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/data06e.root");
  file[5] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_bg_norad06e.root");
  file[6] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_bg_rad06e.root");

  file[7] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/data0607p.root");
  file[8] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_bg_norad0607p.root");
  file[9] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_bg_rad0607p.root");

  file[10] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_prph06e.root");
  //  file[1] = new TFile("/afs/desy.de/user/z/zhmak/public/oleg/dataall.root");
  cout << "file attached" << endl;

const Int_t n_hist = 16+8 + 3;
const Int_t n_wind = 8+4 + 1;
TString s_hist[n_hist] = 
    {"Photon_with_jet/h_fmax", "Inclusive_Photon/h_incl_phot_fmax", "Photon_with_jet/h_deltaz", "Inclusive_Photon/h_incl_phot_deltaz",
     "Photon_with_jet/h_fmax", "Inclusive_Photon/h_incl_phot_fmax", "Photon_with_jet/h_deltaz", "Inclusive_Photon/h_incl_phot_deltaz",
     "Photon_with_jet/h_fmax", "Inclusive_Photon/h_incl_phot_fmax", "Photon_with_jet/h_deltaz", "Inclusive_Photon/h_incl_phot_deltaz",
     "Photon_with_jet/h_fmax", "Inclusive_Photon/h_incl_phot_fmax", "Photon_with_jet/h_deltaz", "Inclusive_Photon/h_incl_phot_deltaz",
     "Photon_with_jet/h_prph_eta", "Photon_with_jet/h_prph_eta", "Photon_with_jet/h_prph_eta", "Photon_with_jet/h_prph_eta",
     "Inclusive_Photon/h_incl_phot_eta", "Inclusive_Photon/h_incl_phot_eta", "Inclusive_Photon/h_incl_phot_eta", "Inclusive_Photon/h_incl_phot_eta"};
TString s_name[n_hist] = {"h_fmax_data", "h_fmax2_data", "h_deltaz_data", "h_deltaz2_data",
			  "h_fmax_rad", "h_fmax2_rad", "h_deltaz_rad", "h_deltaz2_rad",
			  "h_fmax_norad", "h_fmax2_norad", "h_deltaz_norad", "h_deltaz2_norad",
			  "h_fmax_prph", "h_fmax2_prph", "h_deltaz_prph", "h_deltaz2_prph",
			  "h_eta_data", "h_eta_norad", "h_eta_rad", "h_eta_prph",
			  "h_eta2_data", "h_eta2_norad", "h_eta2_rad", "h_eta2_prph"
};
TString s_xaxis[n_wind] = {"f_{max}", "#delta z", "f_{max}", "#delta z", "f_{max}", "#delta z", "f_{max}", "#delta z", 
			     "#eta_{photon}", "#eta_{photon}",
			   "#eta_{photon}", "#eta_{photon}"
};
TString s_yaxis[n_wind] = {"Events", "Events"};
TString s_title[n_wind] = {"Inclusive photon and photon + jet signal, data",
			     "Inclusive photon and photon + jet signal, data",
			   "Inclusive photon and photon + jet signal, MC HH",
			   "Inclusive photon and photon + jet signal, MC HH",
			   "Inclusive photon and photon + jet signal, MC LL",
			   "Inclusive photon and photon + jet signal, MC LL",
			     "Inclusive photon and photon + jet signal, MC SIGNAL",
			   "Inclusive photon and photon + jet signal, MC SIGNAL",
			   "data", "MC HH", "MC LL", "MC QQ"
};
Double_t hist_xmin[n_wind] = {0., 0., 0., 0., 0., 0., 0., 0., -1., -1., -1., -1.};
Double_t hist_xmax[n_wind] = {1., 1.5, 1., 1.5, 1., 1.5, 1., 1.5, 1., 1., 1., 1.};
Double_t hist_ymin[n_wind] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};
Double_t hist_ymax[n_wind];
Int_t hist_line_width[n_hist] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
				 2, 2, 2, 2, 2, 2, 2, 2};
Int_t hist_line_color[n_hist] = {kBlue, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kBlack,
				 kBlue, kBlue, kBlue, kBlue, kBlack, kBlack, kBlack, kBlack};
Double_t hist_marker_size[n_hist] = {0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7,
				     0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7};
Int_t hist_marker_style[n_hist] = {20, 21, 20, 21, 20, 21, 20, 21, 20, 21, 20, 21, 20, 21, 20, 21,
				   20, 20, 20, 20, 21, 21, 21, 21};
Int_t hist_marker_color[n_hist] = {kBlue, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kBlack, kBlue, kBlack,
				   kBlue, kBlue, kBlue, kBlue, kBlack, kBlack, kBlack, kBlack
};


  
  
  TH1D *hist[n_hist];
  //  TH1D *hist1st[n_hist];
  TH1D *hist_ratio[n_hist];
  for(Int_t i=0; i<n_hist; i++) {
    Int_t index = 0;
    if(i>=0 && i<4)
      index = 0;
    if(i>=4 && i<8)
      index = 1;
    if(i>=8 && i<12)
      index = 2;
    if(i>=12 && i<16)
      index = 3;
    if(i>=16 && i < 24)
      index = i%4;
    cout << "main: cdying to " << file[index]->GetName() << endl;
    file[index]->cd();
    cout << "main: getting " << s_hist[i] << endl;
    hist[i] = (TH1D*)file[index]->Get(s_hist[i])->Clone();
    cout <<"OK" << endl;
    hist[i]->SetName(s_name[i]);
    hist[i]->SetLineWidth(hist_line_width[i]);
    hist[i]->SetLineColor(hist_line_color[i]);
    //    if(i%2 == 0) {
      hist[i]->SetMarkerSize(hist_marker_size[i]);
      hist[i]->SetMarkerStyle(hist_marker_style[i]);
      hist[i]->SetMarkerColor(hist_marker_color[i]);
      //    }
    hist[i]->Sumw2();
  }

  for(Int_t i=16; i<24; i++)
    {
      //      if(!(i==19 || i==23)) {
      cout << "goto " << i << endl; 
      TString s;
      if(i%4 == 0) s = "data";
      if(i%4 == 1) s = "norad";
      if(i%4 == 2) s = "rad";
      if(i%4 == 3) s = "prph";
      AddAllPeriods(hist[i], i, s, s_hist[i]);
      //      }
    }
  cout << "histos succesfully read" << endl;
  for(Int_t i=0; i<8; i++){
    hist[2*i+1]->Scale(hist[2*i]->Integral() / hist[2*i+1]->Integral());
    //    hist[3]->Scale(hist[2]->Integral() / hist[3]->Integral());
  }
  
  for(Int_t i=0; i<16; i++)
    hist[i]->Rebin(10);


  for(Int_t i=16; i<20; i++)
    hist[i]->Rebin(10);
  for(Int_t i=20; i<24; i++)
    hist[i]->Rebin(5);

  for(Int_t i=8; i<16; i++)
    hist[i+8]->Scale(1. / hist[i+8]->Integral());

  for(Int_t i=8; i<16; i++)
    hist[i+8]->Scale(1./hist[i+8]->GetBinWidth(1));


  //  hist[1]->Rebin(10);
  //  hist[2]->Rebin(15);
  //  hist[3]->Rebin(15);

  //
  // find ymax
  //

  hist_ymax[0] = 1.2*hist_maximum(hist, 2);
  hist_ymax[1] = 1.2*hist_maximum(hist, 3, 4);
  hist_ymax[2] = 1.2*hist_maximum(hist, 5, 6);
  hist_ymax[3] = 1.2*hist_maximum(hist, 7, 8);
  hist_ymax[4] = 1.2*hist_maximum(hist, 9, 10);
  hist_ymax[5] = 1.2*hist_maximum(hist, 11, 12);
  hist_ymax[6] = 1.2*hist_maximum(hist, 13, 14);
  hist_ymax[7] = 1.2*hist_maximum(hist, 15, 16);
  hist_ymax[8] = 1.;//*hist_maximum(hist, 20, 20);
  hist_ymax[9] = 1.;//2*hist_maximum(hist, 21, 21);
  hist_ymax[10] = 2.;//2*hist_maximum(hist, 22, 22);
  hist_ymax[11] = 1.;//2*hist_maximum(hist, 23, 23);


  cout << "going into histograms drawing " << endl;
  TH2D *h_window[n_wind];
  TH2D *h_window_ratio[n_wind];
  TF1 *f1 = new TF1("f1", "1.", 0., 1000.);
  f1->SetLineColor(39);
  f1->SetLineWidth(1);
  for(Int_t i=0; i<n_wind; i++) {
    TString s; s.Form("h_window%i", i);
    h_window[i] = new TH2D(s, "", 10, hist_xmin[i], hist_xmax[i], 10, hist_ymin[i], hist_ymax[i]);
    h_window_ratio[i] = new TH2D(s + "_ratio", "", 10, hist_xmin[i], hist_xmax[i], 10, 0., 2.);
  }

  const Int_t n_canv = 5;
  TCanvas* c1[n_canv];
  for(Int_t i=0; i<n_canv; i++) {
    TString s; s.Form("canvas_%i", i);
    c1[i] = new TCanvas(s, s, 800, 800);
  }
  for(Int_t i=0; i<4; i++) {
    c1[i]->Divide(1, 2);
    make_clean_pads(c1[i], 2, 0, 0);
  }
  c1[4]->Divide(2, 2);
  make_clean_pads(c1[4], 4, 0, 0);

  for(Int_t i=0; i<8; i++)
    sign_window(c1[i/2]->GetPad(i%2 + 1), h_window[i], s_xaxis[i], s_yaxis[i], s_title[i], "middle");

  for(Int_t i=8; i<12; i++)
    sign_window(c1[4]->GetPad(i%4 + 1), h_window[i], s_xaxis[i], s_yaxis[i], s_title[i], "middle");

  const Int_t n_legs = n_wind; // :)
  TLegend *leg[n_legs];
  for(Int_t i=0; i<4; i++) {
	leg[2*i] = new TLegend(0.2, 0.6, 0.59, 0.87);
	leg[2*i+1] = new TLegend(0.5, 0.6, 0.86, 0.87);
  }
  for(Int_t i=8; i<12; i++)
    leg[i] = new TLegend(0.3, 0.2, 0.8, 0.5);

  for(Int_t i=0; i<n_legs; i++) {
    leg[i]->SetBorderSize(0);
    leg[i]->SetFillColor(0);
  }
  for(Int_t i=0; i<4; i++) {
    leg[2*i]->AddEntry(hist[0], "f_{max}, Photon + Jet", "l");
    leg[2*i]->AddEntry(hist[1], "f_{max}, Inclusive Photon", "l");
    
    leg[2*i+1]->AddEntry(hist[2], "#delta z, Photon + Jet", "l");
    leg[2*i+1]->AddEntry(hist[3], "#delta z, Inclusive Photon", "l");
  }
  leg[11]->AddEntry(hist[16], "Photon + Jet", "l");
  leg[11]->AddEntry(hist[20], "Inclusive Photon", "l");
  //
  // data
  //
  c1[0]->GetPad(1)->cd();
  h_window[0]->DrawClone();
  hist[0]->DrawClone("E X0 SAME");  
  hist[1]->DrawClone("E X0 SAME"); 
  hist[1]->DrawClone("HIST SAME");  
  //leg[0]->Draw();
  c1[0]->GetPad(2)->cd();
  h_window[1]->DrawClone();
  hist[2]->DrawClone("E X0 SAME");  
  hist[3]->DrawClone("E X0 SAME");  
  hist[3]->DrawClone("HIST SAME");  
  leg[1]->Draw();
  c1[0]->Print("prepare_plots1.eps");
  //
  // mc bg norad
  //
  c1[1]->GetPad(1)->cd();
  h_window[2]->DrawClone();
  hist[4]->DrawClone("E X0 SAME");  
  hist[5]->DrawClone("E X0 SAME");  
  hist[5]->DrawClone("HIST SAME");  
  //leg[2]->Draw();
  c1[1]->GetPad(2)->cd();
  h_window[3]->DrawClone();
  hist[6]->DrawClone("E X0 SAME");  
  hist[7]->DrawClone("E X0 SAME");  
  hist[7]->DrawClone("HIST SAME");  
  leg[3]->Draw();
  c1[1]->Print("prepare_plots2.eps");
  //
  // mc bg rad
  //
  c1[2]->GetPad(1)->cd();
  h_window[4]->DrawClone();
  hist[8]->DrawClone("E X0 SAME");  
  hist[9]->DrawClone("E X0 SAME");  
  hist[9]->DrawClone("HIST SAME");  
  //leg[4]->Draw();
  c1[2]->GetPad(2)->cd();
  h_window[5]->DrawClone();
  hist[10]->DrawClone("E X0 SAME");  
  hist[11]->DrawClone("E X0 SAME");  
  hist[11]->DrawClone("HIST SAME");  
  leg[5]->Draw();
  c1[2]->Print("prepare_plots3.eps");
  //
  // mc signal
  //
  c1[3]->GetPad(1)->cd();
  h_window[6]->DrawClone();
  hist[12]->DrawClone("E X0 SAME");  
  hist[13]->DrawClone("E X0 SAME");  
  hist[13]->DrawClone("HIST SAME");  
  //leg[6]->Draw();
  c1[3]->GetPad(2)->cd();
  h_window[7]->DrawClone();
  hist[14]->DrawClone("E X0 SAME");  
  hist[15]->DrawClone("E X0 SAME");  
  hist[15]->DrawClone("HIST SAME");  
  leg[7]->Draw();
  c1[3]->Print("prepare_plots4.eps");
  //leg[6]->Draw();
  for(Int_t i=8; i<12; i++) {
    c1[4]->GetPad(i%4+1)->cd();
    h_window[i]->DrawClone();
    hist[i+12]->DrawClone("E X0 SAME");  
    hist[i+12]->DrawClone("HIST SAME");  
    hist[i+8]->DrawClone("E X0 SAME");  

  }
  leg[11]->Draw();
  c1[4]->Print("prepare_plots5.eps");

  return 0;
}

void AddAllPeriods(TH1D* h, Int_t histogram_index, TString data_type, TString s_hist){
  cout << "here" << endl;
  Int_t index[2] = {0};
  TH1D* h_temp[2];
  if(data_type == "data") {
    index[0] = 4;
    index[1] = 7;
  }
  else
    if(data_type == "norad") {
      index[0] = 5;
      index[1] = 8;
    }
    else
      if(data_type == "rad") {
	index[0] = 6;
	index[1] = 9;
      }
      else
	if(data_type = "prph") {
	  index[0] = 10;
	}
	else {
	  cerr << "in AddAllHistograms: Wrong data_type: " << data_type << endl;
	  exit(-1);
	}
  if(data_type != "prph")  
    for(Int_t i=0; i<2; i++) {
      cout << "cding to " << file[index[i]]->GetName() << endl;
      file[index[i]]->cd();
      h_temp[i] = (TH1D*)file[index[i]]->Get(s_hist)->Clone();
      h->Add(h_temp[i]);
    }
  else
    for(Int_t i=0; i<1; i++) {
      cout << "cding to " << file[index[i]]->GetName() << endl;
      file[index[i]]->cd();
      h_temp[i] = (TH1D*)file[index[i]]->Get(s_hist)->Clone();
      h->Add(h_temp[i]);
    }

    
}
