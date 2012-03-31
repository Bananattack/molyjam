#ifndef RENDERABLE_H_INCLUDED
#define RENDERABLE_H_INCLUDED

#include "Common.h"

class Renderable {
    public:
        virtual ~Renderable() { }
        virtual void render(sf::RenderWindow& window) = 0;
};

#endif/*RENDERABLE_H_INCLUDED*/
