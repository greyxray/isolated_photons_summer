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

    h_1st[0]->SetBinContent(1, 2.41819);
    h_1st[0]->SetBinError(1, 0.178693);
    h_1st[0]->SetBinContent(2, 1.31229);
    h_1st[0]->SetBinError(2, 0.105384);
    h_1st[0]->SetBinContent(3, 0.623526);
    h_1st[0]->SetBinError(3, 0.0759004);
    h_1st[0]->SetBinContent(4, 0.247726);
    h_1st[0]->SetBinError(4, 0.0261127);
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

    h_1st[0]->SetBinContent(1, 6.89499);
    h_1st[0]->SetBinError(1,  0.604369);
    h_1st[0]->SetBinContent(2, 6.73155);
    h_1st[0]->SetBinError(2, 0.565759);
    h_1st[0]->SetBinContent(3, 5.35274);
    h_1st[0]->SetBinError(3, 0.562964);
    h_1st[0]->SetBinContent(4, 4.45287);
    h_1st[0]->SetBinError(4, 0.503169);
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
    h_1st[0]->SetBinContent(1, 0.28516);
    h_1st[0]->SetBinError(1, 0.0238065);
    h_1st[0]->SetBinContent(2, 0.125555);
    h_1st[0]->SetBinError(2, 0.0119632);
    h_1st[0]->SetBinContent(3, 0.0478211);
    h_1st[0]->SetBinError(3, 0.00558003);
    h_1st[0]->SetBinContent(4, 0.0217634);
    h_1st[0]->SetBinError(4, 0.00241322);
    h_1st[0]->SetBinContent(5, 0.00365646);
    h_1st[0]->SetBinError(5, 0.000644297);
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

    h_1st[0]->SetBinContent(1, 4692.38);
    h_1st[0]->SetBinError(1, 334.644);
    h_1st[0]->SetBinContent(2, 1754.8);
    h_1st[0]->SetBinError(2, 148.179);
    h_1st[0]->SetBinContent(3, 259.847);
    h_1st[0]->SetBinError(3, 32.7009);
    h_1st[0]->SetBinContent(4, 24.7458);
    h_1st[0]->SetBinError(4, 6.43478);
  }
  if(s_var[n] == "et_jet") {
    /*    h_1st[0]->SetBinContent(1, 1.34201);
    h_1st[0]->SetBinError(1, 0.181309);
    h_1st[0]->SetBinContent(2, 1.13305);
    h_1st[0]->SetBinError(2, 0.112347);
    h_1st[0]->SetBinContent(3, 0.965631);
    h_1st[0]->SetBinError(3, 0.0970976);
    h_1st[0]->SetBinContent(4, 0.699979);
    h_1st[0]->SetBinError(4, 0.0685523);
    h_1st[0]->SetBinContent(5, 0.279589);
    h_1st[0]->SetBinError(5, 0.026351);
    h_1st[0]->SetBinContent(6, 0.0262237);
    h_1st[0]->SetBinError(6, 0.00477817);*/
   h_1st[0]->SetBinContent(1, 1.41049);
    h_1st[0]->SetBinError(1, 0.165362);
    h_1st[0]->SetBinContent(2, 1.12617);
    h_1st[0]->SetBinError(2, 0.108891);
    h_1st[0]->SetBinContent(3, 0.967167);
    h_1st[0]->SetBinError(3, 0.0967213);
    h_1st[0]->SetBinContent(4, 0.724888);
    h_1st[0]->SetBinError(4, 0.0734868);
    h_1st[0]->SetBinContent(5, 0.319216);
    h_1st[0]->SetBinError(5, 0.0314079);
    h_1st[0]->SetBinContent(6, 0.0320303);
    h_1st[0]->SetBinError(6, 0.00556935);
  }
  if(s_var[n] == "eta_jet") {
    h_1st[0]->SetBinContent(1, 1.48706);
    h_1st[0]->SetBinError(1, 0.170825);
    h_1st[0]->SetBinContent(2, 2.63074);
    h_1st[0]->SetBinError(2, 0.251654);
    h_1st[0]->SetBinContent(3, 3.76784);
    h_1st[0]->SetBinError(3, 0.327495);
    h_1st[0]->SetBinContent(4, 3.5992);
    h_1st[0]->SetBinError(4, 0.318926);
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
