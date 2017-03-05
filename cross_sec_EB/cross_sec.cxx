#include "cross_sec.h"

TString q2_cut_global = "";// _q2_gt_30 // _q2_lt_30//initialisation of q2_cut="" - re do it in form of input parameter
TString whichCorrection("IanSgCorr");//"IanSgCorr" NoCorrection; Default is IanSgCorr QQfit = 1 fitWithLL = 1 fitWithLLinBg = 0
vector<Double_t> IanCorrectionSg({ 1, 1.2, 1.2, 1.4});//paste to whichCorrection "IanSgCorr"
vector<Double_t> PeterCorrectionSg({1, 1.2, 1.3, 1.3});//paste to whichCorrection "PeterSgCorr"
vector<Double_t> PeterCorrectionBg({1, 1.2, 1.3, 1.15, 1.05, 1., 0.95, 0.95});//paste to whichCorrection "PeterBgCorr"
unsigned int NoScalingForBinsTest = 0;
unsigned int ProduceDZoverollPlot = 1;
bool dZdetailed = false;
Bool_t nodebugmode = kTRUE;
Bool_t once = kTRUE;

bool llCorrectiontoo = false;

unsigned int QQfit = 1; 
//0 : data = photons * a + bg' * (1 - a);
    //QQ' = QQ.scale([Data - LL] / QQ)
    //bg' = bg.scale([Data - LL] / bg)
//1 : data = LL + QQ' * a + bg' * (1 - a);
    //QQ' = QQ.scale([Data - LL] / QQ) if fitWithLL==1 and fitWithLLinBg=0
    //bg' = bg.scale([Data] / bg)
unsigned int fitWithLL = 1; 

unsigned int fitWithLLinBg = 0; //DON"T TURN ON ANYMORE
//data =LL’ +  QQ’ * a + bg’ * (1- a)
    //unsigned int QQfit = 1;
    //unsigned int fitWithLL= 1;
    //unsigned int fitWithLLinBg=0;
//data = QQ’ * a + bg’ * (1 - a)
    //unsigned int QQfit = 1;
    //unsigned int fitWithLL= 0;
    //unsigned int fitWithLLinBg=0;
//data = QQ’ * a + bg’’ * (1 - a)
    //unsigned int QQfit = 1;
    //unsigned int fitWithLL= 0;
    //unsigned int fitWithLLinBg=1;
//data = [LL'+QQ']*a + bg’ * (1- a) - перепроверить репараметризацию
    //unsigned int QQfit = 0;
    //unsigned int fitWithLL = 0; - пока что нигде не влияет; оставлю 0 так как не входит в виде отдельного члена
    //unsigned int fitWithLLinBg = 0; - пока что нигде не влияет;
ofstream debug;

#include "CrossectionDrawer.h"
#include "hist.c"
Hist hist;

//0.05 - 0.8 - our new
//0 - 0.8 - paper
//0 - 0.95 - actual dz paper
Double_t leftRange = 0.05;//0.05;//0.00;//0.05
Double_t sys_fit = 0.8;//0.8;//0.95;//0.8
Int_t GetFitRange( TH1D* h, bool f=true)
{
    if (f) 
    {
        
        return h->FindBin(leftRange) ;//-1 was from old code when the range was 0 - 0.95
    } //left range
    else 
    {
        if (once) 
        dout("right ",h->FindBin(sys_fit),"sys_fit=",sys_fit);//0.6 - 1.0
        once = kFALSE;
        return h->FindBin(sys_fit) ;
    }
}

Double_t GetSumError(TH1D* h) 
{
    Double_t sum = 0; 
    for (Int_t i = 0; i < h->GetNbinsX(); i++) 
        sum += pow(h->GetBinError(i+1), 2); 
    return TMath::Sqrt(sum);
}

