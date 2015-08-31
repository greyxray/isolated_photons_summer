#include <TMath.h>
#include "selector.h"

Double_t selector::etph_reweighting(Double_t et, TString mc_type)
{
  Double_t res = 1.;

  //  if(mc_type == "mc_bg_norad") {
  //    res = 0.996392 + eta * 0.223788;
  //  }
  
  if(mc_type == "mc_bg_norad") {
    res = 1.85984 - 0.186233*et + 0.00654264*et*et;
  }
  if(mc_type == "mc_prph") {
    res = 2.19133 - 0.29713*et + 0.0158536*et*et;
  }
  
  return res;
}
