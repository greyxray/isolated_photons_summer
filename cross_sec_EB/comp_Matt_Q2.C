{
//=========Macro generated from canvas: canv_cross_Q2/
//=========  (Tue Jun  7 19:22:41 2011) by ROOT version5.26/00c
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
   h_window_cross_Q2->GetXaxis()->CenterTitle(true);
   h_window_cross_Q2->GetXaxis()->SetNdivisions(507);
   h_window_cross_Q2->GetXaxis()->SetLabelFont(42);
   h_window_cross_Q2->GetXaxis()->SetLabelSize(0.05073171);
   h_window_cross_Q2->GetXaxis()->SetTitleSize(0.06341463);
   h_window_cross_Q2->GetXaxis()->SetTitleFont(42);
   h_window_cross_Q2->GetYaxis()->SetTitle("d#sigma/d Q^{2} (pb/GeV^{2})");
   h_window_cross_Q2->GetYaxis()->CenterTitle(true);
   h_window_cross_Q2->GetYaxis()->SetNdivisions(507);
   h_window_cross_Q2->GetYaxis()->SetLabelFont(42);
   h_window_cross_Q2->GetYaxis()->SetLabelSize(0.0416);
   h_window_cross_Q2->GetYaxis()->SetTitleSize(0.052);
   h_window_cross_Q2->GetYaxis()->SetTitleFont(42);
   h_window_cross_Q2->Draw("");
   Double_t xAxis84[6] = {10, 20, 40, 80, 150, 350}; 
   
   TH1D *h_cross_section_Q2 = new TH1D("h_cross_section_Q2","det_cross_Q2",5, xAxis84);
   h_cross_section_Q2->SetBinContent(1,0.2920547);
   h_cross_section_Q2->SetBinContent(2,0.1298063);
   h_cross_section_Q2->SetBinContent(3,0.0477333);
   h_cross_section_Q2->SetBinContent(4,0.02222794);
   h_cross_section_Q2->SetBinContent(5,0.003642767);
   h_cross_section_Q2->SetBinError(1,0.02575811);
   h_cross_section_Q2->SetBinError(2,0.01239975);
   h_cross_section_Q2->SetBinError(3,0.005746506);
   h_cross_section_Q2->SetBinError(4,0.002485059);
   h_cross_section_Q2->SetBinError(5,0.0006945005);
   h_cross_section_Q2->SetEntries(14144);
   h_cross_section_Q2->SetFillColor(41);
   h_cross_section_Q2->SetMarkerStyle(20);
   h_cross_section_Q2->SetMarkerSize(0.8);
   h_cross_section_Q2->Draw("E1 X0 SAME");
   Double_t xAxis85[6] = {10, 20, 40, 80, 150, 350}; 
   
   TH1D *h_cross_section_Q2_1st_analysis = new TH1D("h_cross_section_Q2_1st_analysis","det_cross_Q2",5, xAxis85);
   h_cross_section_Q2_1st_analysis->SetBinContent(1,0.414);
   h_cross_section_Q2_1st_analysis->SetBinContent(2,0.279);
   h_cross_section_Q2_1st_analysis->SetBinContent(3,0.115);
   h_cross_section_Q2_1st_analysis->SetBinContent(4,0.05);
   h_cross_section_Q2_1st_analysis->SetBinContent(5,0.0088);
   h_cross_section_Q2_1st_analysis->SetBinError(1,0.035);
   h_cross_section_Q2_1st_analysis->SetBinError(2,0.02);
   h_cross_section_Q2_1st_analysis->SetBinError(3,0.008);
   h_cross_section_Q2_1st_analysis->SetBinError(4,0.003);
   h_cross_section_Q2_1st_analysis->SetBinError(5,0.0009);
   h_cross_section_Q2_1st_analysis->SetEntries(14149);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   h_cross_section_Q2_1st_analysis->SetLineColor(ci);

   ci = TColor::GetColor("#000000");
   h_cross_section_Q2_1st_analysis->SetMarkerColor(ci);
   h_cross_section_Q2_1st_analysis->SetMarkerStyle(21);
   h_cross_section_Q2_1st_analysis->SetMarkerSize(0.8);
   h_cross_section_Q2_1st_analysis->Draw("P E1 X0 SAME");
   
   TLegend *leg = new TLegend(0.23,0.289,0.63,0.588,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_Q2_1st_analysis","Matthew","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(0.8);
   entry=leg->AddEntry("h_cross_section_Q2","Oleg & Nataliia","p");
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
   canv_cross_Q2_2->Range(0.7552087,-1.166667,2.638219,0.7);
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
   
   TH2D *h_window_cross_ratio_Q2 = new TH2D("h_window_cross_ratio_Q2","",5, xAxis86,10,-0.7,0.7);
   h_window_cross_ratio_Q2->SetStats(0);
   h_window_cross_ratio_Q2->GetXaxis()->SetTitle("Q^{2} (GeV^{2})");
   h_window_cross_ratio_Q2->GetXaxis()->CenterTitle(true);
   h_window_cross_ratio_Q2->GetXaxis()->SetNdivisions(507);
   h_window_cross_ratio_Q2->GetXaxis()->SetLabelFont(42);
   h_window_cross_ratio_Q2->GetXaxis()->SetLabelSize(0.09756097);
   h_window_cross_ratio_Q2->GetXaxis()->SetTitleSize(0.1219512);
   h_window_cross_ratio_Q2->GetXaxis()->SetTickLength(0.07);
   h_window_cross_ratio_Q2->GetXaxis()->SetTitleOffset(0.8);
   h_window_cross_ratio_Q2->GetXaxis()->SetTitleFont(42);
   h_window_cross_ratio_Q2->GetYaxis()->SetTitle("rel. difference");
   h_window_cross_ratio_Q2->GetYaxis()->CenterTitle(true);
   h_window_cross_ratio_Q2->GetYaxis()->SetNdivisions(406);
   h_window_cross_ratio_Q2->GetYaxis()->SetLabelFont(42);
   h_window_cross_ratio_Q2->GetYaxis()->SetLabelSize(0.08533333);
   h_window_cross_ratio_Q2->GetYaxis()->SetTitleSize(0.1066667);
   h_window_cross_ratio_Q2->GetYaxis()->SetTitleOffset(0.5);
   h_window_cross_ratio_Q2->GetYaxis()->SetTitleFont(42);
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
   h_cross_section_Q2_ratio_1st_analysis->SetBinContent(1,-0.4175426);
   h_cross_section_Q2_ratio_1st_analysis->SetBinContent(2,-1.149357);
   h_cross_section_Q2_ratio_1st_analysis->SetBinContent(3,-1.40922);
   h_cross_section_Q2_ratio_1st_analysis->SetBinContent(4,-1.249421);
   h_cross_section_Q2_ratio_1st_analysis->SetBinContent(5,-1.415746);
   h_cross_section_Q2_ratio_1st_analysis->SetBinError(1,0.1731826);
   h_cross_section_Q2_ratio_1st_analysis->SetBinError(2,0.2566993);
   h_cross_section_Q2_ratio_1st_analysis->SetBinError(3,0.3349816);
   h_cross_section_Q2_ratio_1st_analysis->SetBinError(4,0.2854106);
   h_cross_section_Q2_ratio_1st_analysis->SetBinError(5,0.5226498);
   h_cross_section_Q2_ratio_1st_analysis->SetEntries(14149);

   ci = TColor::GetColor("#000000");
   h_cross_section_Q2_ratio_1st_analysis->SetMarkerColor(ci);
   h_cross_section_Q2_ratio_1st_analysis->SetMarkerStyle(21);
   h_cross_section_Q2_ratio_1st_analysis->SetMarkerSize(0.8);
   h_cross_section_Q2_ratio_1st_analysis->Draw("E X0 SAME");
   canv_cross_Q2_2->Modified();
   canv_cross_Q2->cd();
   canv_cross_Q2->Modified();
   canv_cross_Q2->cd();
   canv_cross_Q2->SetSelected(canv_cross_Q2);
}
