{
//=========Macro generated from canvas: canv_cross_et/
//=========  (Tue Jun  7 19:22:40 2011) by ROOT version5.26/00c
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
   canv_cross_et_1->Range(2.256098,0.05,15.67073,6);
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
   
   TH2D *h_window_cross_et = new TH2D("h_window_cross_et","",4, xAxis73,10,0.05,6);
   h_window_cross_et->SetStats(0);
   h_window_cross_et->GetXaxis()->SetTitle("E_{T}^{photon} (GeV)");
   h_window_cross_et->GetXaxis()->CenterTitle(true);
   h_window_cross_et->GetXaxis()->SetNdivisions(507);
   h_window_cross_et->GetXaxis()->SetLabelFont(42);
   h_window_cross_et->GetXaxis()->SetLabelSize(0.05073171);
   h_window_cross_et->GetXaxis()->SetTitleSize(0.06341463);
   h_window_cross_et->GetXaxis()->SetTitleFont(42);
   h_window_cross_et->GetYaxis()->SetTitle("d#sigma/d E_{T}^{photon} (pb/GeV)");
   h_window_cross_et->GetYaxis()->CenterTitle(true);
   h_window_cross_et->GetYaxis()->SetNdivisions(507);
   h_window_cross_et->GetYaxis()->SetLabelFont(42);
   h_window_cross_et->GetYaxis()->SetLabelSize(0.0416);
   h_window_cross_et->GetYaxis()->SetTitleSize(0.052);
   h_window_cross_et->GetYaxis()->SetTitleFont(42);
   h_window_cross_et->Draw("");
   Double_t xAxis74[5] = {4, 6, 8, 10, 15}; 
   
   TH1D *h_cross_section_et = new TH1D("h_cross_section_et","det_cross_et",4, xAxis74);
   h_cross_section_et->SetBinContent(1,2.415156);
   h_cross_section_et->SetBinContent(2,1.294092);
   h_cross_section_et->SetBinContent(3,0.6277627);
   h_cross_section_et->SetBinContent(4,0.2469974);
   h_cross_section_et->SetBinError(1,0.1924847);
   h_cross_section_et->SetBinError(2,0.110491);
   h_cross_section_et->SetBinError(3,0.07768909);
   h_cross_section_et->SetBinError(4,0.02736425);
   h_cross_section_et->SetEntries(14141);
   h_cross_section_et->SetFillColor(41);
   h_cross_section_et->SetMarkerStyle(20);
   h_cross_section_et->SetMarkerSize(0.8);
   h_cross_section_et->Draw("E1 X0 SAME");
   Double_t xAxis75[5] = {4, 6, 8, 10, 15}; 
   
   TH1D *h_cross_section_et_1st_analysis = new TH1D("h_cross_section_et_1st_analysis","det_cross_et",4, xAxis75);
   h_cross_section_et_1st_analysis->SetBinContent(1,4.87);
   h_cross_section_et_1st_analysis->SetBinContent(2,2.4);
   h_cross_section_et_1st_analysis->SetBinContent(3,1.24);
   h_cross_section_et_1st_analysis->SetBinContent(4,0.55);
   h_cross_section_et_1st_analysis->SetBinError(1,0.28);
   h_cross_section_et_1st_analysis->SetBinError(2,0.16);
   h_cross_section_et_1st_analysis->SetBinError(3,0.11);
   h_cross_section_et_1st_analysis->SetBinError(4,0.04);
   h_cross_section_et_1st_analysis->SetEntries(14145);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   h_cross_section_et_1st_analysis->SetLineColor(ci);

   ci = TColor::GetColor("#000000");
   h_cross_section_et_1st_analysis->SetMarkerColor(ci);
   h_cross_section_et_1st_analysis->SetMarkerStyle(21);
   h_cross_section_et_1st_analysis->SetMarkerSize(0.8);
   h_cross_section_et_1st_analysis->Draw("P E1 X0 SAME");
   
   TLegend *leg = new TLegend(0.4,0.7,0.9,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_et_1st_analysis","Matthew","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(0.8);
   entry=leg->AddEntry("h_cross_section_et","Oleg & Nataliia","p");
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
   canv_cross_et_2->Range(2.256098,-0.875,15.67073,0.525);
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
   
   TH2D *h_window_cross_ratio_et = new TH2D("h_window_cross_ratio_et","",4, xAxis76,10,-0.525,0.525);
   h_window_cross_ratio_et->SetStats(0);
   h_window_cross_ratio_et->GetXaxis()->SetTitle("E_{T}^{photon} (GeV)");
   h_window_cross_ratio_et->GetXaxis()->CenterTitle(true);
   h_window_cross_ratio_et->GetXaxis()->SetNdivisions(507);
   h_window_cross_ratio_et->GetXaxis()->SetLabelFont(42);
   h_window_cross_ratio_et->GetXaxis()->SetLabelSize(0.09756097);
   h_window_cross_ratio_et->GetXaxis()->SetTitleSize(0.1219512);
   h_window_cross_ratio_et->GetXaxis()->SetTickLength(0.07);
   h_window_cross_ratio_et->GetXaxis()->SetTitleOffset(0.8);
   h_window_cross_ratio_et->GetXaxis()->SetTitleFont(42);
   h_window_cross_ratio_et->GetYaxis()->SetTitle("rel. difference");
   h_window_cross_ratio_et->GetYaxis()->CenterTitle(true);
   h_window_cross_ratio_et->GetYaxis()->SetNdivisions(406);
   h_window_cross_ratio_et->GetYaxis()->SetLabelFont(42);
   h_window_cross_ratio_et->GetYaxis()->SetLabelSize(0.08533333);
   h_window_cross_ratio_et->GetYaxis()->SetTitleSize(0.1066667);
   h_window_cross_ratio_et->GetYaxis()->SetTitleOffset(0.5);
   h_window_cross_ratio_et->GetYaxis()->SetTitleFont(42);
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
   h_cross_section_et_ratio_1st_analysis->SetBinContent(1,-1.016433);
   h_cross_section_et_ratio_1st_analysis->SetBinContent(2,-0.8545817);
   h_cross_section_et_ratio_1st_analysis->SetBinContent(3,-0.9752688);
   h_cross_section_et_ratio_1st_analysis->SetBinContent(4,-1.226744);
   h_cross_section_et_ratio_1st_analysis->SetBinError(1,0.1981604);
   h_cross_section_et_ratio_1st_analysis->SetBinError(2,0.2008981);
   h_cross_section_et_ratio_1st_analysis->SetBinError(3,0.3007656);
   h_cross_section_et_ratio_1st_analysis->SetBinError(4,0.2951016);
   h_cross_section_et_ratio_1st_analysis->SetEntries(14145);

   ci = TColor::GetColor("#000000");
   h_cross_section_et_ratio_1st_analysis->SetMarkerColor(ci);
   h_cross_section_et_ratio_1st_analysis->SetMarkerStyle(21);
   h_cross_section_et_ratio_1st_analysis->SetMarkerSize(0.8);
   h_cross_section_et_ratio_1st_analysis->Draw("E X0 SAME");
   canv_cross_et_2->Modified();
   canv_cross_et->cd();
   canv_cross_et->Modified();
   canv_cross_et->cd();
   canv_cross_et->SetSelected(canv_cross_et);
}
