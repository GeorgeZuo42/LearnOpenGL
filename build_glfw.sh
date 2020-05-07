cd glfw
if [ ! -d "build" ]; then
  mkdir build
else
  rm -rf build
  mkdir build
fi
cd build
cmake -DBUILD_SHARED_LIBS=ON -S ../ -B .
