#!/usr/bin/python
import ROOT
import numpy as np

# This is the code to look into a MC root file
# h = ROOT.TH1D("Siq2el[0]", "Q2 hist", 360, 0, 360)

def main():
    # Very clever to keep this line while you want to draw something
    # ROOT.gROOT.SetBatch()
	
	# this is my preselected ntuples -> histograms only
	#directories = ["/afs/desy.de/user/g/glusheno/isolated_photons_summer/my_data0405e_test_zero.root", 
	#			   "/afs/desy.de/user/g/glusheno/isolated_photons_summer/my_data0607p_test_zero.root", 
	#			   "/afs/desy.de/user/g/glusheno/isolated_photons_summer/my_data06e_test_zero.root"]
	#hadd my_data_merged.root my_data0405e_test_zero.root my_data0607p_test_zero.root my_data06e_test_zero.root
	mfile = ROOT.TFile("/afs/desy.de/user/g/glusheno/isolated_photons_summer/my_data_merged.root")# to do 
	mfile.ls()
	histname = "h_det_Q2"
	mhist = mfile.Get("Cross_Sections_Histograms/"+histname)
	print mhist.GetName()
	print "mid point: ", get_midpoint(mhist)
	# ROOT.gROOT.FindObject('c1').Update() # Otherwise it will show empty canvas
	raw_input('Press [Enter] to continue ...')

def get_midpoint(hist):
	N = hist.GetNbinsX()
	diff, mid = np.infty, 1
	for i in range(1, N):
		ndiff = abs(hist.Integral(1, i) - hist.Integral(i, N))
		if ndiff < diff: 
			diff = ndiff
			mid = i

	hist.SetAxisRange(10, 350, "x")
	hist.Draw()
	line  = ROOT.TLine()
	line.SetLineWidth(2)
	line.SetLineStyle(2)
	line.DrawLine(hist.GetBinCenter(mid), 0., hist.GetBinCenter(mid), 90)#hist.GetYaxis().GetXmax()
	c1 = ROOT.gROOT.FindObject('c1')
	ROOT.gPad.SetLogx()
	ROOT.gPad.SetLogy()
	
	c1.Update() # Otherwise it will show empty canvas
	c1.SaveAs("Q2_full.png")
	return hist.GetBinCenter(mid), mid


if __name__ == '__main__':
    main()
