#include "Word.h"
#include "World.h"

Word::Word(const sf::Vector2f& position, const sf::Vector2f& velocity, const std::string& message, const sf::Font& font) :
    text(message, font, 60),
    velocity(velocity) {

    text.setPosition(position);
}

Word::~Word() {
}

void Word::render(sf::RenderWindow& window) {
    window.draw(text);
}

void Word::step(World& world) {
    text.move(velocity);
    if(!world.getScreen().intersects(text.getGlobalBounds())) {
        text.setPosition(sf::Vector2f(world.getResolution()) / 2.0f );
        float r = randf() * 2 * M_PI;
        float mag = 2.0f + randf() * 4.0f;
        velocity = sf::Vector2f(mag * sin(r), mag * -cos(r));
    }
}
