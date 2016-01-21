{
//=========Macro generated from canvas: canv_cross_et/
//=========  (Thu Jan 12 23:28:10 2012) by ROOT version5.26/00c
   TCanvas *canv_cross_et = new TCanvas("canv_cross_et", "",1,1,550,876);
   canv_cross_et->SetHighLightColor(2);
   canv_cross_et->Range(0,0,1,1);
   canv_cross_et->SetFillColor(0);
   canv_cross_et->SetBorderMode(0);
   canv_cross_et->SetBorderSize(2);
   canv_cross_et->SetTopMargin(0.04761905);
   canv_cross_et->SetBottomMargin(0.05);
   canv_cross_et->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_et_1
   TPad *canv_cross_et_1 = new TPad("canv_cross_et_1", "_1",0.1,0.4,0.9,0.9);
   canv_cross_et_1->Draw();
   canv_cross_et_1->cd();
   canv_cross_et_1->Range(2.256098,0.05,15.67073,4);
   canv_cross_et_1->SetFillColor(0);
   canv_cross_et_1->SetBorderMode(0);
   canv_cross_et_1->SetBorderSize(2);
   canv_cross_et_1->SetTickx(1);
   canv_cross_et_1->SetTicky(1);
   canv_cross_et_1->SetLeftMargin(0.13);
   canv_cross_et_1->SetRightMargin(0.05);
   canv_cross_et_1->SetTopMargin(0);
   canv_cross_et_1->SetBottomMargin(0);
   canv_cross_et_1->SetFrameBorderMode(0);
   canv_cross_et_1->SetFrameBorderMode(0);
   Double_t xAxis73[5] = {4, 6, 8, 10, 15}; 
   
   TH2D *h_window_cross_et = new TH2D("h_window_cross_et","",4, xAxis73,10,0.05,4);
   h_window_cross_et->SetStats(0);
   h_window_cross_et->GetXaxis()->SetTitle("E_{T}^{photon} (GeV)");
   h_window_cross_et->GetXaxis()->SetNdivisions(507);
   h_window_cross_et->GetXaxis()->SetLabelFont(22);
   h_window_cross_et->GetXaxis()->SetLabelSize(0.04829268);
   h_window_cross_et->GetXaxis()->SetTitleSize(0.05365854);
   h_window_cross_et->GetXaxis()->SetTitleOffset(0.9);
   h_window_cross_et->GetYaxis()->SetTitle("d#sigma/d E_{T}^{photon} (pb/GeV)");
   h_window_cross_et->GetYaxis()->SetNdivisions(507);
   h_window_cross_et->GetYaxis()->SetLabelFont(22);
   h_window_cross_et->GetYaxis()->SetTitleSize(0.044);
   h_window_cross_et->GetYaxis()->SetTitleOffset(0.9);
   h_window_cross_et->Draw("");
   Double_t xAxis74[5] = {4, 6, 8, 10, 15}; 
   
   TH1D *h_cross_section_et = new TH1D("h_cross_section_et","det_cross_et",4, xAxis74);
   h_cross_section_et->SetBinContent(1,2.412967);
   h_cross_section_et->SetBinContent(2,1.301605);
   h_cross_section_et->SetBinContent(3,0.6230808);
   h_cross_section_et->SetBinContent(4,0.2509107);
   h_cross_section_et->SetBinError(1,0.1801686);
   h_cross_section_et->SetBinError(2,0.1101106);
   h_cross_section_et->SetBinError(3,0.07941434);
   h_cross_section_et->SetBinError(4,0.03057925);
   h_cross_section_et->SetEntries(14122);
   h_cross_section_et->SetFillColor(41);
   h_cross_section_et->SetMarkerStyle(20);
   h_cross_section_et->SetMarkerSize(0.8);
   h_cross_section_et->Draw("E1 X0 SAME");
   Double_t xAxis75[5] = {4, 6, 8, 10, 15}; 
   
   TH1D *h_cross_section_et_1st_analysis = new TH1D("h_cross_section_et_1st_analysis","det_cross_et",4, xAxis75);
   h_cross_section_et_1st_analysis->SetBinContent(1,2.38715);
   h_cross_section_et_1st_analysis->SetBinContent(2,1.29);
   h_cross_section_et_1st_analysis->SetBinContent(3,0.613948);
   h_cross_section_et_1st_analysis->SetBinContent(4,0.250965);
   h_cross_section_et_1st_analysis->SetBinError(1,0.183255);
   h_cross_section_et_1st_analysis->SetBinError(2,0.104856);
   h_cross_section_et_1st_analysis->SetBinError(3,0.0769511);
   h_cross_section_et_1st_analysis->SetBinError(4,0.0270204);
   h_cross_section_et_1st_analysis->SetEntries(14126);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   h_cross_section_et_1st_analysis->SetLineColor(ci);

   ci = TColor::GetColor("#000000");
   h_cross_section_et_1st_analysis->SetMarkerColor(ci);
   h_cross_section_et_1st_analysis->SetMarkerStyle(24);
   h_cross_section_et_1st_analysis->Draw("P E1 X0 SAME");
   
   TLegend *leg = new TLegend(0.4,0.7,0.9,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_et_1st_analysis","without reweighting","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("h_cross_section_et","with reweighting","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.8);
   leg->Draw();
   canv_cross_et_1->Modified();
   canv_cross_et->cd();
  
// ------------>Primitives in pad: canv_cross_et_2
   canv_cross_et_2 = new TPad("canv_cross_et_2", "_2",0.1,0.2,0.9,0.4);
   canv_cross_et_2->Draw();
   canv_cross_et_2->cd();
   canv_cross_et_2->Range(2.256098,-0.1666667,15.67073,0.1);
   canv_cross_et_2->SetFillColor(0);
   canv_cross_et_2->SetBorderMode(0);
   canv_cross_et_2->SetBorderSize(2);
   canv_cross_et_2->SetTickx(1);
   canv_cross_et_2->SetTicky(1);
   canv_cross_et_2->SetLeftMargin(0.13);
   canv_cross_et_2->SetRightMargin(0.05);
   canv_cross_et_2->SetTopMargin(0);
   canv_cross_et_2->SetBottomMargin(0.25);
   canv_cross_et_2->SetFrameBorderMode(0);
   canv_cross_et_2->SetFrameBorderMode(0);
   Double_t xAxis76[5] = {4, 6, 8, 10, 15}; 
   
   TH2D *h_window_cross_ratio_et = new TH2D("h_window_cross_ratio_et","",4, xAxis76,10,-0.1,0.1);
   h_window_cross_ratio_et->SetStats(0);
   h_window_cross_ratio_et->GetXaxis()->SetTitle("E_{T}^{photon} (GeV)");
   h_window_cross_ratio_et->GetXaxis()->SetNdivisions(507);
   h_window_cross_ratio_et->GetXaxis()->SetLabelFont(22);
   h_window_cross_ratio_et->GetXaxis()->SetLabelSize(0.1097561);
   h_window_cross_ratio_et->GetXaxis()->SetTitleSize(0.1219512);
   h_window_cross_ratio_et->GetXaxis()->SetTickLength(0.07);
   h_window_cross_ratio_et->GetXaxis()->SetTitleOffset(0.8);
   h_window_cross_ratio_et->GetYaxis()->SetTitle("rel. difference");
   h_window_cross_ratio_et->GetYaxis()->SetNdivisions(406);
   h_window_cross_ratio_et->GetYaxis()->SetLabelFont(22);
   h_window_cross_ratio_et->GetYaxis()->SetLabelSize(0.096);
   h_window_cross_ratio_et->GetYaxis()->SetTitleSize(0.1066667);
   h_window_cross_ratio_et->GetYaxis()->SetTitleOffset(0.5);
   h_window_cross_ratio_et->Draw("");
   
   TF1 *Unity = new TF1("Unity","0",-100,500);
   Unity->SetFillColor(19);
   Unity->SetFillStyle(0);
   Unity->SetLineColor(32);
   Unity->SetLineWidth(1);
   Unity->GetXaxis()->SetTitleFont(42);
   Unity->Draw("SAME");
   Double_t xAxis77[5] = {4, 6, 8, 10, 15}; 
   
   TH1D *h_cross_section_et_ratio_1st_analysis = new TH1D("h_cross_section_et_ratio_1st_analysis","det_cross_et",4, xAxis77);
   h_cross_section_et_ratio_1st_analysis->SetBinContent(1,0.01069926);
   h_cross_section_et_ratio_1st_analysis->SetBinContent(2,0.00891588);
   h_cross_section_et_ratio_1st_analysis->SetBinContent(3,0.01465754);
   h_cross_section_et_ratio_1st_analysis->SetBinContent(4,-0.0002163583);
   h_cross_section_et_ratio_1st_analysis->SetBinError(1,0.1059446);
   h_cross_section_et_ratio_1st_analysis->SetBinError(2,0.1162721);
   h_cross_section_et_ratio_1st_analysis->SetBinError(3,0.1761374);
   h_cross_section_et_ratio_1st_analysis->SetBinError(4,0.1626544);
   h_cross_section_et_ratio_1st_analysis->SetEntries(14126);

   ci = TColor::GetColor("#000000");
   h_cross_section_et_ratio_1st_analysis->SetMarkerColor(ci);
   h_cross_section_et_ratio_1st_analysis->SetMarkerStyle(24);
   h_cross_section_et_ratio_1st_analysis->Draw("E X0 SAME");
   canv_cross_et_2->Modified();
   canv_cross_et->cd();
   canv_cross_et->Modified();
   canv_cross_et->cd();
   canv_cross_et->SetSelected(canv_cross_et);
}
