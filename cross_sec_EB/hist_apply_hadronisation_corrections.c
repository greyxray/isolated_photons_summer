#include <TMath.h>

void Hist::apply_hadronisation_corrections()
{
  for(Int_t i=0; i<number_etbins; i++){
    y_Spiesberger_pos_nlo_et[i] *= hadronisation_et[i];
    y_Spiesberger_pos_nlo_et_max[i] *= hadronisation_et[i];
    y_Spiesberger_pos_nlo_et_min[i] *= hadronisation_et[i];
    y_Spiesberger_pos_lo_et[i] *= hadronisation_et[i];
    y_Spiesberger_pos_lo_et_min[i] *= hadronisation_et[i];
    y_Spiesberger_pos_lo_et_max[i] *= hadronisation_et[i];

    y_Spiesberger_ele_nlo_et[i] *= hadronisation_et[i];
    y_Spiesberger_ele_nlo_et_max[i] *= hadronisation_et[i];
    y_Spiesberger_ele_nlo_et_min[i] *= hadronisation_et[i];
    y_Spiesberger_ele_lo_et[i] *= hadronisation_et[i];
    y_Spiesberger_ele_lo_et_min[i] *= hadronisation_et[i];
    y_Spiesberger_ele_lo_et_max[i] *= hadronisation_et[i];

    y_Spiesberger_pos_nlo_ra_et[i] *= hadronisation_et[i];
    y_Spiesberger_ele_nlo_ra_et[i] *= hadronisation_et[i];

    y_Spiesberger_pos_nlo_ra_fast_et[i] *= hadronisation_et[i];
    y_Spiesberger_ele_nlo_ra_fast_et[i] *= hadronisation_et[i];

    y_Zotov_et[i] *= hadronisation_et[i];
    y_Zotov_et_eyh[i] *= hadronisation_et[i];
    y_Zotov_et_eyl[i] *= hadronisation_et[i];
  }

  for(Int_t i=0; i<number_etabins; i++){
    y_Spiesberger_pos_nlo_eta[i] *= hadronisation_eta[i];
    y_Spiesberger_pos_nlo_eta_max[i] *= hadronisation_eta[i];
    y_Spiesberger_pos_nlo_eta_min[i] *= hadronisation_eta[i];
    y_Spiesberger_pos_lo_eta[i] *= hadronisation_eta[i];
    y_Spiesberger_pos_lo_eta_min[i] *= hadronisation_eta[i];
    y_Spiesberger_pos_lo_eta_max[i] *= hadronisation_eta[i];

    y_Spiesberger_ele_nlo_eta[i] *= hadronisation_eta[i];
    y_Spiesberger_ele_nlo_eta_max[i] *= hadronisation_eta[i];
    y_Spiesberger_ele_nlo_eta_min[i] *= hadronisation_eta[i];
    y_Spiesberger_ele_lo_eta[i] *= hadronisation_eta[i];
    y_Spiesberger_ele_lo_eta_min[i] *= hadronisation_eta[i];
    y_Spiesberger_ele_lo_eta_max[i] *= hadronisation_eta[i];

    y_Spiesberger_pos_nlo_ra_eta[i] *= hadronisation_eta[i];
    y_Spiesberger_ele_nlo_ra_eta[i] *= hadronisation_eta[i];

    y_Spiesberger_pos_nlo_ra_fast_eta[i] *= hadronisation_eta[i];
    y_Spiesberger_ele_nlo_ra_fast_eta[i] *= hadronisation_eta[i];

    y_Zotov_eta[i] *= hadronisation_eta[i];
    y_Zotov_eta_eyh[i] *= hadronisation_eta[i];
    y_Zotov_eta_eyl[i] *= hadronisation_eta[i];
  }

  for(Int_t i=0; i<number_Q2bins; i++){
    y_Spiesberger_pos_nlo_Q2[i] *= hadronisation_Q2[i];
    y_Spiesberger_pos_nlo_Q2_max[i] *= hadronisation_Q2[i];
    y_Spiesberger_pos_nlo_Q2_min[i] *= hadronisation_Q2[i];
    y_Spiesberger_pos_lo_Q2[i] *= hadronisation_Q2[i];
    y_Spiesberger_pos_lo_Q2_min[i] *= hadronisation_Q2[i];
    y_Spiesberger_pos_lo_Q2_max[i] *= hadronisation_Q2[i];

    y_Spiesberger_ele_nlo_Q2[i] *= hadronisation_Q2[i];
    y_Spiesberger_ele_nlo_Q2_max[i] *= hadronisation_Q2[i];
    y_Spiesberger_ele_nlo_Q2_min[i] *= hadronisation_Q2[i];
    y_Spiesberger_ele_lo_Q2[i] *= hadronisation_Q2[i];
    y_Spiesberger_ele_lo_Q2_min[i] *= hadronisation_Q2[i];
    y_Spiesberger_ele_lo_Q2_max[i] *= hadronisation_Q2[i];

    y_Spiesberger_pos_nlo_ra_Q2[i] *= hadronisation_Q2[i];
    y_Spiesberger_ele_nlo_ra_Q2[i] *= hadronisation_Q2[i];

    y_Spiesberger_pos_nlo_ra_fast_Q2[i] *= hadronisation_Q2[i];
    y_Spiesberger_ele_nlo_ra_fast_Q2[i] *= hadronisation_Q2[i];

    y_Zotov_Q2[i] *= hadronisation_Q2[i];
    y_Zotov_Q2_eyh[i] *= hadronisation_Q2[i];
    y_Zotov_Q2_eyl[i] *= hadronisation_Q2[i];
  }

  for(Int_t i=0; i<number_xbins; i++){
    y_Spiesberger_pos_nlo_x[i] *= hadronisation_x[i];
    y_Spiesberger_pos_nlo_x_max[i] *= hadronisation_x[i];
    y_Spiesberger_pos_nlo_x_min[i] *= hadronisation_x[i];
    y_Spiesberger_pos_lo_x[i] *= hadronisation_x[i];
    y_Spiesberger_pos_lo_x_min[i] *= hadronisation_x[i];
    y_Spiesberger_pos_lo_x_max[i] *= hadronisation_x[i];

    y_Spiesberger_ele_nlo_x[i] *= hadronisation_x[i];
    y_Spiesberger_ele_nlo_x_max[i] *= hadronisation_x[i];
    y_Spiesberger_ele_nlo_x_min[i] *= hadronisation_x[i];
    y_Spiesberger_ele_lo_x[i] *= hadronisation_x[i];
    y_Spiesberger_ele_lo_x_min[i] *= hadronisation_x[i];
    y_Spiesberger_ele_lo_x_max[i] *= hadronisation_x[i];

    y_Spiesberger_pos_nlo_ra_x[i] *= hadronisation_x[i];
    y_Spiesberger_ele_nlo_ra_x[i] *= hadronisation_x[i];

    y_Spiesberger_pos_nlo_ra_fast_x[i] *= hadronisation_x[i];
    y_Spiesberger_ele_nlo_ra_fast_x[i] *= hadronisation_x[i];

    y_Zotov_x[i] *= hadronisation_x[i];
    y_Zotov_x_eyh[i] *= hadronisation_x[i];
    y_Zotov_x_eyl[i] *= hadronisation_x[i];
  }

  for(Int_t i=0; i<number_et_jetbins; i++){
    y_Spiesberger_pos_nlo_et_jet[i] *= hadronisation_et_jet[i];
    y_Spiesberger_pos_nlo_et_jet_max[i] *= hadronisation_et_jet[i];
    y_Spiesberger_pos_nlo_et_jet_min[i] *= hadronisation_et_jet[i];
    y_Spiesberger_pos_lo_et_jet[i] *= hadronisation_et_jet[i];
    y_Spiesberger_pos_lo_et_jet_min[i] *= hadronisation_et_jet[i];
    y_Spiesberger_pos_lo_et_jet_max[i] *= hadronisation_et_jet[i];

    y_Spiesberger_ele_nlo_et_jet[i] *= hadronisation_et_jet[i];
    y_Spiesberger_ele_nlo_et_jet_max[i] *= hadronisation_et_jet[i];
    y_Spiesberger_ele_nlo_et_jet_min[i] *= hadronisation_et_jet[i];
    y_Spiesberger_ele_lo_et_jet[i] *= hadronisation_et_jet[i];
    y_Spiesberger_ele_lo_et_jet_min[i] *= hadronisation_et_jet[i];
    y_Spiesberger_ele_lo_et_jet_max[i] *= hadronisation_et_jet[i];

    y_Spiesberger_pos_nlo_ra_et_jet[i] *= hadronisation_et_jet[i];
    y_Spiesberger_ele_nlo_ra_et_jet[i] *= hadronisation_et_jet[i];

    y_Spiesberger_pos_nlo_ra_fast_et_jet[i] *= hadronisation_et_jet[i];
    y_Spiesberger_ele_nlo_ra_fast_et_jet[i] *= hadronisation_et_jet[i];

    y_Zotov_et_jet[i] *= hadronisation_et_jet[i];
    y_Zotov_et_jet_eyh[i] *= hadronisation_et_jet[i];
    y_Zotov_et_jet_eyl[i] *= hadronisation_et_jet[i];
  }

  for(Int_t i=0; i<number_eta_jetbins; i++){
    y_Spiesberger_pos_nlo_eta_jet[i] *= hadronisation_eta_jet[i];
    y_Spiesberger_pos_nlo_eta_jet_max[i] *= hadronisation_eta_jet[i];
    y_Spiesberger_pos_nlo_eta_jet_min[i] *= hadronisation_eta_jet[i];
    y_Spiesberger_pos_lo_eta_jet[i] *= hadronisation_eta_jet[i];
    y_Spiesberger_pos_lo_eta_jet_min[i] *= hadronisation_eta_jet[i];
    y_Spiesberger_pos_lo_eta_jet_max[i] *= hadronisation_eta_jet[i];

    y_Spiesberger_ele_nlo_eta_jet[i] *= hadronisation_eta_jet[i];
    y_Spiesberger_ele_nlo_eta_jet_max[i] *= hadronisation_eta_jet[i];
    y_Spiesberger_ele_nlo_eta_jet_min[i] *= hadronisation_eta_jet[i];
    y_Spiesberger_ele_lo_eta_jet[i] *= hadronisation_eta_jet[i];
    y_Spiesberger_ele_lo_eta_jet_min[i] *= hadronisation_eta_jet[i];
    y_Spiesberger_ele_lo_eta_jet_max[i] *= hadronisation_eta_jet[i];

    y_Spiesberger_pos_nlo_ra_eta_jet[i] *= hadronisation_eta_jet[i];
    y_Spiesberger_ele_nlo_ra_eta_jet[i] *= hadronisation_eta_jet[i];

    y_Spiesberger_pos_nlo_ra_fast_eta_jet[i] *= hadronisation_eta_jet[i];
    y_Spiesberger_ele_nlo_ra_fast_eta_jet[i] *= hadronisation_eta_jet[i];

    y_Zotov_eta_jet[i] *= hadronisation_eta_jet[i];
    y_Zotov_eta_jet_eyh[i] *= hadronisation_eta_jet[i];
    y_Zotov_eta_jet_eyl[i] *= hadronisation_eta_jet[i];
  }

  
}
