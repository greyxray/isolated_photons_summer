//version before work on fits
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include <TH1D.h>
#include <TFitter.h>
#include <TRandom3.h>
#include <TH2D.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TAxis.h>
#include <TGaxis.h>
#include <TFrame.h>
#include <TF1.h>
#include <TStyle.h>
#include <TString.h>
#include <TMath.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TProfile.h>
#include <TText.h>
#include <TGraphAsymmErrors.h>
#include <TLorentzVector.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TROOT.h>
#include <TPaveLabel.h>

#include "plot_style_utils.h"
#include "../inc/constants.h"
//#include "plot_style_utils.h"

TString fit_method = "deltaz";
TString chi_method = "Barlow-Beeston";//Gauss
unsigned int QQfit = 0; 
Bool_t nodebugmode = kFALSE;
/*
0 : data = photons * a + bg' * (1 - a);
    QQ' = QQ.scale([Data - LL] / QQ)
    bg' = bg.ccale([Data - LL] / bg)
1 : data = LL + QQ' * a + bg' * (1 - a);
    QQ' = QQ.scale([Data - LL] / QQ)
    bg' = bg.ccale([Data] / bg)
*/
Bool_t g_include_04p_data = kFALSE;
const Int_t n_data_type = 4;// data norad rad prph
const Int_t n_cross = 12; //et, eta, q2, x, et_jet, eta_jet, xgamma, xp, dphi, deta, dphi_e_ph, deta_e_ph
const Int_t n_periods = 3; //0405e, 06e, 0607p


Double_t param_eta_PhotonsFit[number_etabins] = {0.};
Double_t param_err_eta_PhotonsFit[number_etabins] = {0.};
Double_t param_eta[number_etabins] = {0.};
Double_t param_err_eta[number_etabins] = {0.};
Double_t chi2_eta[number_etabins] = {0.};
Int_t    dof_eta[number_etabins] = {0};
Int_t    left_eta[number_etabins] = {0};
Int_t    right_eta[number_etabins] = {0};

Double_t param_xgamma_PhotonsFit[number_xgamma_bins] = {0.};
Double_t param_err_xgamma_PhotonsFit[number_xgamma_bins] = {0.};
Double_t param_xgamma[number_xgamma_bins] = {0.};
Double_t param_err_xgamma[number_xgamma_bins] = {0.};
Double_t chi2_xgamma[number_xgamma_bins] = {0.};
Int_t    dof_xgamma[number_xgamma_bins] = {0};
Int_t    left_xgamma[number_xgamma_bins] = {0};
Int_t    right_xgamma[number_xgamma_bins] = {0};

Double_t param_xp_PhotonsFit[number_xp_bins] = {0.};
Double_t param_err_xp_PhotonsFit[number_xp_bins] = {0.};
Double_t param_xp[number_xp_bins] = {0.};
Double_t param_err_xp[number_xp_bins] = {0.};
Double_t chi2_xp[number_xp_bins] = {0.};
Int_t    dof_xp[number_xp_bins] = {0};
Int_t    left_xp[number_xp_bins] = {0};
Int_t    right_xp[number_xp_bins] = {0};

Double_t param_dphi_PhotonsFit[number_dphi_bins] = {0.};
Double_t param_err_dphi_PhotonsFit[number_dphi_bins] = {0.};
Double_t param_dphi[number_dphi_bins] = {0.};
Double_t param_err_dphi[number_dphi_bins] = {0.};
Double_t chi2_dphi[number_dphi_bins] = {0.};
Int_t    dof_dphi[number_dphi_bins] = {0};
Int_t    left_dphi[number_dphi_bins] = {0};
Int_t    right_dphi[number_dphi_bins] = {0};

Double_t param_deta_PhotonsFit[number_deta_bins] = {0.};
Double_t param_err_deta_PhotonsFit[number_deta_bins] = {0.};
Double_t param_deta[number_deta_bins] = {0.};
Double_t param_err_deta[number_deta_bins] = {0.};
Double_t chi2_deta[number_deta_bins] = {0.};
Int_t    dof_deta[number_deta_bins] = {0};
Int_t    left_deta[number_deta_bins] = {0};
Int_t    right_deta[number_deta_bins] = {0};

Double_t param_dphi_e_ph_PhotonsFit[number_dphi_e_ph_bins] = {0.};
Double_t param_err_dphi_e_ph_PhotonsFit[number_dphi_e_ph_bins] = {0.};
Double_t param_dphi_e_ph[number_dphi_e_ph_bins] = {0.};
Double_t param_err_dphi_e_ph[number_dphi_e_ph_bins] = {0.};
Double_t chi2_dphi_e_ph[number_dphi_e_ph_bins] = {0.};
Int_t    dof_dphi_e_ph[number_dphi_e_ph_bins] = {0};
Int_t    left_dphi_e_ph[number_dphi_e_ph_bins] = {0};
Int_t    right_dphi_e_ph[number_dphi_e_ph_bins] = {0};

Double_t param_deta_e_ph_PhotonsFit[number_deta_e_ph_bins] = {0.};
Double_t param_err_deta_e_ph_PhotonsFit[number_deta_e_ph_bins] = {0.};
Double_t param_deta_e_ph[number_deta_e_ph_bins] = {0.};
Double_t param_err_deta_e_ph[number_deta_e_ph_bins] = {0.};
Double_t chi2_deta_e_ph[number_deta_e_ph_bins] = {0.};
Int_t    dof_deta_e_ph[number_deta_e_ph_bins] = {0};
Int_t    left_deta_e_ph[number_deta_e_ph_bins] = {0};
Int_t    right_deta_e_ph[number_deta_e_ph_bins] = {0};

Double_t param_et_PhotonsFit[number_etbins] = {0.};
Double_t param_err_et_PhotonsFit[number_etbins] = {0.};
Double_t param_et[number_etbins] = {0.};
Double_t param_err_et[number_etbins] = {0.};
Double_t chi2_et[number_etbins] = {0.};
Int_t    dof_et[number_etbins] = {0};
Int_t    left_et[number_etbins] = {0};
Int_t    right_et[number_etbins] = {0};

Double_t param_q2_PhotonsFit[number_Q2bins] = {0.};
Double_t param_err_q2_PhotonsFit[number_Q2bins] = {0.} ;
Double_t param_q2[number_Q2bins] = {0.};
Double_t param_err_q2[number_Q2bins] = {0.} ;
Double_t chi2_q2[number_Q2bins] = {0.};
Int_t    dof_q2[number_Q2bins] = {0};
Int_t    left_q2[number_Q2bins] = {0};
Int_t    right_q2[number_Q2bins] = {0};

Double_t param_x_PhotonsFit[number_xbins] = {0.};
Double_t param_err_x_PhotonsFit[number_xbins] = {0.}; 
Double_t param_x[number_xbins] = {0.};
Double_t param_err_x[number_xbins] = {0.}; 
Double_t chi2_x[number_xbins] = {0.};
Int_t    dof_x[number_xbins] = {0};
Int_t    left_x[number_xbins] = {0};
Int_t    right_x[number_xbins] = {0};

Double_t param_et_jet_PhotonsFit[number_et_jetbins] = {0.};
Double_t param_err_et_jet_PhotonsFit[number_et_jetbins] = {0.};
Double_t param_et_jet[number_et_jetbins] = {0.};
Double_t param_err_et_jet[number_et_jetbins] = {0.}; 
Double_t chi2_et_jet[number_et_jetbins] = {0.};
Int_t    dof_et_jet[number_et_jetbins] = {0};
Int_t    left_et_jet[number_et_jetbins] = {0};
Int_t    right_et_jet[number_et_jetbins] = {0};

Double_t param_eta_jet_PhotonsFit[number_eta_jetbins] = {0.};
Double_t param_err_eta_jet_PhotonsFit[number_eta_jetbins] = {0.}; 
Double_t param_eta_jet[number_eta_jetbins] = {0.};
Double_t param_err_eta_jet[number_eta_jetbins] = {0.}; 
Double_t chi2_eta_jet[number_eta_jetbins] = {0.};
Int_t    dof_eta_jet[number_eta_jetbins] = {0};
Int_t    left_eta_jet[number_eta_jetbins] = {0};
Int_t    right_eta_jet[number_eta_jetbins] = {0};


Double_t * PhotonsFits[6] = {param_xp_PhotonsFit, param_xgamma_PhotonsFit, param_deta_PhotonsFit, param_dphi_PhotonsFit, param_dphi_e_ph_PhotonsFit, param_deta_e_ph_PhotonsFit};
Double_t * PhotonsFits_err[6] = {param_err_xp_PhotonsFit, param_err_xgamma_PhotonsFit, param_err_deta_PhotonsFit, param_err_dphi_PhotonsFit, param_err_dphi_e_ph_PhotonsFit, param_err_deta_e_ph_PhotonsFit};
TFile *f;// = new TFile("cross_sec_histos.root", "recreate", "root file with histohrams");
//f->cd();
void dout();
template <typename Head, typename... Tail>
void dout(Head , Tail... );

Bool_t once = kTRUE;

#include "hist.c"
Hist hist;

Double_t sys_fit = 0.8;
void dout() 
{
    cout << endl; 
}
template <typename Head, typename... Tail>
void dout(Head H, Tail... T) 
{
  cout << H << ' ';
  dout(T...);
}

