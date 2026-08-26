#pragma once
#include <vector>
#include <string>

/**
 * @brief Structure holding all particle and simulation state.
 *
 * Stores positions, velocities, forces, particle count, and box dimensions.
 * All arrays (x, y, vx, vy, fx, fy) are assumed to have size n.
 *
 * Fields:
 *   n      - number of particles
 *   x,y    - particle positions
 *   vx,vy  - particle velocities
 *   fx,fy  - particle forces
 *   x_max  - simulation box size in x-direction
 *   y_max  - simulation box size in y-direction
 *   x_half - simulation box half length (used in min-image-dist)
 *   y_half - simulation box half length
 */
struct System {
    int n;
    double x_max, y_max, x_half, y_half;
    std::vector<double> x, y, vx, vy, fx, fy;
};


/**
 * @brief Initialise particle positions according to a chosen arrangement.
 *
 * Supported arrangements:
 *   - "random": particles placed uniformly at random, avoiding overlaps.
 *   - "hex":    particles placed on a hexagonal lattice and centred in the box.
 *
 * @param sys         System to initialise.
 * @param n           Number of particles.
 * @param arrangement String specifying arrangement type ("random" or "grid").
 * @param r_min       Minimum allowed separation between particles.
 * @param x_max       Box size in x-direction.
 * @param y_max       Box size in y-direction.
 */
void setup_atoms(System& sys, int n, const std::string& arrangement, double r_min, double x_max, double y_max);


/**
 * @brief Check whether a proposed particle position overlaps existing particles.
 *
 * @param sys   System containing existing particle positions.
 * @param r_min Minimum allowed separation.
 * @param x,y   Proposed new particle position.
 *
 * @return true if no overlaps occur; false otherwise.
 */
bool no_overlaps(System& sys, double r_min, double x, double y);


/**
 * @brief Initialise particle velocities from a Maxwell-Boltzmann distribution.
 *
 * Samples velocities from a normal distribution with variance kB*T/m,
 * removes centre-of-mass drift, and rescales velocities to match the
 * target temperature.
 *
 * @param sys   System containing particle velocities.
 * @param temp  Target temperature.
 * @param Kb    Boltzmann constant.
 */
void init_velocities(System& sys, double temp, double Kb);


/**
 * @brief Compute the instantaneous temperature from kinetic energy.
 *
 * Uses equipartition: T = 2K / (f kB), with f = 2N in 2D.
 *
 * @param sys System containing velocities.
 * @param Kb  Boltzmann constant.
 *
 * @return Instantaneous temperature.
 */
double current_temp(const System& sys, double Kb);


/**
 * @brief Rescale velocities to match a target temperature.
 *
 * Computes current temperature, determines scaling factor lambda,
 * and multiplies all velocities by lambda.
 *
 * @param sys         System containing velocities.
 * @param target_temp Desired temperature.
 * @param Kb          Boltzmann constant.
 */
void scale_velocities(System& sys, double target_temp, double Kb);
