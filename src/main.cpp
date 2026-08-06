#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "../include/forces.h"
#include "../include/system.h"
#include "../include/integrate.h"

void write_output(const System& sys, int step, std::ofstream& out) {
    for (int i = 0; i < sys.n; i++) {
        out << step << "," << i << "," << sys.x[i] << "," << sys.y[i] << std::endl;
    }
}
/*
* argv arrangemenr num_particles sigma min_dist temp Kb dt
*
*
*
*/
int main(int argc, char* argv[]) {
    std::vector<double> args(6, 1.0);
    for (int i = 2; i < argc; i++) {
        args[i] = std::stod(argv[i]);
    }

    System sys{};
    std::string arrangement = argv[1];
    int n = args[0];
    double sigma = args[1];
    double min_dist = args[2];
    double temp = args[3];
    double Kb = args[4];
    double dt = args[5];
    bool constant_temp = false;
    int output_interval = 1;

    std::ofstream outfile("output.csv");
    outfile << "step,id,x,y\n";

    setup_atoms(sys, n, arrangement, sigma, min_dist);
    init_velocities(sys, temp, Kb);

    for (int step = 0; step < 1000; step++) {
        move(sys, dt);
        std::vector<double> fx_new(sys.n), fy_new(sys.n);
        compute_forces(sys, 1.0, 1.0, fx_new, fy_new);
        update_velocities(sys, fx_new, fy_new, dt);
        sys.fx = fx_new; 
        sys.fy = fy_new;
        if (constant_temp) {
            scale_velocities(sys, temp, Kb);
        }
        if (step % output_interval == 0) {
            write_output(sys, step, outfile);
        }
    }
    outfile.close();
    return 0;
}