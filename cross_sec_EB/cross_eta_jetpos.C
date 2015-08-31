{
//=========Macro generated from canvas: canv_cross_eta_jet/
//=========  (Fri Jan 27 02:10:53 2012) by ROOT version5.26/00c
   TCanvas *canv_cross_eta_jet = new TCanvas("canv_cross_eta_jet", "",0,0,1200,900);
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
   canv_cross_eta_jet_1->Range(-2.023171,-1.170548,2.00122,5.610274);
   canv_cross_eta_jet_1->SetFillColor(0);
   canv_cross_eta_jet_1->SetBorderMode(0);
   canv_cross_eta_jet_1->SetBorderSize(2);
   canv_cross_eta_jet_1->SetGridy();
   canv_cross_eta_jet_1->SetTickx(1);
   canv_cross_eta_jet_1->SetTicky(1);
   canv_cross_eta_jet_1->SetLeftMargin(0.13);
   canv_cross_eta_jet_1->SetRightMargin(0.05);
   canv_cross_eta_jet_1->SetBottomMargin(0.18);
   canv_cross_eta_jet_1->SetFrameBorderMode(0);
   canv_cross_eta_jet_1->SetFrameBorderMode(0);
   Double_t xAxis11[5] = {-1.5, -0.7, 0.1, 0.9, 1.8}; 
   
   TH2D *h_window_cross_eta_jet = new TH2D("h_window_cross_eta_jet","",4, xAxis11,10,0.05,5);
   h_window_cross_eta_jet->SetStats(0);
   h_window_cross_eta_jet->GetXaxis()->SetTitle("#eta^{jet}");
   h_window_cross_eta_jet->GetXaxis()->SetNdivisions(507);
   h_window_cross_eta_jet->GetXaxis()->SetLabelFont(22);
   h_window_cross_eta_jet->GetXaxis()->SetLabelSize(0.04829268);
   h_window_cross_eta_jet->GetXaxis()->SetTitleSize(0.05365854);
   h_window_cross_eta_jet->GetXaxis()->SetTitleOffset(0.9);
   h_window_cross_eta_jet->GetYaxis()->SetTitle("d#sigma/d #eta^{jet} (pb)");
   h_window_cross_eta_jet->GetYaxis()->SetNdivisions(507);
   h_window_cross_eta_jet->GetYaxis()->SetLabelFont(22);
   h_window_cross_eta_jet->GetYaxis()->SetLabelSize(0.05424658);
   h_window_cross_eta_jet->GetYaxis()->SetTitleSize(0.06027398);
   h_window_cross_eta_jet->GetYaxis()->SetTitleOffset(0.9);
   h_window_cross_eta_jet->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3003);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-1.1,2.354);
   grae->SetPointError(0,0.4,0.4,0.438,0.38);
   grae->SetPoint(1,-0.3,3.631);
   grae->SetPointError(1,0.2,0.2,0.621,0.527);
   grae->SetPoint(2,0.5,3.348);
   grae->SetPointError(2,0.4,0.4,0.516,0.423);
   grae->SetPoint(3,1.35,2.406);
   grae->SetPointError(3,0.45,0.45,0.304,0.231);
   
   TH1F *Graph21 = new TH1F("Graph21","Graph",100,-1.83,2.13);
   Graph21->SetMinimum(1.6918);
   Graph21->SetMaximum(4.3822);
   Graph21->SetDirectory(0);
   Graph21->SetStats(0);
   Graph21->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph21);
   
   grae->Draw("2 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3018);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-1.1,1.477);
   grae->SetPointError(0,0.4,0.4,0.171,0.148);
   grae->SetPoint(1,-0.3,2.954);
   grae->SetPointError(1,0.2,0.2,0.181,0.184);
   grae->SetPoint(2,0.5,3.38);
   grae->SetPointError(2,0.4,0.4,0.212,0.138);
   grae->SetPoint(3,1.35,2.78);
   grae->SetPointError(3,0.45,0.45,0.131,0.089);
   
   TH1F *Graph22 = new TH1F("Graph22","Graph",100,-1.434,2.526);
   Graph22->SetMinimum(1.0848);
   Graph22->SetMaximum(3.7392);
   Graph22->SetDirectory(0);
   Graph22->SetStats(0);
   Graph22->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph22);
   
   grae->Draw("2 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3003);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-1.1,2.354);
   grae->SetPointError(0,0.4,0.4,0.438,0.38);
   grae->SetPoint(1,-0.3,3.631);
   grae->SetPointError(1,0.2,0.2,0.621,0.527);
   grae->SetPoint(2,0.5,3.348);
   grae->SetPointError(2,0.4,0.4,0.516,0.423);
   grae->SetPoint(3,1.35,2.406);
   grae->SetPointError(3,0.45,0.45,0.304,0.231);
   
   TH1F *Graph2123 = new TH1F("Graph2123","Graph",100,-1.83,2.13);
   Graph2123->SetMinimum(1.6918);
   Graph2123->SetMaximum(4.3822);
   Graph2123->SetDirectory(0);
   Graph2123->SetStats(0);
   Graph2123->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph2123);
   
   grae->Draw("5 z ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3018);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-1.1,1.477);
   grae->SetPointError(0,0.4,0.4,0.171,0.148);
   grae->SetPoint(1,-0.3,2.954);
   grae->SetPointError(1,0.2,0.2,0.181,0.184);
   grae->SetPoint(2,0.5,3.38);
   grae->SetPointError(2,0.4,0.4,0.212,0.138);
   grae->SetPoint(3,1.35,2.78);
   grae->SetPointError(3,0.45,0.45,0.131,0.089);
   
   TH1F *Graph2224 = new TH1F("Graph2224","Graph",100,-1.434,2.526);
   Graph2224->SetMinimum(1.0848);
   Graph2224->SetMaximum(3.7392);
   Graph2224->SetDirectory(0);
   Graph2224->SetStats(0);
   Graph2224->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph2224);
   
   grae->Draw("5 z ");
   Double_t xAxis12[5] = {-1.5, -0.7, 0.1, 0.9, 1.8}; 
   
   TH1D *h_cross_section_eta_jet = new TH1D("h_cross_section_eta_jet","det_cross_eta_jet",4, xAxis12);
   h_cross_section_eta_jet->SetBinContent(1,1.539651);
   h_cross_section_eta_jet->SetBinContent(2,2.885657);
   h_cross_section_eta_jet->SetBinContent(3,3.888255);
   h_cross_section_eta_jet->SetBinContent(4,3.630983);
   h_cross_section_eta_jet->SetBinError(1,0.1657377);
   h_cross_section_eta_jet->SetBinError(2,0.2416965);
   h_cross_section_eta_jet->SetBinError(3,0.3224532);
   h_cross_section_eta_jet->SetBinError(4,0.2921451);
   h_cross_section_eta_jet->SetEntries(14122);
   h_cross_section_eta_jet->SetFillColor(41);
   h_cross_section_eta_jet->SetLineWidth(2);
   h_cross_section_eta_jet->SetMarkerStyle(20);
   h_cross_section_eta_jet->SetMarkerSize(1.1);
   h_cross_section_eta_jet->Draw("E1 X0 SAME");
   
   TLegend *leg = new TLegend(0.47,0.2,0.87,0.48,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_eta_jet","ZEUS (prel.) 326 pb^{-1}","p");
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
   canv_cross_eta_jet_1->Modified();
   canv_cross_eta_jet->cd();
   TText *text = new TText(0.45,0.92,"ZEUS");
   text->SetTextSize(0.07);
   text->Draw();
   canv_cross_eta_jet->Modified();
   canv_cross_eta_jet->cd();
   canv_cross_eta_jet->SetSelected(canv_cross_eta_jet);
}
