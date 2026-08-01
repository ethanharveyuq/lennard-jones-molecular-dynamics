#include <iostream>

struct ParticleSystem {
    std::vector<double> x, y;
    std::vector<double> vx, vy;
    std::vector<double> fx, fy;
    int n;
};

void init_positions(ParticleSystem& s, int n, ArrangementType type);   // random or HCP grid
void init_velocities(ParticleSystem& s, double target_temp);          // Maxwell-Boltzmann-ish, matched to TEMP
void compute_forces(ParticleSystem& s, double sigma, double eps);      // O(N²) pairwise LJ forces, zero fx/fy first
void velocity_verlet_step(ParticleSystem& s, double dt);               // update v(t+dt/2), x(t+dt), forces, v(t+dt)
void apply_thermostat(ParticleSystem& s, double target_temp);          // only if CONSTANT-TEMPERATURE? equivalent is on
double compute_kinetic_energy(const ParticleSystem& s);
double compute_potential_energy(const ParticleSystem& s);
void write_output(const ParticleSystem& s, int step, std::ofstream& out);

int main() {
    std::cout << "Molecular Dynamics Lennard-Jones" << std::endl;
    return 0;
}