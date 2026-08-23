#!/bin/bash
# ------------------------------------------------------------------------------
# SLURM job script for running the 2D Lennard‑Jones MD simulation on UQ HPC.
#
# Job configuration:
#   --job-name       Name of the job in SLURM queue
#   --ntasks         Number of MPI tasks (1 for serial MD)
#   --nodes          Number of nodes requested
#   --cpus-per-task  CPU cores per task
#   --time           Maximum wall time
#   --partition      Teaching partition for COSC3500
#   --account        Course account for job charging
#
# Workflow:
#   1. Build the md_serial executable using CMake.
#   2. Run the simulation with chosen parameters.
#   3. Run gprof on the output and stores in profile.txt.
# ------------------------------------------------------------------------------

#SBATCH --job-name=milestone0
#SBATCH --ntasks=1
#SBATCH --nodes=1
#SBATCH --cpus-per-task=1
#SBATCH --time=00:05:00
#SBATCH --partition=cosc3500
#SBATCH --account=cosc3500

cmake -S . -B build
cmake --build build
./build/md_serial grid --constant-temp --no-write 40 1.0 1.2 1.0 1.0 0.01 1.0 1.0 10.0 10.0
gprof build/md_serial gmon.out > profile.txt
