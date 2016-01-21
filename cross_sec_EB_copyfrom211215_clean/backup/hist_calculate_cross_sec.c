void Hist::CalculateCrossSec(TH1D* data, TH1D* ll_det, TH1D *det, TH1D* had, TH1D* hd, TH1D *acc, Double_t Lumi, TH1D **res, TString name, Double_t* param, Double_t* param_err/*, Double_t integral_data, Double_t integral_ll, Double_t integral_data_err, Double_t integral_ll_err*/) 
{
  cout << "in CalculateCrossSec: calculate " << name << ", lumi = " << Lumi << " pb^{-1}" << endl;
  //  cout << "input parameters:" << endl;
  //  cout << "integral_data = " << integral_data << " +- " << integral_data_err << endl;
  //  cout << "integral_ll = " << integral_ll << " +- " << integral_ll_err << endl;
  Double_t integral_data, integral_ll, integral_data_err, integral_ll_err;
  Double_t integral_prph = 0.;// = det->Integral();
  Double_t integral_prph_err = 0.;
  //  for(Int_t i=0; i<det->GetNbinsX(); i++) {
  //    Double_t err = det->GetBinError(i+1);
  //    integral_prph_err += err*err;
  //  }
  //  integral_prph_err = TMath::Sqrt(integral_prph_err);
  //  cout << "integral_prph = " << integral_prph << " +- " << integral_prph_err << endl;
  Double_t scale_data_ll = 1;//(integral_data - integral_ll)/integral_prph;
  Double_t scale_err1 = 0.;//integral_data_err/integral_prph;
  Double_t scale_err2 = 0.;//integral_ll_err/integral_prph;
  Double_t scale_err3 = 0.;//(integral_data - integral_ll)*integral_prph_err/(integral_prph*integral_prph);
  Double_t scale_data_ll_err = 0.;//scale_err1*scale_err1 + scale_err2*scale_err2 + scale_err3*scale_err3;
  //
  // scale prph by (data - LL)
  //
  for(Int_t i=0; i<det->GetNbinsX(); i++) {
    integral_data = data->GetBinContent(i+1);
    integral_data_err = data->GetBinError(i+1);
    integral_ll = ll_det->GetBinContent(i+1);
    integral_ll_err = ll_det->GetBinError(i+1);
    integral_prph = det->GetBinContent(i+1);
    integral_prph_err = det->GetBinError(i+1);
    cout << "bin " << i << ", data = " << integral_data << " +- " << integral_data_err 
	 << ", ll = " << integral_ll << " +- " << integral_ll_err  
	 << ", prph = " << integral_prph << " +- " << integral_prph_err << endl;
    scale_data_ll = (integral_data - integral_ll)/integral_prph;
    scale_err1 = integral_data_err/integral_prph;
    scale_err2 = integral_ll_err/integral_prph;
    scale_err3 = scale_err1*scale_err1 + scale_err2*scale_err2 + scale_err3*scale_err3;
    scale_data_ll_err = scale_err1*scale_err1 + scale_err2*scale_err2 + scale_err3*scale_err3;
    cout << "scale_data_ll (in bin "<< i<< ") = " << data->GetBinContent(i+1) << " - " 
      << ll_det->GetBinContent(i+1) << " = " << scale_data_ll << " +- " << scale_data_ll_err << endl;
    cout << "--> scaling by N_{data-LL}" << endl;
    Double_t err = det->GetBinError(i+1);
    Double_t cont = det->GetBinContent(i+1);
    cout << "scaling: old content: " << i << " " << cont << " +- " << err << endl;
    Double_t new_err = cont*cont*scale_data_ll_err*scale_data_ll_err + err*err*scale_data_ll*scale_data_ll;
    new_err = TMath::Sqrt(new_err);
    Double_t new_cont = scale_data_ll * cont;
    cout << "scaling: new content: " << i << " " << new_cont << " +- " << new_err << endl;
    det->SetBinContent(i+1, new_cont);
    det->SetBinError(i+1, new_err);
  }
  for(Int_t i=0; i<had->GetNbinsX(); i++) {
    integral_data = data->GetBinContent(i+1);
    integral_data_err = data->GetBinError(i+1);
    integral_ll = ll_det->GetBinContent(i+1);
    integral_ll_err = ll_det->GetBinError(i+1);
    integral_prph = det->GetBinContent(i+1);
    integral_prph_err = det->GetBinError(i+1);
    cout << "bin " << i << ", data = " << integral_data << " +- " << integral_data_err 
	 << ", ll = " << integral_ll << " +- " << integral_ll_err  
	 << ", prph = " << integral_prph << " +- " << integral_prph_err << endl;
    scale_data_ll = (integral_data - integral_ll)/integral_prph;
    scale_err1 = integral_data_err/integral_prph;
    scale_err2 = integral_ll_err/integral_prph;
    scale_err3 = scale_err1*scale_err1 + scale_err2*scale_err2 + scale_err3*scale_err3;
    scale_data_ll_err = scale_err1*scale_err1 + scale_err2*scale_err2 + scale_err3*scale_err3;
    cout << "scale_data_ll (in bin "<< i<< ") = " << data->GetBinContent(i+1) << " - " 
      << ll_det->GetBinContent(i+1) << " = " << scale_data_ll << " +- " << scale_data_ll_err << endl;
    cout << "--> scaling by N_{data-LL}" << endl;
    Double_t err = had->GetBinError(i+1);
    Double_t cont = had->GetBinContent(i+1);
    Double_t new_err = cont*cont*scale_data_ll_err*scale_data_ll_err + err*err*scale_data_ll*scale_data_ll;
    new_err = TMath::Sqrt(new_err);
    Double_t new_cont = cont*scale_data_ll;
    had->SetBinContent(i+1, new_cont);
    had->SetBinError(i+1, new_err);
  }
  for(Int_t i=0; i<hd->GetNbinsX(); i++) {
    integral_data = data->GetBinContent(i+1);
    integral_data_err = data->GetBinError(i+1);
    integral_ll = ll_det->GetBinContent(i+1);
    integral_ll_err = ll_det->GetBinError(i+1);
    integral_prph = det->GetBinContent(i+1);
    integral_prph_err = det->GetBinError(i+1);
    cout << "bin " << i << ", data = " << integral_data << " +- " << integral_data_err 
	 << ", ll = " << integral_ll << " +- " << integral_ll_err  
	 << ", prph = " << integral_prph << " +- " << integral_prph_err << endl;
    scale_data_ll = (integral_data - integral_ll)/integral_prph;
    scale_err1 = integral_data_err/integral_prph;
    scale_err2 = integral_ll_err/integral_prph;
    scale_err3 = scale_err1*scale_err1 + scale_err2*scale_err2 + scale_err3*scale_err3;
    scale_data_ll_err = scale_err1*scale_err1 + scale_err2*scale_err2 + scale_err3*scale_err3;
    cout << "scale_data_ll (in bin "<< i<< ") = " << data->GetBinContent(i+1) << " - " 
      << ll_det->GetBinContent(i+1) << " = " << scale_data_ll << " +- " << scale_data_ll_err << endl;
    cout << "--> scaling by N_{data-LL}" << endl;
    Double_t err = hd->GetBinError(i+1);
    Double_t cont = hd->GetBinContent(i+1);
    Double_t new_err = cont*cont*scale_data_ll_err*scale_data_ll_err + err*err*scale_data_ll*scale_data_ll;
    new_err = TMath::Sqrt(new_err);
    Double_t new_cont = cont*scale_data_ll;
    hd->SetBinContent(i+1, new_cont);
    hd->SetBinError(i+1, new_err);
  }
  //
  // scale prph by parameter
  //
  cout << "--> scaling by fit param" << endl;
  for(Int_t i=0; i<det->GetNbinsX(); i++) {
    Double_t err = det->GetBinError(i+1);
    Double_t cont = det->GetBinContent(i+1);
    cout << "scaling: old content: " << i << " " << cont << " +- " << err << ", param = " << param[i] << " +- " << param_err[i] << endl;
    Double_t new_err = cont*cont*param_err[i]*param_err[i] + err*err*param[i]*param[i];
    new_err = TMath::Sqrt(new_err);
    Double_t new_cont = cont*param[i];
    cout << "scaling: old content: " << i << " " << new_cont << " +- " << new_err << endl;
    det->SetBinContent(i+1, new_cont);
    det->SetBinError(i+1, new_err);
  }
  for(Int_t i=0; i<had->GetNbinsX(); i++) {
    Double_t err = had->GetBinError(i+1);
    Double_t cont = had->GetBinContent(i+1);
    Double_t new_err = cont*cont*param_err[i]*param_err[i] + err*err*param[i]*param[i];
    new_err = TMath::Sqrt(new_err);
    Double_t new_cont = cont*param[i];
    had->SetBinContent(i+1, new_cont);
    had->SetBinError(i+1, new_err);
  }
  for(Int_t i=0; i<hd->GetNbinsX(); i++) {
    Double_t err = hd->GetBinError(i+1);
    Double_t cont = hd->GetBinContent(i+1);
    Double_t new_err = cont*cont*param_err[i]*param_err[i] + err*err*param[i]*param[i];
    new_err = TMath::Sqrt(new_err);
    Double_t new_cont = cont*param[i];
    hd->SetBinContent(i+1, new_cont);
    hd->SetBinError(i+1, new_err);
  }

  Int_t nbins = 0;
  Double_t sigma_tot = 0;
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
  //cout << "in plot_cross_section: nbins = " << nbins << endl;
  for(Int_t i=0; i<nbins; i++)
    {
      Double_t prph, prph_had, prph_hd;
      Double_t cross_sec;
      prph = det->GetBinContent(i+1) + ll_det->GetBinContent(i+1);;
      prph_had = had->GetBinContent(i+1);
      prph_hd = hd->GetBinContent(i+1);
      Double_t C_acc = 0.;
      Double_t low_edge=0, bottom_edge = 0;
      low_edge = det->GetBinLowEdge(i+1);
      bottom_edge = det->GetBinLowEdge(i+2);
      Double_t bin_width;
      bin_width = bottom_edge - low_edge;
      //      if(prph != 0.)
      //	C_acc = prph_had / prph;
      //      else 
      //	{
      //	  cout << "prph det bin content is 0! Can't calculate acceptance." <<endl;
      //	  exit(1);
      //	}
      //      cout << "C_acc = " << C_acc << ", C_acc_old = " << acc->GetBinContent(i+1) << endl;
      //      cross_sec = prph * C_acc;
      //      cross_sec /= bin_width;
      //      cross_sec /= Lumi;
      //errors:
      Double_t C_err = 0;
      //      C_err = TMath::Sqrt(prph_had/(prph*prph*prph));
      //      C_err *= TMath::Sqrt(prph + prph_had - 2*prph_hd);
      Double_t err1 =  0, err2 = 0, err3 = 0., err = 0; //statistic, acceptance, luminosity, full
      //      err1 = TMath::Sqrt(prph) * C_acc / (bin_width * Lumi);
      ///      err2 = prph * C_err / (bin_width * Lumi);
      //      err = TMath::Sqrt(err1*err1 + err2*err2);
      //cout << "bin " << i+2 << data << " " << prph << " " << prph_had << " " << prph_hd << " " << bin_width << endl;
      //cout << "bin " << i+1 <<" from " << low_edge << " to " << bottom_edge<< ": cross_sec = " << cross_sec << " C_acc = " << C_acc << " err = " << err << endl; 

      //
      // new and cool
      //
      C_acc = acc->GetBinContent(i+1);
      C_err = acc->GetBinError(i+1);
      cross_sec = prph / (bin_width * Lumi * C_acc);
      err1 = det->GetBinError(i+1) / (bin_width * Lumi * C_acc);
      //      err1 *= err1;
      err2 = prph*C_err / (bin_width * Lumi * C_acc * C_acc);
      //      err2 *= err2;
      err3 = 0.026*prph / (bin_width * Lumi * C_acc);
      //      err3 *= err3;
      err = TMath::Sqrt(err1*err1 + err2*err2 + err3*err3);
      res[0]->SetBinContent(i+1, cross_sec);
      res[0]->SetBinError(i+1, err);
      res[1]->SetBinContent(i+1, cross_sec);
      res[1]->SetBinError(i+1, err1);
      res[2]->SetBinContent(i+1, cross_sec);
      res[2]->SetBinError(i+1, err2);
      res[3]->SetBinContent(i+1, cross_sec);
      res[3]->SetBinError(i+1, err3);
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
      cout << name << " cros sec in bin " << i << ": " << cross_sec << " +- " << err << ", lumi = " << Lumi << ", acc_Prompt = " << C_acc << ", binWidth = " << bin_width << ", nentries = " << prph << endl;
      //      cout << "bin " << i+1 << " from " << low_edge << " to " << bottom_edge << " : sigma = " << cross_sec  << " +- " << err << endl;
      cout << "errors (stat. and fit, acc., lumi., total), %: " << err1/cross_sec << ", " 
	   << err2/cross_sec << ", " << err3/cross_sec << ", " << err/cross_sec << endl;
    }
  cout << "sigma_tot = " << sigma_tot << " pb" << endl;
}

