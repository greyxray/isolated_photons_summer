#include <TCanvas.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TGraphAsymmErrors.h>
#include <TPaveText.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TDirectory.h>
#include "TMultiGraph.h"
#include <iostream>
using std::cout;
using std::endl;

//#include "../inc/constants.h"
//Double_t * all_bins[12] = {et_bin, eta_bin_crosssec, Q2_bin, x_bin, et_jet_bin, eta_jet_bin, \
//                            xgamma_bin, xp_bin, dphi_bin, deta_bin, dphi_e_ph_bin, deta_e_ph_bin};

class CrossectionDrawer
{
public:
    CrossectionDrawer(int i, TVirtualPad * p, TH1 * data, TH1 * data_tot_err, TH1 * sum, TH1 * qq, TH1 * ll, TCanvas * canvas, TString name, Double_t * a);
    //void DrawLegend(bool t, bool with_BLZ, TGraphAsymmErrors * fTGraphTheoryFont, TString FontName) const;
    void DrawLegend(bool t, int i, bool with_BLZ, 
                            bool with_Font, TGraphAsymmErrors* fTGraphTheoryFont, TString FontName, 
                            bool with_Font2, TGraphAsymmErrors* fTGraphTheoryFont2, TString FontName2) const;
    void DrawHist(bool nottheory, bool with_BLZ) const;
    void SaveCanvas(bool t, bool nottheory) const;
    void SetPad(TCanvas * c, TVirtualPad * pad);
    void AssighnTheory(Double_t * cs , Double_t * cs_pos , Double_t * cs_neg , int num);
    // ~CrossectionDrawer();
    static void DrawAll(TH1 ** data, TH1 ** data_tot_err, TH1 ** fit, TH1 ** qq, TH1 ** ll, Double_t * all_bins[12], TString s_var[12], int nplots,\
                                 bool with_BLZ, 
                                    Double_t * all_theory_cs_BLZ[12], Double_t * all_theory_cs_BLZ_pos[12], Double_t * all_theory_cs_BLZ_neg[12], TString theory_name_BLZ,\
                                 bool withFontannaz, 
                                    Double_t * all_theory_cs_font[12], Double_t * all_theory_cs_font_pos[12], Double_t * all_theory_cs_font_neg[12], TString theory_name_Font1,
                                 bool two_fontannaz,//frst 0.5 cut second 2.5
                                    Double_t * all_theory_cs_font_25[12], Double_t * all_theory_cs_font_pos_25[12], Double_t * all_theory_cs_font_neg_25[12], TString theory_name_Font2);
    static int m;//how many pic per plot
    static int n;//how many columns
    static bool for_paper;//to insert in latex
private:
    void AdjustPad();
    void SetFigure3Style(TH1* h_data, TH1* h_qq_ll, TH1* h_qq, TH1* h_ll, TH1* h_bg);
    Double_t GetYmax(bool nottheory) const;
    TGraphAsymmErrors * GetErrors() const;
    // TString current_position = "right up";
    enum LegendPosition{kRightUp, kRightDown, kLeftUp, kLeftDown};
    TH1 * fCSdata;
    TH1 * fCSdata_tot_err;
    TH1 * fMCsum;
    TH1 * fMCqq;
    TH1 * fMCll;
    TCanvas * fCanvas;// = new TCanvas(canvas_name, binsof, 800, 600); и номер пада 

    TGraphAsymmErrors * fTGraphTheory;


    TH2D   * fWindowControl;
    TGraphAsymmErrors * fAsymmError;// = new TGraphAsymmErrors(n,x,y,exl,exh,eyl,eyh);

    // TString binsof("bins of "+ fVariablesFullNames[i]);
    TString fVariableName;//(fVariablesFullNames[i]);
    int fIndex;
    TVirtualPad  * fPad;

    Double_t * all_bins;
    // Double_t x1, x2, y1, y2;
    TString theory_name;
};

int CrossectionDrawer::m = 1;
int CrossectionDrawer::n = 1;
bool CrossectionDrawer::for_paper = false;

void CrossectionDrawer::SetFigure3Style(TH1* h_data, TH1* h_qq_ll, TH1* h_qq, TH1* h_ll, TH1* h_bg)
{
    h_data->SetLineColor(kBlack);
    h_data->SetLineWidth(3);
    h_qq_ll->SetLineColor(kRed);
    h_qq->SetLineColor(kBlack);
    h_qq->SetLineStyle(7);
    h_ll->SetLineColor(kBlue);
    h_ll->SetLineStyle(3);

    h_ll->SetFillColor(0);//kYellow
    h_ll->SetFillStyle(0);  
    h_data->SetFillColor(0);//kYellow
    h_data->SetFillStyle(0);    
    h_qq_ll->SetFillColor(0);//kYellow
    h_qq_ll->SetFillStyle(0);   
    h_qq->SetFillColor(0);//kYellow
    h_qq->SetFillStyle(0);  
}

CrossectionDrawer::CrossectionDrawer(int i, TVirtualPad * p, TH1 * data, TH1 * data_tot_err, TH1 * sum, TH1 * qq, TH1 * ll, TCanvas * canvas, TString name, Double_t * al_bins):
fIndex(i),
fPad(p),
fCSdata(data),
//fCSdata_tot_err(data_tot_err),
fMCsum(sum),
fMCqq(qq),
fMCll(ll),
fVariableName(name),
fCanvas(canvas),
fWindowControl(0),
fAsymmError(0),
fTGraphTheory(0),
all_bins(al_bins),
theory_name("BLZ")
{
    SetFigure3Style(fCSdata, fMCsum, fMCqq, fMCll, 0);
    fCSdata_tot_err = (TH1*)data_tot_err->Clone();
    /* Wrong error propagation & approach
    for(int j = 1; j <= fCSdata->GetNbinsX(); j++)
    {
        fCSdata->SetBinContent(j, fCSdata->GetBinContent(j) * all_hadcort[i][j-1]);
        fCSdata_tot_err->SetBinContent(j, fCSdata_tot_err->GetBinContent(j) * all_hadcort[i][j-1]);
    }
    */
    int number_bins = fCSdata->GetNbinsX();
    Int_t dummy_variable = !fVariableName.Contains("xgamma") ? 1000 : 10000;
    TString str_title = "";
        fWindowControl = new TH2D("h_window_fig3_" + fVariableName, str_title, number_bins, all_bins[0], all_bins[number_bins], dummy_variable, -0.0001, GetYmax(true));
        fAsymmError = GetErrors();

    cout << "Constructor reached  here 1" << endl;
    AdjustPad();
    cout << "Constructor reached  here 2" << endl;
    fWindowControl->GetYaxis()->SetRangeUser(-0.0001, GetYmax(true));
    fPad->Update();
    fWindowControl->Draw();

 
    fMCqq->SetLineWidth(3);
    fMCll->SetLineWidth(3);
    fMCsum->SetLineWidth(3);
}

