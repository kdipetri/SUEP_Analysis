import ROOT
from array import array
from plothelper import *
ROOT.gROOT.SetBatch(ROOT.kTRUE)

setStyle()

def adjust(hist):
    name = hist.GetName()
    #if "ntracks" in name: hist.Rebin()
    if "ntracks" in name: hist.GetXaxis().SetRangeUser(0,600)
    #if "npfs" in name: hist.Rebin()
    if "nchpfs" in name: 
        hist.GetXaxis().SetRangeUser(0,500)
    if "nneutrals" in name: 
        hist.GetXaxis().SetRangeUser(0,600)
        hist.GetXaxis().SetTitle("n neutrals")
    if "isotropy" in name: hist.Rebin()
    if "circularity" in name: hist.Rebin()
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
    print(histname)
    hist = f.Get(histname)
    clean1D(hist)

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

def label(mMed,mDark,temp,decay):
    #return "(m_{S},m_{#phi},T)=(%i,%i,%i), %s"%(mMed,mDark,temp,decay_label(decay))
    return "m_{S}=%i, m_{#phi}=%i, T=%i, %s"%(mMed,mDark,temp,decay_label(decay))

def doROC(histname):
    if "nchpfs" in histname: return 1
    if "evtshape" in histname: return 1
    if "suep" in histname: return 1
    else: return 0 

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
        for b in range(1,hist.GetNbinsX()+1):
            eff_sig.append( hist.Integral(b,-1) )
            eff_bkg.append( hbkg.Integral(b,-1) )
            err.append(0.000000001)
        
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
    

def compare1D(hists,labels,filename):
    c = ROOT.TCanvas(filename,"",800,800)

    dy = 0.05*len(hists)
    leg = ROOT.TLegend(0.18,0.86-dy,0.86,0.86)
    leg.SetTextSize(0.035)
    leg.SetBorderSize(0)

    ymax = 0
    for i,hist in enumerate(hists): 
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

def compareMass(temp,mDark,decay,dist):
    mMeds = []
    mMeds.append(125)
    mMeds.append(400)
    mMeds.append(750)
    mMeds.append(1000)

    hists = []
    labels = []
    for mMed in mMeds:
        histname = "mMed-{}_mDark-{}_temp-{}_decay-{}_{}".format(mMed,mDark,temp,decay,dist)
        #print(histname)
        hists.append(get1D(mMed,mDark,temp,decay,histname))
        labels.append(label(mMed,mDark,temp,decay))

    #if "scalar" not in dist and "jet" not in dist and "evtshape" not in dist: 
    hists.append(getQCD(dist))
    labels.append("QCD")
    
    compare1D(hists,labels,"compare_mMed/temp{}_mDark{}_decay_{}_{}".format(temp,mDark,decay,histname))
    #if histname=="h_pf_ntracks": 
    if doROC(histname)  : makeROC(hists,labels,"roc_curve/temp{}_mDark{}_decay_{}_{}".format(temp,mDark,decay,histname))

def compareDecay(mMed,temp,mDark,dist):
    decays = []
    decays.append("darkPho")
    decays.append("darkPhoHad")
    decays.append("generic")

    hists = []
    labels = []
    for decay in decays:
        histname = "mMed-{}_mDark-{}_temp-{}_decay-{}_{}".format(mMed,mDark,temp,decay,dist)
        hists.append(get1D(mMed,mDark,temp,decay,histname))
        labels.append(label(mMed,mDark,temp,decay))
 
    #hists.append(getQCD(histname))
    #labels.append("QCD, H_{T}>1 TeV")

    compare1D(hists,labels,"compare_decay/mMed{}_temp{}_mDark{}_{}".format(mMed,temp,mDark,histname))


sels = []
#sels.append("all")
sels.append("scouting")
sels.append("offline")

dists=[]

#dists.append("trig_isrjet_min_dR") 
#dists.append("trig_isrjet_pt") 
#dists.append("trig_isrjet_scalar_dPhi")    
#dists.append("trig_isrjet_scalar_dR")
#dists.append("trig_isrjet_isolation")
#dists.append("trig_isrjet_multiplicity")
#
#dists.append("trig_suepjet_min_dR") 
#dists.append("trig_suepjet_pt") 
#dists.append("trig_suepjet_scalar_dPhi")    
#dists.append("trig_suepjet_scalar_dR")
#dists.append("trig_suepjet_isolation")
#dists.append("trig_suepjet_multiplicity")


dists.append("evtshape_aplanarity")    
dists.append("evtshape_c")             
dists.append("evtshape_circularity")   
dists.append("evtshape_d")             
dists.append("evtshape_isotropy")      
dists.append("evtshape_sphericity")    
                    
dists.append("jetsAK20_constit_pt")    
dists.append("jetsAK20_dRscalar")      
dists.append("jetsAK20_eta")           
dists.append("jetsAK20_m")             
dists.append("jetsAK20_nconstit")      
dists.append("jetsAK20_njets")         
dists.append("jetsAK20_phi")           
dists.append("jetsAK20_pt")            
dists.append("jetsAK20_width")         

#dists.append("jetsAK15_suep_constit_pt")    
#dists.append("jetsAK15_suep_dRscalar")      
#dists.append("jetsAK15_suep_eta")           
#dists.append("jetsAK15_suep_m")             
#dists.append("jetsAK15_suep_nconstit")      
#dists.append("jetsAK15_suep_phi")           
#dists.append("jetsAK15_suep_pt")            
#dists.append("jetsAK15_suep_width") 

dists.append("jetsAK20_suep_constit_pt")    
dists.append("jetsAK20_suep_dRscalar")      
dists.append("jetsAK20_suep_eta")           
dists.append("jetsAK20_suep_m")             
dists.append("jetsAK20_suep_nconstit")      
dists.append("jetsAK20_suep_phi")           
dists.append("jetsAK20_suep_pt")            
dists.append("jetsAK20_suep_width")  

dists.append("nchpfs")                 
dists.append("nchpfs_07")              
dists.append("nchpfs_08")              
dists.append("nchpfs_09")              
dists.append("nchpfs_2") 

dists.append("ht")             
dists.append("njets")  
dists.append("leadjetpt")  

dists.append("scalar_eta")             
dists.append("scalar_m")               
dists.append("scalar_phi")             
dists.append("scalar_pt")              

for sel in sels: 
    for dist in dists:
        name=sel+"_"+dist
        compareMass(2,2,"darkPhoHad",name)
        #compareMass(2,2,"darkPho",name)
        compareMass(2,2,"generic",name)
        #compareDecay(750,2,2,name)
