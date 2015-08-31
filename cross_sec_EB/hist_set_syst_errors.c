void Hist::SetSystematicErrors(Int_t n, TH1D** h_1st, TH1D** h_2nd, TGraphAsymmErrors** gr_2nd)
{
  TString name = h_2nd[0]->GetName();
  Double_t cross_section_et[number_etbins] = {0.};
  Double_t cross_section_eta[number_etabins] = {0.};
  Double_t cross_section_Q2[number_Q2bins] = {0.};
  Double_t cross_section_x[number_xbins] = {0.};
  Double_t cross_section_et_jet[number_et_jetbins] = {0.};
  Double_t cross_section_eta_jet[number_eta_jetbins] = {0.};
  
  Double_t cross_section_et_err[number_etbins] = {0.};
  Double_t cross_section_eta_err[number_etabins] = {0.};
  Double_t cross_section_Q2_err[number_Q2bins] = {0.};
  Double_t cross_section_x_err[number_xbins] = {0.};
  Double_t cross_section_et_jet_err[number_et_jetbins] = {0.};
  Double_t cross_section_eta_jet_err[number_eta_jetbins] = {0.};

  Double_t x_et[number_etbins] = {0.};
  Double_t x_eta[number_etabins] = {0.};
  Double_t x_Q2[number_Q2bins] = {0.};
  Double_t x_x[number_xbins] = {0.};
  Double_t x_et_jet[number_et_jetbins] = {0.};
  Double_t x_eta_jet[number_eta_jetbins] = {0.};
  
  Double_t x_err[100] = {0.};
  Double_t y_zero[100] = {0.};

  Double_t y1_5[number_etabins] = {0.0995400228, 0.0547338106, 0.0371417611, 0.0734737625};    //eta et_jet_delta_minus
  Double_t my1_5[number_etabins] = {-0.0995400228, -0.0547338106, -0.0371417611, -0.0734737625};    //eta et_jet_delta_minus
  Double_t y1_6[number_etabins] = {0.0771837064, 0.0447158787, 0.0463204268, 0.0224662797};    //eta et_jet_delta_plus

  Double_t y2_5[number_etbins] = {0.0778550730, 0.0936475714, 0.0117903008, 0.0192536183};    //Et et_jet_delta_minus
  Double_t my2_5[number_etbins] = {-0.0778550730, -0.0936475714, -0.0117903008, -0.0192536183};    //Et et_jet_delta_minus
  Double_t y2_6[number_etbins] = {0.0740435972, 0.0318872822, 0.0151360257, 0.0287754279};    //Et et_jet_delta_plus

  Double_t y3_5[number_Q2bins] = {0.0694263286, 0.0694263286, 0.0303045255, 0.1144783219, 0.1732685955};    //Q2 et_jet_delta_minus
  Double_t my3_5[number_Q2bins] = {-0.0694263286, -0.0694263286, -0.0303045255, -0.1144783219, -0.1732685955};    //Q2 et_jet_delta_minus
  Double_t y3_6[number_Q2bins] = {0.0681457064, 0.0681457064, 0.0196989574, 0.0683708038, 0.0642655769};    //Q2 et_jet_delta_plus

  Double_t y4_5[number_xbins] = {0.0548484076, 0.0325932924, 0.1649768131, 0.1529073906};    //x et_jet_delta_minus
  Double_t my4_5[number_xbins] = {-0.0548484076, -0.0325932924, -0.1649768131, -0.1529073906};    //x et_jet_delta_minus
  Double_t y4_6[number_xbins] = {0.0522927640, 0.0606346889, 0.0454525379, 0.2482897703};    //x et_jet_delta_plus

  Double_t y5_5[number_etabins] = {0.0258180008, 0.0352577156, 0.0030450549, 0.0147249780};    //eta en_photon_delta_minus
  Double_t my5_5[number_etabins] = {-0.0258180008, -0.0352577156, -0.0030450549, -0.0147249780};    //eta en_photon_delta_minus
  Double_t y5_6[number_etabins] = {0.0253603945, 0.0140096628, 0.0080377587, 0.0020322657};    //eta en_photon_delta_plus

  /*  Double_t y5_5[number_etabins] = {0.0801617033, 0.0316076368, 0.0053426873, 0.0136392470};    //eta en_photon_delta_minus
  Double_t my5_5[number_etabins] = {-0.0801617033, -0.0316076368, -0.0053426873, -0.0136392470};    //eta en_photon_delta_minus
  Double_t y5_6[number_etabins] = {0.0645272193, 0.0352017388, 0.0469393243, 0.0596356637};     //eta en_photon_delta_plus */

  Double_t y6_5[number_etbins] = {0.0246458609, 0.0314516129, 0.0016432917, 0.0045205109};    //Et en_photon_delta_minus
  Double_t my6_5[number_etbins] = {-0.0246458609, -0.0314516129, -0.0016432917, -0.0045205109};    //Et en_photon_delta_minus
  Double_t y6_6[number_etbins] = {0.0203396505, 0.0134872080, 0.0004351132, 0.0066426089};    //Et en_photon_delta_plus

  /*  Double_t y6_5[number_etbins] = {0.0322233777, 0.0145068595, 0.0491297736, 0.0482943085};    //Et en_photon_delta_minus
  Double_t my6_5[number_etbins] = {-0.0322233777, -0.0145068595, -0.0491297736, -0.0482943085};    //Et en_photon_delta_minus
  Double_t y6_6[number_etbins] = {0.0617862948, 0.0318872822, 0.0072596316, 0.0099583870};    //Et en_photon_delta_plus */

  Double_t y7_5[number_Q2bins] = {0.0195235611, 0.0195235611, 0.0359062623, 0.0317489649, 0.0965727873};    //q2 en_photon_delta_minus
  Double_t my7_5[number_Q2bins] = {-0.0195235611, -0.0195235611, -0.0359062623, -0.0317489649, -0.0965727873};    //q2 en_photon_delta_minus
  Double_t y7_6[number_Q2bins] = {0.0140749875, 0.0140749875, 0.0134122414, 0.0229203025, 0.0453639367};    //q2 en_photon_delta_plus

  /*  Double_t y7_5[number_Q2bins] = {0.0340194939, 0.0155919846, 0.0414947131, 0.0355179975};    //Q2 en_photon_delta_minu
  Double_t my7_5[number_Q2bins] = {-0.0340194939, -0.0155919846, -0.0414947131, -0.0355179975};    //Q2 en_photon_delta_minus
  Double_t y7_6[number_Q2bins] = {0.0622643299, 0.0252977918, 0.0648667146, 0.0512515662};    //Q2 en_photon_delta_plus */

  Double_t y8_5[number_xbins] = {0.0102792094, 0.0260374172, 0.0347077195, 0.0851308869};    //x en_photon_delta_minus
  Double_t my8_5[number_xbins] = {-0.0102792094, -0.0260374172, -0.0347077195, -0.0851308869};    //x en_photon_delta_minus
  Double_t y8_6[number_xbins] = {0.0109965830, 0.0157884943, 0.0350547336, 0.0317183360};    //x en_photon_delta_plus

  /*  Double_t y8_5[number_xbins] = {0.0262926885, 0.0189018193, 0.0543045522, 0.1145952786};    //x en_photon_delta_minus
  Double_t my8_5[number_xbins] = {-0.0262926885, -0.0189018193, -0.0543045522, -0.1145952786};    //x en_photon_delta_minus
  Double_t y8_6[number_xbins] = {0.0354863982, 0.0661671032, 0.1013344270, 0.0112944363};    //x en_photon_delta_plus */

  //  Double_t y9_5[number_etabins] = {0.1684417678, 0.1791993761, 0.0907643879, 0.1537721198};    //eta en_electron_delta_minus
  //  Double_t my9_5[number_etabins] = {-0.1684417678, -0.1791993761, -0.0907643879, -0.1537721198};    //eta en_electron_delta_minus
  //  Double_t y9_6[number_etabins] = {0.0108829666, 0.0113652376, 0.0093783738, 0.0064467763};    //eta en_electron_delta_plus
  Double_t y9_5[number_etabins] = {0.0801617033, 0.0316076368, 0.0053426873, 0.0136392470};
  Double_t my9_5[number_etabins] = {-0.0801617033, -0.0316076368, -0.0053426873, -0.0136392470};
  Double_t y9_6[number_etabins] = {0.0645272193, 0.0352017388, 0.0469393243, 0.0596356637};    //eta en_electron_delta_plus

  /*  Double_t y10_5[number_etbins] = {0.0857253920, 0.1488051539, 0.3337635181, 0.2582549060};    //Et en_electron_delta_minus
  Double_t my10_5[number_etbins] = {-0.0857253920, -0.1488051539, -0.3337635181, -0.2582549060};    //Et en_electron_delta_minus
  Double_t y10_6[number_etbins] = {0.0050382157, 0.0105951057, 0.0024945083, 0.0012157853};    //Et en_electron_delta_plus
  */
  Double_t y10_5[number_etbins] = {0.0322233777, 0.0145068595, 0.0491297736, 0.0482943085};    //Et en_electron_delta_minus
  Double_t my10_5[number_etbins] = {-0.0322233777, -0.0145068595, -0.0491297736, -0.0482943085};    //Et en_electron_delta_minus
  Double_t y10_6[number_etbins] = {0.0617862948, 0.0318872822, 0.0072596316, 0.0099583870};    //Et en_electron_delta_plus

  /*  Double_t y11_5[number_Q2bins] = {0.1559928380, 0.0947186941, 0.1905280088, 0.1438802825};    //Q2 en_electron_delta_minus
  Double_t my11_5[number_Q2bins] = {-0.1559928380, -0.0947186941, -0.1905280088, -0.1438802825};    //Q2 en_electron_delta_minus
  Double_t y11_6[number_Q2bins] = {0.0061185287, 0.0160273527, 0.0017725764, 0.0000000000};    //Q2 en_electron_delta_plus
  */
  Double_t y11_5[number_Q2bins] = {0.0340194939, 0.0340194939, 0.0155919846, 0.0414947131, 0.0355179975};    //q2 en_electron_delta_minus
  Double_t my11_5[number_Q2bins] = {-0.0340194939, -0.0340194939, -0.0155919846, -0.0414947131, -0.0355179975};    //q2 en_electron_delta_minus
  Double_t y11_6[number_Q2bins] = {0.0622643299, 0.0622643299, 0.0252977918, 0.0648667146, 0.0512515662};    //q2 en_electron_delta_plus

  /*  Double_t y12_5[number_xbins] = {0.1789634895, 0.0519173788, 0.3209880438, 0.1848926411};    //x en_electron_delta_minus
  Double_t my12_5[number_xbins] = {-0.1789634895, -0.0519173788, -0.3209880438, -0.1848926411};    //x en_electron_delta_minus
  Double_t y12_6[number_xbins] = {0.0132100583, 0.0003149110, 0.0000000000, 0.0000000000};    //x en_electron_delta_plus
  */
  Double_t y12_5[number_xbins] = {0.0262926885, 0.0189018193, 0.0543045522, 0.1145952786};    //x en_electron_delta_minus
  Double_t my12_5[number_xbins] = {-0.0262926885, -0.0189018193, -0.0543045522, -0.1145952786};    //x en_electron_delta_minus
  Double_t y12_6[number_xbins] = {0.0354863982, 0.0661671032, 0.1013344270, 0.0112944363};    //x en_electron_delta_plus

  Double_t y13_5[number_etabins] = {0.0698382967, 0.0243325722, 0.0630721836, 0.0741757095};    //eta deltaZ_delta_minus
  Double_t my13_5[number_etabins] = {-0.0698382967, -0.0243325722, -0.0630721836, -0.0741757095};    //eta deltaZ_delta_minus
  Double_t y13_6[number_etabins] = {0.0562310319, 0.0286910481, 0.0295765792, 0.0277378417};    //eta deltaZ_delta_plus

  Double_t y14_5[number_etbins] = {0.0806164999, 0.0267426770, 0.0530014363, 0.0185738838};    //Et deltaZ_delta_minu
  Double_t my14_5[number_etbins] = {-0.0806164999, -0.0267426770, -0.0530014363, -0.0185738838};    //Et deltaZ_delta_minus
  Double_t y14_6[number_etbins] = {0.0528659269, 0.0224601409, 0.0553523150, 0.0537929739};    //Et deltaZ_delta_plus

  Double_t y15_5[number_Q2bins] = {0.0508039462, 0.0508039462, 0.1924675506, 0.0315368032, 0.0511732544};    //Q2 deltaZ_delta_minus
  Double_t my15_5[number_Q2bins] = {-0.0508039462, -0.0508039462, -0.1924675506, -0.0315368032, -0.0511732544};    //Q2 deltaZ_delta_minus
  Double_t y15_6[number_Q2bins] = {0.0532821875, 0.0532821875, 0.0500179952, 0.0558532663, 0.0817433648};    //Q2 deltaZ_delta_plus

  Double_t y16_5[number_xbins] = {0.0526490910, 0.0703539886, 0.1318022651, 0.0679593895};    //x deltaZ_delta_minus
  Double_t my16_5[number_xbins] = {-0.0526490910, -0.0703539886, -0.1318022651, -0.0679593895};    //x deltaZ_delta_minus
  Double_t y16_6[number_xbins] = {0.0592187235, 0.0070998125, 0.0486513770, 0.0670301317};    //x deltaZ_delta_plus
  //
  // total syst
  //
  Double_t total_syst_minus_eta[number_etabins] = {0.};   
  Double_t total_syst_plus_eta[number_etabins] = {0.};   

  Double_t total_syst_minus_et[number_etbins] = {0.}; 
  Double_t total_syst_plus_et[number_etbins] = {0.};   

  Double_t total_syst_minus_Q2[number_Q2bins] = {0.}; 
  Double_t total_syst_plus_Q2[number_Q2bins] = {0.};   

  Double_t total_syst_minus_x[number_xbins] = {0.};
  Double_t total_syst_plus_x[number_xbins] = {0.};   

  Double_t total_syst_minus_et_jet[number_et_jetbins] = {0.};
  Double_t total_syst_plus_et_jet[number_et_jetbins] = {0.};   

  Double_t total_syst_minus_eta_jet[number_eta_jetbins] = {0.};
  Double_t total_syst_plus_eta_jet[number_eta_jetbins] = {0.};   

  if(s_var[n] == "et") {
    for(Int_t i=0; i<h_2nd[0]->GetNbinsX(); i++){
      cross_section_et[i] = h_2nd[0]->GetBinContent(i+1);
      cross_section_et_err[i] = h_2nd[0]->GetBinError(i+1);
      x_et[i] = h_2nd[0]->GetBinCenter(i+1);
      total_syst_minus_et[i] = TMath::Sqrt(y2_5[i]*y2_5[i] + y6_5[i]*y6_5[i] + y10_5[i]*y10_5[i] + y14_5[i]*y14_5[i]);
      total_syst_plus_et[i] = TMath::Sqrt(y2_6[i]*y2_6[i] + y6_6[i]*y6_6[i] + y10_6[i]*y10_6[i] + y14_6[i]*y14_6[i]);
      cout << "et cross: " << i << " " << cross_section_et[i] << endl;
      cout << "et syst: " << i << " " << /*cross_section_et[i]*/total_syst_minus_et[i] << " " << /*cross_section_et[i]*/total_syst_plus_et[i] << endl;
    }
    gr_2nd[0] = new TGraphAsymmErrors(number_etbins, x_et, cross_section_et, x_err, x_err, cross_section_et_err, cross_section_et_err);
    gr_2nd[13] = new TGraphAsymmErrors(number_etbins, x_et, y_zero, x_err, x_err, y2_5, y2_6); //relative jet_et syst
    gr_2nd[14] = new TGraphAsymmErrors(number_etbins, x_et, y_zero, x_err, x_err, y6_5, y6_6); //relative phot_et syst
    gr_2nd[15] = new TGraphAsymmErrors(number_etbins, x_et, y_zero, x_err, x_err, y10_5, y10_6); //relative el_et syst
    gr_2nd[16] = new TGraphAsymmErrors(number_etbins, x_et, y_zero, x_err, x_err, y14_5, y14_6); //relative deltaZ syst
    gr_2nd[17] = new TGraphAsymmErrors(number_etbins, x_et, y_zero, x_err, x_err, total_syst_minus_et, total_syst_plus_et); //relative total syst
    gr_2nd[20] = new TGraphAsymmErrors(number_etbins, x_et, my2_5, x_err, x_err); //relative jet_et low
    gr_2nd[21] = new TGraphAsymmErrors(number_etbins, x_et, y2_6, x_err, x_err); //relative jet_et high
    gr_2nd[22] = new TGraphAsymmErrors(number_etbins, x_et, my6_5, x_err, x_err); //relative phot_et low
    gr_2nd[23] = new TGraphAsymmErrors(number_etbins, x_et, y6_6, x_err, x_err); //relative phot_et high
    gr_2nd[24] = new TGraphAsymmErrors(number_etbins, x_et, my10_5, x_err, x_err); //relative el_et low
    gr_2nd[25] = new TGraphAsymmErrors(number_etbins, x_et, y10_6, x_err, x_err); //relative el_et high
    gr_2nd[26] = new TGraphAsymmErrors(number_etbins, x_et, my14_5, x_err, x_err); //relative deltaZ low
    gr_2nd[27] = new TGraphAsymmErrors(number_etbins, x_et, y14_6, x_err, x_err); //relative deltaZ high
  }
  if(s_var[n] == "eta") {
    for(Int_t i=0; i<h_2nd[0]->GetNbinsX(); i++){
      cross_section_eta[i] = h_2nd[0]->GetBinContent(i+1);
      cross_section_eta_err[i] = h_2nd[0]->GetBinError(i+1);
      x_eta[i] = h_2nd[0]->GetBinCenter(i+1);
      total_syst_minus_eta[i] = TMath::Sqrt(y1_5[i]*y1_5[i] + y5_5[i]*y5_5[i] + y9_5[i]*y9_5[i] + y13_5[i]*y13_5[i]);
      total_syst_plus_eta[i] = TMath::Sqrt(y1_6[i]*y1_6[i] + y5_6[i]*y5_6[i] + y9_6[i]*y9_6[i] + y13_6[i]*y13_6[i]);
      cout << "eta syst: " << i << " " << /*cross_section_eta[i]*/total_syst_minus_eta[i] << " " << /*cross_section_eta[i]*/total_syst_plus_eta[i] << endl;
    }
    gr_2nd[0] = new TGraphAsymmErrors(number_etabins, x_eta, cross_section_eta, x_err, x_err, cross_section_eta_err, cross_section_eta_err);
    gr_2nd[13] = new TGraphAsymmErrors(number_etabins, x_eta, y_zero, x_err, x_err, y1_5, y1_6); //relative jet_et syst
    gr_2nd[14] = new TGraphAsymmErrors(number_etabins, x_eta, y_zero, x_err, x_err, y5_5, y5_6); //relative phot_et syst
    gr_2nd[15] = new TGraphAsymmErrors(number_etabins, x_eta, y_zero, x_err, x_err, y9_5, y9_6); //relative el_et syst
    gr_2nd[16] = new TGraphAsymmErrors(number_etabins, x_eta, y_zero, x_err, x_err, y13_5, y13_6); //relative deltaZ syst
    gr_2nd[17] = new TGraphAsymmErrors(number_etabins, x_eta, y_zero, x_err, x_err, total_syst_minus_eta, total_syst_plus_eta); //relative total syst
    gr_2nd[20] = new TGraphAsymmErrors(number_etabins, x_eta, my1_5, x_err, x_err); //relative jet_et low
    gr_2nd[21] = new TGraphAsymmErrors(number_etabins, x_eta, y1_6, x_err, x_err); //relative jet_et high
    gr_2nd[22] = new TGraphAsymmErrors(number_etabins, x_eta, my5_5, x_err, x_err); //relative phot_et low
    gr_2nd[23] = new TGraphAsymmErrors(number_etabins, x_eta, y5_6, x_err, x_err); //relative phot_et high
    gr_2nd[24] = new TGraphAsymmErrors(number_etabins, x_eta, my9_5, x_err, x_err); //relative el_et low
    gr_2nd[25] = new TGraphAsymmErrors(number_etabins, x_eta, y9_6, x_err, x_err); //relative el_et high
    gr_2nd[26] = new TGraphAsymmErrors(number_etabins, x_eta, my13_5, x_err, x_err); //relative deltaZ low
    gr_2nd[27] = new TGraphAsymmErrors(number_etabins, x_eta, y13_6, x_err, x_err); //relative deltaZ high
  }
  if(s_var[n] == "Q2") {
    for(Int_t i=0; i<h_2nd[0]->GetNbinsX(); i++){
      cross_section_Q2[i] = h_2nd[0]->GetBinContent(i+1);
      cross_section_Q2_err[i] = h_2nd[0]->GetBinError(i+1);
      x_Q2[i] = h_2nd[0]->GetBinCenter(i+1);
      total_syst_minus_Q2[i] = TMath::Sqrt(y3_5[i]*y3_5[i] + y7_5[i]*y7_5[i] + y11_5[i]*y11_5[i] + y15_5[i]*y15_5[i]);
      total_syst_plus_Q2[i] = TMath::Sqrt(y3_6[i]*y3_6[i] + y7_6[i]*y7_6[i] + y11_6[i]*y11_6[i] + y15_6[i]*y15_6[i]);
      cout << "Q2 syst: " << i << " " << total_syst_minus_Q2[i] << " " << /*cross_section_Q2[i]*/total_syst_plus_Q2[i] << endl;
    }
    gr_2nd[0] = new TGraphAsymmErrors(number_Q2bins, x_Q2, cross_section_Q2, x_err, x_err, cross_section_Q2_err, cross_section_Q2_err);
    gr_2nd[13] = new TGraphAsymmErrors(number_Q2bins, x_Q2, y_zero, x_err, x_err, y3_5, y3_6); //relative jet_et syst
    gr_2nd[14] = new TGraphAsymmErrors(number_Q2bins, x_Q2, y_zero, x_err, x_err, y7_5, y7_6); //relative phot_et syst
    gr_2nd[15] = new TGraphAsymmErrors(number_Q2bins, x_Q2, y_zero, x_err, x_err, y11_5, y11_6); //relative el_et syst
    gr_2nd[16] = new TGraphAsymmErrors(number_Q2bins, x_Q2, y_zero, x_err, x_err, y15_5, y15_6); //relative deltaZ syst
    gr_2nd[17] = new TGraphAsymmErrors(number_Q2bins, x_Q2, y_zero, x_err, x_err, total_syst_minus_Q2, total_syst_plus_Q2); //relative total syst
    gr_2nd[20] = new TGraphAsymmErrors(number_Q2bins, x_Q2, my3_5, x_err, x_err); //relative jet_et low
    gr_2nd[21] = new TGraphAsymmErrors(number_Q2bins, x_Q2, y3_6, x_err, x_err); //relative jet_et high
    gr_2nd[22] = new TGraphAsymmErrors(number_Q2bins, x_Q2, my7_5, x_err, x_err); //relative phot_et low
    gr_2nd[23] = new TGraphAsymmErrors(number_Q2bins, x_Q2, y7_6, x_err, x_err); //relative phot_et high
    gr_2nd[24] = new TGraphAsymmErrors(number_Q2bins, x_Q2, my11_5, x_err, x_err); //relative el_et low
    gr_2nd[25] = new TGraphAsymmErrors(number_Q2bins, x_Q2, y11_6, x_err, x_err); //relative el_et high
    gr_2nd[26] = new TGraphAsymmErrors(number_Q2bins, x_Q2, my15_5, x_err, x_err); //relative deltaZ low
    gr_2nd[27] = new TGraphAsymmErrors(number_Q2bins, x_Q2, y15_6, x_err, x_err); //relative deltaZ high
  }
  if(s_var[n] == "x") {
    for(Int_t i=0; i<h_2nd[0]->GetNbinsX(); i++){
      cross_section_x[i] = h_2nd[0]->GetBinContent(i+1);
      cross_section_x_err[i] = h_2nd[0]->GetBinError(i+1);
      x_x[i] = h_2nd[0]->GetBinCenter(i+1);
      total_syst_minus_x[i] = TMath::Sqrt(y4_5[i]*y4_5[i] + y8_5[i]*y8_5[i] + y12_5[i]*y12_5[i] + y16_5[i]*y16_5[i]);
      total_syst_plus_x[i] = TMath::Sqrt(y4_6[i]*y4_6[i] + y8_6[i]*y8_6[i] + y12_6[i]*y12_6[i] + y16_6[i]*y16_6[i]);
      cout << "x syst: " << i << " " << /*cross_section_x[i]*/total_syst_minus_x[i] << " " << /*cross_section_x[i]*/total_syst_plus_x[i] << endl;
    }
    gr_2nd[0] = new TGraphAsymmErrors(number_xbins, x_x, cross_section_x, x_err, x_err, cross_section_x_err, cross_section_x_err);
    gr_2nd[13] = new TGraphAsymmErrors(number_xbins, x_x, y_zero, x_err, x_err, y4_5, y4_6); //relative jet_et syst
    gr_2nd[14] = new TGraphAsymmErrors(number_xbins, x_x, y_zero, x_err, x_err, y8_5, y8_6); //relative phot_et syst
    gr_2nd[15] = new TGraphAsymmErrors(number_xbins, x_x, y_zero, x_err, x_err, y12_5, y12_6); //relative el_et syst
    gr_2nd[16] = new TGraphAsymmErrors(number_xbins, x_x, y_zero, x_err, x_err, y16_5, y16_6); //relative deltaZ syst
    gr_2nd[17] = new TGraphAsymmErrors(number_xbins, x_x, y_zero, x_err, x_err, total_syst_minus_x, total_syst_plus_x); //relative total syst
    gr_2nd[20] = new TGraphAsymmErrors(number_xbins, x_x, my4_5, x_err, x_err); //relative jet_et low
    gr_2nd[21] = new TGraphAsymmErrors(number_xbins, x_x, y4_6, x_err, x_err); //relative jet_et high
    gr_2nd[22] = new TGraphAsymmErrors(number_xbins, x_x, my8_5, x_err, x_err); //relative phot_et low
    gr_2nd[23] = new TGraphAsymmErrors(number_xbins, x_x, y8_6, x_err, x_err); //relative phot_et high
    gr_2nd[24] = new TGraphAsymmErrors(number_xbins, x_x, my12_5, x_err, x_err); //relative el_et low
    gr_2nd[25] = new TGraphAsymmErrors(number_xbins, x_x, y12_6, x_err, x_err); //relative el_et high
    gr_2nd[26] = new TGraphAsymmErrors(number_xbins, x_x, my16_5, x_err, x_err); //relative deltaZ low
    gr_2nd[27] = new TGraphAsymmErrors(number_xbins, x_x, y16_6, x_err, x_err); //relative deltaZ high
  }

  if(s_var[n] == "et_jet") {
    for(Int_t i=0; i<h_2nd[0]->GetNbinsX(); i++){
      cross_section_et_jet[i] = h_2nd[0]->GetBinContent(i+1);
      cross_section_et_jet_err[i] = h_2nd[0]->GetBinError(i+1);
      x_et_jet[i] = h_2nd[0]->GetBinCenter(i+1);
      total_syst_minus_et_jet[i] = TMath::Sqrt(y1_5[i]*y1_5[i] + y5_5[i]*y5_5[i] + y9_5[i]*y9_5[i] + y13_5[i]*y13_5[i]);
      total_syst_plus_et_jet[i] = TMath::Sqrt(y1_6[i]*y1_6[i] + y5_6[i]*y5_6[i] + y9_6[i]*y9_6[i] + y13_6[i]*y13_6[i]);
      cout << "et_jet syst: " << i << " " << /*cross_section_et_jet[i]*/total_syst_minus_et_jet[i] << " " << /*cross_section_et_jet[i]*/total_syst_plus_et_jet[i] << endl;
    }
    gr_2nd[0] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet, cross_section_et_jet, x_err, x_err, cross_section_et_jet_err, cross_section_et_jet_err);
    gr_2nd[13] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet, y_zero, x_err, x_err, y1_5, y1_6); //relative jet_et syst
    gr_2nd[14] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet, y_zero, x_err, x_err, y5_5, y5_6); //relative phot_et syst
    gr_2nd[15] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet, y_zero, x_err, x_err, y9_5, y9_6); //relative el_et syst
    gr_2nd[16] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet, y_zero, x_err, x_err, y13_5, y13_6); //relative deltaZ syst
    gr_2nd[17] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet, y_zero, x_err, x_err, total_syst_minus_et_jet, total_syst_plus_et_jet); //relative total syst
    gr_2nd[20] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet, my1_5, x_err, x_err); //relative jet_et low
    gr_2nd[21] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet, y1_6, x_err, x_err); //relative jet_et high
    gr_2nd[22] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet, my5_5, x_err, x_err); //relative phot_et low
    gr_2nd[23] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet, y5_6, x_err, x_err); //relative phot_et high
    gr_2nd[24] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet, my9_5, x_err, x_err); //relative el_et low
    gr_2nd[25] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet, y9_6, x_err, x_err); //relative el_et high
    gr_2nd[26] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet, my13_5, x_err, x_err); //relative deltaZ low
    gr_2nd[27] = new TGraphAsymmErrors(number_et_jetbins, x_et_jet, y13_6, x_err, x_err); //relative deltaZ high
  }
  if(s_var[n] == "eta_jet") {
    for(Int_t i=0; i<h_2nd[0]->GetNbinsX(); i++){
      cross_section_eta_jet[i] = h_2nd[0]->GetBinContent(i+1);
      cross_section_eta_jet_err[i] = h_2nd[0]->GetBinError(i+1);
      x_eta_jet[i] = h_2nd[0]->GetBinCenter(i+1);
      total_syst_minus_eta_jet[i] = TMath::Sqrt(y1_5[i]*y1_5[i] + y5_5[i]*y5_5[i] + y9_5[i]*y9_5[i] + y13_5[i]*y13_5[i]);
      total_syst_plus_eta_jet[i] = TMath::Sqrt(y1_6[i]*y1_6[i] + y5_6[i]*y5_6[i] + y9_6[i]*y9_6[i] + y13_6[i]*y13_6[i]);
      cout << "eta_jet syst: " << i << " " << /*cross_section_eta_jet[i]*/total_syst_minus_eta_jet[i] << " " << /*cross_section_eta_jet[i]*/total_syst_plus_eta_jet[i] << endl;
    }
    gr_2nd[0] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet, cross_section_eta_jet, x_err, x_err, cross_section_eta_jet_err, cross_section_eta_jet_err);
    gr_2nd[13] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet, y_zero, x_err, x_err, y1_5, y1_6); //relative jet_et syst
    gr_2nd[14] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet, y_zero, x_err, x_err, y5_5, y5_6); //relative phot_et syst
    gr_2nd[15] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet, y_zero, x_err, x_err, y9_5, y9_6); //relative el_et syst
    gr_2nd[16] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet, y_zero, x_err, x_err, y13_5, y13_6); //relative deltaZ syst
    gr_2nd[17] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet, y_zero, x_err, x_err, total_syst_minus_eta_jet, total_syst_plus_eta_jet); //relative total syst
    gr_2nd[20] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet, my1_5, x_err, x_err); //relative jet_et low
    gr_2nd[21] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet, y1_6, x_err, x_err); //relative jet_et high
    gr_2nd[22] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet, my5_5, x_err, x_err); //relative phot_et low
    gr_2nd[23] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet, y5_6, x_err, x_err); //relative phot_et high
    gr_2nd[24] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet, my9_5, x_err, x_err); //relative el_et low
    gr_2nd[25] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet, y9_6, x_err, x_err); //relative el_et high
    gr_2nd[26] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet, my13_5, x_err, x_err); //relative deltaZ low
    gr_2nd[27] = new TGraphAsymmErrors(number_eta_jetbins, x_eta_jet, y13_6, x_err, x_err); //relative deltaZ high
  }
  //0 - cross section value; 1 - stat. & fit parameter uncertainty; 2 - acceptance uncertainty
  //3 - lumi uncertainty; 4 - ratio (1); 5 - relative 1; 6 - relative 2; 7 - relative 3
  //8 - jet energy uncertainty; 9 - photon energy uncertainty; 10 - electron energy unc.
  //11 - deltaZ range uncertainty; 12 - 8+9+10+11 (in quadr); 13 - relative 8; 14 - relative 9
  //15 - relative 10; 16 - relative 11; 17 - relative 12
  //18 - syst+stat; 19 - relative 18
  //20, 21 - 8; 22, 23 - 9; 24, 25 - 10; 26, 27 - 11
  RelativeToAbsolute(gr_2nd[17], gr_2nd, gr_2nd[0]);
