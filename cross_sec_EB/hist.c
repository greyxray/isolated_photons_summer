#include "hist.h"
#include "hist_plot_box.c"
#include "hist_apply_hadronisation_corrections.c"
#include "hist_plot_cross_sec.c"
#include "hist_calculate_cross_sec.c"
#include "hist_compare1st2nd.c"
#include "hist_set_syst_errors.c"
//#include "TDirectory.h"
#include "TMath.h"

Hist::~Hist(){}

Hist::Hist()
{
    f = new TFile("cross_sec_histos.root", "recreate", "root file with histohrams");
    f->cd();

    s_periods[0] = "0405e";
    s_periods[1] = "06e";
    s_periods[2] = "0607p";
    s_var[0] = "et";
    s_var[1] = "eta";
    s_var[2] = "Q2";
    s_var[3] = "x";
    s_var[4] = "et_jet";
    s_var[5] = "eta_jet";
    lumi_data[0] = 134.003 * 1.01;//  lumi_data[0] = 134.15997;
    lumi_data[1] = 52.4195 * 1.01;//  lumi_data[1] = 54.79574;
    lumi_data[2] = 136.219 * 1.01;//  lumi_data[2] = 142.93778;
    lumi_mc_bg[0] = 271.36;///703;//271.36;
    lumi_mc_bg[1] = 165.26;
    lumi_mc_bg[2] = 364.6;
    lumi_mc_prph = 3552.40;
    total_luminosity_data = 0.;
    //mc before enlarging  ? 300615
    /*  Double_t lumi_mc0405e   = 135.387;
        Double_t lumi_mc06e     =  55.2645 ;
        Double_t lumi_mc0607p   = 123.161 ;
        Double_t lumi_mc0607p_2 = 150.088 ;
        Double_t lumi_mcall     = //lumi_mc04p+
        lumi_mc0405e+
        lumi_mc06e+
        lumi_mc0607p;
    */
    fout.open("cross_values.c"); //на выход

    f_unity = new TF1("Unity", "0", -100., 500.); //? TF1* ?300615 зачем эта функция - он не сохран
    f_unity->SetLineWidth(1);
    f_unity->SetLineColor(32);

    TString s_path2 = "../my_";
    //TString s_method = "_test";
    //TString s_method = "_test_systElE-";//"_q2etapheph_rew_n.root"; //? 010715
    //TString s_method = "_test_systElE+";
    //TString s_method = "_test_systJetE+";// touch output_systJetE+.txt; ./p cross_sec >  output_systJetE+.txt
    TString s_method = "_test_systJetE-";// touch output_systJetE-.txt; ./p cross_sec >  output_systJetE-.txt &
    //TString s_method = "_test_systPhE+";
    //TString s_method = "_test_systPhE-";
    //TString s_method3 = "_test_rew_eph_bg.root";
    //TString s_method2 = "_test_syst_jet_minus.root";

      //////////////////////////////////////////////////
      //
      //             Connect Input Files
      //
      //////////////////////////////////////////////////  
    for(Int_t i = 0; i < n_periods; i++) 
    {
      TString s; 
      s.Form(s_path2 + "data" + s_periods[i] + "_test.root");//../data
      file_data[i] = new TFile(s, "READ");
      s.Form(s_path2 + "mc_bg_norad" + s_periods[i] + s_method + ".root");
      file_norad[i] = new TFile(s, "READ");
      s.Form(s_path2 + "mc_bg_rad" + s_periods[i] + s_method + ".root");
      file_rad[i] = new TFile(s, "READ");
      if (s_periods[i] != "0607p") //нету такой симуляции
      { 
        s.Form(s_path2 + "mc_prph" + s_periods[i] + s_method + ".root");
        file_prph[i] = new TFile(s, "READ");
      }
      total_luminosity_data += lumi_data[i];
    }

    //////////////////////////////////////////////////
    //
    //             Read Histograms //! 010715 - можно переписать через класы и функции.
    //
    //////////////////////////////////////////////////

    for(Int_t i = 0; i < n_periods; i++) 
    {//data, mc_rad, mc_norad
        //====================== data =============================================
        file_data[i]->cd();
        //
        // dz in bins of et
        //
        for(Int_t j = 0; j < number_etbins; j++) //number_etbins = 4;
        {
            TString s; 
            s.Form("h_deltaz_et_%i", j);
            cout << "reading " << s << " ..." << endl;
            h_deltaz_et_data[j][i] = (TH1D*)file_data[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
            s = s + "_data_" + s_periods[i];
            h_deltaz_et_data[j][i]->SetName(s);
            cout << "OK: renamed to " << s << endl;
            h_deltaz_et_data[j][i]->Sumw2();
            h_deltaz_et_data[j][i]->Rebin(10);
        }
        //
        // dz in bins of eta
        //
        for(Int_t j = 0; j < number_etabins; j++) 
        {
          TString s; 
          s.Form("h_deltaz_eta_%i", j);
          cout << "reading " << s << " ..." << endl;
          h_deltaz_eta_data[j][i] = (TH1D*)file_data[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          s = s + "_data_" + s_periods[i];
          h_deltaz_eta_data[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          h_deltaz_eta_data[j][i]->Sumw2();
          h_deltaz_eta_data[j][i]->Rebin(10);
        }
        //
        // dz in bins of q2
        //
        for(Int_t j = 0; j < number_Q2bins; j++) 
        {
          TString s; 
          s.Form("h_deltaz_q2_%i", j);
          cout << "reading " << s << " ..." << endl;
          h_deltaz_q2_data[j][i] = (TH1D*)file_data[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          s = s + "_data_" + s_periods[i];
          h_deltaz_q2_data[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          h_deltaz_q2_data[j][i]->Sumw2();
          h_deltaz_q2_data[j][i]->Rebin(10);
        }
        //
        // dz in bins of x
        //
        for(Int_t j = 0; j < number_xbins; j++) 
        {
          TString s; s.Form("h_deltaz_x_%i", j);
          cout << "reading " << s << " ..." << endl;
          h_deltaz_x_data[j][i] = (TH1D*)file_data[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          s = s + "_data_" + s_periods[i];
          h_deltaz_x_data[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          h_deltaz_x_data[j][i]->Sumw2();
          h_deltaz_x_data[j][i]->Rebin(10);
        }
        //
        // dz in bins of et_jet
        //
        for(Int_t j = 0; j < number_et_jetbins; j++) 
        {
          TString s; s.Form("h_deltaz_et_jet_%i", j);
          cout << "reading " << s << " ..." << endl;
          h_deltaz_et_jet_data[j][i] = (TH1D*)file_data[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          s = s + "_data_" + s_periods[i];
          h_deltaz_et_jet_data[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          h_deltaz_et_jet_data[j][i]->Sumw2();
          h_deltaz_et_jet_data[j][i]->Rebin(10);
        }
        //
        // dz in bins of eta_jet
        //
        for(Int_t j = 0; j < number_eta_jetbins; j++) 
        {
          TString s; s.Form("h_deltaz_eta_jet_%i", j);
          cout << "reading " << s << " ..." << endl;
          h_deltaz_eta_jet_data[j][i] = (TH1D*)file_data[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          s = s + "_data_" + s_periods[i];
          h_deltaz_eta_jet_data[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          h_deltaz_eta_jet_data[j][i]->Sumw2();
          h_deltaz_eta_jet_data[j][i]->Rebin(10);
        }
        //
        // Profiles
        //
        for(Int_t j = 0; j < n_cross; j++) //6
        {
            //det
            TString s; 
            s.Form("prof_det_cross_" + s_var[j]);
            cout << "reading " << s << " ..." << endl;
            prof_det_data[j][i] = (TProfile*)file_data[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
            s = s + "_data_" + s_var[j] + s_periods[i];
            prof_det_data[j][i]->SetName(s);
            cout << "OK: renamed to " << s << endl;
            prof_det_data[j][i]->Sumw2();

            s.Form("h_det_cross_" + s_var[j]);
            cout << "reading " << s << " ..." << endl;
            h_det_data[j][i] = (TH1D*)file_data[i]->Get("Cross_Sections_Histograms/" + s)->Clone();
            s = s + "_data_" + s_periods[i];
            h_det_data[j][i]->SetName(s);
            cout << "OK: renamed to " << s << endl;
            h_det_data[j][i]->Sumw2();
        }

        //====================== mc norad =============================================
        file_norad[i]->cd();
        //
        // dz in bins of et
        //
        for(Int_t j = 0; j < number_etbins; j++) 
        {
          TString s; 
          s.Form("h_deltaz_et_%i", j);
          cout << "reading " << s << " ..." << endl;
          h_deltaz_et_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          s = s + "_norad_" + s_periods[i];
          h_deltaz_et_norad[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          h_deltaz_et_norad[j][i]->Sumw2();
          h_deltaz_et_norad[j][i]->Rebin(10);
        }
        //
        // dz in bins of eta
        //
        for(Int_t j = 0; j < number_etabins; j++) 
        {
          TString s; 
          s.Form("h_deltaz_eta_%i", j);
          cout << "reading " << s << " ..." << endl;
          h_deltaz_eta_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          s = s + "_norad_" + s_periods[i];
          h_deltaz_eta_norad[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          h_deltaz_eta_norad[j][i]->Sumw2();
          h_deltaz_eta_norad[j][i]->Rebin(10);
        }
        //
        // dz in bins of q2
        //
        for(Int_t j = 0; j < number_Q2bins; j++) 
        {
          TString s; s.Form("h_deltaz_q2_%i", j);
          cout << "reading " << s << " ..." << endl;
          h_deltaz_q2_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          s = s + "_norad_" + s_periods[i];
          h_deltaz_q2_norad[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          h_deltaz_q2_norad[j][i]->Sumw2();
          h_deltaz_q2_norad[j][i]->Rebin(10);
        }
        //
        // dz in bins of x
        //
        for(Int_t j = 0; j < number_xbins; j++) 
        {
          TString s; s.Form("h_deltaz_x_%i", j);
          cout << "reading " << s << " ..." << endl;
          h_deltaz_x_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          s = s + "_norad_" + s_periods[i];
          h_deltaz_x_norad[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          h_deltaz_x_norad[j][i]->Sumw2();
          h_deltaz_x_norad[j][i]->Rebin(10);
        }
        //
        // dz in bins of et_jet
        //
        for(Int_t j = 0; j < number_et_jetbins; j++) 
        {
          TString s; s.Form("h_deltaz_et_jet_%i", j);
          cout << "reading " << s << " ..." << endl;
          h_deltaz_et_jet_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          s = s + "_norad_" + s_periods[i];
          h_deltaz_et_jet_norad[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          h_deltaz_et_jet_norad[j][i]->Sumw2();
          h_deltaz_et_jet_norad[j][i]->Rebin(10);
        }
        //
        // dz in bins of eta_jet
        //
        for(Int_t j = 0; j < number_eta_jetbins; j++) 
        {
          TString s; s.Form("h_deltaz_eta_jet_%i", j);
          cout << "reading " << s << " ..." << endl;
          h_deltaz_eta_jet_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          s = s + "_norad_" + s_periods[i];
          h_deltaz_eta_jet_norad[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          h_deltaz_eta_jet_norad[j][i]->Sumw2();
          h_deltaz_eta_jet_norad[j][i]->Rebin(10);
        }
        
        //
        // Profiles
        //
        for(Int_t j = 0; j < n_cross; j++) 
        {
          //det
          TString s; s.Form("prof_det_cross_" + s_var[j]);
          cout << "reading " << s << " ..." << endl;
          prof_det_norad[j][i] = (TProfile*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          s = s + "_norad_" + s_var[j] + s_periods[i];
          prof_det_norad[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          prof_det_norad[j][i]->Sumw2();
          
          //had
          s.Form("prof_had_cross_" + s_var[j]);
          cout << "reading " << s << " ..." << endl;
          prof_had_norad[j][i] = (TProfile*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          s = s + "_norad_" + s_var[j] + s_periods[i];
          prof_had_norad[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          prof_had_norad[j][i]->Sumw2();
          
          //hd
          s.Form("prof_hd_cross_" + s_var[j]);
          cout << "reading " << s << " ..." << endl;
          prof_hd_norad[j][i] = (TProfile*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          s = s + "_norad_" + s_var[j] + s_periods[i];
          prof_hd_norad[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          prof_hd_norad[j][i]->Sumw2();
          
          //det
          s.Form("h_det_cross_" + s_var[j]);
          cout << "reading " << s << " ..." << endl;
          h_det_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          s = s + "_norad_" + s_var[j] + s_periods[i];
          h_det_norad[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          h_det_norad[j][i]->Sumw2();
          /*      //had
              s.Form("h_had_cross_" + s_var[j]);
              cout << "reading " << s << " ..." << endl;
              h_had_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
              s = s + "_norad_" + s_var[j] + s_periods[i];
              h_had_norad[j][i]->SetName(s);
              cout << "OK: renamed to " << s << endl;
              h_had_norad[j][i]->Sumw2();
              //hd
              s.Form("h_hd_cross_" + s_var[j]);
              cout << "reading " << s << " ..." << endl;
              h_hd_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
              s = s + "_norad_" + s_var[j] + s_periods[i];
              h_hd_norad[j][i]->SetName(s);
              cout << "OK: renamed to " << s << endl;
              h_hd_norad[j][i]->Sumw2();*/
        }

        //====================== mc rad =============================================
        file_rad[i]->cd();
        //
        // dz in bins of et
        //
        for(Int_t j = 0; j < number_etbins; j++) 
        {
          TString s; 
          s.Form("h_deltaz_et_%i", j);
          cout << "reading " << s << " ..." << endl;
          h_deltaz_et_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          cout << "just read et bin " << j << "sum = " << h_deltaz_et_rad[j][i]->GetSum() << ", entries = " << h_deltaz_et_rad[j][i]->GetEntries() 
           << ", integral = " << h_deltaz_et_rad[j][i]->Integral() << endl;
          s = s + "_rad_" + s_periods[i];
          h_deltaz_et_rad[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          h_deltaz_et_rad[j][i]->Sumw2();
          h_deltaz_et_rad[j][i]->Rebin(10);
          
        }
        //
        // dz in bins of eta
        //
        for(Int_t j = 0; j < number_etabins; j++) 
        {
          TString s; 
          s.Form("h_deltaz_eta_%i", j);
          cout << "reading " << s << " ..." << endl;
          h_deltaz_eta_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          s = s + "_rad_" + s_periods[i];
          h_deltaz_eta_rad[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          h_deltaz_eta_rad[j][i]->Sumw2();
          h_deltaz_eta_rad[j][i]->Rebin(10);
        }
        //
        // dz in bins of q2
        //
        for(Int_t j = 0; j < number_Q2bins; j++) 
        {
          TString s; 
          s.Form("h_deltaz_q2_%i", j);
          cout << "reading " << s << " ..." << endl;
          h_deltaz_q2_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          s = s + "_rad_" + s_periods[i];
          h_deltaz_q2_rad[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          h_deltaz_q2_rad[j][i]->Sumw2();
          h_deltaz_q2_rad[j][i]->Rebin(10);
        }
        //
        // dz in bins of x
        //
        for(Int_t j = 0; j < number_xbins; j++) 
        {
          TString s; 
          s.Form("h_deltaz_x_%i", j);
          cout << "reading " << s << " ..." << endl;
          h_deltaz_x_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          s = s + "_rad_" + s_periods[i];
          h_deltaz_x_rad[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          h_deltaz_x_rad[j][i]->Sumw2();
          h_deltaz_x_rad[j][i]->Rebin(10);
        }
        //
        // dz in bins of et_jet
        //
        for(Int_t j = 0; j < number_et_jetbins; j++) 
        {
          TString s; 
          s.Form("h_deltaz_et_jet_%i", j);
          cout << "reading " << s << " ..." << endl;
          h_deltaz_et_jet_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          s = s + "_rad_" + s_periods[i];
          h_deltaz_et_jet_rad[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          h_deltaz_et_jet_rad[j][i]->Sumw2();
          h_deltaz_et_jet_rad[j][i]->Rebin(10);
        }
        //
        // dz in bins of eta_jet
        //
        for(Int_t j = 0; j < number_eta_jetbins; j++) 
        {
          TString s; 
          s.Form("h_deltaz_eta_jet_%i", j);
          cout << "reading " << s << " ..." << endl;
          h_deltaz_eta_jet_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
          s = s + "_rad_" + s_periods[i];
          h_deltaz_eta_jet_rad[j][i]->SetName(s);
          cout << "OK: renamed to " << s << endl;
          h_deltaz_eta_jet_rad[j][i]->Sumw2();
          h_deltaz_eta_jet_rad[j][i]->Rebin(10);
        }
        //
        // Profiles
        //
        for(Int_t j = 0; j < n_cross; j++) 
        { //file_rad
            
            //det prof
            TString s; 
            s.Form("prof_det_cross_" + s_var[j]);
            cout << "reading " << s << " ..." << endl;
            prof_det_rad[j][i] = (TProfile*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
            s = s + "_rad_" + s_var[j] + s_periods[i];
            prof_det_rad[j][i]->SetName(s);
            cout << "OK: renamed to " << s << endl;
            prof_det_rad[j][i]->Sumw2();
            //had prof
            s.Form("prof_had_cross_" + s_var[j]);
            cout << "reading " << s << " ..." << endl;
            prof_had_rad[j][i] = (TProfile*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
            s = s + "_rad_" + s_var[j] + s_periods[i];
            prof_had_rad[j][i]->SetName(s);
            cout << "OK: renamed to " << s << endl;
            prof_had_rad[j][i]->Sumw2();
            //hd prof
            s.Form("prof_hd_cross_" + s_var[j]);
            cout << "reading " << s << " ..." << endl;
            prof_hd_rad[j][i] = (TProfile*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
            s = s + "_rad_" + s_var[j] + s_periods[i];
            prof_hd_rad[j][i]->SetName(s);
            cout << "OK: renamed to " << s << endl;
            prof_hd_rad[j][i]->Sumw2();

            //det
            s.Form("h_det_cross_" + s_var[j]);
            cout << "reading " << s << " ..." << endl;
            h_det_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
            s = s + "_rad_" + s_var[j] + s_periods[i];
            h_det_rad[j][i]->SetName(s);
            cout << "OK: renamed to " << s << endl;
            h_det_rad[j][i]->Sumw2();
            //had
            s.Form("h_had_cross_" + s_var[j]);
            cout << "reading " << s << " ..." << endl;
            h_had_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
            s = s + "_rad_" + s_var[j] + s_periods[i];
            h_had_rad[j][i]->SetName(s);
            cout << "OK: renamed to " << s << endl;
            h_had_rad[j][i]->Sumw2();
            //hd
            s.Form("h_hd_cross_" + s_var[j]); //?
            cout << "reading " << s << " ..." << endl;
            h_hd_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
            s = s + "_rad_" + s_var[j] + s_periods[i];
            h_hd_rad[j][i]->SetName(s);
            cout << "OK: renamed to " << s << endl;
            h_hd_rad[j][i]->Sumw2();
        }
        
        //====================== mc prph =============================================
        if(i != 2) 
        {
            file_prph[i]->cd();
            //
            // dz in bins of et
            //
            for(Int_t j = 0; j < number_etbins; j++) 
            {
                TString s; 
                s.Form("h_deltaz_et_%i", j);
                cout << "reading " << s << " ..." << endl;
                h_deltaz_et_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_periods[i];
                h_deltaz_et_prph[j][i]->SetName(s);
                cout << "OK: renamed to " << s << endl;
                h_deltaz_et_prph[j][i]->Sumw2();
                h_deltaz_et_prph[j][i]->Rebin(10);
            }
            //
            // dz in bins of eta
            //
            for(Int_t j=0; j<number_etabins; j++) 
            {
                TString s; s.Form("h_deltaz_eta_%i", j);
                cout << "reading " << s << " ..." << endl;
                h_deltaz_eta_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_periods[i];
                h_deltaz_eta_prph[j][i]->SetName(s);
                h_deltaz_eta_prph[j][i]->Sumw2();
                h_deltaz_eta_prph[j][i]->Rebin(10);
                cout << "OK: renamed to " << s << endl;
            }
            //
            // dz in bins of q2
            //
            for(Int_t j=0; j<number_Q2bins; j++) 
            {
                TString s; 
                s.Form("h_deltaz_q2_%i", j);
                cout << "reading " << s << " ..." << endl;
                h_deltaz_q2_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_periods[i];
                h_deltaz_q2_prph[j][i]->SetName(s);
                h_deltaz_q2_prph[j][i]->Sumw2();
                h_deltaz_q2_prph[j][i]->Rebin(10);
                cout << "OK: renamed to " << s << endl;
            }
            //
            // dz in bins of x
            //
            for(Int_t j=0; j<number_xbins; j++) 
            {
                TString s; s.Form("h_deltaz_x_%i", j);
                cout << "reading " << s << " ..." << endl;
                h_deltaz_x_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_periods[i];
                h_deltaz_x_prph[j][i]->SetName(s);
                cout << "OK: renamed to " << s << endl;
                h_deltaz_x_prph[j][i]->Sumw2();
                h_deltaz_x_prph[j][i]->Rebin(10);
            }
            //
            // dz in bins of et_jet
            //
            for(Int_t j=0; j<number_et_jetbins; j++) 
            {
                TString s; s.Form("h_deltaz_et_jet_%i", j);
                cout << "reading " << s << " ..." << endl;
                h_deltaz_et_jet_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_periods[i];
                h_deltaz_et_jet_prph[j][i]->SetName(s);
                h_deltaz_et_jet_prph[j][i]->Sumw2();
                h_deltaz_et_jet_prph[j][i]->Rebin(10);
                cout << "OK: renamed to " << s << endl;
            }
            //
            // dz in bins of eta_jet
            //
            for(Int_t j=0; j<number_eta_jetbins; j++) 
            {
                TString s; s.Form("h_deltaz_eta_jet_%i", j);
                cout << "reading " << s << " ..." << endl;
                h_deltaz_eta_jet_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_periods[i];
                h_deltaz_eta_jet_prph[j][i]->SetName(s);
                h_deltaz_eta_jet_prph[j][i]->Sumw2();
                h_deltaz_eta_jet_prph[j][i]->Rebin(10);
                cout << "OK: renamed to " << s << endl;
            }
            //
            // Profiles
            //
            for(Int_t j=0; j<n_cross; j++) 
            {
                //det
                TString s; s.Form("prof_det_cross_" + s_var[j]);
                cout << "reading " << s << " ..." << endl;
                prof_det_prph[j][i] = (TProfile*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_var[j] + s_periods[i];
                prof_det_prph[j][i]->SetName(s);
                cout << "OK: renamed to " << s << endl;
                prof_det_prph[j][i]->Sumw2();
                //had
                s.Form("prof_had_cross_" + s_var[j]);
                cout << "reading " << s << " ..." << endl;
                prof_had_prph[j][i] = (TProfile*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_var[j] + s_periods[i];
                prof_had_prph[j][i]->SetName(s);
                cout << "OK: renamed to " << s << endl;
                prof_had_prph[j][i]->Sumw2();
                //hd
                s.Form("prof_hd_cross_" + s_var[j]);
                cout << "reading " << s << " ..." << endl;
                prof_hd_prph[j][i] = (TProfile*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_var[j] + s_periods[i];
                prof_hd_prph[j][i]->SetName(s);
                cout << "OK: renamed to " << s << endl;
                prof_hd_prph[j][i]->Sumw2();

                //det
                s.Form("h_det_cross_" + s_var[j]);
                cout << "reading " << s << " ..." << endl;
                h_det_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_var[j] + s_periods[i];
                h_det_prph[j][i]->SetName(s);
                cout << "OK: renamed to " << s << endl;
                h_det_prph[j][i]->Sumw2();
                //had
                s.Form("h_had_cross_" + s_var[j]);
                cout << "reading " << s << " ..." << endl;
                h_had_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_var[j] + s_periods[i];
                h_had_prph[j][i]->SetName(s);
                cout << "OK: renamed to " << s << endl;
                h_had_prph[j][i]->Sumw2();
                //hd
                s.Form("h_hd_cross_" + s_var[j]);
                cout << "reading " << s << " ..." << endl;
                h_hd_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_var[j] + s_periods[i];
                h_hd_prph[j][i]->SetName(s);
                cout << "OK: renamed to " << s << endl;
                h_hd_prph[j][i]->Sumw2();
            }
        }//exclude 0607p (there is no mc_prph for 0607p)
    }//for i over periods
 
    //////////////////////////////////////////////////
    //
    //             Sum Over Periods - Initialize, scale to luminosity and Fill
    //             //! Можно переписать через функции/классы
    //
    //////////////////////////////////////////////////  
    f->cd();
    for(Int_t i = 0; i < n_periods; i++) 
    {
        for(Int_t j = 0; j < number_etbins; j++) //et
        {
            if(i==0) 
            {
                TString s; 
                s.Form("h_deltaz_et_data_sum_%i", j);
                h_deltaz_et_data_sum[j] = (TH1D*)h_deltaz_et_data[j][i]->Clone();
                h_deltaz_et_data_sum[j]->SetName(s);
                s.Form("h_deltaz_et_norad_sum_%i", j);
                h_deltaz_et_norad_sum[j] = (TH1D*)h_deltaz_et_norad[j][i]->Clone();
                h_deltaz_et_norad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_et_norad_sum[j]->SetName(s);
                s.Form("h_deltaz_et_rad_sum_%i", j);
                h_deltaz_et_rad_sum[j] = (TH1D*)h_deltaz_et_rad[j][i]->Clone();
                h_deltaz_et_rad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_et_rad_sum[j]->SetName(s);
                s.Form("h_deltaz_et_prph_sum_%i", j);//? 010715 почему нету Scale?
                h_deltaz_et_prph_sum[j] = (TH1D*)h_deltaz_et_prph[j][i]->Clone();
                h_deltaz_et_prph_sum[j]->SetName(s);
                
                s.Form("h_chi2_perbin_et_%i", j);
                h_chi2_perbin_et[j] = new TH1D(s, ";bin;#chi^{2}", 16, 0, 16);
                //	h_chi2_perbin_eta_jet[j]->SetName(s)
            } else {
                h_deltaz_et_data_sum[j]->Add(h_deltaz_et_data[j][i]);
                h_deltaz_et_norad_sum[j]->Add(h_deltaz_et_norad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_et_rad_sum[j]->Add(h_deltaz_et_rad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                if(s_periods[i]!="0607p")
                    h_deltaz_et_prph_sum[j]->Add(h_deltaz_et_prph[j][i]);
            }
        }// for j over et bins

        for(Int_t j=0; j<number_etabins; j++) //eta
        {
            if(i==0) 
            {
                TString s; s.Form("h_deltaz_eta_data_sum_%i", j);
                h_deltaz_eta_data_sum[j] = (TH1D*)h_deltaz_eta_data[j][i]->Clone();
                h_deltaz_eta_data_sum[j]->SetName(s);
                s.Form("h_deltaz_eta_norad_sum_%i", j);
                h_deltaz_eta_norad_sum[j] = (TH1D*)h_deltaz_eta_norad[j][i]->Clone();
                h_deltaz_eta_norad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_eta_norad_sum[j]->SetName(s);
                s.Form("h_deltaz_eta_rad_sum_%i", j);
                h_deltaz_eta_rad_sum[j] = (TH1D*)h_deltaz_eta_rad[j][i]->Clone();
                h_deltaz_eta_rad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_eta_rad_sum[j]->SetName(s);
                s.Form("h_deltaz_eta_prph_sum_%i", j);
                h_deltaz_eta_prph_sum[j] = (TH1D*)h_deltaz_eta_prph[j][i]->Clone();
                h_deltaz_eta_prph_sum[j]->SetName(s);
                
                s.Form("h_chi2_perbin_eta_%i", j);
                h_chi2_perbin_eta[j] = new TH1D(s, ";bin;#chi^{2}", 16, 0, 16);
            } else {
                h_deltaz_eta_data_sum[j]->Add(h_deltaz_eta_data[j][i]);
                h_deltaz_eta_norad_sum[j]->Add(h_deltaz_eta_norad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_eta_rad_sum[j]->Add(h_deltaz_eta_rad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                if(s_periods[i]!="0607p")
                    h_deltaz_eta_prph_sum[j]->Add(h_deltaz_eta_prph[j][i]);
            }
        }// for j over eta bins

        for(Int_t j=0; j<number_Q2bins; j++) 
        {//q2
            if(i==0) 
            {
                TString s; s.Form("h_deltaz_q2_data_sum_%i", j);
                h_deltaz_q2_data_sum[j] = (TH1D*)h_deltaz_q2_data[j][i]->Clone();
                h_deltaz_q2_data_sum[j]->SetName(s);
                s.Form("h_deltaz_q2_norad_sum_%i", j);
                h_deltaz_q2_norad_sum[j] = (TH1D*)h_deltaz_q2_norad[j][i]->Clone();
                h_deltaz_q2_norad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_q2_norad_sum[j]->SetName(s);
                s.Form("h_deltaz_q2_rad_sum_%i", j);
                h_deltaz_q2_rad_sum[j] = (TH1D*)h_deltaz_q2_rad[j][i]->Clone();
                h_deltaz_q2_rad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_q2_rad_sum[j]->SetName(s);
                s.Form("h_deltaz_q2_prph_sum_%i", j);
                h_deltaz_q2_prph_sum[j] = (TH1D*)h_deltaz_q2_prph[j][i]->Clone();
                h_deltaz_q2_prph_sum[j]->SetName(s);

                s.Form("h_chi2_perbin_Q2_%i", j);
                h_chi2_perbin_Q2[j] = new TH1D(s, ";bin;#chi^{2}", 16, 0, 16);
            } else {
                h_deltaz_q2_data_sum[j]->Add(h_deltaz_q2_data[j][i]);
                h_deltaz_q2_norad_sum[j]->Add(h_deltaz_q2_norad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_q2_rad_sum[j]->Add(h_deltaz_q2_rad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                if(s_periods[i]!="0607p")
                    h_deltaz_q2_prph_sum[j]->Add(h_deltaz_q2_prph[j][i]);
            }
        }// for j over q2 bins

        for(Int_t j=0; j<number_xbins; j++) 
        {//x
            if(i==0) 
            {
                TString s; s.Form("h_deltaz_x_data_sum_%i", j);
                h_deltaz_x_data_sum[j] = (TH1D*)h_deltaz_x_data[j][i]->Clone();
                h_deltaz_x_data_sum[j]->SetName(s);
                s.Form("h_deltaz_x_norad_sum_%i", j);
                h_deltaz_x_norad_sum[j] = (TH1D*)h_deltaz_x_norad[j][i]->Clone();
                h_deltaz_x_norad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_x_norad_sum[j]->SetName(s);
                s.Form("h_deltaz_x_rad_sum_%i", j);
                h_deltaz_x_rad_sum[j] = (TH1D*)h_deltaz_x_rad[j][i]->Clone();
                h_deltaz_x_rad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_x_rad_sum[j]->SetName(s);
                s.Form("h_deltaz_x_prph_sum_%i", j);
                h_deltaz_x_prph_sum[j] = (TH1D*)h_deltaz_x_prph[j][i]->Clone();
                h_deltaz_x_prph_sum[j]->SetName(s);
                
                s.Form("h_chi2_perbin_x_%i", j);
                h_chi2_perbin_x[j] = new TH1D(s, ";bin;#chi^{2}", 16, 0, 16);
            } else {
                h_deltaz_x_data_sum[j]->Add(h_deltaz_x_data[j][i]);
                h_deltaz_x_norad_sum[j]->Add(h_deltaz_x_norad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_x_rad_sum[j]->Add(h_deltaz_x_rad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                if(s_periods[i]!="0607p")
                    h_deltaz_x_prph_sum[j]->Add(h_deltaz_x_prph[j][i]);
            }
        }// for j over x bins

        for(Int_t j=0; j<number_et_jetbins; j++) 
        {//et_jet
            if(i==0) {
                TString s; s.Form("h_deltaz_et_jet_data_sum_%i", j);
                h_deltaz_et_jet_data_sum[j] = (TH1D*)h_deltaz_et_jet_data[j][i]->Clone();
                h_deltaz_et_jet_data_sum[j]->SetName(s);
                s.Form("h_deltaz_et_jet_norad_sum_%i", j);
                h_deltaz_et_jet_norad_sum[j] = (TH1D*)h_deltaz_et_jet_norad[j][i]->Clone();
                h_deltaz_et_jet_norad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_et_jet_norad_sum[j]->SetName(s);
                s.Form("h_deltaz_et_jet_rad_sum_%i", j);
                h_deltaz_et_jet_rad_sum[j] = (TH1D*)h_deltaz_et_jet_rad[j][i]->Clone();
                h_deltaz_et_jet_rad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_et_jet_rad_sum[j]->SetName(s);
                s.Form("h_deltaz_et_jet_prph_sum_%i", j);
                h_deltaz_et_jet_prph_sum[j] = (TH1D*)h_deltaz_et_jet_prph[j][i]->Clone();
                h_deltaz_et_jet_prph_sum[j]->SetName(s);
                
                s.Form("h_chi2_perbin_et_jet%i", j);
                h_chi2_perbin_et_jet[j] = new TH1D(s, ";bin;#chi^{2}", 16, 0, 16);
            } else {
                h_deltaz_et_jet_data_sum[j]->Add(h_deltaz_et_jet_data[j][i]);
                h_deltaz_et_jet_norad_sum[j]->Add(h_deltaz_et_jet_norad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_et_jet_rad_sum[j]->Add(h_deltaz_et_jet_rad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                if(s_periods[i]!="0607p")
                    h_deltaz_et_jet_prph_sum[j]->Add(h_deltaz_et_jet_prph[j][i]);
            }
            }// for j over et_jet bins

        for(Int_t j=0; j<number_eta_jetbins; j++) 
        {//eta_jet
            if(i==0) 
            {
                TString s; s.Form("h_deltaz_eta_jet_data_sum_%i", j);
                h_deltaz_eta_jet_data_sum[j] = (TH1D*)h_deltaz_eta_jet_data[j][i]->Clone();
                h_deltaz_eta_jet_data_sum[j]->SetName(s);
                s.Form("h_deltaz_eta_jet_norad_sum_%i", j);
                h_deltaz_eta_jet_norad_sum[j] = (TH1D*)h_deltaz_eta_jet_norad[j][i]->Clone();
                h_deltaz_eta_jet_norad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_eta_jet_norad_sum[j]->SetName(s);
                s.Form("h_deltaz_eta_jet_rad_sum_%i", j);
                h_deltaz_eta_jet_rad_sum[j] = (TH1D*)h_deltaz_eta_jet_rad[j][i]->Clone();
                h_deltaz_eta_jet_rad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_eta_jet_rad_sum[j]->SetName(s);
                s.Form("h_deltaz_eta_jet_prph_sum_%i", j);
                h_deltaz_eta_jet_prph_sum[j] = (TH1D*)h_deltaz_eta_jet_prph[j][i]->Clone();
                h_deltaz_eta_jet_prph_sum[j]->SetName(s);
                
                s.Form("h_chi2_perbin_eta_jet%i", j);
                h_chi2_perbin_eta_jet[j] = new TH1D(s, ";bin;#chi^{2}", 16, 0, 16);
            } else {
                h_deltaz_eta_jet_data_sum[j]->Add(h_deltaz_eta_jet_data[j][i]);
                h_deltaz_eta_jet_norad_sum[j]->Add(h_deltaz_eta_jet_norad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_eta_jet_rad_sum[j]->Add(h_deltaz_eta_jet_rad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                if(s_periods[i]!="0607p")
                    h_deltaz_eta_jet_prph_sum[j]->Add(h_deltaz_eta_jet_prph[j][i]);
            }
        }// for j over eta_jet bins

        //Profiles sum with scales
        for(Int_t j=0; j<n_cross; j++)
        {
            if(i==0) //Initialisation + scaling
            {
                //
                // detector level profiles
                //
                TString	s= "prof_det_cross_data_" + s_var[j] + "_sum";
                prof_det_data_sum[j] = (TProfile*)prof_det_data[j][i]->Clone();
                prof_det_data_sum[j]->SetName(s);

                s = "prof_det_cross_norad_" + s_var[j] + "_sum";
                prof_det_norad_sum[j] = (TProfile*)prof_det_norad[j][i]->Clone();
                prof_det_norad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                prof_det_norad_sum[j]->SetName(s);

                s = "prof_det_cross_rad_" + s_var[j] + "_sum";
                prof_det_rad_sum[j] = (TProfile*)prof_det_rad[j][i]->Clone();
                prof_det_rad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                prof_det_rad_sum[j]->SetName(s);

                s = "prof_det_cross_prph_" + s_var[j] + "_sum";
                prof_det_prph_sum[j] = (TProfile*)prof_det_prph[j][i]->Clone();
                prof_det_prph_sum[j]->SetName(s);

                //detector histograms
                s = "h_det_cross_data_" + s_var[j] + "_sum";
                h_det_data_sum[j] = (TH1D*)h_det_data[j][i]->Clone();
                h_det_data_sum[j]->SetName(s);

                s = "h_det_cross_norad_" + s_var[j] + "_sum";
                h_det_norad_sum[j] = (TH1D*)h_det_norad[j][i]->Clone();
                h_det_norad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_det_norad_sum[j]->SetName(s);

                s = "h_det_cross_rad_" + s_var[j] + "_sum";
                h_det_rad_sum[j] = (TH1D*)h_det_rad[j][i]->Clone();
                h_det_rad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_det_rad_sum[j]->SetName(s);

                s = "h_det_cross_prph_" + s_var[j] + "_sum";
                h_det_prph_sum[j] = (TH1D*)h_det_prph[j][i]->Clone();
                h_det_prph_sum[j]->SetName(s);

                //
                // hadron level profiles
                //
                s = "prof_had_cross_norad_" + s_var[j] + "_sum";
                prof_had_norad_sum[j] = (TProfile*)prof_had_norad[j][i]->Clone();
                prof_had_norad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                prof_had_norad_sum[j]->SetName(s);

                s = "prof_had_cross_rad_" + s_var[j] + "_sum";
                prof_had_rad_sum[j] = (TProfile*)prof_had_rad[j][i]->Clone();
                prof_had_rad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                prof_had_rad_sum[j]->SetName(s);

                s = "prof_had_cross_prph_" + s_var[j] + "_sum";
                prof_had_prph_sum[j] = (TProfile*)prof_had_prph[j][i]->Clone();
                prof_had_prph_sum[j]->SetName(s);

                //hadron level histograms
                s = "h_had_cross_rad_" + s_var[j] + "_sum";
                h_had_rad_sum[j] = (TH1D*)h_had_rad[j][i]->Clone();
                h_had_rad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_had_rad_sum[j]->SetName(s);

                s = "h_had_cross_prph_" + s_var[j] + "_sum";
                h_had_prph_sum[j] = (TH1D*)h_had_prph[j][i]->Clone();
                h_had_prph_sum[j]->SetName(s);
                
                //
                // hadron & detector profiles
                //
                s = "prof_hd_cross_norad_" + s_var[j] + "_sum";
                prof_hd_norad_sum[j] = (TProfile*)prof_hd_norad[j][i]->Clone();
                prof_hd_norad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                prof_hd_norad_sum[j]->SetName(s);

                s = "prof_hd_cross_rad_" + s_var[j] + "_sum";
                prof_hd_rad_sum[j] = (TProfile*)prof_hd_rad[j][i]->Clone();
                prof_hd_rad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                prof_hd_rad_sum[j]->SetName(s);

                s = "prof_hd_cross_prph_" + s_var[j] + "_sum";
                prof_hd_prph_sum[j] = (TProfile*)prof_hd_prph[j][i]->Clone();
                prof_hd_prph_sum[j]->SetName(s);

                // hadron & detector histograms
                s = "h_hd_cross_rad_" + s_var[j] + "_sum";
                h_hd_rad_sum[j] = (TH1D*)h_hd_rad[j][i]->Clone();
                h_hd_rad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_hd_rad_sum[j]->SetName(s);

                s = "h_hd_cross_prph_" + s_var[j] + "_sum";
                h_hd_prph_sum[j] = (TH1D*)h_hd_prph[j][i]->Clone();
                h_hd_prph_sum[j]->SetName(s);

            } else {
                //profiles
                prof_det_data_sum[j]->Add(prof_det_data[j][i]);
                prof_det_norad_sum[j]->Add(prof_det_norad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                prof_det_rad_sum[j]->Add(prof_det_rad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                if(s_periods[i]!="0607p")
                    prof_det_prph_sum[j]->Add(prof_det_prph[j][i]);

                prof_had_norad_sum[j]->Add(prof_had_norad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                prof_had_rad_sum[j]->Add(prof_had_rad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                if(s_periods[i]!="0607p")
                    prof_had_prph_sum[j]->Add(prof_had_prph[j][i]);

                prof_hd_norad_sum[j]->Add(prof_hd_norad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                prof_hd_rad_sum[j]->Add(prof_hd_rad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                if(s_periods[i]!="0607p")
                    prof_hd_prph_sum[j]->Add(prof_hd_prph[j][i]);

                //histograms
                h_det_data_sum[j]->Add(h_det_data[j][i]);
                h_det_norad_sum[j]->Add(h_det_norad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                h_det_rad_sum[j]->Add(h_det_rad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                if(s_periods[i]!="0607p")
                    h_det_prph_sum[j]->Add(h_det_prph[j][i]);

                h_had_rad_sum[j]->Add(h_had_rad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                if(s_periods[i]!="0607p")
                    h_had_prph_sum[j]->Add(h_had_prph[j][i]);

                h_hd_rad_sum[j]->Add(h_hd_rad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                if(s_periods[i]!="0607p")
                    h_hd_prph_sum[j]->Add(h_hd_prph[j][i]);
            }
        }// for j over cross section variables

    }// for i over periods

    //////////////////////////////////////////////////
    //
    //             Draw attributes  //!
    //
    //////////////////////////////////////////////////
    for(Int_t i = 0; i < number_etbins; i++) 
    {
        h_deltaz_et_res[i] = (TH1D*)h_deltaz_et_rad_sum[i]->Clone();//LL
        h_deltaz_et_res[i]->SetName(h_deltaz_et_rad_sum[i]->GetName() + TString("_res"));

        h_deltaz_et_res[i]->SetLineColor(kBlack);
        h_deltaz_et_res[i]->SetLineWidth(1);
        h_deltaz_et_res[i]->SetFillColor(kYellow);
        h_deltaz_et_data_sum[i]->SetMarkerStyle(24);
        h_deltaz_et_data_sum[i]->SetMarkerSize(0.2);
        h_deltaz_et_prph_sum[i]->SetLineColor(kBlue);
        h_deltaz_et_rad_sum[i]->SetLineColor(kRed);          
        h_deltaz_et_norad_sum[i]->SetLineColor(40);
    }
    for(Int_t i=0; i<number_etabins; i++) {
        h_deltaz_eta_res[i] = (TH1D*)h_deltaz_eta_rad_sum[i]->Clone();
        h_deltaz_eta_res[i]->SetName(h_deltaz_eta_rad_sum[i]->GetName() + TString("_res"));

        h_deltaz_eta_res[i]->SetLineColor(kBlack);
        h_deltaz_eta_res[i]->SetLineWidth(1);
        h_deltaz_eta_res[i]->SetFillColor(kYellow);
        h_deltaz_eta_data_sum[i]->SetMarkerStyle(24);
        h_deltaz_eta_data_sum[i]->SetMarkerSize(0.2);
        h_deltaz_eta_prph_sum[i]->SetLineColor(kBlue);          
        h_deltaz_eta_rad_sum[i]->SetLineColor(kRed);          
        h_deltaz_eta_norad_sum[i]->SetLineColor(40);
    }
    for(Int_t i=0; i<number_Q2bins; i++) {
        h_deltaz_q2_res[i] = (TH1D*)h_deltaz_q2_rad_sum[i]->Clone();
        h_deltaz_q2_res[i]->SetName(h_deltaz_q2_rad_sum[i]->GetName() + TString("_res"));

        h_deltaz_q2_res[i]->SetLineColor(kBlack);
        h_deltaz_q2_res[i]->SetLineWidth(1);
        h_deltaz_q2_res[i]->SetFillColor(kYellow);
        h_deltaz_q2_data_sum[i]->SetMarkerStyle(24);
        h_deltaz_q2_data_sum[i]->SetMarkerSize(0.2);
        h_deltaz_q2_prph_sum[i]->SetLineColor(kBlue);          
        h_deltaz_q2_rad_sum[i]->SetLineColor(kRed);          
        h_deltaz_q2_norad_sum[i]->SetLineColor(40);
    }
    for(Int_t i=0; i<number_xbins; i++) 
    {
        h_deltaz_x_res[i] = (TH1D*)h_deltaz_x_rad_sum[i]->Clone();
        h_deltaz_x_res[i]->SetName(h_deltaz_x_rad_sum[i]->GetName() + TString("_res"));

        h_deltaz_x_res[i]->SetLineColor(kBlack);
        h_deltaz_x_res[i]->SetLineWidth(1);
        h_deltaz_x_res[i]->SetFillColor(kYellow);
        h_deltaz_x_data_sum[i]->SetMarkerStyle(24);
        h_deltaz_x_data_sum[i]->SetMarkerSize(0.2);
        h_deltaz_x_prph_sum[i]->SetLineColor(kBlue);          
        h_deltaz_x_rad_sum[i]->SetLineColor(kRed);          
        h_deltaz_x_norad_sum[i]->SetLineColor(40);
    }
    for(Int_t i=0; i<number_et_jetbins; i++) 
    {
        h_deltaz_et_jet_res[i] = (TH1D*)h_deltaz_et_jet_rad_sum[i]->Clone();
        h_deltaz_et_jet_res[i]->SetName(h_deltaz_et_jet_rad_sum[i]->GetName() + TString("_res"));

        h_deltaz_et_jet_res[i]->SetLineColor(kBlack);
        h_deltaz_et_jet_res[i]->SetLineWidth(1);
        h_deltaz_et_jet_res[i]->SetFillColor(kYellow);
        h_deltaz_et_jet_data_sum[i]->SetMarkerStyle(24);
        h_deltaz_et_jet_data_sum[i]->SetMarkerSize(0.2);
        h_deltaz_et_jet_prph_sum[i]->SetLineColor(kBlue);
        h_deltaz_et_jet_rad_sum[i]->SetLineColor(kRed);
        h_deltaz_et_jet_norad_sum[i]->SetLineColor(40);
    }
    for(Int_t i=0; i<number_eta_jetbins; i++) 
    {
        h_deltaz_eta_jet_res[i] = (TH1D*)h_deltaz_eta_jet_rad_sum[i]->Clone();
        h_deltaz_eta_jet_res[i]->SetName(h_deltaz_eta_jet_rad_sum[i]->GetName() + TString("_res"));

        h_deltaz_eta_jet_res[i]->SetLineColor(kBlack);
        h_deltaz_eta_jet_res[i]->SetLineWidth(1);
        h_deltaz_eta_jet_res[i]->SetFillColor(kYellow);
        h_deltaz_eta_jet_data_sum[i]->SetMarkerStyle(24);
        h_deltaz_eta_jet_data_sum[i]->SetMarkerSize(0.2);
        h_deltaz_eta_jet_prph_sum[i]->SetLineColor(kBlue);
        h_deltaz_eta_jet_rad_sum[i]->SetLineColor(kRed);
        h_deltaz_eta_jet_norad_sum[i]->SetLineColor(40);
    }

    //////////////////////////////////////////////////
    //
    //             CHECKS of adding
    //
    //////////////////////////////////////////////////
  {
        //!
    cout << " ---------- data dz in bins of et ------------" << endl;
    for(Int_t i = 0; i < n_periods; i++) 
    {
        cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
        for(Int_t j = 0; j < number_etbins; j++) 
          cout << h_deltaz_et_data[j][i]->GetEntries() << "\t\t";
        cout << endl;
    } // for i over periods
    
    cout << "sum:\t\t\t\t";
    for(Int_t j = 0; j < number_etbins; j++) 
    {
        cout << h_deltaz_et_data_sum[j]->GetEntries() << "\t\t" ;
        if(j==0)
          for(Int_t k = 0; k < h_deltaz_et_data_sum[j]->GetNbinsX(); k++)
            cout << "0th et bin: " << k << ": " << h_deltaz_et_data_sum[j]->GetBinContent(k+1) << endl;
    }
    
    cout << "\nprph:\t\t\t\t";
    for(Int_t j=0; j<number_etbins; j++) 
        cout << h_deltaz_et_prph_sum[j]->GetEntries() << "\t\t";
    cout << endl << endl;

    cout << " ---------- data dz in bins of eta ------------" << endl;
    for(Int_t i=0; i<n_periods; i++) 
    {
        cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
        for(Int_t j=0; j<number_etabins; j++)
          cout << h_deltaz_eta_data[j][i]->GetEntries() << "\t\t";
        cout << endl;
    } // for i over periods
    cout << "sum:\t\t\t\t";
    for(Int_t j=0; j<number_etabins; j++) 
        cout << h_deltaz_eta_data_sum[j]->GetEntries() << "\t\t";
    
    cout << "\nprph:\t\t\t\t";
    for(Int_t j=0; j<number_etabins; j++) 
        cout << h_deltaz_eta_prph_sum[j]->GetEntries() << "\t\t";
    cout << endl << endl;

    cout << " ---------- data dz in bins of q2 ------------" << endl;
    for(Int_t i=0; i<n_periods; i++) 
    {
        cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
        for(Int_t j=0; j<number_Q2bins; j++)
          cout << h_deltaz_q2_data[j][i]->GetEntries() << "\t\t";
        cout << endl;
    } // for i over periods
    cout << "sum:\t\t\t\t";
    for(Int_t j=0; j<number_Q2bins; j++) 
        cout << h_deltaz_q2_data_sum[j]->GetEntries() << "\t\t";
    cout << "\nprph:\t\t\t\t";
    
    for(Int_t j=0; j<number_Q2bins; j++) 
        cout << h_deltaz_q2_prph_sum[j]->GetEntries() << "\t\t";
    cout << endl << endl;

    cout << " ---------- data dz in bins of x ------------" << endl;
    for(Int_t i=0; i<n_periods; i++) 
    {
        cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
        for(Int_t j=0; j<number_xbins; j++) 
          cout << h_deltaz_x_data[j][i]->GetEntries() << "\t\t";
        cout << endl;
    } // for i over periods
    cout << "sum:\t\t\t\t";
    for(Int_t j=0; j<number_xbins; j++) 
        cout << h_deltaz_x_data_sum[j]->GetEntries() << "\t\t";
    cout << "\nprph:\t\t\t\t";
    for(Int_t j=0; j<number_xbins; j++) 
        cout << h_deltaz_x_prph_sum[j]->GetEntries() << "\t\t";
    cout << endl << endl;

    cout << " ---------- data dz in bins of et_jet ------------" << endl;
    for(Int_t i=0; i<n_periods; i++) 
    {
        cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
        for(Int_t j=0; j<number_et_jetbins; j++)
          cout << h_deltaz_et_jet_data[j][i]->GetEntries() << "\t\t";
     cout << endl;
    } // for i over periods
    cout << "sum:\t\t\t\t";
    for(Int_t j=0; j<number_et_jetbins; j++) 
        cout << h_deltaz_et_jet_data_sum[j]->GetEntries() << "\t\t";
    cout << "\nprph:\t\t\t\t";
    for(Int_t j=0; j<number_et_jetbins; j++) 
        cout << h_deltaz_et_jet_prph_sum[j]->GetEntries() << "\t\t";
    cout << endl << endl;

    cout << " ---------- data dz in bins of eta_jet ------------" << endl;
    for(Int_t i=0; i<n_periods; i++) 
    {
        cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
        for(Int_t j=0; j<number_eta_jetbins; j++) 
          cout << h_deltaz_eta_jet_data[j][i]->GetEntries() << "\t\t";
        cout << endl;
    } // for i over periods
    cout << "sum:\t\t\t\t";
    for(Int_t j=0; j<number_eta_jetbins; j++) 
        cout << h_deltaz_eta_jet_data_sum[j]->GetEntries() << "\t\t";
    cout << "\nprph:\t\t\t\t";
    for(Int_t j=0; j<number_eta_jetbins; j++) 
        cout << h_deltaz_eta_jet_prph_sum[j]->GetEntries() << "\t\t";
    cout << endl << endl;


    cout << " ---------- norad dz in bins of et ------------" << endl;
    for(Int_t i=0; i<n_periods; i++) {
    cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
    for(Int_t j=0; j<number_etbins; j++) {
      cout << h_deltaz_et_norad[j][i]->GetEntries() << "\t\t";
    }
    cout << endl;
    } // for i over periods
    cout << "sum:\t\t\t\t";
    for(Int_t j=0; j<number_etbins; j++) 
    cout << h_deltaz_et_norad_sum[j]->GetEntries() << "\t\t";
    cout << endl << endl;

    cout << " ---------- norad dz in bins of eta ------------" << endl;
    for(Int_t i=0; i<n_periods; i++) {
    cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
    for(Int_t j=0; j<number_etabins; j++) {
      cout << h_deltaz_eta_norad[j][i]->GetEntries() << "\t\t";
    }
    cout << endl;
    } // for i over periods
    cout << "sum:\t\t\t\t";
    for(Int_t j=0; j<number_etabins; j++) 
    cout << h_deltaz_eta_norad_sum[j]->GetEntries() << "\t\t";
    cout << endl << endl;

    cout << " ---------- norad dz in bins of q2 ------------" << endl;
    for(Int_t i=0; i<n_periods; i++) {
    cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
    for(Int_t j=0; j<number_Q2bins; j++) {
      cout << h_deltaz_q2_norad[j][i]->GetEntries() << "\t\t";
    }
    cout << endl;
    } // for i over periods
    cout << "sum:\t\t\t\t";
    for(Int_t j=0; j<number_Q2bins; j++) 
    cout << h_deltaz_q2_norad_sum[j]->GetEntries() << "\t\t";
    cout << endl << endl;

    cout << " ---------- norad dz in bins of x ------------" << endl;
    for(Int_t i=0; i<n_periods; i++) {
    cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
    for(Int_t j=0; j<number_xbins; j++) {
      cout << h_deltaz_x_norad[j][i]->GetEntries() << "\t\t";
    }
    cout << endl;
    } // for i over periods
    cout << "sum:\t\t\t\t";
    for(Int_t j=0; j<number_xbins; j++) 
    cout << h_deltaz_x_norad_sum[j]->GetEntries() << "\t\t";
    cout << endl << endl;

    cout << " ---------- norad dz in bins of et_jet ------------" << endl;
    for(Int_t i=0; i<n_periods; i++) {
    cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
    for(Int_t j=0; j<number_et_jetbins; j++) {
      cout << h_deltaz_et_jet_norad[j][i]->GetEntries() << "\t\t";
    }
    cout << endl;
    } // for i over periods
    cout << "sum:\t\t\t\t";
    for(Int_t j=0; j<number_et_jetbins; j++) 
    cout << h_deltaz_et_jet_norad_sum[j]->GetEntries() << "\t\t";
    cout << endl << endl;

    cout << " ---------- norad dz in bins of eta_jet ------------" << endl;
    for(Int_t i=0; i<n_periods; i++) {
    cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
    for(Int_t j=0; j<number_eta_jetbins; j++) {
      cout << h_deltaz_eta_jet_norad[j][i]->GetEntries() << "\t\t";
    }
    cout << endl;
    } // for i over periods
    cout << "sum:\t\t\t\t";
    for(Int_t j=0; j<number_eta_jetbins; j++) 
    cout << h_deltaz_eta_jet_norad_sum[j]->GetEntries() << "\t\t";
    cout << endl << endl;

    cout << " ---------- rad dz in bins of et ------------" << endl;
    for(Int_t i=0; i<n_periods; i++) {
    cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
    for(Int_t j=0; j<number_etbins; j++) {
      cout << h_deltaz_et_rad[j][i]->GetEntries() << "\t\t";
    }
    cout << endl;
    } // for i over periods
    cout << "sum:\t\t\t\t";
    for(Int_t j=0; j<number_etbins; j++) 
    cout << h_deltaz_et_rad_sum[j]->GetEntries() << "\t\t";
    cout << endl << endl;

    cout << " ---------- rad dz in bins of eta ------------" << endl;
    for(Int_t i=0; i<n_periods; i++) {
    cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
    for(Int_t j=0; j<number_etabins; j++) {
      cout << h_deltaz_eta_rad[j][i]->GetEntries() << "\t\t";
    }
    cout << endl;
    } // for i over periods
    cout << "sum:\t\t\t\t";
    for(Int_t j=0; j<number_etabins; j++) 
    cout << h_deltaz_eta_rad_sum[j]->GetEntries() << "\t\t";
    cout << endl << endl;

    cout << " ---------- rad dz in bins of q2 ------------" << endl;
    for(Int_t i=0; i<n_periods; i++) {
    cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
    for(Int_t j=0; j<number_Q2bins; j++) {
      cout << h_deltaz_q2_rad[j][i]->GetEntries() << "\t\t";
    }
    cout << endl;
    } // for i over periods
    cout << "sum:\t\t\t\t";
    for(Int_t j=0; j<number_Q2bins; j++) 
    cout << h_deltaz_q2_rad_sum[j]->GetEntries() << "\t\t";
    cout << endl << endl;

    cout << " ---------- rad dz in bins of x ------------" << endl;
    for(Int_t i=0; i<n_periods; i++) {
    cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
    for(Int_t j=0; j<number_xbins; j++) {
      cout << h_deltaz_x_rad[j][i]->GetEntries() << "\t\t";
    }
    cout << endl;
    } // for i over periods
    cout << "sum:\t\t\t\t";
    for(Int_t j=0; j<number_xbins; j++) 
    cout << h_deltaz_x_rad_sum[j]->GetEntries() << "\t\t";
    cout << endl << endl;

    cout << " ---------- rad dz in bins of et_jet ------------" << endl;
    for(Int_t i=0; i<n_periods; i++) {
    cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
    for(Int_t j=0; j<number_et_jetbins; j++) {
      cout << h_deltaz_et_jet_rad[j][i]->GetEntries() << "\t\t";
    }
    cout << endl;
    } // for i over periods
    cout << "sum:\t\t\t\t";
    for(Int_t j=0; j<number_et_jetbins; j++) 
    cout << h_deltaz_et_jet_rad_sum[j]->GetEntries() << "\t\t";
    cout << endl << endl;

    cout << " ---------- rad dz in bins of eta_jet ------------" << endl;
    for(Int_t i=0; i<n_periods; i++) {
    cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
    for(Int_t j=0; j<number_eta_jetbins; j++) {
      cout << h_deltaz_eta_jet_rad[j][i]->GetEntries() << "\t\t";
    }
    cout << endl;
    } // for i over periods
    cout << "sum:\t\t\t\t";
    for(Int_t j=0; j<number_eta_jetbins; j++) 
    cout << h_deltaz_eta_jet_rad_sum[j]->GetEntries() << "\t\t";
    cout << endl << endl;


    for(Int_t j=0; j<n_cross; j++) 
    {
        cout << " ---------- Profile  " << s_var[j] << "  ------------" << endl;
        cout << "data_det\tnorad_det\trad_det\tnorad_had\trad_had\tnorad_hd\trad_hd" << endl;
        for(Int_t i=0; i<n_periods; i++) 
        {
          cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t";
          cout << prof_det_data[j][i]->GetEntries() << "\t"
           << prof_det_norad[j][i]->GetEntries() << "\t"
           << prof_det_rad[j][i]->GetEntries() << "\t"
           << prof_had_norad[j][i]->GetEntries() << "\t"
           << prof_had_rad[j][i]->GetEntries() << "\t"
           << prof_hd_norad[j][i]->GetEntries() << "\t"
           << prof_hd_rad[j][i]->GetEntries() << endl;
        }
        cout << "sum:\t\t\t";
        cout << prof_det_data_sum[j]->GetEntries() << "\t"
         << prof_det_norad_sum[j]->GetEntries() << "\t"
         << prof_det_rad_sum[j]->GetEntries() << "\t"
         << prof_had_norad_sum[j]->GetEntries() << "\t"
         << prof_had_rad_sum[j]->GetEntries() << "\t"
         << prof_hd_norad_sum[j]->GetEntries() << "\t"
         << prof_hd_rad_sum[j]->GetEntries() << endl;
        cout << "prph:\t\t\t";
        cout << "det: " << prof_det_prph_sum[j]->GetEntries() << "\thad: " << prof_had_prph_sum[j]->GetEntries() << "\thd: " << prof_hd_prph_sum[j]->GetEntries() << endl;
    }


    for(Int_t j=0; j<n_cross; j++) {
    cout << " ---------- Histogram  " << s_var[j] << "  ------------" << endl;
    cout << "data_det\tnorad_det\trad_det\trad_had\trad_hd" << endl;
    for(Int_t i=0; i<n_periods; i++) {
      cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t";
      cout << h_det_data[j][i]->GetEntries() << "\t"
	   << h_det_norad[j][i]->GetEntries() << "\t"
	   << h_det_rad[j][i]->GetEntries() << "\t"
	   << h_had_rad[j][i]->GetEntries() << "\t"
	   << h_hd_rad[j][i]->GetEntries() << endl;
    }
    cout << "sum:\t\t\t";
    cout << h_det_data_sum[j]->GetEntries() << "\t"
	 << h_det_norad_sum[j]->GetEntries() << "\t"
	 << h_det_rad_sum[j]->GetEntries() << "\t"
	 << h_had_rad_sum[j]->GetEntries() << "\t"
	 << h_hd_rad_sum[j]->GetEntries() << endl;
    cout << "prph:\t\t\t";
    cout << "det: " << h_det_prph_sum[j]->GetEntries() << "\thad: " << h_had_prph_sum[j]->GetEntries() << "\thd: " << h_hd_prph_sum[j]->GetEntries() << endl;
     }  
  }
}

void Hist::PlotAcceptance() 
{
    TH2D* h_window_acc[n_cross];
    h_window_acc[0] = new TH2D("h_window_acc_et", "", 10, 4., 15., 10, 0., 1.4);
    h_window_acc[1] = new TH2D("h_window_acc_eta", "", 10, -0.7, 0.9, 10, 0., 1.4);
    h_window_acc[2] = new TH2D("h_window_acc_q2", "", 10, 4., 350., 10, 0., 1.4);
    h_window_acc[3] = new TH2D("h_window_acc_x", "", 10, 1.5e-4, 0.15, 10, 0., 1.4);
    h_window_acc[4] = new TH2D("h_window_acc_et_jet", "", 10, 2.5, 35., 10, 0., 1.4);
    h_window_acc[5] = new TH2D("h_window_acc_eta_jet", "", 10, -1.5, 1.8, 10, 0., 1.4);

    TCanvas* c_acc  = new TCanvas("c_acc", "Acceptance", 800, 600);
    c_acc->Divide(3, 2);
    make_clean_pads(c_acc, 6, 0, 0);

    sign_window(c_acc->GetPad(1), h_window_acc[0], "E_{T, photon} (GeV)", "Acceptance", "", "middle");
    sign_window(c_acc->GetPad(2), h_window_acc[1], "#eta_{photon}", "Acceptance", "", "middle");
    sign_window(c_acc->GetPad(3), h_window_acc[2], "Q^{2} (GeV^{2})", "Acceptance", "", "middle");
    sign_window(c_acc->GetPad(4), h_window_acc[3], "x", "Acceptance", "", "middle");
    sign_window(c_acc->GetPad(5), h_window_acc[4], "E_{T, jet}", "Acceptance", "", "middle");
    sign_window(c_acc->GetPad(6), h_window_acc[5], "#eta_{jet}", "Acceptance", "", "middle");

    for(Int_t i = 0; i < n_cross; i++)  //    h_acceptance_prph, h_acceptance_rad
    {
        h_acceptance_rad[i] = (TH1D*)h_det_rad_sum[i]->Clone();      //     h_acceptance_rad[i]->Sumw2();
        h_acceptance_rad[i]->SetName(TString("h_acceptance_rad_") + s_var[i]);      
        h_acceptance_rad[i]->Divide(h_had_rad_sum[i]); //?
        h_acceptance_rad[i]->SetMarkerStyle(20);
        h_acceptance_rad[i]->SetMarkerSize(0.7);
        cout << "acceptance " << h_acceptance_rad[i]->GetName() << endl;
        for(Int_t j = 0; j < h_acceptance_rad[i]->GetNbinsX(); j++) //Побиновый вывод на экран
            cout << "bin " << j << ": " << h_acceptance_rad[i]->GetBinContent(j+1) << " = "
                 << h_det_rad_sum[i]->GetBinContent(j+1) << " / "
                 << h_had_rad_sum[i]->GetBinContent(j+1) << endl;

        h_acceptance_prph[i] = (TH1D*)h_det_prph_sum[i]->Clone();//     h_acceptance_prph[i]->Sumw2();
        h_acceptance_prph[i]->SetName(TString("h_acceptance_prph_") + s_var[i]);
        h_acceptance_prph[i]->Divide(h_had_prph_sum[i]);
        h_acceptance_prph[i]->SetMarkerStyle(24);
        h_acceptance_prph[i]->SetMarkerSize(0.7);

        for(Int_t j=0; j<h_acceptance_prph[i]->GetNbinsX(); j++)
            cout << "acceptance " << s_var[i] << " bin " << j << ": " << h_acceptance_prph[i]->GetBinContent(j+1) 
                 << ", det = " << h_det_prph_sum[i]->GetBinContent(j+1) << ", had = " << h_had_prph_sum[i]->GetBinContent(j+1) << endl
                 << "acceptance correction: " << 1./h_acceptance_prph[i]->GetBinContent(j+1) << endl;
     
    }

    TLegend *leg_acc = new TLegend(0.2, 0.2, 0.6, 0.4);
    leg_acc->SetFillColor(0);
    leg_acc->SetBorderSize(0);
    leg_acc->AddEntry(h_acceptance_rad[0], "LL photons", "p");// P: draw polymarker associated with TAttMarker if obj inherits from TAttMarker
    leg_acc->AddEntry(h_acceptance_prph[0], "QQ photons", "p");  
    
    for(Int_t i = 0; i < n_cross; i++)//Draw acceptance
    {
        c_acc->GetPad(i+1)->cd();
        if (i==2 || i==3 || i==4) c_acc->GetPad(i+1)->SetLogx();
        h_window_acc[i]->DrawClone();
        h_acceptance_rad[i]->DrawClone("P E1 X0 SAME");
        /*P  : Draw current marker at each bin except empty bins.
        //E1 : Draw error bars with perpendicular lines at the edges.
        //X0 : When used with one of the "E" option, it suppress the error bar along X as gStyle->SetErrorX(0) would do.
        //https://root.cern.ch/root/html/THistPainter.html
         */
        
        cout << "before shift: " << h_acceptance_prph[i]->GetXaxis()->GetXmin() << " " 
                << h_acceptance_prph[i]->GetXaxis()->GetXmax() << " first bin center: " 
                << h_acceptance_prph[i]->GetBinCenter(1) <<endl;
        
        Double_t xmin = h_acceptance_prph[i]->GetXaxis()->GetXmin(),
                 xmax = h_acceptance_prph[i]->GetXaxis()->GetXmax();
        Double_t deltax = xmax-xmin;
        h_acceptance_prph[i]->GetXaxis()->SetLimits(xmin + 0.9 * deltax, xmax + 0.9 * deltax);
        /*
        h_acceptance_prph[i]->GetXaxis()->SetXmin(xmin + 0.9*deltax);
        h_acceptance_prph[i]->GetXaxis()->SetXmax(xmax + 0.9*deltax);
         */
        cout << "after shift: " << h_acceptance_prph[i]->GetXaxis()->GetXmin() << " " 
                << h_acceptance_prph[i]->GetXaxis()->GetXmax() << " first bin center: " 
                << h_acceptance_prph[i]->GetBinCenter(1)<< endl;
        h_acceptance_prph[i]->DrawClone("P E X0 SAME");
        
        if (i==3) leg_acc->Draw();
    }
    
    c_acc->Print("acceptance.eps");
    c_acc->Print("acceptance.png");

}

void Hist::PlotPurity() 
{
    TH2D* h_window_pur[n_cross];
    h_window_pur[0] = new TH2D("h_window_pur_et", "", 10, 4., 15., 10, 0., 1.4);
    h_window_pur[1] = new TH2D("h_window_pur_eta", "", 10, -0.7, 0.9, 10, 0., 1.4);
    h_window_pur[2] = new TH2D("h_window_pur_q2", "", 10, 4., 350., 10, 0., 1.4);
    h_window_pur[3] = new TH2D("h_window_pur_x", "", 10, 1.5e-4, 0.15, 10, 0., 1.4);
    h_window_pur[4] = new TH2D("h_window_pur_et_jet", "", 10, 2.5, 35., 10, 0., 1.4);
    h_window_pur[5] = new TH2D("h_window_pur_eta_jet", "", 10, -1.5, 1.8, 10, 0., 1.4);
    
    TCanvas* c_pur  = new TCanvas("c_pur", "Purity", 800, 600);    
    c_pur->Divide(3, 2);
    make_clean_pads(c_pur, 6, 0, 0);
    
    sign_window(c_pur->GetPad(1), h_window_pur[0], "E_{T, photon} (GeV)", "Purity", "", "middle");
    sign_window(c_pur->GetPad(2), h_window_pur[1], "#eta_{photon}", "Purity", "", "middle");
    sign_window(c_pur->GetPad(3), h_window_pur[2], "Q^{2} (GeV^{2})", "Purity", "", "middle");
    sign_window(c_pur->GetPad(4), h_window_pur[3], "x", "Purity", "", "middle");
    sign_window(c_pur->GetPad(5), h_window_pur[4], "E_{T, jet}", "Purity", "", "middle");
    sign_window(c_pur->GetPad(6), h_window_pur[5], "#eta_{jet}", "Purity", "", "middle");
    
    for(Int_t i = 0; i < n_cross; i++) // Строятся h_purity_rad h_purity_prph
    {
        h_purity_rad[i] = (TH1D*)h_hd_rad_sum[i]->Clone(); //? h_purity_rad[i]->Sumw2();
        h_purity_rad[i]->SetName(TString("h_purity_rad_") + s_var[i]);      
        h_purity_rad[i]->Divide(h_det_rad_sum[i]);
        h_purity_rad[i]->SetMarkerStyle(20);
        h_purity_rad[i]->SetMarkerSize(0.7);
        cout << "purity " << h_purity_rad[i]->GetName() << endl;
        for(Int_t j = 0; j < h_purity_rad[i]->GetNbinsX(); j++)
            cout << "bin " << j << ": " << h_det_rad_sum[i]->GetBinContent(j+1) << " "
               << h_had_rad_sum[i]->GetBinContent(j+1) << endl;
            //	 cout << h_purity_rad[i] << GetBinContent(j+1) << endl;

        h_purity_prph[i] = (TH1D*)h_hd_prph_sum[i]->Clone();//     h_purity_prph[i]->Sumw2();
        h_purity_prph[i]->SetName(TString("h_purity_prph_") + s_var[i]);
        h_purity_prph[i]->Divide(h_det_prph_sum[i]);
        h_purity_prph[i]->SetMarkerStyle(24);
        h_purity_prph[i]->SetMarkerSize(0.7);
        
        for(Int_t j = 0; j < h_purity_prph[i]->GetNbinsX(); j++)
            cout << "purity " << s_var[i] << " bin " << j << ": " << h_purity_prph[i]->GetBinContent(j+1) 
             << ", det = " << h_det_prph_sum[i]->GetBinContent(j+1) << ", had = " << h_had_prph_sum[i]->GetBinContent(j+1) << endl
             << "purity correction: " << 1./h_purity_prph[i]->GetBinContent(j+1) << endl;
    }
    
    TLegend *leg_pur = new TLegend(0.2, 0.2, 0.6, 0.4);
    leg_pur->SetFillColor(0);
    leg_pur->SetBorderSize(0);
    leg_pur->AddEntry(h_purity_rad[0], "LL photons", "p");
    leg_pur->AddEntry(h_purity_prph[0], "QQ photons", "p");  
    for(Int_t i = 0; i < n_cross; i++)
    {
        c_pur->GetPad(i+1)->cd();
        if(i==2 || i==3 || i==4) c_pur->GetPad(i+1)->SetLogx();
        h_window_pur[i]->DrawClone();
        h_purity_rad[i]->DrawClone("P E1 X0 SAME");
        // Shift for h_purity_prph
        cout << "before shift: " << h_purity_prph[i]->GetXaxis()->GetXmin() << " " << h_purity_prph[i]->GetXaxis()->GetXmax() << " first bin center: " << h_purity_prph[i]->GetBinCenter(1) <<endl;
        Double_t xmin = h_purity_prph[i]->GetXaxis()->GetXmin(),
                 xmax = h_purity_prph[i]->GetXaxis()->GetXmax();
        Double_t deltax = xmax - xmin;
        h_purity_prph[i]->GetXaxis()->SetLimits(xmin + 0.9*deltax, xmax+0.9*deltax);
        cout << "after shift: " << h_purity_prph[i]->GetXaxis()->GetXmin() << " " << h_purity_prph[i]->GetXaxis()->GetXmax() << " first bin center: " << h_purity_prph[i]->GetBinCenter(1)<< endl;
        h_purity_prph[i]->DrawClone("P E X0 SAME");
        cout << "after drawing: " << h_purity_prph[i]->GetXaxis()->GetXmin() << " " << h_purity_prph[i]->GetXaxis()->GetXmax() << " first bin center: " << h_purity_prph[i]->GetBinCenter(1)<< endl;
        if(i==3) leg_pur->Draw();
    }
    c_pur->Print("purity.eps");
    c_pur->Print("purity.png");

}

void Hist::PlotFitInBinsOfCrossSec() {

    /*020715 ПЕРЕПИСАТЬ ЧЕРЕЗ ФУНКЦИЮ/КЛАСС*/
    ///////////////////////////////////////////////////////
    //
    //          dz in bins of Et
    //
    ///////////////////////////////////////////////////////
    TH2D* h_window_fit_et[number_etbins];
    Double_t ymax_et[number_etbins] = {500., 250., 150., 120.};
    for(Int_t i = 0; i < number_etbins; i++)
    {
        TString s; 
        s.Form("h_window_fit_et_%i", i); 
        h_window_fit_et[i] = new TH2D(s, "", 10, 0., 1.5, 10, 0., ymax_et[i]);
    }

    TPaveText *pave_et[number_etbins]; //A PaveText is a Pave (see TPave) with text
    TString s1_et[number_etbins], s2_et[number_etbins], s3_et[number_etbins], s4_et[number_etbins];
    /*промежуток по Ет*/          /*параметр фита*/     /*пром-ок фита*/           /*нормированный хи-кв.*/
    TText *t1_et[number_etbins], *t2_et[number_etbins], *t3_et[number_etbins], *t4_et[number_etbins];

    /*Cоздаем подписи в квадратах*/
    for(Int_t i=0; i < number_etbins; i++) 
    {
        pave_et[i] = new TPaveText(0.5, 0.5, 0.9, 0.9, "NDC");
        pave_et[i]->SetFillColor(0);
        pave_et[i]->SetBorderSize(0);
        s1_et[i].Form("%.0f GeV < E_{T, photon} < %.0f GeV", et_bin[i], et_bin[i+1]);
        s2_et[i].Form("Pr. phot. fraction: %.2f #pm %.2f", param_et[i], param_err_et[i]);//+-
        s3_et[i].Form("fit range: bins %i to %i", left_et[i], right_et[i]); 
        s4_et[i].Form("#chi^{2}/%i = %.2f", dof_et[i], chi2_et[i]);
        t1_et[i] = pave_et[i]->AddText(s1_et[i]); t1_et[i]->SetTextSize(0.045);
        t2_et[i] = pave_et[i]->AddText(s2_et[i]); t2_et[i]->SetTextSize(0.045);
        t3_et[i] = pave_et[i]->AddText(s3_et[i]); t3_et[i]->SetTextSize(0.045);
        t4_et[i] = pave_et[i]->AddText(s4_et[i]); t4_et[i]->SetTextSize(0.045);
    }

    TCanvas *c_dz_et = new TCanvas("c_dz_et", "deltaZ in bins of Et", 800, 600);
    c_dz_et->Divide(2, 2);
    make_clean_pads(c_dz_et, 4, 0, 0);
    for(Int_t i = 0; i < number_etbins; i++) 
    {
        sign_window(c_dz_et->GetPad(i+1), h_window_fit_et[i], "#delta z", "Events", "", "middle");
        c_dz_et->GetPad(i+1)->cd();
        cout << "draw " << i << endl;
        cout << "et bin# " << i << " " << h_deltaz_et_data_sum[i]->Integral() << " " << h_deltaz_et_res[i]->Integral() << " " 
             << h_deltaz_et_prph_sum[i]->Integral() << " " 
             << h_deltaz_et_rad_sum[i]->Integral() << " " << h_deltaz_et_norad_sum[i]->Integral() << endl;    
        h_window_fit_et[i]->Draw();
        h_deltaz_et_res[i]->Draw("HIST SAME");
        h_deltaz_et_res[i]->Draw("E X0 F SAME");
        h_deltaz_et_rad_sum[i]->Draw("HIST SAME");
        h_deltaz_et_rad_sum[i]->Draw("E X0 F SAME");
        h_deltaz_et_norad_sum[i]->Draw("HIST SAME");
        h_deltaz_et_norad_sum[i]->Draw("E X0 F SAME");
        h_deltaz_et_prph_sum[i]->Draw("HIST SAME");
        h_deltaz_et_prph_sum[i]->Draw("E X0 F SAME");
        //    h_deltaz_et_photon_sum[i]->Draw("HIST SAME");
        cout << "dz before shift: " << h_deltaz_et_data_sum[i]->GetXaxis()->GetXmin() 
                << " " << h_deltaz_et_data_sum[i]->GetXaxis()->GetXmax() 
                << " first bin center: " << h_deltaz_et_data_sum[i]->GetBinCenter(1) <<endl;
        Double_t xmin = h_deltaz_et_data_sum[i]->GetXaxis()->GetXmin();
        Double_t xmax = h_deltaz_et_data_sum[i]->GetXaxis()->GetXmax();
        Double_t deltax = xmax-xmin;
        h_deltaz_et_data_sum[i]->GetXaxis()->SetLimits(xmin + 0.01*deltax, xmax+0.01*deltax);
        cout << "dz after shift: " << h_deltaz_et_data_sum[i]->GetXaxis()->GetXmin() << " " 
                << h_deltaz_et_data_sum[i]->GetXaxis()->GetXmax() 
                << " first bin center: " << h_deltaz_et_data_sum[i]->GetBinCenter(1) <<endl;
        h_deltaz_et_data_sum[i]->Draw("P E X0 SAME");//https://root.cern.ch/root/html/THistPainter.html
        c_dz_et->GetPad(i+1)->RedrawAxis();
        pave_et[i]->Draw();
    }
    c_dz_et->Print("c_dz_et.eps");  
    c_dz_et->Print("c_dz_et.png");  

    ///////////////////////////////////////////////////////
    //
    //          dz in bins of Eta
    //
    ///////////////////////////////////////////////////////
    TH2D* h_window_fit_eta[number_etabins];
    Double_t ymax_eta[number_etabins] = {300., 280., 260., 200.};
    for(Int_t i=0; i<number_etabins; i++)
    {
        TString s; 
        s.Form("h_window_fit_eta_%i", i); 
        h_window_fit_eta[i] = new TH2D(s, "", 10, 0., 1.5, 10, 0., ymax_eta[i]);
    }

    TPaveText *pave_eta[number_etabins];
    TString s1_eta[number_etabins], s2_eta[number_etabins], s3_eta[number_etabins], s4_eta[number_etabins];
    TText *t1_eta[number_etabins], *t2_eta[number_etabins], *t3_eta[number_etabins], *t4_eta[number_etabins];

    for(Int_t i=0; i<number_etabins; i++) 
    {
        pave_eta[i] = new TPaveText(0.5, 0.5, 0.9, 0.9, "NDC");
        pave_eta[i]->SetFillColor(0);
        pave_eta[i]->SetBorderSize(0);
        s1_eta[i].Form("%.1f < #eta_{photon} < %.1f", eta_bin_crosssec[i], eta_bin_crosssec[i+1]);
        s2_eta[i].Form("Pr. phot. fraction: %.2f #pm %.2f", param_eta[i], param_err_eta[i]);
        s3_eta[i].Form("fit range: bins %i to %i", left_eta[i], right_eta[i]); 
        s4_eta[i].Form("#chi^{2}/%i = %.2f", dof_eta[i], chi2_eta[i]);
        t1_eta[i] = pave_eta[i]->AddText(s1_eta[i]); t1_eta[i]->SetTextSize(0.045);
        t2_eta[i] = pave_eta[i]->AddText(s2_eta[i]); t2_eta[i]->SetTextSize(0.045);
        t3_eta[i] = pave_eta[i]->AddText(s3_eta[i]); t3_eta[i]->SetTextSize(0.045);
        t4_eta[i] = pave_eta[i]->AddText(s4_eta[i]); t4_eta[i]->SetTextSize(0.045);
    }

    TCanvas *c_dz_eta = new TCanvas("c_dz_eta", "deltaZ in bins of Eta", 800, 600);
    c_dz_eta->Divide(2, 2);
    make_clean_pads(c_dz_eta, 4, 0, 0);
    for(Int_t i=0; i<number_etabins; i++) 
    {
        sign_window(c_dz_eta->GetPad(i+1), h_window_fit_eta[i], "#delta z", "Events", "", "middle");
        c_dz_eta->GetPad(i+1)->cd();
        cout << "draw " << i << endl;
        cout << "eta bin# " << i << " " << h_deltaz_eta_data_sum[i]->Integral() << " " << h_deltaz_eta_res[i]->Integral() << " " 
             << h_deltaz_eta_prph_sum[i]->Integral() << " " 
             << h_deltaz_eta_rad_sum[i]->Integral() << " " << h_deltaz_eta_norad_sum[i]->Integral() << endl;    
        h_window_fit_eta[i]->Draw();
        h_deltaz_eta_res[i]->Draw("HIST SAME");
        h_deltaz_eta_res[i]->Draw("E X0 F SAME");
        h_deltaz_eta_rad_sum[i]->Draw("HIST SAME");
        h_deltaz_eta_norad_sum[i]->Draw("HIST SAME");
        h_deltaz_eta_prph_sum[i]->Draw("HIST SAME");
        Double_t xmin = h_deltaz_eta_data_sum[i]->GetXaxis()->GetXmin();
        Double_t xmax = h_deltaz_eta_data_sum[i]->GetXaxis()->GetXmax();
        Double_t deltax = xmax-xmin;
        h_deltaz_eta_data_sum[i]->GetXaxis()->SetLimits(xmin + 0.01*deltax, xmax+0.01*deltax);
        h_deltaz_eta_data_sum[i]->Draw("P E X0 SAME");
        c_dz_eta->GetPad(i+1)->RedrawAxis();
        pave_eta[i]->Draw();
    }
    c_dz_eta->Print("c_dz_eta.eps");  
    c_dz_eta->Print("c_dz_eta.png");  

    ///////////////////////////////////////////////////////
    //
    //          dz in bins of Q2
    //
    ///////////////////////////////////////////////////////
    TH2D* h_window_fit_q2[number_Q2bins];
    Double_t ymax_q2[number_Q2bins] = {280., 260., 200., 140., 90.};
    //  Double_t ymax_q2[number_Q2bins] = {450., 260., 200., 100.};
    //  Double_t ymax_q2[number_Q2bins] = {250., 250., 250., 250.};
    for(Int_t i=0; i<number_Q2bins; i++)
    {
        TString s; s.Form("h_window_fit_q2_%i", i); 
        h_window_fit_q2[i] = new TH2D(s, "", 10, 0., 1.5, 10, 0., ymax_q2[i]);
    }

    TPaveText *pave_q2[number_Q2bins];
    TString s1_q2[number_Q2bins], s2_q2[number_Q2bins], s3_q2[number_Q2bins], s4_q2[number_Q2bins];
    TText *t1_q2[number_Q2bins], *t2_q2[number_Q2bins], *t3_q2[number_Q2bins], *t4_q2[number_Q2bins];

    for(Int_t i=0; i<number_Q2bins; i++) 
    {
        pave_q2[i] = new TPaveText(0.5, 0.5, 0.9, 0.9, "NDC");
        pave_q2[i]->SetFillColor(0);
        pave_q2[i]->SetBorderSize(0);
        s1_q2[i].Form("%.0f GeV^{2} < Q^{2} < %.0f GeV^{2}", Q2_bin[i], Q2_bin[i+1]);
        s2_q2[i].Form("Pr. phot. fraction: %.2f #pm %.2f", param_q2[i], param_err_q2[i]);
        s3_q2[i].Form("fit range: bins %i to %i", left_q2[i], right_q2[i]); 
        s4_q2[i].Form("#chi^{2}/%i = %.2f", dof_q2[i], chi2_q2[i]);
        t1_q2[i] = pave_q2[i]->AddText(s1_q2[i]); t1_q2[i]->SetTextSize(0.045);
        t2_q2[i] = pave_q2[i]->AddText(s2_q2[i]); t2_q2[i]->SetTextSize(0.045);
        t3_q2[i] = pave_q2[i]->AddText(s3_q2[i]); t3_q2[i]->SetTextSize(0.045);
        t4_q2[i] = pave_q2[i]->AddText(s4_q2[i]); t4_q2[i]->SetTextSize(0.045);
    }

    TCanvas *c_dz_q2 = new TCanvas("c_dz_q2", "deltaZ in bins of Q2", 1000, 600);
    c_dz_q2->Divide(3, 2);
    make_clean_pads(c_dz_q2, 6, 0, 0);
    for(Int_t i=0; i<number_Q2bins; i++) 
    {
        sign_window(c_dz_q2->GetPad(i+1), h_window_fit_q2[i], "#delta z", "Events", "", "middle");
        c_dz_q2->GetPad(i+1)->cd();
        cout << "draw " << i << endl;
        cout << "q2 bin# " << i << " " << h_deltaz_q2_data_sum[i]->Integral() << " " << h_deltaz_q2_res[i]->Integral() << " " 
             << h_deltaz_q2_prph_sum[i]->Integral() << " " 
             << h_deltaz_q2_rad_sum[i]->Integral() << " " << h_deltaz_q2_norad_sum[i]->Integral() << endl;    
        h_window_fit_q2[i]->Draw();
        h_deltaz_q2_res[i]->Draw("HIST SAME");
        h_deltaz_q2_res[i]->Draw("E X0 F SAME");
        h_deltaz_q2_rad_sum[i]->Draw("HIST SAME");
        h_deltaz_q2_norad_sum[i]->Draw("HIST SAME");
        h_deltaz_q2_prph_sum[i]->Draw("HIST SAME");
        Double_t xmin = h_deltaz_q2_data_sum[i]->GetXaxis()->GetXmin();
        Double_t xmax = h_deltaz_q2_data_sum[i]->GetXaxis()->GetXmax();
        Double_t deltax = xmax-xmin;
        h_deltaz_q2_data_sum[i]->GetXaxis()->SetLimits(xmin + 0.01*deltax, xmax+0.01*deltax);
        h_deltaz_q2_data_sum[i]->Draw("P E X0 SAME");
        c_dz_q2->GetPad(i+1)->RedrawAxis();
        pave_q2[i]->Draw();
        cout << i << " Q2" << endl;
    }
    c_dz_q2->Print("c_dz_q2.eps");  
    c_dz_q2->Print("c_dz_q2.png");  

    ///////////////////////////////////////////////////////
    //
    //          dz in bins of X
    //
    ///////////////////////////////////////////////////////
    TH2D* h_window_fit_x[number_xbins];
    Double_t ymax_x[number_xbins] = {350., 300., 250., 50.};
    //  Double_t ymax_x[number_xbins] = {300., 300., 300., 300.};
    for(Int_t i=0; i<number_xbins; i++)
    {
        TString s; s.Form("h_window_fit_x_%i", i); 
        h_window_fit_x[i] = new TH2D(s, "", 10, 0., 1.5, 10, 0., ymax_x[i]);
    }

    TPaveText *pave_x[number_xbins];
    TString s1_x[number_xbins], s2_x[number_xbins], s3_x[number_xbins], s4_x[number_xbins];
    TText *t1_x[number_xbins], *t2_x[number_xbins], *t3_x[number_xbins], *t4_x[number_xbins];

    for(Int_t i=0; i<number_xbins; i++) 
    {
        pave_x[i] = new TPaveText(0.5, 0.5, 0.9, 0.9, "NDC");
        pave_x[i]->SetFillColor(0);
        pave_x[i]->SetBorderSize(0);
        s1_x[i].Form("%.4f < x < %.4f", x_bin[i], x_bin[i+1]);
        s2_x[i].Form("Pr. phot. fraction: %.2f #pm %.2f", param_x[i], param_err_x[i]);
        s3_x[i].Form("fit range: bins %i to %i", left_x[i], right_x[i]); 
        s4_x[i].Form("#chi^{2}/%i = %.2f", dof_x[i], chi2_x[i]);
        t1_x[i] = pave_x[i]->AddText(s1_x[i]); t1_x[i]->SetTextSize(0.045);
        t2_x[i] = pave_x[i]->AddText(s2_x[i]); t2_x[i]->SetTextSize(0.045);
        t3_x[i] = pave_x[i]->AddText(s3_x[i]); t3_x[i]->SetTextSize(0.045);
        t4_x[i] = pave_x[i]->AddText(s4_x[i]); t4_x[i]->SetTextSize(0.045);
    }

    TCanvas *c_dz_x = new TCanvas("c_dz_x", "deltaZ in bins of X", 800, 600);
    c_dz_x->Divide(2, 2);
    make_clean_pads(c_dz_x, 4, 0, 0);
    for(Int_t i=0; i<number_xbins; i++) 
    {
        sign_window(c_dz_x->GetPad(i+1), h_window_fit_x[i], "#delta z", "Events", "", "middle");
        c_dz_x->GetPad(i+1)->cd();
        cout << "draw " << i << endl;
        cout << "x bin# " << i << " " << h_deltaz_x_data_sum[i]->Integral() << " " << h_deltaz_x_res[i]->Integral() << " " 
             << h_deltaz_x_prph_sum[i]->Integral() << " " 
             << h_deltaz_x_rad_sum[i]->Integral() << " " << h_deltaz_x_norad_sum[i]->Integral() << endl;    
        h_window_fit_x[i]->Draw();
        h_deltaz_x_res[i]->Draw("HIST SAME");
        h_deltaz_x_res[i]->Draw("E X0 F SAME");
        h_deltaz_x_rad_sum[i]->Draw("HIST SAME");
        h_deltaz_x_norad_sum[i]->Draw("HIST SAME");
        h_deltaz_x_prph_sum[i]->Draw("HIST SAME");
        Double_t xmin = h_deltaz_x_data_sum[i]->GetXaxis()->GetXmin();
        Double_t xmax = h_deltaz_x_data_sum[i]->GetXaxis()->GetXmax();
        Double_t deltax = xmax-xmin;
        h_deltaz_x_data_sum[i]->GetXaxis()->SetLimits(xmin + 0.01*deltax, xmax+0.01*deltax);
        h_deltaz_x_data_sum[i]->Draw("P E X0 SAME");
        c_dz_x->GetPad(i+1)->RedrawAxis();
        pave_x[i]->Draw();
    }
    c_dz_x->Print("c_dz_x.eps");  
    c_dz_x->Print("c_dz_x.png");  

    ///////////////////////////////////////////////////////
    //
    //          dz in bins of Et_Jet
    //
    ///////////////////////////////////////////////////////
    TH2D* h_window_fit_et_jet[number_et_jetbins];
    Double_t ymax_et_jet[number_et_jetbins] = {400., 250., 200., 200., 200., 200.};
    //  Double_t ymax_et_jet[number_et_jetbins] = {400., 400., 400., 400.};
    for(Int_t i=0; i<number_et_jetbins; i++)
    {
        TString s; s.Form("h_window_fit_et_jet_%i", i); 
        h_window_fit_et_jet[i] = new TH2D(s, "", 10, 0., 1.5, 10, 0., ymax_et_jet[i]);
    }

    TPaveText *pave_et_jet[number_et_jetbins];
    TString s1_et_jet[number_et_jetbins], s2_et_jet[number_et_jetbins], s3_et_jet[number_et_jetbins], s4_et_jet[number_et_jetbins];
    TText *t1_et_jet[number_et_jetbins], *t2_et_jet[number_et_jetbins], *t3_et_jet[number_et_jetbins], *t4_et_jet[number_et_jetbins];

    for(Int_t i=0; i<number_et_jetbins; i++) 
    {
        pave_et_jet[i] = new TPaveText(0.5, 0.5, 0.9, 0.9, "NDC");
        pave_et_jet[i]->SetFillColor(0);
        pave_et_jet[i]->SetBorderSize(0);
        s1_et_jet[i].Form("%.1f < E_{T, jet} < %.1f", et_jet_bin[i], et_jet_bin[i+1]);
        s2_et_jet[i].Form("Pr. phot. fraction: %.2f #pm %.2f", param_et_jet[i], param_err_et_jet[i]);
        s3_et_jet[i].Form("fit range: bins %i to %i", left_et_jet[i], right_et_jet[i]); 
        s4_et_jet[i].Form("#chi^{2}/%i = %.2f", dof_et_jet[i], chi2_et_jet[i]);
        t1_et_jet[i] = pave_et_jet[i]->AddText(s1_et_jet[i]); t1_et_jet[i]->SetTextSize(0.045);
        t2_et_jet[i] = pave_et_jet[i]->AddText(s2_et_jet[i]); t2_et_jet[i]->SetTextSize(0.045);
        t3_et_jet[i] = pave_et_jet[i]->AddText(s3_et_jet[i]); t3_et_jet[i]->SetTextSize(0.045);
        t4_et_jet[i] = pave_et_jet[i]->AddText(s4_et_jet[i]); t4_et_jet[i]->SetTextSize(0.045);
    }

    TCanvas *c_dz_et_jet = new TCanvas("c_dz_et_jet", "deltaZ in bins of Et_Jet", 800, 600);
    c_dz_et_jet->Divide(3, 2);
    make_clean_pads(c_dz_et_jet, 6, 0, 0);
    for(Int_t i=0; i<number_et_jetbins; i++) 
    {
        sign_window(c_dz_et_jet->GetPad(i+1), h_window_fit_et_jet[i], "#delta z", "Events", "", "middle");
        c_dz_et_jet->GetPad(i+1)->cd();
        h_window_fit_et_jet[i]->GetYaxis()->SetRangeUser(0., 1.2*h_deltaz_et_jet_data_sum[i]->GetMaximum());
        cout << "draw " << i << endl;
        cout << "et_jet bin# " << i << " " << h_deltaz_et_jet_data_sum[i]->Integral() << " " << h_deltaz_et_jet_res[i]->Integral() << " " 
             << h_deltaz_et_jet_prph_sum[i]->Integral() << " " 
             << h_deltaz_et_jet_rad_sum[i]->Integral() << " " << h_deltaz_et_jet_norad_sum[i]->Integral() << endl;    
        h_window_fit_et_jet[i]->Draw();
        h_deltaz_et_jet_res[i]->Draw("HIST SAME");
        h_deltaz_et_jet_res[i]->Draw("E X0 F SAME");
        h_deltaz_et_jet_rad_sum[i]->Draw("HIST SAME");
        h_deltaz_et_jet_norad_sum[i]->Draw("HIST SAME");
        h_deltaz_et_jet_prph_sum[i]->Draw("HIST SAME");
        Double_t xmin = h_deltaz_et_jet_data_sum[i]->GetXaxis()->GetXmin();
        Double_t xmax = h_deltaz_et_jet_data_sum[i]->GetXaxis()->GetXmax();
        Double_t deltax = xmax-xmin;
        h_deltaz_et_jet_data_sum[i]->GetXaxis()->SetLimits(xmin + 0.01*deltax, xmax+0.01*deltax);
        h_deltaz_et_jet_data_sum[i]->Draw("P E X0 SAME");
        c_dz_et_jet->GetPad(i+1)->RedrawAxis();
        pave_et_jet[i]->Draw();
    }
    c_dz_et_jet->Print("c_dz_et_jet.eps");  
    c_dz_et_jet->Print("c_dz_et_jet.png");  

    ///////////////////////////////////////////////////////
    //
    //          dz in bins of Eta_Jet
    //
    ///////////////////////////////////////////////////////
    TH2D* h_window_fit_eta_jet[number_eta_jetbins];
    Double_t ymax_eta_jet[number_eta_jetbins] = {150., 250., 300., 370.};
    for(Int_t i=0; i<number_eta_jetbins; i++)
    {
        TString s; s.Form("h_window_fit_eta_jet_%i", i); 
        h_window_fit_eta_jet[i] = new TH2D(s, "", 10, 0., 1.5, 10, 0., ymax_eta_jet[i]);
    }

    TPaveText *pave_eta_jet[number_eta_jetbins];
    TString s1_eta_jet[number_eta_jetbins], s2_eta_jet[number_eta_jetbins], s3_eta_jet[number_eta_jetbins], s4_eta_jet[number_eta_jetbins];
    TText *t1_eta_jet[number_eta_jetbins], *t2_eta_jet[number_eta_jetbins], *t3_eta_jet[number_eta_jetbins], *t4_eta_jet[number_eta_jetbins];

    for(Int_t i=0; i<number_eta_jetbins; i++) 
    {
        pave_eta_jet[i] = new TPaveText(0.5, 0.5, 0.9, 0.9, "NDC");
        pave_eta_jet[i]->SetFillColor(0);
        pave_eta_jet[i]->SetBorderSize(0);
        s1_eta_jet[i].Form("%.1f < #eta_{jet} < %.1f", eta_jet_bin[i], eta_jet_bin[i+1]);
        s2_eta_jet[i].Form("Pr. phot. fraction: %.2f #pm %.2f", param_eta_jet[i], param_err_eta_jet[i]);
        s3_eta_jet[i].Form("fit range: bins %i to %i", left_eta_jet[i], right_eta_jet[i]); 
        s4_eta_jet[i].Form("#chi^{2}/%i = %.2f", dof_eta_jet[i], chi2_eta_jet[i]);
        t1_eta_jet[i] = pave_eta_jet[i]->AddText(s1_eta_jet[i]); t1_eta_jet[i]->SetTextSize(0.045);
        t2_eta_jet[i] = pave_eta_jet[i]->AddText(s2_eta_jet[i]); t2_eta_jet[i]->SetTextSize(0.045);
        t3_eta_jet[i] = pave_eta_jet[i]->AddText(s3_eta_jet[i]); t3_eta_jet[i]->SetTextSize(0.045);
        t4_eta_jet[i] = pave_eta_jet[i]->AddText(s4_eta_jet[i]); t4_eta_jet[i]->SetTextSize(0.045);
    }

    TCanvas *c_dz_eta_jet = new TCanvas("c_dz_eta_jet", "deltaZ in bins of Eta_Jet", 800, 600);
    c_dz_eta_jet->Divide(2, 2);
    make_clean_pads(c_dz_eta_jet, 4, 0, 0);
    for(Int_t i=0; i<number_eta_jetbins; i++) 
    {
        sign_window(c_dz_eta_jet->GetPad(i+1), h_window_fit_eta_jet[i], "#delta z", "Events", "", "middle");
        c_dz_eta_jet->GetPad(i+1)->cd();
        h_window_fit_eta_jet[i]->GetYaxis()->SetRangeUser(0., 1.2*h_deltaz_eta_jet_data_sum[i]->GetMaximum());
        cout << "draw " << i << endl;
        cout << "eta_jet bin# " << i << " " << h_deltaz_eta_jet_data_sum[i]->Integral() << " " << h_deltaz_eta_jet_res[i]->Integral() << " " 
             << h_deltaz_eta_jet_prph_sum[i]->Integral() << " " 
             << h_deltaz_eta_jet_rad_sum[i]->Integral() << " " << h_deltaz_eta_jet_norad_sum[i]->Integral() << endl;    
        h_window_fit_eta_jet[i]->Draw();
        h_deltaz_eta_jet_res[i]->Draw("HIST SAME");
        h_deltaz_eta_jet_res[i]->Draw("E X0 F SAME");
        h_deltaz_eta_jet_rad_sum[i]->Draw("HIST SAME");
        h_deltaz_eta_jet_norad_sum[i]->Draw("HIST SAME");
        h_deltaz_eta_jet_prph_sum[i]->Draw("HIST SAME");
        Double_t xmin = h_deltaz_eta_jet_data_sum[i]->GetXaxis()->GetXmin();
        Double_t xmax = h_deltaz_eta_jet_data_sum[i]->GetXaxis()->GetXmax();
        Double_t deltax = xmax-xmin;
        h_deltaz_eta_jet_data_sum[i]->GetXaxis()->SetLimits(xmin + 0.01*deltax, xmax+0.01*deltax);
        h_deltaz_eta_jet_data_sum[i]->Draw("P E X0 SAME");
        c_dz_eta_jet->GetPad(i+1)->RedrawAxis();
        pave_eta_jet[i]->Draw();
    }
    c_dz_eta_jet->Print("c_dz_eta_jet.eps");  
    c_dz_eta_jet->Print("c_dz_eta_jet.png");  


    cout << "Fit in different bins has been drawed" << endl;
    //  delete[] t1;
    //  delete[] pave_et;
    //  delete[] pave_eta;
    //  delete[] pave_q2;
    //  delete[] pave_x;
    //  delete[] h_window_fit_et;
    //  delete[] h_window_fit_eta;
    //  delete[] h_window_fit_q2;
    //  delete[] h_window_fit_x;
    //  delete c_dz_et;
    //  delete c_dz_eta;
    //  delete c_dz_q2;
    //  delete c_dz_x;
    cout << "exiting..." << endl;
}


