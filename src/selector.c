#define selector_c
// The class definition in selector.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts ,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("selector.C")
// Root > T->Process("selector.C","some options")
// Root > T->Process("selector.C+")
//
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
//#include "selector.h"
//#ifndef constants_h
//#error include constants.h in selector.c
#include "constants.h"
//#endif
//#ifdef selector_cxx
#include "selector.h"
#include "runinfo.h"
//#include <TH2.h>
//#include <TStyle.h>
//#include <TSelector.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <TObjArray.h>
#include "Dijets.h"
#include "BCR_CalibTools.h"
#include "KtJet/KtEvent.h"
#include "KtJet/KtLorentzVector.h"
using KtJet::KtLorentzVector;
using KtJet::KtEvent;

extern Bool_t excludedrunlist(Int_t);
extern Bool_t take_run(Int_t);

extern Bool_t poltake(Int_t, Int_t, Int_t, Int_t, RunInfo runinfo[], const int);
extern Double_t polcorr0405e(Double_t );
extern Double_t polcorr0607p(Double_t );
extern Double_t polcorr06e(Double_t );
//extern Double_t jet_en_corr(Double_t eta, Double_t et);

extern "C"
{
	float pcele_(int &Imod,float &Emes,float &Emip,float &The,float &Phi);
}
//extern Double_t reweighting(Double_t , TString period, TString mc_type);
//extern void fill_trigger_bits(TH1D* h_dis, Int_t r_Fltw[], Int_t n);
//extern Bool_t flt_bit_is_1(UInt_t bit, Int_t r_Fltw[], Int_t n);
//extern Double_t zvtx_reweighting_0607p(const Double_t x);

//Int_t findMaxEt(Int_t sorted[], Double_t et_jets[], Int_t N);
//void sortEt(TObjArray *arrayNotSorted, TObjArray *arraySorted);

