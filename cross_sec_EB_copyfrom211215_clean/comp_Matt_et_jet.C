{
//=========Macro generated from canvas: canv_cross_et_jet/
//=========  (Tue Jun  7 19:22:41 2011) by ROOT version5.26/00c
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
   canv_cross_et_jet_1->Range(-2.652439,-1.30103,36.98171,0.4771213);
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
   
   TH2D *h_window_cross_et_jet = new TH2D("h_window_cross_et_jet","",6, xAxis93,10,0.05,3);
   h_window_cross_et_jet->SetStats(0);
   h_window_cross_et_jet->GetXaxis()->SetTitle("E_{T, jet}");
   h_window_cross_et_jet->GetXaxis()->CenterTitle(true);
   h_window_cross_et_jet->GetXaxis()->SetNdivisions(507);
   h_window_cross_et_jet->GetXaxis()->SetLabelFont(42);
   h_window_cross_et_jet->GetXaxis()->SetLabelSize(0.05073171);
   h_window_cross_et_jet->GetXaxis()->SetTitleSize(0.06341463);
   h_window_cross_et_jet->GetXaxis()->SetTitleFont(42);
   h_window_cross_et_jet->GetYaxis()->SetTitle("d#sigma/d E_{T, jet} (pb/GeV)");
   h_window_cross_et_jet->GetYaxis()->CenterTitle(true);
   h_window_cross_et_jet->GetYaxis()->SetNdivisions(507);
   h_window_cross_et_jet->GetYaxis()->SetLabelFont(42);
   h_window_cross_et_jet->GetYaxis()->SetLabelSize(0.0416);
   h_window_cross_et_jet->GetYaxis()->SetTitleSize(0.052);
   h_window_cross_et_jet->GetYaxis()->SetTitleFont(42);
   h_window_cross_et_jet->Draw("");
   Double_t xAxis94[7] = {2.5, 4, 6, 8, 10, 15, 35}; 
   
   TH1D *h_cross_section_et_jet = new TH1D("h_cross_section_et_jet","det_cross_et_jet",6, xAxis94);
   h_cross_section_et_jet->SetBinContent(1,1.418729);
   h_cross_section_et_jet->SetBinContent(2,1.131108);
   h_cross_section_et_jet->SetBinContent(3,0.9539788);
   h_cross_section_et_jet->SetBinContent(4,0.721862);
   h_cross_section_et_jet->SetBinContent(5,0.3174531);
   h_cross_section_et_jet->SetBinContent(6,0.03257214);
   h_cross_section_et_jet->SetBinError(1,0.1708303);
   h_cross_section_et_jet->SetBinError(2,0.1134837);
   h_cross_section_et_jet->SetBinError(3,0.1013478);
   h_cross_section_et_jet->SetBinError(4,0.07727232);
   h_cross_section_et_jet->SetBinError(5,0.03361493);
   h_cross_section_et_jet->SetBinError(6,0.005935494);
   h_cross_section_et_jet->SetEntries(14147);
   h_cross_section_et_jet->SetFillColor(41);
   h_cross_section_et_jet->SetMarkerStyle(20);
   h_cross_section_et_jet->SetMarkerSize(0.8);
   h_cross_section_et_jet->Draw("E1 X0 SAME");
   Double_t xAxis95[7] = {2.5, 4, 6, 8, 10, 15, 35}; 
   
   TH1D *h_cross_section_et_jet_1st_analysis = new TH1D("h_cross_section_et_jet_1st_analysis","det_cross_et_jet",6, xAxis95);
   h_cross_section_et_jet_1st_analysis->SetBinContent(1,1.03691);
   h_cross_section_et_jet_1st_analysis->SetBinContent(2,0.755783);
   h_cross_section_et_jet_1st_analysis->SetBinContent(3,0.592027);
   h_cross_section_et_jet_1st_analysis->SetBinContent(4,0.443129);
   h_cross_section_et_jet_1st_analysis->SetBinContent(5,0.0918591);
   h_cross_section_et_jet_1st_analysis->SetBinContent(6,0.00256088);
   h_cross_section_et_jet_1st_analysis->SetBinError(1,0.178649);
   h_cross_section_et_jet_1st_analysis->SetBinError(2,0.112149);
   h_cross_section_et_jet_1st_analysis->SetBinError(3,0.0944979);
   h_cross_section_et_jet_1st_analysis->SetBinError(4,0.0670221);
   h_cross_section_et_jet_1st_analysis->SetBinError(5,0.026565);
   h_cross_section_et_jet_1st_analysis->SetBinError(6,0.00389595);
   h_cross_section_et_jet_1st_analysis->SetEntries(14153);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   h_cross_section_et_jet_1st_analysis->SetLineColor(ci);

   ci = TColor::GetColor("#000000");
   h_cross_section_et_jet_1st_analysis->SetMarkerColor(ci);
   h_cross_section_et_jet_1st_analysis->SetMarkerStyle(21);
   h_cross_section_et_jet_1st_analysis->SetMarkerSize(0.8);
   h_cross_section_et_jet_1st_analysis->Draw("P E1 X0 SAME");
   
   TLegend *leg = new TLegend(0.4,0.87,0.9,0.97,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_et_jet_1st_analysis","Matthew","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(0.8);
   entry=leg->AddEntry("h_cross_section_et_jet","Oleg & Nataliia","p");
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
   canv_cross_et_jet_2->Range(-2.652439,-0.7083333,36.98171,0.425);
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
   
   TH2D *h_window_cross_ratio_et_jet = new TH2D("h_window_cross_ratio_et_jet","",6, xAxis96,10,-0.425,0.425);
   h_window_cross_ratio_et_jet->SetStats(0);
   h_window_cross_ratio_et_jet->GetXaxis()->SetTitle("E_{T, jet}");
   h_window_cross_ratio_et_jet->GetXaxis()->CenterTitle(true);
   h_window_cross_ratio_et_jet->GetXaxis()->SetNdivisions(507);
   h_window_cross_ratio_et_jet->GetXaxis()->SetLabelFont(42);
   h_window_cross_ratio_et_jet->GetXaxis()->SetLabelSize(0.09756097);
   h_window_cross_ratio_et_jet->GetXaxis()->SetTitleSize(0.1219512);
   h_window_cross_ratio_et_jet->GetXaxis()->SetTickLength(0.07);
   h_window_cross_ratio_et_jet->GetXaxis()->SetTitleOffset(0.8);
   h_window_cross_ratio_et_jet->GetXaxis()->SetTitleFont(42);
   h_window_cross_ratio_et_jet->GetYaxis()->SetTitle("rel. difference");
   h_window_cross_ratio_et_jet->GetYaxis()->CenterTitle(true);
   h_window_cross_ratio_et_jet->GetYaxis()->SetNdivisions(406);
   h_window_cross_ratio_et_jet->GetYaxis()->SetLabelFont(42);
   h_window_cross_ratio_et_jet->GetYaxis()->SetLabelSize(0.08533333);
   h_window_cross_ratio_et_jet->GetYaxis()->SetTitleSize(0.1066667);
   h_window_cross_ratio_et_jet->GetYaxis()->SetTitleOffset(0.5);
   h_window_cross_ratio_et_jet->GetYaxis()->SetTitleFont(42);
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
   h_cross_section_et_jet_ratio_1st_analysis->SetBinContent(1,0.2691278);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinContent(2,0.3318208);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinContent(3,0.3794129);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinContent(4,0.3861306);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinContent(5,0.7106372);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinContent(6,0.9213782);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinError(1,0.1536267);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinError(2,0.1196862);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinError(3,0.1189911);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinError(4,0.1137475);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinError(5,0.08911486);
   h_cross_section_et_jet_ratio_1st_analysis->SetBinError(6,0.1204649);
   h_cross_section_et_jet_ratio_1st_analysis->SetEntries(14153);

   ci = TColor::GetColor("#000000");
   h_cross_section_et_jet_ratio_1st_analysis->SetMarkerColor(ci);
   h_cross_section_et_jet_ratio_1st_analysis->SetMarkerStyle(21);
   h_cross_section_et_jet_ratio_1st_analysis->SetMarkerSize(0.8);
   h_cross_section_et_jet_ratio_1st_analysis->Draw("E X0 SAME");
   canv_cross_et_jet_2->Modified();
   canv_cross_et_jet->cd();
   canv_cross_et_jet->Modified();
   canv_cross_et_jet->cd();
   canv_cross_et_jet->SetSelected(canv_cross_et_jet);
}
