import ROOT
from array import array
from plothelper import *
ROOT.gROOT.SetBatch(ROOT.kTRUE)

setStyle()


lumi = 135000 # pb

def trigger_eff(mass,sr="scout",opt="had"):
    if sr=="scout": 
        if opt=="had":
            if mass==125 : return 0.021 
            if mass==400 : return 0.086
            if mass==750 : return 0.257
            if mass==1000: return 0.718
            if mass>=2000: return 0.9
        if opt=="gen":
            if mass==125 : return 0.020 
            if mass==400 : return 0.071
            if mass==750 : return 0.145
            if mass==1000: return 0.26
            if mass>=2000: return 0.4 
    elif sr=="ht":
        if opt=="gen":
            if mass==125 : return 0.0014 
            if mass==400 : return 0.01
            if mass==750 : return 0.026
            if mass==1000: return 0.048
            if mass>=2000: return 0.1
        if opt=="had":
            if mass==125 : return 0.0025 
            if mass==400 : return 0.0114
            if mass==750 : return 0.033
            if mass==1000: return 0.052
            if mass>=2000: return 0.12

            

def ntrack_eff(mass,sr="scout",opt="had"):
        if opt=="had":
            if mass==125 : return 0.0001 
            if mass==400 : return 0.1
            if mass==750 : return 0.95
            if mass==1000: return 1.0 
            if mass>=2000: return 1.0
        if opt=="gen":
            if mass==125 : return 0.00001 
            if mass==400 : return 0.05
            if mass==750 : return 0.6
            if mass==1000: return 0.95
            if mass>=2000: return 1.0

def shape_eff(mass,sr="scout",opt="had"):
        if opt=="had":
            if mass==125 : return 0.1 
            if mass==400 : return 0.5
            if mass==750 : return 0.7
            if mass==1000: return 0.8 
            if mass>=2000: return 0.9
        if opt=="gen":
            if mass==125 : return 0.1 
            if mass==400 : return 0.5
            if mass==750 : return 0.7
            if mass==1000: return 0.8
            if mass>=2000: return 0.9



def total_eff(mass,sr,opt):
    eff = trigger_eff(mass,sr,opt)*ntrack_eff(mass,sr,opt)*shape_eff(mass,sr,opt)
    return eff

def excluded_xs(eff,qcd_bkg,sigma=3):
    # compute nsig you need after eff
    n_sig_final = sigma * (qcd_bkg+qcd_bkg**2)**0.5
    # compute nsib before selection
    n_sig_init = n_sig_final/eff
    # compute cross section
    xs = n_sig_init/lumi # in pb 
    return xs
    
def qcd_bkg(mass,sr,opt):
    if mass==125 : return 10 
    if mass==400 : return 10 
    if mass>=750 : return 1 

def label(sr,opt):
    lab=""
    if sr=="scout":lab+="Scouting, " 
    if sr=="ht"   :lab+="Offline, " 
    if opt=="had" :lab+="#gamma_{D}#rightarrowee,#mu#mu,#pi#pi" 
    if opt=="gen" :lab+="#gamma_{D}#rightarrowuu" 
    return lab

def clean(graph):
    name = graph.GetName()
    m=20
    if "gen" in name: m+=4 
    col = ROOT.kBlack
    if "scout" in name: col = ROOT.kRed 
    if "ht"    in name: col = ROOT.kBlue 
    graph.SetMarkerColor(col)
    graph.SetLineColor(col)
    graph.SetMarkerStyle(m)
    graph.SetMarkerSize(0.8)
    return
    
masses=[125,400,750,1000]
#masses=[125,400,750,1000,2000]
xs = [34.8, 5.9, 0.5, 0.17]
#xs = [34.8, 5.9, 0.5, 0.17, 0.029]
errs=[1e-9 for mass in masses]
srs = ["scout", "ht"]
opts = ["had", "gen"]

c = ROOT.TCanvas()
c.SetGridy()
c.SetGridx()
mgraph = ROOT.TMultiGraph()
leg = ROOT.TLegend(0.5,0.6,0.85,0.85)
leg.SetMargin(0.15)

graph = ROOT.TGraphErrors(len(masses),array("d",masses),array("d",xs),array("d",errs),array("d",errs))
graph.SetName("gr_xs")
clean(graph)
mgraph.Add(graph)
leg.AddEntry(graph,"Pythia XS","P")

for sr in srs: 
    for opt in opts:
        exclusions=[]
        for i,mass in enumerate(masses):
        
            eff  = total_eff(mass,sr,opt)
            excl = excluded_xs(eff,qcd_bkg(mass,sr,opt)) 
            exclusions.append(excl)
            #print(mass, excl, xs[i])
         
        graph = ROOT.TGraphErrors(len(masses),array("d",masses),array("d",exclusions),array("d",errs),array("d",errs))
        graph.SetName("gr"+sr+opt)
        clean(graph)
        mgraph.Add(graph)
        leg.AddEntry(graph,label(sr,opt),"P")

mgraph.Draw("AELP")
mgraph.SetTitle(";mS [GeV];2#sigma projection, #sigma #times BR [pb]")
leg.Draw()

c.SetLogy(1)
c.SetLogx(0)
c.Print("plots/projection.pdf")
c.Print("plots/projection.png")
