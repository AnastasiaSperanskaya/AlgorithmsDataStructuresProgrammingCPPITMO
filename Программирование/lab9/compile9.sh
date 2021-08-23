rm lab9.out
export PKG_CONFIG_PATH="/usr/local/opt/libffi/lib/pkgconfig:/usr/local/opt/libxml2/lib/pkgconfig"
clang++ $(pkg-config libxml++-2.6 --cflags --libs) -lcurl main.cpp -o lab9.out -std=c++11 -Wno-inconsistent-missing-override
chmod +x lab9.out
./lab9.out $@