//Bool_t selector::Process(Long64_t entry)
Bool_t selector::Process()
{
	// The Process() function is called for each entry in the tree (or possibly
	// keyed object in the case of PROOF) to be processed. The entry argument
	// specifies which entry in the currently loaded tree is to be processed.
	// It can be passed to either selector::GetEntry() or TBranch::GetEntry()
	// to read either all or the required parts of the data. When processing
	// keyed objects with PROOF, the object is already loaded and is available
	// via the fObject pointer.
	//
	// This function should contain the "body" of the analysis. It can contain
	// simple or elaborate selection criteria, run algorithms on the data
	// of the event and typically fill histograms.
	//
	// The processing can be stopped by calling Abort().
	//
	// Use fStatus to set the return value of TTree::Process().
	//
	// The return value is currently not used.
	//  cout <<"geting tree... " ;//<< endl;
	Long64_t nentries = fChain->GetEntries();
	if (!nodebugmode) cout <<"Number of events to process: " << nentries << endl;
	//  if (nodebugmode) cout << "number_Q2bins: " << number_Q2bins << endl;
	//  if (nodebugmode) cout << "Q2 bin 0: " << Q2_bin[0] << endl;
	Bool_t breakindex = kFALSE;
	Bool_t take_event = kTRUE;
	Bool_t take_event_trig = kTRUE;
	here_is_prph = kFALSE;
	Bool_t here_is_jet = kFALSE;
	Bool_t take_jet = kTRUE;
	Bool_t print_interesting_events = kFALSE;
	Bool_t study_jets = kFALSE;//kTRUE;
	//  check_cuts = kTRUE;
	phot_count = 0;
	ofstream list_of_runs("runs" + period);
	Int_t Runnr_prev = 0;
	Bool_t debugcontinue = kTRUE;
	Int_t missed = 0;

	for(Long64_t entry=0; entry<nentries && debugcontinue; entry++)
	{
		//      if (nodebugmode) cout << "Eventnr = " << Eventnr << ", Npart = " << Npart << endl;
		//if (!nodebugmode) cout << "getting entry " << entry << " ... ";
		fChain->GetEntry(entry);
		if(Runnr != Runnr_prev) 
		{
			list_of_runs << Runnr << endl;
			Runnr_prev = Runnr;
		}
		hist.hist_runnr->Fill(Runnr);
		
		wtx = 1.;

		if(!Data) 
		{
			Double_t et_true_photon;
			Int_t index_true_photon = -1;
			TLorentzVector true_photon;

			if(mc_type == "mc_prph")    
			{
				for (Int_t i=0; i<Npart; i++)       
				{
					if (Part_id[i]==12)     
					{
						index_true_photon=i;
						break;
					}
				}
				if(index_true_photon >= 0)
					true_photon.SetPxPyPzE(Part_p[index_true_photon][0], Part_p[index_true_photon][1], Part_p[index_true_photon][2], Part_p[index_true_photon][3]);
				else 
				{
					cerr << "photon not found" << endl; exit(-1);
				}
				wtx *= etaph_reweighting(true_photon.Eta(), mc_type) * systAcc - (systAcc - 1);
				//  wtx *= etph_reweighting(true_photon.Et(), mc_type);
				wtx *= eph_reweighting(true_photon.E(), mc_type) * systAcc - (systAcc - 1);
				if (nodebugmode) cout << "eta = " << true_photon.Eta() << ", wtx_eta = " << etaph_reweighting(true_photon.Eta(), mc_type) << ", et = " << true_photon.E() << ", wtx_et = " << eph_reweighting(true_photon.E(), mc_type) << endl;
			}
		}

		if(!Data && mc_type != "mc_bg_rad")
		{
			wtx *= q2_reweighting(Mc_q2, mc_type) * systAcc - (systAcc - 1);// * y_reweighting_binbybin(Mc_y, mc_type) * eph_reweighting(mc_type); //warning
			if (nodebugmode) cout << "q2 = " << Mc_q2 << ", wtx_q2 = " << q2_reweighting(Mc_q2, mc_type) << endl;
		}
		//        wtx = q2_reweighting_separately(Mc_q2, mc_type, period); //warning
		//      if (nodebugmode) cout << "Mc_q2= " << 73.2351 << " res= " << q2_reweighting(73.2351,  mc_type, period);
		//      if (nodebugmode) cout << "Mc_q2= " << 21.6847 << " res= " << q2_reweighting(21.6847,  mc_type, period);
		//      if(Runnr == 56708 && Eventnr == 136113)
		{   
			//    if(Eventnr == 21334) check_cuts = kTRUE;//52258 22172
			//    else
			check_cuts = kFALSE;
			//    check_cuts = kTRUE;
			if(check_cuts) if (nodebugmode) cout << "going into " << Runnr << " " << Eventnr << endl;      
			take_event = kTRUE;
			take_event_trig = kTRUE;
			here_is_prph = kFALSE;
			here_is_jet = kFALSE;
			hist.zvtx->Fill(Zvtx, wtx);
			det_cross_sec_bin_et = -1;
			det_cross_sec_bin_eta = -1;
			det_cross_sec_bin_q2 = -1;
			det_cross_sec_bin_x = -1;
			det_cross_sec_bin_et_jet = -1;
			det_cross_sec_bin_eta_jet = -1;
			det_cross_sec_bin_xgamma = -1;
			det_cross_sec_bin_xp = -1;
			det_cross_sec_bin_dphi = -1;
			det_cross_sec_bin_deta = -1;
			det_cross_sec_bin_dphi_e_ph = -1;
			det_cross_sec_bin_deta_e_ph = -1;
			deltaRtrack = 999.;      
			//      if(period == "all")
			//  {

			if(Runnr>=47010 && Runnr<=51245)
				period = "04p";
			if(Runnr>=52258 && Runnr <=57123)
				period = "0405e";
			if(Runnr>=58207 && Runnr <=59947)
				period = "06e";
			if(Runnr>=60005 && Runnr <= 62639)
				period = "0607p";

			//  }

			if(Sincand < 1)
			{
				take_event = kFALSE;
				if(check_cuts)
					if (nodebugmode) cout << "rejected by Sincand = " << Sincand << endl;
			}
			if(check_cuts)
			{
				for(Int_t i=0; i<Sincand; i++)
					if (nodebugmode) cout << "electron cand " << i << ": E = " << Siecorr[i][2] * systElE << " " << Sith[i] << " " << Siq2el[i] << endl;
			}
			//
			//electron selection
			//
			Int_t sinistra_electron_number = -1;//
			Bool_t take_electron_event = kTRUE;
			for(Int_t i=0; i<1; i++) 
			{
				take_electron_event = kTRUE;
				if(Siq2el[i] < 10. || Siq2el[i] > 350.)
					take_electron_event = kFALSE;

				if(Siecorr[i][2] * systElE < 10.)
				{
					take_electron_event = kFALSE;
					if(check_cuts)
						if (nodebugmode) cout << "rejected by Siecorr[0][2] = " << Siecorr[i][2] * systElE << endl;
				}
				//  
				if(Sith[i]*180.0/TMath::Pi() < 139.8 || Sith[i]*180.0/TMath::Pi() > 180.0) //if(Sith[i]*180.0/TMath::Pi() < 139.8 || Sith[i]*180.0/TMath::Pi() > 171.9)
				{
					take_electron_event = kFALSE;
					if(check_cuts)
						if (nodebugmode) cout << "rejected by Sith = " << Sith[0] * 180./TMath::Pi() << endl;
				}

				if((TMath::Abs(Sipos[i][0]) < 14.8) &&
						(Sipos[i][1]  >-14.6)  &&
						(Sipos[i][1]  < 12.5))  
				{
					take_electron_event = kFALSE;
					if(check_cuts)
						if (nodebugmode) cout << "rejected by Sipos[0][0] = " << Sipos[0][0] << ", Sipos[0][1] = " << Sipos[0][1] << endl;
				}
				if(take_electron_event)
				{
					sinistra_electron_number = i;
					break;
				}
			}
			if(!take_electron_event)
				take_event = kFALSE;
			if(Zvtx < -40. || Zvtx > 40.) 
			{
				take_event = kFALSE;
				if(check_cuts)
					if (nodebugmode) cout << "rejected by Zvtx = " << Zvtx << endl;
			}

			if(Cal_empz < 35. || Cal_empz > 65.) 
			{
				take_event = kFALSE;
				if(check_cuts)
					if (nodebugmode) cout << "rejected by Cal_empz = " << Cal_empz << endl;
			}

			Int_t nVertTracks = 0;
			for(Int_t ii = 0;ii < Trk_ntracks;ii++)
			{
				if(Trk_prim_vtx[ii] != 1) continue;
				TVector3 tr(Trk_px[ii],Trk_py[ii],Trk_pz[ii]);
				if(tr.Mag() <= 0.25) continue;
				if(tr.Theta() >= 2.44) continue;
				nVertTracks++;
			}

			if(nVertTracks < 1) 
			{
				take_event = kFALSE;
				if(check_cuts)
					if (nodebugmode) cout << "rejected by nVertTracks = " << nVertTracks << endl;
			}

			Bool_t flt_trigger = kTRUE;
			if((Fltw[0] & (1 << 27)) == 0 &&
					(Fltw[0] & (1 << 29)) == 0 &&
					(Fltw[1] & (1 << 3)) == 0 &&
					(Fltw[1] & (1 << 6)) == 0 &&
					(Fltw[1] & (1 << 7)) == 0 &&
					(Fltw[1] & (1 << 8)) == 0 &&
					(Fltw[1] & (1 << 10)) == 0 &&
					(Fltw[1] & (1 << 11)) == 0 &&
					(Fltw[1] & (1 << 13)) == 0 &&
					(Fltw[1] & (1 << 14)) == 0 )
				flt_trigger = kFALSE;

			Bool_t slt_trigger = kTRUE;
			if((Sltw[5] & (1 << 12)) == 0 &&
					(Sltw[5] & (1 << 13)) == 0 &&
					(Sltw[5] & (1 << 14)) == 0 &&
					(Sltw[5] & (1 << 0)) == 0 &&
					(Sltw[5] & (1 << 6)) == 0 )
				slt_trigger = kFALSE;

			Bool_t tlt_trigger = kTRUE;
			if(period == "0405e" || period == "04p") {
				if((Tltw[3] & (1 << 2)) == 0 &&
						(Tltw[2] & (1 << 1)) == 0 &&
						(Tltw[2] & (1 << 8)) == 0 &&
						(Tltw[13] & (1 << 0)) == 0)
					tlt_trigger = kFALSE;
			} else
				if(period == "0607p" || period == "06e") {
					if((Tltw[3] & (1 << 2)) == 0 &&
							(Tltw[2] & (1 << 1)) == 0 &&
							(Tltw[2] & (1 << 8)) == 0 &&
							(Tltw[13] & (1 << 0)) == 0)
						tlt_trigger = kFALSE;
				}

			Bool_t spp01trigger = kTRUE;
			if((Tltw[2] & (1 << 0)) == 0)
			{
				spp01trigger = kFALSE;
			}

			Bool_t spp02trigger = kTRUE;
			if((Tltw[2] & (1 << 1)) == 0)
			{
				spp02trigger = kFALSE;
			}

			Bool_t spp09trigger = kTRUE;
			if((Tltw[2] & (1 << 8)) == 0)
			{
				spp09trigger = kFALSE;
			}
			Bool_t spp_trigger;
			//      if (nodebugmode) cout << Runnr << " " << Eventnr << " " << Bool_t(Tltw[2] & (1 << 8)) << " " << Bool_t(Tltw[2] & 512) << endl;
			if(period == "0405e" || period == "04p")
				spp_trigger = spp02trigger;  ///WARNING !!! MUST be 02!
			else
				if(period == "06e" || period == "0607p")
					spp_trigger = spp09trigger; ///WARNING !!! MUST be 09!

			//      if(mc_type == "mc_prph")
			//  spp_trigger = spp02trigger;  ///WARNING !!! MUST be 02!

			//
			//trigger efficiency study
			//

			//      if(!(flt_trigger && slt_trigger && tlt_trigger)) { //warning
			if(!spp_trigger) 
			{
				take_event_trig = kFALSE;
				if(check_cuts)
					if (nodebugmode) cout << "rejected by trigger condition " << endl;
			}


			//      if (nodebugmode) cout << "dis sel: " << Runnr << " " << Eventnr << " " << Siq2el[0] << " " << Zvtx << " " << Cal_empz << " " << Sith[0] << " " 
			//     << Sipos[0][0] << " " << Sipos[0][1] << " " << spp02trigger << endl;
			TLorentzVector v_electron; 
			Int_t electron_number = -1;
			max_et_candidate_number = -1;
			Double_t dr_elec_min = 999.;
			Double_t de_elec_min = 999.;
			Double_t n_close_tracks = 0.;
			max_et_candidate_number = -1;
			candidate_jet_number = -1;
			radiated_candidate_number = -1;
			max_et_candidate = -999.;
			max_et_candidate_uncorr = -999.;
			jet_energy_frac = 0.;
			cell_energy_frac = 0.;
			Double_t pt_of_event = 0.;
			Double_t px_of_event = 0.;
			Double_t py_of_event = 0.;
			Double_t pz_of_event = 0.;
			Double_t e_of_event = 0.;
			Double_t et_of_event = 0.;
			Double_t e_cal_event = 0.;
			Double_t e_had_event = 0.;
			Double_t e_emc_event = 0.;
			Double_t pt_sqrt_et;

			if(!take_event_trig) take_event = kFALSE;

			if(take_event)
			{
				//
				// check whether electron excluded from zufos
				//    
				v_electron.SetPtEtaPhiE(Sipt[sinistra_electron_number], \
					-TMath::Log(TMath::Tan(Sith[sinistra_electron_number]/2.)), \
					Siph[sinistra_electron_number], \
					Siecorr[sinistra_electron_number][2] * systElE);
				for(Int_t zloop = 0; zloop < Nzufos; zloop++)
				{
					hist.dis_zufo_type->Fill(Tufo[zloop][0], wtx);
					e_cal_event += Zufoecal[zloop];
					e_had_event += Zufoecal[zloop] - Zufoeemc[zloop];
					e_emc_event += Zufoeemc[zloop];
					pt_of_event += TMath::Sqrt(Zufo[zloop][0]*Zufo[zloop][0] + Zufo[zloop][1]*Zufo[zloop][1]);
					px_of_event += Zufo[zloop][0];
					py_of_event += Zufo[zloop][1];
					pz_of_event += Zufo[zloop][2];
					e_of_event += Zufo[zloop][3];
					myKzufodeltaz[zloop] = Kzufodeltaz[zloop]/5.45;
					TLorentzVector v(Zufo[zloop][0], Zufo[zloop][1], Zufo[zloop][2], Zufo[zloop][3]);
					Double_t et = v.Et();
					et_of_event += et;
					Double_t dr = v.DeltaR(v_electron);
					if(v.E() > 5. && dr < dr_elec_min)
					{
						dr_elec_min = dr;
						de_elec_min = v.E() - v_electron.E();
						if(dr < 0.5)
							electron_number = zloop;
					}
					if(check_cuts)
						if (nodebugmode) cout << "electron found: zufo # " << electron_number << endl;
					if(dr < 0.2)
						n_close_tracks++;
				}
				if(electron_number < 0) 
				{
					take_event = kFALSE;
					if(check_cuts) 
						if (nodebugmode) cout << "event rejected because was not found zufo that is close to sinistra electron" << endl;
				}
				if(check_cuts) if (nodebugmode) cout << "Filling histograms" << endl;
				//
				// inclusive DIS histograms
				//
				hist.dis_Q2_x->Fill(Siq2el[0], Sixel[0], wtx);
				hist.dis_Q2->Fill(Siq2el[0], wtx);
				hist.dis_Q2_el->Fill(Siq2el[0], wtx);
				hist.dis_Q2_da->Fill(Siq2da[0], wtx);
				hist.dis_Q2_da_cell->Fill(Siq2da_cell[0], wtx);
				hist.dis_Q2_jb->Fill(Siq2jb[0], wtx);
				hist.dis_Q2_jb_cell->Fill(Siq2jb_cell[0], wtx);
				hist.dis_px_event->Fill(px_of_event, wtx);
				hist.dis_py_event->Fill(py_of_event, wtx);
				hist.dis_pz_event->Fill(pz_of_event, wtx);
				hist.dis_pt_event->Fill(pt_of_event, wtx);
				hist.dis_e_event->Fill(e_of_event, wtx);
				hist.dis_et_event->Fill(et_of_event, wtx);
				hist.dis_n_zufos->Fill(Nzufos, wtx);
				hist.dis_emc->Fill(e_emc_event, wtx);
				hist.dis_had->Fill(e_had_event, wtx);
				hist.dis_cal->Fill(e_cal_event, wtx);
				hist.dis_had_tot_ratio->Fill(e_had_event/e_cal_event, wtx);
				//
				//x_gamma variable
				//
				hist.dis_siyjb->Fill(Siyjb[0], wtx);
				hist.dis_siyjb_cell->Fill(Siyjb_cell[0], wtx);
				Empz = 0.;
				for(Int_t zloop=0; zloop<Nzufos; zloop++)
				{
					if(zloop != electron_number)
						Empz += Zufo[zloop][3] - Zufo[zloop][2];
				}   
				yjb = Empz / (2. * E_e);
				hist.dis_handmade_yjb->Fill(yjb, wtx);
				hist.dis_elec_zufo_dr_min->Fill(dr_elec_min, wtx);
				hist.dis_elec_zufo_de_min->Fill(de_elec_min, wtx);
				hist.dis_zufos_near_electron->Fill(n_close_tracks, wtx);
				hist.dis_zvtx->Fill(Zvtx, wtx);
				hist.dis_n_vtx_tracks->Fill(nVertTracks, wtx);
				hist.dis_cal_empz->Fill(Cal_empz, wtx);
				hist.dis_zufo_empz->Fill(Empz, wtx);
				pt_sqrt_et = pt_of_event/TMath::Sqrt(et_of_event);
				hist.dis_pt_sqrtet->Fill(pt_sqrt_et, wtx);
				hist.dis_x_el->Fill(Sixel[0], wtx);
				hist.dis_x_el_log->Fill(Sixel[0], wtx);
				hist.dis_y_el->Fill(Siyel[0], wtx);
				hist.dis_electron_e->Fill(Siecorr[0][2] * systElE, wtx);
				hist.dis_electron_theta->Fill(Sith[0]*180.0/TMath::Pi(), wtx);
				hist.dis_electron_probability->Fill(Siprob[0], wtx);
				//printout interesting events
				if(print_interesting_events) 
				{
					if(pt_sqrt_et > 10.) {
						if (nodebugmode) cout << endl;
						if (nodebugmode) cout << "============ INTERESTING EVENT ================" << endl;
						if (nodebugmode) cout << "========= " << Runnr << " " << Eventnr << " ================" << endl;
						if (nodebugmode) cout << " seems to cosmic: pt_sqrt_et = " << pt_sqrt_et << endl;
						if (nodebugmode) cout << "===============================================" << endl << endl;      
					}
					if(pz_of_event > 500.) {
						if (nodebugmode) cout << endl;
						if (nodebugmode) cout << "============ INTERESTING EVENT ================" << endl;
						if (nodebugmode) cout << "========= " << Runnr << " " << Eventnr << " ================" << endl;
						if (nodebugmode) cout << " proton fucked up: pz_of_event = " << pz_of_event << endl;
						if (nodebugmode) cout << "===============================================" << endl << endl;      
					}
				}
				//    if(check_cuts) if (nodebugmode) cout << "Filling histograms" << endl;
			}
			if(check_cuts) if (nodebugmode) cout << "here_is_prph = " << here_is_prph << ", take_event = " << take_event << endl;

		
			//    
			// if this is background Monte Carlo, found radiated photon (if exists)
			//
			Int_t index_true_rad_photon = -1;

			if(!Data) 
			{
				for(Int_t ploop=0; ploop < Photn; ploop++)
				{
					if(Photid[ploop] == 5)
					{
						index_true_rad_photon = ploop;
						//        if (nodebugmode) cout << "true rad photon found: " << index_true_rad_photon << endl;
						break;
					}
				}
			}

		
			if(use_ktjetb_prph)
			{
				if(check_cuts)
					if (nodebugmode) cout << "send to prpktjetb " << index_true_rad_photon << endl;
				if(SelectPrPhKtJetB(index_true_rad_photon))
					here_is_prph = kTRUE;
			}
			if(check_cuts) if (nodebugmode) cout << "here_is_prph = " << here_is_prph << ", take_event = " << take_event << endl;
			//      if(use_ktjetb_prph && !here_is_prph)
			//  		take_event = kFALSE;
			if(check_cuts) if (nodebugmode) cout << "here_is_prph = " << here_is_prph << ", take_event = " << take_event << endl;

					
			if(take_event)
			{
				vector<KtLorentzVector> input_vec;
				vector<Int_t> input_vec_to_zufos;
				for(Int_t zloop=0; zloop<Nzufos; zloop++)
				{
					if(electron_number > -1 && zloop == electron_number)
					{
						if(check_cuts)
							if (nodebugmode) cout << "rejecting zufo number " << electron_number << " with e = " << Zufo[zloop][3] << " because it is most probably electron " << endl;
						continue;
					}
					if(here_is_prph && zloop == max_et_candidate_number) 
					{
						index_phot_vector = input_vec_to_zufos.size();
						//    continue;
					}
					//        if (nodebugmode) cout << "particle " << zloop << " " << input_vec.size() << " " << Zufo[zloop][3] << endl;
					KtLorentzVector p(Zufo[zloop][0], Zufo[zloop][1], Zufo[zloop][2], Zufo[zloop][3]);
					input_vec.push_back(p);
					input_vec_to_zufos.push_back(zloop);

				}
				if (check_cuts) if (nodebugmode) cout << Nzufos << " " << input_vec.size() << " hadrons added" << endl;
				int type  = 3; // pe
				int angle = 2; // deltaR
				int recom = 1; // e
				double rparameter = 1.0;	
				// Construct the KtEvent object 
				KtEvent ev(input_vec,type,angle,recom,rparameter);
				// Retrieve the final state jets from KtEvent sorted by Et
				vector<KtLorentzVector> jets = ev.getJetsEt();
				// Retrieve the final state jets from KtEvent sorted by Et
				vector<KtLorentzVector> jets_copy = ev.getJetsEt();
				Int_t n_jets = 0;
				Bool_t take_jet_temp = kTRUE;
				for(Int_t jloop=0; jloop<jets.size(); jloop++) 
				{
					take_jet_temp = kTRUE;
					if(jets[jloop].eta() < -1.5 || jets[jloop].eta() > 1.8)
						take_jet_temp = kFALSE;
					if(jet_en_corr_1stana(jets[jloop].eta(), jets[jloop].et(), period, mc_type) > 2.5)
						take_jet_temp = kFALSE;

					if(take_jet_temp)
						n_jets++;
				}
				//if (nodebugmode) cout<<"!    njets = "<< njets <<endl;
				//    if (nodebugmode) cout << "Eventnr = " << Eventnr << ", n_jets = " << n_jets << endl;
									
				if(!hist.ijet_njets) cout << "This pointer is nonzero" << endl;

				hist.ijet_njets->Fill(n_jets, wtx);
				

				/*
					if (nodebugmode) cout << "======================================================" << endl;
					if (nodebugmode) cout << "before systematic shift:" << endl;
				    for(Int_t jloop=0; jloop < jets.size(); jloop++)
				      if (nodebugmode) cout << jets[jloop].px() << " " << jets[jloop].py() << " " << jets[jloop].pz() << " " << jets[jloop].e() << " " << jets[jloop].et() <<endl;
				*/
				//warning: systematic errors due to jet energy uncertainty
				/*    
					for(Int_t jloop=0; jloop < jets.size(); jloop++) 
				      { 
				        Double_t px = jets[jloop].px(); 
				        Double_t py = jets[jloop].py(); 
				        Double_t pz = jets[jloop].pz(); 
				        Double_t e = jets[jloop].e(); 
				        Double_t et = jets[jloop].et(); 
				        if(et < 10.) { 
				    px *= 0.9; 
				    py *= 0.9; 
				    pz *= 0.9; 
				    e *= 0.9; 
				        } else { 
				    px *= 0.97; 
				    py *= 0.97; 
				    pz *= 0.97; 
				    e *= 0.97; 
				        } 
				        KtLorentzVector vec(px, py, pz, e); 
				        jets[jloop] = vec; 
				      } 
				*/
				if (systJetE_lt10 != 1. || systJetE_gt10 != 1.)
				{
					cout<<"Starting upplying jet correction for systematic" <<endl;
                    for(Int_t jloop=0; jloop < jets.size(); jloop++) 
                    { 
                        Double_t px = jets[jloop].px(); 
                        Double_t py = jets[jloop].py(); 
                        Double_t pz = jets[jloop].pz(); 
                        Double_t e = jets[jloop].e(); 
                        Double_t et = jets[jloop].et(); 
                        if(et < 10.) 
                        { 
                            px *= systJetE_lt10; 
                            py *= systJetE_lt10; 
                            pz *= systJetE_lt10; 
                            e *= systJetE_lt10; 
                        } else 
                        { 
                            px *= systJetE_gt10; 
                            py *= systJetE_gt10; 
                            pz *= systJetE_gt10; 
                            e *= systJetE_gt10; 
                        }
                        KtLorentzVector vec(px, py, pz, e); 
                        jets[jloop] = vec;
                    }
                }	                
				//
				// find jet containing prompt photon from HepForge
				//
				if(use_ktjetb_prph)
				{
					Int_t candidate_jet_copy_number = -1;
					for(Int_t jloop=0; jloop < jets.size(); jloop++)
					{
						if(check_cuts) 
						{
							if (nodebugmode) cout << "jet " << jloop << ": et = " << jets[jloop].et() << ", eta = " << jets[jloop].eta() << endl;
							if (nodebugmode) cout << "max_et_cand (zufos) = "<< max_et_candidate_number << ", max_et_cand (input_vec) = " << input_vec_to_zufos[max_et_candidate_number] 
								<< ", nzufos = " << Nzufos << ", knzufos = " << Knzufos << ", input_vec.size() = " << input_vec_to_zufos.size() << " " << input_vec.size() 
								<< ", zufo_e = " << Zufo[max_et_candidate_number][3] << ", input vec e = " << input_vec[input_vec_to_zufos[max_et_candidate_number]].e() << " " << input_vec[input_vec_to_zufos[max_et_candidate_number]].et() << endl;
							if (nodebugmode) cout << "[][][].et = " << (input_vec[input_vec_to_zufos[max_et_candidate_number]]).et() << endl;
							if (nodebugmode) cout << "index_phot_vector = " << index_phot_vector << endl;
						}

						if( jets[jloop].contains(input_vec[index_phot_vector]) )
						{
							candidate_jet_number = jloop;	
							//break;						
						}
						if( jets_copy[jloop].contains(input_vec[index_phot_vector]) )
						{
							candidate_jet_copy_number = jloop;	
							//break;						
						}
					}
					if (nodebugmode) cout << "candidate_jet_number: " << candidate_jet_number <<" candidate_jet_copy_number: " << candidate_jet_copy_number << endl;
					/*if (candidate_jet_number != candidate_jet_copy_number)
						{
							cout<< "!!!EVENT entry:" << entry << "Runnr: "<< Runnr << endl;
							debugcontinue = kFALSE;
						}
					*/
						candidate_jet_number = candidate_jet_copy_number;
				}
				if (candidate_jet_number==-1)
					if (nodebugmode) cout<< "###############################candidate_jet_number not found###############################"<<endl;
				//
				// searching for second jet
				//
				Int_t max_et_accomp_jet_candidate_number = -1;
				Double_t max_et_accomp_jet = -999.;
				//    wtx *= etaph_reweighting(v_corr_prompt_photon->Eta()); //it is as function of background detector level (we do not need cross section for the BG) warning
				if(!Data && mc_type == "mc_bg_norad") {
					wtx *= etaph_reweighting(v_corr_prompt_photon->Eta(), mc_type) * systAcc - (systAcc - 1); //it is as function of background detector level (we do not need cross section for the BG)      
					wtx *= eph_reweighting(v_corr_prompt_photon->E(), mc_type) * systAcc - (systAcc - 1); //it is as function of background detector level (we do not need cross section for the BG)
					if (nodebugmode) cout << "eta = " << v_corr_prompt_photon->Eta() << ", wtx_eta = " << etaph_reweighting(v_corr_prompt_photon->Eta(), mc_type) << ", e = " << v_corr_prompt_photon->E() << "wtx_e = " << eph_reweighting(v_corr_prompt_photon->E(), mc_type) << endl;
				}
				if(wtx < 0) {cerr << "wtx = " << wtx << endl; exit(-1);}
				if(take_event && here_is_prph)
				{
					for(Int_t jloop = 0; jloop < jets.size(); jloop++)
					{
						if(check_cuts)
							if (nodebugmode) cout << "jet " << jloop << ": calling correction with parameters: " << jets[jloop].eta() 
								<< ", " << jets[jloop].et() << ", " << period << ", " << mc_type << endl;
						Double_t et_jet_corr = jet_en_corr_1stana(jets[jloop].eta(), jets[jloop].et(), period, mc_type);
						if(check_cuts)
							if (nodebugmode) cout << "jet " << jloop << " of " << jets.size() 
								<< ", eta = " << jets[jloop].eta() 
								<< ", et_uncorr = " << jets[jloop].et() << ", et_corr = " << et_jet_corr << endl;
						
						take_jet = kTRUE;
						if((jloop == candidate_jet_number)) 
						{
							take_jet = kFALSE;
							if(check_cuts)
								if (nodebugmode) cout << "jet with eta " << jets[jloop].eta() << " rejected because it is prompt photon jet " << endl;
						}
						if(et_jet_corr < ET_JET_CUT) 
						{
							take_jet = kFALSE;
							if(check_cuts)
								if (nodebugmode) cout << "jet with eta " << jets[jloop].eta() << " rejected by et_jet_corr = "<< et_jet_corr << endl;
						}
						if(jets[jloop].eta() < -1.5 || jets[jloop].eta() > 1.8) 
						{
							take_jet = kFALSE;
							if(check_cuts)
								if (nodebugmode) cout << "jet with eta " << jets[jloop].eta() << " rejected by jets[" << jloop << "].eta() = "<< jets[jloop].eta() << endl;
						}
						//      if(jloop == candidate_jet_number)
						//        take_jet = kFALSE;
						if(take_jet)
						{
							if(check_cuts)
								if (nodebugmode) cout << "jet selected " << jloop << ": " << jets[jloop].eta() << " " << jets[jloop].et() << endl;
							here_is_jet = kTRUE;
							// max_et_accomp_jet_candidate_number = jloop;
							if(et_jet_corr > max_et_accomp_jet)
							{
								max_et_accomp_jet = et_jet_corr;
								max_et_accomp_jet_candidate_number = jloop;
								Double_t Px = jets[jloop].px();
								Double_t Py = jets[jloop].py();
								Double_t Pz = jets[jloop].pz();
								Double_t E  = jets[jloop].e();
								v_accomp_uncorr_jet->SetPxPyPzE(Px, Py, Pz, E);
								Px = jet_en_corr_1stana(jets[jloop].eta(), jets[jloop].px(), period, mc_type);
								Py = jet_en_corr_1stana(jets[jloop].eta(), jets[jloop].py(), period, mc_type);
								Pz = jet_en_corr_1stana(jets[jloop].eta(), jets[jloop].pz(), period, mc_type);
								E = jet_en_corr_1stana(jets[jloop].eta(), jets[jloop].e(), period, mc_type);
								v_accomp_corr_jet->SetPxPyPzE(Px, Py, Pz, E);
							}

							if(study_jets) 
							{
								Double_t n_subzufos = 0;
								for( Int_t zloop = 0; zloop < input_vec.size(); zloop++ )
								{
									if(jets[max_et_accomp_jet_candidate_number].contains(input_vec[zloop]) )
									{
										n_subzufos++;
									}
								}
								hist.h2d_jet_npart_et->Fill(n_subzufos, et_jet_corr, wtx);
							}//if study_jets

						}//if take_jet
					}// for jloop over jets
				}/// if take_event && here_is_prph
				//
				// inclusive prompt photon histograms
				//
				if(take_event && here_is_prph) {
					hist.incl_phot_fmax->Fill(glob_fmax, wtx);
					hist.incl_phot_deltaz->Fill(glob_deltaz, wtx);
					hist.incl_phot_elphot_dphi->Fill(delta_phi(v_corr_prompt_photon->Phi(), v_electron.Phi()), wtx);
					hist.incl_phot_elphot_deta->Fill(v_corr_prompt_photon->Eta() - v_electron.Eta(), wtx);
					hist.incl_phot_phi->Fill(v_corr_prompt_photon->Phi(), wtx);
					hist.incl_phot_eta->Fill(v_corr_prompt_photon->Eta(), wtx);
				}

				//
				// prompt photon + jet
				//
				Double_t hardest_jet_et_corr = 0;
				Double_t hardest_jet_et = 0;
				Double_t hardest_jet_eta = -999.;
				Double_t hardest_jet_phi = -999.;
				if(here_is_jet && !inclusive_prph_analysis) {
					hardest_jet_et = jets[max_et_accomp_jet_candidate_number].et();
					hardest_jet_eta = jets[max_et_accomp_jet_candidate_number].eta();
					hardest_jet_phi = jets[max_et_accomp_jet_candidate_number].phi();
					hardest_jet_et_corr = jet_en_corr_1stana(hardest_jet_eta,
							hardest_jet_et, period, mc_type);
				}
				if(inclusive_prph_analysis)
					here_is_jet = kTRUE;


				if(check_cuts) {
					if (nodebugmode) cout << "take_event = " << take_event << ", here_is_jet = " << here_is_jet << ", here_is_prph = " << here_is_prph << endl;
				}

				if(take_event && here_is_jet && here_is_prph) 
				{

					//
					// x_gamma
					//
					Double_t x_pomeron = v_uncorr_prompt_photon->E() + v_uncorr_prompt_photon->Pz();
					Double_t x_pomeron_exp = v_uncorr_prompt_photon->Et() * TMath::Exp(  v_uncorr_prompt_photon->Eta());
					x_gamma = v_uncorr_prompt_photon->E() - v_uncorr_prompt_photon->Pz();
					x_gamma_exp = v_uncorr_prompt_photon->Et() * TMath::Exp( -1 * v_uncorr_prompt_photon->Eta());
					Double_t x_gamma_dummy = x_gamma;
					//        if (nodebugmode) cout << "--> " << Runnr << " " << Eventnr << " " << x_gamma << " " ;
					if (nodebugmode) cout << "v_uncorr_prompt_photon->E() : " << v_uncorr_prompt_photon->E() << endl;
					if (nodebugmode) cout << "v_uncorr_prompt_photon->Pz() : " << v_uncorr_prompt_photon->Pz() << endl;
					if (nodebugmode) cout << "E_e : " << E_e << endl;
					if (nodebugmode) cout << "yjb : " << yjb << endl;
					if (nodebugmode) cout << "v_uncorr_prompt_photon->E() - v_uncorr_prompt_photon->Pz(): " << Runnr << " " << Eventnr << " " << x_gamma<<endl;
					Double_t empz_jet = jets[max_et_accomp_jet_candidate_number].e() - jets[max_et_accomp_jet_candidate_number].pz();
					Double_t empz_particles_inside_jet = 0.;
					Double_t empz_jet_plus = jets[max_et_accomp_jet_candidate_number].e() + jets[max_et_accomp_jet_candidate_number].pz();
					Double_t empz_particles_inside_jet_plus = 0.;
					if (nodebugmode) cout<<"JETS[]"<<endl;
					if (nodebugmode) cout<<"!    jets[max_et_accomp_jet_candidate_number].getNConstituents() = "<< jets[max_et_accomp_jet_candidate_number].getNConstituents()<<endl;
					if (nodebugmode) cout<<"!    max_et_accomp_jet_candidate_number = "<< max_et_accomp_jet_candidate_number <<endl;
					for( Int_t i =0; i < jets[max_et_accomp_jet_candidate_number].getNConstituents(); i++)
					{
						if (nodebugmode) 
							cout<<"   i : "<< jets[max_et_accomp_jet_candidate_number].getConstituents()[i]<< "  "<< *jets[max_et_accomp_jet_candidate_number].getConstituents()[i]<< endl;
					}

					//vector<KtLorentzVector*>::const_iterator itr = jets[max_et_accomp_jet_candidate_number].begin();
					/*for (; itr != jets[max_et_accomp_jet_candidate_number].end() ; ++itr) 
					  {
					  if (nodebugmode) cout<< **itr <<endl;
					  }
					  */
					if (nodebugmode) cout<<" input_vec.size() = "<<input_vec.size()<< "  jets[max_et_accomp_jet_candidate_number] = "<< jets[max_et_accomp_jet_candidate_number]<< endl;
					/*
					for(Int_t zloop=0; zloop < input_vec.size(); zloop++)
					{
						if (zloop == 1 || zloop == 4 || zloop == 27 || zloop == 30 || zloop == 33)
						{
							if (!nodebugmode) cout<<" test i = "<<zloop<< " "<< input_vec[zloop] << endl;
						}
						if( jets[max_et_accomp_jet_candidate_number].contains(input_vec[zloop]) != jets_copy[max_et_accomp_jet_candidate_number].contains(input_vec[zloop]) )
							cout<< "Affection"<<endl;
						else
							cout<< "not Affection"<<endl;
						if( jets_copy[max_et_accomp_jet_candidate_number].contains(input_vec[zloop]) )//if zufo in the jet of max_et
						{

							if (!nodebugmode) cout<<" i = "<<zloop<< " "<< &input_vec[zloop] << input_vec[zloop] << endl;
							x_gamma += ( input_vec[zloop].e() - input_vec[zloop].pz() )*systJetE_gt10;
							x_pomeron += input_vec[zloop].e() + input_vec[zloop].pz();
							empz_particles_inside_jet += input_vec[zloop].e() - input_vec[zloop].pz();
							empz_particles_inside_jet_plus += input_vec[zloop].e() + input_vec[zloop].pz();
						}
					}
					*/
					//x_gamma_dummy += jets[max_et_accomp_jet_candidate_number].e() - jets[max_et_accomp_jet_candidate_number].pz();
					//x_gamma_dummy /= (2. * E_e * yjb);
					//if (!nodebugmode) cout << "xgamma: " << " " << x_gamma << " ";
					//        if (!nodebugmode) cout << x_gamma << " " ;
					x_gamma_exp += jets[max_et_accomp_jet_candidate_number].et() * TMath::Exp( -1 * jets[max_et_accomp_jet_candidate_number].eta());
					x_pomeron_exp += jets[max_et_accomp_jet_candidate_number].et() * TMath::Exp(  jets[max_et_accomp_jet_candidate_number].eta());
					x_gamma += jets[max_et_accomp_jet_candidate_number].e() - jets[max_et_accomp_jet_candidate_number].pz();
					x_gamma /= (2. * E_e * yjb);
					x_gamma_exp /= (2. * E_e * yjb);
					x_pomeron += jets[max_et_accomp_jet_candidate_number].e() + jets[max_et_accomp_jet_candidate_number].pz();
					x_pomeron /= (2. * E_p);
					x_pomeron_exp /= (2. * E_p);
					if (!nodebugmode && (x_pomeron>=1 || x_pomeron_exp>=1)) cout << "x_pomeron: " << x_pomeron << " x_pomeron_exp: " << x_pomeron_exp <<endl;
					if (nodebugmode) cout << "empz_jet = " << empz_jet << ", empz_particles_inside_jet = " << empz_particles_inside_jet << endl;
					//    if(x_gamma > 0.75)
					//      take_event = kFALSE;
					//breakindex = kTRUE;
					//debugcontinue = kFALSE;

					if(check_cuts) if (nodebugmode) cout << "event accepted" << endl;
					hist.eta_gamma_tef[1]->Fill(v_corr_prompt_photon->Eta(), wtx);
					hist.e_jet_tef[1]->Fill(hardest_jet_et_corr, wtx);
					hist.q2_tef[1]->Fill(Siq2el[0], wtx);
					hist.e_electron_tef[1]->Fill(Siecorr[0][2] * systElE, wtx);
					hist.e_gamma_tef[1]->Fill(v_corr_prompt_photon->Et(), wtx);
					hist.theta_electron_tef[1]->Fill(Sith[0], wtx);

					if(take_event_trig)
					{
						event_list->Enter(entry);
						hist.eta_gamma_tef[0]->Fill(v_corr_prompt_photon->Eta(), wtx);
						hist.e_jet_tef[0]->Fill(hardest_jet_et_corr, wtx);
						hist.q2_tef[0]->Fill(Siq2el[0], wtx);
						hist.e_electron_tef[0]->Fill(Siecorr[0][2] * systElE, wtx);
						hist.e_gamma_tef[0]->Fill(v_corr_prompt_photon->Et(), wtx);
						hist.theta_electron_tef[0]->Fill(Sith[0], wtx);

						fill_trigger_bits(hist.dstw, Dstw);
						fill_trigger_bits_general(hist.fltw, Fltw, 2);
						fill_trigger_bits_general(hist.sltw, Sltw, 6);
						fill_trigger_bits_general(hist.tltw, Tltw, 15);

						//  -> Fill photon with jets
						hist.fmax->Fill(glob_fmax, wtx);
						hist.deltaz->Fill(glob_deltaz, wtx);
						//cout << hist.deltaz->GetBinContent(1)<< endl;
						/*hist_mc_rad[0]->GetBinContent(ii), \
                            hist_mc_rad[0]->GetBinError(ii), "=", sqrt(hist_mc_rad[0]->GetSumw2()->GetAt(ii)), "!=", \
                            sqrt(hist_mc_rad[0]->GetBinContent(ii)), hist_mc_rad[0]->GetBinContent(ii)*/
						//if (entry > 10000) debugcontinue = kFALSE;
						
						hist.fmax_deltaz->Fill(glob_fmax, glob_deltaz, wtx);
						hist.prph_energy->Fill(v_corr_prompt_photon->Et(), wtx);
						hist.prph_eta->Fill(v_corr_prompt_photon->Eta(), wtx);
						hist.prph_phi->Fill(v_corr_prompt_photon->Phi(), wtx);
						hist.prph_jet_energy_frac->Fill(jet_energy_frac, wtx);
						hist.prph_cell_energy_frac->Fill(cell_energy_frac, wtx);

						//  -> Fill Cross_section_histograms
						hist.det_cross_et->Fill(v_corr_prompt_photon->Et(), wtx);
						hist.det_cross_eta->Fill(v_corr_prompt_photon->Eta(), wtx);
						hist.det_cross_Q2->Fill(Siq2el[0], wtx);
						hist.det_cross_x->Fill(Sixel[0], wtx);
						hist.det_cross_et_jet->Fill(hardest_jet_et_corr, wtx);
						hist.det_cross_eta_jet->Fill(hardest_jet_eta, wtx);
						Double_t temp_dphi = delta_phi(hardest_jet_phi, v_corr_prompt_photon->Phi()) * 180.0/TMath::Pi();
						Double_t temp_deta = hardest_jet_eta - v_corr_prompt_photon->Eta();
						Double_t temp_dphi_e_ph = delta_phi(Siph[sinistra_electron_number], v_corr_prompt_photon->Phi()) * 180.0/TMath::Pi();
						Double_t temp_deta_e_ph = -TMath::Log(TMath::Tan(Sith[sinistra_electron_number]/2.)) - v_corr_prompt_photon->Eta();
						hist.det_cross_xgamma->Fill(x_gamma, wtx); 
						hist.det_cross_xp->Fill(x_pomeron, wtx); 
						hist.det_cross_dphi->Fill( temp_dphi, wtx);
						hist.det_cross_deta->Fill( temp_deta, wtx);
						hist.det_cross_dphi_e_ph->Fill(temp_dphi_e_ph, wtx); 
						hist.det_cross_deta_e_ph->Fill(temp_deta_e_ph, wtx); 


						//  -> Fill Cross_section_histograms
						hist.prof_det_cross_et->Fill(v_corr_prompt_photon->Et(), v_corr_prompt_photon->Et(), wtx);
						hist.prof_det_cross_eta->Fill(v_corr_prompt_photon->Eta(), v_corr_prompt_photon->Eta(), wtx);
						hist.prof_det_cross_Q2->Fill(Siq2el[0], Siq2el[0], wtx);
						hist.prof_det_cross_x->Fill(Sixel[0], Sixel[0], wtx);
						hist.prof_det_cross_et_jet->Fill(hardest_jet_et_corr, hardest_jet_et_corr, wtx);
						hist.prof_det_cross_eta_jet->Fill(hardest_jet_eta, hardest_jet_eta, wtx);
						hist.prof_det_cross_xgamma->Fill(x_gamma, x_gamma, wtx); 
						hist.prof_det_cross_xp->Fill(x_pomeron, x_pomeron, wtx); 
						hist.prof_det_cross_dphi->Fill(temp_dphi, temp_dphi, wtx);
						hist.prof_det_cross_deta->Fill(temp_deta, temp_deta, wtx);
						hist.prof_det_cross_dphi_e_ph->Fill(temp_dphi_e_ph, temp_dphi_e_ph, wtx); 
						hist.prof_det_cross_deta_e_ph->Fill(temp_deta_e_ph, temp_deta_e_ph, wtx); 

						det_cross_sec_bin_et = hist.det_cross_et->FindBin(v_corr_prompt_photon->Et());
						det_cross_sec_bin_eta = hist.det_cross_eta->FindBin(v_corr_prompt_photon->Eta());
						det_cross_sec_bin_q2 = hist.det_cross_Q2->FindBin(Siq2el[0]);
						det_cross_sec_bin_x = hist.det_cross_x->FindBin(Sixel[0]);
						det_cross_sec_bin_et_jet = hist.det_cross_et_jet->FindBin(hardest_jet_et_corr);
						det_cross_sec_bin_eta_jet = hist.det_cross_eta_jet->FindBin(hardest_jet_eta);
						det_cross_sec_bin_xgamma = hist.det_cross_xgamma->FindBin(x_gamma); 
						det_cross_sec_bin_xp = hist.det_cross_xp->FindBin(x_pomeron); 
						det_cross_sec_bin_dphi = hist.det_cross_dphi->FindBin(temp_dphi);
						det_cross_sec_bin_deta = hist.det_cross_deta->FindBin(temp_deta);
						det_cross_sec_bin_dphi_e_ph = hist.det_cross_dphi_e_ph->FindBin(temp_dphi_e_ph); 
						det_cross_sec_bin_deta_e_ph = hist.det_cross_deta_e_ph->FindBin(temp_deta_e_ph); 

						for(Int_t i = 0; i<number_deta_e_ph_bins; i++)
						{
							if(temp_deta_e_ph > deta_e_ph_bin[i] && temp_deta_e_ph < deta_e_ph_bin[i+1]) 
							{
								hist.fmax_deta_e_ph[i]->Fill(glob_fmax, wtx);
								hist.deltaz_deta_e_ph[i]->Fill(glob_deltaz, wtx);
							}
						}
						for(Int_t i = 0; i<number_dphi_e_ph_bins; i++)
						{
							if(temp_dphi_e_ph > dphi_e_ph_bin[i] && temp_dphi_e_ph < dphi_e_ph_bin[i+1]) 
							{
								hist.fmax_dphi_e_ph[i]->Fill(glob_fmax, wtx);
								hist.deltaz_dphi_e_ph[i]->Fill(glob_deltaz, wtx);
							}
						}
						for(Int_t i = 0; i<number_deta_bins; i++)
						{
							if(temp_deta > deta_bin[i] && temp_deta < deta_bin[i+1]) 
							{
								hist.fmax_deta[i]->Fill(glob_fmax, wtx);
								hist.deltaz_deta[i]->Fill(glob_deltaz, wtx);
							}
						}
						for(Int_t i = 0; i<number_dphi_bins; i++)
						{
							if(temp_dphi > dphi_bin[i] && temp_dphi < dphi_bin[i+1]) 
							{
								hist.fmax_dphi[i]->Fill(glob_fmax, wtx);
								hist.deltaz_dphi[i]->Fill(glob_deltaz, wtx);
							}
						}
						for(Int_t i = 0; i<number_xp_bins; i++)
						{
							if(x_pomeron > xp_bin[i] && x_pomeron < xp_bin[i+1]) 
							{
								hist.fmax_xp[i]->Fill(glob_fmax, wtx);
								hist.deltaz_xp[i]->Fill(glob_deltaz, wtx);
							}
						}
						Int_t flag = 0;
						for(Int_t i = 0; i<number_xgamma_bins; i++)
						{
							if(x_gamma > xgamma_bin[i] && x_gamma < xgamma_bin[i+1]) 
							{
								hist.fmax_xgamma[i]->Fill(glob_fmax, wtx);
								hist.deltaz_xgamma[i]->Fill(glob_deltaz, wtx);
								flag++;
							}
						}
						if (flag==0) missed++;
						for(Int_t i=0; i<number_etbins; i++)
						{
							if(v_corr_prompt_photon->Et() > et_bin[i] && v_corr_prompt_photon->Et() < et_bin[i+1]) {
								hist.fmax_et[i]->Fill(glob_fmax, wtx);
								hist.deltaz_et[i]->Fill(glob_deltaz, wtx);
							}
						}
						for(Int_t i=0; i<number_Q2bins; i++)
						{
							if(Siq2el[0] > Q2_bin[i] && Siq2el[0] < Q2_bin[i+1]) {
								hist.fmax_q2[i]->Fill(glob_fmax, wtx);
								hist.deltaz_q2[i]->Fill(glob_deltaz, wtx);
							}
						}
						for(Int_t i=0; i<number_xbins; i++)
						{
							if(Sixel[0] > x_bin[i] && Sixel[0] < x_bin[i+1]) {
								hist.fmax_x[i]->Fill(glob_fmax, wtx);
								hist.deltaz_x[i]->Fill(glob_deltaz, wtx);
							}
						}
						for(Int_t i=0; i<number_etabins; i++)
						{
							if(v_corr_prompt_photon->Eta() > eta_bin_crosssec[i] && v_corr_prompt_photon->Eta() < eta_bin_crosssec[i+1]) {
								hist.fmax_eta[i]->Fill(glob_fmax, wtx);
								hist.deltaz_eta[i]->Fill(glob_deltaz, wtx);
							}
						}
						for(Int_t i=0; i<number_et_jetbins; i++)
						{
							if(hardest_jet_et_corr > et_jet_bin[i] && 
									hardest_jet_et_corr < et_jet_bin[i+1]) 
							{
								hist.fmax_et_jet[i]->Fill(glob_fmax, wtx);//  -> Fill Cross_section_histograms
								hist.deltaz_et_jet[i]->Fill(glob_deltaz, wtx);//  -> Fill Cross_section_histograms
							}
						}
						for(Int_t i=0; i<number_eta_jetbins; i++)
						{
							if(hardest_jet_eta > eta_jet_bin[i] && 
									hardest_jet_eta < eta_jet_bin[i+1]) 
							{
								hist.fmax_eta_jet[i]->Fill(glob_fmax, wtx);//  -> Fill Cross_section_histograms
								hist.deltaz_eta_jet[i]->Fill(glob_deltaz, wtx);//  -> Fill Cross_section_histograms
							}
						}

						//if (nodebugmode) cout << "---->>>>" << selectedEventsCount << " " << Runnr << " " << Eventnr << endl;
						/*1*/if (nodebugmode) cout << selectedEventsCount+1 << " " << Runnr << " " << Eventnr << endl;
						/*2*/if (nodebugmode) cout << Siq2el[0] << "   " << Siecorr[0][2] * systElE << "   " << Sith[0]*180/TMath::Pi() << endl;
						/*3*/if (nodebugmode) cout << TMath::Abs(Sipos[0][0]) << "   " << Sipos[0][1] << "   " << Cal_empz << "   " << TMath::Abs(Zvtx) << endl;
						/*4*/if (nodebugmode) cout << max_et_candidate << " " << max_et_candidate_uncorr << "   " << v_corr_prompt_photon->Eta() 
							/*4*/ << "   " << v_uncorr_prompt_photon->E()/v_prompt_photon_jet->E()
							/*4*/     << "   " << v_uncorr_prompt_photon->Et()/v_prompt_photon_jet->Et() << "   " << v_corr_prompt_photon->E() << endl;
						/*5*/if (nodebugmode) cout << nVertTracks << "   " << cell_energy_frac
							<< "   " << 1 << "   " << glob_deltaz << endl;
						/*6*/if (nodebugmode) cout << glob_fmax << "   " << hardest_jet_eta << "   " 
							<< hardest_jet_et << "   " 
							<< hardest_jet_et_corr << 
							" " << spp02trigger << " " << spp09trigger << " " << wtx << endl << endl;
						//        if (nodebugmode) cout << "photon, jet: " << v_corr_prompt_photon->Phi() << " " << jets[max_et_accomp_jet_candidate_number].phi() << ", "
						//       << v_corr_prompt_photon->Eta() << " " << jets[max_et_accomp_jet_candidate_number].eta() << endl;

						hist.x_gamma->Fill(x_gamma, wtx);//  -> Fill photon with jets
						hist.x_gamma_exp->Fill(x_gamma_exp, wtx);
						hist.x_gamma_diff->Fill(x_gamma_exp - x_gamma);
						hist.x_pomeron->Fill(x_pomeron, wtx);
						hist.x_pomeron_exp->Fill(x_pomeron_exp, wtx);
						hist.x_pomeron_diff->Fill(x_pomeron_exp - x_pomeron);
						hist.x_gamma_unmarged->Fill(x_gamma, wtx);
						hist.x_pomeron_unmarged->Fill(x_pomeron, wtx);//  -> Fill photon with jets
						//
						// Sinistra candidates and photon candidate -> Fill photon with jets
						//
						Double_t photon_eta = v_corr_prompt_photon->Eta();
						Double_t photon_phi = v_corr_prompt_photon->Phi();
						Double_t min_sin_phot_dr = 999.;
						Int_t closest_sincand = -1;
						for(Int_t sloop=0; sloop<Sincand; sloop++)
						{
							Double_t dphi = delta_phi(photon_phi, Siph[sloop]);
							Double_t deta = photon_eta+TMath::Log(TMath::Tan(Sith[sloop]/2.));
							Double_t dr = TMath::Sqrt(dphi*dphi + deta*deta);
							hist.phjet_photon_sincand_dr[sloop]->Fill(dr, wtx);//  -> Fill photon with jets
							//      if (nodebugmode) cout << "sloop = " << sloop << ": " << dphi << " " << deta << " "  << dr << endl;
							if(dr < min_sin_phot_dr) 
							{

								min_sin_phot_dr = dr;
								closest_sincand = sloop;
							}
						}
						hist.phjet2d_photon_sincand_dr_nr->Fill((Double_t)closest_sincand, min_sin_phot_dr, wtx);//  -> Fill photon with jets
						//        if (nodebugmode) cout << Runnr << " " << Eventnr << " " << closest_sincand << " " << min_sin_phot_dr << endl;
						//
						//  Fill histograms -> Fill photon with jets
						//
						Double_t photon_jet_deta = hardest_jet_eta - v_corr_prompt_photon->Eta();  
						Double_t photon_jet_dphi = delta_phi(hardest_jet_phi, photon_phi);   

						Double_t photon_electron_dphi_true = delta_phi(Siph[sinistra_electron_number], photon_phi);
						Double_t photon_electron_deta_true = -TMath::Log(TMath::Tan(Sith[sinistra_electron_number]/2.)) - v_corr_prompt_photon->Eta();
						Double_t photon_electron_deta = -TMath::Log(TMath::Tan(Sith[0]/2.)) - v_corr_prompt_photon->Eta();
						Double_t photon_electron_dphi = delta_phi(Siph[0], photon_phi);

						Double_t jet_electron_deta = -TMath::Log(TMath::Tan(Sith[0]/2.)) - hardest_jet_eta;
						Double_t jet_electron_dphi = delta_phi(hardest_jet_phi, Siph[0]);

						hist.comp_jet_e->Fill(max_et_accomp_jet, wtx);
						hist.comp_prph_e->Fill(max_et_candidate, wtx);
						hist.comp_Q2->Fill(Siq2el[0], wtx);
						hist.comp_x->Fill(Sixel[0], wtx);
						hist.comp_y->Fill(Siyel[0], wtx);
						hist.comp_y_da->Fill(Siyda[0], wtx);
						hist.comp_y_jb->Fill(Siyjb[0], wtx);
						hist.comp_y_norew->Fill(Siyel[0]);
						hist.comp_y_da_norew->Fill(Siyda[0]);
						hist.comp_y_jb_norew->Fill(Siyjb[0]);

						if(Sixel[0]*Siyel[0] != 0)
							hist.comp_s->Fill(Siq2el[0]/(Sixel[0] * Siyel[0]));
						hist.phjet_electron_e->Fill(Siecorr[0][2] * systElE, wtx);
						/*        Int_t MCflag = 0;
							  Float_t m_Siecorr[4][3];
							  if(Runnr == 1) MCflag = 1;
							  m_Siecorr[0][2] = BCR_CalibTools::ecorr_newscheme(Sicalene[0], Six0[0],
							  Sicalpos[0][0],Sicalpos[0][1],
							  MCflag);
							  hist.phjet_electron_e_corr_burkard->Fill(m_Siecorr[0][2], wtx);*/
						hist.phjet_electron_theta->Fill(Sith[0]*180.0/TMath::Pi(), wtx);
						hist.phjet_electron_phi->Fill(Siph[0], wtx);
						hist.phjet_electron_probability->Fill(Siprob[0], wtx);
						hist.phjet_dphi_deta->Fill(photon_jet_dphi, photon_jet_deta, wtx);
						hist.phjet_jet_eta->Fill(hardest_jet_eta, wtx);
						hist.phjet_jet_phi->Fill(hardest_jet_phi, wtx);
						hist.phjet_deta->Fill(photon_jet_deta, wtx);
						hist.phjet_dphi->Fill(photon_jet_dphi * 180.0/TMath::Pi(), wtx);
						hist.phjet_deta_unmarged->Fill(photon_jet_deta, wtx);
						hist.phjet_dphi_unmarged->Fill(photon_jet_dphi*180.0/TMath::Pi(), wtx);
						hist.phjet_deta_el_ph->Fill(photon_electron_deta, wtx);
						hist.phjet_dphi_el_ph->Fill(photon_electron_dphi, wtx);

						hist.phjet_deta_el_ph_true->Fill(photon_electron_deta_true, wtx);
						hist.phjet_deta_el_ph_true_unmerged->Fill(photon_electron_deta_true, wtx);
						hist.phjet_dphi_el_ph_true->Fill(photon_electron_dphi_true * 180.0/TMath::Pi(), wtx);
						hist.phjet_dphi_el_ph_true_unmerged->Fill(photon_electron_dphi_true, wtx);

						hist.phjet_deta_el_jet->Fill(jet_electron_deta, wtx);
						hist.phjet_dphi_el_jet->Fill(jet_electron_dphi, wtx);
						hist.et_jet_photon_ratio->Fill(max_et_accomp_jet/max_et_candidate, wtx);
						hist.h2d_et_jet_et_photon->Fill(max_et_accomp_jet, max_et_candidate, wtx);
						Double_t et_3system_ev_ratio = (max_et_accomp_jet + max_et_candidate + Siecorr[0][2]* systElE * TMath::Sin(Sith[0]))/et_of_event;
						hist.et_3system_event_ratio->Fill(et_3system_ev_ratio, wtx);
						hist.h2d_phijet_phigamma->Fill(hardest_jet_phi, v_corr_prompt_photon->Phi(), wtx);
						hist.h2d_dphijet_dphigamma->Fill(hardest_jet_phi - 
								Siph[0], delta_phi(v_corr_prompt_photon->Phi(), Siph[0]), wtx);
						Double_t delta_phi_jet_el = delta_phi(hardest_jet_phi, Siph[0]);
						Double_t delta_phi_photon_el = delta_phi(v_corr_prompt_photon->Phi(), Siph[0]);
						hist.h2d_dphijet_dphigamma_sharp->Fill(delta_phi_jet_el, delta_phi_photon_el, wtx);
						hist.phjet_cal_empz->Fill(Cal_empz, wtx);
						hist.phjet_zufo_empz->Fill(Empz, wtx);
						hist.phjet_zvtx->Fill(Zvtx, wtx);
						hist.phjet_eph->Fill(v_corr_prompt_photon->E(), wtx);
						if(Siyel[0] < 0.5) 
						{
							hist.phjet_y_y_lt_05->Fill(Siyel[0], wtx);
							hist.phjet_eel_y_lt_05->Fill(Siecorr[0][2] * systElE , wtx);
							hist.phjet_phiph_phij_y_lt_05->Fill(photon_jet_dphi, wtx);
							hist.phjet_thetael_y_lt_05->Fill(Sith[0], wtx);
							hist.phjet_etaph_y_lt_05->Fill(photon_eta, wtx);
							hist.phjet_etph_y_lt_05->Fill(max_et_candidate, wtx);
						}
						if(Siyel[0] > 0.5) 
						{
							hist.phjet_y_y_gt_05->Fill(Siyel[0], wtx);
							hist.phjet_eel_y_gt_05->Fill(Siecorr[0][2] * systElE , wtx);
							hist.phjet_phiph_phij_y_gt_05->Fill(photon_jet_dphi, wtx);
							hist.phjet_thetael_y_gt_05->Fill(Sith[0], wtx);
							hist.phjet_etaph_y_gt_05->Fill(photon_eta, wtx);
							hist.phjet_etph_y_gt_05->Fill(max_et_candidate, wtx);
						}
						//
						// histograms for Peter+Misha reweighting procedure
						//
						if(glob_deltaz > 0.35) 
						{
							hist.phjet_q2_dz_gt_035->Fill(Siq2el[0], wtx);
							hist.phjet_y_dz_gt_035->Fill(Siyel[0], wtx);
							hist.phjet_etaph_dz_gt_035->Fill(v_corr_prompt_photon->Eta(), wtx);
							hist.phjet_etph_dz_gt_035->Fill(v_corr_prompt_photon->Et(), wtx);
							hist.phjet_eph_dz_gt_035->Fill(v_corr_prompt_photon->E(), wtx);
							hist.phjet_eel_dz_gt_035->Fill(Siecorr[0][2]* systElE , wtx);
						}
						if(glob_deltaz < 0.35) 
						{
							hist.phjet_q2_dz_lt_035->Fill(Siq2el[0], wtx);
							hist.phjet_y_dz_lt_035->Fill(Siyel[0], wtx);
							hist.phjet_etaph_dz_lt_035->Fill(v_corr_prompt_photon->Eta(), wtx);
							hist.phjet_etph_dz_lt_035->Fill(v_corr_prompt_photon->Et(), wtx);
							hist.phjet_eph_dz_lt_035->Fill(v_corr_prompt_photon->E(), wtx);
							hist.phjet_eel_dz_lt_035->Fill(Siecorr[0][2]* systElE , wtx);
						}

						hist.phjet_q2_dz_full->Fill(Siq2el[0], wtx);
						hist.phjet_y_dz_full->Fill(Siyel[0], wtx);
						hist.phjet_etaph_dz_full->Fill(v_corr_prompt_photon->Eta(), wtx);
						hist.phjet_etph_dz_full->Fill(v_corr_prompt_photon->Et(), wtx);
						hist.phjet_eph_dz_full->Fill(v_corr_prompt_photon->E(), wtx);
						hist.phjet_eel_dz_full->Fill(Siecorr[0][2]* systElE , wtx);
						hist.phjet_dr_track->Fill(deltaRtrack, wtx);
						if(!Data) 
						{
							hist.mccorel_q2[0]->Fill(Siq2el[0] - Mc_q2, Mc_q2, wtx);
							hist.mccorel_q2[1]->Fill(Siq2da[0] - Mc_q2, Mc_q2, wtx);
							hist.mccorel_q2[2]->Fill(Siq2jb[0] - Mc_q2, Mc_q2, wtx);

							hist.mccorel_x[0]->Fill(Sixel[0] - Mc_x, Mc_x, wtx);
							hist.mccorel_x[1]->Fill(Sixda[0] - Mc_x, Mc_x, wtx);
							hist.mccorel_x[2]->Fill(Sixjb[0] - Mc_x, Mc_x, wtx);

							hist.mccorel_y[0]->Fill(Siyel[0] - Mc_y, Mc_y, wtx);
							hist.mccorel_y[1]->Fill(Siyda[0] - Mc_y, Mc_y, wtx);
							hist.mccorel_y[2]->Fill(Siyjb[0] - Mc_y, Mc_y, wtx);
						}
						selectedEventsCount++;
						//printout interesting events
						if(print_interesting_events && et_3system_ev_ratio > 0.95) 
						{
							if (nodebugmode) cout << endl;
							if (nodebugmode) cout << "============ INTERESTING EVENT ================" << endl;
							if (nodebugmode) cout << "========= " << Runnr << " " << Eventnr << " ================" << endl;
							if (nodebugmode) cout << " seems to be clean: et_3system_ev_ratio = " << et_3system_ev_ratio << endl;
							if (nodebugmode) cout << "===============================================" << endl << endl;      
						}
						//if take_event_trig
					}
				}
			}//if take_event for jet searching

			if(!Data && SelectHadronLevel(take_event && here_is_jet && here_is_prph && take_event_trig)) 
			{
				if(take_event && here_is_jet && here_is_prph && take_event_trig) 
				{
					hist.h2d_phot_et_true_det->Fill(v_true_prompt_photon->Et(), v_corr_prompt_photon->Et());
					hist.h2d_phot_eta_true_det->Fill(v_true_prompt_photon->Eta(), v_corr_prompt_photon->Eta());
					hist.h2d_phot_phi_true_det->Fill(v_true_prompt_photon->Phi(), v_corr_prompt_photon->Phi());
					hist.h2d_corr_accjet_et_true_det->Fill(v_true_acc_jet->Et(), v_accomp_corr_jet->Et());
					hist.h2d_corr_accjet_eta_true_det->Fill(v_true_acc_jet->Eta(), v_accomp_corr_jet->Eta());
					hist.h2d_corr_accjet_phi_true_det->Fill(v_true_acc_jet->Phi(), v_accomp_corr_jet->Phi());
					hist.h2d_uncorr_accjet_et_true_det->Fill(v_true_acc_jet->Et(), v_accomp_uncorr_jet->Et());
					hist.h2d_uncorr_accjet_eta_true_det->Fill(v_true_acc_jet->Eta(), v_accomp_uncorr_jet->Eta());
					hist.h2d_uncorr_accjet_phi_true_det->Fill(v_true_acc_jet->Phi(), v_accomp_uncorr_jet->Phi());
					//    hist.h2d_phot_en_true_det->Fill();
				}
				//  event_list->Enter(entry);
			}
		}// if exact event     
		 if (breakindex) break;   
	}// for entry over entries
	list_of_runs.close();
	Terminate();
	cout<<"There was "<<missed <<"missed events by xgamma"<<endl;
	return kTRUE;
}

