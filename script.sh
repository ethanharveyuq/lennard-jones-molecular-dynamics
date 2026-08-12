#!/bin/bash
#SBATCH --job-name=milestone0
#SBATCH --ntasks=1
#SBATCH --nodes=1
#SBATCH --cpus-per-task=1
#SBATCH --time=00:05:00
#SBATCH --partition=cosc3500
#SBATCH --account=cosc3500

cd build
cmake --build .
./md_serial random 20 1.0 1.0 1.0 1.0 0.1 1.0 1.0
