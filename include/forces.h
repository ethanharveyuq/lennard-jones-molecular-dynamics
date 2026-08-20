#pragma once
#include "system.h"

/**
 * @brief Compute the minimum-image displacement and distance between two particles.
 *
 * Applies periodic boundary conditions using the minimum-image convention.
 * The raw displacement between particles i and j is adjusted so that dx and dy
 * represent the shortest separation across the periodic domain.
 *
 * @param sys   System containing particle positions and box dimensions.
 * @param i     Index of the first particle.
 * @param j     Index of the second particle.
 * @param dx    Output: minimum-image x displacement.
 * @param dy    Output: minimum-image y displacement.
 *
 * @return The minimum-image distance between particles i and j.
 */
double min_image_distance(const System& sys, int i, int j, double& dx, double& dy);


/**
 * @brief Compute the Lennard-Jones force magnitude between two particles.
 *
 * Uses the standard LJ force expression:
 *     F(r) = 24 * epsilon * (2*(sigma/r)^12 - (sigma/r)^6) / r
 *
 * @param r             Separation distance between particles.
 * @param sigma         Lennard-Jones size parameter.
 * @param bond_strength Lennard-Jones epsilon (interaction strength).
 *
 * @return The scalar force magnitude F(r).
 */
double calc_force(double r, double sigma, double bond_strength);


/**
 * @brief Compute all pairwise Lennard-Jones forces in the system.
 *
 * Applies the minimum-image convention and ignores interactions beyond
 * the specified cutoff distance. The resulting force components are written
 * into fx_new and fy_new.
 *
 * @param sys          System containing particle positions and box dimensions.
 * @param bond_strength Lennard-Jones epsilon (interaction strength).
 * @param cutoff_dist   Distance beyond which interactions are ignored.
 * @param sigma         Lennard-Jones size parameter.
 * @param fx_new        Output: x-components of forces on each particle.
 * @param fy_new        Output: y-components of forces on each particle.
 */
void compute_forces(const System& sys,
    double bond_strength,
    double cutoff_dist,
    double sigma,
    std::vector<double>& fx_new,
    std::vector<double>& fy_new);