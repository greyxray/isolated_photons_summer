#include <TMath.h>
#include "selector.h"

Double_t selector::y_reweighting_binbybin(Float_t Mc_y, TString mc_type)
{
  Double_t res = 1.;
  if(mc_type == "mc_bg_norad") {
    //res = 1.12129 - 1.54118 * Mc_y + 3.12332*Mc_y*Mc_y;
    if(Mc_y>0.5 && Mc_y<0.55) res = 1.05463;
    if(Mc_y>0.55 && Mc_y<0.6) res = 1.42949;
    if(Mc_y>0.6 && Mc_y<0.65) res = 1.44929;
    if(Mc_y>0.65) res = 1.16928;
  }
  if(mc_type == "mc_prph") {
    //    res = 0.897484 - 0.449061*Mc_q2 + 2.16786*Mc_y*Mc_y;
    if(Mc_y>0.5 && Mc_y<0.55) res = 1.2666;
    if(Mc_y>0.55 && Mc_y<0.6) res = 1.47405;
    if(Mc_y>0.6 && Mc_y<0.65) res = 1.6258;
    if(Mc_y>0.65) res = 1.87158;
  }
  return res;
}
