#pragma once
#include "system.h"

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