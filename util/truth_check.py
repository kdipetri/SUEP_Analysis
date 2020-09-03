
import ROOT
from array import array
from plothelper import *
ROOT.gROOT.SetBatch(ROOT.kTRUE)

setStyle()
def adjust(hist):
	name=hist.GetName()
	if "pt" in name: hist.Rebin()
	if "ntracks" in name: hist.GetXaxis().SetTitle("n_{tracks}")
	if "truthstudy_suep_jet_eta2p5_ntracks_scalar_eta" in name: 
		hist.GetXaxis().SetTitle("scalar #eta")
		hist.GetYaxis().SetTitle("n_{tracks}, |#eta|<2.5")
	if "truthstudy_suep_jet_scalar_mass" in name:
		hist.GetXaxis().SetTitle("scalar mass [GeV]")
		hist.GetYaxis().SetTitle("truth particles mass [GeV]")	
	if "truthstudy_suep_jet_scalar_pt" in name:
		hist.GetXaxis().SetTitle("scalar p_{T} [GeV]")
		hist.GetYaxis().SetTitle("truth particles p_{T} [GeV]")	
	return 

def clean1D(hist):
    # Clean
    adjust(hist)
    hist.SetLineWidth(2)
    hist.GetYaxis().SetNdivisions(505)
    hist.GetXaxis().SetNdivisions(505)
    hist.SetDirectory(0)
    hist.Scale(1.0/hist.Integral(0,-1))
    return hist

def clean2D(hist):
    # Clean
    adjust(hist)
    #hist.SetLineWidth(2)
    hist.GetZaxis().SetTitle("events [AU]")
    hist.GetZaxis().SetTitleOffset(1.2)
    hist.GetYaxis().SetTitleOffset(1.2)
    hist.GetXaxis().SetTitleOffset(0.9)
    hist.GetYaxis().SetNdivisions(505)
    hist.GetXaxis().SetNdivisions(505)
    hist.SetDirectory(0)
    #hist.Scale(1.0/hist.Integral(0,-1))
    return hist

def plot2D(dist):

	c = ROOT.TCanvas(dist,"",900,800)
	c.SetRightMargin(0.25)
	c.SetLeftMargin(0.15)

	mMed=750
	mDark=2
	temp=2
	decay="darkPhoHad"

	filename = "output/mMed-{}_mDark-{}_temp-{}_decay-{}.root".format(mMed,mDark,temp,decay)
	f = ROOT.TFile.Open(filename)
	
	histname="mMed-{}_mDark-{}_temp-{}_decay-{}_{}".format(mMed,mDark,temp,decay,dist)
	hist = f.Get(histname)
	if hist : 
	    clean2D(hist)

	hist.Draw("COLZ")

	c.Print("plots/truth_mass_study/{}.png".format(dist))
	return

def get1D(mMed,mDark,temp,decay,histname):

    # Get hist
    filename = "output/mMed-{}_mDark-{}_temp-{}_decay-{}.root".format(mMed,mDark,temp,decay)
    f = ROOT.TFile.Open(filename)
    
    hist = f.Get(histname)
    if hist : 
        clean1D(hist)
        return hist
    else : return 0


def compare1D(hists,labels,filename):
    c = ROOT.TCanvas(filename,"",800,800)

    dy = 0.05*len(hists)
    leg = ROOT.TLegend(0.18,0.86-dy,0.86,0.86)
    leg.SetTextSize(0.035)
    leg.SetBorderSize(0)

    ymax = 0
    for i,hist in enumerate(hists):
        #print(i,hist) 
        hist.SetLineColor(colors[i])
        if "QCD" in labels[i]: hist.SetLineColor(ROOT.kBlack) 
        if i==0: hist.Draw("hist")
        else : hist.Draw("hist same")

        if hist.GetMaximum() > ymax: ymax=hist.GetMaximum()

        leg.AddEntry(hist,labels[i],"l")

    leg.Draw()
    
    c.SetLogy(1)
    hists[0].GetYaxis().SetRangeUser(0.001,ymax*100)
    c.Print("plots/{}_log.png".format(filename))
    hists[0].GetYaxis().SetRangeUser(0,ymax*1.8)
    c.SetLogy(0)
    c.Print("plots/{}_lin.png".format(filename))

def compareAcceptance(dist):
	temp=2
	decay="darkPhoHad"
	mDark=2
	mMed=750
	sels = [] 
	sels.append("truthstudy_scalar")
	sels.append("truthstudy_suep_jet_charge")
	sels.append("truthstudy_suep_jet_eta2p5")
	sels.append("truthstudy_suep_jet")
	labels = []
	labels.append("scalar, m_{S}=750 GeV")
	labels.append("all status 1 decay products")
	labels.append("status=1, |#eta|<2.5")
	labels.append("status=1, |#eta|<2.5, p_{T}>1 GeV")	
	hists = []
	
	for sel in sels:
	    histname = "mMed-{}_mDark-{}_temp-{}_decay-{}_{}_{}".format(mMed,mDark,temp,decay,sel,dist)
	    #print(histname)
	    hist = get1D(mMed,mDark,temp,decay,histname)
	    if hist : 
	        hists.append(hist)
	
	compare1D(hists,labels,"truth_mass_study/mMed-{}_decay_{}_{}".format(mMed,decay,dist))
	#if histname=="h_pf_ntracks": 


dists=[]
dists.append("mass")
dists.append("pt")
dists.append("ntracks")
for dist in dists:
	compareAcceptance(dist)

dists2D=[]
dists2D.append("truthstudy_suep_jet_eta2p5_ntracks_scalar_eta")
dists2D.append("truthstudy_suep_jet_scalar_pt")
dists2D.append("truthstudy_suep_jet_scalar_mass")
for dist in dists2D:
	plot2D(dist)

