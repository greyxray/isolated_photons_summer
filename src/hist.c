#include "hist.h"
//#include "TDirectory.h"
#include "TMath.h"
#include <iostream>
using namespace std;

Hist::Hist()
{
}

Hist::~Hist()
{
}

void Hist::Init(TDirectory** dir)
{
  Double_t q2start = 10.;
  Double_t q2end = 350.;
  zvtx = new TH1D("h_zvtx", "Z vertex", 200, -100., 100.);
  hist_runnr = new TH1D("h_runnr", "Runnr", 15629, 47010, 62639);
  dstw[0] = new TH1D("h_dstw0", "DSTW bits 0-63", 64, 0., 63.);
  dstw[1] = new TH1D("h_dstw1", "DSTW bits 64-127", 64, 64., 127.);
  fltw[0] = new TH1D("h_fltw0", "FLTW bits 0-31", 32, 0., 31.);
  fltw[1] = new TH1D("h_fltw1", "FLTW bits 32-63", 32, 32., 63.);
  for(Int_t i=0; i<6; i++) {
    TString s; s.Form("h_sltw%i", i);
    TString s_title; s_title.Form("SLTW bits %i-%i", i*32, i*32+31);
    sltw[i] = new TH1D(s, s_title, 32, Double_t(i*32), Double_t(i*32+31));
  }
  for(Int_t i=0; i<15; i++) {
    TString s; s.Form("h_tltw%i", i);
    TString s_title; s_title.Form("TLTW bits %i-%i", i*32, i*32+31);
    tltw[i] = new TH1D(s, s_title, 32, Double_t(i*32), Double_t(i*32+31));
  }
  const Int_t n_x_bins = 500;
  Double_t  x_el_binning[n_x_bins+1];
  for(Int_t i=0; i<n_x_bins+1; i++)
    x_el_binning[i] = TMath::Exp(float(i)*11.5/float(n_x_bins))/TMath::Exp(11.5);

  const Int_t n_q2_bins = 200;
  Double_t  q2_binning[n_q2_bins+1];
  for(Int_t i=0; i<n_q2_bins+1; i++) {
    q2_binning[i] = q2start + (q2end-q2start)*TMath::Exp(float(i)*5./float(n_q2_bins))/TMath::Exp(5.);
    //cout << "q2 binning: " << i << " " << q2_binning[i] << endl;
  }
  mccorel_q2_y = new TH2D("h2d_mccorel_q2_y", "x - Q^{2}, y - y", n_q2_bins-1, q2_binning, 200, 0., 1.);
  mccorel_q2_x = new TH2D("h2d_mccorel_q2_x", "x - Q^{2}, y - x", n_q2_bins-1, q2_binning, n_x_bins-1, x_el_binning);
  mccorel_q2_y_noweight = new TH2D("h2d_mccorel_q2_y_noweight", "x - Q^{2}, y - y, no weight", n_q2_bins-1, q2_binning, 200, 0., 1.);
  mccorel_q2_x_noweight = new TH2D("h2d_mccorel_q2_x_noweight", "x - Q^{2}, y - x, no weight", n_q2_bins-1, q2_binning, n_x_bins-1, x_el_binning);

  //
  //for trigger efficiency study
  //
  eta_gamma_tef[0] = new TH1D("h_eta_gamma_trig", "if include trigger selection", 200, -0.7, 0.9);
  eta_gamma_tef[1] = new TH1D("h_eta_gamma_notrig", "without including trigger selection", 200, -0.7, 0.9);
  e_jet_tef[0] = new TH1D("h_e_jet_trig", "if include trigger selection", 200, 0., 100.);
  e_jet_tef[1] = new TH1D("h_e_jet_notrig", "without including trigger selection", 200, 0., 100.);
  q2_tef[0] = new TH1D("h_q2_trig", "if include trigger selection", 200, q2start, q2end);
  q2_tef[1] = new TH1D("h_q2_notrig", "without including trigger selection", 200, q2start, q2end);
  e_electron_tef[0] = new TH1D("h_e_electron_trig", "if include trigger selection", 200, 0., 50.);
  e_electron_tef[1] = new TH1D("h_e_electron_notrig", "without including trigger selection", 200, 0., 50.);
  e_gamma_tef[0] = new TH1D("h_e_gamma_trig", "if include trigger selection", 200, 0., 20.);
  e_gamma_tef[1] = new TH1D("h_e_gamma_notrig", "without including trigger selection", 200, 0., 20.);
  theta_electron_tef[0] = new TH1D("h_theta_electron_trig", "if include trigger selection", 200, 0., TMath::Pi());
  theta_electron_tef[1] = new TH1D("h_theta_electron_notrig", "without including trigger selection", 200, 0., TMath::Pi());

  had_jet_e = new TH1D("h_had_jet_e", "accompying jet transverse energy (gen level)", 100, 0., 50.);
  had_prph_e = new TH1D("h_had_prph_e", "Photon Transverse Energy (gen level)", 20, 0., 20.);
  had_Q2 = new TH1D("h_had_Q2", "Q^{2} (gen level)", 400, q2start, q2end);
  //  had_Q2_inclusive_DIS = new TH1D("had_Q2_inclusive_DIS", "Q^{2} (gen level, incl. DIS)", 400, q2start, q2end);
  had_x = new TH1D("h_had_x", "x Bjorken (gen level)", 100, 2.e-4, 2.e-2);

  //control distributions for isolated photon candidate
  phcand_jet_deltaR = new TH1D("h_jet_deltaR", "distance in eta-phi between jet and particle in jet", 200, 0., 10.);
  phcand_jet_deltaEta = new TH1D("h_jet_deltaEta", "distance in eta between jet and particle in jet", 200, 0., 10.);
  phcand_jet_deltaPhi = new TH1D("h_jet_deltaPhi", "distance in phi between jet and particle in jet", 200, 0., 10.);

  
  //***Cross_Section_histograms
  //
  // for fit fmax and deltaz in different bins and cross sections
  //
  dir[4]->cd();
  //detector leverl
  det_cross_et = new TH1D("h_det_cross_et", "det_cross_et", number_etbins, et_bin);
  det_cross_eta = new TH1D("h_det_cross_eta", "det_cross_eta", number_etabins, eta_bin_crosssec);
  det_cross_Q2 = new TH1D("h_det_cross_Q2", "det_cross_Q2", number_Q2bins, Q2_bin);
  det_cross_x = new TH1D("h_det_cross_x", "det_cross_x", number_xbins, x_bin);
  det_cross_et_jet = new TH1D("h_det_cross_et_jet", "det_cross_et_jet", number_et_jetbins, et_jet_bin);
  det_cross_eta_jet = new TH1D("h_det_cross_eta_jet", "det_cross_eta_jet", number_eta_jetbins, eta_jet_bin);
    det_cross_xgamma = new TH1D("h_det_cross_xgamma", "det_cross_xgamma", number_xgamma_bins, xgamma_bin);
    det_cross_xp = new TH1D("h_det_cross_xp", "det_cross_xp", number_xp_bins, xp_bin);
    det_cross_dphi = new TH1D("h_det_cross_dphi", "det_cross_dphi", number_dphi_bins, dphi_bin);
    det_cross_deta = new TH1D("h_det_cross_deta", "det_cross_deta", number_deta_bins, deta_bin);
    det_cross_dphi_e_ph = new TH1D("h_det_cross_dphi_e_ph", "det_cross_dphi_e_ph", number_dphi_e_ph_bins, dphi_e_ph_bin);
    det_cross_deta_e_ph = new TH1D("h_det_cross_deta_e_ph", "det_cross_deta_e_ph", number_deta_e_ph_bins, deta_e_ph_bin);

  //hadron leverl
  had_cross_et = new TH1D("h_had_cross_et", "had_cross_et", number_etbins, et_bin);
  had_cross_eta = new TH1D("h_had_cross_eta", "had_cross_eta", number_etabins, eta_bin_crosssec);
  had_cross_Q2 = new TH1D("h_had_cross_Q2", "had_cross_Q2", number_Q2bins, Q2_bin);
  had_cross_x = new TH1D("h_had_cross_x", "had_cross_x", number_xbins, x_bin);
  had_cross_et_jet = new TH1D("h_had_cross_et_jet", "had_cross_et_jet", number_et_jetbins, et_jet_bin);
  had_cross_eta_jet = new TH1D("h_had_cross_eta_jet", "had_cross_eta_jet", number_eta_jetbins, eta_jet_bin);
    had_cross_xgamma = new TH1D("h_had_cross_xgamma", "had_cross_xgamma", number_xgamma_bins, xgamma_bin);
    had_cross_xp = new TH1D("h_had_cross_xp", "had_cross_xp", number_xp_bins, xp_bin);
    had_cross_dphi = new TH1D("h_had_cross_dphi", "had_cross_dphi", number_dphi_bins, dphi_bin);
    had_cross_deta = new TH1D("h_had_cross_deta", "had_cross_deta", number_deta_bins, deta_bin);
    had_cross_dphi_e_ph = new TH1D("h_had_cross_dphi_e_ph", "had_cross_dphi_e_ph", number_dphi_e_ph_bins, dphi_e_ph_bin);
    had_cross_deta_e_ph = new TH1D("h_had_cross_deta_e_ph", "had_cross_deta_e_ph", number_deta_e_ph_bins, deta_e_ph_bin);

  //detector and hadron leverl
  hd_cross_et = new TH1D("h_hd_cross_et", "hd_cross_et", number_etbins, et_bin);
  hd_cross_eta = new TH1D("h_hd_cross_eta", "hd_cross_eta", number_etabins, eta_bin_crosssec);
  hd_cross_Q2 = new TH1D("h_hd_cross_Q2", "hd_cross_Q2", number_Q2bins, Q2_bin);
  hd_cross_x = new TH1D("h_hd_cross_x", "hd_cross_x", number_xbins, x_bin);
  hd_cross_et_jet = new TH1D("h_hd_cross_et_jet", "hd_cross_et_jet", number_et_jetbins, et_jet_bin);
  hd_cross_eta_jet = new TH1D("h_hd_cross_eta_jet", "hd_cross_eta_jet", number_eta_jetbins, eta_jet_bin);
    hd_cross_xgamma = new TH1D("h_hd_cross_xgamma", "hd_cross_xgamma", number_xgamma_bins, xgamma_bin);
    hd_cross_xp = new TH1D("h_hd_cross_xp", "hd_cross_xp", number_xp_bins, xp_bin);
    hd_cross_dphi = new TH1D("h_hd_cross_dphi", "hd_cross_dphi", number_dphi_bins, dphi_bin);
    hd_cross_deta = new TH1D("h_hd_cross_deta", "hd_cross_deta", number_deta_bins, deta_bin);
    hd_cross_dphi_e_ph = new TH1D("h_hd_cross_dphi_e_ph", "hd_cross_dphi_e_ph", number_dphi_e_ph_bins, dphi_e_ph_bin);
    hd_cross_deta_e_ph = new TH1D("h_hd_cross_deta_e_ph", "hd_cross_deta_e_ph", number_deta_e_ph_bins, deta_e_ph_bin);
    
  prof_det_cross_et = new TProfile("prof_det_cross_et", "det_cross_et", number_etbins, et_bin);
  prof_det_cross_eta = new TProfile("prof_det_cross_eta", "det_cross_eta", number_etabins, eta_bin_crosssec);
  prof_det_cross_Q2 = new TProfile("prof_det_cross_Q2", "det_cross_Q2", number_Q2bins, Q2_bin);
  prof_det_cross_x = new TProfile("prof_det_cross_x", "det_cross_x", number_xbins, x_bin);
  prof_det_cross_et_jet = new TProfile("prof_det_cross_et_jet", "det_cross_et_jet", number_et_jetbins, et_jet_bin);
  prof_det_cross_eta_jet = new TProfile("prof_det_cross_eta_jet", "det_cross_eta_jet", number_eta_jetbins, eta_jet_bin);
    prof_det_cross_xgamma = new TProfile("prof_det_cross_xgamma", "det_cross_xgamma", number_xgamma_bins, xgamma_bin);
    prof_det_cross_xp = new TProfile("prof_det_cross_xp", "det_cross_xp", number_xp_bins, xp_bin);
    prof_det_cross_dphi = new TProfile("prof_det_cross_dphi", "det_cross_dphi", number_dphi_bins, dphi_bin);
    prof_det_cross_deta = new TProfile("prof_det_cross_deta", "det_cross_deta", number_deta_bins, deta_bin);
    prof_det_cross_dphi_e_ph = new TProfile("prof_det_cross_dphi_e_ph", "det_cross_dphi_e_ph", number_dphi_e_ph_bins, dphi_e_ph_bin);
    prof_det_cross_deta_e_ph = new TProfile("prof_det_cross_deta_e_ph", "det_cross_deta_e_ph", number_deta_e_ph_bins, deta_e_ph_bin);

  prof_had_cross_et = new TProfile("prof_had_cross_et", "had_cross_et", number_etbins, et_bin);
  prof_had_cross_eta = new TProfile("prof_had_cross_eta", "had_cross_eta", number_etabins, eta_bin_crosssec);
  prof_had_cross_Q2 = new TProfile("prof_had_cross_Q2", "had_cross_Q2", number_Q2bins, Q2_bin);
  prof_had_cross_x = new TProfile("prof_had_cross_x", "had_cross_x", number_xbins, x_bin);
  prof_had_cross_et_jet = new TProfile("prof_had_cross_et_jet", "had_cross_et_jet", number_et_jetbins, et_jet_bin);
  prof_had_cross_eta_jet = new TProfile("prof_had_cross_eta_jet", "had_cross_eta_jet", number_eta_jetbins, eta_jet_bin);
    prof_had_cross_xgamma = new TProfile("prof_had_cross_xgamma", "had_cross_xgamma", number_xgamma_bins, xgamma_bin);
    prof_had_cross_xp = new TProfile("prof_had_cross_xp", "had_cross_xp", number_xp_bins, xp_bin);
    prof_had_cross_dphi = new TProfile("prof_had_cross_dphi", "had_cross_dphi", number_dphi_bins, dphi_bin);
    prof_had_cross_deta = new TProfile("prof_had_cross_deta", "had_cross_deta", number_deta_bins, deta_bin);
    prof_had_cross_dphi_e_ph = new TProfile("prof_had_cross_dphi_e_ph", "had_cross_dphi_e_ph", number_dphi_e_ph_bins, dphi_e_ph_bin);
    prof_had_cross_deta_e_ph = new TProfile("prof_had_cross_deta_e_ph", "had_cross_deta_e_ph", number_deta_e_ph_bins, deta_e_ph_bin);

  prof_hd_cross_et = new TProfile("prof_hd_cross_et", "hd_cross_et", number_etbins, et_bin);
  prof_hd_cross_eta = new TProfile("prof_hd_cross_eta", "hd_cross_eta", number_etabins, eta_bin_crosssec);
  prof_hd_cross_Q2 = new TProfile("prof_hd_cross_Q2", "hd_cross_Q2", number_Q2bins, Q2_bin);
  prof_hd_cross_x = new TProfile("prof_hd_cross_x", "hd_cross_x", number_xbins, x_bin);
  prof_hd_cross_et_jet = new TProfile("prof_hd_cross_et_jet", "hd_cross_et_jet", number_et_jetbins, et_jet_bin);
  prof_hd_cross_eta_jet = new TProfile("prof_hd_cross_eta_jet", "hd_cross_eta_jet", number_eta_jetbins, eta_jet_bin);
    prof_hd_cross_xgamma = new TProfile("prof_hd_cross_xgamma", "hd_cross_xgamma", number_xgamma_bins, xgamma_bin);
    prof_hd_cross_xp = new TProfile("prof_hd_cross_xp", "hd_cross_xp", number_xp_bins, xp_bin);
    prof_hd_cross_dphi = new TProfile("prof_hd_cross_dphi", "hd_cross_dphi", number_dphi_bins, dphi_bin);
    prof_hd_cross_deta = new TProfile("prof_hd_cross_deta", "hd_cross_deta", number_deta_bins, deta_bin);
    prof_hd_cross_dphi_e_ph = new TProfile("prof_hd_cross_dphi_e_ph", "hd_cross_dphi_e_ph", number_dphi_e_ph_bins, dphi_e_ph_bin);
    prof_hd_cross_deta_e_ph = new TProfile("prof_hd_cross_deta_e_ph", "hd_cross_deta_e_ph", number_deta_e_ph_bins, deta_e_ph_bin);

  for(Int_t i = 0; i < number_xgamma_bins; i++)
  {
    TString s; 
    TString s_title; 
    s_title.Form("%.0f < x_{gamma} < %.0f", xgamma_bin[i], xgamma_bin[i+1]);

    s.Form("h_fmax_xgamma_%i", i);
    fmax_xgamma[i] = new TH1D(s, s_title, 200, 0., 1.);

    s.Form("h_deltaz_xgamma_%i", i);
    deltaz_xgamma[i] = new TH1D(s, s_title, 300, 0., 1.5);
  }
  for(Int_t i = 0; i < number_xp_bins; i++)
  {
    TString s; 
    TString s_title; 
    s_title.Form("%.0f < x_{p} < %.0f", xp_bin[i], xp_bin[i+1]);

    s.Form("h_fmax_xp_%i", i);
    fmax_xp[i] = new TH1D(s, s_title, 200, 0., 1.);

    s.Form("h_deltaz_xp_%i", i);
    deltaz_xp[i] = new TH1D(s, s_title, 300, 0., 1.5);
  }

  for(Int_t i = 0; i < number_dphi_bins; i++)
  {
    TString s; 
    TString s_title; 
    s_title.Form("%.0f < #Delta#phi < %.0f", dphi_bin[i], dphi_bin[i+1]);

    s.Form("h_fmax_dphi_%i", i);
    fmax_dphi[i] = new TH1D(s, s_title, 200, 0., 1.);

    s.Form("h_deltaz_dphi_%i", i);
    deltaz_dphi[i] = new TH1D(s, s_title, 300, 0., 1.5);
  }

  for(Int_t i = 0; i < number_deta_bins; i++)
  {
    TString s; 
    TString s_title; 
    s_title.Form("%.0f < #Delta#eta < %.0f", deta_bin[i], deta_bin[i+1]);

    s.Form("h_fmax_deta_%i", i);
    fmax_deta[i] = new TH1D(s, s_title, 200, 0., 1.);

    s.Form("h_deltaz_deta_%i", i);
    deltaz_deta[i] = new TH1D(s, s_title, 300, 0., 1.5);
  }

  for(Int_t i = 0; i < number_dphi_e_ph_bins; i++)
  {
    TString s; 
    TString s_title; 
    s_title.Form("%.0f < #Delta#phi_{e, #gamma} < %.0f", dphi_e_ph_bin[i], dphi_e_ph_bin[i+1]);

    s.Form("h_fmax_dphi_e_ph_%i", i);
    fmax_dphi_e_ph[i] = new TH1D(s, s_title, 200, 0., 1.);

    s.Form("h_deltaz_dphi_e_ph_%i", i);
    deltaz_dphi_e_ph[i] = new TH1D(s, s_title, 300, 0., 1.5);
  }
  for(Int_t i = 0; i < number_deta_e_ph_bins; i++)
  {
    TString s; 
    TString s_title; 
    s_title.Form("%.0f < #Delta#eta_{e, #gamma} < %.0f", deta_e_ph_bin[i], deta_e_ph_bin[i+1]);

    s.Form("h_fmax_deta_e_ph_%i", i);
    fmax_deta_e_ph[i] = new TH1D(s, s_title, 200, 0., 1.);

    s.Form("h_deltaz_deta_e_ph_%i", i);
    deltaz_deta_e_ph[i] = new TH1D(s, s_title, 300, 0., 1.5);
  }

  //fmax and delta_z per E_{t,\gamma} bins  //per == in different
  for(Int_t i = 0; i < number_etbins; i++)
    {
      TString s; 
      TString s_title; 
      s_title.Form("%.0f < E_{T, photon} < %.0f", et_bin[i], et_bin[i+1]);

      s.Form("h_fmax_et_%i", i);
      fmax_et[i] = new TH1D(s, s_title, 200, 0., 1.);

      s.Form("h_deltaz_et_%i", i);
      deltaz_et[i] = new TH1D(s, s_title, 300, 0., 1.5);
    }

  //fmax and delta_z per Q^{2} bins  //per == in different
  for(Int_t i=0; i<number_Q2bins; i++)
    {
      TString s; s.Form("h_fmax_q2_%i", i);
      TString s_title; s_title.Form("%.0f < Q^{2} < %.0f", Q2_bin[i], Q2_bin[i+1]);
      fmax_q2[i] = new TH1D(s, s_title, 200, 0., 1.);
      s.Form("h_deltaz_q2_%i", i);
      deltaz_q2[i] = new TH1D(s, s_title, 300, 0., 1.5);
    }
  
  //fmax and delta_z per x bins  //per == in different
  for(Int_t i=0; i<number_xbins; i++)
    {
      TString s; s.Form("h_fmax_x_%i", i);
      TString s_title; s_title.Form("%.5f < x < %.5f", x_bin[i], x_bin[i+1]);
      fmax_x[i] = new TH1D(s, s_title, 200, 0., 1.);
      s.Form("h_deltaz_x_%i", i);
      deltaz_x[i] = new TH1D(s, s_title, 300, 0., 1.5);
    }
  
  //fmax and delta_z per #eta_{photon} bins  //per == in different
  for(Int_t i=0; i<number_etabins; i++)
    {
      TString s; s.Form("h_fmax_eta_%i", i);
      TString s_title; s_title.Form("%.2f < #eta_{photon} < %.2f", eta_bin[i], eta_bin[i+1]);
      fmax_eta[i] = new TH1D(s, s_title, 200, 0., 1.);
      s.Form("h_deltaz_eta_%i", i);
      deltaz_eta[i] = new TH1D(s, s_title, 300, 0., 1.5);
    }
  
  //fmax and delta_z per E_{T, jet} bins  //per == in different
  for(Int_t i=0; i<number_et_jetbins; i++)
    {
      TString s; s.Form("h_fmax_et_jet_%i", i);
      TString s_title; s_title.Form("%.2f < E_{T, jet} < %.2f", et_jet_bin[i], et_jet_bin[i+1]);
      fmax_et_jet[i] = new TH1D(s, s_title, 200, 0., 1.);
      s.Form("h_deltaz_et_jet_%i", i);
      deltaz_et_jet[i] = new TH1D(s, s_title, 300, 0., 1.5);
    }
  
  //fmax and delta_z per #eta_{jet} bins  //per == in different
  for(Int_t i=0; i<number_eta_jetbins; i++)
    {
      TString s; s.Form("h_fmax_eta_jet_%i", i);
      TString s_title; s_title.Form("%.2f < #eta_{jet} < %.2f", eta_jet_bin[i], eta_jet_bin[i+1]);
      fmax_eta_jet[i] = new TH1D(s, s_title, 200, 0., 1.);
      s.Form("h_deltaz_eta_jet_%i", i);
      deltaz_eta_jet[i] = new TH1D(s, s_title, 300, 0., 1.5);
    }

  //***Photon_with_jet
  //control distributions photon + jet
  dir[2]->cd();
  fmax = new TH1D("h_fmax", "f_{max}", 200, 0., 1.);
  deltaz = new TH1D("h_deltaz", "#delta z", 300, 0., 1.5);
  fmax_deltaz = new TH2D("h2d_fmax_deltaz", "f_{max} vs #delta z", 200, 0., 1., 300, 0., 1.5);
  phjet_electron_theta = new TH1D("h_phjet_electron_theta", "#theta_{electron}", 200, 130., 180.);
  phjet_electron_phi = new TH1D("h_phjet_electron_phi", "#phi_{electron}", 200, -2.1*TMath::Pi(), 2.1*TMath::Pi());
  phjet_electron_e = new TH1D("h_phjet_electron_e", "E_{electron}", 200, 9., 35.);
  phjet_electron_e_corr_burkard = new TH1D("h_phjet_electron_e_corr_burkard", "E_{electron, corr.}", 200, 9., 35.);
  phjet_electron_probability = new TH1D("h_phjet_electron_probability", "Sinistra probability", 200, 0.89, 1.);
  prph_energy = new TH1D("h_prph_energy", "Photon Transverse Energy", 200, 3., 16.);
  prph_eta = new TH1D("h_prph_eta", "Photon Pseudorapidity", 180, -0.8, 1.0);
  prph_phi = new TH1D("h_prph_phi", "Photon #phi", 200, -2.1*TMath::Pi(), 2.1*TMath::Pi());
  prph_jet_energy_frac = new TH1D("h_prph_jet_energy_frac", "fraction of jet energy carried by photon", 200, 0.89, 1.01);
  prph_cell_energy_frac = new TH1D("h_prph_cell_energy_frac", "ratio of energy of most energetic cell to photon energy", 200, 0.89, 1.01);
  comp_jet_e = new TH1D("h_comp_jet_e", "accompanying jet transverse energy", 500, 0., 50.);
  comp_prph_e = new TH1D("h_comp_prph_e", "Photon Transverse Energy", 20, 0., 20.);
  comp_Q2 = new TH1D("h_comp_Q2", "Q2 obtained from Sinistra electron", 400, q2start, q2end);
  comp_x = new TH1D("h_comp_x", "x Bjorken", n_x_bins, x_el_binning);
  comp_y = new TH1D("h_comp_y", "y_el", 200, 0., 1.);  
  comp_y_da = new TH1D("h_comp_y_da", "y_da", 200, 0., 1.);  
  comp_y_jb = new TH1D("h_comp_y_jb", "y_jb", 200, 0., 1.);  
  comp_y_norew = new TH1D("h_comp_y_norew", "y_el_norew", 200, 0., 1.);  
  comp_y_da_norew = new TH1D("h_comp_y_da_norew", "y_da_norew", 200, 0., 1.);  
  comp_y_jb_norew = new TH1D("h_comp_y_jb_norew", "y_jb_norew", 200, 0., 1.);  
  comp_s = new TH1D("h_comp_s", "s", 200, 220., 420.);
  
          /*New Stydies Variables*/
          x_gamma_unmarged = new TH1D("h_x_gamma_unmarged", "x_{#gamma} variable", 120, 0., 1.2);
          x_gamma = new TH1D("h_x_gamma", "x_{#gamma} variable", number_xgamma_bins, xgamma_bin);
          x_gamma_exp = new TH1D("h_x_gamma_exp", "x_{#gamma} variable", number_xgamma_bins, xgamma_bin);
          x_gamma_diff = new TH1D("h_x_gamma_diff", "x_{#gamma} variable", 200, -1.1, 1.1);

          x_pomeron_unmarged = new TH1D("h_x_pomeron_unmarged", "x_{#P} variable", 300, 0., 0.03);
          x_pomeron = new TH1D("h_x_pomeron", "x_{#P} variable", number_xp_bins, xp_bin);
          x_pomeron_exp = new TH1D("h_x_pomeron_exp", "x_{#P} variable", number_xp_bins, xp_bin);
          x_pomeron_diff = new TH1D("h_x_pomeron_diff", "x_{P} variable", 200, -0.1, 0.1);
          
          phjet_deta_unmarged = new TH1D("h_phjet_deta_unmarged", "#eta_{jet} - #eta_{photon}", 200, -7., 7.);
          phjet_deta = new TH1D("h_phjet_deta", "#eta_{jet} - #eta_{photon}", number_deta_bins, deta_bin);
          phjet_dphi_unmarged = new TH1D("h_phjet_dphi_unmarged", "#phi_{jet} - #phi_{photon}", 1000, 0, 180);
          phjet_dphi = new TH1D("h_phjet_dphi", "#phi_{jet} - #phi_{photon}", number_dphi_bins, dphi_bin);
          
          phjet_dphi_el_ph_true = new TH1D("h_phjet_dphi_el_ph_true", "#phi_{el} - #phi_{photon}", number_dphi_e_ph_bins, dphi_e_ph_bin);//merged bins
          phjet_dphi_el_ph_true_unmerged = new TH1D("h_phjet_dphi_el_ph_true_unmerged", "#phi_{el} - #phi_{photon}", 200, -0.5, 3.5);//many unmerged bins
          phjet_deta_el_ph_true = new TH1D("h_phjet_deta_el_ph_true", "#eta_{el} - #eta_{photon}", number_deta_e_ph_bins, deta_e_ph_bin);//merged bins
          phjet_deta_el_ph_true_unmerged = new TH1D("h_phjet_deta_el_ph_true_unmerged", "#eta_{el} - #eta_{photon}", 200, -7., 7.);//many unmerged bins
          
          phjet_deta_el_ph = new TH1D("h_phjet_deta_el_ph", "#eta_{el} - #eta_{photon}", 200, -7., 7.);
          phjet_dphi_el_ph = new TH1D("h_phjet_dphi_el_ph", "#phi_{el} - #phi_{photon}", 200, -0.5, 3.5);

  phjet_dphi_deta = new TH2D("h2d_phjet_dphi_deta", "#Delta #eta vs. #Delta #phi", 200, -0.5, 3.5, 200, -7., 7.);
  phjet_jet_et = new TH1D("h_phjet_jet_et", "Accomp. jet transverse energy", 200, 0., 50.);
  phjet_jet_eta = new TH1D("h_phjet_jet_eta", "Accomp. jet eta", 200, -1.6, 1.9);
  phjet_jet_phi = new TH1D("h_phjet_jet_phi", "Accomp. jet phi", 200, -3.5, 3.5);
  
  phjet_deta_el_jet = new TH1D("h_phjet_deta_el_jet", "#eta_{el} - #eta_{jet}", 200, -7., 7.);
  phjet_dphi_el_jet = new TH1D("h_phjet_dphi_el_jet", "#phi_{el} - #phi_{jet}", 200, -0.5, 3.5);

  et_jet_photon_ratio = new TH1D("h_et_jet_photon_ratio", "E_{T, jet} / E_{T, photon}", 200, 0., 20.);
  h2d_et_jet_et_photon = new TH2D("h2d_et_jet_et_photon", "x - E_{T, jet}, y - E_{T, photon}", 200, 0., 60., 200, 0., 20.);
  et_3system_event_ratio = new TH1D("h_et_3system_event_ratio", "(E_{T, #gamma} + E_{T, jet} + E_{T, electron}) / E_{T, event}", 200, 0., 1.2);
  h2d_phijet_phigamma = new TH2D("h2d_phijet_phigamma", "x - #phi_{jet}, y - #phi_{photon}", 200, -3.2, 3.2, 200, -3.2, 3.2);
  h2d_dphijet_dphigamma = new TH2D("h2d_dphijet_dphigamma", "x - #phi_{jet}-#phi_{electron}, y - #phi_{photon}-#phi_{electron}", 200, -0.5, 3.5, 200, -0.5, 3.5);
  h2d_dphijet_dphigamma_sharp = new TH2D("h2d_dphijet_dphigamma_sharp", "x - #phi_{jet}-#phi_{electron}, y - #phi_{photon}-#phi_{electron}", 200, -0.1, 3.2, 200, -0.1, 3.2);
  phjet_cal_empz  = new TH1D("h_phjet_cal_empz", "E-p_{z} from Calorimeter information", 200, 30., 70.);
  phjet_zufo_empz = new TH1D("h_phjet_zufo_empz", "E-p_{z} from zufos", 200, 30., 70.);
  phjet_zvtx = new TH1D("h_phjet_zvtx", "Z_{vtx}", 200, -50., 50.);
  h2d_jet_npart_et = new TH2D("h2d_jet_npart_et", "x - # of particles in jet, y - jet transverse energy", 35, 0., 35., 35, 0., 35.);
  for(Int_t i=0; i<4; i++) {
    TString s; s.Form("h_phjet_photon_sincand_dr_%i", i);
    TString s1; s1.Form("dr between photon and %ith sinistra candidate", i);
    phjet_photon_sincand_dr[i] = new TH1D(s, s1, 100, 0., 5.);
  }
  phjet2d_photon_sincand_dr_nr = new TH2D("h2d_phjet_photon_sincand_dr_nr", "x - number of closest sincand; y - dr", 5, -1., 4., 100, 0., 5.);
  phjet_q2_dz_gt_035 = new TH1D("h_phjet_q2_dz_gt_035", "Q^{2} for events with dz > 0.35", 400, q2start, q2end);
  phjet_q2_dz_lt_035 = new TH1D("h_phjet_q2_dz_lt_035", "Q^{2} for events with dz < 0.35", 400, q2start, q2end);
  phjet_q2_dz_full = new TH1D("h_phjet_q2_dz_full", "Q^{2} for all events", 400, q2start, q2end);
  phjet_y_dz_gt_035 = new TH1D("h_phjet_y_dz_gt_035", "y for events with dz > 0.35", 400, 0, 1);
  phjet_y_dz_lt_035 = new TH1D("h_phjet_y_dz_lt_035", "y for events with dz < 0.35", 400, 0, 1);
  phjet_y_dz_full = new TH1D("h_phjet_y_dz_full", "y for all events", 400, 0, 1);
  phjet_etaph_dz_gt_035 = new TH1D("h_phjet_etaph_dz_gt_035", "#eta^{#gamma} for events with dz > 0.35", 400, -0.7, 0.9);
  phjet_etaph_dz_lt_035 = new TH1D("h_phjet_etaph_dz_lt_035", "#eta^{#gamma} for events with dz < 0.35", 400, -0.7, 0.9);
  phjet_etaph_dz_full = new TH1D("h_phjet_etaph_dz_full", "#eta^{#gamma} for all events", 400, -0.7, 0.9);
  phjet_etph_dz_gt_035 = new TH1D("h_phjet_etph_dz_gt_035", "E^{#gamma}_{T} for events with dz > 0.35", 400, 4, 25);
  phjet_etph_dz_lt_035 = new TH1D("h_phjet_etph_dz_lt_035", "E^{#gamma}_{T} for events with dz < 0.35", 400, 4, 25);
  phjet_etph_dz_full = new TH1D("h_phjet_etph_dz_full", "E^{#gamma}_{T} for all events", 400, 4, 25);
  phjet_eph_dz_gt_035 = new TH1D("h_phjet_eph_dz_gt_035", "E^{#gamma} for events with dz > 0.35", 400, 4, 25);
  phjet_eph_dz_lt_035 = new TH1D("h_phjet_eph_dz_lt_035", "E^{#gamma} for events with dz < 0.35", 400, 4, 25);
  phjet_eph_dz_full = new TH1D("h_phjet_eph_dz_full", "E^{#gamma} for all events", 400, 4, 25);
  phjet_eel_dz_gt_035 = new TH1D("h_phjet_eel_dz_gt_035", "E^{el} for events with dz > 0.35", 400, 10, 30);
  phjet_eel_dz_lt_035 = new TH1D("h_phjet_eel_dz_lt_035", "E^{el} for events with dz < 0.35", 400, 10, 30);
  phjet_eel_dz_full = new TH1D("h_phjet_eel_dz_full", "E^{el} for all events", 400, 10, 30);

  phjet_y_y_gt_05 = new TH1D("phjet_y_y_gt_05", "y for y > 0.5", 50, 10., 30.);
  phjet_y_y_lt_05 = new TH1D("phjet_y_y_lt_05", "y for y < 0.5", 50, 10., 30.);
  phjet_eph = new TH1D("phjet_eph", "photon cand energy", 50, 0, 20); 
  phjet_eph->Sumw2();
  phjet_eel_y_gt_05 = new TH1D("phjet_eel_y_gt_05", "E^{el} for y > 0.5", 50, 10., 30.);
  phjet_eel_y_lt_05 = new TH1D("phjet_eel_y_lt_05", "E^{el} for y < 0.5", 50, 10., 30.);
  phjet_phiph_phij_y_gt_05 = new TH1D("phjet_phiph_phij_y_gt_05", "phiph - phijet for y > 0.5", 50, 0., 3.2);
  phjet_phiph_phij_y_lt_05 = new TH1D("phjet_phiph_phij_y_lt_05", "phiph - phijet for y < 0.5", 50, 0., 3.2);
  phjet_thetael_y_gt_05 = new TH1D("phjet_thetael_y_gt_05", "#theta^{el} for y > 0.5", 50, -2.1*TMath::Pi(), 2.1*TMath::Pi());
  phjet_thetael_y_lt_05 = new TH1D("phjet_thetael_y_lt_05", "#theta^{el} for y < 0.5", 50, -2.1*TMath::Pi(), 2.1*TMath::Pi());
  phjet_etaph_y_gt_05 = new TH1D("phjet_etaph_y_gt_05", "#eta^{#gamma} for y > 0.5", 50, -0.7, 0.9);
  phjet_etaph_y_lt_05 = new TH1D("phjet_etaph_y_lt_05", "#eta^{#gamma} for y < 0.5", 50, -0.7, 0.9);
  phjet_etph_y_gt_05 = new TH1D("phjet_etph_y_gt_05", "E^{#gamma} for y > 0.5", 50, 4., 15.);
  phjet_etph_y_lt_05 = new TH1D("phjet_etph_y_lt_05", "E^{#gamma} for y < 0.5", 50, 4., 15.);
  phjet_dr_track = new TH1D("phjet_dr_track", "#DELTA R_{track}", 100, 0., 5.);

  h2d_phot_et_true_det = new TH2D("h2d_phot_et_true_det", "X - true E_{T,#gamma}; Y - det E_{T,#gamma}", 100, 0., 20., 100, 0., 20.);
  h2d_phot_eta_true_det = new TH2D("h2d_phot_eta_true_det", "X - true #eta_{#gamma}; Y - det #eta_{#gamma}", 100, -3., 3., 100, -3., 3.);;
  h2d_phot_phi_true_det = new TH2D("h2d_phot_phi_true_det", "X - true #phi_{#gamma}; Y - det #phi_{#gamma}", 100, -4., 4., 100, -4., 4.);;
  h2d_corr_accjet_et_true_det = new TH2D("h2d_corr_accjet_et_true_det", "X - true E_{T,jet}; Y - det E_{T,jet}^{corr}", 100, 0., 40., 100, 0., 40.);;
  h2d_corr_accjet_eta_true_det = new TH2D("h2d_corr_accjet_eta_true_det", "X - true #eta_{jet}; Y - det #eta_{jet}^{corr}", 100, -3., 3., 100, -3., 3.);;
  h2d_corr_accjet_phi_true_det = new TH2D("h2d_corr_accjet_phi_true_det", "X - true #phi_{jet}; Y - det #phi_{jet}^{corr}", 100, -4., 4., 100, -4., 4.);;
  h2d_uncorr_accjet_et_true_det = new TH2D("h2d_uncorr_accjet_et_true_det", "X - true E_{T,jet}^{uncorr}; Y - det E_{T,jet}^{uncorr}", 100, 0., 40., 100, 0., 40.);;
  h2d_uncorr_accjet_eta_true_det = new TH2D("h2d_uncorr_accjet_eta_true_det", "X - true #eta_{jet}; Y - det #eta_{jet}", 100, -3., 3., 100, -3., 3.);;
  h2d_uncorr_accjet_phi_true_det = new TH2D("h2d_uncorr_accjet_phi_true_det", "X - true #phi_{jet}; Y - det #phi_{jet}", 100, -4., 4., 100, -4., 4.);;

  //***Inclusove_Photon
  dir[3]->cd();
  //control distributions inclusive photon
  incl_phot_fmax = new TH1D("h_incl_phot_fmax", "f_{max}", 200, 0., 1.);
  incl_phot_deltaz = new TH1D("h_incl_phot_deltaz", "#delta z", 300, 0., 1.5);
  incl_phot_elphot_dphi = new TH1D("h_incl_phot_elphot_dphi", "#phi_{photon} - #phi_{electron}", 200, -0.5, 3.5);
  incl_phot_elphot_deta = new TH1D("h_incl_phot_elphot_deta", "#eta_{photon} - #eta_{electron}", 200, -7., 7.);
  incl_phot_phi = new TH1D("h_incl_phot_phi", "#phi_{photon}", 200, -3.2, 3.2);
  incl_phot_eta = new TH1D("h_incl_phot_eta", "#eta_{photon}", 180, -0.8, 1.0);
  //
  //control distributions inclusive DIS
  //
  dir[0]->cd();
  dis_electron_theta = new TH1D("h_dis_electron_theta", "#theta_{electron}", 200, 130., 180.);
  dis_electron_e = new TH1D("h_dis_electron_e", "E_{electron}", 200, 9., 60.);
  dis_electron_probability = new TH1D("h_dis_electron_probability", "Sinistra probability", 200, 0.89, 1.);
  dis_Q2 = new TH1D("h_Q2", "Q^{2}", 400, q2start, q2end);
  dis_Q2_el = new TH1D("h_Q2_el", "electron method", 400, q2start, q2end);
  dis_Q2_da = new TH1D("h_Q2_da", "double angle method (zufos)", 400, q2start, q2end);
  dis_Q2_da_cell = new TH1D("h_Q2_da_cell", "double angle method (cells)", 400, q2start, q2end);
  dis_Q2_jb = new TH1D("h_Q2_jb", "Jacket-Blondel method (zufos)", 400, q2start, q2end);
  dis_Q2_jb_cell = new TH1D("h_Q2_jb_cell", "Jacket-Blondel method (cells)", 400, q2start, q2end);
  dis_Q2_true = new TH1D("h_Q2_true", "generated level", 400, q2start, q2end);
  dis_x_true = new TH1D("h_x_true", "generated level", 500, 0., 1.);
  dis_y_true = new TH1D("h_y_true", "generated level", 200, 0., 1.);
  dis_electron_e_true = new TH1D("h_dis_electron_e_true", "E_{electron}, generated level", 200, 9., 60.);
  dis_electron_theta_true = new TH1D("h_dis_electron_theta_true", "#theta_{electron}, generated level", 200, 130., 180.);
  dis_Q2_x = new TH2D("h2d_Q2_x", "Q^{2} vs x", 200, q2start, q2end, 200, 2.e-5, 2.e-1);
  dis_elec_zufo_dr_min = new TH1D("h_elec_zufo_dr_min", "distance in #eta,#phi between electron and closest zufo", 200, 0., 1.);
  dis_elec_zufo_de_min = new TH1D("h_elec_zufo_de_min", "#Delta E of electron and closest zufo", 200, -5., 5.);
  dis_zufos_near_electron = new TH1D("h_zufos_near_electron", "number of zufos inside cone with r=0.2 near electron", 200, 0., 10.);
  dis_zvtx = new TH1D("h_zvtx", "Z_{vtx}", 200, -50., 50.);
  dis_n_vtx_tracks = new TH1D("h_n_vtx_tracks", "Num. of vertex tracks", 200, 0., 50.);
  dis_cal_empz  = new TH1D("h_cal_empz", "E-p_{z} from Calorimeter information", 200, 30., 70.);
  dis_zufo_empz = new TH1D("h_zufo_empz", "E-p_{z} from zufos", 200, 30., 70.);
  dis_pt_sqrtet = new TH1D("h_pt_sqrtet", "P_{T, event}/#sqrt{E_{T, event}}", 200, 0., 20.);


  dis_x_el_log = new TH1D("h_x_el_log", "x_{el}", 500, x_el_binning);
  dis_x_el = new TH1D("h_x_el", "x_{el}", 500, 0., 1.);
  dis_y_el = new TH1D("h_y_el", "y_{el}", 200, 0., 1.);
  dis_siyjb = new TH1D("h_siyjb", "Siyjb (Orange)", 120, 0., 1.2);
  dis_siyjb_cell = new TH1D("h_siyjb_cell", "Siyjb_cell (Orange)", 120, 0., 1.2);
  dis_handmade_yjb = new TH1D("h_handmade_yjb", "yjb (handmade)", 120, 0., 1.2);
  dis_px_event = new TH1D("h_dis_px_event", "P_{x} of event (zufos)", 100, -50., 50.);
  dis_py_event = new TH1D("h_dis_py_event", "P_{y} of event (zufos)", 100, -50., 50.);
  dis_pz_event = new TH1D("h_dis_pz_event", "P_{z} of event (zufos)", 100, -100., 800.);
  dis_pt_event = new TH1D("h_dis_pt_event", "P_{T} of event (zufos)", 100, 0., 200.);
  dis_e_event = new TH1D("h_dis_e_event", "E of event", 100, 0., 1000.);
  dis_et_event = new TH1D("h_dis_et_event", "E_{T} of event", 100, 0., 300.);
  dis_n_zufos = new TH1D("h_dis_n_zufos", "N_{zufos}", 100, 0., 200.);
  dis_emc = new TH1D("h_dis_emc", "EMC Energy", 100, 0., 600.);
  dis_had = new TH1D("h_dis_had", "HAD Energy", 100, 0., 600.);
  dis_cal = new TH1D("h_dis_cal", "HAD Energy", 100, 0., 1000.);
  dis_had_tot_ratio = new TH1D("h_dis_had_tot_ratio", "HAD OVER HAD+EMC Energy", 100, 0., 1.01);
  dis_zufo_type = new TH1D("h_dis_zufo_type", "zufo type", 42, 0., 42.);

  //MC correlation of generated and reconstructed values
  dir[1]->cd();
  TString method[3] = {"Electron", "Double Angle", "Jacquet-Blondel"};
  TString s_method[3] = {"e", "da", "jb"};
  for(Int_t i=0; i<3; i++) {
    mccorel_q2[i] = new TH2D("h2d_q2_" + s_method[i], method[i] + " Method", 100, -200., 200., 100, q2start, q2end);
    mccorel_x[i] = new TH2D("h2d_x_" + s_method[i], method[i] + " Method", 100, -0.015, 0.015, 100, 0., 0.026);
    mccorel_y[i] = new TH2D("h2d_y_" + s_method[i], method[i] + " Method", 100, -0.36, 0.36, 100, 0., 0.72);
  }

  dir[5]->cd(); //inclusive jet
  ijet_njets = new TH1I("ijet_njets", "# of jets with E_{T} > 2.5 GeV", 10, 0, 10); ijet_njets->Sumw2();
  cout << " Reached Here  " << endl;

  ijet_njets_vs_etjet = new TH2D("h2d_ijet_njets_vs_etjet", "# of jets vs E_{T}^{jet}", 200, 0., 100., 10, 0, 10); ijet_njets_vs_etjet->Sumw2();
  zvtx->Sumw2();
   for(Int_t i=0; i<2; i++)
     dstw[i]->Sumw2();
   for(Int_t i=0; i<2; i++)
     fltw[i]->Sumw2();
   for(Int_t i=0; i<6; i++)
     sltw[i]->Sumw2();
   for(Int_t i=0; i<15; i++)
     tltw[i]->Sumw2();
  //for trigger efficiency study
   for(Int_t i=0; i<2; i++)
     theta_electron_tef[i]->Sumw2();
   for(Int_t i=0; i<2; i++) {
     e_electron_tef[i]->Sumw2();
     q2_tef[i]->Sumw2();
     e_gamma_tef[i]->Sumw2();
     eta_gamma_tef[i]->Sumw2();
     e_jet_tef[i]->Sumw2();
   }
  //for fmax & deltaz fit in different bins and cross sections:
   det_cross_et->Sumw2();
   det_cross_eta->Sumw2();
   det_cross_Q2->Sumw2();
   det_cross_x->Sumw2();

   had_cross_et->Sumw2();
   had_cross_eta->Sumw2();
   had_cross_Q2->Sumw2();
   had_cross_x->Sumw2();

   hd_cross_et->Sumw2();
   hd_cross_eta->Sumw2();
   hd_cross_Q2->Sumw2();
   hd_cross_x->Sumw2();

   prof_det_cross_et->Sumw2();
   prof_det_cross_eta->Sumw2();
   prof_det_cross_Q2->Sumw2();
   prof_det_cross_x->Sumw2();

   prof_had_cross_et->Sumw2();
   prof_had_cross_eta->Sumw2();
   prof_had_cross_Q2->Sumw2();
   prof_had_cross_x->Sumw2();

   prof_hd_cross_et->Sumw2();
   prof_hd_cross_eta->Sumw2();
   prof_hd_cross_Q2->Sumw2();
   prof_hd_cross_x->Sumw2();

   for(Int_t i=0; i<number_etbins; i++) {
     fmax_et[i]->Sumw2();
     deltaz_et[i]->Sumw2();
   }

   for(Int_t i=0; i<number_Q2bins; i++) {
     fmax_q2[i]->Sumw2();
     deltaz_q2[i]->Sumw2();
   }

   for(Int_t i=0; i<number_xbins; i++) {
     fmax_x[i]->Sumw2();
     deltaz_x[i]->Sumw2();
   }
   for(Int_t i=0; i<number_etabins; i++) {
     fmax_eta[i]->Sumw2();
     deltaz_eta[i]->Sumw2();
   }

   had_prph_e->Sumw2();
   had_jet_e->Sumw2();
   had_Q2->Sumw2();
   had_x->Sumw2();

  //fmax and deltaz for different particles->Sumw2();
   //   for(Int_t i=0; i<9; i++) {
   //   //     fmax_exact_part[i]->Sumw2();
   //     deltaz_exact_part[i]->Sumw2();
   //   }
  //control distributions for isolated photon candidate
   phcand_jet_deltaEta->Sumw2();
   phcand_jet_deltaPhi->Sumw2();
   phcand_jet_deltaR->Sumw2();
  
  //control distributions photon + jet
   fmax->Sumw2();
   deltaz->Sumw2();
   fmax_deltaz->Sumw2();
   phjet_electron_theta->Sumw2();
   phjet_electron_phi->Sumw2();
   phjet_electron_e->Sumw2();
   phjet_electron_probability->Sumw2();
   prph_energy->Sumw2();
   prph_eta->Sumw2();
   prph_phi->Sumw2();
   prph_jet_energy_frac->Sumw2();
   prph_cell_energy_frac->Sumw2();
   comp_prph_e->Sumw2();
   comp_jet_e->Sumw2();
   comp_Q2->Sumw2();
   comp_x->Sumw2();
   comp_y->Sumw2();
   comp_s->Sumw2();
   phjet_dphi_deta->Sumw2();
   phjet_deta_el_ph_true->Sumw2();
   phjet_deta_el_ph_true_unmerged->Sumw2(); 
   phjet_dphi_el_ph_true->Sumw2();
   phjet_dphi_el_ph_true_unmerged->Sumw2();
   phjet_jet_et->Sumw2();
   phjet_jet_eta->Sumw2();
   phjet_jet_phi->Sumw2();
   phjet_dphi->Sumw2();
   phjet_deta->Sumw2();
   phjet_dphi_unmarged->Sumw2();
   phjet_deta_unmarged->Sumw2();
   phjet_dphi_el_ph->Sumw2();
   phjet_deta_el_ph->Sumw2();
   phjet_dphi_el_jet->Sumw2();
   phjet_deta_el_jet->Sumw2();
   et_jet_photon_ratio->Sumw2();
   h2d_et_jet_et_photon->Sumw2();
   et_3system_event_ratio->Sumw2();
   h2d_phijet_phigamma->Sumw2();
   h2d_dphijet_dphigamma->Sumw2();
   h2d_dphijet_dphigamma_sharp->Sumw2();
   phjet_cal_empz->Sumw2();
   phjet_zufo_empz->Sumw2();
   phjet_zvtx->Sumw2();
   h2d_jet_npart_et->Sumw2();
   for(Int_t i=0; i<4; i++) 
     phjet_photon_sincand_dr[i]->Sumw2();
   phjet2d_photon_sincand_dr_nr->Sumw2();
   phjet_q2_dz_gt_035->Sumw2();
   phjet_q2_dz_lt_035->Sumw2();
   phjet_q2_dz_full->Sumw2();
   phjet_y_dz_gt_035->Sumw2();
   phjet_y_dz_lt_035->Sumw2();
   phjet_y_dz_full->Sumw2();
   phjet_etaph_dz_gt_035->Sumw2();
   phjet_etaph_dz_lt_035->Sumw2();
   phjet_etaph_dz_full->Sumw2();
   phjet_etph_dz_gt_035->Sumw2();
   phjet_etph_dz_lt_035->Sumw2();
   phjet_etph_dz_full->Sumw2();
   phjet_eel_dz_gt_035->Sumw2();
   phjet_eel_dz_lt_035->Sumw2();
   phjet_eel_dz_full->Sumw2();

   phjet_y_y_lt_05->Sumw2();
   phjet_eel_y_lt_05->Sumw2();
   phjet_phiph_phij_y_lt_05->Sumw2();
   phjet_thetael_y_lt_05->Sumw2();
   phjet_etaph_y_lt_05->Sumw2();
   phjet_etph_y_lt_05->Sumw2();

   phjet_y_y_gt_05->Sumw2();
   phjet_eel_y_gt_05->Sumw2();
   phjet_phiph_phij_y_gt_05->Sumw2();
   phjet_thetael_y_gt_05->Sumw2();
   phjet_etaph_y_gt_05->Sumw2();
   phjet_etph_y_gt_05->Sumw2();
   phjet_dr_track->Sumw2();

  h2d_phot_et_true_det->Sumw2();
  h2d_phot_eta_true_det->Sumw2();
  h2d_phot_phi_true_det->Sumw2();
  h2d_corr_accjet_et_true_det->Sumw2();
  h2d_corr_accjet_eta_true_det->Sumw2();
  h2d_corr_accjet_phi_true_det->Sumw2();
  h2d_uncorr_accjet_et_true_det->Sumw2();
  h2d_uncorr_accjet_eta_true_det->Sumw2();
  h2d_uncorr_accjet_phi_true_det->Sumw2();
  //control distributions inclusive photon
   incl_phot_fmax->Sumw2();
   incl_phot_deltaz->Sumw2();
   incl_phot_elphot_dphi->Sumw2();
   incl_phot_elphot_deta->Sumw2();
   incl_phot_phi->Sumw2();
   incl_phot_eta->Sumw2();
  //control distributions inclusive DIS
   dis_electron_theta->Sumw2();
   dis_electron_e->Sumw2();
   dis_electron_probability->Sumw2();
   dis_Q2->Sumw2();  
   dis_Q2_x->Sumw2();
   dis_Q2_el->Sumw2();
   dis_Q2_da->Sumw2();
   dis_Q2_da_cell->Sumw2();
   dis_Q2_jb->Sumw2();
   dis_Q2_jb_cell->Sumw2();
   dis_Q2_true->Sumw2();
   dis_x_true->Sumw2();
   dis_y_true->Sumw2();
   dis_electron_e_true->Sumw2();
   dis_electron_theta_true->Sumw2();
   dis_siyjb->Sumw2();
   dis_siyjb_cell->Sumw2();
   dis_handmade_yjb->Sumw2();
   dis_elec_zufo_dr_min->Sumw2();
   dis_elec_zufo_de_min->Sumw2();
   dis_zufos_near_electron->Sumw2();

   dis_zvtx->Sumw2();
   dis_n_vtx_tracks->Sumw2();
   dis_cal_empz->Sumw2();
   dis_zufo_empz->Sumw2();
   dis_pt_sqrtet->Sumw2();
   dis_x_el->Sumw2();
   dis_x_el_log->Sumw2();
   dis_y_el->Sumw2();
   x_gamma->Sumw2();
   x_pomeron->Sumw2();
   x_gamma_unmarged->Sumw2();
   x_pomeron_unmarged->Sumw2();
   dis_px_event->Sumw2();
   dis_py_event->Sumw2();
   dis_pz_event->Sumw2();
   dis_pt_event->Sumw2();
   dis_e_event->Sumw2();
   dis_et_event->Sumw2();
   dis_n_zufos->Sumw2();
   dis_emc->Sumw2();
   dis_had->Sumw2();
   dis_cal->Sumw2();
   dis_had_tot_ratio->Sumw2();
   dis_zufo_type->Sumw2();


  //MC correlation of generated and reconstructed values
   for(Int_t i=0; i<3; i++) {
     mccorel_q2[i]->Sumw2();
     mccorel_x[i]->Sumw2();
     mccorel_y[i]->Sumw2();
   }
   mccorel_q2_y->Sumw2();
   mccorel_q2_x->Sumw2();
}
