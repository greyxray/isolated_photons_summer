{
//=========Macro generated from canvas: canv_cross_et/
//=========  (Fri Jan 27 02:10:52 2012) by ROOT version5.26/00c
   TCanvas *canv_cross_et = new TCanvas("canv_cross_et", "",0,0,1200,900);
   canv_cross_et->SetHighLightColor(2);
   canv_cross_et->Range(0,0,1,1);
   canv_cross_et->SetFillColor(0);
   canv_cross_et->SetBorderMode(0);
   canv_cross_et->SetBorderSize(2);
   canv_cross_et->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_et_1
   TPad *canv_cross_et_1 = new TPad("canv_cross_et_1", "canv_cross_et_1",0.01,0.01,0.99,0.99);
   canv_cross_et_1->Draw();
   canv_cross_et_1->cd();
   canv_cross_et_1->Range(2.256098,-0.7119178,15.67073,3.520959);
   canv_cross_et_1->SetFillColor(0);
   canv_cross_et_1->SetBorderMode(0);
   canv_cross_et_1->SetBorderSize(2);
   canv_cross_et_1->SetGridy();
   canv_cross_et_1->SetTickx(1);
   canv_cross_et_1->SetTicky(1);
   canv_cross_et_1->SetLeftMargin(0.13);
   canv_cross_et_1->SetRightMargin(0.05);
   canv_cross_et_1->SetBottomMargin(0.18);
   canv_cross_et_1->SetFrameBorderMode(0);
   canv_cross_et_1->SetFrameBorderMode(0);
   Double_t xAxis1[5] = {4, 6, 8, 10, 15}; 
   
   TH2D *h_window_cross_et = new TH2D("h_window_cross_et","",4, xAxis1,10,0.05,3.14);
   h_window_cross_et->SetStats(0);
   h_window_cross_et->GetXaxis()->SetTitle("E_{T}^{#gamma} (GeV)");
   h_window_cross_et->GetXaxis()->SetNdivisions(507);
   h_window_cross_et->GetXaxis()->SetLabelFont(22);
   h_window_cross_et->GetXaxis()->SetLabelSize(0.04829268);
   h_window_cross_et->GetXaxis()->SetTitleSize(0.05365854);
   h_window_cross_et->GetXaxis()->SetTitleOffset(0.9);
   h_window_cross_et->GetYaxis()->SetTitle("d#sigma/d E_{T}^{#gamma} (pb/GeV)");
   h_window_cross_et->GetYaxis()->SetNdivisions(507);
   h_window_cross_et->GetYaxis()->SetLabelFont(22);
   h_window_cross_et->GetYaxis()->SetLabelSize(0.05424658);
   h_window_cross_et->GetYaxis()->SetTitleSize(0.06027398);
   h_window_cross_et->GetYaxis()->SetTitleOffset(0.9);
   h_window_cross_et->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3003);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,5,2.527);
   grae->SetPointError(0,1,1,0.445,0.377);
   grae->SetPoint(1,7,1.191);
   grae->SetPointError(1,1,1,0.187,0.154);
   grae->SetPoint(2,9,0.593);
   grae->SetPointError(2,1,1,0.0804,0.065);
   grae->SetPoint(3,12.5,0.202);
   grae->SetPointError(3,2.5,2.5,0.0212,0.0167);
   
   TH1F *Graph1 = new TH1F("Graph1","Graph",100,2.9,16.1);
   Graph1->SetMinimum(0);
   Graph1->SetMaximum(3.17632);
   Graph1->SetDirectory(0);
   Graph1->SetStats(0);
   Graph1->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph1);
   
   grae->Draw("2 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3018);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,5,2.32);
   grae->SetPointError(0,1,1,0.142,0.121);
   grae->SetPoint(1,7,1.054);
   grae->SetPointError(1,1,1,0.04,0.063);
   grae->SetPoint(2,9,0.522);
   grae->SetPointError(2,1,1,0.0234,0.0244);
   grae->SetPoint(3,12.5,0.18);
   grae->SetPointError(3,2.5,2.5,0.0052,0.0078);
   
   TH1F *Graph2 = new TH1F("Graph2","Graph",100,4.22,17.42);
   Graph2->SetMinimum(0);
   Graph2->SetMaximum(2.66762);
   Graph2->SetDirectory(0);
   Graph2->SetStats(0);
   Graph2->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph2);
   
   grae->Draw("2 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3003);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,5,2.527);
   grae->SetPointError(0,1,1,0.445,0.377);
   grae->SetPoint(1,7,1.191);
   grae->SetPointError(1,1,1,0.187,0.154);
   grae->SetPoint(2,9,0.593);
   grae->SetPointError(2,1,1,0.0804,0.065);
   grae->SetPoint(3,12.5,0.202);
   grae->SetPointError(3,2.5,2.5,0.0212,0.0167);
   
   TH1F *Graph13 = new TH1F("Graph13","Graph",100,2.9,16.1);
   Graph13->SetMinimum(0);
   Graph13->SetMaximum(3.17632);
   Graph13->SetDirectory(0);
   Graph13->SetStats(0);
   Graph13->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph13);
   
   grae->Draw("5 z ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3018);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,5,2.32);
   grae->SetPointError(0,1,1,0.142,0.121);
   grae->SetPoint(1,7,1.054);
   grae->SetPointError(1,1,1,0.04,0.063);
   grae->SetPoint(2,9,0.522);
   grae->SetPointError(2,1,1,0.0234,0.0244);
   grae->SetPoint(3,12.5,0.18);
   grae->SetPointError(3,2.5,2.5,0.0052,0.0078);
   
   TH1F *Graph24 = new TH1F("Graph24","Graph",100,4.22,17.42);
   Graph24->SetMinimum(0);
   Graph24->SetMaximum(2.66762);
   Graph24->SetDirectory(0);
   Graph24->SetStats(0);
   Graph24->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph24);
   
   grae->Draw("5 z ");
   Double_t xAxis2[5] = {4, 6, 8, 10, 15}; 
   
   TH1D *h_cross_section_et = new TH1D("h_cross_section_et","det_cross_et",4, xAxis2);
   h_cross_section_et->SetBinContent(1,2.485469);
   h_cross_section_et->SetBinContent(2,1.335921);
   h_cross_section_et->SetBinContent(3,0.641934);
   h_cross_section_et->SetBinContent(4,0.2601173);
   h_cross_section_et->SetBinError(1,0.1767503);
   h_cross_section_et->SetBinError(2,0.1031686);
   h_cross_section_et->SetBinError(3,0.07418651);
   h_cross_section_et->SetBinError(4,0.02761632);
   h_cross_section_et->SetEntries(14122);
   h_cross_section_et->SetFillColor(41);
   h_cross_section_et->SetLineWidth(2);
   h_cross_section_et->SetMarkerStyle(20);
   h_cross_section_et->SetMarkerSize(1.1);
   h_cross_section_et->Draw("E1 X0 SAME");
   
   TLegend *leg = new TLegend(0.5,0.5,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_et","ZEUS (prel.) 326 pb^{-1}","p");
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
   canv_cross_et_1->Modified();
   canv_cross_et->cd();
   TText *text = new TText(0.45,0.92,"ZEUS");
   text->SetTextSize(0.07);
   text->Draw();
   canv_cross_et->Modified();
   canv_cross_et->cd();
   canv_cross_et->SetSelected(canv_cross_et);
}
