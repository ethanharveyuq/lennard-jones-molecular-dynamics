#!/bin/bash
#SBATCH --job-name=milestone0
#SBATCH --output=milestone0_%j.out
#SBATCH --ntasks=1
#SBATCH --nodes=1
#SBATCH --cpus-per-task=1
#SBATCH --time=00:05:00
#SBATCH --partition=cosc3500
#SBATCH --account=cosc3500

g++ -O2 -o md_project main.cpp
./md_project
