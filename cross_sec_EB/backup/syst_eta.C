{
//=========Macro generated from canvas: canv_cross_eta/
//=========  (Fri Mar 11 01:30:27 2011) by ROOT version5.26/00c
   TCanvas *canv_cross_eta = new TCanvas("canv_cross_eta", "",1,1,550,876);
   canv_cross_eta->SetHighLightColor(2);
   canv_cross_eta->Range(0,0,1,1);
   canv_cross_eta->SetFillColor(0);
   canv_cross_eta->SetBorderMode(0);
   canv_cross_eta->SetBorderSize(2);
   canv_cross_eta->SetTopMargin(0.04761905);
   canv_cross_eta->SetBottomMargin(0.05);
   canv_cross_eta->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_eta_1
   TPad *canv_cross_eta_1 = new TPad("canv_cross_eta_1", "_1",0.1,0.4,0.9,0.9);
   canv_cross_eta_1->Draw();
   canv_cross_eta_1->cd();
   canv_cross_eta_1->Range(-0.9536585,0.05,0.997561,8.5);
   canv_cross_eta_1->SetFillColor(0);
   canv_cross_eta_1->SetBorderMode(0);
   canv_cross_eta_1->SetBorderSize(2);
   canv_cross_eta_1->SetTickx(1);
   canv_cross_eta_1->SetTicky(1);
   canv_cross_eta_1->SetLeftMargin(0.13);
   canv_cross_eta_1->SetRightMargin(0.05);
   canv_cross_eta_1->SetTopMargin(0);
   canv_cross_eta_1->SetBottomMargin(0);
   canv_cross_eta_1->SetFrameBorderMode(0);
   canv_cross_eta_1->SetFrameBorderMode(0);
   Double_t xAxis106[5] = {-0.7, -0.3, 0.1, 0.5, 0.9}; 
   
   TH2D *h_window_cross_eta = new TH2D("h_window_cross_eta","",4, xAxis106,10,0.05,8.5);
   h_window_cross_eta->SetStats(0);
   h_window_cross_eta->GetXaxis()->SetTitle("#eta_{photon}");
   h_window_cross_eta->GetXaxis()->CenterTitle(true);
   h_window_cross_eta->GetXaxis()->SetNdivisions(507);
   h_window_cross_eta->GetXaxis()->SetLabelFont(42);
   h_window_cross_eta->GetXaxis()->SetLabelSize(0.05073171);
   h_window_cross_eta->GetXaxis()->SetTitleSize(0.06341463);
   h_window_cross_eta->GetXaxis()->SetTitleFont(42);
   h_window_cross_eta->GetYaxis()->SetTitle("d#sigma/d #eta_{photon} (pb)");
   h_window_cross_eta->GetYaxis()->CenterTitle(true);
   h_window_cross_eta->GetYaxis()->SetNdivisions(507);
   h_window_cross_eta->GetYaxis()->SetLabelFont(42);
   h_window_cross_eta->GetYaxis()->SetLabelSize(0.0416);
   h_window_cross_eta->GetYaxis()->SetTitleSize(0.052);
   h_window_cross_eta->GetYaxis()->SetTitleFont(42);
   h_window_cross_eta->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(42);
   grae->SetPoint(0,-0.5,12.97556);
   grae->SetPointError(0,0,0,1.919245,1.531235);
   grae->SetPoint(1,-0.1,11.68049);
   grae->SetPointError(1,0,0,0.8918585,0.762202);
   grae->SetPoint(2,0.3,10.39248);
   grae->SetPointError(2,0,0,0.7633648,0.7557457);
   grae->SetPoint(3,0.7,6.480043);
   grae->SetPointError(3,0,0,0.6889381,0.4505687);
   
   TH1F *Graph14 = new TH1F("Graph14","Graph",100,-0.62,0.82);
   Graph14->SetMinimum(4.919537);
   Graph14->SetMaximum(15.37836);
   Graph14->SetDirectory(0);
   Graph14->SetStats(0);
   Graph14->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph14);
   
   grae->Draw("e3 ");
   Double_t xAxis107[5] = {-0.7, -0.3, 0.1, 0.5, 0.9}; 
   
   TH1D *h_cross_section_eta = new TH1D("h_cross_section_eta","det_cross_eta",4, xAxis107);
   h_cross_section_eta->SetBinContent(1,12.97556);
   h_cross_section_eta->SetBinContent(2,11.68049);
   h_cross_section_eta->SetBinContent(3,10.39248);
   h_cross_section_eta->SetBinContent(4,6.480043);
   h_cross_section_eta->SetBinError(1,1.069656);
   h_cross_section_eta->SetBinError(2,1.004123);
   h_cross_section_eta->SetBinError(3,0.9665408);
   h_cross_section_eta->SetBinError(4,0.917661);
   h_cross_section_eta->SetEntries(22622);
   h_cross_section_eta->SetFillColor(41);
   h_cross_section_eta->SetMarkerStyle(20);
   h_cross_section_eta->SetMarkerSize(0.8);
   h_cross_section_eta->Draw("E1 X0 SAME");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(20);
   grae->SetPoint(0,-0.5,12.97556);
   grae->SetPointError(0,0,0,2.197195,1.512722);
   grae->SetPoint(1,-0.1,11.68049);
   grae->SetPointError(1,0,0,1.34301,1.420044);
   grae->SetPoint(2,0.3,10.39248);
   grae->SetPointError(2,0,0,1.231636,1.366895);
   grae->SetPoint(3,0.7,6.480043);
   grae->SetPointError(3,0,0,1.147492,1.297769);
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
   canv_cross_eta_1->Modified();
   canv_cross_eta->cd();
  
