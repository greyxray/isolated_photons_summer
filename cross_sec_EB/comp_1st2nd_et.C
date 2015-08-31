{
//=========Macro generated from canvas: canv_cross_et/
//=========  (Wed Aug 12 00:25:07 2015) by ROOT version5.34/00
   TCanvas *canv_cross_et = new TCanvas("canv_cross_et", "",1,1,1200,976);
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
   Double_t xAxis19[5] = {4, 6, 8, 10, 15}; 
   
   TH2D *h_window_cross_et = new TH2D("h_window_cross_et","",4, xAxis19,10,0.1,4);
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
   Double_t xAxis20[5] = {4, 6, 8, 10, 15}; 
   
   TH1D *h_cross_section_et = new TH1D("h_cross_section_et","det_cross_et",4, xAxis20);
   h_cross_section_et->SetBinContent(1,2.380595);
   h_cross_section_et->SetBinContent(2,1.281126);
   h_cross_section_et->SetBinContent(3,0.615687);
   h_cross_section_et->SetBinContent(4,0.2556284);
   h_cross_section_et->SetBinError(1,0.1767385);
   h_cross_section_et->SetBinError(2,0.1017351);
   h_cross_section_et->SetBinError(3,0.07578678);
   h_cross_section_et->SetBinError(4,0.02508957);
   h_cross_section_et->SetEntries(13887);
   h_cross_section_et->SetFillColor(41);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   h_cross_section_et->SetLineColor(ci);
   h_cross_section_et->SetLineWidth(2);
   h_cross_section_et->SetMarkerStyle(20);
   h_cross_section_et->GetXaxis()->SetLabelFont(42);
   h_cross_section_et->GetXaxis()->SetLabelSize(0.035);
   h_cross_section_et->GetXaxis()->SetTitleSize(0.035);
   h_cross_section_et->GetXaxis()->SetTitleFont(42);
   h_cross_section_et->GetYaxis()->SetLabelFont(42);
   h_cross_section_et->GetYaxis()->SetLabelSize(0.035);
   h_cross_section_et->GetYaxis()->SetTitleSize(0.035);
   h_cross_section_et->GetYaxis()->SetTitleFont(42);
   h_cross_section_et->GetZaxis()->SetLabelFont(42);
   h_cross_section_et->GetZaxis()->SetLabelSize(0.035);
   h_cross_section_et->GetZaxis()->SetTitleSize(0.035);
   h_cross_section_et->GetZaxis()->SetTitleFont(42);
   h_cross_section_et->Draw("E1 X0 SAME");
   Double_t xAxis21[5] = {4, 6, 8, 10, 15}; 
   
   TH1D *h_cross_section_et_1st_analysis = new TH1D("h_cross_section_et_1st_analysis","det_cross_et",4, xAxis21);
   h_cross_section_et_1st_analysis->SetBinContent(1,2.38715);
   h_cross_section_et_1st_analysis->SetBinContent(2,1.29);
   h_cross_section_et_1st_analysis->SetBinContent(3,0.613948);
   h_cross_section_et_1st_analysis->SetBinContent(4,0.250965);
   h_cross_section_et_1st_analysis->SetBinError(1,0.183255);
   h_cross_section_et_1st_analysis->SetBinError(2,0.104856);
   h_cross_section_et_1st_analysis->SetBinError(3,0.0769511);
   h_cross_section_et_1st_analysis->SetBinError(4,0.0270204);
   h_cross_section_et_1st_analysis->SetEntries(13887);

   ci = TColor::GetColor("#0000ff");
   h_cross_section_et_1st_analysis->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   h_cross_section_et_1st_analysis->SetMarkerColor(ci);
   h_cross_section_et_1st_analysis->SetMarkerStyle(24);
   h_cross_section_et_1st_analysis->GetXaxis()->SetLabelFont(42);
   h_cross_section_et_1st_analysis->GetXaxis()->SetLabelSize(0.035);
   h_cross_section_et_1st_analysis->GetXaxis()->SetTitleSize(0.035);
   h_cross_section_et_1st_analysis->GetXaxis()->SetTitleFont(42);
   h_cross_section_et_1st_analysis->GetYaxis()->SetLabelFont(42);
   h_cross_section_et_1st_analysis->GetYaxis()->SetLabelSize(0.035);
   h_cross_section_et_1st_analysis->GetYaxis()->SetTitleSize(0.035);
   h_cross_section_et_1st_analysis->GetYaxis()->SetTitleFont(42);
   h_cross_section_et_1st_analysis->GetZaxis()->SetLabelFont(42);
   h_cross_section_et_1st_analysis->GetZaxis()->SetLabelSize(0.035);
   h_cross_section_et_1st_analysis->GetZaxis()->SetTitleSize(0.035);
   h_cross_section_et_1st_analysis->GetZaxis()->SetTitleFont(42);
   h_cross_section_et_1st_analysis->Draw("P E1 X0 SAME");
   
   TLegend *leg = new TLegend(0.4,0.7,0.9,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_et_1st_analysis","1st analysis","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("h_cross_section_et","2nd analysis","p");
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