void Hist::CalculateCrossSec(TH1D *h_Data, TH1D *h_Lepto_det,
			     TH1D *h_Lepto_had, TH1D *h_Lepto_hd, 
			     Double_t Lumi, Int_t Linecolor, TH1D **h_Cross_Sec)
{
  Int_t nbins = 0;
  TH1D *h_Cross = (TH1D*)h_Data->Clone();
  TH1D *h_Acc = (TH1D*)h_Data->Clone(); //histo with acceptance. Here is to have right binning!
  nbins  = h_Data->GetNbinsX();
  //cout << "in plot_cross_section: nbins = " << nbins << endl;
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
      Double_t low_edge=0, bottom_edge = 0;
      low_edge = h_Data->GetBinLowEdge(i+1);
      bottom_edge = h_Data->GetBinLowEdge(i+2);
      Double_t bin_width;
      bin_width = bottom_edge - low_edge;
      if(lepto != 0.)
	C_acc = lepto_had / lepto;
      else 
	{
	  cout << "lepto det bin content is 0! Can't calculate acceptance." <<endl;
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
      //cout << "bin " << i+2 << data << " " << lepto << " " << lepto_had << " " << lepto_hd << " " << bin_width << endl;
      //cout << "bin " << i+1 <<" from " << low_edge << " to " << bottom_edge<< ": cross_sec = " << cross_sec << " C_acc = " << C_acc << " err = " << err << endl; 
      h_Cross->SetBinContent(i+1, cross_sec);
      h_Cross->SetBinError(i+1, err);
      h_Acc->SetBinContent(i+1, 1./C_acc);
      h_Acc->SetBinError(i+1, C_err/(C_acc*C_acc));
    }
  h_Cross->SetLineColor(Linecolor);
  h_Cross_Sec[0] = (TH1D*)h_Cross->Clone();
  h_Cross_Sec[1] = (TH1D*)h_Acc->Clone();
  //cout << "in plot func. h_cross->GetBinContent(1) = " << h_Cross_Sec[0]->GetBinContent(1) << endl;
  //h_Cross->Draw("SAME");
}


