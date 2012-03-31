#ifndef EVERYTHING_H_INCLUDED
#define EVERYTHING_H_INCLUDED

#include <cstdlib>
#include <cmath>

#include "Renderable.h"
#include "Entity.h"

float randf() {
    return ( (double) rand() / double(RAND_MAX) );
}

#endif/*EVERYTHING_H_INCLUDED*/
