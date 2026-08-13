cmake_minimum_required(VERSION 3.10)
project(lj_md CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -pg")
set(CMAKE_EXE_LINKER_FLAGS "-pg")
add_executable(md_serial
    src/main.cpp
    src/system.cpp
    src/forces.cpp
    src/integrate.cpp
)