Double_t b_scale, d_scale;//for the reparam
Int_t GetFitRange( TH1D* h, bool f=true)
{
    if (f) 
    {
        
        return h->FindBin(0.05);
    } //left range
    else 
    {
        if (once) 
        dout("right ",h->FindBin(sys_fit),"sys_fit=",sys_fit);//0.6 - 1.0
        once = kFALSE;
        return h->FindBin(sys_fit);
    }
}

Double_t GetSumError(TH1D* h) 
{
    Double_t sum = 0; 
    for (Int_t i = 0; i < h->GetNbinsX(); i++) 
        sum += pow(h->GetBinError(i+1), 2); 
    return TMath::Sqrt(sum);
}

void DoReparametrisation(Int_t histindex, Double_t* param, Double_t* param_err, Int_t index)
{
    /*Double_t a = param[index], da = param_err[index];

    Double_t       b = hist.hist_mc_norad_sum[histindex]->GetBinContent(index + 1) ;
    Double_t       p = hist.hist_mc_photon_sum[histindex]->GetBinContent(index + 1) ;
    Double_t       l = hist.hist_mc_rad_sum[histindex]->GetBinContent(index + 1);
    Double_t       dd = hist.hist_data_sum[histindex]->GetBinError(index + 1);
    Double_t       db = hist.hist_mc_norad_sum[histindex]->GetBinError(index + 1) ;
    Double_t       dp = hist.hist_mc_photon_sum[histindex]->GetBinError(index + 1) ;
    Double_t       dl = hist.hist_mc_rad_sum[histindex]->GetBinError(index + 1);
    Double_t        d = hist.hist_data_sum[histindex]->GetBinContent(index + 1);
    Double_t        q = hist.hist_mc_sum[histindex]->GetBinContent(index + 1) ;
    Double_t       dq = hist.hist_mc_sum[histindex]->GetBinError(index + 1) ;
    
    Double_t QQtot = d - b*(1 - a) - l,
            QQtot_err = TMath::Sqrt(b*b*da*da + pow(-1 + a,2)*db*db + dd*dd + dl*dl);
    //Double_t g = QQtot / d;
    //Double_t dg = g * TMath::Sqrt(pow(dd/d,2)+pow(QQtot_err/QQtot,2));
    Double_t g = (l*a*b_scale - 1)/q + a*b_scale,
            dg =  TMath::Sqrt((a*2* dl*dl* b_scale*b_scale)/pow(q,2) + (pow(dq,2) * pow(-1 + a*l*b_scale,2))/pow(q,4) + da*da* pow(b_scale + (l* b_scale)/q,2));
    g = g / d_scale;
    dg = dg / d_scale;
    
    param[index] = g;
    param_err[index] = dg;  */ 
}
//ssssssssssss
void DoReparametrisationQQfit(Int_t histindex, Double_t* param, Double_t* param_err, Int_t index)
{
    Double_t a = param[index], da = param_err[index];

    Double_t        q = hist.hist_mc_sum[histindex]->GetBinContent(index + 1) ;
    Double_t       dq = hist.hist_mc_sum[histindex]->GetBinError(index + 1) ;
    Double_t       dd = hist.hist_data_sum[histindex]->GetBinError(index + 1);
    Double_t        d = hist.hist_data_sum[histindex]->GetBinContent(index + 1);
    /*Double_t d = hist_data[0]->GetSum(), b = hist_mc_norad[0]->GetSum(), p = phist_mc_photon[0]->GetSum(), l = hist_mc_rad[0]->GetSum(),
            dd = GetSumError(hist_data[0]), bb = GetSumError(hist_mc_norad[0]), dp = GetSumError(phist_mc_photon[0]), dl = GetSumError(hist_mc_rad[0]);
            //Or simply sqrt(content) or sqrt(sum of w2)?
            */
            //Double_t Dq = a/d, Da = q/d, Dd = -((a q)/d/d)
    Double_t g = (q*a)/d,
            dg = TMath::Sqrt((d*d* da*da* q*q + a*a* (d*d *dq*dq + dd*dd* q*q))/pow(d,4));

             if (nodebugmode) cout << "===> " << param[index] << " ===> " << g <<endl;
    if (nodebugmode) cout << "===> " << param_err[index] << " ===> " << dg <<endl;
    param[index] = g;
    param_err[index] = dg;   
}

void DoComplicatedScale(TH1D* h, Double_t a, Double_t a_err)
{
        h->Scale(a);// Scaled THE VALUE of QQ
        for(Int_t j = 0; j < h->GetNbinsX(); j++)
        {
            Double_t err = h->GetBinError(j+1) / a;
            Double_t add_err1 = pow( (a_err * h->GetBinContent(j+1) / a), 2);
            Double_t add_err2 = pow(err * a, 2);
            h->SetBinError(j+1, TMath::Sqrt(add_err1 + add_err2));
        }
}
  
TH1D* hist_data[2];
TH1D* hist_mc[2];
TH1D* hist_mc_rad[2];
TH1D* hist_mc_norad[2];
TH1D* hist_mc_photon[2];

//TH1D* hist_res[2];
Int_t g_index_fmax = 1;
Int_t g_index_deltaz = 0;

void minuitFunction(int& nDim, double* gout, double& result, double par[], int flg);
//void minuitFunctionBarlowBeeston(int& nDim, double* gout, double& result, double par[], int flg);
//void minuitFunctionGauss(int& nDim, double* gout, double& result, double par[], int flg);
Double_t chi2(double* par, Int_t& ndf, Int_t& left, Int_t& right, TString s_method);
  


