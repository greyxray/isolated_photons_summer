#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool nodebugmode = false;

#include <TH1D.h>
#include <TChain.h>
#include <TString.h>
#include "constants.h"
#include "selector.h"
#include "runinfo.h"
extern void fill_chain(TChain* chain, TString period, Bool_t data, TString mc_type, Bool_t use_clustered);


int main(int argc, char *argv[])
{

  bool nodebugmode = false;
  for (Int_t i = 0; i < argc; i++) 
    cout << "argv[" << i << "] = " << argv[i] << endl;
  Bool_t use_corr = kTRUE;
  TString s_use_corr = "1";
  Bool_t use_2ndcorr = kFALSE;
  TString s_use_2ndcorr = "1";
  Bool_t data = kTRUE;//kFALSE;
  TString s_data = "data";
  Bool_t use_clustered = kFALSE;
  TString s_use_clustered = "1";
  TString systematics_calc = "zero";
  TString mc_type = "mc_bg_rad";
  TString mc_corr_type = "lepto_corr";
  if((argc == 2) && ((TString)argv[1] == "-h" || (TString)argv[1] == "--help") ) 
  {
    cout << "using: main <period> <data> <use_corr> <use_2ndcorr> <use_clustered>" << endl;
    cout << "  <period>: 0405e, 06e, 0607p" << endl;
    cout << "  <data>: data, mc_prph, mc_bg_rad, mc_bg_norad" << endl;
    //    cout << "  <mc_type_corr>: lepto_corr, ariadne_corr" << endl;
    cout << "  <use_corr>: 1, 0" << endl;
    cout << "  <use_2ndcorr>: 1, 0" << endl;
    cout << "  <use_clustered>: 1, 0" << endl;

    exit(0);
  }
  
  TString period = "989900";
  if(argc>1)
    period = (TString)argv[1];
  if(argc>2) 
  {
    s_data = (TString)argv[2];
    if(s_data == "data") 
      data = kTRUE; 
    else if(s_data == "mc_prph")
  	{
  	  data = kFALSE;
  	  mc_type = "mc_prph";
  	} 
    else if(s_data == "mc_bg_rad")
    {
      data = kFALSE;
      mc_type = "mc_bg_rad";
    } 
    else if(s_data == "mc_bg_norad")
		{
		  data = kFALSE;
		  mc_type = "mc_bg_norad";
		} 
    else    
		{
		  cout << "unknown data type: " << s_data << endl;
		  exit(-1);
		}
  }
  /*  if(argc>3) {
    TString s_mc_corr_type = (TString)argv[3];
    if(s_mc_corr_type == "lepto_corr")
      mc_corr_type = "lepto_corr";
    else 
      if(s_mc_corr_type == "ariadne_corr")	
	mc_corr_type = "ariadne_corr";
      else
	{
	  cout << "unknown mc_corr_type (lepto_corr, ariadne_corr): " << s_mc_corr_type << endl;
	  exit(-1);
	}
	}*/
  if(argc>3) 
  {
    s_use_corr = (TString)argv[3];
    if(s_use_corr=="1") 
      use_corr = kTRUE;
    else if(s_use_corr=="0") 
      use_corr = kFALSE;
    else
  	{
  	  cout << "unknown parameter for use_corr (1 or 0): " << s_use_corr << endl;
  	  exit(-1);
  	}
  }
  if(argc>4) 
  {
    s_use_2ndcorr = (TString)argv[4];
    if(s_use_2ndcorr=="1") 
      use_2ndcorr = kTRUE;
    else if(s_use_2ndcorr=="0") 
      use_2ndcorr = kFALSE;
    else
    { 
  	  cout << "unknown parameter for use_2ndcorr (1 or 0): " << s_use_2ndcorr << endl;
  	  exit(-1);
    }
  }
  if(argc>5) 
  {
    s_use_clustered = (TString)argv[5];
    if(s_use_clustered=="1")
      use_clustered = kTRUE;
    else if(s_use_clustered=="0")
      use_clustered = kFALSE;
    else
  	{
  	  cout << "unknown parameter for use_clustered (1 or 0): " << s_use_clustered << endl;
  	  exit(-1);
  	}
  }
  
  TString s_chain;
  s_chain = "orange";
  TChain* ch = new TChain(s_chain);
  fill_chain(ch, period, data, mc_type, use_clustered);
  selector PromptPhotonPlusJetDIS;
  PromptPhotonPlusJetDIS.Init(ch, period, data, mc_type, mc_corr_type, use_corr, use_2ndcorr, use_clustered);
  if(argc>6) 
  {
    PromptPhotonPlusJetDIS.systematics_sufix = (TString)argv[6];
    if(PromptPhotonPlusJetDIS.systematics_sufix=="systJetE+") 
    {
      PromptPhotonPlusJetDIS.systJetE_gt10 = 1.015;//0.975 1. 1.025
      PromptPhotonPlusJetDIS.systJetE_lt10 = 1.025;
      PromptPhotonPlusJetDIS.systJetE_lt6 = 1.04;
    } 
    else if(PromptPhotonPlusJetDIS.systematics_sufix=="systJetE-") 
    {
      PromptPhotonPlusJetDIS.systJetE_gt10 = 0.985;
      PromptPhotonPlusJetDIS.systJetE_lt10 = 0.975;
      PromptPhotonPlusJetDIS.systJetE_lt6 = 0.96;
    } 
    else if(PromptPhotonPlusJetDIS.systematics_sufix=="systPhE+")
	   PromptPhotonPlusJetDIS.systPhE = 1.02;//0.98 1. 1.2 
    else if(PromptPhotonPlusJetDIS.systematics_sufix=="systPhE-")
	   PromptPhotonPlusJetDIS.systPhE = 0.98;//0.98 1. 1.2 
    else if(PromptPhotonPlusJetDIS.systematics_sufix=="systElE+")
	   PromptPhotonPlusJetDIS.systElE = 1.02;//0.98 1. 1.2 
    else if(PromptPhotonPlusJetDIS.systematics_sufix=="systElE-")
     PromptPhotonPlusJetDIS.systElE = 0.98;//0.98 1. 1.2  
    else if(PromptPhotonPlusJetDIS.systematics_sufix=="systAcc")// calc with wtx==1(systAcc = 0) and wtx!=1.(systAcc = 1) take the diff/2 as systematics. wtx = a*systAcc - (systAcc-1)
     PromptPhotonPlusJetDIS.systAcc = 0.0;//0.98 1. 1.2   
    else if(PromptPhotonPlusJetDIS.systematics_sufix != "zero")
    	{
    	  cout << "unknown parameter for systematics_calc: " << PromptPhotonPlusJetDIS.systematics_sufix << endl;
    	  exit(-1);
    	}
  }
  if (!nodebugmode) cout << "systJetE_lt10 " << PromptPhotonPlusJetDIS.systJetE_lt10 << endl <<
"systJetE_gt10 " << PromptPhotonPlusJetDIS.systJetE_gt10 << endl <<
"systPhE " << PromptPhotonPlusJetDIS.systPhE << endl <<
"systElE " << PromptPhotonPlusJetDIS.systElE << endl;
  //systdZfit = 1;//
  //systAcc = 1.;//
  PromptPhotonPlusJetDIS.Begin();
  PromptPhotonPlusJetDIS.Process();
  //  PromptPhotonPlusJetDIS.Terminate();
  return 0;
}
