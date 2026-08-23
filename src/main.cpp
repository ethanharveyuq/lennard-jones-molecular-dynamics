#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "../include/forces.h"
#include "../include/system.h"
#include "../include/integrate.h"
#include "../include/io.h"

/**
 * @brief Entry point for the 2D Lennard‑Jones molecular dynamics simulation.
 *
 * This program sets up a particle system, initialises positions and velocities,
 * computes forces using the Lennard‑Jones potential, and integrates motion using
 * the Velocity‑Verlet scheme. Optional temperature control and trajectory output
 * can be enabled via command‑line arguments.
 *
 * Command‑line arguments:
 *   argv[1]  <arrangement>
 *            Particle placement mode:
 *              "random"  – random positions with overlap rejection
 *              "hex"     – hexagonal lattice centred in the box
 *
 *   argv[2]  <constant-temp>
 *            "--constant-temp" to enable velocity rescaling each timestep.
 *
 *   argv[3]  <write>
 *            "--write" to output trajectory data to output.csv.
 *
 *   argv[4]  <n>
 *            Number of particles.
 *
 *   argv[5]  <sigma>
 *            Lennard‑Jones sigma parameter.
 *
 *   argv[6]  <min_dist>
 *            Minimum allowed particle separation during setup.
 *
 *   argv[7]  <temp>
 *            Target temperature for initialisation (and rescaling if enabled).
 *
 *   argv[8]  <Kb>
 *            Boltzmann constant.
 *
 *   argv[9]  <dt>
 *            Integration timestep.
 *
 *   argv[10] <bond_strength>
 *            Lennard‑Jones epsilon parameter (interaction strength).
 *
 *   argv[11] <cutoff_dist>
 *            Distance beyond which LJ interactions are ignored.
 *
 *   argv[12] <x_max>
 *   argv[13] <y_max>
 *            Simulation box dimensions.
 *
 * Simulation workflow:
 *   1. Parse command‑line arguments.
 *   2. Initialise particle positions (random or hexagonal).
 *   3. Initialise velocities from Maxwell‑Boltzmann distribution.
 *   4. For each timestep:
 *        - Update positions (Velocity‑Verlet half‑step).
 *        - Compute new forces.
 *        - Update velocities (Velocity‑Verlet second half‑step).
 *        - Optionally rescale velocities to maintain constant temperature.
 *        - Optionally write particle positions to CSV.
 *
 * Output:
 *   If "--write" is enabled, a CSV file "output.csv" is produced containing:
 *       step, id, x, y
 *
 * @note All physical quantities are assumed to be in Lennard‑Jones reduced units.
 */
int main(int argc, char* argv[]) 
{
    // check all args are there
    if (argc < 13) {
        std::cerr << "Usage: " << argv[0]
                    << " <arrangement> <constant-temp> <write> <n> <sigma> <min_dist> <temp> <Kb> <dt> <bond_strength> <cutoff_dist>\n";
        return 1;
    }

    // parse numerical args and store
    std::vector<double> args(10, 1.0);
    for (int i = 4; i < argc; i++) {
        args[i - 4] = std::stod(argv[i]);
        
    }

    // assign variables to args and output
    int n = args[0];
    double sigma = args[1];
    double min_dist = args[2];
    double temp = args[3];
    double Kb = args[4];
    double dt = args[5];
    double bond_strength = args[6];
    double cutoff_dist = args[7];
    double x_max = args[8];
    double y_max = args[9];

    std::cout << "n: " << n << std::endl;
    std::cout << "sigma: " << sigma << std::endl;
    std::cout << "min_dist: " << min_dist << std::endl;
    std::cout << "temp: " << temp << std::endl;
    std::cout << "Kb: " << Kb << std::endl;
    std::cout << "dt: " << dt << std::endl;
    std::cout << "bond_strength: " << bond_strength << std::endl;
    std::cout << "cutoff_dist: " << cutoff_dist << std::endl;
    std::cout << "Area: " << x_max << "x" << y_max << std::endl;

    // Setup system and initial velocities/placement
    System sys{};
    std::string arrangement = argv[1];
    bool constant_temp = false;
    std::string const_temp_arg = "--constant-temp";
    if (const_temp_arg.compare(argv[2]) == 0) {
        constant_temp = true;
    }

    setup_atoms(sys, n, arrangement, min_dist, x_max, y_max);
    init_velocities(sys, temp, Kb);

    // Setup output csv file
    int output_interval = 1;
    std::ofstream outfile;
    bool write_file = false;
    std::string write_file_arg = "--write";
    if (write_file_arg.compare(argv[3]) == 0) {
        write_file = true;
        outfile = std::ofstream("output.csv");
        outfile << "step,id,x,y\n";
    }

    // Main loop
    for (int step = 0; step < 10000; step++) {
        // Move particles based on prev velocity
        move(sys, dt);

        // Find the new forces based on new pos
        std::vector<double> fx_new(sys.n), fy_new(sys.n);
        compute_forces(sys, bond_strength,sigma, cutoff_dist, fx_new, fy_new);

        // Update the velocities based on old and new forces
        update_velocities(sys, fx_new, fy_new, dt);

        // Assign new forces
        sys.fx = fx_new; 
        sys.fy = fy_new;

        // Scale to const temp
        if (constant_temp) {
            scale_velocities(sys, temp, Kb);
        }

        // Write positions to file
        if (step % output_interval == 0 && write_file) {
            write_output(sys, step, outfile);
        }
    }
    outfile.close();
    return 0;
}
