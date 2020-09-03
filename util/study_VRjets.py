import ROOT
from array import array
from plothelper import *
ROOT.gROOT.SetBatch(ROOT.kTRUE)

setStyle()

def adjust2D(hist):
    name = hist.GetName() 
    if "mass" in name and "mMed-750" in name: 
        print("found")
        hist.GetYaxis().SetRangeUser(0,1500)
        hist.GetXaxis().SetRangeUser(0,1500)
    if "dR" in name :
        hist.GetXaxis().SetRangeUser(0,2)
        if "ratio" in name: hist.GetYaxis().SetRangeUser(0,1.5)


def adjust(hist):
    name = hist.GetName()
    if "nchpfs" in name and "QCD" in name: hist.GetYaxis().SetRangeUser(0,300)
    if "suep_truth" in name: hist.Rebin()
    if "suep_nconstit" in name: hist.Rebin(3)
    if "suep_m" in name: hist.Rebin(3)
    if "suep_pt" in name: hist.Rebin(3)
    if "suep_width" in name: hist.GetXaxis().SetRangeUser(0,2)
    if "dR" in name: hist.GetXaxis().SetRangeUser(0,3.5)

def clean2D(hist):
    # Clean
    adjust2D(hist)
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

def get2D(mMed,mDark,temp,decay,histname):

    # Get hist
    filename = "output/mMed-{}_mDark-{}_temp-{}_decay-{}.root".format(mMed,mDark,temp,decay)
    f = ROOT.TFile.Open(filename)
    hist = f.Get(histname)
    if hist : 
    	clean2D(hist)
    	return hist
    return 0

def plot2D(mMed,mDark,temp,decay,sel,dist):

	c = ROOT.TCanvas(dist,"",900,800)
	c.SetRightMargin(0.25)
	c.SetLeftMargin(0.15)

	histname = "mMed-{}_mDark-{}_temp-{}_decay-{}_{}_{}".format(mMed,mDark,temp,decay,sel,dist)
	hist = get2D(mMed,mDark,temp,decay,histname)
	hist.Draw("COLZ")

	c.Print("plots/study_VRjets/2D_{}.png".format(histname))
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

def get1D(mMed,mDark,temp,decay,histname):

    # Get hist
    filename = "output/mMed-{}_mDark-{}_temp-{}_decay-{}.root".format(mMed,mDark,temp,decay)
    f = ROOT.TFile.Open(filename)
    #print(histname)
    hist = f.Get(histname)
    if hist : 
    	clean1D(hist)
    	return hist
    return 0

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
    #tsamples.append("QCD_HT200to300")# do slicing later
    #tsamples.append("QCD_HT300to500")# do slicing later
    #tsamples.append("QCD_HT500to700")# do slicing later
    samples.append("QCD_HT700to1000")# do slicing later
    samples.append("QCD_HT1000to1500")# do slicing later
    samples.append("QCD_HT1500to2000")# do slicing later
    samples.append("QCD_HT2000toInf")# do slicing later
    
    hists = []
    for sample in samples: 
        f = ROOT.TFile.Open("output/{}.root".format(sample))
        h = f.Get("{}_{}".format(sample,dist))
        if not h: continue
        h.Scale(qcd_xs(sample))
        h.SetDirectory(0)
        hists.append(h)

    hist_final = hists[0].Clone("QCD_"+dist)
    for i,hist in enumerate(hists):
        if i>0: hist_final.Add(hist)

    clean1D(hist_final)

    return hist_final

def decay_label(decay):
    if "darkPhoHad" in decay: return "m_{A'}=0.7 GeV"
    if "darkPho" in decay: return "m_{A'}=0.5 GeV"
    if "generic" in decay: return "m_{A'}=m_{#phi}/2, A'#rightarrowu#bar{u}"

def label(mMed,decay,jettype):
    #return "(m_{S},m_{#phi},T)=(%i,%i,%i), %s"%(mMed,mDark,temp,decay_label(decay))
    jet=""
    if "AK15"   in jettype: jet = "anti-k_{T} R=1.5"
    if "VR500"  in jettype: jet = "AKVR #rho=500"
    if "VR1000" in jettype: jet = "AKVR #rho=1000"
    if "VR2000" in jettype: jet = "AKVR #rho=2000"

    return "m_{S}=%i, %s, %s"%(mMed,decay_label(decay),jet)

def compare1D(hists,labels,filename):
    c = ROOT.TCanvas(filename,"",800,800)

    dy = 0.05*len(hists)
    leg = ROOT.TLegend(0.18,0.86-dy,0.86,0.86)
    leg.SetTextSize(0.035)
    leg.SetBorderSize(0)

    ymax = 0
    for i,hist in enumerate(hists): 
        #hist.SetLineColor(colors[i])
        if "anti-k" in labels[i]: hist.SetLineColor(ROOT.kBlack) 
        else: hist.SetLineColor(colors[i])
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
    return

