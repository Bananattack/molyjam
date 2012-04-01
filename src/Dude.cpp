#include "Dude.h"

Dude::Dude() :
    is_jumping(false),
    can_jump(false) {

    if(!spritesheet.loadFromFile("res/sprites.png")) {
        die_horribly();
    }
    sprite.setTexture(spritesheet);
    sprite.setTextureRect(sf::IntRect(0,0,64,64));
    sprite.setPosition(400,300);
}

Dude::~Dude() {
}

enum direction {
    NONE,
    RIGHT,
    LEFT,
    UP,
    DOWN
};

void Dude::step( World& world ) {
    //get keystate
    bool jump = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    bool hold = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

    sf::Vector2f pos = sprite.getPosition();

    //movement!
    static const float MOVE_ACCEL = 2.0f;
    static const float MAX_MOVE_SPEED = 8.0f;
    static const float MOVE_FRICTION = 0.2f;
    static const float JUMP_ACCEL = 16.0f;
    static const float GRAVITY = 0.981f;
    static const float MAX_FALL = 16.0f;

    if( left && !right ) {
        velocity.x -= MOVE_ACCEL;
    } else if( right && !left ) {
        velocity.x += MOVE_ACCEL;
    }
/*
    if( jump ) {
        if( !is_jumping && can_jump ) {
            //jump
        } else if
*/

    pos += velocity;

    // bounding!

    // done!
    sprite.setPosition(pos);
}

void Dude::render( sf::RenderWindow& window ) {
    window.draw(sprite);
}
