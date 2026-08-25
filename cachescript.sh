#!/bin/bash
#SBATCH --job-name=cache_profile
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --time=00:05:00
#SBATCH --partition=cosc3500
#SBATCH --account=cosc3500

module load perf   # if Rangpur requires it

cmake --build build

perf stat -e cache-misses,cache-references,cycles,instructions \
    build/md_serial grid --constant-temp --write 128 1.0 1.2 1.0 1.0 0.01 1.0 1.0 50.0 50.0
