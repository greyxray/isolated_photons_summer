{
//=========Macro generated from canvas: cc/cc
//=========  (Fri Oct 29 05:43:44 2010) by ROOT version5.26/00c
   TCanvas *cc = new TCanvas("cc", "cc",0,0,800,600);
   cc->SetHighLightColor(2);
   cc->Range(0,0,1,1);
   cc->SetFillColor(0);
   cc->SetBorderMode(0);
   cc->SetBorderSize(2);
   cc->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: cc_1
   TPad *cc_1 = new TPad("cc_1", "cc_1",0.01,0.01,0.99,0.99);
   cc_1->Draw();
   cc_1->cd();
   cc_1->Range(-82.66667,-2.666667,330.6667,10.66667);
   cc_1->SetFillColor(0);
   cc_1->SetBorderMode(0);
   cc_1->SetBorderSize(2);
   cc_1->SetLeftMargin(0.2);
   cc_1->SetRightMargin(0.05);
   cc_1->SetTopMargin(0.05);
   cc_1->SetBottomMargin(0.2);
   cc_1->SetFrameBorderMode(0);
   cc_1->SetFrameBorderMode(0);
   
   TH2D *h_window_binning = new TH2D("h_window_binning","",10,0,310,10,0,10);
   h_window_binning->SetStats(0);
   h_window_binning->GetXaxis()->SetTitle("No. of bins");
   h_window_binning->GetXaxis()->CenterTitle(true);
   h_window_binning->GetXaxis()->SetNdivisions(511);
   h_window_binning->GetXaxis()->SetLabelFont(42);
   h_window_binning->GetXaxis()->SetLabelSize(0.05333333);
   h_window_binning->GetXaxis()->SetTitleSize(0.05333333);
   h_window_binning->GetXaxis()->SetTitleOffset(1.2);
   h_window_binning->GetXaxis()->SetTitleFont(42);
   h_window_binning->GetYaxis()->SetTitle("#chi^{2}");
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
   gre->SetPoint(0,300,1.16125);
   gre->SetPointError(0,0,0);
   gre->SetPoint(1,150,1.506374);
   gre->SetPointError(1,0,0);
   gre->SetPoint(2,75,2.009979);
   gre->SetPointError(2,0,0);
   gre->SetPoint(3,60,2.25003);
   gre->SetPointError(3,0,0);
   gre->SetPoint(4,50,2.576186);
   gre->SetPointError(4,0,0);
   gre->SetPoint(5,30,3.02493);
   gre->SetPointError(5,0,0);
   gre->SetPoint(6,20,4.418091);
   gre->SetPointError(6,0,0);
   gre->SetPoint(7,12,4.28739);
   gre->SetPointError(7,0,0);
   gre->SetPoint(8,10,4.75344);
   gre->SetPointError(8,0,0);
   
   TH1F *Graph1 = new TH1F("Graph1","Graph",100,0,329);
   Graph1->SetMinimum(0.8020309);
   Graph1->SetMaximum(5.112659);
   Graph1->SetDirectory(0);
   Graph1->SetStats(0);
   Graph1->GetXaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph1);
   
   gre->Draw(" lp");
   
   gre = new TGraphErrors(9);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#000000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.7);
   gre->SetPoint(0,300,1.77764);
   gre->SetPointError(0,0,0);
   gre->SetPoint(1,150,2.291524);
   gre->SetPointError(1,0,0);
   gre->SetPoint(2,75,3.10134);
   gre->SetPointError(2,0,0);
   gre->SetPoint(3,60,3.373549);
   gre->SetPointError(3,0,0);
   gre->SetPoint(4,50,3.986252);
   gre->SetPointError(4,0,0);
   gre->SetPoint(5,30,4.548292);
   gre->SetPointError(5,0,0);
   gre->SetPoint(6,20,6.712191);
   gre->SetPointError(6,0,0);
   gre->SetPoint(7,12,6.699185);
   gre->SetPointError(7,0,0);
   gre->SetPoint(8,10,7.429155);
   gre->SetPointError(8,0,0);
   
   TH1F *Graph2 = new TH1F("Graph2","Graph",100,0,329);
   Graph2->SetMinimum(1.212489);
   Graph2->SetMaximum(7.994306);
   Graph2->SetDirectory(0);
   Graph2->SetStats(0);
   Graph2->GetXaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph2);
   
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
   cc_1->Modified();
   cc->cd();
   cc->Modified();
   cc->cd();
   cc->SetSelected(cc);
}
