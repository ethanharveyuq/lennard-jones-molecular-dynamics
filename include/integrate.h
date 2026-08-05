#include "system.h"

void move(System& sys, double dt);
void update_velocities(System& sys, const std::vector<double>& fx_new,
                        const std::vector<double>& fy_new, double dt);