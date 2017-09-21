/*CalculateCrossSec(        h_det_data_sum[i],  data
 *         
                            h_det_rad_sum[i],   LL
                            h_had_rad_sum[i],   LL
                            h_hd_rad_sum[i],    LL
 *     
                            h_det_prph_sum[i],  QQ
                            h_had_prph_sum[i],  QQ
                            h_hd_prph_sum[i],   QQ
 *  
                            h_acceptance_rad[i], 
                            h_acceptance_prph[i],
                            total_luminosity_data,  
 * 
                            h_cross[i],             
                            s,
 * 
                            param_et,
                            param_err_et);
 */
void Hist::CalculateCrossSec(TH1D* data, 
                             TH1D* ll_det, TH1D* ll_had, TH1D* ll_hd,
                             TH1D *det, TH1D* had, TH1D* hd, 
                             TH1D* ll_acc, TH1D *acc, Double_t Lumi, 
                             TH1D **res, TString name, 
                             Double_t* param, Double_t* param_err, 
                             TH1D **res_copy,
                             TH1D* ll_det_copy = 0, TH1D* det_copy = 0
/*, Double_t integral_data, Double_t integral_ll, Double_t integral_data_err, Double_t integral_ll_err*/) 
{
  if (nodebugmode) cout << "in CalculateCrossSec: calculate " << name << ", lumi = " << Lumi << " pb^{-1}" << endl;

  Double_t integral_data, integral_LLplusQQ, integral_Nqq, integral_Nqq_err, integral_data_err, integral_LLplusQQ_err,
           integral_prph = 0.,// = det->Integral();
           integral_prph_err = 0.,
           scale_data = 1,//(integral_data - integral_ll) / integral_prph;
           scale_err1 = 0.,//integral_data_err/integral_prph;
           scale_err2 = 0.,//integral_ll_err  /integral_prph;
           scale_err3 = 0.,//(integral_data - integral_ll)*integral_prph_err/(integral_prph**2);
           scale_data_err = 0.,//scale_err1*scale_err1 + scale_err2*scale_err2 + scale_err3*scale_err3;
           sigma_tot = 0, 
           sigma_tot_err = 0.,
           sigma_tot_err_2 = 0.,
           fig3_scale = 1.6,
           sigma_tot_copy = 0, 
           sigma_tot_err_copy = 0.,
           sigma_tot_ll = 0,
           sigma_tot_qq = 0;
  Int_t    nbins = 0;

  if (ll_det_copy == 0) dout("something went wrong");
  if (QQfit == 0)
  {
    TH1D* LLplusQQ = (TH1D*)ll_det->Clone(); //h_det_rad_sum LLdet
    LLplusQQ->SetName("ll_plus_qq");
    det->Scale(total_luminosity_data / lumi_mc_prph);//h_det_prph_sum QQ
    had->Scale(total_luminosity_data / lumi_mc_prph);//h_had_prph_sum QQ
    hd->Scale(total_luminosity_data / lumi_mc_prph);//h_hd_prph_sum QQ

    LLplusQQ->Add(det);//LLdet + QQ'det
    if (nodebugmode && name.Contains("deta_e_ph") ) //s_var[i]=="deta_e_ph"
        {
          dout( 
            "LLplusQQ->GetBinContent(1): ", LLplusQQ->GetBinContent(1), "\n",
            "ll_det->GetBinContent(1):", ll_det->GetBinContent(1), "\n",
          "det->GetBinContent(1):", det->GetBinContent(1), "\n",
          "had->GetBinContent(1):", had->GetBinContent(1), "\n",
          "hd->GetBinContent(1):", hd->GetBinContent(1));
        }
    
    //scale LLplusQQ to data
    for(Int_t i = 0; i < LLplusQQ->GetNbinsX(); i++) 
    {
        integral_data = data->GetBinContent(i+1);
        integral_data_err = data->GetBinError(i+1);
        integral_LLplusQQ = LLplusQQ->GetBinContent(i+1);
        integral_LLplusQQ_err = LLplusQQ->GetBinError(i+1);
        if (nodebugmode) cout << "bin " << i << ", data = " << integral_data << " +- " << integral_data_err << ", ll+qq = " << integral_LLplusQQ << " +- " << integral_LLplusQQ_err << endl;
        
        scale_data = integral_data / integral_LLplusQQ;// data / (QQ'det+LLdet)  
        scale_err1 = integral_data_err / integral_LLplusQQ;// data_err/QQLL
        scale_err2 = integral_data * integral_LLplusQQ_err / (integral_LLplusQQ * integral_LLplusQQ);// data*QQLL_err/LLQQ^2
        scale_data_err = TMath::Sqrt(scale_err1*scale_err1 + scale_err2*scale_err2);
        
        if (nodebugmode) cout << "scale_data_ll (in bin "<< i<< ") = " << data->GetBinContent(i+1) << " - " << ll_det->GetBinContent(i+1) << " = " << scale_data << " +- " << scale_data_err << endl;
        if (nodebugmode) cout << "--> scaling by N_{data-LL}" << endl;
        
        Double_t err = LLplusQQ->GetBinError(i+1),
                 cont = LLplusQQ->GetBinContent(i+1);//! лишняя integral_LLplusQQ
        Double_t new_err = TMath::Sqrt(cont * cont * scale_data_err * scale_data_err + err * err * scale_data * scale_data),
                 new_cont = scale_data * cont;
        if (nodebugmode) cout << "scaling: old content: " << i << " " << cont << " +- " << err << endl;
        if (nodebugmode) cout << "scaling: new content: " << i << " " << new_cont << " +- " << new_err << endl;
        LLplusQQ->SetBinContent(i+1, new_cont);
        LLplusQQ->SetBinError(i+1, err);
        if (name.Contains("xgamma") && nodebugmode) cout<< i<<") " <<"LLplusQQ = "<<LLplusQQ->GetBinContent(i+1) <<" +/- "<< LLplusQQ->GetBinError(i+1)<<endl;
    }

    //scale LLplusQQ by parameter
    // могу переписать через уже существующую функцию класса
    if (nodebugmode) cout << "--> scaling by fit param" << endl;
    for(Int_t i = 0; i < LLplusQQ->GetNbinsX(); i++) 
    {
        
       
        Double_t cont = LLplusQQ->GetBinContent(i+1);
        Double_t err = LLplusQQ->GetBinError(i+1);
        if (nodebugmode) cout << "scaling: old content: " << i << " " << cont << " +- " << err << ", param = " << param[i] << " +- " << param_err[i] << endl;
        //if (name.Contains("deta_e_ph"))
        Double_t new_err = TMath::Sqrt(cont*cont*param_err[i]*param_err[i] + err*err*param[i]*param[i]);
        Double_t new_cont = cont * param[i];
        if (nodebugmode) cout << "scaling: old content: " << i << " " << new_cont << " +- " << new_err << endl;
        /*if (!nodebugmode && name.Contains("deta_e_ph") && i == 0) //s_var[i]=="deta_e_ph"
        {
          dout("bin_width: ",bin_width,"\n",
           "ll_plus_qq: ", ll_plus_qq,"\n",
           "ll_events: ", ll_events,"\n",
           "(ll_plus_qq - ll_events) / C_acc: ", (ll_plus_qq - ll_events) / C_acc ,"\n",
           "(C_ll_acc!=0)*ll_events/C_ll_acc: ", (C_ll_acc!=0)*ll_events/C_ll_acc );
        }*/
        LLplusQQ->SetBinContent(i+1, new_cont);
        LLplusQQ->SetBinError(i+1, new_err);
        if (nodebugmode && name.Contains("deta_e_ph")) cout<< "After" << i<<") " <<"LLplusQQ = "<<LLplusQQ->GetBinContent(i+1) <<" +/- "<< LLplusQQ->GetBinError(i+1)<<endl;
    }

    res[0] = (TH1D*)det->Clone();
    res[0]->SetName(name);
    //statistic, acceptance, luminosity, full
    res[1] = (TH1D*)det->Clone();
    res[1]->SetName(name + "_stat_fit_err");
    res[2] = (TH1D*)det->Clone();
    res[2]->SetName(name + "_acc_err");
    res[3] = (TH1D*)det->Clone();
    res[3]->SetName(name + "_lumi_err");
    //ratios
    res[4] = (TH1D*)det->Clone();
    res[4]->SetName(name + "_ratio");
    //statistic, acceptance, luminosity, full
    res[5] = (TH1D*)det->Clone();
    res[5]->SetName(name + "_stat_fit_err_ratio");
    res[6] = (TH1D*)det->Clone();
    res[6]->SetName(name + "_acc_err_ratio");
    res[7] = (TH1D*)det->Clone();
    res[7]->SetName(name + "_lumi_err_ratio");
    
    //  TH1D *h_Acc = (TH1D*)h_Data->Clone(); //histo with acceptance. Here is to have right binning!
    nbins  = res[0]->GetNbinsX();
    if (nodebugmode) cout << "in plot_cross_section: nbins = " << nbins << endl;
    for(Int_t i = 0; i < nbins; i++)
    {
        Double_t prph          = det->GetBinContent(i+1),//QQ // + ll_det->GetBinContent(i+1);
                 prph_had      = had->GetBinContent(i+1),//QQ
                 prph_hd       = hd->GetBinContent(i+1),//QQ
                 ll_events     = ll_det->GetBinContent(i+1),//LL
                 ll_had_events = ll_had->GetBinContent(i+1),//LL        
                 ll_plus_qq    = LLplusQQ->GetBinContent(i+1),//QQLL
                 bin_width     = det->GetBinWidth(i+1),
                 err1 = 0., err2 = 0., err3 = 0., err11 = 0., err22 = 0., err = 0.,  //statistic, acceptance, luminosity, full
                 C_acc         = acc->GetBinContent(i+1),
                 C_err         = acc->GetBinError(i+1),
                 C_ll_acc      = ll_acc->GetBinContent(i+1),
                 C_ll_err      = ll_acc->GetBinError(i+1);
        
        /*      
          if(prph != 0.)
          //  C_acc = prph_had / prph;
          //      else 
          //  {
          //    if (nodebugmode) cout << "prph det bin content is 0! Can't calculate acceptance." <<endl;
          //    exit(1);
          //  }
          //      if (nodebugmode) cout << "C_acc = " << C_acc << ", C_acc_old = " << acc->GetBinContent(i+1) << endl;
          //      cross_sec = prph * C_acc;
          //      cross_sec /= bin_width;
          //      cross_sec /= Lumi;
          //errors:
          //      C_err = TMath::Sqrt(prph_had/(prph*prph*prph));
          //      C_err *= TMath::Sqrt(prph + prph_had - 2*prph_hd);
        */      
        /*
          //      err1 = TMath::Sqrt(prph) * C_acc / (bin_width * Lumi);
          ///      err2 = prph * C_err / (bin_width * Lumi);
          //      err = TMath::Sqrt(err1*err1 + err2*err2);
        */

        //      cross_sec          = (           prph           / C_acc + ll_events/C_ll_acc)  / (bin_width * Lumi);
        Double_t cross_sec         = ( (ll_plus_qq - ll_events) / C_acc + (C_ll_acc!=0)*ll_events/C_ll_acc ) / (bin_width * Lumi),
                 prph_cross_sec    =   (ll_plus_qq - ll_events)                                / (C_acc * bin_width * Lumi),
                 ll_cross_sec      =                                      ll_events            / (C_ll_acc * bin_width * Lumi),
                 prph_mc_cross_sec =    prph_had                                               / (bin_width * 3552.40),
                 ll_mc_cross_sec   =                                      ll_had_events        / (bin_width * (lumi_mc_bg[0] + lumi_mc_bg[1] + lumi_mc_bg[2]));
         if (nodebugmode && name.Contains("deta") && !name.Contains("deta_e_ph") && i == 0) 
         {
          dout(C_acc, C_ll_acc );
          int q1 = 1 + ((1<0)*1);
          cout<<q1<<endl;

         }
        
        //error propagation for LLplusQQ cs
          //statistic errors
            /* how it was for Oleg
              err1 = LLplusQQ->GetBinError(i+1) / (bin_width * Lumi * C_acc);
              err11 = ll_det->GetBinError(i+1) * (1 / C_acc + 1 / C_ll_acc) / (bin_width * Lumi);
              err1 = TMath::Sqrt(err1 * err1 + err11 * err11);
            */
          err1 = LLplusQQ->GetBinError(i+1) / (bin_width * Lumi * C_acc);
            if (nodebugmode &&name.Contains("xgamma")) cout<< i<<") " <<"LLplusQQ = "<<LLplusQQ->GetBinContent(i+1) <<" +/- "<< LLplusQQ->GetBinError(i+1)<<endl;
          err11 = ll_det->GetBinError(i+1) * (1 / C_acc - 1 / C_ll_acc) / (bin_width * Lumi);
          err1 = TMath::Sqrt(err1 * err1 + err11 * err11);

          //acceptance errors
          err2 = (ll_plus_qq - ll_events) * C_err / (bin_width * Lumi * C_acc * C_acc);
          err22 = ll_events * C_ll_err / (bin_width * Lumi * C_acc * C_ll_acc);
          err2 = TMath::Sqrt(err2*err2 + err22*err22);  
          
          //luminosity errors are negleckted
          err3 = 0.;//0.026*cross_sec;    
          err = TMath::Sqrt(err1*err1 + err2*err2 + err3*err3);//full

        
        //error propagation for LL cs
          //statistic errors
          Double_t err1_ll = TMath::Sqrt( pow(ll_det->GetBinError(i+1) * ( - 1 / C_ll_acc) / (bin_width * Lumi), 2));
          //acceptance errors
          Double_t err2_ll = TMath::Sqrt(pow(ll_events * C_ll_err / (bin_width * Lumi * C_acc * C_ll_acc), 2));  
          //luminosity errors are negleckted
          Double_t err3_ll = 0.;   
          Double_t err_ll = TMath::Sqrt(err1_ll*err1_ll + err2_ll*err2_ll + err3_ll*err3_ll);//full
        

        if (nodebugmode && name.Contains("deta_e_ph") && i == 0) //s_var[i]=="deta_e_ph"
        {
          dout("bin_width: ",bin_width,"\n",
           "ll_plus_qq: ", ll_plus_qq,"\n",
           "ll_events: ", ll_events,"\n",
           "(ll_plus_qq - ll_events) / C_acc: ", (ll_plus_qq - ll_events) / C_acc ,"\n",
           "(C_ll_acc!=0)*ll_events/C_ll_acc: ", (C_ll_acc!=0)*ll_events/C_ll_acc );
        }
        res[0]->SetBinContent(i+1, cross_sec);
        res[0]->SetBinError(i+1, err);//full
        res[1]->SetBinContent(i+1, cross_sec);
        res[1]->SetBinError(i+1, err1);//statistic
        res[2]->SetBinContent(i+1, cross_sec);
        res[2]->SetBinError(i+1, err2);// acceptance
        res[3]->SetBinContent(i+1, cross_sec);
        res[3]->SetBinError(i+1, err3);//luminosity
        
        //ratios
        res[4]->SetBinContent(i+1, 0);
        res[4]->SetBinError(i+1, err/cross_sec);
        res[5]->SetBinContent(i+1, 0);
        res[5]->SetBinError(i+1, err1/cross_sec);
        res[6]->SetBinContent(i+1, 0);
        res[6]->SetBinError(i+1, err2/cross_sec);
        res[7]->SetBinContent(i+1, 0);
        res[7]->SetBinError(i+1, err3/cross_sec);
        //      h_Acc->SetBinContent(i+1, 1./C_acc);
        //      h_Acc->SetBinError(i+1, C_err/(C_acc*C_acc));
        
        sigma_tot += cross_sec * bin_width;
        sigma_tot_err += err * err * bin_width * bin_width;
         
        //if (!nodebugmode && name.Contains("et") && !name.Contains("eta") && !name.Contains("jet"))
        if (nodebugmode && name.Contains("eta") && !name.Contains("deta") && !name.Contains("e_ph") && !name.Contains("jet")) cout<< name << " cros sec in bin " << i << ": " << cross_sec 
                << " +- " << err << ", acc_Prompt = " << C_acc << ", nentries = " << prph << endl;
        //      if (nodebugmode) cout << "bin " << i+1 << " from " << low_edge << " to " << bott;
        selectedoutput << name << " cros sec in bin " << i << ": " << cross_sec 
                << " +- " << err << ", lumi = " << Lumi << ", acc_Prompt = " 
                << C_acc << ", binWidth = " << bin_width << ", nentries = " << prph << endl;
        //      if (nodebugmode) cout << "bin " << i+1 << " from " << low_edge << " to " << bottom_edge << " : sigma = " << cross_sec  << " +- " << err << endl;
        selectedoutput << "errors (stat. and fit, acc., lumi., total), %: " << err1 / cross_sec << ", " 
             << err2/cross_sec << ", " << err3 / cross_sec << ", " << err / cross_sec << endl;
        selectedoutput << "prph data: " << prph_cross_sec << ", prph mc: " << prph_mc_cross_sec << ", prph_had = " << prph_had <<  endl;
        selectedoutput << "ll data: " << ll_cross_sec << ", ll mc: " << ll_mc_cross_sec << endl;
        selectedoutput << "errors for ll (stat. and fit, acc., lumi., total), %: " << err1_ll / ll_cross_sec << ", " 
             << err2_ll/ll_cross_sec << ", " << err3_ll / ll_cross_sec << ", " << err_ll / ll_cross_sec << endl;
        
        if (nodebugmode && name.Contains("xp")) cout << name << " cros sec in bin " << i << ": " << cross_sec 
                << " +- " << err << ", lumi = " << Lumi << ", acc_Prompt = " 
                << C_acc << ", binWidth = " << bin_width << ", nentries = " << prph << endl;

        if (nodebugmode) cout << name << " cros sec in bin " << i << ": " << cross_sec 
                << " +- " << err << ", lumi = " << Lumi << ", acc_Prompt = " 
                << C_acc << ", binWidth = " << bin_width << ", nentries = " << prph << endl;
        //      if (nodebugmode) cout << "bin " << i+1 << " from " << low_edge << " to " << bottom_edge << " : sigma = " << cross_sec  << " +- " << err << endl;
        if (nodebugmode) cout << "errors (stat. and fit, acc., lumi., total), %: " << err1 / cross_sec << ", " 
             << err2/cross_sec << ", " << err3 / cross_sec << ", " << err / cross_sec << endl;
        if (nodebugmode) cout << "prph data: " << prph_cross_sec << ", prph mc: " << prph_mc_cross_sec << ", prph_had = " << prph_had <<  endl;
        if (nodebugmode) cout << "ll data: " << ll_cross_sec << ", ll mc: " << ll_mc_cross_sec << endl;
        fout << "h_1st[0]->SetBinContent(" << i+1 << ", " << cross_sec << ");" << endl;
        fout << "h_1st[0]->SetBinError(" << i+1 << ", " << err << ");" << endl;
    }//for i over bins
    fout << endl;
    if (nodebugmode) cout << "sigma_tot = " << sigma_tot << " +- " << TMath::Sqrt(sigma_tot_err) << " pb" << endl;
    selectedoutput << "sigma_tot = " << sigma_tot << " +- " << TMath::Sqrt(sigma_tot_err) << " pb" << endl;

    //TCanvas* c_acc  = new TCanvas("c_cs_" + name, "CS", 800, 600);
  }
  else// is not sueted for fitWithLLinBg
  {
  
    det->Scale(total_luminosity_data / lumi_mc_prph);//h_det_prph_sum QQ
    det_copy->Scale(total_luminosity_data / lumi_mc_prph);//h_det_prph_sum QQ
    had->Scale(total_luminosity_data / lumi_mc_prph);//h_had_prph_sum QQ
    hd->Scale(total_luminosity_data / lumi_mc_prph);//h_hd_prph_sum QQ
    
    //  ll_det_copy->Scale(total_luminosity_data / (lumi_mc_bg[0]+lumi_mc_bg[1]+lumi_mc_bg[2]));
    TH1D* Nqq = (TH1D*)det->Clone(); //h_det_rad_sum LLdet
    Nqq->SetName("N_qq");
    
    //scale Nqq to data
    if ( name.Contains("Q2") ) debug << "hist_calculate_cs:" << "\n\tdata->GetBinContent\tll_det->GetBinContent:" << endl;
    for(Int_t i = 0; i < Nqq->GetNbinsX(); i++) 
    {
        integral_data = data->GetBinContent(i+1) - fitWithLL * ll_det->GetBinContent(i+1);
        integral_data_err = TMath::Sqrt(data->GetBinError(i+1)*data->GetBinError(i+1) + fitWithLL * ll_det->GetBinError(i+1) * ll_det->GetBinError(i+1));
        integral_Nqq = Nqq->GetBinContent(i+1);
        integral_Nqq_err = Nqq->GetBinError(i+1);
        if (nodebugmode) cout << "bin " << i << ", data = " << integral_data << " +- " << integral_data_err << ", ll+qq = " << integral_Nqq << " +- " << integral_Nqq_err << endl;
        
        scale_data = integral_data / integral_Nqq;// data / qq 
        scale_err1 = integral_data_err / integral_Nqq;// data_err/QQ
        scale_err2 = integral_data * integral_Nqq_err / (integral_Nqq * integral_Nqq);// data*QQ_err/QQ^2
        scale_data_err = TMath::Sqrt(scale_err1*scale_err1 + scale_err2*scale_err2);
        
        Double_t err = Nqq->GetBinError(i+1),
                 cont = Nqq->GetBinContent(i+1);//! лишняя integral_Nqq
        Double_t new_err = TMath::Sqrt(cont * cont * scale_data_err * scale_data_err + err * err * scale_data * scale_data),
                 new_cont = scale_data * cont;
        if (nodebugmode) cout << "scaling: old content: " << i << " " << cont << " +- " << err << endl;
        if (nodebugmode) cout << "scaling: new content: " << i << " " << new_cont << " +- " << new_err << endl;


        new_cont = std::isnan(new_cont) ? 0 : new_cont;
        new_err = std::isnan(new_err) ? 0 : new_err;

        //if ( name.Contains("Q2") )  debug << "\t\t" << i << ")" << data->GetBinContent(i+1) << "\t" << ll_det->GetBinContent(i+1) << cont << " +- " << err << isnan(new_cont) << " +- " << isnan(new_err) << endl;
        
        Nqq->SetBinContent(i+1, new_cont);
        Nqq->SetBinError(i+1, err);
        if (name.Contains("xgamma") && nodebugmode) cout<< i<<") " <<"Nqq = "<<Nqq->GetBinContent(i+1) <<" +/- "<< Nqq->GetBinError(i+1)<<endl;
    }
    if ( false && name.Contains("Q2") ) 
    {
    dout("Controled exit");
    exit(0);
    }
    //scale Nqq by parameter
    if (nodebugmode) cout << "--> scaling by fit param" << endl;
    for(Int_t i = 0; i < Nqq->GetNbinsX(); i++) 
    {
        Double_t cont = Nqq->GetBinContent(i+1);
        Double_t err  = Nqq->GetBinError(i+1);
        if (nodebugmode) cout << "scaling: old content: " << i << " " << cont << " +- " << err << ", param = " << param[i] << " +- " << param_err[i] << endl;
       
        Double_t new_err = TMath::Sqrt(cont*cont*param_err[i]*param_err[i] + err*err*param[i]*param[i]);
        Double_t new_cont = cont * param[i];
        if (nodebugmode) cout << "scaling: old content: " << i << " " << new_cont << " +- " << new_err << endl;

        new_cont = std::isnan(new_cont) ? 0 : new_cont;
        new_err = std::isnan(new_err) ? 0 : new_err;

        Nqq->SetBinContent(i+1, new_cont);
        Nqq->SetBinError(i+1, new_err);
        if (nodebugmode && name.Contains("deta_e_ph")) cout<< "After" << i<<") " <<" Nqq = "<< Nqq->GetBinContent(i+1) <<" +/- "<< Nqq->GetBinError(i+1)<<endl;
        
        // Scaling the copy of QQ on det lev  by the tested parameter found by Oleg
        cont = det_copy->GetBinContent(i+1);
        err  = det_copy->GetBinError(i+1);
        new_err = TMath::Sqrt(cont*cont*0*0 + err*err*fig3_scale*fig3_scale);
        new_cont = cont * fig3_scale;
        det_copy->SetBinContent(i+1, new_cont);
        det_copy->SetBinError(i+1, new_err);
    }

    
    res[0] = (TH1D*)det->Clone();
    res[0]->SetName(name);
    //statistic, acceptance, luminosity, full
    res[1] = (TH1D*)det->Clone();
    res[1]->SetName(name + "_stat_fit_err");
    res[2] = (TH1D*)det->Clone();
    res[2]->SetName(name + "_acc_err");
    res[3] = (TH1D*)det->Clone();
    res[3]->SetName(name + "_lumi_err");
    //ratios
    res[4] = (TH1D*)det->Clone();
    res[4]->SetName(name + "_ratio");
    //statistic, acceptance, luminosity, full
    res[5] = (TH1D*)det->Clone();
    res[5]->SetName(name + "_stat_fit_err_ratio");
    res[6] = (TH1D*)det->Clone();
    res[6]->SetName(name + "_acc_err_ratio");
    res[7] = (TH1D*)det->Clone();
    res[7]->SetName(name + "_lumi_err_ratio");


    //if (nodebugmode && name.Contains("et_jet")  ) dout("here!");
    res_copy[0] = (TH1D*)det_copy->Clone();
    res_copy[0]->SetName(name + "_fig3");
    //statistic, acceptance, luminosity, full
    res_copy[1] = (TH1D*)det_copy->Clone();
    res_copy[1]->SetName(name + "_stat_fit_err" + "_fig3");
    res_copy[2] = (TH1D*)det_copy->Clone();
    res_copy[2]->SetName(name + "_acc_err" + "_fig3");
    res_copy[3] = (TH1D*)det_copy->Clone();
    res_copy[3]->SetName(name + "_lumi_err" + "_fig3");
    res_copy[8] = (TH1D*)det_copy->Clone();
    res_copy[8]->SetName(name + "_qq" + "_fig3");
    res_copy[9] = (TH1D*)ll_det_copy->Clone();
    res_copy[9]->SetName(name + "_ll" + "_fig3");

    //if (nodebugmode && name.Contains("et_jet")  ) dout("here");
    //ratios
    res_copy[4] = (TH1D*)det_copy->Clone();
    res_copy[4]->SetName(name + "_ratio" + "_fig3");
    //statistic, acceptance, luminosity, full
    res_copy[5] = (TH1D*)det_copy->Clone();
    res_copy[5]->SetName(name + "_stat_fit_err_ratio" + "_fig3");
    res_copy[6] = (TH1D*)det_copy->Clone();
    res_copy[6]->SetName(name + "_acc_err_ratio" + "_fig3");
    res_copy[7] = (TH1D*)det_copy->Clone();
    res_copy[7]->SetName(name + "_lumi_err_ratio" + "_fig3");
    
    //  TH1D *h_Acc = (TH1D*)h_Data->Clone(); //histo with acceptance. Here is to have right binning!
    nbins  = res[0]->GetNbinsX();
    if (nodebugmode) cout << "in plot_cross_section: nbins = " << nbins << endl;
    TH1D * test_forest = (TH1D*)det->Clone();
    Double_t test_deleteme = 0;
    for(Int_t i = 0; i < nbins; i++)
    {
      /*if (name.Contains("deta") && !name.Contains("e_ph") && i == 0 ) 
        {
          dout("BEFORE:", ll_det_copy->GetBinContent(1), ll_det->GetBinContent(1));
          ll_det_copy->SetBinContent(1, 0);
          ll_det->SetBinContent(1, 0);
          ll_det_copy->SetBinError(1, 0);
          ll_det->SetBinError(1, 0);
        }*/
      Double_t prph          = det->GetBinContent(i+1),//QQ 
               prph_had      = had->GetBinContent(i+1),//QQ
               prph_hd       = hd->GetBinContent(i+1),//QQ
               ll_events     = ll_det->GetBinContent(i+1),//LL
               ll_had_events = ll_had->GetBinContent(i+1),//LL        
               n_qq          = Nqq->GetBinContent(i+1),//QQLL
               bin_width     = det->GetBinWidth(i+1),
               err1 = 0., err2 = 0., err3 = 0., err11 = 0., err22 = 0., err = 0.,  //statistic, acceptance, luminosity, full
               C_acc         = acc->GetBinContent(i+1),
               C_err         = acc->GetBinError(i+1),
               C_ll_acc      = ll_acc->GetBinContent(i+1),
               C_ll_err      = ll_acc->GetBinError(i+1);


      Double_t ll_events_copy     = ll_det_copy->GetBinContent(i+1),//LL      
               n_qq_copy          = det_copy->GetBinContent(i+1),//QQLL
               err1_copy = 0., err2_copy = 0., err3_copy = 0., err_copy = 0.; //statistic, acceptance, luminosity, full
      

      /*      
        if(prph != 0.)
        //  C_acc = prph_had / prph;
        //      else 
        //  {
        //    if (nodebugmode) cout << "prph det bin content is 0! Can't calculate acceptance." <<endl;
        //    exit(1);
        //  }
        //      if (nodebugmode) cout << "C_acc = " << C_acc << ", C_acc_old = " << acc->GetBinContent(i+1) << endl;
        //      cross_sec = prph * C_acc;
        //      cross_sec /= bin_width;
        //      cross_sec /= Lumi;
        //errors:
        //      C_err = TMath::Sqrt(prph_had/(prph*prph*prph));
        //      C_err *= TMath::Sqrt(prph + prph_had - 2*prph_hd);
      */      
      /*
        //      err1 = TMath::Sqrt(prph) * C_acc / (bin_width * Lumi);
        ///      err2 = prph * C_err / (bin_width * Lumi);
        //      err = TMath::Sqrt(err1*err1 + err2*err2);
      */

      //      cross_sec          = (           prph           / C_acc + ll_events/C_ll_acc)  / (bin_width * Lumi);

      Double_t cross_sec         = ( (n_qq ) / C_acc + (C_ll_acc!=0) * fitWithLL * ll_events/C_ll_acc ) / (bin_width * Lumi),
               prph_cross_sec    =   (n_qq )                                / (C_acc * bin_width * Lumi),
               ll_cross_sec      =                                      ll_events            / (C_ll_acc * bin_width * Lumi),
               prph_mc_cross_sec =    prph_had                                               / (bin_width * 3552.40),
               ll_mc_cross_sec   =                                      ll_had_events        / (bin_width * (lumi_mc_bg[0] + lumi_mc_bg[1] + lumi_mc_bg[2]));
      
      Double_t cross_sec_copy         = ( (n_qq_copy ) / C_acc + (C_ll_acc!=0)*fitWithLL*ll_events_copy/C_ll_acc ) / (bin_width * Lumi),
               prph_cross_sec_copy    =   (n_qq_copy )                                / (C_acc * bin_width * Lumi);
      dout("IAN CS for LL part in", name, "bin", i, ":", ll_cross_sec, ";events: ", ll_events, "; C_ll_acc:", C_ll_acc, "check:", C_ll_acc,"?=", ll_events/ll_had_events,  "; bin_width:", bin_width, "; Lumi:", Lumi,"?=", (lumi_mc_bg[0] + lumi_mc_bg[1] + lumi_mc_bg[2]), "; had:", ll_mc_cross_sec, " +- " , ll_had->GetBinError(i+1)/(bin_width * (lumi_mc_bg[0] + lumi_mc_bg[1] + lumi_mc_bg[2])));
      // exit(1);
      test_forest->SetBinContent( i+1, prph / (C_acc*bin_width * Lumi));
      test_forest->SetBinError( i+1, TMath::Sqrt(pow(det->GetBinError(i+1) / (bin_width * Lumi * C_acc), 2) +
                                      pow(prph * C_err / (bin_width * Lumi * C_acc * C_acc), 2)) );
      if (name.Contains("deta") && !name.Contains("e_ph") && (C_ll_acc==0)) 
      {
        ll_det_copy->SetBinContent(i+1, 0);
        ll_det->SetBinContent(i+1, 0);
        ll_det_copy->SetBinError(i+1, 0);
        ll_det->SetBinError(i+1, 0);

        cross_sec         = ( (n_qq ) / C_acc ) / (bin_width * Lumi);
        ll_cross_sec      = 0;
        cross_sec_copy    = ( (n_qq_copy ) / C_acc ) / (bin_width * Lumi);
      }
      if (nodebugmode && name.Contains("deta") && !name.Contains("e_ph") ) dout(name, i, "cross_sec", cross_sec, "cross_sec_copy", cross_sec_copy);
      if (nodebugmode && name.Contains("deta") && !name.Contains("e_ph") ) dout("     qq:", (n_qq ) / C_acc ,"ll:", (C_ll_acc!=0)*fitWithLL*ll_events/C_ll_acc );
      if (nodebugmode && name.Contains("deta") && !name.Contains("e_ph") ) dout("fig3 qq:", (n_qq_copy ) / C_acc ,"ll:", (C_ll_acc!=0)*fitWithLL*ll_events_copy/C_ll_acc );
      if (nodebugmode && name.Contains("deta") && !name.Contains("deta_e_ph") && i == 0) 
      {
        dout(C_acc, C_ll_acc );
        int q1 = 1 + ((1<0)*1);
        cout<<q1<<endl;
      }


      //No nan objects! Forced to zero
      cross_sec = std::isnan(cross_sec) ? 0 : cross_sec;
      prph_cross_sec = std::isnan(prph_cross_sec) ? 0 : prph_cross_sec;
      ll_cross_sec = std::isnan(ll_cross_sec) ? 0 : ll_cross_sec;
      prph_mc_cross_sec = std::isnan(prph_mc_cross_sec) ? 0 : prph_mc_cross_sec;
      ll_mc_cross_sec = std::isnan(ll_mc_cross_sec) ? 0 : ll_mc_cross_sec;
      cross_sec_copy = std::isnan(cross_sec_copy) ? 0 : cross_sec_copy;
      prph_cross_sec_copy = std::isnan(prph_cross_sec_copy) ? 0 : prph_cross_sec_copy;
          

      //statistical errors
      err1 = Nqq->GetBinError(i+1) / (bin_width * Lumi * C_acc);
        if (nodebugmode && name.Contains("xgamma")) cout<< i<<") " <<"Nqq = "<< Nqq->GetBinContent(i+1) <<" +/- "<< Nqq->GetBinError(i+1)<<endl;
      err11 = fitWithLL*ll_det->GetBinError(i+1) * ( 1 / C_ll_acc) / (bin_width * Lumi);
      if (C_ll_acc == 0) err11 = 0;
      err1 = TMath::Sqrt(err1 * err1 + err11 * err11);

      err1_copy = det_copy->GetBinError(i+1) / (bin_width * Lumi * C_acc);
      if (nodebugmode && name.Contains("xgamma")) cout<< i<<") " <<"det_copy = "<< det_copy->GetBinContent(i+1) <<" +/- "<< det_copy->GetBinError(i+1)<<endl;
      err11 = fitWithLL * ll_det_copy->GetBinError(i+1) * ( 1 / C_ll_acc) / (bin_width * Lumi);
      if (C_ll_acc == 0) err11 = 0;
      err1_copy = TMath::Sqrt(err1_copy * err1_copy + err11 * err11);

      //acceptance errors
      err2 = (n_qq ) * C_err / (bin_width * Lumi * C_acc * C_acc);
      err22 = fitWithLL*ll_events * C_ll_err / (bin_width * Lumi * C_ll_acc * C_ll_acc);
      if (C_ll_acc == 0) err22 = 0;
      err2 = TMath::Sqrt(err2*err2 + err22*err22); 

      err2_copy = (n_qq ) * C_err / (bin_width * Lumi * C_acc * C_acc);
      err22 = fitWithLL*ll_events_copy * C_ll_err / (bin_width * Lumi * C_ll_acc * C_ll_acc);
      if (C_ll_acc == 0) err22 = 0;
      err2_copy = TMath::Sqrt(err2_copy * err2_copy + err22*err22);        
      //luminosity errors are negleckted
      err3 = 0.;//0.026*cross_sec;    
      //      err3 *= err3;
      err = TMath::Sqrt(err1*err1 + err2*err2 + err3*err3);//full
      err_copy = TMath::Sqrt(err1_copy*err1_copy + err2_copy*err2_copy + err3_copy*err3_copy);//full

      //No nan objects! Forced to zero
      err1 = std::isnan(err1) ? 0 : err1;
      err1_copy = std::isnan(err1_copy) ? 0 : err1_copy;
      err2 = std::isnan(err2) ? 0 : err2;
      err2_copy = std::isnan(err2_copy) ? 0 : err2_copy;
      err = std::isnan(err) ? 0 : err;
      err_copy = std::isnan(err_copy) ? 0 : err_copy;

      //error propagation for LL cs
          Double_t err1_ll, err2_ll, err3_ll, err_ll;
          //statistic errors
          //if (C_ll_acc == 0) err1_ll = 0;
          err1_ll = TMath::Sqrt( pow(ll_det->GetBinError(i+1) * ( - 1 / C_ll_acc) / (bin_width * Lumi), 2));
          //acceptance errors
          err2_ll = TMath::Sqrt(pow(ll_events * C_ll_err / (bin_width * Lumi * C_acc * C_ll_acc), 2));  
          //luminosity errors are negleckted
          err3_ll = 0.;   
          err_ll = TMath::Sqrt(err1_ll*err1_ll + err2_ll*err2_ll + err3_ll*err3_ll);//full

          err1_ll = std::isnan(err1_ll) ? 0 : err1_ll;
          err2_ll = std::isnan(err2_ll) ? 0 : err2_ll;
          err_ll = std::isnan(err_ll) ? 0 : err_ll;

        if (nodebugmode && name.Contains("deta_e_ph") && i == 0) //s_var[i]=="deta_e_ph"
        {
          dout("bin_width: ",bin_width,"\n",
           "n_qq: ", n_qq,"\n",
           "ll_events: ", ll_events,"\n",
           "(n_qq - ll_events) / C_acc: ", (n_qq - ll_events) / C_acc ,"\n",
           "(C_ll_acc!=0)*ll_events/C_ll_acc: ", (C_ll_acc!=0)*ll_events/C_ll_acc );
        }



        //cross sections set-up
        res[0]->SetBinContent(i+1, cross_sec);
        res[0]->SetBinError(i+1, err);//full
        res[1]->SetBinContent(i+1, cross_sec);
        res[1]->SetBinError(i+1, err1);//statistic
        res[2]->SetBinContent(i+1, cross_sec);
        res[2]->SetBinError(i+1, err2);// acceptance
        res[3]->SetBinContent(i+1, cross_sec);
        res[3]->SetBinError(i+1, err3);//luminosity

        res_copy[0]->SetBinContent(i+1, cross_sec_copy);
        res_copy[0]->SetBinError(i+1, err_copy);//full
        res_copy[1]->SetBinContent(i+1, cross_sec_copy);
        res_copy[1]->SetBinError(i+1, err1_copy);//statistic
        res_copy[2]->SetBinContent(i+1, cross_sec_copy);
        res_copy[2]->SetBinError(i+1, err2_copy);// acceptance
        res_copy[3]->SetBinContent(i+1, cross_sec_copy);
        res_copy[3]->SetBinError(i+1, err3_copy);//luminosity

    
        res_copy[8]->SetBinContent(i+1, prph_cross_sec_copy);
        res_copy[8]->SetBinError(i+1, 0);
        res_copy[9]->SetBinContent(i+1, ll_cross_sec);
        res_copy[9]->SetBinError(i+1, err_ll);
        

        //ratios
        res[4]->SetBinContent(i+1, 0);
        res[4]->SetBinError(i+1, std::isnan(err/cross_sec) ? 0 : err/cross_sec);
        res[5]->SetBinContent(i+1, 0);
        res[5]->SetBinError(i+1, std::isnan(err1/cross_sec) ? 0 : err1/cross_sec);
        res[6]->SetBinContent(i+1, 0);
        res[6]->SetBinError(i+1, std::isnan(err2/cross_sec) ? 0 : err2/cross_sec);
        res[7]->SetBinContent(i+1, 0);
        res[7]->SetBinError(i+1, std::isnan(err3/cross_sec) ? 0 : err3/cross_sec);

        res_copy[4]->SetBinContent(i+1, 0);
        res_copy[4]->SetBinError(i+1, std::isnan(err_copy/cross_sec_copy) ? 0 : err_copy/cross_sec_copy);
        res_copy[5]->SetBinContent(i+1, 0);
        res_copy[5]->SetBinError(i+1, std::isnan(err1_copy/cross_sec_copy) ? 0 : err1_copy/cross_sec_copy);
        res_copy[6]->SetBinContent(i+1, 0);
        res_copy[6]->SetBinError(i+1, std::isnan(err2_copy/cross_sec_copy) ? 0 : err2_copy/cross_sec_copy);
        res_copy[7]->SetBinContent(i+1, 0);
        res_copy[7]->SetBinError(i+1, std::isnan(err3_copy/cross_sec_copy) ? 0 : err3_copy/cross_sec_copy);

        //      h_Acc->SetBinContent(i+1, 1./C_acc);
        //      h_Acc->SetBinError(i+1, C_err/(C_acc*C_acc));
        sigma_tot_ll += ll_cross_sec * bin_width;
        sigma_tot_qq += prph_cross_sec * bin_width;

        sigma_tot += cross_sec * bin_width;
        sigma_tot_err += err * err * bin_width * bin_width;

        sigma_tot_copy += cross_sec_copy * bin_width;
        sigma_tot_err_copy += TMath::Sqrt(err_copy * err_copy * bin_width * bin_width);

        sigma_tot_err += err * err * bin_width * bin_width;
         
        //if (!nodebugmode && name.Contains("et") && !name.Contains("eta") && !name.Contains("jet"))
        if (nodebugmode && name.Contains("eta") && !name.Contains("deta") && !name.Contains("e_ph") && !name.Contains("jet")) cout<< name << " cros sec in bin " << i << ": " << cross_sec 
                << " +- " << err << ", acc_Prompt = " << C_acc << ", nentries = " << prph << endl;
        //      if (nodebugmode) cout << "bin " << i+1 << " from " << low_edge << " to " << bott;
        selectedoutput << name << " cros sec in bin " << i << ": " << cross_sec 
                << " +- " << err << ", lumi = " << Lumi << ", acc_Prompt = " 
                << C_acc << ", binWidth = " << bin_width << ", nentries = " << prph << endl;
        //      if (nodebugmode) cout << "bin " << i+1 << " from " << low_edge << " to " << bottom_edge << " : sigma = " << cross_sec  << " +- " << err << endl;
        selectedoutput << "errors (stat. and fit, acc., lumi., total), %: " << err1 / cross_sec << ", " 
             << err2/cross_sec << ", " << err3 / cross_sec << ", " << err / cross_sec << endl;
        selectedoutput << "prph data: " << prph_cross_sec << ", prph mc: " << prph_mc_cross_sec << ", prph_had = " << prph_had <<  endl;
        selectedoutput << "ll data: " << ll_cross_sec  << " +- " << err_ll << ", acc_LL = " << C_ll_acc << endl;
        selectedoutput << "ll mc: " << ll_mc_cross_sec  << " +- " << ll_had->GetBinError(i+1)/(bin_width * (lumi_mc_bg[0] + lumi_mc_bg[1] + lumi_mc_bg[2])) << endl;
        selectedoutput << "errors for ll (stat. and fit, acc., lumi., total), %: " << err1_ll / ll_cross_sec << ", " 
             << err2_ll/ll_cross_sec << ", " << err3_ll / ll_cross_sec << ", " << err_ll / ll_cross_sec << endl;
        

        cout << name << " cros sec in bin " << i << ": " << cross_sec 
                << " +- " << err << ", lumi = " << Lumi << ", acc_Prompt = " 
                << C_acc << ", binWidth = " << bin_width << ", nentries = " << prph << endl;
        cout << "ll data: " << ll_cross_sec  << " +- " << err_ll << ", acc_LL = " << C_ll_acc << ", ll mc: " << ll_mc_cross_sec << endl;
        cout << "errors for ll (stat. and fit, acc., lumi., total), %: " << err1_ll / ll_cross_sec << ", " 
             << err2_ll/ll_cross_sec << ", " << err3_ll / ll_cross_sec << ", " << err_ll / ll_cross_sec << endl;

        if (name.Contains("deta_e_ph"))
        {
          dout(i, "res[0]->GetBinContent(i+1)", res[0]->GetBinContent(i+1));
          dout(i, "* res[0]->GetBinWidth(i+1)", res[0]->GetBinWidth(i+1));
          dout(i, "+= test_deleteme", res[0]->GetBinContent(i+1) * res[0]->GetBinWidth(i+1));
            test_deleteme += res[0]->GetBinContent(i+1) * res[0]->GetBinWidth(i+1);
        }
        fout << "h_1st[0]->SetBinContent(" << i+1 << ", " << cross_sec << ");" << endl;
        fout << "h_1st[0]->SetBinError(" << i+1 << ", " << err << ");" << endl;
    }
    fout << endl;

    dout("THE CHECK FOR 1.6!!!!!!!!!!!!!!!!!!!!!!!!!",\
     res[0]->Integral(0, res[0]->GetNbinsX(), "width"), "-", 
     res_copy[9]->Integral(0, res_copy[9]->GetNbinsX(), "width"), "/", 
     test_forest->Integral(0, test_forest->GetNbinsX(), "width"),"=",\
   (res[0]->Integral(0, res[0]->GetNbinsX(), "width") - res_copy[9]->Integral(0, res_copy[9]->GetNbinsX(), "width"))/ test_forest->Integral(0, test_forest->GetNbinsX(), "width"));
    if (name.Contains("deta_e_ph")) dout("test_deleteme", test_deleteme);
    if (nodebugmode) cout << "sigma_tot = " << sigma_tot << " +- " << sigma_tot_err << " pb" << endl;
    dout("sigma ll:", sigma_tot_ll, "sigma qq:", sigma_tot_qq);
    if (nodebugmode) cout << "sigma_tot_fig3 = " << sigma_tot_copy << " +- " << sigma_tot_err_copy << " pb" << endl;
    selectedoutput << "sigma_tot = " << sigma_tot << " +- " << sigma_tot_err << " pb" << endl;
    dout();
    //TCanvas* c_acc  = new TCanvas("c_cs_" + name, "CS", 800, 600);
  }
  
}

