{
//=========Macro generated from canvas: c_deltaz/deltaz
//=========  (Mon Nov 15 23:27:33 2010) by ROOT version5.26/00c
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
   c_deltaz_1->Range(-0.3913044,-238.0595,1.782609,1085.049);
   c_deltaz_1->SetFillColor(0);
   c_deltaz_1->SetBorderMode(0);
   c_deltaz_1->SetBorderSize(2);
   c_deltaz_1->SetLeftMargin(0.18);
   c_deltaz_1->SetRightMargin(0.13);
   c_deltaz_1->SetTopMargin(0.08);
   c_deltaz_1->SetBottomMargin(0.18);
   c_deltaz_1->SetFrameBorderMode(0);
   c_deltaz_1->SetFrameBorderMode(0);
   
   TH2D *h_window1 = new TH2D("h_window1","",10,0,1.5,10,0.1,979.2);
   h_window1->SetStats(0);
   h_window1->GetXaxis()->SetTitle("#delta z");
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
   Photon_with_jet/h_deltaz_res->SetBinContent(0,12.01806);
   Photon_with_jet/h_deltaz_res->SetBinContent(1,168.0091);
   Photon_with_jet/h_deltaz_res->SetBinContent(2,646.2193);
   Photon_with_jet/h_deltaz_res->SetBinContent(3,829.2769);
   Photon_with_jet/h_deltaz_res->SetBinContent(4,694.3465);
   Photon_with_jet/h_deltaz_res->SetBinContent(5,564.6438);
   Photon_with_jet/h_deltaz_res->SetBinContent(6,429.7793);
   Photon_with_jet/h_deltaz_res->SetBinContent(7,396.0174);
   Photon_with_jet/h_deltaz_res->SetBinContent(8,374.3979);
   Photon_with_jet/h_deltaz_res->SetBinContent(9,338.7122);
   Photon_with_jet/h_deltaz_res->SetBinContent(10,403.537);
   Photon_with_jet/h_deltaz_res->SetBinContent(11,431.4272);
   Photon_with_jet/h_deltaz_res->SetBinContent(12,219.2381);
   Photon_with_jet/h_deltaz_res->SetBinContent(13,137.5466);
   Photon_with_jet/h_deltaz_res->SetBinContent(14,89.52593);
   Photon_with_jet/h_deltaz_res->SetBinContent(15,76.8569);
   Photon_with_jet/h_deltaz_res->SetBinContent(16,73.76099);
   Photon_with_jet/h_deltaz_res->SetBinContent(17,67.77694);
   Photon_with_jet/h_deltaz_res->SetBinContent(18,69.69115);
   Photon_with_jet/h_deltaz_res->SetBinContent(19,61.25169);
   Photon_with_jet/h_deltaz_res->SetBinContent(20,47.14482);
   Photon_with_jet/h_deltaz_res->SetBinContent(21,22.31644);
   Photon_with_jet/h_deltaz_res->SetBinContent(22,18.20807);
   Photon_with_jet/h_deltaz_res->SetBinContent(23,11.79398);
   Photon_with_jet/h_deltaz_res->SetBinContent(24,7.864897);
   Photon_with_jet/h_deltaz_res->SetBinContent(25,3.283024);
   Photon_with_jet/h_deltaz_res->SetBinContent(26,6.755834);
   Photon_with_jet/h_deltaz_res->SetBinContent(27,2.995941);
   Photon_with_jet/h_deltaz_res->SetBinContent(28,3.279657);
   Photon_with_jet/h_deltaz_res->SetBinContent(29,3.137799);
   Photon_with_jet/h_deltaz_res->SetBinContent(30,2.204659);
   Photon_with_jet/h_deltaz_res->SetBinContent(31,11.45223);
   Photon_with_jet/h_deltaz_res->SetBinError(0,2.707261);
   Photon_with_jet/h_deltaz_res->SetBinError(1,9.199715);
   Photon_with_jet/h_deltaz_res->SetBinError(2,25.20618);
   Photon_with_jet/h_deltaz_res->SetBinError(3,30.27517);
   Photon_with_jet/h_deltaz_res->SetBinError(4,25.81524);
   Photon_with_jet/h_deltaz_res->SetBinError(5,21.69892);
   Photon_with_jet/h_deltaz_res->SetBinError(6,17.69972);
   Photon_with_jet/h_deltaz_res->SetBinError(7,17.02824);
   Photon_with_jet/h_deltaz_res->SetBinError(8,16.6453);
   Photon_with_jet/h_deltaz_res->SetBinError(9,15.60772);
   Photon_with_jet/h_deltaz_res->SetBinError(10,17.99914);
   Photon_with_jet/h_deltaz_res->SetBinError(11,19.42808);
   Photon_with_jet/h_deltaz_res->SetBinError(12,13.08941);
   Photon_with_jet/h_deltaz_res->SetBinError(13,10.06662);
   Photon_with_jet/h_deltaz_res->SetBinError(14,7.875834);
   Photon_with_jet/h_deltaz_res->SetBinError(15,7.215745);
   Photon_with_jet/h_deltaz_res->SetBinError(16,7.137493);
   Photon_with_jet/h_deltaz_res->SetBinError(17,6.792081);
   Photon_with_jet/h_deltaz_res->SetBinError(18,6.970228);
   Photon_with_jet/h_deltaz_res->SetBinError(19,6.558047);
   Photon_with_jet/h_deltaz_res->SetBinError(20,5.459738);
   Photon_with_jet/h_deltaz_res->SetBinError(21,3.700399);
   Photon_with_jet/h_deltaz_res->SetBinError(22,3.265492);
   Photon_with_jet/h_deltaz_res->SetBinError(23,2.698115);
   Photon_with_jet/h_deltaz_res->SetBinError(24,2.194587);
   Photon_with_jet/h_deltaz_res->SetBinError(25,1.191482);
   Photon_with_jet/h_deltaz_res->SetBinError(26,2.01528);
   Photon_with_jet/h_deltaz_res->SetBinError(27,1.443494);
   Photon_with_jet/h_deltaz_res->SetBinError(28,1.189227);
   Photon_with_jet/h_deltaz_res->SetBinError(29,1.322476);
   Photon_with_jet/h_deltaz_res->SetBinError(30,1.205048);
   Photon_with_jet/h_deltaz_res->SetBinError(31,2.495293);
   Photon_with_jet/h_deltaz_res->SetEntries(19308.1);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   Photon_with_jet/h_deltaz_res->SetFillColor(ci);
   Photon_with_jet/h_deltaz_res->Draw("HIST E1 SAME");
   
   TH1D *Photon_with_jet/h_deltaz_mc_signal = new TH1D("Photon_with_jet/h_deltaz_mc_signal","#delta z",30,0,1.5);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(0,2.800376);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(1,103.2845);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(2,399.3007);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(3,474.0872);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(4,373.1089);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(5,272.9543);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(6,194.7085);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(7,157.48);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(8,115.6391);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(9,98.34262);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(10,105.5907);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(11,87.80003);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(12,18.77899);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(13,5.271296);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(14,1.153096);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(15,0.494184);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(16,0.329456);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(17,0.164728);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(18,0.164728);
   Photon_with_jet/h_deltaz_mc_signal->SetBinContent(19,0.164728);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(0,0.679191);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(1,6.518574);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(2,21.1323);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(3,24.79705);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(4,19.84797);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(5,14.92996);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(6,11.07335);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(7,9.228861);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(8,7.140498);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(9,6.268811);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(10,6.634921);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(11,5.733621);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(12,1.983853);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(13,0.9667956);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(14,0.4394574);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(15,0.2863376);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(16,0.2335163);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(17,0.1649246);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(18,0.1649246);
   Photon_with_jet/h_deltaz_mc_signal->SetBinError(19,0.1649246);
   Photon_with_jet/h_deltaz_mc_signal->SetEntries(14640);

   ci = TColor::GetColor("#000000");
   Photon_with_jet/h_deltaz_mc_signal->SetLineColor(ci);
   Photon_with_jet/h_deltaz_mc_signal->Draw("HIST SAME");
   
   TH1D *Photon_with_jet/h_deltaz_mc_rad = new TH1D("Photon_with_jet/h_deltaz_mc_rad","#delta z",30,0,1.5);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(0,3.388254);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(1,18.43205);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(2,92.34753);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(3,119.4734);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(4,87.91902);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(5,65.30191);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(6,42.56166);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(7,26.45165);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(8,31.66424);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(9,19.78272);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(10,14.447);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(11,19.64262);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(12,4.176578);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(13,1.17612);
   Photon_with_jet/h_deltaz_mc_rad->SetBinContent(14,0.9973236);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(0,1.773736);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(1,3.726507);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(2,8.301667);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(3,9.414218);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(4,7.971141);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(5,6.79509);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(6,5.532109);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(7,4.053048);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(8,4.702465);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(9,3.715628);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(10,3.149083);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(11,3.945729);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(12,1.860649);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(13,0.6790332);
   Photon_with_jet/h_deltaz_mc_rad->SetBinError(14,0.9973236);
   Photon_with_jet/h_deltaz_mc_rad->SetEntries(548.3375);

   ci = TColor::GetColor("#000000");
   Photon_with_jet/h_deltaz_mc_rad->SetLineColor(ci);
   Photon_with_jet/h_deltaz_mc_rad->Draw("HIST SAME");
   
   TH1D *Photon_with_jet/h_deltaz_mc_norad = new TH1D("Photon_with_jet/h_deltaz_mc_norad","#delta z",30,0,1.5);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(0,5.829427);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(1,46.29254);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(2,154.5711);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(3,235.7163);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(4,233.3185);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(5,226.3875);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(6,192.5092);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(7,212.0857);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(8,227.0946);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(9,220.5869);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(10,283.4993);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(11,323.9846);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(12,196.2825);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(13,131.0992);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(14,87.37551);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(15,76.36271);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(16,73.43154);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(17,67.61221);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(18,69.52642);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(19,61.08696);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(20,47.14482);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(21,22.31644);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(22,18.20807);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(23,11.79398);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(24,7.864897);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(25,3.283024);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(26,6.755834);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(27,2.995941);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(28,3.279657);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(29,3.137799);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(30,2.204659);
   Photon_with_jet/h_deltaz_mc_norad->SetBinContent(31,11.45223);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(0,1.929202);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(1,5.315646);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(2,10.94805);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(3,14.59673);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(4,14.45494);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(5,14.20445);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(6,12.65136);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(7,13.7245);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(8,14.28167);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(9,13.80207);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(10,16.4326);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(11,18.13856);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(12,12.80371);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(13,9.997055);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(14,7.800063);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(15,7.210061);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(16,7.133672);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(17,6.790078);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(18,6.968276);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(19,6.555973);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(20,5.459738);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(21,3.700399);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(22,3.265492);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(23,2.698115);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(24,2.194587);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(25,1.191482);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(26,2.01528);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(27,1.443494);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(28,1.189227);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(29,1.322476);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(30,1.205048);
   Photon_with_jet/h_deltaz_mc_norad->SetBinError(31,2.495293);
   Photon_with_jet/h_deltaz_mc_norad->SetEntries(4119.764);
   Photon_with_jet/h_deltaz_mc_norad->SetLineColor(40);
   Photon_with_jet/h_deltaz_mc_norad->Draw("HIST SAME");
   
   TH1D *Photon_with_jet/h_deltaz_data = new TH1D("Photon_with_jet/h_deltaz_data","#delta z",30,0.015,1.515);
   Photon_with_jet/h_deltaz_data->SetBinContent(0,5);
   Photon_with_jet/h_deltaz_data->SetBinContent(1,99);
   Photon_with_jet/h_deltaz_data->SetBinContent(2,701);
   Photon_with_jet/h_deltaz_data->SetBinContent(3,816);
   Photon_with_jet/h_deltaz_data->SetBinContent(4,689);
   Photon_with_jet/h_deltaz_data->SetBinContent(5,511);
   Photon_with_jet/h_deltaz_data->SetBinContent(6,366);
   Photon_with_jet/h_deltaz_data->SetBinContent(7,328);
   Photon_with_jet/h_deltaz_data->SetBinContent(8,319);
   Photon_with_jet/h_deltaz_data->SetBinContent(9,327);
   Photon_with_jet/h_deltaz_data->SetBinContent(10,455);
   Photon_with_jet/h_deltaz_data->SetBinContent(11,488);
   Photon_with_jet/h_deltaz_data->SetBinContent(12,224);
   Photon_with_jet/h_deltaz_data->SetBinContent(13,154);
   Photon_with_jet/h_deltaz_data->SetBinContent(14,106);
   Photon_with_jet/h_deltaz_data->SetBinContent(15,109);
   Photon_with_jet/h_deltaz_data->SetBinContent(16,90);
   Photon_with_jet/h_deltaz_data->SetBinContent(17,84);
   Photon_with_jet/h_deltaz_data->SetBinContent(18,81);
   Photon_with_jet/h_deltaz_data->SetBinContent(19,84);
   Photon_with_jet/h_deltaz_data->SetBinContent(20,52);
   Photon_with_jet/h_deltaz_data->SetBinContent(21,37);
   Photon_with_jet/h_deltaz_data->SetBinContent(22,25);
   Photon_with_jet/h_deltaz_data->SetBinContent(23,9);
   Photon_with_jet/h_deltaz_data->SetBinContent(24,14);
   Photon_with_jet/h_deltaz_data->SetBinContent(25,10);
   Photon_with_jet/h_deltaz_data->SetBinContent(26,9);
   Photon_with_jet/h_deltaz_data->SetBinContent(27,3);
   Photon_with_jet/h_deltaz_data->SetBinContent(28,3);
   Photon_with_jet/h_deltaz_data->SetBinContent(29,3);
   Photon_with_jet/h_deltaz_data->SetBinContent(30,5);
   Photon_with_jet/h_deltaz_data->SetBinContent(31,18);
   Photon_with_jet/h_deltaz_data->SetBinError(0,2.236068);
   Photon_with_jet/h_deltaz_data->SetBinError(1,9.949874);
   Photon_with_jet/h_deltaz_data->SetBinError(2,26.4764);
   Photon_with_jet/h_deltaz_data->SetBinError(3,28.56571);
   Photon_with_jet/h_deltaz_data->SetBinError(4,26.24881);
   Photon_with_jet/h_deltaz_data->SetBinError(5,22.60531);
   Photon_with_jet/h_deltaz_data->SetBinError(6,19.13113);
   Photon_with_jet/h_deltaz_data->SetBinError(7,18.11077);
   Photon_with_jet/h_deltaz_data->SetBinError(8,17.86057);
   Photon_with_jet/h_deltaz_data->SetBinError(9,18.08314);
   Photon_with_jet/h_deltaz_data->SetBinError(10,21.33073);
   Photon_with_jet/h_deltaz_data->SetBinError(11,22.09072);
   Photon_with_jet/h_deltaz_data->SetBinError(12,14.96663);
   Photon_with_jet/h_deltaz_data->SetBinError(13,12.40967);
   Photon_with_jet/h_deltaz_data->SetBinError(14,10.29563);
   Photon_with_jet/h_deltaz_data->SetBinError(15,10.44031);
   Photon_with_jet/h_deltaz_data->SetBinError(16,9.486833);
   Photon_with_jet/h_deltaz_data->SetBinError(17,9.165151);
   Photon_with_jet/h_deltaz_data->SetBinError(18,9);
   Photon_with_jet/h_deltaz_data->SetBinError(19,9.165151);
   Photon_with_jet/h_deltaz_data->SetBinError(20,7.211103);
   Photon_with_jet/h_deltaz_data->SetBinError(21,6.082763);
   Photon_with_jet/h_deltaz_data->SetBinError(22,5);
   Photon_with_jet/h_deltaz_data->SetBinError(23,3);
   Photon_with_jet/h_deltaz_data->SetBinError(24,3.741657);
   Photon_with_jet/h_deltaz_data->SetBinError(25,3.162278);
   Photon_with_jet/h_deltaz_data->SetBinError(26,3);
   Photon_with_jet/h_deltaz_data->SetBinError(27,1.732051);
   Photon_with_jet/h_deltaz_data->SetBinError(28,1.732051);
   Photon_with_jet/h_deltaz_data->SetBinError(29,1.732051);
   Photon_with_jet/h_deltaz_data->SetBinError(30,2.236068);
   Photon_with_jet/h_deltaz_data->SetBinError(31,4.242641);
   Photon_with_jet/h_deltaz_data->SetEntries(6224);
   Photon_with_jet/h_deltaz_data->SetMarkerStyle(24);
   Photon_with_jet/h_deltaz_data->SetMarkerSize(0.2);
   Photon_with_jet/h_deltaz_data->Draw("P E1 SAME");
   
   TH2D *h_window1__1 = new TH2D("h_window1__1","",10,0,1.5,10,0.1,979.2);
   h_window1__1->SetDirectory(0);
   h_window1__1->SetStats(0);
   h_window1__1->GetXaxis()->SetTitle("#delta z");
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
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(0.2);
   entry=leg->AddEntry("Photon_with_jet/h_fmax_mc_signal","signal mc","l");

   ci = TColor::GetColor("#000000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Photon_with_jet/h_fmax_mc_rad","rad bg mc","l");

   ci = TColor::GetColor("#000000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Photon_with_jet/h_fmax_mc_norad","norad bg mc","l");
   entry->SetLineColor(40);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Photon_with_jet/h_fmax_res","signal + bg","f");

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
   TText *text = pt->AddText("fit range: 1 .. 20");
   text->SetTextSize(0.04);
   text = pt->AddText("#chi^{2} / 19-1 = 36.83");
   text->SetTextSize(0.04);
   pt->Draw();
   c_deltaz_1->Modified();
   c_deltaz->cd();
   c_deltaz->Modified();
   c_deltaz->cd();
   c_deltaz->SetSelected(c_deltaz);
}
