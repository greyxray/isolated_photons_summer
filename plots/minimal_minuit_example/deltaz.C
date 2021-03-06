{
//=========Macro generated from canvas: c_deltaz/deltaz
//=========  (Wed Jan  2 21:04:09 2013) by ROOT version5.26/00c
   TCanvas *c_deltaz = new TCanvas("c_deltaz", "deltaz",0,0,800,600);
   c_deltaz->SetHighLightColor(2);
   c_deltaz->Range(0,0,1,1);
   c_deltaz->SetFillColor(0);
   c_deltaz->SetBorderMode(0);
   c_deltaz->SetBorderSize(2);
   c_deltaz->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: c_deltaz_1
   TPad *c_deltaz_1 = new TPad("c_deltaz_1", "c_deltaz_1",0.01,0.01,0.99,0.99);
   c_deltaz_1->Draw();
   c_deltaz_1->cd();
   c_deltaz_1->Range(-0.3913044,-237.4757,1.782609,1082.389);
   c_deltaz_1->SetFillColor(0);
   c_deltaz_1->SetBorderMode(0);
   c_deltaz_1->SetBorderSize(2);
   c_deltaz_1->SetLeftMargin(0.18);
   c_deltaz_1->SetRightMargin(0.13);
   c_deltaz_1->SetTopMargin(0.08);
   c_deltaz_1->SetBottomMargin(0.18);
   c_deltaz_1->SetFrameBorderMode(0);
   c_deltaz_1->SetFrameBorderMode(0);
   
   TH2D *h_window1 = new TH2D("h_window1","",10,0,1.5,10,0.1,976.8);
   h_window1->SetStats(0);
   h_window1->GetXaxis()->SetTitle("<#delta z>");
   h_window1->GetXaxis()->CenterTitle(true);
   h_window1->GetXaxis()->SetNdivisions(507);
   h_window1->GetXaxis()->SetLabelFont(42);
   h_window1->GetXaxis()->SetLabelSize(0.07536232);
   h_window1->GetXaxis()->SetTitleSize(0.07536232);
   h_window1->GetXaxis()->SetTitleFont(42);
   h_window1->GetYaxis()->SetTitle("Events");
   h_window1->GetYaxis()->CenterTitle(true);
   h_window1->GetYaxis()->SetNdivisions(507);
   h_window1->GetYaxis()->SetLabelFont(42);
   h_window1->GetYaxis()->SetLabelSize(0.07027027);
   h_window1->GetYaxis()->SetTitleSize(0.07027027);
   h_window1->GetYaxis()->SetTitleOffset(1.2);
   h_window1->GetYaxis()->SetTitleFont(42);
   h_window1->Draw("");
   
   TH1D *Photon_with_jet/h_deltaz_res = new TH1D("Photon_with_jet/h_deltaz_res","#delta z",30,0,1.5);
   Photon_with_jet/h_deltaz_res->SetBinContent(0,0.3203661);
   Photon_with_jet/h_deltaz_res->SetBinContent(1,153.1913);
   Photon_with_jet/h_deltaz_res->SetBinContent(2,668.6719);
   Photon_with_jet/h_deltaz_res->SetBinContent(3,798.9206);
   Photon_with_jet/h_deltaz_res->SetBinContent(4,600.7533);
   Photon_with_jet/h_deltaz_res->SetBinContent(5,492.879);
   Photon_with_jet/h_deltaz_res->SetBinContent(6,394.7627);
   Photon_with_jet/h_deltaz_res->SetBinContent(7,364.0801);
   Photon_with_jet/h_deltaz_res->SetBinContent(8,351.5158);
   Photon_with_jet/h_deltaz_res->SetBinContent(9,366.4984);
   Photon_with_jet/h_deltaz_res->SetBinContent(10,463.841);
   Photon_with_jet/h_deltaz_res->SetBinContent(11,464.8642);
   Photon_with_jet/h_deltaz_res->SetBinContent(12,237.3308);
   Photon_with_jet/h_deltaz_res->SetBinContent(13,160.5103);
   Photon_with_jet/h_deltaz_res->SetBinContent(14,101.8194);
   Photon_with_jet/h_deltaz_res->SetBinContent(15,89.85477);
   Photon_with_jet/h_deltaz_res->SetBinContent(16,85.75095);
   Photon_with_jet/h_deltaz_res->SetBinContent(17,74.3562);
   Photon_with_jet/h_deltaz_res->SetBinContent(18,72.09067);
   Photon_with_jet/h_deltaz_res->SetBinContent(19,63.76223);
   Photon_with_jet/h_deltaz_res->SetBinContent(20,52.62962);
   Photon_with_jet/h_deltaz_res->SetBinContent(21,20.97606);
   Photon_with_jet/h_deltaz_res->SetBinContent(22,18.11235);
   Photon_with_jet/h_deltaz_res->SetBinContent(23,11.63488);
   Photon_with_jet/h_deltaz_res->SetBinContent(24,8.309983);
   Photon_with_jet/h_deltaz_res->SetBinContent(25,9.46985);
   Photon_with_jet/h_deltaz_res->SetBinContent(26,7.062683);
   Photon_with_jet/h_deltaz_res->SetBinContent(27,3.434609);
   Photon_with_jet/h_deltaz_res->SetBinContent(28,3.502099);
   Photon_with_jet/h_deltaz_res->SetBinContent(29,4.477132);
   Photon_with_jet/h_deltaz_res->SetBinContent(30,1.937084);
   Photon_with_jet/h_deltaz_res->SetBinContent(31,16.30045);
   Photon_with_jet/h_deltaz_res->SetBinError(0,0.3203661);
   Photon_with_jet/h_deltaz_res->SetBinError(1,7.960635);
   Photon_with_jet/h_deltaz_res->SetBinError(2,23.73692);
   Photon_with_jet/h_deltaz_res->SetBinError(3,26.4185);
   Photon_with_jet/h_deltaz_res->SetBinError(4,21.24072);
   Photon_with_jet/h_deltaz_res->SetBinError(5,17.10294);
   Photon_with_jet/h_deltaz_res->SetBinError(6,14.74262);
   Photon_with_jet/h_deltaz_res->SetBinError(7,13.94095);
   Photon_with_jet/h_deltaz_res->SetBinError(8,13.6952);
   Photon_with_jet/h_deltaz_res->SetBinError(9,14.15298);
   Photon_with_jet/h_deltaz_res->SetBinError(10,16.89201);
   Photon_with_jet/h_deltaz_res->SetBinError(11,17.1799);
   Photon_with_jet/h_deltaz_res->SetBinError(12,11.67965);
   Photon_with_jet/h_deltaz_res->SetBinError(13,9.687257);
   Photon_with_jet/h_deltaz_res->SetBinError(14,7.307477);
   Photon_with_jet/h_deltaz_res->SetBinError(15,6.872249);
   Photon_with_jet/h_deltaz_res->SetBinError(16,6.800893);
   Photon_with_jet/h_deltaz_res->SetBinError(17,6.223165);
   Photon_with_jet/h_deltaz_res->SetBinError(18,6.245868);
   Photon_with_jet/h_deltaz_res->SetBinError(19,5.836908);
   Photon_with_jet/h_deltaz_res->SetBinError(20,5.153935);
   Photon_with_jet/h_deltaz_res->SetBinError(21,3.227521);
   Photon_with_jet/h_deltaz_res->SetBinError(22,3.028647);
   Photon_with_jet/h_deltaz_res->SetBinError(23,2.444282);
   Photon_with_jet/h_deltaz_res->SetBinError(24,1.930693);
   Photon_with_jet/h_deltaz_res->SetBinError(25,2.606012);
   Photon_with_jet/h_deltaz_res->SetBinError(26,1.790718);
   Photon_with_jet/h_deltaz_res->SetBinError(27,1.300344);
   Photon_with_jet/h_deltaz_res->SetBinError(28,1.211545);
   Photon_with_jet/h_deltaz_res->SetBinError(29,1.483203);
   Photon_with_jet/h_deltaz_res->SetBinError(30,0.9784517);
   Photon_with_jet/h_deltaz_res->SetBinError(31,3.350582);
   Photon_with_jet/h_deltaz_res->SetEntries(20016.5);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   Photon_with_jet/h_deltaz_res->SetFillColor(ci);
   Photon_with_jet/h_deltaz_res->Draw("HIST E1 SAME");
   
   TH1D *Photon_with_jet/h_deltaz_mc_signal = new TH1D("Photon_with_jet/h_deltaz_mc_signal","#delta z",30,0,1.5);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(1,71.79762);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(2,386.4117);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(3,418.0906);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(4,271.9461);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(5,193.6187);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(6,138.5225);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(7,111.8652);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(8,83.54496);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(9,88.09114);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(10,103.3945);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(11,66.21106);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(12,12.73575);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(13,3.123778);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(14,1.028999);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(15,0.1265265);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(16,0.2038575);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(17,0.1904503);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(18,0.07789064);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(19,0.04554232);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(1,4.953725);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(2,20.51518);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(3,22.0803);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(4,16.35778);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(5,10.96653);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(6,8.281659);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(7,6.968162);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(8,5.462733);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(9,5.864011);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(10,6.470279);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(11,4.538033);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(12,1.457966);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(13,0.7199769);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(14,0.3845651);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(15,0.09880618);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(16,0.2041014);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(17,0.156897);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(18,0.07798384);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(19,0.04559681);
   Photon_with_jet/h_deltaz_mc_signal->SetEntries(14091);

   ci = TColor::GetColor("#000000");
   Photon_with_jet/h_deltaz_mc_signal->SetLineColor(ci);
   Photon_with_jet/h_deltaz_mc_signal->Draw("HIST SAME");
   
   TH1D *Photon_with_jet/h_deltaz_mc_rad = new TH1D("Photon_with_jet/h_deltaz_mc_rad","#delta z",30,0,1.5);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(0,0.3203661);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(1,17.69211);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(2,104.9134);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(3,119.4298);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(4,77.27034);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(5,53.28568);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(6,31.82105);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(7,30.55174);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(8,26.49998);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(9,20.78748);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(10,19.12867);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(11,21.00974);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(12,2.072579);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(13,1.196473);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(0,0.3203661);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(1,2.767044);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(2,6.628548);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(3,7.102453);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(4,5.653143);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(5,4.719424);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(6,3.671278);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(7,3.55039);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(8,3.326374);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(9,2.89824);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(10,2.801226);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(11,2.960134);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(12,0.9407111);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(13,0.702699);
   Photon_with_jet/h_deltaz_mc_rad->SetEntries(742.5158);

   ci = TColor::GetColor("#000000");
   Photon_with_jet/h_deltaz_mc_rad->SetLineColor(ci);
   Photon_with_jet/h_deltaz_mc_rad->Draw("HIST SAME");
   
   TH1D *Photon_with_jet/h_deltaz_mc_norad = new TH1D("Photon_with_jet/h_deltaz_mc_norad","#delta z",30,0,1.5);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(1,63.70156);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(2,177.3468);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(3,261.4002);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(4,251.5369);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(5,245.9747);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(6,224.4192);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(7,221.6631);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(8,241.4709);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(9,257.6198);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(10,341.3179);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(11,377.6434);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(12,222.5225);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(13,156.19);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(14,100.7904);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(15,89.72824);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(16,85.5471);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(17,74.16575);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(18,72.01277);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(19,63.71669);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(20,52.62962);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(21,20.97606);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(22,18.11235);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(23,11.63488);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(24,8.309983);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(25,9.46985);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(26,7.062683);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(27,3.434609);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(28,3.502099);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(29,4.477132);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(30,1.937084);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(31,16.30045);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(1,5.583529);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(2,9.931314);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(3,12.64724);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(4,12.31394);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(5,12.24634);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(6,11.63102);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(7,11.54078);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(8,12.11001);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(9,12.55072);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(10,15.3502);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(11,16.30316);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(12,11.55005);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(13,9.634874);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(14,7.29735);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(15,6.871539);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(16,6.79783);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(17,6.221187);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(18,6.245381);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(19,5.83673);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(20,5.153935);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(21,3.227521);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(22,3.028647);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(23,2.444282);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(24,1.930693);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(25,2.606012);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(26,1.790718);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(27,1.300344);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(28,1.211545);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(29,1.483203);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(30,0.9784517);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(31,3.350582);
   Photon_with_jet/h_deltaz_mc_norad->SetEntries(5182.988);
   Photon_with_jet/h_deltaz_mc_norad->SetLineColor(40);
   Photon_with_jet/h_deltaz_mc_norad->Draw("HIST SAME");
   
   TH1D *Photon_with_jet/h_deltaz_data = new TH1D("Photon_with_jet/h_deltaz_data","#delta z",30,0.015,1.515);
   Photon_with_jet/h_deltaz_data->SetBinContent(1,99);
   Photon_with_jet/h_deltaz_data->SetBinContent(2,692);
   Photon_with_jet/h_deltaz_data->SetBinContent(3,814);
   Photon_with_jet/h_deltaz_data->SetBinContent(4,681);
   Photon_with_jet/h_deltaz_data->SetBinContent(5,505);
   Photon_with_jet/h_deltaz_data->SetBinContent(6,364);
   Photon_with_jet/h_deltaz_data->SetBinContent(7,321);
   Photon_with_jet/h_deltaz_data->SetBinContent(8,318);
   Photon_with_jet/h_deltaz_data->SetBinContent(9,324);
   Photon_with_jet/h_deltaz_data->SetBinContent(10,450);
   Photon_with_jet/h_deltaz_data->SetBinContent(11,480);
   Photon_with_jet/h_deltaz_data->SetBinContent(12,225);
   Photon_with_jet/h_deltaz_data->SetBinContent(13,152);
   Photon_with_jet/h_deltaz_data->SetBinContent(14,107);
   Photon_with_jet/h_deltaz_data->SetBinContent(15,110);
   Photon_with_jet/h_deltaz_data->SetBinContent(16,89);
   Photon_with_jet/h_deltaz_data->SetBinContent(17,83);
   Photon_with_jet/h_deltaz_data->SetBinContent(18,81);
   Photon_with_jet/h_deltaz_data->SetBinContent(19,84);
   Photon_with_jet/h_deltaz_data->SetBinContent(20,54);
   Photon_with_jet/h_deltaz_data->SetBinContent(21,34);
   Photon_with_jet/h_deltaz_data->SetBinContent(22,25);
   Photon_with_jet/h_deltaz_data->SetBinContent(23,9);
   Photon_with_jet/h_deltaz_data->SetBinContent(24,14);
   Photon_with_jet/h_deltaz_data->SetBinContent(25,10);
   Photon_with_jet/h_deltaz_data->SetBinContent(26,8);
   Photon_with_jet/h_deltaz_data->SetBinContent(27,3);
   Photon_with_jet/h_deltaz_data->SetBinContent(28,3);
   Photon_with_jet/h_deltaz_data->SetBinContent(29,3);
   Photon_with_jet/h_deltaz_data->SetBinContent(30,5);
   Photon_with_jet/h_deltaz_data->SetBinContent(31,18);
   Photon_with_jet/h_deltaz_data->SetBinError(1,9.949874);
   Photon_with_jet/h_deltaz_data->SetBinError(2,26.30589);
   Photon_with_jet/h_deltaz_data->SetBinError(3,28.53069);
   Photon_with_jet/h_deltaz_data->SetBinError(4,26.09598);
   Photon_with_jet/h_deltaz_data->SetBinError(5,22.47221);
   Photon_with_jet/h_deltaz_data->SetBinError(6,19.07878);
   Photon_with_jet/h_deltaz_data->SetBinError(7,17.91647);
   Photon_with_jet/h_deltaz_data->SetBinError(8,17.83255);
   Photon_with_jet/h_deltaz_data->SetBinError(9,18);
   Photon_with_jet/h_deltaz_data->SetBinError(10,21.2132);
   Photon_with_jet/h_deltaz_data->SetBinError(11,21.9089);
   Photon_with_jet/h_deltaz_data->SetBinError(12,15);
   Photon_with_jet/h_deltaz_data->SetBinError(13,12.32883);
   Photon_with_jet/h_deltaz_data->SetBinError(14,10.34408);
   Photon_with_jet/h_deltaz_data->SetBinError(15,10.48809);
   Photon_with_jet/h_deltaz_data->SetBinError(16,9.433981);
   Photon_with_jet/h_deltaz_data->SetBinError(17,9.110434);
   Photon_with_jet/h_deltaz_data->SetBinError(18,9);
   Photon_with_jet/h_deltaz_data->SetBinError(19,9.165151);
   Photon_with_jet/h_deltaz_data->SetBinError(20,7.348469);
   Photon_with_jet/h_deltaz_data->SetBinError(21,5.830952);
   Photon_with_jet/h_deltaz_data->SetBinError(22,5);
   Photon_with_jet/h_deltaz_data->SetBinError(23,3);
   Photon_with_jet/h_deltaz_data->SetBinError(24,3.741657);
   Photon_with_jet/h_deltaz_data->SetBinError(25,3.162278);
   Photon_with_jet/h_deltaz_data->SetBinError(26,2.828427);
   Photon_with_jet/h_deltaz_data->SetBinError(27,1.732051);
   Photon_with_jet/h_deltaz_data->SetBinError(28,1.732051);
   Photon_with_jet/h_deltaz_data->SetBinError(29,1.732051);
   Photon_with_jet/h_deltaz_data->SetBinError(30,2.236068);
   Photon_with_jet/h_deltaz_data->SetBinError(31,4.242641);
   Photon_with_jet/h_deltaz_data->SetEntries(6165);

   ci = TColor::GetColor("#000000");
   Photon_with_jet/h_deltaz_data->SetLineColor(ci);

   ci = TColor::GetColor("#000000");
   Photon_with_jet/h_deltaz_data->SetMarkerColor(ci);
   Photon_with_jet/h_deltaz_data->SetMarkerStyle(24);
   Photon_with_jet/h_deltaz_data->SetMarkerSize(0.2);
   Photon_with_jet/h_deltaz_data->Draw("P E1 SAME");
   
   TH2D *h_window1__1 = new TH2D("h_window1__1","",10,0,1.5,10,0.1,976.8);
   h_window1__1->SetDirectory(0);
   h_window1__1->SetStats(0);
   h_window1__1->GetXaxis()->SetTitle("<#delta z>");
   h_window1__1->GetXaxis()->CenterTitle(true);
   h_window1__1->GetXaxis()->SetNdivisions(507);
   h_window1__1->GetXaxis()->SetLabelFont(42);
   h_window1__1->GetXaxis()->SetLabelSize(0.07536232);
   h_window1__1->GetXaxis()->SetTitleSize(0.07536232);
   h_window1__1->GetXaxis()->SetTitleFont(42);
   h_window1__1->GetYaxis()->SetTitle("Events");
   h_window1__1->GetYaxis()->CenterTitle(true);
   h_window1__1->GetYaxis()->SetNdivisions(507);
   h_window1__1->GetYaxis()->SetLabelFont(42);
   h_window1__1->GetYaxis()->SetLabelSize(0.07027027);
   h_window1__1->GetYaxis()->SetTitleSize(0.07027027);
   h_window1__1->GetYaxis()->SetTitleOffset(1.2);
   h_window1__1->GetYaxis()->SetTitleFont(42);
   h_window1__1->Draw("sameaxis");
   
   TLegend *leg = new TLegend(0.5,0.65,0.85,0.9105708,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Photon_with_jet/h_fmax_data","data","pe");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(0.2);
   entry=leg->AddEntry("Photon_with_jet/h_fmax_mc_signal","QQ","l");

   ci = TColor::GetColor("#000000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Photon_with_jet/h_fmax_mc_rad","LL","l");

   ci = TColor::GetColor("#000000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Photon_with_jet/h_fmax_mc_norad","Hadronic BG","l");
   entry->SetLineColor(40);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Photon_with_jet/h_fmax_res","Fit result","f");

   ci = TColor::GetColor("#000000");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.45,0.574664,0.85,0.64,"brNDC");
   pt->SetBorderSize(0);
   TText *text = pt->AddText("fit range: bins 0 .. 20");
   text->SetTextSize(0.04);
   text = pt->AddText("#chi^{2} / 20-2 = 2.76");
   text->SetTextSize(0.04);
   pt->Draw();
   TLine *line = new TLine(0.35,0,0.35,976.8);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   c_deltaz_1->Modified();
   c_deltaz->cd();
   c_deltaz->Modified();
   c_deltaz->cd();
   c_deltaz->SetSelected(c_deltaz);
}
