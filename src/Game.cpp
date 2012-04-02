#include <ctime>
#include <cstdlib>

#include "Common.h"
#include "World.h"
#include "Entity.h"
#include "Word.h"
#include "Wall.h"
#include "Dude.h"
#include "Citizen.h"

int main(int argc, char * argv [] ) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Molyjam!", sf::Style::Titlebar | sf::Style::Close);
    World world(window);
    srand(time(0));

    sf::Music bgmusic;
    bgmusic.openFromFile("res/music.ogg");
    bgmusic.play();

    for(size_t i = 0; i != 64; ++i) {
    sf::Vector2f pos(sf::Vector2f(432, 430));
        world.addWord(EntityPtr(new Word(pos)));
    }

    world.addWall(EntityPtr(new Wall(sf::FloatRect(0, 0, 50, 800))));
    world.addWall(EntityPtr(new Wall(sf::FloatRect(0, 500, 800, 50))));

    world.addCitizen(EntityPtr(new Citizen(sf:: Vector2f(432, 430))));
    world.setPlayer(EntityPtr(new Dude()));
    world.loop();
    return 0;
}
