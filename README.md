# SUEP_Analysis

# How to setup on the LPC
* make a clean directory to start work
$ cd nobackup
$ mkdir SUEPs
$ cd SUEPs
$ git clone https://github.com/kdipetri/SUEP_Analysis.git
* install fastjet in SUEPs directory, following these directions http://fastjet.fr/quickstart.html
$ cd SUEP_Analysis
$ source setup.sh 
* setup 

# Histogram Making Step
* A C++ event loop is used to make histograms
* There are helper scripts to make histograms, pack structures for physics objects, etc 
* FastJet is included to make fatjets from tracks in Root/jetStudies.C
* The event loop lives in Root/doHistos.C
$ source compile.sh 
$ source run.sh 

# Plot Making Step
* Some examples of how to make plots with signal shape comparisons or event displays can be found in utils
$ python util/make_plots.py
$ python util/make_displays.py

# Tips
* Be sure to make output, plot directories to store output histograms and output plots
* Double check location of rootfiles 

# Signal n-tuples live here
eosls /store/user/kdipetri/SUEP/Production_v0.0/2018/merged_NTUP
* there are 12 signal points, and each sample has 10k events
* There are three decay scenarios and 4 scalar masses
* Let's focus on the “generic” decay scenario first

