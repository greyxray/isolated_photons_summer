{
//=========Macro generated from canvas: canv_cross_et_jet/
//=========  (Fri Mar 11 01:30:28 2011) by ROOT version5.26/00c
   TCanvas *canv_cross_et_jet = new TCanvas("canv_cross_et_jet", "",1,1,550,876);
   canv_cross_et_jet->SetHighLightColor(2);
   canv_cross_et_jet->Range(0,0,1,1);
   canv_cross_et_jet->SetFillColor(0);
   canv_cross_et_jet->SetBorderMode(0);
   canv_cross_et_jet->SetBorderSize(2);
   canv_cross_et_jet->SetTopMargin(0.04761905);
   canv_cross_et_jet->SetBottomMargin(0.05);
   canv_cross_et_jet->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_et_jet_1
   TPad *canv_cross_et_jet_1 = new TPad("canv_cross_et_jet_1", "_1",0.1,0.4,0.9,0.9);
   canv_cross_et_jet_1->Draw();
   canv_cross_et_jet_1->cd();
   canv_cross_et_jet_1->Range(-2.652439,-1.30103,36.98171,0.4771213);
   canv_cross_et_jet_1->SetFillColor(0);
   canv_cross_et_jet_1->SetBorderMode(0);
   canv_cross_et_jet_1->SetBorderSize(2);
   canv_cross_et_jet_1->SetLogy();
   canv_cross_et_jet_1->SetTickx(1);
   canv_cross_et_jet_1->SetTicky(1);
   canv_cross_et_jet_1->SetLeftMargin(0.13);
   canv_cross_et_jet_1->SetRightMargin(0.05);
   canv_cross_et_jet_1->SetTopMargin(0);
   canv_cross_et_jet_1->SetBottomMargin(0);
   canv_cross_et_jet_1->SetFrameBorderMode(0);
   canv_cross_et_jet_1->SetFrameBorderMode(0);
   Double_t xAxis115[7] = {2.5, 4, 6, 8, 10, 15, 35}; 
   
   TH2D *h_window_cross_et_jet = new TH2D("h_window_cross_et_jet","",6, xAxis115,10,0.05,3);
   h_window_cross_et_jet->SetStats(0);
   h_window_cross_et_jet->GetXaxis()->SetTitle("E_{T, jet}");
   h_window_cross_et_jet->GetXaxis()->CenterTitle(true);
   h_window_cross_et_jet->GetXaxis()->SetNdivisions(507);
   h_window_cross_et_jet->GetXaxis()->SetLabelFont(42);
   h_window_cross_et_jet->GetXaxis()->SetLabelSize(0.05073171);
   h_window_cross_et_jet->GetXaxis()->SetTitleSize(0.06341463);
   h_window_cross_et_jet->GetXaxis()->SetTitleFont(42);
   h_window_cross_et_jet->GetYaxis()->SetTitle("d#sigma/d E_{T, jet} (pb/GeV)");
   h_window_cross_et_jet->GetYaxis()->CenterTitle(true);
   h_window_cross_et_jet->GetYaxis()->SetNdivisions(507);
   h_window_cross_et_jet->GetYaxis()->SetLabelFont(42);
   h_window_cross_et_jet->GetYaxis()->SetLabelSize(0.0416);
   h_window_cross_et_jet->GetYaxis()->SetTitleSize(0.052);
   h_window_cross_et_jet->GetYaxis()->SetTitleFont(42);
   h_window_cross_et_jet->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(42);
   grae->SetPoint(0,3.25,nan);
   grae->SetPointError(0,0,0,nan,nan);
   grae->SetPoint(1,5,nan);
   grae->SetPointError(1,0,0,nan,nan);
   grae->SetPoint(2,7,nan);
   grae->SetPointError(2,0,0,nan,nan);
   grae->SetPoint(3,9,nan);
   grae->SetPointError(3,0,0,nan,nan);
   grae->SetPoint(4,12.5,nan);
   grae->SetPointError(4,0,0,nan,nan);
   grae->SetPoint(5,25,nan);
   grae->SetPointError(5,0,0,nan,nan);
   
   TH1F *Graph53 = new TH1F("Graph53","Graph",100,1.075,27.175);
   Graph53->SetMinimum(nan);
   Graph53->SetMaximum(nan);
   Graph53->SetDirectory(0);
   Graph53->SetStats(0);
   Graph53->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph53);
   
   grae->Draw("e3 ");
   Double_t xAxis116[7] = {2.5, 4, 6, 8, 10, 15, 35}; 
   
   TH1D *h_cross_section_et_jet = new TH1D("h_cross_section_et_jet","det_cross_et_jet",6, xAxis116);
   h_cross_section_et_jet->SetBinContent(0,23859.31);
   h_cross_section_et_jet->SetBinContent(1,nan);
   h_cross_section_et_jet->SetBinContent(2,nan);
   h_cross_section_et_jet->SetBinContent(3,nan);
   h_cross_section_et_jet->SetBinContent(4,nan);
   h_cross_section_et_jet->SetBinContent(5,nan);
   h_cross_section_et_jet->SetBinContent(6,nan);
   h_cross_section_et_jet->SetBinError(0,154.4646);
   h_cross_section_et_jet->SetBinError(1,nan);
   h_cross_section_et_jet->SetBinError(2,nan);
   h_cross_section_et_jet->SetBinError(3,nan);
   h_cross_section_et_jet->SetBinError(4,nan);
   h_cross_section_et_jet->SetBinError(5,nan);
   h_cross_section_et_jet->SetBinError(6,nan);
   h_cross_section_et_jet->SetEntries(22628);
   h_cross_section_et_jet->SetFillColor(41);
   h_cross_section_et_jet->SetMarkerStyle(20);
   h_cross_section_et_jet->SetMarkerSize(0.8);
   h_cross_section_et_jet->Draw("E1 X0 SAME");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(20);
   grae->SetPoint(0,3.25,nan);
   grae->SetPointError(0,0,0,nan,nan);
   grae->SetPoint(1,5,nan);
   grae->SetPointError(1,0,0,nan,nan);
   grae->SetPoint(2,7,nan);
   grae->SetPointError(2,0,0,nan,nan);
   grae->SetPoint(3,9,nan);
   grae->SetPointError(3,0,0,nan,nan);
   grae->SetPoint(4,12.5,nan);
   grae->SetPointError(4,0,0,nan,nan);
   grae->SetPoint(5,25,nan);
   grae->SetPointError(5,0,0,nan,nan);
   grae->Draw("e ");
   
   TLegend *leg = new TLegend(0.5,0.25,0.9,0.65,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","At the bottom:","h");
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
   canv_cross_et_jet_1->Modified();
   canv_cross_et_jet->cd();
  
// ------------>Primitives in pad: canv_cross_et_jet_2
   canv_cross_et_jet_2 = new TPad("canv_cross_et_jet_2", "_2",0.1,0.2,0.9,0.4);
   canv_cross_et_jet_2->Draw();
   canv_cross_et_jet_2->cd();
   canv_cross_et_jet_2->Range(-2.652439,-0.7083333,36.98171,0.425);
   canv_cross_et_jet_2->SetFillColor(0);
   canv_cross_et_jet_2->SetBorderMode(0);
   canv_cross_et_jet_2->SetBorderSize(2);
   canv_cross_et_jet_2->SetTickx(1);
   canv_cross_et_jet_2->SetTicky(1);
   canv_cross_et_jet_2->SetLeftMargin(0.13);
   canv_cross_et_jet_2->SetRightMargin(0.05);
   canv_cross_et_jet_2->SetTopMargin(0);
   canv_cross_et_jet_2->SetBottomMargin(0.25);
   canv_cross_et_jet_2->SetFrameBorderMode(0);
   canv_cross_et_jet_2->SetFrameBorderMode(0);
   Double_t xAxis117[7] = {2.5, 4, 6, 8, 10, 15, 35}; 
   
   TH2D *h_window_cross_ratio_et_jet = new TH2D("h_window_cross_ratio_et_jet","",6, xAxis117,10,-0.425,0.425);
   h_window_cross_ratio_et_jet->SetStats(0);
   h_window_cross_ratio_et_jet->GetXaxis()->SetTitle("E_{T, jet}");
   h_window_cross_ratio_et_jet->GetXaxis()->CenterTitle(true);
   h_window_cross_ratio_et_jet->GetXaxis()->SetNdivisions(507);
   h_window_cross_ratio_et_jet->GetXaxis()->SetLabelFont(42);
   h_window_cross_ratio_et_jet->GetXaxis()->SetLabelSize(0.09756097);
   h_window_cross_ratio_et_jet->GetXaxis()->SetTitleSize(0.1219512);
   h_window_cross_ratio_et_jet->GetXaxis()->SetTickLength(0.07);
   h_window_cross_ratio_et_jet->GetXaxis()->SetTitleOffset(0.8);
   h_window_cross_ratio_et_jet->GetXaxis()->SetTitleFont(42);
   h_window_cross_ratio_et_jet->GetYaxis()->SetTitle("rel. difference");
   h_window_cross_ratio_et_jet->GetYaxis()->CenterTitle(true);
   h_window_cross_ratio_et_jet->GetYaxis()->SetNdivisions(406);
   h_window_cross_ratio_et_jet->GetYaxis()->SetLabelFont(42);
   h_window_cross_ratio_et_jet->GetYaxis()->SetLabelSize(0.08533333);
   h_window_cross_ratio_et_jet->GetYaxis()->SetTitleSize(0.1066667);
   h_window_cross_ratio_et_jet->GetYaxis()->SetTitleOffset(0.5);
   h_window_cross_ratio_et_jet->GetYaxis()->SetTitleFont(42);
   h_window_cross_ratio_et_jet->Draw("");
   
   TF1 *Unity = new TF1("Unity","0",-100,500);
   Unity->SetFillColor(19);
   Unity->SetFillStyle(0);
   Unity->SetLineColor(32);
   Unity->SetLineWidth(1);
   Unity->GetXaxis()->SetTitleFont(42);
   Unity->Draw("SAME");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3454);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,3.25,0);
   grae->SetPointError(0,0,0,0.09954002,0.07718371);
   grae->SetPoint(1,5,0);
   grae->SetPointError(1,0,0,0.05473381,0.04471588);
   grae->SetPoint(2,7,0);
   grae->SetPointError(2,0,0,0.03714176,0.04632043);
   grae->SetPoint(3,9,0);
   grae->SetPointError(3,0,0,0.07347376,0.02246628);
   grae->SetPoint(4,12.5,0);
   grae->SetPointError(4,0,0,0,-0.09954002);
   grae->SetPoint(5,25,0);
   grae->SetPointError(5,0,0,0,-0.05473381);
   
   TH1F *Graph54 = new TH1F("Graph54","Graph",100,1.075,27.175);
   Graph54->SetMinimum(-0.1172124);
   Graph54->SetMaximum(0.09485608);
   Graph54->SetDirectory(0);
   Graph54->SetStats(0);
   Graph54->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph54);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,3.25,-0.09954002);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,5,-0.05473381);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,7,-0.03714176);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,9,-0.07347376);
   grae->SetPointError(3,0,0,0,0);
   grae->SetPoint(4,12.5,0.09954002);
   grae->SetPointError(4,0,0,0,0);
   grae->SetPoint(5,25,0.05473381);
   grae->SetPointError(5,0,0,0,0);
   
   TH1F *Graph55 = new TH1F("Graph55","Graph",100,1.075,27.175);
   Graph55->SetMinimum(-0.119448);
   Graph55->SetMaximum(0.119448);
   Graph55->SetDirectory(0);
   Graph55->SetStats(0);
   Graph55->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph55);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,3.25,0.07718371);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,5,0.04471588);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,7,0.04632043);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,9,0.02246628);
   grae->SetPointError(3,0,0,0,0);
   grae->SetPoint(4,12.5,-0.09954002);
   grae->SetPointError(4,0,0,0,0);
   grae->SetPoint(5,25,-0.05473381);
   grae->SetPointError(5,0,0,0,0);
   
   TH1F *Graph56 = new TH1F("Graph56","Graph",100,1.075,27.175);
   Graph56->SetMinimum(-0.1172124);
   Graph56->SetMaximum(0.09485608);
   Graph56->SetDirectory(0);
   Graph56->SetStats(0);
   Graph56->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph56);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3445);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,3.25,0);
   grae->SetPointError(0,0,0,0.025818,0.02536039);
   grae->SetPoint(1,5,0);
   grae->SetPointError(1,0,0,0.03525772,0.01400966);
   grae->SetPoint(2,7,0);
   grae->SetPointError(2,0,0,0.003045055,0.008037759);
   grae->SetPoint(3,9,0);
   grae->SetPointError(3,0,0,0.01472498,0.002032266);
   grae->SetPoint(4,12.5,0);
   grae->SetPointError(4,0,0,0.05229276,-0.025818);
   grae->SetPoint(5,25,0);
   grae->SetPointError(5,0,0,0.06063469,-0.03525772);
   
   TH1F *Graph57 = new TH1F("Graph57","Graph",100,1.075,27.175);
   Graph57->SetMinimum(-0.0692342);
   Graph57->SetMaximum(0.0339599);
   Graph57->SetDirectory(0);
   Graph57->SetStats(0);
   Graph57->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph57);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,3.25,-0.025818);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,5,-0.03525772);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,7,-0.003045055);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,9,-0.01472498);
   grae->SetPointError(3,0,0,0,0);
   grae->SetPoint(4,12.5,0.025818);
   grae->SetPointError(4,0,0,0,0);
   grae->SetPoint(5,25,0.03525772);
   grae->SetPointError(5,0,0,0,0);
   
   TH1F *Graph58 = new TH1F("Graph58","Graph",100,1.075,27.175);
   Graph58->SetMinimum(-0.04230926);
   Graph58->SetMaximum(0.04230926);
   Graph58->SetDirectory(0);
   Graph58->SetStats(0);
   Graph58->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph58);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,3.25,0.02536039);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,5,0.01400966);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,7,0.008037759);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,9,0.002032266);
   grae->SetPointError(3,0,0,0,0);
   grae->SetPoint(4,12.5,-0.025818);
   grae->SetPointError(4,0,0,0,0);
   grae->SetPoint(5,25,-0.03525772);
   grae->SetPointError(5,0,0,0,0);
   
   TH1F *Graph59 = new TH1F("Graph59","Graph",100,1.075,27.175);
   Graph59->SetMinimum(-0.04131953);
   Graph59->SetMaximum(0.03142221);
   Graph59->SetDirectory(0);
   Graph59->SetStats(0);
   Graph59->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph59);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3425);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,3.25,0);
   grae->SetPointError(0,0,0,0.0801617,0.06452722);
   grae->SetPoint(1,5,0);
   grae->SetPointError(1,0,0,0.03160764,0.03520174);
   grae->SetPoint(2,7,0);
   grae->SetPointError(2,0,0,0.005342687,0.04693932);
   grae->SetPoint(3,9,0);
   grae->SetPointError(3,0,0,0.01363925,0.05963566);
   grae->SetPoint(4,12.5,0);
   grae->SetPointError(4,0,0,0.01099658,-0.0801617);
   grae->SetPoint(5,25,0);
   grae->SetPointError(5,0,0,0.01578849,-0.03160764);
   
   TH1F *Graph60 = new TH1F("Graph60","Graph",100,1.075,27.175);
   Graph60->SetMinimum(-0.0946306);
   Graph60->SetMaximum(0.07899611);
   Graph60->SetDirectory(0);
   Graph60->SetStats(0);
   Graph60->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph60);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,3.25,-0.0801617);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,5,-0.03160764);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,7,-0.005342687);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,9,-0.01363925);
   grae->SetPointError(3,0,0,0,0);
   grae->SetPoint(4,12.5,0.0801617);
   grae->SetPointError(4,0,0,0,0);
   grae->SetPoint(5,25,0.03160764);
   grae->SetPointError(5,0,0,0,0);
   
   TH1F *Graph61 = new TH1F("Graph61","Graph",100,1.075,27.175);
   Graph61->SetMinimum(-0.09619404);
   Graph61->SetMaximum(0.09619404);
   Graph61->SetDirectory(0);
   Graph61->SetStats(0);
   Graph61->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph61);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,3.25,0.06452722);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,5,0.03520174);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,7,0.04693932);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,9,0.05963566);
   grae->SetPointError(3,0,0,0,0);
   grae->SetPoint(4,12.5,-0.0801617);
   grae->SetPointError(4,0,0,0,0);
   grae->SetPoint(5,25,-0.03160764);
   grae->SetPointError(5,0,0,0,0);
   
   TH1F *Graph62 = new TH1F("Graph62","Graph",100,1.075,27.175);
   Graph62->SetMinimum(-0.0946306);
   Graph62->SetMaximum(0.07899611);
   Graph62->SetDirectory(0);
   Graph62->SetStats(0);
   Graph62->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph62);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3452);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,3.25,0);
   grae->SetPointError(0,0,0,0.0698383,0.05623103);
   grae->SetPoint(1,5,0);
   grae->SetPointError(1,0,0,0.02433257,0.02869105);
   grae->SetPoint(2,7,0);
   grae->SetPointError(2,0,0,0.06307218,0.02957658);
   grae->SetPoint(3,9,0);
   grae->SetPointError(3,0,0,0.07417571,0.02773784);
   grae->SetPoint(4,12.5,0);
   grae->SetPointError(4,0,0,0.0354864,-0.0698383);
   grae->SetPoint(5,25,0);
   grae->SetPointError(5,0,0,0.0661671,-0.02433257);
   
   TH1F *Graph63 = new TH1F("Graph63","Graph",100,1.075,27.175);
   Graph63->SetMinimum(-0.08721638);
   Graph63->SetMaximum(0.06927171);
   Graph63->SetDirectory(0);
   Graph63->SetStats(0);
   Graph63->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph63);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,3.25,-0.0698383);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,5,-0.02433257);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,7,-0.06307218);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,9,-0.07417571);
   grae->SetPointError(3,0,0,0,0);
   grae->SetPoint(4,12.5,0.0698383);
   grae->SetPointError(4,0,0,0,0);
   grae->SetPoint(5,25,0.02433257);
   grae->SetPointError(5,0,0,0,0);
   
   TH1F *Graph64 = new TH1F("Graph64","Graph",100,1.075,27.175);
   Graph64->SetMinimum(-0.08857711);
   Graph64->SetMaximum(0.0842397);
   Graph64->SetDirectory(0);
   Graph64->SetStats(0);
   Graph64->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph64);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,3.25,0.05623103);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,5,0.02869105);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,7,0.02957658);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,9,0.02773784);
   grae->SetPointError(3,0,0,0,0);
   grae->SetPoint(4,12.5,-0.0698383);
   grae->SetPointError(4,0,0,0,0);
   grae->SetPoint(5,25,-0.02433257);
   grae->SetPointError(5,0,0,0,0);
   
   TH1F *Graph65 = new TH1F("Graph65","Graph",100,1.075,27.175);
   Graph65->SetMinimum(-0.08244523);
   Graph65->SetMaximum(0.06883796);
   Graph65->SetDirectory(0);
   Graph65->SetStats(0);
   Graph65->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph65);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);
   grae->SetFillStyle(3445);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,3.25,0);
   grae->SetPointError(0,0,0,0.1479124,0.1180092);
   grae->SetPoint(1,5,0);
   grae->SetPointError(1,0,0,0.07635452,0.06525427);
   grae->SetPoint(2,7,0);
   grae->SetPointError(2,0,0,0.07345357,0.07272044);
   grae->SetPoint(3,9,0);
   grae->SetPointError(3,0,0,0.1063169,0.06953175);
   grae->SetPoint(4,12.5,0);
   grae->SetPointError(4,0,0,0.06414626,0.1479124);
   grae->SetPoint(5,25,0);
   grae->SetPointError(5,0,0,0.09112589,0.07635452);
   grae->Draw("e ");
   canv_cross_et_jet_2->Modified();
   canv_cross_et_jet->cd();
   canv_cross_et_jet->Modified();
   canv_cross_et_jet->cd();
   canv_cross_et_jet->SetSelected(canv_cross_et_jet);
}
