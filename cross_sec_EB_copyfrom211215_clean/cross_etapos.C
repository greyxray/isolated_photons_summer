{
//=========Macro generated from canvas: canv_cross_eta/
//=========  (Fri Jan 27 02:10:52 2012) by ROOT version5.26/00c
   TCanvas *canv_cross_eta = new TCanvas("canv_cross_eta", "",0,0,1200,900);
   canv_cross_eta->SetHighLightColor(2);
   canv_cross_eta->Range(0,0,1,1);
   canv_cross_eta->SetFillColor(0);
   canv_cross_eta->SetBorderMode(0);
   canv_cross_eta->SetBorderSize(2);
   canv_cross_eta->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_eta_1
   TPad *canv_cross_eta_1 = new TPad("canv_cross_eta_1", "canv_cross_eta_1",0.01,0.01,0.99,0.99);
   canv_cross_eta_1->Draw();
   canv_cross_eta_1->cd();
   canv_cross_eta_1->Range(-0.9536585,-3.759589,0.997561,17.40479);
   canv_cross_eta_1->SetFillColor(0);
   canv_cross_eta_1->SetBorderMode(0);
   canv_cross_eta_1->SetBorderSize(2);
   canv_cross_eta_1->SetGridy();
   canv_cross_eta_1->SetTickx(1);
   canv_cross_eta_1->SetTicky(1);
   canv_cross_eta_1->SetLeftMargin(0.13);
   canv_cross_eta_1->SetRightMargin(0.05);
   canv_cross_eta_1->SetBottomMargin(0.18);
   canv_cross_eta_1->SetFrameBorderMode(0);
   canv_cross_eta_1->SetFrameBorderMode(0);
   Double_t xAxis3[5] = {-0.7, -0.3, 0.1, 0.5, 0.9}; 
   
   TH2D *h_window_cross_eta = new TH2D("h_window_cross_eta","",4, xAxis3,10,0.05,15.5);
   h_window_cross_eta->SetStats(0);
   h_window_cross_eta->GetXaxis()->SetTitle("#eta^{#gamma}");
   h_window_cross_eta->GetXaxis()->SetNdivisions(507);
   h_window_cross_eta->GetXaxis()->SetLabelFont(22);
   h_window_cross_eta->GetXaxis()->SetLabelSize(0.04829268);
   h_window_cross_eta->GetXaxis()->SetTitleSize(0.05365854);
   h_window_cross_eta->GetXaxis()->SetTitleOffset(0.9);
   h_window_cross_eta->GetYaxis()->SetTitle("d#sigma/d #eta^{#gamma} (pb)");
   h_window_cross_eta->GetYaxis()->SetNdivisions(507);
   h_window_cross_eta->GetYaxis()->SetLabelFont(22);
   h_window_cross_eta->GetYaxis()->SetLabelSize(0.05424658);
   h_window_cross_eta->GetYaxis()->SetTitleSize(0.06027398);
   h_window_cross_eta->GetYaxis()->SetTitleOffset(0.9);
   h_window_cross_eta->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3003);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-0.5,7.697);
   grae->SetPointError(0,0.2,0.2,1.298,1.093);
   grae->SetPoint(1,-0.1,5.853);
   grae->SetPointError(1,0.2,0.2,0.991,0.832);
   grae->SetPoint(2,0.3,5.382);
   grae->SetPointError(2,0.2,0.2,0.85,0.694);
   grae->SetPoint(3,0.7,5.159);
   grae->SetPointError(3,0.2,0.2,0.705,0.565);
   
   TH1F *Graph5 = new TH1F("Graph5","Graph",100,-0.86,1.06);
   Graph5->SetMinimum(4.0204);
   Graph5->SetMaximum(9.2236);
   Graph5->SetDirectory(0);
   Graph5->SetStats(0);
   Graph5->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph5);
   
   grae->Draw("2 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3018);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-0.5,6.728);
   grae->SetPointError(0,0.2,0.2,0.392,0.39);
   grae->SetPoint(1,-0.1,5.305);
   grae->SetPointError(1,0.2,0.2,0.254,0.304);
   grae->SetPoint(2,0.3,5.027);
   grae->SetPointError(2,0.2,0.2,0.243,0.18);
   grae->SetPoint(3,0.7,4.827);
   grae->SetPointError(3,0.2,0.2,0.219,0.184);
   
   TH1F *Graph6 = new TH1F("Graph6","Graph",100,-0.668,1.252);
   Graph6->SetMinimum(4.357);
   Graph6->SetMaximum(7.369);
   Graph6->SetDirectory(0);
   Graph6->SetStats(0);
   Graph6->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph6);
   
   grae->Draw("2 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3003);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-0.5,7.697);
   grae->SetPointError(0,0.2,0.2,1.298,1.093);
   grae->SetPoint(1,-0.1,5.853);
   grae->SetPointError(1,0.2,0.2,0.991,0.832);
   grae->SetPoint(2,0.3,5.382);
   grae->SetPointError(2,0.2,0.2,0.85,0.694);
   grae->SetPoint(3,0.7,5.159);
   grae->SetPointError(3,0.2,0.2,0.705,0.565);
   
   TH1F *Graph57 = new TH1F("Graph57","Graph",100,-0.86,1.06);
   Graph57->SetMinimum(4.0204);
   Graph57->SetMaximum(9.2236);
   Graph57->SetDirectory(0);
   Graph57->SetStats(0);
   Graph57->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph57);
   
   grae->Draw("5 z ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3018);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-0.5,6.728);
   grae->SetPointError(0,0.2,0.2,0.392,0.39);
   grae->SetPoint(1,-0.1,5.305);
   grae->SetPointError(1,0.2,0.2,0.254,0.304);
   grae->SetPoint(2,0.3,5.027);
   grae->SetPointError(2,0.2,0.2,0.243,0.18);
   grae->SetPoint(3,0.7,4.827);
   grae->SetPointError(3,0.2,0.2,0.219,0.184);
   
   TH1F *Graph68 = new TH1F("Graph68","Graph",100,-0.668,1.252);
   Graph68->SetMinimum(4.357);
   Graph68->SetMaximum(7.369);
   Graph68->SetDirectory(0);
   Graph68->SetStats(0);
   Graph68->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph68);
   
   grae->Draw("5 z ");
   Double_t xAxis4[5] = {-0.7, -0.3, 0.1, 0.5, 0.9}; 
   
   TH1D *h_cross_section_eta = new TH1D("h_cross_section_eta","det_cross_eta",4, xAxis4);
   h_cross_section_eta->SetBinContent(1,7.666201);
   h_cross_section_eta->SetBinContent(2,6.613177);
   h_cross_section_eta->SetBinContent(3,5.68822);
   h_cross_section_eta->SetBinContent(4,5.206515);
   h_cross_section_eta->SetBinError(1,0.5960687);
   h_cross_section_eta->SetBinError(2,0.5109063);
   h_cross_section_eta->SetBinError(3,0.5242988);
   h_cross_section_eta->SetBinError(4,0.526018);
   h_cross_section_eta->SetEntries(14122);
   h_cross_section_eta->SetFillColor(41);
   h_cross_section_eta->SetLineWidth(2);
   h_cross_section_eta->SetMarkerStyle(20);
   h_cross_section_eta->SetMarkerSize(1.1);
   h_cross_section_eta->Draw("E1 X0 SAME");
   
   TLegend *leg = new TLegend(0.5,0.55,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_eta","ZEUS (prel.) 326 pb^{-1}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1.1);
   entry=leg->AddEntry("Graph","Spiesberger et al., e^{+}p, NLO","fl");

   ci = TColor::GetColor("#000000");
   entry->SetFillColor(ci);
   entry->SetFillStyle(3018);

   ci = TColor::GetColor("#000000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Graph","Spiesberger et al., e^{+}p, LO","fl");

   ci = TColor::GetColor("#000000");
   entry->SetFillColor(ci);
   entry->SetFillStyle(3003);

   ci = TColor::GetColor("#000000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   canv_cross_eta_1->Modified();
   canv_cross_eta->cd();
   TText *text = new TText(0.45,0.92,"ZEUS");
   text->SetTextSize(0.07);
   text->Draw();
   canv_cross_eta->Modified();
   canv_cross_eta->cd();
   canv_cross_eta->SetSelected(canv_cross_eta);
}
