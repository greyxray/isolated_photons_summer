#include <iostream>
#include <fstream>
#include <vector>
#include "selector.h"

using namespace std;

#include <TLorentzVector.h>
#include <TMath.h>
#include <TObjArray.h>
//#include "Dijets.h"
#include "KtJet/KtEvent.h"
#include "KtJet/KtLorentzVector.h"
using KtJet::KtLorentzVector;
using KtJet::KtEvent;

Bool_t selector::SelectPartonLevel(Bool_t take_det_event)
{
  Bool_t take_pevent = kTRUE;
  Bool_t here_is_true_prph = kTRUE;
  Bool_t is_true_prph_candidate = kTRUE;
  Bool_t here_is_true_jet = kFALSE;
  Bool_t take_true_jet = kTRUE;
  if(Mc_q2 < 10.) {
    take_pevent = kFALSE;
    if(check_cuts)
      cout << "rejected by cut on true q2 = " << Mc_q2 << endl;
  }
  TVector3 v_true_electron(Mc_pfsl[0],Mc_pfsl[1],Mc_pfsl[2]);
  if ((v_true_electron.Theta()*180.0/TMath::Pi() < 139.8 )||
      (v_true_electron.Theta()*180.0/TMath::Pi() > 180.0 ))  {
      //      (v_true_electron.Theta()*180.0/TMath::Pi() > 171.9 ))  { //warning
    take_pevent = kFALSE;
    if(check_cuts)
      cout << "rejected by cut on true electron theta = " << v_true_electron.Theta()*180.0/TMath::Pi() << endl;
  }
  //cout << "created, OK" << endl;
  if(Mc_pfsl[3] < 10.)
    {
      take_pevent = kFALSE;
      if(check_cuts)
	cout << "rejected by cut on true electron energy = " << Mc_pfsl[3] << endl;
    }

  if(take_pevent) {
/*     hist.dis_Q2_true_part->Fill(Mc_q2, wtx); */
/*     hist.dis_electron_e_true_part->Fill(Mc_pfsl[3], wtx); */
/*     hist.dis_electron_theta_true_part->Fill(v_true_electron.Theta()*180.0/TMath::Pi(), wtx); */
/*     hist.dis_x_true_part->Fill(Mc_x, wtx); */
/*     hist.dis_y_true_part->Fill(Mc_y, wtx); */
  }
  //find true photon
  Int_t index_true_photon = -1;
  Int_t index_jet = -1;//this variable is to compare with Sanja, Nazar, Ian, Natasha
  if(!Data && (mc_type == "mc_bg_rad")/* || mc_type == "mc_bg_norad")*/)
    {
      for (Int_t i=0; i<Npart; i++)
	{
	  if (Part_id[i]==5)
	    {
	      index_jet=Part_jetid[i]-1;
	      index_true_photon=i;
	      break;
	    }
	}
    }
  if(!Data && mc_type == "mc_prph")
    {
      for (Int_t i=0; i<Npart; i++)
	{
	  if (Part_id[i]==12)
	    {
	      index_jet=Part_jetid[i]-1;
	      index_true_photon=i;
	      break;
	    }
	}
    }
  if(index_true_photon < 0)
    {
      here_is_true_prph = kFALSE;
      if(check_cuts)
	cout << "there is no photon in generated level" << endl;
    }

  return (take_pevent && here_is_true_prph && here_is_true_jet);
}
