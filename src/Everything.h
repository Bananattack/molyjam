#ifndef EVERYTHING_H_INCLUDED
#define EVERYTHING_H_INCLUDED

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

inline float randf() {
    return float(rand()) / float(RAND_MAX);
}

#include "Renderable.h"
#include "Entity.h"
#include "World.h"
#include "Word.h"
#include "Thought.h"

#endif/*EVERYTHING_H_INCLUDED*/
