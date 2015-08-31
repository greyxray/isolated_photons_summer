{
//=========Macro generated from canvas: cc/cc
//=========  (Fri Oct 29 05:41:24 2010) by ROOT version5.26/00c
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
   cc_1->Range(-56,-1.6,224,6.4);
   cc_1->SetFillColor(0);
   cc_1->SetBorderMode(0);
   cc_1->SetBorderSize(2);
   cc_1->SetLeftMargin(0.2);
   cc_1->SetRightMargin(0.05);
   cc_1->SetTopMargin(0.05);
   cc_1->SetBottomMargin(0.2);
   cc_1->SetFrameBorderMode(0);
   cc_1->SetFrameBorderMode(0);
   
   TH2D *h_window_binning = new TH2D("h_window_binning","",10,0,310,10,0,6);
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
   gre->SetPoint(0,200,0.9411882);
   gre->SetPointError(0,0,0);
   gre->SetPoint(1,100,0.9610269);
   gre->SetPointError(1,0,0);
   gre->SetPoint(2,50,1.124021);
   gre->SetPointError(2,0,0);
   gre->SetPoint(3,40,1.322928);
   gre->SetPointError(3,0,0);
   gre->SetPoint(4,25,1.765007);
   gre->SetPointError(4,0,0);
   gre->SetPoint(5,20,2.006076);
   gre->SetPointError(5,0,0);
   gre->SetPoint(6,10,1.821965);
   gre->SetPointError(6,0,0);
   gre->SetPoint(7,8,3.536409);
   gre->SetPointError(7,0,0);
   gre->SetPoint(8,5,1.703046);
   gre->SetPointError(8,0,0);
   
   TH1F *Graph1 = new TH1F("Graph1","Graph",100,0,219.5);
   Graph1->SetMinimum(0.6816661);
   Graph1->SetMaximum(3.795931);
   Graph1->SetDirectory(0);
   Graph1->SetStats(0);
   Graph1->GetXaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph1);
   
   gre->Draw(" lp");
   
   TGraphErrors *gre2 = new TGraphErrors(9);
   gre2->SetName("Graph");
   gre2->SetTitle("Graph");
   gre2->SetFillColor(1);
   gre2->SetMarkerStyle(20);
   gre2->SetMarkerSize(0.7);
gre2->SetLineColor(kBlue);
gre2->SetMarkerColor(kBlue);

   gre2->SetPoint(0,300,1.16125);
   gre2->SetPointError(0,0,0);
   gre2->SetPoint(1,150,1.506374);
   gre2->SetPointError(1,0,0);
   gre2->SetPoint(2,75,2.009979);
   gre2->SetPointError(2,0,0);
   gre2->SetPoint(3,60,2.25003);
   gre2->SetPointError(3,0,0);
   gre2->SetPoint(4,50,2.576186);
   gre2->SetPointError(4,0,0);
   gre2->SetPoint(5,30,3.02493);
   gre2->SetPointError(5,0,0);
   gre2->SetPoint(6,20,4.418091);
   gre2->SetPointError(6,0,0);
   gre2->SetPoint(7,12,4.28739);
   gre2->SetPointError(7,0,0);
   gre2->SetPoint(8,10,4.75344);
   gre2->SetPointError(8,0,0);

   
   TH1F *Graph2 = new TH1F("Graph2","Graph",100,0,219.5);
   Graph2->SetMinimum(1.008589);
   Graph2->SetMaximum(5.79107);
   Graph2->SetDirectory(0);
   Graph2->SetStats(0);
   Graph2->GetXaxis()->SetTitleFont(42);
   gre2->SetHistogram(Graph2);
   
   gre2->Draw(" lp");
   
   TLegend *leg = new TLegend(0.4,0.75,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry(gre,"f_{max} fit","lp");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.7);
   entry=leg->AddEntry(gre2,"#delta z fit","lp");

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
