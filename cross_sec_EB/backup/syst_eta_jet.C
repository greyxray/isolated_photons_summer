{
//=========Macro generated from canvas: canv_cross_eta_jet/
//=========  (Fri Mar 11 01:30:28 2011) by ROOT version5.26/00c
   TCanvas *canv_cross_eta_jet = new TCanvas("canv_cross_eta_jet", "",1,1,550,876);
   canv_cross_eta_jet->SetHighLightColor(2);
   canv_cross_eta_jet->Range(0,0,1,1);
   canv_cross_eta_jet->SetFillColor(0);
   canv_cross_eta_jet->SetBorderMode(0);
   canv_cross_eta_jet->SetBorderSize(2);
   canv_cross_eta_jet->SetTopMargin(0.04761905);
   canv_cross_eta_jet->SetBottomMargin(0.05);
   canv_cross_eta_jet->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_eta_jet_1
   TPad *canv_cross_eta_jet_1 = new TPad("canv_cross_eta_jet_1", "_1",0.1,0.4,0.9,0.9);
   canv_cross_eta_jet_1->Draw();
   canv_cross_eta_jet_1->cd();
   canv_cross_eta_jet_1->Range(-2.023171,0.05,2.00122,4);
   canv_cross_eta_jet_1->SetFillColor(0);
   canv_cross_eta_jet_1->SetBorderMode(0);
   canv_cross_eta_jet_1->SetBorderSize(2);
   canv_cross_eta_jet_1->SetTickx(1);
   canv_cross_eta_jet_1->SetTicky(1);
   canv_cross_eta_jet_1->SetLeftMargin(0.13);
   canv_cross_eta_jet_1->SetRightMargin(0.05);
   canv_cross_eta_jet_1->SetTopMargin(0);
   canv_cross_eta_jet_1->SetBottomMargin(0);
   canv_cross_eta_jet_1->SetFrameBorderMode(0);
   canv_cross_eta_jet_1->SetFrameBorderMode(0);
   Double_t xAxis118[5] = {-1.5, -0.7, 0.1, 0.9, 1.8}; 
   
   TH2D *h_window_cross_eta_jet = new TH2D("h_window_cross_eta_jet","",4, xAxis118,10,0.05,4);
   h_window_cross_eta_jet->SetStats(0);
   h_window_cross_eta_jet->GetXaxis()->SetTitle("#eta_{jet}");
   h_window_cross_eta_jet->GetXaxis()->CenterTitle(true);
   h_window_cross_eta_jet->GetXaxis()->SetNdivisions(507);
   h_window_cross_eta_jet->GetXaxis()->SetLabelFont(42);
   h_window_cross_eta_jet->GetXaxis()->SetLabelSize(0.05073171);
   h_window_cross_eta_jet->GetXaxis()->SetTitleSize(0.06341463);
   h_window_cross_eta_jet->GetXaxis()->SetTitleFont(42);
   h_window_cross_eta_jet->GetYaxis()->SetTitle("d#sigma/d #eta_{jet} (pb)");
   h_window_cross_eta_jet->GetYaxis()->CenterTitle(true);
   h_window_cross_eta_jet->GetYaxis()->SetNdivisions(507);
   h_window_cross_eta_jet->GetYaxis()->SetLabelFont(42);
   h_window_cross_eta_jet->GetYaxis()->SetLabelSize(0.0416);
   h_window_cross_eta_jet->GetYaxis()->SetTitleSize(0.052);
   h_window_cross_eta_jet->GetYaxis()->SetTitleFont(42);
   h_window_cross_eta_jet->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(42);
   grae->SetPoint(0,-1.1,nan);
   grae->SetPointError(0,0,0,nan,nan);
   grae->SetPoint(1,-0.3,nan);
   grae->SetPointError(1,0,0,nan,nan);
   grae->SetPoint(2,0.5,nan);
   grae->SetPointError(2,0,0,nan,nan);
   grae->SetPoint(3,1.35,nan);
   grae->SetPointError(3,0,0,nan,nan);
   
   TH1F *Graph66 = new TH1F("Graph66","Graph",100,-1.345,1.595);
   Graph66->SetMinimum(nan);
   Graph66->SetMaximum(nan);
   Graph66->SetDirectory(0);
   Graph66->SetStats(0);
   Graph66->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph66);
   
   grae->Draw("e3 ");
   Double_t xAxis119[5] = {-1.5, -0.7, 0.1, 0.9, 1.8}; 
   
   TH1D *h_cross_section_eta_jet = new TH1D("h_cross_section_eta_jet","det_cross_eta_jet",4, xAxis119);
   h_cross_section_eta_jet->SetBinContent(0,23859.31);
   h_cross_section_eta_jet->SetBinContent(1,nan);
   h_cross_section_eta_jet->SetBinContent(2,nan);
   h_cross_section_eta_jet->SetBinContent(3,nan);
   h_cross_section_eta_jet->SetBinContent(4,nan);
   h_cross_section_eta_jet->SetBinError(0,154.4646);
   h_cross_section_eta_jet->SetBinError(1,nan);
   h_cross_section_eta_jet->SetBinError(2,nan);
   h_cross_section_eta_jet->SetBinError(3,nan);
   h_cross_section_eta_jet->SetBinError(4,nan);
   h_cross_section_eta_jet->SetEntries(22622);
   h_cross_section_eta_jet->SetFillColor(41);
   h_cross_section_eta_jet->SetMarkerStyle(20);
   h_cross_section_eta_jet->SetMarkerSize(0.8);
   h_cross_section_eta_jet->Draw("E1 X0 SAME");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(20);
   grae->SetPoint(0,-1.1,nan);
   grae->SetPointError(0,0,0,nan,nan);
   grae->SetPoint(1,-0.3,nan);
   grae->SetPointError(1,0,0,nan,nan);
   grae->SetPoint(2,0.5,nan);
   grae->SetPointError(2,0,0,nan,nan);
   grae->SetPoint(3,1.35,nan);
   grae->SetPointError(3,0,0,nan,nan);
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
   canv_cross_eta_jet_1->Modified();
   canv_cross_eta_jet->cd();
  
