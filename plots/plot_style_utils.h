void sign_window(TVirtualPad *p, TH2D* h, TString xaxis, TString yaxis, TString title)
{
  Double_t height = 1-p->GetTopMargin()-p->GetBottomMargin();
  Double_t width = 1-p->GetLeftMargin()-p->GetRightMargin();
  //  cout << "pad width is: " << width << endl;
  //  cout << "pad height is: " << height << endl;
  if((width == 0.) || (height == 0.)) {
    cout << "In sign_window(). Width or height of pad is 0. Cannot set text size." << endl;
    exit(-1);
  }
  Double_t fontsizex = 0.08/width; //0.06
  Double_t fontsizey = 0.08/height;

  h->SetStats(kFALSE);
  h->SetTitle(title);
  h->GetXaxis()->SetTitle(xaxis);
  h->GetYaxis()->SetTitle(yaxis);
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
  h->GetXaxis()->SetTitleSize(fontsizex);
  h->GetXaxis()->SetTitleFont(42);
  //  h->GetYaxis()->SetTitleSize(0.5*fontsizey);
  h->GetYaxis()->SetTitleFont(42);
  h->GetXaxis()->SetLabelSize(fontsizex);
  h->GetXaxis()->SetLabelFont(42);
  h->GetXaxis()->SetTitleOffset(1.2);
  h->GetYaxis()->SetLabelSize(fontsizey);
  h->GetYaxis()->SetLabelFont(42);
  if(p->GetLogy())
        h->GetYaxis()->SetTitleOffset(2.5);
  else
        h->GetYaxis()->SetTitleOffset(1.5);
  h->GetXaxis()->SetNdivisions(507, kTRUE);
  h->GetYaxis()->SetNdivisions(507, kTRUE);
}


void sign_window(TVirtualPad *p, TH2D* h, TString xaxis, TString yaxis, TString title, TString title_size)
{

  Double_t coef = 1.;
  if (yaxis.EqualTo("data / mc"))
  {
    coef = 1.6;
    double xlo, ylo, xup, yup, ywidth;
    p->GetPadPar( xlo, ylo, xup, yup );
    ywidth = yup - ylo;
    p->SetPad(xlo, ylo + ywidth/2 , xup, yup);
  }
  Double_t height = 1-p->GetTopMargin()-p->GetBottomMargin();
  Double_t width = 1-p->GetLeftMargin()-p->GetRightMargin();
  //  cout << "pad width is: " << width << endl;
  //  cout << "pad height is: " << height << endl;
  if((width == 0.) || (height == 0.)) {
    cout << "In sign_window(). Width or height of pad is 0. Cannot set text size." << endl;
    exit(-1);
  }
  Double_t fontsizex = 0.04/width * coef; //0.06
  Double_t fontsizey = 0.04/height * coef;

  if(title_size == "small")
    {
      fontsizex *= 0.7 ;
      fontsizey *= 0.7 ;
    }
  if(title_size == "middle")
    {
      fontsizex *= 1.3 ;
      fontsizey *= 1.4 ;
    }
  if(title_size == "large")
    {
      fontsizex *= 1.4 ;
      fontsizey *= 2. ;
    }

  h->SetStats(kFALSE);
  h->SetTitle(title);
  h->GetXaxis()->SetTitle(xaxis);
  h->GetXaxis()->CenterTitle();
  h->GetXaxis()->SetTitleSize(fontsizex*1.3);
  h->GetXaxis()->SetTitleFont(42);
  h->GetXaxis()->SetLabelSize(fontsizex);
  h->GetXaxis()->SetLabelFont(42);
  h->GetXaxis()->SetTitleOffset(1.);
  h->GetXaxis()->SetNdivisions(507, kTRUE);

  h->GetYaxis()->SetTitle(yaxis);
  h->GetYaxis()->CenterTitle();
  h->GetYaxis()->SetTitleSize(fontsizey*1.5);
  h->GetYaxis()->SetTitleFont(42);
  h->GetYaxis()->SetLabelSize(fontsizey);
  h->GetYaxis()->SetLabelFont(42);
  if(p->GetLogy())
    h->GetYaxis()->SetTitleOffset(2.5/coef);
  else
    h->GetYaxis()->SetTitleOffset(0.8/coef);//1
  h->GetYaxis()->SetNdivisions(507, kTRUE);
}


void make_clean_canv(TCanvas *c)
{
  c->SetBorderMode(0);
  c->SetFillColor(kWhite);
  c->SetFillStyle(0);

}

