{
//=========Macro generated from canvas: canv_cross_Q2/
//=========  (Thu Jan 12 23:28:11 2012) by ROOT version5.26/00c
   TCanvas *canv_cross_Q2 = new TCanvas("canv_cross_Q2", "",1,1,550,876);
   canv_cross_Q2->SetHighLightColor(2);
   canv_cross_Q2->Range(0,0,1,1);
   canv_cross_Q2->SetFillColor(0);
   canv_cross_Q2->SetBorderMode(0);
   canv_cross_Q2->SetBorderSize(2);
   canv_cross_Q2->SetTopMargin(0.04761905);
   canv_cross_Q2->SetBottomMargin(0.05);
   canv_cross_Q2->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_Q2_1
   TPad *canv_cross_Q2_1 = new TPad("canv_cross_Q2_1", "_1",0.1,0.4,0.9,0.9);
   canv_cross_Q2_1->Draw();
   canv_cross_Q2_1->cd();
   canv_cross_Q2_1->Range(0.7552087,-3,2.638219,0);
   canv_cross_Q2_1->SetFillColor(0);
   canv_cross_Q2_1->SetBorderMode(0);
   canv_cross_Q2_1->SetBorderSize(2);
   canv_cross_Q2_1->SetLogx();
   canv_cross_Q2_1->SetLogy();
   canv_cross_Q2_1->SetTickx(1);
   canv_cross_Q2_1->SetTicky(1);
   canv_cross_Q2_1->SetLeftMargin(0.13);
   canv_cross_Q2_1->SetRightMargin(0.05);
   canv_cross_Q2_1->SetTopMargin(0);
   canv_cross_Q2_1->SetBottomMargin(0);
   canv_cross_Q2_1->SetFrameBorderMode(0);
   canv_cross_Q2_1->SetFrameBorderMode(0);
   Double_t xAxis83[6] = {10, 20, 40, 80, 150, 350}; 
   
   TH2D *h_window_cross_Q2 = new TH2D("h_window_cross_Q2","",5, xAxis83,10,0.001,1);
   h_window_cross_Q2->SetStats(0);
   h_window_cross_Q2->GetXaxis()->SetTitle("Q^{2} (GeV^{2})");
   h_window_cross_Q2->GetXaxis()->SetNdivisions(507);
   h_window_cross_Q2->GetXaxis()->SetLabelFont(22);
   h_window_cross_Q2->GetXaxis()->SetLabelSize(0.04829268);
   h_window_cross_Q2->GetXaxis()->SetTitleSize(0.05365854);
   h_window_cross_Q2->GetXaxis()->SetTitleOffset(0.9);
   h_window_cross_Q2->GetYaxis()->SetTitle("d#sigma/d Q^{2} (pb/GeV^{2})");
   h_window_cross_Q2->GetYaxis()->SetNdivisions(507);
   h_window_cross_Q2->GetYaxis()->SetLabelFont(22);
   h_window_cross_Q2->GetYaxis()->SetTitleSize(0.044);
   h_window_cross_Q2->GetYaxis()->SetTitleOffset(0.9);
   h_window_cross_Q2->Draw("");
   Double_t xAxis84[6] = {10, 20, 40, 80, 150, 350}; 
   
   TH1D *h_cross_section_Q2 = new TH1D("h_cross_section_Q2","det_cross_Q2",5, xAxis84);
   h_cross_section_Q2->SetBinContent(1,0.2918374);
   h_cross_section_Q2->SetBinContent(2,0.1283835);
   h_cross_section_Q2->SetBinContent(3,0.04872619);
   h_cross_section_Q2->SetBinContent(4,0.02209429);
   h_cross_section_Q2->SetBinContent(5,0.003933291);
   h_cross_section_Q2->SetBinError(1,0.02562223);
   h_cross_section_Q2->SetBinError(2,0.01209815);
   h_cross_section_Q2->SetBinError(3,0.005544669);
   h_cross_section_Q2->SetBinError(4,0.002575273);
   h_cross_section_Q2->SetBinError(5,0.0007241885);
   h_cross_section_Q2->SetEntries(14123);
   h_cross_section_Q2->SetFillColor(41);
   h_cross_section_Q2->SetMarkerStyle(20);
   h_cross_section_Q2->SetMarkerSize(0.8);
   h_cross_section_Q2->Draw("E1 X0 SAME");
   Double_t xAxis85[6] = {10, 20, 40, 80, 150, 350}; 
   
   TH1D *h_cross_section_Q2_1st_analysis = new TH1D("h_cross_section_Q2_1st_analysis","det_cross_Q2",5, xAxis85);
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
   h_cross_section_Q2_1st_analysis->SetEntries(14128);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   h_cross_section_Q2_1st_analysis->SetLineColor(ci);

   ci = TColor::GetColor("#000000");
   h_cross_section_Q2_1st_analysis->SetMarkerColor(ci);
   h_cross_section_Q2_1st_analysis->SetMarkerStyle(24);
   h_cross_section_Q2_1st_analysis->Draw("P E1 X0 SAME");
   
   TLegend *leg = new TLegend(0.23,0.209,0.63,0.508,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_Q2_1st_analysis","without reweighting","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("h_cross_section_Q2","with reweighting","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.8);
   leg->Draw();
   canv_cross_Q2_1->Modified();
   canv_cross_Q2->cd();
  
// ------------>Primitives in pad: canv_cross_Q2_2
   canv_cross_Q2_2 = new TPad("canv_cross_Q2_2", "_2",0.1,0.2,0.9,0.4);
   canv_cross_Q2_2->Draw();
   canv_cross_Q2_2->cd();
   canv_cross_Q2_2->Range(0.7552087,-0.1666667,2.638219,0.1);
   canv_cross_Q2_2->SetFillColor(0);
   canv_cross_Q2_2->SetBorderMode(0);
   canv_cross_Q2_2->SetBorderSize(2);
   canv_cross_Q2_2->SetLogx();
   canv_cross_Q2_2->SetTickx(1);
   canv_cross_Q2_2->SetTicky(1);
   canv_cross_Q2_2->SetLeftMargin(0.13);
   canv_cross_Q2_2->SetRightMargin(0.05);
   canv_cross_Q2_2->SetTopMargin(0);
   canv_cross_Q2_2->SetBottomMargin(0.25);
   canv_cross_Q2_2->SetFrameBorderMode(0);
   canv_cross_Q2_2->SetFrameBorderMode(0);
   Double_t xAxis86[6] = {10, 20, 40, 80, 150, 350}; 
   
   TH2D *h_window_cross_ratio_Q2 = new TH2D("h_window_cross_ratio_Q2","",5, xAxis86,10,-0.1,0.1);
   h_window_cross_ratio_Q2->SetStats(0);
   h_window_cross_ratio_Q2->GetXaxis()->SetTitle("Q^{2} (GeV^{2})");
   h_window_cross_ratio_Q2->GetXaxis()->SetNdivisions(507);
   h_window_cross_ratio_Q2->GetXaxis()->SetLabelFont(22);
   h_window_cross_ratio_Q2->GetXaxis()->SetLabelSize(0.1097561);
   h_window_cross_ratio_Q2->GetXaxis()->SetTitleSize(0.1219512);
   h_window_cross_ratio_Q2->GetXaxis()->SetTickLength(0.07);
   h_window_cross_ratio_Q2->GetXaxis()->SetTitleOffset(0.8);
   h_window_cross_ratio_Q2->GetYaxis()->SetTitle("rel. difference");
   h_window_cross_ratio_Q2->GetYaxis()->SetNdivisions(406);
   h_window_cross_ratio_Q2->GetYaxis()->SetLabelFont(22);
   h_window_cross_ratio_Q2->GetYaxis()->SetLabelSize(0.096);
   h_window_cross_ratio_Q2->GetYaxis()->SetTitleSize(0.1066667);
   h_window_cross_ratio_Q2->GetYaxis()->SetTitleOffset(0.5);
   h_window_cross_ratio_Q2->Draw("");
   
   TF1 *Unity = new TF1("Unity","0",-100,500);
   Unity->SetFillColor(19);
   Unity->SetFillStyle(0);
   Unity->SetLineColor(32);
   Unity->SetLineWidth(1);
   Unity->GetXaxis()->SetTitleFont(42);
   Unity->Draw("SAME");
   Double_t xAxis87[6] = {10, 20, 40, 80, 150, 350}; 
   
   TH1D *h_cross_section_Q2_ratio_1st_analysis = new TH1D("h_cross_section_Q2_ratio_1st_analysis","det_cross_Q2",5, xAxis87);
   h_cross_section_Q2_ratio_1st_analysis->SetBinContent(1,0.001707925);
   h_cross_section_Q2_ratio_1st_analysis->SetBinContent(2,0.002472853);
   h_cross_section_Q2_ratio_1st_analysis->SetBinContent(3,0.03234576);
   h_cross_section_Q2_ratio_1st_analysis->SetBinContent(4,-0.007151515);
   h_cross_section_Q2_ratio_1st_analysis->SetBinContent(5,0.03351665);
   h_cross_section_Q2_ratio_1st_analysis->SetBinError(1,0.1216678);
   h_cross_section_Q2_ratio_1st_analysis->SetBinError(2,0.132064);
   h_cross_section_Q2_ratio_1st_analysis->SetBinError(3,0.1599236);
   h_cross_section_Q2_ratio_1st_analysis->SetBinError(4,0.1606417);
   h_cross_section_Q2_ratio_1st_analysis->SetBinError(5,0.2553874);
   h_cross_section_Q2_ratio_1st_analysis->SetEntries(14128);

   ci = TColor::GetColor("#000000");
   h_cross_section_Q2_ratio_1st_analysis->SetMarkerColor(ci);
   h_cross_section_Q2_ratio_1st_analysis->SetMarkerStyle(24);
   h_cross_section_Q2_ratio_1st_analysis->Draw("E X0 SAME");
   canv_cross_Q2_2->Modified();
   canv_cross_Q2->cd();
   canv_cross_Q2->Modified();
   canv_cross_Q2->cd();
   canv_cross_Q2->SetSelected(canv_cross_Q2);
}
