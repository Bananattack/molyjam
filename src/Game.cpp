#include "Common.h"
#include "World.h"
#include "Entity.h"
#include "Word.h"
#include "Dude.h"

int main(int argc, char * argv [] ) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Molyjam!", sf::Style::Titlebar | sf::Style::Close);
    World world(window);


    const char* const dictionary[] = {"hello", "world", "foo", "bar", "magic", "molyjam!", "stuff"};
    sf::Font font(sf::Font::getDefaultFont());

    for(size_t i = 0; i != 128; ++i) {
        float r = randf() * 2 * M_PI;
        float mag = 2.0f + randf() * 4.0f;
        sf::Vector2f pos(sf::Vector2f(window.getSize()) / 2.0f);
        sf::Vector2f vel(mag * sin(r), mag * -cos(r));

        world.addEntity(std::shared_ptr<Entity>(new Word(pos, vel, dictionary[i % 7], font)));
    }

    world.addEntity(std::shared_ptr<Entity>(new Dude()));
    world.loop();
    return 0;
}