int main(int argc, char *argv[])
{

    if((argc >= 2)) 
    {
        hist.correctiontype.Form((TString)argv[1]);//systJetE+ systJetE- systPhE+ systPhE- systElE+ systElE- systAcc
        if((argc == 2) && (TString)argv[1] != "fit+" && (TString)argv[1] != "fit-") hist.str_selectedoutput.Form("output_selected_" + (TString)argv[1] + ".txt");//Stream class to write on files
        if((argc == 2) && (TString)argv[1] != "fit+" && (TString)argv[1] != "fit-") hist.selectedoutput.open( hist.str_selectedoutput);
        dout("GO!", (TString)argv[1]);
        if ((TString)argv[1] == "fit+")
        {
            hist.str_selectedoutput.Form("output_selected_zero" + (TString)argv[1] + ".txt");//Stream class to write on files
            hist.selectedoutput.open( hist.str_selectedoutput);
            hist.correctiontype.Form("zero");
            hist.sys_fit = 1.0;
            sys_fit = 1.0;
            dout("herw", (TString)argv[2], hist.sys_fit);
        }
        else if ((TString)argv[1] == "fit-")
        {
            hist.str_selectedoutput.Form("output_selected_zero" + (TString)argv[1] + ".txt");//Stream class to write on files
            hist.selectedoutput.open( hist.str_selectedoutput);
            hist.correctiontype.Form("zero");
            sys_fit = 0.6;
            hist.sys_fit = 0.6;       
        }
        /*if((argc >= 3))// to calc the acc and fit syst you need two param: zero + acc+-/fit+-
        {
            hist.str_selectedoutput.Form("output_selected_" + (TString)argv[1] + (TString)argv[2] + ".txt");//Stream class to write on files
            hist.selectedoutput.open( hist.str_selectedoutput);
            if ((TString)argv[2] == "fit+")
                {
                hist.sys_fit = 1.0;
                sys_fit = 1.0;
                dout("herw", (TString)argv[2], hist.sys_fit);
                }
            else if ((TString)argv[2] == "fit-")
                {
                    sys_fit = 0.6;
                    hist.sys_fit = 0.6;       
                }
        };*/
    }
    else if ((argc == 1)) 
    {
        hist.correctiontype.Form("zero");//systJetE+ systJetE- systPhE+ systPhE- systElE+ systElE-
        hist.str_selectedoutput.Form("output_selected_zero.txt");//Stream class to write on files
        hist.selectedoutput.open( hist.str_selectedoutput);
    }
    dout("hist.Init");
    hist.Init();

    dout("end hist.Init");
    gROOT->SetStyle("Plain");
    gStyle->SetTitleBorderSize(0);
    gStyle->SetTitleH(0.08);
    gStyle->SetTitleFont(42);
    gStyle->SetTitleY(0.99);
    gStyle->SetTitleX(0.15);
    gStyle->SetEndErrorSize(5);

    
    //plot acceptance
    hist.PlotAcceptance();
    hist.PlotPurity();


    TFitter* minimizer = new TFitter(1);
    minimizer->SetFCN(minuitFunction);
    {//http://superk.physics.sunysb.edu/~mcgrew/phy310/lectures/phy310-lecture-11-2007.pdf
        double p1 = -1;
        /*
         * -1    : No output except from SHOW commands
         * 0   : Minimum output (no starting values or intermediate results)
         * 1   : Default value, normal output
         * 2   : Additional output giving intermediate results.
         * 3   : Maximum output, showing progress of minimizations.
         */
        minimizer->ExecuteCommand("SET PRINTOUT", &p1, 1);
    }


    /////////////////////////////////////////////////////
    //
    //          Fit in bins of et
    //
    ///////////////////////////////////////////////////////
    ofstream data_file("data.dat");
    ofstream llqq_file("llqq.dat");
    ofstream hadronic_file("hadronic.dat");
        
    for(Int_t i = 0; i < number_etbins; i++)// процедура фитирования выполняется на каждый бин по Et
    {      
        hist_data[0] = (TH1D*)hist.h_deltaz_et_data_sum[i]->Clone(); 
        hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_et_prph_sum[i]->Clone();
        hist_mc[0]->SetName("prph");
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_et_rad_sum[i]->Clone(); 
        hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_et_norad_sum[i]->Clone(); 
        hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); 
        hist_mc_photon[0]->SetName("photon");

        hist_mc[0]->Scale(hist.total_luminosity_data / hist.lumi_mc_prph);
        hist_mc_photon[0]->Add(hist_mc[0]);//LL + QQ.scale(data)

        Double_t n_mc_photon, n_mc_photon_err, n_data, n_data_err;

        calc_integral_err(hist_mc_photon[0], n_mc_photon, n_mc_photon_err);
        scale_hist_to_hist_with_err(hist_mc_photon[0], hist_data[0]);//QQ+LL->data
        scale_hist_to_hist_with_err(hist_mc_norad[0], hist_data[0]);//

        //      hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/n_mc_photon);

        hist_mc[0]->Scale(hist_data[0]->GetSum()/n_mc_photon);
        hist_mc_rad[0]->Scale(hist_data[0]->GetSum()/n_mc_photon);
        //hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());
        if(i == 0)
            for(Int_t j = 0; j <hist_mc[0]->GetNbinsX(); j++) 
            {
                data_file << hist_data[0]->GetBinContent(j+1) << " " << hist_data[0]->GetBinError(j+1) << endl;
                llqq_file << hist_mc_photon[0]->GetBinContent(j+1) << " " << hist_mc_photon[0]->GetBinError(j+1) << endl;
                hadronic_file << hist_mc_norad[0]->GetBinContent(j+1) << " " << hist_mc_norad[0]->GetBinError(j+1) << endl;
            }

        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD", 0, 0);
        minimizer->ExecuteCommand("HESSE", 0, 0);
        minimizer->ExecuteCommand("MINOS", 0, 0);    
        param_et[i] = minimizer->GetParameter(0); //процедура минимизации
        param_err_et[i] = minimizer->GetParError(0);
        Double_t par[1]; par[0] = param_et[i];
        chi2_et[i] = chi2(par, dof_et[i], left_et[i], right_et[i], chi_method) / 
                    dof_et[i];// достаем хи-квадрат dof = degries of freedom
        
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        /*if (nodebugmode) cout<<"Fit in bins of et: from bin "<< GetFitRange(hist_data[0], true)<<
                " to " << GetFitRange(hist_data[0], false)<<endl;       */
        
        //for(Int_t bin = hist_data[0]->FindBin(0.) - 1; bin < hist_data[0]->FindBin(0.6) + 4 - hist_data[0]->FindBin(0.) + 1; bin++) //? 02/07/15
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++) //? 02/07/15
        {
            //if (nodebugmode) cout<<"bin: "<<bin<<endl;
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);
            
            /*
             * TMath::Power(v_d - par[0] * v_ph - (1 - par[0]) * v_bg, 2)
             */
            Double_t chi2_bin = (v_d - par[0] * v_ph - (1 - par[0]) * v_bg) \
                              * (v_d - par[0] * v_ph - (1 - par[0]) * v_bg)\
                    / (s_d * s_d + par[0] * par[0] * s_ph * s_ph + (1. - par[0]) * (1. - par[0]) * s_bg * s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_et[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; sc.Form("chi2_et_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_et[i]->Draw("HIST TEXT");//https://root.cern.ch/root/html/THistPainter.html
        c->Print(sc + ".eps");
        delete c;
        //if (nodebugmode) cout << "total chi2 = " << total_chi2 << endl;
        //if (nodebugmode) cout << "... per dof = " << total_chi2 / Double_t(dof-2) << endl;
        // ----------- end chi2 per bin
        
        //leftet[i]++; //? зачем
        hist.h_deltaz_et_norad_sum[i]->Scale(0.);
        hist.h_deltaz_et_norad_sum[i]->Add(hist_mc_norad[0], 1-param_et[i]);
        hist.h_deltaz_et_photon_sum[i] = (TH1D*)hist.h_deltaz_et_prph_sum[i]->Clone(); 
        hist.h_deltaz_et_photon_sum[i]->SetName((TString)hist.h_deltaz_et_prph_sum[i]->GetName()+"photon");
        hist.h_deltaz_et_photon_sum[i]->Scale(0.);
        hist.h_deltaz_et_photon_sum[i]->Add(hist_mc_photon[0], param_et[i]);
        hist.h_deltaz_et_rad_sum[i]->Scale(0.);
        hist.h_deltaz_et_rad_sum[i]->Add(hist_mc_rad[0], param_et[i]);
        hist.h_deltaz_et_prph_sum[i]->Scale(0.);
        hist.h_deltaz_et_prph_sum[i]->Add(hist_mc[0], param_et[i]);
        hist.h_deltaz_et_res[i]->Scale(0.);//Add(hist.h_deltaz_et_norad_sum[i]);
        hist.h_deltaz_et_res[i]->Add(hist_mc_photon[0], param_et[i]);
        hist.h_deltaz_et_res[i]->Add(hist_mc_norad[0], 1-param_et[i]);
        /*if (nodebugmode) cout << "After fit in Et bins: n_data = " << hist_data[0]->GetSum()  
        << ", n_photon = " << hist_mc_photon[0]->GetSum() * param_et[i]  //gammagamma
        << ", n_bg = " << hist_mc_norad[0]->GetSum() * (1-param_et[i]) 
        << ", h.n_bg = " << hist.h_deltaz_et_norad_sum[i]->GetSum() 
        << ", h.n_rad = " << hist.h_deltaz_et_rad_sum[i]->GetSum() 
        << ", h.n_prph = " << hist.h_deltaz_et_prph_sum[i]->GetSum() 
        << ", n_res = " << hist.h_deltaz_et_res[i]->GetSum() << endl;
        if (nodebugmode) cout << "par in bin et " << i << ": " << param_et[i] << " +- " << param_err_et[i] << ", chi2/dof = " << chi2_et[i]  << endl;*/

    }
    data_file.close();
    llqq_file.close();
    hadronic_file.close();
        
    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of eta
    //
    ///////////////////////////////////////////////////////
    for(Int_t i=0; i<number_etabins; i++)
    {      
        hist_data[0] = (TH1D*)hist.h_deltaz_eta_data_sum[i]->Clone(); 
        hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_eta_prph_sum[i]->Clone(); 
        hist_mc[0]->SetName("prph");
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_eta_rad_sum[i]->Clone(); 
        hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_eta_norad_sum[i]->Clone(); 
        hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); 
        hist_mc_photon[0]->SetName("photon");// LL
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);//LL + QQ.Scale(total_luminosity_data/lumi_mc_prph)
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());//Photon = [LL + QQ.Scale()].scale(DATA/Photon)

        hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
        //hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
        hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
        
        //for the CS further calc...
        hist.h_deltaz_eta_prph_sum[i]->Scale((hist.h_deltaz_eta_data_sum[i]->GetSum() - hist.h_deltaz_eta_rad_sum[i]->GetSum()) / hist.h_deltaz_eta_prph_sum[i]->GetSum());
        hist.h_deltaz_eta_norad_sum[i]->Scale((hist.h_deltaz_eta_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_eta_rad_sum[i]->GetSum()) / hist.h_deltaz_eta_norad_sum[i]->GetSum());
        
        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);   
        param_eta[i] = minimizer->GetParameter(0);
        param_err_eta[i] = minimizer->GetParError(0);
        Double_t par[1]; par[0] = param_eta[i];
        chi2_eta[i] = chi2(par, dof_eta[i], left_eta[i], right_eta[i], chi_method) / dof_eta[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_eta[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; 
        sc.Form("chi2_eta_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_eta[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;
        //if (nodebugmode) cout << "total chi2 = " << total_chi2 << endl;
        //if (nodebugmode) cout << "... per dof = " << total_chi2 / Double_t(dof-2) << endl;
        // ----------- end chi2 per bin
        
        //lefteta[i]++;
        //hist.h_deltaz_eta_norad_sum[i]->Scale(1-param_eta[i]);
        //hist.h_deltaz_eta_prph_sum[i]->Scale(param_eta[i]);


        DoComplicatedScale(hist.h_deltaz_eta_norad_sum[i], 1 - param_deta[i], param_err_deta[i]);
        DoComplicatedScale(hist.h_deltaz_eta_prph_sum[i], param_deta[i], param_err_deta[i]);
        hist.h_deltaz_eta_res[i]->Add(hist.h_deltaz_eta_norad_sum[i]);
        hist.h_deltaz_eta_res[i]->Add(hist.h_deltaz_eta_prph_sum[i]);
        //if (nodebugmode) cout << "par in bin eta " << i << ": " << param_eta[i] << " +- " << param_err_eta[i] << ", chi2/dof = " << chi2_eta[i]  << endl;
    }

    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of q2
    //
    ///////////////////////////////////////////////////////
    for(Int_t i=0; i<number_Q2bins; i++)
    {      
        hist_data[0] = (TH1D*)hist.h_deltaz_q2_data_sum[i]->Clone(); hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_q2_prph_sum[i]->Clone(); hist_mc[0]->SetName("prph");
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_q2_rad_sum[i]->Clone(); hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_q2_norad_sum[i]->Clone(); hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); hist_mc_photon[0]->SetName("photon");
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

        hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum());
        //      hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
        hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());

        hist.h_deltaz_q2_prph_sum[i]->Scale((hist.h_deltaz_q2_data_sum[i]->GetSum() - hist.h_deltaz_q2_rad_sum[i]->GetSum()) / hist.h_deltaz_q2_prph_sum[i]->GetSum());
        hist.h_deltaz_q2_norad_sum[i]->Scale((hist.h_deltaz_q2_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_q2_rad_sum[i]->GetSum()) / hist.h_deltaz_q2_norad_sum[i]->GetSum());
        
        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);    
        param_q2[i] = minimizer->GetParameter(0);
        param_err_q2[i] = minimizer->GetParError(0);
        Double_t par[1]; par[0] = param_q2[i];
        chi2_q2[i] = chi2(par, dof_q2[i], left_q2[i], right_q2[i], chi_method) / dof_q2[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_Q2[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; sc.Form("chi2_q2_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_Q2[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;
        //if (nodebugmode) cout << "total chi2 = " << total_chi2 << endl;
        //if (nodebugmode) cout << "... per dof = " << total_chi2 / Double_t(dof-2) << endl;
        // ----------- end chi2 per bin
        //leftq2[i]++;
        //hist.h_deltaz_q2_norad_sum[i]->Scale(1-param_q2[i]);
        //hist.h_deltaz_q2_prph_sum[i]->Scale(param_q2[i]);
        DoComplicatedScale(hist.h_deltaz_q2_norad_sum[i], 1 - param_q2[i], param_q2[i]);
        DoComplicatedScale(hist.h_deltaz_q2_prph_sum[i], param_q2[i], param_q2[i]);
        hist.h_deltaz_q2_res[i]->Add(hist.h_deltaz_q2_norad_sum[i]);
        hist.h_deltaz_q2_res[i]->Add(hist.h_deltaz_q2_prph_sum[i]);
        //if (nodebugmode) cout << "par in bin q2 " << i << ": " << param_q2[i] << " +- " << param_err_q2[i] << ", chi2/dof = " << chi2_q2[i] << endl;
    }

    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of x
    //
    ///////////////////////////////////////////////////////
    for(Int_t i=0; i<number_xbins; i++)
    {      
        hist_data[0] = (TH1D*)hist.h_deltaz_x_data_sum[i]->Clone(); hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_x_prph_sum[i]->Clone(); hist_mc[0]->SetName("prph");
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_x_rad_sum[i]->Clone(); hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_x_norad_sum[i]->Clone(); hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); hist_mc_photon[0]->SetName("photon");
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

        hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum());
        //      hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
        hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());

        hist.h_deltaz_x_prph_sum[i]->Scale((hist.h_deltaz_x_data_sum[i]->GetSum() - hist.h_deltaz_x_rad_sum[i]->GetSum())/hist.h_deltaz_x_prph_sum[i]->GetSum());
        hist.h_deltaz_x_norad_sum[i]->Scale((hist.h_deltaz_x_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_x_rad_sum[i]->GetSum()) / hist.h_deltaz_x_norad_sum[i]->GetSum());
        
        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);    
        param_x[i] = minimizer->GetParameter(0);
        param_err_x[i] = minimizer->GetParError(0);
        Double_t par[1]; par[0] = param_x[i];
        chi2_x[i] = chi2(par, dof_x[i], left_x[i], right_x[i], chi_method) / dof_x[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_x[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; sc.Form("chi2_x_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_x[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;
        //if (nodebugmode) cout << "total chi2 = " << total_chi2 << endl;
        //if (nodebugmode) cout << "... per dof = " << total_chi2 / Double_t(dof-2) << endl;
        // ----------- end chi2 per bin
        
        //leftx[i]++;
        //hist.h_deltaz_x_norad_sum[i]->Scale(1-param_x[i]);
        //hist.h_deltaz_x_prph_sum[i]->Scale(param_x[i]);
        DoComplicatedScale(hist.h_deltaz_x_norad_sum[i], 1 - param_x[i], param_err_x[i]);
        DoComplicatedScale(hist.h_deltaz_x_prph_sum[i], param_x[i], param_err_x[i]);
        hist.h_deltaz_x_res[i]->Add(hist.h_deltaz_x_norad_sum[i]);
        hist.h_deltaz_x_res[i]->Add(hist.h_deltaz_x_prph_sum[i]);
        //if (nodebugmode) cout << "par in bin x " << i << ": " << param_x[i] << " +- " << param_err_x[i] << ", chi2/dof = " << chi2_x[i]  << endl;
    }

    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of et_jet
    //
    ///////////////////////////////////////////////////////
    for(Int_t i=0; i<number_et_jetbins; i++)
    {     
        hist_data[0] = (TH1D*)hist.h_deltaz_et_jet_data_sum[i]->Clone(); hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_et_jet_prph_sum[i]->Clone(); hist_mc[0]->SetName("prph");
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_et_jet_rad_sum[i]->Clone(); hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_et_jet_norad_sum[i]->Clone(); hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); hist_mc_photon[0]->SetName("photon");
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

        hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum());
        //      hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
        hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());
        
        hist.h_deltaz_et_jet_prph_sum[i]->Scale((hist.h_deltaz_et_jet_data_sum[i]->GetSum() - hist.h_deltaz_et_jet_rad_sum[i]->GetSum()) / hist.h_deltaz_et_jet_prph_sum[i]->GetSum());
        hist.h_deltaz_et_jet_norad_sum[i]->Scale((hist.h_deltaz_et_jet_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_et_jet_rad_sum[i]->GetSum()) / hist.h_deltaz_et_jet_norad_sum[i]->GetSum());
        
        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);   
        param_et_jet[i] = minimizer->GetParameter(0);
        param_err_et_jet[i] = minimizer->GetParError(0);
        Double_t par[1]; par[0] = param_et_jet[i];
        chi2_et_jet[i] = chi2(par, dof_et_jet[i], left_et_jet[i], right_et_jet[i], chi_method) / dof_et_jet[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_et_jet[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; sc.Form("chi2_et_jet_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_et_jet[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;
        //if (nodebugmode) cout << "total chi2 = " << total_chi2 << endl;
        //if (nodebugmode) cout << "... per dof = " << total_chi2 / Double_t(dof-2) << endl;
        // ----------- end chi2 per bin
        
        //leftet_jet[i]++;
        //hist.h_deltaz_et_jet_norad_sum[i]->Scale(1-param_et_jet[i]);
        //hist.h_deltaz_et_jet_prph_sum[i]->Scale(param_et_jet[i]);
        DoComplicatedScale(hist.h_deltaz_et_jet_norad_sum[i], 1 - param_et_jet[i], param_err_et_jet[i]);
        DoComplicatedScale(hist.h_deltaz_et_jet_prph_sum[i], param_et_jet[i], param_err_et_jet[i]);
        hist.h_deltaz_et_jet_res[i]->Add(hist.h_deltaz_et_jet_norad_sum[i]);
        hist.h_deltaz_et_jet_res[i]->Add(hist.h_deltaz_et_jet_prph_sum[i]);
        //if (nodebugmode) cout << "par in bin et_jet " << i << ": " << param_et_jet[i] << " +- " << param_err_et_jet[i] << ", chi2/dof = " << chi2_et_jet[i]  << endl;
    }

    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of eta_jet
    //
    ///////////////////////////////////////////////////////
    for(Int_t i=0; i<number_eta_jetbins; i++)
    {      
        hist_data[0] = (TH1D*)hist.h_deltaz_eta_jet_data_sum[i]->Clone(); hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_eta_jet_prph_sum[i]->Clone(); hist_mc[0]->SetName("prph");
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_eta_jet_rad_sum[i]->Clone(); hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_eta_jet_norad_sum[i]->Clone(); hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); hist_mc_photon[0]->SetName("photon");
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

        hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum());
        //      hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
        hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());
        
        hist.h_deltaz_eta_jet_prph_sum[i]->Scale((hist.h_deltaz_eta_jet_data_sum[i]->GetSum() - hist.h_deltaz_eta_jet_rad_sum[i]->GetSum()) / hist.h_deltaz_eta_jet_prph_sum[i]->GetSum());
        hist.h_deltaz_eta_jet_norad_sum[i]->Scale((hist.h_deltaz_eta_jet_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_eta_jet_rad_sum[i]->GetSum()) / hist.h_deltaz_eta_jet_norad_sum[i]->GetSum());
        
        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);   
        param_eta_jet[i] = minimizer->GetParameter(0);
        param_err_eta_jet[i] = minimizer->GetParError(0);
        Double_t par[1]; par[0] = param_eta_jet[i];
        chi2_eta_jet[i] = chi2(par, dof_eta_jet[i], left_eta_jet[i], right_eta_jet[i], chi_method) / dof_eta_jet[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_eta_jet[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; sc.Form("chi2_eta_jet_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_eta_jet[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;
        //if (nodebugmode) cout << "total chi2 = " << total_chi2 << endl;
        //if (nodebugmode) cout << "... per dof = " << total_chi2 / Double_t(dof-2) << endl;
        // ----------- end chi2 per bin
        
        //lefteta_jet[i]++;
        //hist.h_deltaz_eta_jet_norad_sum[i]->Scale(1-param_eta_jet[i]);
        //hist.h_deltaz_eta_jet_prph_sum[i]->Scale(param_eta_jet[i]);
        DoComplicatedScale(hist.h_deltaz_eta_jet_norad_sum[i], 1 - param_eta_jet[i], param_err_eta_jet[i]);
        DoComplicatedScale(hist.h_deltaz_eta_jet_prph_sum[i], param_eta_jet[i], param_err_eta_jet[i]);
        hist.h_deltaz_eta_jet_res[i]->Add(hist.h_deltaz_eta_jet_norad_sum[i]);
        hist.h_deltaz_eta_jet_res[i]->Add(hist.h_deltaz_eta_jet_prph_sum[i]);
        //if (nodebugmode) cout << "par in bin eta_jet " << i << ": " << param_eta_jet[i] << " +- " << param_err_eta_jet[i] << ", chi2/dof = " << chi2_eta_jet[i]  << endl;
    }

    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of xgamma
    //
    ///////////////////////////////////////////////////////
    for(Int_t i=0; i < number_xgamma_bins; i++)
    {     
        hist_data[0] = (TH1D*)hist.h_deltaz_xgamma_data_sum[i]->Clone(); 
        hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_xgamma_prph_sum[i]->Clone(); 
        hist_mc[0]->SetName("prph");//QQ
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_xgamma_rad_sum[i]->Clone(); 
        hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_xgamma_norad_sum[i]->Clone(); 
        hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); 
        hist_mc_photon[0]->SetName("photon");
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);//LL + QQ'
        b_scale = hist_data[0]->GetSum() / hist_mc_photon[0]->GetSum();
        d_scale = (hist_data[0]->GetSum() )/hist_mc[0]->GetSum();
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());
        if (i+1 == number_xgamma_bins )
            if (nodebugmode) cout <<"qq: " << hist_mc[0]->GetEntries() << " or " << hist_mc[0]->Integral(1, hist_mc[0]->GetNbinsX()) << endl;

            hist_mc[0]->Scale((hist_data[0]->GetSum() )/hist_mc[0]->GetSum());
            hist.h_deltaz_xgamma_prph_sum[i]->Scale((hist.h_deltaz_xgamma_data_sum[i]->GetSum() ) / hist.h_deltaz_xgamma_prph_sum[i]->GetSum());

        hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());
        hist.h_deltaz_xgamma_norad_sum[i]->Scale((hist.h_deltaz_xgamma_data_sum[i]->GetSum()) / hist.h_deltaz_xgamma_norad_sum[i]->GetSum());
        
        //if (i+1 == number_xgamma_bins )
        //    if (nodebugmode) cout <<"qq': " << hist_mc[0]->GetEntries() << " or " << hist_mc[0]->Integral(1, hist_mc[0]->GetNbinsX()) << endl;

        
        //hist.h_deltaz_xgamma_prph_sum[i]->Scale((hist.h_deltaz_xgamma_data_sum[i]->GetSum() - hist.h_deltaz_xgamma_rad_sum[i]->GetSum()) / hist.h_deltaz_xgamma_prph_sum[i]->GetSum());
        //hist.h_deltaz_xgamma_norad_sum[i]->Scale((hist.h_deltaz_xgamma_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_xgamma_rad_sum[i]->GetSum()) / hist.h_deltaz_xgamma_norad_sum[i]->GetSum());

        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);   
        param_xgamma[i] = minimizer->GetParameter(0);
        param_err_xgamma[i] = minimizer->GetParError(0);
        Double_t par[1]; 
        par[0] = param_xgamma[i];
        chi2_xgamma[i] = chi2(par, dof_xgamma[i], left_xgamma[i], right_xgamma[i], chi_method) / dof_xgamma[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_xgamma[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; sc.Form("chi2_xgamma_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_xgamma[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;
        //if (nodebugmode) cout << "total chi2 = " << total_chi2 << endl;
        //if (nodebugmode) cout << "... per dof = " << total_chi2 / Double_t(dof-2) << endl;
        // ----------- end chi2 per bin
        
        //leftxgamma[i]++;
        //hist.h_deltaz_xgamma_norad_sum[i]->Scale(1-param_xgamma[i]);
        //hist.h_deltaz_xgamma_prph_sum[i]->Scale(param_xgamma[i]);
        param_xgamma_PhotonsFit[i] = param_xgamma[i];
        param_err_xgamma_PhotonsFit[i] = param_err_xgamma[i];
        if (!nodebugmode) cout<< "param xgamma after fit " << i << ") " << param_xgamma[i] <<"+/-"<< param_err_xgamma[i]<< endl;
        if (QQfit == 0)
        {
            DoReparametrisation(1, param_xgamma, param_err_xgamma, i);
        }
        if (!nodebugmode) cout<< "param xgamma after reparam " << i << ") " << param_xgamma[i] <<"+/-"<< param_err_xgamma[i]<< endl;
        DoComplicatedScale(hist.h_deltaz_xgamma_norad_sum[i], 1 - param_xgamma_PhotonsFit[i], param_err_xgamma_PhotonsFit[i]);
        DoComplicatedScale(hist.h_deltaz_xgamma_prph_sum[i], param_xgamma[i], param_err_xgamma[i]);
        hist.h_deltaz_xgamma_res[i]->Add(hist.h_deltaz_xgamma_norad_sum[i]);// LL + bg'
        hist.h_deltaz_xgamma_res[i]->Add(hist.h_deltaz_xgamma_prph_sum[i]);//LL +  QQ' + bg'
        //if (nodebugmode) cout << "par in bin xgamma " << i << ": " << param_xgamma[i] << " +- " << param_err_xgamma[i] << ", chi2/dof = " << chi2_xgamma[i]  << endl;
        /*if (i+1 == number_xgamma_bins )
        {
            if (nodebugmode) cout << "Problem bin" << endl;
            if (nodebugmode) cout << "   param: " <<  param_xgamma[i] <<" +/- " << param_err_xgamma[i] << endl;
            if (nodebugmode) cout << "   data: " << hist_data[0]->Integral(1, hist_data[0]->GetNbinsX())<<endl;
            if (nodebugmode) cout << "   res: " << hist.h_deltaz_xgamma_res[i]->Integral(1, hist.h_deltaz_xgamma_res[i]->GetNbinsX())<<endl;
            if (nodebugmode) cout << "       res': " << hist_mc[0]->Integral(1, hist_mc[0]->GetNbinsX()) * param_xgamma[i]  + \
            hist_mc_norad[0]->Integral(1, hist_mc_norad[0]->GetNbinsX()) * (1 - param_xgamma[i]) + \
            hist_mc_rad[0]->Integral(1, hist_mc_rad[0]->GetNbinsX())<< endl;
            if (nodebugmode) cout << "   QQ': " << hist_mc[0]->Integral(1, hist_mc[0]->GetNbinsX()) * param_xgamma[i] <<endl;
                if (nodebugmode) cout << "   hist.QQ[i]: " << hist.h_deltaz_xgamma_prph_sum[i]->GetEntries() << endl;
            if (nodebugmode) cout << "   LL: " << hist_mc_rad[0]->Integral(1, hist_mc_rad[0]->GetNbinsX())<<endl;
            if (nodebugmode) cout << "   bg': " << hist_mc_norad[0]->Integral(1, hist_mc_norad[0]->GetNbinsX()) * (1 - param_xgamma[i]) <<endl;
                if (nodebugmode) cout << "   hist.bg[i]: " << hist.h_deltaz_xgamma_norad_sum[i]->Integral(1, hist.h_deltaz_xgamma_norad_sum[i]->GetNbinsX())<< endl;
            if (nodebugmode) cout << "   photons: " << hist_mc_photon[0]->Integral(1, hist_mc_photon[0]->GetNbinsX())<<endl;
         
        }*/
    }

    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of xp
    //
    ///////////////////////////////////////////////////////
    for(Int_t i=0; i<number_xp_bins; i++)
    {     
        hist_data[0] = (TH1D*)hist.h_deltaz_xp_data_sum[i]->Clone(); hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_xp_prph_sum[i]->Clone(); 
        hist_mc[0]->SetName("prph");
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_xp_rad_sum[i]->Clone(); 
        hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_xp_norad_sum[i]->Clone(); 
        hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); 
        hist_mc_photon[0]->SetName("photon");
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

        if (QQfit == 0)
        hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum());
        else
        hist_mc[0]->Scale((hist_data[0]->GetSum() )/hist_mc[0]->GetSum());
        //      hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
        hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());
        if (QQfit == 0)
            hist.h_deltaz_xp_prph_sum[i]->Scale((hist.h_deltaz_xp_data_sum[i]->GetSum() - hist.h_deltaz_xp_rad_sum[i]->GetSum()) / hist.h_deltaz_xp_prph_sum[i]->GetSum());
        else
            hist.h_deltaz_xp_prph_sum[i]->Scale((hist.h_deltaz_xp_data_sum[i]->GetSum() ) / hist.h_deltaz_xp_prph_sum[i]->GetSum());
        hist.h_deltaz_xp_norad_sum[i]->Scale((hist.h_deltaz_xp_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_xp_rad_sum[i]->GetSum()) / hist.h_deltaz_xp_norad_sum[i]->GetSum());
        
        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);   
        param_xp[i] = minimizer->GetParameter(0);
        param_err_xp[i] = minimizer->GetParError(0);
        Double_t par[1]; par[0] = param_xp[i];
        chi2_xp[i] = chi2(par, dof_xp[i], left_xp[i], right_xp[i], chi_method) / dof_xp[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_xp[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; sc.Form("chi2_xp_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_xp[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;
        //if (nodebugmode) cout << "total chi2 = " << total_chi2 << endl;
        //if (nodebugmode) cout << "... per dof = " << total_chi2 / Double_t(dof-2) << endl;
        // ----------- end chi2 per bin
        
        //leftxp[i]++;
        //hist.h_deltaz_xp_norad_sum[i]->Scale(1-param_xp[i]);
        //hist.h_deltaz_xp_prph_sum[i]->Scale(param_xp[i]);

            param_xp_PhotonsFit[i] = param_xp[i];
            param_err_xp_PhotonsFit[i] = param_err_xp[i];
        if (QQfit == 0)
        {
            //std::copy(param_xp, param_xp + number_xp_bins, param_xp_PhotonsFit);
            //std::copy(param_err_xp, param_err_xp + number_xp_bins,  param_err_xp_PhotonsFit);
            DoReparametrisation(0, param_xp, param_err_xp, i);
        }
        else
            DoReparametrisationQQfit(0, param_xp, param_err_xp, i);
        DoComplicatedScale(hist.h_deltaz_xp_norad_sum[i], 1 - param_xp[i], param_err_xp[i]);
        DoComplicatedScale(hist.h_deltaz_xp_prph_sum[i], param_xp[i], param_err_xp[i]);
        hist.h_deltaz_xp_res[i]->Add(hist.h_deltaz_xp_norad_sum[i]);
        hist.h_deltaz_xp_res[i]->Add(hist.h_deltaz_xp_prph_sum[i]);
        //if (nodebugmode) cout << "par in bin xp " << i << ": " << param_xp[i] << " +- " << param_err_xp[i] << ", chi2/dof = " << chi2_xp[i]  << endl;
    }


    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of dphi
    //
    ///////////////////////////////////////////////////////
    for(Int_t i=0; i<number_dphi_bins; i++)
    {     
        hist_data[0] = (TH1D*)hist.h_deltaz_dphi_data_sum[i]->Clone(); 
        hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_dphi_prph_sum[i]->Clone(); 
        hist_mc[0]->SetName("prph");
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_dphi_rad_sum[i]->Clone(); 
        hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_dphi_norad_sum[i]->Clone(); 
        hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); 
        hist_mc_photon[0]->SetName("photon");
        
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

        
        //      hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
        hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());
        
        if (QQfit == 0)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum());
            hist.h_deltaz_dphi_prph_sum[i]->Scale((hist.h_deltaz_dphi_data_sum[i]->GetSum() - hist.h_deltaz_dphi_rad_sum[i]->GetSum()) / hist.h_deltaz_dphi_prph_sum[i]->GetSum());
        }
        else{
            hist.h_deltaz_dphi_prph_sum[i]->Scale((hist.h_deltaz_dphi_data_sum[i]->GetSum() ) / hist.h_deltaz_dphi_prph_sum[i]->GetSum());
        
            hist_mc[0]->Scale((hist_data[0]->GetSum() )/hist_mc[0]->GetSum());
        }
        hist.h_deltaz_dphi_norad_sum[i]->Scale((hist.h_deltaz_dphi_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_dphi_rad_sum[i]->GetSum()) / hist.h_deltaz_dphi_norad_sum[i]->GetSum());
        
        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);   
        param_dphi[i] = minimizer->GetParameter(0);
        param_err_dphi[i] = minimizer->GetParError(0);
        Double_t par[1]; par[0] = param_dphi[i];
        chi2_dphi[i] = chi2(par, dof_dphi[i], left_dphi[i], right_dphi[i], chi_method) / dof_dphi[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_dphi[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; sc.Form("chi2_dphi_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_dphi[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;
        //if (nodebugmode) cout << "total chi2 = " << total_chi2 << endl;
        //if (nodebugmode) cout << "... per dof = " << total_chi2 / Double_t(dof-2) << endl;
        // ----------- end chi2 per bin
            param_dphi_PhotonsFit[i] = param_dphi[i];
            param_err_dphi_PhotonsFit[i] = param_err_dphi[i];
        
        //leftdphi[i]++;
        if (QQfit == 0)
        {
            //std::copy(param_dphi, param_dphi + number_dphi_bins,  param_dphi_PhotonsFit);
            //std::copy(param_err_dphi, param_err_dphi + number_dphi_bins,  param_err_dphi_PhotonsFit);
            DoReparametrisation(3, param_dphi, param_err_dphi, i);
        }
        else
            DoReparametrisationQQfit(3, param_dphi, param_err_dphi, i);
        
        DoComplicatedScale(hist.h_deltaz_dphi_norad_sum[i], 1 - param_dphi[i], param_err_dphi[i]);
        DoComplicatedScale(hist.h_deltaz_dphi_prph_sum[i], param_dphi[i], param_err_dphi[i]);
        /*
        hist.h_deltaz_dphi_norad_sum[i]->Scale(1-param_dphi[i]);
        hist.h_deltaz_dphi_prph_sum[i]->Scale(param_dphi[i]);
        */
        hist.h_deltaz_dphi_res[i]->Add(hist.h_deltaz_dphi_norad_sum[i]);
        hist.h_deltaz_dphi_res[i]->Add(hist.h_deltaz_dphi_prph_sum[i]);
        //if (nodebugmode) cout << "par in bin dphi " << i << ": " << param_dphi[i] << " +- " << param_err_dphi[i] << ", chi2/dof = " << chi2_dphi[i]  << endl;
    }
     std::copy(param_dphi, param_dphi + number_dphi_bins,  hist.param_dphi);
     std::copy(param_err_dphi, param_err_dphi + number_dphi_bins,  hist.param_err_dphi);

    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of deta
    //
    ///////////////////////////////////////////////////////
    for(Int_t i=0; i<number_deta_bins; i++)
    {     
        hist_data[0] = (TH1D*)hist.h_deltaz_deta_data_sum[i]->Clone(); hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_deta_prph_sum[i]->Clone(); hist_mc[0]->SetName("prph");
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_deta_rad_sum[i]->Clone(); hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_deta_norad_sum[i]->Clone(); hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); hist_mc_photon[0]->SetName("photon");
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

        //      hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
        hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());
        
        if (QQfit == 0)
        {
            hist.h_deltaz_deta_prph_sum[i]->Scale((hist.h_deltaz_deta_data_sum[i]->GetSum() - hist.h_deltaz_deta_rad_sum[i]->GetSum()) / hist.h_deltaz_deta_prph_sum[i]->GetSum());
            hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum());
        }
        else
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() )/hist_mc[0]->GetSum());
            hist.h_deltaz_deta_prph_sum[i]->Scale((hist.h_deltaz_deta_data_sum[i]->GetSum() ) / hist.h_deltaz_deta_prph_sum[i]->GetSum());
        }
        hist.h_deltaz_deta_norad_sum[i]->Scale((hist.h_deltaz_deta_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_deta_rad_sum[i]->GetSum()) / hist.h_deltaz_deta_norad_sum[i]->GetSum());
        
        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);   
        param_deta[i] = minimizer->GetParameter(0);
        param_err_deta[i] = minimizer->GetParError(0);
        Double_t par[1]; par[0] = param_deta[i];
        chi2_deta[i] = chi2(par, dof_deta[i], left_deta[i], right_deta[i], chi_method) / dof_deta[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_deta[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; sc.Form("chi2_deta_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_deta[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;
        //if (nodebugmode) cout << "total chi2 = " << total_chi2 << endl;
        //if (nodebugmode) cout << "... per dof = " << total_chi2 / Double_t(dof-2) << endl;
        // ----------- end chi2 per bin
        
        //leftdeta[i]++;
        //hist.h_deltaz_deta_norad_sum[i]->Scale(1-param_deta[i]);
        //hist.h_deltaz_deta_prph_sum[i]->Scale(param_deta[i]);

            param_deta_PhotonsFit[i] = param_deta[i];
            param_err_deta_PhotonsFit[i] = param_err_deta[i];
        if (QQfit == 0)
        {

            //std::copy(param_deta, param_deta + number_deta_bins,  param_deta_PhotonsFit);
            //std::copy(param_err_deta, param_err_deta + number_deta_bins,  param_err_deta_PhotonsFit);
            DoReparametrisation(2, param_deta, param_err_deta, i);
        }
        else
            DoReparametrisationQQfit(2, param_deta, param_err_deta, i);
        DoComplicatedScale(hist.h_deltaz_deta_norad_sum[i], 1 - param_deta[i], param_err_deta[i]);
        DoComplicatedScale(hist.h_deltaz_deta_prph_sum[i], param_deta[i], param_err_deta[i]);
        hist.h_deltaz_deta_res[i]->Add(hist.h_deltaz_deta_norad_sum[i]);
        hist.h_deltaz_deta_res[i]->Add(hist.h_deltaz_deta_prph_sum[i]);
        //if (nodebugmode) cout << "par in bin deta " << i << ": " << param_deta[i] << " +- " << param_err_deta[i] << ", chi2/dof = " << chi2_deta[i]  << endl;
    }


    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of dphi_e_ph
    //
    ///////////////////////////////////////////////////////
    for(Int_t i=0; i<number_dphi_e_ph_bins; i++)
    {     
        hist_data[0] = (TH1D*)hist.h_deltaz_dphi_e_ph_data_sum[i]->Clone(); hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_dphi_e_ph_prph_sum[i]->Clone(); hist_mc[0]->SetName("prph");
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_dphi_e_ph_rad_sum[i]->Clone(); hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_dphi_e_ph_norad_sum[i]->Clone(); hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); hist_mc_photon[0]->SetName("photon");
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

        //      hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
        hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());
        

         if (QQfit == 0)
         {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum());
            hist.h_deltaz_dphi_e_ph_prph_sum[i]->Scale((hist.h_deltaz_dphi_e_ph_data_sum[i]->GetSum() - hist.h_deltaz_dphi_e_ph_rad_sum[i]->GetSum()) / hist.h_deltaz_dphi_e_ph_prph_sum[i]->GetSum());
         }
        else
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() )/hist_mc[0]->GetSum());
            hist.h_deltaz_dphi_e_ph_prph_sum[i]->Scale((hist.h_deltaz_dphi_e_ph_data_sum[i]->GetSum() ) / hist.h_deltaz_dphi_e_ph_prph_sum[i]->GetSum());
        }
        hist.h_deltaz_dphi_e_ph_norad_sum[i]->Scale((hist.h_deltaz_dphi_e_ph_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_dphi_e_ph_rad_sum[i]->GetSum()) / hist.h_deltaz_dphi_e_ph_norad_sum[i]->GetSum());
        
        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);   
        param_dphi_e_ph[i] = minimizer->GetParameter(0);
        param_err_dphi_e_ph[i] = minimizer->GetParError(0);
        Double_t par[1]; par[0] = param_dphi_e_ph[i];
        chi2_dphi_e_ph[i] = chi2(par, dof_dphi_e_ph[i], left_dphi_e_ph[i], right_dphi_e_ph[i], chi_method) / dof_dphi_e_ph[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_dphi_e_ph[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; sc.Form("chi2_dphi_e_ph_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_dphi_e_ph[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;
        //if (nodebugmode) cout << "total chi2 = " << total_chi2 << endl;
        //if (nodebugmode) cout << "... per dof = " << total_chi2 / Double_t(dof-2) << endl;
        // ----------- end chi2 per bin
        
        //leftdphi_e_ph[i]++;
        //hist.h_deltaz_dphi_e_ph_norad_sum[i]->Scale(1-param_dphi_e_ph[i]);
        //hist.h_deltaz_dphi_e_ph_prph_sum[i]->Scale(param_dphi_e_ph[i]);
            param_dphi_e_ph_PhotonsFit[i] = param_dphi_e_ph[i];
            param_err_dphi_e_ph_PhotonsFit[i] = param_err_dphi_e_ph[i];
        if (QQfit == 0)
        {
            //std::copy(param_dphi_e_ph, param_dphi_e_ph + number_dphi_e_ph_bins,  param_dphi_e_ph_PhotonsFit);
            //std::copy(param_err_dphi_e_ph, param_err_dphi_e_ph + number_dphi_e_ph_bins,  param_err_dphi_e_ph_PhotonsFit);
            DoReparametrisation(4, param_dphi_e_ph, param_err_dphi_e_ph, i);
        }
        else
            DoReparametrisationQQfit(4, param_dphi_e_ph, param_err_dphi_e_ph, i);
        DoComplicatedScale(hist.h_deltaz_dphi_e_ph_norad_sum[i], 1 - param_dphi_e_ph[i], param_err_dphi_e_ph[i]);
        DoComplicatedScale(hist.h_deltaz_dphi_e_ph_prph_sum[i], param_dphi_e_ph[i], param_err_dphi_e_ph[i]);
        hist.h_deltaz_dphi_e_ph_res[i]->Add(hist.h_deltaz_dphi_e_ph_norad_sum[i]);
        hist.h_deltaz_dphi_e_ph_res[i]->Add(hist.h_deltaz_dphi_e_ph_prph_sum[i]);
        //if (nodebugmode) cout << "par in bin dphi_e_ph " << i << ": " << param_dphi_e_ph[i] << " +- " << param_err_dphi_e_ph[i] << ", chi2/dof = " << chi2_dphi_e_ph[i]  << endl;
    }


    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of deta_e_ph
    //
    ///////////////////////////////////////////////////////
    for(Int_t i=0; i<number_deta_e_ph_bins; i++)
    {     
        hist_data[0] = (TH1D*)hist.h_deltaz_deta_e_ph_data_sum[i]->Clone(); hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_deta_e_ph_prph_sum[i]->Clone(); hist_mc[0]->SetName("prph");
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_deta_e_ph_rad_sum[i]->Clone(); hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_deta_e_ph_norad_sum[i]->Clone(); hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); hist_mc_photon[0]->SetName("photon");
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

        
        //      hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
        hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());
        
        if (QQfit == 0)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum());
            hist.h_deltaz_deta_e_ph_prph_sum[i]->Scale((hist.h_deltaz_deta_e_ph_data_sum[i]->GetSum() - hist.h_deltaz_deta_e_ph_rad_sum[i]->GetSum()) / hist.h_deltaz_deta_e_ph_prph_sum[i]->GetSum());
        }
        else
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() )/hist_mc[0]->GetSum());
            hist.h_deltaz_deta_e_ph_prph_sum[i]->Scale((hist.h_deltaz_deta_e_ph_data_sum[i]->GetSum() ) / hist.h_deltaz_deta_e_ph_prph_sum[i]->GetSum());
        }
        hist.h_deltaz_deta_e_ph_norad_sum[i]->Scale((hist.h_deltaz_deta_e_ph_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_deta_e_ph_rad_sum[i]->GetSum()) / hist.h_deltaz_deta_e_ph_norad_sum[i]->GetSum());//?
        
        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);   
        param_deta_e_ph[i] = minimizer->GetParameter(0);
        param_err_deta_e_ph[i] = minimizer->GetParError(0);
        Double_t par[1]; par[0] = param_deta_e_ph[i];
        chi2_deta_e_ph[i] = chi2(par, dof_deta_e_ph[i], left_deta_e_ph[i], right_deta_e_ph[i], chi_method) / dof_deta_e_ph[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            ///if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_deta_e_ph[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; sc.Form("chi2_deta_e_ph_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_deta_e_ph[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;
        ///if (nodebugmode) cout << "total chi2 = " << total_chi2 << endl;
        ///if (nodebugmode) cout << "... per dof = " << total_chi2 / Double_t(dof-2) << endl;
        // ----------- end chi2 per bin
        
        //left_deta_e_ph[i]++;
        //hist.h_deltaz_deta_e_ph_norad_sum[i]->Scale(1-param_deta_e_ph[i]);
        //hist.h_deltaz_deta_e_ph_prph_sum[i]->Scale(param_deta_e_ph[i]);
        if (nodebugmode) cout<< param_deta_e_ph[i]<<endl;        
        param_deta_e_ph_PhotonsFit[i] = param_deta_e_ph[i];
        param_err_deta_e_ph_PhotonsFit[i] = param_err_deta_e_ph[i];
        if (QQfit == 0)
        {
            //std::copy(param_deta_e_ph, param_deta_e_ph + number_deta_e_ph_bins,  param_deta_e_ph_PhotonsFit);
            //std::copy(param_err_deta_e_ph, param_err_deta_e_ph + number_deta_e_ph_bins,  param_err_deta_e_ph_PhotonsFit);
            DoReparametrisation(5, param_deta_e_ph, param_err_deta_e_ph, i);
        }
        else
            DoReparametrisationQQfit(5, param_deta_e_ph, param_err_deta_e_ph, i);
        DoComplicatedScale(hist.h_deltaz_deta_e_ph_norad_sum[i], 1 - param_deta_e_ph[i], param_err_deta_e_ph[i]);
        DoComplicatedScale(hist.h_deltaz_deta_e_ph_prph_sum[i], param_deta_e_ph[i], param_err_deta_e_ph[i]);
        hist.h_deltaz_deta_e_ph_res[i]->Add(hist.h_deltaz_deta_e_ph_norad_sum[i]);
        hist.h_deltaz_deta_e_ph_res[i]->Add(hist.h_deltaz_deta_e_ph_prph_sum[i]);
        ///if (nodebugmode) cout << "par in bin deta_e_ph " << i << ": " << param_deta_e_ph[i] << " +- " << param_err_deta_e_ph[i] << ", chi2/dof = " << chi2_deta_e_ph[i]  << endl;
    }
     if (nodebugmode) cout<<param_deta_e_ph[0]<<endl;
     std::copy(param_deta_e_ph, param_deta_e_ph + number_deta_e_ph_bins,  hist.param_deta_e_ph);
     std::copy(param_err_deta_e_ph, param_err_deta_e_ph + number_deta_e_ph_bins,  hist.param_err_deta_e_ph);
     //hist.param_deta_e_ph[0] = 0;
     //hist.param_err_deta_e_ph[0] = 0;

    hist.PlotFitInBinsOfCrossSec();
    hist.PlotCrossSec(); 
    ///if (nodebugmode) cout << "return to main" << endl;
    if (nodebugmode) cout << "Finish" << endl;
    f->Write();
    hist.selectedoutput.close();
    cerr << "Finish" << endl;
    return 0;
}


