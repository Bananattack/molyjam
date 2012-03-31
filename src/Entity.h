#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "Renderable.h"

class World;
class Entity : public Renderable {
    public:
        virtual ~Entity() {}
        virtual void step(World& world) = 0;
};

#endif/*ENTITY_H_INCLUDED*/
