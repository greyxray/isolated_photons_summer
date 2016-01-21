#include "TH1D.h"
#include "selector.h"
#include "constants.h"
#include <iostream>
using namespace std;


Double_t selector::jet_en_corr(Double_t eta, Double_t et, TString period, TString mc_type)
{
  const Int_t           num_eta_bins = 16;
  Double_t        eta_min = -1.5;
  Double_t        eta_max = 1.8;
  Double_t        eta_bins[num_eta_bins+1] = {-1.5, -1.25, -1.0, -0.75, -0.5, -0.25, 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5};
  Double_t a0_corr040506e[num_eta_bins] = {
    0.0693067, 
    0.0973818, 
    0.133861, 
    0.205572, 
    0.171483, 
    0.169074, 
    0.16055, 
    0.204202, 
    0.223907, 
    0.266871, 
    0.414456, 
    0.307104, 
    0.157326, 
    0.017408, 
    -0.0957113, 
    -0.16327
  };
  Double_t a1_corr040506e[num_eta_bins] = {
    0.850954, 
    0.8585, 
    0.860205, 
    0.860814, 
    0.88126, 
    0.892621, 
    0.90243, 
    0.89551, 
    0.891623, 
    0.876154, 
    0.846797, 
    0.868492, 
    0.889625, 
    0.901179, 
    0.912809, 
    0.951853
  };
  Double_t a0_corr0607p[num_eta_bins] = {
    0.378383, 
    0.165236, 
    0.131539, 
    0.205586, 
    0.209384, 
    0.156212, 
    0.16638, 
    0.227579, 
    0.220046, 
    0.30041, 
    0.410359, 
    0.338179, 
    0.137334, 
    -0.00163451, 
    -0.099333, 
    -0.08347  };
  Double_t a1_corr0607p[num_eta_bins] = {
    0.731974, 
    0.83166, 
    0.86174, 
    0.860348, 
    0.871313, 
    0.894909, 
    0.902218, 
    0.889853, 
    0.892856, 
    0.868316, 
    0.849516, 
    0.862436, 
    0.894076, 
    0.909222, 
    0.914492, 
    0.935125  
  };

  Double_t a0_corr_prph[num_eta_bins] = {
    0.172999, 
    0.0178937, 
    -0.0106123, 
    -0.012102, 
    0.222929, 
    -0.0623331, 
    -0.0652804, 
    0.386358, 
    0.0357075, 
    -0.0468965, 
    0.182879, 
    -0.401991, 
    0.043872, 
    -0.192039, 
    -0.662836, 
    0.620102
  };
  Double_t a1_corr_prph[num_eta_bins] = {
    0.845657, 
    0.898699, 
    0.889519, 
    0.933257, 
    0.88217, 
    0.986758, 
    1.00725, 
    0.912114, 
    0.952196, 
    0.948742, 
    0.843957, 
    1.0041, 
    0.973381, 
    1.01482, 
    1.03749, 
    0.931508
  };

  Double_t a1_corr, a0_corr;
  Double_t et_corr = 0.;
  Double_t corfac = 1.;

  for(Int_t i=0; i<num_eta_bins; i++)
  {
    if(eta>eta_bins[i] && eta<eta_bins[i+1])
    {
      if(period == "0405e" || period == "06e")
      {
        a1_corr = a1_corr040506e[i];
        a0_corr = a0_corr040506e[i];
      }
      if(period == "0607p" || period == "04p") 
      {
        a1_corr = a1_corr0607p[i];
        a0_corr = a0_corr0607p[i];
      }
      if(!Data && mc_type == "mc_prph") 
      {
        a1_corr = a1_corr_prph[i];
        a0_corr = a0_corr_prph[i];
      }
      et_corr = (et - a0_corr) / a1_corr;
      //	  et_corr = (-a1_corr[i]+sqrt(a1_corr[i]*a1_corr[i]-4*a2_corr[i]*(a0_corr[i]-et)))*(0.5/a2_corr[i]);
      ///	  corfac = (1./a1_corr[i]) - (a0_corr[i]/(a1_corr[i] * et));
    }
  }
  //  cout << "return " << et_corr << endl;
  if(check_cuts)
    cout << "return value: " << eta << ", " << et  << ", " << period << ", " << mc_type << ", " << et_corr << ", " << a0_corr << ", " << a1_corr << endl;
  return et_corr;
}

Double_t selector::jet_en_corr(Double_t eta, Double_t et, Double_t* C_scale, Double_t* a0_corr, Double_t* a1_corr, Double_t* a2_corr)
{
  Double_t res = 0.;
  return res;
}
