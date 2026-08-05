#pragma once
#include "system.h"

double min_image_distance(const System& sys, int i, int j, double& dx, double& dy);
double calc_force(double r, double sigma, double bond_strength);
void compute_forces(const System& sys,
    double bond_strength,
    double cutoff_dist,
    std::vector<double>& fx_new,
    std::vector<double>& fy_new);