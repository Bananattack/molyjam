#include <ctime>
#include <cstdlib>

#include "Common.h"
#include "World.h"
#include "Entity.h"
#include "Word.h"
#include "Dude.h"
#include "Citizen.h"

int main(int argc, char * argv [] ) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Molyjam!", sf::Style::Titlebar | sf::Style::Close);
    World world(window);
    srand(time(0));

    const char* const dictionary[] = {"hello", "world", "foo", "bar", "magic", "molyjam!", "stuff"};
    sf::Font font(sf::Font::getDefaultFont());

    for(size_t i = 0; i != 128; ++i) {
        float r = randf() * 2 * M_PI;
        float mag = 2.0f + randf() * 4.0f;
        sf::Vector2f pos(sf::Vector2f(window.getSize()) / 2.0f);
        sf::Vector2f vel(mag * sin(r), mag * -cos(r));

        world.addEntity(EntityPtr(new Word(pos, vel, dictionary[i % 7], font)));
    }
    world.addEntity(EntityPtr(new Citizen(sf::Vector2f(90, 90))));
    world.addEntity(EntityPtr(new Dude()));
    world.loop();
    return 0;
}
