#include <TMath.h>
#include "selector.h"

Double_t selector::etph_bg_reweighting(Double_t et)
{
  Double_t res = 1.;

  if(mc_type == "mc_bg_norad") {    
    res = 0.792989 + 4.31617 * TMath::Exp(-0.538149 * et);
  }
  return res;
}
