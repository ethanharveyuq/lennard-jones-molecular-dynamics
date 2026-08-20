#include "../include/integrate.h"


void move(System& sys, double dt)
{
    // Position update (Velocity-Verlet first half-step):
    // x(t+dt) = x(t) + v(t)*dt + 0.5*a(t)*dt^2
    // where a(t) = F(t) / m. Here mass = 1 in reduced LJ units.

    double dt2 = dt * dt;
    for (int i = 0; i < sys.n; i++) {
        // update x position
        sys.x[i] = sys.x[i] + sys.vx[i] * dt + 0.5 * sys.fx[i] * dt2;

        // Apply wraparound logic to x pos
        if (sys.x[i] >= sys.x_max) sys.x[i] -= sys.x_max;
        if (sys.x[i] < 0) sys.x[i] += sys.x_max;

        // update y position
        sys.y[i] = sys.y[i] + sys.vy[i] * dt + 0.5 * sys.fy[i] * dt2;

        // apply periodic bounding to y pos
        if (sys.y[i] >= sys.y_max) sys.y[i] -= sys.y_max;
        else if (sys.y[i] < 0) sys.y[i] += sys.y_max;
    }
}

void update_velocities(System& sys, const std::vector<double>& fx_new, const std::vector<double>& fy_new, double dt) 
{
    // Velocity update (Velocity-Verlet second half-step):
    // v(t+dt) = v(t) + 0.5*(F_old + F_new)*dt
    // Uses both the old forces stored in sys.fx/sys.fy and the newly computed ones.

    for (int i = 0 ; i < sys.n; i++) {

        // Update x-velocity
        sys.vx[i] = sys.vx[i] + 0.5 * (sys.fx[i] + fx_new[i]) * dt;

        // Update y velocity
        sys.vy[i] = sys.vy[i] + 0.5 * (sys.fy[i] + fy_new[i]) * dt;
    }
}