Double_t CrossectionDrawer::GetYmax(bool nottheory = true) const
{
    Double_t ymax;
    if (nottheory) ymax = fCSdata->GetMaximum() > fMCsum->GetMaximum() ? fCSdata->GetMaximum() : fMCsum->GetMaximum();
    else ymax = TMath::MaxElement(fCSdata->GetNbinsX(), fAsymmError->GetY()) > TMath::MaxElement(fCSdata->GetNbinsX(), fTGraphTheory->GetY()) ? TMath::MaxElement(fCSdata->GetNbinsX(), fAsymmError->GetY()) : TMath::MaxElement(fCSdata->GetNbinsX(), fTGraphTheory->GetY());
    
    ymax = 1.2 * ymax;
    if ( logY_for_xgamma_xp && fVariableName.Contains("xgamma") ) ymax = ymax * 5;
    if ( logY_for_xgamma_xp && fVariableName.Contains("xp") )     ymax = ymax * 2;
    if ( fVariableName.Contains("deta") || fVariableName.Contains("dphi")/*&& !fVariableName.Contains("_e_ph")*/ ) ymax = ymax * 1.2; // extra space for deta
    if ( fVariableName.Contains("dphi") && !q2_cut_global.Contains("_q2_") && !nottheory && !fVariableName.Contains("_e_ph")) ymax = ymax * 1.2;
    return ymax;
}

void CrossectionDrawer::DrawLegend(bool draw, int i, bool with_BLZ = false, 
                                              bool with_Font = false, TGraphAsymmErrors* fTGraphTheoryFont = 0, TString FontName="Fontannaz1", 
                                              bool with_Font2 = false, TGraphAsymmErrors* fTGraphTheoryFont2 = 0, TString FontName2="Fontannaz2" ) const
{
    if (!draw)  return;// //PLOTS
    dout("DrawLegend!", i);
    LegendPosition current_position = kRightUp;

    if (fVariableName.Contains("xgamma") || fVariableName.Contains("dphi"))   current_position = kLeftUp;

    Double_t x1, x2, y1, y2;

    bool is_left = current_position == kLeftUp || current_position == kLeftDown;
    bool is_down = current_position == kRightDown || current_position == kLeftDown;

    x1 = is_left ? 0.21 : 0.55;//0.15  0.45
    x2 = is_left ? 0.60 : 0.98;//0.60 : 0.86
    y1 = is_down ? 0.10 : 0.50;//0.5
    y2 = is_down ? 0.45 : 0.88;//0.88
    if (m == 6)
    {
        if ((fVariableName.Contains("dphi") && !fVariableName.Contains("dphi_e_ph"))) 
        {   
            y1 =  0.40;//0.5
            y2 = 0.83;//0.88
        }
        else if( fVariableName.Contains("xgamma") || fVariableName.Contains("xp") )
        {
            y1 = 0.50;//0.5
            y2 = 0.82;//0.88
            x2 = 0.68;
            if (q2_cut_global.Contains("t"))
            {
                x2 = 0.92;
            }
        }
        else
        {
            y1 = 0.6;// 0.55
            y2 = 0.9;
        } 
    }
    else if (m == 1)
    {
        y1 = 0.6;// 0.55
        y2 = 0.9;

        if (fVariableName.Contains("xp") ) 
        {
            x1 = 0.45; x2 = 0.9; // good at least for split region
        }
        else if (fVariableName.Contains("xgamma") )
        {
            if (q2_cut_global.Contains("_q2_"))
            {
                if (!(with_BLZ|| with_Font))// add the legent entries Fig.3 Fig.4 Fig.5
                {
                               x2 = 0.7;
                    //y1 = 0.65; y2 = 0.97;
                }
            }
            else
            {
                if (!(with_BLZ|| with_Font))// add the legent entries Fig.3 Fig.4 Fig.5
                {
                    x2 =0.5;
                }
            }
        }
        else if (fVariableName.Contains("deta_e_ph") ) 
        {
            if (with_BLZ)
            {
                x1 = 0.35; x2 = 0.8;
                y1 = 0.20; y2 = 0.5;
            }
            else // data
            {
                x1 = 0.21; x2 = 0.8; //0.5;
                y1 = 0.65; y2 = 0.97;
            }
            // else if (! q2_cut_global.Contains("lt_30")) // full q2 and q2>30
            // {
            //     x1 = 0.21; x2 = 0.7; //0.5;
            //     y1 = 0.65; y2 = 0.93;
            // }
            // else // q2<30
            // {
            //     x1 = 0.5;//0.63; 
            //     x2 = 0.9;
            //     y1 = 0.63; y2 = 0.91;
            // }
        }
        else if (fVariableName.Contains("deta") ) 
        {
            if (with_BLZ)
            {
                x1 = 0.42; x2 = 0.95;
                y1 = 0.20; y2 = 0.5;
            }
            else if (!q2_cut_global.Contains("_q2_"))
            {
                x1 = 0.21; x2 = 0.5;
                y1 = 0.65; y2 = 0.93;
            }
            else // full q2
            {
                x1 = 0.21; x2 = 0.5;
                y1 = 0.68; y2 = 0.92;

                 x2 = 0.7;//0.6;
                 y1 = 0.67;
                 if (!fVariableName.Contains("deta_e_ph") )  x2 = 0.7;
                 // if (q2_cut_global.Contains("gt_30"))
                 // {
                 //    x2 = 0.55;
                 // }

            }
        }
        else if (fVariableName.Contains("dphi"))
        {
                if (!(with_BLZ|| with_Font))
                {
                               x2 = 0.7;
                    y1 = 0.65; y2 = 0.97;
                }
        } 

        // control the leg size for theory plots
            if (with_BLZ || with_Font) 
            {
                y1 = 0.7; // Smaller legend for the theory
                if (q2_cut_global.Contains("t")) x2 = 0.7; // For fig.7 more space for legend
            }
    }

    TLegend *leg = new TLegend(x1, y1, x2, y2);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);  

    // add the legent entries Fig.3 Fig.4 Fig.5
        if (!(with_BLZ || with_Font))           
        {
            if (q2_cut_global.Contains("gt_30")) leg->AddEntry(fAsymmError, "ZEUS 326 pb^{-1}" + prel + ", 30<Q^{2}<350 GeV^{2}", "p"); 
            else if (q2_cut_global.Contains("lt_30")) leg->AddEntry(fAsymmError, "ZEUS 326 pb^{-1}" + prel + ", 10<Q^{2}<30 GeV^{2} ", "p"); 
            else leg->AddEntry(fAsymmError, "ZEUS 326 pb^{-1}" + prel, "p"); // no need for lable where Q2 is full
            
            if ((q2_cut_global.Contains("_q2_") && (i == 9 || i == 6)) ||
            (!q2_cut_global.Contains("t") && ( i == 6)) ) //deta xgamma have full legends for split Q2 region, xgamma only for full q2 region
            {
                leg->AddEntry(fMCqq,  "QQ*1.6, MC", "l"); 
                leg->AddEntry(fMCll,  "LL, MC", "l");
                leg->AddEntry(fMCsum, "LL + QQ*1.6, MC", "l");  
            }      
        }
        else
        {
            if (q2_cut_global.Contains("gt_30")) leg->AddEntry(fAsymmError, "ZEUS 326 pb^{-1}" + prel + ", 30<Q^{2}<350 GeV^{2}", "p"); 
            else if (q2_cut_global.Contains("lt_30")) leg->AddEntry(fAsymmError, "ZEUS 326 pb^{-1}" + prel + ", 10<Q^{2}<30 GeV^{2} ", "p"); 
            else leg->AddEntry(fAsymmError, "ZEUS 326 pb^{-1}" + prel, "p"); 

            if (with_BLZ)
            {
                leg->AddEntry(fTGraphTheory, theory_name, "f"); // BLZ

                // if (fVariableName.Contains("xgamma"))
                // {
                //     for(int i = 1; i <= fCSdata->GetNbinsX(); i++)
                //     {
                //         dout("cs plotted ", i, ":", fAsymmError->Eval(fCSdata->GetBinCenter(i)), "theory:", fTGraphTheory->Eval(fCSdata->GetBinCenter(i)));
                //     }
                // }
            }
            if (with_Font)
            {
                if (fTGraphTheoryFont != 0)
                {
                    dout(FontName);
                    leg->AddEntry(fTGraphTheoryFont, FontName, "f");
                }
                if(with_Font2)
                {
                    if (fTGraphTheoryFont2 != 0)
                    {
                        dout(FontName2);
                        leg->AddEntry(fTGraphTheoryFont2, FontName2, "f");
                    }
                }
            }
        }
        //if (!(m==1 && fVariableName.Contains("deta"))) 
    
    leg->Draw();
}

