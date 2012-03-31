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

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <SFML/Graphics.hpp>

inline float randf() {
    return float(rand()) / float(RAND_MAX);
}

#endif/*COMMON_H_INCLUDED*/
