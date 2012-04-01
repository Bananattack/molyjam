#ifndef WORD_H_INCLUDED
#define WORD_H_INCLUDED

#include "Entity.h"

class Word : public Entity {
    private:
        sf::Text text;
        sf::Vector2f velocity;

    public:
        Word(const sf::Vector2f& position);
        ~Word();

        void render(sf::RenderWindow& window);
        void step(World& world);
};

#endif/*WORD_H_INCLUDED*/
