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
#include <TPaveStats.h>
#include <TGraphAsymmErrors.h>
#include <TLorentzVector.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TROOT.h>
#include "../../jets_low_q2/plots/plot_style_utils.h"
#include "../inc/constants.h"

void set_hist_atributes(Int_t number, TString name, TString xaxis, TString yaxis, Double_t xmin, Double_t xmax, Double_t ymin, Bool_t logy, Int_t rebin);
void set_hist_atributes_data(Int_t number, TString name, TString title, TString xaxis, TString yaxis, Double_t xmin, Double_t xmax, Double_t ymin, Bool_t logy, Int_t rebin);
void set_hist_atributes_ll(Int_t number, TString name, TString title, TString xaxis, TString yaxis, Double_t xmin, Double_t xmax, Double_t ymin, Bool_t logy, Int_t rebin);
void set_hist_atributes_prph(Int_t number, TString name, TString title, TString xaxis, TString yaxis, Double_t xmin, Double_t xmax, Double_t ymin, Bool_t logy, Int_t rebin);
void set_hist_atributes_bg(Int_t number, TString name, TString title, TString xaxis, TString yaxis, Double_t xmin, Double_t xmax, Double_t ymin, Bool_t logy, Int_t rebin);


const Int_t n_data_files = 3;
const Int_t n_prph_files = 2;
const Int_t n_ll_files = 3;
const Int_t n_bg_files = 3;
TFile *file_data[n_data_files];
TFile *file_prph[n_prph_files];
TFile *file_ll[n_ll_files];
TFile *file_bg[n_bg_files];


const Int_t n_hist_data = 1;
TString s_hist_data[n_hist_data];
TString s_xaxis_data[n_hist_data];
TString s_yaxis_data[n_hist_data];
TString s_title_data[n_hist_data];
Double_t hist_xmin_data[n_hist_data];
Double_t hist_xmax_data[n_hist_data];
Double_t hist_ymin_data[n_hist_data];
Bool_t hist_logy_data[n_hist_data];
Int_t hist_rebin_data[n_hist_data];

const Int_t n_hist_prph = 0;
TString s_hist_prph[n_hist_prph];
TString s_xaxis_prph[n_hist_prph];
TString s_yaxis_prph[n_hist_prph];
TString s_title_prph[n_hist_prph];
Double_t hist_xmin_prph[n_hist_prph];
Double_t hist_xmax_prph[n_hist_prph];
Double_t hist_ymin_prph[n_hist_prph];
Bool_t hist_logy_prph[n_hist_prph];
Int_t hist_rebin_prph[n_hist_prph];

const Int_t n_hist_ll = 0;
TString s_hist_ll[n_hist_ll];
TString s_xaxis_ll[n_hist_ll];
TString s_yaxis_ll[n_hist_ll];
TString s_title_ll[n_hist_ll];
Double_t hist_xmin_ll[n_hist_ll];
Double_t hist_xmax_ll[n_hist_ll];
Double_t hist_ymin_ll[n_hist_ll];
Bool_t hist_logy_ll[n_hist_ll];
Int_t hist_rebin_ll[n_hist_ll];

const Int_t n_hist_bg = 1;
TString s_hist_bg[n_hist_bg];
TString s_xaxis_bg[n_hist_bg];
TString s_yaxis_bg[n_hist_bg];
TString s_title_bg[n_hist_bg];
Double_t hist_xmin_bg[n_hist_bg];
Double_t hist_xmax_bg[n_hist_bg];
Double_t hist_ymin_bg[n_hist_bg];
Bool_t hist_logy_bg[n_hist_bg];
Int_t hist_rebin_bg[n_hist_bg];

