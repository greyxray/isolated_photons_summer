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

    h_1st[0]->SetBinContent(1, 2.009055e+00);
    h_1st[0]->SetBinError(1, 0.);
    h_1st[0]->SetBinContent(2, 2.755410e+00);
    h_1st[0]->SetBinError(2, 0.);
    h_1st[0]->SetBinContent(3, 1.639251e+00);
    h_1st[0]->SetBinError(3, 0.);
    h_1st[0]->SetBinContent(4, 7.246490e-01);
    h_1st[0]->SetBinError(4, 0.);
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

    h_1st[0]->SetBinContent(1, 1.257025e+01);
    h_1st[0]->SetBinError(1, 0.);
    h_1st[0]->SetBinContent(2, 1.103792e+01);
    h_1st[0]->SetBinError(2, 0.);
    h_1st[0]->SetBinContent(3, 9.520717e+00);
    h_1st[0]->SetBinError(3, 0.);
    h_1st[0]->SetBinContent(4, 7.947796e+00);
    h_1st[0]->SetBinError(4, 0.);
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
    h_1st[0]->SetBinContent(1, 6.370623e-01);
    h_1st[0]->SetBinError(1, 0.);
    h_1st[0]->SetBinContent(2, 2.330193e-01);
    h_1st[0]->SetBinError(2, 0.);
    h_1st[0]->SetBinContent(3, 8.707464e-02);
    h_1st[0]->SetBinError(3, 0.);
    h_1st[0]->SetBinContent(4, 2.900020e-02);
    h_1st[0]->SetBinError(4, 0.);
    h_1st[0]->SetBinContent(5, 5.020052e-03);
    h_1st[0]->SetBinError(5, 0.);
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

    h_1st[0]->SetBinContent(1, 9.725006e+03);
    h_1st[0]->SetBinError(1, 0.);
    h_1st[0]->SetBinContent(2, 3.212485e+03);
    h_1st[0]->SetBinError(2, 0.);
    h_1st[0]->SetBinContent(3, 5.089281e+02);
    h_1st[0]->SetBinError(3, 0.);
    h_1st[0]->SetBinContent(4, 3.859887e+01);
    h_1st[0]->SetBinError(4, 0.);
  }
  if(s_var[n] == "et_jet") {
    h_1st[0]->SetBinContent(1, 2.052771e+00);
    h_1st[0]->SetBinError(1, 0.);
    h_1st[0]->SetBinContent(2, 1.888230e+00);
    h_1st[0]->SetBinError(2, 0.);
    h_1st[0]->SetBinContent(3, 1.540041e+00);
    h_1st[0]->SetBinError(3, 0.);
    h_1st[0]->SetBinContent(4, 1.176246e+00);
    h_1st[0]->SetBinError(4, 0.);
    h_1st[0]->SetBinContent(5, 6.097821e-01);
    h_1st[0]->SetBinError(5, 0.);
    h_1st[0]->SetBinContent(6, 5.424107e-02);
    h_1st[0]->SetBinError(6, 0.);

  }
  if(s_var[n] == "eta_jet") {
    h_1st[0]->SetBinContent(1, 4.876686e+00);
    h_1st[0]->SetBinError(1, 0.);
    h_1st[0]->SetBinContent(2, 5.825526e+00);
    h_1st[0]->SetBinError(2, 0.);
    h_1st[0]->SetBinContent(3, 5.128622e+00);
    h_1st[0]->SetBinError(3, 0.);
    h_1st[0]->SetBinContent(4, 4.184456e+00);
    h_1st[0]->SetBinError(4, 0.);
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
