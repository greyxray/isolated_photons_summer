{
//=========Macro generated from canvas: canv_cross_Q2/
//=========  (Fri Mar 11 01:30:27 2011) by ROOT version5.26/00c
   TCanvas *canv_cross_Q2 = new TCanvas("canv_cross_Q2", "",1,1,550,876);
   canv_cross_Q2->SetHighLightColor(2);
   canv_cross_Q2->Range(0,0,1,1);
   canv_cross_Q2->SetFillColor(0);
   canv_cross_Q2->SetBorderMode(0);
   canv_cross_Q2->SetBorderSize(2);
   canv_cross_Q2->SetTopMargin(0.04761905);
   canv_cross_Q2->SetBottomMargin(0.05);
   canv_cross_Q2->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_Q2_1
   TPad *canv_cross_Q2_1 = new TPad("canv_cross_Q2_1", "_1",0.1,0.4,0.9,0.9);
   canv_cross_Q2_1->Draw();
   canv_cross_Q2_1->cd();
   canv_cross_Q2_1->Range(0.7552087,-3,2.638219,0);
   canv_cross_Q2_1->SetFillColor(0);
   canv_cross_Q2_1->SetBorderMode(0);
   canv_cross_Q2_1->SetBorderSize(2);
   canv_cross_Q2_1->SetLogx();
   canv_cross_Q2_1->SetLogy();
   canv_cross_Q2_1->SetTickx(1);
   canv_cross_Q2_1->SetTicky(1);
   canv_cross_Q2_1->SetLeftMargin(0.13);
   canv_cross_Q2_1->SetRightMargin(0.05);
   canv_cross_Q2_1->SetTopMargin(0);
   canv_cross_Q2_1->SetBottomMargin(0);
   canv_cross_Q2_1->SetFrameBorderMode(0);
   canv_cross_Q2_1->SetFrameBorderMode(0);
   Double_t xAxis109[6] = {10, 20, 40, 80, 150, 350}; 
   
   TH2D *h_window_cross_Q2 = new TH2D("h_window_cross_Q2","",5, xAxis109,10,0.001,1);
   h_window_cross_Q2->SetStats(0);
   h_window_cross_Q2->GetXaxis()->SetTitle("Q^{2} (GeV^{2})");
   h_window_cross_Q2->GetXaxis()->CenterTitle(true);
   h_window_cross_Q2->GetXaxis()->SetNdivisions(507);
   h_window_cross_Q2->GetXaxis()->SetLabelFont(42);
   h_window_cross_Q2->GetXaxis()->SetLabelSize(0.05073171);
   h_window_cross_Q2->GetXaxis()->SetTitleSize(0.06341463);
   h_window_cross_Q2->GetXaxis()->SetTitleFont(42);
   h_window_cross_Q2->GetYaxis()->SetTitle("d#sigma/d Q^{2} (pb/GeV^{2})");
   h_window_cross_Q2->GetYaxis()->CenterTitle(true);
   h_window_cross_Q2->GetYaxis()->SetNdivisions(507);
   h_window_cross_Q2->GetYaxis()->SetLabelFont(42);
   h_window_cross_Q2->GetYaxis()->SetLabelSize(0.0416);
   h_window_cross_Q2->GetYaxis()->SetTitleSize(0.052);
   h_window_cross_Q2->GetYaxis()->SetTitleFont(42);
   h_window_cross_Q2->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(5);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(42);
   grae->SetPoint(0,15,0.5296151);
   grae->SetPointError(0,0,0,0.05007468,0.05693739);
   grae->SetPoint(1,30,0.2358471);
   grae->SetPointError(1,0,0,0.04687041,0.01436484);
   grae->SetPoint(2,60,0.07480814);
   grae->SetPointError(2,0,0,0.0097048,0.008372895);
   grae->SetPoint(3,115,0.03624455);
   grae->SetPointError(3,0,0,0.007535777,0.004511923);
   grae->SetPoint(4,250,0.00676895);
   grae->SetPointError(4,0,0,0,0);
   
   TH1F *Graph27 = new TH1F("Graph27","Graph",100,13.5,273.5);
   Graph27->SetMinimum(0.006092055);
   Graph27->SetMaximum(0.6445308);
   Graph27->SetDirectory(0);
   Graph27->SetStats(0);
   Graph27->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph27);
   
   grae->Draw("e3 ");
   Double_t xAxis110[6] = {10, 20, 40, 80, 150, 350}; 
   
   TH1D *h_cross_section_Q2 = new TH1D("h_cross_section_Q2","det_cross_Q2",5, xAxis110);
   h_cross_section_Q2->SetBinContent(1,0.5296151);
   h_cross_section_Q2->SetBinContent(2,0.2358471);
   h_cross_section_Q2->SetBinContent(3,0.07480814);
   h_cross_section_Q2->SetBinContent(4,0.03624455);
   h_cross_section_Q2->SetBinContent(5,0.00676895);
   h_cross_section_Q2->SetBinError(1,0.0441957);
   h_cross_section_Q2->SetBinError(2,0.02207298);
   h_cross_section_Q2->SetBinError(3,0.009578358);
   h_cross_section_Q2->SetBinError(4,0.003631931);
   h_cross_section_Q2->SetBinError(5,0.0009374938);
   h_cross_section_Q2->SetEntries(22625);
   h_cross_section_Q2->SetFillColor(41);
   h_cross_section_Q2->SetMarkerStyle(20);
   h_cross_section_Q2->SetMarkerSize(0.8);
   h_cross_section_Q2->Draw("E1 X0 SAME");
   
   grae = new TGraphAsymmErrors(5);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(20);
   grae->SetPoint(0,15,0.5296151);
   grae->SetPointError(0,0,0,0.06678872,0.06250216);
   grae->SetPoint(1,30,0.2358471);
   grae->SetPointError(1,0,0,0.05180783,0.0312159);
   grae->SetPoint(2,60,0.07480814);
   grae->SetPointError(2,0,0,0.01363555,0.01354584);
   grae->SetPoint(3,115,0.03624455);
   grae->SetPointError(3,0,0,0.008365337,0.005136326);
   grae->SetPoint(4,250,0.00676895);
   grae->SetPointError(4,0,0,0.0009374938,0.001325816);
   grae->Draw("e ");
   
   TLegend *leg = new TLegend(0.5,0.5,0.9,0.9,NULL,"brNDC");
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

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   entry->SetFillColor(ci);
   entry->SetFillStyle(3454);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Graph","photon energy uncertainty","f");

   ci = TColor::GetColor("#000000");
   entry->SetFillColor(ci);
   entry->SetFillStyle(3445);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Graph","electron energy uncertainty","f");

   ci = TColor::GetColor("#000000");
   entry->SetFillColor(ci);
   entry->SetFillStyle(3425);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Graph","#delta Z range unc.","f");

   ci = TColor::GetColor("#000000");
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
   canv_cross_Q2_1->Modified();
   canv_cross_Q2->cd();
  
