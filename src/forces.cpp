#include "../include/forces.h"
#include <cmath>

const double SIGMA = 1.0;
const double EPSILON = 1.0;

double min_image_distance(const System& sys, int i, int j, double& dx, double& dy) {
    // currently only calculates raw distance
    dx = sys.x[i] - sys.x[j];
    dy = sys.y[i] - sys.y[j];
    return sqrt((dx * dx) + (dy * dy));
}


double calc_force(double r, double sigma, double bond_strength) {
    return 24 * bond_strength * (2 * pow(sigma / r, 12) - pow(sigma / r, 6)) / r;
}


void compute_forces(const System& sys,
    double bond_strength,
    double cutoff_dist,
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
            double F = calc_force(dist, SIGMA, EPSILON);
            double Fx = F * dx / dist;
            double Fy = F * dy / dist;
            fx_new[i] += Fx;
            fy_new[i] += Fy;
        }
    }

}