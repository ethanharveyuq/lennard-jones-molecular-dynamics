#include "system.h"
#include <iostream>
#include <ostream>

/**
 * @brief Write particle positions to an output file for a single MD timestep.
 *
 * Outputs one CSV line per particle in the format:
 *     step, particle_index, x_position, y_position
 *
 * @param sys   System containing particle positions.
 * @param step  Current simulation timestep.
 * @param out   Open output file stream to append data to.
 */
void write_output(const System& sys, int step, std::ofstream& out);