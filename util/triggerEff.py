import ROOT
from array import array
from plothelper import *
ROOT.gROOT.SetBatch(ROOT.kTRUE)

setStyle()


def get1D(mMed,mDark,temp,decay,histname):

    # Get hist
    filename = "output/mMed-{}_mDark-{}_temp-{}_decay-{}.root".format(mMed,mDark,temp,decay)
    f = ROOT.TFile.Open(filename)
    hist = f.Get(histname)
    hist.SetDirectory(0)
    #clean1D(hist)

    return hist


def triggerEff(mMed,temp,mDark,decay,dist):

    num_name = "mMed-{}_mDark-{}_temp-{}_decay-{}_trig_{}".format(mMed,mDark,temp,decay,dist)
    den_name = "mMed-{}_mDark-{}_temp-{}_decay-{}_{}".format(mMed,mDark,temp,decay,dist)
    
    num_hist = get1D(mMed,mDark,temp,decay,num_name)
    den_hist = get1D(mMed,mDark,temp,decay,den_name)

    num = num_hist.Integral()
    den = den_hist.Integral()
    eff = num/den*100

    print("mMed-{}_mDark-{}_temp-{}_decay-{} : {:0.1f} ".format(mMed,mDark,temp,decay,eff) )


mMeds = []
mMeds.append(125)
mMeds.append(400)
mMeds.append(750)
mMeds.append(1000)

decays = []
decays.append("darkPho")
decays.append("darkPhoHad")
decays.append("generic")

mDark=2
temp=2
dist = "HT"
for decay in decays: 
	for mMed in mMeds: 
		triggerEff(mMed,temp,mDark,decay,dist)