void CrossectionDrawer::DrawHist(bool nottheory = true, bool with_BLZ = false) const
{
    TString title("cs, " + fVariableName);
    gStyle->SetOptStat(0);
    if (nottheory)
    {
        fMCll->Draw("HIST F  SAME");// PLOTS E1
        fMCqq->Draw("HIST F E1 SAME");
        fMCsum->Draw("HIST F  SAME");
        //fAsymmError->Draw("SAME P ");
    }
    else if (with_BLZ)
    {

        fPad->Update();
        //fWindowControl->GetXaxis()->SetTitle("vasia");
        sign_window(fPad, fWindowControl, cs_x_names[fIndex] , cs_y_names[fIndex],  "", "large");
        fWindowControl->Draw("");

        /*
         TMultiGraph *mg = new TMultiGraph();
         mg->SetTitle("Exclusion graphs");
          TGraphAsymmErrors *gr1 = fAsymmError;
           gr1->SetLineColor(2);
           gr1->SetLineWidth(1504);
           gr1->SetFillStyle(3005);
           TGraphAsymmErrors *gr2 = fTGraphTheory;
           gr2->SetLineColor(4);
           gr2->SetLineWidth(-2002);
           gr2->SetFillStyle(3004);
           gr2->SetFillColor(9);
            mg->Add(gr1);
           mg->Add(gr2);
           mg->Draw("SAME 3");
        */

        fTGraphTheory->SetLineColor(kOrange +7);// kBlack
        fTGraphTheory->SetLineWidth(1);
        fTGraphTheory->SetFillStyle(1001);//1001            // 3003
        fTGraphTheory->SetFillColor(kOrange - 4);//kOrange-4      // kBlue
        fTGraphTheory->SetMarkerStyle(1);
        //fTGraphTheory->SetFillStyle(3001);

        fAsymmError->SetLineColor(kBlack);
        fAsymmError->SetLineWidth(3);
        fAsymmError->SetFillStyle(3002);
        fAsymmError->SetFillColor(2);

        // fAsymmError->Draw("SAME 2");
        // fTGraphTheory->GetXaxis()->SetTitle("vasia");
        fTGraphTheory->Draw("SAME 5");// box 

        //fAsymmError->Draw("SAME P E");
        //fTGraphTheory->Draw("SAME P ");
    }
    else 
    {
        fPad->Update();
        fWindowControl->Draw("");
    }

    // For AFG comparison we compare to qq+ ll:
        // dout("drawing data with ll");
        // TH1 * fCSdata_tot_err_clone = (TH1 *)fCSdata_tot_err->Clone(); 
        // dout("\tCSdata_tot_err_clone before anything");
        // for(int j = 0; j < fCSdata_tot_err_clone->GetNbinsX(); ++j){
        //         cout << fCSdata_tot_err_clone->GetBinContent(j+1)<<"+-" << fCSdata_tot_err_clone->GetBinError(j+1) <<  ", ";
        //     }
        // dout();
        // fCSdata_tot_err_clone->Add(fMCll);
        // dout("\tCSdata_tot_err_clone after addinf ll");
        // for(int j = 0; j < fCSdata_tot_err_clone->GetNbinsX(); ++j){
        //         cout << fCSdata_tot_err_clone->GetBinContent(j+1)<<"+-" << fCSdata_tot_err_clone->GetBinError(j+1) <<  ", ";
        //     }
        // dout();
        // dout("\tsetting the errors");
        // for(int j = 0; j < fCSdata_tot_err_clone->GetNbinsX(); ++j){
        //         fCSdata_tot_err_clone->SetBinError(j+1, TMath::Sqrt(pow(fCSdata_tot_err_clone->GetBinError(j+1),2) + pow(fMCll->GetBinError(j+1),2)));
        //         cout << fCSdata_tot_err_clone->GetBinContent(j+1)<<"+-" << fCSdata_tot_err_clone->GetBinError(j+1) <<  ", ";
        //     }
        // dout();
        // TH1 * fCSdata_clone = (TH1 *)fCSdata->Clone();
        // fCSdata_clone->Add(fMCll);
        //  fCSdata_tot_err_clone->SetLineWidth(2);
        // fCSdata_tot_err_clone->SetLineColor(kBlue);
        // fCSdata_tot_err_clone->Draw("SAME P E X0");// Assymetric
        // fCSdata_clone->SetLineColor(kBlue);
        // fCSdata_clone->SetMarkerColor(kBlue);
        // fCSdata_clone->SetMarkerSize(1);
        // fCSdata_clone->SetMarkerStyle(20);
        // fCSdata_clone->Draw("SAME P E1 X0");

    // Otherwise only qq
        dout("drawing data");
        fCSdata_tot_err->SetLineWidth(2);
        fCSdata_tot_err->Draw("SAME P E X0");// Assymetric
        fCSdata->SetMarkerSize(1);
        fCSdata->SetMarkerStyle(20);
        fCSdata->Draw("SAME P E1 X0");

   


    const Int_t nn = fCSdata->GetNbinsX();
    Double_t x[nn];
    Double_t y[nn];
    Double_t exl[nn] ;
    Double_t exh[nn] ;
    Double_t eyl[nn];
    Double_t eyh[nn];
    for(int j = 0; j < fCSdata->GetNbinsX(); ++j)
    {
        x[j] = fCSdata->GetBinCenter(j + 1);// + fCSdata->GetBinWidth(j + 1)*0.25 ;
        y[j] = fCSdata->GetBinContent(j + 1);
        exl[j] = 0;
        exh[j] = 0;
        eyl[j] = fCSdata->GetBinError(j + 1);//fCSdata->GetBinError(j + 1);//statistical - not statistical and acceptance
        eyh[j] = fCSdata->GetBinError(j + 1);
    }

    TGraphAsymmErrors * graph = new TGraphAsymmErrors(nn, x, y, exl, exh, eyl, eyh);
    graph->SetMarkerColor(1);
    graph->SetMarkerSize(1.3);//1.1
    graph->SetMarkerStyle(20);
    graph->SetLineWidth(3);
    //graph-> Draw("SAME E1");
    //fCSdata->Draw("P E SAME");

    fPad->RedrawAxis();
}

