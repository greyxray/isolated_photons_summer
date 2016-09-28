#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "selector.h"

extern "C"
{
  float pcele_(int &Imod,float &Emes,float &Emip,float &The,float &Phi);
}

Bool_t selector::SelectPrPhKtJetB(Int_t i_true_rad_photon)
{
    if(!Data && i_true_rad_photon > -1) 
    {
        TVector3 v_true_rad_photon(Photp[i_true_rad_photon][0], Photp[i_true_rad_photon][1], Photp[i_true_rad_photon][2]);
        Double_t dr, dr_min = 999.;
        for(Int_t zloop = 0; zloop < Knzufos; zloop++)
        {
            Double_t zufo_px = Kzufos[zloop][0], zufo_py = Kzufos[zloop][1], zufo_pz = Kzufos[zloop][2];
            if(TMath::Sqrt((zufo_px*zufo_px + zufo_py*zufo_py)/(zufo_pz*zufo_pz)) < 1.e-10 || zufo_px!=zufo_px || zufo_py!=zufo_py || zufo_pz!=zufo_pz || zufo_px*zufo_px+zufo_py*zufo_py+zufo_pz*zufo_pz<1.e-200)
              continue;
            TVector3 v_zufo(zufo_px, zufo_py, zufo_pz);
            dr = v_zufo.DeltaR(v_true_rad_photon);
            if(dr < dr_min && dr < 0.2) 
            {
              dr_min = dr;
              radiated_candidate_number = zloop;
            }
        }
    }

    Bool_t take_prph = kTRUE;
    for (Int_t zloop = 0; zloop < Knzufos; zloop++)
    {
        take_prph = kTRUE;
        
        if ((!Data && mc_type=="mc_bg_rad" && radiated_candidate_number != zloop)||
            (!Data && mc_type=="mc_bg_norad" && radiated_candidate_number == zloop))
            take_prph = kFALSE;
        
        // sets global cuts
        Float_t zu_phi = Kzufophi[zloop];
        Double_t zu_eta = Kzufoeta[zloop];
        Double_t zu_pt = TMath::Sqrt(Kzufos[zloop][0]*Kzufos[zloop][0] + Kzufos[zloop][1]*Kzufos[zloop][1]);
        Float_t zu_theta = TMath::ATan2(zu_pt, Kzufos[zloop][2]);
        TVector3 v_photon; 
        v_photon.SetXYZ(Kzufos[zloop][0], Kzufos[zloop][1], Kzufos[zloop][2]);
        Float_t bpres_mips = (Float_t)BPRES_mips(v_photon, bpres_conerad);
        //		      cout << "calling correction " << pcele_mode << " " << photon_e << " " << bpres_mips << " " << photon_theta << " " << photon_phi << endl;
        Float_t photon_e = Kzufos[zloop][3] * systPhE; //systematics 290715
        //      if (nodebugmode) cout << "before pcele: " << 0. << " " << pcele_mode << " " << photon_e << " " << bpres_mips
        //      	   << " " << zu_theta << " " << zu_phi  << " " << photon_e * TMath::Sin(zu_theta) << endl;
        Double_t zu_e_corr = pcele_(pcele_mode, photon_e, bpres_mips, zu_theta, zu_phi);
        //      if (nodebugmode) cout << "after pcele: " << zu_e_corr  << " " << pcele_mode << " " << photon_e << " " << bpres_mips 
        //      	   << " " << zu_theta << " " << zu_phi << " " << zu_e_corr * TMath::Sin(zu_theta) << endl;
        Double_t zu_et_corr  = zu_e_corr * TMath::Sin(zu_theta);
        //      if (nodebugmode) cout << "zu_et_corr = " << zu_et_corr << endl;
        Double_t zu_et_uncorr = Kzufos[zloop][3] * systPhE * TMath::Sin(zu_theta); //! error? 070815
        Double_t zu_fmax     = Kzufofmax[zloop];//Calibration(Kzufofmax[zloop],"zu","fmax",zu_eta,zu_et_corr);
        if (zu_fmax > 0.999) zu_fmax = 0.999;
        Double_t zu_deltaz   = Kzufodeltaz[zloop] / 5.45;//Calibration(Kzufodeltaz[zloop]/5.45,"zu","deltaz",zu_eta,zu_et_corr);
        //      myKzufodeltaz[zloop] = Kzufodeltaz[zloop]/5.45;
        if(check_cuts)
          if (nodebugmode) cout << "prph candidate " << zloop  << " of " << Knzufos << ", eta = " << zu_eta 
               << ", et_corr = " << zu_et_corr << ", Knzufos = " << Knzufos << ", Nzufos = " << Nzufos << endl;
        // Cleaning cuts
        //      if (zu_fmax  <=0.05)  {
        //	take_prph = kFALSE;
        //	if(check_cuts)
        //	  if (nodebugmode) cout << "candidate " << zloop << " rejected by cut on zu_fmax = " << zu_fmax << endl;
        //      }
        //      if (zu_deltaz <0.0)   {
        //     take_prph = kFALSE;
        //    }

        if (zu_fmax <= 0.05) 
        {
            take_prph = kFALSE;
            if (check_cuts && nodebugmode) cout << "photon with eta " << zu_eta << " rejected, because fmax = " << zu_fmax << endl;
        } 
        if (zu_deltaz < 0.0)   
        {
            take_prph = kFALSE;
            if (check_cuts && nodebugmode) cout << "photon with eta " << zu_eta << " rejected, because deltaz = " << zu_deltaz << endl;
        } 
        // Phase space cuts
        if (zu_eta < -0.7)     
        {
            take_prph = kFALSE;
            if (check_cuts && nodebugmode) cout << "photon with eta " << zu_eta << " rejected, because eta = " << zu_eta << endl;
        }
        if (zu_eta > 0.9)     
        {
            take_prph = kFALSE;
            if (check_cuts && nodebugmode) cout << "photon with eta " << zu_eta << " rejected, because eta = " << zu_eta << endl;
        }
        if (zu_et_corr < 4.)  
        {
            take_prph = kFALSE;
            if (check_cuts && nodebugmode) cout << "photon with eta " << zu_eta << " rejected, because et_corr = " << zu_et_corr << endl;
        }
        if (zu_et_corr > 15.)  
        {
            take_prph = kFALSE;
            if (check_cuts && nodebugmode) cout << "photon with eta " << zu_eta << " rejected, because et_corr = " << zu_et_corr << endl;
        }
        //  Photon EMC Energy / Photon Total Energy > 0.90
        if (Kzufoemcfrac[zloop] < 0.9)
        {
            take_prph = kFALSE;
            if (check_cuts && nodebugmode) cout << "photon with eta " << zu_eta << " rejected, because emcfrac = " << Kzufoemcfrac[zloop] << endl;
        }
        // Only trackless zufos:
        if (Kzufotype[zloop] != 31)   
        {
            take_prph = kFALSE;
            if (check_cuts && nodebugmode) cout << "photon with eta " << zu_eta << " rejected, because zufo type = " << Kzufotype[zloop] << endl;
        }
        // track isolation
        //      Int_t ntrack=Tracks(zu_phi, zu_eta, 2, min_dist);
        Int_t ntrack = 0;
        for (Int_t i = 0; i < Trk_ntracks; i++)
        {
            TVector3 tr;	      
            tr.SetXYZ(Trk_px[i], Trk_py[i], Trk_pz[i]);
            if (tr.Mag() < 0.25) continue;
            // Calculating phi, eta of track
            Double_t       ddr = pow(tr.PseudoRapidity() - zu_eta, 2);
            Double_t delta_phi = tr.Phi() - zu_phi;
            if (delta_phi > TMath::Pi()) delta_phi -= 2.*TMath::Pi();
            if (delta_phi < -TMath::Pi()) delta_phi += 2.*TMath::Pi();
            ddr = TMath::Sqrt(ddr + pow(delta_phi, 2));

            if (ddr < 0.2) ntrack++;
            if (check_cuts && nodebugmode) cout << "track # " << i << " " << tr.Eta() << " " << tr.PseudoRapidity() <<  " " 
                                                << zu_eta << ", phi: " << tr.Phi() << " " << zu_phi << " " << ddr << " " << ntrack << endl;
        }
        if (ntrack > 0)  
        {
            take_prph = kFALSE;
            if (check_cuts && nodebugmode) cout << "photon with eta " << zu_eta << " rejected, because ntrack = " << ntrack << endl;
        }

        // Fraction of zufo energy to jet energy
        Double_t zu_jetEnergy = Kpjets[Kzufoidjet[zloop]-1][3];
        if ((Kzufos[zloop][3] * systPhE / zu_jetEnergy) < 0.9)
        {
            take_prph = kFALSE;
            if (check_cuts && nodebugmode) cout << "photon with eta " << zu_eta << " rejected, because e_phot/e_jet_cont_phot = " 
                                                << (Kzufos[zloop][3] * systPhE/zu_jetEnergy)<< endl;
        }

        //dR cut:
        TVector3 jet_contained_prph(Kpjets[Kzufoidjet[zloop]-1][0], 
                                    Kpjets[Kzufoidjet[zloop]-1][1],
                                    Kpjets[Kzufoidjet[zloop]-1][2]);

        Double_t   dR_jet = pow(jet_contained_prph.Eta() - zu_eta, 2);
        Double_t dphi_jet = jet_contained_prph.Phi() - zu_phi;
        if (dphi_jet >  TMath::Pi()) dphi_jet = dphi_jet - 2. * TMath::Pi();
        if (dphi_jet < -TMath::Pi()) dphi_jet = dphi_jet + 2. * TMath::Pi();
        dR_jet = TMath::Sqrt(dR_jet + pow(dphi_jet, 2));

        if (check_cuts && nodebugmode) cout << "cont jet: " << jet_contained_prph.Phi() << " " 
                                            << jet_contained_prph.Eta() << ", photon: " << zu_phi
                                            << " " << zu_eta << " dR = " << dR_jet << endl;
        if(dR_jet > 0.2)
        {
            take_prph = kFALSE;
            if (check_cuts && nodebugmode) cout << "candidate with eta " << zu_eta << " rejected by dR_jet = " << dR_jet << endl;
        }

        if(take_prph)
        {
            here_is_prph = kTRUE;
            if(zu_et_corr > max_et_candidate)
            {
                jet_energy_frac = Kzufos[zloop][3] * systPhE/zu_jetEnergy;
                cell_energy_frac = Kzufoemcfrac[zloop];
                max_et_candidate = zu_et_corr;
                max_et_candidate_uncorr = zu_et_uncorr;
                max_et_candidate_number = zloop;

                v_uncorr_prompt_photon->SetPxPyPzE(Kzufos[zloop][0], 
                                                  Kzufos[zloop][1], 
                                                  Kzufos[zloop][2], 
                                                  Kzufos[zloop][3] * systPhE);
                Double_t corfac = zu_e_corr / (Kzufos[zloop][3] * systPhE);
                v_corr_prompt_photon->SetPxPyPzE(corfac * Kzufos[zloop][0],
                                                corfac * Kzufos[zloop][1],
                                                corfac * Kzufos[zloop][2],
                                                corfac * Kzufos[zloop][3] * systPhE);
                v_prompt_photon_jet->SetPxPyPzE(Kpjets[Kzufoidjet[zloop]-1][0],
                                                Kpjets[Kzufoidjet[zloop]-1][1],
                                                Kpjets[Kzufoidjet[zloop]-1][2],
                                                Kpjets[Kzufoidjet[zloop]-1][3]);
                glob_fmax = Kzufofmax[zloop];
                glob_deltaz = myKzufodeltaz[zloop];
                glob_fmax = stretch_calib(Kzufofmax[zloop], "zu", "fmax", v_corr_prompt_photon->Eta(), v_corr_prompt_photon->Et());
                glob_deltaz = stretch_calib(myKzufodeltaz[zloop], "zu", "deltaz", v_corr_prompt_photon->Eta(), v_corr_prompt_photon->Et());
            }
            if (check_cuts && nodebugmode) cout << "====\n HERE IS PRPH CANDIDATE WITH ETA = " << zu_eta << ", it is zufo # " << max_et_candidate_number << "\n====" << endl;
            phot_count++;
        }   
        phot_count++;
    }
    return here_is_prph;
}
