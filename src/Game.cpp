#include <SFML/Graphics.hpp>
#include <vector>

#include <cstdlib>
#include <cmath>

float randf() {
    return ( (double) rand() / double(RAND_MAX) );
}

int main(int argc, char * argv [] ) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Molyjam!");
    sf::FloatRect screen( sf::Vector2f(0, 0), sf::Vector2f( window.getSize() ) );

    std::string dict[] = {"hello", "world", "foo", "bar", "magic", "molyjam!", "stuff"};

    sf::Text words[7];
    std::vector<sf::Vector2f> vels;

    for( size_t i = 0; i < 7; ++i ) {
        words[i] = sf::Text(dict[i]);
        words[i].setPosition( sf::Vector2f( window.getSize() ) / 2.0f );
        float r = randf() * 2 * M_PI;
        vels.push_back(sf::Vector2f( sin(r), -cos(r) ) );
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
        for( size_t i = 0; i < 7; ++i ) {
            words[i].move(vels[i]);
            if( !screen.intersects( words[i].getGlobalBounds() ) ) {
                words[i].setPosition( sf::Vector2f( window.getSize() ) / 2.0f );
                float r = randf() * 2 * M_PI;
                vels[i] = sf::Vector2f( sin(r), -cos(r) );
            }
            window.draw(words[i]);
        }

        window.display();
    }

    return 0;
}
