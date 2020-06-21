g++ -I $PWD -Wno-deprecated $(root-config --cflags --libs) $(~/Documents/fastjet-install/bin/fastjet-config --cxxflags --libs --plugins) -o doHistos Root/doHistos.C
