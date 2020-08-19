import ROOT
from plothelper import *
ROOT.gROOT.SetBatch(ROOT.kTRUE)

setStyle()

def jetGraph(c,hist):

	c.cd()
	graph = ROOT.TGraph()
	i=0
	
	size_str = hist.GetName().split("_")[-1].strip("jetsAK")
	jet_size = 4. if size_str == "" else int(size_str) 

	txt = ROOT.TText()
	txt.SetNDC()
	txt.SetTextFont(42);
	txt.SetTextSize(0.03);
	for xbin in range(1,hist.GetNbinsX()+1):
		for ybin in range(1,hist.GetNbinsY()+1):
			pt  = hist.GetBinContent(xbin,ybin)
			if pt > 0:
				eta = hist.GetXaxis().GetBinCenter(xbin)
				phi = hist.GetYaxis().GetBinCenter(ybin)
				x=((eta+4)/9)#-0.04
				y=((phi+4)/9)+0.15
				#print(x,y)
				txt.DrawText(x,y,"pT={:.0f} GeV".format(pt))
				graph.SetPoint(i,eta,phi)
				i+=1

	graph.SetMarkerStyle(24)
	graph.SetMarkerColor(ROOT.kBlack)
	graph.SetMarkerSize(2.0*jet_size)
	graph.Draw("P")
	return graph

def clean2D(hist):
	hist.GetZaxis().SetTitle("track pT [GeV]")
	hist.GetYaxis().SetTitle("#phi")
	hist.GetXaxis().SetTitle("#eta")
	hist.GetZaxis().SetTitleOffset(1.3)
	hist.GetXaxis().SetTitleOffset(0.9)
	return

def sample(f):
	s = f.replace("output/","")
	s = s.replace(".root","")
	return s

def event(f,name):
	event=name.replace(sample(f)+"_","")
	event=event.replace("_event_display_tracks","")
	return event

def getEvents(filename):

	c=ROOT.TCanvas("c","",900,800)
	c.SetRightMargin(0.22)

	f=ROOT.TFile.Open(filename)
	for key in f.GetListOfKeys():
	    name=key.GetName()
	    print(name)
	    if "event_display_tracks" in name:
	        hist=f.Get(name)
	        clean2D(hist)
	        hist.Draw("COLZ")
	        c.Print("plots/displays/{}_{}_tracks.png".format(sample(filename),event(filename,name)))

	        #c.Print("plots/displays/{}_{}.png".format(sample(filename),event(filename,name)))

	        #hist_jets=f.Get(name.strip("tracks")+"jets")
	        #hist_jets=f.Get(name.strip("tracks")+"jetsAK20")
	        #hist_jets=f.Get(name.strip("tracks")+"jetsAK15")
	        #hist_jets=f.Get(name.strip("tracks")+"jetsAK8")
	        #hist_jets=f.Get(name.strip("tracks")+"jetsAK18")
	        #graph_jets=jetGraph(c,hist_jets)
	        #graph_jets.Draw("P")

	        #c.Print("plots/displays/{}_{}_jets.png".format(sample(filename),event(filename,name)))
	        #c.Print("plots/displays/{}_{}_jetsAK20.png".format(sample(filename),event(filename,name)))
	        #c.Print("plots/displays/{}_{}_jetsAK15.png".format(sample(filename),event(filename,name)))
	        #c.Print("plots/displays/{}_{}_jetsAK8.png".format(sample(filename),event(filename,name)))
	        #c.Print("plots/displays/{}_{}_jetsAK18.png".format(sample(filename),event(filename,name)))
            

files=[]
files.append("output/mMed-125_mDark-2_temp-2_decay-generic.root")
files.append("output/mMed-400_mDark-2_temp-2_decay-generic.root")
files.append("output/mMed-750_mDark-2_temp-2_decay-generic.root")
files.append("output/mMed-1000_mDark-2_temp-2_decay-generic.root")
files.append("output/QCD_HT1000to1500.root")
files.append("output/QCD_HT500to700.root")


for f in files: 
	getEvents(f)
