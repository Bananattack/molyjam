#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED
/*
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
*/
#include <cmath>
#include <memory>
#include <cassert>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define die_horribly() assert(0)

inline float randf() {
    return float(rand()) / float(RAND_MAX);
}

#endif/*COMMON_H_INCLUDED*/
