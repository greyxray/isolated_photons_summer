#include <TMath.h>
#include "selector.h"

Double_t selector::q2_reweighting(Float_t Mc_q2, TString mc_type)
{
  Double_t res = 1.;
  if(mc_type == "mc_bg_norad") {
    res = 1.06663 - 0.00182823*Mc_q2;
  }
  if(mc_type == "mc_prph") {
    res = 1.31306 - 0.0076222*Mc_q2 + 1.59938e-05*Mc_q2*Mc_q2;
  }
  if(res < 0) res = 0.;
  return res;
}
