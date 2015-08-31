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


int main(int argc, char *argv[])
{
  gROOT->SetStyle("Plain");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleH(0.08);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleY(0.99);
  gStyle->SetTitleX(0.15);
    
  //    TFile *file1 = new TFile("../data0405e_nocorr.root");
   TFile *file1 = new TFile("../mc_bg0405e_nocorr.root");
  //  TFile *file2 = new TFile("/data/zenith234b/zhmak/Topic/ana_gammajet_new/out/31.08.10_newMC_ddr_mt0_5/dataall.root");
  cout << "file attached" << endl;
  
  const Int_t n_hist = 6;
  TString s_hist[n_hist] = {"h_Q2_el", "h_Q2_da", "h_Q2_da_cell", "h_Q2_jb", "h_Q2_jb_cell", "h_Q2_true"};
  TString s_legend[n_hist] = {"electron method",
			      "Double-Angle (zufos)",
			      "Double-Angle (cells)",
			      "Jacquet-Blondel (zufos)",
			      "Jacquet-Blondel (cells)",
			      "Q^{2} at generated level"
  };
  TH1D *hist[n_hist];

  for(Int_t i=0; i<n_hist; i++)
    {
      file1->cd();
      cout << "reading "  << i << " ..." << endl;
      hist[i] = (TH1D*)file1->Get(s_hist[i])->Clone();
      cout << "1 - OK, " ;
      hist[i]->SetLineColor(i+2);
      hist[i]->SetLineWidth(1);
      //      hist[i]->SetLineStyle(i);
    }
  cout << "histos succesfully read" << endl;

  cout << "before calling hist_maximum: " << endl;
  for(Int_t i=0; i<n_hist; i++)
    cout << i << " " << hist[i]->GetMaximum() << endl;
  Double_t y_max = hist_maximum(hist, n_hist);
  TH2D *h_window;
  h_window = new TH2D("h_window", "", 10, 0.1, 410., 10, 0.9, 1.2 * y_max);

  TCanvas* c1;
  c1 = new TCanvas("c1", "c1", 800, 600);
  c1->Divide(1, 1);
  make_clean_pads(c1, 1, 1, 1);

  sign_window(c1->GetPad(1), h_window, "Q^{2} (GeV^{2})", "Events", "");
  
  TLegend *leg = new TLegend(0.5, 0.7, 0.89, 0.949);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  for(Int_t i=0; i<n_hist; i++)
    {
      leg->AddEntry(hist[i], s_legend[i], "l");
    }
  c1->GetPad(1)->cd();
  c1->GetPad(1)->SetLogy();
  c1->GetPad(1)->SetLogx();
  //  h_window[0]->GetXaxis()->SetRangeUser(0., 35.);
  h_window->DrawClone();
  for(Int_t i=0; i<n_hist; i++)
    hist[i]->DrawClone("SAME");
  leg->Draw();

  c1->Print("Q2.eps");
  c1->Print("Q2.png");
  return 0;
}
