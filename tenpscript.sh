cmake -S . -B build
cmake --build build
./build/md_serial grid --constant-temp --no-write 40 1.0 1.2 1.0 1.0 0.01 1.0 1.0 10.0 10.0
gprof build/md_serial gmon.out > profile.txt
