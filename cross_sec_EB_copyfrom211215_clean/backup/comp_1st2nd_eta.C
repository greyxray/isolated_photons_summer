{
//=========Macro generated from canvas: canv_cross_eta/
//=========  (Fri Mar 11 01:30:27 2011) by ROOT version5.26/00c
   TCanvas *canv_cross_eta = new TCanvas("canv_cross_eta", "",1,1,550,876);
   canv_cross_eta->SetHighLightColor(2);
   canv_cross_eta->Range(0,0,1,1);
   canv_cross_eta->SetFillColor(0);
   canv_cross_eta->SetBorderMode(0);
   canv_cross_eta->SetBorderSize(2);
   canv_cross_eta->SetTopMargin(0.04761905);
   canv_cross_eta->SetBottomMargin(0.05);
   canv_cross_eta->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_eta_1
   TPad *canv_cross_eta_1 = new TPad("canv_cross_eta_1", "_1",0.1,0.4,0.9,0.9);
   canv_cross_eta_1->Draw();
   canv_cross_eta_1->cd();
   canv_cross_eta_1->Range(-0.9536585,0.05,0.997561,8.5);
   canv_cross_eta_1->SetFillColor(0);
   canv_cross_eta_1->SetBorderMode(0);
   canv_cross_eta_1->SetBorderSize(2);
   canv_cross_eta_1->SetTickx(1);
   canv_cross_eta_1->SetTicky(1);
   canv_cross_eta_1->SetLeftMargin(0.13);
   canv_cross_eta_1->SetRightMargin(0.05);
   canv_cross_eta_1->SetTopMargin(0);
   canv_cross_eta_1->SetBottomMargin(0);
   canv_cross_eta_1->SetFrameBorderMode(0);
   canv_cross_eta_1->SetFrameBorderMode(0);
   Double_t xAxis78[5] = {-0.7, -0.3, 0.1, 0.5, 0.9}; 
   
   TH2D *h_window_cross_eta = new TH2D("h_window_cross_eta","",4, xAxis78,10,0.05,8.5);
   h_window_cross_eta->SetStats(0);
   h_window_cross_eta->GetXaxis()->SetTitle("#eta_{photon}");
   h_window_cross_eta->GetXaxis()->CenterTitle(true);
   h_window_cross_eta->GetXaxis()->SetNdivisions(507);
   h_window_cross_eta->GetXaxis()->SetLabelFont(42);
   h_window_cross_eta->GetXaxis()->SetLabelSize(0.05073171);
   h_window_cross_eta->GetXaxis()->SetTitleSize(0.06341463);
   h_window_cross_eta->GetXaxis()->SetTitleFont(42);
   h_window_cross_eta->GetYaxis()->SetTitle("d#sigma/d #eta_{photon} (pb)");
   h_window_cross_eta->GetYaxis()->CenterTitle(true);
   h_window_cross_eta->GetYaxis()->SetNdivisions(507);
   h_window_cross_eta->GetYaxis()->SetLabelFont(42);
   h_window_cross_eta->GetYaxis()->SetLabelSize(0.0416);
   h_window_cross_eta->GetYaxis()->SetTitleSize(0.052);
   h_window_cross_eta->GetYaxis()->SetTitleFont(42);
   h_window_cross_eta->Draw("");
   Double_t xAxis79[5] = {-0.7, -0.3, 0.1, 0.5, 0.9}; 
   
   TH1D *h_cross_section_eta = new TH1D("h_cross_section_eta","det_cross_eta",4, xAxis79);
   h_cross_section_eta->SetBinContent(1,12.97556);
   h_cross_section_eta->SetBinContent(2,11.68049);
   h_cross_section_eta->SetBinContent(3,10.39248);
   h_cross_section_eta->SetBinContent(4,6.480043);
   h_cross_section_eta->SetBinError(1,1.069656);
   h_cross_section_eta->SetBinError(2,1.004123);
   h_cross_section_eta->SetBinError(3,0.9665408);
   h_cross_section_eta->SetBinError(4,0.917661);
   h_cross_section_eta->SetEntries(22622);
   h_cross_section_eta->SetFillColor(41);
   h_cross_section_eta->SetMarkerStyle(20);
   h_cross_section_eta->SetMarkerSize(0.8);
   h_cross_section_eta->Draw("E1 X0 SAME");
   Double_t xAxis80[5] = {-0.7, -0.3, 0.1, 0.5, 0.9}; 
   
   TH1D *h_cross_section_eta_1st_analysis = new TH1D("h_cross_section_eta_1st_analysis","det_cross_eta",4, xAxis80);
   h_cross_section_eta_1st_analysis->SetBinContent(1,3.83192);
   h_cross_section_eta_1st_analysis->SetBinContent(2,5.41867);
   h_cross_section_eta_1st_analysis->SetBinContent(3,4.83434);
   h_cross_section_eta_1st_analysis->SetBinContent(4,4.21572);
   h_cross_section_eta_1st_analysis->SetBinError(1,0.584391);
   h_cross_section_eta_1st_analysis->SetBinError(2,0.555239);
   h_cross_section_eta_1st_analysis->SetBinError(3,0.554612);
   h_cross_section_eta_1st_analysis->SetBinError(4,0.491631);
   h_cross_section_eta_1st_analysis->SetEntries(22626);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   h_cross_section_eta_1st_analysis->SetLineColor(ci);

   ci = TColor::GetColor("#000000");
   h_cross_section_eta_1st_analysis->SetMarkerColor(ci);
   h_cross_section_eta_1st_analysis->SetMarkerStyle(21);
   h_cross_section_eta_1st_analysis->SetMarkerSize(0.8);
   h_cross_section_eta_1st_analysis->Draw("P E1 X0 SAME");
   
   TLegend *leg = new TLegend(0.37,0.059,0.77,0.358,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_eta_1st_analysis","1st analysis","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(0.8);
   entry=leg->AddEntry("h_cross_section_eta","2nd analysis","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.8);
   leg->Draw();
   canv_cross_eta_1->Modified();
   canv_cross_eta->cd();
  
// ------------>Primitives in pad: canv_cross_eta_2
   canv_cross_eta_2 = new TPad("canv_cross_eta_2", "_2",0.1,0.2,0.9,0.4);
   canv_cross_eta_2->Draw();
   canv_cross_eta_2->cd();
   canv_cross_eta_2->Range(-0.9536585,-0.5416667,0.997561,0.325);
   canv_cross_eta_2->SetFillColor(0);
   canv_cross_eta_2->SetBorderMode(0);
   canv_cross_eta_2->SetBorderSize(2);
   canv_cross_eta_2->SetTickx(1);
   canv_cross_eta_2->SetTicky(1);
   canv_cross_eta_2->SetLeftMargin(0.13);
   canv_cross_eta_2->SetRightMargin(0.05);
   canv_cross_eta_2->SetTopMargin(0);
   canv_cross_eta_2->SetBottomMargin(0.25);
   canv_cross_eta_2->SetFrameBorderMode(0);
   canv_cross_eta_2->SetFrameBorderMode(0);
   Double_t xAxis81[5] = {-0.7, -0.3, 0.1, 0.5, 0.9}; 
   
   TH2D *h_window_cross_ratio_eta = new TH2D("h_window_cross_ratio_eta","",4, xAxis81,10,-0.325,0.325);
   h_window_cross_ratio_eta->SetStats(0);
   h_window_cross_ratio_eta->GetXaxis()->SetTitle("#eta_{photon}");
   h_window_cross_ratio_eta->GetXaxis()->CenterTitle(true);
   h_window_cross_ratio_eta->GetXaxis()->SetNdivisions(507);
   h_window_cross_ratio_eta->GetXaxis()->SetLabelFont(42);
   h_window_cross_ratio_eta->GetXaxis()->SetLabelSize(0.09756097);
   h_window_cross_ratio_eta->GetXaxis()->SetTitleSize(0.1219512);
   h_window_cross_ratio_eta->GetXaxis()->SetTickLength(0.07);
   h_window_cross_ratio_eta->GetXaxis()->SetTitleOffset(0.8);
   h_window_cross_ratio_eta->GetXaxis()->SetTitleFont(42);
   h_window_cross_ratio_eta->GetYaxis()->SetTitle("rel. difference");
   h_window_cross_ratio_eta->GetYaxis()->CenterTitle(true);
   h_window_cross_ratio_eta->GetYaxis()->SetNdivisions(406);
   h_window_cross_ratio_eta->GetYaxis()->SetLabelFont(42);
   h_window_cross_ratio_eta->GetYaxis()->SetLabelSize(0.08533333);
   h_window_cross_ratio_eta->GetYaxis()->SetTitleSize(0.1066667);
   h_window_cross_ratio_eta->GetYaxis()->SetTitleOffset(0.5);
   h_window_cross_ratio_eta->GetYaxis()->SetTitleFont(42);
   h_window_cross_ratio_eta->Draw("");
   
   TF1 *Unity = new TF1("Unity","0",-100,500);
   Unity->SetFillColor(19);
   Unity->SetFillStyle(0);
   Unity->SetLineColor(32);
   Unity->SetLineWidth(1);
   Unity->GetXaxis()->SetTitleFont(42);
   Unity->Draw("SAME");
   Double_t xAxis82[5] = {-0.7, -0.3, 0.1, 0.5, 0.9}; 
   
   TH1D *h_cross_section_eta_ratio_1st_analysis = new TH1D("h_cross_section_eta_ratio_1st_analysis","det_cross_eta",4, xAxis82);
   h_cross_section_eta_ratio_1st_analysis->SetBinContent(1,0.7046816);
   h_cross_section_eta_ratio_1st_analysis->SetBinContent(2,0.5360924);
   h_cross_section_eta_ratio_1st_analysis->SetBinContent(3,0.5348233);
   h_cross_section_eta_ratio_1st_analysis->SetBinContent(4,0.3494303);
   h_cross_section_eta_ratio_1st_analysis->SetBinError(1,0.05119651);
   h_cross_section_eta_ratio_1st_analysis->SetBinError(2,0.06204886);
   h_cross_section_eta_ratio_1st_analysis->SetBinError(3,0.06870013);
   h_cross_section_eta_ratio_1st_analysis->SetBinError(4,0.1193476);
   h_cross_section_eta_ratio_1st_analysis->SetEntries(22626);

   ci = TColor::GetColor("#000000");
   h_cross_section_eta_ratio_1st_analysis->SetMarkerColor(ci);
   h_cross_section_eta_ratio_1st_analysis->SetMarkerStyle(21);
   h_cross_section_eta_ratio_1st_analysis->SetMarkerSize(0.8);
   h_cross_section_eta_ratio_1st_analysis->Draw("E X0 SAME");
   canv_cross_eta_2->Modified();
   canv_cross_eta->cd();
   canv_cross_eta->Modified();
   canv_cross_eta->cd();
   canv_cross_eta->SetSelected(canv_cross_eta);
}
