#define selectorTermninate_c

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "constants.h"
#include "selector.h"
#include "runinfo.h"

void selector::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.
  delete v_uncorr_prompt_photon;
  delete v_corr_prompt_photon;
  if (nodebugmode) cout << "generating tree..." << endl;
  fChain->SetEventList(event_list);
  TTree *tree = fChain->CopyTree("");
  tree->Write();
  if (nodebugmode) cout << "done" << endl;
  f->Write();
  {
    if (nodebugmode) cout << "DIS03: " << cut_DIS03 << endl;
  }
  if (nodebugmode) cout << "gamma had cut: " << cut_gammahad << endl;
  if (nodebugmode) cout << "number of good tracks: " << cut_ngoodtrks << endl;
  if (nodebugmode) cout << "electron is in outer parto of RCAL: " << cut_RCAL << endl;
  if (nodebugmode) cout << "poltake: " << cut_poltake << endl;
  if (nodebugmode) cout << "QED Compton rejecting: " << cut_QEDC << endl;
  if (nodebugmode) cout << "y*(1-x)^2 > 0.004: " << cut_yx2 << endl;
  //		if (nodebugmode) cout << "Sincand: " << cut_Sincand << endl;
  //		if (nodebugmode) cout << "Siecorr && Emecorr: " << cut_Siecorr << endl;
  if (nodebugmode) cout << "electron candidate: " << cutElCand << endl;
  if (nodebugmode) cout << "electron energy: " << cutEC_1 << endl;
  if (nodebugmode) cout << "electron track in ctd acc.: " << cutEC_6_1 << endl;
  if (nodebugmode) cout << "electron track momentum: " << cut_track_momentum << endl;
  if (nodebugmode) cout << "electron track dca: " << cut_electron_track_dca << endl;
  if (nodebugmode) cout << "electron distance to the module edge: " << cut_electron_distance_module_edge << endl;
  if (nodebugmode) cout << "electron distance to beam pipe: " << cutEC_4 << endl;
  if (nodebugmode) cout << "enin: " << cutEC_5 << endl;
  if (nodebugmode) cout << "zvtx: " << cutC_1 << endl;
  if (nodebugmode) cout << "e-pz: " << cutC_2 << endl;
  if (nodebugmode) cout << "q2: " << cutPS_1 << endl;
  if (nodebugmode) cout << "y: " << cutPS_2 << endl;
  if (nodebugmode) cout << "pt/et: " << cutC_3 << endl;
  if (nodebugmode) cout << "chimney: " << cutEC_2 << endl;
  if (nodebugmode) cout << "super crack: " << cutEC_3 << endl;
  
  //		if (nodebugmode) cout << "Rejected cells: " << float(badCells/numberOfEntries) <<
  //				" per event" << endl;
  if (nodebugmode) cout << "Total events selected: " << selectedEventsCount << endl;
  if (nodebugmode) cout << "If in ctd acc: " << cutCTDacc << endl;
  if (nodebugmode) cout << "Selected jets in this file: " << localSelectedJetsCount << endl;
  if (nodebugmode) cout << "selected jets total: " << totalSelectedJetsCount << endl;
  if (nodebugmode) cout << "eta_lab: "<< cutJPS_1 << endl;
  if (nodebugmode) cout << "dijets assimetric cut (is already not assymetric): " << cut_assymetric << endl;
  if (nodebugmode) cout << "Mjj > 20 GeV cut: " << cut_Mjj << endl;
  if (nodebugmode) cout << "distance betw. el. and jet: "<< cutJC_1 << endl;
  if (nodebugmode) cout << "E Breit > 5 && eta lab < -2: " << cutJC_2 << endl;
  if (nodebugmode) cout << "EtLab > 3: " << cutJC_3 << endl;
  if (nodebugmode) cout << "dijet events: " << detector_dijets << endl;
  
  if(!Data)
    {
      if (nodebugmode) cout << "hadron q2: " << cut_q2_bos << endl;
      if (nodebugmode) cout << "hadron y: " << cut_y_bos << endl;
      if (nodebugmode) cout << "\n-----parton level-----" << endl;
      if (nodebugmode) cout << "Et_jet: " << cut_part_Et_jet << endl;
      if (nodebugmode) cout << "M_jj cut: " << cut_p_Mjj << endl;
      if (nodebugmode) cout << "eta_jet: " << cut_part_eta << endl;
      if (nodebugmode) cout << "parton dijet events: " << partonDijetEvents << endl;
      if (nodebugmode) cout << "\n-----hadron level-----" << endl;
      if (nodebugmode) cout << "Et_jet: " << cut_hadr_Et_jet << endl;
      if (nodebugmode) cout << "M_jj cut: " << cut_h_Mjj << endl;
      if (nodebugmode) cout << "eta_jet: " << cut_hadr_eta << endl;
      if (nodebugmode) cout << "hadron dijet events: " << hadronDijetEvents << endl;
    }
  if (nodebugmode) cout << "period: " << period << endl;
  if (nodebugmode) cout << "use_corr: " << use_corr << endl;
  if (nodebugmode) cout << endl;
  //		} //if % 10
  
  
  if (nodebugmode) cout << "Total processed: " << processedEventsCount << " events" << endl;
  if (nodebugmode) cout << take_det_dijet << endl;

  time_end.Set();
  if (nodebugmode) cout << "\nbegin time:\t" << time_begin.AsString()  << endl;
  if (nodebugmode) cout << "finish time:\t" << time_end.AsString() << endl << endl;
  Int_t d_days = time_end.GetDay() - time_begin.GetDay();
  Int_t d_hours = time_end.GetHour() - time_begin.GetHour();
  Int_t d_minutes = time_end.GetMinute() - time_begin.GetMinute();
  Int_t d_sec = time_end.GetSecond() - time_begin.GetSecond();

  if (d_sec < 0)
    {
      d_minutes--;
      d_sec = 60 + d_sec;
    }
  if (d_minutes < 0)
    {
      d_hours--;
      d_minutes = 60 + d_minutes;
    }
  if (d_hours < 0)
    {
      d_days--;
      d_hours = 24 + d_hours;
    }
  if (nodebugmode) cout << "time of running: " << d_days << " days " << d_hours << " hours "
       << d_minutes << " minutes " << d_sec <<" seconds" << endl;

}
