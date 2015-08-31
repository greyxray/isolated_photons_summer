{
//=========Macro generated from canvas: canv_cross_x/
//=========  (Fri Jan 27 02:10:52 2012) by ROOT version5.26/00c
   TCanvas *canv_cross_x = new TCanvas("canv_cross_x", "",0,0,1200,900);
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
   canv_cross_x_1->Range(-4.016043,0.311873,-1.577019,4.36476);
   canv_cross_x_1->SetFillColor(0);
   canv_cross_x_1->SetBorderMode(0);
   canv_cross_x_1->SetBorderSize(2);
   canv_cross_x_1->SetLogx();
   canv_cross_x_1->SetLogy();
   canv_cross_x_1->SetGridy();
   canv_cross_x_1->SetTickx(1);
   canv_cross_x_1->SetTicky(1);
   canv_cross_x_1->SetLeftMargin(0.13);
   canv_cross_x_1->SetRightMargin(0.05);
   canv_cross_x_1->SetBottomMargin(0.18);
   canv_cross_x_1->SetFrameBorderMode(0);
   canv_cross_x_1->SetFrameBorderMode(0);
   Double_t xAxis7[5] = {0.0002, 0.001, 0.003, 0.01, 0.02}; 
   
   TH2D *h_window_cross_x = new TH2D("h_window_cross_x","",4, xAxis7,10,11,10000);
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
   h_window_cross_x->GetYaxis()->SetLabelSize(0.05424658);
   h_window_cross_x->GetYaxis()->SetTitleSize(0.06027398);
   h_window_cross_x->GetYaxis()->SetTitleOffset(0.9);
   h_window_cross_x->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3003);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,0.0006,3037);
   grae->SetPointError(0,0.0004,0.0004,525,449);
   grae->SetPoint(1,0.002,1736);
   grae->SetPointError(1,0.001,0.001,292,246);
   grae->SetPoint(2,0.0065,462.5);
   grae->SetPointError(2,0.0035,0.0035,68.4,55.4);
   grae->SetPoint(3,0.015,43.58);
   grae->SetPointError(3,0.005,0.005,4.11,3.07);
   
   TH1F *Graph13 = new TH1F("Graph13","Graph",100,0.00018,0.02198);
   Graph13->SetMinimum(35.523);
   Graph13->SetMaximum(3830.653);
   Graph13->SetDirectory(0);
   Graph13->SetStats(0);
   Graph13->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph13);
   
   grae->Draw("2 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3018);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,0.0006,3408);
   grae->SetPointError(0,0.0004,0.0004,233,108);
   grae->SetPoint(1,0.002,1623);
   grae->SetPointError(1,0.001,0.001,84,77);
   grae->SetPoint(2,0.0065,344.1);
   grae->SetPointError(2,0.0035,0.0035,25,26.1);
   grae->SetPoint(3,0.015,31.43);
   grae->SetPointError(3,0.005,0.005,2.3,2.64);
   
   TH1F *Graph14 = new TH1F("Graph14","Graph",100,0.002198,0.024178);
   Graph14->SetMinimum(0);
   Graph14->SetMaximum(3864.687);
   Graph14->SetDirectory(0);
   Graph14->SetStats(0);
   Graph14->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph14);
   
   grae->Draw("2 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3003);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,0.0006,3037);
   grae->SetPointError(0,0.0004,0.0004,525,449);
   grae->SetPoint(1,0.002,1736);
   grae->SetPointError(1,0.001,0.001,292,246);
   grae->SetPoint(2,0.0065,462.5);
   grae->SetPointError(2,0.0035,0.0035,68.4,55.4);
   grae->SetPoint(3,0.015,43.58);
   grae->SetPointError(3,0.005,0.005,4.11,3.07);
   
   TH1F *Graph1315 = new TH1F("Graph1315","Graph",100,0.00018,0.02198);
   Graph1315->SetMinimum(35.523);
   Graph1315->SetMaximum(3830.653);
   Graph1315->SetDirectory(0);
   Graph1315->SetStats(0);
   Graph1315->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph1315);
   
   grae->Draw("5 z ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3018);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,0.0006,3408);
   grae->SetPointError(0,0.0004,0.0004,233,108);
   grae->SetPoint(1,0.002,1623);
   grae->SetPointError(1,0.001,0.001,84,77);
   grae->SetPoint(2,0.0065,344.1);
   grae->SetPointError(2,0.0035,0.0035,25,26.1);
   grae->SetPoint(3,0.015,31.43);
   grae->SetPointError(3,0.005,0.005,2.3,2.64);
   
   TH1F *Graph1416 = new TH1F("Graph1416","Graph",100,0.002198,0.024178);
   Graph1416->SetMinimum(0);
   Graph1416->SetMaximum(3864.687);
   Graph1416->SetDirectory(0);
   Graph1416->SetStats(0);
   Graph1416->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph1416);
   
   grae->Draw("5 z ");
   Double_t xAxis8[5] = {0.0002, 0.001, 0.003, 0.01, 0.02}; 
   
   TH1D *h_cross_section_x = new TH1D("h_cross_section_x","det_cross_x",4, xAxis8);
   h_cross_section_x->SetBinContent(0,4.359529);
   h_cross_section_x->SetBinContent(1,4894.067);
   h_cross_section_x->SetBinContent(2,1836.197);
   h_cross_section_x->SetBinContent(3,285.6633);
   h_cross_section_x->SetBinContent(4,27.36101);
   h_cross_section_x->SetBinContent(5,23.61412);
   h_cross_section_x->SetBinError(0,0.6292439);
   h_cross_section_x->SetBinError(1,330.1682);
   h_cross_section_x->SetBinError(2,138.2609);
   h_cross_section_x->SetBinError(3,31.16427);
   h_cross_section_x->SetBinError(4,7.141125);
   h_cross_section_x->SetBinError(5,1.464485);
   h_cross_section_x->SetEntries(14122);
   h_cross_section_x->SetFillColor(41);
   h_cross_section_x->SetLineWidth(2);
   h_cross_section_x->SetMarkerStyle(20);
   h_cross_section_x->SetMarkerSize(1.1);
   h_cross_section_x->Draw("E1 X0 SAME");
   
   TLegend *leg = new TLegend(0.21,0.289,0.61,0.6,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_x","ZEUS (prel.) 326 pb^{-1}","p");
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
   canv_cross_x_1->Modified();
   canv_cross_x->cd();
   TText *text = new TText(0.45,0.92,"ZEUS");
   text->SetTextSize(0.07);
   text->Draw();
   canv_cross_x->Modified();
   canv_cross_x->cd();
   canv_cross_x->SetSelected(canv_cross_x);
}
