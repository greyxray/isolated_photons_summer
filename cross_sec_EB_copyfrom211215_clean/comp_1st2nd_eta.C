{
//=========Macro generated from canvas: canv_cross_eta/
//=========  (Mon Sep 14 17:32:39 2015) by ROOT version5.34/00
   TCanvas *canv_cross_eta = new TCanvas("canv_cross_eta", "",1,1,1200,976);
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
   Double_t xAxis22[5] = {-0.7, -0.3, 0.1, 0.5, 0.9}; 
   
   TH2D *h_window_cross_eta = new TH2D("h_window_cross_eta","",4, xAxis22,10,0.05,18.5);
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
   Double_t xAxis23[5] = {-0.7, -0.3, 0.1, 0.5, 0.9}; 
   
   TH1D *h_cross_section_eta = new TH1D("h_cross_section_eta","det_cross_eta",4, xAxis23);
   h_cross_section_eta->SetBinContent(1,7.56376);
   h_cross_section_eta->SetBinContent(2,6.7092);
   h_cross_section_eta->SetBinContent(3,5.833198);
   h_cross_section_eta->SetBinContent(4,5.155802);
   h_cross_section_eta->SetBinError(1,0.5928052);
   h_cross_section_eta->SetBinError(2,0.5351351);
   h_cross_section_eta->SetBinError(3,0.5522194);
   h_cross_section_eta->SetBinError(4,0.5284563);
   h_cross_section_eta->SetEntries(14099);
   h_cross_section_eta->SetFillColor(41);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   h_cross_section_eta->SetLineColor(ci);
   h_cross_section_eta->SetLineWidth(2);
   h_cross_section_eta->SetMarkerStyle(20);
   h_cross_section_eta->GetXaxis()->SetLabelFont(42);
   h_cross_section_eta->GetXaxis()->SetLabelSize(0.035);
   h_cross_section_eta->GetXaxis()->SetTitleSize(0.035);
   h_cross_section_eta->GetXaxis()->SetTitleFont(42);
   h_cross_section_eta->GetYaxis()->SetLabelFont(42);
   h_cross_section_eta->GetYaxis()->SetLabelSize(0.035);
   h_cross_section_eta->GetYaxis()->SetTitleSize(0.035);
   h_cross_section_eta->GetYaxis()->SetTitleFont(42);
   h_cross_section_eta->GetZaxis()->SetLabelFont(42);
   h_cross_section_eta->GetZaxis()->SetLabelSize(0.035);
   h_cross_section_eta->GetZaxis()->SetTitleSize(0.035);
   h_cross_section_eta->GetZaxis()->SetTitleFont(42);
   h_cross_section_eta->Draw("E1 X0 SAME");
   Double_t xAxis24[5] = {-0.7, -0.3, 0.1, 0.5, 0.9}; 
   
   TH1D *h_cross_section_eta_1st_analysis = new TH1D("h_cross_section_eta_1st_analysis","det_cross_eta",4, xAxis24);
   h_cross_section_eta_1st_analysis->SetBinContent(1,7.26298);
   h_cross_section_eta_1st_analysis->SetBinContent(2,6.36946);
   h_cross_section_eta_1st_analysis->SetBinContent(3,5.52583);
   h_cross_section_eta_1st_analysis->SetBinContent(4,5.03845);
   h_cross_section_eta_1st_analysis->SetBinError(1,0.606495);
   h_cross_section_eta_1st_analysis->SetBinError(2,0.534726);
   h_cross_section_eta_1st_analysis->SetBinError(3,0.543494);
   h_cross_section_eta_1st_analysis->SetBinError(4,0.528302);
   h_cross_section_eta_1st_analysis->SetEntries(14099);

   ci = TColor::GetColor("#0000ff");
   h_cross_section_eta_1st_analysis->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   h_cross_section_eta_1st_analysis->SetMarkerColor(ci);
   h_cross_section_eta_1st_analysis->SetMarkerStyle(24);
   h_cross_section_eta_1st_analysis->GetXaxis()->SetLabelFont(42);
   h_cross_section_eta_1st_analysis->GetXaxis()->SetLabelSize(0.035);
   h_cross_section_eta_1st_analysis->GetXaxis()->SetTitleSize(0.035);
   h_cross_section_eta_1st_analysis->GetXaxis()->SetTitleFont(42);
   h_cross_section_eta_1st_analysis->GetYaxis()->SetLabelFont(42);
   h_cross_section_eta_1st_analysis->GetYaxis()->SetLabelSize(0.035);
   h_cross_section_eta_1st_analysis->GetYaxis()->SetTitleSize(0.035);
   h_cross_section_eta_1st_analysis->GetYaxis()->SetTitleFont(42);
   h_cross_section_eta_1st_analysis->GetZaxis()->SetLabelFont(42);
   h_cross_section_eta_1st_analysis->GetZaxis()->SetLabelSize(0.035);
   h_cross_section_eta_1st_analysis->GetZaxis()->SetTitleSize(0.035);
   h_cross_section_eta_1st_analysis->GetZaxis()->SetTitleFont(42);
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

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("h_cross_section_eta","2nd analysis","p");
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
