# ------------------------------------------------------------------------------
# CMake configuration for the 2D Lennard‑Jones molecular dynamics simulation.
#
# This file configures the build system, sets compiler options, and defines
# the md_serial executable. The code is compiled with:
#   - C++17 standard
#   - Ox optimi
#   - gprof instrumentation (-pg) for profiling
#
# Source files:
#   src/main.cpp       – program entry point and simulation loop
#   src/system.cpp     – system data structure and initialisation
#   src/forces.cpp     – Lennard‑Jones force calculations
#   src/integrate.cpp  – Velocity‑Verlet integrator
#   src/io.cpp         - Handles output file writing
# ------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.10)
project(lj_md CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-pg")
set(CMAKE_EXE_LINKER_FLAGS "-pg")
add_executable(md_serial
    src/main.cpp
    src/system.cpp
    src/forces.cpp
    src/integrate.cpp
    src/io.cpp
)
