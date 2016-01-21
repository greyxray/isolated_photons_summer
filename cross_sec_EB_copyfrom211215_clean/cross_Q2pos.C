{
//=========Macro generated from canvas: canv_cross_Q2/
//=========  (Fri Jan 27 02:10:52 2012) by ROOT version5.26/00c
   TCanvas *canv_cross_Q2 = new TCanvas("canv_cross_Q2", "",0,0,1200,900);
   canv_cross_Q2->SetHighLightColor(2);
   canv_cross_Q2->Range(0,0,1,1);
   canv_cross_Q2->SetFillColor(0);
   canv_cross_Q2->SetBorderMode(0);
   canv_cross_Q2->SetBorderSize(2);
   canv_cross_Q2->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_Q2_1
   TPad *canv_cross_Q2_1 = new TPad("canv_cross_Q2_1", "canv_cross_Q2_1",0.01,0.01,0.99,0.99);
   canv_cross_Q2_1->Draw();
   canv_cross_Q2_1->cd();
   canv_cross_Q2_1->Range(0.7552087,-3.641604,2.638219,-0.07713807);
   canv_cross_Q2_1->SetFillColor(0);
   canv_cross_Q2_1->SetBorderMode(0);
   canv_cross_Q2_1->SetBorderSize(2);
   canv_cross_Q2_1->SetLogx();
   canv_cross_Q2_1->SetLogy();
   canv_cross_Q2_1->SetGridy();
   canv_cross_Q2_1->SetTickx(1);
   canv_cross_Q2_1->SetTicky(1);
   canv_cross_Q2_1->SetLeftMargin(0.13);
   canv_cross_Q2_1->SetRightMargin(0.05);
   canv_cross_Q2_1->SetBottomMargin(0.18);
   canv_cross_Q2_1->SetFrameBorderMode(0);
   canv_cross_Q2_1->SetFrameBorderMode(0);
   Double_t xAxis5[6] = {10, 20, 40, 80, 150, 350}; 
   
   TH2D *h_window_cross_Q2 = new TH2D("h_window_cross_Q2","",5, xAxis5,10,0.001,0.4);
   h_window_cross_Q2->SetStats(0);
   h_window_cross_Q2->GetXaxis()->SetTitle("Q^{2} (GeV^{2})");
   h_window_cross_Q2->GetXaxis()->SetNdivisions(507);
   h_window_cross_Q2->GetXaxis()->SetLabelFont(22);
   h_window_cross_Q2->GetXaxis()->SetLabelSize(0.04829268);
   h_window_cross_Q2->GetXaxis()->SetTitleSize(0.05365854);
   h_window_cross_Q2->GetXaxis()->SetTitleOffset(0.9);
   h_window_cross_Q2->GetYaxis()->SetTitle("d#sigma/d Q^{2} (pb/GeV^{2})");
   h_window_cross_Q2->GetYaxis()->SetNdivisions(507);
   h_window_cross_Q2->GetYaxis()->SetLabelFont(22);
   h_window_cross_Q2->GetYaxis()->SetLabelSize(0.05424658);
   h_window_cross_Q2->GetYaxis()->SetTitleSize(0.06027398);
   h_window_cross_Q2->GetYaxis()->SetTitleOffset(0.9);
   h_window_cross_Q2->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(5);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3003);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,15,0.1979);
   grae->SetPointError(0,5,5,0.0359,0.0303);
   grae->SetPoint(1,30,0.1002);
   grae->SetPointError(1,10,10,0.01778,0.0148);
   grae->SetPoint(2,60,0.0574);
   grae->SetPointError(2,20,20,0.00982,0.00816);
   grae->SetPoint(3,115,0.0286);
   grae->SetPointError(3,35,35,0.00407,0.00333);
   grae->SetPoint(4,250,0.00679);
   grae->SetPointError(4,100,100,0.000708,0.000553);
   
   TH1F *Graph9 = new TH1F("Graph9","Graph",100,9,384);
   Graph9->SetMinimum(0.0054738);
   Graph9->SetMaximum(0.2504118);
   Graph9->SetDirectory(0);
   Graph9->SetStats(0);
   Graph9->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph9);
   
   grae->Draw("2 ");
   
   grae = new TGraphAsymmErrors(5);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3018);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,15,0.2089);
   grae->SetPointError(0,5,5,0.014,0.0086);
   grae->SetPoint(1,30,0.1);
   grae->SetPointError(1,10,10,0.00587,0.00431);
   grae->SetPoint(2,60,0.0491);
   grae->SetPointError(2,20,20,0.00217,0.00283);
   grae->SetPoint(3,115,0.0232);
   grae->SetPointError(3,35,35,0.00133,0.00125);
   grae->SetPoint(4,250,0.00538);
   grae->SetPointError(4,100,100,0.000292,0.00029);
   
   TH1F *Graph10 = new TH1F("Graph10","Graph",100,38.4,422.4);
   Graph10->SetMinimum(0);
   Graph10->SetMaximum(0.2387412);
   Graph10->SetDirectory(0);
   Graph10->SetStats(0);
   Graph10->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph10);
   
   grae->Draw("2 ");
   
   grae = new TGraphAsymmErrors(5);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3003);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,15,0.1979);
   grae->SetPointError(0,5,5,0.0359,0.0303);
   grae->SetPoint(1,30,0.1002);
   grae->SetPointError(1,10,10,0.01778,0.0148);
   grae->SetPoint(2,60,0.0574);
   grae->SetPointError(2,20,20,0.00982,0.00816);
   grae->SetPoint(3,115,0.0286);
   grae->SetPointError(3,35,35,0.00407,0.00333);
   grae->SetPoint(4,250,0.00679);
   grae->SetPointError(4,100,100,0.000708,0.000553);
   
   TH1F *Graph911 = new TH1F("Graph911","Graph",100,9,384);
   Graph911->SetMinimum(0.0054738);
   Graph911->SetMaximum(0.2504118);
   Graph911->SetDirectory(0);
   Graph911->SetStats(0);
   Graph911->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph911);
   
   grae->Draw("5 z ");
   
   grae = new TGraphAsymmErrors(5);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3018);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,15,0.2089);
   grae->SetPointError(0,5,5,0.014,0.0086);
   grae->SetPoint(1,30,0.1);
   grae->SetPointError(1,10,10,0.00587,0.00431);
   grae->SetPoint(2,60,0.0491);
   grae->SetPointError(2,20,20,0.00217,0.00283);
   grae->SetPoint(3,115,0.0232);
   grae->SetPointError(3,35,35,0.00133,0.00125);
   grae->SetPoint(4,250,0.00538);
   grae->SetPointError(4,100,100,0.000292,0.00029);
   
   TH1F *Graph1012 = new TH1F("Graph1012","Graph",100,38.4,422.4);
   Graph1012->SetMinimum(0);
   Graph1012->SetMaximum(0.2387412);
   Graph1012->SetDirectory(0);
   Graph1012->SetStats(0);
   Graph1012->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph1012);
   
   grae->Draw("5 z ");
   Double_t xAxis6[6] = {10, 20, 40, 80, 150, 350}; 
   
   TH1D *h_cross_section_Q2 = new TH1D("h_cross_section_Q2","det_cross_Q2",5, xAxis6);
   h_cross_section_Q2->SetBinContent(1,0.3001759);
   h_cross_section_Q2->SetBinContent(2,0.1322137);
   h_cross_section_Q2->SetBinContent(3,0.05005303);
   h_cross_section_Q2->SetBinContent(4,0.02275342);
   h_cross_section_Q2->SetBinContent(5,0.004067262);
   h_cross_section_Q2->SetBinError(1,0.02403333);
   h_cross_section_Q2->SetBinError(2,0.0114218);
   h_cross_section_Q2->SetBinError(3,0.005321033);
   h_cross_section_Q2->SetBinError(4,0.002394318);
   h_cross_section_Q2->SetBinError(5,0.0006825807);
   h_cross_section_Q2->SetEntries(14123);
   h_cross_section_Q2->SetFillColor(41);
   h_cross_section_Q2->SetLineWidth(2);
   h_cross_section_Q2->SetMarkerStyle(20);
   h_cross_section_Q2->SetMarkerSize(1.1);
   h_cross_section_Q2->Draw("E1 X0 SAME");
   
   TLegend *leg = new TLegend(0.23,0.239,0.63,0.55,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_Q2","ZEUS (prel.) 326 pb^{-1}","p");
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
   canv_cross_Q2_1->Modified();
   canv_cross_Q2->cd();
   TText *text = new TText(0.45,0.92,"ZEUS");
   text->SetTextSize(0.07);
   text->Draw();
   canv_cross_Q2->Modified();
   canv_cross_Q2->cd();
   canv_cross_Q2->SetSelected(canv_cross_Q2);
}
