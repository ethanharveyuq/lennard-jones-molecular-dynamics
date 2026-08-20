#include "../include/io.h"
#include <iostream>
#include <ostream>
#include <fstream>

void write_output(const System& sys, int step, std::ofstream& out) {
    for (int i = 0; i < sys.n; i++) {
        out << step << "," << i << "," << sys.x[i] << "," << sys.y[i] << std::endl;
    }
}