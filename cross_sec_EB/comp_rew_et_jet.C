{
//=========Macro generated from canvas: canv_cross_et_jet/
//=========  (Thu Jan 12 23:28:11 2012) by ROOT version5.26/00c
   TCanvas *canv_cross_et_jet = new TCanvas("canv_cross_et_jet", "",1,1,550,876);
   canv_cross_et_jet->SetHighLightColor(2);
   canv_cross_et_jet->Range(0,0,1,1);
   canv_cross_et_jet->SetFillColor(0);
   canv_cross_et_jet->SetBorderMode(0);
   canv_cross_et_jet->SetBorderSize(2);
   canv_cross_et_jet->SetTopMargin(0.04761905);
   canv_cross_et_jet->SetBottomMargin(0.05);
   canv_cross_et_jet->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_et_jet_1
   TPad *canv_cross_et_jet_1 = new TPad("canv_cross_et_jet_1", "_1",0.1,0.4,0.9,0.9);
   canv_cross_et_jet_1->Draw();
   canv_cross_et_jet_1->cd();
   canv_cross_et_jet_1->Range(-2.652439,-1.69897,36.98171,0.4771213);
   canv_cross_et_jet_1->SetFillColor(0);
   canv_cross_et_jet_1->SetBorderMode(0);
   canv_cross_et_jet_1->SetBorderSize(2);
   canv_cross_et_jet_1->SetLogy();
   canv_cross_et_jet_1->SetTickx(1);
   canv_cross_et_jet_1->SetTicky(1);
   canv_cross_et_jet_1->SetLeftMargin(0.13);
   canv_cross_et_jet_1->SetRightMargin(0.05);
   canv_cross_et_jet_1->SetTopMargin(0);
   canv_cross_et_jet_1->SetBottomMargin(0);
   canv_cross_et_jet_1->SetFrameBorderMode(0);
   canv_cross_et_jet_1->SetFrameBorderMode(0);
   Double_t xAxis93[7] = {2.5, 4, 6, 8, 10, 15, 35}; 
   
   TH2D *h_window_cross_et_jet = new TH2D("h_window_cross_et_jet","",6, xAxis93,10,0.02,3);
   h_window_cross_et_jet->SetStats(0);
   h_window_cross_et_jet->GetXaxis()->SetTitle("E_{T, jet}");
   h_window_cross_et_jet->GetXaxis()->SetNdivisions(507);
   h_window_cross_et_jet->GetXaxis()->SetLabelFont(22);
   h_window_cross_et_jet->GetXaxis()->SetLabelSize(0.04829268);
   h_window_cross_et_jet->GetXaxis()->SetTitleSize(0.05365854);
   h_window_cross_et_jet->GetXaxis()->SetTitleOffset(0.9);
   h_window_cross_et_jet->GetYaxis()->SetTitle("d#sigma/d E_{T, jet} (pb/GeV)");
   h_window_cross_et_jet->GetYaxis()->SetNdivisions(507);
   h_window_cross_et_jet->GetYaxis()->SetLabelFont(22);
   h_window_cross_et_jet->GetYaxis()->SetTitleSize(0.044);
   h_window_cross_et_jet->GetYaxis()->SetTitleOffset(0.9);
   h_window_cross_et_jet->Draw("");
   Double_t xAxis94[7] = {2.5, 4, 6, 8, 10, 15, 35}; 
   
   TH1D *h_cross_section_et_jet = new TH1D("h_cross_section_et_jet","det_cross_et_jet",6, xAxis94);
   h_cross_section_et_jet->SetBinContent(1,1.372187);
   h_cross_section_et_jet->SetBinContent(2,1.156543);
   h_cross_section_et_jet->SetBinContent(3,0.9426788);
   h_cross_section_et_jet->SetBinContent(4,0.7320863);
   h_cross_section_et_jet->SetBinContent(5,0.3056491);
   h_cross_section_et_jet->SetBinContent(6,0.02767247);
   h_cross_section_et_jet->SetBinError(1,0.1640982);
   h_cross_section_et_jet->SetBinError(2,0.1097115);
   h_cross_section_et_jet->SetBinError(3,0.09844716);
   h_cross_section_et_jet->SetBinError(4,0.08469104);
   h_cross_section_et_jet->SetBinError(5,0.03686416);
   h_cross_section_et_jet->SetBinError(6,0.006865012);
   h_cross_section_et_jet->SetEntries(14124);
   h_cross_section_et_jet->SetFillColor(41);
   h_cross_section_et_jet->SetMarkerStyle(20);
   h_cross_section_et_jet->SetMarkerSize(0.8);
   h_cross_section_et_jet->Draw("E1 X0 SAME");
   Double_t xAxis95[7] = {2.5, 4, 6, 8, 10, 15, 35}; 
   
   TH1D *h_cross_section_et_jet_1st_analysis = new TH1D("h_cross_section_et_jet_1st_analysis","det_cross_et_jet",6, xAxis95);
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
   h_cross_section_et_jet_1st_analysis->SetEntries(14130);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   h_cross_section_et_jet_1st_analysis->SetLineColor(ci);

   ci = TColor::GetColor("#000000");
   h_cross_section_et_jet_1st_analysis->SetMarkerColor(ci);
   h_cross_section_et_jet_1st_analysis->SetMarkerStyle(24);
   h_cross_section_et_jet_1st_analysis->Draw("P E1 X0 SAME");
   
   TLegend *leg = new TLegend(0.4,0.87,0.9,0.97,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_et_jet_1st_analysis","without reweighting","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("h_cross_section_et_jet","with reweighting","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.8);
   leg->Draw();
   canv_cross_et_jet_1->Modified();
   canv_cross_et_jet->cd();
  
// ------------>Primitives in pad: canv_cross_et_jet_2
   canv_cross_et_jet_2 = new TPad("canv_cross_et_jet_2", "_2",0.1,0.2,0.9,0.4);
   canv_cross_et_jet_2->Draw();
   canv_cross_et_jet_2->cd();
   canv_cross_et_jet_2->Range(-2.652439,-0.1666667,36.98171,0.1);
   canv_cross_et_jet_2->SetFillColor(0);
   canv_cross_et_jet_2->SetBorderMode(0);
   canv_cross_et_jet_2->SetBorderSize(2);
   canv_cross_et_jet_2->SetTickx(1);
   canv_cross_et_jet_2->SetTicky(1);
   canv_cross_et_jet_2->SetLeftMargin(0.13);
   canv_cross_et_jet_2->SetRightMargin(0.05);
   canv_cross_et_jet_2->SetTopMargin(0);
   canv_cross_et_jet_2->SetBottomMargin(0.25);
   canv_cross_et_jet_2->SetFrameBorderMode(0);
   canv_cross_et_jet_2->SetFrameBorderMode(0);
   Double_t xAxis96[7] = {2.5, 4, 6, 8, 10, 15, 35}; 
   
   TH2D *h_window_cross_ratio_et_jet = new TH2D("h_window_cross_ratio_et_jet","",6, xAxis96,10,-0.1,0.1);
   h_window_cross_ratio_et_jet->SetStats(0);
   h_window_cross_ratio_et_jet->GetXaxis()->SetTitle("E_{T, jet}");
   h_window_cross_ratio_et_jet->GetXaxis()->SetNdivisions(507);
   h_window_cross_ratio_et_jet->GetXaxis()->SetLabelFont(22);
   h_window_cross_ratio_et_jet->GetXaxis()->SetLabelSize(0.1097561);
   h_window_cross_ratio_et_jet->GetXaxis()->SetTitleSize(0.1219512);
   h_window_cross_ratio_et_jet->GetXaxis()->SetTickLength(0.07);
   h_window_cross_ratio_et_jet->GetXaxis()->SetTitleOffset(0.8);
   h_window_cross_ratio_et_jet->GetYaxis()->SetTitle("rel. difference");
   h_window_cross_ratio_et_jet->GetYaxis()->SetNdivisions(406);
   h_window_cross_ratio_et_jet->GetYaxis()->SetLabelFont(22);
   h_window_cross_ratio_et_jet->GetYaxis()->SetLabelSize(0.096);
   h_window_cross_ratio_et_jet->GetYaxis()->SetTitleSize(0.1066667);
   h_window_cross_ratio_et_jet->GetYaxis()->SetTitleOffset(0.5);
   h_window_cross_ratio_et_jet->Draw("");
   
   TF1 *Unity = new TF1("Unity","0",-100,500);
   Unity->SetFillColor(19);
   Unity->SetFillStyle(0);
   Unity->SetLineColor(32);
   Unity->SetLineWidth(1);
   Unity->GetXaxis()->SetTitleFont(42);
   Unity->Draw("SAME");
   Double_t xAxis97[7] = {2.5, 4, 6, 8, 10, 15, 35}; 
   
   TH1D *h_cross_section_et_jet_ratio_1st_analysis = new TH1D("h_cross_section_et_jet_ratio_1st_analysis","det_cross_et_jet",6, xAxis97);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinContent(1,0.02860884);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinContent(2,-0.001268166);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinContent(3,-0.001140584);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinContent(4,0.009991073);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinContent(5,-0.03951878);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinContent(6,-0.02555352);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinError(1,0.1688134);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinError(2,0.1335956);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinError(3,0.146368);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinError(4,0.1531693);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinError(5,0.1661349);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinError(6,0.3682612);
   h_cross_section_et_jet_ratio_1st_analysis->SetEntries(14130);

   ci = TColor::GetColor("#000000");
   h_cross_section_et_jet_ratio_1st_analysis->SetMarkerColor(ci);
   h_cross_section_et_jet_ratio_1st_analysis->SetMarkerStyle(24);
   h_cross_section_et_jet_ratio_1st_analysis->Draw("E X0 SAME");
   canv_cross_et_jet_2->Modified();
   canv_cross_et_jet->cd();
   canv_cross_et_jet->Modified();
   canv_cross_et_jet->cd();
   canv_cross_et_jet->SetSelected(canv_cross_et_jet);
}
