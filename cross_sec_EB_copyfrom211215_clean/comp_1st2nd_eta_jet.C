{
//=========Macro generated from canvas: canv_cross_eta_jet/
//=========  (Mon Sep 14 17:32:40 2015) by ROOT version5.34/00
   TCanvas *canv_cross_eta_jet = new TCanvas("canv_cross_eta_jet", "",1,1,1200,976);
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
   Double_t xAxis34[5] = {-1.5, -0.7, 0.1, 0.9, 1.8}; 
   
   TH2D *h_window_cross_eta_jet = new TH2D("h_window_cross_eta_jet","",4, xAxis34,10,0.05,11);
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
   Double_t xAxis35[5] = {-1.5, -0.7, 0.1, 0.9, 1.8}; 
   
   TH1D *h_cross_section_eta_jet = new TH1D("h_cross_section_eta_jet","det_cross_eta_jet",4, xAxis35);
   h_cross_section_eta_jet->SetBinContent(1,1.529209);
   h_cross_section_eta_jet->SetBinContent(2,2.844649);
   h_cross_section_eta_jet->SetBinContent(3,3.910317);
   h_cross_section_eta_jet->SetBinContent(4,3.57312);
   h_cross_section_eta_jet->SetBinError(1,0.1725428);
   h_cross_section_eta_jet->SetBinError(2,0.2464578);
   h_cross_section_eta_jet->SetBinError(3,0.3293549);
   h_cross_section_eta_jet->SetBinError(4,0.2905448);
   h_cross_section_eta_jet->SetEntries(14099);
   h_cross_section_eta_jet->SetFillColor(41);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   h_cross_section_eta_jet->SetLineColor(ci);
   h_cross_section_eta_jet->SetLineWidth(2);
   h_cross_section_eta_jet->SetMarkerStyle(20);
   h_cross_section_eta_jet->GetXaxis()->SetLabelFont(42);
   h_cross_section_eta_jet->GetXaxis()->SetLabelSize(0.035);
   h_cross_section_eta_jet->GetXaxis()->SetTitleSize(0.035);
   h_cross_section_eta_jet->GetXaxis()->SetTitleFont(42);
   h_cross_section_eta_jet->GetYaxis()->SetLabelFont(42);
   h_cross_section_eta_jet->GetYaxis()->SetLabelSize(0.035);
   h_cross_section_eta_jet->GetYaxis()->SetTitleSize(0.035);
   h_cross_section_eta_jet->GetYaxis()->SetTitleFont(42);
   h_cross_section_eta_jet->GetZaxis()->SetLabelFont(42);
   h_cross_section_eta_jet->GetZaxis()->SetLabelSize(0.035);
   h_cross_section_eta_jet->GetZaxis()->SetTitleSize(0.035);
   h_cross_section_eta_jet->GetZaxis()->SetTitleFont(42);
   h_cross_section_eta_jet->Draw("E1 X0 SAME");
   Double_t xAxis36[5] = {-1.5, -0.7, 0.1, 0.9, 1.8}; 
   
   TH1D *h_cross_section_eta_jet_1st_analysis = new TH1D("h_cross_section_eta_jet_1st_analysis","det_cross_eta_jet",4, xAxis36);
   h_cross_section_eta_jet_1st_analysis->SetBinContent(1,1.5117);
   h_cross_section_eta_jet_1st_analysis->SetBinContent(2,2.78151);
   h_cross_section_eta_jet_1st_analysis->SetBinContent(3,3.78551);
   h_cross_section_eta_jet_1st_analysis->SetBinContent(4,3.46116);
   h_cross_section_eta_jet_1st_analysis->SetBinError(1,0.170621);
   h_cross_section_eta_jet_1st_analysis->SetBinError(2,0.251139);
   h_cross_section_eta_jet_1st_analysis->SetBinError(3,0.337509);
   h_cross_section_eta_jet_1st_analysis->SetBinError(4,0.315143);
   h_cross_section_eta_jet_1st_analysis->SetEntries(14099);

   ci = TColor::GetColor("#0000ff");
   h_cross_section_eta_jet_1st_analysis->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   h_cross_section_eta_jet_1st_analysis->SetMarkerColor(ci);
   h_cross_section_eta_jet_1st_analysis->SetMarkerStyle(24);
   h_cross_section_eta_jet_1st_analysis->GetXaxis()->SetLabelFont(42);
   h_cross_section_eta_jet_1st_analysis->GetXaxis()->SetLabelSize(0.035);
   h_cross_section_eta_jet_1st_analysis->GetXaxis()->SetTitleSize(0.035);
   h_cross_section_eta_jet_1st_analysis->GetXaxis()->SetTitleFont(42);
   h_cross_section_eta_jet_1st_analysis->GetYaxis()->SetLabelFont(42);
   h_cross_section_eta_jet_1st_analysis->GetYaxis()->SetLabelSize(0.035);
   h_cross_section_eta_jet_1st_analysis->GetYaxis()->SetTitleSize(0.035);
   h_cross_section_eta_jet_1st_analysis->GetYaxis()->SetTitleFont(42);
   h_cross_section_eta_jet_1st_analysis->GetZaxis()->SetLabelFont(42);
   h_cross_section_eta_jet_1st_analysis->GetZaxis()->SetLabelSize(0.035);
   h_cross_section_eta_jet_1st_analysis->GetZaxis()->SetTitleSize(0.035);
   h_cross_section_eta_jet_1st_analysis->GetZaxis()->SetTitleFont(42);
   h_cross_section_eta_jet_1st_analysis->Draw("P E1 X0 SAME");
   
   TLegend *leg = new TLegend(0.37,0.059,0.77,0.358,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_eta_jet_1st_analysis","1st analysis","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("h_cross_section_eta_jet","2nd analysis","p");
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
