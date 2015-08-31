#include "iostream"
#include <fstream>
#include <vector>
using namespace std;
#include <TROOT.h>
#include <TSystem.h>
#include <TROOT.h>
#include <TH1.h>

#include <TCanvas.h>
#include <TChain.h>
#include <TMath.h>
#include <TChain.h>
#include "stdlib.h"
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TNtuple.h>
#include <TF1.h>
#include <TVector3.h>
#include <math.h>
#include <string.h>
#include <TTree.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include "plot_style_utils.h"

using namespace std;

int main(int argc, char** argv) 

//int main()
{

gROOT->Reset();
gROOT->SetStyle("Plain");

const Int_t n=4;
const Int_t q=5;
const Int_t j=6;



// *************** et_jet_systematics  sys_un_2 *************** //
// eta_photon
Double_t x_un2_eta_1[n] = {-.5,-.1,.3,.7};
Double_t y_un2_eta_1[n] = {0.079406345, 0.080874765, 0.097399971, 0.103643608};  //eta rel_sigma (povna vidnosna stat.poh.)

Double_t x_un2_eta_2[n] = {-.5,-.1,.3,.7};
Double_t y_un2_eta_2[n] = {-0.079406345, -0.080874765, -0.097399971, -0.103643608};  //eta rel_sigma (povna vidnosna stat.poh.)

Double_t x_un2_eta_3[n] = {-.5,-.1,.3,.7};
Double_t y_un2_eta_3[n] = {0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un2_eta_4[n] = {-.5,-.1,.3,.7};
Double_t y_un2_eta_4[n] = {-0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un2_eta_5[n] = {-.5,-.1,.3,.7};
Double_t y_un2_eta_5[n] = {-0.024177902, -0.035505566, -0.010840235, -0.011457470};    //eta rel_delta_syst2_minus

Double_t x_un2_eta_6[n] = {-.5,-.1,.3,.7};
Double_t y_un2_eta_6[n] = {0.028470958, 0.033470934, 0.011028101, 0.020822468};    //eta rel_delta_syst2_plus

Double_t x_un2_eta_7[n] = {-.5,-.1,.3,.7};
Double_t y_un2_eta_7[n] = {.0,.0,.0,.0};  //0 line 


// E_T_photon
Double_t x_un2_et_1[n] = {5.,7.,9.,12.5};
Double_t y_un2_et_1[n] = {0.073909070, 0.079935692, 0.121903012, 0.105632500};  //Et rel_sigma (povna vidnosna stat.poh.)

Double_t x_un2_et_2[n] = {5.,7.,9.,12.5};
Double_t y_un2_et_2[n] = {-0.073909070, -0.079935692, -0.121903012, -0.105632500};  //Et rel_sigma (povna vidnosna stat.poh.)

Double_t x_un2_et_3[n] = {5.,7.,9.,12.5};
Double_t y_un2_et_3[n] = {0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un2_et_4[n] = {5.,7.,9.,12.5};
Double_t y_un2_et_4[n] = {-0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un2_et_5[n] = {5.,7.,9.,12.5};
Double_t y_un2_et_5[n] = {-0.018893745, -0.037252904, -0.012517590, -0.015735340};    //Et rel_delta_syst2_minus

Double_t x_un2_et_6[n] = {5.,7.,9.,12.5};
Double_t y_un2_et_6[n] = {0.029104566, 0.020115491, 0.032582598, 0.026898844};    //Et rel_delta_syst2_plus

Double_t x_un2_et_7[n] = {5.,7.,9.,12.5};
Double_t y_un2_et_7[n] = {.0,.0,.0,.0};  //0 line


// Q2_photon
Double_t x_un2_q2_1[q] = {15.,30.,60.,115.,250.};
Double_t y_un2_q2_1[q] = {0.082699930, 0.091492816, 0.113197388, 0.106888231, 0.179507320};  //q2 rel_sigma (povna vidnosna stat.poh.)

Double_t x_un2_q2_2[q] = {15.,30.,60.,115.,250.};
Double_t y_un2_q2_2[q] = {-0.082699930, -0.091492816, -0.113197388, -0.106888231, -0.179507320};  //q2 rel_sigma (povna vidnosna stat.poh.)

Double_t x_un2_q2_3[q] = {15.,30.,60.,115.,250.};
Double_t y_un2_q2_3[q] = {0.1, 0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un2_q2_4[q] = {15.,30.,60.,115.,250.};
Double_t y_un2_q2_4[q] = {-0.1, -0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un2_q2_5[q] = {15.,30.,60.,115.,250.};
Double_t y_un2_q2_5[q] = {-0.024452260, -0.025403275, -0.024860229, -0.018780249, -0.009075061};    //q2 rel_delta_syst2_minus

Double_t x_un2_q2_6[q] = {15.,30.,60.,115.,250.};
Double_t y_un2_q2_6[q] = {0.034317282, 0.014117252, 0.026177066, 0.022899992, 0.036832473};    //q2 rel_delta_syst2_plus

Double_t x_un2_q2_7[q] = {15.,30.,60.,115.,250.};
Double_t y_un2_q2_7[q] = {.0,.0,.0,.0,.0};  //0 line


// x
Double_t x_un2_x_1[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un2_x_1[n] = {0.070535686, 0.079400073, 0.122084542, 0.255756947};  //x rel_sigma (povna vidnosna stat.poh.)

Double_t x_un2_x_2[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un2_x_2[n] = {-0.070535686, -0.079400073, -0.122084542, -0.255756947};  //x rel_sigma (povna vidnosna stat.poh.)

Double_t x_un2_x_3[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un2_x_3[n] = {0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un2_x_4[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un2_x_4[n] = {-0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un2_x_5[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un2_x_5[n] = {-0.021442227, -0.020372435, -0.027431208, -0.013914258};    //x rel_delta_syst2_minus

Double_t x_un2_x_6[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un2_x_6[n] = {0.019155168, 0.035512973, 0.019725354, 0.019765556};    //x rel_delta_syst2_plus

Double_t x_un2_x_7[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un2_x_7[n] = {.0,.0,.0,.0};  //0 line


// eta_jet
Double_t x_un2_eta_jet_1[n] = {-1.1,-.3,.4,1.35};
Double_t y_un2_eta_jet_1[n] = {0.114665875, 0.092753821, 0.084312295, 0.085367962};  //eta_jet rel_sigma (povna vidnosna stat.poh.)

Double_t x_un2_eta_jet_2[n] = {-1.1,-.3,.4,1.35};
Double_t y_un2_eta_jet_2[n] = {-0.114665875, -0.092753821, -0.084312295, -0.085367962};  //eta_jet rel_sigma (povna vidnosna stat.poh.)

Double_t x_un2_eta_jet_3[n] = {-1.1,-.3,.4,1.35};
Double_t y_un2_eta_jet_3[n] = {0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un2_eta_jet_4[n] = {-1.1,-.3,.4,1.35};
Double_t y_un2_eta_jet_4[n] = {-0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un2_eta_jet_5[n] = {-1.1,-.3,.4,1.35};
Double_t y_un2_eta_jet_5[n] = {-0.029849271, -0.011559036, -0.018075512, -0.032109346};    //eta_jet rel_delta_syst2_minus

Double_t x_un2_eta_jet_6[n] = {-1.1,-.3,.4,1.35};
Double_t y_un2_eta_jet_6[n] = {0.015021484, 0.025244846, 0.019090278, 0.033766878};    //eta_jet rel_delta_syst2_plus

Double_t x_un2_eta_jet_7[n] = {-1.1,-.3,.4,1.35};
Double_t y_un2_eta_jet_7[n] = {.0,.0,.0,.0};  //0 line 


// E_T_jet
Double_t x_un2_et_jet_1[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un2_et_jet_1[j] = {0.117236814, 0.096753041, 0.100163383, 0.101394600, 0.098390559, 0.173877469};  //Et_jet rel_sigma (povna vidnosna stat.poh.)

Double_t x_un2_et_jet_2[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un2_et_jet_2[j] = {-0.117236814, -0.096753041, -0.100163383, -0.101394600, -0.098390559, -0.173877469};  //Et_jet rel_sigma (povna vidnosna stat.poh.)

Double_t x_un2_et_jet_3[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un2_et_jet_3[j] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un2_et_jet_4[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un2_et_jet_4[j] = {-0.1, -0.1, -0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un2_et_jet_5[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un2_et_jet_5[j] = {-0.032357481, -0.045185801, -0.026026670, -0.064214079, -0.007117438, -0.102824513};    //Et_jet rel_delta_syst2_minus

Double_t x_un2_et_jet_6[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un2_et_jet_6[j] = {0.006947925, 0.014442508, 0.050377038, 0.036371919, 0.046573480, 0.111344571};    //Et_jet rel_delta_syst2_plus

Double_t x_un2_et_jet_7[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un2_et_jet_7[j] = {.0,.0,.0,.0,.0,.0};  //0 line
// *************** et_jet_systematics   sys_un_2 *************** // 


// *************** en_photon_systematics   sys_un_3 *************** //
// eta_photon
Double_t x_un3_eta_1[n] = {-.5,-.1,.3,.7};
Double_t y_un3_eta_1[n] = {0.079406345, 0.080874765, 0.097399971, 0.103643608};  //eta rel_sigma (povna vidnosna stat.poh.)

Double_t x_un3_eta_2[n] = {-.5,-.1,.3,.7};
Double_t y_un3_eta_2[n] = {-0.079406345, -0.080874765, -0.097399971, -0.103643608};  //eta rel_sigma (povna vidnosna stat.poh.)

Double_t x_un3_eta_3[n] = {-.5,-.1,.3,.7};
Double_t y_un3_eta_3[n] = {0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un3_eta_4[n] = {-.5,-.1,.3,.7};
Double_t y_un3_eta_4[n] = {-0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un3_eta_5[n] = {-.5,-.1,.3,.7};
Double_t y_un3_eta_5[n] = {-0.070811580, -0.045496289, -0.021821369, -0.031719454};    //eta rel_delta_syst3_minus

Double_t x_un3_eta_6[n] = {-.5,-.1,.3,.7};
Double_t y_un3_eta_6[n] = {0.003378857, 0.002325294, 0.009872002, 0.032820756};    //eta rel_delta_syst3_plus

Double_t x_un3_eta_7[n] = {-.5,-.1,.3,.7};
Double_t y_un3_eta_7[n] = {.0,.0,.0,.0};  //0 line 


// E_T_photon
Double_t x_un3_et_1[n] = {5.,7.,9.,12.5};
Double_t y_un3_et_1[n] = {0.073909070, 0.079935692, 0.121903012, 0.105632500};  //Et rel_sigma (povna vidnosna stat.poh.)

Double_t x_un3_et_2[n] = {5.,7.,9.,12.5};
Double_t y_un3_et_2[n] = {-0.073909070, -0.079935692, -0.121903012, -0.105632500};  //Et rel_sigma (povna vidnosna stat.poh.)

Double_t x_un3_et_3[n] = {5.,7.,9.,12.5};
Double_t y_un3_et_3[n] = {0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un3_et_4[n] = {5.,7.,9.,12.5};
Double_t y_un3_et_4[n] = {-0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un3_et_5[n] = {5.,7.,9.,12.5};
Double_t y_un3_et_5[n] = {-0.055890372, -0.009419036, -0.014128369, -0.075032132};    //Et rel_delta_syst3_minus

Double_t x_un3_et_6[n] = {5.,7.,9.,12.5};
Double_t y_un3_et_6[n] = {0.005821741, 0.003662959, 0.027700578, 0.025858691};    //Et rel_delta_syst3_plus

Double_t x_un3_et_7[n] = {5.,7.,9.,12.5};
Double_t y_un3_et_7[n] = {.0,.0,.0,.0};  //0 line


// Q2_photon
Double_t x_un3_q2_1[q] = {15.,30.,60.,115.,250.};
Double_t y_un3_q2_1[q] = {0.082699930, 0.091492816, 0.113197388, 0.106888231, 0.179507320};  //q2 rel_sigma (povna vidnosna stat.poh.)

Double_t x_un3_q2_2[q] = {15.,30.,60.,115.,250.};
Double_t y_un3_q2_2[q] = {-0.082699930, -0.091492816, -0.113197388, -0.106888231, -0.179507320};  //q2 rel_sigma (povna vidnosna stat.poh.)

Double_t x_un3_q2_3[q] = {15.,30.,60.,115.,250.};
Double_t y_un3_q2_3[q] = {0.1, 0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un3_q2_4[q] = {15.,30.,60.,115.,250.};
Double_t y_un3_q2_4[q] = {-0.1, -0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un3_q2_5[q] = {15.,30.,60.,115.,250.};
Double_t y_un3_q2_5[q] = {-0.084750283, -0.054641153, -0.018887801, -0.055533044, -0.015860990};    //q2 rel_delta_syst3_minus

Double_t x_un3_q2_6[q] = {15.,30.,60.,115.,250.};
Double_t y_un3_q2_6[q] = {0.015144604, 0.008338123, 0.043862087, 0.002436649, 0.014563001};    //q2 rel_delta_syst3_plus

Double_t x_un3_q2_7[q] = {15.,30.,60.,115.,250.};
Double_t y_un3_q2_7[q] = {.0,.0,.0,.0,.0};  //0 line


// x
Double_t x_un3_x_1[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un3_x_1[n] = {0.070535686, 0.079400073, 0.122084542, 0.255756947};  //x rel_sigma (povna vidnosna stat.poh.)

Double_t x_un3_x_2[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un3_x_2[n] = {-0.070535686, -0.079400073, -0.122084542, -0.255756947};  //x rel_sigma (povna vidnosna stat.poh.)

Double_t x_un3_x_3[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un3_x_3[n] = {0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un3_x_4[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un3_x_4[n] = {-0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un3_x_5[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un3_x_5[n] = {-0.067995678, -0.020613562, -0.053108722, -0.007689954};    //x rel_delta_syst3_minus

Double_t x_un3_x_6[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un3_x_6[n] = {0.027832909, 0.041131794, 0.029705067, 0.064070393};    //x rel_delta_syst3_plus

Double_t x_un3_x_7[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un3_x_7[n] = {.0,.0,.0,.0};  //0 line


// eta_jet
Double_t x_un3_eta_jet_1[n] = {-1.1,-.3,.4,1.35};
Double_t y_un3_eta_jet_1[n] = {0.114665875, 0.092753821, 0.084312295, 0.085367962};  //eta_jet rel_sigma (povna vidnosna stat.poh.)

Double_t x_un3_eta_jet_2[n] = {-1.1,-.3,.4,1.35};
Double_t y_un3_eta_jet_2[n] = {-0.114665875, -0.092753821, -0.084312295, -0.085367962};  //eta_jet rel_sigma (povna vidnosna stat.poh.)

Double_t x_un3_eta_jet_3[n] = {-1.1,-.3,.4,1.35};
Double_t y_un3_eta_jet_3[n] = {0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un3_eta_jet_4[n] = {-1.1,-.3,.4,1.35};
Double_t y_un3_eta_jet_4[n] = {-0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un3_eta_jet_5[n] = {-1.1,-.3,.4,1.35};
Double_t y_un3_eta_jet_5[n] = {-0.019322878, -0.075351203, -0.047039459, -0.027995470};    //eta_jet rel_delta_syst3_minus

Double_t x_un3_eta_jet_6[n] = {-1.1,-.3,.4,1.35};
Double_t y_un3_eta_jet_6[n] = {0.026135645, 0.035889775, 0.015300128, 0.019122963};    //eta_jet rel_delta_syst3_plus

Double_t x_un3_eta_jet_7[n] = {-1.1,-.3,.4,1.35};
Double_t y_un3_eta_jet_7[n] = {.0,.0,.0,.0};  //0 line 


// E_T_jet
Double_t x_un3_et_jet_1[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un3_et_jet_1[j] = {0.117236814, 0.096753041, 0.100163383, 0.101394600, 0.098390559, 0.173877469};  //Et_jet rel_sigma (povna vidnosna stat.poh.)

Double_t x_un3_et_jet_2[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un3_et_jet_2[j] = {-0.117236814, -0.096753041, -0.100163383, -0.101394600, -0.098390559, -0.173877469};  //Et_jet rel_sigma (povna vidnosna stat.poh.)

Double_t x_un3_et_jet_3[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un3_et_jet_3[j] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un3_et_jet_4[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un3_et_jet_4[j] = {-0.1, -0.1, -0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un3_et_jet_5[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un3_et_jet_5[j] = {-0.061630933, -0.040923844, -0.025208709, -0.073598332, -0.053098842, -0.037679947};    //Et_jet rel_delta_syst3_minus

Double_t x_un3_et_jet_6[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un3_et_jet_6[j] = {0.069925905, 0.006960544, 0.037511247, 0.056556760, 0.044806651, 0.072606251};    //Et_jet rel_delta_syst3_plus

Double_t x_un3_et_jet_7[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un3_et_jet_7[j] = {.0,.0,.0,.0,.0,.0};  //0 line

// *************** en_photon_systematics   sys_un_3 *************** //


// *************** en_el_systematics   sys_un_4 *************** //
// eta_photon
Double_t x_un4_eta_1[n] = {-.5,-.1,.3,.7};
Double_t y_un4_eta_1[n] = {0.079406345, 0.080874765, 0.097399971, 0.103643608};  //eta rel_sigma (povna vidnosna stat.poh.)

Double_t x_un4_eta_2[n] = {-.5,-.1,.3,.7};
Double_t y_un4_eta_2[n] = {-0.079406345, -0.080874765, -0.097399971, -0.103643608};  //eta rel_sigma (povna vidnosna stat.poh.)

Double_t x_un4_eta_3[n] = {-.5,-.1,.3,.7};
Double_t y_un4_eta_3[n] = {0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un4_eta_4[n] = {-.5,-.1,.3,.7};
Double_t y_un4_eta_4[n] = {-0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un4_eta_5[n] = {-.5,-.1,.3,.7};
Double_t y_un4_eta_5[n] = {-0.041050389, -0.033388992, -0.031055710, -0.020639573};    //eta rel_delta_syst4_minus

Double_t x_un4_eta_6[n] = {-.5,-.1,.3,.7};
Double_t y_un4_eta_6[n] = {0.024030758, 0.013981138, 0.017191554, 0.031255334};    //eta rel_delta_syst4_plus

Double_t x_un4_eta_7[n] = {-.5,-.1,.3,.7};
Double_t y_un4_eta_7[n] = {.0,.0,.0,.0};  //0 line 


// E_T_photon
Double_t x_un4_et_1[n] = {5.,7.,9.,12.5};
Double_t y_un4_et_1[n] = {0.073909070, 0.079935692, 0.121903012, 0.105632500};  //Et rel_sigma (povna vidnosna stat.poh.)

Double_t x_un4_et_2[n] = {5.,7.,9.,12.5};
Double_t y_un4_et_2[n] = {-0.073909070, -0.079935692, -0.121903012, -0.105632500};  //Et rel_sigma (povna vidnosna stat.poh.)

Double_t x_un4_et_3[n] = {5.,7.,9.,12.5};
Double_t y_un4_et_3[n] = {0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un4_et_4[n] = {5.,7.,9.,12.5};
Double_t y_un4_et_4[n] = {-0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un4_et_5[n] = {5.,7.,9.,12.5};
Double_t y_un4_et_5[n] = {-0.051927779, -0.020923496, -0.023376319, -0.035675640};    //Et rel_delta_syst4_minus

Double_t x_un4_et_6[n] = {5.,7.,9.,12.5};
Double_t y_un4_et_6[n] = {0.037911709, 0.008449430, 0.045234821, 0.037852705};    //Et rel_delta_syst4_plus

Double_t x_un4_et_7[n] = {5.,7.,9.,12.5};
Double_t y_un4_et_7[n] = {.0,.0,.0,.0};  //0 line


// Q2_photon
Double_t x_un4_q2_1[q] = {15.,30.,60.,115.,250.};
Double_t y_un4_q2_1[q] = {0.082699930, 0.091492816, 0.113197388, 0.106888231, 0.179507320};  //q2 rel_sigma (povna vidnosna stat.poh.)

Double_t x_un4_q2_2[q] = {15.,30.,60.,115.,250.};
Double_t y_un4_q2_2[q] = {-0.082699930, -0.091492816, -0.113197388, -0.106888231, -0.179507320};  //q2 rel_sigma (povna vidnosna stat.poh.)

Double_t x_un4_q2_3[q] = {15.,30.,60.,115.,250.};
Double_t y_un4_q2_3[q] = {0.1, 0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un4_q2_4[q] = {15.,30.,60.,115.,250.};
Double_t y_un4_q2_4[q] = {-0.1, -0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un4_q2_5[q] = {15.,30.,60.,115.,250.};
Double_t y_un4_q2_5[q] = {-0.060130471, -0.049149815, -0.029824809, -0.050407056, -0.031032254};    //q2 rel_delta_syst4_minus

Double_t x_un4_q2_6[q] = {15.,30.,60.,115.,250.};
Double_t y_un4_q2_6[q] = {0.046671641, 0.036347062, 0.046168107, 0.036621938, 0.031032254};    //q2 rel_delta_syst4_plus

Double_t x_un4_q2_7[q] = {15.,30.,60.,115.,250.};
Double_t y_un4_q2_7[q] = {.0,.0,.0,.0,.0};  //0 line


// x
Double_t x_un4_x_1[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un4_x_1[n] = {0.070535686, 0.079400073, 0.122084542, 0.255756947};  //x rel_sigma (povna vidnosna stat.poh.)

Double_t x_un4_x_2[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un4_x_2[n] = {-0.070535686, -0.079400073, -0.122084542, -0.255756947};  //x rel_sigma (povna vidnosna stat.poh.)

Double_t x_un4_x_3[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un4_x_3[n] = {0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un4_x_4[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un4_x_4[n] = {-0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un4_x_5[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un4_x_5[n] = {-0.063626215, -0.011882518, -0.026844166, -0.071274309};    //x rel_delta_syst4_minus

Double_t x_un4_x_6[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un4_x_6[n] = {0.041008812, 0.004715997, 0.026844166, 0.071274309};    //x rel_delta_syst4_plus

Double_t x_un4_x_7[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un4_x_7[n] = {.0,.0,.0,.0};  //0 line


// eta_jet
Double_t x_un4_eta_jet_1[n] = {-1.1,-.3,.4,1.35};
Double_t y_un4_eta_jet_1[n] = {0.114665875, 0.092753821, 0.084312295, 0.085367962};  //eta_jet rel_sigma (povna vidnosna stat.poh.)

Double_t x_un4_eta_jet_2[n] = {-1.1,-.3,.4,1.35};
Double_t y_un4_eta_jet_2[n] = {-0.114665875, -0.092753821, -0.084312295, -0.085367962};  //eta_jet rel_sigma (povna vidnosna stat.poh.)

Double_t x_un4_eta_jet_3[n] = {-1.1,-.3,.4,1.35};
Double_t y_un4_eta_jet_3[n] = {0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un4_eta_jet_4[n] = {-1.1,-.3,.4,1.35};
Double_t y_un4_eta_jet_4[n] = {-0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un4_eta_jet_5[n] = {-1.1,-.3,.4,1.35};
Double_t y_un4_eta_jet_5[n] = {-0.044783925, -0.066582407, -0.039243523, -0.006053846};    //eta_jet rel_delta_syst4_minus

Double_t x_un4_eta_jet_6[n] = {-1.1,-.3,.4,1.35};
Double_t y_un4_eta_jet_6[n] = {0.023624272, 0.053611664, 0.024237676, 0.001406478};    //eta_jet rel_delta_syst4_plus

Double_t x_un4_eta_jet_7[n] = {-1.1,-.3,.4,1.35};
Double_t y_un4_eta_jet_7[n] = {.0,.0,.0,.0};  //0 line 


// E_T_jet
Double_t x_un4_et_jet_1[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un4_et_jet_1[j] = {0.117236814, 0.096753041, 0.100163383, 0.101394600, 0.098390559, 0.173877469};  //Et_jet rel_sigma (povna vidnosna stat.poh.)

Double_t x_un4_et_jet_2[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un4_et_jet_2[j] = {-0.117236814, -0.096753041, -0.100163383, -0.101394600, -0.098390559, -0.173877469};  //Et_jet rel_sigma (povna vidnosna stat.poh.)

Double_t x_un4_et_jet_3[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un4_et_jet_3[j] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un4_et_jet_4[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un4_et_jet_4[j] = {-0.1, -0.1, -0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un4_et_jet_5[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un4_et_jet_5[j] = {-0.018348195, -0.054678825, -0.029451749, -0.058315445, -0.039474838, -0.019731317};    //Et_jet rel_delta_syst4_minus

Double_t x_un4_et_jet_6[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un4_et_jet_6[j] = {0.000758600, 0.053460997, 0.015239947, 0.040284095, 0.023451205, 0.009556576};    //Et_jet rel_delta_syst4_plus

Double_t x_un4_et_jet_7[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un4_et_jet_7[j] = {.0,.0,.0,.0,.0,.0};  //0 line
// *************** en_el_systematics   sys_un_4 *************** //


// *************** deltaZ_systematics   sys_un_5 *************** //
// eta_photon
Double_t x_un5_eta_1[n] = {-.5,-.1,.3,.7};
Double_t y_un5_eta_1[n] = {0.079406345, 0.080874765, 0.097399971, 0.103643608};  //eta rel_sigma (povna vidnosna stat.poh.)

Double_t x_un5_eta_2[n] = {-.5,-.1,.3,.7};
Double_t y_un5_eta_2[n] = {-0.079406345, -0.080874765, -0.097399971, -0.103643608};  //eta rel_sigma (povna vidnosna stat.poh.)

Double_t x_un5_eta_3[n] = {-.5,-.1,.3,.7};
Double_t y_un5_eta_3[n] = {0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un5_eta_4[n] = {-.5,-.1,.3,.7};
Double_t y_un5_eta_4[n] = {-0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un5_eta_5[n] = {-.5,-.1,.3,.7};
Double_t y_un5_eta_5[n] = {-0.036254591, -0.019772727, -0.055409658, -0.075850185};    //eta rel_delta_syst5_minus

Double_t x_un5_eta_6[n] = {-.5,-.1,.3,.7};
Double_t y_un5_eta_6[n] = {0.031184943, 0.022946815, 0.025795459, 0.023943478};    //eta rel_delta_syst5_plus

Double_t x_un5_eta_7[n] = {-.5,-.1,.3,.7};
Double_t y_un5_eta_7[n] = {.0,.0,.0,.0};  //0 line 


// E_T_photon
Double_t x_un5_et_1[n] = {5.,7.,9.,12.5};
Double_t y_un5_et_1[n] = {0.073909070, 0.079935692, 0.121903012, 0.105632500};  //Et rel_sigma (povna vidnosna stat.poh.)

Double_t x_un5_et_2[n] = {5.,7.,9.,12.5};
Double_t y_un5_et_2[n] = {-0.073909070, -0.079935692, -0.121903012, -0.105632500};  //Et rel_sigma (povna vidnosna stat.poh.)

Double_t x_un5_et_3[n] = {5.,7.,9.,12.5};
Double_t y_un5_et_3[n] = {0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un5_et_4[n] = {5.,7.,9.,12.5};
Double_t y_un5_et_4[n] = {-0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un5_et_5[n] = {5.,7.,9.,12.5};
Double_t y_un5_et_5[n] = {-0.064473921, -0.021423690, -0.038333317, -0.013937246};    //Et rel_delta_syst5_minus

Double_t x_un5_et_6[n] = {5.,7.,9.,12.5};
Double_t y_un5_et_6[n] = {0.041431254, 0.017245147, 0.042428380, 0.039239575};    //Et rel_delta_syst5_plus

Double_t x_un5_et_7[n] = {5.,7.,9.,12.5};
Double_t y_un5_et_7[n] = {.0,.0,.0,.0};  //0 line


// Q2_photon
Double_t x_un5_q2_1[q] = {15.,30.,60.,115.,250.};
Double_t y_un5_q2_1[q] = {0.082699930, 0.091492816, 0.113197388, 0.106888231, 0.179507320};  //q2 rel_sigma (povna vidnosna stat.poh.)

Double_t x_un5_q2_2[q] = {15.,30.,60.,115.,250.};
Double_t y_un5_q2_2[q] = {-0.082699930, -0.091492816, -0.113197388, -0.106888231, -0.179507320};  //q2 rel_sigma (povna vidnosna stat.poh.)

Double_t x_un5_q2_3[q] = {15.,30.,60.,115.,250.};
Double_t y_un5_q2_3[q] = {0.1, 0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un5_q2_4[q] = {15.,30.,60.,115.,250.};
Double_t y_un5_q2_4[q] = {-0.1, -0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un5_q2_5[q] = {15.,30.,60.,115.,250.};
Double_t y_un5_q2_5[q] = {-0.004171690, -0.087775860, -0.134717637, -0.023229391, -0.023214451};    //q2 rel_delta_syst5_minus

Double_t x_un5_q2_6[q] = {15.,30.,60.,115.,250.};
Double_t y_un5_q2_6[q] = {0.050128673, 0.044630739, 0.035052756, 0.036306076, 0.031032254};    //q2 rel_delta_syst5_plus

Double_t x_un5_q2_7[q] = {15.,30.,60.,115.,250.};
Double_t y_un5_q2_7[q] = {.0,.0,.0,.0,.0};  //0 line


// x
Double_t x_un5_x_1[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un5_x_1[n] = {0.070535686, 0.079400073, 0.122084542, 0.255756947};  //x rel_sigma (povna vidnosna stat.poh.)

Double_t x_un5_x_2[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un5_x_2[n] = {-0.070535686, -0.079400073, -0.122084542, -0.255756947};  //x rel_sigma (povna vidnosna stat.poh.)

Double_t x_un5_x_3[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un5_x_3[n] = {0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un5_x_4[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un5_x_4[n] = {-0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un5_x_5[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un5_x_5[n] = {-0.047488107, -0.054590050, -0.078622755, -0.031980564};    //x rel_delta_syst5_minus

Double_t x_un5_x_6[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un5_x_6[n] = {0.052963122, 0.005192644, 0.026844166, 0.071274309};    //x rel_delta_syst5_plus

Double_t x_un5_x_7[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_un5_x_7[n] = {.0,.0,.0,.0};  //0 line


// eta_jet
Double_t x_un5_eta_jet_1[n] = {-1.1,-.3,.4,1.35};
Double_t y_un5_eta_jet_1[n] = {0.114665875, 0.092753821, 0.084312295, 0.085367962};  //eta_jet rel_sigma (povna vidnosna stat.poh.)

Double_t x_un5_eta_jet_2[n] = {-1.1,-.3,.4,1.35};
Double_t y_un5_eta_jet_2[n] = {-0.114665875, -0.092753821, -0.084312295, -0.085367962};  //eta_jet rel_sigma (povna vidnosna stat.poh.)

Double_t x_un5_eta_jet_3[n] = {-1.1,-.3,.4,1.35};
Double_t y_un5_eta_jet_3[n] = {0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un5_eta_jet_4[n] = {-1.1,-.3,.4,1.35};
Double_t y_un5_eta_jet_4[n] = {-0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un5_eta_jet_5[n] = {-1.1,-.3,.4,1.35};
Double_t y_un5_eta_jet_5[n] = {-0.076169408, -0.071256149, -0.017131780, -0.087444119};    //eta_jet rel_delta_syst5_minus

Double_t x_un5_eta_jet_6[n] = {-1.1,-.3,.4,1.35};
Double_t y_un5_eta_jet_6[n] = {0.031846347, 0.059962499, 0.032675452, 0.001229598};    //eta_jet rel_delta_syst5_plus

Double_t x_un5_eta_jet_7[n] = {-1.1,-.3,.4,1.35};
Double_t y_un5_eta_jet_7[n] = {.0,.0,.0,.0};  //0 line 


// E_T_jet
Double_t x_un5_et_jet_1[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un5_et_jet_1[j] = {0.117236814, 0.096753041, 0.100163383, 0.101394600, 0.098390559, 0.173877469};  //Et_jet rel_sigma (povna vidnosna stat.poh.)

Double_t x_un5_et_jet_2[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un5_et_jet_2[j] = {-0.117236814, -0.096753041, -0.100163383, -0.101394600, -0.098390559, -0.173877469};  //Et_jet rel_sigma (povna vidnosna stat.poh.)

Double_t x_un5_et_jet_3[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un5_et_jet_3[j] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_un5_et_jet_4[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un5_et_jet_4[j] = {-0.1, -0.1, -0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_un5_et_jet_5[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un5_et_jet_5[j] = {-0.121638321, -0.041067745, -0.017106760, -0.009962659, -0.011932359, -0.030133967};    //Et_jet rel_delta_syst5_minus

Double_t x_un5_et_jet_6[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un5_et_jet_6[j] = {0.008720355, 0.056109841, 0.013302727, 0.050591865, 0.039211694, 0.009556576};    //Et_jet rel_delta_syst5_plus

Double_t x_un5_et_jet_7[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_un5_et_jet_7[j] = {.0,.0,.0,.0,.0,.0};  //0 line
// *************** deltaZ_systematics   sys_un_5 *************** //



// *************** total_systematics *************** //
// eta_photon
Double_t x_tot_eta_1[n] = {-.5,-.1,.3,.7};
Double_t y_tot_eta_1[n] = {0.582823514, 0.523097980, 0.539192408, 0.527016555};  //eta sigma_stat_err

Double_t x_tot_eta_2[n] = {-.5,-.1,.3,.7};
Double_t y_tot_eta_2[n] = {-0.582823514, -0.523097980, -0.539192408, -0.527016555};  //eta sigma_stat_err

Double_t x_tot_eta_3[n] = {-.5,-.1,.3,.7};
Double_t y_tot_eta_3[n] = {0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_tot_eta_4[n] = {-.5,-.1,.3,.7};
Double_t y_tot_eta_4[n] = {-0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_tot_eta_5[n] = {-.5,-.1,.3,.7};
Double_t y_tot_eta_5[n] = {-0.114304693, -0.095888713, -0.115533628, -0.145928778};    //eta otnositelnaja_polnaja_nizhnaja_pogreshnost

Double_t x_tot_eta_6[n] = {-.5,-.1,.3,.7};
Double_t y_tot_eta_6[n] = {0.104010560, 0.096154490, 0.124034412, 0.123417439};    //eta otnositelnaja_polnaja_verhnaja_pogreshnost

Double_t x_tot_eta_7[n] = {-.5,-.1,.3,.7};
Double_t y_tot_eta_7[n] = {.0,.0,.0,.0};  //0 line 


// E_T_photon
Double_t x_tot_et_1[n] = {5.,7.,9.,12.5};
Double_t y_tot_et_1[n] = {0.178496687, 0.103876112, 0.076057971, 0.026201128};  //Et sigma_stat_err

Double_t x_tot_et_2[n] = {5.,7.,9.,12.5};
Double_t y_tot_et_2[n] = {-0.178496687, -0.103876112, -0.076057971, -0.026201128};  //Et sigma_stat_err

Double_t x_tot_et_3[n] = {5.,7.,9.,12.5};
Double_t y_tot_et_3[n] = {0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_tot_et_4[n] = {5.,7.,9.,12.5};
Double_t y_tot_et_4[n] = {-0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_tot_et_5[n] = {5.,7.,9.,12.5};
Double_t y_tot_et_5[n] = {-0.117569102, -0.109315603, -0.134993914, -0.113344191};    //Et otnositelnaja_polnaja_nizhnaja_pogreshnost

Double_t x_tot_et_6[n] = {5.,7.,9.,12.5};
Double_t y_tot_et_6[n] = {0.118586872, 0.092100969, 0.130169324, 0.114608119};    //Et otnositelnaja_polnaja_verhnaja_pogreshnost

Double_t x_tot_et_7[n] = {5.,7.,9.,12.5};
Double_t y_tot_et_7[n] = {.0,.0,.0,.0};  //0 line


// Q2_photon
Double_t x_tot_q2_1[q] = {15.,30.,60.,115.,250.};
Double_t y_tot_q2_1[q] = {0.024185380, 0.011762874, 0.005458559, 0.002368812, 0.000661057};  //q2 sigma_stat_err

Double_t x_tot_q2_2[q] = {15.,30.,60.,115.,250.};
Double_t y_tot_q2_2[q] = {-0.024185380, -0.011762874, -0.005458559, -0.002368812, -0.000661057};  //q2 sigma_stat_err

Double_t x_tot_q2_3[q] = {15.,30.,60.,115.,250.};
Double_t y_tot_q2_3[q] = {0.1, 0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_tot_q2_4[q] = {15.,30.,60.,115.,250.};
Double_t y_tot_q2_4[q] = {-0.1, -0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_tot_q2_5[q] = {15.,30.,60.,115.,250.};
Double_t y_tot_q2_5[q] = {-0.109600909, -0.144744687, -0.178602737, -0.135638345, -0.195932664};    //q2 otnositelnaja_polnaja_nizhnaja_pogreshnost

Double_t x_tot_q2_6[q] = {15.,30.,60.,115.,250.};
Double_t y_tot_q2_6[q] = {0.135614777, 0.130661035, 0.120820915, 0.128020462, 0.184391907};    //q2 otnositelnaja_polnaja_verhnaja_pogreshnost

Double_t x_tot_q2_7[q] = {15.,30.,60.,115.,250.};
Double_t y_tot_q2_7[q] = {.0,.0,.0,.0,.0};  //0 line


// x
Double_t x_tot_x_1[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_tot_x_1[n] = {334.318908178, 141.593515510, 32.858566196, 6.788075813};  //x sigma_stat_err

Double_t x_tot_x_2[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_tot_x_2[n] = {-334.318908178, -141.593515510, -32.858566196, -6.788075813};  //x sigma_stat_err

Double_t x_tot_x_3[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_tot_x_3[n] = {0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_tot_x_4[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_tot_x_4[n] = {-0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_tot_x_5[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_tot_x_5[n] = {-0.101684325, -0.099730237, -0.173546333, -0.285820801};    //x otnositelnaja_polnaja_nizhnaja_pogreshnost

Double_t x_tot_x_6[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_tot_x_6[n] = {0.104084437, 0.110842662, 0.143574585, 0.310383384};    //x otnositelnaja_polnaja_verhnaja_pogreshnost

Double_t x_tot_x_7[n] = {0.0006, 0.0020, 0.0065, 0.0150};
Double_t y_tot_x_7[n] = {.0,.0,.0,.0};  //0 line


// eta_jet
Double_t x_tot_eta_jet_1[n] = {-1.1,-.3,.4,1.35};
Double_t y_tot_eta_jet_1[n] = {0.171676486, 0.251643805, 0.332341953, 0.299232633};  //eta_jet sigma_stat_err

Double_t x_tot_eta_jet_2[n] = {-1.1,-.3,.4,1.35};
Double_t y_tot_eta_jet_2[n] = {-0.171676486, -0.251643805, -0.332341953, -0.299232633};  //eta_jet sigma_stat_err

Double_t x_tot_eta_jet_3[n] = {-1.1,-.3,.4,1.35};
Double_t y_tot_eta_jet_3[n] = {0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_tot_eta_jet_4[n] = {-1.1,-.3,.4,1.35};
Double_t y_tot_eta_jet_4[n] = {-0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_tot_eta_jet_5[n] = {-1.1,-.3,.4,1.35};
Double_t y_tot_eta_jet_5[n] = {-0.157315507, -0.126717911, -0.093265271, -0.135516778};    //eta_jet otnositelnaja_polnaja_nizhnaja_pogreshnost

Double_t x_tot_eta_jet_6[n] = {-1.1,-.3,.4,1.35};
Double_t y_tot_eta_jet_6[n] = {0.146049275, 0.115356170, 0.109732045, 0.106574618};    //eta_jet otnositelnaja_polnaja_verhnaja_pogreshnost

Double_t x_tot_eta_jet_7[n] = {-1.1,-.3,.4,1.35};
Double_t y_tot_eta_jet_7[n] = {.0,.0,.0,.0};  //0 line 


// E_T_jet
Double_t x_tot_et_jet_1[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_tot_et_jet_1[j] = {0.165361706, 0.108922058, 0.096739498, 0.073450756, 0.031407841, 0.005569347};  //Et_jet sigma_stat_err

Double_t x_tot_et_jet_2[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_tot_et_jet_2[j] = {-0.165361706, -0.108922058, -0.096739498, -0.073450756, -0.031407841, -0.005569347};  //Et_jet sigma_stat_err

Double_t x_tot_et_jet_3[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_tot_et_jet_3[j] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1};  //10% line 

Double_t x_tot_et_jet_4[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_tot_et_jet_4[j] = {-0.1, -0.1, -0.1, -0.1, -0.1, -0.1};  //10% line 

Double_t x_tot_et_jet_5[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_tot_et_jet_5[j] = {-0.194225952, -0.112813857, -0.110671363, -0.405733719, -0.103175728, -0.247885001};    //Et_jet otnositelnaja_polnaja_nizhnaja_pogreshnost

Double_t x_tot_et_jet_6[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_tot_et_jet_6[j] = {0.161227355, 0.127351231, 0.129598200, 0.122044733, 0.304982021, 0.290458271};    //Et_jet otnositelnaja_polnaja_verhnaja_pogreshnost

Double_t x_tot_et_jet_7[j] = {3.25,5.,7.,9.,12.5,25.};
Double_t y_tot_et_jet_7[j] = {.0,.0,.0,.0,.0,.0};  //0 line
// *************** total_systematics *************** //



// *************** et_jet_systematics un_2  *************** //
 TH2D *w_eta = new TH2D("w_eta", "", 10, -0.7, 0.9, 10, -0.3, 0.3); //plain_style
 TH2D *w_et = new TH2D("w_et", "", 10, 4., 14., 10, -0.3, 0.3); //plain_style
 TH2D *w_Q2 = new TH2D("w_Q2", "", 10, 10., 350., 10, -0.3, 0.3); //plain_style
 TH2D *w_x = new TH2D("w_x", "", 10, 5.e-4, 2.e-2, 10, -0.3, 0.3); //plain_style
 TH2D *w_et_jet = new TH2D("w_et_jet", "", 10, 2.5, 35., 10, -0.3, 0.3); //plain_style
 TH2D *w_eta_jet = new TH2D("w_eta_jet", "", 10, -1.5, 1.8, 10, -0.3, 0.3); //plain_style

 TCanvas *can_un2 = new TCanvas("can_un2","Systematic uncertainties jet_et", 0, 0, 1600, 1200);
 can_un2->Divide(3,3);
 make_clean_pads(can_un2, 9, 0, 0);//plain_style
 sign_window(can_un2->GetPad(1), w_eta, "#eta^{#gamma}", "rel. uncertainty", "", "middle");//plain_style
 sign_window(can_un2->GetPad(2), w_et, "E_{T}^{#gamma} (GeV)", "rel. uncertainty", "", "middle");//plain_style
 sign_window(can_un2->GetPad(3), w_Q2, "Q^{2} (GeV^{2})", "rel. uncertainty", "", "middle");//plain_style
 sign_window(can_un2->GetPad(4), w_x, "x", "rel. uncertainty", "", "middle");//plain_style
 sign_window(can_un2->GetPad(5), w_eta_jet, "#eta^{jet}", "rel. uncertainty", "", "middle");//plain_style
 sign_window(can_un2->GetPad(6), w_et_jet, "E_{T}^{jet} (GeV)", "rel. uncertainty", "", "middle");//plain_style

 can_un2->GetPad(3)->SetLogx();
 can_un2->GetPad(4)->SetLogx();
 can_un2->GetPad(6)->SetLogx();

// eta_photon
can_un2->cd(1);

TCanvas *c_un2_1 = new TCanvas("c_un2_1","Graph of  systematic Uncertainties, eta",600,400);

TGraph* gr_un2_eta_1 = new TGraph(n,x_un2_eta_1,y_un2_eta_1); 
gr_un2_eta_1->SetTitle("#eta^{#gamma} , E_{T}_jet  systematic");
gr_un2_eta_1->GetYaxis()->SetRangeUser(-0.3,0.3);
gr_un2_eta_1->SetMarkerColor(61);
gr_un2_eta_1->SetMarkerStyle(7);
c_un2_1->cd();
can_un2->cd(1);
gr_un2_eta_1->SetLineWidth(2);
gr_un2_eta_1->SetLineColor(61);
 w_eta->Draw();//plain_style
gr_un2_eta_1->Draw("CP SAME");

TGraph* gr_un2_eta_2 = new TGraph(n,x_un2_eta_2,y_un2_eta_2); 
gr_un2_eta_2->SetTitle("#eta^{#gamma} , E_{T}_jet  systematic");
gr_un2_eta_2->SetMarkerColor(61);
gr_un2_eta_2->SetMarkerStyle(7);
c_un2_1->cd();
can_un2->cd(1);
gr_un2_eta_2->SetLineWidth(2);
gr_un2_eta_2->SetLineColor(61);
gr_un2_eta_2->Draw("CP same");

TGraph* gr_un2_eta_3 = new TGraph(n,x_un2_eta_3,y_un2_eta_3); 
gr_un2_eta_3->SetTitle("#eta^{#gamma} , E_{T}_jet  systematic");
gr_un2_eta_3->SetMarkerColor(2);
gr_un2_eta_3->SetMarkerStyle(7);
gr_un2_eta_3->SetMarkerSize(2);
gr_un2_eta_3->SetLineColor(2);
gr_un2_eta_3->Draw("CP");

TGraph* gr_un2_eta_4 = new TGraph(n,x_un2_eta_4,y_un2_eta_4); 
gr_un2_eta_4->SetTitle("#eta^{#gamma} , E_{T}_jet  systematic");
gr_un2_eta_4->SetMarkerColor(2);
gr_un2_eta_4->SetMarkerStyle(7);
gr_un2_eta_4->SetMarkerSize(2);
gr_un2_eta_4->SetLineColor(2);
gr_un2_eta_4->Draw("CP");

TGraph* gr_un2_eta_5 = new TGraph(n,x_un2_eta_5,y_un2_eta_5); 
gr_un2_eta_5->SetTitle("#eta^{#gamma} , E_{T}_jet  systematic");
gr_un2_eta_5->SetMarkerColor(1);
gr_un2_eta_5->SetMarkerStyle(4);
gr_un2_eta_5->SetMarkerSize(1);
gr_un2_eta_5->SetLineColor(12);
gr_un2_eta_5->Draw("P");

TGraph* gr_un2_eta_6 = new TGraph(n,x_un2_eta_6,y_un2_eta_6); 
gr_un2_eta_6->SetTitle("#eta^{#gamma} , E_{T}_jet  systematic");
gr_un2_eta_6->SetMarkerColor(1);
gr_un2_eta_6->SetMarkerStyle(8);
gr_un2_eta_6->SetMarkerSize(1);
gr_un2_eta_6->SetLineColor(12);
gr_un2_eta_6->Draw("P");

TGraph* gr_un2_eta_7 = new TGraph(n,x_un2_eta_7,y_un2_eta_7); 
gr_un2_eta_7->SetTitle("#eta^{#gamma} , E_{T}_jet  systematic");
gr_un2_eta_7->SetMarkerColor(1);
gr_un2_eta_7->SetMarkerStyle(7);
gr_un2_eta_7->SetMarkerSize(2);
gr_un2_eta_7->SetLineColor(1);
gr_un2_eta_7->Draw("C");



// Et_photon
can_un2->cd(2);

TCanvas *c_un2_2 = new TCanvas("c_un2_2","Graph of  systematic Uncertainties, E_T",600,400);

TGraph* gr_un2_et_1 = new TGraph(n,x_un2_et_1,y_un2_et_1); 
gr_un2_et_1->SetTitle("E_{T} , E_{T}_jet  systematic");
gr_un2_et_1->GetYaxis()->SetRangeUser(-0.3,0.3);
gr_un2_et_1->SetMarkerColor(61);
gr_un2_et_1->SetMarkerStyle(7);
c_un2_2->cd();
can_un2->cd(2);
gr_un2_et_1->SetLineWidth(2);
gr_un2_et_1->SetLineColor(61);
 w_et->Draw();//plain_style
gr_un2_et_1->Draw("CP SAME");

TGraph* gr_un2_et_2 = new TGraph(n,x_un2_et_2,y_un2_et_2); 
gr_un2_et_2->SetTitle("E_{T} , E_{T}_jet  systematic");
gr_un2_et_2->SetMarkerColor(61);
gr_un2_et_2->SetMarkerStyle(7);
c_un2_2->cd();
can_un2->cd(2);
gr_un2_et_2->SetLineWidth(2);
gr_un2_et_2->SetLineColor(61);
gr_un2_et_2->Draw("CP same");

TGraph* gr_un2_et_3 = new TGraph(n,x_un2_et_3,y_un2_et_3); 
gr_un2_et_3->SetTitle("E_{T} , E_{T}_jet  systematic");
gr_un2_et_3->SetMarkerColor(2);
gr_un2_et_3->SetMarkerStyle(7);
gr_un2_et_3->SetMarkerSize(2);
gr_un2_et_3->SetLineColor(2);
gr_un2_et_3->Draw("CP");

TGraph* gr_un2_et_4 = new TGraph(n,x_un2_et_4,y_un2_et_4); 
gr_un2_et_4->SetTitle("E_{T} , E_{T}_jet  systematic");
gr_un2_et_4->SetMarkerColor(2);
gr_un2_et_4->SetMarkerStyle(7);
gr_un2_et_4->SetMarkerSize(2);
gr_un2_et_4->SetLineColor(2);
gr_un2_et_4->Draw("CP");

TGraph* gr_un2_et_5 = new TGraph(n,x_un2_et_5,y_un2_et_5); 
gr_un2_et_5->SetTitle("E_{T} , E_{T}_jet  systematic");
gr_un2_et_5->SetMarkerColor(1);
gr_un2_et_5->SetMarkerStyle(4);
gr_un2_et_5->SetMarkerSize(1);
gr_un2_et_5->SetLineColor(12);
gr_un2_et_5->Draw("P");

TGraph* gr_un2_et_6 = new TGraph(n,x_un2_et_6,y_un2_et_6); 
gr_un2_et_6->SetTitle("E_{T} , E_{T}_jet  systematic");
gr_un2_et_6->SetMarkerColor(1);
gr_un2_et_6->SetMarkerStyle(8);
gr_un2_et_6->SetMarkerSize(1);
gr_un2_et_6->SetLineColor(12);
gr_un2_et_6->Draw("P");

TGraph* gr_un2_et_7 = new TGraph(n,x_un2_et_7,y_un2_et_7); 
gr_un2_et_7->SetTitle("E_{T} , E_{T}_jet  systematic");
gr_un2_et_7->SetMarkerColor(1);
gr_un2_et_7->SetMarkerStyle(7);
gr_un2_et_7->SetMarkerSize(2);
gr_un2_et_7->SetLineColor(1);
gr_un2_et_7->Draw("C");



// Q2_photon
can_un2->cd(3);

TCanvas *c_un2_3 = new TCanvas("c_un2_3","Graph of  systematic Uncertainties, Q^{2}",600,400);

TGraph* gr_un2_q2_1 = new TGraph(q,x_un2_q2_1,y_un2_q2_1); 
gr_un2_q2_1->SetTitle("Q^{2} , E_{T}_jet  systematic");
gr_un2_q2_1->GetYaxis()->SetRangeUser(-0.3,0.3);
gr_un2_q2_1->SetMarkerColor(61);
gr_un2_q2_1->SetMarkerStyle(7);
c_un2_3->cd();
can_un2->cd(3);
gr_un2_q2_1->SetLineWidth(2);
gr_un2_q2_1->SetLineColor(61);
 w_Q2->Draw();//plain_style
gr_un2_q2_1->Draw("CP SAME");

TGraph* gr_un2_q2_2 = new TGraph(q,x_un2_q2_2,y_un2_q2_2); 
gr_un2_q2_2->SetTitle("Q^{2} , E_{T}_jet  systematic");
gr_un2_q2_2->SetMarkerColor(61);
gr_un2_q2_2->SetMarkerStyle(7);
c_un2_3->cd();
can_un2->cd(3);
gr_un2_q2_2->SetLineWidth(2);
gr_un2_q2_2->SetLineColor(61);
gr_un2_q2_2->Draw("CP same");

TGraph* gr_un2_q2_3 = new TGraph(q,x_un2_q2_3,y_un2_q2_3); 
gr_un2_q2_3->SetTitle("Q^{2} , E_{T}_jet  systematic");
gr_un2_q2_3->SetMarkerColor(2);
gr_un2_q2_3->SetMarkerStyle(7);
gr_un2_q2_3->SetMarkerSize(2);
gr_un2_q2_3->SetLineColor(2);
gr_un2_q2_3->Draw("CP");

TGraph* gr_un2_q2_4 = new TGraph(q,x_un2_q2_4,y_un2_q2_4); 
gr_un2_q2_4->SetTitle("Q^{2} , E_{T}_jet  systematic");
gr_un2_q2_4->SetMarkerColor(2);
gr_un2_q2_4->SetMarkerStyle(7);
gr_un2_q2_4->SetMarkerSize(2);
gr_un2_q2_4->SetLineColor(2);
gr_un2_q2_4->Draw("CP");

TGraph* gr_un2_q2_5 = new TGraph(q,x_un2_q2_5,y_un2_q2_5); 
gr_un2_q2_5->SetTitle("Q^{2} , E_{T}_jet  systematic");
gr_un2_q2_5->SetMarkerColor(1);
gr_un2_q2_5->SetMarkerStyle(4);
gr_un2_q2_5->SetMarkerSize(1);
gr_un2_q2_5->SetLineColor(12);
gr_un2_q2_5->Draw("P");

TGraph* gr_un2_q2_6 = new TGraph(q,x_un2_q2_6,y_un2_q2_6); 
gr_un2_q2_6->SetTitle("Q^{2} , E_{T}_jet  systematic");
gr_un2_q2_6->SetMarkerColor(1);
gr_un2_q2_6->SetMarkerStyle(8);
gr_un2_q2_6->SetMarkerSize(1);
gr_un2_q2_6->SetLineColor(12);
gr_un2_q2_6->Draw("P");

TGraph* gr_un2_q2_7 = new TGraph(q,x_un2_q2_7,y_un2_q2_7); 
gr_un2_q2_7->SetTitle("Q^{2} , E_{T}_jet  systematic");
gr_un2_q2_7->SetMarkerColor(1);
gr_un2_q2_7->SetMarkerStyle(7);
gr_un2_q2_7->SetMarkerSize(2);
gr_un2_q2_7->SetLineColor(1);
gr_un2_q2_7->Draw("C");



// x_Bjorken
can_un2->cd(4);

TCanvas *c_un2_4 = new TCanvas("c_un2_4","Graph of  systematic Uncertainties, x",600,400);

TGraph* gr_un2_x_1 = new TGraph(n,x_un2_x_1,y_un2_x_1); 
gr_un2_x_1->SetTitle("x , E_{T}_jet  systematic");
gr_un2_x_1->GetYaxis()->SetRangeUser(-0.5,0.5);
gr_un2_x_1->SetMarkerColor(61);
gr_un2_x_1->SetMarkerStyle(7);
c_un2_4->cd();
can_un2->cd(4);
gr_un2_x_1->SetLineWidth(2);
gr_un2_x_1->SetLineColor(61);
 w_x->Draw();//plain_style
gr_un2_x_1->Draw("CP SAME");

TGraph* gr_un2_x_2 = new TGraph(n,x_un2_x_2,y_un2_x_2); 
gr_un2_x_2->SetTitle("x , E_{T}_jet  systematic");
gr_un2_x_2->SetMarkerColor(61);
gr_un2_x_2->SetMarkerStyle(7);
c_un2_4->cd();
can_un2->cd(4);
gr_un2_x_2->SetLineWidth(2);
gr_un2_x_2->SetLineColor(61);
gr_un2_x_2->Draw("CP same");

TGraph* gr_un2_x_3 = new TGraph(n,x_un2_x_3,y_un2_x_3); 
gr_un2_x_3->SetTitle("x , E_{T}_jet  systematic");
gr_un2_x_3->SetMarkerColor(2);
gr_un2_x_3->SetMarkerStyle(7);
gr_un2_x_3->SetMarkerSize(2);
gr_un2_x_3->SetLineColor(2);
gr_un2_x_3->Draw("CP");

TGraph* gr_un2_x_4 = new TGraph(n,x_un2_x_4,y_un2_x_4); 
gr_un2_x_4->SetTitle("x , E_{T}_jet  systematic");
gr_un2_x_4->SetMarkerColor(2);
gr_un2_x_4->SetMarkerStyle(7);
gr_un2_x_4->SetMarkerSize(2);
gr_un2_x_4->SetLineColor(2);
gr_un2_x_4->Draw("CP");

TGraph* gr_un2_x_5 = new TGraph(n,x_un2_x_5,y_un2_x_5); 
gr_un2_x_5->SetTitle("x , E_{T}_jet  systematic");
gr_un2_x_5->SetMarkerColor(1);
gr_un2_x_5->SetMarkerStyle(4);
gr_un2_x_5->SetMarkerSize(1);
gr_un2_x_5->SetLineColor(12);
gr_un2_x_5->Draw("P");

TGraph* gr_un2_x_6 = new TGraph(n,x_un2_x_6,y_un2_x_6); 
gr_un2_x_6->SetTitle("x , E_{T}_jet  systematic");
gr_un2_x_6->SetMarkerColor(1);
gr_un2_x_6->SetMarkerStyle(8);
gr_un2_x_6->SetMarkerSize(1);
gr_un2_x_6->SetLineColor(12);
gr_un2_x_6->Draw("P");

TGraph* gr_un2_x_7 = new TGraph(n,x_un2_x_7,y_un2_x_7); 
gr_un2_x_7->SetTitle("x , E_{T}_jet  systematic");
gr_un2_x_7->SetMarkerColor(1);
gr_un2_x_7->SetMarkerStyle(7);
gr_un2_x_7->SetMarkerSize(2);
gr_un2_x_7->SetLineColor(1);
gr_un2_x_7->Draw("C");



// eta_jet
can_un2->cd(5);

TCanvas *c_un2_5 = new TCanvas("c_un2_5","Graph of  systematic Uncertainties, eta_jet",600,400);

TGraph* gr_un2_eta_jet_1 = new TGraph(n,x_un2_eta_jet_1,y_un2_eta_jet_1); 
gr_un2_eta_jet_1->SetTitle("eta_{jet} , E_{T}_jet  systematic");
gr_un2_eta_jet_1->GetYaxis()->SetRangeUser(-0.3,0.3);
gr_un2_eta_jet_1->SetMarkerColor(61);
gr_un2_eta_jet_1->SetMarkerStyle(7);
c_un2_5->cd();
can_un2->cd(5);
gr_un2_eta_jet_1->SetLineWidth(2);
gr_un2_eta_jet_1->SetLineColor(61);
 w_eta_jet->Draw();//plain_style
gr_un2_eta_jet_1->Draw("CP SAME");

TGraph* gr_un2_eta_jet_2 = new TGraph(n,x_un2_eta_jet_2,y_un2_eta_jet_2); 
gr_un2_eta_jet_2->SetTitle("eta_{jet} , E_{T}_jet  systematic");
gr_un2_eta_jet_2->SetMarkerColor(61);
gr_un2_eta_jet_2->SetMarkerStyle(7);
c_un2_5->cd();
can_un2->cd(5);
gr_un2_eta_jet_2->SetLineWidth(2);
gr_un2_eta_jet_2->SetLineColor(61);
gr_un2_eta_jet_2->Draw("CP same");

TGraph* gr_un2_eta_jet_3 = new TGraph(n,x_un2_eta_jet_3,y_un2_eta_jet_3); 
gr_un2_eta_jet_3->SetTitle("eta_{jet} , E_{T}_jet  systematic");
gr_un2_eta_jet_3->SetMarkerColor(2);
gr_un2_eta_jet_3->SetMarkerStyle(7);
gr_un2_eta_jet_3->SetMarkerSize(2);
gr_un2_eta_jet_3->SetLineColor(2);
gr_un2_eta_jet_3->Draw("CP");

TGraph* gr_un2_eta_jet_4 = new TGraph(n,x_un2_eta_jet_4,y_un2_eta_jet_4); 
gr_un2_eta_jet_4->SetTitle("eta_{jet} , E_{T}_jet  systematic");
gr_un2_eta_jet_4->SetMarkerColor(2);
gr_un2_eta_jet_4->SetMarkerStyle(7);
gr_un2_eta_jet_4->SetMarkerSize(2);
gr_un2_eta_jet_4->SetLineColor(2);
gr_un2_eta_jet_4->Draw("CP");

TGraph* gr_un2_eta_jet_5 = new TGraph(n,x_un2_eta_jet_5,y_un2_eta_jet_5); 
gr_un2_eta_jet_5->SetTitle("eta_{jet} , E_{T}_jet  systematic");
gr_un2_eta_jet_5->SetMarkerColor(1);
gr_un2_eta_jet_5->SetMarkerStyle(4);
gr_un2_eta_jet_5->SetMarkerSize(1);
gr_un2_eta_jet_5->SetLineColor(12);
gr_un2_eta_jet_5->Draw("P");

TGraph* gr_un2_eta_jet_6 = new TGraph(n,x_un2_eta_jet_6,y_un2_eta_jet_6); 
gr_un2_eta_jet_6->SetTitle("eta_{jet} , E_{T}_jet  systematic");
gr_un2_eta_jet_6->SetMarkerColor(1);
gr_un2_eta_jet_6->SetMarkerStyle(8);
gr_un2_eta_jet_6->SetMarkerSize(1);
gr_un2_eta_jet_6->SetLineColor(12);
gr_un2_eta_jet_6->Draw("P");

TGraph* gr_un2_eta_jet_7 = new TGraph(n,x_un2_eta_jet_7,y_un2_eta_jet_7); 
gr_un2_eta_jet_7->SetTitle("eta_{jet} , E_{T}_jet  systematic");
gr_un2_eta_jet_7->SetMarkerColor(1);
gr_un2_eta_jet_7->SetMarkerStyle(7);
gr_un2_eta_jet_7->SetMarkerSize(2);
gr_un2_eta_jet_7->SetLineColor(1);
gr_un2_eta_jet_7->Draw("C");



// et_jet
can_un2->cd(6);

TCanvas *c_un2_6 = new TCanvas("c_un2_6","Graph of  systematic Uncertainties, et_jet",600,400);

TGraph* gr_un2_et_jet_1 = new TGraph(j,x_un2_et_jet_1,y_un2_et_jet_1); 
gr_un2_et_jet_1->SetTitle("E_{T}_jet , E_{T}_jet  systematic");
gr_un2_et_jet_1->GetYaxis()->SetRangeUser(-0.3,0.3);
gr_un2_et_jet_1->SetMarkerColor(61);
gr_un2_et_jet_1->SetMarkerStyle(7);
c_un2_6->cd();
can_un2->cd(6);
gr_un2_et_jet_1->SetLineWidth(2);
gr_un2_et_jet_1->SetLineColor(61);
 w_et_jet->Draw();//plain_style
gr_un2_et_jet_1->Draw("CP same");

TGraph* gr_un2_et_jet_2 = new TGraph(j,x_un2_et_jet_2,y_un2_et_jet_2); 
gr_un2_et_jet_2->SetTitle("E_{T}_jet , E_{T}_jet  systematic");
gr_un2_et_jet_2->SetMarkerColor(61);
gr_un2_et_jet_2->SetMarkerStyle(7);
c_un2_6->cd();
can_un2->cd(6);
gr_un2_et_jet_2->SetLineWidth(2);
gr_un2_et_jet_2->SetLineColor(61);
gr_un2_et_jet_2->Draw("CP same");

TGraph* gr_un2_et_jet_3 = new TGraph(j,x_un2_et_jet_3,y_un2_et_jet_3); 
gr_un2_et_jet_3->SetTitle("E_{T}_jet , E_{T}_jet  systematic");
gr_un2_et_jet_3->SetMarkerColor(2);
gr_un2_et_jet_3->SetMarkerStyle(7);
gr_un2_et_jet_3->SetMarkerSize(2);
gr_un2_et_jet_3->SetLineColor(2);
gr_un2_et_jet_3->Draw("CP");

TGraph* gr_un2_et_jet_4 = new TGraph(j,x_un2_et_jet_4,y_un2_et_jet_4); 
gr_un2_et_jet_4->SetTitle("E_{T}_jet , E_{T}_jet  systematic");
gr_un2_et_jet_4->SetMarkerColor(2);
gr_un2_et_jet_4->SetMarkerStyle(7);
gr_un2_et_jet_4->SetMarkerSize(2);
gr_un2_et_jet_4->SetLineColor(2);
gr_un2_et_jet_4->Draw("CP");

TGraph* gr_un2_et_jet_5 = new TGraph(j,x_un2_et_jet_5,y_un2_et_jet_5); 
gr_un2_et_jet_5->SetTitle("E_{T}_jet , E_{T}_jet  systematic");
gr_un2_et_jet_5->SetMarkerColor(1);
gr_un2_et_jet_5->SetMarkerStyle(4);
gr_un2_et_jet_5->SetMarkerSize(1);
gr_un2_et_jet_5->SetLineColor(12);
gr_un2_et_jet_5->Draw("P");

TGraph* gr_un2_et_jet_6 = new TGraph(j,x_un2_et_jet_6,y_un2_et_jet_6); 
gr_un2_et_jet_6->SetTitle("E_{T}_jet , E_{T}_jet  systematic");
gr_un2_et_jet_6->SetMarkerColor(1);
gr_un2_et_jet_6->SetMarkerStyle(8);
gr_un2_et_jet_6->SetMarkerSize(1);
gr_un2_et_jet_6->SetLineColor(12);
gr_un2_et_jet_6->Draw("P");

TGraph* gr_un2_et_jet_7 = new TGraph(j,x_un2_et_jet_7,y_un2_et_jet_7); 
gr_un2_et_jet_7->SetTitle("E_{T}_jet , E_{T}_jet  systematic");
gr_un2_et_jet_7->SetMarkerColor(1);
gr_un2_et_jet_7->SetMarkerStyle(7);
gr_un2_et_jet_7->SetMarkerSize(2);
gr_un2_et_jet_7->SetLineColor(1);
gr_un2_et_jet_7->Draw("C");



can_un2->cd(9);
TLegend *leg1 = new TLegend(0.2,0.3,0.9,0.9);
//leg1->SetHeader("MC 06-07p GR");
leg1->AddEntry(gr_un2_eta_1,"Total relative statistical error","l");
leg1->AddEntry(gr_un2_eta_3,"10% line","l");
//leg1->AddEntry(gr_un2_eta_5,"(jet_et < 10) jet_et_corr - 10%","p");
//leg1->AddEntry(gr_un2_eta_5,"(else) jet_et_corr - 3%","p");
//leg1->AddEntry(gr_un2_eta_6,"(jet_et < 10) jet_et_corr + 10%","p");
//leg1->AddEntry(gr_un2_eta_6,"(else) jet_et_corr + 3%","p");
leg1->AddEntry(gr_un2_eta_5,"minus %, MC","p");
leg1->AddEntry(gr_un2_eta_6,"plus %, MC","p");
leg1->SetTextFont(12);
leg1->SetTextSize(0.067);
leg1->SetFillColor(0);
leg1->SetBorderSize(0);
leg1->Draw();

can_un2->Print("MT2_5_un2_jet_et_corr.eps");

// *************** et_jet_systematics un_2  *************** //




// *************** en_photon_systematics un_3  *************** //
TCanvas *can_un3 = new TCanvas("can_un3","Systematic uncertainties en_photon", 0, 0, 1200, 1000);
can_un3->Divide(3,3);
 make_clean_pads(can_un3, 9, 0, 0);//plain_style
 sign_window(can_un3->GetPad(1), w_eta, "#eta^{#gamma}", "rel. uncertainty", "", "middle");//plain_style
 sign_window(can_un3->GetPad(2), w_et, "E_{T}^{#gamma} (GeV)", "rel. uncertainty", "", "middle");//plain_style
 sign_window(can_un3->GetPad(3), w_Q2, "Q^{2} (GeV^{2})", "rel. uncertainty", "", "middle");//plain_style
 sign_window(can_un3->GetPad(4), w_x, "x", "rel. uncertainty", "", "middle");//plain_style
 sign_window(can_un3->GetPad(5), w_eta_jet, "#eta^{jet}", "rel. uncertainty", "", "middle");//plain_style
 sign_window(can_un3->GetPad(6), w_et_jet, "E_{T}^{jet} (GeV)", "rel. uncertainty", "", "middle");//plain_style

 can_un3->GetPad(3)->SetLogx();
 can_un3->GetPad(4)->SetLogx();
 can_un3->GetPad(6)->SetLogx();


// eta_photon
can_un3->cd(1);

TCanvas *c_un3_1 = new TCanvas("c_un3_1","Graph of  systematic Uncertainties, eta",600,400);

TGraph* gr_un3_eta_1 = new TGraph(n,x_un3_eta_1,y_un3_eta_1); 
gr_un3_eta_1->SetTitle("#eta^{#gamma} , e_{#gamma}  systematic");
gr_un3_eta_1->GetYaxis()->SetRangeUser(-.3,.3);
gr_un3_eta_1->SetMarkerColor(61);
gr_un3_eta_1->SetMarkerStyle(7);
c_un3_1->cd();
can_un3->cd(1);
gr_un3_eta_1->SetLineWidth(2);
gr_un3_eta_1->SetLineColor(61);
 w_eta->Draw();
gr_un3_eta_1->Draw("CP SAME");

TGraph* gr_un3_eta_2 = new TGraph(n,x_un3_eta_2,y_un3_eta_2); 
gr_un3_eta_2->SetTitle("#eta^{#gamma} , e_{#gamma}  systematic");
gr_un3_eta_2->SetMarkerColor(61);
gr_un3_eta_2->SetMarkerStyle(7);
c_un3_1->cd();
can_un3->cd(1);
gr_un3_eta_2->SetLineWidth(2);
gr_un3_eta_2->SetLineColor(61);
gr_un3_eta_2->Draw("CP same");

TGraph* gr_un3_eta_3 = new TGraph(n,x_un3_eta_3,y_un3_eta_3); 
gr_un3_eta_3->SetTitle("#eta^{#gamma} , e_{#gamma}  systematic");
gr_un3_eta_3->SetMarkerColor(2);
gr_un3_eta_3->SetMarkerStyle(7);
gr_un3_eta_3->SetMarkerSize(2);
gr_un3_eta_3->SetLineColor(2);
gr_un3_eta_3->Draw("CP");

TGraph* gr_un3_eta_4 = new TGraph(n,x_un3_eta_4,y_un3_eta_4); 
gr_un3_eta_4->SetTitle("#eta^{#gamma} , e_{#gamma}  systematic");
gr_un3_eta_4->SetMarkerColor(2);
gr_un3_eta_4->SetMarkerStyle(7);
gr_un3_eta_4->SetMarkerSize(2);
gr_un3_eta_4->SetLineColor(2);
gr_un3_eta_4->Draw("CP");

TGraph* gr_un3_eta_5 = new TGraph(n,x_un3_eta_5,y_un3_eta_5); 
gr_un3_eta_5->SetTitle("#eta^{#gamma} , e_{#gamma}  systematic");
gr_un3_eta_5->SetMarkerColor(1);
gr_un3_eta_5->SetMarkerStyle(4);
gr_un3_eta_5->SetMarkerSize(1);
gr_un3_eta_5->SetLineColor(12);
gr_un3_eta_5->Draw("P");

TGraph* gr_un3_eta_6 = new TGraph(n,x_un3_eta_6,y_un3_eta_6); 
gr_un3_eta_6->SetTitle("#eta^{#gamma} , e_{#gamma}  systematic");
gr_un3_eta_6->SetMarkerColor(1);
gr_un3_eta_6->SetMarkerStyle(8);
gr_un3_eta_6->SetMarkerSize(1);
gr_un3_eta_6->SetLineColor(12);
gr_un3_eta_6->Draw("P");

TGraph* gr_un3_eta_7 = new TGraph(n,x_un3_eta_7,y_un3_eta_7); 
gr_un3_eta_7->SetTitle("#eta^{#gamma} , e_{#gamma}  systematic");
gr_un3_eta_7->SetMarkerColor(1);
gr_un3_eta_7->SetMarkerStyle(7);
gr_un3_eta_7->SetMarkerSize(2);
gr_un3_eta_7->SetLineColor(1);
gr_un3_eta_7->Draw("C");



// Et_photon
can_un3->cd(2);

TCanvas *c_un3_2 = new TCanvas("c_un3_2","Graph of  systematic Uncertainties, E_T",600,400);

TGraph* gr_un3_et_1 = new TGraph(n,x_un3_et_1,y_un3_et_1); 
gr_un3_et_1->SetTitle("E_{T} , e_{#gamma}  systematic");
gr_un3_et_1->GetYaxis()->SetRangeUser(-.3,.3);
gr_un3_et_1->SetMarkerColor(61);
gr_un3_et_1->SetMarkerStyle(7);
c_un3_2->cd();
can_un3->cd(2);
gr_un3_et_1->SetLineWidth(2);
gr_un3_et_1->SetLineColor(61);
 w_et->Draw();
gr_un3_et_1->Draw("CP SAME");

TGraph* gr_un3_et_2 = new TGraph(n,x_un3_et_2,y_un3_et_2); 
gr_un3_et_2->SetTitle("E_{T} , e_{#gamma}  systematic");
gr_un3_et_2->SetMarkerColor(61);
gr_un3_et_2->SetMarkerStyle(7);
c_un3_2->cd();
can_un3->cd(2);
gr_un3_et_2->SetLineWidth(2);
gr_un3_et_2->SetLineColor(61);
gr_un3_et_2->Draw("CP same");

TGraph* gr_un3_et_3 = new TGraph(n,x_un3_et_3,y_un3_et_3); 
gr_un3_et_3->SetTitle("E_{T} , e_{#gamma}  systematic");
gr_un3_et_3->SetMarkerColor(2);
gr_un3_et_3->SetMarkerStyle(7);
gr_un3_et_3->SetMarkerSize(2);
gr_un3_et_3->SetLineColor(2);
gr_un3_et_3->Draw("CP");

TGraph* gr_un3_et_4 = new TGraph(n,x_un3_et_4,y_un3_et_4); 
gr_un3_et_4->SetTitle("E_{T} , e_{#gamma}  systematic");
gr_un3_et_4->SetMarkerColor(2);
gr_un3_et_4->SetMarkerStyle(7);
gr_un3_et_4->SetMarkerSize(2);
gr_un3_et_4->SetLineColor(2);
gr_un3_et_4->Draw("CP");

TGraph* gr_un3_et_5 = new TGraph(n,x_un3_et_5,y_un3_et_5); 
gr_un3_et_5->SetTitle("E_{T} , e_{#gamma}  systematic");
gr_un3_et_5->SetMarkerColor(1);
gr_un3_et_5->SetMarkerStyle(4);
gr_un3_et_5->SetMarkerSize(1);
gr_un3_et_5->SetLineColor(12);
gr_un3_et_5->Draw("P");

TGraph* gr_un3_et_6 = new TGraph(n,x_un3_et_6,y_un3_et_6); 
gr_un3_et_6->SetTitle("E_{T} , e_{#gamma}  systematic");
gr_un3_et_6->SetMarkerColor(1);
gr_un3_et_6->SetMarkerStyle(8);
gr_un3_et_6->SetMarkerSize(1);
gr_un3_et_6->SetLineColor(12);
gr_un3_et_6->Draw("P");

TGraph* gr_un3_et_7 = new TGraph(n,x_un3_et_7,y_un3_et_7); 
gr_un3_et_7->SetTitle("E_{T} , e_{#gamma}  systematic");
gr_un3_et_7->SetMarkerColor(1);
gr_un3_et_7->SetMarkerStyle(7);
gr_un3_et_7->SetMarkerSize(2);
gr_un3_et_7->SetLineColor(1);
gr_un3_et_7->Draw("C");



// Q2_photon
can_un3->cd(3);

TCanvas *c_un3_3 = new TCanvas("c_un3_3","Graph of  systematic Uncertainties, Q^{2}",600,400);

TGraph* gr_un3_q2_1 = new TGraph(q,x_un3_q2_1,y_un3_q2_1); 
gr_un3_q2_1->SetTitle("Q^{2} , e_{#gamma}  systematic");
gr_un3_q2_1->GetYaxis()->SetRangeUser(-0.3,0.3);
gr_un3_q2_1->SetMarkerColor(61);
gr_un3_q2_1->SetMarkerStyle(7);
c_un3_3->cd();
can_un3->cd(3);
gr_un3_q2_1->SetLineWidth(2);
gr_un3_q2_1->SetLineColor(61);
 w_Q2->Draw();
gr_un3_q2_1->Draw("CP SAME");

TGraph* gr_un3_q2_2 = new TGraph(q,x_un3_q2_2,y_un3_q2_2); 
gr_un3_q2_2->SetTitle("Q^{2} , e_{#gamma}  systematic");
gr_un3_q2_2->SetMarkerColor(61);
gr_un3_q2_2->SetMarkerStyle(7);
c_un3_3->cd();
can_un3->cd(3);
gr_un3_q2_2->SetLineWidth(2);
gr_un3_q2_2->SetLineColor(61);
gr_un3_q2_2->Draw("CP same");

TGraph* gr_un3_q2_3 = new TGraph(q,x_un3_q2_3,y_un3_q2_3); 
gr_un3_q2_3->SetTitle("Q^{2} , e_{#gamma}  systematic");
gr_un3_q2_3->SetMarkerColor(2);
gr_un3_q2_3->SetMarkerStyle(7);
gr_un3_q2_3->SetMarkerSize(2);
gr_un3_q2_3->SetLineColor(2);
gr_un3_q2_3->Draw("CP");

TGraph* gr_un3_q2_4 = new TGraph(q,x_un3_q2_4,y_un3_q2_4); 
gr_un3_q2_4->SetTitle("Q^{2} , e_{#gamma}  systematic");
gr_un3_q2_4->SetMarkerColor(2);
gr_un3_q2_4->SetMarkerStyle(7);
gr_un3_q2_4->SetMarkerSize(2);
gr_un3_q2_4->SetLineColor(2);
gr_un3_q2_4->Draw("CP");

TGraph* gr_un3_q2_5 = new TGraph(q,x_un3_q2_5,y_un3_q2_5); 
gr_un3_q2_5->SetTitle("Q^{2} , e_{#gamma}  systematic");
gr_un3_q2_5->SetMarkerColor(1);
gr_un3_q2_5->SetMarkerStyle(4);
gr_un3_q2_5->SetMarkerSize(1);
gr_un3_q2_5->SetLineColor(12);
gr_un3_q2_5->Draw("P");

TGraph* gr_un3_q2_6 = new TGraph(q,x_un3_q2_6,y_un3_q2_6); 
gr_un3_q2_6->SetTitle("Q^{2} , e_{#gamma}  systematic");
gr_un3_q2_6->SetMarkerColor(1);
gr_un3_q2_6->SetMarkerStyle(8);
gr_un3_q2_6->SetMarkerSize(1);
gr_un3_q2_6->SetLineColor(12);
gr_un3_q2_6->Draw("P");

TGraph* gr_un3_q2_7 = new TGraph(q,x_un3_q2_7,y_un3_q2_7); 
gr_un3_q2_7->SetTitle("Q^{2} , e_{#gamma}  systematic");
gr_un3_q2_7->SetMarkerColor(1);
gr_un3_q2_7->SetMarkerStyle(7);
gr_un3_q2_7->SetMarkerSize(2);
gr_un3_q2_7->SetLineColor(1);
gr_un3_q2_7->Draw("C");



// x_Bjorken
can_un3->cd(4);

TCanvas *c_un3_4 = new TCanvas("c_un3_4","Graph of  systematic Uncertainties, x",600,400);

TGraph* gr_un3_x_1 = new TGraph(n,x_un3_x_1,y_un3_x_1); 
gr_un3_x_1->SetTitle("x , e_{#gamma}  systematic");
gr_un3_x_1->GetYaxis()->SetRangeUser(-.4,.4);
gr_un3_x_1->SetMarkerColor(61);
gr_un3_x_1->SetMarkerStyle(7);
c_un3_4->cd();
can_un3->cd(4);
gr_un3_x_1->SetLineWidth(2);
gr_un3_x_1->SetLineColor(61);
 w_x->Draw();
gr_un3_x_1->Draw("CP SAME");

TGraph* gr_un3_x_2 = new TGraph(n,x_un3_x_2,y_un3_x_2); 
gr_un3_x_2->SetTitle("x , e_{#gamma}  systematic");
gr_un3_x_2->SetMarkerColor(61);
gr_un3_x_2->SetMarkerStyle(7);
c_un3_4->cd();
can_un3->cd(4);
gr_un3_x_2->SetLineWidth(2);
gr_un3_x_2->SetLineColor(61);
gr_un3_x_2->Draw("CP same");

TGraph* gr_un3_x_3 = new TGraph(n,x_un3_x_3,y_un3_x_3); 
gr_un3_x_3->SetTitle("x , e_{#gamma}  systematic");
gr_un3_x_3->SetMarkerColor(2);
gr_un3_x_3->SetMarkerStyle(7);
gr_un3_x_3->SetMarkerSize(2);
gr_un3_x_3->SetLineColor(2);
gr_un3_x_3->Draw("CP");

TGraph* gr_un3_x_4 = new TGraph(n,x_un3_x_4,y_un3_x_4); 
gr_un3_x_4->SetTitle("x , e_{#gamma}  systematic");
gr_un3_x_4->SetMarkerColor(2);
gr_un3_x_4->SetMarkerStyle(7);
gr_un3_x_4->SetMarkerSize(2);
gr_un3_x_4->SetLineColor(2);
gr_un3_x_4->Draw("CP");

TGraph* gr_un3_x_5 = new TGraph(n,x_un3_x_5,y_un3_x_5); 
gr_un3_x_5->SetTitle("x , e_{#gamma}  systematic");
gr_un3_x_5->SetMarkerColor(1);
gr_un3_x_5->SetMarkerStyle(4);
gr_un3_x_5->SetMarkerSize(1);
gr_un3_x_5->SetLineColor(12);
gr_un3_x_5->Draw("P");

TGraph* gr_un3_x_6 = new TGraph(n,x_un3_x_6,y_un3_x_6); 
gr_un3_x_6->SetTitle("x , e_{#gamma}  systematic");
gr_un3_x_6->SetMarkerColor(1);
gr_un3_x_6->SetMarkerStyle(8);
gr_un3_x_6->SetMarkerSize(1);
gr_un3_x_6->SetLineColor(12);
gr_un3_x_6->Draw("P");

TGraph* gr_un3_x_7 = new TGraph(n,x_un3_x_7,y_un3_x_7); 
gr_un3_x_7->SetTitle("x , e_{#gamma}  systematic");
gr_un3_x_7->SetMarkerColor(1);
gr_un3_x_7->SetMarkerStyle(7);
gr_un3_x_7->SetMarkerSize(2);
gr_un3_x_7->SetLineColor(1);
gr_un3_x_7->Draw("C");



// eta_jet
can_un3->cd(5);

TCanvas *c_un3_5 = new TCanvas("c_un3_5","Graph of  systematic Uncertainties, eta_jet",600,400);

TGraph* gr_un3_eta_jet_1 = new TGraph(n,x_un3_eta_jet_1,y_un3_eta_jet_1); 
gr_un3_eta_jet_1->SetTitle("#eta_{jet} , e_{#gamma}  systematic");
gr_un3_eta_jet_1->GetYaxis()->SetRangeUser(-.3,.3);
gr_un3_eta_jet_1->SetMarkerColor(61);
gr_un3_eta_jet_1->SetMarkerStyle(7);
c_un3_5->cd();
can_un3->cd(5);
gr_un3_eta_jet_1->SetLineWidth(2);
gr_un3_eta_jet_1->SetLineColor(61);
 w_eta_jet->Draw();
gr_un3_eta_jet_1->Draw("CP SAME");

TGraph* gr_un3_eta_jet_2 = new TGraph(n,x_un3_eta_jet_2,y_un3_eta_jet_2); 
gr_un3_eta_jet_2->SetTitle("#eta_{jet} , e_{#gamma}  systematic");
gr_un3_eta_jet_2->SetMarkerColor(61);
gr_un3_eta_jet_2->SetMarkerStyle(7);
c_un3_5->cd();
can_un3->cd(5);
gr_un3_eta_jet_2->SetLineWidth(2);
gr_un3_eta_jet_2->SetLineColor(61);
gr_un3_eta_jet_2->Draw("CP same");

TGraph* gr_un3_eta_jet_3 = new TGraph(n,x_un3_eta_jet_3,y_un3_eta_jet_3); 
gr_un3_eta_jet_3->SetTitle("#eta_{jet} , e_{#gamma}  systematic");
gr_un3_eta_jet_3->SetMarkerColor(2);
gr_un3_eta_jet_3->SetMarkerStyle(7);
gr_un3_eta_jet_3->SetMarkerSize(2);
gr_un3_eta_jet_3->SetLineColor(2);
gr_un3_eta_jet_3->Draw("CP");

TGraph* gr_un3_eta_jet_4 = new TGraph(n,x_un3_eta_jet_4,y_un3_eta_jet_4); 
gr_un3_eta_jet_4->SetTitle("#eta_{jet} , e_{#gamma}  systematic");
gr_un3_eta_jet_4->SetMarkerColor(2);
gr_un3_eta_jet_4->SetMarkerStyle(7);
gr_un3_eta_jet_4->SetMarkerSize(2);
gr_un3_eta_jet_4->SetLineColor(2);
gr_un3_eta_jet_4->Draw("CP");

TGraph* gr_un3_eta_jet_5 = new TGraph(n,x_un3_eta_jet_5,y_un3_eta_jet_5); 
gr_un3_eta_jet_5->SetTitle("#eta_{jet} , e_{#gamma}  systematic");
gr_un3_eta_jet_5->SetMarkerColor(1);
gr_un3_eta_jet_5->SetMarkerStyle(4);
gr_un3_eta_jet_5->SetMarkerSize(1);
gr_un3_eta_jet_5->SetLineColor(12);
gr_un3_eta_jet_5->Draw("P");

TGraph* gr_un3_eta_jet_6 = new TGraph(n,x_un3_eta_jet_6,y_un3_eta_jet_6); 
gr_un3_eta_jet_6->SetTitle("#eta_{jet} , e_{#gamma}  systematic");
gr_un3_eta_jet_6->SetMarkerColor(1);
gr_un3_eta_jet_6->SetMarkerStyle(8);
gr_un3_eta_jet_6->SetMarkerSize(1);
gr_un3_eta_jet_6->SetLineColor(12);
gr_un3_eta_jet_6->Draw("P");

TGraph* gr_un3_eta_jet_7 = new TGraph(n,x_un3_eta_jet_7,y_un3_eta_jet_7); 
gr_un3_eta_jet_7->SetTitle("#eta_{jet} , e_{#gamma}  systematic");
gr_un3_eta_jet_7->SetMarkerColor(1);
gr_un3_eta_jet_7->SetMarkerStyle(7);
gr_un3_eta_jet_7->SetMarkerSize(2);
gr_un3_eta_jet_7->SetLineColor(1);
gr_un3_eta_jet_7->Draw("C");


// Et_jet
can_un3->cd(6);

TCanvas *c_un3_6 = new TCanvas("c_un3_6","Graph of  systematic Uncertainties, E_T_jet",600,400);

TGraph* gr_un3_et_jet_1 = new TGraph(j,x_un3_et_jet_1,y_un3_et_jet_1); 
gr_un3_et_jet_1->SetTitle("E_{T_jet} , e_{#gamma}  systematic");
gr_un3_et_jet_1->GetYaxis()->SetRangeUser(-.35,.35);
gr_un3_et_jet_1->SetMarkerColor(61);
gr_un3_et_jet_1->SetMarkerStyle(7);
c_un3_6->cd();
can_un3->cd(6);
gr_un3_et_jet_1->SetLineWidth(2);
gr_un3_et_jet_1->SetLineColor(61);
 w_et_jet->Draw();
gr_un3_et_jet_1->Draw("CP SAME");

TGraph* gr_un3_et_jet_2 = new TGraph(j,x_un3_et_jet_2,y_un3_et_jet_2); 
gr_un3_et_jet_2->SetTitle("E_{T_jet} , e_{#gamma}  systematic");
gr_un3_et_jet_2->SetMarkerColor(61);
gr_un3_et_jet_2->SetMarkerStyle(7);
c_un3_6->cd();
can_un3->cd(6);
gr_un3_et_jet_2->SetLineWidth(2);
gr_un3_et_jet_2->SetLineColor(61);
gr_un3_et_jet_2->Draw("CP same");

TGraph* gr_un3_et_jet_3 = new TGraph(j,x_un3_et_jet_3,y_un3_et_jet_3); 
gr_un3_et_jet_3->SetTitle("E_{T_jet} , e_{#gamma}  systematic");
gr_un3_et_jet_3->SetMarkerColor(2);
gr_un3_et_jet_3->SetMarkerStyle(7);
gr_un3_et_jet_3->SetMarkerSize(2);
gr_un3_et_jet_3->SetLineColor(2);
gr_un3_et_jet_3->Draw("CP");

TGraph* gr_un3_et_jet_4 = new TGraph(j,x_un3_et_jet_4,y_un3_et_jet_4); 
gr_un3_et_jet_4->SetTitle("E_{T_jet} , e_{#gamma}  systematic");
gr_un3_et_jet_4->SetMarkerColor(2);
gr_un3_et_jet_4->SetMarkerStyle(7);
gr_un3_et_jet_4->SetMarkerSize(2);
gr_un3_et_jet_4->SetLineColor(2);
gr_un3_et_jet_4->Draw("CP");

TGraph* gr_un3_et_jet_5 = new TGraph(j,x_un3_et_jet_5,y_un3_et_jet_5); 
gr_un3_et_jet_5->SetTitle("E_{T_jet} , e_{#gamma}  systematic");
gr_un3_et_jet_5->SetMarkerColor(1);
gr_un3_et_jet_5->SetMarkerStyle(4);
gr_un3_et_jet_5->SetMarkerSize(1);
gr_un3_et_jet_5->SetLineColor(12);
gr_un3_et_jet_5->Draw("P");

TGraph* gr_un3_et_jet_6 = new TGraph(j,x_un3_et_jet_6,y_un3_et_jet_6); 
gr_un3_et_jet_6->SetTitle("E_{T_jet} , e_{#gamma}  systematic");
gr_un3_et_jet_6->SetMarkerColor(1);
gr_un3_et_jet_6->SetMarkerStyle(8);
gr_un3_et_jet_6->SetMarkerSize(1);
gr_un3_et_jet_6->SetLineColor(12);
gr_un3_et_jet_6->Draw("P");

TGraph* gr_un3_et_jet_7 = new TGraph(j,x_un3_et_jet_7,y_un3_et_jet_7); 
gr_un3_et_jet_7->SetTitle("E_{T_jet} , e_{#gamma}  systematic");
gr_un3_et_jet_7->SetMarkerColor(1);
gr_un3_et_jet_7->SetMarkerStyle(7);
gr_un3_et_jet_7->SetMarkerSize(2);
gr_un3_et_jet_7->SetLineColor(1);
gr_un3_et_jet_7->Draw("C");



can_un3->cd(9);
TLegend *leg2 = new TLegend(0.2,0.3,0.9,0.9);
leg2->AddEntry(gr_un3_eta_1,"Total relative statistical error","l");
leg2->AddEntry(gr_un3_eta_3,"10% line","l");
leg2->AddEntry(gr_un3_eta_5,"e_{#gamma} - 2%, data","p");
leg2->AddEntry(gr_un3_eta_6,"e_{#gamma} + 2%, data","p");
leg2->SetTextFont(12);
leg2->SetTextSize(0.067);
leg2->SetFillColor(0);
leg2->SetBorderSize(0);
leg2->Draw();

can_un3->Print("MT2_5_un3_en_photon.eps");
// *************** en_photon_systematics un_3  *************** //




// *************** en_el_systematics un_4  *************** //
TCanvas *can_un4 = new TCanvas("can_un4","Systematic uncertainties en_el", 0, 0, 1200, 1000);
can_un4->Divide(3,3);


// eta_photon
can_un4->cd(1);

TCanvas *c_un4_1 = new TCanvas("c_un4_1","Graph of  systematic Uncertainties, eta",600,400);

TGraph* gr_un4_eta_1 = new TGraph(n,x_un4_eta_1,y_un4_eta_1); 
gr_un4_eta_1->SetTitle("#eta^{#gamma} , en_{el}  systematic");
gr_un4_eta_1->GetYaxis()->SetRangeUser(-.25,.25);
gr_un4_eta_1->SetMarkerColor(61);
gr_un4_eta_1->SetMarkerStyle(7);
c_un4_1->cd();
can_un4->cd(1);
gr_un4_eta_1->SetLineWidth(2);
gr_un4_eta_1->SetLineColor(61);
gr_un4_eta_1->Draw("ACP");

TGraph* gr_un4_eta_2 = new TGraph(n,x_un4_eta_2,y_un4_eta_2); 
gr_un4_eta_2->SetTitle("#eta^{#gamma} , en_{el}  systematic");
gr_un4_eta_2->SetMarkerColor(61);
gr_un4_eta_2->SetMarkerStyle(7);
c_un4_1->cd();
can_un4->cd(1);
gr_un4_eta_2->SetLineWidth(2);
gr_un4_eta_2->SetLineColor(61);
gr_un4_eta_2->Draw("CP same");

TGraph* gr_un4_eta_3 = new TGraph(n,x_un4_eta_3,y_un4_eta_3); 
gr_un4_eta_3->SetTitle("#eta^{#gamma} , en_{el}  systematic");
gr_un4_eta_3->SetMarkerColor(2);
gr_un4_eta_3->SetMarkerStyle(7);
gr_un4_eta_3->SetMarkerSize(2);
gr_un4_eta_3->SetLineColor(2);
gr_un4_eta_3->Draw("CP");

TGraph* gr_un4_eta_4 = new TGraph(n,x_un4_eta_4,y_un4_eta_4); 
gr_un4_eta_4->SetTitle("#eta^{#gamma} , en_{el}  systematic");
gr_un4_eta_4->SetMarkerColor(2);
gr_un4_eta_4->SetMarkerStyle(7);
gr_un4_eta_4->SetMarkerSize(2);
gr_un4_eta_4->SetLineColor(2);
gr_un4_eta_4->Draw("CP");

TGraph* gr_un4_eta_5 = new TGraph(n,x_un4_eta_5,y_un4_eta_5); 
gr_un4_eta_5->SetTitle("#eta^{#gamma} , en_{el}  systematic");
gr_un4_eta_5->SetMarkerColor(1);
gr_un4_eta_5->SetMarkerStyle(4);
gr_un4_eta_5->SetMarkerSize(1);
gr_un4_eta_5->SetLineColor(12);
gr_un4_eta_5->Draw("P");

TGraph* gr_un4_eta_6 = new TGraph(n,x_un4_eta_6,y_un4_eta_6); 
gr_un4_eta_6->SetTitle("#eta^{#gamma} , en_{el}  systematic");
gr_un4_eta_6->SetMarkerColor(1);
gr_un4_eta_6->SetMarkerStyle(8);
gr_un4_eta_6->SetMarkerSize(1);
gr_un4_eta_6->SetLineColor(12);
gr_un4_eta_6->Draw("P");

TGraph* gr_un4_eta_7 = new TGraph(n,x_un4_eta_7,y_un4_eta_7); 
gr_un4_eta_7->SetTitle("#eta^{#gamma} , en_{el}  systematic");
gr_un4_eta_7->SetMarkerColor(1);
gr_un4_eta_7->SetMarkerStyle(7);
gr_un4_eta_7->SetMarkerSize(2);
gr_un4_eta_7->SetLineColor(1);
gr_un4_eta_7->Draw("C");



// Et_photon
can_un4->cd(2);

TCanvas *c_un4_2 = new TCanvas("c_un4_2","Graph of  systematic Uncertainties, E_T",600,400);

TGraph* gr_un4_et_1 = new TGraph(n,x_un4_et_1,y_un4_et_1); 
gr_un4_et_1->SetTitle("E_{T} , en_{el}  systematic");
gr_un4_et_1->GetYaxis()->SetRangeUser(-.25,.25);
gr_un4_et_1->SetMarkerColor(61);
gr_un4_et_1->SetMarkerStyle(7);
c_un4_2->cd();
can_un4->cd(2);
gr_un4_et_1->SetLineWidth(2);
gr_un4_et_1->SetLineColor(61);
gr_un4_et_1->Draw("ACP");

TGraph* gr_un4_et_2 = new TGraph(n,x_un4_et_2,y_un4_et_2); 
gr_un4_et_2->SetTitle("E_{T} , en_{el}  systematic");
gr_un4_et_2->SetMarkerColor(61);
gr_un4_et_2->SetMarkerStyle(7);
c_un4_2->cd();
can_un4->cd(2);
gr_un4_et_2->SetLineWidth(2);
gr_un4_et_2->SetLineColor(61);
gr_un4_et_2->Draw("CP same");

TGraph* gr_un4_et_3 = new TGraph(n,x_un4_et_3,y_un4_et_3); 
gr_un4_et_3->SetTitle("E_{T} , en_{el}  systematic");
gr_un4_et_3->SetMarkerColor(2);
gr_un4_et_3->SetMarkerStyle(7);
gr_un4_et_3->SetMarkerSize(2);
gr_un4_et_3->SetLineColor(2);
gr_un4_et_3->Draw("CP");

TGraph* gr_un4_et_4 = new TGraph(n,x_un4_et_4,y_un4_et_4); 
gr_un4_et_4->SetTitle("E_{T} , en_{el}  systematic");
gr_un4_et_4->SetMarkerColor(2);
gr_un4_et_4->SetMarkerStyle(7);
gr_un4_et_4->SetMarkerSize(2);
gr_un4_et_4->SetLineColor(2);
gr_un4_et_4->Draw("CP");

TGraph* gr_un4_et_5 = new TGraph(n,x_un4_et_5,y_un4_et_5); 
gr_un4_et_5->SetTitle("E_{T} , en_{el}  systematic");
gr_un4_et_5->SetMarkerColor(1);
gr_un4_et_5->SetMarkerStyle(4);
gr_un4_et_5->SetMarkerSize(1);
gr_un4_et_5->SetLineColor(12);
gr_un4_et_5->Draw("P");

TGraph* gr_un4_et_6 = new TGraph(n,x_un4_et_6,y_un4_et_6); 
gr_un4_et_6->SetTitle("E_{T} , en_{el}  systematic");
gr_un4_et_6->SetMarkerColor(1);
gr_un4_et_6->SetMarkerStyle(8);
gr_un4_et_6->SetMarkerSize(1);
gr_un4_et_6->SetLineColor(12);
gr_un4_et_6->Draw("P");

TGraph* gr_un4_et_7 = new TGraph(n,x_un4_et_7,y_un4_et_7); 
gr_un4_et_7->SetTitle("E_{T} , en_{el}  systematic");
gr_un4_et_7->SetMarkerColor(1);
gr_un4_et_7->SetMarkerStyle(7);
gr_un4_et_7->SetMarkerSize(2);
gr_un4_et_7->SetLineColor(1);
gr_un4_et_7->Draw("C");



// Q2_photon
can_un4->cd(3);

TCanvas *c_un4_3 = new TCanvas("c_un4_3","Graph of  systematic Uncertainties, Q^{2}",600,400);

TGraph* gr_un4_q2_1 = new TGraph(q,x_un4_q2_1,y_un4_q2_1); 
gr_un4_q2_1->SetTitle("Q^{2} , en_{el}  systematic");
gr_un4_q2_1->GetYaxis()->SetRangeUser(-0.3,0.3);
gr_un4_q2_1->SetMarkerColor(61);
gr_un4_q2_1->SetMarkerStyle(7);
c_un4_3->cd();
can_un4->cd(3);
gr_un4_q2_1->SetLineWidth(2);
gr_un4_q2_1->SetLineColor(61);
gr_un4_q2_1->Draw("ACP");

TGraph* gr_un4_q2_2 = new TGraph(q,x_un4_q2_2,y_un4_q2_2); 
gr_un4_q2_2->SetTitle("Q^{2} , en_{el}  systematic");
gr_un4_q2_2->SetMarkerColor(61);
gr_un4_q2_2->SetMarkerStyle(7);
c_un4_3->cd();
can_un4->cd(3);
gr_un4_q2_2->SetLineWidth(2);
gr_un4_q2_2->SetLineColor(61);
gr_un4_q2_2->Draw("CP same");

TGraph* gr_un4_q2_3 = new TGraph(q,x_un4_q2_3,y_un4_q2_3); 
gr_un4_q2_3->SetTitle("Q^{2} , en_{el}  systematic");
gr_un4_q2_3->SetMarkerColor(2);
gr_un4_q2_3->SetMarkerStyle(7);
gr_un4_q2_3->SetMarkerSize(2);
gr_un4_q2_3->SetLineColor(2);
gr_un4_q2_3->Draw("CP");

TGraph* gr_un4_q2_4 = new TGraph(q,x_un4_q2_4,y_un4_q2_4); 
gr_un4_q2_4->SetTitle("Q^{2} , en_{el}  systematic");
gr_un4_q2_4->SetMarkerColor(2);
gr_un4_q2_4->SetMarkerStyle(7);
gr_un4_q2_4->SetMarkerSize(2);
gr_un4_q2_4->SetLineColor(2);
gr_un4_q2_4->Draw("CP");

TGraph* gr_un4_q2_5 = new TGraph(q,x_un4_q2_5,y_un4_q2_5); 
gr_un4_q2_5->SetTitle("Q^{2} , en_{el}  systematic");
gr_un4_q2_5->SetMarkerColor(1);
gr_un4_q2_5->SetMarkerStyle(4);
gr_un4_q2_5->SetMarkerSize(1);
gr_un4_q2_5->SetLineColor(12);
gr_un4_q2_5->Draw("P");

TGraph* gr_un4_q2_6 = new TGraph(q,x_un4_q2_6,y_un4_q2_6); 
gr_un4_q2_6->SetTitle("Q^{2} , en_{el}  systematic");
gr_un4_q2_6->SetMarkerColor(1);
gr_un4_q2_6->SetMarkerStyle(8);
gr_un4_q2_6->SetMarkerSize(1);
gr_un4_q2_6->SetLineColor(12);
gr_un4_q2_6->Draw("P");

TGraph* gr_un4_q2_7 = new TGraph(q,x_un4_q2_7,y_un4_q2_7); 
gr_un4_q2_7->SetTitle("Q^{2} , en_{el}  systematic");
gr_un4_q2_7->SetMarkerColor(1);
gr_un4_q2_7->SetMarkerStyle(7);
gr_un4_q2_7->SetMarkerSize(2);
gr_un4_q2_7->SetLineColor(1);
gr_un4_q2_7->Draw("C");



// x_Bjorken
can_un4->cd(4);

TCanvas *c_un4_4 = new TCanvas("c_un4_4","Graph of  systematic Uncertainties, x",600,400);

TGraph* gr_un4_x_1 = new TGraph(n,x_un4_x_1,y_un4_x_1); 
gr_un4_x_1->SetTitle("x , en_{el}  systematic");
gr_un4_x_1->GetYaxis()->SetRangeUser(-0.5,0.5);
gr_un4_x_1->SetMarkerColor(61);
gr_un4_x_1->SetMarkerStyle(7);
c_un4_4->cd();
can_un4->cd(4);
gr_un4_x_1->SetLineWidth(2);
gr_un4_x_1->SetLineColor(61);
gr_un4_x_1->Draw("ACP");

TGraph* gr_un4_x_2 = new TGraph(n,x_un4_x_2,y_un4_x_2); 
gr_un4_x_2->SetTitle("x , en_{el}  systematic");
gr_un4_x_2->SetMarkerColor(61);
gr_un4_x_2->SetMarkerStyle(7);
c_un4_4->cd();
can_un4->cd(4);
gr_un4_x_2->SetLineWidth(2);
gr_un4_x_2->SetLineColor(61);
gr_un4_x_2->Draw("CP same");

TGraph* gr_un4_x_3 = new TGraph(n,x_un4_x_3,y_un4_x_3); 
gr_un4_x_3->SetTitle("x , en_{el}  systematic");
gr_un4_x_3->SetMarkerColor(2);
gr_un4_x_3->SetMarkerStyle(7);
gr_un4_x_3->SetMarkerSize(2);
gr_un4_x_3->SetLineColor(2);
gr_un4_x_3->Draw("CP");

TGraph* gr_un4_x_4 = new TGraph(n,x_un4_x_4,y_un4_x_4); 
gr_un4_x_4->SetTitle("x , en_{el}  systematic");
gr_un4_x_4->SetMarkerColor(2);
gr_un4_x_4->SetMarkerStyle(7);
gr_un4_x_4->SetMarkerSize(2);
gr_un4_x_4->SetLineColor(2);
gr_un4_x_4->Draw("CP");

TGraph* gr_un4_x_5 = new TGraph(n,x_un4_x_5,y_un4_x_5); 
gr_un4_x_5->SetTitle("x , en_{el}  systematic");
gr_un4_x_5->SetMarkerColor(1);
gr_un4_x_5->SetMarkerStyle(4);
gr_un4_x_5->SetMarkerSize(1);
gr_un4_x_5->SetLineColor(12);
gr_un4_x_5->Draw("P");

TGraph* gr_un4_x_6 = new TGraph(n,x_un4_x_6,y_un4_x_6); 
gr_un4_x_6->SetTitle("x , en_{el}  systematic");
gr_un4_x_6->SetMarkerColor(1);
gr_un4_x_6->SetMarkerStyle(8);
gr_un4_x_6->SetMarkerSize(1);
gr_un4_x_6->SetLineColor(12);
gr_un4_x_6->Draw("P");

TGraph* gr_un4_x_7 = new TGraph(n,x_un4_x_7,y_un4_x_7); 
gr_un4_x_7->SetTitle("x , en_{el}  systematic");
gr_un4_x_7->SetMarkerColor(1);
gr_un4_x_7->SetMarkerStyle(7);
gr_un4_x_7->SetMarkerSize(2);
gr_un4_x_7->SetLineColor(1);
gr_un4_x_7->Draw("C");



// eta_jet
can_un4->cd(5);

TCanvas *c_un4_5 = new TCanvas("c_un4_5","Graph of  systematic Uncertainties, eta_jet",600,400);

TGraph* gr_un4_eta_jet_1 = new TGraph(n,x_un4_eta_jet_1,y_un4_eta_jet_1); 
gr_un4_eta_jet_1->SetTitle("#eta_{jet} , en_{el}  systematic");
gr_un4_eta_jet_1->GetYaxis()->SetRangeUser(-.25,.25);
gr_un4_eta_jet_1->SetMarkerColor(61);
gr_un4_eta_jet_1->SetMarkerStyle(7);
c_un4_5->cd();
can_un4->cd(5);
gr_un4_eta_jet_1->SetLineWidth(2);
gr_un4_eta_jet_1->SetLineColor(61);
gr_un4_eta_jet_1->Draw("ACP");

TGraph* gr_un4_eta_jet_2 = new TGraph(n,x_un4_eta_jet_2,y_un4_eta_jet_2); 
gr_un4_eta_jet_2->SetTitle("#eta_{jet} , en_{el}  systematic");
gr_un4_eta_jet_2->SetMarkerColor(61);
gr_un4_eta_jet_2->SetMarkerStyle(7);
c_un4_5->cd();
can_un4->cd(5);
gr_un4_eta_jet_2->SetLineWidth(2);
gr_un4_eta_jet_2->SetLineColor(61);
gr_un4_eta_jet_2->Draw("CP same");

TGraph* gr_un4_eta_jet_3 = new TGraph(n,x_un4_eta_jet_3,y_un4_eta_jet_3); 
gr_un4_eta_jet_3->SetTitle("#eta_{jet} , en_{el}  systematic");
gr_un4_eta_jet_3->SetMarkerColor(2);
gr_un4_eta_jet_3->SetMarkerStyle(7);
gr_un4_eta_jet_3->SetMarkerSize(2);
gr_un4_eta_jet_3->SetLineColor(2);
gr_un4_eta_jet_3->Draw("CP");

TGraph* gr_un4_eta_jet_4 = new TGraph(n,x_un4_eta_jet_4,y_un4_eta_jet_4); 
gr_un4_eta_jet_4->SetTitle("#eta_{jet} , en_{el}  systematic");
gr_un4_eta_jet_4->SetMarkerColor(2);
gr_un4_eta_jet_4->SetMarkerStyle(7);
gr_un4_eta_jet_4->SetMarkerSize(2);
gr_un4_eta_jet_4->SetLineColor(2);
gr_un4_eta_jet_4->Draw("CP");

TGraph* gr_un4_eta_jet_5 = new TGraph(n,x_un4_eta_jet_5,y_un4_eta_jet_5); 
gr_un4_eta_jet_5->SetTitle("#eta_{jet} , en_{el}  systematic");
gr_un4_eta_jet_5->SetMarkerColor(1);
gr_un4_eta_jet_5->SetMarkerStyle(4);
gr_un4_eta_jet_5->SetMarkerSize(1);
gr_un4_eta_jet_5->SetLineColor(12);
gr_un4_eta_jet_5->Draw("P");

TGraph* gr_un4_eta_jet_6 = new TGraph(n,x_un4_eta_jet_6,y_un4_eta_jet_6); 
gr_un4_eta_jet_6->SetTitle("#eta_{jet} , en_{el}  systematic");
gr_un4_eta_jet_6->SetMarkerColor(1);
gr_un4_eta_jet_6->SetMarkerStyle(8);
gr_un4_eta_jet_6->SetMarkerSize(1);
gr_un4_eta_jet_6->SetLineColor(12);
gr_un4_eta_jet_6->Draw("P");

TGraph* gr_un4_eta_jet_7 = new TGraph(n,x_un4_eta_jet_7,y_un4_eta_jet_7); 
gr_un4_eta_jet_7->SetTitle("#eta_{jet} , en_{el}  systematic");
gr_un4_eta_jet_7->SetMarkerColor(1);
gr_un4_eta_jet_7->SetMarkerStyle(7);
gr_un4_eta_jet_7->SetMarkerSize(2);
gr_un4_eta_jet_7->SetLineColor(1);
gr_un4_eta_jet_7->Draw("C");



// Et_jet
can_un4->cd(6);

TCanvas *c_un4_6 = new TCanvas("c_un4_6","Graph of  systematic Uncertainties, E_T_jet",600,400);

TGraph* gr_un4_et_jet_1 = new TGraph(j,x_un4_et_jet_1,y_un4_et_jet_1); 
gr_un4_et_jet_1->SetTitle("E_{T_jet} , en_{el}  systematic");
gr_un4_et_jet_1->GetYaxis()->SetRangeUser(-.3,.3);
gr_un4_et_jet_1->SetMarkerColor(61);
gr_un4_et_jet_1->SetMarkerStyle(7);
c_un4_6->cd();
can_un4->cd(6);
gr_un4_et_jet_1->SetLineWidth(2);
gr_un4_et_jet_1->SetLineColor(61);
gr_un4_et_jet_1->Draw("ACP");

TGraph* gr_un4_et_jet_2 = new TGraph(j,x_un4_et_jet_2,y_un4_et_jet_2); 
gr_un4_et_jet_2->SetTitle("E_{T_jet} , en_{el}  systematic");
gr_un4_et_jet_2->SetMarkerColor(61);
gr_un4_et_jet_2->SetMarkerStyle(7);
c_un4_6->cd();
can_un4->cd(6);
gr_un4_et_jet_2->SetLineWidth(2);
gr_un4_et_jet_2->SetLineColor(61);
gr_un4_et_jet_2->Draw("CP same");

TGraph* gr_un4_et_jet_3 = new TGraph(j,x_un4_et_jet_3,y_un4_et_jet_3); 
gr_un4_et_jet_3->SetTitle("E_{T_jet} , en_{el}  systematic");
gr_un4_et_jet_3->SetMarkerColor(2);
gr_un4_et_jet_3->SetMarkerStyle(7);
gr_un4_et_jet_3->SetMarkerSize(2);
gr_un4_et_jet_3->SetLineColor(2);
gr_un4_et_jet_3->Draw("CP");

TGraph* gr_un4_et_jet_4 = new TGraph(j,x_un4_et_jet_4,y_un4_et_jet_4); 
gr_un4_et_jet_4->SetTitle("E_{T_jet} , en_{el}  systematic");
gr_un4_et_jet_4->SetMarkerColor(2);
gr_un4_et_jet_4->SetMarkerStyle(7);
gr_un4_et_jet_4->SetMarkerSize(2);
gr_un4_et_jet_4->SetLineColor(2);
gr_un4_et_jet_4->Draw("CP");

TGraph* gr_un4_et_jet_5 = new TGraph(j,x_un4_et_jet_5,y_un4_et_jet_5); 
gr_un4_et_jet_5->SetTitle("E_{T_jet} , en_{el}  systematic");
gr_un4_et_jet_5->SetMarkerColor(1);
gr_un4_et_jet_5->SetMarkerStyle(4);
gr_un4_et_jet_5->SetMarkerSize(1);
gr_un4_et_jet_5->SetLineColor(12);
gr_un4_et_jet_5->Draw("P");

TGraph* gr_un4_et_jet_6 = new TGraph(j,x_un4_et_jet_6,y_un4_et_jet_6); 
gr_un4_et_jet_6->SetTitle("E_{T_jet} , en_{el}  systematic");
gr_un4_et_jet_6->SetMarkerColor(1);
gr_un4_et_jet_6->SetMarkerStyle(8);
gr_un4_et_jet_6->SetMarkerSize(1);
gr_un4_et_jet_6->SetLineColor(12);
gr_un4_et_jet_6->Draw("P");

TGraph* gr_un4_et_jet_7 = new TGraph(j,x_un4_et_jet_7,y_un4_et_jet_7); 
gr_un4_et_jet_7->SetTitle("E_{T_jet} , en_{el}  systematic");
gr_un4_et_jet_7->SetMarkerColor(1);
gr_un4_et_jet_7->SetMarkerStyle(7);
gr_un4_et_jet_7->SetMarkerSize(2);
gr_un4_et_jet_7->SetLineColor(1);
gr_un4_et_jet_7->Draw("C");


can_un4->cd(9);
TLegend *leg3 = new TLegend(0.2,0.3,0.9,0.9);
leg3->AddEntry(gr_un3_eta_1,"Total relative statistical error","l");
leg3->AddEntry(gr_un3_eta_3,"10% line","l");
leg3->AddEntry(gr_un3_eta_5,"e_{el} - 2%, data","p");
leg3->AddEntry(gr_un3_eta_6,"e_{el} + 2%, data","p");
leg3->SetTextFont(12);
leg3->SetTextSize(0.067);
leg3->SetFillColor(0);
leg3->SetBorderSize(0);
leg3->Draw();

can_un4->Print("MT2_5_un4_en_el.eps");

// *************** en_el_systematics un_4  *************** //




// *************** deltaZ_systematics un_5  *************** //
TCanvas *can_un5 = new TCanvas("can_un5","Systematic uncertainties delta_Z", 0, 0, 1200, 1000);
can_un5->Divide(3,3);


// eta_photon
can_un5->cd(1);

TCanvas *c_un5_1 = new TCanvas("c_un5_1","Graph of  systematic Uncertainties, eta",600,400);

TGraph* gr_un5_eta_1 = new TGraph(n,x_un5_eta_1,y_un5_eta_1); 
gr_un5_eta_1->SetTitle("#eta^{#gamma} , delta^{z}  systematic");
gr_un5_eta_1->GetYaxis()->SetRangeUser(-.21,.21);
gr_un5_eta_1->SetMarkerColor(61);
gr_un5_eta_1->SetMarkerStyle(7);
c_un5_1->cd();
can_un5->cd(1);
gr_un5_eta_1->SetLineWidth(2);
gr_un5_eta_1->SetLineColor(61);
gr_un5_eta_1->Draw("ACP");

TGraph* gr_un5_eta_2 = new TGraph(n,x_un5_eta_2,y_un5_eta_2); 
gr_un5_eta_2->SetTitle("#eta^{#gamma} , delta^{z}  systematic");
gr_un5_eta_2->SetMarkerColor(61);
gr_un5_eta_2->SetMarkerStyle(7);
c_un5_1->cd();
can_un5->cd(1);
gr_un5_eta_2->SetLineWidth(2);
gr_un5_eta_2->SetLineColor(61);
gr_un5_eta_2->Draw("CP same");

TGraph* gr_un5_eta_3 = new TGraph(n,x_un5_eta_3,y_un5_eta_3); 
gr_un5_eta_3->SetTitle("#eta^{#gamma} , delta^{z}  systematic");
gr_un5_eta_3->SetMarkerColor(2);
gr_un5_eta_3->SetMarkerStyle(7);
gr_un5_eta_3->SetMarkerSize(2);
gr_un5_eta_3->SetLineColor(2);
gr_un5_eta_3->Draw("CP");

TGraph* gr_un5_eta_4 = new TGraph(n,x_un5_eta_4,y_un5_eta_4); 
gr_un5_eta_4->SetTitle("#eta^{#gamma} , delta^{z}  systematic");
gr_un5_eta_4->SetMarkerColor(2);
gr_un5_eta_4->SetMarkerStyle(7);
gr_un5_eta_4->SetMarkerSize(2);
gr_un5_eta_4->SetLineColor(2);
gr_un5_eta_4->Draw("CP");

TGraph* gr_un5_eta_5 = new TGraph(n,x_un5_eta_5,y_un5_eta_5); 
gr_un5_eta_5->SetTitle("#eta^{#gamma} , delta^{z}  systematic");
gr_un5_eta_5->SetMarkerColor(1);
gr_un5_eta_5->SetMarkerStyle(4);
gr_un5_eta_5->SetMarkerSize(1);
gr_un5_eta_5->SetLineColor(12);
gr_un5_eta_5->Draw("P");

TGraph* gr_un5_eta_6 = new TGraph(n,x_un5_eta_6,y_un5_eta_6); 
gr_un5_eta_6->SetTitle("#eta^{#gamma} , delta^{z}  systematic");
gr_un5_eta_6->SetMarkerColor(1);
gr_un5_eta_6->SetMarkerStyle(8);
gr_un5_eta_6->SetMarkerSize(1);
gr_un5_eta_6->SetLineColor(12);
gr_un5_eta_6->Draw("P");

TGraph* gr_un5_eta_7 = new TGraph(n,x_un5_eta_7,y_un5_eta_7); 
gr_un5_eta_7->SetTitle("#eta^{#gamma} , delta^{z}  systematic");
gr_un5_eta_7->SetMarkerColor(1);
gr_un5_eta_7->SetMarkerStyle(7);
gr_un5_eta_7->SetMarkerSize(2);
gr_un5_eta_7->SetLineColor(1);
gr_un5_eta_7->Draw("C");



// Et_photon
can_un5->cd(2);

TCanvas *c_un5_2 = new TCanvas("c_un5_2","Graph of  systematic Uncertainties, E_T",600,400);

TGraph* gr_un5_et_1 = new TGraph(n,x_un5_et_1,y_un5_et_1); 
gr_un5_et_1->SetTitle("E_{T} , delta^{z}  systematic");
gr_un5_et_1->GetYaxis()->SetRangeUser(-.21,.21);
gr_un5_et_1->SetMarkerColor(61);
gr_un5_et_1->SetMarkerStyle(7);
c_un5_2->cd();
can_un5->cd(2);
gr_un5_et_1->SetLineWidth(2);
gr_un5_et_1->SetLineColor(61);
gr_un5_et_1->Draw("ACP");

TGraph* gr_un5_et_2 = new TGraph(n,x_un5_et_2,y_un5_et_2); 
gr_un5_et_2->SetTitle("E_{T} , delta^{z}  systematic");
gr_un5_et_2->SetMarkerColor(61);
gr_un5_et_2->SetMarkerStyle(7);
c_un5_2->cd();
can_un5->cd(2);
gr_un5_et_2->SetLineWidth(2);
gr_un5_et_2->SetLineColor(61);
gr_un5_et_2->Draw("CP same");

TGraph* gr_un5_et_3 = new TGraph(n,x_un5_et_3,y_un5_et_3); 
gr_un5_et_3->SetTitle("E_{T} , delta^{z}  systematic");
gr_un5_et_3->SetMarkerColor(2);
gr_un5_et_3->SetMarkerStyle(7);
gr_un5_et_3->SetMarkerSize(2);
gr_un5_et_3->SetLineColor(2);
gr_un5_et_3->Draw("CP");

TGraph* gr_un5_et_4 = new TGraph(n,x_un5_et_4,y_un5_et_4); 
gr_un5_et_4->SetTitle("E_{T} , delta^{z}  systematic");
gr_un5_et_4->SetMarkerColor(2);
gr_un5_et_4->SetMarkerStyle(7);
gr_un5_et_4->SetMarkerSize(2);
gr_un5_et_4->SetLineColor(2);
gr_un5_et_4->Draw("CP");

TGraph* gr_un5_et_5 = new TGraph(n,x_un5_et_5,y_un5_et_5); 
gr_un5_et_5->SetTitle("E_{T} , delta^{z}  systematic");
gr_un5_et_5->SetMarkerColor(1);
gr_un5_et_5->SetMarkerStyle(4);
gr_un5_et_5->SetMarkerSize(1);
gr_un5_et_5->SetLineColor(12);
gr_un5_et_5->Draw("P");

TGraph* gr_un5_et_6 = new TGraph(n,x_un5_et_6,y_un5_et_6); 
gr_un5_et_6->SetTitle("E_{T} , delta^{z}  systematic");
gr_un5_et_6->SetMarkerColor(1);
gr_un5_et_6->SetMarkerStyle(8);
gr_un5_et_6->SetMarkerSize(1);
gr_un5_et_6->SetLineColor(12);
gr_un5_et_6->Draw("P");

TGraph* gr_un5_et_7 = new TGraph(n,x_un5_et_7,y_un5_et_7); 
gr_un5_et_7->SetTitle("E_{T} , delta^{z}  systematic");
gr_un5_et_7->SetMarkerColor(1);
gr_un5_et_7->SetMarkerStyle(7);
gr_un5_et_7->SetMarkerSize(2);
gr_un5_et_7->SetLineColor(1);
gr_un5_et_7->Draw("C");



// Q2_photon
can_un5->cd(3);

TCanvas *c_un5_3 = new TCanvas("c_un5_3","Graph of  systematic Uncertainties, Q^{2}",600,400);

TGraph* gr_un5_q2_1 = new TGraph(q,x_un5_q2_1,y_un5_q2_1); 
gr_un5_q2_1->SetTitle("Q^{2} , delta^{z}  systematic");
gr_un5_q2_1->GetYaxis()->SetRangeUser(-.3,.3);
gr_un5_q2_1->SetMarkerColor(61);
gr_un5_q2_1->SetMarkerStyle(7);
c_un5_3->cd();
can_un5->cd(3);
gr_un5_q2_1->SetLineWidth(2);
gr_un5_q2_1->SetLineColor(61);
gr_un5_q2_1->Draw("ACP");

TGraph* gr_un5_q2_2 = new TGraph(q,x_un5_q2_2,y_un5_q2_2); 
gr_un5_q2_2->SetTitle("Q^{2} , delta^{z}  systematic");
gr_un5_q2_2->SetMarkerColor(61);
gr_un5_q2_2->SetMarkerStyle(7);
c_un5_3->cd();
can_un5->cd(3);
gr_un5_q2_2->SetLineWidth(2);
gr_un5_q2_2->SetLineColor(61);
gr_un5_q2_2->Draw("CP same");

TGraph* gr_un5_q2_3 = new TGraph(q,x_un5_q2_3,y_un5_q2_3); 
gr_un5_q2_3->SetTitle("Q^{2} , delta^{z}  systematic");
gr_un5_q2_3->SetMarkerColor(2);
gr_un5_q2_3->SetMarkerStyle(7);
gr_un5_q2_3->SetMarkerSize(2);
gr_un5_q2_3->SetLineColor(2);
gr_un5_q2_3->Draw("CP");

TGraph* gr_un5_q2_4 = new TGraph(q,x_un5_q2_4,y_un5_q2_4); 
gr_un5_q2_4->SetTitle("Q^{2} , delta^{z}  systematic");
gr_un5_q2_4->SetMarkerColor(2);
gr_un5_q2_4->SetMarkerStyle(7);
gr_un5_q2_4->SetMarkerSize(2);
gr_un5_q2_4->SetLineColor(2);
gr_un5_q2_4->Draw("CP");

TGraph* gr_un5_q2_5 = new TGraph(q,x_un5_q2_5,y_un5_q2_5); 
gr_un5_q2_5->SetTitle("Q^{2} , delta^{z}  systematic");
gr_un5_q2_5->SetMarkerColor(1);
gr_un5_q2_5->SetMarkerStyle(4);
gr_un5_q2_5->SetMarkerSize(1);
gr_un5_q2_5->SetLineColor(12);
gr_un5_q2_5->Draw("P");

TGraph* gr_un5_q2_6 = new TGraph(q,x_un5_q2_6,y_un5_q2_6); 
gr_un5_q2_6->SetTitle("Q^{2} , delta^{z}  systematic");
gr_un5_q2_6->SetMarkerColor(1);
gr_un5_q2_6->SetMarkerStyle(8);
gr_un5_q2_6->SetMarkerSize(1);
gr_un5_q2_6->SetLineColor(12);
gr_un5_q2_6->Draw("P");

TGraph* gr_un5_q2_7 = new TGraph(q,x_un5_q2_7,y_un5_q2_7); 
gr_un5_q2_7->SetTitle("Q^{2} , delta^{z}  systematic");
gr_un5_q2_7->SetMarkerColor(1);
gr_un5_q2_7->SetMarkerStyle(7);
gr_un5_q2_7->SetMarkerSize(2);
gr_un5_q2_7->SetLineColor(1);
gr_un5_q2_7->Draw("C");



// x_Bjorken
can_un5->cd(4);

TCanvas *c_un5_4 = new TCanvas("c_un5_4","Graph of  systematic Uncertainties, x",600,400);

TGraph* gr_un5_x_1 = new TGraph(n,x_un5_x_1,y_un5_x_1); 
gr_un5_x_1->SetTitle("x , delta^{z}  systematic");
gr_un5_x_1->GetYaxis()->SetRangeUser(-.5,.5);
gr_un5_x_1->SetMarkerColor(61);
gr_un5_x_1->SetMarkerStyle(7);
c_un5_4->cd();
can_un5->cd(4);
gr_un5_x_1->SetLineWidth(2);
gr_un5_x_1->SetLineColor(61);
gr_un5_x_1->Draw("ACP");

TGraph* gr_un5_x_2 = new TGraph(n,x_un5_x_2,y_un5_x_2); 
gr_un5_x_2->SetTitle("x , delta^{z}  systematic");
gr_un5_x_2->SetMarkerColor(61);
gr_un5_x_2->SetMarkerStyle(7);
c_un5_4->cd();
can_un5->cd(4);
gr_un5_x_2->SetLineWidth(2);
gr_un5_x_2->SetLineColor(61);
gr_un5_x_2->Draw("CP same");

TGraph* gr_un5_x_3 = new TGraph(n,x_un5_x_3,y_un5_x_3); 
gr_un5_x_3->SetTitle("x , delta^{z}  systematic");
gr_un5_x_3->SetMarkerColor(2);
gr_un5_x_3->SetMarkerStyle(7);
gr_un5_x_3->SetMarkerSize(2);
gr_un5_x_3->SetLineColor(2);
gr_un5_x_3->Draw("CP");

TGraph* gr_un5_x_4 = new TGraph(n,x_un5_x_4,y_un5_x_4); 
gr_un5_x_4->SetTitle("x , delta^{z}  systematic");
gr_un5_x_4->SetMarkerColor(2);
gr_un5_x_4->SetMarkerStyle(7);
gr_un5_x_4->SetMarkerSize(2);
gr_un5_x_4->SetLineColor(2);
gr_un5_x_4->Draw("CP");

TGraph* gr_un5_x_5 = new TGraph(n,x_un5_x_5,y_un5_x_5); 
gr_un5_x_5->SetTitle("x, delta^{z}  systematic");
gr_un5_x_5->SetMarkerColor(1);
gr_un5_x_5->SetMarkerStyle(4);
gr_un5_x_5->SetMarkerSize(1);
gr_un5_x_5->SetLineColor(12);
gr_un5_x_5->Draw("P");

TGraph* gr_un5_x_6 = new TGraph(n,x_un5_x_6,y_un5_x_6); 
gr_un5_x_6->SetTitle("x , delta^{z}  systematic");
gr_un5_x_6->SetMarkerColor(1);
gr_un5_x_6->SetMarkerStyle(8);
gr_un5_x_6->SetMarkerSize(1);
gr_un5_x_6->SetLineColor(12);
gr_un5_x_6->Draw("P");

TGraph* gr_un5_x_7 = new TGraph(n,x_un5_x_7,y_un5_x_7); 
gr_un5_x_7->SetTitle("x , delta^{z}  systematic");
gr_un5_x_7->SetMarkerColor(1);
gr_un5_x_7->SetMarkerStyle(7);
gr_un5_x_7->SetMarkerSize(2);
gr_un5_x_7->SetLineColor(1);
gr_un5_x_7->Draw("C");



// eta_jet
can_un5->cd(5);

TCanvas *c_un5_5 = new TCanvas("c_un5_5","Graph of  systematic Uncertainties, eta_jet",600,400);

TGraph* gr_un5_eta_jet_1 = new TGraph(n,x_un5_eta_jet_1,y_un5_eta_jet_1); 
gr_un5_eta_jet_1->SetTitle("#eta_{jet} , delta^{z}  systematic");
gr_un5_eta_jet_1->GetYaxis()->SetRangeUser(-.21,.21);
gr_un5_eta_jet_1->SetMarkerColor(61);
gr_un5_eta_jet_1->SetMarkerStyle(7);
c_un5_5->cd();
can_un5->cd(5);
gr_un5_eta_jet_1->SetLineWidth(2);
gr_un5_eta_jet_1->SetLineColor(61);
gr_un5_eta_jet_1->Draw("ACP");

TGraph* gr_un5_eta_jet_2 = new TGraph(n,x_un5_eta_jet_2,y_un5_eta_jet_2); 
gr_un5_eta_jet_2->SetTitle("#eta_{jet} , delta^{z}  systematic");
gr_un5_eta_jet_2->SetMarkerColor(61);
gr_un5_eta_jet_2->SetMarkerStyle(7);
c_un5_5->cd();
can_un5->cd(5);
gr_un5_eta_jet_2->SetLineWidth(2);
gr_un5_eta_jet_2->SetLineColor(61);
gr_un5_eta_jet_2->Draw("CP same");

TGraph* gr_un5_eta_jet_3 = new TGraph(n,x_un5_eta_jet_3,y_un5_eta_jet_3); 
gr_un5_eta_jet_3->SetTitle("#eta_{jet} , delta^{z}  systematic");
gr_un5_eta_jet_3->SetMarkerColor(2);
gr_un5_eta_jet_3->SetMarkerStyle(7);
gr_un5_eta_jet_3->SetMarkerSize(2);
gr_un5_eta_jet_3->SetLineColor(2);
gr_un5_eta_jet_3->Draw("CP");

TGraph* gr_un5_eta_jet_4 = new TGraph(n,x_un5_eta_jet_4,y_un5_eta_jet_4); 
gr_un5_eta_jet_4->SetTitle("#eta_{jet} , delta^{z}  systematic");
gr_un5_eta_jet_4->SetMarkerColor(2);
gr_un5_eta_jet_4->SetMarkerStyle(7);
gr_un5_eta_jet_4->SetMarkerSize(2);
gr_un5_eta_jet_4->SetLineColor(2);
gr_un5_eta_jet_4->Draw("CP");

TGraph* gr_un5_eta_jet_5 = new TGraph(n,x_un5_eta_jet_5,y_un5_eta_jet_5); 
gr_un5_eta_jet_5->SetTitle("#eta_{jet} , delta^{z}  systematic");
gr_un5_eta_jet_5->SetMarkerColor(1);
gr_un5_eta_jet_5->SetMarkerStyle(4);
gr_un5_eta_jet_5->SetMarkerSize(1);
gr_un5_eta_jet_5->SetLineColor(12);
gr_un5_eta_jet_5->Draw("P");

TGraph* gr_un5_eta_jet_6 = new TGraph(n,x_un5_eta_jet_6,y_un5_eta_jet_6); 
gr_un5_eta_jet_6->SetTitle("#eta_{jet} , delta^{z}  systematic");
gr_un5_eta_jet_6->SetMarkerColor(1);
gr_un5_eta_jet_6->SetMarkerStyle(8);
gr_un5_eta_jet_6->SetMarkerSize(1);
gr_un5_eta_jet_6->SetLineColor(12);
gr_un5_eta_jet_6->Draw("P");

TGraph* gr_un5_eta_jet_7 = new TGraph(n,x_un5_eta_jet_7,y_un5_eta_jet_7); 
gr_un5_eta_jet_7->SetTitle("#eta_{jet} , delta^{z}  systematic");
gr_un5_eta_jet_7->SetMarkerColor(1);
gr_un5_eta_jet_7->SetMarkerStyle(7);
gr_un5_eta_jet_7->SetMarkerSize(2);
gr_un5_eta_jet_7->SetLineColor(1);
gr_un5_eta_jet_7->Draw("C");



// Et_jet
can_un5->cd(6);

TCanvas *c_un5_6 = new TCanvas("c_un5_6","Graph of  systematic Uncertainties, E_T_jet",600,400);

TGraph* gr_un5_et_jet_1 = new TGraph(j,x_un5_et_jet_1,y_un5_et_jet_1); 
gr_un5_et_jet_1->SetTitle("E_{T_jet} , delta^{z}  systematic");
gr_un5_et_jet_1->GetYaxis()->SetRangeUser(-.3,.3);
gr_un5_et_jet_1->SetMarkerColor(61);
gr_un5_et_jet_1->SetMarkerStyle(7);
c_un5_6->cd();
can_un5->cd(6);
gr_un5_et_jet_1->SetLineWidth(2);
gr_un5_et_jet_1->SetLineColor(61);
gr_un5_et_jet_1->Draw("ACP");

TGraph* gr_un5_et_jet_2 = new TGraph(j,x_un5_et_jet_2,y_un5_et_jet_2); 
gr_un5_et_jet_2->SetTitle("E_{T_jet} , delta^{z}  systematic");
gr_un5_et_jet_2->SetMarkerColor(61);
gr_un5_et_jet_2->SetMarkerStyle(7);
c_un5_6->cd();
can_un5->cd(6);
gr_un5_et_jet_2->SetLineWidth(2);
gr_un5_et_jet_2->SetLineColor(61);
gr_un5_et_jet_2->Draw("CP same");

TGraph* gr_un5_et_jet_3 = new TGraph(j,x_un5_et_jet_3,y_un5_et_jet_3); 
gr_un5_et_jet_3->SetTitle("E_{T_jet} , delta^{z}  systematic");
gr_un5_et_jet_3->SetMarkerColor(2);
gr_un5_et_jet_3->SetMarkerStyle(7);
gr_un5_et_jet_3->SetMarkerSize(2);
gr_un5_et_jet_3->SetLineColor(2);
gr_un5_et_jet_3->Draw("CP");

TGraph* gr_un5_et_jet_4 = new TGraph(j,x_un5_et_jet_4,y_un5_et_jet_4); 
gr_un5_et_jet_4->SetTitle("E_{T_jet} , delta^{z}  systematic");
gr_un5_et_jet_4->SetMarkerColor(2);
gr_un5_et_jet_4->SetMarkerStyle(7);
gr_un5_et_jet_4->SetMarkerSize(2);
gr_un5_et_jet_4->SetLineColor(2);
gr_un5_et_jet_4->Draw("CP");

TGraph* gr_un5_et_jet_5 = new TGraph(j,x_un5_et_jet_5,y_un5_et_jet_5); 
gr_un5_et_jet_5->SetTitle("E_{T_jet} , delta^{z}  systematic");
gr_un5_et_jet_5->SetMarkerColor(1);
gr_un5_et_jet_5->SetMarkerStyle(4);
gr_un5_et_jet_5->SetMarkerSize(1);
gr_un5_et_jet_5->SetLineColor(12);
gr_un5_et_jet_5->Draw("P");

TGraph* gr_un5_et_jet_6 = new TGraph(j,x_un5_et_jet_6,y_un5_et_jet_6); 
gr_un5_et_jet_6->SetTitle("E_{T_jet} , delta^{z}  systematic");
gr_un5_et_jet_6->SetMarkerColor(1);
gr_un5_et_jet_6->SetMarkerStyle(8);
gr_un5_et_jet_6->SetMarkerSize(1);
gr_un5_et_jet_6->SetLineColor(12);
gr_un5_et_jet_6->Draw("P");

TGraph* gr_un5_et_jet_7 = new TGraph(j,x_un5_et_jet_7,y_un5_et_jet_7); 
gr_un5_et_jet_7->SetTitle("E_{T_jet} , delta^{z}  systematic");
gr_un5_et_jet_7->SetMarkerColor(1);
gr_un5_et_jet_7->SetMarkerStyle(7);
gr_un5_et_jet_7->SetMarkerSize(2);
gr_un5_et_jet_7->SetLineColor(1);
gr_un5_et_jet_7->Draw("C");


can_un5->cd(9);
TLegend *leg4 = new TLegend(0.2,0.3,0.9,0.9);
leg4->AddEntry(gr_un3_eta_1,"Total relative statistical errorr","l");
leg4->AddEntry(gr_un3_eta_3,"10% line","l");
leg4->AddEntry(gr_un3_eta_5,"#delta z < 0.6, data","p");
leg4->AddEntry(gr_un3_eta_6,"#delta z < 1.0, data","p");
leg4->SetTextFont(12);
leg4->SetTextSize(0.067);
leg4->SetFillColor(0);
leg4->SetBorderSize(0);
leg4->Draw();

can_un5->Print("MT2_5_un5_deltaZ.eps");
// *************** deltaZ_systematics un_5  *************** //



// *************** total_systematics *************** //
TCanvas *can_tot = new TCanvas("can_tot","Total uncertainties", 0, 0, 1200, 1000);
can_tot->Divide(3,3);


// eta_photon
can_tot->cd(1);

TCanvas *c_tot_1 = new TCanvas("c_tot_1","Total uncertainties, eta",600,400);

TGraph* gr_tot_eta_1 = new TGraph(n,x_tot_eta_1,y_tot_eta_1); 
gr_tot_eta_1->SetTitle("#eta^{#gamma} , Total uncertainties");
gr_tot_eta_1->GetYaxis()->SetRangeUser(-1.,1.);
gr_tot_eta_1->SetMarkerColor(61);
gr_tot_eta_1->SetMarkerStyle(7);
c_tot_1->cd();
can_tot->cd(1);
gr_tot_eta_1->SetLineWidth(2);
gr_tot_eta_1->SetLineColor(61);
gr_tot_eta_1->Draw("ACP");

TGraph* gr_tot_eta_2 = new TGraph(n,x_tot_eta_2,y_tot_eta_2); 
gr_tot_eta_2->SetTitle("#eta^{#gamma} , Total uncertainties");
gr_tot_eta_2->SetMarkerColor(61);
gr_tot_eta_2->SetMarkerStyle(7);
c_tot_1->cd();
can_tot->cd(1);
gr_tot_eta_2->SetLineWidth(2);
gr_tot_eta_2->SetLineColor(61);
gr_tot_eta_2->Draw("CP same");

TGraph* gr_tot_eta_3 = new TGraph(n,x_tot_eta_3,y_tot_eta_3); 
gr_tot_eta_3->SetTitle("#eta^{#gamma} , Total uncertainties");
gr_tot_eta_3->SetMarkerColor(2);
gr_tot_eta_3->SetMarkerStyle(7);
gr_tot_eta_3->SetMarkerSize(2);
gr_tot_eta_3->SetLineColor(2);
gr_tot_eta_3->Draw("CP");

TGraph* gr_tot_eta_4 = new TGraph(n,x_tot_eta_4,y_tot_eta_4); 
gr_tot_eta_4->SetTitle("#eta^{#gamma} , Total uncertainties");
gr_tot_eta_4->SetMarkerColor(2);
gr_tot_eta_4->SetMarkerStyle(7);
gr_tot_eta_4->SetMarkerSize(2);
gr_tot_eta_4->SetLineColor(2);
gr_tot_eta_4->Draw("CP");

TGraph* gr_tot_eta_5 = new TGraph(n,x_tot_eta_5,y_tot_eta_5); 
gr_tot_eta_5->SetTitle("#eta^{#gamma} , Total uncertainties");
gr_tot_eta_5->SetMarkerColor(1);
gr_tot_eta_5->SetMarkerStyle(4);
gr_tot_eta_5->SetMarkerSize(1);
gr_tot_eta_5->SetLineColor(12);
gr_tot_eta_5->Draw("P");

TGraph* gr_tot_eta_6 = new TGraph(n,x_tot_eta_6,y_tot_eta_6); 
gr_tot_eta_6->SetTitle("#eta^{#gamma} , Total uncertainties");
gr_tot_eta_6->SetMarkerColor(1);
gr_tot_eta_6->SetMarkerStyle(8);
gr_tot_eta_6->SetMarkerSize(1);
gr_tot_eta_6->SetLineColor(12);
gr_tot_eta_6->Draw("P");

TGraph* gr_tot_eta_7 = new TGraph(n,x_tot_eta_7,y_tot_eta_7); 
gr_tot_eta_7->SetTitle("#eta^{#gamma} , Total uncertainties");
gr_tot_eta_7->SetMarkerColor(1);
gr_tot_eta_7->SetMarkerStyle(7);
gr_tot_eta_7->SetMarkerSize(2);
gr_tot_eta_7->SetLineColor(1);
gr_tot_eta_7->Draw("C");


// Et_photon
can_tot->cd(2);

TCanvas *c_tot_2 = new TCanvas("c_tot_2","Total uncertainties, E_T",600,400);

TGraph* gr_tot_et_1 = new TGraph(n,x_tot_et_1,y_tot_et_1); 
gr_tot_et_1->SetTitle("E_{T} , Total uncertainties");
gr_tot_et_1->GetYaxis()->SetRangeUser(-1.,1.);
gr_tot_et_1->SetMarkerColor(61);
gr_tot_et_1->SetMarkerStyle(7);
c_tot_2->cd();
can_tot->cd(2);
gr_tot_et_1->SetLineWidth(2);
gr_tot_et_1->SetLineColor(61);
gr_tot_et_1->Draw("ACP");

TGraph* gr_tot_et_2 = new TGraph(n,x_tot_et_2,y_tot_et_2); 
gr_tot_et_2->SetTitle("E_{T} , Total uncertainties");
gr_tot_et_2->SetMarkerColor(61);
gr_tot_et_2->SetMarkerStyle(7);
c_tot_2->cd();
can_tot->cd(2);
gr_tot_et_2->SetLineWidth(2);
gr_tot_et_2->SetLineColor(61);
gr_tot_et_2->Draw("CP same");

TGraph* gr_tot_et_3 = new TGraph(n,x_tot_et_3,y_tot_et_3); 
gr_tot_et_3->SetTitle("E_{T} , Total uncertainties");
gr_tot_et_3->SetMarkerColor(2);
gr_tot_et_3->SetMarkerStyle(7);
gr_tot_et_3->SetMarkerSize(2);
gr_tot_et_3->SetLineColor(2);
gr_tot_et_3->Draw("CP");

TGraph* gr_tot_et_4 = new TGraph(n,x_tot_et_4,y_tot_et_4); 
gr_tot_et_4->SetTitle("E_{T} , Total uncertainties");
gr_tot_et_4->SetMarkerColor(2);
gr_tot_et_4->SetMarkerStyle(7);
gr_tot_et_4->SetMarkerSize(2);
gr_tot_et_4->SetLineColor(2);
gr_tot_et_4->Draw("CP");

TGraph* gr_tot_et_5 = new TGraph(n,x_tot_et_5,y_tot_et_5); 
gr_tot_et_5->SetTitle("E_{T} , Total uncertainties");
gr_tot_et_5->SetMarkerColor(1);
gr_tot_et_5->SetMarkerStyle(4);
gr_tot_et_5->SetMarkerSize(1);
gr_tot_et_5->SetLineColor(12);
gr_tot_et_5->Draw("P");

TGraph* gr_tot_et_6 = new TGraph(n,x_tot_et_6,y_tot_et_6); 
gr_tot_et_6->SetTitle("E_{T} , Total uncertainties");
gr_tot_et_6->SetMarkerColor(1);
gr_tot_et_6->SetMarkerStyle(8);
gr_tot_et_6->SetMarkerSize(1);
gr_tot_et_6->SetLineColor(12);
gr_tot_et_6->Draw("P");

TGraph* gr_tot_et_7 = new TGraph(n,x_tot_et_7,y_tot_et_7); 
gr_tot_et_7->SetTitle("E_{T} , Total uncertainties");
gr_tot_et_7->SetMarkerColor(1);
gr_tot_et_7->SetMarkerStyle(7);
gr_tot_et_7->SetMarkerSize(2);
gr_tot_et_7->SetLineColor(1);
gr_tot_et_7->Draw("C");



// Q2_photon
can_tot->cd(3);

TCanvas *c_tot_3 = new TCanvas("c_tot_3","Total uncertainties, Q^{2}",600,400);

TGraph* gr_tot_q2_1 = new TGraph(q,x_tot_q2_1,y_tot_q2_1); 
gr_tot_q2_1->SetTitle("Q^{2} , Total uncertainties");
gr_tot_q2_1->GetYaxis()->SetRangeUser(-0.6,0.6);
gr_tot_q2_1->SetMarkerColor(61);
gr_tot_q2_1->SetMarkerStyle(7);
c_tot_3->cd();
can_tot->cd(3);
gr_tot_q2_1->SetLineWidth(2);
gr_tot_q2_1->SetLineColor(61);
gr_tot_q2_1->Draw("ACP");

TGraph* gr_tot_q2_2 = new TGraph(q,x_tot_q2_2,y_tot_q2_2); 
gr_tot_q2_2->SetTitle("Q^{2} , Total uncertainties");
gr_tot_q2_2->SetMarkerColor(61);
gr_tot_q2_2->SetMarkerStyle(7);
c_tot_3->cd();
can_tot->cd(3);
gr_tot_q2_2->SetLineWidth(2);
gr_tot_q2_2->SetLineColor(61);
gr_tot_q2_2->Draw("CP same");

TGraph* gr_tot_q2_3 = new TGraph(q,x_tot_q2_3,y_tot_q2_3); 
gr_tot_q2_3->SetTitle("Q^{2} , Total uncertainties");
gr_tot_q2_3->SetMarkerColor(2);
gr_tot_q2_3->SetMarkerStyle(7);
gr_tot_q2_3->SetMarkerSize(2);
gr_tot_q2_3->SetLineColor(2);
gr_tot_q2_3->Draw("CP");

TGraph* gr_tot_q2_4 = new TGraph(q,x_tot_q2_4,y_tot_q2_4); 
gr_tot_q2_4->SetTitle("Q^{2} , Total uncertainties");
gr_tot_q2_4->SetMarkerColor(2);
gr_tot_q2_4->SetMarkerStyle(7);
gr_tot_q2_4->SetMarkerSize(2);
gr_tot_q2_4->SetLineColor(2);
gr_tot_q2_4->Draw("CP");

TGraph* gr_tot_q2_5 = new TGraph(q,x_tot_q2_5,y_tot_q2_5); 
gr_tot_q2_5->SetTitle("Q^{2} , Total uncertainties");
gr_tot_q2_5->SetMarkerColor(1);
gr_tot_q2_5->SetMarkerStyle(4);
gr_tot_q2_5->SetMarkerSize(1);
gr_tot_q2_5->SetLineColor(12);
gr_tot_q2_5->Draw("P");

TGraph* gr_tot_q2_6 = new TGraph(q,x_tot_q2_6,y_tot_q2_6); 
gr_tot_q2_6->SetTitle("Q^{2} , Total uncertainties");
gr_tot_q2_6->SetMarkerColor(1);
gr_tot_q2_6->SetMarkerStyle(8);
gr_tot_q2_6->SetMarkerSize(1);
gr_tot_q2_6->SetLineColor(12);
gr_tot_q2_6->Draw("P");

TGraph* gr_tot_q2_7 = new TGraph(q,x_tot_q2_7,y_tot_q2_7); 
gr_tot_q2_7->SetTitle("Q^{2} , Total uncertainties");
gr_tot_q2_7->SetMarkerColor(1);
gr_tot_q2_7->SetMarkerStyle(7);
gr_tot_q2_7->SetMarkerSize(2);
gr_tot_q2_7->SetLineColor(1);
gr_tot_q2_7->Draw("C");



// x_Bjorken
can_tot->cd(4);

TCanvas *c_tot_4 = new TCanvas("c_tot_4","Total uncertainties, x",600,400);

TGraph* gr_tot_x_1 = new TGraph(n,x_tot_x_1,y_tot_x_1); 
gr_tot_x_1->SetTitle("x , Total uncertainties");
gr_tot_x_1->GetYaxis()->SetRangeUser(-1.,1.);
gr_tot_x_1->SetMarkerColor(61);
gr_tot_x_1->SetMarkerStyle(7);
c_tot_4->cd();
can_tot->cd(4);
gr_tot_x_1->SetLineWidth(2);
gr_tot_x_1->SetLineColor(61);
gr_tot_x_1->Draw("ACP");

TGraph* gr_tot_x_2 = new TGraph(n,x_tot_x_2,y_tot_x_2); 
gr_tot_x_2->SetTitle("x , Total uncertainties");
gr_tot_x_2->SetMarkerColor(61);
gr_tot_x_2->SetMarkerStyle(7);
c_tot_4->cd();
can_tot->cd(4);
gr_tot_x_2->SetLineWidth(2);
gr_tot_x_2->SetLineColor(61);
gr_tot_x_2->Draw("CP same");

TGraph* gr_tot_x_3 = new TGraph(n,x_tot_x_3,y_tot_x_3); 
gr_tot_x_3->SetTitle("x , Total uncertainties");
gr_tot_x_3->SetMarkerColor(2);
gr_tot_x_3->SetMarkerStyle(7);
gr_tot_x_3->SetMarkerSize(2);
gr_tot_x_3->SetLineColor(2);
gr_tot_x_3->Draw("CP");

TGraph* gr_tot_x_4 = new TGraph(n,x_tot_x_4,y_tot_x_4); 
gr_tot_x_4->SetTitle("x , Total uncertainties");
gr_tot_x_4->SetMarkerColor(2);
gr_tot_x_4->SetMarkerStyle(7);
gr_tot_x_4->SetMarkerSize(2);
gr_tot_x_4->SetLineColor(2);
gr_tot_x_4->Draw("CP");

TGraph* gr_tot_x_5 = new TGraph(n,x_tot_x_5,y_tot_x_5); 
gr_tot_x_5->SetTitle("x , Total uncertainties");
gr_tot_x_5->SetMarkerColor(1);
gr_tot_x_5->SetMarkerStyle(4);
gr_tot_x_5->SetMarkerSize(1);
gr_tot_x_5->SetLineColor(12);
gr_tot_x_5->Draw("P");

TGraph* gr_tot_x_6 = new TGraph(n,x_tot_x_6,y_tot_x_6); 
gr_tot_x_6->SetTitle("x , delta^{z}  systematic");
gr_tot_x_6->SetMarkerColor(1);
gr_tot_x_6->SetMarkerStyle(8);
gr_tot_x_6->SetMarkerSize(1);
gr_tot_x_6->SetLineColor(12);
gr_tot_x_6->Draw("P");

TGraph* gr_tot_x_7 = new TGraph(n,x_tot_x_7,y_tot_x_7); 
gr_tot_x_7->SetTitle("x , Total uncertainties");
gr_tot_x_7->SetMarkerColor(1);
gr_tot_x_7->SetMarkerStyle(7);
gr_tot_x_7->SetMarkerSize(2);
gr_tot_x_7->SetLineColor(1);
gr_tot_x_7->Draw("C");



// eta_jet
can_tot->cd(5);

TCanvas *c_tot_5 = new TCanvas("c_tot_5","Total uncertainties, eta_jet",600,400);

TGraph* gr_tot_eta_jet_1 = new TGraph(n,x_tot_eta_jet_1,y_tot_eta_jet_1); 
gr_tot_eta_jet_1->SetTitle("#eta_{jet} , Total uncertainties");
gr_tot_eta_jet_1->GetYaxis()->SetRangeUser(-0.6,0.6);
gr_tot_eta_jet_1->SetMarkerColor(61);
gr_tot_eta_jet_1->SetMarkerStyle(7);
c_tot_5->cd();
can_tot->cd(5);
gr_tot_eta_jet_1->SetLineWidth(2);
gr_tot_eta_jet_1->SetLineColor(61);
gr_tot_eta_jet_1->Draw("ACP");

TGraph* gr_tot_eta_jet_2 = new TGraph(n,x_tot_eta_jet_2,y_tot_eta_jet_2); 
gr_tot_eta_jet_2->SetTitle("#eta_{jet} , Total uncertainties");
gr_tot_eta_jet_2->SetMarkerColor(61);
gr_tot_eta_jet_2->SetMarkerStyle(7);
c_tot_5->cd();
can_tot->cd(5);
gr_tot_eta_jet_2->SetLineWidth(2);
gr_tot_eta_jet_2->SetLineColor(61);
gr_tot_eta_jet_2->Draw("CP same");

TGraph* gr_tot_eta_jet_3 = new TGraph(n,x_tot_eta_jet_3,y_tot_eta_jet_3); 
gr_tot_eta_jet_3->SetTitle("#eta_{jet} , Total uncertainties");
gr_tot_eta_jet_3->SetMarkerColor(2);
gr_tot_eta_jet_3->SetMarkerStyle(7);
gr_tot_eta_jet_3->SetMarkerSize(2);
gr_tot_eta_jet_3->SetLineColor(2);
gr_tot_eta_jet_3->Draw("CP");

TGraph* gr_tot_eta_jet_4 = new TGraph(n,x_tot_eta_jet_4,y_tot_eta_jet_4); 
gr_tot_eta_jet_4->SetTitle("#eta_{jet} , Total uncertainties");
gr_tot_eta_jet_4->SetMarkerColor(2);
gr_tot_eta_jet_4->SetMarkerStyle(7);
gr_tot_eta_jet_4->SetMarkerSize(2);
gr_tot_eta_jet_4->SetLineColor(2);
gr_tot_eta_jet_4->Draw("CP");

TGraph* gr_tot_eta_jet_5 = new TGraph(n,x_tot_eta_jet_5,y_tot_eta_jet_5); 
gr_tot_eta_jet_5->SetTitle("#eta_{jet} , Total uncertainties");
gr_tot_eta_jet_5->SetMarkerColor(1);
gr_tot_eta_jet_5->SetMarkerStyle(4);
gr_tot_eta_jet_5->SetMarkerSize(1);
gr_tot_eta_jet_5->SetLineColor(12);
gr_tot_eta_jet_5->Draw("P");

TGraph* gr_tot_eta_jet_6 = new TGraph(n,x_tot_eta_jet_6,y_tot_eta_jet_6); 
gr_tot_eta_jet_6->SetTitle("#eta_{jet} , Total uncertainties");
gr_tot_eta_jet_6->SetMarkerColor(1);
gr_tot_eta_jet_6->SetMarkerStyle(8);
gr_tot_eta_jet_6->SetMarkerSize(1);
gr_tot_eta_jet_6->SetLineColor(12);
gr_tot_eta_jet_6->Draw("P");

TGraph* gr_tot_eta_jet_7 = new TGraph(n,x_tot_eta_jet_7,y_tot_eta_jet_7); 
gr_tot_eta_jet_7->SetTitle("#eta_{jet} , Total uncertainties");
gr_tot_eta_jet_7->SetMarkerColor(1);
gr_tot_eta_jet_7->SetMarkerStyle(7);
gr_tot_eta_jet_7->SetMarkerSize(2);
gr_tot_eta_jet_7->SetLineColor(1);
gr_tot_eta_jet_7->Draw("C");


// Et_jet
can_tot->cd(6);

TCanvas *c_tot_6 = new TCanvas("c_tot_6","Total uncertainties, E_T_jet",600,400);

TGraph* gr_tot_et_jet_1 = new TGraph(j,x_tot_et_jet_1,y_tot_et_jet_1); 
gr_tot_et_jet_1->SetTitle("E_{T_jet} , Total uncertainties");
gr_tot_et_jet_1->GetYaxis()->SetRangeUser(-0.7,0.7);
gr_tot_et_jet_1->SetMarkerColor(61);
gr_tot_et_jet_1->SetMarkerStyle(7);
c_tot_6->cd();
can_tot->cd(6);
gr_tot_et_jet_1->SetLineWidth(2);
gr_tot_et_jet_1->SetLineColor(61);
gr_tot_et_jet_1->Draw("ACP");

TGraph* gr_tot_et_jet_2 = new TGraph(j,x_tot_et_jet_2,y_tot_et_jet_2); 
gr_tot_et_jet_2->SetTitle("E_{T_jet} , Total uncertainties");
gr_tot_et_jet_2->SetMarkerColor(61);
gr_tot_et_jet_2->SetMarkerStyle(7);
c_tot_6->cd();
can_tot->cd(6);
gr_tot_et_jet_2->SetLineWidth(2);
gr_tot_et_jet_2->SetLineColor(61);
gr_tot_et_jet_2->Draw("CP same");

TGraph* gr_tot_et_jet_3 = new TGraph(j,x_tot_et_jet_3,y_tot_et_jet_3); 
gr_tot_et_jet_3->SetTitle("E_{T_jet} , Total uncertainties");
gr_tot_et_jet_3->SetMarkerColor(2);
gr_tot_et_jet_3->SetMarkerStyle(7);
gr_tot_et_jet_3->SetMarkerSize(2);
gr_tot_et_jet_3->SetLineColor(2);
gr_tot_et_jet_3->Draw("CP");

TGraph* gr_tot_et_jet_4 = new TGraph(j,x_tot_et_jet_4,y_tot_et_jet_4); 
gr_tot_et_jet_4->SetTitle("E_{T_jet} , Total uncertainties");
gr_tot_et_jet_4->SetMarkerColor(2);
gr_tot_et_jet_4->SetMarkerStyle(7);
gr_tot_et_jet_4->SetMarkerSize(2);
gr_tot_et_jet_4->SetLineColor(2);
gr_tot_et_jet_4->Draw("CP");

TGraph* gr_tot_et_jet_5 = new TGraph(j,x_tot_et_jet_5,y_tot_et_jet_5); 
gr_tot_et_jet_5->SetTitle("E_{T_jet} , Total uncertainties");
gr_tot_et_jet_5->SetMarkerColor(1);
gr_tot_et_jet_5->SetMarkerStyle(4);
gr_tot_et_jet_5->SetMarkerSize(1);
gr_tot_et_jet_5->SetLineColor(12);
gr_tot_et_jet_5->Draw("P");

TGraph* gr_tot_et_jet_6 = new TGraph(j,x_tot_et_jet_6,y_tot_et_jet_6); 
gr_tot_et_jet_6->SetTitle("E_{T_jet} , Total uncertainties");
gr_tot_et_jet_6->SetMarkerColor(1);
gr_tot_et_jet_6->SetMarkerStyle(8);
gr_tot_et_jet_6->SetMarkerSize(1);
gr_tot_et_jet_6->SetLineColor(12);
gr_tot_et_jet_6->Draw("P");

TGraph* gr_tot_et_jet_7 = new TGraph(j,x_tot_et_jet_7,y_tot_et_jet_7); 
gr_tot_et_jet_7->SetTitle("E_{T_jet} , Total uncertainties");
gr_tot_et_jet_7->SetMarkerColor(1);
gr_tot_et_jet_7->SetMarkerStyle(7);
gr_tot_et_jet_7->SetMarkerSize(2);
gr_tot_et_jet_7->SetLineColor(1);
gr_tot_et_jet_7->Draw("C");




can_tot->cd(9);
TLegend *leg5 = new TLegend(0.2,0.3,0.9,0.9);
leg5->AddEntry(gr_un3_eta_1,"Statistical unc.","l");
leg5->AddEntry(gr_un3_eta_3,"10% line","l");
leg5->AddEntry(gr_un3_eta_5,"Total  systematic unc.","p");
leg5->AddEntry(gr_un3_eta_6,"Total  systematic unc.","p");
leg5->SetTextFont(12);
leg5->SetTextSize(0.067);
leg5->SetFillColor(0);
leg5->SetBorderSize(0);
leg5->Draw();

can_tot->Print("MT2_5_total.eps");
// *************** total_systematics *************** //



return 0;
}
