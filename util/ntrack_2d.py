import ROOT
from array import array
from plothelper import *
ROOT.gROOT.SetBatch(ROOT.kTRUE)

setStyle()

def adjust(hist):
	name = hist.GetName()
	if "nchpfs" in name and "QCD" in name: hist.GetYaxis().SetRangeUser(0,300)

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

def get2D(sample,histname):

    # Get hist
    filename = "output/{}.root".format(sample)
    f = ROOT.TFile.Open(filename)
    print(histname)
    hist = f.Get(histname)
    if hist : 
        clean2D(hist)
        return hist
    else : return 0

def plot2D(dist):

    c = ROOT.TCanvas(dist,"",900,800)
    c.SetRightMargin(0.25)
    c.SetLeftMargin(0.15)
    c.SetLogz(1)
    
    sample = "mMed-{}_mDark-{}_temp-{}_decay-{}".format(400,2,2,"darkPho",dist)
    histname="{}_{}".format(sample,dist)
    hist = get2D(sample,histname)
    hist.SetBinContent(hist.GetXaxis().FindBin(31),hist.GetYaxis().FindBin(30),0)
    hist.RebinX()
    hist.Draw("COLZ")
    hist.GetYaxis().SetRangeUser(0,300)
    profile = hist.ProfileX("profx_"+histname)
    profile.Draw("same")
    
    c.Print("plots/nTracks/{}.png".format(dist))
    return

def clean1D(hist):
    name=hist.GetName()
    if "low" in name: hist.SetLineColor(ROOT.kBlue+1)  
    if "mid" in name: hist.SetLineColor(ROOT.kBlack)  
    if "high" in name: hist.SetLineColor(ROOT.kRed+1)  
    hist.SetLineWidth(2)
    hist.Scale(1.0/hist.Integral(0,-1))
    hist.GetXaxis().SetRangeUser(0,400)
    return
def compareNtracks():
    
    c = ROOT.TCanvas("c1","",800,800)
    c.SetRightMargin(0.05)
    c.SetLeftMargin(0.2)
    c.SetLogz(1)

    sample = "mMed-{}_mDark-{}_temp-{}_decay-{}".format(400,2,2,"darkPho")
    h1 = get2D(sample,"{}_{}".format(sample,"scouting_lownPV_ntracks"))
    h2 = get2D(sample,"{}_{}".format(sample,"scouting_midnPV_ntracks"))
    h3 = get2D(sample,"{}_{}".format(sample,"scouting_highnPV_ntracks"))
    h3.SetBinContent(h3.FindBin(30),0)
    clean1D(h1)
    clean1D(h2)
    clean1D(h3)
    h1.Draw()
    h1.GetYaxis().SetTitle("Events [AU]")
    h2.Draw("same")
    h3.Draw("same")

    leg = ROOT.TLegend(0.6,0.7,0.86,0.86) 
    leg.SetTextSize(0.035) 
    leg.SetBorderSize(0)
    leg.AddEntry(h1,"n_{PV}<20")
    leg.AddEntry(h2,"20<n_{PV}<30")
    leg.AddEntry(h3,"n_{PV}>30")
    leg.Draw()
    c.SetLogy(1)
    c.Print("plots/nTracks/{}_compare_scouting_ntracks.png".format(sample))
    return

plot2D("scouting_ntracks_v_npvs")

compareNtracks()