void selector::SlaveTerminate()
{
	// The SlaveTerminate() function is called after all entries or objects
	// have been processed. When running with PROOF SlaveTerminate() is called
	// on each slave server.
}


/*
	void sortEt(TObjArray *arrayNotSorted, TObjArray *arraySorted)
  	{
	//  Double_t maxEt = 0.;// (static_cast<TLorentzVector*> (arrayNotSorted->At(0)))->Et();
	Double_t et[100];

	Int_t sortedIndex[100] = {0};
	Int_t counter = 0;
	for(Int_t i=0; i<arrayNotSorted->GetEntries(); i++)
	{
	et[i] = (static_cast<TLorentzVector*> (arrayNotSorted->At(i)))->Et();
	}
	while(counter<arrayNotSorted->GetEntries())
	{
	Int_t max;
	Int_t N = arrayNotSorted->GetEntries();
	max = findMaxEt(sortedIndex, et, N);
	Double_t px_jet = (static_cast<TLorentzVector*>(arrayNotSorted->At(max)))->Px();
	Double_t py_jet = (static_cast<TLorentzVector*>(arrayNotSorted->At(max)))->Py();
	Double_t pz_jet = (static_cast<TLorentzVector*>(arrayNotSorted->At(max)))->Pz();
	Double_t e_jet = (static_cast<TLorentzVector*>(arrayNotSorted->At(max)))->E();
	arraySorted->Add(new TLorentzVector(px_jet, py_jet, pz_jet, e_jet) );
	sortedIndex[max] = 1;
	counter++;
	}
	}

	Int_t findMaxEt(Int_t sorted[], Double_t et_jets[], Int_t N)
	{
	Double_t et;
	Double_t maxEt = 0;
	Int_t sort = -1;
	for(Int_t j=0; j<N; j++)
	{
	et = et_jets[j];
	if(et>maxEt && sorted[j]==0)
	{
	maxEt = et;
	sort = j;
	}
	}
	return sort;
	}
*/
//#endif
