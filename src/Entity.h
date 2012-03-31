#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "Renderable.h"

class Entity : public Renderable {
    public:
        virtual ~Entity() {}
        virtual void update( float dt ) = 0;
};

#endif/*ENTITY_H_INCLUDED*/