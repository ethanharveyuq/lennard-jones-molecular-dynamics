#include "../include/forces.h"
#include <cmath>

double min_image_distance(const System& sys, int i, int j, double& dx, double& dy) {
    // currently only calculates raw distance
    double dx_raw = sys.x[i] - sys.x[j];
    double dy_raw = sys.y[i] - sys.y[j];
    if (dx_raw > 5) dx_raw -= 10;
    else if (dx_raw < -5) dx_raw += 10;
    if (dy_raw > 5) dy_raw -= 10;
    else if (dy_raw < -5) dy_raw += 10;
    dx = dx_raw;
    dy = dy_raw;

    return sqrt((dx * dx) + (dy * dy));
}


double calc_force(double r, double sigma, double bond_strength) {
    return 24 * bond_strength * (2 * pow(sigma / r, 12) - pow(sigma / r, 6)) / r;
}


void compute_forces(const System& sys,
    double bond_strength,
    double cutoff_dist,
    double sigma,
    std::vector<double>& fx_new,
    std::vector<double>& fy_new)
{
    fx_new.assign(sys.n, 0.0);
    fy_new.assign(sys.n, 0.0);

    for (int i = 0; i < sys.n; i++) {
        for (int j = 0; j < sys.n; j++) {
            if (i == j) {
                continue;
            }
            double dx, dy;
            double dist = min_image_distance(sys, i, j, dx, dy);
            if (dist > cutoff_dist) {
                continue;
            }
            double F = calc_force(dist, sigma, bond_strength);
            double Fx = F * dx / dist;
            double Fy = F * dy / dist;
            fx_new[i] += Fx;
            fy_new[i] += Fy;
        }
    }

}