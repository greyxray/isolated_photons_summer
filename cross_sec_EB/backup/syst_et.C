{
//=========Macro generated from canvas: canv_cross_et/
//=========  (Fri Mar 11 01:30:27 2011) by ROOT version5.26/00c
   TCanvas *canv_cross_et = new TCanvas("canv_cross_et", "",1,1,550,876);
   canv_cross_et->SetHighLightColor(2);
   canv_cross_et->Range(0,0,1,1);
   canv_cross_et->SetFillColor(0);
   canv_cross_et->SetBorderMode(0);
   canv_cross_et->SetBorderSize(2);
   canv_cross_et->SetTopMargin(0.04761905);
   canv_cross_et->SetBottomMargin(0.05);
   canv_cross_et->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_et_1
   TPad *canv_cross_et_1 = new TPad("canv_cross_et_1", "_1",0.1,0.4,0.9,0.9);
   canv_cross_et_1->Draw();
   canv_cross_et_1->cd();
   canv_cross_et_1->Range(2.256098,0.05,15.67073,2.6);
   canv_cross_et_1->SetFillColor(0);
   canv_cross_et_1->SetBorderMode(0);
   canv_cross_et_1->SetBorderSize(2);
   canv_cross_et_1->SetTickx(1);
   canv_cross_et_1->SetTicky(1);
   canv_cross_et_1->SetLeftMargin(0.13);
   canv_cross_et_1->SetRightMargin(0.05);
   canv_cross_et_1->SetTopMargin(0);
   canv_cross_et_1->SetBottomMargin(0);
   canv_cross_et_1->SetFrameBorderMode(0);
   canv_cross_et_1->SetFrameBorderMode(0);
   Double_t xAxis103[5] = {4, 6, 8, 10, 15}; 
   
   TH2D *h_window_cross_et = new TH2D("h_window_cross_et","",4, xAxis103,10,0.05,2.6);
   h_window_cross_et->SetStats(0);
   h_window_cross_et->GetXaxis()->SetTitle("E_{T}^{photon} (GeV)");
   h_window_cross_et->GetXaxis()->CenterTitle(true);
   h_window_cross_et->GetXaxis()->SetNdivisions(507);
   h_window_cross_et->GetXaxis()->SetLabelFont(42);
   h_window_cross_et->GetXaxis()->SetLabelSize(0.05073171);
   h_window_cross_et->GetXaxis()->SetTitleSize(0.06341463);
   h_window_cross_et->GetXaxis()->SetTitleFont(42);
   h_window_cross_et->GetYaxis()->SetTitle("d#sigma/d E_{T}^{photon} (pb/GeV)");
   h_window_cross_et->GetYaxis()->CenterTitle(true);
   h_window_cross_et->GetYaxis()->SetNdivisions(507);
   h_window_cross_et->GetYaxis()->SetLabelFont(42);
   h_window_cross_et->GetYaxis()->SetLabelSize(0.0416);
   h_window_cross_et->GetYaxis()->SetTitleSize(0.052);
   h_window_cross_et->GetYaxis()->SetTitleFont(42);
   h_window_cross_et->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(42);
   grae->SetPoint(0,5,4.450064);
   grae->SetPointError(0,0,0,0.530402,0.4977016);
   grae->SetPoint(1,7,2.113483);
   grae->SetPointError(1,0,0,0.218464,0.110225);
   grae->SetPoint(2,9,0.9970458);
   grae->SetPointError(2,0,0,0.07302704,0.05767261);
   grae->SetPoint(3,12.5,0.4281783);
   grae->SetPointError(3,0,0,0.0237184,0.02661948);
   
   TH1F *Graph1 = new TH1F("Graph1","Graph",100,4.25,13.25);
   Graph1->SetMinimum(0);
   Graph1->SetMaximum(5.402096);
   Graph1->SetDirectory(0);
   Graph1->SetStats(0);
   Graph1->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph1);
   
   grae->Draw("e3 ");
   Double_t xAxis104[5] = {4, 6, 8, 10, 15}; 
   
   TH1D *h_cross_section_et = new TH1D("h_cross_section_et","det_cross_et",4, xAxis104);
   h_cross_section_et->SetBinContent(1,4.450064);
   h_cross_section_et->SetBinContent(2,2.113483);
   h_cross_section_et->SetBinContent(3,0.9970458);
   h_cross_section_et->SetBinContent(4,0.4281783);
   h_cross_section_et->SetBinError(1,0.3443503);
   h_cross_section_et->SetBinError(2,0.1795041);
   h_cross_section_et->SetBinError(3,0.1155849);
   h_cross_section_et->SetBinError(4,0.04047526);
   h_cross_section_et->SetEntries(22622);
   h_cross_section_et->SetFillColor(41);
   h_cross_section_et->SetMarkerStyle(20);
   h_cross_section_et->SetMarkerSize(0.8);
   h_cross_section_et->Draw("E1 X0 SAME");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(20);
   grae->SetPoint(0,5,4.450064);
   grae->SetPointError(0,0,0,0.6323792,0.4869849);
   grae->SetPoint(1,7,2.113483);
   grae->SetPointError(1,0,0,0.2827512,0.2538571);
   grae->SetPoint(2,9,0.9970458);
   grae->SetPointError(2,0,0,0.1367217,0.1634617);
   grae->SetPoint(3,12.5,0.4281783);
   grae->SetPointError(3,0,0,0.04691278,0.05724066);
   grae->Draw("e ");
   
   TLegend *leg = new TLegend(0.3,0.65,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_cross_section_et","ZEUS (332 pb^{-1})","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.8);
   entry=leg->AddEntry("Graph","systematic uncertainty","f");
   entry->SetFillColor(42);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Graph","inner error bars are stat. uncertainties","le");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Graph","outer error bars are total uncertainties","le");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   
   leg = new TLegend(0.5,0.25,0.9,0.65,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("NULL","At the bottom:","h");
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
   canv_cross_et_1->Modified();
   canv_cross_et->cd();
  
// ------------>Primitives in pad: canv_cross_et_2
   canv_cross_et_2 = new TPad("canv_cross_et_2", "_2",0.1,0.2,0.9,0.4);
   canv_cross_et_2->Draw();
   canv_cross_et_2->cd();
   canv_cross_et_2->Range(2.256098,-0.5416667,15.67073,0.325);
   canv_cross_et_2->SetFillColor(0);
   canv_cross_et_2->SetBorderMode(0);
   canv_cross_et_2->SetBorderSize(2);
   canv_cross_et_2->SetTickx(1);
   canv_cross_et_2->SetTicky(1);
   canv_cross_et_2->SetLeftMargin(0.13);
   canv_cross_et_2->SetRightMargin(0.05);
   canv_cross_et_2->SetTopMargin(0);
   canv_cross_et_2->SetBottomMargin(0.25);
   canv_cross_et_2->SetFrameBorderMode(0);
   canv_cross_et_2->SetFrameBorderMode(0);
   Double_t xAxis105[5] = {4, 6, 8, 10, 15}; 
   
   TH2D *h_window_cross_ratio_et = new TH2D("h_window_cross_ratio_et","",4, xAxis105,10,-0.325,0.325);
   h_window_cross_ratio_et->SetStats(0);
   h_window_cross_ratio_et->GetXaxis()->SetTitle("E_{T}^{photon} (GeV)");
   h_window_cross_ratio_et->GetXaxis()->CenterTitle(true);
   h_window_cross_ratio_et->GetXaxis()->SetNdivisions(507);
   h_window_cross_ratio_et->GetXaxis()->SetLabelFont(42);
   h_window_cross_ratio_et->GetXaxis()->SetLabelSize(0.09756097);
   h_window_cross_ratio_et->GetXaxis()->SetTitleSize(0.1219512);
   h_window_cross_ratio_et->GetXaxis()->SetTickLength(0.07);
   h_window_cross_ratio_et->GetXaxis()->SetTitleOffset(0.8);
   h_window_cross_ratio_et->GetXaxis()->SetTitleFont(42);
   h_window_cross_ratio_et->GetYaxis()->SetTitle("rel. difference");
   h_window_cross_ratio_et->GetYaxis()->CenterTitle(true);
   h_window_cross_ratio_et->GetYaxis()->SetNdivisions(406);
   h_window_cross_ratio_et->GetYaxis()->SetLabelFont(42);
   h_window_cross_ratio_et->GetYaxis()->SetLabelSize(0.08533333);
   h_window_cross_ratio_et->GetYaxis()->SetTitleSize(0.1066667);
   h_window_cross_ratio_et->GetYaxis()->SetTitleOffset(0.5);
   h_window_cross_ratio_et->GetYaxis()->SetTitleFont(42);
   h_window_cross_ratio_et->Draw("");
   
   TF1 *Unity = new TF1("Unity","0",-100,500);
   Unity->SetFillColor(19);
   Unity->SetFillStyle(0);
   Unity->SetLineColor(32);
   Unity->SetLineWidth(1);
   Unity->GetXaxis()->SetTitleFont(42);
   Unity->Draw("SAME");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3454);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,5,0);
   grae->SetPointError(0,0,0,0.07785507,0.0740436);
   grae->SetPoint(1,7,0);
   grae->SetPointError(1,0,0,0.09364757,0.03188728);
   grae->SetPoint(2,9,0);
   grae->SetPointError(2,0,0,0.0117903,0.01513603);
   grae->SetPoint(3,12.5,0);
   grae->SetPointError(3,0,0,0.01925362,0.02877543);
   
   TH1F *Graph2 = new TH1F("Graph2","Graph",100,4.25,13.25);
   Graph2->SetMinimum(-0.1104167);
   Graph2->SetMaximum(0.09081271);
   Graph2->SetDirectory(0);
   Graph2->SetStats(0);
   Graph2->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph2);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,5,-0.07785507);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,7,-0.09364757);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,9,-0.0117903);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,12.5,-0.01925362);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph3 = new TH1F("Graph3","Graph",100,4.25,13.25);
   Graph3->SetMinimum(-0.1018333);
   Graph3->SetMaximum(-0.003604574);
   Graph3->SetDirectory(0);
   Graph3->SetStats(0);
   Graph3->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph3);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,5,0.0740436);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,7,0.03188728);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,9,0.01513603);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,12.5,0.02877543);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph4 = new TH1F("Graph4","Graph",100,4.25,13.25);
   Graph4->SetMinimum(0.009245269);
   Graph4->SetMaximum(0.07993435);
   Graph4->SetDirectory(0);
   Graph4->SetStats(0);
   Graph4->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph4);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3445);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,5,0);
   grae->SetPointError(0,0,0,0.02464586,0.02033965);
   grae->SetPoint(1,7,0);
   grae->SetPointError(1,0,0,0.03145161,0.01348721);
   grae->SetPoint(2,9,0);
   grae->SetPointError(2,0,0,0.001643292,0.0004351132);
   grae->SetPoint(3,12.5,0);
   grae->SetPointError(3,0,0,0.004520511,0.006642609);
   
   TH1F *Graph5 = new TH1F("Graph5","Graph",100,4.25,13.25);
   Graph5->SetMinimum(-0.03663074);
   Graph5->SetMaximum(0.02551878);
   Graph5->SetDirectory(0);
   Graph5->SetStats(0);
   Graph5->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph5);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,5,-0.02464586);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,7,-0.03145161);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,9,-0.001643292);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,12.5,-0.004520511);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph6 = new TH1F("Graph6","Graph",100,4.25,13.25);
   Graph6->SetMinimum(-0.03443245);
   Graph6->SetMaximum(0.00133754);
   Graph6->SetDirectory(0);
   Graph6->SetStats(0);
   Graph6->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph6);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,5,0.02033965);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,7,0.01348721);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,9,0.0004351132);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,12.5,0.006642609);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph7 = new TH1F("Graph7","Graph",100,4.25,13.25);
   Graph7->SetMinimum(0);
   Graph7->SetMaximum(0.0223301);
   Graph7->SetDirectory(0);
   Graph7->SetStats(0);
   Graph7->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph7);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3425);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,5,0);
   grae->SetPointError(0,0,0,0.03222338,0.06178629);
   grae->SetPoint(1,7,0);
   grae->SetPointError(1,0,0,0.01450686,0.03188728);
   grae->SetPoint(2,9,0);
   grae->SetPointError(2,0,0,0.04912977,0.007259632);
   grae->SetPoint(3,12.5,0);
   grae->SetPointError(3,0,0,0.04829431,0.009958387);
   
   TH1F *Graph8 = new TH1F("Graph8","Graph",100,4.25,13.25);
   Graph8->SetMinimum(-0.06022138);
   Graph8->SetMaximum(0.0728779);
   Graph8->SetDirectory(0);
   Graph8->SetStats(0);
   Graph8->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph8);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,5,-0.03222338);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,7,-0.01450686);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,9,-0.04912977);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,12.5,-0.04829431);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph9 = new TH1F("Graph9","Graph",100,4.25,13.25);
   Graph9->SetMinimum(-0.05259207);
   Graph9->SetMaximum(-0.01104457);
   Graph9->SetDirectory(0);
   Graph9->SetStats(0);
   Graph9->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph9);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,5,0.06178629);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,7,0.03188728);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,9,0.007259632);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,12.5,0.009958387);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph10 = new TH1F("Graph10","Graph",100,4.25,13.25);
   Graph10->SetMinimum(0.001806965);
   Graph10->SetMaximum(0.06723896);
   Graph10->SetDirectory(0);
   Graph10->SetStats(0);
   Graph10->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph10);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3452);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,5,0);
   grae->SetPointError(0,0,0,0.0806165,0.05286593);
   grae->SetPoint(1,7,0);
   grae->SetPointError(1,0,0,0.02674268,0.02246014);
   grae->SetPoint(2,9,0);
   grae->SetPointError(2,0,0,0.05300144,0.05535231);
   grae->SetPoint(3,12.5,0);
   grae->SetPointError(3,0,0,0.01857388,0.05379297);
   
   TH1F *Graph11 = new TH1F("Graph11","Graph",100,4.25,13.25);
   Graph11->SetMinimum(-0.09421338);
   Graph11->SetMaximum(0.0689492);
   Graph11->SetDirectory(0);
   Graph11->SetStats(0);
   Graph11->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph11);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,5,-0.0806165);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,7,-0.02674268);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,9,-0.05300144);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,12.5,-0.01857388);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph12 = new TH1F("Graph12","Graph",100,4.25,13.25);
   Graph12->SetMinimum(-0.08682076);
   Graph12->SetMaximum(-0.01236962);
   Graph12->SetDirectory(0);
   Graph12->SetStats(0);
   Graph12->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph12);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,5,0.05286593);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,7,0.02246014);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,9,0.05535231);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,12.5,0.05379297);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph13 = new TH1F("Graph13","Graph",100,4.25,13.25);
   Graph13->SetMinimum(0.01917092);
   Graph13->SetMaximum(0.05864153);
   Graph13->SetDirectory(0);
   Graph13->SetStats(0);
   Graph13->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph13);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);
   grae->SetFillStyle(3445);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,5,0);
   grae->SetPointError(0,0,0,0.1191898,0.1118414);
   grae->SetPoint(1,7,0);
   grae->SetPointError(1,0,0,0.1033668,0.05215324);
   grae->SetPoint(2,9,0);
   grae->SetPointError(2,0,0,0.07324342,0.05784349);
   grae->SetPoint(3,12.5,0);
   grae->SetPointError(3,0,0,0.05539374,0.06216915);
   grae->Draw("e ");
   canv_cross_et_2->Modified();
   canv_cross_et->cd();
   canv_cross_et->Modified();
   canv_cross_et->cd();
   canv_cross_et->SetSelected(canv_cross_et);
}
