#include "../include/forces.h"
#include <cmath>

double min_image_distance(const System& sys, int i, int j, double& dx, double& dy) {
    // currently only calculates raw distance
    double dx_raw = sys.vx[i] - sys.vx[j];
    double dy_raw = sys.vy[i] - sys.vy[j];
    return sqrt(dx_raw * dx_raw + dy_raw * dy_raw);
}


double calc_force(double r, double sigma, double bond_strength) {
    return 24 * bond_strength * (2 * pow(sigma / r, 12) - pow(sigma / r, 6)) / r;
}


void compute_forces(const System& sys, double bond_strength, double cutoff_dist,
                     std::vector<double>& fx_new, std::vector<double>& fy_new) {

}