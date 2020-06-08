g++ -I ~/Documents/Fermilab/SUEP/SUEP_Analysis -Wall $(root-config --cflags --libs) $(~/Documents/fastjet-install/bin/fastjet-config --cxxflags --libs --plugins) -o doHistos Root/doHistos.C