cout <<   gr_2nd[12]->GetN() << endl;;
  SystPlusStat(gr_2nd[12], gr_2nd[0], gr_2nd);

    gr_2nd[12]->SetFillColor(42);
    //    gr_2nd[12]->SetFillStyle(3454);
    //    gr_2nd[18]->SetLineColor(kBlue);  
    gr_2nd[18]->SetMarkerStyle(20);
    gr_2nd[18]->SetMarkerSize(1);
    //    gr_2nd[18]->SetMarkerColor(kBlue);

    gr_2nd[13]->SetMarkerColor(kBlue);
    gr_2nd[13]->SetFillColor(kBlue);
    gr_2nd[13]->SetFillStyle(3454);
    gr_2nd[20]->SetLineColor(kBlue);
    gr_2nd[21]->SetLineColor(kBlue);

    gr_2nd[14]->SetMarkerColor(kBlue);
    gr_2nd[14]->SetFillColor(kRed);
    gr_2nd[14]->SetFillStyle(3445);
    gr_2nd[22]->SetLineColor(kRed);
    gr_2nd[23]->SetLineColor(kRed);

    gr_2nd[15]->SetMarkerColor(kBlue);
    gr_2nd[15]->SetFillColor(kGreen);
    gr_2nd[15]->SetFillStyle(3425);
    gr_2nd[24]->SetLineColor(kGreen);
    gr_2nd[25]->SetLineColor(kGreen);

    gr_2nd[16]->SetMarkerColor(kBlue);
    gr_2nd[16]->SetFillColor(kYellow);
    gr_2nd[16]->SetFillStyle(3452);
    gr_2nd[26]->SetLineColor(kYellow);
    gr_2nd[27]->SetLineColor(kYellow);

    gr_2nd[17]->SetMarkerColor(kBlue);
    gr_2nd[17]->SetFillColor(kBlack);
    gr_2nd[17]->SetFillStyle(3445);
    //  gr_2nd[i][20]->SetLineColor(kBlue);
    //  gr_2nd[i][21]->SetLineColor(kBlue);


  /*  gr_2nd[8] = (TGraphAsymmErrors*)gr_2nd[0]->Clone();
  //  gr_2nd[8]->SetName(name + "_jet_et_syst_err");
  gr_2nd[9] = (TGraphAsymmErrors*)gr_2nd[0]->Clone();
  //  gr_2nd[9]->SetName(name + "_phot_et_syst_err");
  gr_2nd[10] = (TGraphAsymmErrors*)gr_2nd[0]->Clone();
  //gr_2nd[10]->SetName(name + "_el_et_syst_err");
  gr_2nd[11] = (TGraphAsymmErrors*)gr_2nd[0]->Clone();
  //gr_2nd[11]->SetName(name + "_dz_syst_err");
  gr_2nd[12] = (TGraphAsymmErrors*)gr_2nd[0]->Clone();
  //gr_2nd[12]->SetName(name + "_total_syst_err");
  //ratios
  gr_2nd[13] = (TGraphAsymmErrors*)gr_2nd[0]->Clone();
  //gr_2nd[13]->SetName(name + "_jet_et_syst_err_ratio");
  gr_2nd[14] = (TGraphAsymmErrors*)gr_2nd[0]->Clone();
  //gr_2nd[14]->SetName(name + "_phot_et_syst_err_ratio");
  gr_2nd[15] = (TGraphAsymmErrors*)gr_2nd[0]->Clone();
  //gr_2nd[15]->SetName(name + "_el_et_syst_err_ratio");
  gr_2nd[16] = (TGraphAsymmErrors*)gr_2nd[0]->Clone();
  //gr_2nd[16]->SetName(name + "_dz_syst_err_ratio");
  gr_2nd[17] = (TGraphAsymmErrors*)gr_2nd[0]->Clone();
  //gr_2nd[17]->SetName(name + "_total_syst_err_ratio");

  //total uncertainty
  gr_2nd[18] = (TGraphAsymmErrors*)gr_2nd[0]->Clone();
  //gr_2nd[18]->SetName(name + "_total_err");
  gr_2nd[19] = (TGraphAsymmErrors*)gr_2nd[0]->Clone();
  //gr_2nd[19]->SetName(name + "_total_err_ratio");
  */


  /*  cout << "Entering hist_compare1st2nd.c" << endl;
  h_1st[0] = (TH1D*)h_2nd[0]->Clone();
  h_1st[0]->SetName(h_2nd[0]->GetName() + TString("_1st_analysis"));
  
  h_1st[4] = (TH1D*)h_2nd[4]->Clone();
  h_1st[4]->SetName(h_2nd[4]->GetName() + TString("_1st_analysis"));

  if(s_var[n] == "et") {

    h_1st[0]->SetBinContent(1, 1.98219);
    h_1st[0]->SetBinError(1, 0.177986);
    h_1st[0]->SetBinContent(2, 1.05604);
    h_1st[0]->SetBinError(2, 0.102235);
    h_1st[0]->SetBinContent(3, 0.471539);
    h_1st[0]->SetBinError(3, 0.0747391);
    h_1st[0]->SetBinContent(4, 0.181919);
    h_1st[0]->SetBinError(4, 0.026227);
  }
  if(s_var[n] == "eta") {
    h_1st[0]->SetBinContent(1, 4.24056);
    h_1st[0]->SetBinError(1, 0.569197);
    h_1st[0]->SetBinContent(2, 5.19166);
    h_1st[0]->SetBinError(2, 0.517889);
    h_1st[0]->SetBinContent(3, 4.97616);
    h_1st[0]->SetBinError(3, 0.534486);
    h_1st[0]->SetBinContent(4, 4.99691);
    h_1st[0]->SetBinError(4, 0.525977);
  }
  if(s_var[n] == "Q2") {
    h_1st[0]->SetBinContent(1, 0.171572);
    h_1st[0]->SetBinError(1, 0.0106341);
    h_1st[0]->SetBinContent(2, 0.0378808);
    h_1st[0]->SetBinError(2, 0.00514758);
    h_1st[0]->SetBinContent(3, 0.0147135);
    h_1st[0]->SetBinError(3, 0.00217574);
    h_1st[0]->SetBinContent(4, 0.0016933);
    h_1st[0]->SetBinError(4, 0.000631156);
    //    h_1st[0]->SetBinContent(5, );
    //    h_1st[0]->SetBinError(5, );
  }
  if(s_var[n] == "x") {
    h_1st[0]->SetBinContent(1, 4322.44);
    h_1st[0]->SetBinError(1, 333.187);
    h_1st[0]->SetBinContent(2, 1369.93);
    h_1st[0]->SetBinError(2, 137.845);
    h_1st[0]->SetBinContent(3, 156.295);
    h_1st[0]->SetBinError(3, 32.6035);
    h_1st[0]->SetBinContent(4, 19.0949);
    h_1st[0]->SetBinError(4, 7.27503);
  }
  for(Int_t i=0; i<h_1st[0]->GetNbinsX(); i++) {
    Double_t ratio = h_1st[0]->GetBinContent(i+1) / h_2nd[0]->GetBinContent(i+1);
    Double_t e1 = h_1st[0]->GetBinError(i+1) / h_2nd[0]->GetBinContent(i+1);
    Double_t e2 = h_1st[0]->GetBinContent(i+1) * h_2nd[0]->GetBinError(i+1) / 
      TMath::Power(h_2nd[0]->GetBinContent(i+1), 2.);
    Double_t err = TMath::Sqrt(e1*e1 + e2*e2);
    h_1st[4]->SetBinContent(i+1, 1 - ratio);
    h_1st[4]->SetBinError(i+1, err);
    cout << i << ", ratio 1st/2nd = " << ratio << " +- " << err << endl;
  }
  cout << "exiting hist_compare1st2nd.c" << endl;
*/
    cout << "exiting Hist::SetSystematicErrors" << endl;
}


