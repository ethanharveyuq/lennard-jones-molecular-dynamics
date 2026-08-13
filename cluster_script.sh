#!/bin/bash
#SBATCH --job-name=milestone0
#SBATCH --ntasks=1
#SBATCH --nodes=1
#SBATCH --cpus-per-task=1
#SBATCH --time=00:05:00
#SBATCH --partition=cosc3500
#SBATCH --account=cosc3500

cmake --build build
build/md_serial grid --constant-temp --no-write 40 1.0 1.2 1.0 1.0 0.01 1.0 1.0 10.0 10.0