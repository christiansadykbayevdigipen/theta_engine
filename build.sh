cmake -S theta/src -B theta/build

cd theta 
cd build
make
cd ..
cd ..

cmake -S sandbox/src -B sandbox/build
cd sandbox
cd build
make
cd ..
cd ..

rm -rf sandbox/build/res
cp theta/build/libtheta.so sandbox/build/libtheta.so
mkdir sandbox/build/res
cp -r res sandbox/build/