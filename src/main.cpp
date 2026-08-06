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

int main() {
    std::cout << "Molecular Dynamics Lennard-Jones" << std::endl;
    System sys{};

    int n = 15;
    std::string arrangement = "grid";
    double sigma = 1.0;
    double min_dist = 1.0;
    double temp = 1;
    double Kb = 1;
    double dt = 1.0;
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