{
//=========Macro generated from canvas: canv_cross_Q2/
//=========  (Wed Aug 12 00:25:07 2015) by ROOT version5.34/00
   TCanvas *canv_cross_Q2 = new TCanvas("canv_cross_Q2", "",1,1,1200,976);
   canv_cross_Q2->SetHighLightColor(2);
   canv_cross_Q2->Range(0,0,1,1);
   canv_cross_Q2->SetFillColor(0);
   canv_cross_Q2->SetBorderMode(0);
   canv_cross_Q2->SetBorderSize(2);
   canv_cross_Q2->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_Q2_1
   TPad *canv_cross_Q2_1 = new TPad("canv_cross_Q2_1", "canv_cross_Q2_1",0.01,0.01,0.99,0.99);
   canv_cross_Q2_1->Draw();
   canv_cross_Q2_1->cd();
   canv_cross_Q2_1->Range(0.7104872,-3.701531,2.640572,0.1958636);
   canv_cross_Q2_1->SetFillColor(0);
   canv_cross_Q2_1->SetBorderMode(0);
   canv_cross_Q2_1->SetBorderSize(2);
   canv_cross_Q2_1->SetLogx();
   canv_cross_Q2_1->SetLogy();
   canv_cross_Q2_1->SetTickx(1);
   canv_cross_Q2_1->SetTicky(1);
   canv_cross_Q2_1->SetLeftMargin(0.15);
   canv_cross_Q2_1->SetRightMargin(0.05);
   canv_cross_Q2_1->SetBottomMargin(0.18);
   canv_cross_Q2_1->SetFrameBorderMode(0);
   canv_cross_Q2_1->SetFrameBorderMode(0);
   Double_t xAxis25[6] = {10, 20, 40, 80, 150, 350}; 
   
   TH2D *h_window_cross_Q2 = new TH2D("h_window_cross_Q2","",5, xAxis25,10,0.001,0.7);
   h_window_cross_Q2->SetStats(0);
   h_window_cross_Q2->GetXaxis()->SetTitle("Q^{2} (GeV^{2})");
   h_window_cross_Q2->GetXaxis()->SetMoreLogLabels();
   h_window_cross_Q2->GetXaxis()->SetNdivisions(507);
   h_window_cross_Q2->GetXaxis()->SetLabelFont(22);
   h_window_cross_Q2->GetXaxis()->SetLabelSize(0.05424658);
   h_window_cross_Q2->GetXaxis()->SetTitleSize(0.06027398);
   h_window_cross_Q2->GetXaxis()->SetTitleOffset(1.1);
   h_window_cross_Q2->GetXaxis()->SetTitleFont(22);
   h_window_cross_Q2->GetYaxis()->SetTitle("d#sigma/dQ^{2} (pb/GeV^{2})");
   h_window_cross_Q2->GetYaxis()->SetNdivisions(507);
   h_window_cross_Q2->GetYaxis()->SetLabelFont(22);
   h_window_cross_Q2->GetYaxis()->SetLabelOffset(0.016);
   h_window_cross_Q2->GetYaxis()->SetLabelSize(0.05424658);
   h_window_cross_Q2->GetYaxis()->SetTitleSize(0.06027398);
   h_window_cross_Q2->GetYaxis()->SetTitleOffset(1.2);
   h_window_cross_Q2->GetYaxis()->SetTitleFont(22);
   h_window_cross_Q2->Draw("");
   Double_t xAxis26[6] = {10, 20, 40, 80, 150, 350}; 
   
   TH1D *h_cross_section_Q2 = new TH1D("h_cross_section_Q2","det_cross_Q2",5, xAxis26);
   h_cross_section_Q2->SetBinContent(1,0.2978664);
   h_cross_section_Q2->SetBinContent(2,0.1291481);
   h_cross_section_Q2->SetBinContent(3,0.0486016);
   h_cross_section_Q2->SetBinContent(4,0.02243448);
   h_cross_section_Q2->SetBinContent(5,0.00374546);
   h_cross_section_Q2->SetBinError(1,0.02413826);
   h_cross_section_Q2->SetBinError(2,0.01165591);
   h_cross_section_Q2->SetBinError(3,0.00522137);
   h_cross_section_Q2->SetBinError(4,0.002318905);
   h_cross_section_Q2->SetBinError(5,0.0006528721);
   h_cross_section_Q2->SetEntries(13889);
   h_cross_section_Q2->SetFillColor(41);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   h_cross_section_Q2->SetLineColor(ci);
   h_cross_section_Q2->SetLineWidth(2);
   h_cross_section_Q2->SetMarkerStyle(20);
   h_cross_section_Q2->GetXaxis()->SetLabelFont(42);
   h_cross_section_Q2->GetXaxis()->SetLabelSize(0.035);
   h_cross_section_Q2->GetXaxis()->SetTitleSize(0.035);
   h_cross_section_Q2->GetXaxis()->SetTitleFont(42);
   h_cross_section_Q2->GetYaxis()->SetLabelFont(42);
   h_cross_section_Q2->GetYaxis()->SetLabelSize(0.035);
   h_cross_section_Q2->GetYaxis()->SetTitleSize(0.035);
   h_cross_section_Q2->GetYaxis()->SetTitleFont(42);
   h_cross_section_Q2->GetZaxis()->SetLabelFont(42);
   h_cross_section_Q2->GetZaxis()->SetLabelSize(0.035);
   h_cross_section_Q2->GetZaxis()->SetTitleSize(0.035);
   h_cross_section_Q2->GetZaxis()->SetTitleFont(42);
   h_cross_section_Q2->Draw("E1 X0 SAME");
   Double_t xAxis27[6] = {10, 20, 40, 80, 150, 350}; 
   
   TH1D *h_cross_section_Q2_1st_analysis = new TH1D("h_cross_section_Q2_1st_analysis","det_cross_Q2",5, xAxis27);
   h_cross_section_Q2_1st_analysis->SetBinContent(1,0.291339);
   h_cross_section_Q2_1st_analysis->SetBinContent(2,0.128066);
   h_cross_section_Q2_1st_analysis->SetBinContent(3,0.0471501);
   h_cross_section_Q2_1st_analysis->SetBinContent(4,0.0222523);
   h_cross_section_Q2_1st_analysis->SetBinContent(5,0.00380146);
   h_cross_section_Q2_1st_analysis->SetBinError(1,0.0246273);
   h_cross_section_Q2_1st_analysis->SetBinError(2,0.011909);
   h_cross_section_Q2_1st_analysis->SetBinError(3,0.00565118);
   h_cross_section_Q2_1st_analysis->SetBinError(4,0.00242282);
   h_cross_section_Q2_1st_analysis->SetBinError(5,0.00072053);
   h_cross_section_Q2_1st_analysis->SetEntries(13889);

   ci = TColor::GetColor("#0000ff");
   h_cross_section_Q2_1st_analysis->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   h_cross_section_Q2_1st_analysis->SetMarkerColor(ci);
   h_cross_section_Q2_1st_analysis->SetMarkerStyle(24);
   h_cross_section_Q2_1st_analysis->GetXaxis()->SetLabelFont(42);
   h_cross_section_Q2_1st_analysis->GetXaxis()->SetLabelSize(0.035);
   h_cross_section_Q2_1st_analysis->GetXaxis()->SetTitleSize(0.035);
   h_cross_section_Q2_1st_analysis->GetXaxis()->SetTitleFont(42);
   h_cross_section_Q2_1st_analysis->GetYaxis()->SetLabelFont(42);
   h_cross_section_Q2_1st_analysis->GetYaxis()->SetLabelSize(0.035);
   h_cross_section_Q2_1st_analysis->GetYaxis()->SetTitleSize(0.035);
   h_cross_section_Q2_1st_analysis->GetYaxis()->SetTitleFont(42);
   h_cross_section_Q2_1st_analysis->GetZaxis()->SetLabelFont(42);
   h_cross_section_Q2_1st_analysis->GetZaxis()->SetLabelSize(0.035);
   h_cross_section_Q2_1st_analysis->GetZaxis()->SetTitleSize(0.035);
   h_cross_section_Q2_1st_analysis->GetZaxis()->SetTitleFont(42);
   h_cross_section_Q2_1st_analysis->Draw("P E1 X0 SAME");
   
   TLegend *leg = new TLegend(0.23,0.209,0.63,0.508,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_Q2_1st_analysis","1st analysis","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("h_cross_section_Q2","2nd analysis","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();
   canv_cross_Q2_1->Modified();
   canv_cross_Q2->cd();
   TText *text = new TText(0.45,0.95,"ZEUS");
   text->SetTextFont(22);
   text->SetTextSize(0.07);
   text->Draw();
   canv_cross_Q2->Modified();
   canv_cross_Q2->cd();
   canv_cross_Q2->SetSelected(canv_cross_Q2);
}
