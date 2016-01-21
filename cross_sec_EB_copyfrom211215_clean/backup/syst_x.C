{
//=========Macro generated from canvas: canv_cross_x/
//=========  (Fri Mar 11 01:30:28 2011) by ROOT version5.26/00c
   TCanvas *canv_cross_x = new TCanvas("canv_cross_x", "",1,1,550,876);
   canv_cross_x->SetHighLightColor(2);
   canv_cross_x->Range(0,0,1,1);
   canv_cross_x->SetFillColor(0);
   canv_cross_x->SetBorderMode(0);
   canv_cross_x->SetBorderSize(2);
   canv_cross_x->SetTopMargin(0.04761905);
   canv_cross_x->SetBottomMargin(0.05);
   canv_cross_x->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: canv_cross_x_1
   TPad *canv_cross_x_1 = new TPad("canv_cross_x_1", "_1",0.1,0.4,0.9,0.9);
   canv_cross_x_1->Draw();
   canv_cross_x_1->cd();
   canv_cross_x_1->Range(-4.016043,0.90309,-1.577019,3.845098);
   canv_cross_x_1->SetFillColor(0);
   canv_cross_x_1->SetBorderMode(0);
   canv_cross_x_1->SetBorderSize(2);
   canv_cross_x_1->SetLogx();
   canv_cross_x_1->SetLogy();
   canv_cross_x_1->SetTickx(1);
   canv_cross_x_1->SetTicky(1);
   canv_cross_x_1->SetLeftMargin(0.13);
   canv_cross_x_1->SetRightMargin(0.05);
   canv_cross_x_1->SetTopMargin(0);
   canv_cross_x_1->SetBottomMargin(0);
   canv_cross_x_1->SetFrameBorderMode(0);
   canv_cross_x_1->SetFrameBorderMode(0);
   Double_t xAxis112[5] = {0.0002, 0.001, 0.003, 0.01, 0.02}; 
   
   TH2D *h_window_cross_x = new TH2D("h_window_cross_x","",4, xAxis112,10,8,7000);
   h_window_cross_x->SetStats(0);
   h_window_cross_x->GetXaxis()->SetTitle("x_{Bj}");
   h_window_cross_x->GetXaxis()->CenterTitle(true);
   h_window_cross_x->GetXaxis()->SetNdivisions(507);
   h_window_cross_x->GetXaxis()->SetLabelFont(42);
   h_window_cross_x->GetXaxis()->SetLabelSize(0.05073171);
   h_window_cross_x->GetXaxis()->SetTitleSize(0.06341463);
   h_window_cross_x->GetXaxis()->SetTitleFont(42);
   h_window_cross_x->GetYaxis()->SetTitle("d#sigma/d x_{Bj} (pb)");
   h_window_cross_x->GetYaxis()->CenterTitle(true);
   h_window_cross_x->GetYaxis()->SetNdivisions(507);
   h_window_cross_x->GetYaxis()->SetLabelFont(42);
   h_window_cross_x->GetYaxis()->SetLabelSize(0.0416);
   h_window_cross_x->GetYaxis()->SetTitleSize(0.052);
   h_window_cross_x->GetYaxis()->SetTitleFont(42);
   h_window_cross_x->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(42);
   grae->SetPoint(0,0.0006,6603.177);
   grae->SetPointError(0,0,0,535.5189,576.469);
   grae->SetPoint(1,0.002,3761.659);
   grae->SetPointError(1,0,0,315.783,343.8234);
   grae->SetPoint(2,0.0065,529.5045);
   grae->SetPointError(2,0,0,116.9028,66.83175);
   grae->SetPoint(3,0.015,52.43288);
   grae->SetPointError(3,0,0,11.53267,13.59968);
   
   TH1F *Graph40 = new TH1F("Graph40","Graph",100,0.00054,0.01644);
   Graph40->SetMinimum(36.81019);
   Graph40->SetMaximum(7893.52);
   Graph40->SetDirectory(0);
   Graph40->SetStats(0);
   Graph40->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph40);
   
   grae->Draw("e3 ");
   Double_t xAxis113[5] = {0.0002, 0.001, 0.003, 0.01, 0.02}; 
   
   TH1D *h_cross_section_x = new TH1D("h_cross_section_x","det_cross_x",4, xAxis113);
   h_cross_section_x->SetBinContent(0,102.6147);
   h_cross_section_x->SetBinContent(1,6603.177);
   h_cross_section_x->SetBinContent(2,3761.659);
   h_cross_section_x->SetBinContent(3,529.5045);
   h_cross_section_x->SetBinContent(4,52.43288);
   h_cross_section_x->SetBinContent(5,508.2469);
   h_cross_section_x->SetBinError(0,13.14732);
   h_cross_section_x->SetBinError(1,474.7921);
   h_cross_section_x->SetBinError(2,284.6673);
   h_cross_section_x->SetBinError(3,66.2578);
   h_cross_section_x->SetBinError(4,13.80455);
   h_cross_section_x->SetBinError(5,24.10049);
   h_cross_section_x->SetEntries(22622);
   h_cross_section_x->SetFillColor(41);
   h_cross_section_x->SetMarkerStyle(20);
   h_cross_section_x->SetMarkerSize(0.8);
   h_cross_section_x->Draw("E1 X0 SAME");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(20);
   grae->SetPoint(0,0.0006,6603.177);
   grae->SetPointError(0,0,0,715.6871,671.4575);
   grae->SetPoint(1,0.002,3761.659);
   grae->SetPointError(1,0,0,425.1522,402.5804);
   grae->SetPoint(2,0.0065,529.5045);
   grae->SetPointError(2,0,0,134.3739,93.70268);
   grae->SetPoint(3,0.015,52.43288);
   grae->SetPointError(3,0,0,17.988,19.52258);
   grae->Draw("e ");
   
   TLegend *leg = new TLegend(0.23,0.289,0.63,0.6,NULL,"brNDC");
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
   canv_cross_x_1->Modified();
   canv_cross_x->cd();
  
