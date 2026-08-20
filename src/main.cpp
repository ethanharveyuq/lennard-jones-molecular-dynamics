#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "../include/forces.h"
#include "../include/system.h"
#include "../include/integrate.h"
#include "../include/io.h"

/*
*
*
*
*/
int main(int argc, char* argv[]) {
    if (argc < 13) {
        std::cerr << "Usage: " << argv[0]
                    << " <arrangement> <constant-temp> <write> <n> <sigma> <min_dist> <temp> <Kb> <dt> <bond_strength> <cutoff_dist>\n";
        return 1;
    }

    std::vector<double> args(10, 1.0);
    for (int i = 4; i < argc; i++) {
        args[i - 4] = std::stod(argv[i]);
        
    }
    
    int n = args[0];
    std::cout << "n: " << n << std::endl;
    double sigma = args[1];
    std::cout << "sigma: " << sigma << std::endl;
    double min_dist = args[2];
    std::cout << "min_dist: " << min_dist << std::endl;
    double temp = args[3];
    std::cout << "temp: " << temp << std::endl;
    double Kb = args[4];
    std::cout << "Kb: " << Kb << std::endl;
    double dt = args[5];
    std::cout << "dt: " << dt << std::endl;
    double bond_strength = args[6];
    std::cout << "bond_strength: " << bond_strength << std::endl;
    double cutoff_dist = args[7];
    std::cout << "cutoff_dist: " << cutoff_dist << std::endl;
    double x_max = args[8];
    double y_max = args[9];
    std::cout << "Area: " << x_max << "x" << y_max << std::endl;

    System sys{};
    std::string arrangement = argv[1];
    bool constant_temp = false;
    std::string const_temp_arg = "--constant-temp";
    if (const_temp_arg.compare(argv[2]) == 0) {
        constant_temp = true;
    }

    int output_interval = 1;
    std::ofstream outfile;
    bool write_file = false;
    std::string write_file_arg = "--write";
    if (write_file_arg.compare(argv[3]) == 0) {
        write_file = true;
        outfile = std::ofstream("output.csv");
        outfile << "step,id,x,y\n";
    }

    

    setup_atoms(sys, n, arrangement, sigma, min_dist, x_max, y_max);
    init_velocities(sys, temp, Kb);

    for (int step = 0; step < 10000; step++) {
        move(sys, dt);
        std::vector<double> fx_new(sys.n), fy_new(sys.n);
        compute_forces(sys, bond_strength,sigma, cutoff_dist, fx_new, fy_new);
        update_velocities(sys, fx_new, fy_new, dt);
        sys.fx = fx_new; 
        sys.fy = fy_new;
        if (constant_temp) {
            scale_velocities(sys, temp, Kb);
        }
        if (step % output_interval == 0 && write_file) {
            write_output(sys, step, outfile);
        }
    }
    outfile.close();
    return 0;
}
