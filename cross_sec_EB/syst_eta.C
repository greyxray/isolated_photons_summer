{
//=========Macro generated from canvas: canv_cross_eta/
//=========  (Wed Aug 12 00:25:09 2015) by ROOT version5.34/00
   TCanvas *canv_cross_eta = new TCanvas("canv_cross_eta", "",1,1,1200,976);
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
   canv_cross_eta_1->Range(-1,-4.499315,1,20.77466);
   canv_cross_eta_1->SetFillColor(0);
   canv_cross_eta_1->SetBorderMode(0);
   canv_cross_eta_1->SetBorderSize(2);
   canv_cross_eta_1->SetTickx(1);
   canv_cross_eta_1->SetTicky(1);
   canv_cross_eta_1->SetLeftMargin(0.15);
   canv_cross_eta_1->SetRightMargin(0.05);
   canv_cross_eta_1->SetBottomMargin(0.18);
   canv_cross_eta_1->SetFrameBorderMode(0);
   canv_cross_eta_1->SetFrameBorderMode(0);
   Double_t xAxis39[5] = {-0.7, -0.3, 0.1, 0.5, 0.9}; 
   
   TH2D *h_window_cross_eta = new TH2D("h_window_cross_eta","",4, xAxis39,10,0.05,18.5);
   h_window_cross_eta->SetStats(0);
   h_window_cross_eta->GetXaxis()->SetTitle("#eta^{#gamma}");
   h_window_cross_eta->GetXaxis()->SetNdivisions(507);
   h_window_cross_eta->GetXaxis()->SetLabelFont(22);
   h_window_cross_eta->GetXaxis()->SetLabelSize(0.05424658);
   h_window_cross_eta->GetXaxis()->SetTitleSize(0.06027398);
   h_window_cross_eta->GetXaxis()->SetTitleOffset(1.02);
   h_window_cross_eta->GetXaxis()->SetTitleFont(22);
   h_window_cross_eta->GetYaxis()->SetTitle("d#sigma/d#eta^{#gamma} (pb)");
   h_window_cross_eta->GetYaxis()->SetNdivisions(507);
   h_window_cross_eta->GetYaxis()->SetLabelFont(22);
   h_window_cross_eta->GetYaxis()->SetLabelOffset(0.016);
   h_window_cross_eta->GetYaxis()->SetLabelSize(0.05424658);
   h_window_cross_eta->GetYaxis()->SetTitleSize(0.06027398);
   h_window_cross_eta->GetYaxis()->SetTitleOffset(0.94);
   h_window_cross_eta->GetYaxis()->SetTitleFont(22);
   h_window_cross_eta->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(42);
   grae->SetPoint(0,-0.5,7.833415);
   grae->SetPointError(0,0,0,1.158659,0.9244149);
   grae->SetPoint(1,-0.1,7.112428);
   grae->SetPointError(1,0,0,0.543066,0.4641162);
   grae->SetPoint(2,0.3,5.748288);
   grae->SetPointError(2,0,0,0.4222323,0.418018);
   grae->SetPoint(3,0.7,5.371657);
   grae->SetPointError(3,0,0,0.571098,0.3735007);
   
   TH1F *Graph_Graph2 = new TH1F("Graph_Graph2","Graph",100,-0.62,0.82);
   Graph_Graph2->SetMinimum(4.404832);
   Graph_Graph2->SetMaximum(9.153557);
   Graph_Graph2->SetDirectory(0);
   Graph_Graph2->SetStats(0);
   Graph_Graph2->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph2);
   
   grae->Draw("e3 ");
   Double_t xAxis40[5] = {-0.7, -0.3, 0.1, 0.5, 0.9}; 
   
   TH1D *h_cross_section_eta = new TH1D("h_cross_section_eta","det_cross_eta",4, xAxis40);
   h_cross_section_eta->SetBinContent(1,7.56376);
   h_cross_section_eta->SetBinContent(2,6.7092);
   h_cross_section_eta->SetBinContent(3,5.833198);
   h_cross_section_eta->SetBinContent(4,5.155802);
   h_cross_section_eta->SetBinError(1,0.5928052);
   h_cross_section_eta->SetBinError(2,0.5351351);
   h_cross_section_eta->SetBinError(3,0.5522194);
   h_cross_section_eta->SetBinError(4,0.5284563);
   h_cross_section_eta->SetEntries(13887);
   h_cross_section_eta->SetFillColor(41);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   h_cross_section_eta->SetLineColor(ci);
   h_cross_section_eta->SetLineWidth(2);
   h_cross_section_eta->SetMarkerStyle(20);
   h_cross_section_eta->GetXaxis()->SetLabelFont(42);
   h_cross_section_eta->GetXaxis()->SetLabelSize(0.035);
   h_cross_section_eta->GetXaxis()->SetTitleSize(0.035);
   h_cross_section_eta->GetXaxis()->SetTitleFont(42);
   h_cross_section_eta->GetYaxis()->SetLabelFont(42);
   h_cross_section_eta->GetYaxis()->SetLabelSize(0.035);
   h_cross_section_eta->GetYaxis()->SetTitleSize(0.035);
   h_cross_section_eta->GetYaxis()->SetTitleFont(42);
   h_cross_section_eta->GetZaxis()->SetLabelFont(42);
   h_cross_section_eta->GetZaxis()->SetLabelSize(0.035);
   h_cross_section_eta->GetZaxis()->SetTitleSize(0.035);
   h_cross_section_eta->GetZaxis()->SetTitleFont(42);
   h_cross_section_eta->Draw("E1 X0 SAME");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(20);
   grae->SetPoint(0,-0.5,7.833415);
   grae->SetPointError(0,0,0,1.304407,0.8473339);
   grae->SetPoint(1,-0.1,7.112428);
   grae->SetPointError(1,0,0,0.8085383,0.8471286);
   grae->SetPoint(2,0.3,5.748288);
   grae->SetPointError(2,0,0,0.7719371,0.9139002);
   grae->SetPoint(3,0.7,5.371657);
   grae->SetPointError(3,0,0,0.8076583,0.807662);
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
   canv_cross_eta_1->Modified();
   canv_cross_eta->cd();
   TText *text = new TText(0.45,0.95,"ZEUS");
   text->SetTextFont(22);
   text->SetTextSize(0.07);
   text->Draw();
   canv_cross_eta->Modified();
   canv_cross_eta->cd();
   canv_cross_eta->SetSelected(canv_cross_eta);
}
