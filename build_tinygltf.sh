cd tinygltf
if [ ! -d "build" ]; then
  mkdir build
else
  rm -rf build
  mkdir build
fi
cd build
cmake -DCMAKE_PREFIX_PATH=./engine -S ../ -B .
cmd /k