void Hist::RelativeToAbsolute(TGraphAsymmErrors* rel, TGraphAsymmErrors** abs, TGraphAsymmErrors* cross)
{
  Double_t *px, x[100] = {0.};
  Double_t *py, y[100] = {0.};
  Double_t x_err[100] = {0.};
  Double_t *py_err_plus, y_err_plus[100] = {0.};
  Double_t *py_err_minus, y_err_minus[100] = {0.};
  Int_t n = rel->GetN();
  px = rel->GetX();
  py = cross->GetY();
  py_err_plus = rel->GetEYhigh();
  py_err_minus = rel->GetEYlow();

  for(Int_t i=0; i<n; i++) {
    y_err_plus[i] = py_err_plus[i]*py[i];
    y_err_minus[i] = py_err_minus[i]*py[i];
    x[i] = px[i];
    y[i] = py[i];
    //    y_err_plus[i] = py_err_plus[i];
    //    y_err_minus[i] = py_err_minus[i];
    cout << "bin i " << x[i] << " " << y[i] << " " << y_err_plus[i] << " " << y_err_minus[i] << endl;
  }

  abs[12] = new TGraphAsymmErrors(n, x, y, x_err, x_err, y_err_minus, y_err_plus);
    cout << "get ylow" << endl << abs[12]->GetN() << endl;
}

