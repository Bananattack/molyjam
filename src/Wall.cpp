#include "Wall.h"

namespace {
    sf::Texture getTexture() {
        sf::Texture tex;
        tex.loadFromFile("res/wall.png");
        tex.setRepeated(true);
        return tex;
    }
}

static sf::Texture walltex = getTexture();

Wall::Wall(sf::FloatRect box) : box(box) {
    sprite.setTexture(walltex);
    sprite.setPosition(box.left, box.top);
    sprite.setTextureRect(sf::IntRect(0, 0, box.width, box.height));
}

Wall::~Wall() {
}
void Wall::step(World& world) {
}

void Wall::render( sf::RenderWindow& window ) {
    window.draw( sprite );
}

bool Wall::acquireBounds(sf::FloatRect& bounds ) {
    bounds = box;
    return true;
}
