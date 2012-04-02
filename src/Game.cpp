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
    sf::RenderWindow window(sf::VideoMode(800, 600), "Molyjam!", sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen);
    World world(window);
    srand(time(0));

    sf::Music bgmusic;
    bgmusic.openFromFile("res/music.ogg");
    bgmusic.play();

    //floor
    world.addWall(EntityPtr(new Wall(sf::FloatRect(-1024, 1024,8*1024, 1024))));
    //ceil
    world.addWall(EntityPtr(new Wall(sf::FloatRect(-1024, -1024, 8*1024, 1024))));
    //left wall
    world.addWall(EntityPtr(new Wall(sf::FloatRect(-1024, 0, 1024, 1024))));
    //right wall
    world.addWall(EntityPtr(new Wall(sf::FloatRect(3*1024, 0, 1024, 1024))));

    for(size_t i = 0; i < 10; ++i ) {
        sf::Vector2f origin(128 + 300 * i, 950 );
        world.addCitizen(EntityPtr(new Citizen(origin)));

        for(size_t i = 0; i != 5; ++i) {
            sf::Vector2f pos(origin);
            pos.y -= 64;
            pos.x -= 32;
            world.addWord(EntityPtr(new Word(pos)));
        }
    }

    world.setPlayer(EntityPtr(new Dude()));
    world.loop();
    return 0;
}
