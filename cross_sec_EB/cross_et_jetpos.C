{
//=========Macro generated from canvas: canv_cross_et_jet/
//=========  (Fri Jan 27 02:10:53 2012) by ROOT version5.26/00c
   TCanvas *canv_cross_et_jet = new TCanvas("canv_cross_et_jet", "",0,0,1200,900);
   canv_cross_et_jet->SetHighLightColor(2);
   canv_cross_et_jet->Range(0,0,1,1);
   canv_cross_et_jet->SetFillColor(0);
   canv_cross_et_jet->SetBorderMode(0);
   canv_cross_et_jet->SetBorderSize(2);
   canv_cross_et_jet->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_et_jet_1
   TPad *canv_cross_et_jet_1 = new TPad("canv_cross_et_jet_1", "canv_cross_et_jet_1",0.01,0.01,0.99,0.99);
   canv_cross_et_jet_1->Draw();
   canv_cross_et_jet_1->cd();
   canv_cross_et_jet_1->Range(-2.652439,-2.391286,36.98171,0.7608099);
   canv_cross_et_jet_1->SetFillColor(0);
   canv_cross_et_jet_1->SetBorderMode(0);
   canv_cross_et_jet_1->SetBorderSize(2);
   canv_cross_et_jet_1->SetLogy();
   canv_cross_et_jet_1->SetGridy();
   canv_cross_et_jet_1->SetTickx(1);
   canv_cross_et_jet_1->SetTicky(1);
   canv_cross_et_jet_1->SetLeftMargin(0.13);
   canv_cross_et_jet_1->SetRightMargin(0.05);
   canv_cross_et_jet_1->SetBottomMargin(0.18);
   canv_cross_et_jet_1->SetFrameBorderMode(0);
   canv_cross_et_jet_1->SetFrameBorderMode(0);
   Double_t xAxis9[7] = {2.5, 4, 6, 8, 10, 15, 35}; 
   
   TH2D *h_window_cross_et_jet = new TH2D("h_window_cross_et_jet","",6, xAxis9,10,0.015,3);
   h_window_cross_et_jet->SetStats(0);
   h_window_cross_et_jet->GetXaxis()->SetTitle("E_{T}^{jet} (GeV)");
   h_window_cross_et_jet->GetXaxis()->SetNdivisions(507);
   h_window_cross_et_jet->GetXaxis()->SetLabelFont(22);
   h_window_cross_et_jet->GetXaxis()->SetLabelSize(0.04829268);
   h_window_cross_et_jet->GetXaxis()->SetTitleSize(0.05365854);
   h_window_cross_et_jet->GetXaxis()->SetTitleOffset(0.9);
   h_window_cross_et_jet->GetYaxis()->SetTitle("d#sigma/d E_{T}^{jet} (pb/GeV)");
   h_window_cross_et_jet->GetYaxis()->SetNdivisions(507);
   h_window_cross_et_jet->GetYaxis()->SetLabelFont(22);
   h_window_cross_et_jet->GetYaxis()->SetLabelSize(0.05424658);
   h_window_cross_et_jet->GetYaxis()->SetTitleSize(0.06027398);
   h_window_cross_et_jet->GetYaxis()->SetTitleOffset(0.9);
   h_window_cross_et_jet->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3003);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,3.25,1.464);
   grae->SetPointError(0,0.75,0.75,0.344,0.289);
   grae->SetPoint(1,5,1.111);
   grae->SetPointError(1,1,1,0.2059,0.171);
   grae->SetPoint(2,7,0.883);
   grae->SetPointError(2,1,1,0.1338,0.1116);
   grae->SetPoint(3,9,0.6402);
   grae->SetPointError(3,1,1,0.0804,0.0657);
   grae->SetPoint(4,12.5,0.3149);
   grae->SetPointError(4,2.5,2.5,0.0295,0.0238);
   grae->SetPoint(5,25,0.0297);
   grae->SetPointError(5,10,10,0.00145,0.00106);
   
   TH1F *Graph17 = new TH1F("Graph17","Graph",100,0,38.25);
   Graph17->SetMinimum(0.025425);
   Graph17->SetMaximum(1.925475);
   Graph17->SetDirectory(0);
   Graph17->SetStats(0);
   Graph17->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph17);
   
   grae->Draw("2 ");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3018);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,3.25,1.297);
   grae->SetPointError(0,0.75,0.75,0.1,0.107);
   grae->SetPoint(1,5,1.0375);
   grae->SetPointError(1,1,1,0.0633,0.054);
   grae->SetPoint(2,7,0.7803);
   grae->SetPointError(2,1,1,0.0374,0.0368);
   grae->SetPoint(3,9,0.5558);
   grae->SetPointError(3,1,1,0.0216,0.026);
   grae->SetPoint(4,12.5,0.2829);
   grae->SetPointError(4,2.5,2.5,0.0079,0.0096);
   grae->SetPoint(5,25,0.0281);
   grae->SetPointError(5,10,10,0.0003,0.0005);
   
   TH1F *Graph18 = new TH1F("Graph18","Graph",100,0,38.25);
   Graph18->SetMinimum(0.02502);
   Graph18->SetMaximum(1.54162);
   Graph18->SetDirectory(0);
   Graph18->SetStats(0);
   Graph18->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph18);
   
   grae->Draw("2 ");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3003);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,3.25,1.464);
   grae->SetPointError(0,0.75,0.75,0.344,0.289);
   grae->SetPoint(1,5,1.111);
   grae->SetPointError(1,1,1,0.2059,0.171);
   grae->SetPoint(2,7,0.883);
   grae->SetPointError(2,1,1,0.1338,0.1116);
   grae->SetPoint(3,9,0.6402);
   grae->SetPointError(3,1,1,0.0804,0.0657);
   grae->SetPoint(4,12.5,0.3149);
   grae->SetPointError(4,2.5,2.5,0.0295,0.0238);
   grae->SetPoint(5,25,0.0297);
   grae->SetPointError(5,10,10,0.00145,0.00106);
   
   TH1F *Graph1719 = new TH1F("Graph1719","Graph",100,0,38.25);
   Graph1719->SetMinimum(0.025425);
   Graph1719->SetMaximum(1.925475);
   Graph1719->SetDirectory(0);
   Graph1719->SetStats(0);
   Graph1719->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph1719);
   
   grae->Draw("5 z ");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3018);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,3.25,1.297);
   grae->SetPointError(0,0.75,0.75,0.1,0.107);
   grae->SetPoint(1,5,1.0375);
   grae->SetPointError(1,1,1,0.0633,0.054);
   grae->SetPoint(2,7,0.7803);
   grae->SetPointError(2,1,1,0.0374,0.0368);
   grae->SetPoint(3,9,0.5558);
   grae->SetPointError(3,1,1,0.0216,0.026);
   grae->SetPoint(4,12.5,0.2829);
   grae->SetPointError(4,2.5,2.5,0.0079,0.0096);
   grae->SetPoint(5,25,0.0281);
   grae->SetPointError(5,10,10,0.0003,0.0005);
   
   TH1F *Graph1820 = new TH1F("Graph1820","Graph",100,0,38.25);
   Graph1820->SetMinimum(0.02502);
   Graph1820->SetMaximum(1.54162);
   Graph1820->SetDirectory(0);
   Graph1820->SetStats(0);
   Graph1820->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph1820);
   
   grae->Draw("5 z ");
   Double_t xAxis10[7] = {2.5, 4, 6, 8, 10, 15, 35}; 
   
   TH1D *h_cross_section_et_jet = new TH1D("h_cross_section_et_jet","det_cross_et_jet",6, xAxis10);
   h_cross_section_et_jet->SetBinContent(1,1.41325);
   h_cross_section_et_jet->SetBinContent(2,1.190548);
   h_cross_section_et_jet->SetBinContent(3,0.9676393);
   h_cross_section_et_jet->SetBinContent(4,0.7534549);
   h_cross_section_et_jet->SetBinContent(5,0.3145193);
   h_cross_section_et_jet->SetBinContent(6,0.02875704);
   h_cross_section_et_jet->SetBinError(1,0.1620547);
   h_cross_section_et_jet->SetBinError(2,0.1035764);
   h_cross_section_et_jet->SetBinError(3,0.09048733);
   h_cross_section_et_jet->SetBinError(4,0.07461337);
   h_cross_section_et_jet->SetBinError(5,0.03278017);
   h_cross_section_et_jet->SetBinError(6,0.006100327);
   h_cross_section_et_jet->SetEntries(14124);
   h_cross_section_et_jet->SetFillColor(41);
   h_cross_section_et_jet->SetLineWidth(2);
   h_cross_section_et_jet->SetMarkerStyle(20);
   h_cross_section_et_jet->SetMarkerSize(1.1);
   h_cross_section_et_jet->Draw("E1 X0 SAME");
   
   TLegend *leg = new TLegend(0.5,0.5,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_et_jet","ZEUS (prel.) 326 pb^{-1}","p");
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
   canv_cross_et_jet_1->Modified();
   canv_cross_et_jet->cd();
   TText *text = new TText(0.45,0.92,"ZEUS");
   text->SetTextSize(0.07);
   text->Draw();
   canv_cross_et_jet->Modified();
   canv_cross_et_jet->cd();
   canv_cross_et_jet->SetSelected(canv_cross_et_jet);
}
