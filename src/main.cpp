#include <iostream>
#include "../include/forces.h"
#include "../include/system.h"

void move(System&, double dt);                       // x += vx*dt + 0.5*fx*dt²  (uses OLD force)
void update_velocities(System&, const std::vector<double>& fx_new,
                        const std::vector<double>& fy_new, double dt);           // v += 0.5*(f_old+f_new)*dt

int main() {
    std::cout << "Molecular Dynamics Lennard-Jones" << std::endl;
    /*
    for (int step = 0; step < num_steps; step++) {
        move(sys, dt);                                          // uses sys.fx/fy (old)
        std::vector<double> fx_new(sys.n), fy_new(sys.n);
        compute_forces(sys, bond_strength, cutoff_dist, fx_new, fy_new);  // from new positions
        update_velocities(sys, fx_new, fy_new, dt);              // combines old + new
        sys.fx = fx_new; sys.fy = fy_new;                        // new becomes old for next iter
        if (constant_temp) scale_velocities(sys, temp, Kb);
        if (step % output_interval == 0) write_output(sys, step, outfile);
    }
        */
}