const Int_t n_hist_ratio = 1;
int main(int argc, char *argv[])
{
  set_hist_atributes_data(0, "Inclusive_jets/ijet_njets", "Inclusive_jets", "N of jets", "Events", 0, 10, 0.1, kFALSE, 1);
  set_hist_atributes_bg(0, "Inclusive_jets/ijet_njets", "Inclusive_jets", "N of jets", "Events", 0, 10, 0.1, kFALSE, 1);


  gROOT->SetStyle("Plain");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleH(0.08);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleY(0.99);
  gStyle->SetTitleX(0.15);
    
  file_data[0] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/data0405e_m.root");
  file_data[1] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/data06e_m.root");
  file_data[2] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/data0607p_m.root");

  cout << "data files OK" << endl;

  file_bg[0] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_bg_norad0405e_m.root");
  file_bg[1] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_bg_norad06e_m.root");
  file_bg[2] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_bg_norad0607p_m.root");

  file_ll[0] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_bg_rad0405e.root");
  file_ll[1] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_bg_rad06e.root");
  file_ll[2] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_bg_rad0607p.root");

  file_prph[0] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_prph0405e_m.root");
  file_prph[1] = new TFile("/diskmnt/b/kuprash/analyses/prompt_photons/mc_prph06e_m.root");

  TH1D *hist_data[n_hist_data];
  TH1D *hist_prph[n_hist_prph];
  TH1D *hist_ll[n_hist_ll];
  TH1D *hist_bg[n_hist_bg];
  TH1D *hist_ratio[n_hist_ratio];


  for(Int_t i=0; i<n_hist_data; i++)
    {
      file_data[0]->cd();
      cout << "reading "  << i << " ..." << endl;
      hist_data[i] = (TH1D*)file_data[0]->Get(s_hist_data[i])->Clone();
      hist_data[i]->SetName(s_hist_data[i] + "_data");
      cout << "data - OK, " ;
      hist_data[i]->SetMarkerStyle(20);
      hist_data[i]->SetMarkerColor(kBlue);
      //      hist_data[i]->SetLineWidth(1);
    }

  for(Int_t i=0; i<n_hist_bg; i++)
    {
      file_bg[0]->cd();
      cout << "reading "  << i << " ..." << endl;
      hist_bg[i] = (TH1D*)file_bg[0]->Get(s_hist_bg[i])->Clone();
      hist_bg[i]->SetName(s_hist_bg[i] + "_bg");
      cout << "bg - OK, " ;
      hist_bg[i]->SetLineColor(kBlack);
      hist_bg[i]->SetLineWidth(1);
    }

  Double_t int_data0 = hist_data[0]->Integral();
  Double_t int_bg0 = hist_bg[0]->Integral();
  hist_bg[0]->Scale(int_data0/int_bg0);

  hist_ratio[0] = (TH1D*)hist_data[0]->Clone();
  hist_ratio[0]->SetName(hist_data[0]->GetName() + (TString)"ratio");
  for(Int_t i=0; i<hist_ratio[0]->GetNbinsX(); i++) {
    Double_t num = hist_data[0]->GetBinContent(i+1);
    Double_t denom = hist_bg[0]->GetBinContent(i+1);
    hist_ratio[0]->SetBinContent(i+1, double(num)/double(denom));
    cout << "i = " << i << " " << num << " " << denom << " " << num/denom << endl;
    cout << hist_ratio[0]->GetBinContent(i+1) << endl;
    hist_ratio[0]->SetBinError(i+1, 0.);
  }

  //  hist_ratio[0]->Divide(hist_bg[0]);

  TCanvas* c1;
  c1 = new TCanvas("c1", "c1", 800, 600);
  c1->Divide(1, 1);
  make_clean_pads(c1, 1, 0, 0);
  prepare_canvas_for_cross_sec(c1->GetPad(1));

  cout << "canvas ready" << endl;
  TH2D *h_window[n_hist_ratio];
  TH2D *h_window_ratio[n_hist_ratio];
  h_window[0] = new TH2D("w0", "", 10, 0., 10., 10, 0.1, 5.e5);
  h_window_ratio[0] = new TH2D("r0", "", 10, 0., 10., 10, 0.1, 1.2);

  sign_window(c1->GetPad(1)->GetPad(1), h_window[0], s_xaxis_data[0], s_yaxis_data[0], s_title_data[0], "large");
  sign_window(c1->GetPad(1)->GetPad(2), h_window_ratio[0], s_xaxis_data[0], "ratio", "", "large");
  c1->GetPad(1)->GetPad(1)->SetLogy(hist_logy_data[0]);
  cout << "canvas ready 2" << endl;
  TLegend *leg = new TLegend(0.2, 0.75, 0.65, 0.89);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(hist_data[0], "Data", "p");
  leg->AddEntry(hist_bg[0], "Ariadne", "l");

  TF1 *f = new TF1("f1", "1", -10000., 10000.);
  f->SetLineColor(kBlue);
  f->SetLineWidth(1);

  cout << "hello" << endl;
  c1->GetPad(1)->GetPad(1)->cd();
  h_window[0]->DrawClone();    
  hist_bg[0]->DrawClone("E HIST SAME");
  hist_data[0]->DrawClone("E P X0 SAMES");

  cout << "draw legend" << endl;
  leg->DrawClone();
  c1->GetPad(1)->GetPad(2)->cd();
  h_window_ratio[0]->GetYaxis()->SetTitleOffset(0.4);
  h_window_ratio[0]->DrawClone();    
  //  f->DrawClone("SAME");

  for(Int_t i=0; i<hist_ratio[0]->GetNbinsX(); i++) {


    cout << "i = " << i << " " << hist_ratio[0]->GetBinContent(i+1);

  }

  //  hist_ratio[0]->DrawClone("P SAME");


  c1->Print("hjet_data_ariadne.eps");
  return 0;
}

