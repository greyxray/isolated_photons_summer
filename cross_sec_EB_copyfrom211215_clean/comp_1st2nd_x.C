{
//=========Macro generated from canvas: canv_cross_x/
//=========  (Mon Sep 14 17:32:40 2015) by ROOT version5.34/00
   TCanvas *canv_cross_x = new TCanvas("canv_cross_x", "",1,1,1200,976);
   canv_cross_x->SetHighLightColor(2);
   canv_cross_x->Range(0,0,1,1);
   canv_cross_x->SetFillColor(0);
   canv_cross_x->SetBorderMode(0);
   canv_cross_x->SetBorderSize(2);
   canv_cross_x->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_x_1
   TPad *canv_cross_x_1 = new TPad("canv_cross_x_1", "canv_cross_x_1",0.01,0.01,0.99,0.99);
   canv_cross_x_1->Draw();
   canv_cross_x_1->cd();
   canv_cross_x_1->Range(-4.07397,0.2376465,-1.57397,4.702903);
   canv_cross_x_1->SetFillColor(0);
   canv_cross_x_1->SetBorderMode(0);
   canv_cross_x_1->SetBorderSize(2);
   canv_cross_x_1->SetLogx();
   canv_cross_x_1->SetLogy();
   canv_cross_x_1->SetTickx(1);
   canv_cross_x_1->SetTicky(1);
   canv_cross_x_1->SetLeftMargin(0.15);
   canv_cross_x_1->SetRightMargin(0.05);
   canv_cross_x_1->SetBottomMargin(0.18);
   canv_cross_x_1->SetFrameBorderMode(0);
   canv_cross_x_1->SetFrameBorderMode(0);
   Double_t xAxis28[5] = {0.0002, 0.001, 0.003, 0.01, 0.02}; 
   
   TH2D *h_window_cross_x = new TH2D("h_window_cross_x","",4, xAxis28,10,11,20000);
   h_window_cross_x->SetStats(0);
   h_window_cross_x->GetXaxis()->SetTitle("x");
   h_window_cross_x->GetXaxis()->SetNdivisions(507);
   h_window_cross_x->GetXaxis()->SetLabelFont(22);
   h_window_cross_x->GetXaxis()->SetLabelSize(0.05424658);
   h_window_cross_x->GetXaxis()->SetTitleSize(0.06027398);
   h_window_cross_x->GetXaxis()->SetTitleOffset(1.1);
   h_window_cross_x->GetXaxis()->SetTitleFont(22);
   h_window_cross_x->GetYaxis()->SetTitle("d#sigma/dx (pb)");
   h_window_cross_x->GetYaxis()->SetNdivisions(507);
   h_window_cross_x->GetYaxis()->SetLabelFont(22);
   h_window_cross_x->GetYaxis()->SetLabelOffset(0.016);
   h_window_cross_x->GetYaxis()->SetLabelSize(0.05424658);
   h_window_cross_x->GetYaxis()->SetTitleSize(0.06027398);
   h_window_cross_x->GetYaxis()->SetTitleOffset(1.2);
   h_window_cross_x->GetYaxis()->SetTitleFont(22);
   h_window_cross_x->Draw("");
   Double_t xAxis29[5] = {0.0002, 0.001, 0.003, 0.01, 0.02}; 
   
   TH1D *h_cross_section_x = new TH1D("h_cross_section_x","det_cross_x",4, xAxis29);
   h_cross_section_x->SetBinContent(0,5.564609);
   h_cross_section_x->SetBinContent(1,4869.363);
   h_cross_section_x->SetBinContent(2,1811.322);
   h_cross_section_x->SetBinContent(3,278.144);
   h_cross_section_x->SetBinContent(4,25.08412);
   h_cross_section_x->SetBinContent(5,14.93033);
   h_cross_section_x->SetBinError(0,0.8243007);
   h_cross_section_x->SetBinError(1,333.8703);
   h_cross_section_x->SetBinError(2,139.3552);
   h_cross_section_x->SetBinError(3,31.40374);
   h_cross_section_x->SetBinError(4,6.870834);
   h_cross_section_x->SetBinError(5,1.033642);
   h_cross_section_x->SetEntries(14099);
   h_cross_section_x->SetFillColor(41);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   h_cross_section_x->SetLineColor(ci);
   h_cross_section_x->SetLineWidth(2);
   h_cross_section_x->SetMarkerStyle(20);
   h_cross_section_x->GetXaxis()->SetLabelFont(42);
   h_cross_section_x->GetXaxis()->SetLabelSize(0.035);
   h_cross_section_x->GetXaxis()->SetTitleSize(0.035);
   h_cross_section_x->GetXaxis()->SetTitleFont(42);
   h_cross_section_x->GetYaxis()->SetLabelFont(42);
   h_cross_section_x->GetYaxis()->SetLabelSize(0.035);
   h_cross_section_x->GetYaxis()->SetTitleSize(0.035);
   h_cross_section_x->GetYaxis()->SetTitleFont(42);
   h_cross_section_x->GetZaxis()->SetLabelFont(42);
   h_cross_section_x->GetZaxis()->SetLabelSize(0.035);
   h_cross_section_x->GetZaxis()->SetTitleSize(0.035);
   h_cross_section_x->GetZaxis()->SetTitleFont(42);
   h_cross_section_x->Draw("E1 X0 SAME");
   Double_t xAxis30[5] = {0.0002, 0.001, 0.003, 0.01, 0.02}; 
   
   TH1D *h_cross_section_x_1st_analysis = new TH1D("h_cross_section_x_1st_analysis","det_cross_x",4, xAxis30);
   h_cross_section_x_1st_analysis->SetBinContent(0,5.564609);
   h_cross_section_x_1st_analysis->SetBinContent(1,4734.89);
   h_cross_section_x_1st_analysis->SetBinContent(2,1741.56);
   h_cross_section_x_1st_analysis->SetBinContent(3,266.356);
   h_cross_section_x_1st_analysis->SetBinContent(4,27.8896);
   h_cross_section_x_1st_analysis->SetBinContent(5,14.93033);
   h_cross_section_x_1st_analysis->SetBinError(0,0.8243007);
   h_cross_section_x_1st_analysis->SetBinError(1,340.147);
   h_cross_section_x_1st_analysis->SetBinError(2,143.044);
   h_cross_section_x_1st_analysis->SetBinError(3,34.3157);
   h_cross_section_x_1st_analysis->SetBinError(4,7.70353);
   h_cross_section_x_1st_analysis->SetBinError(5,1.033642);
   h_cross_section_x_1st_analysis->SetEntries(14099);

   ci = TColor::GetColor("#0000ff");
   h_cross_section_x_1st_analysis->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   h_cross_section_x_1st_analysis->SetMarkerColor(ci);
   h_cross_section_x_1st_analysis->SetMarkerStyle(24);
   h_cross_section_x_1st_analysis->GetXaxis()->SetLabelFont(42);
   h_cross_section_x_1st_analysis->GetXaxis()->SetLabelSize(0.035);
   h_cross_section_x_1st_analysis->GetXaxis()->SetTitleSize(0.035);
   h_cross_section_x_1st_analysis->GetXaxis()->SetTitleFont(42);
   h_cross_section_x_1st_analysis->GetYaxis()->SetLabelFont(42);
   h_cross_section_x_1st_analysis->GetYaxis()->SetLabelSize(0.035);
   h_cross_section_x_1st_analysis->GetYaxis()->SetTitleSize(0.035);
   h_cross_section_x_1st_analysis->GetYaxis()->SetTitleFont(42);
   h_cross_section_x_1st_analysis->GetZaxis()->SetLabelFont(42);
   h_cross_section_x_1st_analysis->GetZaxis()->SetLabelSize(0.035);
   h_cross_section_x_1st_analysis->GetZaxis()->SetTitleSize(0.035);
   h_cross_section_x_1st_analysis->GetZaxis()->SetTitleFont(42);
   h_cross_section_x_1st_analysis->Draw("P E1 X0 SAME");
   
   TLegend *leg = new TLegend(0.23,0.289,0.63,0.588,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_x_1st_analysis","1st analysis","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("h_cross_section_x","2nd analysis","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();
   canv_cross_x_1->Modified();
   canv_cross_x->cd();
   TText *text = new TText(0.45,0.95,"ZEUS");
   text->SetTextFont(22);
   text->SetTextSize(0.07);
   text->Draw();
   canv_cross_x->Modified();
   canv_cross_x->cd();
   canv_cross_x->SetSelected(canv_cross_x);
}
