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

    h_1st[0]->SetBinContent(1, 2.84325);
    h_1st[0]->SetBinError(1, 0.300097);
    h_1st[0]->SetBinContent(2, 1.35037);
    h_1st[0]->SetBinError(2, 0.175797);
    h_1st[0]->SetBinContent(3, 0.636231);
    h_1st[0]->SetBinError(3, 0.104606);
    h_1st[0]->SetBinContent(4, 0.358404);
    h_1st[0]->SetBinError(4, 0.025162);
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

    h_1st[0]->SetBinContent(1, 8.18224);
    h_1st[0]->SetBinError(1,  0.909208);
    h_1st[0]->SetBinContent(2, 6.78585);
    h_1st[0]->SetBinError(2, 0.910296);
    h_1st[0]->SetBinContent(3, 6.52948);
    h_1st[0]->SetBinError(3, 0.881052);
    h_1st[0]->SetBinContent(4, 5.3774);
    h_1st[0]->SetBinError(4, 0.923367);
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
    h_1st[0]->SetBinContent(1, 0.316676);
    h_1st[0]->SetBinError(1, 0.0409231);
    h_1st[0]->SetBinContent(2, 0.146083);
    h_1st[0]->SetBinError(2, 0.0189199);
    h_1st[0]->SetBinContent(3, 0.0527507);
    h_1st[0]->SetBinError(3, 0.00975121);
    h_1st[0]->SetBinContent(4, 0.0241152);
    h_1st[0]->SetBinError(4, 0.0036906);
    h_1st[0]->SetBinContent(5, 0.00469674);
    h_1st[0]->SetBinError(5, 0.00105384);
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

    h_1st[0]->SetBinContent(1, 5244.9);
    h_1st[0]->SetBinError(1, 524.942);
    h_1st[0]->SetBinContent(2, 2120.32);
    h_1st[0]->SetBinError(2, 251.365);
    h_1st[0]->SetBinContent(3, 233.248);
    h_1st[0]->SetBinError(3, 57.7452);
    h_1st[0]->SetBinContent(4, 29.3547);
    h_1st[0]->SetBinError(4, 12.3906);
  }
  if(s_var[n] == "et_jet") {
    h_1st[0]->SetBinContent(1, 1.70221);
    h_1st[0]->SetBinError(1, 0.269623);
    h_1st[0]->SetBinContent(2, 1.33855);
    h_1st[0]->SetBinError(2, 0.176441);
    h_1st[0]->SetBinContent(3, 0.836545);
    h_1st[0]->SetBinError(3, 0.174854);
    h_1st[0]->SetBinContent(4, 0.776461);
    h_1st[0]->SetBinError(4, 0.120627);
    h_1st[0]->SetBinContent(5, 0.339377);
    h_1st[0]->SetBinError(5, 0.0525964);
    h_1st[0]->SetBinContent(6, 0.0199135);
    h_1st[0]->SetBinError(6, 0.010984);
  }
  if(s_var[n] == "eta_jet") {
    h_1st[0]->SetBinContent(1, 1.58726);
    h_1st[0]->SetBinError(1, 0.288447);
    h_1st[0]->SetBinContent(2, 3.11455);
    h_1st[0]->SetBinError(2, 0.410444);
    h_1st[0]->SetBinContent(3, 4.26571);
    h_1st[0]->SetBinError(3, 0.583151);
    h_1st[0]->SetBinContent(4, 3.97136);
    h_1st[0]->SetBinError(4, 0.491055);
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
