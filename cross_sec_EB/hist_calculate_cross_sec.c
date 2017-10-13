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

  Double_t integral_LLplusQQ, 
           integral_data_err, integral_LLplusQQ_err,
           integral_prph = 0.,
           integral_prph_err = 0.,
           scale_err3 = 0.,
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
  //  ll_det_copy->Scale(total_luminosity_data / (lumi_mc_bg[0]+lumi_mc_bg[1]+lumi_mc_bg[2]));

  // QQ
  det->Scale(total_luminosity_data / lumi_mc_prph);
  det_copy->Scale(total_luminosity_data / lumi_mc_prph);
  had->Scale(total_luminosity_data / lumi_mc_prph);
  hd->Scale(total_luminosity_data / lumi_mc_prph);
  
  TH1D* Nqq = (TH1D*)det->Clone(); //h_det_rad_sum LLdet
  Nqq->SetName("N_qq");
  
  // Scale Nqq to (data - a * LL)
  if ( name.Contains("Q2") ) debug << "hist_calculate_cs:" << "\n\tdata->GetBinContent\tll_det->GetBinContent:" << endl;
  for(Int_t i = 0; i < Nqq->GetNbinsX(); i++) 
  {
      Double_t integral_data_qqFromFit = data->GetBinContent(i + 1) - fitWithLL * ll_det->GetBinContent(i + 1),
               integral_data_qqFromFit_err = TMath::Sqrt(pow(data->GetBinError(i + 1), 2) + fitWithLL * pow(ll_det->GetBinError(i + 1), 2));

      Double_t err = Nqq->GetBinError(i + 1),
               cont = Nqq->GetBinContent(i + 1);//! лишняя integral_Nqq
      
      Double_t scale_data = integral_data_qqFromFit / cont, // data / qq 
               scale_err1 = integral_data_qqFromFit_err / cont, // data_err / QQ
               scale_err2 = integral_data_qqFromFit * err / pow(cont, 2), // data * QQ_err / QQ^2
               scale_data_err = TMath::Sqrt(pow(scale_err1, 2) + pow(scale_err2, 2));

      Double_t new_err = TMath::Sqrt( pow(cont, 2) * pow(scale_data_err, 2) + pow(err, 2) * pow(scale_data, 2)),
               new_cont = scale_data * cont;
      new_cont = std::isnan(new_cont) ? 0 : new_cont;
      new_err  = std::isnan(new_err) ? 0 : new_err;

      Nqq->SetBinContent(i + 1, new_cont);
      Nqq->SetBinError(i + 1, err);

      if (nodebugmode)
      {
        cout << "bin " << i << ", data = " << integral_data_qqFromFit << " +- " << integral_data_qqFromFit_err 
             << ", ll+qq = " << cont << " +- " << err << endl;
        cout << "scaling: old content: " << i << " " << cont << " +- " << err << endl;
        cout << "scaling: new content: " << i << " " << new_cont << " +- " << new_err << endl;
      } 
  }

  if (nodebugmode) cout << "--> scaling by fit param" << endl;
  for(Int_t i = 0; i < Nqq->GetNbinsX(); i++) 
  {
      Double_t cont = Nqq->GetBinContent(i + 1),
               err  = Nqq->GetBinError(i + 1);
       
      Double_t new_err = TMath::Sqrt(pow(cont, 2) * pow(param_err[i], 2) + pow(err, 2) * pow(param[i], 2)),
               new_cont = cont * param[i];
      new_cont = std::isnan(new_cont) ? 0 : new_cont;
      new_err  = std::isnan(new_err) ? 0 : new_err;

      Nqq->SetBinContent(i + 1, new_cont);
      Nqq->SetBinError(i + 1, new_err);
      
      // Scaling the copy of QQ on det lev  by the tested parameter found by Oleg
      cont = det_copy->GetBinContent(i + 1);
      err  = det_copy->GetBinError(i + 1);
      new_err = TMath::Sqrt(pow(err, 2) * pow(fig3_scale, 2));
      new_cont = cont * fig3_scale;

      det_copy->SetBinContent(i + 1, new_cont);
      det_copy->SetBinError(i + 1, new_err);
      
      if (nodebugmode)
      {
        cout << "scaling: old content: " << i << " " << cont << " +- " << err << ", param = " << param[i] << " +- " << param_err[i] << endl;
        cout << "scaling: old content: " << i << " " << new_cont << " +- " << new_err << endl;
        if (name.Contains("deta_e_ph")) cout<< "After" << i<<") " <<" Nqq = "<< Nqq->GetBinContent(i + 1) <<" +/- "<< Nqq->GetBinError(i + 1)<<endl;
      }
  }

  // Filling initial histograms
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
  
  nbins  = res[0]->GetNbinsX();
  TH1D * test_forest = (TH1D*)det->Clone();
  Double_t test_deleteme = 0;
  for(Int_t i = 0; i < nbins; i++)
  {
    Double_t prph          = det->GetBinContent(i + 1), // QQ 
             prph_had      = had->GetBinContent(i + 1), // QQ
             prph_hd       = hd->GetBinContent(i + 1), // QQ
             ll_events     = ll_det->GetBinContent(i + 1), // LL
             ll_had_events = ll_had->GetBinContent(i + 1), // LL        
             n_qq          = Nqq->GetBinContent(i + 1), // QQLL
             bin_width     = det->GetBinWidth(i + 1),
             err1 = 0., err2 = 0., err3 = 0., err11 = 0., err22 = 0., err = 0., // statistic, acceptance, luminosity, full
             C_acc         = acc->GetBinContent(i + 1),
             C_err         = acc->GetBinError(i + 1),
             C_ll_acc      = ll_acc->GetBinContent(i + 1),
             C_ll_err      = ll_acc->GetBinError(i + 1),
             Lumi_bg       = lumi_mc_bg[0] + lumi_mc_bg[1] + lumi_mc_bg[2],
             Lumi_qq       = lumi_mc_prph;

    Double_t ll_events_copy     = ll_det_copy->GetBinContent(i + 1), // LL      
             n_qq_copy          = det_copy->GetBinContent(i + 1), // QQLL
             err1_copy = 0., err2_copy = 0., err3_copy = 0., err_copy = 0.; //statistic, acceptance, luminosity, full

    Double_t cross_sec         = ( (n_qq ) / C_acc + (C_ll_acc!=0) * fitWithLL * ll_events/C_ll_acc ) / (bin_width * Lumi),
             prph_cross_sec    =   (n_qq )                                                    / (C_acc * bin_width * Lumi),
             ll_cross_sec      =                                      ll_events            / (C_ll_acc * bin_width * Lumi),
             prph_mc_cross_sec =    prph_had                                                          / (bin_width * Lumi_qq),
             ll_mc_cross_sec   =                                      ll_had_events                   / (bin_width * Lumi_bg);
    
    Double_t cross_sec_copy      = ( (n_qq_copy ) / C_acc + (C_ll_acc!=0) * fitWithLL * ll_events_copy / C_ll_acc ) / (bin_width * Lumi),
             prph_cross_sec_copy =   (n_qq_copy )                                                           / (C_acc * bin_width * Lumi);

    dout("IAN CS for LL part in", name, "bin", i, ":", ll_cross_sec, ";events: ", ll_events, "; C_ll_acc:", C_ll_acc, "check:", C_ll_acc,"?=", ll_events/ll_had_events,  "; bin_width:", bin_width, "; Lumi:", Lumi,"?=", (lumi_mc_bg[0] + lumi_mc_bg[1] + lumi_mc_bg[2]), "; had:", ll_mc_cross_sec, " +- " , ll_had->GetBinError(i + 1) / (bin_width * Lumi_bg));

    test_forest->SetBinContent( i + 1, prph / (C_acc*bin_width * Lumi));
    test_forest->SetBinError( i + 1, TMath::Sqrt(pow(det->GetBinError(i + 1) / (bin_width * Lumi * C_acc), 2) + pow(prph * C_err / (bin_width * Lumi * C_acc * C_acc), 2)) );
    
    if (name.Contains("deta") && !name.Contains("e_ph") && (C_ll_acc==0)) 
    {
      ll_det_copy->SetBinContent(i + 1, 0);
      ll_det->SetBinContent(i + 1, 0);
      ll_det_copy->SetBinError(i + 1, 0);
      ll_det->SetBinError(i + 1, 0);

      cross_sec         = ( (n_qq ) / C_acc ) / (bin_width * Lumi);
      ll_cross_sec      = 0;
      cross_sec_copy    = ( (n_qq_copy ) / C_acc ) / (bin_width * Lumi);
    }

    if (nodebugmode && name.Contains("deta"))
    {
      if (!name.Contains("e_ph"))
      {
        dout(name, i, "cross_sec", cross_sec, "cross_sec_copy", cross_sec_copy);
        dout("     qq:", (n_qq ) / C_acc ,"ll:", (C_ll_acc!=0)*fitWithLL*ll_events/C_ll_acc );
        dout("fig3 qq:", (n_qq_copy ) / C_acc ,"ll:", (C_ll_acc!=0)*fitWithLL*ll_events_copy/C_ll_acc );
      }
      if (!name.Contains("deta_e_ph") && i == 0) 
      {
        dout(C_acc, C_ll_acc );
        int q1 = 1 + ((1<0)*1);
        cout<<q1<<endl;
      }
    }

    //No nan objects! Forced to zero
      cross_sec = std::isnan(cross_sec) ? 0 : cross_sec;
      prph_cross_sec = std::isnan(prph_cross_sec) ? 0 : prph_cross_sec;
      ll_cross_sec = std::isnan(ll_cross_sec) ? 0 : ll_cross_sec;
      prph_mc_cross_sec = std::isnan(prph_mc_cross_sec) ? 0 : prph_mc_cross_sec;
      ll_mc_cross_sec = std::isnan(ll_mc_cross_sec) ? 0 : ll_mc_cross_sec;
      cross_sec_copy = std::isnan(cross_sec_copy) ? 0 : cross_sec_copy;
      prph_cross_sec_copy = std::isnan(prph_cross_sec_copy) ? 0 : prph_cross_sec_copy;

    // Errors assighnment
      //statistical errors
      err1 = Nqq->GetBinError(i + 1) / (bin_width * Lumi * C_acc);
      if (C_ll_acc == 0) err11 = 0;
      else err11 = fitWithLL * ll_det->GetBinError(i + 1) * ( 1 / C_ll_acc) / (bin_width * Lumi);
      err1 = TMath::Sqrt(pow(err1, 2) + pow(err11, 2));

      err1_copy = det_copy->GetBinError(i + 1) / (bin_width * Lumi * C_acc);
      if (C_ll_acc == 0) err11 = 0;
      else err11 = fitWithLL * ll_det_copy->GetBinError(i + 1) * ( 1 / C_ll_acc) / (bin_width * Lumi);
      err1_copy = TMath::Sqrt(pow(err1_copy, 2) + pow(err11, 2));

      //acceptance errors
      err2 = (n_qq ) * C_err / (bin_width * Lumi * C_acc * C_acc);
      if (C_ll_acc == 0) err22 = 0;
      else err22 = fitWithLL * ll_events * C_ll_err / (bin_width * Lumi * pow(C_ll_acc, 2));
      err2 = TMath::Sqrt(pow(err2, 2) + pow(err22, 2)); 

      err2_copy = (n_qq ) * C_err / (bin_width * Lumi * C_acc * C_acc);
      if (C_ll_acc == 0) err22 = 0;
      else err22 = fitWithLL * ll_events_copy * C_ll_err / (bin_width * Lumi * pow(C_ll_acc, 2));
      err2_copy = TMath::Sqrt(pow(err2_copy, 2) + pow(err22, 2));        

      err3 = 0.;//luminosity errors are negleckted
      
      err = TMath::Sqrt(pow(err1, 2) + pow(err2, 2) + pow(err3, 2));//full
      err_copy = TMath::Sqrt(pow(err1_copy, 2) + pow(err2_copy, 2) + pow(err3_copy, 2));//full

      //No nan objects! Forced to zero
        err1 = std::isnan(err1) ? 0 : err1;
        err1_copy = std::isnan(err1_copy) ? 0 : err1_copy;
        err2 = std::isnan(err2) ? 0 : err2;
        err2_copy = std::isnan(err2_copy) ? 0 : err2_copy;
        err = std::isnan(err) ? 0 : err;
        err_copy = std::isnan(err_copy) ? 0 : err_copy;

      // Error propagation for LL cs
          Double_t err1_ll, err2_ll, err3_ll, err_ll;
          //statistic errors
          err1_ll = TMath::Sqrt( pow(ll_det->GetBinError(i + 1) * ( - 1 / C_ll_acc) / (bin_width * Lumi), 2));
          //acceptance errors
          err2_ll = TMath::Sqrt(pow(ll_events * C_ll_err / (bin_width * Lumi * C_ll_acc * C_ll_acc), 2));  
          //luminosity errors are negleckted
          err3_ll = 0.;   
          err_ll = TMath::Sqrt(pow(err1_ll, 2) + pow(err2_ll, 2) + pow(err3_ll, 2));//full

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

    // Filling histograms with cs
      //cross sections set-up
      res[0]->SetBinContent(i + 1, cross_sec);
      res[0]->SetBinError(i + 1, err);//full
      res[1]->SetBinContent(i + 1, cross_sec);
      res[1]->SetBinError(i + 1, err1);//statistic
      res[2]->SetBinContent(i + 1, cross_sec);
      res[2]->SetBinError(i + 1, err2);// acceptance
      res[3]->SetBinContent(i + 1, cross_sec);
      res[3]->SetBinError(i + 1, err3);//luminosity

      res_copy[0]->SetBinContent(i + 1, cross_sec_copy);
      res_copy[0]->SetBinError(i + 1, err_copy);//full
      res_copy[1]->SetBinContent(i + 1, cross_sec_copy);
      res_copy[1]->SetBinError(i + 1, err1_copy);//statistic
      res_copy[2]->SetBinContent(i + 1, cross_sec_copy);
      res_copy[2]->SetBinError(i + 1, err2_copy);// acceptance
      res_copy[3]->SetBinContent(i + 1, cross_sec_copy);
      res_copy[3]->SetBinError(i + 1, err3_copy);//luminosity

      res_copy[8]->SetBinContent(i + 1, prph_cross_sec_copy);
      res_copy[8]->SetBinError(i + 1, 0);
      res_copy[9]->SetBinContent(i + 1, ll_cross_sec);
      res_copy[9]->SetBinError(i + 1, err_ll);      

      //ratios
      res[4]->SetBinContent(i + 1, 0);
      res[4]->SetBinError(i + 1, std::isnan(err/cross_sec) ? 0 : err/cross_sec);
      res[5]->SetBinContent(i + 1, 0);
      res[5]->SetBinError(i + 1, std::isnan(err1/cross_sec) ? 0 : err1/cross_sec);
      res[6]->SetBinContent(i + 1, 0);
      res[6]->SetBinError(i + 1, std::isnan(err2/cross_sec) ? 0 : err2/cross_sec);
      res[7]->SetBinContent(i + 1, 0);
      res[7]->SetBinError(i + 1, std::isnan(err3/cross_sec) ? 0 : err3/cross_sec);

      res_copy[4]->SetBinContent(i + 1, 0);
      res_copy[4]->SetBinError(i + 1, std::isnan(err_copy/cross_sec_copy) ? 0 : err_copy/cross_sec_copy);
      res_copy[5]->SetBinContent(i + 1, 0);
      res_copy[5]->SetBinError(i + 1, std::isnan(err1_copy/cross_sec_copy) ? 0 : err1_copy/cross_sec_copy);
      res_copy[6]->SetBinContent(i + 1, 0);
      res_copy[6]->SetBinError(i + 1, std::isnan(err2_copy/cross_sec_copy) ? 0 : err2_copy/cross_sec_copy);
      res_copy[7]->SetBinContent(i + 1, 0);
      res_copy[7]->SetBinError(i + 1, std::isnan(err3_copy/cross_sec_copy) ? 0 : err3_copy/cross_sec_copy);

    sigma_tot_ll += ll_cross_sec * bin_width;
    sigma_tot_qq += prph_cross_sec * bin_width;

    sigma_tot += cross_sec * bin_width;
    sigma_tot_err += err * err * bin_width * bin_width;

    sigma_tot_copy += cross_sec_copy * bin_width;
    sigma_tot_err_copy += TMath::Sqrt(err_copy * err_copy * bin_width * bin_width);

    sigma_tot_err += err * err * bin_width * bin_width;
     
    // Store the resulting CS and errors for the further syst. calculation using python script
    {
      selectedoutput << name << " cros sec in bin " << i << ": " << cross_sec 
              << " +- " << err << ", lumi = " << Lumi << ", acc_Prompt = " 
              << C_acc << ", binWidth = " << bin_width << ", nentries = " << prph << endl;
      selectedoutput << "errors (stat. and fit, acc., lumi., total), %: " << err1 / cross_sec << ", " 
              << err2/cross_sec << ", " << err3 / cross_sec << ", " << err / cross_sec << endl;
      selectedoutput << "prph data: " << prph_cross_sec << ", prph mc: " << prph_mc_cross_sec << ", prph_had = " << prph_had <<  endl;
      selectedoutput << "ll data: " << ll_cross_sec  << " +- " << err_ll << ", acc_LL = " << C_ll_acc << endl;
      selectedoutput << "ll mc: " << ll_mc_cross_sec  << " +- " << ll_had->GetBinError(i + 1) / (bin_width * (Lumi_bg)) << endl;
      selectedoutput << "errors for ll (stat. and fit, acc., lumi., total), %: " << err1_ll / ll_cross_sec << ", " 
           << err2_ll/ll_cross_sec << ", " << err3_ll / ll_cross_sec << ", " << err_ll / ll_cross_sec << endl;  

      dout(name,"cros sec in bin ", i ,":", cross_sec, "+-", err, ",lumi =", Lumi, ", acc_Prompt =", C_acc, ", binWidth =", bin_width, ", nentries =", prph);
      dout("ll data:", ll_cross_sec , "+-", err_ll, ", acc_LL =", C_ll_acc, ", ll mc:", ll_mc_cross_sec);
      dout("errors for ll (stat. and fit, acc., lumi., total), :", err1_ll / ll_cross_sec, ",", err2_ll/ll_cross_sec, ",", err3_ll / ll_cross_sec, ",", err_ll / ll_cross_sec);
      if (name.Contains("deta_e_ph"))
      {
        dout(i, "res[0]->GetBinContent(i + 1)", res[0]->GetBinContent(i + 1));
        dout(i, "* res[0]->GetBinWidth(i + 1)", res[0]->GetBinWidth(i + 1));
        dout(i, "+= test_deleteme", res[0]->GetBinContent(i + 1) * res[0]->GetBinWidth(i + 1));
        test_deleteme += res[0]->GetBinContent(i + 1) * res[0]->GetBinWidth(i + 1);
      }
      fout << "h_1st[0]->SetBinContent(" << i + 1 << ", " << cross_sec << ");" << endl;
      fout << "h_1st[0]->SetBinError(" << i + 1 << ", " << err << ");" << endl;
    }
  }
  selectedoutput << "sigma_tot = " << sigma_tot << " +- " << sigma_tot_err << " pb" << endl;
  fout << endl;
  
  if (nodebugmode)
  {
    dout("THE CHECK FOR 1.6!!!!!!!!!!!!!!!!!!!!!!!!!",\
     res[0]->Integral(0, res[0]->GetNbinsX(), "width"), "-",
     res_copy[9]->Integral(0, res_copy[9]->GetNbinsX(), "width"), "/",
     test_forest->Integral(0, test_forest->GetNbinsX(), "width"),"=",
     (res[0]->Integral(0, res[0]->GetNbinsX(), "width") - res_copy[9]->Integral(0, res_copy[9]->GetNbinsX(), "width"))/ test_forest->Integral(0, test_forest->GetNbinsX(), "width"));

    if (name.Contains("deta_e_ph"))dout("test_deleteme", test_deleteme);
    cout << "sigma_tot = " << sigma_tot << " +- " << sigma_tot_err << " pb" << endl; 
    dout("sigma ll:", sigma_tot_ll, "sigma qq:", sigma_tot_qq);
    cout << "sigma_tot_fig3 = " << sigma_tot_copy << " +- " << sigma_tot_err_copy << " pb" << endl;
    dout();
  }
}