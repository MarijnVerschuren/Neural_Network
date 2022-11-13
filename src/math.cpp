#include "math.hpp"



void Math::init_random(uint32_t seed) { srand(seed); }
void Math::init_random() {
    std::random_device rd;
    std::uniform_int_distribution<uint32_t> dist(0, 0xffffffff);
    init_random(dist(rd));
}