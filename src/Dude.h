#ifndef DUDE_H_INCLUDED
#define DUDE_H_INCLUDED

#include <memory>
#include "Common.h"
#include "Entity.h"

class Dude : public Entity, public std::enable_shared_from_this<Dude> {
    public:
        Dude();
        virtual ~Dude();

        virtual void step(World& world);
        virtual void render(sf::RenderWindow& window);
        virtual bool acquireBounds(sf::FloatRect& bounds);
        bool move(World& world, sf::Vector2f offset);

    private:
        EntityPtr grapplingWord;
        sf::Texture spritesheet;
        sf::Sprite sprite;
        sf::Vector2f velocity;
        bool is_jumping, can_jump, release_jump_button;
};

#endif/*DUDE_H_INCLUDED*/
