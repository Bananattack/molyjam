#include <SFML/Graphics.hpp>
#include <vector>

#include "Everything.h"

int main(int argc, char * argv [] ) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Molyjam!");
    sf::FloatRect screen( sf::Vector2f(0, 0), sf::Vector2f( window.getSize() ) );

    std::string dict[] = {"hello", "world", "foo", "bar", "magic", "molyjam!", "stuff"};
    size_t count = 256;
    sf::Text words[count];
    std::vector<sf::Vector2f> vels;

    for( size_t i = 0; i < count; ++i ) {
        words[i] = sf::Text(dict[i % 7]);
        words[i].setPosition( sf::Vector2f( window.getSize() ) / 2.0f );
        float r = randf() * 2 * M_PI;
        float mag = 2.0f + randf() * 4.0f;
        vels.push_back(sf::Vector2f( mag * sin(r), mag * -cos(r) ) );
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        // draw our shit
        for( size_t i = 0; i < count; ++i ) {
            words[i].move(vels[i]);
            if( !screen.intersects( words[i].getGlobalBounds() ) ) {
                words[i].setPosition( sf::Vector2f( window.getSize() ) / 2.0f );
                float r = randf() * 2 * M_PI;
                float mag = 2.0f + randf() * 4.0f;
                vels[i] = sf::Vector2f( mag * sin(r), mag * -cos(r) );
            }
            window.draw(words[i]);
        }

        window.display();
    }

    return 0;
}
