#!/bin/bash -e

export SCRAM_ARCH=slc7_amd64_gcc700
# cmd below is cmsrel
scram project CMSSW_10_6_13
cd CMSSW_10_6_13/src/
# cmd below is cmsenv
eval `scram runtime -sh`
git clone https://github.com/kdipetri/SUEP_Analysis -b cmssw
cd SUEP_Analysis
./compile.sh
