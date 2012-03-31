#include <SFML/Graphics.hpp>

int main(int argc, char * argv [] ) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Molyjam!");

    sf::Text text("Hello World!");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        // draw our shit
        window.draw(text);

        window.display();
    }

    return 0;
}
