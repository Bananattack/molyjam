#ifndef RENDERABLE_H_INCLUDED
#define RENDERABLE_H_INCLUDED

#include <memory>
#include "Common.h"

class Renderable {
    public:
        virtual ~Renderable() { }
        virtual void render(sf::RenderWindow& window) = 0;
};

typedef std::shared_ptr<Renderable> RenderablePtr;

#endif/*RENDERABLE_H_INCLUDED*/
