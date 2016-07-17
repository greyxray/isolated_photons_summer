#!/usr/bin/python
import ROOT
import numpy as np

# This is the code to look into a MC root file
# h = ROOT.TH1D("Siq2el[0]", "Q2 hist", 360, 0, 360)

def main():
    # Very clever to keep this line while you want to draw something
    # ROOT.gROOT.SetBatch() 
	directories = {lambda x: "/nfs/dust/zeus/group/kuprash/orange/nat_out/data/VCGET_off/06-07p/data06-07p_%s.root" % x : 350, 
				   lambda x: "/nfs/dust/zeus/group/kuprash/orange/nat_out/data/VCGET_off/06e/data06e_%s.root" % x: 132,
				   lambda x: "/nfs/dust/zeus/group/kuprash/orange/nat_out/data/VCGET_off/04-05e/data04-05e_%s.root" % x: 415}
				   
	chain = ROOT.TChain("orange")

	for i in directories:
		dataset = map(i, range(1, directories[i] + 1) )
		map(chain.Add, dataset)

    # for f in files: chain.Add(f)
	loop_over_chain(chain)

def get_midpoint(hist):
	N = hist.GetNbinsX()
	diff, mid = np.infty, 1
	for i in range(1, N):
		ndiff = abs(hist.Integral(1, i) - hist.Integral(i, N))
		if ndiff < diff: 
			diff = ndiff
			mid = i
	return hist.GetBinCenter(mid)

def loop_over_chain(chain):
	count = 0
	h = ROOT.TH1D("Q2tot", "Q^{2}", 360, -360, 360)
	# h = ROOT.TH1D("hQ2Low",  "Q^{2} low", 360, -360, 360)
	# h = ROOT.TH1D("hQ2High", "Q^{2} high", 360, -360, 360)

	# data = [event.Siq2el[0] for event in chain]
	# map(h.Fill, data)
	h.FillRandom("gaus", 1000)
	midpoint = get_midpoint(h)
	print midpoint
	# x = np.array(event.Siq2el)[0]
	# count += 1
	# h.Fill(x)
	# if count > 5: break

    
	# h.Draw()
	# ROOT.gROOT.FindObject('c1').Update() # Otherwise it will show empty canvas
	raw_input('Press [Enter] to continue ...')


if __name__ == '__main__':
    main()