void CrossectionDrawer::SaveCanvas(bool draw, bool nottheory=true) const
{
    if ( !draw ) return;
    //fCanvas->Print(TString("separate_per_") + fCanvas->GetName() + TString(".eps") );

    //TPaveText t;
    //t.SetOption(Option_t* option = "NDC");
    TString outname = "separate_";
    TString canvas_name = "";
    if (!nottheory) outname = "theory_";

    if (m == 2)
    {
        //TPaveText t(-0.3, 0.87, 0.3, 1.03, "NDC"); //-0.228, 0.89, 0.2, 1.03,
        TPaveText t(-0.228, 0.89, 0.2, 1.03, "NDC"); //
        if (!q2_cut_global.Contains("gt") && !q2_cut_global.Contains("_q2_"))
        {
            t.SetX1NDC(-0.228);
            t.SetX2NDC(0.2);
            t.SetY1NDC(0.89);
            t.SetY2NDC(1.03);
        }
        t.SetFillStyle(0);
        t.SetTextAlign(22);//center bottom
        /*t.SetX1(-0.228);
        t.SetX2(0.2);
        t.SetY1(0.90);
        t.SetY2(1.03);*/
        t.AddText("ZEUS 326 pb^{-1}" + prel);
        t.SetFillColor(0);
        t.SetBorderSize(0);
        if (false) t.Draw(); // big ZUES lable on top
        canvas_name = outname + "per_2_plots_of_" + Form("%d",n) + "_width_" + fCanvas->GetName() + q2_cut_global + TString(".png") ;
        fCanvas->Print(canvas_name);
        dout("cs saved canvas: ", canvas_name);
    }
    
    if(m == 1)
    {

        TString the_title = q2_cut_global.Contains("lt_30") ? "10<Q^{2}<30 GeV^{2} " : "ZEUS 326 pb^{-1}" + prel;
                the_title = q2_cut_global.Contains("gt_30") ? "30<Q^2<350 GeV^{2}" : the_title;
        Double_t x1(0), y1(0), x2(1), y2(1), t_size(0.1);
        if (q2_cut_global.Contains("30"))
        {
            x1 = 0.4; y1 = 0.93; x2 = 0.6; y2 = 1.0; t_size = 0.07;
        }
        else
        {
            x1 = 0.4; y1 = 0.93; x2 = 0.6; y2 = 1.0; t_size = 0.07;
        }
        TPaveText t(x1, y1, x2, y2, "NDC"); // left-up
        t.SetTextSize(t_size);
        t.SetFillStyle(0);//0 - transparent 3001 - dashed
        t.SetTextAlign(22);//center bottom
            //t.SetX1(0.4);
            //t.SetX2(0.6);
            //t.SetY1(0.90);
            //t.SetY2(1.03);
        t.AddText(the_title);
        t.SetFillColor(0);
        t.SetBorderSize(0);
        //if (!for_paper) 
        
        if (false) t.Draw(); // big ZEUS 326 pb^{-1} something lable on top
        canvas_name = outname + "per_1_plot_" + Form("%d",n) + "_width_"  + fVariableName + q2_cut_global + TString(".png") ;
        fCanvas->Print(canvas_name);// here we can simply name with variablename
        dout("cs saved canvas:: ", canvas_name);
    }

    if(m == 6)
    {
        //TPaveText t(-0.228, 3.01, 0.2, 3.2, "NDC"); // left-up
        TPaveText t(-0.38, 2.96, 0.37, 3.21, "NDC");//-0.42, 2.96, 0.4, 3.21,
        if ( n == 3)
        {
            t.SetX1( -0.9);
            t.SetX2( -0.2);
            t.SetY1( 1.9);
            t.SetY2( 2.1);
            /* 
            t.SetX1NDC( -0.38);
            t.SetX2NDC( 0.37);
            t.SetY1NDC( 1.96);
            t.SetY2NDC( 2.21); */    
        } 

        t.SetFillStyle(0);
        t.SetTextAlign(22);//center bottom
        /*t.SetX1(0.4);
        t.SetX2(0.6);
        t.SetY1(0.90);
        t.SetY2(1.03);*/
        TString add_data_leg = q2_cut_global.Contains("lt_30") ? "ZEUS 326 pb^{-1}, 10<Q^{2}<30 GeV^{2} " : "ZEUS 326 pb^{-1}" + prel;
                add_data_leg = q2_cut_global.Contains("gt_30") ? "ZEUS 326 pb^{-1}, 30<Q^2<350 GeV^{2}" : add_data_leg;
        t.AddText(add_data_leg);
        t.SetFillColor(0);
        t.SetBorderSize(0);
        Float_t textsize = t.GetTextSize();
        dout("text size:", textsize);
        //void SetTextSize(Float_t tsize = 1)
        if (false) t.Draw(); // big ZEUS lable on top
        canvas_name = outname + "per_6_plots_" + Form("%d", n) + "_width_"  + fCanvas->GetName() + q2_cut_global + TString(".png") ;
        fCanvas->Print(canvas_name);
        dout("saved canvas: ", canvas_name);
    }
    
    //TH1F * frame = fCanvas->DrawFrame(-1., 0., 2., 2.,"ZEUS");
   
    //fCanvas->Print(TString("separate_per_") + fCanvas->GetName() + TString(".png") );
}

TGraphAsymmErrors * CrossectionDrawer::GetErrors() const
{
    const Int_t nn = fCSdata->GetNbinsX();
    Double_t x[nn];
    Double_t y[nn];
    Double_t exl[nn] ;
    Double_t exh[nn] ;
    Double_t eyl[nn];
    Double_t eyh[nn];
    for(int j = 0; j < fCSdata->GetNbinsX(); ++j)
    {
        x[j] = fCSdata->GetBinCenter(j + 1) ;
        y[j] = fCSdata->GetBinContent(j + 1);
        exl[j] = 0;
        exh[j] = 0;
        fCSdata_tot_err->SetBinError(j+1, TMath::Sqrt(pow(all_syst[fIndex][j], 2) + pow(fCSdata_tot_err->GetBinError(j + 1), 2) ));
        eyl[j] = TMath::Sqrt(pow(all_syst[fIndex][j], 2) + pow(fCSdata_tot_err->GetBinError(j + 1), 2) );//fCSdata->GetBinError(j + 1);//statistical - not statistical and acceptance
        eyh[j] = TMath::Sqrt(pow(all_syst[fIndex][j], 2) + pow(fCSdata_tot_err->GetBinError(j + 1), 2) );
    }

    TGraphAsymmErrors * graph = new TGraphAsymmErrors(nn, x, y, exl, exh, eyl, eyh);
    graph->SetMarkerColor(1);
    graph->SetMarkerSize(1.3);//1.1
    graph->SetMarkerStyle(20);
    graph->SetLineWidth(1);
       //graph->SetMarkerSize(5);
    return graph;
}

