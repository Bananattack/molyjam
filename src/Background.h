#include "Renderable.h"
#include "World.h"

class Background : public Renderable {
    void render(sf::RenderWindow& window) {
        window.clear(sf::Color(0x98, 0x82, 0xDB));
    }
};