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

def qcd_xs(sample):
    if "QCD_HT200to300"   in sample : return 1559000
    if "QCD_HT300to500"   in sample : return 311900
    if "QCD_HT500to700"   in sample : return 29070
    if "QCD_HT700to1000"  in sample : return 5962
    if "QCD_HT1000to1500" in sample : return 1207 
    if "QCD_HT1500to2000" in sample : return 119.9 
    if "QCD_HT2000toInf"  in sample : return 25.24 

def getQCD(dist):

    # Get hist
    samples =[]
    samples.append("QCD_HT200to300")# do slicing later
    samples.append("QCD_HT300to500")# do slicing later
    samples.append("QCD_HT500to700")# do slicing later
    samples.append("QCD_HT700to1000")# do slicing later
    samples.append("QCD_HT1000to1500")# do slicing later
    samples.append("QCD_HT1500to2000")# do slicing later
    samples.append("QCD_HT2000toInf")# do slicing later
    
    hists = []
    for sample in samples: 
        f = ROOT.TFile.Open("output/safe_qcd/{}.root".format(sample))
        h = f.Get("{}_{}".format(sample,dist))
        if not h: continue
        h.Scale(qcd_xs(sample))
        h.SetDirectory(0)
        hists.append(h)

    hist_final = hists[0].Clone("QCD_"+dist)
    for i,hist in enumerate(hists):
        if i>0: hist_final.Add(hist)

    clean2D(hist_final)

    return hist_final



def plot2D(dist):

    c = ROOT.TCanvas(dist,"",900,800)
    c.SetRightMargin(0.25)
    c.SetLeftMargin(0.15)
    c.SetLogz(1)
    
    hist = getQCD(dist)
    hist.Draw("COLZ")
    
    c.Print("plots/2Dplots/{}.png".format(dist))
    return


dists=[]
dists.append("offline_evtshape_ht_v_circularity")	
dists.append("offline_evtshape_nchpfs_v_circularity")	
dists.append("offline_evtshape_njets_v_circularity")	
dists.append("offline_nchpfs_v_ht")	
dists.append("offline_nchpfs_v_njets")	
dists.append("scouting_evtshape_ht_v_circularity")	
dists.append("scouting_evtshape_nchpfs_v_circularity")	
dists.append("scouting_evtshape_njets_v_circularity")	
dists.append("scouting_nchpfs_v_ht")	
dists.append("scouting_nchpfs_v_njets")
dists.append("ntracks_v_npvs")



for dist in dists:
	plot2D(dist)
