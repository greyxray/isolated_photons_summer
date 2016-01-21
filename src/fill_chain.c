#include <stdlib.h>
#include <iostream>
using namespace std;

#include <TChain.h>
#include "04pNtuplesNames.h"
#include "0405eBGntuplesNames.h" //warning
#include "0405e_2BGntuplesNames.h" //warning
//#include "0405ePHPDIR_PYTHIAntuplesNames.h"//warning
#include "0405eNtuplesNames.h"
#include "0607pBGntuplesNames.h"
#include "0607pNtuplesNames.h"
#include "06eBGntuplesNames.h"
#include "06e_2BGntuplesNames.h"
#include "06eNtuplesNames.h"
#include "0405ePRPHntuplesNames.h"//warning
//#include "0405ePRPHPHPntuplesNames.h"//warning
#include "06ePRPHntuplesNames.h"
#include "PrivateNtuplesNames.h"
void fill(TChain* chain, TString location, TString* str, Int_t n);

void fill_chain(TChain* chain, TString run_period, Bool_t data, TString mc_type, Bool_t use_clustered)
{
  if(mc_type == "mc_prph")
    {
      if(run_period == "0405e") {
	if(!use_clustered)
	  fill(chain, str_location_prph0405e, rootFile_prph0405e, numberOfRootFiles_prph0405e);
	else
	  fill(chain, str_location_prph0405eprivate, rootFile_prph0405eprivate, numberOfRootFiles_prph0405eprivate);      
      } else if(run_period == "06e") {
	if(!use_clustered)
	  fill(chain, str_location_prph06e, rootFile_prph06e, numberOfRootFiles_prph06e);
	else
	  fill(chain, str_location_prph06eprivate, rootFile_prph06eprivate, numberOfRootFiles_prph06eprivate);      
      } else {cerr << "mc_prph: unknown period: " << run_period << endl; exit(-1);}
      
    }
  else
    {
      if(run_period == "0405e")
	{
	  if(data)
	    {
	      if(!use_clustered)
		fill(chain, str_location0405e, rootFile0405e, numberOfRootFiles0405e);
	      else
		fill(chain, str_location0405eprivate, rootFile0405eprivate, numberOfRootFiles0405eprivate);
	    } 
	  else
	    {
	      if(mc_type == "mc_bg_rad" || mc_type == "mc_bg_norad")
		{
		  if(!use_clustered){
		    fill(chain, str_location0405e_bg, rootFile0405e_bg, numberOfRootFiles0405e_bg);
		    fill(chain, str_location0405e_2bg, rootFile0405e_2bg, numberOfRootFiles0405e_2bg);//warning
		  }
		  else
		    fill(chain, str_location0405eleptoprivate, rootFile0405eleptoprivate, numberOfRootFiles0405eleptoprivate);		
		} 
	      else
		{
		  cout << "unknown mc type: " << mc_type << endl;
		  exit(-1);
		}
	    }
	} 
      else if(run_period == "06e")
	{
	  if(data)
	    {
	      if(!use_clustered)
		fill(chain, str_location06e, rootFile06e, numberOfRootFiles06e);
	      else
		fill(chain, str_location06eprivate, rootFile06eprivate, numberOfRootFiles06eprivate);
	    } 
	  else
	    {
	      if(mc_type == "mc_bg_rad" || mc_type == "mc_bg_norad")
		{
		  if(!use_clustered) {
		    fill(chain, str_location06e_bg, rootFile06e_bg, numberOfRootFiles06e_bg);
		    fill(chain, str_location06e_2bg, rootFile06e_2bg, numberOfRootFiles06e_2bg);
		  }
		  else
		    fill(chain, str_location06eleptoprivate, rootFile06eleptoprivate, numberOfRootFiles06eleptoprivate);
		} 
	      else
		{
		  cout << "unknown mc type: " << mc_type << endl;
		  exit(-1);
		}
	    }
	}
      else if(run_period == "0607p")
	{
	  if(data)
	    {
	      if(!use_clustered)
		fill(chain, str_location0607p, rootFile0607p, numberOfRootFiles0607p);
	      else
		fill(chain, str_location0607pprivate, rootFile0607pprivate, numberOfRootFiles0607pprivate);
	    } 
	  else
	    {
	      if(mc_type == "mc_bg_rad" || mc_type == "mc_bg_norad")
		{
		  if(!use_clustered)
		    fill(chain, str_location0607p_bg, rootFile0607p_bg, numberOfRootFiles0607p_bg);
		  else
		    fill(chain, str_location0607pleptoprivate, rootFile0607pleptoprivate, numberOfRootFiles0607pleptoprivate);
		} 
	      else
		{
		  cout << "unknown mc type: " << mc_type << endl;
		  exit(-1);
		}
	    }
	} 
      else if(run_period == "04p")
	{
	  if(data)
	    {
	      if(!use_clustered)
		fill(chain, str_location04p, rootFile04p, numberOfRootFiles04p);
	      else
		fill(chain, str_location04pprivate, rootFile04pprivate, numberOfRootFiles04pprivate);
	    } 
	}
      else if(run_period == "all")
	{
	  if(data) {
	    if(!use_clustered) {
	      fill(chain, str_location04p, rootFile04p, numberOfRootFiles04p);
	      fill(chain, str_location0405e, rootFile0405e, numberOfRootFiles0405e);
	      fill(chain, str_location06e, rootFile06e, numberOfRootFiles06e);
	      fill(chain, str_location0607p, rootFile0607p, numberOfRootFiles0607p);
	    }
	    else {
	      fill(chain, str_location04pprivate, rootFile04pprivate, numberOfRootFiles04pprivate);
	      fill(chain, str_location0405eprivate, rootFile0405eprivate, numberOfRootFiles0405eprivate);
	      fill(chain, str_location06eprivate, rootFile06eprivate, numberOfRootFiles06eprivate);
	      fill(chain, str_location0607pprivate, rootFile0607pprivate, numberOfRootFiles0607pprivate);
	    }
	  }
	  else
	    {
	      if(mc_type == "mc_bg_rad" || mc_type == "mc_bg_norad")
		{
		  if(!use_clustered) {
		    fill(chain, str_location0405e_bg, rootFile0405e_bg, numberOfRootFiles0405e_bg);
		    fill(chain, str_location06e_bg, rootFile06e_bg, numberOfRootFiles06e_bg);
		    fill(chain, str_location0607p_bg, rootFile0607p_bg, numberOfRootFiles0607p_bg);
		  }
		  else
		    fill(chain, str_location0607pleptoprivate, rootFile0607pleptoprivate, numberOfRootFiles0607pleptoprivate);
		} 
	      else
		{
		  cout << "unknown mc type: " << mc_type << endl;
		  exit(-1);
		}
	    }
	}
    
      else
	{ cout << "error. Unknown period: " << run_period << endl; exit(-1);} 
    }  //  chain->Add("selectedEvents_lepto_989900.root");
  //chain->Add("1.root");
}


void fill(TChain* chain, TString location, TString* str, Int_t n)
{
  for(Int_t i=0; i<n; i++)
    {
      TString file = location + str[i];
      chain->Add(file);
      //cout << file << " added to chain in fill" << endl;
    }
    cout << chain->GetEntries() << " events chained" << endl;
}
