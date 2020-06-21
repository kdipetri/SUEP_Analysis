g++ -I $PWD -Wno-deprecated $(root-config --cflags --libs) $(PWD/../fastjet-install/bin/fastjet-config --cxxflags --libs --plugins) -o doHistos Root/doHistos.C
