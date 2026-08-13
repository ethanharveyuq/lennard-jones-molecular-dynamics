#pragma once
#include <vector>

struct System {
    int n;
    double x_max, y_max;
    double box_length;
    std::vector<double> x, y, vx, vy, fx, fy;
    std::vector<double> sigma;
};

void setup_atoms(System& sys, int n, const std::string& arrangement, double sigma_val, double r_min, double x_max, double y_max);
bool no_overlaps(System& sys, double r_min, double x, double y);
void init_velocities(System& sys, double temp, double Kb);
double current_temp(const System& sys, double Kb);
void scale_velocities(System& sys, double target_temp, double Kb);