void make_clean_pads(TCanvas *c, Int_t n, Int_t gridx, Int_t gridy)
{

  for(Int_t i=0; i<n; i++)
    {
      c->GetPad(i+1)->SetBottomMargin(0.18);
      c->GetPad(i+1)->SetTopMargin(0.08);
      c->GetPad(i+1)->SetLeftMargin(0.16);//0.18
      c->GetPad(i+1)->SetRightMargin(0.16);//0.13
      c->GetPad(i+1)->SetFrameBorderMode(0);
      c->GetPad(i+1)->SetBorderMode(0);
      c->GetPad(i+1)->SetFillColor(kWhite);
      c->GetPad(i+1)->SetGrid(gridx, gridy);
    }
}

void make_clean_pads_close(TCanvas *c, Int_t n, Int_t gridx, Int_t gridy)
{

  for(Int_t i=0; i<n; i++)
    {
      //c->GetPad(i+1)->SetBottomMargin(0.18);
      //c->GetPad(i+1)->SetTopMargin(0.08);
      c->GetPad(i+1)->SetLeftMargin(0.16);//0.18
      c->GetPad(i+1)->SetRightMargin(0.16);//0.13
      c->GetPad(i+1)->SetFrameBorderMode(0);
      c->GetPad(i+1)->SetBorderMode(0);
      c->GetPad(i+1)->SetFillColor(kWhite);
      c->GetPad(i+1)->SetGrid(gridx, gridy);
    }
}

void make_clean_pads(TVirtualPad *c, Int_t n, Int_t gridx, Int_t gridy)
{

  for(Int_t i=0; i<n; i++)
    {
      //          c->GetPad(i+1)->SetBottomMargin(0.17);
      //            c->GetPad(i+1)->SetTopMargin(0.05);
      //            c->GetPad(i+1)->SetLeftMargin(0.17);
      //            c->GetPad(i+1)->SetRightMargin(0.05);
      c->GetPad(i+1)->SetTicks(1,1);
      c->GetPad(i+1)->SetFrameBorderMode(0);
      c->GetPad(i+1)->SetBorderMode(0);
      c->GetPad(i+1)->SetFillColor(kWhite);
      c->GetPad(i+1)->SetGrid(gridx, gridy);
    }
}

Double_t hist_maximum(TH1D** h, Int_t n)
{
  vector<Double_t> maximums;
  for(Int_t i=0; i<n; i++)
    {
      Double_t max = h[i]->GetMaximum();
      maximums.push_back(max);
      cout << i << " added " << max << endl;
    }
  sort(maximums.begin(), maximums.end());
  cout << "max is " << maximums.back() << endl;
  return maximums.back();
}

Double_t hist_maximum(TH1D** h, Int_t start, Int_t end)
{
  vector<Double_t> maximums;
  for(Int_t i=start-1; i<end; i++)
    {
      Double_t max = h[i]->GetMaximum();
      maximums.push_back(max);
      cout << i << " added " << max << endl;
    }
  sort(maximums.begin(), maximums.end());
  cout << "max is " << maximums.back() << endl;
  return maximums.back();
}
void scale_hist_to_hist_with_err(TH1D* hist_to_scale, TH1D* hist_ref)
{
  if(hist_to_scale->GetNbinsX() != hist_ref->GetNbinsX()) {
    cerr << "error in scale_hist_to_hist_with_errr(): histograms have different binning" << endl;
    exit(-1);
  }
  Double_t scale = 1;
  Double_t scale_err = 0;
  Double_t sum_to_scale = 0, sum_to_scale_err = 0, sum_ref = 0, sum_ref_err = 0;
  for(Int_t i=0; i<hist_to_scale->GetNbinsX(); i++) {
    sum_to_scale += hist_to_scale->GetBinContent(i+1);
    sum_to_scale_err += TMath::Power(hist_to_scale->GetBinError(i+1), 2.);
    sum_ref += hist_ref->GetBinContent(i+1);
    sum_ref_err += TMath::Power(hist_ref->GetBinError(i+1), 2.);
  }
  sum_to_scale_err = TMath::Sqrt(sum_to_scale_err);
  sum_ref_err = TMath::Sqrt(sum_ref_err);
  if(sum_to_scale == 0) {
    cerr << "error in scale_hist_to_hist_with_errr(): division by 0" << endl;
    exit(-1);
  }
  scale = sum_ref / sum_to_scale;
  scale_err = TMath::Sqrt( TMath::Power(sum_ref_err/sum_to_scale, 2.) + 
         TMath::Power(sum_ref*sum_to_scale_err/(sum_to_scale*sum_to_scale), 2.) );
  for(Int_t i=0; i<hist_to_scale->GetNbinsX(); i++) {
    Double_t oldc = hist_to_scale->GetBinContent(i+1);
    Double_t oldc_err = hist_to_scale->GetBinError(i+1);
    Double_t newc = oldc*scale;
    Double_t newc_err = TMath::Sqrt(TMath::Power(oldc*scale_err, 2.) + TMath::Power(oldc_err*scale, 2.));
    hist_to_scale->SetBinContent(i+1, newc);
    hist_to_scale->SetBinError(i+1, newc_err);
  }
}
