g++ -I $PWD -Wno-deprecated $(root-config --cflags --libs) $($PWD/../fastjet-install/bin/fastjet-config --cxxflags --libs --plugins) -lVariableRPlugin -o doHistos Root/doHistos.C
