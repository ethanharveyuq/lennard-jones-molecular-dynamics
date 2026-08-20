#include "system.h"


/**
 * @brief Advance particle positions using the Velocity-Verlet integrator.
 *
 * Updates positions according to:
 *     x(t + dt) = x(t) + v(t)*dt + 0.5*a(t)*dt^2
 *
 * Periodic boundary conditions are applied by wrapping positions into
 * the domain [0, x_max) × [0, y_max).
 *
 * @param sys  System containing particle positions, velocities, forces, and box size.
 * @param dt   Time step for the integration.
 */
void move(System& sys, double dt);


/**
 * @brief Update particle velocities using the Velocity-Verlet integrator.
 *
 * Velocities are updated using both old and newly computed forces:
 *     v(t + dt) = v(t) + 0.5*(F_old + F_new)*dt
 *
 * This completes the second half-step of the Velocity-Verlet scheme.
 *
 * @param sys      System containing particle velocities and old forces.
 * @param fx_new   Newly computed x-components of forces.
 * @param fy_new   Newly computed y-components of forces.
 * @param dt       Time step for the integration.
 */
void update_velocities(System& sys, const std::vector<double>& fx_new,
                        const std::vector<double>& fy_new, double dt);