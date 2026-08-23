#include "../include/forces.h"

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
        // cache memory rather than conitnually reference
        const double xi = sys.x[i];
        const double yi = sys.y[i];
        
        for (int j = i + 1; j < sys.n; j++) {
            // Compute min-image distance and displacement
            // Raw displacement between particles i and j
            double dx = xi - sys.x[j];
            double dy = yi - sys.y[j];

            // Apply minimum-image convention in x-direction
            // If the displacement crosses more than half the box,
            // wrap it back into the nearest periodic image.
            if (dx > sys.x_half) dx -= sys.x_max;
            else if (dx < -sys.x_half) dx += sys.x_max;

            // same logic for y direction
            if (dy > sys.y_half) dy -= sys.y_max;
            else if (dy < -sys.y_half) dy += sys.y_max;

            // Euclidean distance squared using minimum-image dx, dy
            double dist2 = (dx * dx) + (dy * dy);

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
            fx_new[j] -= Fx;
            fy_new[j] -= Fy;
        }
    }
}