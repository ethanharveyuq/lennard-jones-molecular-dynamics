#include "../include/forces.h"

double min_image_distance(const System& sys, int i, int j, double& dx, double& dy, double x_half, double y_half) 
{
    // Raw displacement between particles i and j
    double dx_raw = sys.x[i] - sys.x[j];
    double dy_raw = sys.y[i] - sys.y[j];

    // Apply minimum-image convention in x-direction
    // If the displacement crosses more than half the box,
    // wrap it back into the nearest periodic image.
    if (dx_raw > x_half) dx_raw -= sys.x_max;
    else if (dx_raw < -x_half) dx_raw += sys.x_max;

    // same logic for y direction
    if (dy_raw > y_half) dy_raw -= sys.y_max;
    else if (dy_raw < -y_half) dy_raw += sys.y_max;

    // store the correct distances
    dx = dx_raw;
    dy = dy_raw;

    // Return Euclidean distance squared using minimum-image dx, dy
    return (dx * dx) + (dy * dy);
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

    // orevents recalculations
    double cutoff_dist2 = cutoff_dist * cutoff_dist;
    double sigma2 = sigma * sigma;
    double x_half = 0.5 * sys.x_max;
    double y_half = 0.5 * sys.y_max;

    // Loop over all particle pairs (i,j)
    for (int i = 0; i < sys.n; i++) {
        for (int j = 0; j < sys.n; j++) {

            // Skip self interaction
            if (i == j) continue;

            // Compute min-image distance and displacement
            double dx, dy;
            double dist2 = min_image_distance(sys, i, j, dx, dy, x_half, y_half);

            // Ignore interactions beyond the cutoff
            if (dist2 > cutoff_dist2) continue;

            // Compute LJ force magnitude
            // Compute (sigma/r)^6 and (sigma/r)^12 efficiently
            double inv_r2 = 1.0 / dist2; // Prevents multiple divisions
            double sor2 = (sigma2) * inv_r2;
            double sor6 = sor2 * sor2 * sor2; // Avoiding pow function
            double sor12 = sor6 * sor6;

            // Standard unit Lennard-Jones force magnitude (F/r)
            double F = 24 * bond_strength * (2 * sor12 - sor6) * inv_r2;



            // Convert scalar force to vector components
            double Fx = F * dx;
            double Fy = F * dy;

            // Accumulate the force on particle i
            fx_new[i] += Fx;
            fy_new[i] += Fy;
        }
    }
}