{
//=========Macro generated from canvas: cc1/cc1
//=========  (Fri Oct 29 05:43:44 2010) by ROOT version5.26/00c
   TCanvas *cc1 = new TCanvas("cc1", "cc1",0,0,800,600);
   cc1->SetHighLightColor(2);
   cc1->Range(0,0,1,1);
   cc1->SetFillColor(0);
   cc1->SetBorderMode(0);
   cc1->SetBorderSize(2);
   cc1->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: cc1_1
   TPad *cc1_1 = new TPad("cc1_1", "cc1_1",0.01,0.01,0.99,0.99);
   cc1_1->Draw();
   cc1_1->cd();
   cc1_1->Range(-82.66667,-0.5333333,330.6667,2.133333);
   cc1_1->SetFillColor(0);
   cc1_1->SetBorderMode(0);
   cc1_1->SetBorderSize(2);
   cc1_1->SetLeftMargin(0.2);
   cc1_1->SetRightMargin(0.05);
   cc1_1->SetTopMargin(0.05);
   cc1_1->SetBottomMargin(0.2);
   cc1_1->SetFrameBorderMode(0);
   cc1_1->SetFrameBorderMode(0);
   
   TH2D *h_window_binning = new TH2D("h_window_binning","",10,0,310,10,0,3.5);
   h_window_binning->SetStats(0);
   h_window_binning->GetXaxis()->SetTitle("No. of bins");
   h_window_binning->GetXaxis()->CenterTitle(true);
   h_window_binning->GetXaxis()->SetNdivisions(511);
   h_window_binning->GetXaxis()->SetLabelFont(42);
   h_window_binning->GetXaxis()->SetLabelSize(0.05333333);
   h_window_binning->GetXaxis()->SetTitleSize(0.05333333);
   h_window_binning->GetXaxis()->SetTitleOffset(1.2);
   h_window_binning->GetXaxis()->SetTitleFont(42);
   h_window_binning->GetYaxis()->SetTitle("fit parameter");
   h_window_binning->GetYaxis()->SetRange(1,2);
   h_window_binning->GetYaxis()->CenterTitle(true);
   h_window_binning->GetYaxis()->SetNdivisions(507);
   h_window_binning->GetYaxis()->SetLabelFont(42);
   h_window_binning->GetYaxis()->SetLabelSize(0.05333333);
   h_window_binning->GetYaxis()->SetTitleOffset(1.5);
   h_window_binning->GetYaxis()->SetTitleFont(42);
   h_window_binning->Draw("");
   
TGraphErrors*   gre1 = new TGraphErrors(9);
   gre1->SetName("Graph");
   gre1->SetTitle("Graph");
   gre1->SetFillColor(1);

//   gre1->SetLineColor(kBlue);
   gre1->SetMarkerStyle(20);
   gre1->SetMarkerSize(0.7);
   gre1->SetPoint(0,200,0.3536812);
   gre1->SetPointError(0,0,0.1651273);
   gre1->SetPoint(1,100,0.338424);
   gre1->SetPointError(1,0,0.1195571);
   gre1->SetPoint(2,50,0.3284156);
   gre1->SetPointError(2,0,0.08473719);
   gre1->SetPoint(3,40,0.3323218);
   gre1->SetPointError(3,0,0.07657201);
   gre1->SetPoint(4,25,0.3275697);
   gre1->SetPointError(4,0,0.0594083);
   gre1->SetPoint(5,20,0.3241187);
   gre1->SetPointError(5,0,0.05466966);
   gre1->SetPoint(6,10,0.3163367);
   gre1->SetPointError(6,0,0.0388582);
   gre1->SetPoint(7,8,0.3158308);
   gre1->SetPointError(7,0,0.0331787);
   gre1->SetPoint(8,5,0.3148429);
   gre1->SetPointError(8,0,0.02614382);

   
   TH1F *Graph3 = new TH1F("Graph3","Graph",100,0,329);
   Graph3->SetMinimum(0.08862989);
   Graph3->SetMaximum(0.6643829);
   Graph3->SetDirectory(0);
   Graph3->SetStats(0);
   Graph3->GetXaxis()->SetTitleFont(42);
   gre1->SetHistogram(Graph3);
   
   gre1->Draw(" lp");
   
   gre = new TGraphErrors(9);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.7);
gre->SetLineColor(kBlue);
gre->SetMarkerColor(kBlue);
   gre->SetPoint(0,300,0.4098651);
   gre->SetPointError(0,0,0.1927064);
   gre->SetPoint(1,150,0.394356);
   gre->SetPointError(1,0,0.1400161);
   gre->SetPoint(2,75,0.374883);
   gre->SetPointError(2,0,0.1003657);
   gre->SetPoint(3,60,0.3771329);
   gre->SetPointError(3,0,0.09080546);
   gre->SetPoint(4,50,0.3618999);
   gre->SetPointError(4,0,0.08144527);
   gre->SetPoint(5,30,0.3737342);
   gre->SetPointError(5,0,0.06388273);
   gre->SetPoint(6,20,0.3482395);
   gre->SetPointError(6,0,0.05152173);
   gre->SetPoint(7,12,0.3543259);
   gre->SetPointError(7,0,0.03957025);
   gre->SetPoint(8,10,0.3505388);
   gre->SetPointError(8,0,0.03587908);
   
   TH1F *Graph4 = new TH1F("Graph4","Graph",100,0,329);
   Graph4->SetMinimum(0.1786174);
   Graph4->SetMaximum(0.6411128);
   Graph4->SetDirectory(0);
   Graph4->SetStats(0);
   Graph4->GetXaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph4);
   
   gre->Draw(" lp");
   
   TLegend *leg = new TLegend(0.4,0.75,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry(gre1,"f_{max} fit","lp");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.7);
   entry=leg->AddEntry(gre,"#delta z fit","lp");

   ci = TColor::GetColor("#000000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.7);
   leg->Draw();
   cc1_1->Modified();
   cc1->cd();
   cc1->Modified();
   cc1->cd();
   cc1->SetSelected(cc1);
}
