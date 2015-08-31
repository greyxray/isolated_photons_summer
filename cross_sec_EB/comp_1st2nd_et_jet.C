{
//=========Macro generated from canvas: canv_cross_et_jet/
//=========  (Wed Aug 12 00:25:08 2015) by ROOT version5.34/00
   TCanvas *canv_cross_et_jet = new TCanvas("canv_cross_et_jet", "",1,1,1200,976);
   canv_cross_et_jet->SetHighLightColor(2);
   canv_cross_et_jet->Range(0,0,1,1);
   canv_cross_et_jet->SetFillColor(0);
   canv_cross_et_jet->SetBorderMode(0);
   canv_cross_et_jet->SetBorderSize(2);
   canv_cross_et_jet->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_et_jet_1
   TPad *canv_cross_et_jet_1 = new TPad("canv_cross_et_jet_1", "canv_cross_et_jet_1",0.01,0.01,0.99,0.99);
   canv_cross_et_jet_1->Draw();
   canv_cross_et_jet_1->cd();
   canv_cross_et_jet_1->Range(-3.59375,-2.391286,37.03125,0.7608099);
   canv_cross_et_jet_1->SetFillColor(0);
   canv_cross_et_jet_1->SetBorderMode(0);
   canv_cross_et_jet_1->SetBorderSize(2);
   canv_cross_et_jet_1->SetLogy();
   canv_cross_et_jet_1->SetTickx(1);
   canv_cross_et_jet_1->SetTicky(1);
   canv_cross_et_jet_1->SetLeftMargin(0.15);
   canv_cross_et_jet_1->SetRightMargin(0.05);
   canv_cross_et_jet_1->SetBottomMargin(0.18);
   canv_cross_et_jet_1->SetFrameBorderMode(0);
   canv_cross_et_jet_1->SetFrameBorderMode(0);
   Double_t xAxis31[7] = {2.5, 4, 6, 8, 10, 15, 35}; 
   
   TH2D *h_window_cross_et_jet = new TH2D("h_window_cross_et_jet","",6, xAxis31,10,0.015,3);
   h_window_cross_et_jet->SetStats(0);
   h_window_cross_et_jet->GetXaxis()->SetTitle("E_{T}^{jet} (GeV)");
   h_window_cross_et_jet->GetXaxis()->SetNdivisions(507);
   h_window_cross_et_jet->GetXaxis()->SetLabelFont(22);
   h_window_cross_et_jet->GetXaxis()->SetLabelSize(0.05424658);
   h_window_cross_et_jet->GetXaxis()->SetTitleSize(0.06027398);
   h_window_cross_et_jet->GetXaxis()->SetTitleOffset(1.02);
   h_window_cross_et_jet->GetXaxis()->SetTitleFont(22);
   h_window_cross_et_jet->GetYaxis()->SetTitle("d#sigma/dE_{T}^{jet} (pb/GeV)");
   h_window_cross_et_jet->GetYaxis()->SetNdivisions(507);
   h_window_cross_et_jet->GetYaxis()->SetLabelFont(22);
   h_window_cross_et_jet->GetYaxis()->SetLabelOffset(0.016);
   h_window_cross_et_jet->GetYaxis()->SetLabelSize(0.05424658);
   h_window_cross_et_jet->GetYaxis()->SetTitleSize(0.06027398);
   h_window_cross_et_jet->GetYaxis()->SetTitleOffset(1.2);
   h_window_cross_et_jet->GetYaxis()->SetTitleFont(22);
   h_window_cross_et_jet->Draw("");
   Double_t xAxis32[7] = {2.5, 4, 6, 8, 10, 15, 35}; 
   
   TH1D *h_cross_section_et_jet = new TH1D("h_cross_section_et_jet","det_cross_et_jet",6, xAxis32);
   h_cross_section_et_jet->SetBinContent(1,1.397993);
   h_cross_section_et_jet->SetBinContent(2,1.192586);
   h_cross_section_et_jet->SetBinContent(3,1.008039);
   h_cross_section_et_jet->SetBinContent(4,0.742206);
   h_cross_section_et_jet->SetBinContent(5,0.315349);
   h_cross_section_et_jet->SetBinContent(6,0.0305625);
   h_cross_section_et_jet->SetBinError(1,0.1634298);
   h_cross_section_et_jet->SetBinError(2,0.1082324);
   h_cross_section_et_jet->SetBinError(3,0.0976833);
   h_cross_section_et_jet->SetBinError(4,0.07229249);
   h_cross_section_et_jet->SetBinError(5,0.03208905);
   h_cross_section_et_jet->SetBinError(6,0.005654617);
   h_cross_section_et_jet->SetEntries(13891);
   h_cross_section_et_jet->SetFillColor(41);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   h_cross_section_et_jet->SetLineColor(ci);
   h_cross_section_et_jet->SetLineWidth(2);
   h_cross_section_et_jet->SetMarkerStyle(20);
   h_cross_section_et_jet->GetXaxis()->SetLabelFont(42);
   h_cross_section_et_jet->GetXaxis()->SetLabelSize(0.035);
   h_cross_section_et_jet->GetXaxis()->SetTitleSize(0.035);
   h_cross_section_et_jet->GetXaxis()->SetTitleFont(42);
   h_cross_section_et_jet->GetYaxis()->SetLabelFont(42);
   h_cross_section_et_jet->GetYaxis()->SetLabelSize(0.035);
   h_cross_section_et_jet->GetYaxis()->SetTitleSize(0.035);
   h_cross_section_et_jet->GetYaxis()->SetTitleFont(42);
   h_cross_section_et_jet->GetZaxis()->SetLabelFont(42);
   h_cross_section_et_jet->GetZaxis()->SetLabelSize(0.035);
   h_cross_section_et_jet->GetZaxis()->SetTitleSize(0.035);
   h_cross_section_et_jet->GetZaxis()->SetTitleFont(42);
   h_cross_section_et_jet->Draw("E1 X0 SAME");
   Double_t xAxis33[7] = {2.5, 4, 6, 8, 10, 15, 35}; 
   
   TH1D *h_cross_section_et_jet_1st_analysis = new TH1D("h_cross_section_et_jet_1st_analysis","det_cross_et_jet",6, xAxis33);
   h_cross_section_et_jet_1st_analysis->SetBinContent(1,1.33293);
   h_cross_section_et_jet_1st_analysis->SetBinContent(2,1.15801);
   h_cross_section_et_jet_1st_analysis->SetBinContent(3,0.943754);
   h_cross_section_et_jet_1st_analysis->SetBinContent(4,0.724772);
   h_cross_section_et_jet_1st_analysis->SetBinContent(5,0.317728);
   h_cross_section_et_jet_1st_analysis->SetBinContent(6,0.0283796);
   h_cross_section_et_jet_1st_analysis->SetBinError(1,0.168075);
   h_cross_section_et_jet_1st_analysis->SetBinError(2,0.108655);
   h_cross_section_et_jet_1st_analysis->SetBinError(3,0.0965607);
   h_cross_section_et_jet_1st_analysis->SetBinError(4,0.0744572);
   h_cross_section_et_jet_1st_analysis->SetBinError(5,0.0333168);
   h_cross_section_et_jet_1st_analysis->SetBinError(6,0.00736767);
   h_cross_section_et_jet_1st_analysis->SetEntries(13891);

   ci = TColor::GetColor("#0000ff");
   h_cross_section_et_jet_1st_analysis->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   h_cross_section_et_jet_1st_analysis->SetMarkerColor(ci);
   h_cross_section_et_jet_1st_analysis->SetMarkerStyle(24);
   h_cross_section_et_jet_1st_analysis->GetXaxis()->SetLabelFont(42);
   h_cross_section_et_jet_1st_analysis->GetXaxis()->SetLabelSize(0.035);
   h_cross_section_et_jet_1st_analysis->GetXaxis()->SetTitleSize(0.035);
   h_cross_section_et_jet_1st_analysis->GetXaxis()->SetTitleFont(42);
   h_cross_section_et_jet_1st_analysis->GetYaxis()->SetLabelFont(42);
   h_cross_section_et_jet_1st_analysis->GetYaxis()->SetLabelSize(0.035);
   h_cross_section_et_jet_1st_analysis->GetYaxis()->SetTitleSize(0.035);
   h_cross_section_et_jet_1st_analysis->GetYaxis()->SetTitleFont(42);
   h_cross_section_et_jet_1st_analysis->GetZaxis()->SetLabelFont(42);
   h_cross_section_et_jet_1st_analysis->GetZaxis()->SetLabelSize(0.035);
   h_cross_section_et_jet_1st_analysis->GetZaxis()->SetTitleSize(0.035);
   h_cross_section_et_jet_1st_analysis->GetZaxis()->SetTitleFont(42);
   h_cross_section_et_jet_1st_analysis->Draw("P E1 X0 SAME");
   
   TLegend *leg = new TLegend(0.4,0.87,0.9,0.97,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_et_jet_1st_analysis","1st analysis","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("h_cross_section_et_jet","2nd analysis","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();
   canv_cross_et_jet_1->Modified();
   canv_cross_et_jet->cd();
   TText *text = new TText(0.45,0.95,"ZEUS");
   text->SetTextFont(22);
   text->SetTextSize(0.07);
   text->Draw();
   canv_cross_et_jet->Modified();
   canv_cross_et_jet->cd();
   canv_cross_et_jet->SetSelected(canv_cross_et_jet);
}
