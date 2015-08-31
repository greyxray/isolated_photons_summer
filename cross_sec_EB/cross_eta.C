{
//=========Macro generated from canvas: canv_cross_eta/
//=========  (Wed Aug 12 00:25:06 2015) by ROOT version5.34/00
   TCanvas *canv_cross_eta = new TCanvas("canv_cross_eta", "",0,0,1200,1000);
   canv_cross_eta->SetHighLightColor(2);
   canv_cross_eta->Range(0,0,1,1);
   canv_cross_eta->SetFillColor(0);
   canv_cross_eta->SetBorderMode(0);
   canv_cross_eta->SetBorderSize(2);
   canv_cross_eta->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_eta_1
   TPad *canv_cross_eta_1 = new TPad("canv_cross_eta_1", "canv_cross_eta_1",0.01,0.01,0.99,0.99);
   canv_cross_eta_1->Draw();
   canv_cross_eta_1->cd();
   canv_cross_eta_1->Range(-1,-4.499315,1,20.77466);
   canv_cross_eta_1->SetFillColor(0);
   canv_cross_eta_1->SetBorderMode(0);
   canv_cross_eta_1->SetBorderSize(2);
   canv_cross_eta_1->SetTickx(1);
   canv_cross_eta_1->SetTicky(1);
   canv_cross_eta_1->SetLeftMargin(0.15);
   canv_cross_eta_1->SetRightMargin(0.05);
   canv_cross_eta_1->SetBottomMargin(0.18);
   canv_cross_eta_1->SetFrameBorderMode(0);
   canv_cross_eta_1->SetFrameBorderMode(0);
   Double_t xAxis4[5] = {-0.7, -0.3, 0.1, 0.5, 0.9}; 
   
   TH2D *h_window_cross_eta = new TH2D("h_window_cross_eta","",4, xAxis4,10,0.05,18.5);
   h_window_cross_eta->SetStats(0);
   h_window_cross_eta->GetXaxis()->SetTitle("#eta^{#gamma}");
   h_window_cross_eta->GetXaxis()->SetNdivisions(507);
   h_window_cross_eta->GetXaxis()->SetLabelFont(22);
   h_window_cross_eta->GetXaxis()->SetLabelSize(0.05424658);
   h_window_cross_eta->GetXaxis()->SetTitleSize(0.06027398);
   h_window_cross_eta->GetXaxis()->SetTitleOffset(1.02);
   h_window_cross_eta->GetXaxis()->SetTitleFont(22);
   h_window_cross_eta->GetYaxis()->SetTitle("d#sigma/d#eta^{#gamma} (pb)");
   h_window_cross_eta->GetYaxis()->SetNdivisions(507);
   h_window_cross_eta->GetYaxis()->SetLabelFont(22);
   h_window_cross_eta->GetYaxis()->SetLabelOffset(0.016);
   h_window_cross_eta->GetYaxis()->SetLabelSize(0.05424658);
   h_window_cross_eta->GetYaxis()->SetTitleSize(0.06027398);
   h_window_cross_eta->GetYaxis()->SetTitleOffset(0.94);
   h_window_cross_eta->GetYaxis()->SetTitleFont(22);
   h_window_cross_eta->Draw("");
   Double_t xAxis5[5] = {-0.7, -0.3, 0.1, 0.5, 0.9}; 
   
   TH1D *h_cross_section_eta_stat_fit_err = new TH1D("h_cross_section_eta_stat_fit_err","det_cross_eta",4, xAxis5);
   h_cross_section_eta_stat_fit_err->SetBinContent(1,7.833415);
   h_cross_section_eta_stat_fit_err->SetBinContent(2,7.112428);
   h_cross_section_eta_stat_fit_err->SetBinContent(3,5.748288);
   h_cross_section_eta_stat_fit_err->SetBinContent(4,5.371657);
   h_cross_section_eta_stat_fit_err->SetBinError(1,0.5667733);
   h_cross_section_eta_stat_fit_err->SetBinError(2,0.5751059);
   h_cross_section_eta_stat_fit_err->SetBinError(3,0.6316072);
   h_cross_section_eta_stat_fit_err->SetBinError(4,0.5444783);
   h_cross_section_eta_stat_fit_err->SetEntries(13883);
   h_cross_section_eta_stat_fit_err->SetFillColor(43);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   h_cross_section_eta_stat_fit_err->SetLineColor(ci);
   h_cross_section_eta_stat_fit_err->SetLineWidth(2);
   h_cross_section_eta_stat_fit_err->SetMarkerStyle(20);
   h_cross_section_eta_stat_fit_err->GetXaxis()->SetLabelFont(42);
   h_cross_section_eta_stat_fit_err->GetXaxis()->SetLabelSize(0.035);
   h_cross_section_eta_stat_fit_err->GetXaxis()->SetTitleSize(0.035);
   h_cross_section_eta_stat_fit_err->GetXaxis()->SetTitleFont(42);
   h_cross_section_eta_stat_fit_err->GetYaxis()->SetLabelFont(42);
   h_cross_section_eta_stat_fit_err->GetYaxis()->SetLabelSize(0.035);
   h_cross_section_eta_stat_fit_err->GetYaxis()->SetTitleSize(0.035);
   h_cross_section_eta_stat_fit_err->GetYaxis()->SetTitleFont(42);
   h_cross_section_eta_stat_fit_err->GetZaxis()->SetLabelFont(42);
   h_cross_section_eta_stat_fit_err->GetZaxis()->SetLabelSize(0.035);
   h_cross_section_eta_stat_fit_err->GetZaxis()->SetTitleSize(0.035);
   h_cross_section_eta_stat_fit_err->GetZaxis()->SetTitleFont(42);
   h_cross_section_eta_stat_fit_err->Draw("E1 X0 SAME");
   Double_t xAxis6[5] = {-0.7, -0.3, 0.1, 0.5, 0.9}; 
   
   TH2D *h_window_cross_eta__2 = new TH2D("h_window_cross_eta__2","",4, xAxis6,10,0.05,18.5);
   h_window_cross_eta__2->SetDirectory(0);
   h_window_cross_eta__2->SetStats(0);
   h_window_cross_eta__2->GetXaxis()->SetTitle("#eta^{#gamma}");
   h_window_cross_eta__2->GetXaxis()->SetNdivisions(507);
   h_window_cross_eta__2->GetXaxis()->SetLabelFont(22);
   h_window_cross_eta__2->GetXaxis()->SetLabelSize(0.05424658);
   h_window_cross_eta__2->GetXaxis()->SetTitleSize(0.06027398);
   h_window_cross_eta__2->GetXaxis()->SetTitleOffset(1.02);
   h_window_cross_eta__2->GetXaxis()->SetTitleFont(22);
   h_window_cross_eta__2->GetYaxis()->SetTitle("d#sigma/d#eta^{#gamma} (pb)");
   h_window_cross_eta__2->GetYaxis()->SetNdivisions(507);
   h_window_cross_eta__2->GetYaxis()->SetLabelFont(22);
   h_window_cross_eta__2->GetYaxis()->SetLabelOffset(0.016);
   h_window_cross_eta__2->GetYaxis()->SetLabelSize(0.05424658);
   h_window_cross_eta__2->GetYaxis()->SetTitleSize(0.06027398);
   h_window_cross_eta__2->GetYaxis()->SetTitleOffset(0.94);
   h_window_cross_eta__2->GetYaxis()->SetTitleFont(22);
   h_window_cross_eta__2->Draw("sameaxis");
   
   TLegend *leg = new TLegend(0.5,0.6,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(22);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_eta","ZEUS 326 pb^{-1}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();
   canv_cross_eta_1->Modified();
   canv_cross_eta->cd();
   TText *text = new TText(0.45,0.95,"ZEUS");
   text->SetTextFont(22);
   text->SetTextSize(0.07);
   text->Draw();
   canv_cross_eta->Modified();
   canv_cross_eta->cd();
   canv_cross_eta->SetSelected(canv_cross_eta);
}
