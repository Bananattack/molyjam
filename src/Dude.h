#ifndef DUDE_H_INCLUDED
#define DUDE_H_INCLUDED

#include "Common.h"
#include "Entity.h"

class Dude : public Entity {
    public:
        Dude();
        virtual ~Dude();

        virtual void step(World& world);
        virtual void render(sf::RenderWindow& window);
    private:
        sf::Texture spritesheet;
        sf::Sprite sprite;
        sf::Vector2f velocity;
        bool is_jumping, can_jump;
};

#endif/*DUDE_H_INCLUDED*/
