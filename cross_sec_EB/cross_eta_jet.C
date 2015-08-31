{
//=========Macro generated from canvas: canv_cross_eta_jet/
//=========  (Wed Aug 12 00:25:06 2015) by ROOT version5.34/00
   TCanvas *canv_cross_eta_jet = new TCanvas("canv_cross_eta_jet", "",0,0,1200,1000);
   canv_cross_eta_jet->SetHighLightColor(2);
   canv_cross_eta_jet->Range(0,0,1,1);
   canv_cross_eta_jet->SetFillColor(0);
   canv_cross_eta_jet->SetBorderMode(0);
   canv_cross_eta_jet->SetBorderSize(2);
   canv_cross_eta_jet->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_eta_jet_1
   TPad *canv_cross_eta_jet_1 = new TPad("canv_cross_eta_jet_1", "canv_cross_eta_jet_1",0.01,0.01,0.99,0.99);
   canv_cross_eta_jet_1->Draw();
   canv_cross_eta_jet_1->cd();
   canv_cross_eta_jet_1->Range(-2.11875,-2.65,2.00625,12.35);
   canv_cross_eta_jet_1->SetFillColor(0);
   canv_cross_eta_jet_1->SetBorderMode(0);
   canv_cross_eta_jet_1->SetBorderSize(2);
   canv_cross_eta_jet_1->SetTickx(1);
   canv_cross_eta_jet_1->SetTicky(1);
   canv_cross_eta_jet_1->SetLeftMargin(0.15);
   canv_cross_eta_jet_1->SetRightMargin(0.05);
   canv_cross_eta_jet_1->SetBottomMargin(0.18);
   canv_cross_eta_jet_1->SetFrameBorderMode(0);
   canv_cross_eta_jet_1->SetFrameBorderMode(0);
   Double_t xAxis16[5] = {-1.5, -0.7, 0.1, 0.9, 1.8}; 
   
   TH2D *h_window_cross_eta_jet = new TH2D("h_window_cross_eta_jet","",4, xAxis16,10,0.05,11);
   h_window_cross_eta_jet->SetStats(0);
   h_window_cross_eta_jet->GetXaxis()->SetTitle("#eta^{jet}");
   h_window_cross_eta_jet->GetXaxis()->SetNdivisions(507);
   h_window_cross_eta_jet->GetXaxis()->SetLabelFont(22);
   h_window_cross_eta_jet->GetXaxis()->SetLabelSize(0.05424658);
   h_window_cross_eta_jet->GetXaxis()->SetTitleSize(0.06027398);
   h_window_cross_eta_jet->GetXaxis()->SetTitleOffset(1.02);
   h_window_cross_eta_jet->GetXaxis()->SetTitleFont(22);
   h_window_cross_eta_jet->GetYaxis()->SetTitle("d#sigma/d#eta^{jet} (pb)");
   h_window_cross_eta_jet->GetYaxis()->SetNdivisions(507);
   h_window_cross_eta_jet->GetYaxis()->SetLabelFont(22);
   h_window_cross_eta_jet->GetYaxis()->SetLabelOffset(0.016);
   h_window_cross_eta_jet->GetYaxis()->SetLabelSize(0.05424658);
   h_window_cross_eta_jet->GetYaxis()->SetTitleSize(0.06027398);
   h_window_cross_eta_jet->GetYaxis()->SetTitleOffset(0.94);
   h_window_cross_eta_jet->GetYaxis()->SetTitleFont(22);
   h_window_cross_eta_jet->Draw("");
   Double_t xAxis17[5] = {-1.5, -0.7, 0.1, 0.9, 1.8}; 
   
   TH1D *h_cross_section_eta_jet_stat_fit_err = new TH1D("h_cross_section_eta_jet_stat_fit_err","det_cross_eta_jet",4, xAxis17);
   h_cross_section_eta_jet_stat_fit_err->SetBinContent(1,1.692533);
   h_cross_section_eta_jet_stat_fit_err->SetBinContent(2,3.114765);
   h_cross_section_eta_jet_stat_fit_err->SetBinContent(3,4.091523);
   h_cross_section_eta_jet_stat_fit_err->SetBinContent(4,3.524909);
   h_cross_section_eta_jet_stat_fit_err->SetBinError(1,0.1739141);
   h_cross_section_eta_jet_stat_fit_err->SetBinError(2,0.2534561);
   h_cross_section_eta_jet_stat_fit_err->SetBinError(3,0.3427997);
   h_cross_section_eta_jet_stat_fit_err->SetBinError(4,0.3019802);
   h_cross_section_eta_jet_stat_fit_err->SetEntries(13883);
   h_cross_section_eta_jet_stat_fit_err->SetFillColor(43);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   h_cross_section_eta_jet_stat_fit_err->SetLineColor(ci);
   h_cross_section_eta_jet_stat_fit_err->SetLineWidth(2);
   h_cross_section_eta_jet_stat_fit_err->SetMarkerStyle(20);
   h_cross_section_eta_jet_stat_fit_err->GetXaxis()->SetLabelFont(42);
   h_cross_section_eta_jet_stat_fit_err->GetXaxis()->SetLabelSize(0.035);
   h_cross_section_eta_jet_stat_fit_err->GetXaxis()->SetTitleSize(0.035);
   h_cross_section_eta_jet_stat_fit_err->GetXaxis()->SetTitleFont(42);
   h_cross_section_eta_jet_stat_fit_err->GetYaxis()->SetLabelFont(42);
   h_cross_section_eta_jet_stat_fit_err->GetYaxis()->SetLabelSize(0.035);
   h_cross_section_eta_jet_stat_fit_err->GetYaxis()->SetTitleSize(0.035);
   h_cross_section_eta_jet_stat_fit_err->GetYaxis()->SetTitleFont(42);
   h_cross_section_eta_jet_stat_fit_err->GetZaxis()->SetLabelFont(42);
   h_cross_section_eta_jet_stat_fit_err->GetZaxis()->SetLabelSize(0.035);
   h_cross_section_eta_jet_stat_fit_err->GetZaxis()->SetTitleSize(0.035);
   h_cross_section_eta_jet_stat_fit_err->GetZaxis()->SetTitleFont(42);
   h_cross_section_eta_jet_stat_fit_err->Draw("E1 X0 SAME");
   Double_t xAxis18[5] = {-1.5, -0.7, 0.1, 0.9, 1.8}; 
   
   TH2D *h_window_cross_eta_jet__6 = new TH2D("h_window_cross_eta_jet__6","",4, xAxis18,10,0.05,11);
   h_window_cross_eta_jet__6->SetDirectory(0);
   h_window_cross_eta_jet__6->SetStats(0);
   h_window_cross_eta_jet__6->GetXaxis()->SetTitle("#eta^{jet}");
   h_window_cross_eta_jet__6->GetXaxis()->SetNdivisions(507);
   h_window_cross_eta_jet__6->GetXaxis()->SetLabelFont(22);
   h_window_cross_eta_jet__6->GetXaxis()->SetLabelSize(0.05424658);
   h_window_cross_eta_jet__6->GetXaxis()->SetTitleSize(0.06027398);
   h_window_cross_eta_jet__6->GetXaxis()->SetTitleOffset(1.02);
   h_window_cross_eta_jet__6->GetXaxis()->SetTitleFont(22);
   h_window_cross_eta_jet__6->GetYaxis()->SetTitle("d#sigma/d#eta^{jet} (pb)");
   h_window_cross_eta_jet__6->GetYaxis()->SetNdivisions(507);
   h_window_cross_eta_jet__6->GetYaxis()->SetLabelFont(22);
   h_window_cross_eta_jet__6->GetYaxis()->SetLabelOffset(0.016);
   h_window_cross_eta_jet__6->GetYaxis()->SetLabelSize(0.05424658);
   h_window_cross_eta_jet__6->GetYaxis()->SetTitleSize(0.06027398);
   h_window_cross_eta_jet__6->GetYaxis()->SetTitleOffset(0.94);
   h_window_cross_eta_jet__6->GetYaxis()->SetTitleFont(22);
   h_window_cross_eta_jet__6->Draw("sameaxis");
   
   TLegend *leg = new TLegend(0.47,0.6,0.87,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(22);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_eta_jet","ZEUS 326 pb^{-1}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();
   canv_cross_eta_jet_1->Modified();
   canv_cross_eta_jet->cd();
   TText *text = new TText(0.45,0.95,"ZEUS");
   text->SetTextFont(22);
   text->SetTextSize(0.07);
   text->Draw();
   canv_cross_eta_jet->Modified();
   canv_cross_eta_jet->cd();
   canv_cross_eta_jet->SetSelected(canv_cross_eta_jet);
}
