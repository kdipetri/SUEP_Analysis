# SUEP_Analysis

# How to setup on the LPC, slc7
* make a clean directory to start work
```
cd nobackup
mkdir SUEPs
cd SUEPs
```
* install analysis code (once):
```
wget https://raw.githubusercontent.com/kdipetri/SUEP_Analysis/cmssw/setup.sh
chmod +x setup.sh
./setup.sh
```
* setup environment (every time):
```
cd ~/nobackup/SUEPs/CMSSW_10_6_13/src/SUEP_Analysis
cmsenv
```

# Histogram Making Step
* A C++ event loop is used to make histograms
* There are helper scripts to make histograms, pack structures for physics objects, etc 
* FastJet is included to make fatjets from tracks in Root/jetStudies.C
* The event loop lives in Root/doHistos.C
```
./compile.sh 
./run.sh 
```

# Plot Making Step
* Some examples of how to make plots with signal shape comparisons or event displays can be found in utils
```
python util/make_plots.py
python util/make_displays.py
```

# Tips
* directories output, plots are used to store output histograms and output plots
* Double check location of rootfiles 

# Signal n-tuples live here
```
eosls /store/user/kdipetri/SUEP/Production_v0.1/2018/merged_NTUP
```
* There are 12 signal points, and each sample has 10k events
* There are three decay scenarios and 4 scalar masses
* The "darkPho" and "darkPhoHad" scenarios have full truth information 
* The "generic" decay scenarios don't have full truth info, but everything else is ok 
- scalar pdgId = 25
- dark meson pdgId = 999999
- dark photon pdgId = 999998

# QCD n-tuples live here
eosls /store/user/kdipetri/SUEP/Production_v0.0/2018/merged_NTUP