// ------------>Primitives in pad: canv_cross_eta_2
   canv_cross_eta_2 = new TPad("canv_cross_eta_2", "_2",0.1,0.2,0.9,0.4);
   canv_cross_eta_2->Draw();
   canv_cross_eta_2->cd();
   canv_cross_eta_2->Range(-0.9536585,-0.5416667,0.997561,0.325);
   canv_cross_eta_2->SetFillColor(0);
   canv_cross_eta_2->SetBorderMode(0);
   canv_cross_eta_2->SetBorderSize(2);
   canv_cross_eta_2->SetTickx(1);
   canv_cross_eta_2->SetTicky(1);
   canv_cross_eta_2->SetLeftMargin(0.13);
   canv_cross_eta_2->SetRightMargin(0.05);
   canv_cross_eta_2->SetTopMargin(0);
   canv_cross_eta_2->SetBottomMargin(0.25);
   canv_cross_eta_2->SetFrameBorderMode(0);
   canv_cross_eta_2->SetFrameBorderMode(0);
   Double_t xAxis108[5] = {-0.7, -0.3, 0.1, 0.5, 0.9}; 
   
   TH2D *h_window_cross_ratio_eta = new TH2D("h_window_cross_ratio_eta","",4, xAxis108,10,-0.325,0.325);
   h_window_cross_ratio_eta->SetStats(0);
   h_window_cross_ratio_eta->GetXaxis()->SetTitle("#eta_{photon}");
   h_window_cross_ratio_eta->GetXaxis()->CenterTitle(true);
   h_window_cross_ratio_eta->GetXaxis()->SetNdivisions(507);
   h_window_cross_ratio_eta->GetXaxis()->SetLabelFont(42);
   h_window_cross_ratio_eta->GetXaxis()->SetLabelSize(0.09756097);
   h_window_cross_ratio_eta->GetXaxis()->SetTitleSize(0.1219512);
   h_window_cross_ratio_eta->GetXaxis()->SetTickLength(0.07);
   h_window_cross_ratio_eta->GetXaxis()->SetTitleOffset(0.8);
   h_window_cross_ratio_eta->GetXaxis()->SetTitleFont(42);
   h_window_cross_ratio_eta->GetYaxis()->SetTitle("rel. difference");
   h_window_cross_ratio_eta->GetYaxis()->CenterTitle(true);
   h_window_cross_ratio_eta->GetYaxis()->SetNdivisions(406);
   h_window_cross_ratio_eta->GetYaxis()->SetLabelFont(42);
   h_window_cross_ratio_eta->GetYaxis()->SetLabelSize(0.08533333);
   h_window_cross_ratio_eta->GetYaxis()->SetTitleSize(0.1066667);
   h_window_cross_ratio_eta->GetYaxis()->SetTitleOffset(0.5);
   h_window_cross_ratio_eta->GetYaxis()->SetTitleFont(42);
   h_window_cross_ratio_eta->Draw("");
   
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
   grae->SetPoint(0,-0.5,0);
   grae->SetPointError(0,0,0,0.09954002,0.07718371);
   grae->SetPoint(1,-0.1,0);
   grae->SetPointError(1,0,0,0.05473381,0.04471588);
   grae->SetPoint(2,0.3,0);
   grae->SetPointError(2,0,0,0.03714176,0.04632043);
   grae->SetPoint(3,0.7,0);
   grae->SetPointError(3,0,0,0.07347376,0.02246628);
   
   TH1F *Graph15 = new TH1F("Graph15","Graph",100,-0.62,0.82);
   Graph15->SetMinimum(-0.1172124);
   Graph15->SetMaximum(0.09485608);
   Graph15->SetDirectory(0);
   Graph15->SetStats(0);
   Graph15->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph15);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-0.5,-0.09954002);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,-0.1,-0.05473381);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.3,-0.03714176);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,0.7,-0.07347376);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph16 = new TH1F("Graph16","Graph",100,-0.62,0.82);
   Graph16->SetMinimum(-0.1057798);
   Graph16->SetMaximum(-0.03090193);
   Graph16->SetDirectory(0);
   Graph16->SetStats(0);
   Graph16->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph16);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-0.5,0.07718371);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,-0.1,0.04471588);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.3,0.04632043);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,0.7,0.02246628);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph17 = new TH1F("Graph17","Graph",100,-0.62,0.82);
   Graph17->SetMinimum(0.01699454);
   Graph17->SetMaximum(0.08265545);
   Graph17->SetDirectory(0);
   Graph17->SetStats(0);
   Graph17->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph17);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3445);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,-0.5,0);
   grae->SetPointError(0,0,0,0.025818,0.02536039);
   grae->SetPoint(1,-0.1,0);
   grae->SetPointError(1,0,0,0.03525772,0.01400966);
   grae->SetPoint(2,0.3,0);
   grae->SetPointError(2,0,0,0.003045055,0.008037759);
   grae->SetPoint(3,0.7,0);
   grae->SetPointError(3,0,0,0.01472498,0.002032266);
   
   TH1F *Graph18 = new TH1F("Graph18","Graph",100,-0.62,0.82);
   Graph18->SetMinimum(-0.04131953);
   Graph18->SetMaximum(0.03142221);
   Graph18->SetDirectory(0);
   Graph18->SetStats(0);
   Graph18->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph18);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-0.5,-0.025818);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,-0.1,-0.03525772);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.3,-0.003045055);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,0.7,-0.01472498);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph19 = new TH1F("Graph19","Graph",100,-0.62,0.82);
   Graph19->SetMinimum(-0.03847898);
   Graph19->SetMaximum(0.0001762112);
   Graph19->SetDirectory(0);
   Graph19->SetStats(0);
   Graph19->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph19);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-0.5,0.02536039);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,-0.1,0.01400966);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.3,0.008037759);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,0.7,0.002032266);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph20 = new TH1F("Graph20","Graph",100,-0.62,0.82);
   Graph20->SetMinimum(0);
   Graph20->SetMaximum(0.02769321);
   Graph20->SetDirectory(0);
   Graph20->SetStats(0);
   Graph20->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph20);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3425);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,-0.5,0);
   grae->SetPointError(0,0,0,0.0801617,0.06452722);
   grae->SetPoint(1,-0.1,0);
   grae->SetPointError(1,0,0,0.03160764,0.03520174);
   grae->SetPoint(2,0.3,0);
   grae->SetPointError(2,0,0,0.005342687,0.04693932);
   grae->SetPoint(3,0.7,0);
   grae->SetPointError(3,0,0,0.01363925,0.05963566);
   
   TH1F *Graph21 = new TH1F("Graph21","Graph",100,-0.62,0.82);
   Graph21->SetMinimum(-0.0946306);
   Graph21->SetMaximum(0.07899611);
   Graph21->SetDirectory(0);
   Graph21->SetStats(0);
   Graph21->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph21);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-0.5,-0.0801617);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,-0.1,-0.03160764);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.3,-0.005342687);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,0.7,-0.01363925);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph22 = new TH1F("Graph22","Graph",100,-0.62,0.82);
   Graph22->SetMinimum(-0.0876436);
   Graph22->SetMaximum(0.002139214);
   Graph22->SetDirectory(0);
   Graph22->SetStats(0);
   Graph22->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph22);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-0.5,0.06452722);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,-0.1,0.03520174);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.3,0.04693932);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,0.7,0.05963566);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph23 = new TH1F("Graph23","Graph",100,-0.62,0.82);
   Graph23->SetMinimum(0.03226919);
   Graph23->SetMaximum(0.06745977);
   Graph23->SetDirectory(0);
   Graph23->SetStats(0);
   Graph23->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph23);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3452);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,-0.5,0);
   grae->SetPointError(0,0,0,0.0698383,0.05623103);
   grae->SetPoint(1,-0.1,0);
   grae->SetPointError(1,0,0,0.02433257,0.02869105);
   grae->SetPoint(2,0.3,0);
   grae->SetPointError(2,0,0,0.06307218,0.02957658);
   grae->SetPoint(3,0.7,0);
   grae->SetPointError(3,0,0,0.07417571,0.02773784);
   
   TH1F *Graph24 = new TH1F("Graph24","Graph",100,-0.62,0.82);
   Graph24->SetMinimum(-0.08721638);
   Graph24->SetMaximum(0.06927171);
   Graph24->SetDirectory(0);
   Graph24->SetStats(0);
   Graph24->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph24);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-0.5,-0.0698383);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,-0.1,-0.02433257);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.3,-0.06307218);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,0.7,-0.07417571);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph25 = new TH1F("Graph25","Graph",100,-0.62,0.82);
   Graph25->SetMinimum(-0.07916002);
   Graph25->SetMaximum(-0.01934826);
   Graph25->SetDirectory(0);
   Graph25->SetStats(0);
   Graph25->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph25);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-0.5,0.05623103);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,-0.1,0.02869105);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.3,0.02957658);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,0.7,0.02773784);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph26 = new TH1F("Graph26","Graph",100,-0.62,0.82);
   Graph26->SetMinimum(0.02488852);
   Graph26->SetMaximum(0.05908035);
   Graph26->SetDirectory(0);
   Graph26->SetStats(0);
   Graph26->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph26);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);
   grae->SetFillStyle(3445);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,-0.5,0);
   grae->SetPointError(0,0,0,0.1479124,0.1180092);
   grae->SetPoint(1,-0.1,0);
   grae->SetPointError(1,0,0,0.07635452,0.06525427);
   grae->SetPoint(2,0.3,0);
   grae->SetPointError(2,0,0,0.07345357,0.07272044);
   grae->SetPoint(3,0.7,0);
   grae->SetPointError(3,0,0,0.1063169,0.06953175);
   grae->Draw("e ");
   canv_cross_eta_2->Modified();
   canv_cross_eta->cd();
   canv_cross_eta->Modified();
   canv_cross_eta->cd();
   canv_cross_eta->SetSelected(canv_cross_eta);
}