void set_hist_atributes(Int_t number, TString name, TString xaxis, TString yaxis, Double_t xmin, Double_t xmax, Double_t ymin, Bool_t logy, Int_t rebin)
{

}

void set_hist_atributes_data(Int_t number, TString name, TString title, TString xaxis, TString yaxis, Double_t xmin, Double_t xmax, Double_t ymin, Bool_t logy, Int_t rebin)
{
  s_hist_data[number] = name;
  s_xaxis_data[number] = xaxis;
  s_yaxis_data[number] = yaxis;
  s_title_data[number] = title;
  hist_xmin_data[number] = xmin;
  hist_xmax_data[number] = xmax;
  hist_ymin_data[number] = ymin;
  hist_logy_data[number] = logy;
  hist_rebin_data[number] = rebin;
}
void set_hist_atributes_prph(Int_t number, TString name, TString title, TString xaxis, TString yaxis, Double_t xmin, Double_t xmax, Double_t ymin, Bool_t logy, Int_t rebin)
{
  s_hist_prph[number] = name;
  s_xaxis_prph[number] = xaxis;
  s_yaxis_prph[number] = yaxis;
  s_title_prph[number] = title;
  hist_xmin_prph[number] = xmin;
  hist_xmax_prph[number] = xmax;
  hist_ymin_prph[number] = ymin;
  hist_logy_prph[number] = logy;
  hist_rebin_prph[number] = rebin;
}
void set_hist_atributes_ll(Int_t number, TString name, TString title, TString xaxis, TString yaxis, Double_t xmin, Double_t xmax, Double_t ymin, Bool_t logy, Int_t rebin)
{
  s_hist_ll[number] = name;
  s_xaxis_ll[number] = xaxis;
  s_yaxis_ll[number] = yaxis;
  s_title_ll[number] = title;
  hist_xmin_ll[number] = xmin;
  hist_xmax_ll[number] = xmax;
  hist_ymin_ll[number] = ymin;
  hist_logy_ll[number] = logy;
  hist_rebin_ll[number] = rebin;
}
void set_hist_atributes_bg(Int_t number, TString name, TString title, TString xaxis, TString yaxis, Double_t xmin, Double_t xmax, Double_t ymin, Bool_t logy, Int_t rebin)
{
  s_hist_bg[number] = name;
  s_xaxis_bg[number] = xaxis;
  s_yaxis_bg[number] = yaxis;
  s_title_bg[number] = title;
  hist_xmin_bg[number] = xmin;
  hist_xmax_bg[number] = xmax;
  hist_ymin_bg[number] = ymin;
  hist_logy_bg[number] = logy;
  hist_rebin_bg[number] = rebin;
}
