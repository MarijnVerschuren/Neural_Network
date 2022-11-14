#pragma once

#include "macro.hpp"

#include <stdlib.h>     /* srand, rand */
#include <random>       /* random_device */
#include <math.h>       /* exp */



namespace Math {
    void init_random(uint32_t);
    void init_random();

    inline double rand_uniform() { return ((double)rand()) / RAND_MAX; }
    inline double rand_uniform(double min, double max) { return min + (((max - min) * (double)rand()) / RAND_MAX); }

    inline double sigma(double x) { return 1 / (1 + exp(-x)); }
};  // Math