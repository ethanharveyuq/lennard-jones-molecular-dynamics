#pragma once
#include "system.h"

/**
 * @brief Compute the minimum-image displacement and distance between two particles.
 *
 * Applies periodic boundary conditions using the minimum-image convention.
 * The raw displacement between particles i and j is adjusted so that dx and dy
 * represent the shortest separation across the periodic domain.
 *
 * @param sys       System containing particle positions and box dimensions.
 * @param i         Index of the first particle.
 * @param j         Index of the second particle.
 * @param dx        Output: minimum-image x displacement.
 * @param dy        Output: minimum-image y displacement.
 * @param half_x    Half the sys.x_max (prevents recalc).
 * @param half_y    Half the sys.y_max (prevents recalc)
 *
 * @return The minimum-image distance squared between particles i and j.
 */
double min_image_distance(const System& sys, int i, int j, double& dx, double& dy, double x_half, double y_half);


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