// ------------>Primitives in pad: canv_cross_Q2_2
   canv_cross_Q2_2 = new TPad("canv_cross_Q2_2", "_2",0.1,0.2,0.9,0.4);
   canv_cross_Q2_2->Draw();
   canv_cross_Q2_2->cd();
   canv_cross_Q2_2->Range(0.7552087,-0.8333333,2.638219,0.5);
   canv_cross_Q2_2->SetFillColor(0);
   canv_cross_Q2_2->SetBorderMode(0);
   canv_cross_Q2_2->SetBorderSize(2);
   canv_cross_Q2_2->SetLogx();
   canv_cross_Q2_2->SetTickx(1);
   canv_cross_Q2_2->SetTicky(1);
   canv_cross_Q2_2->SetLeftMargin(0.13);
   canv_cross_Q2_2->SetRightMargin(0.05);
   canv_cross_Q2_2->SetTopMargin(0);
   canv_cross_Q2_2->SetBottomMargin(0.25);
   canv_cross_Q2_2->SetFrameBorderMode(0);
   canv_cross_Q2_2->SetFrameBorderMode(0);
   Double_t xAxis111[6] = {10, 20, 40, 80, 150, 350}; 
   
   TH2D *h_window_cross_ratio_Q2 = new TH2D("h_window_cross_ratio_Q2","",5, xAxis111,10,-0.5,0.5);
   h_window_cross_ratio_Q2->SetStats(0);
   h_window_cross_ratio_Q2->GetXaxis()->SetTitle("Q^{2} (GeV^{2})");
   h_window_cross_ratio_Q2->GetXaxis()->CenterTitle(true);
   h_window_cross_ratio_Q2->GetXaxis()->SetNdivisions(507);
   h_window_cross_ratio_Q2->GetXaxis()->SetLabelFont(42);
   h_window_cross_ratio_Q2->GetXaxis()->SetLabelSize(0.09756097);
   h_window_cross_ratio_Q2->GetXaxis()->SetTitleSize(0.1219512);
   h_window_cross_ratio_Q2->GetXaxis()->SetTickLength(0.07);
   h_window_cross_ratio_Q2->GetXaxis()->SetTitleOffset(0.8);
   h_window_cross_ratio_Q2->GetXaxis()->SetTitleFont(42);
   h_window_cross_ratio_Q2->GetYaxis()->SetTitle("rel. difference");
   h_window_cross_ratio_Q2->GetYaxis()->CenterTitle(true);
   h_window_cross_ratio_Q2->GetYaxis()->SetNdivisions(406);
   h_window_cross_ratio_Q2->GetYaxis()->SetLabelFont(42);
   h_window_cross_ratio_Q2->GetYaxis()->SetLabelSize(0.08533333);
   h_window_cross_ratio_Q2->GetYaxis()->SetTitleSize(0.1066667);
   h_window_cross_ratio_Q2->GetYaxis()->SetTitleOffset(0.5);
   h_window_cross_ratio_Q2->GetYaxis()->SetTitleFont(42);
   h_window_cross_ratio_Q2->Draw("");
   
   TF1 *Unity = new TF1("Unity","0",-100,500);
   Unity->SetFillColor(19);
   Unity->SetFillStyle(0);
   Unity->SetLineColor(32);
   Unity->SetLineWidth(1);
   Unity->GetXaxis()->SetTitleFont(42);
   Unity->Draw("SAME");
   
   grae = new TGraphAsymmErrors(5);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3454);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,15,0);
   grae->SetPointError(0,0,0,0.06942633,0.06814571);
   grae->SetPoint(1,30,0);
   grae->SetPointError(1,0,0,0.03030453,0.01969896);
   grae->SetPoint(2,60,0);
   grae->SetPointError(2,0,0,0.1144783,0.0683708);
   grae->SetPoint(3,115,0);
   grae->SetPointError(3,0,0,0.1732686,0.06426558);
   grae->SetPoint(4,250,0);
   grae->SetPointError(4,0,0,0,0);
   
   TH1F *Graph28 = new TH1F("Graph28","Graph",100,13.5,273.5);
   Graph28->SetMinimum(-0.1974325);
   Graph28->SetMaximum(0.09253474);
   Graph28->SetDirectory(0);
   Graph28->SetStats(0);
   Graph28->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph28);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(5);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,15,-0.06942633);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,30,-0.03030453);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,60,-0.1144783);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,115,-0.1732686);
   grae->SetPointError(3,0,0,0,0);
   grae->SetPoint(4,250,0);
   grae->SetPointError(4,0,0,0,0);
   
   TH1F *Graph29 = new TH1F("Graph29","Graph",100,13.5,273.5);
   Graph29->SetMinimum(-0.1905955);
   Graph29->SetMaximum(0.01732686);
   Graph29->SetDirectory(0);
   Graph29->SetStats(0);
   Graph29->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph29);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(5);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,15,0.06814571);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,30,0.01969896);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,60,0.0683708);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,115,0.06426558);
   grae->SetPointError(3,0,0,0,0);
   grae->SetPoint(4,250,0);
   grae->SetPointError(4,0,0,0,0);
   
   TH1F *Graph30 = new TH1F("Graph30","Graph",100,13.5,273.5);
   Graph30->SetMinimum(0);
   Graph30->SetMaximum(0.07520788);
   Graph30->SetDirectory(0);
   Graph30->SetStats(0);
   Graph30->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph30);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(5);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3445);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,15,0);
   grae->SetPointError(0,0,0,0.01952356,0.01407499);
   grae->SetPoint(1,30,0);
   grae->SetPointError(1,0,0,0.03590626,0.01341224);
   grae->SetPoint(2,60,0);
   grae->SetPointError(2,0,0,0.03174896,0.0229203);
   grae->SetPoint(3,115,0);
   grae->SetPointError(3,0,0,0.09657279,0.04536394);
   grae->SetPoint(4,250,0);
   grae->SetPointError(4,0,0,0,0);
   
   TH1F *Graph31 = new TH1F("Graph31","Graph",100,13.5,273.5);
   Graph31->SetMinimum(-0.1107665);
   Graph31->SetMaximum(0.05955761);
   Graph31->SetDirectory(0);
   Graph31->SetStats(0);
   Graph31->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph31);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(5);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,15,-0.01952356);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,30,-0.03590626);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,60,-0.03174896);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,115,-0.09657279);
   grae->SetPointError(3,0,0,0,0);
   grae->SetPoint(4,250,0);
   grae->SetPointError(4,0,0,0,0);
   
   TH1F *Graph32 = new TH1F("Graph32","Graph",100,13.5,273.5);
   Graph32->SetMinimum(-0.1062301);
   Graph32->SetMaximum(0.009657279);
   Graph32->SetDirectory(0);
   Graph32->SetStats(0);
   Graph32->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph32);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(5);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,15,0.01407499);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,30,0.01341224);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,60,0.0229203);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,115,0.04536394);
   grae->SetPointError(3,0,0,0,0);
   grae->SetPoint(4,250,0);
   grae->SetPointError(4,0,0,0,0);
   
   TH1F *Graph33 = new TH1F("Graph33","Graph",100,13.5,273.5);
   Graph33->SetMinimum(0);
   Graph33->SetMaximum(0.04990033);
   Graph33->SetDirectory(0);
   Graph33->SetStats(0);
   Graph33->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph33);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(5);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3425);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,15,0);
   grae->SetPointError(0,0,0,0.03401949,0.06226433);
   grae->SetPoint(1,30,0);
   grae->SetPointError(1,0,0,0.01559198,0.02529779);
   grae->SetPoint(2,60,0);
   grae->SetPointError(2,0,0,0.04149471,0.06486671);
   grae->SetPoint(3,115,0);
   grae->SetPointError(3,0,0,0.035518,0.05125157);
   grae->SetPoint(4,250,0);
   grae->SetPointError(4,0,0,0,0);
   
   TH1F *Graph34 = new TH1F("Graph34","Graph",100,13.5,273.5);
   Graph34->SetMinimum(-0.05213086);
   Graph34->SetMaximum(0.07550286);
   Graph34->SetDirectory(0);
   Graph34->SetStats(0);
   Graph34->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph34);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(5);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,15,-0.03401949);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,30,-0.01559198);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,60,-0.04149471);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,115,-0.035518);
   grae->SetPointError(3,0,0,0,0);
   grae->SetPoint(4,250,0);
   grae->SetPointError(4,0,0,0,0);
   
   TH1F *Graph35 = new TH1F("Graph35","Graph",100,13.5,273.5);
   Graph35->SetMinimum(-0.04564418);
   Graph35->SetMaximum(0.004149471);
   Graph35->SetDirectory(0);
   Graph35->SetStats(0);
   Graph35->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph35);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(5);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,15,0.06226433);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,30,0.02529779);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,60,0.06486671);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,115,0.05125157);
   grae->SetPointError(3,0,0,0,0);
   grae->SetPoint(4,250,0);
   grae->SetPointError(4,0,0,0,0);
   
   TH1F *Graph36 = new TH1F("Graph36","Graph",100,13.5,273.5);
   Graph36->SetMinimum(0);
   Graph36->SetMaximum(0.07135339);
   Graph36->SetDirectory(0);
   Graph36->SetStats(0);
   Graph36->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph36);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(5);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3452);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,15,0);
   grae->SetPointError(0,0,0,0.05080395,0.05328219);
   grae->SetPoint(1,30,0);
   grae->SetPointError(1,0,0,0.1924676,0.050018);
   grae->SetPoint(2,60,0);
   grae->SetPointError(2,0,0,0.0315368,0.05585327);
   grae->SetPoint(3,115,0);
   grae->SetPointError(3,0,0,0.05117325,0.08174336);
   grae->SetPoint(4,250,0);
   grae->SetPointError(4,0,0,0,0);
   
   TH1F *Graph37 = new TH1F("Graph37","Graph",100,13.5,273.5);
   Graph37->SetMinimum(-0.2198886);
   Graph37->SetMaximum(0.1091645);
   Graph37->SetDirectory(0);
   Graph37->SetStats(0);
   Graph37->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph37);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(5);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,15,-0.05080395);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,30,-0.1924676);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,60,-0.0315368);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,115,-0.05117325);
   grae->SetPointError(3,0,0,0,0);
   grae->SetPoint(4,250,0);
   grae->SetPointError(4,0,0,0,0);
   
   TH1F *Graph38 = new TH1F("Graph38","Graph",100,13.5,273.5);
   Graph38->SetMinimum(-0.2117143);
   Graph38->SetMaximum(0.01924676);
   Graph38->SetDirectory(0);
   Graph38->SetStats(0);
   Graph38->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph38);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(5);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,15,0.05328219);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,30,0.050018);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,60,0.05585327);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,115,0.08174336);
   grae->SetPointError(3,0,0,0,0);
   grae->SetPoint(4,250,0);
   grae->SetPointError(4,0,0,0,0);
   
   TH1F *Graph39 = new TH1F("Graph39","Graph",100,13.5,273.5);
   Graph39->SetMinimum(0);
   Graph39->SetMaximum(0.0899177);
   Graph39->SetDirectory(0);
   Graph39->SetStats(0);
   Graph39->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph39);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(5);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);
   grae->SetFillStyle(3445);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,15,0);
   grae->SetPointError(0,0,0,0.0945492,0.1075071);
   grae->SetPoint(1,30,0);
   grae->SetPointError(1,0,0,0.1987322,0.06090743);
   grae->SetPoint(2,60,0);
   grae->SetPointError(2,0,0,0.1297292,0.1119249);
   grae->SetPoint(3,115,0);
   grae->SetPointError(3,0,0,0.2079147,0.1244855);
   grae->SetPoint(4,250,0);
   grae->SetPointError(4,0,0,0,0);
   grae->Draw("e ");
   canv_cross_Q2_2->Modified();
   canv_cross_Q2->cd();
   canv_cross_Q2->Modified();
   canv_cross_Q2->cd();
   canv_cross_Q2->SetSelected(canv_cross_Q2);
}
