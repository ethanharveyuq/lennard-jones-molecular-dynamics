#include "../include/system.h"
#include <cmath>
#include <random>

const double MASS = 1;
const double SEED = 42;

void setup_atoms(System &sys, int n, const std::string &arrangement, double sigma_val, double r_min, double x_max, double y_max) {
    sys.x_max = x_max;
    sys.y_max = y_max;

    if (arrangement == "random") {
        // random atom arrangement setup
        sys.n = 0;
        sys.vx.resize(n);
        sys.vy.resize(n);
        sys.fx.resize(n);
        sys.fy.resize(n);
        double x_min = 0.0, y_min = 0.0;
        for (int i = 0; i < n; i++) {
            bool ok = false;
            double x, y;
        
            while (!ok) {
                x = x_min + (x_max - x_min) * (rand() / double(RAND_MAX));
                y = y_min + (y_max - y_min) * (rand() / double(RAND_MAX));
                ok = no_overlaps(sys, r_min, x, y); // check if any overlaps
            }
        
            sys.x.push_back(x);
            sys.y.push_back(y);
            sys.n++;
        }
    } else {
        // hexagonal grid particle arrangement
        sys.n = n;
        sys.vx.resize(n);
        sys.vy.resize(n);
        sys.fx.resize(n);
        sys.fy.resize(n);
        sys.x.resize(n);
        sys.y.resize(n);
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
        
                sys.x[placed] = x;
                sys.y[placed] = y;
        
                placed++;
            }
        }
        // Compute bounding box
        double xmin = sys.x[0], xmax = sys.x[0];
        double ymin = sys.y[0], ymax = sys.y[0];

        for (int i = 1; i < sys.n; i++) {
            if (sys.x[i] < xmin) xmin = sys.x[i];
            if (sys.x[i] > xmax) xmax = sys.x[i];
            if (sys.y[i] < ymin) ymin = sys.y[i];
            if (sys.y[i] > ymax) ymax = sys.y[i];
        }

        double x_center = 0.5 * (xmin + xmax);
        double y_center = 0.5 * (ymin + ymax);

        // shift to recentre
        double target_xc = sys.x_max / 2;
        double target_yc = sys.y_max / 2;

        double shift_x = target_xc - x_center;
        double shift_y = target_yc - y_center;

        for (int i = 0; i < sys.n; i++) {
            sys.x[i] += shift_x;
            sys.y[i] += shift_y;
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

/**
* 
*
*/
void init_velocities(System& sys, double temp, double Kb) {
    // Sample velocities based on temp
    std::normal_distribution<double> normal(0, std::sqrt(Kb * temp / MASS));
    std::mt19937 rng(SEED);
    for (int i = 0; i < sys.n; i++) {
        double vx = normal(rng);
        double vy = normal(rng);
        sys.vx[i] = vx;
        sys.vy[i] = vy;
    }

    // Remove centre of mass drift (whole system velocity is 0)
    double vx_cm = 0.0, vy_cm = 0.0;
    for (int i = 0; i < sys.n; i++) {
        vx_cm += sys.vx[i];
        vy_cm += sys.vy[i];
    }
    vx_cm /= sys.n;
    vy_cm /= sys.n;
    for (int i = 0; i < sys.n; i++) {
        sys.vx[i] -= vx_cm;
        sys.vy[i] -= vy_cm;
    }

    // Rescale back to temperature
    scale_velocities(sys, temp, Kb);
}

// Might need to adjust this later (Dof might be arbitrary)
double current_temp(const System& sys, double Kb) {
    double kenergy = 0.0;
    for (int i = 0; i < sys.n; i++) {
        kenergy += 0.5 * MASS * (sys.vx[i]*sys.vx[i] + sys.vy[i]*sys.vy[i]);
    }
    int f = 2 * sys.n; // 2D
    return (2 * kenergy) / (f * Kb);
}

void scale_velocities(System& sys, double target_temp, double Kb) {
    double t_inst = current_temp(sys, Kb);
    double lambda = std::sqrt(target_temp / t_inst);
    for (int i = 0; i < sys.n; i++) {
        sys.vx[i] *= lambda;
        sys.vy[i] *= lambda;
    }
}