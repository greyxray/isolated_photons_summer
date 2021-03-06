//version before work on fits
#include "hist.h"
#include "hist_plot_box.c"
#include "hist_apply_hadronisation_corrections.c"
#include "hist_plot_cross_sec.c"
#include "hist_calculate_cross_sec.c"
#include "hist_compare1st2nd.c"
#include "hist_set_syst_errors.c"
//#include "TDirectory.h"
#include "TMath.h"
#include <algorithm>

Hist::~Hist(){}

void Hist::SetFigure3Style(TH1D* h_data, TH1D* h_qq_ll, TH1D* h_qq, TH1D* h_ll, TH1D* h_bg)
{
    h_data->SetLineColor(kBlack);
    h_data->SetLineWidth(3);
    h_qq_ll->SetLineColor(kRed);
    h_qq->SetLineColor(kBlack);
    h_qq->SetLineStyle(7);
    h_ll->SetLineColor(kBlue);
    h_ll->SetLineStyle(3);

    h_ll->SetFillColor(0);//kYellow
    h_ll->SetFillStyle(0);  
    h_data->SetFillColor(0);//kYellow
    h_data->SetFillStyle(0);    
    h_qq_ll->SetFillColor(0);//kYellow
    h_qq_ll->SetFillStyle(0);   
    h_qq->SetFillColor(0);//kYellow
    h_qq->SetFillStyle(0);  

}
void Hist::SetVioletStyle(TH1D* h_data, TH1D*  h_res, TH1D*  h_qq, TH1D*  h_ll, TH1D*  h_bg)
{
    h_res->SetLineColor(kRed);
    h_res->SetLineStyle(1);
    h_res->SetLineWidth(1);
    h_res->SetFillColor(kWhite);

    h_data->SetMarkerStyle(21);
    h_data->SetMarkerColor(kBlack);//kRed
    h_data->SetLineColor(kBlack);
    h_data->SetMarkerSize(0.5); //hist_data_sum[i]->Sumw2();

    h_qq->SetLineColor(kBlue);
    h_qq->SetFillColor(kBlue);//kYellow
    h_qq->SetFillStyle(3004);//     h_deltaz_xgamma_prph_sum[i]->Sumw2();

    h_ll->SetLineColor(kMagenta+3);
    h_ll->SetFillColor(kMagenta+3);//kYellow
    h_ll->SetFillStyle(3006);       //h_deltaz_xgamma_rad_sum[i]->Sumw2();h_deltaz_xgamma_rad_sum[i]->Scale(lumi_data[0] / lumi_mc_bg[0]);// LL 

    h_bg->SetLineColor(kOrange+7);
    h_bg->SetFillColor(kOrange+7);//kYellow
    h_bg->SetFillStyle(3005);       
}


