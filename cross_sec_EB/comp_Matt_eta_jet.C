{
//=========Macro generated from canvas: canv_cross_eta_jet/
//=========  (Tue Jun  7 19:22:41 2011) by ROOT version5.26/00c
   TCanvas *canv_cross_eta_jet = new TCanvas("canv_cross_eta_jet", "",1,1,550,876);
   canv_cross_eta_jet->SetHighLightColor(2);
   canv_cross_eta_jet->Range(0,0,1,1);
   canv_cross_eta_jet->SetFillColor(0);
   canv_cross_eta_jet->SetBorderMode(0);
   canv_cross_eta_jet->SetBorderSize(2);
   canv_cross_eta_jet->SetTopMargin(0.04761905);
   canv_cross_eta_jet->SetBottomMargin(0.05);
   canv_cross_eta_jet->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_eta_jet_1
   TPad *canv_cross_eta_jet_1 = new TPad("canv_cross_eta_jet_1", "_1",0.1,0.4,0.9,0.9);
   canv_cross_eta_jet_1->Draw();
   canv_cross_eta_jet_1->cd();
   canv_cross_eta_jet_1->Range(-2.023171,0.05,2.00122,4);
   canv_cross_eta_jet_1->SetFillColor(0);
   canv_cross_eta_jet_1->SetBorderMode(0);
   canv_cross_eta_jet_1->SetBorderSize(2);
   canv_cross_eta_jet_1->SetTickx(1);
   canv_cross_eta_jet_1->SetTicky(1);
   canv_cross_eta_jet_1->SetLeftMargin(0.13);
   canv_cross_eta_jet_1->SetRightMargin(0.05);
   canv_cross_eta_jet_1->SetTopMargin(0);
   canv_cross_eta_jet_1->SetBottomMargin(0);
   canv_cross_eta_jet_1->SetFrameBorderMode(0);
   canv_cross_eta_jet_1->SetFrameBorderMode(0);
   Double_t xAxis98[5] = {-1.5, -0.7, 0.1, 0.9, 1.8}; 
   
   TH2D *h_window_cross_eta_jet = new TH2D("h_window_cross_eta_jet","",4, xAxis98,10,0.05,4);
   h_window_cross_eta_jet->SetStats(0);
   h_window_cross_eta_jet->GetXaxis()->SetTitle("#eta_{jet}");
   h_window_cross_eta_jet->GetXaxis()->CenterTitle(true);
   h_window_cross_eta_jet->GetXaxis()->SetNdivisions(507);
   h_window_cross_eta_jet->GetXaxis()->SetLabelFont(42);
   h_window_cross_eta_jet->GetXaxis()->SetLabelSize(0.05073171);
   h_window_cross_eta_jet->GetXaxis()->SetTitleSize(0.06341463);
   h_window_cross_eta_jet->GetXaxis()->SetTitleFont(42);
   h_window_cross_eta_jet->GetYaxis()->SetTitle("d#sigma/d #eta_{jet} (pb)");
   h_window_cross_eta_jet->GetYaxis()->CenterTitle(true);
   h_window_cross_eta_jet->GetYaxis()->SetNdivisions(507);
   h_window_cross_eta_jet->GetYaxis()->SetLabelFont(42);
   h_window_cross_eta_jet->GetYaxis()->SetLabelSize(0.0416);
   h_window_cross_eta_jet->GetYaxis()->SetTitleSize(0.052);
   h_window_cross_eta_jet->GetYaxis()->SetTitleFont(42);
   h_window_cross_eta_jet->Draw("");
   Double_t xAxis99[5] = {-1.5, -0.7, 0.1, 0.9, 1.8}; 
   
   TH1D *h_cross_section_eta_jet = new TH1D("h_cross_section_eta_jet","det_cross_eta_jet",4, xAxis99);
   h_cross_section_eta_jet->SetBinContent(1,1.494573);
   h_cross_section_eta_jet->SetBinContent(2,2.736729);
   h_cross_section_eta_jet->SetBinContent(3,3.939846);
   h_cross_section_eta_jet->SetBinContent(4,3.485126);
   h_cross_section_eta_jet->SetBinError(1,0.1749494);
   h_cross_section_eta_jet->SetBinError(2,0.2609417);
   h_cross_section_eta_jet->SetBinError(3,0.353036);
   h_cross_section_eta_jet->SetBinError(4,0.3215534);
   h_cross_section_eta_jet->SetEntries(14141);
   h_cross_section_eta_jet->SetFillColor(41);
   h_cross_section_eta_jet->SetMarkerStyle(20);
   h_cross_section_eta_jet->SetMarkerSize(0.8);
   h_cross_section_eta_jet->Draw("E1 X0 SAME");
   Double_t xAxis100[5] = {-1.5, -0.7, 0.1, 0.9, 1.8}; 
   
   TH1D *h_cross_section_eta_jet_1st_analysis = new TH1D("h_cross_section_eta_jet_1st_analysis","det_cross_eta_jet",4, xAxis100);
   h_cross_section_eta_jet_1st_analysis->SetBinContent(1,1.494573);
   h_cross_section_eta_jet_1st_analysis->SetBinContent(2,2.736729);
   h_cross_section_eta_jet_1st_analysis->SetBinContent(3,3.939846);
   h_cross_section_eta_jet_1st_analysis->SetBinContent(4,3.485126);
   h_cross_section_eta_jet_1st_analysis->SetBinError(1,0.1749494);
   h_cross_section_eta_jet_1st_analysis->SetBinError(2,0.2609417);
   h_cross_section_eta_jet_1st_analysis->SetBinError(3,0.353036);
   h_cross_section_eta_jet_1st_analysis->SetBinError(4,0.3215534);
   h_cross_section_eta_jet_1st_analysis->SetEntries(14141);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   h_cross_section_eta_jet_1st_analysis->SetLineColor(ci);

   ci = TColor::GetColor("#000000");
   h_cross_section_eta_jet_1st_analysis->SetMarkerColor(ci);
   h_cross_section_eta_jet_1st_analysis->SetMarkerStyle(21);
   h_cross_section_eta_jet_1st_analysis->SetMarkerSize(0.8);
   h_cross_section_eta_jet_1st_analysis->Draw("P E1 X0 SAME");
   
   TLegend *leg = new TLegend(0.37,0.059,0.77,0.358,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_eta_jet_1st_analysis","Matthew","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(0.8);
   entry=leg->AddEntry("h_cross_section_eta_jet","Oleg & Nataliia","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.8);
   leg->Draw();
   canv_cross_eta_jet_1->Modified();
   canv_cross_eta_jet->cd();
  
// ------------>Primitives in pad: canv_cross_eta_jet_2
   canv_cross_eta_jet_2 = new TPad("canv_cross_eta_jet_2", "_2",0.1,0.2,0.9,0.4);
   canv_cross_eta_jet_2->Draw();
   canv_cross_eta_jet_2->cd();
   canv_cross_eta_jet_2->Range(-2.023171,-0.7083333,2.00122,0.425);
   canv_cross_eta_jet_2->SetFillColor(0);
   canv_cross_eta_jet_2->SetBorderMode(0);
   canv_cross_eta_jet_2->SetBorderSize(2);
   canv_cross_eta_jet_2->SetTickx(1);
   canv_cross_eta_jet_2->SetTicky(1);
   canv_cross_eta_jet_2->SetLeftMargin(0.13);
   canv_cross_eta_jet_2->SetRightMargin(0.05);
   canv_cross_eta_jet_2->SetTopMargin(0);
   canv_cross_eta_jet_2->SetBottomMargin(0.25);
   canv_cross_eta_jet_2->SetFrameBorderMode(0);
   canv_cross_eta_jet_2->SetFrameBorderMode(0);
   Double_t xAxis101[5] = {-1.5, -0.7, 0.1, 0.9, 1.8}; 
   
   TH2D *h_window_cross_ratio_eta_jet = new TH2D("h_window_cross_ratio_eta_jet","",4, xAxis101,10,-0.425,0.425);
   h_window_cross_ratio_eta_jet->SetStats(0);
   h_window_cross_ratio_eta_jet->GetXaxis()->SetTitle("#eta_{jet}");
   h_window_cross_ratio_eta_jet->GetXaxis()->CenterTitle(true);
   h_window_cross_ratio_eta_jet->GetXaxis()->SetNdivisions(507);
   h_window_cross_ratio_eta_jet->GetXaxis()->SetLabelFont(42);
   h_window_cross_ratio_eta_jet->GetXaxis()->SetLabelSize(0.09756097);
   h_window_cross_ratio_eta_jet->GetXaxis()->SetTitleSize(0.1219512);
   h_window_cross_ratio_eta_jet->GetXaxis()->SetTickLength(0.07);
   h_window_cross_ratio_eta_jet->GetXaxis()->SetTitleOffset(0.8);
   h_window_cross_ratio_eta_jet->GetXaxis()->SetTitleFont(42);
   h_window_cross_ratio_eta_jet->GetYaxis()->SetTitle("rel. difference");
   h_window_cross_ratio_eta_jet->GetYaxis()->CenterTitle(true);
   h_window_cross_ratio_eta_jet->GetYaxis()->SetNdivisions(406);
   h_window_cross_ratio_eta_jet->GetYaxis()->SetLabelFont(42);
   h_window_cross_ratio_eta_jet->GetYaxis()->SetLabelSize(0.08533333);
   h_window_cross_ratio_eta_jet->GetYaxis()->SetTitleSize(0.1066667);
   h_window_cross_ratio_eta_jet->GetYaxis()->SetTitleOffset(0.5);
   h_window_cross_ratio_eta_jet->GetYaxis()->SetTitleFont(42);
   h_window_cross_ratio_eta_jet->Draw("");
   
   TF1 *Unity = new TF1("Unity","0",-100,500);
   Unity->SetFillColor(19);
   Unity->SetFillStyle(0);
   Unity->SetLineColor(32);
   Unity->SetLineWidth(1);
   Unity->GetXaxis()->SetTitleFont(42);
   Unity->Draw("SAME");
   Double_t xAxis102[5] = {-1.5, -0.7, 0.1, 0.9, 1.8}; 
   
   TH1D *h_cross_section_eta_jet_ratio_1st_analysis = new TH1D("h_cross_section_eta_jet_ratio_1st_analysis","det_cross_eta_jet",4, xAxis102);
   h_cross_section_eta_jet_ratio_1st_analysis->SetBinError(1,0.1655429);
   h_cross_section_eta_jet_ratio_1st_analysis->SetBinError(2,0.1348425);
   h_cross_section_eta_jet_ratio_1st_analysis->SetBinError(3,0.1267228);
   h_cross_section_eta_jet_ratio_1st_analysis->SetBinError(4,0.1304817);
   h_cross_section_eta_jet_ratio_1st_analysis->SetEntries(14145);

   ci = TColor::GetColor("#000000");
   h_cross_section_eta_jet_ratio_1st_analysis->SetMarkerColor(ci);
   h_cross_section_eta_jet_ratio_1st_analysis->SetMarkerStyle(21);
   h_cross_section_eta_jet_ratio_1st_analysis->SetMarkerSize(0.8);
   h_cross_section_eta_jet_ratio_1st_analysis->Draw("E X0 SAME");
   canv_cross_eta_jet_2->Modified();
   canv_cross_eta_jet->cd();
   canv_cross_eta_jet->Modified();
   canv_cross_eta_jet->cd();
   canv_cross_eta_jet->SetSelected(canv_cross_eta_jet);
}
