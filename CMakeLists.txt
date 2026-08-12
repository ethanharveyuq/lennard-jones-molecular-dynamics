cmake_minimum_required(VERSION 3.10)
project(lj_md CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
add_executable(md_serial
    src/main.cpp
    src/system.cpp
    src/forces.cpp
    src/integrate.cpp
)