def makeROC(hists,labels,filename):
    c = ROOT.TCanvas(filename,"",800,800)

    dy = 0.05*len(hists)
    leg = ROOT.TLegend(0.18,0.86-dy,0.86,0.86)
    leg.SetTextSize(0.04)
    leg.SetBorderSize(0)

    for i,hist in enumerate(hists):
        if "QCD" in labels[i] : hbkg = hist

    ymax = 0
    mgraph = ROOT.TMultiGraph()
    for i,hist in enumerate(hists): 
        if "QCD" in labels[i]: continue
        eff_sig = []
        eff_bkg = []
        err = []

        crossed=False
        for b in range(1,hist.GetNbinsX()+1):
            eff_sig.append( hist.Integral(b,-1) )
            eff_bkg.append( hbkg.Integral(b,-1) )
            err.append(0.000000001)
            #print (hbkg.Integral(b,-1))
            if hbkg.Integral(b,-1) < 0.01 and crossed is False:
                print(hist.GetName(),hist.Integral(b,-1))
                crossed=True
            
        
        graph = ROOT.TGraphErrors(len(err),array("d",eff_sig),array("d",eff_bkg),array("d",err),array("d",err))

        graph.SetLineColor(colors[i])
        mgraph.Add(graph)
        leg.AddEntry(graph,labels[i],"l")
    
    mgraph.SetTitle(";sig eff;bkg eff")
    mgraph.Draw("AELP")
    if "nchpfs" in hists[0].GetName(): mgraph.GetYaxis().SetRangeUser(0.00000001,1)
    else : mgraph.GetYaxis().SetRangeUser(0.01,1)
    
    leg.Draw()
    c.SetLogy(1)
    c.SetLogx(1)
    mgraph.GetXaxis().SetRangeUser(0.001,1)
    c.Print("plots/{}_logx.png".format(filename))
    c.SetLogx(0)
    mgraph.GetXaxis().SetRangeUser(0,1)
    c.Print("plots/{}_linx.png".format(filename))
    c.SetLogy(0)

def compareJetType(mMed,mDark,temp,decay,sel,dist):
    jettypes = []
    jettypes.append("jetsVR500")
    jettypes.append("jetsVR1000")
    jettypes.append("jetsVR2000")
    jettypes.append("jetsAK15")

    hists = []
    labels = []
    for jettype in jettypes:
        histname = "mMed-{}_mDark-{}_temp-{}_decay-{}_{}_{}_{}".format(mMed,mDark,temp,decay,sel,jettype,dist)
        #print(histname)
        hist = get1D(mMed,mDark,temp,decay,histname)
        if hist : 
            if "ratio" in histname:
                print(mMed,decay,dist,jettype,hist.GetMean())
            hists.append(hist)
            labels.append(label(mMed,decay,jettype))

    #if "scalar" not in dist and "jet" not in dist and "evtshape" not in dist: 
    #hists.append(getQCD(dist))
    #labels.append("QCD")
    
    compare1D(hists,labels,"study_VRjets/mMed{}_temp{}_mDark{}_decay_{}_{}_{}".format(mMed,temp,mDark,decay,sel,dist))
    #if histname=="h_pf_ntracks": 
    return

def getFixedEff(sel,dist):

    mMeds = []
    mMeds.append(125)
    mMeds.append(400)
    mMeds.append(750)
    mMeds.append(1000)

    jettypes = []
    jettypes.append("jetsVR500")
    jettypes.append("jetsVR1000")
    jettypes.append("jetsVR2000")

    decay="darkPhoHad"
    mDark=2
    temp=2

    for jettype in jettypes: 
        hists = []
        labels = []
        for mMed in mMeds:
            histname = "mMed-{}_mDark-{}_temp-{}_decay-{}_{}_{}_{}".format(mMed,mDark,temp,decay,sel,jettype,dist)
            #print(histname)
            hist = get1D(mMed,mDark,temp,decay,histname)
            if hist : 
                hists.append(hist)
                labels.append(label(mMed,decay,jettype))
    
        #hists.append(getQCD("{}_jetsAK{}_{}".format(sel,size,dist)))
        #labels.append("QCD")
        
        compare1D(hists,labels,"study_VRjets/scanEff_temp{}_mDark{}_decay_{}_{}_{}".format(temp,mDark,decay,jettype,dist))
        #if histname=="h_pf_ntracks": 
        #makeROC(hists,labels,"study_VRjets/ROC_temp{}_mDark{}_decay_{}_jetsAK{}_{}".format(temp,mDark,decay,size,dist))

 
    return


sels = []
#sels.append("all")
#sels.append("scouting")
sels.append("offline")

dists=[]
#dists.append("suep_constit_pt")    
dists.append("suep_dRscalar")     
dists.append("suep_dRtruth") 
dists.append("suep_eta")           
dists.append("suep_m")             
dists.append("suep_nconstit")      
dists.append("suep_phi")           
dists.append("suep_pt")            
dists.append("suep_width") 

dists.append("suep_truth_ratio_mass")
dists.append("suep_truth_ratio_pt")
dists.append("suep_truth_ratio_nconstit")

mMeds=[]
#mMeds.append(125) 
#mMeds.append(400) 
mMeds.append(750) 
#mMeds.append(1000) 

dists2D=[]
#dists2D.append("suep_scalar_Tmass"   )
#dists2D.append("suep_scalar_Rmass"   )
#dists2D.append("suep_scalar_Tpt"   )
#dists2D.append("suep_scalar_Rpt"   )
dists2D.append("suep_truth_mass"    )
dists2D.append("suep_truth_pt"      )
dists2D.append("suep_truth_nconstit")
#dists2D.append("suep_dRtruth_ntrack")
#dists2D.append("suep_dRtruth_rationtrack")




for sel in sels: 
    for dist in dists:

        getFixedEff(sel,dist)
        for mMed in mMeds:
            #print(sel,dist,mMed)
            compareJetType(mMed,2,2,"darkPhoHad",sel,dist)

for sel in sels:
    for mMed in mMeds:
            if mMed==750:   
                for dist in dists2D:
            #    #    plot2D(mMed,2,2,"darkPhoHad",sel,"jetsAK20_" + dist)
                    plot2D(mMed,2,2,"darkPhoHad",sel,"jetsVR500_" + dist)
                    plot2D(mMed,2,2,"darkPhoHad",sel,"jetsVR1000_" + dist)
                    plot2D(mMed,2,2,"darkPhoHad",sel,"jetsVR2000_" + dist)

        
        



