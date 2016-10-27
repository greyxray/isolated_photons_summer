#include "TMath.h"
#include "../inc/constants.h"

void Hist::PlotCrossSec() 
{
    //  TGaxis::SetMaxDigits(3);
    if (nodebugmode) cout << "========== calculate and plot cross sections ==============" << endl;
    int m = 1; //1 or 2 or 4 or 6 histogams per canvas
    //0 - cross section value; 
    //1 - stat. & fit parameter uncertainty;         //4 - ratio (1); //5 - relative 1; 
    //2 - acceptance uncertainty                     //6 - relative 2; 
    //3 - lumi uncertainty;                          //7 - relative 3
                                                                //low,high
    //8 - jet energy uncertainty;        //13 - relative 8;     //20, 21 - 8;
    //9 - photon energy uncertainty;     //14 - relative 9      //22, 23 - 9;
    //10 - electron energy unc.          //15 - relative 10;    //24, 25 - 10; 
    //11 - deltaZ range uncertainty;     //16 - relative 11;    //26, 27 - 11
        
    //12 - 8+9+10+11 (in quadr); - total systematics    //17 - relative 12
    //18 - syst+stat;                                   //19 - relative 18
    TH1D *h_cross[n_cross][8]; //why 8
    TH1D *h_cross_copy[n_cross][10]; //
    TGraphAsymmErrors *gr_cross[n_cross][40]; //why 40
    TH1D *h_1st_cross[n_cross][8];
    TH2D *h_window_cross[n_cross][2];

    TH1D * h_var[n_cross];
    TH2D * h_var_win[n_cross]; 

     TH1 * data_for_CrossectionDrawer[n_cross];// erors are stat uncertainties
     TH1 * data_for_CrossectionDrawer_tot_err[n_cross];// erors are stat uncertainties
     TH1 * sum_for_CrossectionDrawer[n_cross];
     TH1 * qq_for_CrossectionDrawer[n_cross];
     TH1 * ll_for_CrossectionDrawer[n_cross];

    
    TGraphAsymmErrors *h_Spiesberger_pos_lo[n_cross];
    TGraphAsymmErrors *h_Spiesberger_pos_nlo[n_cross];
    TGraphAsymmErrors *h_Spiesberger_ele_lo[n_cross];
    TGraphAsymmErrors *h_Spiesberger_ele_nlo[n_cross];

    TGraphAsymmErrors *h_Spiesberger_pos_nlo_ra[n_cross];
    TGraphAsymmErrors *h_Spiesberger_ele_nlo_ra[n_cross];
    TGraphAsymmErrors *h_Spiesberger_pos_nlo_ra_fast[n_cross];
    TGraphAsymmErrors *h_Spiesberger_ele_nlo_ra_fast[n_cross];

    TGraphAsymmErrors *h_Zotov[n_cross];

    TGraphAsymmErrors *h_systematics[n_cross];

    const Int_t MAX_CROSS_SEC_BINS = 500;
    Double_t zero_array[MAX_CROSS_SEC_BINS] = {0.};

    Double_t x_et_bin[MAX_CROSS_SEC_BINS] = {0.};
    Double_t x_eta_bin[MAX_CROSS_SEC_BINS] = {0.};
    Double_t x_Q2_bin[MAX_CROSS_SEC_BINS] = {0.};
    Double_t x_x_bin[MAX_CROSS_SEC_BINS] = {0.};
    Double_t x_et_jet_bin[MAX_CROSS_SEC_BINS] = {0.};
    Double_t x_eta_jet_bin[MAX_CROSS_SEC_BINS] = {0.};

    Double_t x_xgamma_bin[MAX_CROSS_SEC_BINS] = {0.};
    Double_t x_xp_bin[MAX_CROSS_SEC_BINS] = {0.};
    Double_t x_dphi_bin[MAX_CROSS_SEC_BINS] = {0.};
    Double_t x_deta_bin[MAX_CROSS_SEC_BINS] = {0.};
    Double_t x_dphi_e_ph_bin[MAX_CROSS_SEC_BINS] = {0.};
    Double_t x_deta_e_ph_bin[MAX_CROSS_SEC_BINS] = {0.};
    
    /* середины бинов*/
    for(Int_t i = 0; i < number_etbins; i++)
        x_et_bin[i] = 0.5 * (et_bin[i] + et_bin[i+1]);
    for(Int_t i=0; i<number_etabins; i++)
        x_eta_bin[i] = 0.5 * (eta_bin_crosssec[i] + eta_bin_crosssec[i+1]);
    for(Int_t i=0; i<number_Q2bins; i++)
        x_Q2_bin[i] = 0.5 * (Q2_bin[i] + Q2_bin[i+1]);
    for(Int_t i=0; i<number_xbins; i++)
        x_x_bin[i] = 0.5 * (x_bin[i] + x_bin[i+1]);
    for(Int_t i=0; i<number_et_jetbins; i++)
        x_et_jet_bin[i] = 0.5 * (et_jet_bin[i] + et_jet_bin[i+1]);
    for(Int_t i=0; i<number_eta_jetbins; i++)
        x_eta_jet_bin[i] = 0.5 * (eta_jet_bin[i] + eta_jet_bin[i+1]);
    for(Int_t i = 0; i < number_xgamma_bins; i++)
        x_xgamma_bin[i] = 0.5 * (xgamma_bin[i] + xgamma_bin[i+1]);
    for(Int_t i = 0; i < number_xp_bins; i++)
        x_xp_bin[i] = 0.5 * (xp_bin[i] + xp_bin[i+1]);
    for(Int_t i = 0; i < number_dphi_bins; i++)
        x_dphi_bin[i] = 0.5 * (dphi_bin[i] + dphi_bin[i+1]);
    for(Int_t i = 0; i < number_deta_bins; i++)
        x_deta_bin[i] = 0.5 * (deta_bin[i] + deta_bin[i+1]);
    for(Int_t i = 0; i < number_dphi_e_ph_bins; i++)
        x_dphi_e_ph_bin[i] = 0.5 * (dphi_e_ph_bin[i] + dphi_e_ph_bin[i+1]);
    for(Int_t i = 0; i < number_deta_e_ph_bins; i++)
        x_deta_e_ph_bin[i] = 0.5 * (deta_e_ph_bin[i] + deta_e_ph_bin[i+1]);

    //////////////////////////////////////////////////
    //
    //          Hadronisation correction + styling
    //
    //////////////////////////////////////////////////
    apply_hadronisation_corrections();//warning hist_apply_hadronisation_corrections.c - correct theor values
    
    h_systematics[0] = new TGraphAsymmErrors(number_etbins, x_et_bin, y_1stcross_et, zero_array, zero_array, eyl_syst_et, eyh_syst_et);
    h_systematics[1] = new TGraphAsymmErrors(number_etabins, x_eta_bin, y_1stcross_eta, zero_array, zero_array, eyl_syst_eta, eyh_syst_eta);
    h_systematics[2] = new TGraphAsymmErrors(number_Q2bins, x_Q2_bin, y_1stcross_Q2, zero_array, zero_array, eyl_syst_Q2, eyh_syst_Q2);
    h_systematics[3] = new TGraphAsymmErrors(number_xbins, x_x_bin, y_1stcross_x, zero_array, zero_array, eyl_syst_x, eyh_syst_x);
    h_systematics[4] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet_bin, y_1stcross_et_jet, zero_array, zero_array, eyl_syst_et_jet, eyh_syst_et_jet);
    h_systematics[5] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet_bin, y_1stcross_eta_jet, zero_array, zero_array, eyl_syst_eta_jet, eyh_syst_eta_jet);
        h_systematics[6] = new TGraphAsymmErrors(number_xgamma_bins, x_xgamma_bin, y_1stcross_xgamma, zero_array, zero_array, eyl_syst_xgamma, eyh_syst_xgamma);
        h_systematics[7] = new TGraphAsymmErrors(number_xp_bins, x_xp_bin, y_1stcross_xp, zero_array, zero_array, eyl_syst_xp, eyh_syst_xp);
        h_systematics[8] = new TGraphAsymmErrors(number_dphi_bins, x_dphi_bin, y_1stcross_dphi, zero_array, zero_array, eyl_syst_dphi, eyh_syst_dphi);
        h_systematics[9] = new TGraphAsymmErrors(number_deta_bins, x_deta_bin, y_1stcross_deta, zero_array, zero_array, eyl_syst_deta, eyh_syst_deta);
        h_systematics[10] = new TGraphAsymmErrors(number_dphi_e_ph_bins, x_dphi_e_ph_bin, y_1stcross_dphi_e_ph, zero_array, zero_array, eyl_syst_dphi_e_ph, eyh_syst_dphi_e_ph);
        h_systematics[11] = new TGraphAsymmErrors(number_deta_e_ph_bins, x_deta_e_ph_bin, y_1stcross_deta_e_ph, zero_array, zero_array, eyl_syst_deta_e_ph, eyh_syst_deta_e_ph);
    
    //////////////////////////////////////////////////
    //
    //          Calculating cross-section for each case
    //
    //////////////////////////////////////////////////
    for(Int_t i = 0; i < n_cross; i++) 
    {
        selectedoutput << "==================================================================================================" <<endl;
        selectedoutput << "processing variable " << s_var[i] << endl;
        if (nodebugmode) cout << "==================================================================================================" <<endl;
        if (!nodebugmode) cout << "processing variable " << s_var[i] << endl;
        if (!nodebugmode) cout << "AND IT IS " << cs_x_names[i] << endl;
        //    this->h_det_prph_sum[i]->Scale((this->h_det_data_sum[i]->Integral()-this->h_det_rad_sum[i]->Integral())/this->h_det_prph_sum[i]->Integral());
        //    this->h_had_prph_sum[i]->Scale((this->h_det_data_sum[i]->Integral()-this->h_det_rad_sum[i]->Integral())/this->h_det_prph_sum[i]->Integral());
        //    this->h_hd_prph_sum[i]->Scale((this->h_det_data_sum[i]->Integral()-this->h_det_rad_sum[i]->Integral())/this->h_det_prph_sum[i]->Integral());
        //    this->h_hd_prph_sum[i]-Scale(param_et);
        Double_t int_data = this->h_det_data_sum[i]->Integral(),
                 int_ll   = this->h_det_rad_sum[i]->Integral(),
                 int_data_err =0, int_ll_err = 0.;
        
        //! use existing function!
        for(Int_t j = 0; j < this->h_det_data_sum[i]->GetNbinsX(); j++) // integrating over bins
        {
            Double_t err = this->h_det_data_sum[i]->GetBinError(j+1);
            int_data_err += err * err;
            Double_t err1 = this->h_det_rad_sum[i]->GetBinError(j+1);
            int_ll_err += err1 * err1;
        }
        
        int_data_err = TMath::Sqrt(int_data_err);
        int_ll_err = TMath::Sqrt(int_ll_err);
        
        TString s; 
        s.Form("h_cross_section_" + s_var[i]);
        //    h_cross[i] = (TH1D*)h_det_prph_sum[i]->Clone();//what was that?
        //    h_cross[i]->SetName(s + "temp");//what was that?
        /*
         * 020715 можно переписать через класс
         */
        if (nodebugmode) cout << "choose  variable" << endl;
        Double_t * param;
        Double_t * param_err;
        {
            if (s_var[i] == "et")
            {
                param = param_et_PhotonsFit; //param_et;//param_xgamma_PhotonsFit
                param_err = param_err_et_PhotonsFit;//param_err_et;
            }
            if(s_var[i]=="eta") 
            {
                param = param_eta_PhotonsFit; //param_eta;
                param_err = param_err_eta_PhotonsFit;//param_err_eta;
            }
            if(s_var[i] == "Q2")
            {
                param = param_q2_PhotonsFit;//param_q2;
                param_err = param_err_q2_PhotonsFit;//param_err_q2;
            }
            if(s_var[i]=="x") 
            {
                param = param_x_PhotonsFit;//param_x;
                param_err = param_err_x_PhotonsFit;//param_err_x;
            }
            if(s_var[i]=="et_jet") 
            {
                param = param_et_jet_PhotonsFit;//param_et_jet;
                param_err = param_err_et_jet_PhotonsFit;//param_err_et_jet;
            }
            if(s_var[i]=="eta_jet") 
            {
                param = param_eta_jet_PhotonsFit;//param_eta_jet;
                param_err = param_err_eta_jet_PhotonsFit;//param_err_eta_jet;
            }
            if(s_var[i]=="xgamma") 
            {
                param = param_xgamma_PhotonsFit;//param_xgamma;
                param_err = param_err_xgamma_PhotonsFit;//param_err_xgamma;
            }
            if(s_var[i]=="xp") 
            {
                param = param_xp_PhotonsFit;//param_xp;
                param_err = param_err_xp_PhotonsFit;//param_err_xp;
            }
            if(s_var[i]=="dphi") 
            {
                param = param_dphi_PhotonsFit;//param_dphi;
                param_err = param_err_dphi_PhotonsFit;//param_err_dphi;
            }
            if(s_var[i]=="deta") 
            {
                param = param_deta_PhotonsFit;//param_deta;
                param_err = param_err_deta_PhotonsFit;//param_err_deta;
            }
            if(s_var[i]=="dphi_e_ph") 
            {
                param = param_dphi_e_ph_PhotonsFit;//param_dphi_e_ph;
                param_err = param_err_dphi_e_ph_PhotonsFit;//param_err_dphi_e_ph;
            }
            if(s_var[i]=="deta_e_ph") 
            {
                param = param_deta_e_ph_PhotonsFit;//param_deta_e_ph;
                param_err = param_err_deta_e_ph_PhotonsFit;//param_err_deta_e_ph;
            }
        }

        
        h_det_rad_sum_copy[i] = (TH1D*)h_det_rad_sum[i]->Clone();
        h_det_prph_sum_copy[i] = (TH1D*)h_det_prph_sum[i]->Clone();

        CalculateCrossSec(h_det_data_sum[i],
                        h_det_rad_sum[i],
                        h_had_rad_sum[i],
                        h_hd_rad_sum[i],
                        h_det_prph_sum[i],
                        h_had_prph_sum[i],
                        h_hd_prph_sum[i],
                        h_acceptance_rad[i],
                        h_acceptance_prph[i],
                        total_luminosity_data,
                        h_cross[i],
                        s,
                        param,
                        param_err,
                        h_cross_copy[i],
                        h_det_rad_sum_copy[i],
                        h_det_prph_sum_copy[i]);
        if (i==4) dout("here");
         if(s_var[i] == "Q2")
        {
          for(Int_t bb = 0; bb < h_cross[i][7]->GetNbinsX(); bb++)
            if (nodebugmode) cout << "lumi unc. in bin " << bb << ": " << h_cross[i][7]->GetBinError(bb+1) << " " << endl;
        }
        //!Compare1st2nd(i, h_1st_cross[i], h_cross[i]);// h_cross теперь относительно чего-то ,
        
        if (nodebugmode) cout << "going into SetSystematicErrors" << endl;
        //!SetSystematicErrors(i, h_1st_cross[i], h_cross[i], gr_cross[i]); НАдо дописать для остальных гистограмм
        if (nodebugmode) cout << "returned from SetSystematicErrors" << endl;
        dout("Done:", i);

        h_cross[i][0]->SetLineColor(kBlack);
        h_cross[i][1]->SetLineColor(kBlue);
        h_cross[i][2]->SetLineColor(kRed);
        h_cross[i][3]->SetLineColor(kGreen);

        data_for_CrossectionDrawer[i] = h_cross[i][1];//stat
        data_for_CrossectionDrawer_tot_err[i] = h_cross[i][0];// full error = stat+acc+lum
        sum_for_CrossectionDrawer[i]  = h_cross_copy[i][0];
        qq_for_CrossectionDrawer[i]   = h_cross_copy[i][8];//error =0
        ll_for_CrossectionDrawer[i]   = h_cross_copy[i][9];//error =0
        //FIG 3 TYPE - no sence for QQfit=1 withLL=0 res=QQ*a+bg*(1-a)
        if (false && QQfit != 0)
        {
            dout("making single fig3");
            TString legend_possition = "left up";
            TString canvas_name("cs_fig3_" + s_var[i]);
            TString variable(s_var[i]);
            if (variable.Contains("xp") )   legend_possition= "right up";
            
            TString title("cs, " + variable);
            Double_t ymax;
            Double_t number_bins = h_cross[i][0]->GetNbinsX();
            gStyle->SetOptStat(0);

            dout("settiong x2");
            Double_t x1, x2, y1, y2;
            {
                if(legend_possition.Contains("left"))
                {
                    x1 = 0.2;//0.15
                    x2 = 0.6;
                }
                else
                {
                    x1 = 0.45;
                    x2 = 0.86;
                }
                if(legend_possition.Contains("up"))
                {
                    y1 = 0.6;//0.5
                    y2 = 0.91;//0.88
                }
                else
                {
                    y1 = 0.1;
                    y2 = 0.45;
                }
            }
            if (variable.Contains("deta")) 
            {
                x2 = 0.5;
            }

            dout("settiong ymax begin");
            dout(h_cross[i][0]->GetMaximum());
            dout(h_cross_copy[i][0]->GetMaximum());
            if (h_cross[i][0]->GetMaximum() > h_cross_copy[i][0]->GetMaximum())
                ymax =  1.2 * h_cross[i][0]->GetMaximum();
            else
                ymax =  1.2 * h_cross_copy[i][0]->GetMaximum();
            if (variable.Contains("xgamma") ) ymax = ymax*5;
            if (variable.Contains("xp")) ymax = ymax*2;
            if (variable.Contains("deta")) ymax = ymax*1.5;
            dout("settiong ymax ended");
            if (i==9) dout(ymax);
            TLegend *leg = new TLegend(x1, y1, x2, y2);
            leg->SetBorderSize(0);
            leg->SetFillStyle(0);
            
            SetFigure3Style(h_cross[i][0], h_cross_copy[i][0], h_cross_copy[i][8], h_cross_copy[i][9], 0);

            TString binsof("bins of "+ s_var[i]);
            TCanvas *c_control = new TCanvas(canvas_name, binsof, 800, 600);
            TH2D *h_window_control;
            if (!variable.Contains("xgamma")) h_window_control = new TH2D("h_window_fig3_"+variable, "title", number_bins, all_bins[i][0], \
                                                all_bins[i][(Int_t)number_bins ], 1000, -0.0001, ymax);//array_bin[0], array_bin[number_bins - 1]
            else h_window_control = new TH2D("h_window_fig3_"+variable, "title", number_bins, all_bins[i][0], \
                                                all_bins[i][(Int_t)number_bins ], 10000, -0.0001, ymax);
            if (true && variable.Contains("xp") || variable.Contains("gamma") ) c_control->GetPad(0)->SetLogy();
            
            c_control->GetPad(0)->SetTicks(1,1);
            c_control->GetPad(0)->SetFrameBorderMode(0);
            c_control->GetPad(0)->SetBorderMode(0);
            c_control->GetPad(0)->SetFillColor(kWhite);
            c_control->GetPad(0)->SetGrid(0, 0);
            sign_window(c_control->GetPad(0), h_window_control, cs_x_names[i] , cs_y_names[i], "", "large");
      
            c_control->GetPad(0)->SetMargin(c_control->GetPad(0)->GetLeftMargin() + 0.08 , \
                                            c_control->GetPad(0)->GetRightMargin() - 0.03 ,\
                                            c_control->GetPad(0)->GetBottomMargin()  + 0.08, \
                                            c_control->GetPad(0)->GetTopMargin() - 0.03);
            
            h_window_control->GetYaxis()->SetRangeUser(-0.0001, ymax);
            c_control->GetPad(0)->Update();
            h_window_control->Draw();
            //h_res->GetYaxis()->SetRange(0, h_res->GetMaximum());

            
          
            const Int_t n = all_nbins[i];
               Double_t x[n];
               Double_t y[n];
               Double_t exl[n] ;
               Double_t exh[n] ;
               Double_t eyl[n];
               Double_t eyh[n];
               //h_cross[i][0]->GetXaxis()->GetCenter(x)
               for(int j = 0; j < h_cross[i][0]->GetNbinsX(); j++)
               {
                x[j] = h_cross[i][0]->GetBinCenter(j+1) ;//+ 0.2 * h_cross[i][0]->GetBinWidth(j+1);
                y[j] = h_cross[i][0]->GetBinContent(j+1);
                exl[j] = 0;
                exh[j] = 0;
                eyl[j] = h_cross[i][1]->GetBinError(j+1);//statistical - not statistical and acceptance
                eyh[j] = TMath::Sqrt(pow(all_syst[i][j],2) + pow(h_cross[i][1]->GetBinError(j+1),2));
               }
                
               TGraphAsymmErrors* gr = new TGraphAsymmErrors(n,x,y,exl,exh,eyl,eyh);
               gr->SetMarkerColor(1);
               gr->SetMarkerSize(1.1);
               gr->SetMarkerStyle(20);
               gr->SetLineWidth(3);
               //gr->SetMarkerSize(5);


               h_cross_copy[i][8]->SetLineWidth(3);
               h_cross_copy[i][9]->SetLineWidth(3);
               h_cross_copy[i][0]->SetLineWidth(3);
            
                //h_cross[i][0]->GetYaxis()->SetRangeUser(0, 100);
                /*h_cross[i][0]->SetMarkerSize(1);
                h_cross[i][0]->SetMarkerColor(1);
                h_cross[i][0]->SetMarkerStyle(20);
                h_cross[i][0]->Draw("P X0 E1 SAME");*/  
                //P X0 - Cross section
                //"E1"  Draw error bars with perpendicular lines at the edges.; 
                //"X0"   When used with one of the "E" option, it suppress the error bar along X as gStyle->SetErrorX(0) would do.
                //"P"   Draw current marker at each bin except empty bins.
                //option = "F" draw the bins as filled areas.
                //"HIST"    When an histogram has errors it is visualized by default with error bars. To visualize it without errors use the option "HIST" together with the required option (eg "hist same c"). The "HIST" option can also be used to plot only the histogram and not the associated function(s).
                h_cross_copy[i][8]->Draw("HIST F E1 SAME");
                h_cross_copy[i][9]->Draw("HIST F E1 SAME");
                //h_cross_copy[i][0]->GetYaxis()->SetRange(0, ymax);
                h_cross_copy[i][0]->Draw("HIST F  SAME");
               gr->Draw("SAME P E");

                leg->AddEntry(gr, "ZEUS (prel.)", "pe"); //black " 326 pb^{-1}"
                //leg->AddEntry(h_cross[i][0], "ZEUS, 326 pb^{-1}", "pe"); //black
            leg->AddEntry(h_cross_copy[i][8], "QQ*1.6, MC", "f"); //blue
            leg->AddEntry(h_cross_copy[i][9], "LL, MC", "f");// red dots
            leg->AddEntry(h_cross_copy[i][0], "LL + QQ*1.6, MC", "f");// red
                if ( variable.Contains("xgamma") )    //
                    leg->Draw();
                c_control->GetPad(0)->RedrawAxis();
                TPaveText *t = new TPaveText(0.4, 0.93, 0.6, 1.0, "NDC"); // left-up
                t->AddText("ZEUS");
                t->SetFillColor(0);
                t->SetBorderSize(0);
                //t->Draw();
                //canvas_name += ".eps";
                c_control->Print(canvas_name+ ".eps");
                c_control->Print(canvas_name+ ".png");
        }

        if (false && i>5 && i<11)//comparison with theory
        {
            TString legend_possition = "right up";
            TString canvas_name("cs_theory_" + s_var[i]);
            TString variable(s_var[i]);
            if (variable.Contains("xgamma") || variable.Contains("dphi"))   legend_possition= "left up";
            
            TString title("cs, " + variable);
            Double_t ymax;
            Double_t number_bins = h_cross[i][0]->GetNbinsX();
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

            TH1D * h_theory = new TH1D("h_theory_" + variable, "theory for " + variable, all_nbins[i], all_bins[i]);
            for(int j = 0; j < h_cross[i][0]->GetNbinsX(); j++)
            {
                h_theory->SetBinContent(j+1, all_theory[i][j]);
                h_theory->SetBinError(j+1, 0); //We do not have this information
            }

            if (h_cross[i][0]->GetMaximum() > h_theory->GetMaximum())
                ymax =  1.2 * h_cross[i][0]->GetMaximum();
            else
                ymax =  1.2 * h_theory->GetMaximum();
            
            h_theory->SetLineColor(kBlue);
            h_theory->SetFillColor(kBlue);//kYellow
            h_theory->SetFillStyle(3004);//     h_deltaz_xgamma_prph_sum[i]->Sumw2();

            TLegend *leg = new TLegend(x1, y1, x2, y2);
            leg->SetBorderSize(0);
            leg->SetFillStyle(0);
            leg->AddEntry(h_cross[i][0], "ZEUS, 386 pb^{-1}", "f"); //black
            leg->AddEntry(h_theory, "Theory predicted", "l"); //blue

            TString binsof("bins of "+ s_var[i]);
            TCanvas *c_control = new TCanvas(canvas_name, binsof, 800, 600);
            TH2D *h_window_control;
            if (!variable.Contains("xgamma")) h_window_control = new TH2D("h_window_fig3_"+variable, "title", number_bins, all_bins[i][0], \
                                                all_bins[i][(Int_t)number_bins ], 1000, -0.0001, ymax);//array_bin[0], array_bin[number_bins - 1]
            else h_window_control = new TH2D("h_window_fig3_"+variable, "title", number_bins, all_bins[i][0], \
                                                all_bins[i][(Int_t)number_bins ], 10000, -0.0001, ymax);
            if (true && variable.Contains("xp") || variable.Contains("gamma") ) c_control->GetPad(0)->SetLogy();
            
            c_control->GetPad(0)->SetTicks(1,1);
            c_control->GetPad(0)->SetFrameBorderMode(0);
            c_control->GetPad(0)->SetBorderMode(0);
            c_control->GetPad(0)->SetFillColor(kWhite);
            c_control->GetPad(0)->SetGrid(0, 0);
            sign_window(c_control->GetPad(0), h_window_control, cs_x_names[i] , cs_y_names[i], "", "large");
      
            c_control->GetPad(0)->SetMargin(c_control->GetPad(0)->GetLeftMargin() + 0.03 , \
                                            c_control->GetPad(0)->GetRightMargin() - 0.03 ,\
                                            c_control->GetPad(0)->GetBottomMargin()  + 0.03, \
                                            c_control->GetPad(0)->GetTopMargin() - 0.03);
            
            h_window_control->GetYaxis()->SetRangeUser(-0.0001, ymax);
            c_control->GetPad(0)->Update();
            h_window_control->Draw();

           
            
                //h_cross[i][0]->GetYaxis()->SetRangeUser(0, 100);
                h_cross[i][0]->SetMarkerSize(1);
                h_cross[i][0]->SetMarkerColor(1);
                h_cross[i][0]->SetMarkerStyle(20);
                h_cross[i][0]->Draw("P X0 E1 SAME"); 
                //P X0 - Cross section
                //"E1"  Draw error bars with perpendicular lines at the edges.; 
                //"X0"   When used with one of the "E" option, it suppress the error bar along X as gStyle->SetErrorX(0) would do.
                //"P"   Draw current marker at each bin except empty bins.
                //option = "F" draw the bins as filled areas.
                //"HIST"    When an histogram has errors it is visualized by default with error bars. To visualize it without errors use the option "HIST" together with the required option (eg "hist same c"). The "HIST" option can also be used to plot only the histogram and not the associated function(s).
                h_theory->Draw("HIST SAME");
                if (!(variable.Contains("eta") || variable.Contains("xp") ||  variable.Contains("gamma") ))    
                    leg->Draw();
                c_control->GetPad(0)->RedrawAxis();
                TPaveText *t = new TPaveText(0.4, 0.9, 0.6, 1.0, "brNDC"); // left-up
                t->AddText("ZEUS");
                //t->Draw();
                canvas_name += ".eps";
                c_control->Print(canvas_name);
        }

    }

    if (true && QQfit != 0)
    {  
        //m - on one page n - width
        //usual m=6 n=2
        CrossectionDrawer::m = 1;
        CrossectionDrawer::n = 1;
        CrossectionDrawer::for_paper = true;
        /* //Fontanazz prediction on full range
        CrossectionDrawer::DrawAll(data_for_CrossectionDrawer, data_for_CrossectionDrawer_tot_err,
                                        sum_for_CrossectionDrawer, \
                                     qq_for_CrossectionDrawer, ll_for_CrossectionDrawer, \
                                     all_bins, s_var, n_cross, \
                                     true, all_theory_cs_font, all_theory_cs_font_pos, all_theory_cs_font_neg, "Fontannaz");
        */
        // BLZ prediction
        CrossectionDrawer::DrawAll(data_for_CrossectionDrawer, data_for_CrossectionDrawer_tot_err,
                                        sum_for_CrossectionDrawer, \
                                     qq_for_CrossectionDrawer, ll_for_CrossectionDrawer, \
                                     all_bins, s_var, n_cross, \
                                     true, all_theory_cs, all_theory_pos, all_theory_neg, "BLZ");
        

        


    }

}
