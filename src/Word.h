#ifndef WORD_H_INCLUDED
#define WORD_H_INCLUDED

#include "Entity.h"

class Word : public Entity {
    private:
        bool reset;
        sf::Text text;
        sf::Vector2f velocity;
        sf::Vector2f origin;

    public:
        Word(const sf::Vector2f& position);
        ~Word();

        void render(sf::RenderWindow& window);
        void step(World& world);
        virtual bool acquireBounds(sf::FloatRect& bounds) {
            bounds = text.getGlobalBounds();
            return true;
        }

        sf::Vector2f getVelocity() {
            return velocity;
        }

        std::string getText() {
            return text.getString();
        }

        void setReset(bool r) { reset = r; }
};

#endif/*WORD_H_INCLUDED*/
