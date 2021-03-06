#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <memory>
#include "Renderable.h"
#include "Renderable.h"

class World;
class Entity : public Renderable {
    public:
        virtual ~Entity() {}
        virtual void step(World& world) = 0;
        virtual bool acquireBounds(sf::FloatRect& bounds) { return false; }
};

typedef std::shared_ptr<Entity> EntityPtr;

#endif/*ENTITY_H_INCLUDED*/
