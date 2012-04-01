#include "World.h"
#include "Citizen.h"

namespace {
    bool loaded = false;
    sf::Texture headSheet;
    sf::Texture bodySheet;
    sf::Texture legSheet;

    void init() {
        if(!loaded) {
            headSheet.loadFromFile("res/heads.png");
            bodySheet.loadFromFile("res/bodies.png");
            legSheet.loadFromFile("res/legs.png");

            loaded = true;
        }
    }
}

Citizen::Citizen(const sf::Vector2f& position) {
    init();
    head.setScale(2.0, 2.0);
    head.setOrigin(32, 38);
    head.setTexture(headSheet);
    head.setTextureRect(sf::IntRect(0, (rand() % 9) * 64, 64, 64));
    head.setPosition(position + sf::Vector2f(0, -19));

    body.setScale(2.0, 2.0);
    body.setOrigin(32, 32);
    body.setTexture(bodySheet);
    body.setTextureRect(sf::IntRect(0, 0, 64, 64));
    body.setPosition(position + sf::Vector2f(0, 32));

    legs.setScale(2.0, 2.0);
    legs.setOrigin(32, 16);
    legs.setTexture(legSheet);
    legs.setTextureRect(sf::IntRect(0, 0, 64, 64));
    legs.setPosition(position + sf::Vector2f(0, 42));
}

Citizen::~Citizen() {

}

void Citizen::render(sf::RenderWindow& window) {
    window.draw(legs);
    window.draw(body);
    window.draw(head);
}

void Citizen::step(World& world) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        head.setTextureRect(sf::IntRect(0, (rand() % 9) * 64, 64, 64));
    }

    head.setRotation(sin(float(world.getLastUpdateTime()) * 0.02f) * 20);
    body.setScale(2.0f, sin(float((world.getLastUpdateTime() + 10) * 0.03)) * 0.1f + 2.1f);
    legs.setRotation(cos(float(world.getLastUpdateTime() + 16) * 0.04f) * 3);
    legs.setScale(2.0f, cos(float((world.getLastUpdateTime() + 10) * 0.01)) * 0.1f + 2.1f);
}