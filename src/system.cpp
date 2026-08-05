#include "../include/system.h"
#include <cmath>
#include <random>


void setup_atoms(System &sys, int n, const std::string &arrangement, double sigma_val, double r_min) {

    if (arrangement == "random") {
        // random atom arrangement setup

    } else {
        // hexagonal grid atom arrangement
        sys.n = n;
        int grid_width = std::sqrt(n);
        int curr = 0;
        double dx = r_min; // x spacing
        double dy = r_min * std::sqrt(3.0) / 2.0; // y spacing, ensures r_min dist between all
        int placed = 0;

        for (int row = 0; placed < n; row++) {
            double x_offset = (row % 2 == 1) ? dx * 0.5 : 0.0; // offsets every odd row
            int extra = (row % 2 == 1) ? 0 : 1;
        
            for (int col = 0; col < grid_width + extra && placed < n; col++) {
                double x = x_offset + col * dx;
                double y = row * dy;
        
                sys.x.push_back(x);
                sys.y.push_back(y);
                sys.fx.push_back(0);
                sys.fy.push_back(0);
                sys.vx.push_back(0);
                sys.vy.push_back(0);
        
                placed++;
            }
        }
    }

    return;

}