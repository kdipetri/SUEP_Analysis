import ROOT
from plothelper import *

f=ROOT.TFile.Open("output/track_matching.root")

setStyle()

def xaxis(dist):
    name = dist 
    if "pt" in name: return "track p_{T} [GeV]"
    if "eta" in name: return "track #eta"
    if "phi" in name: return "track #phi"
    return ""

def ratio(hnum,hden): 
    name = hden.GetName()
    hist = hden.Clone()
    hist.Divide(hnum,hden,1,1,"B")
    hist.SetDirectory(0)
    return hist

def eff(dist):
    hnum = f.Get("h_truth_recod_{}".format(dist))
    hden = f.Get("h_truth_{}".format(dist))
    return ratio(hnum,hden)

def fake(dist):
    hnum = f.Get("h_reco_fake_{}".format(dist))
    hden = f.Get("h_reco_{}".format(dist))
    return ratio(hnum,hden)

def draw(dist):
    h_eff = eff(dist)
    h_fake = fake(dist)
    h_eff.SetLineColor(ROOT.kBlue+1)
    h_fake.SetLineColor(ROOT.kRed+1)
    #h_eff.SetLineWidth(2)
    #h_fake.SetLineWidth(2)

    c = ROOT.TCanvas("c1","",800,800)

    h_eff.Draw("he")
    h_fake.Draw("hesame")
    h_eff.GetXaxis().SetTitle(xaxis(dist))
    h_eff.GetXaxis().SetTitleSize(0.06)
    h_eff.GetYaxis().SetTitleSize(0.06)
    h_eff.GetXaxis().SetLabelSize(0.05)
    h_eff.GetYaxis().SetLabelSize(0.05)
    if "ptS" in dist: h_eff.GetXaxis().SetRangeUser(0,6)

    leg = ROOT.TLegend(0.3,0.5,0.8,0.7)
    leg.AddEntry(h_eff,"track selection efficiency")
    leg.AddEntry(h_fake,"track selection fake rate")
    leg.SetBorderSize(0)
    leg.Draw()

    c.Print("plots/trackingeff/{}.png".format(dist))

draw("ptS")
draw("ptL")
draw("eta")
draw("phi")
