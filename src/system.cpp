#include "../include/system.h"
#include <cmath>
#include <random>


void setup_atoms(System &sys, int n, const std::string &arrangement, double sigma_val, double r_min) {

    if (arrangement == "random") {
        // random atom arrangement setup
    } else {
        // hexagonal grid atom arrangement
        int grid_width = std::sqrt(n);
        
    }

    return;

}