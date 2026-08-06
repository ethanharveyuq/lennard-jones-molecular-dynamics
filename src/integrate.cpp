#include "../include/integrate.h"
#include <cmath>

// uses velocity verlet

void move(System& sys, double dt) {
    for (int i = 0; i < sys.n; i++) {
        sys.x[i] = sys.x[i] + sys.vx[i] * dt + 0.5 * sys.fx[i] * dt * dt;
        sys.x[i] = std::fmod(sys.x[i], 10.0);
        sys.y[i] = sys.y[i] + sys.vy[i] * dt + 0.5 * sys.fy[i] * dt * dt;
        sys.y[i] = std::fmod(sys.y[i], 10.0);
    }

}

void update_velocities(System& sys, const std::vector<double>& fx_new, const std::vector<double>& fy_new, double dt) {
    for (int i = 0 ; i < sys.n; i++) {
        sys.vx[i] = sys.vx[i] + 0.5 * (sys.fx[i] + fx_new[i]) * dt;
        sys.vy[i] = sys.vy[i] + 0.5 * (sys.fy[i] + fy_new[i]) * dt;
    }
}