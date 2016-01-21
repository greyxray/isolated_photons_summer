void Hist::Compare1st2nd(Int_t n, TH1D** h_1st, TH1D** h_2nd)
{
  cout << "Entering hist_compare1st2nd.c" << endl;
  h_1st[0] = (TH1D*)h_2nd[0]->Clone();
  h_1st[0]->SetName(h_2nd[0]->GetName() + TString("_1st_analysis"));
  
  h_1st[4] = (TH1D*)h_2nd[4]->Clone();
  h_1st[4]->SetName(h_2nd[4]->GetName() + TString("_1st_analysis"));

  if(s_var[n] == "et") {
h_1st[0]->SetBinContent(1, 2.38715);
h_1st[0]->SetBinError(1, 0.183255);
h_1st[0]->SetBinContent(2, 1.29);
h_1st[0]->SetBinError(2, 0.104856);
h_1st[0]->SetBinContent(3, 0.613948);
h_1st[0]->SetBinError(3, 0.0769511);
h_1st[0]->SetBinContent(4, 0.250965);
h_1st[0]->SetBinError(4, 0.0270204);

  }
  if(s_var[n] == "eta") {

h_1st[0]->SetBinContent(1, 7.26298);
h_1st[0]->SetBinError(1, 0.606495);
h_1st[0]->SetBinContent(2, 6.36946);
h_1st[0]->SetBinError(2, 0.534726);
h_1st[0]->SetBinContent(3, 5.52583);
h_1st[0]->SetBinError(3, 0.543494);
h_1st[0]->SetBinContent(4, 5.03845);
h_1st[0]->SetBinError(4, 0.528302);

  }
  if(s_var[n] == "Q2") {

h_1st[0]->SetBinContent(1, 0.291339);
h_1st[0]->SetBinError(1, 0.0246273);
h_1st[0]->SetBinContent(2, 0.128066);
h_1st[0]->SetBinError(2, 0.011909);
h_1st[0]->SetBinContent(3, 0.0471501);
h_1st[0]->SetBinError(3, 0.00565118);
h_1st[0]->SetBinContent(4, 0.0222523);
h_1st[0]->SetBinError(4, 0.00242282);
h_1st[0]->SetBinContent(5, 0.00380146);
h_1st[0]->SetBinError(5, 0.00072053);

  }
  if(s_var[n] == "x") {

h_1st[0]->SetBinContent(1, 4734.89);
h_1st[0]->SetBinError(1, 340.147);
h_1st[0]->SetBinContent(2, 1741.56);
h_1st[0]->SetBinError(2, 143.044);
h_1st[0]->SetBinContent(3, 266.356);
h_1st[0]->SetBinError(3, 34.3157);
h_1st[0]->SetBinContent(4, 27.8896);
h_1st[0]->SetBinError(4, 7.70353);

  }
  if(s_var[n] == "et_jet") {

h_1st[0]->SetBinContent(1, 1.33293);
h_1st[0]->SetBinError(1, 0.168075);
h_1st[0]->SetBinContent(2, 1.15801);
h_1st[0]->SetBinError(2, 0.108655);
h_1st[0]->SetBinContent(3, 0.943754);
h_1st[0]->SetBinError(3, 0.0965607);
h_1st[0]->SetBinContent(4, 0.724772);
h_1st[0]->SetBinError(4, 0.0744572);
h_1st[0]->SetBinContent(5, 0.317728);
h_1st[0]->SetBinError(5, 0.0333168);
h_1st[0]->SetBinContent(6, 0.0283796);
h_1st[0]->SetBinError(6, 0.00736767);

  }
  if(s_var[n] == "eta_jet") {

h_1st[0]->SetBinContent(1, 1.5117);
h_1st[0]->SetBinError(1, 0.170621);
h_1st[0]->SetBinContent(2, 2.78151);
h_1st[0]->SetBinError(2, 0.251139);
h_1st[0]->SetBinContent(3, 3.78551);
h_1st[0]->SetBinError(3, 0.337509);
h_1st[0]->SetBinContent(4, 3.46116);
h_1st[0]->SetBinError(4, 0.315143);


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