void minuitFunction(int& nDim, double* gout, double& result, double par[], int flg) 
{
    Int_t ndf, left, right;
    result = chi2(par, ndf, left, right, chi_method);
}

Double_t chi2(double* par, Int_t& ndf, Int_t& left, Int_t& right, TString s_method)
{
    Double_t res = 0.;
    ndf = 0;
    Int_t index;
    if(fit_method == "deltaz") 
    {
        index = g_index_deltaz;
        left = GetFitRange(hist_data[index], true);//hist_data[index]->FindBin(0.) - 1;
        right = GetFitRange(hist_data[index], false); // 5;//20;//hist_data[index]->FindBin(0.8);//18;//hist_data[index]->FindBin(0.8); //0.8 / 0.05
        //if (nodebugmode) cout<<"right "<<right<<" left "<< left<< endl; 
    }
    else
    if(fit_method == "fmax") 
    {
        index = g_index_fmax;
        left = 1;//0.2
        right = 20;//1.
    }
    else 
    {
        cerr << "wrong fit method: " << fit_method << endl;
        exit(-1);
    }

    for(Int_t i = left; i < right; i++)
    {
        Double_t diff;
        //Check the bins abd ranges
        //if (nodebugmode) cout << "getting bin " << i << " from " << hist_data_sum[index]->GetBinLowEdge(i+1) << " to " <<  hist_data_sum[index]->GetBinLowEdge(i+2) << endl;
        Double_t s_d = hist_data[index]->GetBinError(i+1);
        Double_t s_l = hist_mc_rad[index]->GetBinError(i+1);
        Double_t s_q = hist_mc[index]->GetBinError(i+1);
        Double_t s_ph = hist_mc_photon[index]->GetBinError(i+1);
        Double_t s_bg = hist_mc_norad[index]->GetBinError(i+1);
        //      Double_t s_photon = hist_mc_photon[index]->GetBinError(i+1);

        Double_t v_d = hist_data[index]->GetBinContent(i+1);
        Double_t v_l = hist_mc_rad[index]->GetBinContent(i+1);
        Double_t v_q = hist_mc[index]->GetBinContent(i+1);
        Double_t v_ph = hist_mc_photon[index]->GetBinContent(i+1);
        Double_t v_bg = hist_mc_norad[index]->GetBinContent(i+1);
        //      Double_t v_photon = hist_mc_photon[index]->GetBinContent(i+1);
        //
        // Ian's page
        //
        //      ebb = sdd**2*(param(1)**2*ggn(i)/sgg+(1.-param(1))**2*aan(i)/saa)
        //  edd(i) = sqrt(dd(i) + ebb)
        Double_t dd_i = v_d;
        Double_t sdd = hist_data[index]->GetSum();
        //      dd_i /= sdd;
        //      Double_t ggn_i = v_photon;
        //      Double_t sgg = hist_mc_photon[index]->GetSum();
        //      ggn_i *= sdd/sgg;
        Double_t aan_i = v_bg;
        Double_t saa = hist_mc_norad[index]->GetSum();
        //      aan_i *= sdd/saa;
        //      Double_t ebb = sdd*sdd*(par[0]*par[0]*ggn_i/(sgg*sgg) + (1-par[0])*(1-par[0])*aan_i/(saa*saa));


        // Oleg
        //
        // ====================================================================================================
            //  diff = hist_data[index]->GetBinContent(i+1) - hist_mc_rad[index]->GetBinContent(i+1) - par[0]*hist_mc[index]->GetBinContent(i+1) - (1-par[0])*hist_mc_norad[index]->GetBinContent(i+1);
        //EB:
        //!!!! by 031015
        if (QQfit == 0)
            diff = hist_data[index]->GetBinContent(i+1) - par[0]*hist_mc_photon[index]->GetBinContent(i+1) - (1-par[0])*hist_mc_norad[index]->GetBinContent(i+1);
        else
            diff = hist_data[index]->GetBinContent(i+1) - hist_mc_rad[index]->GetBinContent(i+1) - par[0]*hist_mc[index]->GetBinContent(i+1) - (1-par[0])*hist_mc_norad[index]->GetBinContent(i+1);
        ///if (nodebugmode) cout << "par[0] = " << par[0] ;
        // ====================================================================================================
        //
        // Ian
        //
        // ====================================================================================================
        //      diff = v_d/sdd - par[0]/sgg - (1-par[0])*aan_i/saa;
        //diff = dd_i - par[0]*ggn_i*sdd/sgg - (1-par[0])*aan_i*sdd/saa;
        // ====================================================================================================
        Double_t denom = 0.;
        
        if(s_method == "Barlow-Beeston") 
        {
            //  denom = 1.;//s_d*s_d + s_l*s_l + par[0]*par[0]*s_q*s_q + (1.-par[0])*(1.-par[0])*s_bg*s_bg;
            //  denom = v_d - v_l + par[0]*par[0]*v_q + (1.-par[0])*(1.-par[0])*v_bg;
            //  denom = (s_d + s_l)*(s_d + s_l) + par[0]*par[0]*s_q*s_q + (1.-par[0])*(1.-par[0])*s_bg*s_bg; //this sent to Ian
            //
            // Oleg
            //
            // ====================================================================================================
              //denom = s_d*s_d + s_l*s_l + par[0]*par[0]*s_q*s_q + (1.-par[0])*(1.-par[0])*s_bg*s_bg;
            if(denom==0)
            {
                //! cerr << "denom = 0 in cross_sec.cxx. Exiting" << endl;
                //      exit(-1);
            }
            //  denom = (s_d + s_l)*(s_d + s_l) + par[0]*par[0]*s_q*s_q + (1.-par[0])*(1.-par[0])*s_bg*s_bg;

            //!!!! by 031015
            if (QQfit != 1)
                denom = s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg;
            else
                denom = s_d*s_d + s_l*s_l + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg;

            //  if (nodebugmode) cout << "min: " << i << " " << s_d << " " << s_l << " " << s_q << " " << s_bg << " " << par[0] << " " << denom << endl;
            //  if (nodebugmode) cout << " denom = " << denom << endl;
            ///if (nodebugmode) cout << "dz " << i << "\t" << "numer=" << diff*diff << "\tdenom=" << denom << "\tndf=" << ndf << " " << diff*diff/denom << endl;
            ///if (nodebugmode) cout <<i+1 << " yhDat=" << v_d << "\tyh1= " << v_q << "\tyh2= " << v_bg  << "\tyhDatE=" << s_d << "\tyh1E= " << s_q << "\tyh2E= " << s_bg << "\t sl = " << s_l << endl;
            // ====================================================================================================
            //
            // Ian
            //
            // ====================================================================================================
            //  denom = s_d*s_d + par[0]*par[0]*s_photon*s_photon + (1.-par[0])*(1.-par[0])*s_bg*s_bg;
            //denom = dd_i + ebb;
            //  if (nodebugmode) cout << dd_i << " - " << par[0] << "*" << ggn_i << "*" <<  sdd << "/" << sgg << " - (1-" << par[0] << ")*" << aan_i << "*" << sdd << "/ " << saa << endl;
            //  if (nodebugmode) cout << 
            // ====================================================================================================
            //denom = (s_d )*(s_d ) + par[0]*par[0]*s_q*s_q + (1.-par[0])*(1.-par[0])*s_bg*s_bg;
        }
        else
        if(s_method == "Gauss")
            if (QQfit != 1)
                denom = s_d*s_d;
            else
                denom = s_d*s_d + s_l*s_l;
        else
        {
            cerr << "Unknown fit method: " << s_method << ". Exiting" << endl;
            exit(-1);
        }
        ///if (nodebugmode) cout << "errs: " << i << " " << par[0] << " " << s_d << " " << s_l << " " << s_q << " " << s_bg << " " << diff << " " << denom << endl;  
        //      if (nodebugmode) cout << "bin " << i+1  << " " << diff << " " << denom << " " << diff*diff/denom << " " << res << endl;

        if(par[0]!=par[0])
            res += 1000.;
        else
            res += diff*diff/denom;
        ndf++;
    }
    ndf = ndf - 2 ;//?- QQfit
    //   if (nodebugmode) cout << "ndf = " << ndf << endl;
    //  res /= float(ndf-1);
    //  if (nodebugmode) cout << float(hist_data[index]->GetNbinsX() - 1) << endl;
    //   if (nodebugmode) cout << "calling chi2: " << res << endl << endl << endl;
    return res;
}
