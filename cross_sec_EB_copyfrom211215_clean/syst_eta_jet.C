{
//=========Macro generated from canvas: canv_cross_eta_jet/
//=========  (Mon Sep 14 17:32:41 2015) by ROOT version5.34/00
   TCanvas *canv_cross_eta_jet = new TCanvas("canv_cross_eta_jet", "",1,1,1200,976);
   canv_cross_eta_jet->SetHighLightColor(2);
   canv_cross_eta_jet->Range(0,0,1,1);
   canv_cross_eta_jet->SetFillColor(0);
   canv_cross_eta_jet->SetBorderMode(0);
   canv_cross_eta_jet->SetBorderSize(2);
   canv_cross_eta_jet->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_eta_jet_1
   TPad *canv_cross_eta_jet_1 = new TPad("canv_cross_eta_jet_1", "canv_cross_eta_jet_1",0.01,0.01,0.99,0.99);
   canv_cross_eta_jet_1->Draw();
   canv_cross_eta_jet_1->cd();
   canv_cross_eta_jet_1->Range(-2.11875,-2.65,2.00625,12.35);
   canv_cross_eta_jet_1->SetFillColor(0);
   canv_cross_eta_jet_1->SetBorderMode(0);
   canv_cross_eta_jet_1->SetBorderSize(2);
   canv_cross_eta_jet_1->SetTickx(1);
   canv_cross_eta_jet_1->SetTicky(1);
   canv_cross_eta_jet_1->SetLeftMargin(0.15);
   canv_cross_eta_jet_1->SetRightMargin(0.05);
   canv_cross_eta_jet_1->SetBottomMargin(0.18);
   canv_cross_eta_jet_1->SetFrameBorderMode(0);
   canv_cross_eta_jet_1->SetFrameBorderMode(0);
   Double_t xAxis47[5] = {-1.5, -0.7, 0.1, 0.9, 1.8}; 
   
   TH2D *h_window_cross_eta_jet = new TH2D("h_window_cross_eta_jet","",4, xAxis47,10,0.05,11);
   h_window_cross_eta_jet->SetStats(0);
   h_window_cross_eta_jet->GetXaxis()->SetTitle("#eta^{jet}");
   h_window_cross_eta_jet->GetXaxis()->SetNdivisions(507);
   h_window_cross_eta_jet->GetXaxis()->SetLabelFont(22);
   h_window_cross_eta_jet->GetXaxis()->SetLabelSize(0.05424658);
   h_window_cross_eta_jet->GetXaxis()->SetTitleSize(0.06027398);
   h_window_cross_eta_jet->GetXaxis()->SetTitleOffset(1.02);
   h_window_cross_eta_jet->GetXaxis()->SetTitleFont(22);
   h_window_cross_eta_jet->GetYaxis()->SetTitle("d#sigma/d#eta^{jet} (pb)");
   h_window_cross_eta_jet->GetYaxis()->SetNdivisions(507);
   h_window_cross_eta_jet->GetYaxis()->SetLabelFont(22);
   h_window_cross_eta_jet->GetYaxis()->SetLabelOffset(0.016);
   h_window_cross_eta_jet->GetYaxis()->SetLabelSize(0.05424658);
   h_window_cross_eta_jet->GetYaxis()->SetTitleSize(0.06027398);
   h_window_cross_eta_jet->GetYaxis()->SetTitleOffset(0.94);
   h_window_cross_eta_jet->GetYaxis()->SetTitleFont(22);
   h_window_cross_eta_jet->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(42);
   grae->SetPoint(0,-1.1,1.668237);
   grae->SetPointError(0,0,0,0.2467529,0.1968673);
   grae->SetPoint(1,-0.3,3.090256);
   grae->SetPointError(1,0,0,0.235955,0.2016524);
   grae->SetPoint(2,0.5,4.0346);
   grae->SetPointError(2,0,0,0.2963558,0.2933978);
   grae->SetPoint(3,1.35,3.461141);
   grae->SetPointError(3,0,0,0.3679778,0.2406592);
   
   TH1F *Graph_Graph6 = new TH1F("Graph_Graph6","Graph",100,-1.345,1.595);
   Graph_Graph6->SetMinimum(1.130833);
   Graph_Graph6->SetMaximum(4.618649);
   Graph_Graph6->SetDirectory(0);
   Graph_Graph6->SetStats(0);
   Graph_Graph6->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph6);
   
   grae->Draw("e3 ");
   Double_t xAxis48[5] = {-1.5, -0.7, 0.1, 0.9, 1.8}; 
   
   TH1D *h_cross_section_eta_jet = new TH1D("h_cross_section_eta_jet","det_cross_eta_jet",4, xAxis48);
   h_cross_section_eta_jet->SetBinContent(1,1.529209);
   h_cross_section_eta_jet->SetBinContent(2,2.844649);
   h_cross_section_eta_jet->SetBinContent(3,3.910317);
   h_cross_section_eta_jet->SetBinContent(4,3.57312);
   h_cross_section_eta_jet->SetBinError(1,0.1725428);
   h_cross_section_eta_jet->SetBinError(2,0.2464578);
   h_cross_section_eta_jet->SetBinError(3,0.3293549);
   h_cross_section_eta_jet->SetBinError(4,0.2905448);
   h_cross_section_eta_jet->SetEntries(14099);
   h_cross_section_eta_jet->SetFillColor(41);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   h_cross_section_eta_jet->SetLineColor(ci);
   h_cross_section_eta_jet->SetLineWidth(2);
   h_cross_section_eta_jet->SetMarkerStyle(20);
   h_cross_section_eta_jet->GetXaxis()->SetLabelFont(42);
   h_cross_section_eta_jet->GetXaxis()->SetLabelSize(0.035);
   h_cross_section_eta_jet->GetXaxis()->SetTitleSize(0.035);
   h_cross_section_eta_jet->GetXaxis()->SetTitleFont(42);
   h_cross_section_eta_jet->GetYaxis()->SetLabelFont(42);
   h_cross_section_eta_jet->GetYaxis()->SetLabelSize(0.035);
   h_cross_section_eta_jet->GetYaxis()->SetTitleSize(0.035);
   h_cross_section_eta_jet->GetYaxis()->SetTitleFont(42);
   h_cross_section_eta_jet->GetZaxis()->SetLabelFont(42);
   h_cross_section_eta_jet->GetZaxis()->SetLabelSize(0.035);
   h_cross_section_eta_jet->GetZaxis()->SetTitleSize(0.035);
   h_cross_section_eta_jet->GetZaxis()->SetTitleFont(42);
   h_cross_section_eta_jet->Draw("E1 X0 SAME");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(20);
   grae->SetPoint(0,-1.1,1.668237);
   grae->SetPointError(0,0,0,0.3031038,0.2489373);
   grae->SetPoint(1,-0.3,3.090256);
   grae->SetPointError(1,0,0,0.3493298,0.3642982);
   grae->SetPoint(2,0.5,4.0346);
   grae->SetPointError(2,0,0,0.4587425,0.495213);
   grae->SetPoint(3,1.35,3.461141);
   grae->SetPointError(3,0,0,0.4766827,0.4285296);
   grae->Draw("e ");
   
   TLegend *leg = new TLegend(0.37,0.059,0.77,0.458,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","Bottom:","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph","jet energy uncertainty","f");

   ci = TColor::GetColor("#0000ff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(3454);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Graph","photon energy uncertainty","f");

   ci = TColor::GetColor("#ff0000");
   entry->SetFillColor(ci);
   entry->SetFillStyle(3445);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Graph","electron energy uncertainty","f");

   ci = TColor::GetColor("#00ff00");
   entry->SetFillColor(ci);
   entry->SetFillStyle(3425);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Graph","#delta Z range unc.","f");

   ci = TColor::GetColor("#ffff00");
   entry->SetFillColor(ci);
   entry->SetFillStyle(3452);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Graph","total syst. unc.","le");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   canv_cross_eta_jet_1->Modified();
   canv_cross_eta_jet->cd();
   TText *text = new TText(0.45,0.95,"ZEUS");
   text->SetTextFont(22);
   text->SetTextSize(0.07);
   text->Draw();
   canv_cross_eta_jet->Modified();
   canv_cross_eta_jet->cd();
   canv_cross_eta_jet->SetSelected(canv_cross_eta_jet);
}
