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
void Hist::CalculateCrossSecQQfit0(TH1D* data, 
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

  Double_t integral_data, integral_LLplusQQ, 
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
  
 
  TH1D* LLplusQQ = (TH1D*)ll_det->Clone(); // h_det_rad_sum LLdet
        LLplusQQ->SetName("ll_plus_qq");
  det->Scale(total_luminosity_data / lumi_mc_prph); // h_det_prph_sum QQ
  had->Scale(total_luminosity_data / lumi_mc_prph); // h_had_prph_sum QQ
  hd->Scale(total_luminosity_data / lumi_mc_prph); // h_hd_prph_sum QQ

  LLplusQQ->Add(det); // LLdet + QQ'det
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
      Double_t integral_data = data->GetBinContent(i + 1),
               integral_data_err = data->GetBinError(i + 1);
               integral_LLplusQQ = LLplusQQ->GetBinContent(i + 1);
               integral_LLplusQQ_err = LLplusQQ->GetBinError(i + 1);
      
      Double_t scale_data = integral_data / integral_LLplusQQ,// data / (QQ'det+LLdet)  
               scale_err1 = integral_data_err / integral_LLplusQQ,// data_err/QQLL
               scale_err2 = integral_data * integral_LLplusQQ_err / (integral_LLplusQQ * integral_LLplusQQ),// data*QQLL_err/LLQQ^2
               scale_data_err = TMath::Sqrt(scale_err1*scale_err1 + scale_err2*scale_err2);
      
      Double_t err = LLplusQQ->GetBinError(i + 1),
               cont = LLplusQQ->GetBinContent(i + 1);//! лишняя integral_LLplusQQ
      Double_t new_err = TMath::Sqrt(cont * cont * scale_data_err * scale_data_err + err * err * scale_data * scale_data),
               new_cont = scale_data * cont;

      LLplusQQ->SetBinContent(i + 1, new_cont);
      LLplusQQ->SetBinError(i + 1, err);

      if (nodebugmode) 
      {
        cout << "bin " << i << ", data = " << integral_data << " +- " << integral_data_err << ", ll+qq = " << integral_LLplusQQ << " +- " << integral_LLplusQQ_err << endl;
        cout << "scale_data_ll (in bin "<< i<< ") = " << data->GetBinContent(i + 1) << " - " << ll_det->GetBinContent(i + 1) << " = " << scale_data << " +- " << scale_data_err << endl;
        cout << "--> scaling by N_{data-LL}" << endl;
        cout << "scaling: old content: " << i << " " << cont << " +- " << err << endl;
        cout << "scaling: new content: " << i << " " << new_cont << " +- " << new_err << endl;
        if (name.Contains("xgamma")) cout<< i<<") " <<"LLplusQQ = "<<LLplusQQ->GetBinContent(i + 1) <<" +/- "<< LLplusQQ->GetBinError(i + 1)<<endl;
      }
  }

  //scale LLplusQQ by parameter
  // могу переписать через уже существующую функцию класса
  if (nodebugmode) cout << "--> scaling by fit param" << endl;
  for(Int_t i = 0; i < LLplusQQ->GetNbinsX(); i++) 
  {
      
     
      Double_t cont = LLplusQQ->GetBinContent(i + 1);
      Double_t err = LLplusQQ->GetBinError(i + 1);
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
      LLplusQQ->SetBinContent(i + 1, new_cont);
      LLplusQQ->SetBinError(i + 1, new_err);
      if (nodebugmode && name.Contains("deta_e_ph")) cout<< "After" << i<<") " <<"LLplusQQ = "<<LLplusQQ->GetBinContent(i + 1) <<" +/- "<< LLplusQQ->GetBinError(i + 1)<<endl;
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
      Double_t prph          = det->GetBinContent(i + 1),//QQ // + ll_det->GetBinContent(i + 1);
               prph_had      = had->GetBinContent(i + 1),//QQ
               prph_hd       = hd->GetBinContent(i + 1),//QQ
               ll_events     = ll_det->GetBinContent(i + 1),//LL
               ll_had_events = ll_had->GetBinContent(i + 1),//LL        
               ll_plus_qq    = LLplusQQ->GetBinContent(i + 1),//QQLL
               bin_width     = det->GetBinWidth(i + 1),
               err1 = 0., err2 = 0., err3 = 0., err11 = 0., err22 = 0., err = 0.,  //statistic, acceptance, luminosity, full
               C_acc         = acc->GetBinContent(i + 1),
               C_err         = acc->GetBinError(i + 1),
               C_ll_acc      = ll_acc->GetBinContent(i + 1),
               C_ll_err      = ll_acc->GetBinError(i + 1);
      
      /*      
        if(prph != 0.)
        //  C_acc = prph_had / prph;
        //      else 
        //  {
        //    if (nodebugmode) cout << "prph det bin content is 0! Can't calculate acceptance." <<endl;
        //    exit(1);
        //  }
        //      if (nodebugmode) cout << "C_acc = " << C_acc << ", C_acc_old = " << acc->GetBinContent(i + 1) << endl;
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
            err1 = LLplusQQ->GetBinError(i + 1) / (bin_width * Lumi * C_acc);
            err11 = ll_det->GetBinError(i + 1) * (1 / C_acc + 1 / C_ll_acc) / (bin_width * Lumi);
            err1 = TMath::Sqrt(err1 * err1 + err11 * err11);
          */
        err1 = LLplusQQ->GetBinError(i + 1) / (bin_width * Lumi * C_acc);
          if (nodebugmode &&name.Contains("xgamma")) cout<< i<<") " <<"LLplusQQ = "<<LLplusQQ->GetBinContent(i + 1) <<" +/- "<< LLplusQQ->GetBinError(i + 1)<<endl;
        err11 = ll_det->GetBinError(i + 1) * (1 / C_acc - 1 / C_ll_acc) / (bin_width * Lumi);
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
        Double_t err1_ll = TMath::Sqrt( pow(ll_det->GetBinError(i + 1) * ( - 1 / C_ll_acc) / (bin_width * Lumi), 2));
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
      res[0]->SetBinContent(i + 1, cross_sec);
      res[0]->SetBinError(i + 1, err);//full
      res[1]->SetBinContent(i + 1, cross_sec);
      res[1]->SetBinError(i + 1, err1);//statistic
      res[2]->SetBinContent(i + 1, cross_sec);
      res[2]->SetBinError(i + 1, err2);// acceptance
      res[3]->SetBinContent(i + 1, cross_sec);
      res[3]->SetBinError(i + 1, err3);//luminosity
      
      //ratios
      res[4]->SetBinContent(i + 1, 0);
      res[4]->SetBinError(i + 1, err/cross_sec);
      res[5]->SetBinContent(i + 1, 0);
      res[5]->SetBinError(i + 1, err1/cross_sec);
      res[6]->SetBinContent(i + 1, 0);
      res[6]->SetBinError(i + 1, err2/cross_sec);
      res[7]->SetBinContent(i + 1, 0);
      res[7]->SetBinError(i + 1, err3/cross_sec);
      //      h_Acc->SetBinContent(i + 1, 1./C_acc);
      //      h_Acc->SetBinError(i + 1, C_err/(C_acc*C_acc));
      
      sigma_tot += cross_sec * bin_width;
      sigma_tot_err += err * err * bin_width * bin_width;
       
      //if (!nodebugmode && name.Contains("et") && !name.Contains("eta") && !name.Contains("jet"))
      if (nodebugmode && name.Contains("eta") && !name.Contains("deta") && !name.Contains("e_ph") && !name.Contains("jet")) cout<< name << " cros sec in bin " << i << ": " << cross_sec 
              << " +- " << err << ", acc_Prompt = " << C_acc << ", nentries = " << prph << endl;
      //      if (nodebugmode) cout << "bin " << i + 1 << " from " << low_edge << " to " << bott;
      selectedoutput << name << " cros sec in bin " << i << ": " << cross_sec 
              << " +- " << err << ", lumi = " << Lumi << ", acc_Prompt = " 
              << C_acc << ", binWidth = " << bin_width << ", nentries = " << prph << endl;
      //      if (nodebugmode) cout << "bin " << i + 1 << " from " << low_edge << " to " << bottom_edge << " : sigma = " << cross_sec  << " +- " << err << endl;
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
      //      if (nodebugmode) cout << "bin " << i + 1 << " from " << low_edge << " to " << bottom_edge << " : sigma = " << cross_sec  << " +- " << err << endl;
      if (nodebugmode) cout << "errors (stat. and fit, acc., lumi., total), %: " << err1 / cross_sec << ", " 
           << err2/cross_sec << ", " << err3 / cross_sec << ", " << err / cross_sec << endl;
      if (nodebugmode) cout << "prph data: " << prph_cross_sec << ", prph mc: " << prph_mc_cross_sec << ", prph_had = " << prph_had <<  endl;
      if (nodebugmode) cout << "ll data: " << ll_cross_sec << ", ll mc: " << ll_mc_cross_sec << endl;
      fout << "h_1st[0]->SetBinContent(" << i + 1 << ", " << cross_sec << ");" << endl;
      fout << "h_1st[0]->SetBinError(" << i + 1 << ", " << err << ");" << endl;
  }//for i over bins
  fout << endl;
  if (nodebugmode) cout << "sigma_tot = " << sigma_tot << " +- " << TMath::Sqrt(sigma_tot_err) << " pb" << endl;
  selectedoutput << "sigma_tot = " << sigma_tot << " +- " << TMath::Sqrt(sigma_tot_err) << " pb" << endl;

  //TCanvas* c_acc  = new TCanvas("c_cs_" + name, "CS", 800, 600);

}