void CrossectionDrawer::AdjustPad()
{
    if (!fPad) 
    {
        cout << "ERROR: in CrossectionDrawer::AdjustPad fPad is zero" << endl;
        return;
    }

    if (logY_for_xgamma_xp && (fVariableName.Contains("xp") || fVariableName.Contains("gamma"))) fPad->SetLogy();

    fPad->SetFrameBorderMode(0);
    fPad->SetTicks(1,1);
    fPad->SetBorderMode(0);
    fPad->SetFillColor(kWhite);
    fPad->SetGrid(0, 0);
    sign_window(fPad, fWindowControl, cs_x_names[fIndex] , cs_y_names[fIndex],  "", "large");
 

    //for m = 2
    if (!for_paper)
    {
        if (!(m == 1 && n == 1))
        {
            if (fPad->GetLogy() || fVariableName.Contains("deta"))
                fWindowControl->GetYaxis()->SetTitleOffset(1.1);
            else
                    fWindowControl->GetYaxis()->SetTitleOffset(1.4);
        }
        else 
        {
            if (fPad->GetLogy() || fVariableName.Contains("deta")) fWindowControl->GetYaxis()->SetTitleOffset(1.1);
            else if (!fPad->GetLogy() && fVariableName.Contains("xp")) fWindowControl->GetYaxis()->SetTitleOffset(1.2);
            else
            {
                //fWindowControl->GetYaxis()->SetTitleOffset(1.5);
                debug << "xaxis:"<< fWindowControl->GetXaxis()->GetTitleOffset() << endl;
                fWindowControl->GetXaxis()->SetTitleOffset(1.5);
            }
        }
    }
    else
    {
        if (fPad->GetLogy()) fWindowControl->GetYaxis()->SetTitleOffset(1.1);
        else                 fWindowControl->GetYaxis()->SetTitleOffset(1.1);
        // Setting lable text offset a bit away from axis
            if (fVariableName.Contains("deta")) fWindowControl->GetYaxis()->SetTitleOffset(0.8);
            if (fPad->GetLogy() && fVariableName.Contains("xp")) fWindowControl->GetYaxis()->SetTitleOffset(0.9);
            else if (!fPad->GetLogy() && fVariableName.Contains("xp")) fWindowControl->GetYaxis()->SetTitleOffset(1.0);
            if (fVariableName.Contains("dphi_e_ph")) fWindowControl->GetYaxis()->SetTitleOffset(1.2);
    }

    if (!for_paper)fPad->SetMargin(fPad->GetLeftMargin()  + 0.1,/*left border |+ n| to the right*/
                   fPad->GetRightMargin()  - 0.06,/*right border |- n| to the right*/
                   fPad->GetBottomMargin() + 0.08,
                   fPad->GetTopMargin()    + 0.02);
    else 
    {
        fPad->SetMargin(fPad->GetLeftMargin() + 0.08 , \
        fPad->GetRightMargin() - 0.03 ,\
        fPad->GetBottomMargin()  + 0.08, \
        fPad->GetTopMargin() - 0.03);
    }
    
}

