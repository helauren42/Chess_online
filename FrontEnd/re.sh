rm a.out
qmake6 Qt.pro
make -j$(nproc)
nohup ./a.out &
