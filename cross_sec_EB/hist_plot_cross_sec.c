#include "TMath.h"
#include "../inc/constants.h"

void Hist::PlotCrossSec() 
{
    //  TGaxis::SetMaxDigits(3);
    //
    // et
    //
    if (nodebugmode) cout << "========== calculate and plot cross sections ==============" << endl;
    //0 - cross section value; 
    //1 - stat. & fit parameter uncertainty;         //4 - ratio (1); //5 - relative 1; 
    //2 - acceptance uncertainty                     //6 - relative 2; 
    //3 - lumi uncertainty;                          //7 - relative 3
                                                                //low,high
    //8 - jet energy uncertainty;        //13 - relative 8;     //20, 21 - 8;
    //9 - photon energy uncertainty;     //14 - relative 9      //22, 23 - 9;
    //10 - electron energy unc.          //15 - relative 10;    //24, 25 - 10; 
    //11 - deltaZ range uncertainty;     //16 - relative 11;    //26, 27 - 11
        
    //12 - 8+9+10+11 (in quadr); - total systematics    //17 - relative 12
    //18 - syst+stat;                                   //19 - relative 18
    TH1D *h_cross[n_cross][8]; //why 8
    TGraphAsymmErrors *gr_cross[n_cross][40]; //why 40
    TH1D *h_1st_cross[n_cross][8];
    TH2D *h_window_cross[n_cross][2];
    
    TGraphAsymmErrors *h_Spiesberger_pos_lo[n_cross];
    TGraphAsymmErrors *h_Spiesberger_pos_nlo[n_cross];
    TGraphAsymmErrors *h_Spiesberger_ele_lo[n_cross];
    TGraphAsymmErrors *h_Spiesberger_ele_nlo[n_cross];

    TGraphAsymmErrors *h_Spiesberger_pos_nlo_ra[n_cross];
    TGraphAsymmErrors *h_Spiesberger_ele_nlo_ra[n_cross];
    TGraphAsymmErrors *h_Spiesberger_pos_nlo_ra_fast[n_cross];
    TGraphAsymmErrors *h_Spiesberger_ele_nlo_ra_fast[n_cross];

    TGraphAsymmErrors *h_Zotov[n_cross];

    TGraphAsymmErrors *h_systematics[n_cross];

    const Int_t MAX_CROSS_SEC_BINS = 500;
    Double_t zero_array[MAX_CROSS_SEC_BINS] = {0.};

    Double_t x_et_bin[MAX_CROSS_SEC_BINS] = {0.};
    Double_t x_eta_bin[MAX_CROSS_SEC_BINS] = {0.};
    Double_t x_Q2_bin[MAX_CROSS_SEC_BINS] = {0.};
    Double_t x_x_bin[MAX_CROSS_SEC_BINS] = {0.};
    Double_t x_et_jet_bin[MAX_CROSS_SEC_BINS] = {0.};
    Double_t x_eta_jet_bin[MAX_CROSS_SEC_BINS] = {0.};

    Double_t x_xgamma_bin[MAX_CROSS_SEC_BINS] = {0.};
    Double_t x_xp_bin[MAX_CROSS_SEC_BINS] = {0.};
    Double_t x_dphi_bin[MAX_CROSS_SEC_BINS] = {0.};
    Double_t x_deta_bin[MAX_CROSS_SEC_BINS] = {0.};
    Double_t x_dphi_e_ph_bin[MAX_CROSS_SEC_BINS] = {0.};
    Double_t x_deta_e_ph_bin[MAX_CROSS_SEC_BINS] = {0.};
    
    /*//? середины бинов*/
    for(Int_t i = 0; i < number_etbins; i++)
        x_et_bin[i] = 0.5 * (et_bin[i] + et_bin[i+1]);
    for(Int_t i=0; i<number_etabins; i++)
        x_eta_bin[i] = 0.5 * (eta_bin_crosssec[i] + eta_bin_crosssec[i+1]);
    for(Int_t i=0; i<number_Q2bins; i++)
        x_Q2_bin[i] = 0.5 * (Q2_bin[i] + Q2_bin[i+1]);
    for(Int_t i=0; i<number_xbins; i++)
        x_x_bin[i] = 0.5 * (x_bin[i] + x_bin[i+1]);
    for(Int_t i=0; i<number_et_jetbins; i++)
        x_et_jet_bin[i] = 0.5 * (et_jet_bin[i] + et_jet_bin[i+1]);
    for(Int_t i=0; i<number_eta_jetbins; i++)
        x_eta_jet_bin[i] = 0.5 * (eta_jet_bin[i] + eta_jet_bin[i+1]);
    /*
    static Double_t xgamma_bin[number_xgamma_bins + 1] = {0, 0.4, 0.6, 0.7, 0.8, 0.9, 1};
    static Double_t xp_bin[number_xp_bins + 1] = {0, 0.002, 0.004, 0.006, 0.008, 0.01, 0.03};
    static Double_t dphi_bin[number_dphi_bins + 1] = {0., 45., 85., 120., 145., 180.};
    static Double_t deta_bin[number_deta_bins + 1] = {-2.2, -1.5, -0.8, -0.1, 0.6, 1.3, 2., 2.7};
    static Double_t dphi_e_ph_bin[number_dphi_e_ph_bins + 1] = {0., 30., 60., 90., 120., 150., 180.};
    static Double_t deta_e_ph_bin[number_deta_e_ph_bins + 1] = {-4.5, -3.75, -3.0, -2.25, -1.5, -0.75, 0.};
    */
    for(Int_t i = 0; i < number_xgamma_bins; i++)
        x_xgamma_bin[i] = 0.5 * (xgamma_bin[i] + xgamma_bin[i+1]);
    for(Int_t i = 0; i < number_xp_bins; i++)
        x_xp_bin[i] = 0.5 * (xp_bin[i] + xp_bin[i+1]);
    for(Int_t i = 0; i < number_dphi_bins; i++)
        x_dphi_bin[i] = 0.5 * (dphi_bin[i] + dphi_bin[i+1]);
    for(Int_t i = 0; i < number_deta_bins; i++)
        x_deta_bin[i] = 0.5 * (deta_bin[i] + deta_bin[i+1]);
    for(Int_t i = 0; i < number_dphi_e_ph_bins; i++)
        x_dphi_e_ph_bin[i] = 0.5 * (dphi_e_ph_bin[i] + dphi_e_ph_bin[i+1]);
    for(Int_t i = 0; i < number_deta_e_ph_bins; i++)
        x_deta_e_ph_bin[i] = 0.5 * (deta_e_ph_bin[i] + deta_e_ph_bin[i+1]);

    //////////////////////////////////////////////////
    //
    //          Hadronisation correction + styling
    //
    //////////////////////////////////////////////////
    apply_hadronisation_corrections();//warning hist_apply_hadronisation_corrections.c - correct theor values
    
    //
    /*Результаты сечений из статте?*/
    //
    /*
        h_Spiesberger_pos_nlo[0] = new TGraphAsymmErrors(number_etbins, x_et_bin, y_Spiesberger_pos_nlo_et, et_bin_err, et_bin_err, y_Spiesberger_pos_nlo_et_min, y_Spiesberger_pos_nlo_et_max);
        h_Spiesberger_pos_nlo[1] = new TGraphAsymmErrors(number_etabins, x_eta_bin, y_Spiesberger_pos_nlo_eta, eta_bin_crosssec_err, eta_bin_crosssec_err, y_Spiesberger_pos_nlo_eta_min, y_Spiesberger_pos_nlo_eta_max);
        h_Spiesberger_pos_nlo[2] = new TGraphAsymmErrors(number_Q2bins, x_Q2_bin, y_Spiesberger_pos_nlo_Q2, Q2_bin_err, Q2_bin_err, y_Spiesberger_pos_nlo_Q2_min, y_Spiesberger_pos_nlo_Q2_max);
        h_Spiesberger_pos_nlo[3] = new TGraphAsymmErrors(number_xbins, x_x_bin, y_Spiesberger_pos_nlo_x, x_bin_err, x_bin_err, y_Spiesberger_pos_nlo_x_min, y_Spiesberger_pos_nlo_x_max);
        h_Spiesberger_pos_nlo[4] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet_bin, y_Spiesberger_pos_nlo_et_jet, et_jet_bin_err, et_jet_bin_err, y_Spiesberger_pos_nlo_et_jet_min, y_Spiesberger_pos_nlo_et_jet_max);
        h_Spiesberger_pos_nlo[5] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet_bin, y_Spiesberger_pos_nlo_eta_jet, eta_jet_bin_err, eta_jet_bin_err, y_Spiesberger_pos_nlo_eta_jet_min, y_Spiesberger_pos_nlo_eta_jet_max);

        h_Spiesberger_ele_nlo[0] = new TGraphAsymmErrors(number_etbins, x_et_bin, y_Spiesberger_ele_nlo_et, et_bin_err, et_bin_err, y_Spiesberger_ele_nlo_et_min, y_Spiesberger_ele_nlo_et_max);
        h_Spiesberger_ele_nlo[1] = new TGraphAsymmErrors(number_etabins, x_eta_bin, y_Spiesberger_ele_nlo_eta, eta_bin_crosssec_err, eta_bin_crosssec_err, y_Spiesberger_ele_nlo_eta_min, y_Spiesberger_ele_nlo_eta_max);
        h_Spiesberger_ele_nlo[2] = new TGraphAsymmErrors(number_Q2bins, x_Q2_bin, y_Spiesberger_ele_nlo_Q2, Q2_bin_err, Q2_bin_err, y_Spiesberger_ele_nlo_Q2_min, y_Spiesberger_ele_nlo_Q2_max);
        h_Spiesberger_ele_nlo[3] = new TGraphAsymmErrors(number_xbins, x_x_bin, y_Spiesberger_ele_nlo_x, x_bin_err, x_bin_err, y_Spiesberger_ele_nlo_x_min, y_Spiesberger_ele_nlo_x_max);
        h_Spiesberger_ele_nlo[4] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet_bin, y_Spiesberger_ele_nlo_et_jet, et_jet_bin_err, et_jet_bin_err, y_Spiesberger_ele_nlo_et_jet_min, y_Spiesberger_ele_nlo_et_jet_max);
        h_Spiesberger_ele_nlo[5] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet_bin, y_Spiesberger_ele_nlo_eta_jet, eta_jet_bin_err, eta_jet_bin_err, y_Spiesberger_ele_nlo_eta_jet_min, y_Spiesberger_ele_nlo_eta_jet_max);

        //--------------------This block for running alpha em  ----------------------------------------------------------------------------------------------------------------------------------------------------------
        // OK, 20.03.2013
        h_Spiesberger_pos_nlo_ra[0] = new TGraphAsymmErrors(number_etbins, x_et_bin, y_Spiesberger_pos_nlo_ra_et, et_bin_err, et_bin_err, y_Spiesberger_pos_nlo_et_min, y_Spiesberger_pos_nlo_et_max);
        h_Spiesberger_pos_nlo_ra[1] = new TGraphAsymmErrors(number_etabins, x_eta_bin, y_Spiesberger_pos_nlo_ra_eta, eta_bin_crosssec_err, eta_bin_crosssec_err, y_Spiesberger_pos_nlo_eta_min, y_Spiesberger_pos_nlo_eta_max);
        h_Spiesberger_pos_nlo_ra[2] = new TGraphAsymmErrors(number_Q2bins, x_Q2_bin, y_Spiesberger_pos_nlo_ra_Q2, Q2_bin_err, Q2_bin_err, y_Spiesberger_pos_nlo_Q2_min, y_Spiesberger_pos_nlo_Q2_max);
        h_Spiesberger_pos_nlo_ra[3] = new TGraphAsymmErrors(number_xbins, x_x_bin, y_Spiesberger_pos_nlo_ra_x, x_bin_err, x_bin_err, y_Spiesberger_pos_nlo_x_min, y_Spiesberger_pos_nlo_x_max);
        h_Spiesberger_pos_nlo_ra[4] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet_bin, y_Spiesberger_pos_nlo_ra_et_jet, et_jet_bin_err, et_jet_bin_err, y_Spiesberger_pos_nlo_et_jet_min, y_Spiesberger_pos_nlo_et_jet_max);
        h_Spiesberger_pos_nlo_ra[5] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet_bin, y_Spiesberger_pos_nlo_ra_eta_jet, eta_jet_bin_err, eta_jet_bin_err, y_Spiesberger_pos_nlo_eta_jet_min, y_Spiesberger_pos_nlo_eta_jet_max);

        h_Spiesberger_ele_nlo_ra[0] = new TGraphAsymmErrors(number_etbins, x_et_bin, y_Spiesberger_ele_nlo_ra_et, et_bin_err, et_bin_err, y_Spiesberger_ele_nlo_et_min, y_Spiesberger_ele_nlo_et_max);
        h_Spiesberger_ele_nlo_ra[1] = new TGraphAsymmErrors(number_etabins, x_eta_bin, y_Spiesberger_ele_nlo_ra_eta, eta_bin_crosssec_err, eta_bin_crosssec_err, y_Spiesberger_ele_nlo_eta_min, y_Spiesberger_ele_nlo_eta_max);
        h_Spiesberger_ele_nlo_ra[2] = new TGraphAsymmErrors(number_Q2bins, x_Q2_bin, y_Spiesberger_ele_nlo_ra_Q2, Q2_bin_err, Q2_bin_err, y_Spiesberger_ele_nlo_Q2_min, y_Spiesberger_ele_nlo_Q2_max);
        h_Spiesberger_ele_nlo_ra[3] = new TGraphAsymmErrors(number_xbins, x_x_bin, y_Spiesberger_ele_nlo_ra_x, x_bin_err, x_bin_err, y_Spiesberger_ele_nlo_x_min, y_Spiesberger_ele_nlo_x_max);
        h_Spiesberger_ele_nlo_ra[4] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet_bin, y_Spiesberger_ele_nlo_ra_et_jet, et_jet_bin_err, et_jet_bin_err, y_Spiesberger_ele_nlo_et_jet_min, y_Spiesberger_ele_nlo_et_jet_max);
        h_Spiesberger_ele_nlo_ra[5] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet_bin, y_Spiesberger_ele_nlo_ra_eta_jet, eta_jet_bin_err, eta_jet_bin_err, y_Spiesberger_ele_nlo_eta_jet_min, y_Spiesberger_ele_nlo_eta_jet_max);

        // OK, 28.04.2013
        h_Spiesberger_pos_nlo_ra_fast[0] = new TGraphAsymmErrors(number_etbins, x_et_bin, y_Spiesberger_pos_nlo_ra_fast_et, et_bin_err, et_bin_err, y_Spiesberger_pos_nlo_et_min, y_Spiesberger_pos_nlo_et_max);
        h_Spiesberger_pos_nlo_ra_fast[1] = new TGraphAsymmErrors(number_etabins, x_eta_bin, y_Spiesberger_pos_nlo_ra_fast_eta, eta_bin_crosssec_err, eta_bin_crosssec_err, y_Spiesberger_pos_nlo_eta_min, y_Spiesberger_pos_nlo_eta_max);
        h_Spiesberger_pos_nlo_ra_fast[2] = new TGraphAsymmErrors(number_Q2bins, x_Q2_bin, y_Spiesberger_pos_nlo_ra_fast_Q2, Q2_bin_err, Q2_bin_err, y_Spiesberger_pos_nlo_Q2_min, y_Spiesberger_pos_nlo_Q2_max);
        h_Spiesberger_pos_nlo_ra_fast[3] = new TGraphAsymmErrors(number_xbins, x_x_bin, y_Spiesberger_pos_nlo_ra_fast_x, x_bin_err, x_bin_err, y_Spiesberger_pos_nlo_x_min, y_Spiesberger_pos_nlo_x_max);
        h_Spiesberger_pos_nlo_ra_fast[4] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet_bin, y_Spiesberger_pos_nlo_ra_fast_et_jet, et_jet_bin_err, et_jet_bin_err, y_Spiesberger_pos_nlo_et_jet_min, y_Spiesberger_pos_nlo_et_jet_max);
        h_Spiesberger_pos_nlo_ra_fast[5] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet_bin, y_Spiesberger_pos_nlo_ra_fast_eta_jet, eta_jet_bin_err, eta_jet_bin_err, y_Spiesberger_pos_nlo_eta_jet_min, y_Spiesberger_pos_nlo_eta_jet_max);

        h_Spiesberger_ele_nlo_ra_fast[0] = new TGraphAsymmErrors(number_etbins, x_et_bin, y_Spiesberger_ele_nlo_ra_fast_et, et_bin_err, et_bin_err, y_Spiesberger_ele_nlo_et_min, y_Spiesberger_ele_nlo_et_max);
        h_Spiesberger_ele_nlo_ra_fast[1] = new TGraphAsymmErrors(number_etabins, x_eta_bin, y_Spiesberger_ele_nlo_ra_fast_eta, eta_bin_crosssec_err, eta_bin_crosssec_err, y_Spiesberger_ele_nlo_eta_min, y_Spiesberger_ele_nlo_eta_max);
        h_Spiesberger_ele_nlo_ra_fast[2] = new TGraphAsymmErrors(number_Q2bins, x_Q2_bin, y_Spiesberger_ele_nlo_ra_fast_Q2, Q2_bin_err, Q2_bin_err, y_Spiesberger_ele_nlo_Q2_min, y_Spiesberger_ele_nlo_Q2_max);
        h_Spiesberger_ele_nlo_ra_fast[3] = new TGraphAsymmErrors(number_xbins, x_x_bin, y_Spiesberger_ele_nlo_ra_fast_x, x_bin_err, x_bin_err, y_Spiesberger_ele_nlo_x_min, y_Spiesberger_ele_nlo_x_max);
        h_Spiesberger_ele_nlo_ra_fast[4] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet_bin, y_Spiesberger_ele_nlo_ra_fast_et_jet, et_jet_bin_err, et_jet_bin_err, y_Spiesberger_ele_nlo_et_jet_min, y_Spiesberger_ele_nlo_et_jet_max);
        h_Spiesberger_ele_nlo_ra_fast[5] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet_bin, y_Spiesberger_ele_nlo_ra_fast_eta_jet, eta_jet_bin_err, eta_jet_bin_err, y_Spiesberger_ele_nlo_eta_jet_min, y_Spiesberger_ele_nlo_eta_jet_max);
        //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        h_Spiesberger_pos_lo[0] = new TGraphAsymmErrors(number_etbins, x_et_bin, y_Spiesberger_pos_lo_et, et_bin_err, et_bin_err, y_Spiesberger_pos_lo_et_min, y_Spiesberger_pos_lo_et_max);
        h_Spiesberger_pos_lo[1] = new TGraphAsymmErrors(number_etabins, x_eta_bin, y_Spiesberger_pos_lo_eta, eta_bin_crosssec_err, eta_bin_crosssec_err, y_Spiesberger_pos_lo_eta_min, y_Spiesberger_pos_lo_eta_max);
        h_Spiesberger_pos_lo[2] = new TGraphAsymmErrors(number_Q2bins, x_Q2_bin, y_Spiesberger_pos_lo_Q2, Q2_bin_err, Q2_bin_err, y_Spiesberger_pos_lo_Q2_min, y_Spiesberger_pos_lo_Q2_max);
        h_Spiesberger_pos_lo[3] = new TGraphAsymmErrors(number_xbins, x_x_bin, y_Spiesberger_pos_lo_x, x_bin_err, x_bin_err, y_Spiesberger_pos_lo_x_min, y_Spiesberger_pos_lo_x_max);
        h_Spiesberger_pos_lo[4] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet_bin, y_Spiesberger_pos_lo_et_jet, et_jet_bin_err, et_jet_bin_err, y_Spiesberger_pos_lo_et_jet_min, y_Spiesberger_pos_lo_et_jet_max);
        h_Spiesberger_pos_lo[5] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet_bin, y_Spiesberger_pos_lo_eta_jet, eta_jet_bin_err, eta_jet_bin_err, y_Spiesberger_pos_lo_eta_jet_min, y_Spiesberger_pos_lo_eta_jet_max);

        h_Spiesberger_ele_lo[0] = new TGraphAsymmErrors(number_etbins, x_et_bin, y_Spiesberger_ele_lo_et, et_bin_err, et_bin_err, y_Spiesberger_ele_lo_et_min, y_Spiesberger_ele_lo_et_max);
        h_Spiesberger_ele_lo[1] = new TGraphAsymmErrors(number_etabins, x_eta_bin, y_Spiesberger_ele_lo_eta, eta_bin_crosssec_err, eta_bin_crosssec_err, y_Spiesberger_ele_lo_eta_min, y_Spiesberger_ele_lo_eta_max);
        h_Spiesberger_ele_lo[2] = new TGraphAsymmErrors(number_Q2bins, x_Q2_bin, y_Spiesberger_ele_lo_Q2, Q2_bin_err, Q2_bin_err, y_Spiesberger_ele_lo_Q2_min, y_Spiesberger_ele_lo_Q2_max);
        h_Spiesberger_ele_lo[3] = new TGraphAsymmErrors(number_xbins, x_x_bin, y_Spiesberger_ele_lo_x, x_bin_err, x_bin_err, y_Spiesberger_ele_lo_x_min, y_Spiesberger_ele_lo_x_max);
        h_Spiesberger_ele_lo[4] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet_bin, y_Spiesberger_ele_lo_et_jet, et_jet_bin_err, et_jet_bin_err, y_Spiesberger_ele_lo_et_jet_min, y_Spiesberger_ele_lo_et_jet_max);
        h_Spiesberger_ele_lo[5] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet_bin, y_Spiesberger_ele_lo_eta_jet, eta_jet_bin_err, eta_jet_bin_err, y_Spiesberger_ele_lo_eta_jet_min, y_Spiesberger_ele_lo_eta_jet_max);


        h_Zotov[0] = new TGraphAsymmErrors(number_etbins, x_et_bin, y_Zotov_et, et_bin_err, et_bin_err, y_Zotov_et_eyl, y_Zotov_et_eyh);
        h_Zotov[1] = new TGraphAsymmErrors(number_etabins, x_eta_bin, y_Zotov_eta, eta_bin_crosssec_err, eta_bin_crosssec_err, y_Zotov_eta_eyl, y_Zotov_eta_eyh);
        h_Zotov[2] = new TGraphAsymmErrors(number_Q2bins, x_Q2_bin, y_Zotov_Q2, Q2_bin_err, Q2_bin_err, y_Zotov_Q2_eyl, y_Zotov_Q2_eyh);
        h_Zotov[3] = new TGraphAsymmErrors(number_xbins, x_x_bin, y_Zotov_x, x_bin_err, x_bin_err, y_Zotov_x_eyl, y_Zotov_x_eyh);
        h_Zotov[4] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet_bin, y_Zotov_et_jet, et_jet_bin_err, et_jet_bin_err, y_Zotov_et_jet_eyl, y_Zotov_et_jet_eyh);
        h_Zotov[5] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet_bin, y_Zotov_eta_jet, eta_jet_bin_err, eta_jet_bin_err, y_Zotov_eta_jet_eyl, y_Zotov_eta_jet_eyh);
    */
    h_systematics[0] = new TGraphAsymmErrors(number_etbins, x_et_bin, y_1stcross_et, zero_array, zero_array, eyl_syst_et, eyh_syst_et);
    h_systematics[1] = new TGraphAsymmErrors(number_etabins, x_eta_bin, y_1stcross_eta, zero_array, zero_array, eyl_syst_eta, eyh_syst_eta);
    h_systematics[2] = new TGraphAsymmErrors(number_Q2bins, x_Q2_bin, y_1stcross_Q2, zero_array, zero_array, eyl_syst_Q2, eyh_syst_Q2);
    h_systematics[3] = new TGraphAsymmErrors(number_xbins, x_x_bin, y_1stcross_x, zero_array, zero_array, eyl_syst_x, eyh_syst_x);
    h_systematics[4] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet_bin, y_1stcross_et_jet, zero_array, zero_array, eyl_syst_et_jet, eyh_syst_et_jet);
    h_systematics[5] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet_bin, y_1stcross_eta_jet, zero_array, zero_array, eyl_syst_eta_jet, eyh_syst_eta_jet);
        h_systematics[6] = new TGraphAsymmErrors(number_xgamma_bins, x_xgamma_bin, y_1stcross_xgamma, zero_array, zero_array, eyl_syst_xgamma, eyh_syst_xgamma);
        h_systematics[7] = new TGraphAsymmErrors(number_xp_bins, x_xp_bin, y_1stcross_xp, zero_array, zero_array, eyl_syst_xp, eyh_syst_xp);
        h_systematics[8] = new TGraphAsymmErrors(number_dphi_bins, x_dphi_bin, y_1stcross_dphi, zero_array, zero_array, eyl_syst_dphi, eyh_syst_dphi);
        h_systematics[9] = new TGraphAsymmErrors(number_deta_bins, x_deta_bin, y_1stcross_deta, zero_array, zero_array, eyl_syst_deta, eyh_syst_deta);
        h_systematics[10] = new TGraphAsymmErrors(number_dphi_e_ph_bins, x_dphi_e_ph_bin, y_1stcross_dphi_e_ph, zero_array, zero_array, eyl_syst_dphi_e_ph, eyh_syst_dphi_e_ph);
        h_systematics[11] = new TGraphAsymmErrors(number_deta_e_ph_bins, x_deta_e_ph_bin, y_1stcross_deta_e_ph, zero_array, zero_array, eyl_syst_deta_e_ph, eyh_syst_deta_e_ph);
    //
    /*Результаты сечений из статтей? Styling*/ 
    //
    /*
        for(Int_t i = 0; i < n_cross; i++) 
        {
            h_Spiesberger_pos_nlo[i]->SetLineWidth(1);
            h_Spiesberger_pos_nlo[i]->SetLineColor(kGreen);//28
            h_Spiesberger_pos_nlo[i]->SetFillColor(kGreen);
            h_Spiesberger_pos_nlo[i]->SetFillStyle(3018);
            Double_t xmin = h_Spiesberger_pos_nlo[i]->GetXaxis()->GetXmin(),
                     xmax = h_Spiesberger_pos_nlo[i]->GetXaxis()->GetXmax();
            Double_t deltax = xmax - xmin;
            h_Spiesberger_pos_nlo[i]->GetXaxis()->SetLimits(xmin + 0.1 * deltax, xmax + 0.1 * deltax);
            h_Spiesberger_pos_nlo[i]->GetXaxis()->SetRangeUser(xmin + 0.1 * deltax, xmax + 0.1 * deltax);

            h_Spiesberger_ele_nlo[i]->SetLineWidth(1);
            h_Spiesberger_ele_nlo[i]->SetLineColor(kBlack);
            h_Spiesberger_ele_nlo[i]->SetFillColor(kBlack);
            h_Spiesberger_ele_nlo[i]->SetFillStyle(3345);

            h_Spiesberger_ele_nlo_ra[i]->SetLineWidth(2);
            h_Spiesberger_ele_nlo_ra[i]->SetLineColor(kRed);
            h_Spiesberger_ele_nlo_ra[i]->SetFillColor(kRed);
            h_Spiesberger_ele_nlo_ra[i]->SetFillStyle(3345);

            h_Spiesberger_ele_nlo_ra_fast[i]->SetLineWidth(2);
            h_Spiesberger_ele_nlo_ra_fast[i]->SetLineColor(kBlue);
            h_Spiesberger_ele_nlo_ra_fast[i]->SetFillColor(kBlue);
            h_Spiesberger_ele_nlo_ra_fast[i]->SetFillStyle(3345);

            
            h_Spiesberger_pos_lo[i]->SetLineWidth(1);
            h_Spiesberger_pos_lo[i]->SetLineColor(kRed);
            h_Spiesberger_pos_lo[i]->SetFillColor(kRed);
            h_Spiesberger_pos_lo[i]->SetFillStyle(3003);

            h_Spiesberger_ele_lo[i]->SetLineWidth(1);
            h_Spiesberger_ele_lo[i]->SetLineColor(44);
            h_Spiesberger_ele_lo[i]->SetFillColor(44);
            h_Spiesberger_ele_lo[i]->SetFillStyle(3002);

            h_Zotov[i]->SetLineWidth(1);
            h_Zotov[i]->SetLineColor(kBlack);
            h_Zotov[i]->SetFillColor(91);
            h_Zotov[i]->SetFillStyle(1001);
        }
    */
    
    //////////////////////////////////////////////////
    //
    //          Calculating cross-section for each case
    //
    //////////////////////////////////////////////////
    for(Int_t i = 0; i < n_cross; i++) 
    {
        selectedoutput << "==================================================================================================" <<endl;
        selectedoutput << "processing variable " << s_var[i] << endl;
        if (nodebugmode) cout << "==================================================================================================" <<endl;
        if (nodebugmode) cout << "processing variable " << s_var[i] << endl;
        //    this->h_det_prph_sum[i]->Scale((this->h_det_data_sum[i]->Integral()-this->h_det_rad_sum[i]->Integral())/this->h_det_prph_sum[i]->Integral());
        //    this->h_had_prph_sum[i]->Scale((this->h_det_data_sum[i]->Integral()-this->h_det_rad_sum[i]->Integral())/this->h_det_prph_sum[i]->Integral());
        //    this->h_hd_prph_sum[i]->Scale((this->h_det_data_sum[i]->Integral()-this->h_det_rad_sum[i]->Integral())/this->h_det_prph_sum[i]->Integral());
        //    this->h_hd_prph_sum[i]-Scale(param_et);
        Double_t int_data = this->h_det_data_sum[i]->Integral(),
                 int_ll   = this->h_det_rad_sum[i]->Integral(),
                 int_data_err =0, int_ll_err = 0.;
        
        //! use existing function!
        for(Int_t j = 0; j < this->h_det_data_sum[i]->GetNbinsX(); j++) // integrating over bins
        {
            Double_t err = this->h_det_data_sum[i]->GetBinError(j+1);
            int_data_err += err * err;
            Double_t err1 = this->h_det_rad_sum[i]->GetBinError(j+1);
            int_ll_err += err1 * err1;
        }
        int_data_err = TMath::Sqrt(int_data_err);
        int_ll_err = TMath::Sqrt(int_ll_err);
        
        TString s; 
        s.Form("h_cross_section_" + s_var[i]);
        //    h_cross[i] = (TH1D*)h_det_prph_sum[i]->Clone();//what was that?
        //    h_cross[i]->SetName(s + "temp");//what was that?
        /*
         * 020715 можно переписать через класс
         */
        if (nodebugmode) cout << "choose  variable" << endl;
        Double_t * param;
        Double_t * param_err;
        {
            if (s_var[i] == "et")
            {
                param = param_et;
                param_err = param_err_et;
            }
            if(s_var[i]=="eta") 
            {
                param = param_eta;
                param_err = param_err_eta;
            }
            if(s_var[i] == "Q2")
            {
                param = param_q2;
                param_err = param_err_q2;
            }
            if(s_var[i]=="x") 
            {
                param = param_x;
                param_err = param_err_x;
            }
            if(s_var[i]=="et_jet") 
            {
                param = param_et_jet;
                param_err = param_err_et_jet;
            }
            if(s_var[i]=="eta_jet") 
            {
                param = param_eta_jet;
                param_err = param_err_eta_jet;
            }
            if(s_var[i]=="xgamma") 
            {
                param = param_xgamma;
                param_err = param_err_xgamma;
            }
            if(s_var[i]=="xp") 
            {
                param = param_xp;
                param_err = param_err_xp;
            }
            if(s_var[i]=="dphi") 
            {
                param = param_dphi;
                param_err = param_err_dphi;
            }
            if(s_var[i]=="deta") 
            {
                param = param_deta;
                param_err = param_err_deta;
            }
            if(s_var[i]=="dphi_e_ph") 
            {
                param = param_dphi_e_ph;
                param_err = param_err_dphi_e_ph;
            }
            if(s_var[i]=="deta_e_ph") 
            {
                param = param_deta_e_ph;
                param_err = param_err_deta_e_ph;
            }
        }
        CalculateCrossSec(h_det_data_sum[i],
                        h_det_rad_sum[i],
                        h_had_rad_sum[i],
                        h_hd_rad_sum[i],
                        h_det_prph_sum[i],
                        h_had_prph_sum[i],
                        h_hd_prph_sum[i],
                        h_acceptance_rad[i],
                        h_acceptance_prph[i],
                        total_luminosity_data,
                        h_cross[i],
                        s,
                        param,
                        param_err);
         if(s_var[i] == "Q2")
        {
          for(Int_t bb = 0; bb < h_cross[i][7]->GetNbinsX(); bb++)
            if (nodebugmode) cout << "lumi unc. in bin " << bb << ": " << h_cross[i][7]->GetBinError(bb+1) << " " << endl;
        }
        //!Compare1st2nd(i, h_1st_cross[i], h_cross[i]);// h_cross теперь относительно чего-то ,
        
        if (nodebugmode) cout << "going into SetSystematicErrors" << endl;
        //!SetSystematicErrors(i, h_1st_cross[i], h_cross[i], gr_cross[i]); НАдо дописать для остальных гистограмм
        if (nodebugmode) cout << "returned from SetSystematicErrors" << endl;
        h_cross[i][0]->SetLineColor(kBlack);
        h_cross[i][1]->SetLineColor(kBlue);
        h_cross[i][2]->SetLineColor(kRed);
        h_cross[i][3]->SetLineColor(kGreen);
        /*Setting style*/
        /*
        {
            h_cross[i][0]->SetFillColor(41);
            h_cross[i][0]->SetMarkerStyle(20);
            h_cross[i][0]->SetMarkerSize(1. );
            h_1st_cross[i][0]->SetMarkerStyle(24);
            h_1st_cross[i][0]->SetMarkerSize(1.);
            h_1st_cross[i][0]->SetMarkerColor(kBlue);
            h_1st_cross[i][0]->SetLineColor(kBlue);
            h_cross[i][1]->SetFillColor(43);
            h_cross[i][2]->SetFillColor(46);
            h_cross[i][3]->SetFillColor(49);
            h_cross[i][4]->SetFillColor(41);
            h_cross[i][4]->SetMarkerStyle(20);
            h_cross[i][4]->SetMarkerSize(0.6);
            h_1st_cross[i][4]->SetMarkerStyle(24);
            h_1st_cross[i][4]->SetMarkerSize(1.);
            h_1st_cross[i][4]->SetMarkerColor(kBlue);
            //    h_1st_cross[i][4]->SetLineColor(kBlue);
            h_cross[i][5]->SetFillColor(43);
            h_cross[i][6]->SetFillColor(46);
            h_cross[i][7]->SetFillColor(49);
        }
        */
    }

    /*
        TLegend *leg_cross[n_cross];// = new TLegend(0.5, 0.5, 0.9, 0.9);
        leg_cross[0] = new TLegend(0.5, 0.6, 0.9, 0.9);
        leg_cross[1] = new TLegend(0.5, 0.6, 0.9, 0.9); // Zotov
        leg_cross[2] = new TLegend(0.16, 0.3, 0.55, 0.55); // Zotov
        leg_cross[3] = new TLegend(0.16, 0.3, 0.55, 0.6);
        leg_cross[4] = new TLegend(0.5, 0.6, 0.9, 0.9); // Zotov
        leg_cross[5] = new TLegend(0.47, 0.6, 0.87, 0.9); // Zotov
        leg_cross[6] = new TLegend(0.5, 0.6, 0.9, 0.9);
        leg_cross[7] = new TLegend(0.5, 0.6, 0.9, 0.9); // Zotov
        leg_cross[8] = new TLegend(0.16, 0.3, 0.55, 0.55); // Zotov
        leg_cross[9] = new TLegend(0.16, 0.3, 0.55, 0.6);
        leg_cross[10] = new TLegend(0.5, 0.6, 0.9, 0.9); // Zotov
        leg_cross[11] = new TLegend(0.47, 0.6, 0.87, 0.9); // Zotov
        for(Int_t i = 0; i < n_cross; i++) 
        {
            leg_cross[i]->SetBorderSize(0);
            leg_cross[i]->SetFillColor(0);
            leg_cross[i]->SetTextFont(22);
            leg_cross[i]->AddEntry(h_cross[i][1], "statistic unc.", "f");
            leg_cross[i]->AddEntry(h_cross[i][2], "acceptance unc.", "f");
            leg_cross[i]->AddEntry(h_cross[i][3], "luminosity unc.", "f");
            leg_cross[i]->AddEntry(h_cross[i][0], "total unc.", "fpl");
        }

        h_window_cross[0][0] = new TH2D("h_window_cross_" + s_var[0], "", number_etbins, et_bin, 10, 0.1, 4.);
        h_window_cross[1][0] = new TH2D("h_window_cross_" + s_var[1], "", number_etabins, eta_bin_crosssec, 10, 0.05, 18.5);
        h_window_cross[2][0] = new TH2D("h_window_cross_" + s_var[2], "", number_Q2bins, Q2_bin, 10, 1.e-3, 0.7);
        h_window_cross[3][0] = new TH2D("h_window_cross_" + s_var[3], "", number_xbins, x_bin, 10, 11., 2.e4);
        h_window_cross[4][0] = new TH2D("h_window_cross_" + s_var[4], "", number_et_jetbins, et_jet_bin, 10, 0.015, 3.);
        h_window_cross[5][0] = new TH2D("h_window_cross_" + s_var[5], "", number_eta_jetbins, eta_jet_bin, 10, 0.05, 11.);

        h_window_cross[6][0] = new TH2D("h_window_cross_" + s_var[6], "", number_xgamma_bins, xgamma_bin, 10, h_cross[6][0]->GetMinimum() - (h_cross[6][0]->GetMaximum() - h_cross[6][0]->GetMinimum())*0.1, h_cross[6][0]->GetMaximum() + (h_cross[6][0]->GetMaximum() - h_cross[6][0]->GetMinimum())*0.1);
        h_window_cross[7][0] = new TH2D("h_window_cross_" + s_var[7], "", number_xp_bins, xp_bin, 10, 15, 900.);
        h_window_cross[8][0] = new TH2D("h_window_cross_" + s_var[8], "", number_dphi_bins, dphi_bin, 10, 0.01, 0.07);
        h_window_cross[9][0] = new TH2D("h_window_cross_" + s_var[9], "", number_deta_bins, deta_bin, 10, 0.01, 3.);
        h_window_cross[10][0] = new TH2D("h_window_cross_" + s_var[10], "", number_dphi_e_ph_bins, dphi_e_ph_bin, 10, 0., 0.5);
        h_window_cross[11][0] = new TH2D("h_window_cross_" + s_var[11], "", number_deta_e_ph_bins, deta_e_ph_bin, 10, 0.01, 6.);

        TCanvas *c_cross[n_cross];
        TPad* pad_cross[n_cross];
        TPad* pad_ratio[n_cross];
        for(Int_t i = 0; i < n_cross; i++)
        {
          c_cross[i] = new TCanvas("canv_cross_" + s_var[i], "", 1200, 1000);
          c_cross[i]->Divide(1, 1);
          make_clean_pads(c_cross[i], 1, 0, 0);
        }
        for(Int_t i = 0; i < n_cross; i++)
        {
          c_cross[i]->cd();
          if(i==3) 
          {
            c_cross[i]->GetPad(1)->SetLogy();
            c_cross[i]->GetPad(1)->SetLogx();
            //      c_cross[i]->GetPad(2)->SetLogx();
          }
          if(i==2) 
          {
            c_cross[i]->GetPad(1)->SetLogy();
            c_cross[i]->GetPad(1)->SetLogx();
            h_window_cross[i][0]->GetXaxis()->SetMoreLogLabels();
          }
          if(i==4) 
          {
            c_cross[i]->GetPad(1)->SetLogy();
          }
        }
        sign_window(c_cross[0]->GetPad(1), h_window_cross[0][0], "E_{T}^{#gamma} (GeV)", "d#sigma/dE_{T}^{#gamma} (pb/GeV)", "", "middle");
        sign_window(c_cross[1]->GetPad(1), h_window_cross[1][0], "#eta^{#gamma}", "d#sigma/d#eta^{#gamma} (pb)", "", "middle");
        sign_window(c_cross[2]->GetPad(1), h_window_cross[2][0], "Q^{2} (GeV^{2})", "d#sigma/dQ^{2} (pb/GeV^{2})", "", "middle");
        sign_window(c_cross[3]->GetPad(1), h_window_cross[3][0], "x", "d#sigma/dx (pb)", "", "middle");
        sign_window(c_cross[4]->GetPad(1), h_window_cross[4][0], "E_{T}^{jet} (GeV)", "d#sigma/dE_{T}^{jet} (pb/GeV)", "", "middle");
        sign_window(c_cross[5]->GetPad(1), h_window_cross[5][0], "#eta^{jet}", "d#sigma/d#eta^{jet} (pb)", "", "middle");

        sign_window(c_cross[6]->GetPad(1), h_window_cross[6][0], "xgamma_bins", "d#sigma/d_xgamma_bins(pb)", "", "middle");
        sign_window(c_cross[7]->GetPad(1), h_window_cross[7][0], "xp_bins", "d#sigma/d_xp_bins (pb)", "", "middle");
        sign_window(c_cross[8]->GetPad(1), h_window_cross[8][0], "dphi_bins", "d#sigma/d_dphi_bins (pb)", "", "middle");
        sign_window(c_cross[9]->GetPad(1), h_window_cross[9][0], "deta_bins", "d#sigma/d_deta_bins (pb)", "", "middle");
        sign_window(c_cross[10]->GetPad(1), h_window_cross[10][0], "dphi_e_ph_bins", "d#sigma/d_dphi_e_ph_bins (pb)", "", "middle");
        sign_window(c_cross[11]->GetPad(1), h_window_cross[11][0], "deta_e_ph_bins", "d#sigma/d_deta_e_ph_bins (pb)", "", "middle");
        
        for(Int_t i = 0; i < n_cross; i++)
        {
          c_cross[i]->GetPad(1)->cd();
          h_window_cross[i][0]->Draw();
          h_cross[i][0]->SetLineWidth(2);
          if (nodebugmode) cout <<"+++++++++++++++  "<<s_var[i]<<"  ++++++++++++++++"<<endl;
          if (nodebugmode) cout<< "CS:"<<endl;
          for(Int_t j = 0; j < h_cross[i][0]->GetNbinsX(); j++)
          {
            if (nodebugmode) cout << h_cross[i][0]->GetBinContent(j+1) << "  ";
          }
          if (nodebugmode) cout << endl << "max: " << h_cross[i][0]->GetMaximum() << " min: " << h_cross[i][0]->GetMinimum() << endl;

          if (nodebugmode) cout<< "CS error:"<<endl;
          for(Int_t j = 0; j < h_cross[i][0]->GetNbinsX(); j++)
          {
            if (nodebugmode) cout << h_cross[i][0]->GetBinError(j+1) << "  ";
          }
          if (nodebugmode) cout << endl;
          if (nodebugmode) cout<< "CS statistic:"<<endl;
          for(Int_t j = 0; j < h_cross[i][0]->GetNbinsX(); j++)
          {
            if (nodebugmode) cout << h_cross[i][1]->GetBinError(j+1) << "  ";
          }
          if (nodebugmode) cout<< "CS acc:"<<endl;
          for(Int_t j = 0; j < h_cross[i][0]->GetNbinsX(); j++)
          {
            if (nodebugmode) cout << h_cross[i][2]->GetBinError(j+1) << "  ";
          }
          if (nodebugmode) cout<< "CS lumi:"<<endl;
          for(Int_t j = 0; j < h_cross[i][0]->GetNbinsX(); j++)
          {
            if (nodebugmode) cout << h_cross[i][3]->GetBinError(j+1) << "  ";
          }
          if (nodebugmode) cout << endl;
          if (nodebugmode) cout << endl;
          if (nodebugmode) cout << endl;
          h_cross[i][0]->SetMarkerStyle(20);
          h_cross[i][0]->SetMarkerSize(1);
          if(i == 9 || i ==11)
          {
            h_cross[i][0]->SetBinContent(1, 0);
            h_cross[i][0]->SetBinError(1, 0);
          }
          h_cross[i][0]->Draw("SAME"); //these are cross sections from root files
          //h_cross[i][1]->Draw("E1 X0 SAME"); //these are cross sections from root files
          //h_cross[i][2]->Draw("E1 X0 SAME"); //these are cross sections from root files
          //h_cross[i][3]->Draw("E1 X0 SAME"); //these are cross sections from root files
          c_cross[i]->GetPad(1)->RedrawAxis();
          leg_cross[i]->Draw();
          
          c_cross[i]->Print("cross_" + s_var[i] + ".png");
        }
    */
    /*
        //////////////////////////////////////////////////
        //
        //          Legends to cross-section
        //
        //////////////////////////////////////////////////    
        if (nodebugmode) cout << "cross sections have been calculated" << endl
             << "cross section in first et bin is: " << h_cross[0][0]->GetBinContent(1) << " +- " << h_cross[0][0]->GetBinError(1) << endl;
        
        //
        //cross_*.png
        //
        TLegend *leg_cross[n_cross];// = new TLegend(0.5, 0.5, 0.9, 0.9);
        leg_cross[0] = new TLegend(0.5, 0.6, 0.9, 0.9);
        leg_cross[1] = new TLegend(0.5, 0.6, 0.9, 0.9); // Zotov
        leg_cross[2] = new TLegend(0.16, 0.3, 0.55, 0.55); // Zotov
        leg_cross[3] = new TLegend(0.16, 0.3, 0.55, 0.6);
        leg_cross[4] = new TLegend(0.5, 0.6, 0.9, 0.9); // Zotov
        leg_cross[5] = new TLegend(0.47, 0.6, 0.87, 0.9); // Zotov
        for(Int_t i = 0; i < n_cross; i++) 
        {
            leg_cross[i]->SetBorderSize(0);
            leg_cross[i]->SetFillColor(0);
            leg_cross[i]->SetTextFont(22);
            leg_cross[i]->AddEntry(h_cross[i][0], "ZEUS 326 pb^{-1}", "p");
            //qwe leg_cross[i]->AddEntry(h_Spiesberger_ele_nlo[0], "GKS NLO", "f");
            //    leg_cross[i]->AddEntry(h_Spiesberger_ele_nlo_ra[0], "GKS NLO (running #alpha_{em})", "l");
            //    leg_cross[i]->AddEntry(h_Spiesberger_ele_nlo_ra_fast[0], "GKS NLO (running #alpha_{em}), fast calc", "l");
            //    leg_cross[i]->AddEntry(h_Spiesberger_pos_nlo[0], "Spiesberger et al., e^{+}p, NLO", "fl");
            //    leg_cross[i]->AddEntry(h_Spiesberger_ele_lo[0], "Spiesberger et al., e^{-}p, LO", "fl");
            //    leg_cross[i]->AddEntry(h_Spiesberger_pos_lo[0], "Spiesberger et al., e^{+}p, LO", "fl");
            //qwe leg_cross[i]->AddEntry(h_Zotov[0], "BLZ", "f");
            //    leg_cross[i]->AddEntry(h_cross[i][1], "statistic & fit parameter unc.", "f");
            //    leg_cross[i]->AddEntry(h_cross[i][2], "acceptance unc.", "f");
            //    leg_cross[i]->AddEntry(h_cross[i][3], "luminosity unc.", "f");
            //    leg_cross[i]->AddEntry(h_cross[i][0], "total unc.", "fpl");
        }
        
        //
        //comp_1st2nd_*.png
        //
        TLegend *leg_1st2nd[n_cross];// = new TLegend(0.5, 0.5, 0.9, 0.9);
        leg_1st2nd[0] = new TLegend(0.4, 0.7, 0.9, 0.85);
        leg_1st2nd[1] = new TLegend(0.37, 0.059, 0.77, 0.358);
        leg_1st2nd[2] = new TLegend(0.23, 0.209, 0.63, 0.508);
        leg_1st2nd[3] = new TLegend(0.23, 0.289, 0.63, 0.588);
        leg_1st2nd[4] = new TLegend(0.4, 0.87, 0.9, 0.97);
        leg_1st2nd[5] = new TLegend(0.37, 0.059, 0.77, 0.358);
        for(Int_t i = 0; i < n_cross; i++) 
        {
            leg_1st2nd[i]->SetBorderSize(0);
            leg_1st2nd[i]->SetFillColor(0);
            leg_1st2nd[i]->AddEntry(h_1st_cross[i][0], "1st analysis", "p");
            leg_1st2nd[i]->AddEntry(h_cross[i][0], "2nd analysis", "p");
        }
        
        //
        //syst_*.png
        //
        TLegend *leg_syst[n_cross];// = new TLegend(0.5, 0.5, 0.9, 0.9);
        leg_syst[0] = new TLegend(0.3, 0.65, 0.9, 0.85);
        leg_syst[1] = new TLegend(0.37, 0.059, 0.77, 0.458);
        leg_syst[2] = new TLegend(0.1, 0.1, 0.5, 0.5);
        leg_syst[3] = new TLegend(0.23, 0.2, 0.63, 0.6);
        leg_syst[4] = new TLegend(0.3, 0.65, 0.9, 0.9);
        leg_syst[5] = new TLegend(0.37, 0.059, 0.77, 0.458);
        for(Int_t i = 0; i < n_cross; i++)
        {
            leg_syst[i]->SetBorderSize(0);
            leg_syst[i]->SetFillColor(0);
            leg_syst[i]->AddEntry(h_cross[i][0], "ZEUS (332 pb^{-1})", "p");
            leg_syst[i]->AddEntry(gr_cross[i][12], "systematic uncertainty", "f");
            leg_syst[i]->AddEntry(gr_cross[i][17], "inner error bars are stat. uncertainties", "le");
            leg_syst[i]->AddEntry(gr_cross[i][17], "outer error bars are total uncertainties", "le");
            //    leg_syst[i]->AddEntry(h_cross[i][2], "acceptance unc.", "f");
            //    leg_syst[i]->AddEntry(h_cross[i][3], "luminosity unc.", "f");
            //    leg_syst[i]->AddEntry(h_cross[i][0], "total unc.", "fpl");
        }
        
        TLegend *leg_syst_ratio[n_cross];// = new TLegend(0.5, 0.5, 0.9, 0.9);
        leg_syst_ratio[0] = new TLegend(0.5, 0.25, 0.9, 0.65, "At the bottom:");
        leg_syst_ratio[1] = new TLegend(0.37, 0.059, 0.77, 0.458, "Bottom:");
        leg_syst_ratio[2] = new TLegend(0.5, 0.5, 0.9, 0.9, "Bottom:");
        leg_syst_ratio[3] = new TLegend(0.23, 0.289, 0.63, 0.6, "Bottom:");
        leg_syst_ratio[4] = new TLegend(0.5, 0.25, 0.9, 0.65, "At the bottom:");
        leg_syst_ratio[5] = new TLegend(0.37, 0.059, 0.77, 0.458, "Bottom:");
        for(Int_t i=0; i<n_cross; i++) 
        {
            leg_syst_ratio[i]->SetBorderSize(0);
            leg_syst_ratio[i]->SetFillColor(0);
            leg_syst_ratio[i]->AddEntry(gr_cross[i][13], "jet energy uncertainty", "f");
            leg_syst_ratio[i]->AddEntry(gr_cross[i][14], "photon energy uncertainty", "f");
            leg_syst_ratio[i]->AddEntry(gr_cross[i][15], "electron energy uncertainty", "f");
            leg_syst_ratio[i]->AddEntry(gr_cross[i][16], "#delta Z range unc.", "f");
            leg_syst_ratio[i]->AddEntry(gr_cross[i][17], "total syst. unc.", "le");
        }
        
        h_window_cross[0][0] = new TH2D("h_window_cross_" + s_var[0], "", number_etbins, et_bin, 10, 0.1, 4.);
        //  h_window_cross[0][0] = new TH2D("h_window_cross_" + s_var[0], "", number_etbins, et_bin, 10, 0.05, 4.); // Zotov
        h_window_cross[0][1] = new TH2D("h_window_cross_ratio_" + s_var[0], "", number_etbins, et_bin, 10, -0.525, 0.525);
        h_window_cross[1][0] = new TH2D("h_window_cross_" + s_var[1], "", number_etabins, eta_bin_crosssec, 10, 0.05, /*20.* /18.5);
        //  h_window_cross[1][0] = new TH2D("h_window_cross_" + s_var[1], "", number_etabins, eta_bin_crosssec, 10, 0.05, 20.); // Zotov
        h_window_cross[1][1] = new TH2D("h_window_cross_ratio_" + s_var[1], "", number_etabins, eta_bin_crosssec, 10, -0.525, 0.525);
        h_window_cross[2][0] = new TH2D("h_window_cross_" + s_var[2], "", number_Q2bins, Q2_bin, 10, 1.e-3, /*1.2* /0.7);
        //  h_window_cross[2][0] = new TH2D("h_window_cross_" + s_var[2], "", number_Q2bins, Q2_bin, 10, 1.e-3, 1.2); // Zotov
        h_window_cross[2][1] = new TH2D("h_window_cross_ratio_" + s_var[2], "", number_Q2bins, Q2_bin, 10, -0.7, 0.7);
        h_window_cross[3][0] = new TH2D("h_window_cross_" + s_var[3], "", number_xbins, x_bin, 10, 11., 2.e4);
        h_window_cross[3][1] = new TH2D("h_window_cross_ratio_" + s_var[3], "", number_xbins, x_bin, 10, -0.9, 0.9);
        h_window_cross[4][0] = new TH2D("h_window_cross_" + s_var[4], "", number_et_jetbins, et_jet_bin, 10, 0.015, 3.);
        h_window_cross[4][1] = new TH2D("h_window_cross_ratio_" + s_var[4], "", number_et_jetbins, et_jet_bin, 10, -0.425, 0.425);
        h_window_cross[5][0] = new TH2D("h_window_cross_" + s_var[5], "", number_eta_jetbins, eta_jet_bin, 10, 0.05, /*7.* /11.);
        //  h_window_cross[5][0] = new TH2D("h_window_cross_" + s_var[5], "", number_eta_jetbins, eta_jet_bin, 10, 0.05, 7.); // Zotov
        h_window_cross[5][1] = new TH2D("h_window_cross_ratio_" + s_var[5], "", number_eta_jetbins, eta_jet_bin, 10, -0.425, 0.425);
        if (nodebugmode) cout << "after returning integral is " << h_cross[0][0]->Integral() << endl;
        
        
        TCanvas *c_cross[n_cross];
        TPad* pad_cross[n_cross];
        TPad* pad_ratio[n_cross];
        for(Int_t i = 0; i < n_cross; i++)
        {
          c_cross[i] = new TCanvas("canv_cross_" + s_var[i], "", 1200, 1000);
          //    pad_cross[i] = new TPad("pad_cross_" + s_var[i], "", 0.1, 0.3, 0.9, 0.9);
          //    pad_ratio[i] = new TPad("pad_ratio_" + s_var[i], "", 0.1, 0.1, 0.9, 0.3);
          c_cross[i]->Divide(1, 1);
          make_clean_pads(c_cross[i], 1, 0, 0);
        }
        if (nodebugmode) cout << "canvas prepared" << endl;
        for(Int_t i = 0; i < n_cross; i++)
        {
          c_cross[i]->cd();
          //    c_cross[i]->GetPad(1)->SetGridy();
          //    pad_cross[i]->GetFrame()->SetY1(0.3);
          //    pad_cross[i]->SetBottomMargin(-0.5);
          //    pad_cross[i]->Draw();
          //    pad_ratio[i]->SetTopMargin(-0.5);
          //    pad_ratio[i]->GetFrame()->SetY2(0.3);
          //    pad_ratio[i]->Draw();
          //    pad_cross[i]->cd();
          if(i==3) 
          {
            c_cross[i]->GetPad(1)->SetLogy();
            c_cross[i]->GetPad(1)->SetLogx();
            //      c_cross[i]->GetPad(2)->SetLogx();
          }
          if(i==2) 
          {
            c_cross[i]->GetPad(1)->SetLogy();
            c_cross[i]->GetPad(1)->SetLogx();
            h_window_cross[i][0]->GetXaxis()->SetMoreLogLabels();
          }
          if(i==4) 
          {
            c_cross[i]->GetPad(1)->SetLogy();
            //      c_cross[i]->GetPad(1)->SetLogx();
            //      c_cross[i]->GetPad(2)->SetLogx();
          }

          //
          // this was uncommented for paper: draw Natasha's cross section values
          //

          if(i==0)
            for(Int_t j = 0; j < number_etbins; j++) 
            {
              h_cross[i][0]->SetBinContent(j+1, y_1stcross_et[j]);
              h_cross[i][0]->SetBinError(j+1, y_1stcross_stat_err_et[j]);
            }
          if(i==1)
            for(Int_t j=0; j<number_etabins; j++) {
              h_cross[i][0]->SetBinContent(j+1, y_1stcross_eta[j]);
              h_cross[i][0]->SetBinError(j+1, y_1stcross_stat_err_eta[j]);
            }
          if(i==2)
            for(Int_t j=0; j<number_Q2bins; j++) {
              h_cross[i][0]->SetBinContent(j+1, y_1stcross_Q2[j]);
              h_cross[i][0]->SetBinError(j+1, y_1stcross_stat_err_Q2[j]);
            }
          if(i==3)
            for(Int_t j=0; j<number_xbins; j++) {
              h_cross[i][0]->SetBinContent(j+1, y_1stcross_x[j]);
              h_cross[i][0]->SetBinError(j+1, y_1stcross_stat_err_x[j]);
            }
          if(i==4) {
            for(Int_t j=0; j<number_et_jetbins; j++) {
              h_cross[i][0]->SetBinContent(j+1, y_1stcross_et_jet[j]);
              h_cross[i][0]->SetBinError(j+1, y_1stcross_stat_err_et_jet[j]);
            }
          }
          if(i==5) {
            for(Int_t j=0; j<number_eta_jetbins; j++) {
              h_cross[i][0]->SetBinContent(j+1, y_1stcross_eta_jet[j]);
              h_cross[i][0]->SetBinError(j+1, y_1stcross_stat_err_eta_jet[j]);
            }
          }
        }

        sign_window(c_cross[0]->GetPad(1), h_window_cross[0][0], "E_{T}^{#gamma} (GeV)", "d#sigma/dE_{T}^{#gamma} (pb/GeV)", "", "middle");
        //  sign_window(c_cross[0]->GetPad(2), h_window_cross[0][1], "E_{T}^{#gamma} (GeV)", "rel. uncertainty", "", "large");
        sign_window(c_cross[1]->GetPad(1), h_window_cross[1][0], "#eta^{#gamma}", "d#sigma/d#eta^{#gamma} (pb)", "", "middle");
        //  sign_window(c_cross[1]->GetPad(2), h_window_cross[1][1], "#eta_{#gamma}", "rel. uncertainty", "", "large");
        sign_window(c_cross[2]->GetPad(1), h_window_cross[2][0], "Q^{2} (GeV^{2})", "d#sigma/dQ^{2} (pb/GeV^{2})", "", "middle");
        //  sign_window(c_cross[2]->GetPad(2), h_window_cross[2][1], "Q^{2} (GeV^{2})", "rel. uncertainty", "", "large");
        sign_window(c_cross[3]->GetPad(1), h_window_cross[3][0], "x", "d#sigma/dx (pb)", "", "middle");
        //  sign_window(c_cross[3]->GetPad(2), h_window_cross[3][1], "x", "rel. uncertainty", "", "large");
        sign_window(c_cross[4]->GetPad(1), h_window_cross[4][0], "E_{T}^{jet} (GeV)", "d#sigma/dE_{T}^{jet} (pb/GeV)", "", "middle");
        //  sign_window(c_cross[4]->GetPad(2), h_window_cross[4][1], "E_{T, jet}", "rel. uncertainty", "", "large");
        sign_window(c_cross[5]->GetPad(1), h_window_cross[5][0], "#eta^{jet}", "d#sigma/d#eta^{jet} (pb)", "", "middle");
        //  sign_window(c_cross[5]->GetPad(2), h_window_cross[5][1], "#eta_{jet}", "rel. uncertainty", "", "large");

        //
        //cross_*.png
        //
        for(Int_t i = 0; i < n_cross; i++)
        {
          c_cross[i]->GetPad(1)->cd();
          if (nodebugmode) cout << i << " where is problem?" << endl;
          h_window_cross[i][0]->Draw();
          //    h_cross[i][0]->Draw("E3 SAME");
          //    h_cross[i][1]->Draw("E3 SAME");
          //    h_cross[i][2]->Draw("E3 SAME");
          //    h_cross[i][3]->Draw("E3 SAME");
          h_cross[i][0]->SetLineWidth(2);
          h_cross[i][1]->SetLineWidth(2);
          h_systematics[i]->SetLineWidth(2);

          //qwe h_Zotov[i]->DrawClone("2 SAME");
          //    h_Zotov[i]->DrawClone("5 Z X SAME");

          //    h_Spiesberger_pos_nlo[i]->Draw("a2 SAME");
          //    h_Spiesberger_pos_nlo[i]->Draw("2 SAME");

          //    h_Spiesberger_pos_lo[i]->Draw("2 SAME");
          //    h_Spiesberger_ele_lo[i]->Draw("2 SAME");
          //    h_Spiesberger_pos_nlo[i]->Draw("2 SAME");
          //    h_Spiesberger_ele_nlo[i]->Draw("2 SAME");

          //    h_Spiesberger_pos_lo[i]->Draw("5 Z SAME");
          //    h_Spiesberger_ele_lo[i]->Draw("5 Z SAME");
          //    h_Spiesberger_pos_nlo[i]->Draw("5 Z SAME");
          //    h_Spiesberger_ele_nlo[i]->Draw("5 Z SAME");
          if(i==0) {
            //      c_cross[i]->GetPad(1)->SetLogy();

            //qwe plot_box(number_etbins, x_et_bin, et_bin_err, et_bin_err, y_Zotov_et, y_Zotov_et_eyl, y_Zotov_et_eyh);
            //qwe plot_box_posele(number_etbins, x_et_bin, et_bin_err, et_bin_err, y_Spiesberger_ele_nlo_et, y_Spiesberger_ele_nlo_et_min, y_Spiesberger_ele_nlo_et_max, y_Spiesberger_pos_nlo_et, y_Spiesberger_pos_nlo_et_min, y_Spiesberger_pos_nlo_et_max);
            //      plot_box_posele_ra(number_etbins, x_et_bin, et_bin_err, et_bin_err, y_Spiesberger_ele_nlo_ra_et, zero_array, zero_array, y_Spiesberger_pos_nlo_ra_et, zero_array, zero_array);
            //      plot_box_posele_ra(number_etbins, x_et_bin, et_bin_err, et_bin_err, y_Spiesberger_ele_nlo_ra_fast_et, zero_array, zero_array, y_Spiesberger_pos_nlo_ra_fast_et, zero_array, zero_array, kBlue);
          }
          if(i==1) {
            //qwe plot_box(number_etabins, x_eta_bin, eta_bin_crosssec_err, eta_bin_crosssec_err, y_Zotov_eta, y_Zotov_eta_eyl, y_Zotov_eta_eyh);
            //qwe plot_box_posele(number_etabins, x_eta_bin, eta_bin_crosssec_err, eta_bin_crosssec_err, y_Spiesberger_ele_nlo_eta, y_Spiesberger_ele_nlo_eta_min, y_Spiesberger_ele_nlo_eta_max, y_Spiesberger_pos_nlo_eta, y_Spiesberger_pos_nlo_eta_min, y_Spiesberger_pos_nlo_eta_max);
            //      plot_box_posele_ra(number_etabins, x_eta_bin, eta_bin_crosssec_err, eta_bin_crosssec_err, y_Spiesberger_ele_nlo_ra_eta, zero_array, zero_array, y_Spiesberger_pos_nlo_ra_eta, zero_array, zero_array);
          }
          if(i==2) {
            //qwe plot_box(number_Q2bins, x_Q2_bin, Q2_bin_err, Q2_bin_err, y_Zotov_Q2, y_Zotov_Q2_eyl, y_Zotov_Q2_eyh);
            //qwe plot_box_posele(number_Q2bins, x_Q2_bin, Q2_bin_err, Q2_bin_err, y_Spiesberger_ele_nlo_Q2, y_Spiesberger_ele_nlo_Q2_min, y_Spiesberger_ele_nlo_Q2_max, y_Spiesberger_pos_nlo_Q2, y_Spiesberger_pos_nlo_Q2_min, y_Spiesberger_pos_nlo_Q2_max);
            //      plot_box_posele_ra(number_Q2bins, x_Q2_bin, Q2_bin_err, Q2_bin_err, y_Spiesberger_ele_nlo_ra_Q2, zero_array, zero_array, y_Spiesberger_pos_nlo_ra_Q2, zero_array, zero_array);
          }
          if(i==3) {
            //qwe plot_box(number_xbins, x_x_bin, x_bin_err, x_bin_err, y_Zotov_x, y_Zotov_x_eyl, y_Zotov_x_eyh);
            //qwe plot_box_posele(number_xbins, x_x_bin, x_bin_err, x_bin_err, y_Spiesberger_ele_nlo_x, y_Spiesberger_ele_nlo_x_min, y_Spiesberger_ele_nlo_x_max, y_Spiesberger_pos_nlo_x, y_Spiesberger_pos_nlo_x_min, y_Spiesberger_pos_nlo_x_max);
            //      plot_box_posele_ra(number_xbins, x_x_bin, x_bin_err, x_bin_err, y_Spiesberger_ele_nlo_ra_x, zero_array, zero_array, y_Spiesberger_pos_nlo_ra_x, zero_array, zero_array);
          }
          if(i==4) {
            //qwe plot_box(number_et_jetbins, x_et_jet_bin, et_jet_bin_err, et_jet_bin_err, y_Zotov_et_jet, y_Zotov_et_jet_eyl, y_Zotov_et_jet_eyh);
            //qwe plot_box_posele(number_et_jetbins, x_et_jet_bin, et_jet_bin_err, et_jet_bin_err, y_Spiesberger_ele_nlo_et_jet, y_Spiesberger_ele_nlo_et_jet_min, y_Spiesberger_ele_nlo_et_jet_max, y_Spiesberger_pos_nlo_et_jet, y_Spiesberger_pos_nlo_et_jet_min, y_Spiesberger_pos_nlo_et_jet_max);
            //      plot_box_posele_ra(number_et_jetbins, x_et_jet_bin, et_jet_bin_err, et_jet_bin_err, y_Spiesberger_ele_nlo_ra_et_jet, zero_array, zero_array, y_Spiesberger_pos_nlo_ra_et_jet, zero_array, zero_array);
          }
          if(i==5) {
            //qwe plot_box(number_eta_jetbins, x_eta_jet_bin, eta_jet_bin_err, eta_jet_bin_err, y_Zotov_eta_jet, y_Zotov_eta_jet_eyl, y_Zotov_eta_jet_eyh);
            //qwe plot_box_posele(number_eta_jetbins, x_eta_jet_bin, eta_jet_bin_err, eta_jet_bin_err, y_Spiesberger_ele_nlo_eta_jet, y_Spiesberger_ele_nlo_eta_jet_min, y_Spiesberger_ele_nlo_eta_jet_max, y_Spiesberger_pos_nlo_eta_jet, y_Spiesberger_pos_nlo_eta_jet_min, y_Spiesberger_pos_nlo_eta_jet_max);
            //      plot_box_posele_ra(number_eta_jetbins, x_eta_jet_bin, eta_jet_bin_err, eta_jet_bin_err, y_Spiesberger_ele_nlo_ra_eta_jet, zero_array, zero_array, y_Spiesberger_pos_nlo_ra_eta_jet, zero_array, zero_array);
          }
          //    h_Spiesberger_pos3C3C_nlo[i]->Draw("2 SAME");
          //    h_Spiesberger_pos_nlo[i]->Draw("3 SAME");
          //    h_Spiesberger_pos_nlo[i]->Draw("p SAME");
          //    h_Spiesberger_ele_nlo[i]->Draw("L SAME");
          //    h_Spiesberger_pos_lo[i]->Draw("L SAME");
          //    h_Spiesberger_ele_lo[i]->Draw("L SAME");
          //    h_Zotov[i]->SetFillColor(kRed);
          //    h_Zotov[i]->SetFillStyle(1001);
          //    h_Zotov[i]->SetMarkerStyle(20);
          //    h_Zotov[i]->SetMarkerSize(0.7);
          //this was for paper    //    h_cross[i][0]->Draw("E1 X0 SAME");
          h_cross[i][1]->SetMarkerStyle(20);
          h_cross[i][1]->SetMarkerSize(1);
          h_cross[i][1]->Draw("E1 X0 SAME"); //these are cross sections from root files
          //    h_systematics[i]->Draw("Z SAME");
          c_cross[i]->GetPad(1)->RedrawAxis();
          leg_cross[i]->Draw();
          //    c_cross[i]->GetPad(2)->cd();
          //    pad_ratio[i]->cd();
          //    h_window_cross[i][1]->Draw();
          //    h_cross[i][4]->Draw("E3 SAME");
          //    h_cross[i][5]->Draw("E3 SAME");
          //    h_cross[i][6]->Draw("E3 SAME");
          //    h_cross[i][7]->Draw("E3 SAME");
          if(s_var[i] == "Q2")
            for(Int_t bb=0; bb<h_cross[i][7]->GetNbinsX(); bb++)
              if (nodebugmode) cout << "lumi unc. in bin " << bb << ": " << h_cross[i][7]->GetBinError(bb+1) << " " << endl;
          //    h_cross[i][4]->Draw("E1 X0 SAME");
          TText* t_zeus = new TText(0.45, 0.95, "ZEUS");
          t_zeus->SetTextSize(0.07);
          t_zeus->SetTextFont(22);
          c_cross[i]->cd();
          t_zeus->Draw();
          c_cross[i]->Print("cross_" + s_var[i] + ".eps");
          c_cross[i]->Print("cross_" + s_var[i] + ".C");
          c_cross[i]->Print("cross_" + s_var[i] + ".png");
          c_cross[i]->Print("cross_" + s_var[i] + ".pdf");
        }

        //plot comparison of 1st and 2nd on the same Canvas
        for(Int_t i=0; i<n_cross; i++)
        {
          c_cross[i]->cd();
          if(i==3) 
          {
            c_cross[i]->GetPad(1)->SetLogy();
            c_cross[i]->GetPad(1)->SetLogx();
            //      c_cross[i]->GetPad(2)->SetLogx();
          }
          if(i==2) {
            c_cross[i]->GetPad(1)->SetLogy();
          }
          //    if(i==4) {
          //      c_cross[i]->GetPad(1)->SetLogy();
          //    }
          c_cross[i]->GetPad(1)->cd();
          h_window_cross[i][0]->Draw();
          //    h_cross[i][0]->Draw("E3 SAME");
          //    h_cross[i][1]->Draw("E3 SAME");
          //    h_cross[i][3]->Draw("E3 SAME");
          //    h_cross[i][2]->Draw("E3 SAME");
          if (nodebugmode) cout << "checkcheck2 : h_cross[i][0]->GetBinContent(1) = " << h_cross[i][0]->GetBinContent(1) << endl;
          h_cross[i][0]->Draw("E1 X0 SAME");
          if (nodebugmode) cout << "checkcheck2 after drawing : h_cross[i][0]->GetBinContent(1) = " << h_cross[i][0]->GetBinContent(1) << endl;

          Double_t xmin = h_1st_cross[i][0]->GetXaxis()->GetXmin();
          Double_t xmax = h_1st_cross[i][0]->GetXaxis()->GetXmax();
          Double_t deltax = xmax-xmin;
          h_1st_cross[i][0]->GetXaxis()->SetLimits(xmin + 0.01*deltax, xmax+0.01*deltax);
          h_1st_cross[i][0]->Draw("P E1 X0 SAME");
          leg_1st2nd[i]->Draw();
          //    c_cross[i]->GetPad(2)->cd();
          //    pad_ratio[i]->cd();
          h_window_cross[i][1]->GetYaxis()->SetTitle("rel. difference");
          //    h_window_cross[i][1]->Draw();
          //    h_cross[i][4]->Draw("E3 SAME");
          //    h_cross[i][5]->Draw("E3 SAME");
          //    h_cross[i][7]->Draw("E3 SAME");
          //    h_cross[i][6]->Draw("E3 SAME");
          //    h_cross[i][4]->Draw("E1 X0 SAME");
          //    f_unity->DrawClone("SAME");
          //    h_1st_cross[i][4]->Draw("E X0 SAME");
          if (nodebugmode) cout << "checkcheck2 before saving: h_cross[i][0]->GetBinContent(1) = " << h_cross[i][0]->GetBinContent(1) << endl;
          c_cross[i]->Print("comp_1st2nd_" + s_var[i] + ".eps");
          c_cross[i]->Print("comp_1st2nd_" + s_var[i] + ".C");
          c_cross[i]->Print("comp_1st2nd_" + s_var[i] + ".png");
          if (nodebugmode) cout << "checkcheck2 after saving: h_cross[i][0]->GetBinContent(1) = " << h_cross[i][0]->GetBinContent(1) << endl;
        }
        // plot systematic uncertainty
        for(Int_t i=0; i<n_cross; i++)
        {
          c_cross[i]->cd();
          if(i==3) {
            c_cross[i]->GetPad(1)->SetLogy();
            c_cross[i]->GetPad(1)->SetLogx();
            //      c_cross[i]->GetPad(2)->SetLogx();
          }
          if(i==2) {
            c_cross[i]->GetPad(1)->SetLogy();
          }
          c_cross[i]->GetPad(1)->cd();
          h_window_cross[i][0]->Draw();
          //    h_cross[i][0]->Draw("E3 SAME");
          //    h_cross[i][1]->Draw("E3 SAME");
          //    h_cross[i][3]->Draw("E3 SAME");
          //    h_cross[i][2]->Draw("E3 SAME");
          gr_cross[i][12]->Draw("E3 SAME");
          h_cross[i][0]->Draw("E1 X0 SAME");
          gr_cross[i][18]->Draw("E SAME");
          //    Double_t *a;
          //    a = gr_cross[i][18]->GetEYlow();
          //    if (nodebugmode) cout << "a " << a[0] << " " << a[1] << " " << a[2] << endl;
          //    h_1st_cross[i][0]->Draw("P E1 X0 SAME");
          if(i==0)
            leg_syst[i]->Draw();

          leg_syst_ratio[i]->Draw();
          //    c_cross[i]->GetPad(2)->cd();
          //    pad_ratio[i]->cd();
          h_window_cross[i][1]->GetYaxis()->SetTitle("rel. difference");
          //    h_window_cross[i][1]->Draw();
          //    f_unity->DrawClone("SAME");
          //0 - cross section value; 1 - stat. & fit parameter uncertainty; 2 - acceptance uncertainty
          //3 - lumi uncertainty; 4 - ratio (1); 5 - relative 1; 6 - relative 2; 7 - relative 3
          //8 - jet energy uncertainty; 9 - photon energy uncertainty; 10 - electron energy unc.
          //11 - deltaZ range uncertainty; 12 - 8+9+10+11 (in quadr); 13 - relative 8; 14 - relative 9
          //15 - relative 10; 16 - relative 11; 17 - relative 12
          //18 - syst+stat; 19 - relative 18
          //20, 21 - 8; 22, 23 - 9; 24, 25 - 10; 26, 27 - 11

          //    gr_cross[i][13]->DrawClone("E3 SAME");
          //    gr_cross[i][20]->DrawClone("L SAME");
          //    gr_cross[i][21]->DrawClone("L SAME");

          //    gr_cross[i][14]->DrawClone("E3 SAME");
          //    gr_cross[i][22]->DrawClone("L SAME");
          //    gr_cross[i][23]->DrawClone("L SAME");

          //    gr_cross[i][15]->DrawClone("E3 SAME");
          //    gr_cross[i][24]->DrawClone("L SAME");
          //    gr_cross[i][25]->DrawClone("L SAME");

          //    gr_cross[i][16]->DrawClone("E3 SAME");
          //    gr_cross[i][26]->DrawClone("L SAME");
          //    gr_cross[i][27]->DrawClone("L SAME");

          //    gr_cross[i][17]->DrawClone("E SAME");


          c_cross[i]->Print("syst_" + s_var[i] + ".eps");
          c_cross[i]->Print("syst_" + s_var[i] + ".C");
          c_cross[i]->Print("syst_" + s_var[i] + ".png");
        }
    */
}