// ------------>Primitives in pad: canv_cross_x_2
   canv_cross_x_2 = new TPad("canv_cross_x_2", "_2",0.1,0.2,0.9,0.4);
   canv_cross_x_2->Draw();
   canv_cross_x_2->cd();
   canv_cross_x_2->Range(-4.016043,-0.7083333,-1.577019,0.425);
   canv_cross_x_2->SetFillColor(0);
   canv_cross_x_2->SetBorderMode(0);
   canv_cross_x_2->SetBorderSize(2);
   canv_cross_x_2->SetLogx();
   canv_cross_x_2->SetTickx(1);
   canv_cross_x_2->SetTicky(1);
   canv_cross_x_2->SetLeftMargin(0.13);
   canv_cross_x_2->SetRightMargin(0.05);
   canv_cross_x_2->SetTopMargin(0);
   canv_cross_x_2->SetBottomMargin(0.25);
   canv_cross_x_2->SetFrameBorderMode(0);
   canv_cross_x_2->SetFrameBorderMode(0);
   Double_t xAxis114[5] = {0.0002, 0.001, 0.003, 0.01, 0.02}; 
   
   TH2D *h_window_cross_ratio_x = new TH2D("h_window_cross_ratio_x","",4, xAxis114,10,-0.425,0.425);
   h_window_cross_ratio_x->SetStats(0);
   h_window_cross_ratio_x->GetXaxis()->SetTitle("x_{Bj}");
   h_window_cross_ratio_x->GetXaxis()->CenterTitle(true);
   h_window_cross_ratio_x->GetXaxis()->SetNdivisions(507);
   h_window_cross_ratio_x->GetXaxis()->SetLabelFont(42);
   h_window_cross_ratio_x->GetXaxis()->SetLabelSize(0.09756097);
   h_window_cross_ratio_x->GetXaxis()->SetTitleSize(0.1219512);
   h_window_cross_ratio_x->GetXaxis()->SetTickLength(0.07);
   h_window_cross_ratio_x->GetXaxis()->SetTitleOffset(0.8);
   h_window_cross_ratio_x->GetXaxis()->SetTitleFont(42);
   h_window_cross_ratio_x->GetYaxis()->SetTitle("rel. difference");
   h_window_cross_ratio_x->GetYaxis()->CenterTitle(true);
   h_window_cross_ratio_x->GetYaxis()->SetNdivisions(406);
   h_window_cross_ratio_x->GetYaxis()->SetLabelFont(42);
   h_window_cross_ratio_x->GetYaxis()->SetLabelSize(0.08533333);
   h_window_cross_ratio_x->GetYaxis()->SetTitleSize(0.1066667);
   h_window_cross_ratio_x->GetYaxis()->SetTitleOffset(0.5);
   h_window_cross_ratio_x->GetYaxis()->SetTitleFont(42);
   h_window_cross_ratio_x->Draw("");
   
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
   grae->SetPoint(0,0.0006,0);
   grae->SetPointError(0,0,0,0.05484841,0.05229276);
   grae->SetPoint(1,0.002,0);
   grae->SetPointError(1,0,0,0.03259329,0.06063469);
   grae->SetPoint(2,0.0065,0);
   grae->SetPointError(2,0,0,0.1649768,0.04545254);
   grae->SetPoint(3,0.015,0);
   grae->SetPointError(3,0,0,0.1529074,0.2482898);
   
   TH1F *Graph41 = new TH1F("Graph41","Graph",100,0.00054,0.01644);
   Graph41->SetMinimum(-0.2063035);
   Graph41->SetMaximum(0.2896164);
   Graph41->SetDirectory(0);
   Graph41->SetStats(0);
   Graph41->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph41);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,0.0006,-0.05484841);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,0.002,-0.03259329);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.0065,-0.1649768);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,0.015,-0.1529074);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph42 = new TH1F("Graph42","Graph",100,0.00054,0.01644);
   Graph42->SetMinimum(-0.1782152);
   Graph42->SetMaximum(-0.01935494);
   Graph42->SetDirectory(0);
   Graph42->SetStats(0);
   Graph42->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph42);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,0.0006,0.05229276);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,0.002,0.06063469);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.0065,0.04545254);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,0.015,0.2482898);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph43 = new TH1F("Graph43","Graph",100,0.00054,0.01644);
   Graph43->SetMinimum(0.02516881);
   Graph43->SetMaximum(0.2685735);
   Graph43->SetDirectory(0);
   Graph43->SetStats(0);
   Graph43->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph43);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3445);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,0.0006,0);
   grae->SetPointError(0,0,0,0.01027921,0.01099658);
   grae->SetPoint(1,0.002,0);
   grae->SetPointError(1,0,0,0.02603742,0.01578849);
   grae->SetPoint(2,0.0065,0);
   grae->SetPointError(2,0,0,0.03470772,0.03505473);
   grae->SetPoint(3,0.015,0);
   grae->SetPointError(3,0,0,0.08513089,0.03171834);
   
   TH1F *Graph44 = new TH1F("Graph44","Graph",100,0.00054,0.01644);
   Graph44->SetMinimum(-0.09714945);
   Graph44->SetMaximum(0.0470733);
   Graph44->SetDirectory(0);
   Graph44->SetStats(0);
   Graph44->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph44);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,0.0006,-0.01027921);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,0.002,-0.02603742);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.0065,-0.03470772);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,0.015,-0.08513089);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph45 = new TH1F("Graph45","Graph",100,0.00054,0.01644);
   Graph45->SetMinimum(-0.09261605);
   Graph45->SetMaximum(-0.002794042);
   Graph45->SetDirectory(0);
   Graph45->SetStats(0);
   Graph45->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph45);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,0.0006,0.01099658);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,0.002,0.01578849);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.0065,0.03505473);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,0.015,0.03171834);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph46 = new TH1F("Graph46","Graph",100,0.00054,0.01644);
   Graph46->SetMinimum(0.008590768);
   Graph46->SetMaximum(0.03746055);
   Graph46->SetDirectory(0);
   Graph46->SetStats(0);
   Graph46->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph46);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3425);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,0.0006,0);
   grae->SetPointError(0,0,0,0.02629269,0.0354864);
   grae->SetPoint(1,0.002,0);
   grae->SetPointError(1,0,0,0.01890182,0.0661671);
   grae->SetPoint(2,0.0065,0);
   grae->SetPointError(2,0,0,0.05430455,0.1013344);
   grae->SetPoint(3,0.015,0);
   grae->SetPointError(3,0,0,0.1145953,0.01129444);
   
   TH1F *Graph47 = new TH1F("Graph47","Graph",100,0.00054,0.01644);
   Graph47->SetMinimum(-0.1361882);
   Graph47->SetMaximum(0.1229274);
   Graph47->SetDirectory(0);
   Graph47->SetStats(0);
   Graph47->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph47);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,0.0006,-0.02629269);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,0.002,-0.01890182);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.0065,-0.05430455);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,0.015,-0.1145953);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph48 = new TH1F("Graph48","Graph",100,0.00054,0.01644);
   Graph48->SetMinimum(-0.1241646);
   Graph48->SetMaximum(-0.009332473);
   Graph48->SetDirectory(0);
   Graph48->SetStats(0);
   Graph48->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph48);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,0.0006,0.0354864);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,0.002,0.0661671);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.0065,0.1013344);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,0.015,0.01129444);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph49 = new TH1F("Graph49","Graph",100,0.00054,0.01644);
   Graph49->SetMinimum(0.002290437);
   Graph49->SetMaximum(0.1103384);
   Graph49->SetDirectory(0);
   Graph49->SetStats(0);
   Graph49->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph49);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#000000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(3452);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,0.0006,0);
   grae->SetPointError(0,0,0,0.05264909,0.05921872);
   grae->SetPoint(1,0.002,0);
   grae->SetPointError(1,0,0,0.07035399,0.007099813);
   grae->SetPoint(2,0.0065,0);
   grae->SetPointError(2,0,0,0.1318023,0.04865138);
   grae->SetPoint(3,0.015,0);
   grae->SetPointError(3,0,0,0.06795939,0.06703013);
   
   TH1F *Graph50 = new TH1F("Graph50","Graph",100,0.00054,0.01644);
   Graph50->SetMinimum(-0.1516855);
   Graph50->SetMaximum(0.08691337);
   Graph50->SetDirectory(0);
   Graph50->SetStats(0);
   Graph50->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph50);
   
   grae->Draw("e3 ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,0.0006,-0.05264909);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,0.002,-0.07035399);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.0065,-0.1318023);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,0.015,-0.06795939);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph51 = new TH1F("Graph51","Graph",100,0.00054,0.01644);
   Graph51->SetMinimum(-0.1397176);
   Graph51->SetMaximum(-0.04473377);
   Graph51->SetDirectory(0);
   Graph51->SetStats(0);
   Graph51->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph51);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000000");
   grae->SetLineColor(ci);
   grae->SetPoint(0,0.0006,0.05921872);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,0.002,0.007099813);
   grae->SetPointError(1,0,0,0,0);
   grae->SetPoint(2,0.0065,0.04865138);
   grae->SetPointError(2,0,0,0,0);
   grae->SetPoint(3,0.015,0.06703013);
   grae->SetPointError(3,0,0,0,0);
   
   TH1F *Graph52 = new TH1F("Graph52","Graph",100,0.00054,0.01644);
   Graph52->SetMinimum(0.001106781);
   Graph52->SetMaximum(0.07302316);
   Graph52->SetDirectory(0);
   Graph52->SetStats(0);
   Graph52->GetXaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph52);
   
   grae->Draw("l ");
   
   grae = new TGraphAsymmErrors(4);
   grae->SetName("Graph");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);
   grae->SetFillStyle(3445);

   ci = TColor::GetColor("#000000");
   grae->SetMarkerColor(ci);
   grae->SetPoint(0,0.0006,0);
   grae->SetPointError(0,0,0,0.0811002,0.08730177);
   grae->SetPoint(1,0.002,0);
   grae->SetPointError(1,0,0,0.0839478,0.09140205);
   grae->SetPoint(2,0.0065,0);
   grae->SetPointError(2,0,0,0.2207777,0.1262156);
   grae->SetPoint(3,0.015,0);
   grae->SetPointError(3,0,0,0.2199511,0.2593732);
   grae->Draw("e ");
   canv_cross_x_2->Modified();
   canv_cross_x->cd();
   canv_cross_x->Modified();
   canv_cross_x->cd();
   canv_cross_x->SetSelected(canv_cross_x);
}
