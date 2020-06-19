g++ -I $PWD -Wno-deprecated $(root-config --cflags --libs) $($PWD/../fastjet-install/bin/fastjet-config --cxxflags --libs --plugins) -o doHistos Root/doHistos.C
#g++ -I $PWD -Wall $(root-config --cflags --libs) $($PWD/../fastjet-install/bin/fastjet-config --cxxflags --libs --plugins) -o doHistos Root/doHistos.C