void Hist::CalculateCrossSec(TH1D *h_Data, TH1D *h_Lepto_det,
           TH1D *h_Lepto_had, TH1D *h_Lepto_hd, 
           Double_t Lumi, Int_t Linecolor, TH1D **h_Cross_Sec)
{
  Int_t nbins = 0;
  TH1D *h_Cross = (TH1D*)h_Data->Clone();
  TH1D *h_Acc = (TH1D*)h_Data->Clone(); //histo with acceptance. Here is to have right binning!
  nbins  = h_Data->GetNbinsX();
  //if (nodebugmode) cout << "in plot_cross_section: nbins = " << nbins << endl;
  for(Int_t i=0; i<nbins; i++)
    {
      Double_t data, lepto, lepto_had, lepto_hd;
      Double_t cross_sec;
      //Double_t cross_sec_error;
      data = h_Data->GetBinContent(i+1);
      lepto = h_Lepto_det->GetBinContent(i+1);
      lepto_had = h_Lepto_had->GetBinContent(i+1);
      lepto_hd = h_Lepto_hd->GetBinContent(i+1);
      Double_t C_acc = 0.;
      Double_t low_edge = 0, bottom_edge = 0;
      low_edge = h_Data->GetBinLowEdge(i+1);
      bottom_edge = h_Data->GetBinLowEdge(i+2);
      Double_t bin_width;
      bin_width = bottom_edge - low_edge;
      if(lepto != 0.)
  C_acc = lepto_had / lepto;
      else 
  {
    if (nodebugmode) cout << "lepto det bin content is 0! Can't calculate acceptance." <<endl;
    exit(1);
  }
      cross_sec = data * C_acc;
      cross_sec /= bin_width;
      cross_sec /= Lumi;
      //errors:
      Double_t C_err = 0;
      C_err = TMath::Sqrt(lepto_had/(lepto*lepto*lepto));
      C_err *= TMath::Sqrt(lepto + lepto_had - 2*lepto_hd);
      Double_t err1 =  0, err2 = 0, err = 0; //statistic, acceptance, full
      err1 = TMath::Sqrt(data) * C_acc / (bin_width * Lumi);
      err2 = data * C_err / (bin_width * Lumi);
      err = TMath::Sqrt(err1*err1 + err2*err2);
      //if (nodebugmode) cout << "bin " << i+2 << data << " " << lepto << " " << lepto_had << " " << lepto_hd << " " << bin_width << endl;
      //if (nodebugmode) cout << "bin " << i+1 <<" from " << low_edge << " to " << bottom_edge<< ": cross_sec = " << cross_sec << " C_acc = " << C_acc << " err = " << err << endl; 
      h_Cross->SetBinContent(i+1, cross_sec);
      h_Cross->SetBinError(i+1, err);
      h_Acc->SetBinContent(i+1, 1./C_acc);
      h_Acc->SetBinError(i+1, C_err/(C_acc*C_acc));
    }
  h_Cross->SetLineColor(Linecolor);
  h_Cross_Sec[0] = (TH1D*)h_Cross->Clone();
  h_Cross_Sec[1] = (TH1D*)h_Acc->Clone();
  //if (nodebugmode) cout << "in plot func. h_cross->GetBinContent(1) = " << h_Cross_Sec[0]->GetBinContent(1) << endl;
  //h_Cross->Draw("SAME");
}