void Hist::SystPlusStat(TGraphAsymmErrors* syst_abs, TGraphAsymmErrors* stat_abs, TGraphAsymmErrors** tot)
{
  cout << "goto in" << endl;
  Double_t *x;
  x = syst_abs->GetX();
  Double_t *y;
  y = syst_abs->GetY();
  Double_t x_err[100] = {0.};
  
  Double_t *syst_eplus;// = new Double_t;
  cout << "goto in geteyhigh" << endl;
  syst_eplus = (Double_t*)stat_abs->GetEYhigh();
  cout << "goto in 2" << endl;

  Double_t *syst_eminus;
  syst_eminus = syst_abs->GetEYlow();
  Double_t *stat_eplus;
  stat_eplus = stat_abs->GetEYhigh();
  Double_t *stat_eminus;
  stat_eminus = stat_abs->GetEYlow();

  Double_t tot_eminus[100] = {0.};
  Double_t tot_eplus[100] = {0.};
  Double_t tot_eminus_rel[100] = {0.};
  Double_t tot_eplus_rel[100] = {0.};

  Int_t n = stat_abs->GetN();
  for(Int_t i=0; i<n; i++)
    {
      tot_eminus[i] = TMath::Sqrt(syst_eminus[i]*syst_eminus[i] + stat_eminus[i]*stat_eminus[i]);
      tot_eplus[i] = TMath::Sqrt(syst_eplus[i]*syst_eplus[i] + stat_eplus[i]*stat_eplus[i]);
      tot_eminus_rel[i] = tot_eminus[i]/y[i];
      tot_eplus_rel[i] = tot_eplus[i]/y[i];
      cout << "total " << i << " " << x[i] << " " << y[i] << " " << tot_eminus[i] << " " << tot_eplus[i] << " " << tot_eminus_rel[i] << " " << tot_eplus_rel[i] << endl;
    }
  cout << "here" << endl;
  tot[18] = new TGraphAsymmErrors(n, x, y, x_err, x_err, tot_eminus, tot_eplus);
  tot[19] = new TGraphAsymmErrors(n, x, y, x_err, x_err, tot_eminus_rel, tot_eplus_rel);
  cout << "SystPlusStat done successfully" << endl;
}
