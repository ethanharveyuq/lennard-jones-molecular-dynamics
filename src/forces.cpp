#include "../include/forces.h"
#include <cmath>

double min_image_distance(const System& sys, int i, int j, double& dx, double& dy) 
{
    // Raw displacement between particles i and j
    double dx_raw = sys.x[i] - sys.x[j];
    double dy_raw = sys.y[i] - sys.y[j];

    // Apply minimum-image convention in x-direction
    // If the displacement crosses more than half the box,
    // wrap it back into the nearest periodic image.
    if (dx_raw > sys.x_max / 2) dx_raw -= sys.x_max;
    else if (dx_raw < - sys.x_max / 2) dx_raw += sys.x_max;

    // same logic for y direction
    if (dy_raw > sys.y_max / 2) dy_raw -= sys.y_max;
    else if (dy_raw < - sys.x_max / 2) dy_raw += sys.y_max;

    // store the correct distances
    dx = dx_raw;
    dy = dy_raw;

    // Return Euclidean distance using minimum-image dx, dy
    return sqrt((dx * dx) + (dy * dy));
}


double calc_force(double r, double sigma, double bond_strength) 
{
    // Compute (sigma/r)^6 and (sigma/r)^12 efficiently
    double sor = sigma / r;
    double sor6 = sor * sor * sor * sor * sor * sor;
    double sor12 = sor6 * sor6;

    // Standard Lennard-Jones force magnitude
    return 24 * bond_strength * (2 * sor12 - sor6) / r;
}


void compute_forces(const System& sys,
    double bond_strength,
    double cutoff_dist,
    double sigma,
    std::vector<double>& fx_new,
    std::vector<double>& fy_new)
{
    // Reset force arrays to zero for this timestep
    fx_new.assign(sys.n, 0.0);
    fy_new.assign(sys.n, 0.0);

    // Loop over all particle pairs (i,j)
    for (int i = 0; i < sys.n; i++) {
        for (int j = 0; j < sys.n; j++) {

            // Skip self interaction
            if (i == j) continue;

            //Compute min-image distance and displacement
            double dx, dy;
            double dist = min_image_distance(sys, i, j, dx, dy);

            // Ignore interactions beyond the cutoff
            if (dist > cutoff_dist) continue;

            // Compute LJ force magnitude
            double F = calc_force(dist, sigma, bond_strength);

            // Convert scalar force to vector comps
            double Fx = F * dx / dist;
            double Fy = F * dy / dist;

            // Accumulate the force on particle i
            fx_new[i] += Fx;
            fy_new[i] += Fy;
        }
    }
}