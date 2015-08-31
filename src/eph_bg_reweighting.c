#include <TMath.h>
#include "selector.h"

Double_t selector::eph_bg_reweighting(Double_t et)
{
  Double_t res = 1.;

  if(mc_type == "mc_bg_norad") {    
    res = 0.74599 + 1.29083 * TMath::Exp(-0.25546 * et);
  }
  return res;
}