void Hist::Init()
{
    f = new TFile("cross_sec_histos.root", "recreate", "root file with histohrams");
    f->cd();
    sys_acc = 1;
    sys_fit = 0.8;

    g_index_fmax = 1;
    g_index_deltaz = 0;
    s_periods[0] = "0405e";
    s_periods[1] = "06e";
    s_periods[2] = "0607p";
    s_var[0] = "et";
    s_var[1] = "eta";
    s_var[2] = "Q2";
    s_var[3] = "x";
    s_var[4] = "et_jet";
    s_var[5] = "eta_jet";
    s_var[6] = "xgamma";
    s_var[7] = "xp";
    s_var[8] = "dphi";
    s_var[9] = "deta";
    s_var[10] = "dphi_e_ph";
    s_var[11] = "deta_e_ph";
    s_title[0] = "E_{T}";
    s_title[1] = "#eta";
    s_title[2] = "Q^{2}";
    s_title[3] = "x";
    s_title[4] = "E_{T,jet}";
    s_title[5] = "#eta_{jet}";
    s_title[6] = "x_{#gamma}";
    s_title[7] = "x_{p}";
    s_title[8] = "#Delta#phi";
    s_title[9] = "#Delta#eta";
    s_title[10] = "#Delta#phi_{e,#gamma}";
    s_title[11] = "#Delta#eta_{e,#gamma}";
    //s_var
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
    TString s_method = "_test_zero";
    //TString s_method = "_test_systElE-";//"_q2etapheph_rew_n.root"; //? 010715
    //TString s_method = "_test_systElE+";
    //TString s_method = "_test_systJetE+";// touch output_systJetE+.txt; ./p cross_sec >  output_systJetE+.txt
    //TString s_method = "_test_systJetE-";// touch output_systJetE-.txt; ./p cross_sec >  output_systJetE-.txt &
    //TString s_method = "_test_systPhE+";
    //TString s_method = "_test_systPhE-";
    //TString s_method3 = "_test_rew_eph_bg.root";
    //TString s_method2 = "_test_syst_jet_minus.root";
    set_hist_atributes(0,  "h_x_pomeron", "Photon_with_jet", "x_{#p}", 0., 0.03, 0.0, kFALSE, 1);
    set_hist_atributes(1,  "h_x_gamma", "Photon_with_jet", "x_{#gamma}", 0., 1.0, 0.0, kFALSE, 1);
    set_hist_atributes(2,  "h_phjet_deta", "Photon_with_jet", "#Delta#eta", -2.2, 2.7, 0.0, kFALSE, 1);
    //23
    set_hist_atributes(3,  "h_phjet_dphi", "Photon_with_jet", "#Delta#phi, deg.", 0.0, 180., 0.0, kFALSE, 1);
    set_hist_atributes(4,  "h_phjet_dphi_el_ph_true", "Photon_with_jet", "#Delta#phi_{e,#gamma}, deg.", 0.0, 180., 0.0, kFALSE, 1);
    set_hist_atributes(5,  "h_phjet_deta_el_ph_true", "Photon_with_jet", "#Delta#eta_{e,#gamma}",  -4.5, 0., 0.0, kFALSE, 1);
    

    cout<< "n_hist"<<n_hist<<endl;
    TString s_process = "_test_zero.root"; 
    s_process.Form("_test_" + correctiontype + ".root");
    {
        TString s_period[n_periods] = {"0405e", "06e", "0607p"};
        TFile *file[n_periods][4];

        TString s_path = "../my_";//"../my_"    ../../isolated_photons/
        selectedoutput << str_selectedoutput <<endl;
        //***********************
        //    READING FROM DATA
        //***********************
        for(Int_t p = 0; p < n_periods; p++) 
        {
            file[p][0] =  new TFile(s_path + "data" + s_period[p] + "_test_zero.root", "READ");//s_path2 + "data" + s_periods[i] + "_test.root"
            file[p][1] =  new TFile(s_path + "mc_bg_norad" + s_period[p] + s_process, "READ");
            file[p][2] =  new TFile(s_path + "mc_bg_rad" + s_period[p] + s_process, "READ");
            if(s_period[p] != "0607p") 
                file[p][3] =  new TFile(s_path + "mc_prph" + s_period[p] + s_process, "READ");

            for(Int_t i = 0; i < n_hist; i++)
            {
                if(s_period[p] != "0607p") 
                {
                    file[p][3]->cd();
                    hist_mc_control[p][i] = (TH1D*)file[p][3]->Get(s_hist[i])->Clone();             
                    hist_mc_control[p][i] -> SetName(s_hist[i]+"_mc_signal" + s_period[p]);//dir + "/" + name + "_mc_signal" + s_period[p]
                }

                file[p][2]->cd();
                hist_mc_rad_control[p][i] = (TH1D*)file[p][2]->Get(s_hist[i])->Clone();
                hist_mc_rad_control[p][i]->SetName(s_hist[i]+"_mc_rad" + s_period[p]);
        

                file[p][1]->cd();
                hist_mc_norad_control[p][i] = (TH1D*)file[p][1]->Get(s_hist[i])->Clone();
                hist_mc_norad_control[p][i]->SetName(s_hist[i]+"_mc_norad" + s_period[p]);

                file[p][0]->cd();
                hist_data_control[p][i] = (TH1D*)file[p][0]->Get(s_hist[i])->Clone();
                hist_data_control[p][i]->SetName(s_hist[i]+"_data" + s_period[p]);

                if(s_period[p]!="0607p")
                    hist_mc_control[p][i]->Sumw2();
                hist_mc_rad_control[p][i]->Sumw2();
                hist_mc_norad_control[p][i]->Sumw2();
                hist_data_control[p][i]->Sumw2();
                //  hist_ratio[i]->Sumw2();
                //  hist_res[i]->Sumw2();
                if(i == 1) 
                {
                    //if (nodebugmode) cout << "period = " << s_period[p] << ", n_data = " << hist_data_control[p][i]->Integral()<< ", n_mc_norad = " << hist_mc_norad_control[p][i]->Integral()<< ", n_mc_rad = " << hist_mc_rad_control[p][i]->Integral();
                    if(s_period[p] != "0607p") 
                        if (nodebugmode) cout << ", n_mc = " <<  hist_mc_control[p][i]->Integral() << endl;
                }
            }
        }

        //***********************
        //    CREATING HISTOGRAMS FOR SUMMING OVER PERIODS *_sum
        //***********************
        //***********************
        //    SCALE TO LUMINOSITY //scale first period monte carlo to data luminosity styling
        //***********************
        for(Int_t i = 0; i < n_hist; i++)
        {      

            hist_ratio[i] = (TH1D*) hist_data_control[0][i]->Clone();   //data
            hist_ratio[i]->SetName(s_hist[i]+"_ratio");
            hist_ratio[i]->SetLineColor(kBlue);
            hist_ratio[i]->Sumw2();

            hist_mc_sum[i] = (TH1D*) hist_mc_control[0][i]->Clone();    //  hist_mc_sum[i]->Sumw2();
            hist_mc_sum[i]->SetName(s_hist[i]+"_mc_signal");
            hist_mc_sum[i]->SetLineColor(kBlue);
            hist_mc_sum[i]->SetFillColor(kBlue);//kYellow
            hist_mc_sum[i]->SetFillStyle(3004);
            hist_mc_sum[i]->Sumw2();

            hist_mc_rad_sum[i] = (TH1D*) hist_mc_rad_control[0][i]->Clone();    //ll
            hist_mc_rad_sum[i]->SetName(s_hist[i]+"_mc_rad");
            hist_mc_rad_sum[i]->SetLineColor(kMagenta+3);
            hist_mc_rad_sum[i]->SetFillColor(kMagenta+3);//kYellow
            hist_mc_rad_sum[i]->SetFillStyle(3006);
            hist_mc_rad_sum[i]->Sumw2();
            hist_mc_rad_sum[i]->Scale(lumi_data[0] / lumi_mc_bg[0]);// LL

            hist_mc_norad_sum[i] = (TH1D*) hist_mc_norad_control[0][i]->Clone();    //bg
            hist_mc_norad_sum[i]->SetName(s_hist[i]+"_mc_norad");
            hist_mc_norad_sum[i]->SetLineColor(kOrange+7);
            hist_mc_norad_sum[i]->SetFillColor(kOrange+7);//kYellow
            hist_mc_norad_sum[i]->SetFillStyle(3005);
            hist_mc_norad_sum[i]->Sumw2();
            hist_mc_norad_sum[i]->Scale(lumi_data[0] / lumi_mc_bg[0]);// bg

            hist_data_sum[i] = (TH1D*) hist_data_control[0][i]->Clone();
            hist_data_sum[i]->SetName(s_hist[i]+"_data");
            hist_data_sum[i]->SetMarkerStyle(21);
            hist_data_sum[i]->SetMarkerSize(0.5);
            hist_data_sum[i]->Sumw2();
        }


        //***********************
        //    SUM HISTOGR FOR ALL PERIODS 
        //***********************

        for(Int_t i = 0; i < n_hist; i++)
        {
            for(Int_t p = 1; p < n_periods; p++) //0 - already cloned
            {
                cerr << i << " " << p << " adding :" << hist_data_control[p][i]->GetName() << endl;
                hist_data_sum[i]->Add(hist_data_control[p][i]);
                cerr << hist_data_control[p][i]->GetNbinsX() << endl;
                cerr << "data scaled - ok" << endl;

                hist_mc_rad_sum[i]->Add(hist_mc_rad_control[p][i], lumi_data[p]/lumi_mc_bg[p]);
                cerr << hist_mc_rad_control[p][i]->GetNbinsX() << endl;
                cerr << "mc_rad scaled - ok" << endl;

                hist_mc_norad_sum[i]->Add(hist_mc_norad_control[p][i], lumi_data[p]/lumi_mc_bg[p]);
                cerr << hist_mc_norad_control[p][i]->GetNbinsX() << endl;
                cerr << "mc_norad scaled - ok" << endl;

                if(s_period[p] != "0607p") 
                {
                    hist_mc_sum[i]->Add(hist_mc_control[p][i]);//QQ
                    cerr << hist_mc_control[p][i]->GetNbinsX() << endl;
                    cerr << "mc_prph - ok" << endl;
                }
            }
            for (Int_t j = 0; j < hist_mc_sum[i]->GetNbinsX(); j++)
            {
                Double_t mult ;
                if (hist_mc_sum[i]->GetBinContent(j+1) != 0 )
                {
                    /*if (QQfit == 0)
                      mult = (hist_data_sum[i]->GetBinContent(j+1) - hist_mc_rad_sum[i]->GetBinContent(j+1)) / hist_mc_sum[i]->GetBinContent(j+1);
                    else*/
                      //Before the meeting 
                      //mult = (hist_data_sum[i]->GetBinContent(j+1)) / hist_mc_sum[i]->GetBinContent(j+1);
                      //For the meeting - like in the QQ+LL fit
                      mult = (hist_data_sum[i]->GetBinContent(j+1) - hist_mc_rad_sum[i]->GetBinContent(j+1)) / hist_mc_sum[i]->GetBinContent(j+1);
                }
                else
                    mult = 0;
                hist_mc_sum[i]->SetBinContent(j+1, hist_mc_sum[i]->GetBinContent(j+1) * mult);
                hist_mc_sum[i]->SetBinError(j+1, hist_mc_sum[i]->GetBinError(j+1) * mult);

                if (hist_mc_norad_sum[i]->GetBinContent(j+1) != 0 )
                {
                    //mult = (hist_data_sum[i]->GetBinContent(j+1) - hist_mc_rad_sum[i]->GetBinContent(j+1)) / hist_mc_norad_sum[i]->GetBinContent(j+1);
                    //mult = (hist_data_sum[i]->GetBinContent(j+1)  - QQfit * hist_mc_rad_sum[i]->GetBinContent(j+1) )/ hist_mc_norad_sum[i]->GetBinContent(j+1);
                    mult = (hist_data_sum[i]->GetBinContent(j+1)  ) / hist_mc_norad_sum[i]->GetBinContent(j+1);
                }
                else 
                    mult = 0;

                hist_mc_norad_sum[i]->SetBinContent(j+1, hist_mc_norad_sum[i]->GetBinContent(j+1) * mult);
                hist_mc_norad_sum[i]->SetBinError(j+1, hist_mc_norad_sum[i]->GetBinError(j+1) * mult);
            }
            //hist_mc_sum[i]      ->Scale((hist_data_sum[i]->Integral() - hist_mc_rad_sum[i]->Integral()) / hist_mc_sum[i]->Integral());//QQ.scale([Data - LL]/QQ)
            //hist_mc_norad_sum[i]->Scale((hist_data_sum[i]->Integral() - hist_mc_rad_sum[i]->Integral()) / hist_mc_norad_sum[i]->Integral());//bg.scale([Data - LL]/bg)
        
            hist_mc_photon_sum[i] = (TH1D*)hist_mc_rad_sum[i]->Clone();//LL
            hist_mc_photon_sum[i] -> SetName(s_hist[i]+"_mc_photon");
            hist_mc_photon_sum[i] -> Add(hist_mc_sum[i]);//LL+QQ
        }
        cerr << "ADDING : OK" << endl;
        //if (nodebugmode) cout << "AFTER  SCALING: mc QQ: " << hist_mc_sum[g_index_deltaz]->Integral() << " mc LL: " << hist_mc_rad_sum[g_index_deltaz]->Integral() << " mc bg: " << hist_mc_norad_sum[g_index_deltaz]->Integral() << " data: " << hist_data_sum [g_index_deltaz]->Integral()<<endl;

        //
        //rebinings as in the head
        //
        for(Int_t i = 0; i < n_hist; i++)
        {
            hist_data_sum[i] -> Rebin(hist_rebin[i]);
            hist_mc_sum[i] -> Rebin(hist_rebin[i]);
            hist_mc_rad_sum[i] -> Rebin(hist_rebin[i]);
            hist_mc_norad_sum[i] -> Rebin(hist_rebin[i]);
            hist_mc_photon_sum[i] -> Rebin(hist_rebin[i]);
            hist_ratio[i] -> Rebin(hist_rebin[i]);
        }

        //
        //set "per bin" histograms
        //
        for(Int_t i = 0; i < n_hist; i++) 
        {
            for(Int_t l = 0; l < hist_data_sum[i]->GetNbinsX(); l++)
            {
                Double_t bin_width = hist_data_sum[i]->GetBinWidth(l+1);
                if(bin_width != 0)
                {
                    hist_data_sum[i]->SetBinContent(l+1, hist_data_sum[i]->GetBinContent(l+1) / bin_width);
                    hist_data_sum[i]->SetBinError(l+1, hist_data_sum[i]->GetBinError(l+1) / bin_width);

                    hist_mc_sum[i]->SetBinContent(l+1, hist_mc_sum[i]->GetBinContent(l+1) / bin_width);
                    hist_mc_sum[i]->SetBinError(l+1, hist_mc_sum[i]->GetBinError(l+1) / bin_width);

                    hist_mc_rad_sum[i]->SetBinContent(l+1, hist_mc_rad_sum[i]->GetBinContent(l+1) / bin_width);
                    hist_mc_rad_sum[i]->SetBinError(l+1, hist_mc_rad_sum[i]->GetBinError(l+1) / bin_width);

                    hist_mc_norad_sum[i]->SetBinContent(l+1, hist_mc_norad_sum[i]->GetBinContent(l+1) / bin_width);
                    hist_mc_norad_sum[i]->SetBinError(l+1, hist_mc_norad_sum[i]->GetBinError(l+1) / bin_width);

                    hist_mc_photon_sum[i]->SetBinContent(l+1, hist_mc_photon_sum[i]->GetBinContent(l+1) / bin_width);
                    hist_mc_photon_sum[i]->SetBinError(l+1, hist_mc_photon_sum[i]->GetBinError(l+1) / bin_width);

                    hist_ratio[i]->SetBinContent(l+1, hist_ratio[i]->GetBinContent(l+1) / bin_width);
                    hist_ratio[i]->SetBinError(l+1, hist_ratio[i]->GetBinError(l+1) / bin_width);
                }
            }
        }
    }
    //////////////////////////////////////////////////
    //
    //             Connect Input Files
    //
    //////////////////////////////////////////////////  

    for(Int_t i = 0; i < n_periods; i++) 
    {
        TString s; 
        s.Form(s_path2 + "data" + s_periods[i] + "_test_zero.root");//../data
        //if (nodebugmode) cout<<s<<endl;
        file_data[i] = new TFile(s, "READ");
        s.Form(s_path2 + "mc_bg_norad" + s_periods[i] + s_process);
        file_norad[i] = new TFile(s, "READ");
        s.Form(s_path2 + "mc_bg_rad" + s_periods[i] + s_process);
        file_rad[i] = new TFile(s, "READ");
        if (s_periods[i] != "0607p") //нету такой симуляции
        { 
            s.Form(s_path2 + "mc_prph" + s_periods[i] + s_process);
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
        {
            file_data[i]->cd();
            //
            // dz in bins of xgamma
            //
            for(Int_t j = 0; j < number_xgamma_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_xgamma_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_xgamma_data[j][i] = (TH1D*)file_data[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_xgamma_data[j][i]->SetName(s + "_data_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_data_" + s_periods[i] << endl;
                h_deltaz_xgamma_data[j][i]->Sumw2();
                h_deltaz_xgamma_data[j][i]->Rebin(10);
            }
            //
            // dz in bins of xp
            //
            for(Int_t j = 0; j < number_xp_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_xp_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_xp_data[j][i] = (TH1D*)file_data[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_xp_data[j][i]->SetName(s + "_data_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_data_" + s_periods[i] << endl;
                h_deltaz_xp_data[j][i]->Sumw2();
                h_deltaz_xp_data[j][i]->Rebin(10);
            }
            //
            // dz in bins of dphi
            //
            for(Int_t j = 0; j < number_dphi_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_dphi_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_dphi_data[j][i] = (TH1D*)file_data[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_dphi_data[j][i]->SetName(s + "_data_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_data_" + s_periods[i] << endl;
                h_deltaz_dphi_data[j][i]->Sumw2();
                h_deltaz_dphi_data[j][i]->Rebin(10);
            }
            //
            // dz in bins of deta
            //
            for(Int_t j = 0; j < number_deta_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_deta_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_deta_data[j][i] = (TH1D*)file_data[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_deta_data[j][i]->SetName(s + "_data_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_data_" + s_periods[i] << endl;
                h_deltaz_deta_data[j][i]->Sumw2();
                h_deltaz_deta_data[j][i]->Rebin(10);
            }
            //
            // dz in bins of dphi_e_ph
            //
            for(Int_t j = 0; j < number_dphi_e_ph_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_dphi_e_ph_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_dphi_e_ph_data[j][i] = (TH1D*)file_data[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_dphi_e_ph_data[j][i]->SetName(s + "_data_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_data_" + s_periods[i] << endl;
                h_deltaz_dphi_e_ph_data[j][i]->Sumw2();
                h_deltaz_dphi_e_ph_data[j][i]->Rebin(10);
            }
            //
            // dz in bins of deta_e_ph
            //
            for(Int_t j = 0; j < number_deta_e_ph_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_deta_e_ph_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_deta_e_ph_data[j][i] = (TH1D*)file_data[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_deta_e_ph_data[j][i]->SetName(s + "_data_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_data_" + s_periods[i] << endl;
                h_deltaz_deta_e_ph_data[j][i]->Sumw2();
                h_deltaz_deta_e_ph_data[j][i]->Rebin(10);
            }
            //
            // dz in bins of et
            //
            for(Int_t j = 0; j < number_etbins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_et_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_et_data[j][i] = (TH1D*)file_data[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_et_data[j][i]->SetName(s + "_data_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_data_" + s_periods[i] << endl;
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
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_eta_data[j][i] = (TH1D*)file_data[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_data_" + s_periods[i];
                h_deltaz_eta_data[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
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
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_q2_data[j][i] = (TH1D*)file_data[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_data_" + s_periods[i];
                h_deltaz_q2_data[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                h_deltaz_q2_data[j][i]->Sumw2();
                h_deltaz_q2_data[j][i]->Rebin(10);
            }
            //
            // dz in bins of x
            //
            for(Int_t j = 0; j < number_xbins; j++) 
            {
                TString s; s.Form("h_deltaz_x_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_x_data[j][i] = (TH1D*)file_data[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_data_" + s_periods[i];
                h_deltaz_x_data[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                h_deltaz_x_data[j][i]->Sumw2();
                h_deltaz_x_data[j][i]->Rebin(10);
            }
            //
            // dz in bins of et_jet
            //
            for(Int_t j = 0; j < number_et_jetbins; j++) 
            {
                TString s; s.Form("h_deltaz_et_jet_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_et_jet_data[j][i] = (TH1D*)file_data[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_data_" + s_periods[i];
                h_deltaz_et_jet_data[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                h_deltaz_et_jet_data[j][i]->Sumw2();
                h_deltaz_et_jet_data[j][i]->Rebin(10);
            }
            //
            // dz in bins of eta_jet
            //
            for(Int_t j = 0; j < number_eta_jetbins; j++) 
            {
                TString s; s.Form("h_deltaz_eta_jet_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_eta_jet_data[j][i] = (TH1D*)file_data[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_data_" + s_periods[i];
                h_deltaz_eta_jet_data[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
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
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                prof_det_data[j][i] = (TProfile*)file_data[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_data_" + s_var[j] + s_periods[i];
                prof_det_data[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                prof_det_data[j][i]->Sumw2();

                s.Form("h_det_cross_" + s_var[j]);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_det_data[j][i] = (TH1D*)file_data[i]->Get("Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_data_" + s_periods[i];
                h_det_data[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                h_det_data[j][i]->Sumw2();
            }
        }
        //====================== mc norad =============================================
        {
            file_norad[i]->cd();
            //
            // dz in bins of xgamma
            //
            for(Int_t j = 0; j < number_xgamma_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_xgamma_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_xgamma_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_xgamma_norad[j][i]->SetName(s + "_norad_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_norad_" + s_periods[i] << endl;
                h_deltaz_xgamma_norad[j][i]->Sumw2();
                h_deltaz_xgamma_norad[j][i]->Rebin(10);
            }
            //
            // dz in bins of xp
            //
            for(Int_t j = 0; j < number_xp_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_xp_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_xp_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_xp_norad[j][i]->SetName(s + "_norad_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_norad_" + s_periods[i] << endl;
                h_deltaz_xp_norad[j][i]->Sumw2();
                h_deltaz_xp_norad[j][i]->Rebin(10);
            }
            //
            // dz in bins of dphi
            //
            for(Int_t j = 0; j < number_dphi_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_dphi_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_dphi_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_dphi_norad[j][i]->SetName(s + "_norad_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_norad_" + s_periods[i] << endl;
                h_deltaz_dphi_norad[j][i]->Sumw2();
                h_deltaz_dphi_norad[j][i]->Rebin(10);
            }
            //
            // dz in bins of deta
            //
            for(Int_t j = 0; j < number_deta_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_deta_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_deta_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_deta_norad[j][i]->SetName(s + "_norad_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_norad_" + s_periods[i] << endl;
                h_deltaz_deta_norad[j][i]->Sumw2();
                h_deltaz_deta_norad[j][i]->Rebin(10);
            }
            //
            // dz in bins of dphi_e_ph
            //
            for(Int_t j = 0; j < number_dphi_e_ph_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_dphi_e_ph_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_dphi_e_ph_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_dphi_e_ph_norad[j][i]->SetName(s + "_norad_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_norad_" + s_periods[i] << endl;
                h_deltaz_dphi_e_ph_norad[j][i]->Sumw2();
                h_deltaz_dphi_e_ph_norad[j][i]->Rebin(10);
            }
            //
            // dz in bins of deta_e_ph
            //
            for(Int_t j = 0; j < number_deta_e_ph_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_deta_e_ph_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_deta_e_ph_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_deta_e_ph_norad[j][i]->SetName(s + "_norad_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_norad_" + s_periods[i] << endl;
                h_deltaz_deta_e_ph_norad[j][i]->Sumw2();
                h_deltaz_deta_e_ph_norad[j][i]->Rebin(10);
            }
            //
            // dz in bins of et
            //
            for(Int_t j = 0; j < number_etbins; j++) 
            {
                TString s; 
                s.Form("h_deltaz_et_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_et_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_norad_" + s_periods[i];
                h_deltaz_et_norad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
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
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_eta_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_norad_" + s_periods[i];
                h_deltaz_eta_norad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                h_deltaz_eta_norad[j][i]->Sumw2();
                h_deltaz_eta_norad[j][i]->Rebin(10);
            }
            //
            // dz in bins of q2
            //
            for(Int_t j = 0; j < number_Q2bins; j++) 
            {
                TString s; s.Form("h_deltaz_q2_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_q2_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_norad_" + s_periods[i];
                h_deltaz_q2_norad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                h_deltaz_q2_norad[j][i]->Sumw2();
                h_deltaz_q2_norad[j][i]->Rebin(10);
            }
            //
            // dz in bins of x
            //
            for(Int_t j = 0; j < number_xbins; j++) 
            {
                TString s; s.Form("h_deltaz_x_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_x_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_norad_" + s_periods[i];
                h_deltaz_x_norad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                h_deltaz_x_norad[j][i]->Sumw2();
                h_deltaz_x_norad[j][i]->Rebin(10);
            }
            //
            // dz in bins of et_jet
            //
            for(Int_t j = 0; j < number_et_jetbins; j++) 
            {
                TString s; s.Form("h_deltaz_et_jet_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_et_jet_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_norad_" + s_periods[i];
                h_deltaz_et_jet_norad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                h_deltaz_et_jet_norad[j][i]->Sumw2();
                h_deltaz_et_jet_norad[j][i]->Rebin(10);
            }
            //
            // dz in bins of eta_jet
            //
            for(Int_t j = 0; j < number_eta_jetbins; j++) 
            {
                TString s; s.Form("h_deltaz_eta_jet_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_eta_jet_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_norad_" + s_periods[i];
                h_deltaz_eta_jet_norad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
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
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                prof_det_norad[j][i] = (TProfile*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_norad_" + s_var[j] + s_periods[i];
                prof_det_norad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                prof_det_norad[j][i]->Sumw2();

                //had
                s.Form("prof_had_cross_" + s_var[j]);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                prof_had_norad[j][i] = (TProfile*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_norad_" + s_var[j] + s_periods[i];
                prof_had_norad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                prof_had_norad[j][i]->Sumw2();

                //hd
                s.Form("prof_hd_cross_" + s_var[j]);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                prof_hd_norad[j][i] = (TProfile*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_norad_" + s_var[j] + s_periods[i];
                prof_hd_norad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                prof_hd_norad[j][i]->Sumw2();

                //det
                s.Form("h_det_cross_" + s_var[j]);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_det_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_norad_" + s_var[j] + s_periods[i];
                h_det_norad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                h_det_norad[j][i]->Sumw2();
                /*      //had
                    s.Form("h_had_cross_" + s_var[j]);
                    //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                    h_had_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                    s = s + "_norad_" + s_var[j] + s_periods[i];
                    h_had_norad[j][i]->SetName(s);
                    //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                    h_had_norad[j][i]->Sumw2();
                //hd
                s.Form("h_hd_cross_" + s_var[j]);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_hd_norad[j][i] = (TH1D*)file_norad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_norad_" + s_var[j] + s_periods[i];
                h_hd_norad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                h_hd_norad[j][i]->Sumw2();*/
            }
        }
        //====================== mc rad =============================================
        {
            file_rad[i]->cd();
            //
            // dz in bins of xgamma
            //
            for(Int_t j = 0; j < number_xgamma_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_xgamma_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_xgamma_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_xgamma_rad[j][i]->SetName(s + "_rad_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_rad_" + s_periods[i] << endl;
                h_deltaz_xgamma_rad[j][i]->Sumw2();
                h_deltaz_xgamma_rad[j][i]->Rebin(10);
            }
            //
            // dz in bins of xp
            //
            for(Int_t j = 0; j < number_xp_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_xp_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_xp_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_xp_rad[j][i]->SetName(s + "_rad_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_rad_" + s_periods[i] << endl;
                h_deltaz_xp_rad[j][i]->Sumw2();
                h_deltaz_xp_rad[j][i]->Rebin(10);
            }
            //
            // dz in bins of dphi
            //
            for(Int_t j = 0; j < number_dphi_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_dphi_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_dphi_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_dphi_rad[j][i]->SetName(s + "_rad_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_rad_" + s_periods[i] << endl;
                h_deltaz_dphi_rad[j][i]->Sumw2();
                h_deltaz_dphi_rad[j][i]->Rebin(10);
            }
            //
            // dz in bins of deta
            //
            for(Int_t j = 0; j < number_deta_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_deta_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_deta_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_deta_rad[j][i]->SetName(s + "_rad_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_rad_" + s_periods[i] << endl;
                h_deltaz_deta_rad[j][i]->Sumw2();
                h_deltaz_deta_rad[j][i]->Rebin(10);
            }
            //
            // dz in bins of dphi_e_ph
            //
            for(Int_t j = 0; j < number_dphi_e_ph_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_dphi_e_ph_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_dphi_e_ph_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_dphi_e_ph_rad[j][i]->SetName(s + "_rad_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_rad_" + s_periods[i] << endl;
                h_deltaz_dphi_e_ph_rad[j][i]->Sumw2();
                h_deltaz_dphi_e_ph_rad[j][i]->Rebin(10);
            }
            //
            // dz in bins of deta_e_ph
            //
            for(Int_t j = 0; j < number_deta_e_ph_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_deta_e_ph_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_deta_e_ph_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_deta_e_ph_rad[j][i]->SetName(s + "_rad_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_rad_" + s_periods[i] << endl;
                h_deltaz_deta_e_ph_rad[j][i]->Sumw2();
                h_deltaz_deta_e_ph_rad[j][i]->Rebin(10);
            }
            //
            // dz in bins of et
            //
            for(Int_t j = 0; j < number_etbins; j++) 
            {
                TString s; 
                s.Form("h_deltaz_et_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_et_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                if (nodebugmode) cout << "just read et bin " << j << "sum = " << h_deltaz_et_rad[j][i]->GetSum() << ", entries = " << h_deltaz_et_rad[j][i]->GetEntries() 
                    << ", integral = " << h_deltaz_et_rad[j][i]->Integral() << endl;
                s = s + "_rad_" + s_periods[i];
                h_deltaz_et_rad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
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
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_eta_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_rad_" + s_periods[i];
                h_deltaz_eta_rad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
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
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_q2_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_rad_" + s_periods[i];
                h_deltaz_q2_rad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
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
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_x_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_rad_" + s_periods[i];
                h_deltaz_x_rad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
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
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_et_jet_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_rad_" + s_periods[i];
                h_deltaz_et_jet_rad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
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
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_eta_jet_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_rad_" + s_periods[i];
                h_deltaz_eta_jet_rad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
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
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                prof_det_rad[j][i] = (TProfile*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_rad_" + s_var[j] + s_periods[i];
                prof_det_rad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                prof_det_rad[j][i]->Sumw2();
                //had prof
                s.Form("prof_had_cross_" + s_var[j]);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                prof_had_rad[j][i] = (TProfile*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_rad_" + s_var[j] + s_periods[i];
                prof_had_rad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                prof_had_rad[j][i]->Sumw2();
                //hd prof
                s.Form("prof_hd_cross_" + s_var[j]);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                prof_hd_rad[j][i] = (TProfile*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_rad_" + s_var[j] + s_periods[i];
                prof_hd_rad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                prof_hd_rad[j][i]->Sumw2();

                //det
                s.Form("h_det_cross_" + s_var[j]);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_det_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_rad_" + s_var[j] + s_periods[i];
                h_det_rad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                h_det_rad[j][i]->Sumw2();
                //had
                s.Form("h_had_cross_" + s_var[j]);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_had_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_rad_" + s_var[j] + s_periods[i];
                h_had_rad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                h_had_rad[j][i]->Sumw2();
                //hd
                s.Form("h_hd_cross_" + s_var[j]); //?
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_hd_rad[j][i] = (TH1D*)file_rad[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_rad_" + s_var[j] + s_periods[i];
                h_hd_rad[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                h_hd_rad[j][i]->Sumw2();
            }
        }
        //====================== mc prph =============================================
        if(i != 2) 
        {
            file_prph[i]->cd();
            //
            // dz in bins of xgamma
            //
            for(Int_t j = 0; j < number_xgamma_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_xgamma_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_xgamma_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_xgamma_prph[j][i]->SetName(s + "_prph_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_prph_" + s_periods[i] << endl;
                h_deltaz_xgamma_prph[j][i]->Sumw2();
                h_deltaz_xgamma_prph[j][i]->Rebin(10);
            }
            //
            // dz in bins of xp
            //
            for(Int_t j = 0; j < number_xp_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_xp_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_xp_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_xp_prph[j][i]->SetName(s + "_prph_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_prph_" + s_periods[i] << endl;
                h_deltaz_xp_prph[j][i]->Sumw2();
                h_deltaz_xp_prph[j][i]->Rebin(10);
            }
            //
            // dz in bins of dphi
            //
            for(Int_t j = 0; j < number_dphi_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_dphi_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_dphi_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_dphi_prph[j][i]->SetName(s + "_prph_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_prph_" + s_periods[i] << endl;
                h_deltaz_dphi_prph[j][i]->Sumw2();
                h_deltaz_dphi_prph[j][i]->Rebin(10);
            }
            //
            // dz in bins of deta
            //
            for(Int_t j = 0; j < number_deta_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_deta_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_deta_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_deta_prph[j][i]->SetName(s + "_prph_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_prph_" + s_periods[i] << endl;
                h_deltaz_deta_prph[j][i]->Sumw2();
                h_deltaz_deta_prph[j][i]->Rebin(10);
            }
            //
            // dz in bins of dphi_e_ph
            //
            for(Int_t j = 0; j < number_dphi_e_ph_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_dphi_e_ph_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_dphi_e_ph_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_dphi_e_ph_prph[j][i]->SetName(s + "_prph_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_prph_" + s_periods[i] << endl;
                h_deltaz_dphi_e_ph_prph[j][i]->Sumw2();
                h_deltaz_dphi_e_ph_prph[j][i]->Rebin(10);
            }
            //
            // dz in bins of deta_e_ph
            //
            for(Int_t j = 0; j < number_deta_e_ph_bins; j++) //number_etbins = 4;
            {
                TString s; 
                s.Form("h_deltaz_deta_e_ph_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_deta_e_ph_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                //s = s + "_data_" + s_periods[i];
                h_deltaz_deta_e_ph_prph[j][i]->SetName(s + "_prph_" + s_periods[i]);
                //if (nodebugmode) cout << "OK: renamed to " << s + "_prph_" + s_periods[i] << endl;
                h_deltaz_deta_e_ph_prph[j][i]->Sumw2();
                h_deltaz_deta_e_ph_prph[j][i]->Rebin(10);
            }
            //
            // dz in bins of et
            //
            for(Int_t j = 0; j < number_etbins; j++) 
            {
                TString s; 
                s.Form("h_deltaz_et_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_et_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_periods[i];
                h_deltaz_et_prph[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                h_deltaz_et_prph[j][i]->Sumw2();
                h_deltaz_et_prph[j][i]->Rebin(10);
            }
            //
            // dz in bins of eta
            //
            for(Int_t j=0; j<number_etabins; j++) 
            {
                TString s; s.Form("h_deltaz_eta_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_eta_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_periods[i];
                h_deltaz_eta_prph[j][i]->SetName(s);
                h_deltaz_eta_prph[j][i]->Sumw2();
                h_deltaz_eta_prph[j][i]->Rebin(10);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
            }
            //
            // dz in bins of q2
            //
            for(Int_t j=0; j<number_Q2bins; j++) 
            {
                TString s; 
                s.Form("h_deltaz_q2_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_q2_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_periods[i];
                h_deltaz_q2_prph[j][i]->SetName(s);
                h_deltaz_q2_prph[j][i]->Sumw2();
                h_deltaz_q2_prph[j][i]->Rebin(10);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
            }
            //
            // dz in bins of x
            //
            for(Int_t j=0; j<number_xbins; j++) 
            {
                TString s; s.Form("h_deltaz_x_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_x_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_periods[i];
                h_deltaz_x_prph[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                h_deltaz_x_prph[j][i]->Sumw2();
                h_deltaz_x_prph[j][i]->Rebin(10);
            }
            //
            // dz in bins of et_jet
            //
            for(Int_t j=0; j<number_et_jetbins; j++) 
            {
                TString s; s.Form("h_deltaz_et_jet_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_et_jet_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_periods[i];
                h_deltaz_et_jet_prph[j][i]->SetName(s);
                h_deltaz_et_jet_prph[j][i]->Sumw2();
                h_deltaz_et_jet_prph[j][i]->Rebin(10);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
            }
            //
            // dz in bins of eta_jet
            //
            for(Int_t j=0; j<number_eta_jetbins; j++) 
            {
                TString s; s.Form("h_deltaz_eta_jet_%i", j);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_deltaz_eta_jet_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_periods[i];
                h_deltaz_eta_jet_prph[j][i]->SetName(s);
                h_deltaz_eta_jet_prph[j][i]->Sumw2();
                h_deltaz_eta_jet_prph[j][i]->Rebin(10);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
            }
            //
            // Profiles
            //
            for(Int_t j=0; j<n_cross; j++) 
            {
                //det
                TString s; s.Form("prof_det_cross_" + s_var[j]);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                prof_det_prph[j][i] = (TProfile*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_var[j] + s_periods[i];
                prof_det_prph[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                prof_det_prph[j][i]->Sumw2();
                //had
                s.Form("prof_had_cross_" + s_var[j]);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                prof_had_prph[j][i] = (TProfile*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_var[j] + s_periods[i];
                prof_had_prph[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                prof_had_prph[j][i]->Sumw2();
                //hd
                s.Form("prof_hd_cross_" + s_var[j]);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                prof_hd_prph[j][i] = (TProfile*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_var[j] + s_periods[i];
                prof_hd_prph[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                prof_hd_prph[j][i]->Sumw2();

                //det
                s.Form("h_det_cross_" + s_var[j]);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_det_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_var[j] + s_periods[i];
                h_det_prph[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                h_det_prph[j][i]->Sumw2();
                //had
                s.Form("h_had_cross_" + s_var[j]);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_had_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_var[j] + s_periods[i];
                h_had_prph[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
                h_had_prph[j][i]->Sumw2();
                //hd
                s.Form("h_hd_cross_" + s_var[j]);
                //if (nodebugmode) cout << "reading " << s << " ..." << endl;
                h_hd_prph[j][i] = (TH1D*)file_prph[i]->Get( "Cross_Sections_Histograms/" + s)->Clone();
                s = s + "_prph_" + s_var[j] + s_periods[i];
                h_hd_prph[j][i]->SetName(s);
                //if (nodebugmode) cout << "OK: renamed to " << s << endl;
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
        for(Int_t j = 0; j < number_xgamma_bins; j++) //
        {
            if(i==0) 
            {
                TString s; 
                s.Form("h_deltaz_xgamma_data_sum_%i", j);
                h_deltaz_xgamma_data_sum[j] = (TH1D*)h_deltaz_xgamma_data[j][i]->Clone();
                h_deltaz_xgamma_data_sum[j]->SetName(s);
                s.Form("h_deltaz_xgamma_norad_sum_%i", j);
                h_deltaz_xgamma_norad_sum[j] = (TH1D*)h_deltaz_xgamma_norad[j][i]->Clone();
                h_deltaz_xgamma_norad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_xgamma_norad_sum[j]->SetName(s);
                s.Form("h_deltaz_xgamma_rad_sum_%i", j);
                h_deltaz_xgamma_rad_sum[j] = (TH1D*)h_deltaz_xgamma_rad[j][i]->Clone();
                h_deltaz_xgamma_rad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_xgamma_rad_sum[j]->SetName(s);
                s.Form("h_deltaz_xgamma_prph_sum_%i", j);//? 010715 почему нету Scale?
                h_deltaz_xgamma_prph_sum[j] = (TH1D*)h_deltaz_xgamma_prph[j][i]->Clone();
                h_deltaz_xgamma_prph_sum[j]->SetName(s);

                s.Form("h_chi2_perbin_xgamma_%i", j);
                h_chi2_perbin_xgamma[j] = new TH1D(s, ";bin;#chi^{2}", 16, 0, 16);
                //h_chi2_perbin_eta_jet[j]->SetName(s)
            } else {
                h_deltaz_xgamma_data_sum[j]->Add(h_deltaz_xgamma_data[j][i]);
                h_deltaz_xgamma_norad_sum[j]->Add(h_deltaz_xgamma_norad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_xgamma_rad_sum[j]->Add(h_deltaz_xgamma_rad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                if(s_periods[i]!="0607p")
                    h_deltaz_xgamma_prph_sum[j]->Add(h_deltaz_xgamma_prph[j][i]);
            }
        }// for j over  bins xp
        for(Int_t j = 0; j < number_xp_bins; j++) //
        {
            if(i==0) 
            {
                TString s; 
                s.Form("h_deltaz_xp_data_sum_%i", j);
                h_deltaz_xp_data_sum[j] = (TH1D*)h_deltaz_xp_data[j][i]->Clone();
                h_deltaz_xp_data_sum[j]->SetName(s);
                s.Form("h_deltaz_xp_norad_sum_%i", j);
                h_deltaz_xp_norad_sum[j] = (TH1D*)h_deltaz_xp_norad[j][i]->Clone();
                h_deltaz_xp_norad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_xp_norad_sum[j]->SetName(s);
                s.Form("h_deltaz_xp_rad_sum_%i", j);
                h_deltaz_xp_rad_sum[j] = (TH1D*)h_deltaz_xp_rad[j][i]->Clone();
                h_deltaz_xp_rad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_xp_rad_sum[j]->SetName(s);
                s.Form("h_deltaz_xp_prph_sum_%i", j);//? 010715 почему нету Scale?
                h_deltaz_xp_prph_sum[j] = (TH1D*)h_deltaz_xp_prph[j][i]->Clone();
                h_deltaz_xp_prph_sum[j]->SetName(s);

                s.Form("h_chi2_perbin_xp_%i", j);
                h_chi2_perbin_xp[j] = new TH1D(s, ";bin;#chi^{2}", 16, 0, 16);
                //h_chi2_perbin_eta_jet[j]->SetName(s)
            } else {
                h_deltaz_xp_data_sum[j]->Add(h_deltaz_xp_data[j][i]);
                h_deltaz_xp_norad_sum[j]->Add(h_deltaz_xp_norad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_xp_rad_sum[j]->Add(h_deltaz_xp_rad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                if(s_periods[i]!="0607p")
                    h_deltaz_xp_prph_sum[j]->Add(h_deltaz_xp_prph[j][i]);
            }
        }// for j over  bins dphi
        for(Int_t j = 0; j < number_dphi_bins; j++) //
        {
            if(i==0) 
            {
                TString s; 
                s.Form("h_deltaz_dphi_data_sum_%i", j);
                h_deltaz_dphi_data_sum[j] = (TH1D*)h_deltaz_dphi_data[j][i]->Clone();
                h_deltaz_dphi_data_sum[j]->SetName(s);
                s.Form("h_deltaz_dphi_norad_sum_%i", j);
                h_deltaz_dphi_norad_sum[j] = (TH1D*)h_deltaz_dphi_norad[j][i]->Clone();
                h_deltaz_dphi_norad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_dphi_norad_sum[j]->SetName(s);
                s.Form("h_deltaz_dphi_rad_sum_%i", j);
                h_deltaz_dphi_rad_sum[j] = (TH1D*)h_deltaz_dphi_rad[j][i]->Clone();
                h_deltaz_dphi_rad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_dphi_rad_sum[j]->SetName(s);
                s.Form("h_deltaz_dphi_prph_sum_%i", j);//? 010715 почему нету Scale?
                h_deltaz_dphi_prph_sum[j] = (TH1D*)h_deltaz_dphi_prph[j][i]->Clone();
                h_deltaz_dphi_prph_sum[j]->SetName(s);

                s.Form("h_chi2_perbin_dphi_%i", j);
                h_chi2_perbin_dphi[j] = new TH1D(s, ";bin;#chi^{2}", 16, 0, 16);
                //h_chi2_perbin_eta_jet[j]->SetName(s)
            } else {
                h_deltaz_dphi_data_sum[j]->Add(h_deltaz_dphi_data[j][i]);
                h_deltaz_dphi_norad_sum[j]->Add(h_deltaz_dphi_norad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_dphi_rad_sum[j]->Add(h_deltaz_dphi_rad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                if(s_periods[i]!="0607p")
                    h_deltaz_dphi_prph_sum[j]->Add(h_deltaz_dphi_prph[j][i]);
            }
        }// for j over  bins deta
        for(Int_t j = 0; j < number_deta_bins; j++) //
        {
            if(i==0) 
            {
                TString s; 
                s.Form("h_deltaz_deta_data_sum_%i", j);
                h_deltaz_deta_data_sum[j] = (TH1D*)h_deltaz_deta_data[j][i]->Clone();
                h_deltaz_deta_data_sum[j]->SetName(s);
                s.Form("h_deltaz_deta_norad_sum_%i", j);
                h_deltaz_deta_norad_sum[j] = (TH1D*)h_deltaz_deta_norad[j][i]->Clone();
                h_deltaz_deta_norad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_deta_norad_sum[j]->SetName(s);
                s.Form("h_deltaz_deta_rad_sum_%i", j);
                h_deltaz_deta_rad_sum[j] = (TH1D*)h_deltaz_deta_rad[j][i]->Clone();
                h_deltaz_deta_rad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_deta_rad_sum[j]->SetName(s);
                s.Form("h_deltaz_deta_prph_sum_%i", j);//? 010715 почему нету Scale?
                h_deltaz_deta_prph_sum[j] = (TH1D*)h_deltaz_deta_prph[j][i]->Clone();
                h_deltaz_deta_prph_sum[j]->SetName(s);

                s.Form("h_chi2_perbin_deta_%i", j);
                h_chi2_perbin_deta[j] = new TH1D(s, ";bin;#chi^{2}", 16, 0, 16);
                //h_chi2_perbin_eta_jet[j]->SetName(s)
            } else {
                h_deltaz_deta_data_sum[j]->Add(h_deltaz_deta_data[j][i]);
                h_deltaz_deta_norad_sum[j]->Add(h_deltaz_deta_norad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_deta_rad_sum[j]->Add(h_deltaz_deta_rad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                if(s_periods[i]!="0607p")
                    h_deltaz_deta_prph_sum[j]->Add(h_deltaz_deta_prph[j][i]);
            }
        }// for j over  bins dphi_e_ph
        for(Int_t j = 0; j < number_dphi_e_ph_bins; j++) //
        {
            if(i==0) 
            {
                TString s; 
                s.Form("h_deltaz_dphi_e_ph_data_sum_%i", j);
                h_deltaz_dphi_e_ph_data_sum[j] = (TH1D*)h_deltaz_dphi_e_ph_data[j][i]->Clone();
                h_deltaz_dphi_e_ph_data_sum[j]->SetName(s);
                s.Form("h_deltaz_dphi_e_ph_norad_sum_%i", j);
                h_deltaz_dphi_e_ph_norad_sum[j] = (TH1D*)h_deltaz_dphi_e_ph_norad[j][i]->Clone();
                h_deltaz_dphi_e_ph_norad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_dphi_e_ph_norad_sum[j]->SetName(s);
                s.Form("h_deltaz_dphi_e_ph_rad_sum_%i", j);
                h_deltaz_dphi_e_ph_rad_sum[j] = (TH1D*)h_deltaz_dphi_e_ph_rad[j][i]->Clone();
                h_deltaz_dphi_e_ph_rad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_dphi_e_ph_rad_sum[j]->SetName(s);
                s.Form("h_deltaz_dphi_e_ph_prph_sum_%i", j);//? 010715 почему нету Scale?
                h_deltaz_dphi_e_ph_prph_sum[j] = (TH1D*)h_deltaz_dphi_e_ph_prph[j][i]->Clone();
                h_deltaz_dphi_e_ph_prph_sum[j]->SetName(s);

                s.Form("h_chi2_perbin_dphi_e_ph_%i", j);
                h_chi2_perbin_dphi_e_ph[j] = new TH1D(s, ";bin;#chi^{2}", 16, 0, 16);
                //h_chi2_perbin_eta_jet[j]->SetName(s)
            } else {
                h_deltaz_dphi_e_ph_data_sum[j]->Add(h_deltaz_dphi_e_ph_data[j][i]);
                h_deltaz_dphi_e_ph_norad_sum[j]->Add(h_deltaz_dphi_e_ph_norad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_dphi_e_ph_rad_sum[j]->Add(h_deltaz_dphi_e_ph_rad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                if(s_periods[i]!="0607p")
                    h_deltaz_dphi_e_ph_prph_sum[j]->Add(h_deltaz_dphi_e_ph_prph[j][i]);
            }
        }// for j over  bins deta_e_ph
        for(Int_t j = 0; j < number_deta_e_ph_bins; j++) //
        {
            if(i==0) 
            {
                TString s; 
                s.Form("h_deltaz_deta_e_ph_data_sum_%i", j);
                h_deltaz_deta_e_ph_data_sum[j] = (TH1D*)h_deltaz_deta_e_ph_data[j][i]->Clone();
                h_deltaz_deta_e_ph_data_sum[j]->SetName(s);
                s.Form("h_deltaz_deta_e_ph_norad_sum_%i", j);
                h_deltaz_deta_e_ph_norad_sum[j] = (TH1D*)h_deltaz_deta_e_ph_norad[j][i]->Clone();
                h_deltaz_deta_e_ph_norad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_deta_e_ph_norad_sum[j]->SetName(s);
                s.Form("h_deltaz_deta_e_ph_rad_sum_%i", j);
                h_deltaz_deta_e_ph_rad_sum[j] = (TH1D*)h_deltaz_deta_e_ph_rad[j][i]->Clone();
                h_deltaz_deta_e_ph_rad_sum[j]->Scale(lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_deta_e_ph_rad_sum[j]->SetName(s);
                s.Form("h_deltaz_deta_e_ph_prph_sum_%i", j);//? 010715 почему нету Scale?
                h_deltaz_deta_e_ph_prph_sum[j] = (TH1D*)h_deltaz_deta_e_ph_prph[j][i]->Clone();
                h_deltaz_deta_e_ph_prph_sum[j]->SetName(s);

                s.Form("h_chi2_perbin_deta_e_ph_%i", j);
                h_chi2_perbin_deta_e_ph[j] = new TH1D(s, ";bin;#chi^{2}", 16, 0, 16);
                //h_chi2_perbin_eta_jet[j]->SetName(s)
            } else {
                h_deltaz_deta_e_ph_data_sum[j]->Add(h_deltaz_deta_e_ph_data[j][i]);
                h_deltaz_deta_e_ph_norad_sum[j]->Add(h_deltaz_deta_e_ph_norad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                h_deltaz_deta_e_ph_rad_sum[j]->Add(h_deltaz_deta_e_ph_rad[j][i], lumi_data[i]/lumi_mc_bg[i]);
                if(s_periods[i]!="0607p")
                    h_deltaz_deta_e_ph_prph_sum[j]->Add(h_deltaz_deta_e_ph_prph[j][i]);
            }
        }// for j over  bins deta_e_ph

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
                //  h_chi2_perbin_eta_jet[j]->SetName(s)
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
        for(Int_t j = 0; j < n_cross; j++)
        {
            if(i==0) //Initialisation + scaling
            {
                //
                // detector level profiles
                //
                TString s= "prof_det_cross_data_" + s_var[j] + "_sum";
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

            } 
            else 
            {
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
    //             Draw attributes  //! styling
    //
    //////////////////////////////////////////////////
    for(Int_t i = 0; i < number_xgamma_bins; i++) 
    {
        h_deltaz_xgamma_res[i] = (TH1D*)h_deltaz_xgamma_rad_sum[i]->Clone();//LL
        h_deltaz_xgamma_res[i]->SetName(h_deltaz_xgamma_rad_sum[i]->GetName() + TString("_res"));
        h_deltaz_xgamma_res[i]->SetLineColor(kRed);
        h_deltaz_xgamma_res[i]->SetLineStyle(1);
        h_deltaz_xgamma_res[i]->SetLineWidth(1);
        h_deltaz_xgamma_res[i]->SetFillColor(kWhite);

        h_deltaz_xgamma_data_sum[i]->SetMarkerStyle(21);
        h_deltaz_xgamma_data_sum[i]->SetMarkerColor(kBlack);//kRed
        h_deltaz_xgamma_data_sum[i]->SetLineColor(kBlack);
        h_deltaz_xgamma_data_sum[i]->SetMarkerSize(0.5); //hist_data_sum[i]->Sumw2();

        h_deltaz_xgamma_prph_sum[i]->SetLineColor(kBlue);
        h_deltaz_xgamma_prph_sum[i]->SetFillColor(kBlue);//kYellow
        h_deltaz_xgamma_prph_sum[i]->SetFillStyle(3004);//      h_deltaz_xgamma_prph_sum[i]->Sumw2();

        h_deltaz_xgamma_rad_sum[i]->SetLineColor(kMagenta+3);
        h_deltaz_xgamma_rad_sum[i]->SetFillColor(kMagenta+3);//kYellow
        h_deltaz_xgamma_rad_sum[i]->SetFillStyle(3006);     //h_deltaz_xgamma_rad_sum[i]->Sumw2();h_deltaz_xgamma_rad_sum[i]->Scale(lumi_data[0] / lumi_mc_bg[0]);// LL 

        h_deltaz_xgamma_norad_sum[i]->SetLineColor(kOrange+7);
        h_deltaz_xgamma_norad_sum[i]->SetFillColor(kOrange+7);//kYellow
        h_deltaz_xgamma_norad_sum[i]->SetFillStyle(3005);       //h_deltaz_xgamma_norad_sum[i]->Sumw2();
    }
    for(Int_t i = 0; i < number_xp_bins; i++) 
    {
        h_deltaz_xp_res[i] = (TH1D*)h_deltaz_xp_rad_sum[i]->Clone();//LL
        h_deltaz_xp_res[i]->SetName(h_deltaz_xp_rad_sum[i]->GetName() + TString("_res"));
        h_deltaz_xp_res[i]->SetLineColor(kRed);
        h_deltaz_xp_res[i]->SetLineStyle(1);
        h_deltaz_xp_res[i]->SetLineWidth(1);
        h_deltaz_xp_res[i]->SetFillColor(kWhite);

        h_deltaz_xp_data_sum[i]->SetMarkerStyle(21);
        h_deltaz_xp_data_sum[i]->SetMarkerColor(kBlack);//kRed
        h_deltaz_xp_data_sum[i]->SetLineColor(kBlack);
        h_deltaz_xp_data_sum[i]->SetMarkerSize(0.5); //hist_data_sum[i]->Sumw2();

        h_deltaz_xp_prph_sum[i]->SetLineColor(kBlue);
        h_deltaz_xp_prph_sum[i]->SetFillColor(kBlue);//kYellow
        h_deltaz_xp_prph_sum[i]->SetFillStyle(3004);//      h_deltaz_xp_prph_sum[i]->Sumw2();

        h_deltaz_xp_rad_sum[i]->SetLineColor(kMagenta+3);
        h_deltaz_xp_rad_sum[i]->SetFillColor(kMagenta+3);//kYellow
        h_deltaz_xp_rad_sum[i]->SetFillStyle(3006);     //h_deltaz_xp_rad_sum[i]->Sumw2();h_deltaz_xp_rad_sum[i]->Scale(lumi_data[0] / lumi_mc_bg[0]);// LL 

        h_deltaz_xp_norad_sum[i]->SetLineColor(kOrange+7);
        h_deltaz_xp_norad_sum[i]->SetFillColor(kOrange+7);//kYellow
        h_deltaz_xp_norad_sum[i]->SetFillStyle(3005);       //h_deltaz_xp_norad_sum[i]->Sumw2();
    }
    for(Int_t i = 0; i < number_dphi_bins; i++) 
    {
        h_deltaz_dphi_res[i] = (TH1D*)h_deltaz_dphi_rad_sum[i]->Clone();//LL
        h_deltaz_dphi_res[i]->SetName(h_deltaz_dphi_rad_sum[i]->GetName() + TString("_res"));
        h_deltaz_dphi_res[i]->SetLineColor(kRed);
        h_deltaz_dphi_res[i]->SetLineStyle(1);
        h_deltaz_dphi_res[i]->SetLineWidth(1);
        h_deltaz_dphi_res[i]->SetFillColor(kWhite);

        h_deltaz_dphi_data_sum[i]->SetMarkerStyle(21);
        h_deltaz_dphi_data_sum[i]->SetMarkerColor(kBlack);//kRed
        h_deltaz_dphi_data_sum[i]->SetLineColor(kBlack);
        h_deltaz_dphi_data_sum[i]->SetMarkerSize(0.5); //hist_data_sum[i]->Sumw2();

        h_deltaz_dphi_prph_sum[i]->SetLineColor(kBlue);
        h_deltaz_dphi_prph_sum[i]->SetFillColor(kBlue);//kYellow
        h_deltaz_dphi_prph_sum[i]->SetFillStyle(3004);//        h_deltaz_dphi_prph_sum[i]->Sumw2();

        h_deltaz_dphi_rad_sum[i]->SetLineColor(kMagenta+3);
        h_deltaz_dphi_rad_sum[i]->SetFillColor(kMagenta+3);//kYellow
        h_deltaz_dphi_rad_sum[i]->SetFillStyle(3006);       //h_deltaz_dphi_rad_sum[i]->Sumw2();h_deltaz_dphi_rad_sum[i]->Scale(lumi_data[0] / lumi_mc_bg[0]);// LL 

        h_deltaz_dphi_norad_sum[i]->SetLineColor(kOrange+7);
        h_deltaz_dphi_norad_sum[i]->SetFillColor(kOrange+7);//kYellow
        h_deltaz_dphi_norad_sum[i]->SetFillStyle(3005);     //h_deltaz_dphi_norad_sum[i]->Sumw2();
    }
    for(Int_t i = 0; i < number_deta_bins; i++) 
    {
        h_deltaz_deta_res[i] = (TH1D*)h_deltaz_deta_rad_sum[i]->Clone();//LL
        h_deltaz_deta_res[i]->SetName(h_deltaz_deta_rad_sum[i]->GetName() + TString("_res"));
        h_deltaz_deta_res[i]->SetLineColor(kRed);
        h_deltaz_deta_res[i]->SetLineStyle(1);
        h_deltaz_deta_res[i]->SetLineWidth(1);
        h_deltaz_deta_res[i]->SetFillColor(kWhite);

        h_deltaz_deta_data_sum[i]->SetMarkerStyle(21);
        h_deltaz_deta_data_sum[i]->SetMarkerColor(kBlack);//kRed
        h_deltaz_deta_data_sum[i]->SetLineColor(kBlack);
        h_deltaz_deta_data_sum[i]->SetMarkerSize(0.5); //hist_data_sum[i]->Sumw2();

        h_deltaz_deta_prph_sum[i]->SetLineColor(kBlue);
        h_deltaz_deta_prph_sum[i]->SetFillColor(kBlue);//kYellow
        h_deltaz_deta_prph_sum[i]->SetFillStyle(3004);//        h_deltaz_deta_prph_sum[i]->Sumw2();

        h_deltaz_deta_rad_sum[i]->SetLineColor(kMagenta+3);
        h_deltaz_deta_rad_sum[i]->SetFillColor(kMagenta+3);//kYellow
        h_deltaz_deta_rad_sum[i]->SetFillStyle(3006);       //h_deltaz_deta_rad_sum[i]->Sumw2();h_deltaz_deta_rad_sum[i]->Scale(lumi_data[0] / lumi_mc_bg[0]);// LL 

        h_deltaz_deta_norad_sum[i]->SetLineColor(kOrange+7);
        h_deltaz_deta_norad_sum[i]->SetFillColor(kOrange+7);//kYellow
        h_deltaz_deta_norad_sum[i]->SetFillStyle(3005);     //h_deltaz_deta_norad_sum[i]->Sumw2();
    }
    for(Int_t i = 0; i < number_dphi_e_ph_bins; i++) 
    {
        h_deltaz_dphi_e_ph_res[i] = (TH1D*)h_deltaz_dphi_e_ph_rad_sum[i]->Clone();//LL
        h_deltaz_dphi_e_ph_res[i]->SetName(h_deltaz_dphi_e_ph_rad_sum[i]->GetName() + TString("_res"));
        h_deltaz_dphi_e_ph_res[i]->SetLineColor(kRed);
        h_deltaz_dphi_e_ph_res[i]->SetLineStyle(1);
        h_deltaz_dphi_e_ph_res[i]->SetLineWidth(1);
        h_deltaz_dphi_e_ph_res[i]->SetFillColor(kWhite);

        h_deltaz_dphi_e_ph_data_sum[i]->SetMarkerStyle(21);
        h_deltaz_dphi_e_ph_data_sum[i]->SetMarkerColor(kBlack);//kRed
        h_deltaz_dphi_e_ph_data_sum[i]->SetLineColor(kBlack);
        h_deltaz_dphi_e_ph_data_sum[i]->SetMarkerSize(0.5); //hist_data_sum[i]->Sumw2();

        h_deltaz_dphi_e_ph_prph_sum[i]->SetLineColor(kBlue);
        h_deltaz_dphi_e_ph_prph_sum[i]->SetFillColor(kBlue);//kYellow
        h_deltaz_dphi_e_ph_prph_sum[i]->SetFillStyle(3004);//       h_deltaz_dphi_e_ph_prph_sum[i]->Sumw2();

        h_deltaz_dphi_e_ph_rad_sum[i]->SetLineColor(kMagenta+3);
        h_deltaz_dphi_e_ph_rad_sum[i]->SetFillColor(kMagenta+3);//kYellow
        h_deltaz_dphi_e_ph_rad_sum[i]->SetFillStyle(3006);      //h_deltaz_dphi_e_ph_rad_sum[i]->Sumw2();h_deltaz_dphi_e_ph_rad_sum[i]->Scale(lumi_data[0] / lumi_mc_bg[0]);// LL 

        h_deltaz_dphi_e_ph_norad_sum[i]->SetLineColor(kOrange+7);
        h_deltaz_dphi_e_ph_norad_sum[i]->SetFillColor(kOrange+7);//kYellow
        h_deltaz_dphi_e_ph_norad_sum[i]->SetFillStyle(3005);        //h_deltaz_dphi_e_ph_norad_sum[i]->Sumw2();
    }
    for(Int_t i = 0; i < number_deta_e_ph_bins; i++) 
    {
        h_deltaz_deta_e_ph_res[i] = (TH1D*)h_deltaz_deta_e_ph_rad_sum[i]->Clone();//LL
        h_deltaz_deta_e_ph_res[i]->SetName(h_deltaz_deta_e_ph_rad_sum[i]->GetName() + TString("_res"));
        h_deltaz_deta_e_ph_res[i]->SetLineColor(kRed);
        h_deltaz_deta_e_ph_res[i]->SetLineStyle(1);
        h_deltaz_deta_e_ph_res[i]->SetLineWidth(1);
        h_deltaz_deta_e_ph_res[i]->SetFillColor(kWhite);

        h_deltaz_deta_e_ph_data_sum[i]->SetMarkerStyle(21);
        h_deltaz_deta_e_ph_data_sum[i]->SetMarkerColor(kBlack);//kRed
        h_deltaz_deta_e_ph_data_sum[i]->SetLineColor(kBlack);
        h_deltaz_deta_e_ph_data_sum[i]->SetMarkerSize(0.5); //hist_data_sum[i]->Sumw2();

        h_deltaz_deta_e_ph_prph_sum[i]->SetLineColor(kBlue);
        h_deltaz_deta_e_ph_prph_sum[i]->SetFillColor(kBlue);//kYellow
        h_deltaz_deta_e_ph_prph_sum[i]->SetFillStyle(3004);//       h_deltaz_deta_e_ph_prph_sum[i]->Sumw2();

        h_deltaz_deta_e_ph_rad_sum[i]->SetLineColor(kMagenta+3);
        h_deltaz_deta_e_ph_rad_sum[i]->SetFillColor(kMagenta+3);//kYellow
        h_deltaz_deta_e_ph_rad_sum[i]->SetFillStyle(3006);      //h_deltaz_deta_e_ph_rad_sum[i]->Sumw2();h_deltaz_deta_e_ph_rad_sum[i]->Scale(lumi_data[0] / lumi_mc_bg[0]);// LL 

        h_deltaz_deta_e_ph_norad_sum[i]->SetLineColor(kOrange+7);
        h_deltaz_deta_e_ph_norad_sum[i]->SetFillColor(kOrange+7);//kYellow
        h_deltaz_deta_e_ph_norad_sum[i]->SetFillStyle(3005);        //h_deltaz_deta_e_ph_norad_sum[i]->Sumw2();
    }
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
    for(Int_t i=0; i<number_etabins; i++) 
    {
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
    for(Int_t i=0; i<number_Q2bins; i++) 
    {
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
    //             CHECKS of adding - add new variables!!!
    //
    //////////////////////////////////////////////////
    /*
    {
        //!
        if (nodebugmode) cout << " ---------- data dz in bins of et ------------" << endl;
        for(Int_t i = 0; i < n_periods; i++) 
        {
            if (nodebugmode) cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
            for(Int_t j = 0; j < number_etbins; j++) 
                if (nodebugmode) cout << h_deltaz_et_data[j][i]->GetEntries() << "\t\t";
            if (nodebugmode) cout << endl;
        } // for i over periods

        if (nodebugmode) cout << "sum:\t\t\t\t";
        for(Int_t j = 0; j < number_etbins; j++) 
        {
            if (nodebugmode) cout << h_deltaz_et_data_sum[j]->GetEntries() << "\t\t" ;
            if(j==0)
                for(Int_t k = 0; k < h_deltaz_et_data_sum[j]->GetNbinsX(); k++)
                    if (nodebugmode) cout << "0th et bin: " << k << ": " << h_deltaz_et_data_sum[j]->GetBinContent(k+1) << endl;
        }

        if (nodebugmode) cout << "\nprph:\t\t\t\t";
        for(Int_t j=0; j<number_etbins; j++) 
            if (nodebugmode) cout << h_deltaz_et_prph_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << endl << endl;

        if (nodebugmode) cout << " ---------- data dz in bins of eta ------------" << endl;
        for(Int_t i=0; i<n_periods; i++) 
        {
            if (nodebugmode) cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
            for(Int_t j=0; j<number_etabins; j++)
                if (nodebugmode) cout << h_deltaz_eta_data[j][i]->GetEntries() << "\t\t";
            if (nodebugmode) cout << endl;
        } // for i over periods
        if (nodebugmode) cout << "sum:\t\t\t\t";
        for(Int_t j=0; j<number_etabins; j++) 
            if (nodebugmode) cout << h_deltaz_eta_data_sum[j]->GetEntries() << "\t\t";

        if (nodebugmode) cout << "\nprph:\t\t\t\t";
        for(Int_t j=0; j<number_etabins; j++) 
            if (nodebugmode) cout << h_deltaz_eta_prph_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << endl << endl;

        if (nodebugmode) cout << " ---------- data dz in bins of q2 ------------" << endl;
        for(Int_t i=0; i<n_periods; i++) 
        {
            if (nodebugmode) cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
            for(Int_t j=0; j<number_Q2bins; j++)
                if (nodebugmode) cout << h_deltaz_q2_data[j][i]->GetEntries() << "\t\t";
            if (nodebugmode) cout << endl;
        } // for i over periods
        if (nodebugmode) cout << "sum:\t\t\t\t";
        for(Int_t j=0; j<number_Q2bins; j++) 
            if (nodebugmode) cout << h_deltaz_q2_data_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << "\nprph:\t\t\t\t";

        for(Int_t j=0; j<number_Q2bins; j++) 
            if (nodebugmode) cout << h_deltaz_q2_prph_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << endl << endl;

        if (nodebugmode) cout << " ---------- data dz in bins of x ------------" << endl;
        for(Int_t i=0; i<n_periods; i++) 
        {
            if (nodebugmode) cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
            for(Int_t j=0; j<number_xbins; j++) 
                if (nodebugmode) cout << h_deltaz_x_data[j][i]->GetEntries() << "\t\t";
            if (nodebugmode) cout << endl;
        } // for i over periods
        if (nodebugmode) cout << "sum:\t\t\t\t";
        for(Int_t j=0; j<number_xbins; j++) 
            if (nodebugmode) cout << h_deltaz_x_data_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << "\nprph:\t\t\t\t";
        for(Int_t j=0; j<number_xbins; j++) 
            if (nodebugmode) cout << h_deltaz_x_prph_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << endl << endl;

        if (nodebugmode) cout << " ---------- data dz in bins of et_jet ------------" << endl;
        for(Int_t i=0; i<n_periods; i++) 
        {
            if (nodebugmode) cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
            for(Int_t j=0; j<number_et_jetbins; j++)
                if (nodebugmode) cout << h_deltaz_et_jet_data[j][i]->GetEntries() << "\t\t";
            if (nodebugmode) cout << endl;
        } // for i over periods
        if (nodebugmode) cout << "sum:\t\t\t\t";
        for(Int_t j=0; j<number_et_jetbins; j++) 
            if (nodebugmode) cout << h_deltaz_et_jet_data_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << "\nprph:\t\t\t\t";
        for(Int_t j=0; j<number_et_jetbins; j++) 
            if (nodebugmode) cout << h_deltaz_et_jet_prph_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << endl << endl;

        if (nodebugmode) cout << " ---------- data dz in bins of eta_jet ------------" << endl;
        for(Int_t i=0; i<n_periods; i++) 
        {
            if (nodebugmode) cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
            for(Int_t j=0; j<number_eta_jetbins; j++) 
                if (nodebugmode) cout << h_deltaz_eta_jet_data[j][i]->GetEntries() << "\t\t";
            if (nodebugmode) cout << endl;
        } // for i over periods
        if (nodebugmode) cout << "sum:\t\t\t\t";
        for(Int_t j=0; j<number_eta_jetbins; j++) 
            if (nodebugmode) cout << h_deltaz_eta_jet_data_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << "\nprph:\t\t\t\t";
        for(Int_t j=0; j<number_eta_jetbins; j++) 
            if (nodebugmode) cout << h_deltaz_eta_jet_prph_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << endl << endl;


        if (nodebugmode) cout << " ---------- norad dz in bins of et ------------" << endl;
        for(Int_t i=0; i<n_periods; i++) {
            if (nodebugmode) cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
            for(Int_t j=0; j<number_etbins; j++) {
                if (nodebugmode) cout << h_deltaz_et_norad[j][i]->GetEntries() << "\t\t";
            }
            if (nodebugmode) cout << endl;
        } // for i over periods
        if (nodebugmode) cout << "sum:\t\t\t\t";
        for(Int_t j=0; j<number_etbins; j++) 
            if (nodebugmode) cout << h_deltaz_et_norad_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << endl << endl;

        if (nodebugmode) cout << " ---------- norad dz in bins of eta ------------" << endl;
        for(Int_t i=0; i<n_periods; i++) {
            if (nodebugmode) cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
            for(Int_t j=0; j<number_etabins; j++) {
                if (nodebugmode) cout << h_deltaz_eta_norad[j][i]->GetEntries() << "\t\t";
            }
            if (nodebugmode) cout << endl;
        } // for i over periods
        if (nodebugmode) cout << "sum:\t\t\t\t";
        for(Int_t j=0; j<number_etabins; j++) 
            if (nodebugmode) cout << h_deltaz_eta_norad_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << endl << endl;

        if (nodebugmode) cout << " ---------- norad dz in bins of q2 ------------" << endl;
        for(Int_t i=0; i<n_periods; i++) {
            if (nodebugmode) cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
            for(Int_t j=0; j<number_Q2bins; j++) {
                if (nodebugmode) cout << h_deltaz_q2_norad[j][i]->GetEntries() << "\t\t";
            }
            if (nodebugmode) cout << endl;
        } // for i over periods
        if (nodebugmode) cout << "sum:\t\t\t\t";
        for(Int_t j=0; j<number_Q2bins; j++) 
            if (nodebugmode) cout << h_deltaz_q2_norad_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << endl << endl;

        if (nodebugmode) cout << " ---------- norad dz in bins of x ------------" << endl;
        for(Int_t i=0; i<n_periods; i++) {
            if (nodebugmode) cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
            for(Int_t j=0; j<number_xbins; j++) {
                if (nodebugmode) cout << h_deltaz_x_norad[j][i]->GetEntries() << "\t\t";
            }
            if (nodebugmode) cout << endl;
        } // for i over periods
        if (nodebugmode) cout << "sum:\t\t\t\t";
        for(Int_t j=0; j<number_xbins; j++) 
            if (nodebugmode) cout << h_deltaz_x_norad_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << endl << endl;

        if (nodebugmode) cout << " ---------- norad dz in bins of et_jet ------------" << endl;
        for(Int_t i=0; i<n_periods; i++) {
            if (nodebugmode) cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
            for(Int_t j=0; j<number_et_jetbins; j++) {
                if (nodebugmode) cout << h_deltaz_et_jet_norad[j][i]->GetEntries() << "\t\t";
            }
            if (nodebugmode) cout << endl;
        } // for i over periods
        if (nodebugmode) cout << "sum:\t\t\t\t";
        for(Int_t j=0; j<number_et_jetbins; j++) 
            if (nodebugmode) cout << h_deltaz_et_jet_norad_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << endl << endl;

        if (nodebugmode) cout << " ---------- norad dz in bins of eta_jet ------------" << endl;
        for(Int_t i=0; i<n_periods; i++) {
            if (nodebugmode) cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
            for(Int_t j=0; j<number_eta_jetbins; j++) {
                if (nodebugmode) cout << h_deltaz_eta_jet_norad[j][i]->GetEntries() << "\t\t";
            }
            if (nodebugmode) cout << endl;
        } // for i over periods
        if (nodebugmode) cout << "sum:\t\t\t\t";
        for(Int_t j=0; j<number_eta_jetbins; j++) 
            if (nodebugmode) cout << h_deltaz_eta_jet_norad_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << endl << endl;

        if (nodebugmode) cout << " ---------- rad dz in bins of et ------------" << endl;
        for(Int_t i=0; i<n_periods; i++) {
            if (nodebugmode) cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
            for(Int_t j=0; j<number_etbins; j++) {
                if (nodebugmode) cout << h_deltaz_et_rad[j][i]->GetEntries() << "\t\t";
            }
            if (nodebugmode) cout << endl;
        } // for i over periods
        if (nodebugmode) cout << "sum:\t\t\t\t";
        for(Int_t j=0; j<number_etbins; j++) 
            if (nodebugmode) cout << h_deltaz_et_rad_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << endl << endl;

        if (nodebugmode) cout << " ---------- rad dz in bins of eta ------------" << endl;
        for(Int_t i=0; i<n_periods; i++) {
            if (nodebugmode) cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
            for(Int_t j=0; j<number_etabins; j++) {
                if (nodebugmode) cout << h_deltaz_eta_rad[j][i]->GetEntries() << "\t\t";
            }
            if (nodebugmode) cout << endl;
        } // for i over periods
        if (nodebugmode) cout << "sum:\t\t\t\t";
        for(Int_t j=0; j<number_etabins; j++) 
            if (nodebugmode) cout << h_deltaz_eta_rad_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << endl << endl;

        if (nodebugmode) cout << " ---------- rad dz in bins of q2 ------------" << endl;
        for(Int_t i=0; i<n_periods; i++) {
            if (nodebugmode) cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
            for(Int_t j=0; j<number_Q2bins; j++) {
                if (nodebugmode) cout << h_deltaz_q2_rad[j][i]->GetEntries() << "\t\t";
            }
            if (nodebugmode) cout << endl;
        } // for i over periods
        if (nodebugmode) cout << "sum:\t\t\t\t";
        for(Int_t j=0; j<number_Q2bins; j++) 
            if (nodebugmode) cout << h_deltaz_q2_rad_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << endl << endl;

        if (nodebugmode) cout << " ---------- rad dz in bins of x ------------" << endl;
        for(Int_t i=0; i<n_periods; i++) {
            if (nodebugmode) cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
            for(Int_t j=0; j<number_xbins; j++) {
                if (nodebugmode) cout << h_deltaz_x_rad[j][i]->GetEntries() << "\t\t";
            }
            if (nodebugmode) cout << endl;
        } // for i over periods
        if (nodebugmode) cout << "sum:\t\t\t\t";
        for(Int_t j=0; j<number_xbins; j++) 
            if (nodebugmode) cout << h_deltaz_x_rad_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << endl << endl;

        if (nodebugmode) cout << " ---------- rad dz in bins of et_jet ------------" << endl;
        for(Int_t i=0; i<n_periods; i++) {
            if (nodebugmode) cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
            for(Int_t j=0; j<number_et_jetbins; j++) {
                if (nodebugmode) cout << h_deltaz_et_jet_rad[j][i]->GetEntries() << "\t\t";
            }
            if (nodebugmode) cout << endl;
        } // for i over periods
        if (nodebugmode) cout << "sum:\t\t\t\t";
        for(Int_t j=0; j<number_et_jetbins; j++) 
            if (nodebugmode) cout << h_deltaz_et_jet_rad_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << endl << endl;

        if (nodebugmode) cout << " ---------- rad dz in bins of eta_jet ------------" << endl;
        for(Int_t i=0; i<n_periods; i++) {
            if (nodebugmode) cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t\t";
            for(Int_t j=0; j<number_eta_jetbins; j++) {
                if (nodebugmode) cout << h_deltaz_eta_jet_rad[j][i]->GetEntries() << "\t\t";
            }
            if (nodebugmode) cout << endl;
        } // for i over periods
        if (nodebugmode) cout << "sum:\t\t\t\t";
        for(Int_t j=0; j<number_eta_jetbins; j++) 
            if (nodebugmode) cout << h_deltaz_eta_jet_rad_sum[j]->GetEntries() << "\t\t";
        if (nodebugmode) cout << endl << endl;


        for(Int_t j=0; j<n_cross; j++) 
        {
            if (nodebugmode) cout << " ---------- Profile  " << s_var[j] << "  ------------" << endl;
            if (nodebugmode) cout << "data_det\tnorad_det\trad_det\tnorad_had\trad_had\tnorad_hd\trad_hd" << endl;
            for(Int_t i=0; i<n_periods; i++) 
            {
                if (nodebugmode) cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t";
                if (nodebugmode) cout << prof_det_data[j][i]->GetEntries() << "\t"
                    << prof_det_norad[j][i]->GetEntries() << "\t"
                    << prof_det_rad[j][i]->GetEntries() << "\t"
                    << prof_had_norad[j][i]->GetEntries() << "\t"
                    << prof_had_rad[j][i]->GetEntries() << "\t"
                    << prof_hd_norad[j][i]->GetEntries() << "\t"
                    << prof_hd_rad[j][i]->GetEntries() << endl;
            }
            if (nodebugmode) cout << "sum:\t\t\t";
            if (nodebugmode) cout << prof_det_data_sum[j]->GetEntries() << "\t"
                << prof_det_norad_sum[j]->GetEntries() << "\t"
                << prof_det_rad_sum[j]->GetEntries() << "\t"
                << prof_had_norad_sum[j]->GetEntries() << "\t"
                << prof_had_rad_sum[j]->GetEntries() << "\t"
                << prof_hd_norad_sum[j]->GetEntries() << "\t"
                << prof_hd_rad_sum[j]->GetEntries() << endl;
            if (nodebugmode) cout << "prph:\t\t\t";
            if (nodebugmode) cout << "det: " << prof_det_prph_sum[j]->GetEntries() << "\thad: " << prof_had_prph_sum[j]->GetEntries() << "\thd: " << prof_hd_prph_sum[j]->GetEntries() << endl;
        }


        for(Int_t j = 0; j < n_cross; j++) 
        {
            if (nodebugmode) cout << " ---------- Histogram  " << s_var[j] << "  ------------" << endl;
            if (nodebugmode) cout << "data_det\tnorad_det\trad_det\trad_had\trad_hd" << endl;
            for(Int_t i=0; i<n_periods; i++) {
                if (nodebugmode) cout << s_periods[i] << "\t" << lumi_data[i] << "\t" << lumi_mc_bg[i] <<  ":\t";
                if (nodebugmode) cout << h_det_data[j][i]->GetEntries() << "\t"
                    << h_det_norad[j][i]->GetEntries() << "\t"
                    << h_det_rad[j][i]->GetEntries() << "\t"
                    << h_had_rad[j][i]->GetEntries() << "\t"
                    << h_hd_rad[j][i]->GetEntries() << endl;
            }
            if (nodebugmode) cout << "sum:\t\t\t";
            if (nodebugmode) cout << h_det_data_sum[j]->GetEntries() << "\t"
                << h_det_norad_sum[j]->GetEntries() << "\t"
                << h_det_rad_sum[j]->GetEntries() << "\t"
                << h_had_rad_sum[j]->GetEntries() << "\t"
                << h_hd_rad_sum[j]->GetEntries() << endl;
            if (nodebugmode) cout << "prph:\t\t\t";
            if (nodebugmode) cout << "det: " << h_det_prph_sum[j]->GetEntries() << "\thad: " << h_had_prph_sum[j]->GetEntries() << "\thd: " << h_hd_prph_sum[j]->GetEntries() << endl;
        }  
    }
    */
}

void Hist::PlotAcceptance() 
{
    

    for(Int_t i = 0; i < n_cross; i++)  //    h_acceptance_prph, h_acceptance_rad
    {
        h_acceptance_rad[i] = (TH1D*)h_det_rad_sum[i]->Clone();      //     h_acceptance_rad[i]->Sumw2();
        h_acceptance_rad[i]->SetName(TString("h_acceptance_rad_") + s_var[i]);      // LL_det / LL_had
        h_acceptance_rad[i]->Divide(h_had_rad_sum[i]); //?
        h_acceptance_rad[i]->SetMarkerStyle(20);
        h_acceptance_rad[i]->SetMarkerSize(0.7);

        h_acceptance_prph[i] = (TH1D*)h_det_prph_sum[i]->Clone();//     h_acceptance_prph[i]->Sumw2();
        h_acceptance_prph[i]->SetName(TString("h_acceptance_prph_") + s_var[i]);    // QQ_det / QQ_had
        h_acceptance_prph[i]->Divide(h_had_prph_sum[i]);
        h_acceptance_prph[i]->SetMarkerStyle(24);
        h_acceptance_prph[i]->SetMarkerSize(0.7);

        if (h_had_rad_sum[i]->GetBinContent(1)==0)
        {

            h_acceptance_rad[i]->SetBinContent(1, h_acceptance_prph[i]->GetBinContent(1));
            h_acceptance_rad[i]->SetBinError(1, h_acceptance_prph[i]->GetBinError(1));
            dout(s_var[i] ,"redorad to " ,h_acceptance_rad[i]->GetBinContent(1),h_acceptance_rad[i]->GetBinError(1));
        }
        if (nodebugmode) cout << "acceptance " << h_acceptance_rad[i]->GetName() << endl;
        if (s_var[i].EqualTo("xp") || s_var[i].EqualTo("deta") || s_var[i].EqualTo("deta_e_ph"))
        {
            if (nodebugmode) dout(s_var[i], "haccLL=", h_det_rad_sum[i]->GetBinContent(1),"/", h_had_rad_sum[i]->GetBinContent(1) );

            TString tempstr, vartex;
            tempstr.Form( s_var[i] + "_levels_LL");
            if (s_var[i].EqualTo("xgamma"))
                vartex.Form("x_{#gamma}");
            else if (s_var[i].EqualTo("xp"))
                vartex.Form("x_{p}");
            else if (s_var[i].EqualTo("deta"))
                vartex.Form("#Delta#eta");
            else if (s_var[i].EqualTo("deta_e_ph"))
                vartex.Form("#Delta#eta_{e,#phi}");
            gStyle->SetOptStat(0);
            TCanvas* c  = new TCanvas("c_"+tempstr, tempstr, 800, 600); 
            
            TH2D *h_window_control = new TH2D(tempstr + "_win", "title", h_had_rad_sum[i]->GetNbinsX(), h_had_rad_sum[i]->GetBinCenter(1)- h_had_rad_sum[i]->GetBinWidth(1)/2, \
            h_had_prph_sum[i]->GetBinCenter(h_had_rad_sum[i]->GetNbinsX()) + h_had_rad_sum[i]->GetBinWidth(h_had_rad_sum[i]->GetNbinsX())/2, 10, 0., h_had_rad_sum[i]->GetMaximum()*1.3);//array_bin[0], array_bin[number_bins - 1]
            c->GetPad(0)->SetTicks(1,1);
            c->GetPad(0)->SetFrameBorderMode(0);
            c->GetPad(0)->SetBorderMode(0);
            c->GetPad(0)->SetFillColor(kWhite);
            c->GetPad(0)->SetGrid(0, 0);
            sign_window(c->GetPad(0), h_window_control, vartex , "entries", "LL MC, " + vartex, "middle");
            h_window_control->GetYaxis()->SetRange(0, h_det_rad_sum[i]->GetMaximum()*1.3);
            h_window_control->Draw();



            h_det_rad_sum[i]->SetLineColor(kBlue);
            h_had_rad_sum[i]->SetLineColor(kRed);
            h_hd_rad_sum[i]->SetLineColor(kMagenta);

            TLegend *leg_acc = new TLegend(0.2, 0.5, 0.6, 0.75);
            leg_acc->SetFillColor(0);
            leg_acc->SetBorderSize(0);
            TString detstring, hadstring, hdstring;
                detstring.Form("det.level (%5.0f events)", h_det_rad_sum[i]->GetSum());
                hadstring.Form("had.level (%5.0f events)", h_had_rad_sum[i]->GetSum());
                hdstring.Form("hd.level (%5.0f events)", h_hd_rad_sum[i]->GetSum());
            leg_acc->AddEntry(h_det_rad_sum[i], detstring, "l");// P: draw polymarker associated with TAttMarker if obj inherits from TAttMarker
            leg_acc->AddEntry(h_had_rad_sum[i], hadstring, "l"); 
            leg_acc->AddEntry(h_hd_rad_sum[i], hdstring, "l"); 

            h_det_rad_sum[i]->Draw("same");
            h_had_rad_sum[i]->Draw("same");
            h_hd_rad_sum[i]->Draw("same");
            leg_acc->Draw("same");
            c->Print(tempstr + ".png");


            tempstr.Form( s_var[i] + "_levels_QQ");
            c  = new TCanvas("c_" + tempstr, tempstr, 800, 600); 
            h_window_control = new TH2D(tempstr + "_win", "title", h_had_prph_sum[i]->GetNbinsX(), h_had_prph_sum[i]->GetBinCenter(1)- h_had_prph_sum[i]->GetBinWidth(1)/2, \
            h_had_prph_sum[i]->GetBinCenter(h_had_prph_sum[i]->GetNbinsX()) + h_had_prph_sum[i]->GetBinWidth(h_had_prph_sum[i]->GetNbinsX())/2, 10, 0., h_had_prph_sum[i]->GetMaximum()*1.3);//array_bin[0], array_bin[number_bins - 1]
            c->GetPad(0)->SetTicks(1,1);
            c->GetPad(0)->SetFrameBorderMode(0);
            c->GetPad(0)->SetBorderMode(0);
            c->GetPad(0)->SetFillColor(kWhite);
            c->GetPad(0)->SetGrid(0, 0);
            sign_window(c->GetPad(0), h_window_control, vartex , "entries", "QQ MC, " + vartex, "middle");
            h_window_control->GetYaxis()->SetRange(0, h_det_rad_sum[i]->GetMaximum() * 1.3);
            h_window_control->Draw();
            h_det_prph_sum[i]->SetLineColor(kBlue);
            h_det_prph_sum[i]->Draw("same");
            h_had_prph_sum[i]->SetLineColor(kRed);
            h_had_prph_sum[i]->Draw("same");
            h_hd_prph_sum[i]->SetLineColor(kMagenta);
            h_hd_prph_sum[i]->Draw("same");
            leg_acc = new TLegend(0.2, 0.5, 0.6, 0.75);
            leg_acc->SetFillColor(0);
            leg_acc->SetBorderSize(0);
                detstring.Form("det.level (%5.0f events)", h_det_prph_sum[i]->GetSum());
                hadstring.Form("had.level (%5.0f events)", h_had_prph_sum[i]->GetSum());
                hdstring.Form("hd.level (%5.0f events)", h_hd_rad_sum[i]->GetSum());
            leg_acc->AddEntry(h_det_prph_sum[i], detstring, "l");// P: draw polymarker associated with TAttMarker if obj inherits from TAttMarker
            leg_acc->AddEntry(h_had_prph_sum[i], hadstring, "l"); 
            leg_acc->AddEntry(h_hd_prph_sum[i], hdstring, "l"); 
            leg_acc->Draw("same");
            c->Print(tempstr + ".png");

            if (nodebugmode) cout << "LL:   det = " << h_det_rad_sum[i]->GetSum() <<" had = "<<  h_had_rad_sum[i]->GetSum() << " hd = "<<   h_hd_rad_sum[i]->GetSum() <<endl
                << "QQ:   det = " << h_det_prph_sum[i]->GetSum() <<" had = "<<  h_had_prph_sum[i]->GetSum() << " hd = "<<   h_hd_prph_sum[i]->GetSum() <<endl;
            if (nodebugmode) cout << "LL[1]:   det = " << h_det_rad_sum[i]->GetBinContent(1) <<" had = "<<  h_had_rad_sum[i]->GetBinContent(1) << " hd = "<<   h_hd_rad_sum[i]->GetBinContent(1) <<endl
                << "QQ[1]:   det = " << h_det_prph_sum[i]->GetBinContent(1) <<" had = "<<  h_had_prph_sum[i]->GetBinContent(1) << " hd = "<<   h_hd_prph_sum[i]->GetBinContent(1) <<endl;
        }
        /*
        if (s_var[i].EqualTo("xgamma"))
        { 
            gStyle->SetOptStat(0);
            TCanvas* c  = new TCanvas("c_xgamma_levels_LL", "x_gamma_levels_LL", 800, 600); 
            //c->GetPad(0)->SetTitlePS("c_xgamma_levels_LL");

            TH2D *h_window_control = new TH2D("x_gamma_levels_LL_win", "title", h_had_rad_sum[i]->GetNbinsX(), h_had_rad_sum[i]->GetBinCenter(1)- h_had_rad_sum[i]->GetBinWidth(1)/2, \
            h_had_prph_sum[i]->GetBinCenter(h_had_rad_sum[i]->GetNbinsX()) + h_had_rad_sum[i]->GetBinWidth(h_had_rad_sum[i]->GetNbinsX())/2, 10, 0., h_had_rad_sum[i]->GetMaximum()*1.3);//array_bin[0], array_bin[number_bins - 1]
            c->GetPad(0)->SetTicks(1,1);
            c->GetPad(0)->SetFrameBorderMode(0);
            c->GetPad(0)->SetBorderMode(0);
            c->GetPad(0)->SetFillColor(kWhite);
            c->GetPad(0)->SetGrid(0, 0);
            sign_window(c->GetPad(0), h_window_control, "x_{#gamma}" , "entries", "LL MC, x_{#gamma}", "middle");
            h_window_control->GetYaxis()->SetRange(0, h_det_rad_sum[i]->GetMaximum()*1.3);
            h_window_control->Draw();



            h_det_rad_sum[i]->SetLineColor(kBlue);
            h_had_rad_sum[i]->SetLineColor(kRed);
            h_hd_rad_sum[i]->SetLineColor(kMagenta);

            TLegend *leg_acc = new TLegend(0.2, 0.5, 0.6, 0.75);
            leg_acc->SetFillColor(0);
            leg_acc->SetBorderSize(0);
            TString detstring, hadstring, hdstring;
                detstring.Form("det.level (%5.0f events)", h_det_rad_sum[i]->GetSum());
                hadstring.Form("had.level (%5.0f events)", h_had_rad_sum[i]->GetSum());
                hdstring.Form("hd.level (%5.0f events)", h_hd_rad_sum[i]->GetSum());
            leg_acc->AddEntry(h_det_rad_sum[i], detstring, "l");// P: draw polymarker associated with TAttMarker if obj inherits from TAttMarker
            leg_acc->AddEntry(h_had_rad_sum[i], hadstring, "l"); 
            leg_acc->AddEntry(h_hd_rad_sum[i], hdstring, "l"); 

            h_det_rad_sum[i]->Draw("same");
            h_had_rad_sum[i]->Draw("same");
            h_hd_rad_sum[i]->Draw("same");
            leg_acc->Draw("same");
            c->Print("x_gamma_levels_LL.png");


            c  = new TCanvas("c_xgamma_levels_QQ", "x_gamma_levels_QQ", 800, 600); 
            h_window_control = new TH2D("x_gamma_levels_QQ_win", "title", h_had_prph_sum[i]->GetNbinsX(), h_had_prph_sum[i]->GetBinCenter(1)- h_had_prph_sum[i]->GetBinWidth(1)/2, \
            h_had_prph_sum[i]->GetBinCenter(h_had_prph_sum[i]->GetNbinsX()) + h_had_prph_sum[i]->GetBinWidth(h_had_prph_sum[i]->GetNbinsX())/2, 10, 0., h_had_prph_sum[i]->GetMaximum()*1.3);//array_bin[0], array_bin[number_bins - 1]
            c->GetPad(0)->SetTicks(1,1);
            c->GetPad(0)->SetFrameBorderMode(0);
            c->GetPad(0)->SetBorderMode(0);
            c->GetPad(0)->SetFillColor(kWhite);
            c->GetPad(0)->SetGrid(0, 0);
            sign_window(c->GetPad(0), h_window_control, "x_{#gamma}" , "entries", "QQ MC, x_{#gamma}", "middle");
            h_window_control->GetYaxis()->SetRange(0, h_det_rad_sum[i]->GetMaximum() * 1.3);
            h_window_control->Draw();
            h_det_prph_sum[i]->SetLineColor(kBlue);
            h_det_prph_sum[i]->Draw("same");
            h_had_prph_sum[i]->SetLineColor(kRed);
            h_had_prph_sum[i]->Draw("same");
            h_hd_prph_sum[i]->SetLineColor(kMagenta);
            h_hd_prph_sum[i]->Draw("same");
            leg_acc = new TLegend(0.2, 0.5, 0.6, 0.75);
            leg_acc->SetFillColor(0);
            leg_acc->SetBorderSize(0);
                detstring.Form("det.level (%5.0f events)", h_det_prph_sum[i]->GetSum());
                hadstring.Form("had.level (%5.0f events)", h_had_prph_sum[i]->GetSum());
                hdstring.Form("hd.level (%5.0f events)", h_hd_rad_sum[i]->GetSum());
            leg_acc->AddEntry(h_det_prph_sum[i], detstring, "l");// P: draw polymarker associated with TAttMarker if obj inherits from TAttMarker
            leg_acc->AddEntry(h_had_prph_sum[i], hadstring, "l"); 
            leg_acc->AddEntry(h_hd_prph_sum[i], hdstring, "l"); 
            leg_acc->Draw("same");
            c->Print("x_gamma_levels_QQ.png");
            if (nodebugmode) cout << "LL:   det = " << h_det_rad_sum[i]->GetSum() <<" had = "<<  h_had_rad_sum[i]->GetSum() << " hd = "<<   h_hd_rad_sum[i]->GetSum() <<endl
                << "QQ:   det = " << h_det_prph_sum[i]->GetSum() <<" had = "<<  h_had_prph_sum[i]->GetSum() << " hd = "<<   h_hd_prph_sum[i]->GetSum() <<endl;
        }
        */
        if (s_var[i].EqualTo("xp"))
            for(Int_t j = 0; j < h_acceptance_rad[i]->GetNbinsX(); j++) //Побиновый вывод на экран
                if (nodebugmode) cout << "bin " << j << ": " << h_acceptance_rad[i]->GetBinContent(j+1) << " = "
                    << h_det_rad_sum[i]->GetBinContent(j+1) << " / "
                    << h_had_rad_sum[i]->GetBinContent(j+1) << endl;

        if (s_var[i].EqualTo("xp"))
            for(Int_t j = 0; j < h_acceptance_rad[i]->GetNbinsX(); j++) //Побиновый вывод на экран
                if (!nodebugmode) cout << "bin " << j << ": " << h_acceptance_rad[i]->GetBinContent(j+1) << " "
                    << h_acceptance_prph[i]->GetBinContent(j+1) << endl;
        /*
            h_acceptance_prph[i] = (TH1D*)h_det_prph_sum[i]->Clone();//     h_acceptance_prph[i]->Sumw2();
            h_acceptance_prph[i]->SetName(TString("h_acceptance_prph_") + s_var[i]);    // QQ_det / QQ_had
            h_acceptance_prph[i]->Divide(h_had_prph_sum[i]);
            h_acceptance_prph[i]->SetMarkerStyle(24);
            h_acceptance_prph[i]->SetMarkerSize(0.7);
        */
        if (s_var[i].EqualTo("xgamma"))
            for(Int_t j=0; j<h_acceptance_prph[i]->GetNbinsX(); j++)
                if (nodebugmode) cout << "acceptance " << s_var[i] << " bin " << j << ": " << h_acceptance_prph[i]->GetBinContent(j+1) 
                    << ", det = " << h_det_prph_sum[i]->GetBinContent(j+1) << ", had = " << h_had_prph_sum[i]->GetBinContent(j+1) << endl
                    << "acceptance correction: " << 1./h_acceptance_prph[i]->GetBinContent(j+1) << endl;


    }

    TH2D* h_window_acc[n_cross];
    h_window_acc[0] = new TH2D("h_window_acc_et", "", 10, 4., 15., 10, 0., 1.4);
    h_window_acc[1] = new TH2D("h_window_acc_eta", "", 10, -0.7, 0.9, 10, 0., 1.4);
    h_window_acc[2] = new TH2D("h_window_acc_q2", "", 10, 4., 350., 10, 0., 1.4);
    h_window_acc[3] = new TH2D("h_window_acc_x", "", 10, 1.5e-4, 0.15, 10, 0., 1.4);
    h_window_acc[4] = new TH2D("h_window_acc_et_jet", "", 10, 2.5, 35., 10, 0., 1.4);
    h_window_acc[5] = new TH2D("h_window_acc_eta_jet", "", 10, -1.5, 1.8, 10, 0., 1.4);
    h_window_acc[6] = new TH2D("h_window_acc_xgamma", "", 10, 0., 1., 10, 0., 1.2*max(h_acceptance_prph[6]->GetMaximum() + h_acceptance_prph[6]->GetBinError(h_acceptance_prph[6]->GetMaximumBin()), h_acceptance_rad[6]->GetMaximum() + h_acceptance_prph[6]->GetBinError(h_acceptance_prph[6]->GetMaximumBin())));
    h_window_acc[7] = new TH2D("h_window_acc_xp", "", 10, 0., 0.03, 10, 0., 1.2*max(h_acceptance_prph[7]->GetMaximum() + h_acceptance_prph[7]->GetBinError(h_acceptance_prph[7]->GetMaximumBin()), h_acceptance_rad[7]->GetMaximum() + h_acceptance_prph[7]->GetBinError(h_acceptance_prph[7]->GetMaximumBin())));
    h_window_acc[8] = new TH2D("h_window_acc_dphi", "", 10, 0., 180., 10, 0., 1.2*max(h_acceptance_prph[8]->GetMaximum() + h_acceptance_prph[8]->GetBinError(h_acceptance_prph[8]->GetMaximumBin()), h_acceptance_rad[8]->GetMaximum() + h_acceptance_prph[8]->GetBinError(h_acceptance_prph[8]->GetMaximumBin())));
    h_window_acc[9] = new TH2D("h_window_acc_deta", "", 10, -2.2, 2.7, 10, 0., 1.2*max(h_acceptance_prph[9]->GetMaximum() + h_acceptance_prph[9]->GetBinError(h_acceptance_prph[9]->GetMaximumBin()), h_acceptance_rad[9]->GetMaximum() + h_acceptance_prph[9]->GetBinError(h_acceptance_prph[9]->GetMaximumBin())));
    h_window_acc[10] = new TH2D("h_window_acc_dphi_e_ph", "", 10, 0., 180., 10, 0., 1.2*max(h_acceptance_prph[10]->GetMaximum() + h_acceptance_prph[10]->GetBinError(h_acceptance_prph[10]->GetMaximumBin()), h_acceptance_rad[10]->GetMaximum() + h_acceptance_prph[10]->GetBinError(h_acceptance_prph[10]->GetMaximumBin())));
    h_window_acc[11] = new TH2D("h_window_acc_deta_e_ph", "", 10, -4.5, 0., 10, 0., 1.2*max(h_acceptance_prph[11]->GetMaximum() + h_acceptance_prph[11]->GetBinError(h_acceptance_prph[11]->GetMaximumBin()), h_acceptance_rad[11]->GetMaximum() + h_acceptance_prph[11]->GetBinError(h_acceptance_prph[11]->GetMaximumBin())));

    TCanvas* c_acc  = new TCanvas("c_acc", "Acceptance", 800, 600);
    TCanvas* c_acc_2  = new TCanvas("c_acc_2", "Acceptance", 800, 600);
    c_acc->Divide(3, 2);
    make_clean_pads(c_acc, 6, 0, 0);
    c_acc_2->Divide(3, 2);
    make_clean_pads(c_acc_2, 6, 0, 0);

    sign_window(c_acc->GetPad(1), h_window_acc[0], "", "Acceptance", "", "middle");
    sign_window(c_acc->GetPad(2), h_window_acc[1], "", "Acceptance", "", "middle");
    sign_window(c_acc->GetPad(3), h_window_acc[2], "", "Acceptance", "", "middle");
    sign_window(c_acc->GetPad(4), h_window_acc[3], "", "Acceptance", "", "middle");
    sign_window(c_acc->GetPad(5), h_window_acc[4], "", "Acceptance", "", "middle");
    sign_window(c_acc->GetPad(6), h_window_acc[5], "", "Acceptance", "", "middle");

    sign_window(c_acc_2->GetPad(1), h_window_acc[6], "", "Acceptance", "", "middle");
    sign_window(c_acc_2->GetPad(2), h_window_acc[7], "", "Acceptance", "", "middle");
    sign_window(c_acc_2->GetPad(3), h_window_acc[8], "", "Acceptance", "", "middle");
    sign_window(c_acc_2->GetPad(4), h_window_acc[9], "", "Acceptance", "", "middle");
    sign_window(c_acc_2->GetPad(5), h_window_acc[10], "", "Acceptance", "", "middle");
    sign_window(c_acc_2->GetPad(6), h_window_acc[11], "", "Acceptance", "", "middle");

    TLegend *leg_acc = new TLegend(0.3, 0.2, 0.6, 0.4);
    leg_acc->SetFillColor(0);
    leg_acc->SetBorderSize(0);
    leg_acc->AddEntry(h_acceptance_rad[0], "LL photons", "p");// P: draw polymarker associated with TAttMarker if obj inherits from TAttMarker
    leg_acc->AddEntry(h_acceptance_prph[0], "QQ photons", "p");  

    for(Int_t i = 0; i < n_cross; i++)//Draw acceptance
    {
        if (i==6)
        {
            c_acc->Print("acceptance.eps");
            c_acc->Print("acceptance.png");
            c_acc = c_acc_2;
        }
        c_acc->GetPad(i%6+1)->cd();
        if (i==2 || i==3 || i==4) c_acc->GetPad(i+1)->SetLogx();
        h_window_acc[i]->DrawClone();

        h_acceptance_rad[i]->DrawClone("P E1 X0 SAME");
        /*P  : Draw current marker at each bin except empty bins.
        //E1 : Draw error bars with perpendicular lines at the edges.
        //X0 : When used with one of the "E" option, it suppress the error bar along X as gStyle->SetErrorX(0) would do.
        //https://root.cern.ch/root/html/THistPainter.html
        */

        if (nodebugmode) cout << "before shift: " << h_acceptance_prph[i]->GetXaxis()->GetXmin() << " " 
            << h_acceptance_prph[i]->GetXaxis()->GetXmax() << " first bin center: " 
            << h_acceptance_prph[i]->GetBinCenter(1) <<endl;

        Double_t xmin = h_acceptance_prph[i]->GetXaxis()->GetXmin(),
                 xmax = h_acceptance_prph[i]->GetXaxis()->GetXmax();
        Double_t deltax = xmax - xmin;
        h_acceptance_prph[i]->GetXaxis()->SetLimits(xmin + 0.9 * deltax, xmax + 0.9 * deltax);
        /*
           h_acceptance_prph[i]->GetXaxis()->SetXmin(xmin + 0.9*deltax);
           h_acceptance_prph[i]->GetXaxis()->SetXmax(xmax + 0.9*deltax);
           */
        if (nodebugmode) cout << "after shift: " << h_acceptance_prph[i]->GetXaxis()->GetXmin() << " " 
            << h_acceptance_prph[i]->GetXaxis()->GetXmax() << " first bin center: " 
            << h_acceptance_prph[i]->GetBinCenter(1)<< endl;
        h_acceptance_prph[i]->DrawClone("P E X0 SAME");

        if (i==3 || i==9) leg_acc->Draw();
        TPaveText *t = new TPaveText(0.4, 0.9, 0.6, 1.0, "brNDC"); // left-up
        t->AddText(s_title[i]);
        t->Draw();
    }

    c_acc->Print("acceptance_2.eps");
    c_acc->Print("acceptance_2.png");

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
    h_window_pur[6] = new TH2D("h_window_pur_xgamma", "", 10, 0., 1., 10, 0., 1.4);
    h_window_pur[7] = new TH2D("h_window_pur_xp", "", 10, 0., 0.03, 10, 0., 1.4);
    h_window_pur[8] = new TH2D("h_window_pur_dphi", "", 10, 0., 180., 10, 0., 1.4);
    h_window_pur[9] = new TH2D("h_window_pur_deta", "", 10, -2.2, 2.7, 10, 0., 1.4);
    h_window_pur[10] = new TH2D("h_window_pur_dphi_e_ph", "", 10, 0., 180., 10, 0., 1.4);
    h_window_pur[11] = new TH2D("h_window_pur_deta_e_ph", "", 10, -4.5, 0., 10, 0., 1.4);

    TCanvas* c_pur  = new TCanvas("c_pur", "Purity", 800, 600);    
    c_pur->Divide(3, 2);
    make_clean_pads(c_pur, 6, 0, 0);
    TCanvas* c_pur_2  = new TCanvas("c_pur_2", "Purity", 800, 600);    
    c_pur_2->Divide(3, 2);
    make_clean_pads(c_pur_2, 6, 0, 0);

    sign_window(c_pur->GetPad(1), h_window_pur[0], "", "Purity", "", "middle");
    sign_window(c_pur->GetPad(2), h_window_pur[1], "", "Purity", "", "middle");
    sign_window(c_pur->GetPad(3), h_window_pur[2], "", "Purity", "", "middle");
    sign_window(c_pur->GetPad(4), h_window_pur[3], "", "Purity", "", "middle");
    sign_window(c_pur->GetPad(5), h_window_pur[4], "", "Purity", "", "middle");
    sign_window(c_pur->GetPad(6), h_window_pur[5], "", "Purity", "", "middle");

    sign_window(c_pur_2->GetPad(1), h_window_pur[6], "", "Purity", "", "middle");
    sign_window(c_pur_2->GetPad(2), h_window_pur[7], "", "Purity", "", "middle");
    sign_window(c_pur_2->GetPad(3), h_window_pur[8], "", "Purity", "", "middle");
    sign_window(c_pur_2->GetPad(4), h_window_pur[9], "", "Purity", "", "middle");
    sign_window(c_pur_2->GetPad(5), h_window_pur[10], "", "Purity", "", "middle");
    sign_window(c_pur_2->GetPad(6), h_window_pur[11], "", "Purity", "", "middle");

    for(Int_t i = 0; i < n_cross; i++) // Строятся h_purity_rad h_purity_prph
    {
        h_purity_rad[i] = (TH1D*)h_hd_rad_sum[i]->Clone(); //? h_purity_rad[i]->Sumw2();
        h_purity_rad[i]->SetName(TString("h_purity_rad_") + s_var[i]);      
        h_purity_rad[i]->Divide(h_det_rad_sum[i]);
        h_purity_rad[i]->SetMarkerStyle(20);
        h_purity_rad[i]->SetMarkerSize(0.7);
        if (nodebugmode) cout << "purity " << h_purity_rad[i]->GetName() << endl;
        for(Int_t j = 0; j < h_purity_rad[i]->GetNbinsX(); j++)
            if (nodebugmode) cout << "bin " << j << ": " << h_det_rad_sum[i]->GetBinContent(j+1) << " "
                << h_had_rad_sum[i]->GetBinContent(j+1) << endl;
        //   if (nodebugmode) cout << h_purity_rad[i] << GetBinContent(j+1) << endl;

        h_purity_prph[i] = (TH1D*)h_hd_prph_sum[i]->Clone();//     h_purity_prph[i]->Sumw2();
        h_purity_prph[i]->SetName(TString("h_purity_prph_") + s_var[i]);
        h_purity_prph[i]->Divide(h_det_prph_sum[i]);
        h_purity_prph[i]->SetMarkerStyle(24);
        h_purity_prph[i]->SetMarkerSize(0.7);

        for(Int_t j = 0; j < h_purity_prph[i]->GetNbinsX(); j++)
            if (nodebugmode) cout << "purity " << s_var[i] << " bin " << j << ": " << h_purity_prph[i]->GetBinContent(j+1) 
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
        Int_t j = 0;
        if (i==6)
        {
            c_pur->Print("purity.eps");
            c_pur->Print("purity.png");
            c_pur = c_pur_2;
        }
        c_pur->GetPad(i%6+1)->cd();
        
        if(i==2 || i==3 || i==4) c_pur->GetPad(i+1)->SetLogx();
        
        h_window_pur[i]->DrawClone();
        
        h_purity_rad[i]->DrawClone("P E1 X0 SAME");
        
        // Shift for h_purity_prph
        if (nodebugmode) cout << "before shift: " << h_purity_prph[i]->GetXaxis()->GetXmin() << " " << h_purity_prph[i]->GetXaxis()->GetXmax() << " first bin center: " << h_purity_prph[i]->GetBinCenter(1) <<endl;
        Double_t xmin = h_purity_prph[i]->GetXaxis()->GetXmin(),
             xmax = h_purity_prph[i]->GetXaxis()->GetXmax();
        Double_t deltax = xmax - xmin;
        h_purity_prph[i]->GetXaxis()->SetLimits(xmin + 0.9*deltax, xmax+0.9*deltax);
        if (nodebugmode) cout << "after shift: " << h_purity_prph[i]->GetXaxis()->GetXmin() << " " << h_purity_prph[i]->GetXaxis()->GetXmax() << " first bin center: " << h_purity_prph[i]->GetBinCenter(1)<< endl;
        h_purity_prph[i]->DrawClone("P E X0 SAME");
        if (nodebugmode) cout << "after drawing: " << h_purity_prph[i]->GetXaxis()->GetXmin() << " " << h_purity_prph[i]->GetXaxis()->GetXmax() << " first bin center: " << h_purity_prph[i]->GetBinCenter(1)<< endl;
        if(i%6==3) leg_pur->Draw();
        TPaveText *t = new TPaveText(0.4, 0.9, 0.6, 1.0, "brNDC"); // left-up
        t->AddText(s_title[i]);
        t->Draw();
    }
    c_pur->Print("purity_2.eps");
    c_pur->Print("purity_2.png");

}
void Hist::set_hist_atributes(Int_t number, TString name, TString dir, TString xaxis, Double_t xmin, Double_t xmax, Double_t ymin, Bool_t logy, Int_t rebin)
{
    if(dir!= "")
        s_hist[number] = dir + "/" + name;
    else
        s_hist[number] = name;

    s_xaxis[number] = xaxis;
    hist_xmin[number] = xmin;
    hist_xmax[number] = xmax;
    hist_ymin[number] = ymin;
    hist_logy[number] = logy;
    hist_rebin[number] = rebin;
}
void Hist::PlotFitInBinsOfCrossSec() 
{
    
    /*020715 ПЕРЕПИСАТЬ ЧЕРЕЗ ФУНКЦИЮ/КЛАСС*/
    ///////////////////////////////////////////////////////
    //
    //          dz in bins of Et
    //
    ///////////////////////////////////////////////////////
    {
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
            /*if (nodebugmode) cout << "draw " << i << endl;
            if (nodebugmode) cout << "et bin# " << i << " " << h_deltaz_et_data_sum[i]->Integral() << " " << h_deltaz_et_res[i]->Integral() << " " 
                << h_deltaz_et_prph_sum[i]->Integral() << " " 
                << h_deltaz_et_rad_sum[i]->Integral() << " " << h_deltaz_et_norad_sum[i]->Integral() << endl;   */ 
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
            /*if (nodebugmode) cout << "dz before shift: " << h_deltaz_et_data_sum[i]->GetXaxis()->GetXmin() 
                << " " << h_deltaz_et_data_sum[i]->GetXaxis()->GetXmax() 
                << " first bin center: " << h_deltaz_et_data_sum[i]->GetBinCenter(1) <<endl;*/
            Double_t xmin = h_deltaz_et_data_sum[i]->GetXaxis()->GetXmin();
            Double_t xmax = h_deltaz_et_data_sum[i]->GetXaxis()->GetXmax();
            Double_t deltax = xmax-xmin;
            h_deltaz_et_data_sum[i]->GetXaxis()->SetLimits(xmin + 0.01*deltax, xmax+0.01*deltax);
            /*if (nodebugmode) cout << "dz after shift: " << h_deltaz_et_data_sum[i]->GetXaxis()->GetXmin() << " " 
                << h_deltaz_et_data_sum[i]->GetXaxis()->GetXmax() 
                << " first bin center: " << h_deltaz_et_data_sum[i]->GetBinCenter(1) <<endl;*/
            h_deltaz_et_data_sum[i]->Draw("P E X0 SAME");//https://root.cern.ch/root/html/THistPainter.html
            c_dz_et->GetPad(i+1)->RedrawAxis();
            pave_et[i]->Draw();
        }
        c_dz_et->Print("c_dz_et.eps");  
        c_dz_et->Print("c_dz_et.png");  
    }
    ///////////////////////////////////////////////////////
    //
    //          dz in bins of Eta
    //
    ///////////////////////////////////////////////////////
    {
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
            s2_eta[i].Form("QQ phot. fraction: %.2f #pm %.2f", param_eta[i], param_err_eta[i]);
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
            /*if (nodebugmode) cout << "draw " << i << endl;*/
            /*if (nodebugmode) cout << "eta bin# " << i << " " << h_deltaz_eta_data_sum[i]->Integral() << " " << h_deltaz_eta_res[i]->Integral() << " " 
                << h_deltaz_eta_prph_sum[i]->Integral() << " " 
                << h_deltaz_eta_rad_sum[i]->Integral() << " " << h_deltaz_eta_norad_sum[i]->Integral() << endl;*/    
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
    }
    ///////////////////////////////////////////////////////
    //
    //          dz in bins of Q2
    //
    ///////////////////////////////////////////////////////
    {
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
            s2_q2[i].Form("QQ phot. fraction: %.2f #pm %.2f", param_q2[i], param_err_q2[i]);
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
            /*if (nodebugmode) cout << "draw " << i << endl;*/
            /*if (nodebugmode) cout << "q2 bin# " << i << " " << h_deltaz_q2_data_sum[i]->Integral() << " " << h_deltaz_q2_res[i]->Integral() << " " 
                << h_deltaz_q2_prph_sum[i]->Integral() << " " 
                << h_deltaz_q2_rad_sum[i]->Integral() << " " << h_deltaz_q2_norad_sum[i]->Integral() << endl;*/    
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
            /*if (nodebugmode) cout << i << " Q2" << endl;*/
        }
        c_dz_q2->Print("c_dz_q2.eps");  
        c_dz_q2->Print("c_dz_q2.png");  
    }
    ///////////////////////////////////////////////////////
    //
    //          dz in bins of X
    //
    ///////////////////////////////////////////////////////
    {
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
            s2_x[i].Form("QQ phot. fraction: %.2f #pm %.2f", param_x[i], param_err_x[i]);
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
            /*if (nodebugmode) cout << "draw " << i << endl;*/
            /*if (nodebugmode) cout << "x bin# " << i << " " << h_deltaz_x_data_sum[i]->Integral() << " " << h_deltaz_x_res[i]->Integral() << " " 
                << h_deltaz_x_prph_sum[i]->Integral() << " " 
                << h_deltaz_x_rad_sum[i]->Integral() << " " << h_deltaz_x_norad_sum[i]->Integral() << endl;*/    
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
    }
    ///////////////////////////////////////////////////////
    //
    //          dz in bins of Et_Jet
    //
    ///////////////////////////////////////////////////////
    {
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
            s2_et_jet[i].Form("QQ phot. fraction: %.2f #pm %.2f", param_et_jet[i], param_err_et_jet[i]);
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
            /*if (nodebugmode) cout << "draw " << i << endl;*/
            /*if (nodebugmode) cout << "et_jet bin# " << i << " " << h_deltaz_et_jet_data_sum[i]->Integral() << " " << h_deltaz_et_jet_res[i]->Integral() << " " 
                << h_deltaz_et_jet_prph_sum[i]->Integral() << " " 
                << h_deltaz_et_jet_rad_sum[i]->Integral() << " " << h_deltaz_et_jet_norad_sum[i]->Integral() << endl;*/    
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
    }
    ///////////////////////////////////////////////////////
    //
    //          dz in bins of Eta_Jet
    //
    ///////////////////////////////////////////////////////
    {
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
            s2_eta_jet[i].Form("QQ phot. fraction: %.2f #pm %.2f", param_eta_jet[i], param_err_eta_jet[i]);
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
            /*if (nodebugmode) cout << "draw " << i << endl;*/
            /*if (nodebugmode) cout << "eta_jet bin# " << i << " " << h_deltaz_eta_jet_data_sum[i]->Integral() << " " << h_deltaz_eta_jet_res[i]->Integral() << " " 
                << h_deltaz_eta_jet_prph_sum[i]->Integral() << " " 
                << h_deltaz_eta_jet_rad_sum[i]->Integral() << " " << h_deltaz_eta_jet_norad_sum[i]->Integral() << endl;*/    
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
    }
    ///////////////////////////////////////////////////////
    //
    //          dz in bins of xgamma
    //
    ///////////////////////////////////////////////////////
    {
        PlotControlPlot(param_xgamma, param_err_xgamma, number_xgamma_bins, xgamma_bin, 1, "xgamma", "c_control_xgamma", "x_{#gamma}", "bins of xgamma", "Events", "leftup");
        
        TH2D* h_window_fit_xgamma[number_xgamma_bins];
        Double_t ymax_xgamma[number_xgamma_bins] ;
        for(Int_t i = 0; i < number_xgamma_bins; i++) 
            ymax_xgamma[i] = 1.5 * h_deltaz_xgamma_data_sum[i]->GetMaximum();

        for(Int_t i=0; i<number_xgamma_bins; i++)
        {
            TString s; 
            s.Form("h_window_fit_xgamma_%i", i); 
            h_window_fit_xgamma[i] = new TH2D(s, "", 10, 0., 1.5, 10, 0., ymax_xgamma[i]);
        }

        TPaveText *pave_xgamma[number_xgamma_bins];
        TString s1_xgamma[number_xgamma_bins], s2_xgamma[number_xgamma_bins], s3_xgamma[number_xgamma_bins], s4_xgamma[number_xgamma_bins], s5_xgamma[number_xgamma_bins];
        TText *t1_xgamma[number_xgamma_bins], *t2_xgamma[number_xgamma_bins], *t3_xgamma[number_xgamma_bins], *t4_xgamma[number_xgamma_bins], *t5_xgamma[number_xgamma_bins];

        for(Int_t i = 0; i < number_xgamma_bins; i++) 
        {
            pave_xgamma[i] = new TPaveText(0.5, 0.5, 0.9, 0.9, "NDC");
            pave_xgamma[i]->SetFillColor(0);
            pave_xgamma[i]->SetBorderSize(0);
            s1_xgamma[i].Form("%.1f < x_{#gamma} < %.1f", xgamma_bin[i], xgamma_bin[i+1]);
            s2_xgamma[i].Form("QQ phot. fraction: %.2f #pm %.2f", param_xgamma[i], param_err_xgamma[i]);
            s3_xgamma[i].Form("fit range: bins %i to %i", left_xgamma[i], right_xgamma[i]); 
            s4_xgamma[i].Form("#chi^{2}/%i = %.2f", dof_xgamma[i], chi2_xgamma[i]);
            s5_xgamma[i].Form("N_{Data} = %.0f", h_deltaz_xgamma_data_sum[i]->GetEntries());
            t1_xgamma[i] = pave_xgamma[i]->AddText(s1_xgamma[i]); t1_xgamma[i]->SetTextSize(0.045);
            t2_xgamma[i] = pave_xgamma[i]->AddText(s2_xgamma[i]); t2_xgamma[i]->SetTextSize(0.045);
            t3_xgamma[i] = pave_xgamma[i]->AddText(s3_xgamma[i]); t3_xgamma[i]->SetTextSize(0.045);
            t4_xgamma[i] = pave_xgamma[i]->AddText(s4_xgamma[i]); t4_xgamma[i]->SetTextSize(0.045);
            t5_xgamma[i] = pave_xgamma[i]->AddText(s5_xgamma[i]); t5_xgamma[i]->SetTextSize(0.045);
        }

        TCanvas *c_dz_xgamma = new TCanvas("c_dz_xgamma", "deltaZ in bins of xgamma", 800, 600);
        c_dz_xgamma->Divide(3, 2);
        make_clean_pads(c_dz_xgamma, 6, 0, 0);
        for(Int_t i = 0; i < number_xgamma_bins; i++) 
        {
            sign_window(c_dz_xgamma->GetPad(i+1), h_window_fit_xgamma[i], "", "Events", "", "middle");//
            c_dz_xgamma->GetPad(i+1)->cd();
            h_window_fit_xgamma[i]->GetYaxis()->SetRangeUser(0., 1.2*h_deltaz_xgamma_data_sum[i]->GetMaximum());
            /*if (nodebugmode) cout << "draw " << i << endl;*/
            /*if (nodebugmode) cout << "xgamma bin# " << i << " " << h_deltaz_xgamma_data_sum[i]->Integral() << " " << h_deltaz_xgamma_res[i]->Integral() << " " 
                << h_deltaz_xgamma_prph_sum[i]->Integral() << " " 
                << h_deltaz_xgamma_rad_sum[i]->Integral() << " " << h_deltaz_xgamma_norad_sum[i]->Integral() << endl;*/
            h_window_fit_xgamma[i]->Draw();
            h_deltaz_xgamma_res[i]->Draw("HIST SAME");
            h_deltaz_xgamma_res[i]->Draw(" X0 SAME");
            h_deltaz_xgamma_rad_sum[i]->Draw("HIST F SAME");
            h_deltaz_xgamma_norad_sum[i]->Draw("HIST F SAME");
            h_deltaz_xgamma_prph_sum[i]->Draw("HIST F SAME");
            Double_t xmin = h_deltaz_xgamma_data_sum[i]->GetXaxis()->GetXmin();
            Double_t xmax = h_deltaz_xgamma_data_sum[i]->GetXaxis()->GetXmax();
            Double_t deltax = xmax-xmin;
            h_deltaz_xgamma_data_sum[i]->GetXaxis()->SetLimits(xmin + 0.01*deltax, xmax+0.01*deltax);
            h_deltaz_xgamma_data_sum[i]->Draw("P  X0 SAME");
            c_dz_xgamma->GetPad(i+1)->RedrawAxis();
            pave_xgamma[i]->Draw();

            TPaveText *t = new TPaveText(0.5, 0.94, 0.6, 1.0, "brNDC"); // left-up
            t->AddText("#deltaZ");
            t->Draw();
            if (i+1 == number_xgamma_bins )
            {
                if (nodebugmode) cout << "Problem bin PAINT" << endl;
                
                /*if (nodebugmode) cout << "   data: " << h_deltaz_xgamma_data_sum[i]->GetEntries()<<endl;
                if (nodebugmode) cout << "   res: " << h_deltaz_xgamma_res[i]->GetEntries()<<endl;
                if (nodebugmode) cout << "   QQ': " << h_deltaz_xgamma_prph_sum[i]->GetEntries() <<endl;
                if (nodebugmode) cout << "   LL: " << h_deltaz_xgamma_rad_sum[i]->GetEntries()<<endl;
                if (nodebugmode) cout << "   bg': " << h_deltaz_xgamma_norad_sum[i]->GetEntries() <<endl;*/
                
                if (nodebugmode) cout << "   data: " << h_deltaz_xgamma_data_sum[i]->Integral(1, h_deltaz_xgamma_data_sum[i]->GetNbinsX())<<endl;
                if (nodebugmode) cout << "   res: " << h_deltaz_xgamma_res[i]->Integral(1, h_deltaz_xgamma_res[i]->GetNbinsX())<<endl;
                if (nodebugmode) cout << "   QQ': " << h_deltaz_xgamma_prph_sum[i]->Integral(1, h_deltaz_xgamma_prph_sum[i]->GetNbinsX()) <<endl;
                if (nodebugmode) cout << "   LL: " << h_deltaz_xgamma_rad_sum[i]->Integral(1, h_deltaz_xgamma_rad_sum[i]->GetNbinsX())<<endl;
                if (nodebugmode) cout << "   bg': " << h_deltaz_xgamma_norad_sum[i]->Integral(1, h_deltaz_xgamma_norad_sum[i]->GetNbinsX()) <<endl;
            }
        }
        c_dz_xgamma->Print("c_dz_xgamma.eps");  
        c_dz_xgamma->Print("c_dz_xgamma.png");  
    }
    ///////////////////////////////////////////////////////
    //
    //          dz in bins of xp
    //
    ///////////////////////////////////////////////////////
    {
        //Double_t xp_bin_copy = xp_bin
        PlotControlPlot(param_xp, param_err_xp, number_xp_bins, xp_bin, 0, "xp", "c_control_xp", "x_{p}", "bins of xp", "Events", "righttup");
        
        TH2D* h_window_fit_xp[number_xp_bins];
        Double_t ymax_xp[number_xp_bins] ;
        for(Int_t i = 0; i < number_xp_bins; i++) 
            ymax_xp[i] = 1.5 * h_deltaz_xp_data_sum[i]->GetMaximum();

        for(Int_t i=0; i<number_xp_bins; i++)
        {
            TString s; 
            s.Form("h_window_fit_xp_%i", i); 
            h_window_fit_xp[i] = new TH2D(s, "", 10, 0., 1.5, 10, 0., ymax_xp[i]);
        }

        TPaveText *pave_xp[number_xp_bins];
        TString s1_xp[number_xp_bins], s2_xp[number_xp_bins], s3_xp[number_xp_bins], s4_xp[number_xp_bins], s5_xp[number_xp_bins];
        TText *t1_xp[number_xp_bins], *t2_xp[number_xp_bins], *t3_xp[number_xp_bins], *t4_xp[number_xp_bins], *t5_xp[number_xp_bins];
        if (nodebugmode) cout<<"xp_bin:"<<endl;
        for(Int_t i = 0; i < number_xp_bins ; i++) 
        {
            //if (nodebugmode) cout<< i<<") "<<xp_bin[i]<<"..."<<xp_bin[i+1]<< endl;
            pave_xp[i] = new TPaveText(0.5, 0.5, 0.9, 0.9, "NDC");
            pave_xp[i]->SetFillColor(0);
            pave_xp[i]->SetBorderSize(0);
            s1_xp[i].Form("%.3f < x_{p} < %.3f", xp_bin[i], xp_bin[i+1]);
            s2_xp[i].Form("QQ phot. fraction: %.2f #pm %.2f", param_xp[i], param_err_xp[i]);
            s3_xp[i].Form("fit range: bins %i to %i", left_xp[i], right_xp[i]); 
            s4_xp[i].Form("#chi^{2}/%i = %.2f", dof_xp[i], chi2_xp[i]);
            s5_xp[i].Form("N_{Data} = %.0f", h_deltaz_xp_data_sum[i]->GetEntries());
            t1_xp[i] = pave_xp[i]->AddText(s1_xp[i]); t1_xp[i]->SetTextSize(0.045);
            t2_xp[i] = pave_xp[i]->AddText(s2_xp[i]); t2_xp[i]->SetTextSize(0.045);
            t3_xp[i] = pave_xp[i]->AddText(s3_xp[i]); t3_xp[i]->SetTextSize(0.045);
            t4_xp[i] = pave_xp[i]->AddText(s4_xp[i]); t4_xp[i]->SetTextSize(0.045);
            t5_xp[i] = pave_xp[i]->AddText(s5_xp[i]); t5_xp[i]->SetTextSize(0.045);
        }
        TCanvas *c_dz_xp = new TCanvas("c_dz_xp", "deltaZ in bins of xp", 800, 600);
        c_dz_xp->Divide(3, 2);
        make_clean_pads(c_dz_xp, 6, 0, 0);
        for(Int_t i = 0; i < number_xp_bins; i++) 
        {
            sign_window(c_dz_xp->GetPad(i+1), h_window_fit_xp[i], "", "Events", "", "middle");
            c_dz_xp->GetPad(i+1)->cd();
            h_window_fit_xp[i]->GetYaxis()->SetRangeUser(0., 1.2*h_deltaz_xp_data_sum[i]->GetMaximum());
            /*if (nodebugmode) cout << "draw " << i << endl;*/
            /*if (nodebugmode) cout << "xp bin# " << i << " " << h_deltaz_xp_data_sum[i]->Integral() << " " << h_deltaz_xp_res[i]->Integral() << " " 
                << h_deltaz_xp_prph_sum[i]->Integral() << " " 
                << h_deltaz_xp_rad_sum[i]->Integral() << " " << h_deltaz_xp_norad_sum[i]->Integral() << endl;*/    
            h_window_fit_xp[i]->Draw();
            h_deltaz_xp_res[i]->Draw("HIST SAME");
            h_deltaz_xp_res[i]->Draw(" X0 SAME");
            h_deltaz_xp_rad_sum[i]->Draw("HIST F SAME");
            h_deltaz_xp_norad_sum[i]->Draw("HIST F SAME");
            h_deltaz_xp_prph_sum[i]->Draw("HIST F SAME");
            Double_t xmin = h_deltaz_xp_data_sum[i]->GetXaxis()->GetXmin();
            Double_t xmax = h_deltaz_xp_data_sum[i]->GetXaxis()->GetXmax();
            Double_t deltax = xmax-xmin;
            h_deltaz_xp_data_sum[i]->GetXaxis()->SetLimits(xmin + 0.01*deltax, xmax+0.01*deltax);
            h_deltaz_xp_data_sum[i]->Draw("P  X0 SAME");
            c_dz_xp->GetPad(i+1)->RedrawAxis();
            pave_xp[i]->Draw();

            TPaveText *t = new TPaveText(0.5, 0.94, 0.6, 1.0, "brNDC"); // left-up
            t->AddText("#deltaZ");
            t->Draw();
        }
        c_dz_xp->Print("c_dz_xp.eps");  
        c_dz_xp->Print("c_dz_xp.png");  
    }
    ///////////////////////////////////////////////////////
    //
    //          dz in bins of dphi
    //
    ///////////////////////////////////////////////////////
    {
        /*{ Try to construct contol plots via Integrating

            TString variable = "dhi";
            TString name = "h_all_data_";
            name += variable; 
            TH1D* h_data = new TH1D("h_all_data_"  + variable, "data all bins", number_dphi_bins, dphi_bin); 
            TH1D* h_res = new TH1D("h_all_res_"  + variable, "res all bins", number_dphi_bins, dphi_bin); 
            TH1D* h_qq = new TH1D("h_all_qq_"  + variable, "qq all bins", number_dphi_bins, dphi_bin); 
            TH1D* h_ll = new TH1D("h_all_ll_"  + variable, "ll all bins", number_dphi_bins, dphi_bin); 
            TH1D* h_bg = new TH1D("h_all_bg_"  + variable, "bg all bins", number_dphi_bins, dphi_bin);
            SetVioletStyle(h_data, h_res, h_qq, h_ll, h_bg);
            h_data->Sumw2();
            h_res->Sumw2(); 
            h_qq->Sumw2();  
            h_ll->Sumw2();  
            h_bg->Sumw2();   
            Double_t ymax = 0;
            for(Int_t i = 0; i < number_dphi_bins; i++) 
            {
                Double_t err(0);
                Double_t bin_width = h_data->GetBinWidth(i+1);
                Double_t t = h_deltaz_dphi_data_sum[i]->IntegralAndError(1, h_deltaz_dphi_data_sum[i]->GetNbinsX(), err);
                if (nodebugmode) cout<< "bin " << i+1 << " " << t / bin_width <<" ";
                if (ymax < 1.2 * t)
                    ymax = 1.2 * t;
                h_data->SetBinContent(i+1, t / bin_width);
                h_data->SetBinError(i+1, err / bin_width);
                t = h_deltaz_dphi_res[i]->IntegralAndError(1, h_deltaz_dphi_res[i]->GetNbinsX(), err);
                if (nodebugmode) cout<< t / bin_width <<" ";
                if (ymax < 1.2 * t)
                    ymax = 1.2 * t;
                h_res->SetBinContent(i+1, t / bin_width);
                h_res->SetBinError(i+1, err / bin_width);
                t = h_deltaz_dphi_prph_sum[i]->IntegralAndError(1, h_deltaz_dphi_prph_sum[i]->GetNbinsX(), err);
                if (nodebugmode) cout<< t / bin_width <<" ";
                h_qq->SetBinContent(i+1, t / bin_width);
                h_qq->SetBinError(i+1, err / bin_width);
                t = h_deltaz_dphi_rad_sum[i]->IntegralAndError(1, h_deltaz_dphi_rad_sum[i]->GetNbinsX(), err);
                if (nodebugmode) cout<< t / bin_width <<" ";
                h_ll->SetBinContent(i+1, t / bin_width);
                h_ll->SetBinError(i+1, err / bin_width);
                t = h_deltaz_dphi_norad_sum[i]->IntegralAndError(1, h_deltaz_dphi_norad_sum[i]->GetNbinsX(), err);
                if (nodebugmode) cout<< t / bin_width <<" "<<endl;
                h_bg->SetBinContent(i+1, t / bin_width);
                h_bg->SetBinError(i+1, err / bin_width);
            }
            gStyle->SetOptStat(0);
            TLegend *leg = new TLegend(0.1, 0.6, 0.7, 0.91);//right 0.45, 0.6, 0.86, 0.91
            leg->SetBorderSize(0);
            leg->SetFillColor(0);
            leg->AddEntry(h_data, "data", "pe"); //black на самом деле kRed
            leg->AddEntry(h_qq, "QQ", "f"); //blue
            leg->AddEntry(h_ll, "LL", "f");// red dots
            leg->AddEntry(h_bg, "Hadronic BG", "f");// small dots
            leg->AddEntry(h_res, "Fit result", "f");//yellow area
            

            TCanvas *c_control_dphi = new TCanvas("c_control_dphi", "bins of dphi", 800, 600);
            TH2D *h_window_dphi = new TH2D("h_window_"+variable, "#Delta#Phi", number_dphi_bins, dphi_bin[0], dphi_bin[number_dphi_bins - 1], 10, 0., ymax);
            //make_clean_pads(c_control_dphi, 1, 0, 0);
            c_control_dphi->GetPad(0)->SetTicks(1,1);
            c_control_dphi->GetPad(0)->SetFrameBorderMode(0);
            c_control_dphi->GetPad(0)->SetBorderMode(0);
            c_control_dphi->GetPad(0)->SetFillColor(kWhite);
            c_control_dphi->GetPad(0)->SetGrid(0, 0);
            sign_window(c_control_dphi->GetPad(0), h_window_dphi, variable, "Events", "", "large");
            h_window_dphi->Draw();
                h_res->Draw("HIST ");
                h_res->Draw(" X0 SAME");
                h_ll->Draw("HIST F SAME");
                h_bg->Draw("HIST F SAME");
                h_qq->Draw("HIST F SAME");
                h_data->Draw("P  X0 SAME");
                leg->Draw();
                c_control_dphi->GetPad(0)->RedrawAxis();
                c_control_dphi->Print("c_control_dphi.png");
        }*/
        PlotControlPlot(param_dphi, param_err_dphi, number_dphi_bins, dphi_bin, 3, "dhi", "c_control_dphi", "#Delta#phi", "bins of dhi", "Events", "leftup");

        TH2D* h_window_fit_dphi[number_dphi_bins];
        Double_t ymax_dphi[number_dphi_bins] ;
        for(Int_t i = 0; i < number_dphi_bins; i++) 
            ymax_dphi[i] = 1.5 * h_deltaz_dphi_data_sum[i]->GetMaximum();

        for(Int_t i=0; i<number_dphi_bins; i++)
        {
            TString s; 
            s.Form("h_window_fit_dphi_%i", i); 
            h_window_fit_dphi[i] = new TH2D(s, "", 10, 0., 1.5, 10, 0., ymax_dphi[i]);
        }

        TPaveText *pave_dphi[number_dphi_bins];
        TString s1_dphi[number_dphi_bins], s2_dphi[number_dphi_bins], s3_dphi[number_dphi_bins], s4_dphi[number_dphi_bins], s5_dphi[number_dphi_bins];
        TText *t1_dphi[number_dphi_bins], *t2_dphi[number_dphi_bins], *t3_dphi[number_dphi_bins], *t4_dphi[number_dphi_bins], *t5_dphi[number_dphi_bins];

        for(Int_t i = 0; i < number_dphi_bins; i++) 
        {
            pave_dphi[i] = new TPaveText(0.5, 0.5, 0.9, 0.9, "NDC");
            pave_dphi[i]->SetFillColor(0);
            pave_dphi[i]->SetBorderSize(0);
            s1_dphi[i].Form("%.1f < #Delta#phi < %.1f", dphi_bin[i], dphi_bin[i+1]);
            s2_dphi[i].Form("QQ phot. fraction: %.2f #pm %.2f", param_dphi[i], param_err_dphi[i]);
            s3_dphi[i].Form("fit range: bins %i to %i", left_dphi[i], right_dphi[i]); 
            s4_dphi[i].Form("#chi^{2}/%i = %.2f", dof_dphi[i], chi2_dphi[i]);
            s5_dphi[i].Form("N_{Data} = %.0f", h_deltaz_dphi_data_sum[i]->GetEntries());
            t1_dphi[i] = pave_dphi[i]->AddText(s1_dphi[i]); t1_dphi[i]->SetTextSize(0.045);
            t2_dphi[i] = pave_dphi[i]->AddText(s2_dphi[i]); t2_dphi[i]->SetTextSize(0.045);
            t3_dphi[i] = pave_dphi[i]->AddText(s3_dphi[i]); t3_dphi[i]->SetTextSize(0.045);
            t4_dphi[i] = pave_dphi[i]->AddText(s4_dphi[i]); t4_dphi[i]->SetTextSize(0.045);
            t5_dphi[i] = pave_dphi[i]->AddText(s5_dphi[i]); t5_dphi[i]->SetTextSize(0.045);
        }

        TCanvas *c_dz_dphi = new TCanvas("c_dz_dphi", "deltaZ in bins of dphi", 800, 600);
        c_dz_dphi->Divide(3, 2);
        make_clean_pads(c_dz_dphi, 6, 0, 0);
        for(Int_t i = 0; i < number_dphi_bins; i++) 
        {
            sign_window(c_dz_dphi->GetPad(i+1), h_window_fit_dphi[i], "", "Events", "", "middle");
            c_dz_dphi->GetPad(i+1)->cd();
            h_window_fit_dphi[i]->GetYaxis()->SetRangeUser(0., 1.2*h_deltaz_dphi_data_sum[i]->GetMaximum());
            /*if (nodebugmode) cout << "draw " << i << endl;*/
            /*if (nodebugmode) cout << "dphi bin# " << i << " " << h_deltaz_dphi_data_sum[i]->Integral() << " " << h_deltaz_dphi_res[i]->Integral() << " " 
                << h_deltaz_dphi_prph_sum[i]->Integral() << " " 
                << h_deltaz_dphi_rad_sum[i]->Integral() << " " << h_deltaz_dphi_norad_sum[i]->Integral() << endl;*/    
            h_window_fit_dphi[i]->Draw();
            h_deltaz_dphi_res[i]->Draw("HIST SAME");
            h_deltaz_dphi_res[i]->Draw(" X0 SAME");
            h_deltaz_dphi_rad_sum[i]->Draw("HIST F SAME");
            h_deltaz_dphi_norad_sum[i]->Draw("HIST F SAME");
            h_deltaz_dphi_prph_sum[i]->Draw("HIST F SAME");
            Double_t xmin = h_deltaz_dphi_data_sum[i]->GetXaxis()->GetXmin();
            Double_t xmax = h_deltaz_dphi_data_sum[i]->GetXaxis()->GetXmax();
            Double_t deltax = xmax-xmin;
            h_deltaz_dphi_data_sum[i]->GetXaxis()->SetLimits(xmin + 0.01*deltax, xmax+0.01*deltax);
            h_deltaz_dphi_data_sum[i]->Draw("P  X0 SAME");
            c_dz_dphi->GetPad(i+1)->RedrawAxis();
            pave_dphi[i]->Draw();
            if(i==0)
            {
                if (nodebugmode) cout<<"            THE DeltaPhi CONTENT AND ERRORS"<<endl;
                if (nodebugmode) cout<<"bin "<<i<<endl;
                Double_t err(0);
                Double_t t = h_deltaz_dphi_data_sum[i]->IntegralAndError(1, h_deltaz_dphi_data_sum[i]->GetNbinsX(), err);
                if (nodebugmode) cout << "   data: " << t << " +/- " << err<< endl;
                t = h_deltaz_dphi_res[i]->IntegralAndError(1, h_deltaz_dphi_res[i]->GetNbinsX(), err);
                if (nodebugmode) cout << "   res: " << t << " +/- " << err<<endl;
                t = h_deltaz_dphi_rad_sum[i]->IntegralAndError(1, h_deltaz_dphi_rad_sum[i]->GetNbinsX(), err);
                if (nodebugmode) cout << "      ll: " << t << " +/- " << err <<endl;
                t = h_deltaz_dphi_prph_sum[i]->IntegralAndError(1, h_deltaz_dphi_prph_sum[i]->GetNbinsX(), err);
                if (nodebugmode) cout << "      qq: " << t << " +/- " << err <<endl;
                t = h_deltaz_dphi_norad_sum[i]->IntegralAndError(1, h_deltaz_dphi_norad_sum[i]->GetNbinsX(), err);
                if (nodebugmode) cout << "      bg: " << t << " +/- " << err <<endl;

            }

            TPaveText *t = new TPaveText(0.5, 0.94, 0.6, 1.0, "brNDC"); // left-up
            t->AddText("#deltaZ");
            t->Draw();
        }
        c_dz_dphi->Print("c_dz_dphi.eps");  
        c_dz_dphi->Print("c_dz_dphi.png");  
    }
    ///////////////////////////////////////////////////////
    //
    //          dz in bins of deta
    //
    ///////////////////////////////////////////////////////
    {
        PlotControlPlot(param_deta, param_err_deta, number_deta_bins, deta_bin, 2, "deta", "c_control_deta", "#Delta#eta", "bins of deta", "Events", "leftup");
        TH2D* h_window_fit_deta[number_deta_bins];
        Double_t ymax_deta[number_deta_bins] ;
        for(Int_t i = 0; i < number_deta_bins; i++) 
            ymax_deta[i] = 1.5 * h_deltaz_deta_data_sum[i]->GetMaximum();

        for(Int_t i=0; i<number_deta_bins; i++)
        {
            TString s; 
            s.Form("h_window_fit_deta_%i", i); 
            h_window_fit_deta[i] = new TH2D(s, "", 10, 0., 1.5, 10, 0., ymax_deta[i]);
        }

        TPaveText *pave_deta[number_deta_bins];
        TString s1_deta[number_deta_bins], s2_deta[number_deta_bins], s3_deta[number_deta_bins], s4_deta[number_deta_bins], s5_deta[number_deta_bins];
        TText *t1_deta[number_deta_bins], *t2_deta[number_deta_bins], *t3_deta[number_deta_bins], *t4_deta[number_deta_bins], *t5_deta[number_deta_bins];

        for(Int_t i = 0; i < number_deta_bins; i++) 
        {
            pave_deta[i] = new TPaveText(0.5, 0.5, 0.9, 0.9, "NDC");
            pave_deta[i]->SetFillColor(0);
            pave_deta[i]->SetBorderSize(0);
            s1_deta[i].Form("%.1f < #Delta#eta < %.1f", deta_bin[i], deta_bin[i+1]);
            s2_deta[i].Form("QQ phot. fraction: %.2f #pm %.2f", param_deta[i], param_err_deta[i]);
            s3_deta[i].Form("fit range: bins %i to %i", left_deta[i], right_deta[i]); 
            s4_deta[i].Form("#chi^{2}/%i = %.2f", dof_deta[i], chi2_deta[i]);
            s5_deta[i].Form("N_{Data} = %.0f", h_deltaz_deta_data_sum[i]->GetEntries());
            t1_deta[i] = pave_deta[i]->AddText(s1_deta[i]); t1_deta[i]->SetTextSize(0.045);
            t2_deta[i] = pave_deta[i]->AddText(s2_deta[i]); t2_deta[i]->SetTextSize(0.045);
            t3_deta[i] = pave_deta[i]->AddText(s3_deta[i]); t3_deta[i]->SetTextSize(0.045);
            t4_deta[i] = pave_deta[i]->AddText(s4_deta[i]); t4_deta[i]->SetTextSize(0.045);
            t5_deta[i] = pave_deta[i]->AddText(s5_deta[i]); t5_deta[i]->SetTextSize(0.045);
        }

        TCanvas *c_dz_deta = new TCanvas("c_dz_deta", "deltaZ in bins of deta", 800, 600);
        c_dz_deta->Divide(3, 2);
        make_clean_pads(c_dz_deta, 6, 0, 0);

        TCanvas *c_dz_deta_2 = new TCanvas("c_dz_deta_2", "deltaZ in bins of deta", 800, 600);
        c_dz_deta_2->Divide(3, 2);
        make_clean_pads(c_dz_deta_2, 6, 0, 0);
        for(Int_t j = 0; j < number_deta_bins; j++) 
        {
            Int_t i = j;
            if(j == number_deta_bins - 1)
            {
                TCanvas *temp  = c_dz_deta;
                c_dz_deta->Print("c_dz_deta.eps");  
                c_dz_deta->Print("c_dz_deta.png");  
                c_dz_deta = c_dz_deta_2;
                i = 0;
                delete temp;   
            }
            sign_window(c_dz_deta->GetPad(i+1), h_window_fit_deta[i], "", "Events", "", "middle");
            c_dz_deta->GetPad(i+1)->cd();
            h_window_fit_deta[i]->GetYaxis()->SetRangeUser(0., 1.2*h_deltaz_deta_data_sum[i]->GetMaximum());
            /*if (nodebugmode) cout << "draw " << i << endl;*/
            /*if (nodebugmode) cout << "deta bin# " << i << " " << h_deltaz_deta_data_sum[i]->Integral() << " " << h_deltaz_deta_res[i]->Integral() << " " 
                << h_deltaz_deta_prph_sum[i]->Integral() << " " 
                << h_deltaz_deta_rad_sum[i]->Integral() << " " << h_deltaz_deta_norad_sum[i]->Integral() << endl;*/    
            h_window_fit_deta[i]->Draw();
            h_deltaz_deta_res[i]->Draw("HIST SAME");
            h_deltaz_deta_res[i]->Draw(" X0 SAME");
            h_deltaz_deta_rad_sum[i]->Draw("HIST F SAME");
            h_deltaz_deta_norad_sum[i]->Draw("HIST F SAME");
            h_deltaz_deta_prph_sum[i]->Draw("HIST F SAME");
            Double_t xmin = h_deltaz_deta_data_sum[i]->GetXaxis()->GetXmin();
            Double_t xmax = h_deltaz_deta_data_sum[i]->GetXaxis()->GetXmax();
            Double_t deltax = xmax-xmin;
            h_deltaz_deta_data_sum[i]->GetXaxis()->SetLimits(xmin + 0.01*deltax, xmax+0.01*deltax);
            h_deltaz_deta_data_sum[i]->Draw("P  X0 SAME");
            c_dz_deta->GetPad(i+1)->RedrawAxis();
            pave_deta[i]->Draw();

            TPaveText *t = new TPaveText(0.5, 0.94, 0.6, 1.0, "brNDC"); // left-up
            t->AddText("#deltaZ");
            t->Draw();
        }
        c_dz_deta->Print("c_dz_deta_2.eps");  
        c_dz_deta->Print("c_dz_deta_2.png");  
    }

    ///////////////////////////////////////////////////////
    //
    //          dz in bins of dphi_e_ph
    //
    ///////////////////////////////////////////////////////
    {

        PlotControlPlot(param_dphi_e_ph, param_err_dphi_e_ph, number_dphi_e_ph_bins, dphi_e_ph_bin, 4, "dphi_e_ph", "c_control_dphi_e_ph", "#Delta#phi_{e, #gamma}, deg.", "bins of dphi_e_ph", "Events", "leftup");
        TH2D* h_window_fit_dphi_e_ph[number_dphi_e_ph_bins];
        Double_t ymax_dphi_e_ph[number_dphi_e_ph_bins] ;
        for(Int_t i = 0; i < number_dphi_e_ph_bins; i++) 
            ymax_dphi_e_ph[i] = 1.5 * h_deltaz_dphi_e_ph_data_sum[i]->GetMaximum();

        for(Int_t i=0; i<number_dphi_e_ph_bins; i++)
        {
            TString s; 
            s.Form("h_window_fit_dphi_e_ph_%i", i); 
            h_window_fit_dphi_e_ph[i] = new TH2D(s, "", 10, 0., 1.5, 10, 0., ymax_dphi_e_ph[i]);
        }

        TPaveText *pave_dphi_e_ph[number_dphi_e_ph_bins];
        TString s1_dphi_e_ph[number_dphi_e_ph_bins], s2_dphi_e_ph[number_dphi_e_ph_bins], s3_dphi_e_ph[number_dphi_e_ph_bins], s4_dphi_e_ph[number_dphi_e_ph_bins], s5_dphi_e_ph[number_dphi_e_ph_bins];
        TText *t1_dphi_e_ph[number_dphi_e_ph_bins], *t2_dphi_e_ph[number_dphi_e_ph_bins], *t3_dphi_e_ph[number_dphi_e_ph_bins], *t4_dphi_e_ph[number_dphi_e_ph_bins], *t5_dphi_e_ph[number_dphi_e_ph_bins];

        for(Int_t i = 0; i < number_dphi_e_ph_bins; i++) 
        {
            pave_dphi_e_ph[i] = new TPaveText(0.5, 0.5, 0.9, 0.9, "NDC");
            pave_dphi_e_ph[i]->SetFillColor(0);
            pave_dphi_e_ph[i]->SetBorderSize(0);
            s1_dphi_e_ph[i].Form("%.1f < #Delta#phi_{e, #gamma} < %.1f", dphi_e_ph_bin[i], dphi_e_ph_bin[i+1]);
            s2_dphi_e_ph[i].Form("QQ phot. fraction: %.2f #pm %.2f", param_dphi_e_ph[i], param_err_dphi_e_ph[i]);
            s3_dphi_e_ph[i].Form("fit range: bins %i to %i", left_dphi_e_ph[i], right_dphi_e_ph[i]); 
            s4_dphi_e_ph[i].Form("#chi^{2}/%i = %.2f", dof_dphi_e_ph[i], chi2_dphi_e_ph[i]);            
            s5_dphi_e_ph[i].Form("N_{Data} = %.0f", h_deltaz_dphi_e_ph_data_sum[i]->GetEntries());
            t1_dphi_e_ph[i] = pave_dphi_e_ph[i]->AddText(s1_dphi_e_ph[i]); t1_dphi_e_ph[i]->SetTextSize(0.045);
            t2_dphi_e_ph[i] = pave_dphi_e_ph[i]->AddText(s2_dphi_e_ph[i]); t2_dphi_e_ph[i]->SetTextSize(0.045);
            t3_dphi_e_ph[i] = pave_dphi_e_ph[i]->AddText(s3_dphi_e_ph[i]); t3_dphi_e_ph[i]->SetTextSize(0.045);
            t4_dphi_e_ph[i] = pave_dphi_e_ph[i]->AddText(s4_dphi_e_ph[i]); t4_dphi_e_ph[i]->SetTextSize(0.045);
            t5_dphi_e_ph[i] = pave_dphi_e_ph[i]->AddText(s5_dphi_e_ph[i]); t5_dphi_e_ph[i]->SetTextSize(0.045);
        }

        TCanvas *c_dz_dphi_e_ph = new TCanvas("c_dz_dphi_e_ph", "deltaZ in bins of dphi_e_ph", 800, 600);
        c_dz_dphi_e_ph->Divide(3, 2);
        make_clean_pads(c_dz_dphi_e_ph, 6, 0, 0);
        for(Int_t i = 0; i < number_dphi_e_ph_bins; i++) 
        {
            sign_window(c_dz_dphi_e_ph->GetPad(i+1), h_window_fit_dphi_e_ph[i], "", "Events", "", "middle");
            c_dz_dphi_e_ph->GetPad(i+1)->cd();
            h_window_fit_dphi_e_ph[i]->GetYaxis()->SetRangeUser(0., 1.2*h_deltaz_dphi_e_ph_data_sum[i]->GetMaximum());
            /*if (nodebugmode) cout << "draw " << i << endl;*/
            /*if (nodebugmode) cout << "dphi_e_ph bin# " << i << " " << h_deltaz_dphi_e_ph_data_sum[i]->Integral() << " " << h_deltaz_dphi_e_ph_res[i]->Integral() << " " 
                << h_deltaz_dphi_e_ph_prph_sum[i]->Integral() << " " 
                << h_deltaz_dphi_e_ph_rad_sum[i]->Integral() << " " << h_deltaz_dphi_e_ph_norad_sum[i]->Integral() << endl;*/    
            h_window_fit_dphi_e_ph[i]->Draw();
            h_deltaz_dphi_e_ph_res[i]->Draw("HIST SAME");
            h_deltaz_dphi_e_ph_res[i]->Draw(" X0 SAME");
            h_deltaz_dphi_e_ph_rad_sum[i]->Draw("HIST F SAME");
            h_deltaz_dphi_e_ph_norad_sum[i]->Draw("HIST F SAME");
            h_deltaz_dphi_e_ph_prph_sum[i]->Draw("HIST F SAME");
            Double_t xmin = h_deltaz_dphi_e_ph_data_sum[i]->GetXaxis()->GetXmin();
            Double_t xmax = h_deltaz_dphi_e_ph_data_sum[i]->GetXaxis()->GetXmax();
            Double_t deltax = xmax-xmin;
            h_deltaz_dphi_e_ph_data_sum[i]->GetXaxis()->SetLimits(xmin + 0.01*deltax, xmax+0.01*deltax);
            h_deltaz_dphi_e_ph_data_sum[i]->Draw("P  X0 SAME");
            c_dz_dphi_e_ph->GetPad(i+1)->RedrawAxis();
            pave_dphi_e_ph[i]->Draw();          
            TPaveText *t = new TPaveText(0.5, 0.94, 0.6, 1.0, "brNDC"); // left-up
            t->AddText("#deltaZ");
            t->Draw();
        }
        c_dz_dphi_e_ph->Print("c_dz_dphi_e_ph.eps");  
        c_dz_dphi_e_ph->Print("c_dz_dphi_e_ph.png");  
    }
    
    ///////////////////////////////////////////////////////
    //
    //          dz in bins of deta_e_ph
    //
    ///////////////////////////////////////////////////////
    {
        PlotControlPlot(param_deta_e_ph, param_err_deta_e_ph, number_deta_e_ph_bins, deta_e_ph_bin, 5, "deta_e_ph", "c_control_deta_e_ph", "#Delta#eta_{e, #gamma}", "bins of deta_e_ph", "Events", "leftup");
        
        TH2D* h_window_fit_deta_e_ph[number_deta_e_ph_bins];
        Double_t ymax_deta_e_ph[number_deta_e_ph_bins] ;
        for(Int_t i = 0; i < number_deta_e_ph_bins; i++) 
            ymax_deta_e_ph[i] = 1.5 * h_deltaz_deta_e_ph_data_sum[i]->GetMaximum();

        for(Int_t i=0; i<number_deta_e_ph_bins; i++)
        {
            TString s; 
            s.Form("h_window_fit_deta_e_ph_%i", i); 
            h_window_fit_deta_e_ph[i] = new TH2D(s, "", 10, 0., 1.5, 10, 0., ymax_deta_e_ph[i]);
        }

        TPaveText *pave_deta_e_ph[number_deta_e_ph_bins];
        TString s1_deta_e_ph[number_deta_e_ph_bins], s2_deta_e_ph[number_deta_e_ph_bins], s3_deta_e_ph[number_deta_e_ph_bins], s4_deta_e_ph[number_deta_e_ph_bins], s5_deta_e_ph[number_deta_e_ph_bins];
        TText *t1_deta_e_ph[number_deta_e_ph_bins], *t2_deta_e_ph[number_deta_e_ph_bins], *t3_deta_e_ph[number_deta_e_ph_bins], *t4_deta_e_ph[number_deta_e_ph_bins], *t5_deta_e_ph[number_deta_e_ph_bins];

        for(Int_t i = 0; i < number_deta_e_ph_bins; i++) 
        {
            pave_deta_e_ph[i] = new TPaveText(0.5, 0.5, 0.9, 0.9, "NDC");
            pave_deta_e_ph[i]->SetFillColor(0);
            pave_deta_e_ph[i]->SetBorderSize(0);
            s1_deta_e_ph[i].Form("%.1f < #Delta#eta_{e, #gamma} < %.1f", deta_e_ph_bin[i], deta_e_ph_bin[i+1]);
            s2_deta_e_ph[i].Form("QQ phot. fraction: %.2f #pm %.2f", param_deta_e_ph[i], param_err_deta_e_ph[i]);
            s3_deta_e_ph[i].Form("fit range: bins %i to %i", left_deta_e_ph[i], right_deta_e_ph[i]); 
            s4_deta_e_ph[i].Form("#chi^{2}/%i = %.2f", dof_deta_e_ph[i], chi2_deta_e_ph[i]);                
            s5_deta_e_ph[i].Form("N_{Data} = %.0f", h_deltaz_deta_e_ph_data_sum[i]->GetEntries());
            t1_deta_e_ph[i] = pave_deta_e_ph[i]->AddText(s1_deta_e_ph[i]); t1_deta_e_ph[i]->SetTextSize(0.045);
            t2_deta_e_ph[i] = pave_deta_e_ph[i]->AddText(s2_deta_e_ph[i]); t2_deta_e_ph[i]->SetTextSize(0.045);
            t3_deta_e_ph[i] = pave_deta_e_ph[i]->AddText(s3_deta_e_ph[i]); t3_deta_e_ph[i]->SetTextSize(0.045);
            t4_deta_e_ph[i] = pave_deta_e_ph[i]->AddText(s4_deta_e_ph[i]); t4_deta_e_ph[i]->SetTextSize(0.045);
            t5_deta_e_ph[i] = pave_deta_e_ph[i]->AddText(s5_deta_e_ph[i]); t5_deta_e_ph[i]->SetTextSize(0.045);
        }

        TCanvas *c_dz_deta_e_ph = new TCanvas("c_dz_deta_e_ph", "deltaZ in bins of deta_e_ph", 800, 600);
        c_dz_deta_e_ph->Divide(3, 2);
        make_clean_pads(c_dz_deta_e_ph, 6, 0, 0);
        for(Int_t i = 0; i < 5; i++) //number_deta_e_ph_bins
        {
            sign_window(c_dz_deta_e_ph->GetPad(i+1), h_window_fit_deta_e_ph[i], "", "Events", "", "middle");
            c_dz_deta_e_ph->GetPad(i+1)->cd();
            h_window_fit_deta_e_ph[i]->GetYaxis()->SetRangeUser(0., 1.2*h_deltaz_deta_e_ph_data_sum[i]->GetMaximum());
            /*if (nodebugmode) cout << "draw " << i << endl;*/
            /*if (nodebugmode) cout << "deta_e_ph bin# " << i << " " << h_deltaz_deta_e_ph_data_sum[i]->Integral() << " " << h_deltaz_deta_e_ph_res[i]->Integral() << " " 
                << h_deltaz_deta_e_ph_prph_sum[i]->Integral() << " " 
                << h_deltaz_deta_e_ph_rad_sum[i]->Integral() << " " << h_deltaz_deta_e_ph_norad_sum[i]->Integral() << endl;*/    
            h_window_fit_deta_e_ph[i]->Draw();
            h_deltaz_deta_e_ph_res[i]->Draw("HIST SAME");
            h_deltaz_deta_e_ph_res[i]->Draw(" X0 SAME");
            h_deltaz_deta_e_ph_rad_sum[i]->Draw("HIST F SAME");
            h_deltaz_deta_e_ph_norad_sum[i]->Draw("HIST F SAME");
            h_deltaz_deta_e_ph_prph_sum[i]->Draw("HIST F SAME");
            Double_t xmin = h_deltaz_deta_e_ph_data_sum[i]->GetXaxis()->GetXmin();
            Double_t xmax = h_deltaz_deta_e_ph_data_sum[i]->GetXaxis()->GetXmax();
            Double_t deltax = xmax-xmin;
            h_deltaz_deta_e_ph_data_sum[i]->GetXaxis()->SetLimits(xmin + 0.01*deltax, xmax+0.01*deltax);
            h_deltaz_deta_e_ph_data_sum[i]->Draw("P  X0 SAME");
            c_dz_deta_e_ph->GetPad(i+1)->RedrawAxis();
            pave_deta_e_ph[i]->Draw();
            TPaveText *t = new TPaveText(0.5, 0.94, 0.6, 1.0, "brNDC"); // left-up
            t->AddText("#deltaZ");
            t->Draw();
        }
        c_dz_deta_e_ph->Print("c_dz_deta_e_ph.eps");  
        c_dz_deta_e_ph->Print("c_dz_deta_e_ph.png");  
    }
    /*if (nodebugmode) cout << "Fit in different bins has been drawed" << endl;*/
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
    /*if (nodebugmode) cout << "exiting..." << endl;*/
}

void Hist::DoParamScale(TH1D* h, Double_t *a, Double_t *a_err, Int_t nbins, bool qq)
{
    //if (nodebugmode) cout << "DoParamScale"<<endl;
    //if (nodebugmode) cout << h->GetNbinsX()<< "  "<< h->GetEntries()<< "  "<< h->GetBinContent(2)<<endl;
        for(Int_t i = 1; i < h->GetNbinsX() + 1; i++)// Barlow-Beeston param used//nbins
            {       
                Double_t x = h->GetBinContent(i);
                Double_t y = 1 - a[i-1];
                if (qq)
                    y = a[i-1];
                Double_t dx = h->GetBinError(i);
                Double_t dy = a_err[i-1];
                //if (nodebugmode) cout << "x = " << x << " +- " << dx << "  y = " << y <<" +- " <<dy;
                h->SetBinContent(i, x * y);
                if (x == 0 || y == 0)
                {
                    h->SetBinError(i, 0);   
                    //if (nodebugmode) cout << "  z = " << x * y << "  +- " << 0 <<endl;
                }
                else
                {
                    h->SetBinError(i,x * y * TMath::Sqrt(pow(dx/x, 2) + pow(dy/y, 2))); 
                    //if (nodebugmode) cout << "  z = " << x * y << "  +- " << x * y * TMath::Sqrt(pow(dx/x, 2) + pow(dy/y, 2)) <<endl;
                }
            }
}

//PlotControlPlot(param_dphi, param_err_dphi, number_dphi_bins, 3, "dhi", "c_control_dphi", "#Delta#Phi", "bins of dhi", "Events");
void Hist::PlotControlPlot(Double_t * a, Double_t * a_err, Double_t number_bins, Double_t array_bin[], Int_t index, TString variable, TString canvas_name,\
                    TString title, TString xaxis_name, TString yaxis_name, TString legend_possition)
{//Control plot
    //*******************
    //QQ and bg are scaled with found param
    //*******************
    //if (nodebugmode) cout << "Integrals: mc QQ: " << hist_mc_sum[index]->Integral() << " mc LL: " << hist_mc_rad_sum[index]->Integral() \
    //<< " mc bg: " << hist_mc_norad_sum[index]->Integral() << " data: " << hist_data_sum [index]->Integral()<<endl;    
    hist_res[index] = (TH1D*)hist_mc_rad_sum[index]->Clone();
    /*
        if (nodebugmode) cout<<"a :"<<endl;
        for(Int_t i = 0; i < number_bins; i++)// Barlow-Beeston param used//nbins
        {
            if (nodebugmode) cout << array_bin[i] << "..." <<array_bin[i+1]<< ": " << a[i]  << "+/-" << a_err[i] << endl;
        }
    */
    //if (nodebugmode) cout<< ">>" << hist_res[index]->GetBinContent(1) <<"    "<< hist_res[index]->GetBinError(1)<< "  "<< endl;
    //if (nodebugmode) cout<< ">>" << hist_mc_rad_sum[index]->GetNbinsX()<< " " << number_bins<< endl;
    /*for(Int_t i = 1; i < hist_mc_sum[index]->GetNbinsX() + 1; i++)// Barlow-Beeston param used//nbins
        {
            if (nodebugmode) cout << ">> >> " << hist_mc_sum[index]->GetBinContent(i)<< "  " <<hist_mc_sum[index]->GetBinError(i)  <<endl;
        }
    */
    hist_res[index]->Sumw2();
    hist_res[index]->SetName(s_hist[index]+"_res");//LL
    if (variable.EqualTo("xgamma"))
    {
        if (nodebugmode) cout <<"bin by bin xgamma"<<endl;
        TH1D * h = hist_data_sum[index];//hist_mc_sum[index];
        for(Int_t i = 1; i < h->GetNbinsX() + 1; i++)// Barlow-Beeston param used//nbins
            {       
                if (nodebugmode) cout << h->GetBinContent(i) * h->GetBinWidth(i)<< " ";//24268
            }
            if (nodebugmode) cout<<endl;
    }
    DoParamScale(hist_mc_sum[index], a, a_err, number_bins, true);
    DoParamScale(hist_mc_norad_sum[index], PhotonsFits[index], PhotonsFits_err[index], number_bins, false);
    //DoParamScale(hist_mc_norad_sum[index], a, a_err, number_bins, false);
    /*if (QQfit == 1)
        DoParamScale(hist_mc_norad_sum[index], a, a_err, number_bins, false);
    else{       
        DoParamScale(hist_mc_norad_sum[index], PhotonsFits[index], PhotonsFits_err[index], number_bins, false);
        if (variable.EqualTo("deta_e_ph"))
        {
            if (nodebugmode) cout<<"deta_e_ph PARAM, index "<<index<<endl;
            for(Int_t i = 0; i < number_bins; i ++){
                if (nodebugmode) cout<<PhotonsFits[index][i]<<"+/-"<<PhotonsFits_err[index][i]<<endl;
                if (nodebugmode) cout<<"old:" << a[i]<<"+/-"<<a_err[i]<<endl;
                if (nodebugmode) cout<<"bg:" << hist_mc_norad_sum[index]->GetBinContent(i)<<endl;
            }

        }
    }*/
    hist_res[index]->Add(hist_mc_sum[index]);//+QQ
    hist_res[index]->Add(hist_mc_norad_sum[index]);//+bg
    hist_res[index]->SetLineColor(kRed);
    hist_res[index]->SetLineStyle(1);
    hist_res[index]->SetLineWidth(2);
    hist_res[index]->SetFillColor(kWhite);//kYellow

    TH1D* h_data = hist_data_sum[index];
    TH1D* h_res = hist_res[index];
    TH1D* h_qq = hist_mc_sum[index];
    TH1D* h_ll = hist_mc_rad_sum[index];
    TH1D* h_bg = hist_mc_norad_sum[index];
    h_data->SetLineWidth(2);
    h_res->SetLineWidth(2);
    h_qq->SetLineWidth(2);
    h_ll->SetLineWidth(2);
    h_bg->SetLineWidth(2);

    TH1D* h_data_qq = (TH1D*)h_data->Clone();

    TH1D* h_qq_ll = (TH1D*)h_qq->Clone();
    h_qq_ll->Add(h_ll);

    TH1D* h_data_nobg = (TH1D*)h_data->Clone();
    h_data_nobg->Sumw2();
    h_data_nobg->Add(h_bg, -1);
    DoParamScale(h_data_qq, a, a_err, number_bins, true);
    /*if (nodebugmode) cout<<"h_data: "<<h_data->GetBinContent(1)<< " "<<" "<<h_data->GetBinError(1) <<" h_data_qq: " << h_data_qq->GetBinContent(1)<<" "<<h_data_qq->GetBinError(1)<<endl;
    if (nodebugmode) cout << TMath::Sqrt( pow(h_data->GetBinError(1), 2) + pow(a_err[0], 2) +  pow(h_ll->GetBinError(1), 2)  )<<endl;*/
    h_data_qq->SetLineColor(kBlack);
    h_data_qq->SetLineWidth(2);

    /*for(Int_t i = 1; i < h_res->GetNbinsX() + 1 ; i++)// Barlow-Beeston param used//nbins
    {
        if (nodebugmode) cout << ">>" << h_res->GetBinContent(i) << "  " << h_res->GetBinError(i)*1000  <<endl;
    }
    for(Int_t i = 1; i < h_data->GetNbinsX() + 1 ; i++)// Barlow-Beeston param used//nbins
    {       
        if (nodebugmode) cout << h_data->GetBinError(i) << "   " << h_res->GetBinError(i) << "   " << h_qq->GetBinError(i) << "   "  << h_ll->GetBinError(i) << "   "  << h_bg->GetBinError(i) << endl;
    }*/
    //SetVioletStyle(h_data, h_res, h_qq, h_ll, h_bg);
    Double_t ymax;
    if  (h_data->GetMaximum() > h_res->GetMaximum())
        ymax =  1.1 * h_data->GetMaximum();
    else
        ymax =  1.1 * h_res->GetMaximum();
    gStyle->SetOptStat(0);
    Double_t x1, x2, y1, y2;
    {
        if(legend_possition.Contains("left"))
        {
            x1 = 0.15;
            x2 = 0.6;
        }
        else
        {
            x1 = 0.45;
            x2 = 0.86;
        }
        if(legend_possition.Contains("up"))
        {
            y1 = 0.5;
            y2 = 0.88;
        }
        else
        {
            y1 = 0.1;
            y2 = 0.45;
        }
    }
    {
        TLegend *leg = new TLegend(x1, y1, x2, y2);//right 0.45, 0.6, 0.86, 0.91  //x1 y1 x2 y2
        leg->SetBorderSize(0);
        //leg->SetFillColor(0);
        leg->SetFillStyle(0);
        leg->AddEntry(h_data, "data", "pe"); //black на самом деле kRed
        leg->AddEntry(h_qq, "QQ", "f"); //blue
        leg->AddEntry(h_ll, "LL", "f");// red dots
        leg->AddEntry(h_bg, "Hadronic BG", "f");// small dots
        leg->AddEntry(h_res, "Fit result", "f");//yellow area
        leg->AddEntry(h_data_qq, "QQ from data", "f");//yellow area


        TString binsof = "bins of ";
        binsof += variable;
        TCanvas *c_control = new TCanvas(canvas_name, binsof, 800, 600);
        //if (nodebugmode) cout<<"array_bin[(Int_t)number_bins - 1] = "<<array_bin[(Int_t)number_bins - 1]<<endl;
        TH2D *h_window_control = new TH2D("h_window_"+variable, "title", number_bins, array_bin[0], array_bin[(Int_t)number_bins ], 10, 0., ymax);//array_bin[0], array_bin[number_bins - 1]
        //if (nodebugmode) cout<<"array_bin[1]" << array_bin[1]<<endl;
        //make_clean_pads(c_control, 1, 0, 0);
        c_control->GetPad(0)->SetTicks(1,1);
        c_control->GetPad(0)->SetFrameBorderMode(0);
        c_control->GetPad(0)->SetBorderMode(0);
        c_control->GetPad(0)->SetFillColor(kWhite);
        c_control->GetPad(0)->SetGrid(0, 0);
        sign_window(c_control->GetPad(0), h_window_control, "" , yaxis_name, "", "middle");
        h_window_control->GetYaxis()->SetRange(0, ymax);
        h_window_control->Draw();
        h_res->GetYaxis()->SetRange(0, h_res->GetMaximum());
            h_res->Draw("HIST SAME");
            h_res->Draw("E1 X0 SAME");
            h_ll->Draw("HIST F E1 SAME");
            h_bg->Draw("HIST F E1 SAME");
            h_qq->Draw("HIST F E1 SAME");
            h_ll->Draw("HIST F E1 SAME");
            h_data->Draw("P E1 X0 SAME");
            h_data_qq->Draw("HIST E1 X0 SAME");

            leg->Draw();
            c_control->GetPad(0)->RedrawAxis();
            //TPaveLabel * pl = new TPaveLabel(0.0, 0.9, 0.3, 100.0,"New Title","br");
       //pl->Draw("SAME");
            TPaveText *t = new TPaveText(0.4, 0.9, 0.6, 1.0, "brNDC"); // left-up
            t->AddText(title);
            t->Draw();
            canvas_name += ".png";
            c_control->Print(canvas_name);
    }
    {
        if (h_data_nobg->GetMaximum() > h_qq_ll->GetMaximum())
            ymax =  1.2 * h_data_nobg->GetMaximum();
        else
            ymax =  1.2 * h_qq_ll->GetMaximum();
        TLegend *leg = new TLegend(x1, y1, x2, y2);//right 0.45, 0.6, 0.86, 0.91  //x1 y1 x2 y2
        leg->SetBorderSize(0);
        //leg->SetFillColor(0);
        leg->SetFillStyle(0);
        leg->AddEntry(h_data_nobg, "data - bg", "pe"); //black на самом деле kRed
        leg->AddEntry(h_qq_ll, "LL + QQ*a, MC", "f"); //blue
        leg->AddEntry(h_qq, "QQ*a, MC", "f");// red dots
        leg->AddEntry(h_ll, "LL, MC", "f");// small dots
        SetFigure3Style(h_data_nobg, h_qq_ll, h_qq, h_ll, h_bg);

        TString binsof = "bins of ";
        binsof += variable;
        canvas_name += "_fig3";
        TCanvas *c_control = new TCanvas(canvas_name, binsof, 800, 600);
        TH2D *h_window_control = new TH2D("h_window_fig3_"+variable, "title", number_bins, array_bin[0], array_bin[(Int_t)number_bins ], 10, 0., ymax);//array_bin[0], array_bin[number_bins - 1]
        //if (nodebugmode) cout<<"array_bin[1]" << array_bin[1]<<endl;
        //make_clean_pads(c_control, 1, 0, 0);
        c_control->GetPad(0)->SetTicks(1,1);
        c_control->GetPad(0)->SetFrameBorderMode(0);
        c_control->GetPad(0)->SetBorderMode(0);
        c_control->GetPad(0)->SetFillColor(kWhite);
        c_control->GetPad(0)->SetGrid(0, 0);
        sign_window(c_control->GetPad(0), h_window_control, "" , yaxis_name, "", "middle");
        h_window_control->GetYaxis()->SetRange(0, ymax);
        h_window_control->Draw();
        //h_res->GetYaxis()->SetRange(0, h_res->GetMaximum());
            h_data_nobg->Draw("E1 X0 SAME");
            h_qq_ll->Draw("HIST F E1 SAME");
            h_qq->Draw("HIST F E1 SAME");
            h_ll->Draw("HIST F E1 SAME");
            //if (nodebugmode) cout<<variable<<endl;
            if (!variable.EqualTo("deta"))
                leg->Draw();
            c_control->GetPad(0)->RedrawAxis();
            TPaveText *t = new TPaveText(0.4, 0.9, 0.6, 1.0, "brNDC"); // left-up
            t->AddText(title);
            t->Draw();
            canvas_name += ".png";
            c_control->Print(canvas_name);
    }
}