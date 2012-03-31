#ifndef EVERYTHING_H_INCLUDED
#define EVERYTHING_H_INCLUDED

#include <cstdlib>
#include <cmath>
#include <vector>
#include <memory>

#include "Renderable.h"
#include "Entity.h"
#include "World.h"

float randf() {
    return float(rand()) / float(RAND_MAX);
}

#endif/*EVERYTHING_H_INCLUDED*/
