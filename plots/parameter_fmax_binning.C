{
//=========Macro generated from canvas: cc1/cc1
//=========  (Fri Oct 29 05:41:24 2010) by ROOT version5.26/00c
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
   cc1_1->Range(-56,-0.16,224,0.64);
   cc1_1->SetFillColor(0);
   cc1_1->SetBorderMode(0);
   cc1_1->SetBorderSize(2);
   cc1_1->SetLeftMargin(0.2);
   cc1_1->SetRightMargin(0.05);
   cc1_1->SetTopMargin(0.05);
   cc1_1->SetBottomMargin(0.2);
   cc1_1->SetFrameBorderMode(0);
   cc1_1->SetFrameBorderMode(0);
   
   TH2D *h_window_binning = new TH2D("h_window_binning","",10,0,210,10,0,6);
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
   h_window_binning->GetYaxis()->SetRange(1,1);
   h_window_binning->GetYaxis()->CenterTitle(true);
   h_window_binning->GetYaxis()->SetNdivisions(507);
   h_window_binning->GetYaxis()->SetLabelFont(42);
   h_window_binning->GetYaxis()->SetLabelSize(0.05333333);
   h_window_binning->GetYaxis()->SetTitleOffset(1.5);
   h_window_binning->GetYaxis()->SetTitleFont(42);
   h_window_binning->Draw("");
   
   TGraphErrors *gre = new TGraphErrors(9);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.7);
   gre->SetPoint(0,200,0.3315805);
   gre->SetPointError(0,0,0.2047875);
   gre->SetPoint(1,100,0.3285581);
   gre->SetPointError(1,0,0.1457319);
   gre->SetPoint(2,50,0.3255292);
   gre->SetPointError(2,0,0.1023048);
   gre->SetPoint(3,40,0.3282557);
   gre->SetPointError(3,0,0.09275639);
   gre->SetPoint(4,25,0.3258319);
   gre->SetPointError(4,0,0.0715643);
   gre->SetPoint(5,20,0.3218691);
   gre->SetPointError(5,0,0.06620634);
   gre->SetPoint(6,10,0.3159923);
   gre->SetPointError(6,0,0.04717772);
   gre->SetPoint(7,8,0.3162587);
   gre->SetPointError(7,0,0.04010695);
   gre->SetPoint(8,5,0.3147319);
   gre->SetPointError(8,0,0.03200396);
   
   TH1F *Graph3 = new TH1F("Graph3","Graph",100,0,219.5);
   Graph3->SetMinimum(0.08583556);
   Graph3->SetMaximum(0.5773255);
   Graph3->SetDirectory(0);
   Graph3->SetStats(0);
   Graph3->GetXaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph3);
   
   gre->Draw(" lp");
   
   gre = new TGraphErrors(9);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.7);
   gre->SetPoint(0,200,0.3536812);
   gre->SetPointError(0,0,0.1651273);
   gre->SetPoint(1,100,0.338424);
   gre->SetPointError(1,0,0.1195571);
   gre->SetPoint(2,50,0.3284156);
   gre->SetPointError(2,0,0.08473719);
   gre->SetPoint(3,40,0.3323218);
   gre->SetPointError(3,0,0.07657201);
   gre->SetPoint(4,25,0.3275697);
   gre->SetPointError(4,0,0.0594083);
   gre->SetPoint(5,20,0.3241187);
   gre->SetPointError(5,0,0.05466966);
   gre->SetPoint(6,10,0.3163367);
   gre->SetPointError(6,0,0.0388582);
   gre->SetPoint(7,8,0.3158308);
   gre->SetPointError(7,0,0.0331787);
   gre->SetPoint(8,5,0.3148429);
   gre->SetPointError(8,0,0.02614382);
   
   TH1F *Graph4 = new TH1F("Graph4","Graph",100,0,219.5);
   Graph4->SetMinimum(0.1555285);
   Graph4->SetMaximum(0.5518339);
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
   TLegendEntry *entry=leg->AddEntry("Graph","Barlow-Beeston fit","lp");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.7);
   entry=leg->AddEntry("Graph","Gauss approach","lp");

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
