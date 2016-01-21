void Hist::Compare1st2nd(Int_t n, TH1D** h_1st, TH1D** h_2nd)
{
  cout << "Entering hist_compare1st2nd.c" << endl;
  h_1st[0] = (TH1D*)h_2nd[0]->Clone();
  h_1st[0]->SetName(h_2nd[0]->GetName() + TString("_1st_analysis"));
  
  h_1st[4] = (TH1D*)h_2nd[4]->Clone();
  h_1st[4]->SetName(h_2nd[4]->GetName() + TString("_1st_analysis"));

  if(s_var[n] == "et") {
    //incluing 04p
    /*    h_1st[0]->SetBinContent(1, 2.06836);
    h_1st[0]->SetBinError(1, 0.168925);
    h_1st[0]->SetBinContent(2, 1.09996);
    h_1st[0]->SetBinError(2, 0.0970804);
    h_1st[0]->SetBinContent(3, 0.475102);
    h_1st[0]->SetBinError(3, 0.0713353);
    h_1st[0]->SetBinContent(4, 0.188527);
    h_1st[0]->SetBinError(4, 0.0246533);*/
    //without 04p
    /*    h_1st[0]->SetBinContent(1, 2.0454);
    h_1st[0]->SetBinError(1, 0.176207);
    h_1st[0]->SetBinContent(2, 1.06464);
    h_1st[0]->SetBinError(2, 0.100957);
    h_1st[0]->SetBinContent(3, 0.496737);
    h_1st[0]->SetBinError(3, 0.0731337);
    h_1st[0]->SetBinContent(4, 0.190146);
    h_1st[0]->SetBinError(4, 0.026259);*/

    h_1st[0]->SetBinContent(1, 2.3029);
    h_1st[0]->SetBinError(1, 0.193011);
    h_1st[0]->SetBinContent(2, 1.25909);
    h_1st[0]->SetBinError(2, 0.108181);
    h_1st[0]->SetBinContent(3, 0.613656);
    h_1st[0]->SetBinError(3, 0.0755884);
    h_1st[0]->SetBinContent(4, 0.246259);
    h_1st[0]->SetBinError(4, 0.0277468);
  }
  if(s_var[n] == "eta") {
    /*    h_1st[0]->SetBinContent(1, 4.50035);
    h_1st[0]->SetBinError(1, 0.535664);
    h_1st[0]->SetBinContent(2, 5.598);
    h_1st[0]->SetBinError(2, 0.489786);
    h_1st[0]->SetBinContent(3, 5.00197);
    h_1st[0]->SetBinError(3, 0.505879);
    h_1st[0]->SetBinContent(4, 5.00544);
    h_1st[0]->SetBinError(4, 0.50755);*/

    h_1st[0]->SetBinContent(1, 6.91446);
    h_1st[0]->SetBinError(1,  0.634514);
    h_1st[0]->SetBinContent(2, 6.6533);
    h_1st[0]->SetBinError(2, 0.59514);
    h_1st[0]->SetBinContent(3, 5.33947);
    h_1st[0]->SetBinError(3, 0.574126);
    h_1st[0]->SetBinContent(4, 4.30459);
    h_1st[0]->SetBinError(4, 0.502665);
  }
  if(s_var[n] == "Q2") {
    /*    h_1st[0]->SetBinContent(1, 0.267827);
    h_1st[0]->SetBinError(1, 0.023663 );
    h_1st[0]->SetBinContent(2, 0.111924);
    h_1st[0]->SetBinError(2, 0.01187);
    h_1st[0]->SetBinContent(3, 0.0336359);
    h_1st[0]->SetBinError(3, 0.0055053 );
    h_1st[0]->SetBinContent(4, 0.0140906);
    h_1st[0]->SetBinError(4, 0.00236281 );
    h_1st[0]->SetBinContent(5, 0.00137384);
    h_1st[0]->SetBinError(5, 0.000636037);*/
    h_1st[0]->SetBinContent(1, 0.285541);
    h_1st[0]->SetBinError(1, 0.0254409);
    h_1st[0]->SetBinContent(2, 0.125852);
    h_1st[0]->SetBinError(2, 0.0123756);
    h_1st[0]->SetBinContent(3, 0.04703);
    h_1st[0]->SetBinError(3, 0.00577837);
    h_1st[0]->SetBinContent(4, 0.0216404);
    h_1st[0]->SetBinError(4, 0.00247263);
    h_1st[0]->SetBinContent(5, 0.00360813);
    h_1st[0]->SetBinError(5, 0.000680103);
  }

  if(s_var[n] == "x") {
    /*    h_1st[0]->SetBinContent(1, 4393.37);
    h_1st[0]->SetBinError(1, 315.263);
    h_1st[0]->SetBinContent(2, 1431.61);
    h_1st[0]->SetBinError(2, 131.266);
    h_1st[0]->SetBinContent(3, 171.277);
    h_1st[0]->SetBinError(3, 30.5389);
    h_1st[0]->SetBinContent(4, 24.063);
    h_1st[0]->SetBinError(4, 6.98514);*/

    h_1st[0]->SetBinContent(1, 4732.08);
    h_1st[0]->SetBinError(1, 361.546);
    h_1st[0]->SetBinContent(2, 1689.19);
    h_1st[0]->SetBinError(2, 149.128);
    h_1st[0]->SetBinContent(3, 258.045);
    h_1st[0]->SetBinError(3, 34.0546);
    h_1st[0]->SetBinContent(4, 26.8737);
    h_1st[0]->SetBinError(4, 7.29227);
  }
  if(s_var[n] == "et_jet") {
    h_1st[0]->SetBinContent(1, 1.30534);
    h_1st[0]->SetBinError(1, 0.171617);
    h_1st[0]->SetBinContent(2, 1.10396);
    h_1st[0]->SetBinError(2, 0.112333);
    h_1st[0]->SetBinContent(3, 0.912755);
    h_1st[0]->SetBinError(3, 0.0975553);
    h_1st[0]->SetBinContent(4, 0.728053);
    h_1st[0]->SetBinError(4, 0.0758943);
    h_1st[0]->SetBinContent(5, 0.306062);
    h_1st[0]->SetBinError(5, 0.0330386);
    h_1st[0]->SetBinContent(6, 0.0298964);
    h_1st[0]->SetBinError(6, 0.00619988);
  }
  if(s_var[n] == "eta_jet") {
    h_1st[0]->SetBinContent(1, 1.48369);
    h_1st[0]->SetBinError(1, 0.175538);
    h_1st[0]->SetBinContent(2, 2.64817);
    h_1st[0]->SetBinError(2, 0.259203);
    h_1st[0]->SetBinContent(3, 3.80235);
    h_1st[0]->SetBinError(3, 0.348653);
    h_1st[0]->SetBinContent(4, 3.41252);
    h_1st[0]->SetBinError(4, 0.317002);
  }

  for(Int_t i=0; i<h_1st[0]->GetNbinsX(); i++) {
    Double_t ratio = h_1st[0]->GetBinContent(i+1) / h_2nd[0]->GetBinContent(i+1);
    Double_t e1 = h_1st[0]->GetBinError(i+1) / h_2nd[0]->GetBinContent(i+1);
    Double_t e2 = h_1st[0]->GetBinContent(i+1) * h_2nd[0]->GetBinError(i+1) / 
      TMath::Power(h_2nd[0]->GetBinContent(i+1), 2.);
    Double_t err = TMath::Sqrt(e1*e1 + e2*e2);
    h_1st[4]->SetBinContent(i+1, 1 - ratio);
    h_1st[4]->SetBinError(i+1, err);
    cout << i << ", ratio 1st/2nd = " << ratio << " +- " << err << endl;
  }
  cout << "exiting hist_compare1st2nd.c" << endl;
}
