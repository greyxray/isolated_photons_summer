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

    h_1st[0]->SetBinContent(1, 2.30529);
    h_1st[0]->SetBinError(1, 0.193131);
    h_1st[0]->SetBinContent(2, 1.26835);
    h_1st[0]->SetBinError(2, 0.109497);
    h_1st[0]->SetBinContent(3, 0.611918);
    h_1st[0]->SetBinError(3, 0.0759759);
    h_1st[0]->SetBinContent(4, 0.251099);
    h_1st[0]->SetBinError(4, 0.0276728);
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

    h_1st[0]->SetBinContent(1, 6.94217);
    h_1st[0]->SetBinError(1,  0.641734);
    h_1st[0]->SetBinContent(2, 6.71715);
    h_1st[0]->SetBinError(2, 0.59723);
    h_1st[0]->SetBinContent(3, 5.46751);
    h_1st[0]->SetBinError(3, 0.574704);
    h_1st[0]->SetBinContent(4, 4.37557);
    h_1st[0]->SetBinError(4, 0.513001);
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
    h_1st[0]->SetBinContent(1, 0.286882);
    h_1st[0]->SetBinError(1, 0.0254851);
    h_1st[0]->SetBinContent(2, 0.126377);
    h_1st[0]->SetBinError(2, 0.0124057);
    h_1st[0]->SetBinContent(3, 0.0473137);
    h_1st[0]->SetBinError(3, 0.00580999);
    h_1st[0]->SetBinContent(4, 0.0217085);
    h_1st[0]->SetBinError(4, 0.00249202);
    h_1st[0]->SetBinContent(5, 0.00363598);
    h_1st[0]->SetBinError(5, 0.000690612);
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

    h_1st[0]->SetBinContent(1, 4779.77);
    h_1st[0]->SetBinError(1, 364.354);
    h_1st[0]->SetBinContent(2, 1719.3);
    h_1st[0]->SetBinError(2, 151.204);
    h_1st[0]->SetBinContent(3, 262.594);
    h_1st[0]->SetBinError(3, 34.1521);
    h_1st[0]->SetBinContent(4, 24.0518);
    h_1st[0]->SetBinError(4, 6.19243);
  }
  if(s_var[n] == "et_jet") {
    h_1st[0]->SetBinContent(1, 1.32077);
    h_1st[0]->SetBinError(1, 0.172326);
    h_1st[0]->SetBinContent(2, 1.12271);
    h_1st[0]->SetBinError(2, 0.11241);
    h_1st[0]->SetBinContent(3, 0.940803);
    h_1st[0]->SetBinError(3, 0.0999052);
    h_1st[0]->SetBinContent(4, 0.73129);
    h_1st[0]->SetBinError(4, 0.0763486);
    h_1st[0]->SetBinContent(5, );
    h_1st[0]->SetBinError(5, );
    h_1st[0]->SetBinContent(6, );
    h_1st[0]->SetBinError(6, );
  }
  if(s_var[n] == "eta_jet") {
    h_1st[0]->SetBinContent(1, 1.50537);
    h_1st[0]->SetBinError(1, 0.174825);
    h_1st[0]->SetBinContent(2, 2.68503);
    h_1st[0]->SetBinError(2, 0.260746);
    h_1st[0]->SetBinContent(3, 3.87402);
    h_1st[0]->SetBinError(3, 0.350877);
    h_1st[0]->SetBinContent(4, 3.42605);
    h_1st[0]->SetBinError(4, 0.314938);
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