// ------------>Primitives in pad: canv_cross_eta_jet_2
   canv_cross_eta_jet_2 = new TPad("canv_cross_eta_jet_2", "_2",0.1,0.2,0.9,0.4);
   canv_cross_eta_jet_2->Draw();
   canv_cross_eta_jet_2->cd();
   canv_cross_eta_jet_2->Range(-2.023171,-0.7083333,2.00122,0.425);
   canv_cross_eta_jet_2->SetFillColor(0);
   canv_cross_eta_jet_2->SetBorderMode(0);
   canv_cross_eta_jet_2->SetBorderSize(2);
   canv_cross_eta_jet_2->SetTickx(1);
   canv_cross_eta_jet_2->SetTicky(1);
   canv_cross_eta_jet_2->SetLeftMargin(0.13);
   canv_cross_eta_jet_2->SetRightMargin(0.05);
   canv_cross_eta_jet_2->SetTopMargin(0);
   canv_cross_eta_jet_2->SetBottomMargin(0.25);
   canv_cross_eta_jet_2->SetFrameBorderMode(0);
   canv_cross_eta_jet_2->SetFrameBorderMode(0);
   Double_t xAxis120[5] = {-1.5, -0.7, 0.1, 0.9, 1.8}; 
   
   TH2D *h_window_cross_ratio_eta_jet = new TH2D("h_window_cross_ratio_eta_jet","",4, xAxis120,10,-0.425,0.425);
   h_window_cross_ratio_eta_jet->SetStats(0);
   h_window_cross_ratio_eta_jet->GetXaxis()->SetTitle("#eta_{jet}");
   h_window_cross_ratio_eta_jet->GetXaxis()->CenterTitle(true);
   h_window_cross_ratio_eta_jet->GetXaxis()->SetNdivisions(507);
   h_window_cross_ratio_eta_jet->GetXaxis()->SetLabelFont(42);
   h_window_cross_ratio_eta_jet->GetXaxis()->SetLabelSize(0.09756097);
   h_window_cross_ratio_eta_jet->GetXaxis()->SetTitleSize(0.1219512);
   h_window_cross_ratio_eta_jet->GetXaxis()->SetTickLength(0.07);
   h_window_cross_ratio_eta_jet->GetXaxis()->SetTitleOffset(0.8);
   h_window_cross_ratio_eta_jet->GetXaxis()->SetTitleFont(42);
   h_window_cross_ratio_eta_jet->GetYaxis()->SetTitle("rel. difference");
   h_window_cross_ratio_eta_jet->GetYaxis()->CenterTitle(true);
   h_window_cross_ratio_eta_jet->GetYaxis()->SetNdivisions(406);
   h_window_cross_ratio_eta_jet->GetYaxis()->SetLabelFont(42);
   h_window_cross_ratio_eta_jet->GetYaxis()->SetLabelSize(0.08533333);
   h_window_cross_ratio_eta_jet->GetYaxis()->SetTitleSize(0.1066667);
   h_window_cross_ratio_eta_jet->GetYaxis()->SetTitleOffset(0.5);
   h_window_cross_ratio_eta_jet->GetYaxis()->SetTitleFont(42);
   h_window_cross_ratio_eta_jet->Draw("");
   
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
   grae->SetPoint(0,-1.1,0);
   grae->SetPointError(0,0,0,0.09954002,0.07718371);
   grae->SetPoint(1,-0.3,0);
   grae->SetPointError(1,0,0,0.05473381,0.04471588);
   grae->SetPoint(2,0.5,0);
   grae->SetPointError(2,0,0,0.03714176,0.04632043);
   grae->SetPoint(3,1.35,0);
   grae->SetPointError(3,0,0,0.07347376,0.02246628);
   
   TH1F *Graph67 = new TH1F("Graph67","Graph",100,-1.345,1.595);
   Graph67->SetMinimum(-0.1172124);
   Graph67->SetMaximum(0.09485608);
   Graph67->SetDirectory(0);
   Graph67->SetStats(0);
   Graph67->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph67);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-1.1,-0.09954002);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,-0.3,-0.05473381);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.5,-0.03714176);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,1.35,-0.07347376);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph68 = new TH1F("Graph68","Graph",100,-1.345,1.595);
   Graph68->SetMinimum(-0.1057798);
   Graph68->SetMaximum(-0.03090193);
   Graph68->SetDirectory(0);
   Graph68->SetStats(0);
   Graph68->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph68);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-1.1,0.07718371);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,-0.3,0.04471588);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.5,0.04632043);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,1.35,0.02246628);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph69 = new TH1F("Graph69","Graph",100,-1.345,1.595);
   Graph69->SetMinimum(0.01699454);
   Graph69->SetMaximum(0.08265545);
   Graph69->SetDirectory(0);
   Graph69->SetStats(0);
   Graph69->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph69);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3445);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,-1.1,0);
   grae->SetPointError(0,0,0,0.025818,0.02536039);
   grae->SetPoint(1,-0.3,0);
   grae->SetPointError(1,0,0,0.03525772,0.01400966);
   grae->SetPoint(2,0.5,0);
   grae->SetPointError(2,0,0,0.003045055,0.008037759);
   grae->SetPoint(3,1.35,0);
   grae->SetPointError(3,0,0,0.01472498,0.002032266);
   
   TH1F *Graph70 = new TH1F("Graph70","Graph",100,-1.345,1.595);
   Graph70->SetMinimum(-0.04131953);
   Graph70->SetMaximum(0.03142221);
   Graph70->SetDirectory(0);
   Graph70->SetStats(0);
   Graph70->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph70);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-1.1,-0.025818);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,-0.3,-0.03525772);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.5,-0.003045055);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,1.35,-0.01472498);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph71 = new TH1F("Graph71","Graph",100,-1.345,1.595);
   Graph71->SetMinimum(-0.03847898);
   Graph71->SetMaximum(0.0001762112);
   Graph71->SetDirectory(0);
   Graph71->SetStats(0);
   Graph71->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph71);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-1.1,0.02536039);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,-0.3,0.01400966);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.5,0.008037759);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,1.35,0.002032266);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph72 = new TH1F("Graph72","Graph",100,-1.345,1.595);
   Graph72->SetMinimum(0);
   Graph72->SetMaximum(0.02769321);
   Graph72->SetDirectory(0);
   Graph72->SetStats(0);
   Graph72->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph72);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3425);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,-1.1,0);
   grae->SetPointError(0,0,0,0.0801617,0.06452722);
   grae->SetPoint(1,-0.3,0);
   grae->SetPointError(1,0,0,0.03160764,0.03520174);
   grae->SetPoint(2,0.5,0);
   grae->SetPointError(2,0,0,0.005342687,0.04693932);
   grae->SetPoint(3,1.35,0);
   grae->SetPointError(3,0,0,0.01363925,0.05963566);
   
   TH1F *Graph73 = new TH1F("Graph73","Graph",100,-1.345,1.595);
   Graph73->SetMinimum(-0.0946306);
   Graph73->SetMaximum(0.07899611);
   Graph73->SetDirectory(0);
   Graph73->SetStats(0);
   Graph73->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph73);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-1.1,-0.0801617);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,-0.3,-0.03160764);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.5,-0.005342687);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,1.35,-0.01363925);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph74 = new TH1F("Graph74","Graph",100,-1.345,1.595);
   Graph74->SetMinimum(-0.0876436);
   Graph74->SetMaximum(0.002139214);
   Graph74->SetDirectory(0);
   Graph74->SetStats(0);
   Graph74->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph74);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-1.1,0.06452722);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,-0.3,0.03520174);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.5,0.04693932);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,1.35,0.05963566);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph75 = new TH1F("Graph75","Graph",100,-1.345,1.595);
   Graph75->SetMinimum(0.03226919);
   Graph75->SetMaximum(0.06745977);
   Graph75->SetDirectory(0);
   Graph75->SetStats(0);
   Graph75->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph75);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3452);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,-1.1,0);
   grae->SetPointError(0,0,0,0.0698383,0.05623103);
   grae->SetPoint(1,-0.3,0);
   grae->SetPointError(1,0,0,0.02433257,0.02869105);
   grae->SetPoint(2,0.5,0);
   grae->SetPointError(2,0,0,0.06307218,0.02957658);
   grae->SetPoint(3,1.35,0);
   grae->SetPointError(3,0,0,0.07417571,0.02773784);
   
   TH1F *Graph76 = new TH1F("Graph76","Graph",100,-1.345,1.595);
   Graph76->SetMinimum(-0.08721638);
   Graph76->SetMaximum(0.06927171);
   Graph76->SetDirectory(0);
   Graph76->SetStats(0);
   Graph76->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph76);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-1.1,-0.0698383);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,-0.3,-0.02433257);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.5,-0.06307218);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,1.35,-0.07417571);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph77 = new TH1F("Graph77","Graph",100,-1.345,1.595);
   Graph77->SetMinimum(-0.07916002);
   Graph77->SetMaximum(-0.01934826);
   Graph77->SetDirectory(0);
   Graph77->SetStats(0);
   Graph77->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph77);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,-1.1,0.05623103);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,-0.3,0.02869105);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.5,0.02957658);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,1.35,0.02773784);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph78 = new TH1F("Graph78","Graph",100,-1.345,1.595);
   Graph78->SetMinimum(0.02488852);
   Graph78->SetMaximum(0.05908035);
   Graph78->SetDirectory(0);
   Graph78->SetStats(0);
   Graph78->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph78);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);
   grae->SetFillStyle(3445);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,-1.1,0);
   grae->SetPointError(0,0,0,0.1479124,0.1180092);
   grae->SetPoint(1,-0.3,0);
   grae->SetPointError(1,0,0,0.07635452,0.06525427);
   grae->SetPoint(2,0.5,0);
   grae->SetPointError(2,0,0,0.07345357,0.07272044);
   grae->SetPoint(3,1.35,0);
   grae->SetPointError(3,0,0,0.1063169,0.06953175);
   grae->Draw("e ");
   canv_cross_eta_jet_2->Modified();
   canv_cross_eta_jet->cd();
   canv_cross_eta_jet->Modified();
   canv_cross_eta_jet->cd();
   canv_cross_eta_jet->SetSelected(canv_cross_eta_jet);
}
