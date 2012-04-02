#include "Word.h"
#include "World.h"
#include <fstream>

namespace {
    std::vector<std::string> getWords() {
        std::vector<std::string> words;
        std::ifstream f("res/words");
        while(!f.eof()) {
            std::string line;
            std::getline(f, line);
            words.push_back(line);
        }
        return words;
    }

    sf::Font getFont() {
        sf::Font font;
        font.loadFromFile("res/font.ttf");
        return font;
    }

    static sf::Font font = getFont();

    std::string getWord() {
        static std::vector<std::string> words = getWords();
        return words[ rand() % words.size() ];
    }

    sf::Vector2f randomizeVelocity() {
        float r = -M_PI/2.0f + randf() *  M_PI;
        float mag = 2.0f;//2.0f + randf() * 4.0f;
        return sf::Vector2f(mag * sin(r), mag * -cos(r));
    }
}

Word::Word(const sf::Vector2f& position) :
    reset(false),
    text(getWord(), font, 60),
    velocity(randomizeVelocity()) {
    origin = position;
    text.setPosition(position);
}

Word::~Word() {
}

void Word::render(sf::RenderWindow& window) {
    window.draw(text);
}

void Word::step(World& world) {
    if( sf::Mouse::isButtonPressed(sf::Mouse::Left) ) {
        sf::Vector2f mouse( sf::Mouse::getPosition( world.getWindow() ) );
        if( text.getGlobalBounds().contains(mouse) ) {
            reset = true;
        }
    }

    text.move(velocity);
    if(!world.calculateCameraBounds().intersects(text.getGlobalBounds())) {
        reset = true;
    }

    if( reset ) {
        text.setString( getWord() );
        text.setPosition(origin);
        velocity = randomizeVelocity();
        reset = false;
    }
}
