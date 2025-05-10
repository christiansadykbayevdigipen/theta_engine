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

cp theta/build/libtheta.so sandbox/build/libtheta.so
cp res/*.* sandbox/build/res/