void DoReparametrisation(Int_t histindex, Double_t* param, Double_t* param_err, Int_t index)//171215
{
    Double_t        a = param[index], da = param_err[index];
    Double_t        d = hist.hist_data_sum[histindex]->GetBinContent(index + 1) * hist.hist_data_sum[histindex]->GetBinWidth(index+1);
    Double_t       dd = hist.hist_data_sum[histindex]->GetBinError(index + 1) * hist.hist_data_sum[histindex]->GetBinWidth(index+1);
    Double_t        b = hist.hist_mc_norad_sum[histindex]->GetBinContent(index + 1) * hist.hist_mc_norad_sum[histindex]->GetBinWidth(index+1);
    Double_t       db = hist.hist_mc_norad_sum[histindex]->GetBinError(index + 1) * hist.hist_mc_norad_sum[histindex]->GetBinWidth(index+1);
    Double_t        p = hist.hist_mc_photon_sum[histindex]->GetBinContent(index + 1)  * hist.hist_mc_sum[histindex]->GetBinWidth(index+1);
    Double_t       dp = hist.hist_mc_photon_sum[histindex]->GetBinError(index + 1)  * hist.hist_mc_sum[histindex]->GetBinWidth(index+1);
    Double_t        l = hist.hist_mc_rad_sum[histindex]->GetBinContent(index + 1) * hist.hist_mc_rad_sum[histindex]->GetBinWidth(index+1);
    Double_t       dl = hist.hist_mc_rad_sum[histindex]->GetBinError(index + 1) * hist.hist_mc_rad_sum[histindex]->GetBinWidth(index+1);
    Double_t        q = hist.hist_mc_sum[histindex]->GetBinContent(index + 1) * hist.hist_mc_sum[histindex]->GetBinWidth(index+1);
    Double_t       dq = hist.hist_mc_sum[histindex]->GetBinError(index + 1) * hist.hist_mc_sum[histindex]->GetBinWidth(index+1);

    if (histindex==1 && index == 0 && nodebugmode)
    {
        /*q = hist_mc[0]->IntegralAndError(0, hist_mc[0]->GetNbinsX()+1, dq);
        Double_t       dd, d ;
        d = hist_data[0]->IntegralAndError(0, hist_data[0]->GetNbinsX()+1, dd);
        Double_t       db, b ;
        b = hist_mc_norad[0]->IntegralAndError(0, hist_mc_norad[0]->GetNbinsX()+1, db);
        Double_t       p, dp ;
        p = hist_mc_photon[0]->IntegralAndError(0, hist_mc_photon[0]->GetNbinsX()+1, dp);
        Double_t       l, dl ;
        l = hist_mc_rad[0]->IntegralAndError(0, hist_mc_rad[0]->GetNbinsX()+1, dl);*/

     dout("xgamma in the raparametrisation:\n   data in hist_data[0]:", hist_data[0]->GetSum(),
         "   data in hist_data_sum[]:", hist.hist_data_sum[histindex]->GetBinContent(index + 1)*hist.hist_data_sum[histindex]->GetBinWidth(index+1),
         "   data in hist_data[0] integral:", hist_data[0]->Integral(0, hist_data[0]->GetNbinsX()+1));
     dout("   QQ in hist_mc[0]:", hist_mc[0]->GetSum(),"   QQ in hist_mc_sum[]:", 
         hist.hist_mc_sum[histindex]->GetBinContent(index + 1)*hist.hist_mc_sum[histindex]->GetBinWidth(index+1));
     dout("   LL in hist_mc_rad[0]:", hist_mc_rad[0]->GetSum(),"   LL in hist_mc_rad_sum[]:", 
         hist.hist_mc_rad_sum[histindex]->GetBinContent(index + 1) * hist.hist_mc_rad_sum[histindex]->GetBinWidth(index+1));
     dout("   bg in hist_mc_norad[0]:", hist_mc_norad[0]->GetSum(),"   bg in hist_mc_norad_sum[]:", 
         hist.hist_mc_norad_sum[histindex]->GetBinContent(index + 1) * hist.hist_mc_norad_sum[histindex]->GetBinWidth(index+1));
    }

    if (nodebugmode && histindex == 1) dout("err",index,":", da, pow(d,-2)*\
             TMath::Sqrt( pow(dd,2)*pow(l - a*p, 2) +\
                 pow(d,2)*(pow(dl,2) + pow(a,2)*pow(dp, 2) + 
                     pow(da*p, 2))
                 ) );
    da = pow(d,-2)*\
     TMath::Sqrt( pow(dd,2)*pow(l - a*p, 2) +\
         pow(d,2)*(pow(dl,2) + pow(a,2)*pow(dp, 2) + 
             pow(da*p, 2))
         ) ;
    if (nodebugmode && histindex == 1) dout("a",index,":",a, (a*hist_mc_photon[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_data[0]->GetSum());
    a = (a*p - l)/d;
    param[index] = a;
    param_err[index] = da; 
}

void DoReparametrisation(Double_t* param, Double_t* param_err, Int_t index)//for old variables
{
    Double_t        a = param[index], da = param_err[index];
    
    Double_t        q, dq = 0;
    q = hist_mc[0]->IntegralAndError(0, hist_mc[0]->GetNbinsX()+1, dq);
    Double_t       dd = 0, d ;
    d = hist_data[0]->IntegralAndError(0, hist_data[0]->GetNbinsX()+1, dd);
    Double_t       db = 0, b ;
    b = hist_mc_norad[0]->IntegralAndError(0, hist_mc_norad[0]->GetNbinsX()+1, db);
    Double_t       p, dp = 0 ;
    p = hist_mc_photon[0]->IntegralAndError(0, hist_mc_photon[0]->GetNbinsX()+1, dp);
    Double_t       l, dl = 0 ;
    l = hist_mc_rad[0]->IntegralAndError(0, hist_mc_rad[0]->GetNbinsX()+1, dl);

    da = pow(d,-2)*\
     TMath::Sqrt( pow(dd,2)*pow(l - a*p, 2) +\
         pow(d,2)*(pow(dl,2) + pow(a,2)*pow(dp, 2) + 
             pow(da*p, 2))
         ) ;
   
    a = (a*p - l)/d;
    param[index] = a;
    param_err[index] = da; 
}

void DoReparametrisationforQQ(Int_t histindex, Double_t* param, Double_t* param_err, Int_t index)//171215
{
    Double_t a = param[index], da = param_err[index];
    Double_t        d = hist.hist_data_sum[histindex]->GetBinContent(index + 1) * hist.hist_data_sum[histindex]->GetBinWidth(index+1);
    Double_t       dd = hist.hist_data_sum[histindex]->GetBinError(index + 1) * hist.hist_data_sum[histindex]->GetBinWidth(index+1);
    Double_t        b = hist.hist_mc_norad_sum[histindex]->GetBinContent(index + 1) * hist.hist_mc_norad_sum[histindex]->GetBinWidth(index+1);
    Double_t       db = hist.hist_mc_norad_sum[histindex]->GetBinError(index + 1) * hist.hist_mc_norad_sum[histindex]->GetBinWidth(index+1);
    Double_t        p = hist.hist_mc_photon_sum[histindex]->GetBinContent(index + 1)  * hist.hist_mc_sum[histindex]->GetBinWidth(index+1);
    Double_t       dp = hist.hist_mc_photon_sum[histindex]->GetBinError(index + 1)  * hist.hist_mc_sum[histindex]->GetBinWidth(index+1);
    Double_t        l = hist.hist_mc_rad_sum[histindex]->GetBinContent(index + 1) * hist.hist_mc_rad_sum[histindex]->GetBinWidth(index+1);
    Double_t       dl = hist.hist_mc_rad_sum[histindex]->GetBinError(index + 1) * hist.hist_mc_rad_sum[histindex]->GetBinWidth(index+1);
    Double_t        q = hist.hist_mc_sum[histindex]->GetBinContent(index + 1) * hist.hist_mc_sum[histindex]->GetBinWidth(index+1);
    Double_t       dq = hist.hist_mc_sum[histindex]->GetBinError(index + 1) * hist.hist_mc_sum[histindex]->GetBinWidth(index+1);
    da = pow(q,-2)*\
        TMath::Sqrt( pow(dq,2)*pow(l - a*p, 2) +\
            pow(q,2)*(pow(dl,2) + pow(a,2)*pow(dp, 2) + 
                pow(da*p, 2))
            ) ;
    a = (a*p - l)/q;
    param[index] = a;
    param_err[index] = da;  
}
void DoReparametrisationforQQ(Double_t* param, Double_t* param_err, Int_t index)//for old variables
{
    Double_t a = param[index], da = param_err[index];
    Double_t        q, dq;
    q = hist_mc[0]->IntegralAndError(0, hist_mc[0]->GetNbinsX()+1, dq);
    Double_t       dd, d ;
    d = hist_data[0]->IntegralAndError(0, hist_data[0]->GetNbinsX()+1, dd);
    Double_t       db, b ;
    b = hist_mc_norad[0]->IntegralAndError(0, hist_mc_norad[0]->GetNbinsX()+1, db);
    Double_t       p, dp ;
    p = hist_mc_photon[0]->IntegralAndError(0, hist_mc_photon[0]->GetNbinsX()+1, dp);
    Double_t       l, dl ;
    l = hist_mc_rad[0]->IntegralAndError(0, hist_mc_rad[0]->GetNbinsX()+1, dl);

    da = pow(q,-2)*\
        TMath::Sqrt( pow(dq,2)*pow(l - a*p, 2) +\
            pow(q,2)*(pow(dl,2) + pow(a,2)*pow(dp, 2) + 
                pow(da*p, 2))
            ) ;
    a = (a*p - l)/q;
    param[index] = a;
    param_err[index] = da;  
}

void DoReparametrisationQQfit(Int_t histindex, Double_t* param, Double_t* param_err, Int_t index)//QQfit==1 для новых переменных только
{
    Double_t a = param[index], da = param_err[index];

    Double_t        q = hist.hist_mc_sum[histindex]->GetBinContent(index + 1) * hist.hist_mc_sum[histindex]->GetBinWidth(index+1);//added mult by width on 230116
    Double_t       dq = hist.hist_mc_sum[histindex]->GetBinError(index + 1) * hist.hist_mc_sum[histindex]->GetBinWidth(index+1) ;
    Double_t       dd = hist.hist_data_sum[histindex]->GetBinError(index + 1) * hist.hist_data_sum[histindex]->GetBinWidth(index+1);
    Double_t        d = hist.hist_data_sum[histindex]->GetBinContent(index + 1) * hist.hist_data_sum[histindex]->GetBinWidth(index+1);
    /*Double_t d = hist_data[0]->GetSum(), b = hist_mc_norad[0]->GetSum(), p = phist_mc_photon[0]->GetSum(), l = hist_mc_rad[0]->GetSum(),
            dd = GetSumError(hist_data[0]), bb = GetSumError(hist_mc_norad[0]), dp = GetSumError(phist_mc_photon[0]), dl = GetSumError(hist_mc_rad[0]);
            //Or simply sqrt(content) or sqrt(sum of w2)?
            */
            //Double_t Dq = a/d, Da = q/d, Dd = -((a q)/d/d)
    Double_t g = (q*a)/d,
            dg = TMath::Sqrt((d*d* da*da* q*q + a*a* (d*d *dq*dq + dd*dd* q*q))/pow(d,4));

    if (nodebugmode) cout << "===> " << param[index] << " ===> " << g <<endl;
    if (nodebugmode) cout << "===> " << param_err[index] << " ===> " << dg <<endl;
    param[index] = g;
    param_err[index] = dg;   
}
void DoReparametrisationQQfit(Double_t* param, Double_t* param_err, Int_t index)//QQfit==1
{
    Double_t a = param[index], da = param_err[index];
    Double_t        q, dq;
    q = hist_mc[0]->IntegralAndError(0, hist_mc[0]->GetNbinsX()+1, dq);
    Double_t       dd, d ;
    d = hist_data[0]->IntegralAndError(0, hist_data[0]->GetNbinsX()+1, dd);
    /*Double_t d = hist_data[0]->GetSum(), b = hist_mc_norad[0]->GetSum(), p = phist_mc_photon[0]->GetSum(), l = hist_mc_rad[0]->GetSum(),
            dd = GetSumError(hist_data[0]), bb = GetSumError(hist_mc_norad[0]), dp = GetSumError(phist_mc_photon[0]), dl = GetSumError(hist_mc_rad[0]);
            //Or simply sqrt(content) or sqrt(sum of w2)?
            */
            //Double_t Dq = a/d, Da = q/d, Dd = -((a q)/d/d)
    Double_t g = (q*a)/d,
            dg = TMath::Sqrt((d*d* da*da* q*q + a*a* (d*d *dq*dq + dd*dd* q*q))/pow(d,4));

             if (nodebugmode) cout << "===> " << param[index] << " ===> " << g <<endl;
    if (nodebugmode) cout << "===> " << param_err[index] << " ===> " << dg <<endl;
    param[index] = g;
    param_err[index] = dg;   
}

void DoComplicatedScale(TH1D* h, Double_t a, Double_t a_err, bool out = false)
{
        h->Scale(a);// Scaled THE VALUE of QQ
        for(Int_t j = 0; j < h->GetNbinsX(); j++)
        {
            Double_t err = h->GetBinError(j+1) / a;
            Double_t add_err1 = pow( (a_err * h->GetBinContent(j+1) / a), 2);
            Double_t add_err2 = pow(err * a, 2);
            h->SetBinError(j+1, TMath::Sqrt(add_err1 + add_err2));
            if(out) dout("***",j,add_err1, add_err2,TMath::Sqrt(add_err1 + add_err2));
        }
}

void MakeCorrection(TH1D* d, TH1D* nr, TH1D* ll=0)
{
    if(!whichCorrection.Contains("NoCorrection"))//Think how to extend it to other case
        {
            if (nodebugmode) dout("correction: ", whichCorrection);
            if (whichCorrection.Contains("IanSg"))
                for (size_t j = 0; j != IanCorrectionSg.size(); ++j) 
                {
                    d->SetBinContent(j+1, d->GetBinContent(j+1) * IanCorrectionSg[j]); 
                    d->SetBinError(j+1, d->GetBinError(j+1) * IanCorrectionSg[j]);
                    if (llCorrectiontoo && ll !=0)
                    {
                        ll->SetBinContent(j+1, ll->GetBinContent(j+1) * IanCorrectionSg[j]);  
                        ll->SetBinError(j+1, ll->GetBinError(j+1) * IanCorrectionSg[j]);                  
                    }
                }
            if (whichCorrection.Contains("PeterSg"))
                for (size_t j = 0; j != PeterCorrectionSg.size(); ++j) 
                {
                    d->SetBinContent(j+1, d->GetBinContent(j+1) * PeterCorrectionSg[j]);  
                    d->SetBinError(j+1, d->GetBinError(j+1) * PeterCorrectionSg[j]);                   
                }
            if (whichCorrection.Contains("PeterBg"))
                for (size_t j = 0; j != PeterCorrectionBg.size(); ++j) 
                {
                    nr->SetBinContent(j+1, nr->GetBinContent(j+1) * PeterCorrectionBg[j]);  
                    nr->SetBinError(j+1, nr->GetBinError(j+1) * PeterCorrectionBg[j]);                   
                }
        }
}

void minuitFunction(int& nDim, double* gout, double& result, double par[], int flg);
//void minuitFunctionBarlowBeeston(int& nDim, double* gout, double& result, double par[], int flg);
//void minuitFunctionGauss(int& nDim, double* gout, double& result, double par[], int flg);
Double_t chi2(double* par, Int_t& ndf, Int_t& left, Int_t& right, TString s_method);

void Chi2StatisticsCheck(Double_t* array, Int_t number_of_bins)
{
    Double_t    mean(0), hmax(0), hmaxbin(-1), hminbin(-1),
                hmin = std::numeric_limits<double>::infinity();
    for(int i = 0; i < number_of_bins; i++)
    {
        mean += array[i];
        if (array[i] < hmin) 
        {
            hmin = array[i];
            hminbin = i+1;
        }
        if (array[i] > hmax) 
        {
            hmax = array[i];
            hmaxbin = i+1;
        }
    }
    mean = mean / number_of_bins;
    dout("mean = ", mean, ", with max =", hmax, "in bin =", hmaxbin, "and min =", hmin, "in bin =", hminbin);
}

  
int main(int argc, char *argv[])
{
    if (false)
    {
        dout("====");
        TH1D * h = new TH1D("temp","temp", 5, 0, 5);
        dout("nbins:",h->GetNbinsX());
        h->Print();
        for(int i = 1; i<=5; i++){
            dout("i bin",i);
                    h->SetBinContent(i,i);}
        h->Print();
        for(int i = 0; i<=6; i++)
            dout("h i", i, h->GetBinContent(i));
        dout("Integral:", h->Integral());
        dout("Integral 2 4:", h->Integral(2, 4));
        exit(1);
    }
    dout("stststst");
    if (q2_cut_global.Contains("gt")) {
            auto init = std::initializer_list<Double_t *>({et_sys_q2_gt_30, eta_sys_q2_gt_30, Q2_sys_q2_gt_30, x_sys_q2_gt_30, et_jet_sys_q2_gt_30, eta_jet_sys_q2_gt_30, xgamma_sys_q2_gt_30, xp_sys_q2_gt_30, dphi_sys_q2_gt_30, deta_sys_q2_gt_30, dphi_e_ph_sys_q2_gt_30, deta_e_ph_sys_q2_gt_30});
            std::copy(init.begin(), init.end(), all_syst);
            //all_syst = {et_sys_q2_gt_30, eta_sys_q2_gt_30, Q2_sys_q2_gt_30, x_sys_q2_gt_30, et_jet_sys_q2_gt_30, eta_jet_sys_q2_gt_30, xgamma_sys_q2_gt_30, xp_sys_q2_gt_30, dphi_sys_q2_gt_30, deta_sys_q2_gt_30, dphi_e_ph_sys_q2_gt_30, deta_e_ph_sys_q2_gt_30};
        }
    else if (q2_cut_global.Contains("lt")){
            auto init = std::initializer_list<Double_t *>({et_sys_q2_lt_30, eta_sys_q2_lt_30, Q2_sys_q2_lt_30, x_sys_q2_lt_30, et_jet_sys_q2_lt_30, eta_jet_sys_q2_lt_30, xgamma_sys_q2_lt_30, xp_sys_q2_lt_30, dphi_sys_q2_lt_30, deta_sys_q2_lt_30, dphi_e_ph_sys_q2_lt_30, deta_e_ph_sys_q2_lt_30});
            std::copy(init.begin(), init.end(), all_syst);
            //all_syst = {et_sys_q2_lt_30, eta_sys_q2_lt_30, Q2_sys_q2_lt_30, x_sys_q2_lt_30, et_jet_sys_q2_lt_30, eta_jet_sys_q2_lt_30, xgamma_sys_q2_lt_30, xp_sys_q2_lt_30, dphi_sys_q2_lt_30, deta_sys_q2_lt_30, dphi_e_ph_sys_q2_lt_30, deta_e_ph_sys_q2_lt_30};
        }
    hist.q2_cut.Form(q2_cut_global);
    debug.open("debug" + q2_cut_global + ".txt");
    if((argc >= 2)) 
    {
        hist.correctiontype.Form((TString)argv[1]);//systJetE+ systJetE- systPhE+ systPhE- systElE+ systElE- systAcc
        if((argc == 2) && (TString)argv[1] != "fit+" && (TString)argv[1] != "fit-") hist.str_selectedoutput.Form("output_selected_" + (TString)argv[1] + hist.q2_cut + ".txt");//Stream class to write on files
        if((argc == 2) && (TString)argv[1] != "fit+" && (TString)argv[1] != "fit-") hist.selectedoutput.open( hist.str_selectedoutput);
        dout("GO!", (TString)argv[1]);
        if ((TString)argv[1] == "fit+")// change the upper range on delta Z for fit systematics
        {
            hist.str_selectedoutput.Form("output_selected_zero" + (TString)argv[1] + hist.q2_cut + ".txt");//Stream class to write on files
            hist.selectedoutput.open( hist.str_selectedoutput);
            hist.correctiontype.Form("zero");
            hist.sys_fit = 1.0;// upper range on delta Z
            sys_fit = 1.0;
            dout("herw", (TString)argv[2], hist.sys_fit);
        }
        else if ((TString)argv[1] == "fit-")// change the upper range on delta Z for fit systematics
        {
            hist.str_selectedoutput.Form("output_selected_zero" + (TString)argv[1] + hist.q2_cut + ".txt");//Stream class to write on files
            hist.selectedoutput.open( hist.str_selectedoutput);
            hist.correctiontype.Form("zero");
            sys_fit = 0.6;// upper range on delta Z
            hist.sys_fit = 0.6;       
        }
    }
    else if ((argc == 1)) 
    {
        hist.correctiontype.Form("zero");//systJetE+ systJetE- systPhE+ systPhE- systElE+ systElE-
        hist.str_selectedoutput.Form("output_selected_zero.txt");//Stream class to write on files
        hist.selectedoutput.open( hist.str_selectedoutput);
    }

    hist.Init();
    gROOT->SetStyle("Plain");
    gStyle->SetTitleBorderSize(0);
    gStyle->SetTitleH(0.08);
    gStyle->SetTitleFont(42);
    gStyle->SetTitleY(0.99);
    gStyle->SetTitleX(0.15);
    gStyle->SetEndErrorSize(5);

    
    //plot acceptance
    hist.PlotAcceptance();
    hist.PlotPurity();


    TFitter* minimizer = new TFitter(1);
    minimizer->SetFCN(minuitFunction);
    {//http://superk.physics.sunysb.edu/~mcgrew/phy310/lectures/phy310-lecture-11-2007.pdf
        double p1 = -1;
         //-1    : No output except from SHOW commands
         //0   : Minimum output (no starting values or intermediate results)
         //1   : Default value, normal output
         //2   : Additional output giving intermediate results.
         //3   : Maximum output, showing progress of minimizations.
        minimizer->ExecuteCommand("SET PRINTOUT", &p1, 1);
    }

    //FITS

    /////////////////////////////////////////////////////
    //
    //          Fit in bins of et
    //
    ///////////////////////////////////////////////////////
    dout("number of events:", hist.hist_data_sum[hist.n_hist - 1]->GetEntries());
    Double_t checksum = 0;
    for(Int_t i = 0; i < number_etbins; i++)// процедура фитирования выполняется на каждый бин по Et
    {
        MakeCorrection(hist.h_deltaz_et_prph_sum[i], hist.h_deltaz_et_norad_sum[i]);
        hist_data[0] = (TH1D*)hist.h_deltaz_et_data_sum[i]->Clone(); 
        checksum += hist_data[0]->GetEntries();
        hist_mc[0] = (TH1D*)hist.h_deltaz_et_prph_sum[i]->Clone();
        hist_mc[0]->Scale(hist.total_luminosity_data / hist.lumi_mc_prph);
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_et_rad_sum[i]->Clone(); 
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_et_norad_sum[i]->Clone(); 
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); 
        hist_mc_photon[0]->Add(hist_mc[0]);//LL + QQ.scale(data)

        if (!nodebugmode && i == 0) dout("0)hist_data[0]->GetSum() ", hist_data[0]->GetSum() );
        if (!nodebugmode && i == 0) dout("0)hist_mc[0]->GetSum() ", hist_mc[0]->GetSum() );
        if (!nodebugmode && i == 0) dout("0)hist_mc_rad[0]->GetSum() ", hist_mc_rad[0]->GetSum() );
        if (!nodebugmode && i == 0) dout("0)hist_mc_norad[0]->GetSum() ", hist_mc_norad[0]->GetSum() );
        if (!nodebugmode && i == 0) dout("0)hist_mc_photon[0]->GetSum() ", hist_mc_photon[0]->GetSum() );

        hist_data[0]->SetName("data");
        hist_mc[0]->SetName("prph");
        hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0]->SetName("photon");

        bool oldway = false;//oldway is wrong because the integrating function is wrong.
        if (QQfit == 0)
        {
            if (oldway)
            {
                Double_t n_mc_photon, n_mc_photon_err, n_data, n_data_err;

                calc_integral_err(hist_mc_photon[0], n_mc_photon, n_mc_photon_err);
                if (!nodebugmode && i == 0) dout("1)calc_integral_err hist_mc_photon[0]: ",  n_mc_photon, n_mc_photon_err);
                scale_hist_to_hist_with_err(hist_mc_photon[0], hist_data[0]);//QQ+LL->data
                scale_hist_to_hist_with_err(hist_mc_norad[0], hist_data[0]);//
                if (!nodebugmode && i == 0) dout("2)hist_mc_norad[0]->GetSum() ", hist_mc_norad[0]->GetSum() );
                if (!nodebugmode && i == 0) dout("2)hist_mc_photon[0]->GetSum() ", hist_mc_photon[0]->GetSum() );

                hist_mc[0]->Scale(hist_data[0]->GetSum()/n_mc_photon);
                hist_mc_rad[0]->Scale(hist_data[0]->GetSum()/n_mc_photon);
                if (!nodebugmode && i == 0) dout("3)hist_mc[0]->GetSum() ", hist_mc[0]->GetSum() );
                if (!nodebugmode && i == 0) dout("3)hist_mc_rad[0]->GetSum() ", hist_mc_rad[0]->GetSum() );
                if (!nodebugmode && i == 0) dout("3)sum:", hist_mc_rad[0]->GetSum() + hist_mc[0]->GetSum() );                
            }
            else
            {
                hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());//Photon = [LL + QQ.Scale()].scale(DATA/Photon)

                hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
                hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
                
                //for the CS further painting...
                hist.h_deltaz_et_prph_sum[i]->Scale((hist.h_deltaz_et_data_sum[i]->GetSum() - hist.h_deltaz_et_rad_sum[i]->GetSum()) / hist.h_deltaz_et_prph_sum[i]->GetSum());
                hist.h_deltaz_et_norad_sum[i]->Scale((hist.h_deltaz_et_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_et_rad_sum[i]->GetSum()) / hist.h_deltaz_et_norad_sum[i]->GetSum()); 
    
            }
        }
        else 
        {
            if (fitWithLLinBg == 0)//data =LL’ +  QQ’ * a + bg’ * (1- a) //data = QQ’ * a + bg’ * (1 - a)
            {
                hist_mc[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
                hist.h_deltaz_et_prph_sum[i]->Scale((hist.h_deltaz_et_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_et_rad_sum[i]->GetSum()) / hist.h_deltaz_et_prph_sum[i]->GetSum());

                hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
                hist.h_deltaz_et_norad_sum[i]->Scale((hist.h_deltaz_et_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_et_rad_sum[i]->GetSum()) / hist.h_deltaz_et_norad_sum[i]->GetSum()); 
            }
            else if (fitWithLL == 0 && fitWithLLinBg == 1)//data = QQ’ * a + bg’’ * (1 - a)
            {
                hist_mc[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
                hist.h_deltaz_et_prph_sum[i]->Scale((hist.h_deltaz_et_data_sum[i]->GetSum() - fitWithLL * hist.h_deltaz_et_rad_sum[i]->GetSum()) / hist.h_deltaz_et_prph_sum[i]->GetSum());

                hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
                hist.h_deltaz_et_norad_sum[i]->Scale((hist.h_deltaz_et_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_et_rad_sum[i]->GetSum()) / hist.h_deltaz_et_norad_sum[i]->GetSum()); 
            }
        }
       

        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD", 0, 0);
        minimizer->ExecuteCommand("HESSE", 0, 0);
        minimizer->ExecuteCommand("MINOS", 0, 0);    
        param_et[i] = minimizer->GetParameter(0); //процедура минимизации
        param_err_et[i] = minimizer->GetParError(0);
        Double_t par[1]; par[0] = param_et[i];
        chi2_et[i] = chi2(par, dof_et[i], left_et[i], right_et[i], chi_method) / 
                    dof_et[i];// достаем хи-квадрат dof = degries of freedom
        
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        if (nodebugmode) dout("Fit in bins of et: from bin ", GetFitRange(hist_data[0], true),"to", GetFitRange(hist_data[0], false), "(not including)");      
        
        //for(Int_t bin = hist_data[0]->FindBin(0.) - 1; bin < hist_data[0]->FindBin(0.6) + 4 - hist_data[0]->FindBin(0.) + 1; bin++) //? 02/07/15
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++) //? 02/07/15
        {
            //if (nodebugmode) cout<<"bin: "<<bin<<endl;
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);
            
            //TMath::Power(v_d - par[0] * v_ph - (1 - par[0]) * v_bg, 2) 
            Double_t chi2_bin = (v_d - par[0] * v_ph - (1 - par[0]) * v_bg) \
                              * (v_d - par[0] * v_ph - (1 - par[0]) * v_bg)\
                    / (s_d * s_d + par[0] * par[0] * s_ph * s_ph + (1. - par[0]) * (1. - par[0]) * s_bg * s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_et[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; sc.Form("chi2_et_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_et[i]->Draw("HIST TEXT");//https://root.cern.ch/root/html/THistPainter.html
        c->Print(sc + ".eps");
        delete c;
        //if (nodebugmode) cout << "total chi2 = " << total_chi2 << endl;
        //if (nodebugmode) cout << "... per dof = " << total_chi2 / Double_t(dof-2) << endl;
        // ----------- end chi2 per bin
        
        //leftet[i]++; //? зачем
        param_et_PhotonsFit[i] = param_et[i];
        param_err_et_PhotonsFit[i] = param_err_et[i];
        param_et_PhotonsFitforQQ[i] = param_et[i];
        param_err_et_PhotonsFitforQQ[i] = param_err_et[i];

        if (QQfit == 0 && oldway)
        {
            hist.h_deltaz_et_norad_sum[i]->Scale(0.);//bg = 0
            hist.h_deltaz_et_norad_sum[i]->Add(hist_mc_norad[0], 1-param_et[i]);//bg = bg.scale(data)
            hist.h_deltaz_et_photon_sum[i] = (TH1D*)hist.h_deltaz_et_prph_sum[i]->Clone(); //photons = QQ
            hist.h_deltaz_et_photon_sum[i]->SetName((TString)hist.h_deltaz_et_prph_sum[i]->GetName()+"photon");
            hist.h_deltaz_et_photon_sum[i]->Scale(0.);//photons = 0
            hist.h_deltaz_et_photon_sum[i]->Add(hist_mc_photon[0], param_et[i]);////photons = photons.scale(data)*a
            hist.h_deltaz_et_rad_sum[i]->Scale(0.);//LL =0
            hist.h_deltaz_et_rad_sum[i]->Add(hist_mc_rad[0], param_et[i]);//LL = LL'*a , LL' = LL.scale(photon?)
            hist.h_deltaz_et_prph_sum[i]->Scale(0.);
            hist.h_deltaz_et_prph_sum[i]->Add(hist_mc[0], param_et[i]);
            hist.h_deltaz_et_res[i]->Scale(0.);//Add(hist.h_deltaz_et_norad_sum[i]);
            hist.h_deltaz_et_res[i]->Add(hist_mc_photon[0], param_et[i]);
            hist.h_deltaz_et_res[i]->Add(hist_mc_norad[0], 1-param_et[i]);
        }
        else if (!oldway)
        {
            
            if (QQfit==0)//photon*a+bg(1-a)
            {
                    DoReparametrisation(param_et, param_err_et, i);
                    DoReparametrisationforQQ(param_et_PhotonsFitforQQ, param_err_et_PhotonsFitforQQ, i);
            }
            else if(QQfit != 0)
                DoReparametrisationQQfit(param_et, param_err_et, i);
            
            DoComplicatedScale(hist.h_deltaz_et_norad_sum[i], 1 - param_et_PhotonsFit[i], param_err_et_PhotonsFit[i]);
                       if (i==0 && !nodebugmode)
                {
                    dout("qq error, bin 3:",hist.h_deltaz_et_prph_sum[i]->GetBinError(3));
                    dout("rad error, bin 3:",hist.h_deltaz_et_rad_sum[i]->GetBinError(3));
                    dout("bg error, bin 3:",hist.h_deltaz_et_norad_sum[i]->GetBinError(3));
                    dout("param_et_PhotonsFitforQQ[i], param_et_PhotonsFitforQQ[i]:",param_et_PhotonsFitforQQ[i], param_et_PhotonsFitforQQ[i]);
                }
            bool temp = false;
            if (i==0) temp = true;
            DoComplicatedScale(hist.h_deltaz_et_prph_sum[i], param_et_PhotonsFitforQQ[i], param_err_et_PhotonsFit[i],temp);
                       if (i==0 && !nodebugmode)
                {
                    dout("qq error, bin 3:",hist.h_deltaz_et_prph_sum[i]->GetBinError(3));
                    dout("rad error, bin 3:",hist.h_deltaz_et_rad_sum[i]->GetBinError(3));
                    dout("bg error, bin 3:",hist.h_deltaz_et_norad_sum[i]->GetBinError(3));
                }

            if (QQfit == 1 && fitWithLL== 0) hist.h_deltaz_et_res[i]->Scale(0);
            hist.h_deltaz_et_res[i]->Add(hist.h_deltaz_et_norad_sum[i]);
            hist.h_deltaz_et_res[i]->Add(hist.h_deltaz_et_prph_sum[i]);
        }

       
        if (nodebugmode) dout("After fit in Et bins: n_data = ", hist_data[0]->GetSum() ,\
            ", n_photon =", hist_mc_photon[0]->GetSum() * param_et[i], 
            ", n_bg = " , hist_mc_norad[0]->GetSum() * (1-param_et[i]) \
            , ", h.n_bg = " , hist.h_deltaz_et_norad_sum[i]->GetSum() \
            , ", h.n_rad = " , hist.h_deltaz_et_rad_sum[i]->GetSum() \
            , ", h.n_prph = " , hist.h_deltaz_et_prph_sum[i]->GetSum() \
            , ", n_res = " , hist.h_deltaz_et_res[i]->GetSum());
        if (i==0 && !nodebugmode) dout(  "par in bin et ", i, ": ", param_et[i], " +- ", param_err_et[i], ", chi2/dof = ", chi2_et[i] );

    }
    dout("checksum = ", checksum);
    dout("et:");
    Chi2StatisticsCheck(chi2_et, number_etbins);

    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of eta
    //
    ///////////////////////////////////////////////////////
    for(Int_t i=0; i<number_etabins; i++)
    {      
        MakeCorrection(hist.h_deltaz_eta_prph_sum[i], hist.h_deltaz_eta_norad_sum[i]);

        hist_data[0] = (TH1D*)hist.h_deltaz_eta_data_sum[i]->Clone(); 
        hist_mc[0] = (TH1D*)hist.h_deltaz_eta_prph_sum[i]->Clone(); 
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_eta_rad_sum[i]->Clone(); 
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_eta_norad_sum[i]->Clone(); 
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); 
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);//LL + QQ.Scale(total_luminosity_data/lumi_mc_prph)
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());//Photon = [LL + QQ.Scale()].scale(DATA/Photon)

        hist_data[0]->SetName("data");
        hist_mc[0]->SetName("prph");
        hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0]->SetName("photon");// LL

        if (QQfit == 0)
        {
            //эта переменная все равно в фите не будет учавствовать. но для построения контрольного графика это не верно.
            hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            //hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
            hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            
            //for the CS further painting...
            hist.h_deltaz_eta_prph_sum[i]->Scale((hist.h_deltaz_eta_data_sum[i]->GetSum() - hist.h_deltaz_eta_rad_sum[i]->GetSum()) / hist.h_deltaz_eta_prph_sum[i]->GetSum());
            hist.h_deltaz_eta_norad_sum[i]->Scale((hist.h_deltaz_eta_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_eta_rad_sum[i]->GetSum()) / hist.h_deltaz_eta_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLLinBg == 0)//data =LL’ +  QQ’ * a + bg’ * (1- a) //data = QQ’ * a + bg’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_eta_prph_sum[i]->Scale((hist.h_deltaz_eta_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_eta_rad_sum[i]->GetSum()) / hist.h_deltaz_eta_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_eta_norad_sum[i]->Scale((hist.h_deltaz_eta_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_eta_rad_sum[i]->GetSum()) / hist.h_deltaz_eta_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLL == 0 && fitWithLLinBg == 1)//data = QQ’ * a + bg’’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_eta_prph_sum[i]->Scale((hist.h_deltaz_eta_data_sum[i]->GetSum() - fitWithLL * hist.h_deltaz_eta_rad_sum[i]->GetSum()) / hist.h_deltaz_eta_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_eta_norad_sum[i]->Scale((hist.h_deltaz_eta_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_eta_rad_sum[i]->GetSum()) / hist.h_deltaz_eta_norad_sum[i]->GetSum()); 
        }
        
        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);   
        param_eta[i] = minimizer->GetParameter(0);
        param_err_eta[i] = minimizer->GetParError(0);
        Double_t par[1]; 
        par[0] = param_eta[i];
        chi2_eta[i] = chi2(par, dof_eta[i], left_eta[i], right_eta[i], chi_method) / dof_eta[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_eta[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; 
        sc.Form("chi2_eta_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_eta[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;


        param_eta_PhotonsFit[i] = param_eta[i];
        param_err_eta_PhotonsFit[i] = param_err_eta[i];
        param_eta_PhotonsFitforQQ[i] = param_eta[i];
        param_err_eta_PhotonsFitforQQ[i] = param_err_eta[i];
        //DOIT
        if (QQfit==0)//photon*a+bg(1-a)
        {
                DoReparametrisation(param_eta, param_err_eta, i);
                DoReparametrisationforQQ(param_eta_PhotonsFitforQQ, param_err_eta_PhotonsFitforQQ, i);
        }
        else if(QQfit != 0)
            DoReparametrisationQQfit(param_eta, param_err_eta, i);
        
        DoComplicatedScale(hist.h_deltaz_eta_norad_sum[i], 1 - param_eta_PhotonsFit[i], param_err_eta_PhotonsFit[i]);
        DoComplicatedScale(hist.h_deltaz_eta_prph_sum[i], param_eta_PhotonsFitforQQ[i], param_err_eta_PhotonsFitforQQ[i]);

        if (QQfit == 1 && fitWithLL== 0) hist.h_deltaz_eta_res[i]->Scale(0);
        hist.h_deltaz_eta_res[i]->Add(hist.h_deltaz_eta_norad_sum[i]);
        hist.h_deltaz_eta_res[i]->Add(hist.h_deltaz_eta_prph_sum[i]);

    }
    dout("eta:");
    Chi2StatisticsCheck(chi2_eta, number_etabins);

    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of q2
    //
    ///////////////////////////////////////////////////////
    debug << "Q2 comparison h_deltaz_q2_data_sum[i]" << endl;
    for(Int_t i=0; i<number_Q2bins; i++)
    { 
        MakeCorrection(hist.h_deltaz_q2_prph_sum[i], hist.h_deltaz_q2_norad_sum[i]);

        hist_data[0] = (TH1D*)hist.h_deltaz_q2_data_sum[i]->Clone(); hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_q2_prph_sum[i]->Clone(); hist_mc[0]->SetName("prph");
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_q2_rad_sum[i]->Clone(); hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_q2_norad_sum[i]->Clone(); hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); hist_mc_photon[0]->SetName("photon");
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

        debug << i << ")" << hist_data[0]->GetSum() << endl;


        if (QQfit == 0)
        {
            //эта переменная все равно в фите не будет учавствовать. но для построения контрольного графика это не верно.
            hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            //hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
            hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            
            //for the CS further painting...
            hist.h_deltaz_q2_prph_sum[i]->Scale((hist.h_deltaz_q2_data_sum[i]->GetSum() - hist.h_deltaz_q2_rad_sum[i]->GetSum()) / hist.h_deltaz_q2_prph_sum[i]->GetSum());
            hist.h_deltaz_q2_norad_sum[i]->Scale((hist.h_deltaz_q2_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_q2_rad_sum[i]->GetSum()) / hist.h_deltaz_q2_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLLinBg == 0)//data =LL’ +  QQ’ * a + bg’ * (1- a) //data = QQ’ * a + bg’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_q2_prph_sum[i]->Scale((hist.h_deltaz_q2_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_q2_rad_sum[i]->GetSum()) / hist.h_deltaz_q2_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_q2_norad_sum[i]->Scale((hist.h_deltaz_q2_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_q2_rad_sum[i]->GetSum()) / hist.h_deltaz_q2_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLL == 0 && fitWithLLinBg == 1)//data = QQ’ * a + bg’’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_q2_prph_sum[i]->Scale((hist.h_deltaz_q2_data_sum[i]->GetSum() - fitWithLL * hist.h_deltaz_q2_rad_sum[i]->GetSum()) / hist.h_deltaz_q2_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_q2_norad_sum[i]->Scale((hist.h_deltaz_q2_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_q2_rad_sum[i]->GetSum()) / hist.h_deltaz_q2_norad_sum[i]->GetSum()); 
        }
        
        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);    
        param_q2[i] = minimizer->GetParameter(0);
        param_err_q2[i] = minimizer->GetParError(0);
        Double_t par[1]; par[0] = param_q2[i];
        chi2_q2[i] = chi2(par, dof_q2[i], left_q2[i], right_q2[i], chi_method) / dof_q2[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_Q2[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; sc.Form("chi2_q2_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_Q2[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;

        param_q2_PhotonsFit[i] = param_q2[i];
        param_err_q2_PhotonsFit[i] = param_err_q2[i];
        param_q2_PhotonsFitforQQ[i] = param_q2[i];
        param_err_q2_PhotonsFitforQQ[i] = param_err_q2[i];
        //DOIT
        if (QQfit==0)
        {
                DoReparametrisation(param_q2, param_err_q2, i);
                DoReparametrisationforQQ(param_q2_PhotonsFitforQQ, param_err_q2_PhotonsFitforQQ, i);
        }
        else if(QQfit != 0)
            DoReparametrisationQQfit(param_q2, param_err_q2, i);
        
        DoComplicatedScale(hist.h_deltaz_q2_norad_sum[i], 1 - param_q2_PhotonsFit[i], param_err_q2_PhotonsFit[i]);
        DoComplicatedScale(hist.h_deltaz_q2_prph_sum[i], param_q2_PhotonsFitforQQ[i], param_err_q2_PhotonsFitforQQ[i]);

        if (QQfit == 1 && fitWithLL== 0) hist.h_deltaz_q2_res[i]->Scale(0);
        hist.h_deltaz_q2_res[i]->Add(hist.h_deltaz_q2_norad_sum[i]);
        hist.h_deltaz_q2_res[i]->Add(hist.h_deltaz_q2_prph_sum[i]);
    }

    dout("q2:");
    Chi2StatisticsCheck(chi2_q2, number_Q2bins);
    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of x
    //
    ///////////////////////////////////////////////////////
    for(Int_t i=0; i<number_xbins; i++)
    { 
        MakeCorrection(hist.h_deltaz_x_prph_sum[i], hist.h_deltaz_x_norad_sum[i]);

        hist_data[0] = (TH1D*)hist.h_deltaz_x_data_sum[i]->Clone(); hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_x_prph_sum[i]->Clone(); hist_mc[0]->SetName("prph");
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_x_rad_sum[i]->Clone(); hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_x_norad_sum[i]->Clone(); hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); hist_mc_photon[0]->SetName("photon");
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

        if (QQfit == 0)
        {
            //эта переменная все равно в фите не будет учавствовать. но для построения контрольного графика это не верно.
            hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            //hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
            hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            
            //for the CS further painting...
            hist.h_deltaz_x_prph_sum[i]->Scale((hist.h_deltaz_x_data_sum[i]->GetSum() - hist.h_deltaz_x_rad_sum[i]->GetSum()) / hist.h_deltaz_x_prph_sum[i]->GetSum());
            hist.h_deltaz_x_norad_sum[i]->Scale((hist.h_deltaz_x_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_x_rad_sum[i]->GetSum()) / hist.h_deltaz_x_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLLinBg == 0)//data =LL’ +  QQ’ * a + bg’ * (1- a) //data = QQ’ * a + bg’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_x_prph_sum[i]->Scale((hist.h_deltaz_x_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_x_rad_sum[i]->GetSum()) / hist.h_deltaz_x_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_x_norad_sum[i]->Scale((hist.h_deltaz_x_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_x_rad_sum[i]->GetSum()) / hist.h_deltaz_x_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLL == 0 && fitWithLLinBg == 1)//data = QQ’ * a + bg’’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_x_prph_sum[i]->Scale((hist.h_deltaz_x_data_sum[i]->GetSum() - fitWithLL * hist.h_deltaz_x_rad_sum[i]->GetSum()) / hist.h_deltaz_x_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_x_norad_sum[i]->Scale((hist.h_deltaz_x_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_x_rad_sum[i]->GetSum()) / hist.h_deltaz_eta_norad_sum[i]->GetSum()); 
        }

        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);    
        param_x[i] = minimizer->GetParameter(0);
        param_err_x[i] = minimizer->GetParError(0);
        Double_t par[1]; par[0] = param_x[i];
        chi2_x[i] = chi2(par, dof_x[i], left_x[i], right_x[i], chi_method) / dof_x[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_x[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; sc.Form("chi2_x_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_x[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;
        
        param_x_PhotonsFit[i] = param_x[i];
        param_err_x_PhotonsFit[i] = param_err_x[i];
        param_x_PhotonsFitforQQ[i] = param_x[i];
        param_err_x_PhotonsFitforQQ[i] = param_err_x[i];
        //DOIT
        if (QQfit==0)
        {
                DoReparametrisation(param_x, param_err_x, i);
                DoReparametrisationforQQ(param_x_PhotonsFitforQQ, param_err_x_PhotonsFitforQQ, i);
        }
        else if(QQfit != 0)
            DoReparametrisationQQfit(param_x, param_err_x, i);
        
        DoComplicatedScale(hist.h_deltaz_x_norad_sum[i], 1 - param_x_PhotonsFit[i], param_err_x_PhotonsFit[i]);
        DoComplicatedScale(hist.h_deltaz_x_prph_sum[i], param_x_PhotonsFitforQQ[i], param_err_x_PhotonsFitforQQ[i]);

        if (QQfit == 1 && fitWithLL== 0) hist.h_deltaz_x_res[i]->Scale(0);
        hist.h_deltaz_x_res[i]->Add(hist.h_deltaz_x_norad_sum[i]);
        hist.h_deltaz_x_res[i]->Add(hist.h_deltaz_x_prph_sum[i]);
    }

    dout("x:");
    Chi2StatisticsCheck(chi2_x, number_xbins);
    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of et_jet
    //
    ///////////////////////////////////////////////////////
    for(Int_t i=0; i<number_et_jetbins; i++)
    { 
        MakeCorrection(hist.h_deltaz_et_jet_prph_sum[i], hist.h_deltaz_et_jet_norad_sum[i]);

        hist_data[0] = (TH1D*)hist.h_deltaz_et_jet_data_sum[i]->Clone(); hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_et_jet_prph_sum[i]->Clone(); hist_mc[0]->SetName("prph");
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_et_jet_rad_sum[i]->Clone(); hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_et_jet_norad_sum[i]->Clone(); hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); hist_mc_photon[0]->SetName("photon");
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

        if (QQfit == 0)
        {
            //эта переменная все равно в фите не будет учавствовать. но для построения контрольного графика это не верно.
            hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            //hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
            hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            
            //for the CS further painting...
            hist.h_deltaz_et_jet_prph_sum[i]->Scale((hist.h_deltaz_et_jet_data_sum[i]->GetSum() - hist.h_deltaz_et_jet_rad_sum[i]->GetSum()) / hist.h_deltaz_et_jet_prph_sum[i]->GetSum());
            hist.h_deltaz_et_jet_norad_sum[i]->Scale((hist.h_deltaz_et_jet_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_et_jet_rad_sum[i]->GetSum()) / hist.h_deltaz_et_jet_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLLinBg == 0)//data =LL’ +  QQ’ * a + bg’ * (1- a) //data = QQ’ * a + bg’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_et_jet_prph_sum[i]->Scale((hist.h_deltaz_et_jet_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_et_jet_rad_sum[i]->GetSum()) / hist.h_deltaz_et_jet_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_et_jet_norad_sum[i]->Scale((hist.h_deltaz_et_jet_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_et_jet_rad_sum[i]->GetSum()) / hist.h_deltaz_et_jet_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLL == 0 && fitWithLLinBg == 1)//data = QQ’ * a + bg’’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_et_jet_prph_sum[i]->Scale((hist.h_deltaz_et_jet_data_sum[i]->GetSum() - fitWithLL * hist.h_deltaz_et_jet_rad_sum[i]->GetSum()) / hist.h_deltaz_et_jet_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_et_jet_norad_sum[i]->Scale((hist.h_deltaz_et_jet_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_et_jet_rad_sum[i]->GetSum()) / hist.h_deltaz_et_jet_norad_sum[i]->GetSum()); 
        }
        
        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);   
        param_et_jet[i] = minimizer->GetParameter(0);
        param_err_et_jet[i] = minimizer->GetParError(0);
        Double_t par[1]; par[0] = param_et_jet[i];
        chi2_et_jet[i] = chi2(par, dof_et_jet[i], left_et_jet[i], right_et_jet[i], chi_method) / dof_et_jet[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_et_jet[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; sc.Form("chi2_et_jet_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_et_jet[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;
        
        param_et_jet_PhotonsFit[i] = param_et_jet[i];
        param_err_et_jet_PhotonsFit[i] = param_err_et_jet[i];
        param_et_jet_PhotonsFitforQQ[i] = param_et_jet[i];
        param_err_et_jet_PhotonsFitforQQ[i] = param_err_et_jet[i];
        //DOIT
        if (QQfit==0)
        {
                DoReparametrisation(param_et_jet, param_err_et_jet, i);
                DoReparametrisationforQQ(param_et_jet_PhotonsFitforQQ, param_err_et_jet_PhotonsFitforQQ, i);
        }
        else if(QQfit != 0)
            DoReparametrisationQQfit(param_et_jet, param_err_et_jet, i);
        
        DoComplicatedScale(hist.h_deltaz_et_jet_norad_sum[i], 1 - param_et_jet_PhotonsFit[i], param_err_et_jet_PhotonsFit[i]);
        DoComplicatedScale(hist.h_deltaz_et_jet_prph_sum[i], param_et_jet_PhotonsFitforQQ[i], param_err_et_jet_PhotonsFitforQQ[i]);

        if (QQfit == 1 && fitWithLL== 0) hist.h_deltaz_et_jet_res[i]->Scale(0);
        hist.h_deltaz_et_jet_res[i]->Add(hist.h_deltaz_et_jet_norad_sum[i]);
        hist.h_deltaz_et_jet_res[i]->Add(hist.h_deltaz_et_jet_prph_sum[i]);
    }

    dout("et_jet:");
    Chi2StatisticsCheck(chi2_et, number_et_jetbins);
    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of eta_jet
    //
    ///////////////////////////////////////////////////////
    for(Int_t i=0; i<number_eta_jetbins; i++)
    { 
        MakeCorrection(hist.h_deltaz_eta_jet_prph_sum[i], hist.h_deltaz_eta_jet_norad_sum[i]);

        hist_data[0] = (TH1D*)hist.h_deltaz_eta_jet_data_sum[i]->Clone(); hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_eta_jet_prph_sum[i]->Clone(); hist_mc[0]->SetName("prph");
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_eta_jet_rad_sum[i]->Clone(); hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_eta_jet_norad_sum[i]->Clone(); hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); hist_mc_photon[0]->SetName("photon");
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

        if (QQfit == 0)
        {
            //эта переменная все равно в фите не будет учавствовать. но для построения контрольного графика это не верно.
            hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            //hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
            hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            
            //for the CS further painting...
            hist.h_deltaz_eta_jet_prph_sum[i]->Scale((hist.h_deltaz_eta_jet_data_sum[i]->GetSum() - hist.h_deltaz_eta_jet_rad_sum[i]->GetSum()) / hist.h_deltaz_eta_jet_prph_sum[i]->GetSum());
            hist.h_deltaz_eta_jet_norad_sum[i]->Scale((hist.h_deltaz_eta_jet_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_eta_jet_rad_sum[i]->GetSum()) / hist.h_deltaz_eta_jet_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLLinBg == 0)//data =LL’ +  QQ’ * a + bg’ * (1- a) //data = QQ’ * a + bg’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_eta_jet_prph_sum[i]->Scale((hist.h_deltaz_eta_jet_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_eta_jet_rad_sum[i]->GetSum()) / hist.h_deltaz_eta_jet_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_eta_jet_norad_sum[i]->Scale((hist.h_deltaz_eta_jet_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_eta_jet_rad_sum[i]->GetSum()) / hist.h_deltaz_eta_jet_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLL == 0 && fitWithLLinBg == 1)//data = QQ’ * a + bg’’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_eta_jet_prph_sum[i]->Scale((hist.h_deltaz_eta_jet_data_sum[i]->GetSum() - fitWithLL * hist.h_deltaz_eta_jet_rad_sum[i]->GetSum()) / hist.h_deltaz_eta_jet_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_eta_jet_norad_sum[i]->Scale((hist.h_deltaz_eta_jet_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_eta_jet_rad_sum[i]->GetSum()) / hist.h_deltaz_eta_jet_norad_sum[i]->GetSum()); 
        }


        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);   
        param_eta_jet[i] = minimizer->GetParameter(0);
        param_err_eta_jet[i] = minimizer->GetParError(0);
        Double_t par[1]; par[0] = param_eta_jet[i];
        chi2_eta_jet[i] = chi2(par, dof_eta_jet[i], left_eta_jet[i], right_eta_jet[i], chi_method) / dof_eta_jet[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_eta_jet[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; sc.Form("chi2_eta_jet_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_eta_jet[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;
        param_eta_jet_PhotonsFit[i] = param_eta_jet[i];
        param_err_eta_jet_PhotonsFit[i] = param_err_eta_jet[i];
        param_eta_jet_PhotonsFitforQQ[i] = param_eta_jet[i];
        param_err_eta_jet_PhotonsFitforQQ[i] = param_err_eta_jet[i];
        //DOIT
        if (QQfit==0)
        {
                DoReparametrisation(param_eta_jet, param_err_eta_jet, i);
                DoReparametrisationforQQ(param_eta_jet_PhotonsFitforQQ, param_err_eta_jet_PhotonsFitforQQ, i);
        }
        else if(QQfit != 0)
            DoReparametrisationQQfit(param_eta_jet, param_err_eta_jet, i);
        
        DoComplicatedScale(hist.h_deltaz_eta_jet_norad_sum[i], 1 - param_eta_jet_PhotonsFit[i], param_err_eta_jet_PhotonsFit[i]);
        DoComplicatedScale(hist.h_deltaz_eta_jet_prph_sum[i], param_eta_jet_PhotonsFitforQQ[i], param_err_eta_jet_PhotonsFitforQQ[i]);

        if (QQfit == 1 && fitWithLL== 0) hist.h_deltaz_eta_jet_res[i]->Scale(0);
        hist.h_deltaz_eta_jet_res[i]->Add(hist.h_deltaz_eta_jet_norad_sum[i]);
        hist.h_deltaz_eta_jet_res[i]->Add(hist.h_deltaz_eta_jet_prph_sum[i]);//if (nodebugmode) cout << "par in bin eta_jet " << i << ": " << param_eta_jet[i] << " +- " << param_err_eta_jet[i] << ", chi2/dof = " << chi2_eta_jet[i]  << endl;
    }

    dout("eta_jet:");
    Chi2StatisticsCheck(chi2_eta_jet, number_eta_jetbins);
    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of xgamma
    //
    ///////////////////////////////////////////////////////
    /*
        for (Int_t i = 0; i< hist.hist_data_sum[1]->GetNbinsX();i++)
        {
            if (nodebugmode) dout("hist.hist_data_sum[1]->GetBinContent(",i+1,")", \
                hist.hist_data_sum[1]->GetBinContent(i+1)*hist.hist_data_sum[1]->GetBinWidth(i+1));
        }
        for (Int_t i = 0; i< hist.hist_data_sum[1]->GetNbinsX();i++)
        {
            if (nodebugmode) dout("hist.h_deltaz_xgamma_data_sum[i]->GetSum()", \
                TMath::Sqrt(hist.h_deltaz_xgamma_data_sum[i]->Integral(0, hist.h_deltaz_xgamma_data_sum[i]->GetNbinsX() +1)));
                //hist.h_deltaz_xgamma_data_sum[i]->Integral(0, hist.h_deltaz_xgamma_data_sum[i]->GetNbinsX() +1));
        }
    */
    for(Int_t i=0; i < number_xgamma_bins; i++)
    { 
        MakeCorrection(hist.h_deltaz_xgamma_prph_sum[i], hist.h_deltaz_xgamma_norad_sum[i]);

        hist_data[0] = (TH1D*)hist.h_deltaz_xgamma_data_sum[i]->Clone(); 
        hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_xgamma_prph_sum[i]->Clone(); 
        hist_mc[0]->SetName("prph");//QQ
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_xgamma_rad_sum[i]->Clone(); 
        hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_xgamma_norad_sum[i]->Clone(); 
        hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); 
        hist_mc_photon[0]->SetName("photon");
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);//LL + QQ'
        b_scale = hist_data[0]->GetSum() / hist_mc_photon[0]->GetSum();
        d_scale = (hist_data[0]->GetSum() )/hist_mc[0]->GetSum();
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

        if (i+1 == 1 )
            if (nodebugmode) cout <<"qq: " << hist_mc[0]->GetEntries() << " or " << hist_mc[0]->Integral(1, hist_mc[0]->GetNbinsX()) << endl;

        if (QQfit == 0)
        {
            //эта переменная все равно в фите не будет учавствовать. но для построения контрольного графика это не верно.
            hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            //hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
            hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            
            //for the CS further painting...
            hist.h_deltaz_xgamma_prph_sum[i]->Scale((hist.h_deltaz_xgamma_data_sum[i]->GetSum() - hist.h_deltaz_xgamma_rad_sum[i]->GetSum()) / hist.h_deltaz_xgamma_prph_sum[i]->GetSum());
            hist.h_deltaz_xgamma_norad_sum[i]->Scale((hist.h_deltaz_xgamma_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_xgamma_rad_sum[i]->GetSum()) / hist.h_deltaz_xgamma_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLLinBg == 0)//data =LL’ +  QQ’ * a + bg’ * (1- a) //data = QQ’ * a + bg’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_xgamma_prph_sum[i]->Scale((hist.h_deltaz_xgamma_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_xgamma_rad_sum[i]->GetSum()) / hist.h_deltaz_xgamma_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_xgamma_norad_sum[i]->Scale((hist.h_deltaz_xgamma_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_xgamma_rad_sum[i]->GetSum()) / hist.h_deltaz_xgamma_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLL == 0 && fitWithLLinBg == 1)//data = QQ’ * a + bg’’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_xgamma_prph_sum[i]->Scale((hist.h_deltaz_xgamma_data_sum[i]->GetSum() - fitWithLL * hist.h_deltaz_xgamma_rad_sum[i]->GetSum()) / hist.h_deltaz_xgamma_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_xgamma_norad_sum[i]->Scale((hist.h_deltaz_xgamma_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_xgamma_rad_sum[i]->GetSum()) / hist.h_deltaz_xgamma_norad_sum[i]->GetSum()); 
        }
        //if (i+1 == number_xgamma_bins )
        //    if (nodebugmode) cout <<"qq': " << hist_mc[0]->GetEntries() << " or " << hist_mc[0]->Integral(1, hist_mc[0]->GetNbinsX()) << endl;        
        //hist.h_deltaz_xgamma_prph_sum[i]->Scale((hist.h_deltaz_xgamma_data_sum[i]->GetSum() - hist.h_deltaz_xgamma_rad_sum[i]->GetSum()) / hist.h_deltaz_xgamma_prph_sum[i]->GetSum());
        //hist.h_deltaz_xgamma_norad_sum[i]->Scale((hist.h_deltaz_xgamma_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_xgamma_rad_sum[i]->GetSum()) / hist.h_deltaz_xgamma_norad_sum[i]->GetSum());
        
        {
                if (nodebugmode) dout("hist.hist_mc_sum[0]->GetBinContent(",i+1,")", \
                                hist.hist_mc_sum[1]->GetBinContent(i+1)*hist.hist_mc_sum[1]->GetBinWidth(i+1));
                if (nodebugmode) dout("hist.h_deltaz_xgamma_prph_sum[i]->GetSum()", \
                                hist.h_deltaz_xgamma_prph_sum[i]->Integral(0, hist.h_deltaz_xgamma_prph_sum[i]->GetNbinsX() +1));

                if (nodebugmode) dout("hist.hist_mc_photon_sum[0]->GetBinContent(",i+1,")", \
                                hist.hist_mc_photon_sum[1]->GetBinContent(i+1)*hist.hist_mc_photon_sum[1]->GetBinWidth(i+1));
                if (nodebugmode) dout("hist_mc_photon[0]", \
                                hist_mc_photon[0]->Integral(0, hist_mc_photon[0]->GetNbinsX() +1));
        }
       
        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);   
        param_xgamma[i] = minimizer->GetParameter(0);
        param_err_xgamma[i] = minimizer->GetParError(0);
        Double_t par[1]; 
        par[0] = param_xgamma[i];
        chi2_xgamma[i] = chi2(par, dof_xgamma[i], left_xgamma[i], right_xgamma[i], chi_method) / dof_xgamma[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_xgamma[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; sc.Form("chi2_xgamma_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_xgamma[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;


        param_xgamma_PhotonsFit[i] = param_xgamma[i];
        param_err_xgamma_PhotonsFit[i] = param_err_xgamma[i];
        param_xgamma_PhotonsFitforQQ[i] = param_xgamma[i];
        param_err_xgamma_PhotonsFitforQQ[i] = param_err_xgamma[i];
        dout("xgamma found parameter:",param_xgamma[i],"+/-",param_err_xgamma[i]);
        if (nodebugmode) cout<< "param xgamma after fit " << i << ") " << param_xgamma[i] <<"+/-"<< param_err_xgamma[i]<< endl;
        if (QQfit == 0)
        {
            DoReparametrisation(1, param_xgamma, param_err_xgamma, i);
            DoReparametrisationforQQ(1, param_xgamma_PhotonsFitforQQ, param_err_xgamma_PhotonsFitforQQ, i);
            if (nodebugmode) 
                dout("err",i,":", param_err_xgamma[i], pow(hist_data[0]->GetSum(),-2)*\
                TMath::Sqrt( pow(hist_data[0]->GetRMS(),2)*pow(hist_mc_rad[0]->GetSum() - param_xgamma[i]*hist_mc_photon[0]->GetSum(), 2) +\
                    pow(hist_data[0]->GetSum(),2)*(pow(hist_mc_rad[0]->GetRMS(),2) + pow(param_xgamma[i],2)*pow(hist_mc_photon[0]->GetRMS(), 2) + \
                        pow(param_err_xgamma[i]*hist_mc_photon[0]->GetSum(), 2))\
                    ) );
            //param_err_xgamma[i] = pow(hist_data[0]->GetSum(),-2)*\
            //    TMath::Sqrt( pow(hist_data[0]->GetRMS(),2)*pow(hist_mc_rad[0]->GetSum() - param_xgamma[i]*hist_mc_photon[0]->GetSum(), 2) +\
            //        pow(hist_data[0]->GetSum(),2)*(pow(hist_mc_rad[0]->GetRMS(),2) + pow(param_xgamma[i],2)*pow(hist_mc_photon[0]->GetRMS(), 2) + 
            //            pow(param_err_xgamma[i]*hist_mc_photon[0]->GetSum(), 2))
            //        ) ;
            //if (!nodebugmode) dout("a",i,":",param_xgamma[i], (param_xgamma[i]*hist_mc_photon[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_data[0]->GetSum());
            //param_xgamma[i] = (param_xgamma[i]*hist_mc_photon[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_data[0]->GetSum();
        }
        else if(QQfit != 0)
            DoReparametrisationQQfit(0, param_xgamma, param_err_xgamma, i);
        if (nodebugmode) cout<< "param param_xgamma after reparam " << i << ") " << param_xgamma[i] <<"+/-"<< param_err_xgamma[i]<< endl;

        if (nodebugmode) cout<< "param param_xgamma_PhotonsFit after reparam " << i << ") " << param_xgamma_PhotonsFit[i] <<"+/-"<< param_err_xgamma_PhotonsFit[i]<< endl;

        if (nodebugmode) cout<< "param param_xgamma_PhotonsFitforQQ after reparam " << i << ") " << param_xgamma_PhotonsFitforQQ[i] <<"+/-"<< param_err_xgamma_PhotonsFitforQQ[i]<< endl;

        DoComplicatedScale(hist.h_deltaz_xgamma_norad_sum[i], 1 - param_xgamma_PhotonsFit[i], param_err_xgamma_PhotonsFit[i]);
        DoComplicatedScale(hist.h_deltaz_xgamma_prph_sum[i], param_xgamma_PhotonsFitforQQ[i], param_err_xgamma_PhotonsFitforQQ[i]);

        if (QQfit == 1 && fitWithLL== 0) hist.h_deltaz_xgamma_res[i]->Scale(0);
        hist.h_deltaz_xgamma_res[i]->Add(hist.h_deltaz_xgamma_norad_sum[i]);// LL + bg'
        hist.h_deltaz_xgamma_res[i]->Add(hist.h_deltaz_xgamma_prph_sum[i]);//LL +  QQ' + bg'
        //if (nodebugmode) cout << "par in bin xgamma " << i << ": " << param_xgamma[i] << " +- " << param_err_xgamma[i] << ", chi2/dof = " << chi2_xgamma[i]  << endl;

        if (i+1 == 1 && !nodebugmode)//if (i+1 == number_xgamma_bins && nodebugmode)
        {
             cout << "Problem bin" << endl;
             cout << "   param: " <<  param_xgamma[i] <<" +/- " << param_err_xgamma[i] << endl;
             cout << "   data: " << hist_data[0]->Integral(1, hist_data[0]->GetNbinsX())<<endl;
             cout << "   res: " << hist.h_deltaz_xgamma_res[i]->Integral(1, hist.h_deltaz_xgamma_res[i]->GetNbinsX())<<endl;
             cout << "       res': " << hist_mc[0]->Integral(1, hist_mc[0]->GetNbinsX()) * param_xgamma[i]  + \
                                        hist_mc_norad[0]->Integral(1, hist_mc_norad[0]->GetNbinsX()) * (1 - param_xgamma[i]) + \
                                        hist_mc_rad[0]->Integral(1, hist_mc_rad[0]->GetNbinsX())<< endl;
             cout << "   QQ': " << hist_mc[0]->Integral(1, hist_mc[0]->GetNbinsX()) * param_xgamma[i] <<endl;
                 cout << "   hist.QQ[i]: " << hist.h_deltaz_xgamma_prph_sum[i]->GetEntries() << endl;
             cout << "   LL: " << hist_mc_rad[0]->Integral(1, hist_mc_rad[0]->GetNbinsX())<<endl;
             cout << "   bg': " << hist_mc_norad[0]->Integral(1, hist_mc_norad[0]->GetNbinsX()) * (1 - param_xgamma[i]) <<endl;
                 cout << "   hist.bg[i]: " << hist.h_deltaz_xgamma_norad_sum[i]->Integral(1, hist.h_deltaz_xgamma_norad_sum[i]->GetNbinsX())<< endl;
             cout << "   photons: " << hist_mc_photon[0]->Integral(1, hist_mc_photon[0]->GetNbinsX())<<endl;
        }
    }

    dout("xgamma:");
    Chi2StatisticsCheck(chi2_xgamma, number_xgamma_bins);
    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of xp
    //
    ///////////////////////////////////////////////////////
    for(Int_t i=0; i<number_xp_bins; i++)
    { 
        MakeCorrection(hist.h_deltaz_xp_prph_sum[i], hist.h_deltaz_xp_norad_sum[i]);

        hist_data[0] = (TH1D*)hist.h_deltaz_xp_data_sum[i]->Clone(); hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_xp_prph_sum[i]->Clone(); 
        hist_mc[0]->SetName("prph");
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_xp_rad_sum[i]->Clone(); 
        hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_xp_norad_sum[i]->Clone(); 
        hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); 
        hist_mc_photon[0]->SetName("photon");
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

        /*was:
            if (QQfit == 0)
                hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum());
            else
            hist_mc[0]->Scale((hist_data[0]->GetSum() )/hist_mc[0]->GetSum());
            //      hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
            hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());
            if (QQfit == 0)
                hist.h_deltaz_xp_prph_sum[i]->Scale((hist.h_deltaz_xp_data_sum[i]->GetSum() - hist.h_deltaz_xp_rad_sum[i]->GetSum()) / hist.h_deltaz_xp_prph_sum[i]->GetSum());
            else
                hist.h_deltaz_xp_prph_sum[i]->Scale((hist.h_deltaz_xp_data_sum[i]->GetSum() ) / hist.h_deltaz_xp_prph_sum[i]->GetSum());
            hist.h_deltaz_xp_norad_sum[i]->Scale((hist.h_deltaz_xp_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_xp_rad_sum[i]->GetSum()) / hist.h_deltaz_xp_norad_sum[i]->GetSum());
        */
        if (QQfit == 0)
        {
            //эта переменная все равно в фите не будет учавствовать. но для построения контрольного графика это не верно.
            hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            //hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
            hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            
            //for the CS further painting...
            hist.h_deltaz_xp_prph_sum[i]->Scale((hist.h_deltaz_xp_data_sum[i]->GetSum() - hist.h_deltaz_xp_rad_sum[i]->GetSum()) / hist.h_deltaz_xp_prph_sum[i]->GetSum());
            hist.h_deltaz_xp_norad_sum[i]->Scale((hist.h_deltaz_xp_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_xp_rad_sum[i]->GetSum()) / hist.h_deltaz_xp_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLLinBg == 0)//data =LL’ +  QQ’ * a + bg’ * (1- a) //data = QQ’ * a + bg’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_xp_prph_sum[i]->Scale((hist.h_deltaz_xp_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_xp_rad_sum[i]->GetSum()) / hist.h_deltaz_xp_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_xp_norad_sum[i]->Scale((hist.h_deltaz_xp_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_xp_rad_sum[i]->GetSum()) / hist.h_deltaz_xp_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLL == 0 && fitWithLLinBg == 1)//data = QQ’ * a + bg’’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_xp_prph_sum[i]->Scale((hist.h_deltaz_xp_data_sum[i]->GetSum() - fitWithLL * hist.h_deltaz_xp_rad_sum[i]->GetSum()) / hist.h_deltaz_xp_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_xp_norad_sum[i]->Scale((hist.h_deltaz_xp_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_xp_rad_sum[i]->GetSum()) / hist.h_deltaz_xp_norad_sum[i]->GetSum()); 
        }


        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);   
        param_xp[i] = minimizer->GetParameter(0);
        param_err_xp[i] = minimizer->GetParError(0);
        if (param_xp[i] != param_xp[i]) param_xp[i] = 0;
        if (param_err_xp[i] != param_err_xp[i]) param_err_xp[i] = 0;
        Double_t par[1]; par[0] = param_xp[i];
        chi2_xp[i] = chi2(par, dof_xp[i], left_xp[i], right_xp[i], chi_method) / dof_xp[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_xp[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; sc.Form("chi2_xp_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_xp[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;
        //if (nodebugmode) cout << "total chi2 = " << total_chi2 << endl;
        //if (nodebugmode) cout << "... per dof = " << total_chi2 / Double_t(dof-2) << endl;
        // ----------- end chi2 per bin
        
        //leftxp[i]++;
        //hist.h_deltaz_xp_norad_sum[i]->Scale(1-param_xp[i]);
        //hist.h_deltaz_xp_prph_sum[i]->Scale(param_xp[i]);

        param_xp_PhotonsFit[i] = param_xp[i];
        param_err_xp_PhotonsFit[i] = param_err_xp[i];
        param_xp_PhotonsFitforQQ[i] = param_xp[i];
        param_err_xp_PhotonsFitforQQ[i] = param_err_xp[i];
        if (QQfit == 0)
        {
            //std::copy(param_xp, param_xp + number_xp_bins, param_xp_PhotonsFit);
            //std::copy(param_err_xp, param_err_xp + number_xp_bins,  param_err_xp_PhotonsFit);
            DoReparametrisation(0, param_xp, param_err_xp, i);
            DoReparametrisationforQQ(0, param_xp_PhotonsFitforQQ, param_err_xp_PhotonsFitforQQ, i);
        }
        else
            DoReparametrisationQQfit(0, param_xp, param_err_xp, i);
        DoComplicatedScale(hist.h_deltaz_xp_norad_sum[i], 1 - param_xp_PhotonsFit[i], param_err_xp_PhotonsFit[i]);
        DoComplicatedScale(hist.h_deltaz_xp_prph_sum[i], param_xp_PhotonsFitforQQ[i], param_err_xp_PhotonsFitforQQ[i]);

        if (QQfit == 1 && fitWithLL == 0) hist.h_deltaz_xp_res[i]->Scale(0);
        hist.h_deltaz_xp_res[i]->Add(hist.h_deltaz_xp_norad_sum[i]);
        hist.h_deltaz_xp_res[i]->Add(hist.h_deltaz_xp_prph_sum[i]);
        //if (nodebugmode) 
            cout << "par in bin xp " << i << ": " << param_xp[i] << " +- " << param_err_xp[i] << ", chi2/dof = " << chi2_xp[i]  << endl;
    }


    dout("xp:");
    Chi2StatisticsCheck(chi2_xp, number_xp_bins);
    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of dphi
    //
    ///////////////////////////////////////////////////////
    for(Int_t i=0; i<number_dphi_bins; i++)
    { 
        MakeCorrection(hist.h_deltaz_dphi_prph_sum[i], hist.h_deltaz_dphi_norad_sum[i]);

        hist_data[0] = (TH1D*)hist.h_deltaz_dphi_data_sum[i]->Clone(); 
        hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_dphi_prph_sum[i]->Clone(); 
        hist_mc[0]->SetName("prph");
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_dphi_rad_sum[i]->Clone(); 
        hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_dphi_norad_sum[i]->Clone(); 
        hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); 
        hist_mc_photon[0]->SetName("photon");
        
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

        if (QQfit == 0)
        {
            //эта переменная все равно в фите не будет учавствовать. но для построения контрольного графика это не верно.
            hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            //hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
            hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            
            //for the CS further painting...
            hist.h_deltaz_dphi_prph_sum[i]->Scale((hist.h_deltaz_dphi_data_sum[i]->GetSum() - hist.h_deltaz_dphi_rad_sum[i]->GetSum()) / hist.h_deltaz_dphi_prph_sum[i]->GetSum());
            hist.h_deltaz_dphi_norad_sum[i]->Scale((hist.h_deltaz_dphi_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_dphi_rad_sum[i]->GetSum()) / hist.h_deltaz_dphi_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLLinBg == 0)//data =LL’ +  QQ’ * a + bg’ * (1- a) //data = QQ’ * a + bg’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_dphi_prph_sum[i]->Scale((hist.h_deltaz_dphi_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_dphi_rad_sum[i]->GetSum()) / hist.h_deltaz_dphi_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_dphi_norad_sum[i]->Scale((hist.h_deltaz_dphi_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_dphi_rad_sum[i]->GetSum()) / hist.h_deltaz_dphi_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLL == 0 && fitWithLLinBg == 1)//data = QQ’ * a + bg’’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_xp_prph_sum[i]->Scale((hist.h_deltaz_xp_data_sum[i]->GetSum() - fitWithLL * hist.h_deltaz_xp_rad_sum[i]->GetSum()) / hist.h_deltaz_xp_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_xp_norad_sum[i]->Scale((hist.h_deltaz_xp_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_xp_rad_sum[i]->GetSum()) / hist.h_deltaz_xp_norad_sum[i]->GetSum()); 
        }

        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);   
        param_dphi[i] = minimizer->GetParameter(0);
        param_err_dphi[i] = minimizer->GetParError(0);
        Double_t par[1]; par[0] = param_dphi[i];
        chi2_dphi[i] = chi2(par, dof_dphi[i], left_dphi[i], right_dphi[i], chi_method) / dof_dphi[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_dphi[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; sc.Form("chi2_dphi_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_dphi[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;
        //if (nodebugmode) cout << "total chi2 = " << total_chi2 << endl;
        //if (nodebugmode) cout << "... per dof = " << total_chi2 / Double_t(dof-2) << endl;
        // ----------- end chi2 per bin
            param_dphi_PhotonsFit[i] = param_dphi[i];
            param_err_dphi_PhotonsFit[i] = param_err_dphi[i];
            param_dphi_PhotonsFitforQQ[i] = param_dphi[i];
            param_err_dphi_PhotonsFitforQQ[i] = param_err_dphi[i];
        
        //leftdphi[i]++;
        if (QQfit == 0)
        {
            //std::copy(param_dphi, param_dphi + number_dphi_bins,  param_dphi_PhotonsFit);
            //std::copy(param_err_dphi, param_err_dphi + number_dphi_bins,  param_err_dphi_PhotonsFit);
            DoReparametrisation(3, param_dphi, param_err_dphi, i);
            DoReparametrisationforQQ(3, param_dphi_PhotonsFitforQQ, param_err_dphi_PhotonsFitforQQ, i);
        }
        else
            DoReparametrisationQQfit(3, param_dphi, param_err_dphi, i);
        
        DoComplicatedScale(hist.h_deltaz_dphi_norad_sum[i], 1 - param_dphi_PhotonsFit[i], param_err_dphi_PhotonsFit[i]);
        DoComplicatedScale(hist.h_deltaz_dphi_prph_sum[i], param_dphi_PhotonsFitforQQ[i], param_err_dphi_PhotonsFitforQQ[i]);
        
        //hist.h_deltaz_dphi_norad_sum[i]->Scale(1-param_dphi[i]);
        //hist.h_deltaz_dphi_prph_sum[i]->Scale(param_dphi[i]);
        if (QQfit == 1 && fitWithLL== 0) hist.h_deltaz_dphi_res[i]->Scale(0);
        hist.h_deltaz_dphi_res[i]->Add(hist.h_deltaz_dphi_norad_sum[i]);
        hist.h_deltaz_dphi_res[i]->Add(hist.h_deltaz_dphi_prph_sum[i]);
        //if (nodebugmode) cout << "par in bin dphi " << i << ": " << param_dphi[i] << " +- " << param_err_dphi[i] << ", chi2/dof = " << chi2_dphi[i]  << endl;
    }
     std::copy(param_dphi, param_dphi + number_dphi_bins,  hist.param_dphi);//?
     std::copy(param_err_dphi, param_err_dphi + number_dphi_bins,  hist.param_err_dphi);

    dout("dphi:");
    Chi2StatisticsCheck(chi2_dphi, number_dphi_bins);
    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of deta
    //
    ///////////////////////////////////////////////////////
    for(Int_t i=0; i<number_deta_bins; i++)
    { 
        MakeCorrection(hist.h_deltaz_deta_prph_sum[i], hist.h_deltaz_deta_norad_sum[i]);

        hist_data[0] = (TH1D*)hist.h_deltaz_deta_data_sum[i]->Clone(); hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_deta_prph_sum[i]->Clone(); hist_mc[0]->SetName("prph");
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_deta_rad_sum[i]->Clone(); hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_deta_norad_sum[i]->Clone(); hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); hist_mc_photon[0]->SetName("photon");
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());
        
        /*was
            //      hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
            hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());
            if (QQfit == 0)
            {
                hist.h_deltaz_deta_prph_sum[i]->Scale((hist.h_deltaz_deta_data_sum[i]->GetSum() - hist.h_deltaz_deta_rad_sum[i]->GetSum()) / hist.h_deltaz_deta_prph_sum[i]->GetSum());
                hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum());
            }
            else
            {
                hist_mc[0]->Scale((hist_data[0]->GetSum() )/hist_mc[0]->GetSum());
                hist.h_deltaz_deta_prph_sum[i]->Scale((hist.h_deltaz_deta_data_sum[i]->GetSum() ) / hist.h_deltaz_deta_prph_sum[i]->GetSum());
            }
            hist.h_deltaz_deta_norad_sum[i]->Scale((hist.h_deltaz_deta_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_deta_rad_sum[i]->GetSum()) / hist.h_deltaz_deta_norad_sum[i]->GetSum());
        */

        if (QQfit == 0)
        {
            //эта переменная все равно в фите не будет учавствовать. но для построения контрольного графика это не верно.
            hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            //hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
            hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            
            //for the CS further painting...
            hist.h_deltaz_deta_prph_sum[i]->Scale((hist.h_deltaz_deta_data_sum[i]->GetSum() - hist.h_deltaz_deta_rad_sum[i]->GetSum()) / hist.h_deltaz_deta_prph_sum[i]->GetSum());
            hist.h_deltaz_deta_norad_sum[i]->Scale((hist.h_deltaz_deta_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_deta_rad_sum[i]->GetSum()) / hist.h_deltaz_deta_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLLinBg == 0)//data =LL’ +  QQ’ * a + bg’ * (1- a) //data = QQ’ * a + bg’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_deta_prph_sum[i]->Scale((hist.h_deltaz_deta_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_deta_rad_sum[i]->GetSum()) / hist.h_deltaz_deta_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_deta_norad_sum[i]->Scale((hist.h_deltaz_deta_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_deta_rad_sum[i]->GetSum()) / hist.h_deltaz_deta_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLL == 0 && fitWithLLinBg == 1)//data = QQ’ * a + bg’’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_deta_prph_sum[i]->Scale((hist.h_deltaz_deta_data_sum[i]->GetSum() - fitWithLL * hist.h_deltaz_deta_rad_sum[i]->GetSum()) / hist.h_deltaz_deta_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_deta_norad_sum[i]->Scale((hist.h_deltaz_deta_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_deta_rad_sum[i]->GetSum()) / hist.h_deltaz_deta_norad_sum[i]->GetSum()); 
        }
        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);   
        param_deta[i] = minimizer->GetParameter(0);
        param_err_deta[i] = minimizer->GetParError(0);
        Double_t par[1]; par[0] = param_deta[i];
        chi2_deta[i] = chi2(par, dof_deta[i], left_deta[i], right_deta[i], chi_method) / dof_deta[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_deta[i]->SetBinContent(dof, chi2_bin);
        }
        
        TString sc; sc.Form("chi2_deta_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_deta[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;
        //if (nodebugmode) cout << "total chi2 = " << total_chi2 << endl;
        //if (nodebugmode) cout << "... per dof = " << total_chi2 / Double_t(dof-2) << endl;
        // ----------- end chi2 per bin
        
        //leftdeta[i]++;
        //hist.h_deltaz_deta_norad_sum[i]->Scale(1-param_deta[i]);
        //hist.h_deltaz_deta_prph_sum[i]->Scale(param_deta[i]);

        param_deta_PhotonsFit[i] = param_deta[i];
        param_err_deta_PhotonsFit[i] = param_err_deta[i];
        param_deta_PhotonsFitforQQ[i] = param_deta[i];
        param_err_deta_PhotonsFitforQQ[i] = param_err_deta[i];
        if (QQfit == 0)
        {

            //std::copy(param_deta, param_deta + number_deta_bins,  param_deta_PhotonsFit);
            //std::copy(param_err_deta, param_err_deta + number_deta_bins,  param_err_deta_PhotonsFit);
            DoReparametrisation(2, param_deta, param_err_deta, i);
            DoReparametrisationforQQ(2, param_deta_PhotonsFitforQQ, param_err_deta_PhotonsFitforQQ, i);
        }
        else
            DoReparametrisationQQfit(2, param_deta, param_err_deta, i);
        DoComplicatedScale(hist.h_deltaz_deta_norad_sum[i], 1 - param_deta_PhotonsFit[i], param_err_deta_PhotonsFit[i]);
        DoComplicatedScale(hist.h_deltaz_deta_prph_sum[i], param_deta_PhotonsFitforQQ[i], param_err_deta_PhotonsFitforQQ[i]);
        hist.h_deltaz_deta_res[i]->Add(hist.h_deltaz_deta_norad_sum[i]);
        hist.h_deltaz_deta_res[i]->Add(hist.h_deltaz_deta_prph_sum[i]);
        //if (nodebugmode) cout << "par in bin deta " << i << ": " << param_deta[i] << " +- " << param_err_deta[i] << ", chi2/dof = " << chi2_deta[i]  << endl;
    }

    dout("deta:");
    Chi2StatisticsCheck(chi2_deta, number_deta_bins);

    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of dphi_e_ph
    //
    ///////////////////////////////////////////////////////
    for(Int_t i = 0; i < number_dphi_e_ph_bins; i++)
    { 
        MakeCorrection(hist.h_deltaz_dphi_e_ph_prph_sum[i], hist.h_deltaz_dphi_e_ph_norad_sum[i]);
      
        hist_data[0] = (TH1D*)hist.h_deltaz_dphi_e_ph_data_sum[i]->Clone(); hist_data[0]->SetName("data");
        hist_mc[0] = (TH1D*)hist.h_deltaz_dphi_e_ph_prph_sum[i]->Clone(); hist_mc[0]->SetName("prph");
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_dphi_e_ph_rad_sum[i]->Clone(); hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_dphi_e_ph_norad_sum[i]->Clone(); hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); hist_mc_photon[0]->SetName("photon");
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

        /*was
            //      hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
            hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());
            
            if (QQfit == 0)
            {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum());
            hist.h_deltaz_dphi_e_ph_prph_sum[i]->Scale((hist.h_deltaz_dphi_e_ph_data_sum[i]->GetSum() - hist.h_deltaz_dphi_e_ph_rad_sum[i]->GetSum()) / hist.h_deltaz_dphi_e_ph_prph_sum[i]->GetSum());
            }
            else
            {
            hist_mc[0]->Scale((hist_data[0]->GetSum() )/hist_mc[0]->GetSum());
            hist.h_deltaz_dphi_e_ph_prph_sum[i]->Scale((hist.h_deltaz_dphi_e_ph_data_sum[i]->GetSum() ) / hist.h_deltaz_dphi_e_ph_prph_sum[i]->GetSum());
            }
            hist.h_deltaz_dphi_e_ph_norad_sum[i]->Scale((hist.h_deltaz_dphi_e_ph_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_dphi_e_ph_rad_sum[i]->GetSum()) / hist.h_deltaz_dphi_e_ph_norad_sum[i]->GetSum());
        */
        if (QQfit == 0)
        {
            //эта переменная все равно в фите не будет учавствовать. но для построения контрольного графика это не верно.
            hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            //hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
            hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            
            //for the CS further painting...
            hist.h_deltaz_dphi_e_ph_prph_sum[i]->Scale((hist.h_deltaz_dphi_e_ph_data_sum[i]->GetSum() - hist.h_deltaz_dphi_e_ph_rad_sum[i]->GetSum()) / hist.h_deltaz_dphi_e_ph_prph_sum[i]->GetSum());
            hist.h_deltaz_dphi_e_ph_norad_sum[i]->Scale((hist.h_deltaz_dphi_e_ph_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_dphi_e_ph_rad_sum[i]->GetSum()) / hist.h_deltaz_dphi_e_ph_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLLinBg == 0)//data =LL’ +  QQ’ * a + bg’ * (1- a) //data = QQ’ * a + bg’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_dphi_e_ph_prph_sum[i]->Scale((hist.h_deltaz_dphi_e_ph_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_dphi_e_ph_rad_sum[i]->GetSum()) / hist.h_deltaz_dphi_e_ph_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_dphi_e_ph_norad_sum[i]->Scale((hist.h_deltaz_dphi_e_ph_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_dphi_e_ph_rad_sum[i]->GetSum()) / hist.h_deltaz_dphi_e_ph_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLL == 0 && fitWithLLinBg == 1)//data = QQ’ * a + bg’’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_dphi_e_ph_prph_sum[i]->Scale((hist.h_deltaz_dphi_e_ph_data_sum[i]->GetSum() - fitWithLL * hist.h_deltaz_dphi_e_ph_rad_sum[i]->GetSum()) / hist.h_deltaz_dphi_e_ph_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_dphi_e_ph_norad_sum[i]->Scale((hist.h_deltaz_dphi_e_ph_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_dphi_e_ph_rad_sum[i]->GetSum()) / hist.h_deltaz_dphi_e_ph_norad_sum[i]->GetSum()); 
        }

        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);   
        param_dphi_e_ph[i] = minimizer->GetParameter(0);
        param_err_dphi_e_ph[i] = minimizer->GetParError(0);
        Double_t par[1]; par[0] = param_dphi_e_ph[i];
        chi2_dphi_e_ph[i] = chi2(par, dof_dphi_e_ph[i], left_dphi_e_ph[i], right_dphi_e_ph[i], chi_method) / dof_dphi_e_ph[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            //if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_dphi_e_ph[i]->SetBinContent(dof, chi2_bin);
        }
        if (nodebugmode && i == 0)
        {
           dout("==> param: ", param_dphi_e_ph[i]);
        }
        TString sc; sc.Form("chi2_dphi_e_ph_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_dphi_e_ph[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;
        //if (nodebugmode) cout << "total chi2 = " << total_chi2 << endl;
        //if (nodebugmode) cout << "... per dof = " << total_chi2 / Double_t(dof-2) << endl;
        // ----------- end chi2 per bin
        
        //leftdphi_e_ph[i]++;
        //hist.h_deltaz_dphi_e_ph_norad_sum[i]->Scale(1-param_dphi_e_ph[i]);
        //hist.h_deltaz_dphi_e_ph_prph_sum[i]->Scale(param_dphi_e_ph[i]);
        param_dphi_e_ph_PhotonsFit[i] = param_dphi_e_ph[i];
        param_err_dphi_e_ph_PhotonsFit[i] = param_err_dphi_e_ph[i];
        param_dphi_e_ph_PhotonsFitforQQ[i] = param_dphi_e_ph[i];
        param_err_dphi_e_ph_PhotonsFitforQQ[i] = param_err_dphi_e_ph[i];
        if (QQfit == 0)
        {
            //std::copy(param_dphi_e_ph, param_dphi_e_ph + number_dphi_e_ph_bins,  param_dphi_e_ph_PhotonsFit);
            //std::copy(param_err_dphi_e_ph, param_err_dphi_e_ph + number_dphi_e_ph_bins,  param_err_dphi_e_ph_PhotonsFit);
            DoReparametrisation(4, param_dphi_e_ph, param_err_dphi_e_ph, i);
            DoReparametrisationforQQ(4, param_dphi_e_ph_PhotonsFitforQQ, param_err_dphi_e_ph_PhotonsFitforQQ, i);
        }
        else
            DoReparametrisationQQfit(4, param_dphi_e_ph, param_err_dphi_e_ph, i);
        DoComplicatedScale(hist.h_deltaz_dphi_e_ph_norad_sum[i], 1 - param_dphi_e_ph_PhotonsFit[i], param_err_dphi_e_ph_PhotonsFit[i]);
        DoComplicatedScale(hist.h_deltaz_dphi_e_ph_prph_sum[i], param_dphi_e_ph_PhotonsFitforQQ[i], param_err_dphi_e_ph_PhotonsFitforQQ[i]);

        if (QQfit == 1 && fitWithLL== 0) hist.h_deltaz_dphi_e_ph_res[i]->Scale(0);
        hist.h_deltaz_dphi_e_ph_res[i]->Add(hist.h_deltaz_dphi_e_ph_norad_sum[i]);
        hist.h_deltaz_dphi_e_ph_res[i]->Add(hist.h_deltaz_dphi_e_ph_prph_sum[i]);

        //if (nodebugmode) cout << "par in bin dphi_e_ph " << i << ": " << param_dphi_e_ph[i] << " +- " << param_err_dphi_e_ph[i] << ", chi2/dof = " << chi2_dphi_e_ph[i]  << endl;
    }

    dout("dphi_e_ph:");
    Chi2StatisticsCheck(chi2_dphi_e_ph, number_dphi_e_ph_bins);

    ///////////////////////////////////////////////////////
    //
    //          Fit in bins of deta_e_ph
    //
    ///////////////////////////////////////////////////////
    for(Int_t i=0; i<number_deta_e_ph_bins; i++)
    { 
        MakeCorrection(hist.h_deltaz_deta_e_ph_prph_sum[i], hist.h_deltaz_deta_e_ph_norad_sum[i]);

        hist_data[0] = (TH1D*)hist.h_deltaz_deta_e_ph_data_sum[i]->Clone(); 
        hist_mc[0] = (TH1D*)hist.h_deltaz_deta_e_ph_prph_sum[i]->Clone(); 
        hist_mc_rad[0] = (TH1D*)hist.h_deltaz_deta_e_ph_rad_sum[i]->Clone(); 
        hist_mc_norad[0] = (TH1D*)hist.h_deltaz_deta_e_ph_norad_sum[i]->Clone(); 
        hist_mc_photon[0] = (TH1D*)hist_mc_rad[0]->Clone(); 
        hist_mc_photon[0]->Add(hist_mc[0], hist.total_luminosity_data/hist.lumi_mc_prph);
        hist_mc_photon[0]->Scale(hist_data[0]->GetSum()/hist_mc_photon[0]->GetSum());

        hist_data[0]->SetName("data");
        hist_mc[0]->SetName("prph");
        hist_mc_rad[0]->SetName("rad");
        hist_mc_norad[0]->SetName("norad");
        hist_mc_photon[0]->SetName("photon");
        
        /*was
            //      hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
            hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum());
            if (QQfit == 0)
            {
                hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum());
                hist.h_deltaz_deta_e_ph_prph_sum[i]->Scale((hist.h_deltaz_deta_e_ph_data_sum[i]->GetSum() - hist.h_deltaz_deta_e_ph_rad_sum[i]->GetSum()) / hist.h_deltaz_deta_e_ph_prph_sum[i]->GetSum());
            }
            else
            {
                hist_mc[0]->Scale((hist_data[0]->GetSum() )/hist_mc[0]->GetSum());
                hist.h_deltaz_deta_e_ph_prph_sum[i]->Scale((hist.h_deltaz_deta_e_ph_data_sum[i]->GetSum() ) / hist.h_deltaz_deta_e_ph_prph_sum[i]->GetSum());
            }

            hist.h_deltaz_deta_e_ph_norad_sum[i]->Scale((hist.h_deltaz_deta_e_ph_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_deta_e_ph_rad_sum[i]->GetSum()) / hist.h_deltaz_deta_e_ph_norad_sum[i]->GetSum());//?
        */
        if (QQfit == 0)
        {
            //эта переменная все равно в фите не будет учавствовать. но для построения контрольного графика это не верно.
            hist_mc[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            //hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum());
            hist_mc_norad[0]->Scale(hist_data[0]->GetSum()/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            
            //for the CS further painting...
            hist.h_deltaz_deta_e_ph_prph_sum[i]->Scale((hist.h_deltaz_deta_e_ph_data_sum[i]->GetSum() - hist.h_deltaz_deta_e_ph_rad_sum[i]->GetSum()) / hist.h_deltaz_deta_e_ph_prph_sum[i]->GetSum());
            hist.h_deltaz_deta_e_ph_norad_sum[i]->Scale((hist.h_deltaz_deta_e_ph_data_sum[i]->GetSum() - QQfit * hist.h_deltaz_deta_e_ph_rad_sum[i]->GetSum()) / hist.h_deltaz_deta_e_ph_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLLinBg == 0)//data =LL’ +  QQ’ * a + bg’ * (1- a) //data = QQ’ * a + bg’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_deta_e_ph_prph_sum[i]->Scale((hist.h_deltaz_deta_e_ph_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_deta_e_ph_rad_sum[i]->GetSum()) / hist.h_deltaz_deta_e_ph_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - QQfit * fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_deta_e_ph_norad_sum[i]->Scale((hist.h_deltaz_deta_e_ph_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_deta_e_ph_rad_sum[i]->GetSum()) / hist.h_deltaz_deta_e_ph_norad_sum[i]->GetSum()); 
        }
        else if (fitWithLL == 0 && fitWithLLinBg == 1)//data = QQ’ * a + bg’’ * (1 - a)
        {
            hist_mc[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc[0]->GetSum()); // QQ' = QQ.scale([Data - LL]/QQ)
            hist.h_deltaz_deta_e_ph_prph_sum[i]->Scale((hist.h_deltaz_deta_e_ph_data_sum[i]->GetSum() - fitWithLL * hist.h_deltaz_deta_e_ph_rad_sum[i]->GetSum()) / hist.h_deltaz_deta_e_ph_prph_sum[i]->GetSum());

            hist_mc_norad[0]->Scale((hist_data[0]->GetSum() - fitWithLL * hist_mc_rad[0]->GetSum())/hist_mc_norad[0]->GetSum()); // bg' = bg.scale(Data / bg)
            hist.h_deltaz_deta_e_ph_norad_sum[i]->Scale((hist.h_deltaz_deta_e_ph_data_sum[i]->GetSum() - QQfit * fitWithLL * hist.h_deltaz_deta_e_ph_rad_sum[i]->GetSum()) / hist.h_deltaz_deta_e_ph_norad_sum[i]->GetSum()); 
        }

        minimizer->SetParameter(0, "ALPHA", 0.3, 0.05, 0., 1.);
        minimizer->ExecuteCommand("SIMPLEX", 0, 0);
        minimizer->ExecuteCommand("MIGRAD",0,0);
        minimizer->ExecuteCommand("HESSE",0,0);
        minimizer->ExecuteCommand("MINOS",0,0);   
        param_deta_e_ph[i] = minimizer->GetParameter(0);
        param_err_deta_e_ph[i] = minimizer->GetParError(0);
        Double_t par[1]; par[0] = param_deta_e_ph[i];
        chi2_deta_e_ph[i] = chi2(par, dof_deta_e_ph[i], left_deta_e_ph[i], right_deta_e_ph[i], chi_method) / dof_deta_e_ph[i];
        //chi squared per bin
        Double_t total_chi2 = 0;
        Int_t dof = 0;
        for(Int_t bin = GetFitRange(hist_data[0], true); bin < GetFitRange(hist_data[0], false); bin++)
        {
            Double_t s_d = hist_data[0]->GetBinError(bin+1);
            Double_t s_l = hist_mc_rad[0]->GetBinError(bin+1);
            Double_t s_q = hist_mc[0]->GetBinError(bin+1);
            Double_t s_ph = hist_mc_photon[0]->GetBinError(bin+1);
            Double_t s_bg = hist_mc_norad[0]->GetBinError(bin+1);
            //      Double_t s_photon = hist_mc_photon[0]->GetBinError(bin+1);

            Double_t v_d = hist_data[0]->GetBinContent(bin+1);
            Double_t v_l = hist_mc_rad[0]->GetBinContent(bin+1);
            Double_t v_q = hist_mc[0]->GetBinContent(bin+1);
            Double_t v_ph = hist_mc_photon[0]->GetBinContent(bin+1);
            Double_t v_bg = hist_mc_norad[0]->GetBinContent(bin+1);

            Double_t chi2_bin = (v_d - par[0]*v_ph - (1-par[0])*v_bg)*(v_d - par[0]*v_ph - (1-par[0])*v_bg)/(s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg);
            total_chi2 += chi2_bin;
            dof++;
            ///if (nodebugmode) cout << "bin " << bin << ", chi2 = " << chi2_bin << endl;
            hist.h_chi2_perbin_deta_e_ph[i]->SetBinContent(dof, chi2_bin);
        }

        TString sc; sc.Form("chi2_deta_e_ph_%i", i);
        TCanvas *c = new TCanvas("c", sc, 800, 600);
        c->cd();
        hist.h_chi2_perbin_deta_e_ph[i]->Draw("HIST TEXT");
        c->Print(sc + ".eps");
        delete c;
        ///if (nodebugmode) cout << "total chi2 = " << total_chi2 << endl;
        ///if (nodebugmode) cout << "... per dof = " << total_chi2 / Double_t(dof-2) << endl;
        // ----------- end chi2 per bin
        
        //left_deta_e_ph[i]++;
        //hist.h_deltaz_deta_e_ph_norad_sum[i]->Scale(1-param_deta_e_ph[i]);
        //hist.h_deltaz_deta_e_ph_prph_sum[i]->Scale(param_deta_e_ph[i]);
        if (nodebugmode) cout<< param_deta_e_ph[i]<<endl;        
        param_deta_e_ph_PhotonsFit[i] = param_deta_e_ph[i];
        param_err_deta_e_ph_PhotonsFit[i] = param_err_deta_e_ph[i];
        param_deta_e_ph_PhotonsFitforQQ[i] = param_deta_e_ph[i];
        param_err_deta_e_ph_PhotonsFitforQQ[i] = param_err_deta_e_ph[i];
        if (QQfit == 0)
        {
            //std::copy(param_deta_e_ph, param_deta_e_ph + number_deta_e_ph_bins,  param_deta_e_ph_PhotonsFit);
            //std::copy(param_err_deta_e_ph, param_err_deta_e_ph + number_deta_e_ph_bins,  param_err_deta_e_ph_PhotonsFit);
            DoReparametrisation(5, param_deta_e_ph, param_err_deta_e_ph, i);
            DoReparametrisationforQQ(5, param_deta_e_ph_PhotonsFitforQQ, param_err_deta_e_ph_PhotonsFitforQQ, i);
        }
        else
            DoReparametrisationQQfit(5, param_deta_e_ph, param_err_deta_e_ph, i);
        if (param_deta_e_ph_PhotonsFit[i] != param_deta_e_ph_PhotonsFit[i])
        {
            dout("PAPAMETER WAS NOT FOUND! MANUALLY PUT EQUAL ZERO!: ");
            param_deta_e_ph[i] = 0;
            param_err_deta_e_ph[i] = 0;
            param_deta_e_ph_PhotonsFit[i] = 0;
            param_err_deta_e_ph_PhotonsFit[i] = 0;
            param_deta_e_ph_PhotonsFitforQQ[i] = 1;
            param_err_deta_e_ph_PhotonsFitforQQ[i] = 1;
        }
        DoComplicatedScale(hist.h_deltaz_deta_e_ph_norad_sum[i], 1 - param_deta_e_ph_PhotonsFit[i], param_err_deta_e_ph_PhotonsFit[i]);
        DoComplicatedScale(hist.h_deltaz_deta_e_ph_prph_sum[i], param_deta_e_ph_PhotonsFitforQQ[i], param_err_deta_e_ph_PhotonsFitforQQ[i]);
        //dout(" hist.h_deltaz_deta_e_ph_res[i]->",  hist.h_deltaz_deta_e_ph_res[i]->GetBinContent(1));
        
        if (QQfit == 1 && fitWithLL== 0) hist.h_deltaz_deta_e_ph_res[i]->Scale(0);
        hist.h_deltaz_deta_e_ph_res[i]->Add(hist.h_deltaz_deta_e_ph_norad_sum[i]);
        hist.h_deltaz_deta_e_ph_res[i]->Add(hist.h_deltaz_deta_e_ph_prph_sum[i]);
        dout("i:",i);
        if (nodebugmode && i == 6)
        {
            for(Int_t j = 1; j <= hist.h_deltaz_deta_e_ph_data_sum[i]->GetNbinsX(); j++)
                {
                    dout("4===>",j,")", hist.h_deltaz_deta_e_ph_prph_sum[i]->GetBinContent(j)); 
                    //dout("4===>",j,")", hist.h_deltaz_deta_e_ph_norad_sum[i]->GetBinContent(j));
                }
        }
        ///if (nodebugmode) cout << "par in bin deta_e_ph " << i << ": " << param_deta_e_ph[i] << " +- " << param_err_deta_e_ph[i] << ", chi2/dof = " << chi2_deta_e_ph[i]  << endl;
    }
    if (nodebugmode) cout<<param_deta_e_ph[0]<<endl;
    std::copy(param_deta_e_ph, param_deta_e_ph + number_deta_e_ph_bins,  hist.param_deta_e_ph);
    std::copy(param_err_deta_e_ph, param_err_deta_e_ph + number_deta_e_ph_bins,  hist.param_err_deta_e_ph);
     //hist.param_deta_e_ph[0] = 0;
     //hist.param_err_deta_e_ph[0] = 0;

    dout("deta_e_ph:");
    Chi2StatisticsCheck(chi2_deta_e_ph, number_deta_e_ph_bins);

    hist.PlotFitInBinsOfCrossSec();
    dout("PlotCrossSec");
    hist.PlotCrossSec(); 
    
    if (ProduceDZoverollPlot == 1)
    {
        dout("ProduceDZoverollPlot");
            Int_t i = hist.n_hist - 1;
            hist_data[0] = (TH1D*)hist.hist_data_sum[i]->Clone();             hist_data[0]->SetName("data");
            hist_mc[0] = (TH1D*)hist.hist_mc_sum[i]->Clone();             hist_mc[0]->SetName("prph");//QQ
            hist_mc_rad[0] = (TH1D*)hist.hist_mc_rad_sum[i]->Clone();             hist_mc_rad[0]->SetName("rad");
            hist_mc_norad[0] = (TH1D*)hist.hist_mc_norad_sum[i]->Clone();             hist_mc_norad[0]->SetName("norad");
            
            if (NoScalingForBinsTest == 1)
            {
                ofstream myfile;
                myfile.open("deltaZ_bins.txt");
                myfile << "Bins values of deltaZ variable before the scaling and fitting procedures\n" << setw(3)<<"bin" << setw(10) << "data" <<
                setw(10)<<"data_err" << setw(10) << "QQ,MC" << setw(10) << "QQ,err" << setw(10) << "LL,MC" << setw(10) << "LL,err" << setw(10) << "bg.,MC" << "  bg.,MC,err"<<endl;
                for(Int_t i = 1; i <= hist_data[0]->GetNbinsX(); i++)
                {
                    myfile << setw(3) << i << setw(10) << hist_data[0]->GetBinContent(i) << setw(10) << hist_data[0]->GetBinError(i) << setw(10) << 
                    hist_mc[0]->GetBinContent(i) << setw(10) << hist_mc[0]->GetBinError(i) << setw(10) <<
                     hist_mc_rad[0]->GetBinContent(i) << setw(10) << hist_mc_rad[0]->GetBinError(i) << setw(10) << 
                     hist_mc_norad[0]->GetBinContent(i) << setw(10) << hist_mc_norad[0]->GetBinError(i)<<endl ;
                }
            
                myfile.close();
            }
            if (fitWithLLinBg==1)
            {
                hist_mc_norad[0]->Add(hist_mc_rad[0]);
                hist_mc_norad[0]->Scale(hist_data[0]->Integral()/hist_mc_norad[0]->Integral());
            }

            cout << "AFTER  SCALING: mc QQ: " << hist_mc[0]->Integral() << " mc LL: " << hist_mc_rad[0]->Integral() << " mc bg: " << hist_mc_norad[0]->Integral() << " data: " << hist_data[0]->Integral()<<endl;
            
            bool minusone = true;
            double scalefactor = (hist_data[0]->Integral(GetFitRange(hist_data[0], true), GetFitRange(hist_data[0], false) - 1*minusone)
                                    - hist_mc_rad[0]->Integral(GetFitRange(hist_data[0], true), GetFitRange(hist_data[0], false) - 1*minusone)) 
                                / hist_mc[0]->Integral(GetFitRange(hist_data[0], true), GetFitRange(hist_data[0], false) - 1*minusone) ;
            dout("Scale factor:", scalefactor);
            hist_mc[0]->Scale(scalefactor);
            hist_mc_norad[0]->Scale(scalefactor);

            dout("AFTER RESCALING IN RANGE OF FIT");
            cout << " mc QQ: " << hist_mc[0]->Integral() << " mc LL: " << hist_mc_rad[0]->Integral() << " mc bg: " << hist_mc_norad[0]->Integral() << " data: " << hist_data[0]->Integral()<<endl;

                hist_mc_photon[0] = (TH1D*)hist.hist_mc_rad_sum[i]->Clone();//LL' - scaled to totLum
                hist_mc_photon[0]->SetName("photon");
                hist_mc_photon[0]->Add(hist_mc[0], QQfit + (1 - QQfit) * hist.total_luminosity_data/hist.lumi_mc_prph);// QQfit==0: LL' + QQ.scaledto(totLum) //PhotonFit: LL'+QQ';    QQfit: LL' + QQ  => the variable makes no sence for QQfit
                hist_mc_photon[0]->Scale(hist_data[0]->Integral()/hist_mc_photon[0]->Integral());//phtotons scaled to data
            //Стоп, разве это должно тут быть? разве это не сделано в hist.c? Да. Но Вообще говоря не играет роли, потому что входят в фотоны с параметром.
                dout("Error second scale:", (hist_data[0]->Integral() - hist_mc_rad[0]->Integral())/hist_mc[0]->Integral());
                dout("Error second scale:", hist_data[0]->Integral() / hist_mc_norad[0]->Integral());
            //hist_mc[0]->Scale((hist_data[0]->Integral() - hist_mc_rad[0]->Integral())/hist_mc[0]->Integral());//QQ'
            //hist_mc_norad[0]->Scale(hist_data[0]->Integral() / hist_mc_norad[0]->Integral());//Bg'

            if (QQfit == 1 && fitWithLL == 1 && fitWithLLinBg == 0)
                hist_res[0] = (TH1D*)hist.hist_mc_rad_sum[i]->Clone(); //LL
            //dout("hist_res[0][3] = ", hist_res[0]->GetBinContent(3));
           

            // for(Int_t j = 0;j<10;j++)//GetNbinsX()
            //      dout("csj=",j,")",hist_mc[0]->GetBinContent(j+1) );

            
            minimizer->SetParameter(0, "ALPHA",  0.3, 0.05, 0., 1.);//0.3648, 0.05, 0., 0.5);// 0.3, 0.05, 0., 1.)
            minimizer->ExecuteCommand("SIMPLEX", 0, 0);
            minimizer->ExecuteCommand("MIGRAD",0,0);
            minimizer->ExecuteCommand("HESSE",0,0);
            minimizer->ExecuteCommand("MINOS",0,0);    
            
            Int_t ndf;
            Double_t chi_squared,  chi_squared_Gauss;
            Int_t left_bound, right_bound;
            Double_t param[1] = {0.};
            Double_t param_err[1] = {0.};

            param[0] = minimizer->GetParameter(0);
            param_err[0] = minimizer->GetParError(0);
            chi_squared = chi2(param, ndf, left_bound, right_bound, "Barlow-Beeston") / (ndf);
            dout("param[0]",param[0]);
            TH1D* hA;
            Double_t sumSgAll, sumRd, sumSg, a, aErr;
            if (QQfit == 1)
            {
                // double tempd = 0;
                // hA = hist_mc[0];

                // dout("sumSgAll bins:");
                //     for(int i=1; i<=hA->GetNbinsX(); i++ )
                //     {
                //         dout("bin i", i, ":", hA->GetBinContent(i));
                //         tempd+= hA->GetBinContent(i);
                //     }
                //     dout("sum:", tempd); 
                // sumSgAll = hA->Integral();

                // dout("sumRd (data) bins:");
                //     tempd = 0;
                //     for(int i=1; i<=hist_data[0]->GetNbinsX(); i++ )
                //     {
                //         dout("bin i", i, ":", hist_data[0]->GetBinContent(i));
                //         tempd+= hist_data[0]->GetBinContent(i);
                //     }
                //     dout("sum:", tempd); 
                // sumRd = hist_data[0]->Integral();

                // dout("sumSg bins:");
                //     tempd = 0;
                //     for(int i=GetFitRange(hist_data[0], true); i<=GetFitRange(hist_data[0], false); i++ )
                //     {
                //         dout("bin i", i, ":", hA->GetBinContent(i));
                //         tempd+= hA->GetBinContent(i);
                //     }
                //     dout("sum:", tempd); 
                // sumSg = hA->Integral(GetFitRange(hist_data[0], true), GetFitRange(hist_data[0], false));

                // a = param[0];
                // aErr = param_err[0];
                
                double tempd = 0;
                hA = hist_mc[0];

                dout("sumSgAll bins:");
                    for(int i=1; i<=hA->GetNbinsX(); i++ )
                    {
                        dout("bin i", i, ":", hA->GetBinContent(i));
                        tempd+= hA->GetBinContent(i);
                    }
                    dout("sum:", tempd); 
                sumSgAll = hA->Integral();

                dout("sumRd (data) bins:");
                    tempd = 0;
                    for(int i=1; i<=hist_data[0]->GetNbinsX(); i++ )
                    {
                        dout("bin i", i, ":", hist_data[0]->GetBinContent(i));
                        tempd+= hist_data[0]->GetBinContent(i);
                    }
                    dout("sum:", tempd); 
                sumRd = hist_data[0]->Integral(GetFitRange(hist_data[0], true), GetFitRange(hist_data[0], false) - 1*minusone);
                //sumRd = hist_data[0]->Integral();
                dout("sumSg bins:");
                    tempd = 0;
                    for(int i=GetFitRange(hist_data[0], true); i < GetFitRange(hist_data[0], false); i++ )
                    {
                        dout("bin i", i, ":", hA->GetBinContent(i));
                        tempd+= hA->GetBinContent(i);
                    }
                    dout("sum:", tempd); 
                sumSg = hA->Integral(GetFitRange(hist_data[0], true), GetFitRange(hist_data[0], false) - 1*minusone);

                a = param[0];
                aErr = param_err[0];
            }
            else
            {
                hA = hist_mc_photon[0];
                sumSgAll = hA->Integral();
                sumRd = hist_data[0]->Integral();
                sumSg = hA->Integral(GetFitRange(hist_data[0], true), GetFitRange(hist_data[0], false) - 1*minusone);
                a = param[0];
                aErr = param_err[0];
            }
            Double_t sumLL_fit = hist_mc_rad[0]->Integral(GetFitRange(hist_data[0], true), GetFitRange(hist_data[0], false) - 1*minusone);
            dout("a, sumSgAll, sumRd_fit, sumSg_fit, sumLL_fit", a, sumSgAll, sumRd, sumSg, sumLL_fit);
            //Double_t N = a * sumRd * (sumSgAll / sumSg);  
            //Double_t N = a * (sumRd - hist_mc_rad[0]->Integral(GetFitRange(hist_data[0], true), GetFitRange(hist_data[0], false))) * (sumSgAll / sumSg);       

            dout("N =", a ,"*", "(",sumRd, "-", sumLL_fit,") * (",sumSgAll, "/", sumSg);       
            Double_t N = a * (sumRd - sumLL_fit) * (sumSgAll / sumSg);              
            Double_t dS = sumSgAll - sumSg;
            Double_t Nerr = TMath::Sqrt( pow((1 + dS/sumSg), 2) * ( pow(sumRd, 2) * pow(aErr, 2) + pow(a, 2) * sumRd ) \
                                        + pow(a, 2) * pow(sumRd, 2) * ( dS + pow(dS, 2) / sumSg ) / pow(sumSg, 2) );
            Double_t NLL =  hist_mc_rad[0]->Integral(), NLLerr(0);
            if (QQfit == 1 && fitWithLL==1 && fitWithLLinBg==0)
            {
                dout("sumLLAll (LL) bins:");
                    double tempd = 0;
                    for(int i=1; i<=hist_mc_rad[0]->GetNbinsX(); i++ )
                    {
                        dout("bin i", i, ":", hist_mc_rad[0]->GetBinContent(i), "+-", hist_mc_rad[0]->GetBinError(i));
                        tempd+= hist_mc_rad[0]->GetBinContent(i);
                    }
                    dout("sum:", tempd); 
                dout("N+=",hist_mc_rad[0]->Integral());
                N += hist_mc_rad[0]->Integral();
                Double_t hist_mc_noradIntegrated_error = 0;
                Double_t total = hist_mc_rad[0]->IntegralAndError(1, hist_mc_rad[0]->GetNbinsX(), hist_mc_noradIntegrated_error,"");
                NLLerr = hist_mc_noradIntegrated_error;
                Nerr = TMath::Sqrt( Nerr*Nerr + hist_mc_noradIntegrated_error*hist_mc_noradIntegrated_error);
                dout(total, "=", hist_mc_rad[0]->GetSumOfWeights());
                //dout(hist_mc_rad[0]->GetSumw2()->GetSum());
                float err(0.);
                int bins = hist_mc_rad[0]->GetNbinsX();
                double tem=0;
                for(int ii=1; false && ii<=5; ++ii)
                {
                        dout(hist_mc_rad[0]->GetBinContent(ii), \
                            hist_mc_rad[0]->GetBinError(ii), "=", sqrt(hist_mc_rad[0]->GetSumw2()->GetAt(ii)), "!=", \
                            sqrt(hist_mc_rad[0]->GetBinContent(ii)), hist_mc_rad[0]->GetBinContent(ii));
                        tem+=hist_mc_rad[0]->GetSumw2()->GetAt(ii);
                        err += hist_mc_rad[0]->GetBinError(ii)*hist_mc_rad[0]->GetBinError(ii)*0.05*0.05;
                }
                dout("tem", tem);
                dout(sqrt(err));

            }
            dout("N +/- dN =", N, Nerr);
            
            //dout("param[0]", param[0], param_err[0], param_err[0]);
            if (QQfit == 0)
            {
                //DoReparametrisation(1, param_xgamma, param_err_xgamma, i);
                //DoReparametrisationforQQ(1, param_xgamma_PhotonsFitforQQ, param_err_xgamma_PhotonsFitforQQ, i);
            }

            dout("hist_mc_norad (had.bg.) bins:");
            double tempd = 0;
                    for(int i=1; i<=hist_mc_norad[0]->GetNbinsX(); i++ )
                    {
                        dout("bin i", i, ":", hist_mc_norad[0]->GetBinContent(i), "+-", hist_mc_norad[0]->GetBinError(i));
                        tempd+= hist_mc_norad[0]->GetBinContent(i);
                    }
                    dout("sum:", tempd); 


            DoComplicatedScale(hist_mc_norad[0], 1 - param[0], param_err[0]);//Bg*a
            DoComplicatedScale(hist_mc[0], param[0], param_err[0]);//QQ*a
            if (QQfit == 1 && fitWithLL == 0)
                hist_res[0] = (TH1D*)hist_mc[0]->Clone(); //QQ
            else if (QQfit == 0)
            {
                DoComplicatedScale(hist_mc_photon[0], param[0], param_err[0]);
                hist_res[0] = (TH1D*)hist_mc_photon[0]->Clone(); 
            }
            dout("hist_res[0][3] = ", hist_res[0]->GetBinContent(3));
            //#temp if (QQfit==0)  DoComplicatedScale(hist_res[0], param[0], param_err[0]);//LL*a or QQ*a
            hist_res[0]->Add(hist_mc_norad[0]);// LL + bg'*(1-a) || QQ*a + bg'*(1-a)

            

            if (QQfit == 1 && fitWithLL == 1)
                hist_res[0]->Add(hist_mc[0]);//LL +  QQ'*a + bg'*(1-a)
            // dout("hist_res[0][3] = ", hist_res[0]->GetBinContent(3));
                 dout("hist_data[0][3] = ", hist_data[0]->GetBinContent(3));
                // dout("hist_mc_rad[0][3] = ", hist_mc_rad[0]->GetBinContent(3));
                // dout("hist_mc_norad[0][3] = ", hist_mc_norad[0]->GetBinContent(3));
                // dout("hist_mc[0][3] = ", hist_mc[0]->GetBinContent(3));
                // dout("sum:", hist_mc_rad[0]->GetBinContent(3) + hist_mc_norad[0]->GetBinContent(3) + hist_mc[0]->GetBinContent(3));
            


            TString tempstr, vartex;
            tempstr.Form( "deltaz_fit");
            vartex.Form("#LT #delta Z #GT");
            gStyle->SetOptStat(0);
            TCanvas* c  = new TCanvas("c_"+tempstr, tempstr, 800, 700); 
            Double_t y_max = 1.2 * hist_data[0]->GetMaximum();
            TH2D *h_window_control = new TH2D(tempstr + "_win", "title", hist_data[0]->GetNbinsX(), 0, \
                                     hist_data[0]->GetBinCenter(hist_data[0]->GetNbinsX()) + hist_data[0]->GetBinWidth(hist_data[0]->GetNbinsX())/2, \
                                     10, 0., y_max);//array_bin[0], array_bin[number_bins - 1]


            c->GetPad(0)->SetTicks(1,1);
            c->GetPad(0)->SetFrameBorderMode(0);
            c->GetPad(0)->SetBorderMode(0);
            c->GetPad(0)->SetFillColor(kWhite);
            c->GetPad(0)->SetGrid(0, 0);
            //TVirtualPad * pad = test->cd(i % m + 1);
            //c->GetPad(0)->SetBottomMargin(0.05);
            dout("t GetTopMargin() const: ", c->GetPad(0)->GetTopMargin() );
            c->GetPad(0)->SetTopMargin(2* c->GetPad(0)->GetTopMargin());


            sign_window(c->GetPad(0), h_window_control, vartex , "Entries", "", "middle");
            h_window_control->GetXaxis()->SetTitleOffset(1.0);
            h_window_control->GetYaxis()->SetTitleOffset(1.1);
            c->GetPad(0)->SetMargin(c->GetPad(0)->GetLeftMargin() + 0.03 , \
                                            c->GetPad(0)->GetRightMargin() - 0.03 ,\
                                            c->GetPad(0)->GetBottomMargin()  + 0.03, \
                                            c->GetPad(0)->GetTopMargin() - 0.03);
            //h_window_control->GetYaxis()->SetRange(0, h_det_rad_sum[i]->GetMaximum()*1.3);
            h_window_control->Draw();

            TLegend *leg = new TLegend(0.5, 0.4, 0.9, 0.79);//(0.5, 0.5, 0.9, 0.89);//TLegend(0.55, 0.6, 0.95, 0.91);//
            if (dZdetailed) leg = new TLegend(0.5, 0.5, 0.9, 0.79);//0.55, 0.65, 0.9, 0.91
            leg->SetBorderSize(0);
            leg->SetFillColor(0);
            hist_res[0]->SetLineColor(kRed);
            hist_res[0]->SetLineWidth(2);
            hist_res[0]->SetFillColor(0);//kYellow
    
            hist_mc[0]->SetLineColor(kBlue);
            hist_mc[0]->SetFillColor(kBlue);//kYellow
            hist_mc[0]->SetFillStyle(3004);
            hist_mc[0]->Sumw2();

            hist_mc_photon[0]->SetLineColor(kBlue);
            hist_mc_photon[0]->SetFillColor(kBlue);//kYellow
            hist_mc_photon[0]->SetFillStyle(3004);
            hist_mc_photon[0]->Sumw2();

            hist_mc_rad[0]->SetLineColor(kMagenta+3);
            hist_mc_rad[0]->SetFillColor(kMagenta+3);//kYellow
            hist_mc_rad[0]->SetFillStyle(3006);
            hist_mc_rad[0]->Sumw2();

            hist_mc_norad[0]->SetLineColor(kOrange+7);
            hist_mc_norad[0]->SetFillColor(kOrange+7);//kYellow
            hist_mc_norad[0]->SetFillStyle(3005);
            hist_mc_norad[0]->Sumw2();

            hist_data[0]->SetMarkerStyle(21);
            hist_data[0]->SetMarkerSize(1);//0.7
            hist_data[0]->Sumw2();
                TPaveText* inform;// = new TPaveText(0.6, 0.61, 0.94, 0.92, "NDC");
        
                //leg->SetX1(0.5);
                //leg->SetY1(0.5);
                //leg->SetX2(0.9);
                //leg->SetY2(0.89);
                inform = new TPaveText(0.45,0.3,0.9,0.5, "NDC");
                TText *t1, *t2, *t3, *t4;
                TString s1, s2, s3, s4; 
                s1.Form("fit range: bins %i .. %i", int(left_bound), int(right_bound - 1)); 
                s2.Form("#chi^{2} / %i-2 = %.2f", ndf+2, chi_squared);
                s3.Form("N_{fitted photons} = %.2f +- %.2f", N, Nerr);
                s4.Form("N_{LL photons} = %.2f +- %.2f", NLL, NLLerr);
                t1 = inform->AddText(s1); t1->SetTextSize(0.04);
                t2 = inform->AddText(s2); t2->SetTextSize(0.04);
                t3 = inform->AddText(s3); t3->SetTextSize(0.04);
                if  (QQfit == 1 && fitWithLL==1)
                {
                    t4 = inform->AddText(s4); t4->SetTextSize(0.04);                    
                }
                inform->SetFillColor(0);
                inform->SetBorderSize(0);
            TH1D datamarker_h;
            datamarker_h.SetMarkerColor(hist_data[0]->GetMarkerColor()); 
            datamarker_h.SetMarkerSize(2); 
            datamarker_h.SetMarkerStyle(hist_data[0]->GetMarkerStyle()); 


            leg->AddEntry(&datamarker_h, "ZEUS", "p"); 
            if(QQfit == 1)
                leg->AddEntry(hist_mc[0], "QQ", "f"); //blue
            else
                leg->AddEntry(hist_mc_photon[0], "Sg.(LL+QQ)", "f"); //blue
            if (fitWithLL==1)
                leg->AddEntry(hist_mc_rad[0], "LL", "f");// red dots
            leg->AddEntry(hist_mc_norad[0], "Hadronic BG", "f");// small dots
            leg->AddEntry(hist_res[0], "Fit result", "f");//yellow area

            hist_res[0]->DrawClone("HIST SAME"); //E1 - with errors
            if(QQfit == 1)
                hist_mc[0]->DrawClone("HIST SAME");    //к нему рисуем синий QQ. без ошибок
            else
                hist_mc_photon[0]->DrawClone("HIST SAME");    //к нему рисуем синий QQ. без ошибок

            if (fitWithLL==1)
                hist_mc_rad[0]->DrawClone("HIST SAME");    //к нему рисуем красный LL. без ошибок
            hist_mc_norad[0]->DrawClone("HIST SAME");  //к нему рисуем маленькие точечки Hadronic BG. без ошибок
        
            hist_data[0]->SetMarkerColor(kBlack);//kRed
            hist_data[0]->SetLineColor(kBlack);
            hist_data[0]->SetLineWidth(2);
            hist_data[0]->Draw("P X0 E SAME");//DrawClone("P E1 SAME");  
            
            leg->DrawClone();

            if (dZdetailed)
            {
                    inform->Draw();
                    TLine *lineLeft = new TLine(), *lineRight = new TLine();
                    
                    lineLeft->SetLineWidth(2);
                    lineLeft->SetLineStyle(2);
                    lineLeft->DrawLine(leftRange, 0., leftRange, h_window_control->GetYaxis()->GetXmax());
                    lineRight->SetLineWidth(2);
                    lineRight->SetLineStyle(2);
                    lineRight->DrawLine(sys_fit, 0., sys_fit, h_window_control->GetYaxis()->GetXmax());
            }
            else
            {
                cout << "fit range: bins " << int(left_bound)<< ".."  << int(right_bound - 1) << endl;
                cout << "#chi^{2} /" << ndf+2 << "-2 = " << chi_squared << endl;
                cout << "N_{fitted photons} = " << N <<  "+-" <<  Nerr << endl;
                cout << "N_{LL photons} = " << NLL << "+-" << NLLerr << endl;
            }
            TString str_temp2(whichCorrection);
            if (QQfit == 1)
                str_temp2 += "_QQfit";
            else
                str_temp2 += "_PhotonFit";
            if (fitWithLL == 1)
                str_temp2 += "_withLL";
            else
                str_temp2 += "_noLL";
            if (fitWithLLinBg == 1)
                str_temp2 += "_LLinBg";
            else
                str_temp2 += "_noLLinBg";

            TPaveText *t = new TPaveText(0.27, 0.85, 0.8, 0.95, "NDC"); // left-up
                t->AddText("ZEUS");
                t->SetFillColor(0);
                t->SetBorderSize(0);
                t->SetFillStyle(0);
                t->Draw();

            dout(tempstr + "_" + str_temp2  + ".png");
            c->Print(tempstr + "_" + str_temp2  + ".png");
         
    }


    if (nodebugmode) cout << "Finish" << endl;
    f->Write();
    hist.selectedoutput.close();
    debug.close();
    cerr << "Finish" << endl;
    return 0;
}


void minuitFunction(int& nDim, double* gout, double& result, double par[], int flg) 
{
    Int_t ndf, left, right;
    result = chi2(par, ndf, left, right, chi_method);
}

Double_t chi2(double* par, Int_t& ndf, Int_t& left, Int_t& right, TString s_method)
{
    Double_t res = 0.;
    ndf = 0;
    Int_t index;
    if(fit_method == "deltaz") 
    {
        index = g_index_deltaz;
        left = GetFitRange(hist_data[index], true);//hist_data[index]->FindBin(0.) - 1;
        right = GetFitRange(hist_data[index], false) ; // 5;//20;//hist_data[index]->FindBin(0.8);//18;//hist_data[index]->FindBin(0.8); //0.8 / 0.05
        //if (nodebugmode) cout<<"right "<<right<<" left "<< left<< endl; 
        //dout("left:", left,"right",right);exit(1);
    }
    else
    if(fit_method == "fmax") 
    {
        index = g_index_fmax;
        left = 1;//0.2
        right = 20;//1.
    }
    else 
    {
        cerr << "wrong fit method: " << fit_method << endl;
        exit(-1);
    }

    for(Int_t i = left; i < right; i++)
    {
        //dout("i",i);
        Double_t diff;
        //Check the bins abd ranges
        //if (nodebugmode) cout << "getting bin " << i << " from " << hist_data_sum[index]->GetBinLowEdge(i+1) << " to " <<  hist_data_sum[index]->GetBinLowEdge(i+2) << endl;
        Double_t s_d = hist_data[index]->GetBinError(i+1);
        Double_t s_l = hist_mc_rad[index]->GetBinError(i+1);
        Double_t s_q = hist_mc[index]->GetBinError(i+1);
        Double_t s_ph = hist_mc_photon[index]->GetBinError(i+1);
        Double_t s_bg = hist_mc_norad[index]->GetBinError(i+1);
        //      Double_t s_photon = hist_mc_photon[index]->GetBinError(i+1);

        Double_t v_d = hist_data[index]->GetBinContent(i+1);
        Double_t v_l = hist_mc_rad[index]->GetBinContent(i+1);
        Double_t v_q = hist_mc[index]->GetBinContent(i+1);
        Double_t v_ph = hist_mc_photon[index]->GetBinContent(i+1);
        Double_t v_bg = hist_mc_norad[index]->GetBinContent(i+1);
            //      Double_t v_photon = hist_mc_photon[index]->GetBinContent(i+1);
            //
            // Ian's page
            //
            //      ebb = sdd**2*(param(1)**2*ggn(i)/sgg+(1.-param(1))**2*aan(i)/saa)
            //  edd(i) = sqrt(dd(i) + ebb)
        Double_t dd_i = v_d;
        Double_t sdd = hist_data[index]->GetSum();
            //      dd_i /= sdd;
            //      Double_t ggn_i = v_photon;
            //      Double_t sgg = hist_mc_photon[index]->GetSum();
            //      ggn_i *= sdd/sgg;
        Double_t aan_i = v_bg;
        Double_t saa = hist_mc_norad[index]->GetSum();
            //      aan_i *= sdd/saa;
            //      Double_t ebb = sdd*sdd*(par[0]*par[0]*ggn_i/(sgg*sgg) + (1-par[0])*(1-par[0])*aan_i/(saa*saa));


            // Oleg
            //
            // ====================================================================================================
                //  diff = hist_data[index]->GetBinContent(i+1) - hist_mc_rad[index]->GetBinContent(i+1) - par[0]*hist_mc[index]->GetBinContent(i+1) - (1-par[0])*hist_mc_norad[index]->GetBinContent(i+1);
            //EB:
            //!!!! by 031015
        if (QQfit == 0)
            diff = hist_data[index]->GetBinContent(i+1) \
                    - par[0]*hist_mc_photon[index]->GetBinContent(i+1) - \
                    (1-par[0])*hist_mc_norad[index]->GetBinContent(i+1);
        else
            diff = hist_data[index]->GetBinContent(i+1) - fitWithLL*hist_mc_rad[index]->GetBinContent(i+1) \
                    - par[0]*hist_mc[index]->GetBinContent(i+1) - (1-par[0])*hist_mc_norad[index]->GetBinContent(i+1);
               
        ///if (nodebugmode) cout << "par[0] = " << par[0] ;
                // ====================================================================================================
                //
                // Ian
                //
                // ====================================================================================================
                //      diff = v_d/sdd - par[0]/sgg - (1-par[0])*aan_i/saa;
                //diff = dd_i - par[0]*ggn_i*sdd/sgg - (1-par[0])*aan_i*sdd/saa;
                // ====================================================================================================
        Double_t denom = 0.;
        
        if(s_method == "Barlow-Beeston") 
        {
            //  denom = 1.;//s_d*s_d + s_l*s_l + par[0]*par[0]*s_q*s_q + (1.-par[0])*(1.-par[0])*s_bg*s_bg;
                //  denom = v_d - v_l + par[0]*par[0]*v_q + (1.-par[0])*(1.-par[0])*v_bg;
                //  denom = (s_d + s_l)*(s_d + s_l) + par[0]*par[0]*s_q*s_q + (1.-par[0])*(1.-par[0])*s_bg*s_bg; //this sent to Ian
                //
                // Oleg
                //
                // ====================================================================================================
                  //denom = s_d*s_d + s_l*s_l + par[0]*par[0]*s_q*s_q + (1.-par[0])*(1.-par[0])*s_bg*s_bg;
            if(denom==0)
            {
                //! cerr << "denom = 0 in cross_sec.cxx. Exiting" << endl;
                //      exit(-1);
            }
            //  denom = (s_d + s_l)*(s_d + s_l) + par[0]*par[0]*s_q*s_q + (1.-par[0])*(1.-par[0])*s_bg*s_bg;

            if (QQfit == 0)
                denom = s_d*s_d + par[0]*par[0]*s_ph*s_ph + (1.-par[0])*(1.-par[0])*s_bg*s_bg;
            else
                denom = s_d*s_d + s_l*s_l*fitWithLL + par[0]*par[0]*s_q*s_q + (1.-par[0])*(1.-par[0])*s_bg*s_bg;

            //  if (nodebugmode) cout << "min: " << i << " " << s_d << " " << s_l << " " << s_q << " " << s_bg << " " << par[0] << " " << denom << endl;
                //  if (nodebugmode) cout << " denom = " << denom << endl;
                ///if (nodebugmode) cout << "dz " << i << "\t" << "numer=" << diff*diff << "\tdenom=" << denom << "\tndf=" << ndf << " " << diff*diff/denom << endl;
                ///if (nodebugmode) cout <<i+1 << " yhDat=" << v_d << "\tyh1= " << v_q << "\tyh2= " << v_bg  << "\tyhDatE=" << s_d << "\tyh1E= " << s_q << "\tyh2E= " << s_bg << "\t sl = " << s_l << endl;
                // ====================================================================================================
                //
                // Ian
                //
                // ====================================================================================================
                //  denom = s_d*s_d + par[0]*par[0]*s_photon*s_photon + (1.-par[0])*(1.-par[0])*s_bg*s_bg;
                //denom = dd_i + ebb;
                //  if (nodebugmode) cout << dd_i << " - " << par[0] << "*" << ggn_i << "*" <<  sdd << "/" << sgg << " - (1-" << par[0] << ")*" << aan_i << "*" << sdd << "/ " << saa << endl;
                //  if (nodebugmode) cout << 
                // ====================================================================================================
                //denom = (s_d )*(s_d ) + par[0]*par[0]*s_q*s_q + (1.-par[0])*(1.-par[0])*s_bg*s_bg;
        }
        else if(s_method == "Gauss")
            if (QQfit == 0)
                denom = s_d*s_d;
            else
                denom = s_d*s_d + s_l*s_l;//?
        else
        {
            cerr << "Unknown fit method: " << s_method << ". Exiting" << endl;
            exit(-1);
        }
        ///if (nodebugmode) cout << "errs: " << i << " " << par[0] << " " << s_d << " " << s_l << " " << s_q << " " << s_bg << " " << diff << " " << denom << endl;  
            // if (nodebugmode) cout << "bin " << i+1  << " " << diff << " " << denom << " " << diff*diff/denom << " " << res << endl;

        if(par[0]!=par[0])
            res += 1000.;
        else
            res += diff*diff/denom;
        ndf++;
    }
    //exit(1);
    ndf = ndf - 2 ;//?- QQfit
    //   if (nodebugmode) cout << "ndf = " << ndf << endl;
        //  res /= float(ndf-1);
        //  if (nodebugmode) cout << float(hist_data[index]->GetNbinsX() - 1) << endl;
        //   if (nodebugmode) cout << "calling chi2: " << res << endl << endl << endl;
    return res;
}
