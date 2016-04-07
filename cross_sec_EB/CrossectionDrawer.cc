#include <TCanvas.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TGraphAsymmErrors.h>
#include <TPaveText.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TDirectory.h>
#include <iostream>
using std::cout;
using std::endl;

//#include "../inc/constants.h"
//Double_t * all_bins[12] = {et_bin, eta_bin_crosssec, Q2_bin, x_bin, et_jet_bin, eta_jet_bin, \
//                            xgamma_bin, xp_bin, dphi_bin, deta_bin, dphi_e_ph_bin, deta_e_ph_bin};

class CrossectionDrawer
{
public:
    CrossectionDrawer(int i, TVirtualPad * p, TH1 * data, TH1 * sum, TH1 * qq, TH1 * ll, TCanvas * canvas, TString name, Double_t * a);
    void DrawLegend(bool t) const;
    void DrawHist() const;
    void SaveCanvas(bool t) const;
    // ~CrossectionDrawer();
    static void DrawAll(TH1 ** data, TH1 ** fit, TH1 ** qq, TH1 ** ll, Double_t * all_bins[12], int nplots);
private:
    void AdjustPad();
    Double_t GetYmax() const;
    TGraphAsymmErrors * GetErrors() const;
    // TString current_position = "right up";
    enum LegendPosition{kRightUp, kRightDown, kLeftUp, kLeftDown};
    TH1 * fCSdata;
    TH1 * fMCsum;
    TH1 * fMCqq;
    TH1 * fMCll;
    TCanvas * fCanvas;// = new TCanvas(canvas_name, binsof, 800, 600); и номер пада  

    TH2D   * fWindowControl;
    TGraphAsymmErrors * fAsymmError;// = new TGraphAsymmErrors(n,x,y,exl,exh,eyl,eyh);

    // TString binsof("bins of "+ fVariablesFullNames[i]);
    TString fVariableName;//(fVariablesFullNames[i]);
    int fIndex;
    TVirtualPad  * fPad;

    Double_t * all_bins;
    // Double_t x1, x2, y1, y2;
};

CrossectionDrawer::CrossectionDrawer(int i, TVirtualPad * p, TH1 * data, TH1 * sum, TH1 * qq, TH1 * ll, TCanvas * canvas, TString name, Double_t * all_bins):
fIndex(i),
fPad(p),
fCSdata(data),
fMCsum(sum),
fMCqq(qq),
fMCll(ll),
fVariableName(name),
fCanvas(canvas),
fWindowControl(0),
fAsymmError(0)
{
    // SetFigure3Style(fCSdata, fMCsum, fMCqq, fMCll, 0);

    int number_bins = fCSdata->GetNbinsX();
    Int_t dummy_variable = !fVariableName.Contains("xgamma") ? 1000 : 10000;
    fWindowControl = new TH2D("h_window_fig3_" + fVariableName, "title", number_bins, all_bins[0], all_bins[number_bins], dummy_variable, -0.0001, GetYmax());
    fAsymmError = GetErrors();

    cout << "Constructor reached  here " << endl;
    AdjustPad();
    cout << "Constructor reached  here " << endl;
    fWindowControl->GetYaxis()->SetRangeUser(-0.0001, GetYmax());
    fPad->Update();
    fWindowControl->Draw();

 
    fMCqq->SetLineWidth(3);
    fMCll->SetLineWidth(3);
    fMCsum->SetLineWidth(3);

}

Double_t CrossectionDrawer::GetYmax() const
{
    Double_t ymax = fCSdata->GetMaximum() > fMCsum->GetMaximum() ? fCSdata->GetMaximum() : fMCsum->GetMaximum();
    ymax = 1.2 * ymax;
    if ( fVariableName.Contains("xgamma") ) ymax = ymax * 5;
    if ( fVariableName.Contains("xp") )     ymax = ymax * 2;
    return ymax;
}

void CrossectionDrawer::DrawLegend(bool draw) const
{
    if( !draw )  return;
    LegendPosition current_position = kRightUp;

    if (fVariableName.Contains("xgamma") || fVariableName.Contains("dphi"))   current_position = kLeftUp;

    Double_t x1, x2, y1, y2;

    bool is_left = current_position == kLeftUp  || current_position == kLeftDown;
    bool is_down = current_position == kRightDown  || current_position == kLeftDown;

    x1 = is_left ? 0.20 : 0.45 ;//0.15
    x2 = is_left ? 0.60 : 0.86 ;
    y1 = is_down ? 0.10 : 0.60;//0.5
    y2 = is_down ? 0.45 : 0.91;//0.88

    TLegend *leg = new TLegend(x1, y1, x2, y2);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);             
    leg->AddEntry(fAsymmError, "ZEUS, 326 pb^{-1}", "pe"); 
    leg->AddEntry(fMCll,  "QQ*1.6, MC", "f"); 
    leg->AddEntry(fMCqq,  "LL, MC", "f");
    leg->AddEntry(fMCsum, "LL + QQ*1.6, MC", "f");
    leg->Draw();

}

