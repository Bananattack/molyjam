#ifndef CITIZEN_H_INCLUDED
#define CITIZEN_H_INCLUDED
 
#include "Common.h"
#include "Entity.h"
#include "Thought.h"

class Citizen : public Entity {
    public:
        Citizen(const sf::Vector2f& position);
        virtual ~Citizen();

        virtual void render(sf::RenderWindow& window);
        virtual void step(World& world);

    private:
        sf::Sprite head;
        sf::Sprite body;
        sf::Sprite legs;
        ThoughtEmitter emitter;
};

#endif