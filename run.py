import subprocess

filepath="root://cmseos.fnal.gov//store/user/kdipetri/SUEP/Production_v0.0/2018/merged_NTUP"

samples=[]
samples.append("mMed-1000_mDark-2_temp-2_decay-darkPhoHad") 
samples.append("mMed-1000_mDark-2_temp-2_decay-darkPho") 
samples.append("mMed-1000_mDark-2_temp-2_decay-generic") 
samples.append("mMed-125_mDark-2_temp-2_decay-darkPhoHad") 
samples.append("mMed-125_mDark-2_temp-2_decay-darkPho") 
samples.append("mMed-125_mDark-2_temp-2_decay-generic") 
samples.append("mMed-400_mDark-2_temp-2_decay-darkPhoHad") 
samples.append("mMed-400_mDark-2_temp-2_decay-darkPho") 
samples.append("mMed-400_mDark-2_temp-2_decay-generic") 
samples.append("mMed-750_mDark-2_temp-2_decay-darkPhoHad") 
samples.append("mMed-750_mDark-2_temp-2_decay-darkPho") 
samples.append("mMed-750_mDark-2_temp-2_decay-generic") 
samples.append("QCD_HT1000to1500")
samples.append("QCD_HT1500to2000")
samples.append("QCD_HT2000toInf")
samples.append("QCD_HT200to300")
samples.append("QCD_HT300to500")
samples.append("QCD_HT500to700")
samples.append("QCD_HT700to1000")

def get_filename(sample):
    if "mMed" in sample: return "{}/SUEP_2018_{}_13TeV-pythia8_AnalysisTree.root".format(filepath,sample)
    elif "QCD" in sample: return "{}/{}_TuneCP5_13TeV-madgraphMLM-pythia8_AnalysisTree.root".format(filepath,sample)
    else : return "{}/{}.root".format(filepath,sample)

for sample in samples:
    filename = get_filename(sample) 
    print "./doHistos {} {}".format(sample,filename)

#QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8_AnalysisTree.root
