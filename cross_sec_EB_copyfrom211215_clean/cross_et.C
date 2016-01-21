{
//=========Macro generated from canvas: canv_cross_et/
//=========  (Mon Sep 14 17:32:38 2015) by ROOT version5.34/00
   TCanvas *canv_cross_et = new TCanvas("canv_cross_et", "",0,0,1200,1000);
   canv_cross_et->SetHighLightColor(2);
   canv_cross_et->Range(0,0,1,1);
   canv_cross_et->SetFillColor(0);
   canv_cross_et->SetBorderMode(0);
   canv_cross_et->SetBorderSize(2);
   canv_cross_et->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_et_1
   TPad *canv_cross_et_1 = new TPad("canv_cross_et_1", "canv_cross_et_1",0.01,0.01,0.99,0.99);
   canv_cross_et_1->Draw();
   canv_cross_et_1->cd();
   canv_cross_et_1->Range(1.9375,-0.8616438,15.6875,4.480822);
   canv_cross_et_1->SetFillColor(0);
   canv_cross_et_1->SetBorderMode(0);
   canv_cross_et_1->SetBorderSize(2);
   canv_cross_et_1->SetTickx(1);
   canv_cross_et_1->SetTicky(1);
   canv_cross_et_1->SetLeftMargin(0.15);
   canv_cross_et_1->SetRightMargin(0.05);
   canv_cross_et_1->SetBottomMargin(0.18);
   canv_cross_et_1->SetFrameBorderMode(0);
   canv_cross_et_1->SetFrameBorderMode(0);
   Double_t xAxis1[5] = {4, 6, 8, 10, 15}; 
   
   TH2D *h_window_cross_et = new TH2D("h_window_cross_et","",4, xAxis1,10,0.1,4);
   h_window_cross_et->SetStats(0);
   h_window_cross_et->GetXaxis()->SetTitle("E_{T}^{#gamma} (GeV)");
   h_window_cross_et->GetXaxis()->SetNdivisions(507);
   h_window_cross_et->GetXaxis()->SetLabelFont(22);
   h_window_cross_et->GetXaxis()->SetLabelSize(0.05424658);
   h_window_cross_et->GetXaxis()->SetTitleSize(0.06027398);
   h_window_cross_et->GetXaxis()->SetTitleOffset(1.02);
   h_window_cross_et->GetXaxis()->SetTitleFont(22);
   h_window_cross_et->GetYaxis()->SetTitle("d#sigma/dE_{T}^{#gamma} (pb/GeV)");
   h_window_cross_et->GetYaxis()->SetNdivisions(507);
   h_window_cross_et->GetYaxis()->SetLabelFont(22);
   h_window_cross_et->GetYaxis()->SetLabelOffset(0.016);
   h_window_cross_et->GetYaxis()->SetLabelSize(0.05424658);
   h_window_cross_et->GetYaxis()->SetTitleSize(0.06027398);
   h_window_cross_et->GetYaxis()->SetTitleOffset(0.94);
   h_window_cross_et->GetYaxis()->SetTitleFont(22);
   h_window_cross_et->Draw("");
   Double_t xAxis2[5] = {4, 6, 8, 10, 15}; 
   
   TH1D *h_cross_section_et_stat_fit_err = new TH1D("h_cross_section_et_stat_fit_err","det_cross_et",4, xAxis2);
   h_cross_section_et_stat_fit_err->SetBinContent(1,2.490761);
   h_cross_section_et_stat_fit_err->SetBinContent(2,1.347578);
   h_cross_section_et_stat_fit_err->SetBinContent(3,0.6555723);
   h_cross_section_et_stat_fit_err->SetBinContent(4,0.2518526);
   h_cross_section_et_stat_fit_err->SetBinError(1,0.1884532);
   h_cross_section_et_stat_fit_err->SetBinError(2,0.1035082);
   h_cross_section_et_stat_fit_err->SetBinError(3,0.07354144);
   h_cross_section_et_stat_fit_err->SetBinError(4,0.02602027);
   h_cross_section_et_stat_fit_err->SetEntries(14095);
   h_cross_section_et_stat_fit_err->SetFillColor(43);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   h_cross_section_et_stat_fit_err->SetLineColor(ci);
   h_cross_section_et_stat_fit_err->SetLineWidth(2);
   h_cross_section_et_stat_fit_err->SetMarkerStyle(20);
   h_cross_section_et_stat_fit_err->GetXaxis()->SetLabelFont(42);
   h_cross_section_et_stat_fit_err->GetXaxis()->SetLabelSize(0.035);
   h_cross_section_et_stat_fit_err->GetXaxis()->SetTitleSize(0.035);
   h_cross_section_et_stat_fit_err->GetXaxis()->SetTitleFont(42);
   h_cross_section_et_stat_fit_err->GetYaxis()->SetLabelFont(42);
   h_cross_section_et_stat_fit_err->GetYaxis()->SetLabelSize(0.035);
   h_cross_section_et_stat_fit_err->GetYaxis()->SetTitleSize(0.035);
   h_cross_section_et_stat_fit_err->GetYaxis()->SetTitleFont(42);
   h_cross_section_et_stat_fit_err->GetZaxis()->SetLabelFont(42);
   h_cross_section_et_stat_fit_err->GetZaxis()->SetLabelSize(0.035);
   h_cross_section_et_stat_fit_err->GetZaxis()->SetTitleSize(0.035);
   h_cross_section_et_stat_fit_err->GetZaxis()->SetTitleFont(42);
   h_cross_section_et_stat_fit_err->Draw("E1 X0 SAME");
   Double_t xAxis3[5] = {4, 6, 8, 10, 15}; 
   
   TH2D *h_window_cross_et__1 = new TH2D("h_window_cross_et__1","",4, xAxis3,10,0.1,4);
   h_window_cross_et__1->SetDirectory(0);
   h_window_cross_et__1->SetStats(0);
   h_window_cross_et__1->GetXaxis()->SetTitle("E_{T}^{#gamma} (GeV)");
   h_window_cross_et__1->GetXaxis()->SetNdivisions(507);
   h_window_cross_et__1->GetXaxis()->SetLabelFont(22);
   h_window_cross_et__1->GetXaxis()->SetLabelSize(0.05424658);
   h_window_cross_et__1->GetXaxis()->SetTitleSize(0.06027398);
   h_window_cross_et__1->GetXaxis()->SetTitleOffset(1.02);
   h_window_cross_et__1->GetXaxis()->SetTitleFont(22);
   h_window_cross_et__1->GetYaxis()->SetTitle("d#sigma/dE_{T}^{#gamma} (pb/GeV)");
   h_window_cross_et__1->GetYaxis()->SetNdivisions(507);
   h_window_cross_et__1->GetYaxis()->SetLabelFont(22);
   h_window_cross_et__1->GetYaxis()->SetLabelOffset(0.016);
   h_window_cross_et__1->GetYaxis()->SetLabelSize(0.05424658);
   h_window_cross_et__1->GetYaxis()->SetTitleSize(0.06027398);
   h_window_cross_et__1->GetYaxis()->SetTitleOffset(0.94);
   h_window_cross_et__1->GetYaxis()->SetTitleFont(22);
   h_window_cross_et__1->Draw("sameaxis");
   
   TLegend *leg = new TLegend(0.5,0.6,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(22);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_et","ZEUS 326 pb^{-1}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();
   canv_cross_et_1->Modified();
   canv_cross_et->cd();
   TText *text = new TText(0.45,0.95,"ZEUS");
   text->SetTextFont(22);
   text->SetTextSize(0.07);
   text->Draw();
   canv_cross_et->Modified();
   canv_cross_et->cd();
   canv_cross_et->SetSelected(canv_cross_et);
}
