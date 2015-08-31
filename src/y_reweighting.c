#include <TMath.h>
#include "selector.h"

Double_t selector::y_reweighting(Float_t Mc_y, TString mc_type)
{
  Double_t res = 1.;
  if(mc_type == "mc_bg_norad") {
    res = 1.12129 - 1.54118 * Mc_y + 3.12332*Mc_y*Mc_y;
  }
  if(mc_type == "mc_prph") {
    res = 0.897484 - 0.449061*Mc_q2 + 2.16786*Mc_y*Mc_y;
  }
  return res;
}
