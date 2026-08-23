#include "../include/integrate.h"
#include <cmath>



void move(System& sys, double dt)
{
    // Position update (Velocity-Verlet first half-step):
    // x(t+dt) = x(t) + v(t)*dt + 0.5*a(t)*dt^2
    // where a(t) = F(t) / m. Here mass = 1 in reduced LJ units.

    double dt2 = dt * dt;
    double half_dt2 = 0.5 * dt2;

    for (int i = 0; i < sys.n; i++) {

        // update x position
        // x(t+dt) = x + vx*dt + 0.5*fx*dt^2
        double x_new = std::fma(sys.vx[i], dt, sys.x[i]);
        x_new = std::fma(half_dt2, sys.fx[i], x_new);
        sys.x[i] = x_new;

        // Apply wraparound logic to x pos
        if (sys.x[i] >= sys.x_max)  sys.x[i] -= sys.x_max;
        if (sys.x[i] < 0)           sys.x[i] += sys.x_max;

        // update y position
        double y_new = std::fma(sys.vy[i], dt, sys.y[i]);
        y_new = std::fma(half_dt2, sys.fy[i], y_new);
        sys.y[i] = y_new;

        // apply periodic bounding to y pos
        if (sys.y[i] >= sys.y_max)  sys.y[i] -= sys.y_max;
        else if (sys.y[i] < 0)      sys.y[i] += sys.y_max;
    }
}

void update_velocities(System& sys, 
    const std::vector<double>& fx_new, 
    const std::vector<double>& fy_new, 
    double dt) 
{
    // Velocity update (Velocity-Verlet second half-step):
    // v(t+dt) = v(t) + 0.5*(F_old + F_new)*dt
    // Uses both the old forces stored in sys.fx/sys.fy and the newly computed ones.
    double half_dt = 0.5 * dt;

    for (int i = 0 ; i < sys.n; i++) {

        // Update x-velocity
        // v(t+dt) = v + 0.5*(F_old + F_new)*dt
        double fx_sum = sys.fx[i] + fx_new[i];
        sys.vx[i] = std::fma(half_dt, fx_sum, sys.vx[i]);

        // Update y velocity
        double fy_sum = sys.fy[i] + fy_new[i];
        sys.vy[i] = std::fma(half_dt, fy_sum, sys.vy[i]);
    }
}