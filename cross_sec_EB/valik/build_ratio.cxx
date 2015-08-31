int build_ratio()
{
const Int_t n_bins = 20;
TH1D* h1 = new TH1D("h1",  "h1", n_bins, 0., 10.);
TH1D* h2 = new TH1D("h2",  "h2", n_bins, 0., 10.);
TH1D* ratio =new TH1D("ratio", "ratio", n_bins, 0., 10.);
Double_t pi = 3.1415926535 8979323846 26;
//fill histograms
for(Int_t i=0; i<n_bins; i++)
{
    h1->SetBinContent(i+1, 5000.);
    h1->SetBinError(i+1, TMath::Sqrt(5000.));
    h2->SetBinContent(i+1, 5000. + 100*TMath::Sin(2*pi*i/n_bins));
    h2->SetBinError(i+1, TMath::Sqrt(5000. +  100*TMath::Sin(pi*i/n_bins)));
}
//build ratio
for(Int_t i=0; i<n_bins; i++)
{
    Double_t x = h1->GetBinContent(i+1);
    Double_t x_err = h1->GetBinError(i+1);
    Double_t y = h2->GetBinContent(i+1);
    Double_t y_err = h2->GetBinError(i+1);
    Double_t r = x/y;
    Double_t r_err = TMath::Sqrt(x_err*x_err/(y*y) + (y_err*y_err*x*x)/(y*y*y*y));
    ratio->SetBinContent(i+1, r);
    ratio->SetBinError(i+1, r_err);
    cout << "in bin " << i+1 << " ratio = " << r << " +- " << r_err << endl;
}
ratio->SetMarkerStyle(20);
ratio->SetMarkerSize(0.5);
ratio->SetMarkerColor(kBlue);
ratio->GetYaxis()->SetRangeUser(0.8, 1.2);
ratio->Draw("E P X0");
return 0;
}

