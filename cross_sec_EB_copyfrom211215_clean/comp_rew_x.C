{
//=========Macro generated from canvas: canv_cross_x/
//=========  (Thu Jan 12 23:28:11 2012) by ROOT version5.26/00c
   TCanvas *canv_cross_x = new TCanvas("canv_cross_x", "",1,1,550,876);
   canv_cross_x->SetHighLightColor(2);
   canv_cross_x->Range(0,0,1,1);
   canv_cross_x->SetFillColor(0);
   canv_cross_x->SetBorderMode(0);
   canv_cross_x->SetBorderSize(2);
   canv_cross_x->SetTopMargin(0.04761905);
   canv_cross_x->SetBottomMargin(0.05);
   canv_cross_x->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_x_1
   TPad *canv_cross_x_1 = new TPad("canv_cross_x_1", "_1",0.1,0.4,0.9,0.9);
   canv_cross_x_1->Draw();
   canv_cross_x_1->cd();
   canv_cross_x_1->Range(-4.016043,1.041393,-1.577019,4);
   canv_cross_x_1->SetFillColor(0);
   canv_cross_x_1->SetBorderMode(0);
   canv_cross_x_1->SetBorderSize(2);
   canv_cross_x_1->SetLogx();
   canv_cross_x_1->SetLogy();
   canv_cross_x_1->SetTickx(1);
   canv_cross_x_1->SetTicky(1);
   canv_cross_x_1->SetLeftMargin(0.13);
   canv_cross_x_1->SetRightMargin(0.05);
   canv_cross_x_1->SetTopMargin(0);
   canv_cross_x_1->SetBottomMargin(0);
   canv_cross_x_1->SetFrameBorderMode(0);
   canv_cross_x_1->SetFrameBorderMode(0);
   Double_t xAxis88[5] = {0.0002, 0.001, 0.003, 0.01, 0.02}; 
   
   TH2D *h_window_cross_x = new TH2D("h_window_cross_x","",4, xAxis88,10,11,10000);
   h_window_cross_x->SetStats(0);
   h_window_cross_x->GetXaxis()->SetTitle("x");
   h_window_cross_x->GetXaxis()->SetNdivisions(507);
   h_window_cross_x->GetXaxis()->SetLabelFont(22);
   h_window_cross_x->GetXaxis()->SetLabelSize(0.04829268);
   h_window_cross_x->GetXaxis()->SetTitleSize(0.05365854);
   h_window_cross_x->GetXaxis()->SetTitleOffset(0.9);
   h_window_cross_x->GetYaxis()->SetTitle("d#sigma/d x (pb)");
   h_window_cross_x->GetYaxis()->SetNdivisions(507);
   h_window_cross_x->GetYaxis()->SetLabelFont(22);
   h_window_cross_x->GetYaxis()->SetTitleSize(0.044);
   h_window_cross_x->GetYaxis()->SetTitleOffset(0.9);
   h_window_cross_x->Draw("");
   Double_t xAxis89[5] = {0.0002, 0.001, 0.003, 0.01, 0.02}; 
   
   TH1D *h_cross_section_x = new TH1D("h_cross_section_x","det_cross_x",4, xAxis89);
   h_cross_section_x->SetBinContent(0,4.484542);
   h_cross_section_x->SetBinContent(1,4753.19);
   h_cross_section_x->SetBinContent(2,1784.736);
   h_cross_section_x->SetBinContent(3,277.5644);
   h_cross_section_x->SetBinContent(4,26.59717);
   h_cross_section_x->SetBinContent(5,24.29127);
   h_cross_section_x->SetBinError(0,0.6472879);
   h_cross_section_x->SetBinError(1,355.8699);
   h_cross_section_x->SetBinError(2,146.5498);
   h_cross_section_x->SetBinError(3,32.53525);
   h_cross_section_x->SetBinError(4,7.520558);
   h_cross_section_x->SetBinError(5,1.506481);
   h_cross_section_x->SetEntries(14122);
   h_cross_section_x->SetFillColor(41);
   h_cross_section_x->SetMarkerStyle(20);
   h_cross_section_x->SetMarkerSize(0.8);
   h_cross_section_x->Draw("E1 X0 SAME");
   Double_t xAxis90[5] = {0.0002, 0.001, 0.003, 0.01, 0.02}; 
   
   TH1D *h_cross_section_x_1st_analysis = new TH1D("h_cross_section_x_1st_analysis","det_cross_x",4, xAxis90);
   h_cross_section_x_1st_analysis->SetBinContent(0,4.484542);
   h_cross_section_x_1st_analysis->SetBinContent(1,4734.89);
   h_cross_section_x_1st_analysis->SetBinContent(2,1741.56);
   h_cross_section_x_1st_analysis->SetBinContent(3,266.356);
   h_cross_section_x_1st_analysis->SetBinContent(4,27.8896);
   h_cross_section_x_1st_analysis->SetBinContent(5,24.29127);
   h_cross_section_x_1st_analysis->SetBinError(0,0.6472879);
   h_cross_section_x_1st_analysis->SetBinError(1,340.147);
   h_cross_section_x_1st_analysis->SetBinError(2,143.044);
   h_cross_section_x_1st_analysis->SetBinError(3,34.3157);
   h_cross_section_x_1st_analysis->SetBinError(4,7.70353);
   h_cross_section_x_1st_analysis->SetBinError(5,1.506481);
   h_cross_section_x_1st_analysis->SetEntries(14126);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   h_cross_section_x_1st_analysis->SetLineColor(ci);

   ci = TColor::GetColor("#000000");
   h_cross_section_x_1st_analysis->SetMarkerColor(ci);
   h_cross_section_x_1st_analysis->SetMarkerStyle(24);
   h_cross_section_x_1st_analysis->Draw("P E1 X0 SAME");
   
   TLegend *leg = new TLegend(0.23,0.289,0.63,0.588,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_x_1st_analysis","without reweighting","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("h_cross_section_x","with reweighting","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.8);
   leg->Draw();
   canv_cross_x_1->Modified();
   canv_cross_x->cd();
  
// ------------>Primitives in pad: canv_cross_x_2
   canv_cross_x_2 = new TPad("canv_cross_x_2", "_2",0.1,0.2,0.9,0.4);
   canv_cross_x_2->Draw();
   canv_cross_x_2->cd();
   canv_cross_x_2->Range(-4.016043,-0.1666667,-1.577019,0.1);
   canv_cross_x_2->SetFillColor(0);
   canv_cross_x_2->SetBorderMode(0);
   canv_cross_x_2->SetBorderSize(2);
   canv_cross_x_2->SetLogx();
   canv_cross_x_2->SetTickx(1);
   canv_cross_x_2->SetTicky(1);
   canv_cross_x_2->SetLeftMargin(0.13);
   canv_cross_x_2->SetRightMargin(0.05);
   canv_cross_x_2->SetTopMargin(0);
   canv_cross_x_2->SetBottomMargin(0.25);
   canv_cross_x_2->SetFrameBorderMode(0);
   canv_cross_x_2->SetFrameBorderMode(0);
   Double_t xAxis91[5] = {0.0002, 0.001, 0.003, 0.01, 0.02}; 
   
   TH2D *h_window_cross_ratio_x = new TH2D("h_window_cross_ratio_x","",4, xAxis91,10,-0.1,0.1);
   h_window_cross_ratio_x->SetStats(0);
   h_window_cross_ratio_x->GetXaxis()->SetTitle("x");
   h_window_cross_ratio_x->GetXaxis()->SetNdivisions(507);
   h_window_cross_ratio_x->GetXaxis()->SetLabelFont(22);
   h_window_cross_ratio_x->GetXaxis()->SetLabelSize(0.1097561);
   h_window_cross_ratio_x->GetXaxis()->SetTitleSize(0.1219512);
   h_window_cross_ratio_x->GetXaxis()->SetTickLength(0.07);
   h_window_cross_ratio_x->GetXaxis()->SetTitleOffset(0.8);
   h_window_cross_ratio_x->GetYaxis()->SetTitle("rel. difference");
   h_window_cross_ratio_x->GetYaxis()->SetNdivisions(406);
   h_window_cross_ratio_x->GetYaxis()->SetLabelFont(22);
   h_window_cross_ratio_x->GetYaxis()->SetLabelSize(0.096);
   h_window_cross_ratio_x->GetYaxis()->SetTitleSize(0.1066667);
   h_window_cross_ratio_x->GetYaxis()->SetTitleOffset(0.5);
   h_window_cross_ratio_x->Draw("");
   
   TF1 *Unity = new TF1("Unity","0",-100,500);
   Unity->SetFillColor(19);
   Unity->SetFillStyle(0);
   Unity->SetLineColor(32);
   Unity->SetLineWidth(1);
   Unity->GetXaxis()->SetTitleFont(42);
   Unity->Draw("SAME");
   Double_t xAxis92[5] = {0.0002, 0.001, 0.003, 0.01, 0.02}; 
   
   TH1D *h_cross_section_x_ratio_1st_analysis = new TH1D("h_cross_section_x_ratio_1st_analysis","det_cross_x",4, xAxis92);
   h_cross_section_x_ratio_1st_analysis->SetBinContent(0,4.484542);
   h_cross_section_x_ratio_1st_analysis->SetBinContent(1,0.003849987);
   h_cross_section_x_ratio_1st_analysis->SetBinContent(2,0.02419166);
   h_cross_section_x_ratio_1st_analysis->SetBinContent(3,0.0403813);
   h_cross_section_x_ratio_1st_analysis->SetBinContent(4,-0.04859293);
   h_cross_section_x_ratio_1st_analysis->SetBinContent(5,24.29127);
   h_cross_section_x_ratio_1st_analysis->SetBinError(0,0.6472879);
   h_cross_section_x_ratio_1st_analysis->SetBinError(1,0.103361);
   h_cross_section_x_ratio_1st_analysis->SetBinError(2,0.1133315);
   h_cross_section_x_ratio_1st_analysis->SetBinError(3,0.1671445);
   h_cross_section_x_ratio_1st_analysis->SetBinError(4,0.4144886);
   h_cross_section_x_ratio_1st_analysis->SetBinError(5,1.506481);
   h_cross_section_x_ratio_1st_analysis->SetEntries(14126);

   ci = TColor::GetColor("#000000");
   h_cross_section_x_ratio_1st_analysis->SetMarkerColor(ci);
   h_cross_section_x_ratio_1st_analysis->SetMarkerStyle(24);
   h_cross_section_x_ratio_1st_analysis->Draw("E X0 SAME");
   canv_cross_x_2->Modified();
   canv_cross_x->cd();
   canv_cross_x->Modified();
   canv_cross_x->cd();
   canv_cross_x->SetSelected(canv_cross_x);
}