void CrossectionDrawer::DrawHist() const
{
    TString title("cs, " + fVariableName);
    gStyle->SetOptStat(0);
    fAsymmError->Draw("SAME P E");
    fMCll->Draw("HIST F E1 SAME");
    fMCqq->Draw("HIST F E1 SAME");
    fMCsum->Draw("HIST F E1 SAME");
    fPad->RedrawAxis();
    TPaveText t(0.4, 0.93, 0.6, 1.0, "NDC"); 
    t.AddText("ZEUS");
    t.SetFillColor(0);
    t.SetBorderSize(0);
}

void CrossectionDrawer::SaveCanvas(bool draw) const
{
    if ( !draw ) return;
    fCanvas->Print(TString("temp_") + fCanvas->GetName() + TString(".eps") );
    fCanvas->Print(TString("temp_") + fCanvas->GetName() + TString(".png") );
}

TGraphAsymmErrors * CrossectionDrawer::GetErrors() const
{
    const Int_t n = fCSdata->GetNbinsX();
    Double_t x[n];
    Double_t y[n];
    Double_t exl[n] ;
    Double_t exh[n] ;
    Double_t eyl[n];
    Double_t eyh[n];
    for(int j = 0; j < fCSdata->GetNbinsX(); ++j)
    {
        x[j] = fCSdata->GetBinCenter(j + 1) ;// +  0.2 * fCSdata->GetBinWidth(j + 1);
        y[j] = fCSdata->GetBinContent(j + 1);
        exl[j] = 0;
        exh[j] = 0;
        eyl[j] = fCSdata->GetBinError(j + 1); //h_cross[i][1]->GetBinError(j + 1);//statistical - not statistical and acceptance
        eyh[j] = 1;//TMath::Sqrt(pow(all_syst[i][j], 2) + pow(h_cross[i][1]->GetBinError(j + 1), 2) );
    }

    TGraphAsymmErrors * graph = new TGraphAsymmErrors(n, x, y, exl, exh, eyl, eyh);
    graph->SetMarkerColor(1);
    graph->SetMarkerSize(1.1);
    graph->SetMarkerStyle(20);
    graph->SetLineWidth(3);
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

    if (fVariableName.Contains("xp") || fVariableName.Contains("gamma") ) fPad->SetLogy();


    cout << fPad << endl;
    fPad->SetFrameBorderMode(0);
   cout << "AdjustPad reached  here " << endl;
    fPad->SetTicks(1,1);
    fPad->SetBorderMode(0);
    fPad->SetFillColor(kWhite);
    fPad->SetGrid(0, 0);
   cout << "AdjustPad reached  here " << endl;
    // sign_window(fPad, fWindowControl, cs_x_names[i] , cs_y_names[i], "", "large");

    fPad->SetMargin(fPad->GetLeftMargin()   + 0.08,
                   fPad->GetRightMargin()  - 0.03,
                   fPad->GetBottomMargin() + 0.08,
                   fPad->GetTopMargin()    - 0.03);

}

void CrossectionDrawer::DrawAll(TH1 ** data, TH1 ** fit, TH1 ** qq, TH1 ** ll, Double_t * all_bins[12], int nplots)
{
    int m = 1;
    TCanvas * test;// = new TCanvas('c1', 'c', 899, 900);
    CrossectionDrawer * drawers[12] = {};
    for(int i = 0; i < nplots; ++i)
    {
        if ( (i ) % m == 0 ) 
        {
            test  = new TCanvas(Form("c%d", i * 10), "bins of ", 800, 600);
            test->Divide(1  +  1 * (m > 1), m / 2 + m % 2 );
            cout << "Divided " << 1  +  1 * (m > 1) <<  " and " << m / 2 + m % 2 << endl;
        }

        cout << "reached  here " << endl;
        TVirtualPad * pad = test->GetPad(i % m);
        cout << pad <<endl;
        cout << "reached  here " << endl;
        drawers[i] = new CrossectionDrawer(i, pad, data[i], fit[i], qq[i], ll[i], test, "some", all_bins[i]); 
        cout << "end  here " << endl;
        drawers[i]->DrawLegend( (i ) % m == 0 );
        drawers[i]->DrawHist();
        drawers[i]->SaveCanvas( (i + 1) % m == 0 );
    }
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