#!/bin/bash

# get fastjet info
eval $(scram tool info fastjet | grep "FASTJET_BASE=")

g++ -I $PWD -Wno-deprecated $(root-config --cflags --libs) $($FASTJET_BASE/bin/fastjet-config --cxxflags --libs --plugins) -o doHistos Root/doHistos.C
