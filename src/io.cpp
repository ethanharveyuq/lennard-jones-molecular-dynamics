#include "../include/io.h"
#include <iostream>
#include <ostream>
#include <fstream>

void write_output(const System& sys, int step, std::ofstream& out) 
{
    // Loop over all particles and write one CSV line per particle.
    // The file stream is assumed to be already open by the caller.
    for (int i = 0; i < sys.n; i++) {
        out << step << "," << i << "," << sys.x[i] << "," << sys.y[i] << "\n";
    }
}