void CrossectionDrawer::DrawAll( TH1 ** data, TH1 ** data_tot_err, TH1 ** fit, TH1 ** qq, TH1 ** ll, \
                                 Double_t * all_bins[12], TString s_var[12], int nplots,\
                                 bool with_BLZ = false, \
                                 Double_t * all_theory_cs_BLZ[12] = 0, Double_t * all_theory_cs_BLZ_pos[12] = 0, Double_t * all_theory_cs_BLZ_neg[12] = 0, TString theory_name_BLZ = "BLZ",\
                                 bool withFontannaz = false,
                                 Double_t * all_theory_cs_font[12] = 0, Double_t * all_theory_cs_font_pos[12] = 0, Double_t * all_theory_cs_font_neg[12] = 0, TString theory_name_Font1 = "Fontannaz",
                                 bool two_fontannaz = false,//frst 0.5 cut second 2.5
                                 Double_t * all_theory_cs_font_25[12] = 0, Double_t * all_theory_cs_font_pos_25[12] = 0, Double_t * all_theory_cs_font_neg_25[12] = 0, TString theory_name_Font2 = "Fontannaz")//TString s_var[n_cross];
{
    dout("CrossectionDrawer::DrawAll: m,n ============>", m, n);
    dout("BLZ:", with_BLZ);
    // exit(1);
    // Check the positioning of plots on the canvas
        if ( (m == 1 || m == 2 || m== 3) && !(n == m || n == 1)) n = m;
        else if ((m == 6 && !(n == 3 || n == 2)) || (m == 4)) n = 2;
        else if (m == 5 || m > 6) 
        {
            dout("CrossectionDrawer::DrawAll: m forced to 6, n forced to 2"); 
            m = 6; 
            n = 2;
        }

    TCanvas * test;
    CrossectionDrawer * drawers[12] = {};

    //////////////////////////////////////////////////
    // Draws separate plots
    // saves the same data to be plotted with theory - Fig. 3-5
    //////////////////////////////////////////////////
        for(int i = 0; i < nplots; ++i)
        {
            dout("CrossectionDrawer::DrawAll: ===>",i);
            if ( (i ) % m == 0 ) 
            {   
                //test  = new TCanvas(Form("c%d", i * 10), "bins of ", (1  +  1 * (m > 1))*800, (m / 2 + m % 2) * 600 + 100);
                test  = new TCanvas(Form("c%d", i * 10), "bins of ", n*800, (m / n + m % n) * 600 + 100 * (for_paper == false));
                gStyle->SetLineWidth(2); // width of the border line around plots
                //test->Divide(1  +  1 * (m > 1), m / 2 + m % 2 );
                test->Divide(n, m / n + m % n );
            }

            dout("CrossectionDrawer::DrawAll: pad:", i%m);
            cout << "CrossectionDrawer::DrawAll: Pad value " << test->GetListOfPrimitives()->GetEntries()  << endl;
            TVirtualPad * pad = test->cd(i % m + 1);
            cout << "CrossectionDrawer::DrawAll: " << pad << endl;
            if ( m == 6 && ((n == 2 && (i == 0 || i == 1 || i == 6 || i == 7) ) || (n == 3 && ( i == 6 || i == 7 || i == 8))))
            {
                dout("CrossectionDrawer::DrawAll: t GetBottomMargin() const: ", pad->GetBottomMargin() );
                pad->SetBottomMargin(0);
                dout("CrossectionDrawer::DrawAll: t GetTopMargin() const: ", pad->GetTopMargin() );
                pad->SetTopMargin(2* pad->GetTopMargin());

            }
            if ( m == 6 && n == 2 && (i==2 || i==3 || i==8 || i==9 ))//if ( m == 6 && ((n == 2 && (i == 2 || i == 3 || i == 8 || i == 9) ) || (n == 3 && ( i == 9 || i == 10 || i == 11))))
            {
                dout("CrossectionDrawer::DrawAll: t GetBottomMargin() const: ", pad->GetBottomMargin() );
                pad->SetBottomMargin(0.05);
                dout("CrossectionDrawer::DrawAll: t GetTopMargin() const: ", pad->GetTopMargin() );
                pad->SetTopMargin(pad->GetTopMargin());

            }
            pad->SetFillStyle(4000);//transparent TPad
            drawers[i] = new CrossectionDrawer(i, pad, data[i], data_tot_err[i], fit[i], qq[i], ll[i], test, s_var[i], all_bins[i]); 
            
            dout("here for pap:", (!for_paper || (for_paper 
                                                && ( ( (i == 0 || i == 6) /*&& !q2_cut_global.Contains("_q2_gt_30")*/ ) 
                                                                                                || ( q2_cut_global.Contains("_q2_")  && i == 9) )
                                            ) ));
            
            if (!for_paper || (for_paper 
                                    && ((m == 1 && ( ( (i == 0 || i == 6) /*&& !q2_cut_global.Contains("_q2_gt_30")*/ ) 
                                                    || ( q2_cut_global.Contains("_q2_") ) )) // && i == 9 - fo the deta 
                                        || (m == 6 && ( i == 0 || i == 6  ))// For the pictures with 6 on one use 1 legend
                                        )
                                ) 
                                ) //PLOTS if (!for_paper || (for_paper && (i == 0 || i == 6) )) //PLOTS
            {
                drawers[i]->DrawLegend( true, i);//(i ) % m == 0 
            }
            
            drawers[i]->DrawHist();
            drawers[i]->SaveCanvas( (i + 1) % m == 0 );
            dout(drawers[i]->fVariableName);
        }
    dout("CrossectionDrawer::DrawAll: DONE CALCULATING THE SEPARATE PLOTS!!!!!!!!!!!!!!!!!!");


    //////////////////////////////////////////////////
    // Draws theory - Fig. 6-8
    //////////////////////////////////////////////////
    if (with_BLZ || withFontannaz)
    {
        //Check the necessary pointers to arrays 
            if (with_BLZ)
            {
                if (all_theory_cs_BLZ == 0 || all_theory_cs_BLZ_pos == 0 || all_theory_cs_BLZ_neg == 0) 
                {
                    dout("CrossectionDrawer::DrawAll: one of the passed BLZ theory arrays is zero");
                    return;
                }
            }
            
            if (withFontannaz)
            {
                if ( (all_theory_cs_font == 0 || all_theory_cs_font_pos == 0 || all_theory_cs_font_neg == 0) ||
                    (two_fontannaz && (all_theory_cs_font_25 == 0 || all_theory_cs_font_pos_25 == 0 || all_theory_cs_font_neg_25 == 0)) )
                {
                    dout("CrossectionDrawer::DrawAll: one of the passed Font theory arrays is zero");
                    return;
                }
            }

        dout("Draws theory - Fig. 6-8");
        TCanvas * test_theor;// = new TCanvas('c1', 'c', 899, 900);
        for(int i = 0; i < nplots; ++i)
        {
            dout("\nCrossectionDrawer::DrawAll::processing", i,  drawers[i]->fVariableName);
            if ( (i ) % m == 0 ) 
            {   
                test_theor  = new TCanvas(Form("theor_c%d", i * 10), "bins of ",  n*800, (m / n + m % n) * 600 + 100 * (for_paper == false));
                test_theor->Divide(n, m / n + m % n);
                gStyle->SetLineWidth(2);
            }
            TVirtualPad * pad = test_theor->cd(i % m + 1);
            drawers[i]->SetPad(test_theor, pad);
            // Adjusting pads
                    if ( m == 6 && ((n == 2 && (i == 0 || i == 1 || i == 6 || i == 7) ) || (n == 3 && ( i == 6 || i == 7 || i == 8))))
                    {
                        //dout("CrossectionDrawer::DrawAll: t GetBottomMargin() const: ", pad->GetBottomMargin() );
                        pad->SetBottomMargin(0);
                        //dout("CrossectionDrawer::DrawAll: t GetTopMargin() const: ", pad->GetTopMargin() );
                        pad->SetTopMargin(2* pad->GetTopMargin());
                    }
                    if ( m == 6 && n == 2 && (i == 2 || i == 3 || i == 8 || i == 9 ))
                    {
                        //dout("CrossectionDrawer::DrawAll: t GetBottomMargin() const: ", pad->GetBottomMargin() );
                        pad->SetBottomMargin(0.05);
                        //dout("CrossectionDrawer::DrawAll: t GetTopMargin() const: ", pad->GetTopMargin() );
                        pad->SetTopMargin(pad->GetTopMargin());
                    }

            pad->SetFillStyle(4000);//transparent TPad
            drawers[i]->AdjustPad();
            // Say what we are drawing data or theory with BLZ or theory withpit BLZ
                if (with_BLZ)
                {
                    //Check the pointer
                        if (all_theory_cs_BLZ[i] == 0) 
                        {
                            dout("CrossectionDrawer::DrawAll:", i, "appered to be ", all_theory_cs_BLZ[0]);
                            continue;
                        };
                    drawers[i]->theory_name = theory_name_BLZ;
                    if (IanBLZ && (all_ian_blz_cs[i] != 0))
                        drawers[i]->theory_name += ", unforld.";
                    drawers[i]->AssighnTheory(all_theory_cs_BLZ[i], all_theory_cs_BLZ_pos[i], all_theory_cs_BLZ_neg[i], i);
                    drawers[i]->DrawHist(false, true);
                }
                else drawers[i]->DrawHist(false, false);
                //if (i==6) drawers[i]->fCanvas->Print("testing4.png");

            //////////////////////////////////////////////////////////
            // Plotting Fontannaz theory 
            TGraphAsymmErrors * fTGraphTheoryFont;
            TGraphAsymmErrors * fTGraphTheoryFont2;
            if (withFontannaz)
            {   
                //Check the pointer
                    if ((all_theory_cs_font[i] == 0 || all_theory_cs_font_pos[i] == 0 || all_theory_cs_font_neg[i] == 0) ||
                    (two_fontannaz && (all_theory_cs_font_25[i] == 0 || all_theory_cs_font_pos_25[i] == 0 || all_theory_cs_font_neg_25[i] == 0)) )
                    {
                        dout("CrossectionDrawer::DrawAll: one of the passed Font[i] theory arrays is zero");
                        continue;
                    }

                // Init
                    const Int_t nn = drawers[i]->fCSdata->GetNbinsX();
                    Double_t x[nn], y[nn], exl[nn], exh[nn], eyl[nn], eyh[nn];
                    Double_t temp = 0;

                // Creating graph for AFG theory
                    dout("\tCreating graph for AFG theory");
                    for(int j = 0; j < drawers[i]->fCSdata->GetNbinsX(); ++j)
                    {
                        x[j]   = drawers[i]->fCSdata->GetBinCenter(j + 1) ;
                        y[j]   = all_theory_cs_font[i][j];// * all_hadcort[i][j];
                        exl[j] = 0.5 * drawers[i]->fCSdata->GetBinWidth(j+1); 
                        exh[j] = 0.5 * drawers[i]->fCSdata->GetBinWidth(j+1);
                        eyl[j] = all_theory_cs_font_neg[i][j]; //sqrt(pow(all_theory_cs_font[i][j], 2) * pow(all_hadcort_err[i][j],2) + pow(all_theory_cs_font_neg[i][j], 2) * pow(all_hadcort[i][j], 2) );//all_theory_cs_font_neg[i][j] * all_hadcort[i][j];//statistical - not statistical and acceptance //TODO: propagate errors
                        eyh[j] = all_theory_cs_font_pos[i][j]; //sqrt(pow(all_theory_cs_font[i][j], 2) * pow(all_hadcort_err[i][j],2) + pow(all_theory_cs_font_pos[i][j], 2) * pow(all_hadcort[i][j], 2) );//all_theory_cs_font_pos[i][j] * all_hadcort[i][j];
                        // dout("\t\tbin", j, ") cs: ", all_theory_cs_font[i][j], "*", all_hadcort[i][j], "=", y[j]); //(afg+ll)* had
                        // dout( "\t\t\t", "eyl[j]: ", eyl[j], " eyh[j]: ", eyh[j], " cs all_theory_cs_font:", all_theory_cs_font[i][j]); // afg+ll
                        // dout("\t\t\t", "Had:", all_hadcort[i][j], "dHad:", all_hadcort_err[i][j], "neg:", all_theory_cs_font_neg[i][j], "pos:", all_theory_cs_font_pos[i][j]);
                        temp  += all_theory_cs_font[i][j] * drawers[i]->fCSdata->GetBinWidth(j+1);
                    }
                    dout("\tCrossectionDrawer::DrawAll: Fontannaz(1) theory sum_sigma = ", temp);
                    //if (drawers[i]->fVariableName.Contains("deta")); exit(1);
                    fTGraphTheoryFont = new TGraphAsymmErrors(nn, x, y, exl, exh, eyl, eyh);
                    fTGraphTheoryFont->SetMarkerColor(kBlue);//kRed
                    fTGraphTheoryFont->SetMarkerSize(1.1);
                    fTGraphTheoryFont->SetMarkerStyle(20);
                    fTGraphTheoryFont->SetLineColor(1);
                    fTGraphTheoryFont->SetLineWidth(1);
                    fTGraphTheoryFont->SetFillStyle(3005);
                    fTGraphTheoryFont->SetFillColor(kBlue);//kRed
                    //fTGraphTheoryFont->SetMarkerStyle(1);
                    fTGraphTheoryFont->Draw("SAME 5 ");

                if (two_fontannaz) 
                {   
                    temp = 0;
                    for(int j = 0; j < drawers[i]->fCSdata->GetNbinsX(); ++j)
                    {
                        x[j]   = drawers[i]->fCSdata->GetBinCenter(j + 1) ;
                        y[j]   = all_theory_cs_font_25[i][j];// * all_hadcort[i][j];
                        exl[j] = 0.5 * drawers[i]->fCSdata->GetBinWidth(j+1); 
                        exh[j] = 0.5 * drawers[i]->fCSdata->GetBinWidth(j+1);
                        eyl[j] = all_theory_cs_font_neg_25[i][j]; //sqrt(pow(all_theory_cs_font_25[i][j], 2) * pow(all_hadcort_err[i][j], 2) + pow(all_theory_cs_font_neg_25[i][j], 2) * pow(all_hadcort[i][j], 2));//all_theory_cs_font_neg[i][j] * all_hadcort[i][j];//statistical - not statistical and acceptance //TODO: propagate errors
                        eyh[j] = all_theory_cs_font_pos_25[i][j]; //sqrt(pow(all_theory_cs_font_25[i][j], 2) * pow(all_hadcort_err[i][j],2) + pow(all_theory_cs_font_pos_25[i][j], 2) * pow(all_hadcort[i][j], 2));//all_theory_cs_font_pos[i][j] * all_hadcort[i][j];
                        temp  += all_theory_cs_font_25[i][j] * drawers[i]->fCSdata->GetBinWidth(j+1);
                    }
                    dout("CrossectionDrawer::DrawAll: Fontannaz(2) theory sum_sigma = ", temp);
                    fTGraphTheoryFont2 = new TGraphAsymmErrors(nn, x, y, exl, exh, eyl, eyh);
                    fTGraphTheoryFont2->SetMarkerColor(kBlue);
                    fTGraphTheoryFont2->SetMarkerSize(1.1);
                    fTGraphTheoryFont2->SetMarkerStyle(20);
                    fTGraphTheoryFont2->SetLineColor(1);
                    fTGraphTheoryFont2->SetLineWidth(1);
                    fTGraphTheoryFont2->SetFillStyle(3004);
                    fTGraphTheoryFont2->SetFillColor(kBlue);
                    fTGraphTheoryFont2->Draw("SAME 5");
                }
            }

            //Draw Legend
                //make it wider with respect to q2 cut
                    // void DrawLegend(bool t, bool with_BLZ, 
                    //                 bool with_Font, TGraphAsymmErrors* fTGraphTheoryFont, TString FontName, 
                    //                 bool with_Font2, TGraphAsymmErrors* fTGraphTheoryFont2, TString FontName2) const;
                if (!(with_BLZ || withFontannaz))
                {
                    dout("(!(with_BLZ || withFontannaz))");
                    if (!for_paper ||
                    (for_paper && (( (i == 0 || i == 6) && !q2_cut_global.Contains("_q2_gt_30") )|| ( q2_cut_global.Contains("_q2_")  && i == 9) )) ) //PLOTS
                        drawers[i]->DrawLegend( (i ) % m == 0, i );
                }
                else if (with_BLZ)
                {
                    if (!withFontannaz)
                    {
                        dout("here for pap:");
                        if (!for_paper ||
                            (for_paper && ( ( (i == 0 || i == 6) /*&& !q2_cut_global.Contains("_q2_gt_30")*/ ) || ( q2_cut_global.Contains("_q2_")  && i == 9) )) ) //PLOTS
                            drawers[i]->DrawLegend( (i ) % m == 0 , i, true);
                    }
                    else if (withFontannaz && ! two_fontannaz)
                    {

                        
                        dout("with_BLZ && (withFontannaz && ! two_fontannaz)");
                        if (!for_paper || 
                            (for_paper && (( (i == 0 || i == 6) /*&& !q2_cut_global.Contains("_q2_gt_30")*/ ) || ( q2_cut_global.Contains("_q2_")  && i == 9) )) ) //PLOTS
                        {
                            TString theoryname = theory_name_Font1;
                            if (IanAFG && all_ian_afg_cs[i] != 0) theoryname += ", unforld.";
                            drawers[i]->DrawLegend( (i ) % m == 0 , i, true,
                                true, fTGraphTheoryFont, theoryname,
                                false );//"#splitline{Fontannaz }{(0.5 < p_{T} cut < 2.5)}"
                    
                        }
                    }
                    else if (withFontannaz && withFontannaz)
                    {
                        dout("with_BLZ && (withFontannaz && withFontannaz)");
                        if (!for_paper || 
                            (for_paper && (( (i == 0 || i == 6) /*&& !q2_cut_global.Contains("_q2_gt_30")*/ ) || ( q2_cut_global.Contains("_q2_")  && i == 9) )) ) //PLOTS
                        {
                            TString theoryname1 = theory_name_Font1;
                            TString theoryname2 = theory_name_Font2;
                            if (IanAFG && all_ian_afg_cs[i] != 0)
                            {
                                theoryname1 += ", unforld.";
                                theoryname2 += ", unforld.";
                            }
                            drawers[i]->DrawLegend( (i ) % m == 0 , i, true, 
                                true, fTGraphTheoryFont,  theoryname1, 
                                true, fTGraphTheoryFont2, theoryname2);
                        }
                    }
                    else cerr << "Something strange"<< endl;

                }
                else if (withFontannaz)
                {
                    if (!two_fontannaz)
                    {
                        dout("!with_BLZ && withFontannaz && !two_fontannaz");
                        if (!for_paper || (for_paper && (i == 0 || i == 6))) //PLOTS
                        {
                            TString theoryname = theory_name_Font1;
                            if (IanAFG && all_ian_afg_cs[i] != 0) theoryname += ", unforld.";
                            drawers[i]->DrawLegend( (i ) % m == 0 , i, false, 
                                                                true, fTGraphTheoryFont, theoryname,
                                                                false );//"#splitline{Fontannaz }{(0.5 < p_{T} cut < 2.5)}"
                        }
                    }
                    else if ( two_fontannaz)
                    {
                        dout("!with_BLZ && withFontannaz && two_fontannaz");
                        if (!for_paper || (for_paper && (i == 0 || i == 6))) //PLOTS
                        {
                            TString theoryname1 = theory_name_Font1;
                            TString theoryname2 = theory_name_Font2;
                            if (IanAFG && all_ian_afg_cs[i] != 0)
                            {
                                theoryname1 += ", unforld.";
                                theoryname2 += ", unforld.";
                            }
                            drawers[i]->DrawLegend( (i ) % m == 0 , i, false,
                                true, fTGraphTheoryFont,  theoryname1, 
                                true, fTGraphTheoryFont2, theoryname2);
                        }
                    }
                    else cerr << "Something strange"<< endl;
                }
            drawers[i]->SaveCanvas( (i + 1) % m == 0 , false);
        }    
    }
}

