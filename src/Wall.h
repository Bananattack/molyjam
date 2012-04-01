#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include "Common.h"
#include "Entity.h"

class Wall : public Entity {
    public:
        Wall(sf::FloatRect box) : box(box) {}
        virtual ~Wall() {}

        virtual void step(World& world) {}
        virtual void render(sf::RenderWindow& window) {}
        virtual bool acquireBounds(sf::FloatRect& bounds) {
            bounds = box;
            return true;
        }

    private:
        sf::FloatRect box;
};

#endif/*DUDE_H_INCLUDED*/
