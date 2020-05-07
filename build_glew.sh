cd glew
cd auto 
make
cd ..
./cmake-testbuild.sh
cp -r ./out/bin/glew*.dll ../engine/lib/
cp -r ./out/include/* ../engine/include/