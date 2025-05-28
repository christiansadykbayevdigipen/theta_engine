cmake -S cimgui -B cimgui_build -DIMGUI_STATIC=yes

cd cimgui_build
make
mv cimgui.a libcimgui.a
cd ..