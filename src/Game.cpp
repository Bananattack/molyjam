#include <SFML/Graphics.hpp>
#include <vector>

#include "Everything.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Word : public Entity {
    private:
        sf::Text text;
        sf::Vector2f velocity;

    public:
        Word(const sf::Vector2f& position, const sf::Vector2f& velocity, const std::string& message, const sf::Font& font)
            : text(message, font),
            velocity(velocity) {
            text.setPosition(position);
        }

        ~Word() {
        }

        void render(sf::RenderWindow& window) {
            window.draw(text);
        }

        void step(World& world) {
            text.move(velocity);
            if(!world.screen.intersects(text.getGlobalBounds())) {
                text.setPosition(sf::Vector2f(world.resolution) / 2.0f );
                float r = randf() * 2 * M_PI;
                float mag = 2.0f + randf() * 4.0f;
                velocity = sf::Vector2f(mag * sin(r), mag * -cos(r));
            }
        }
};

int main(int argc, char * argv [] ) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Molyjam!");
    World world(window);

    const char* const dictionary[] = {"hello", "world", "foo", "bar", "magic", "molyjam!", "stuff"};
    sf::Font font(sf::Font::getDefaultFont());

    for(size_t i = 0; i != 256; ++i) {
        float r = randf() * 2 * M_PI;
        float mag = 2.0f + randf() * 4.0f;
        sf::Vector2f pos(sf::Vector2f(window.getSize()) / 2.0f);
        sf::Vector2f vel(mag * sin(r), mag * -cos(r));

        world.addEntity(std::shared_ptr<Entity>(new Word(pos, vel, dictionary[i % 7], font)));
    }

    world.loop();
    return 0;
}