// So far used only on BLZ
void CrossectionDrawer::AssighnTheory(Double_t * cs = 0, Double_t * cs_pos = 0, Double_t * cs_neg = 0, int num = -1)
{
    if (num == -1)
    {
        dout("in CrossectionDrawer::AssighnTheory num =-1");
        exit(0);
    }
    if (cs == 0 || cs_pos == 0 || cs_neg == 0) 
    {
        dout("one of the passed the passed theory arrays is zero");
        dout("cs[0]", cs[0]);
        dout("cs_pos[0]", cs_pos[0]);
        dout("cs_neg[0]", cs_neg[0]);
        return;
    }

    //fTH1Theory = new TH1(Form("theory_%d", num), "theory", fCSdata->GetNbinsX(), fCSdata->GetXaxis()->GetBinLowEdge(1), fCSdata->GetXaxis()->GetBinUpEdge(fCSdata->GetNbinsX());

    const Int_t nn = fCSdata->GetNbinsX();
    Double_t x[nn];
    Double_t y[nn];
    Double_t exl[nn] ;
    Double_t exh[nn] ;
    Double_t eyl[nn];
    Double_t eyh[nn];
    dout("theory CrossectionDrawer::AssighnTheory sum for", fVariableName);
    Double_t temp = 0;
    for(int j = 0; j < fCSdata->GetNbinsX(); ++j)
    {
        if (!IanBLZ || all_ian_blz_cs[num] == 0)
        {
            x[j] = fCSdata->GetBinCenter(j + 1);
            y[j] = cs[j] * all_hadcort_BLZ_rew[num][j] ;//+
                   // + fMCll->GetBinContent(j+1);// THIS IS ONLY FOR FONTANNAZ of 2.5 where we need to add the ll; // The handonisation correction is always applied
            exl[j] = 0.5 * fCSdata->GetBinWidth(j+1); 
            exh[j] = 0.5 * fCSdata->GetBinWidth(j+1);
            eyl[j] = sqrt(pow(cs[j], 2) * pow(all_hadcort_err_BLZ_rew[num][j],2) + pow(cs_neg[j], 2) * pow(all_hadcort_BLZ_rew[num][j], 2) );//cs_neg[j] * all_hadcort[num][j];//statistical - not statistical and acceptance // TODO: propagate the error
            eyh[j] = sqrt(pow(cs[j], 2) * pow(all_hadcort_err_BLZ_rew[num][j],2) + pow(cs_pos[j], 2) * pow(all_hadcort_BLZ_rew[num][j], 2) );//cs_pos[j] * all_hadcort[num][j];
            // dout("was",j,":", cs[j] * all_hadcort[num][j], "+-", eyl[j], " : +", fMCll->GetBinContent(j+1), "+-", fMCll->GetBinError(j+1));

            //  eyl[j] = sqrt(pow(eyl[j], 2) + pow(fMCll->GetBinError(j+1), 2));
            //  eyh[j] =  sqrt(pow(eyh[j], 2) + pow(fMCll->GetBinError(j+1), 2));
            //  dout("became",j,":",y[j], "+-", eyl[j]);
            temp += cs[j] * fCSdata->GetBinWidth(j+1);
        }
        else 
        {
            x[j] = fCSdata->GetBinCenter(j + 1);
            y[j] = all_ian_blz_cs[num][j];
            exl[j] = 0.5 * fCSdata->GetBinWidth(j+1); 
            exh[j] = 0.5 * fCSdata->GetBinWidth(j+1);
            eyl[j] = all_ian_blz_neg[num][j];
            eyh[j] = all_ian_blz_pos[num][j];
            dout("IAN CS: bin:", j, "cs:", y[j], "+-",  eyl[j], eyh[j]);
            temp += cs[j] * fCSdata->GetBinWidth(j+1);
        }
    }

    dout("theory CrossectionDrawer::AssighnTheory sum_sigma = ", temp);
    fTGraphTheory = new TGraphAsymmErrors(nn, x, y, exl, exh, eyl, eyh);
    fTGraphTheory->SetMarkerColor(31);
    fTGraphTheory->SetMarkerSize(1.1);
    fTGraphTheory->SetMarkerStyle(20);
    fTGraphTheory->SetLineWidth(3);
    
    Int_t dummy_variable = !fVariableName.Contains("xgamma") ? 1000 : 100000;
    TString str_title = "";
    fWindowControl = new TH2D("h_window_new_" + fVariableName, str_title, fCSdata->GetNbinsX(), all_bins[0], all_bins[fCSdata->GetNbinsX()], dummy_variable, -0.0001, GetYmax(false));
    
    fWindowControl->GetYaxis()->SetRangeUser(-0.0001, GetYmax(false));
    fWindowControl->Draw();
       //graph->SetMarkerSize(5);  
}

void CrossectionDrawer::SetPad(TCanvas * c, TVirtualPad * pad)//rewrite so there was a pads vector to store all the pads 
{
    fPad = pad;
    fCanvas = c;
}
/*int main()
    {
        TH1 * data[1] = {new TH1D("h1", "test", 3, 4, 10)};
        TH1 * fit[1] = {new TH1D("h2", "test", 3, 4, 10)};
        TH1 * qq[1] = {new TH1D("h3", "test", 3, 4, 10)};
        TH1 * ll[1] = {new TH1D("h4", "test", 3, 4, 10)};
        data[0]->SetBinContent(1, 3);
        data[0]->SetBinContent(2, 5);
        data[0]->SetBinContent(3, 4);
        data[0]->SetBinError(1, 0.5);
        data[0]->SetBinError(2, 0.5);
        data[0]->SetBinError(3, 0.4);
        //Double_t * all_bins[12] = {0};
        //for(int i = 0; i < 12; i++) all_bins[i] = new Double_t[20];
        CrossectionDrawer::DrawAll(data, fit, qq, ll, all_bins, 1);
    }
*/