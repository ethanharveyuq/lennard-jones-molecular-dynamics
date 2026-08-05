#include "../include/system.h"
#include <cmath>
#include <random>


void setup_atoms(System &sys, int n, const std::string &arrangement, double sigma_val, double r_min) {

    if (arrangement == "random") {
        // random atom arrangement setup
        sys.n = 0;
        double xmin = 0.0, xmax = 10.0;
        double ymin = 0.0, ymax = 10.0; // max bounds
        for (int i = 0; i < n; i++) {
            bool ok = false;
            double x, y;
        
            while (!ok) {
                x = xmin + (xmax - xmin) * (rand() / double(RAND_MAX));
                y = ymin + (ymax - ymin) * (rand() / double(RAND_MAX));
                ok = no_overlaps(sys, r_min, x, y);
            }
        
            sys.x.push_back(x);
            sys.y.push_back(y);
            sys.fx.push_back(0);
            sys.fy.push_back(0);
            sys.vx.push_back(0);
            sys.vy.push_back(0);
            sys.n++;
        }
    } else {
        // hexagonal grid particle arrangement
        sys.n = n;
        int grid_width = std::sqrt(n);
        int curr = 0;
        double dx = r_min; // x spacing
        double dy = r_min * std::sqrt(3.0) / 2.0; // y spacing, ensures r_min dist between all
        int placed = 0;

        for (int row = 0; placed < n; row++) {
            double x_offset = (row % 2 == 1) ? dx * 0.5 : 0.0; // offsets every odd row
            int extra = (row % 2 == 1) ? 0 : 1; // alternate number in each
        
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

bool no_overlaps(System &sys, double r_min, double x, double y) {
    for (int i = 0; i < sys.n; i++) {
        double dx = x - sys.x[i];
        double dy = y - sys.y[i];
        double dist = std::sqrt(dx*dx + dy*dy);

        if (dist < r_min) {
            return false;
        }
    }
    return true;
}

void init_velocities(System& sys, double temp, double Kb);