#include "Dude.h"

Dude::Dude() :
    is_jumping(false),
    can_jump(false) {

    if(!spritesheet.loadFromFile("res/sprites.png")) {
        die_horribly();
    }
    sprite.setTexture(spritesheet);
    sprite.setPosition(400,300);
    sprite.setScale(2.0f, 2.0f);
}

Dude::~Dude() {
}

enum Direction {
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

    Direction dir = NONE;
    //movement!
    static const float MOVE_ACCEL = 1.0f;
    static const float MAX_MOVE_SPEED = 16.0f;
    static const float MOVE_FRICTION = 0.9f;
    static const float JUMP_ACCEL = 16.0f;
    static const float GRAVITY = 2.0f;
    static const float MAX_FALL = 16.0f;

    if( left && !right ) {
        velocity.x -= MOVE_ACCEL;
        dir = LEFT;
    } else if( right && !left ) {
        velocity.x += MOVE_ACCEL;
        dir = RIGHT;
    } else {
        velocity.x *= MOVE_FRICTION;
        dir = NONE;
    }

    velocity.x = std::min( std::max( velocity.x, -MAX_MOVE_SPEED ), MAX_MOVE_SPEED );
    if( velocity.x > 6.5f ) {
        dir = RIGHT;
    } else if( velocity.x < -6.5f ) {
        dir = LEFT;
    }
    if( jump ) {
        if( can_jump ) {
            can_jump = false;
//            is_jumping = true;
            velocity.y = -JUMP_ACCEL;
        } else {
            velocity.y += GRAVITY * 0.3f;
        }
    } else {
        velocity.y += GRAVITY;
    }

    velocity.y = std::min( velocity.y, MAX_FALL );
    pos += velocity;
    // bounding!
    sprite.setPosition( pos );
    sf::FloatRect bounds = sprite.getGlobalBounds();
    if( bounds.top + bounds.height  > 600 ) {
        pos.y = 600 - bounds.height;
        can_jump = true;
    }

    sprite.setPosition( pos );
    switch(dir) {
        default:
        case NONE:
            sprite.setTextureRect(sf::IntRect(0,0,48,32));
            break;
        case LEFT:
            sprite.setTextureRect(sf::IntRect(0,32,48,32));
            break;
        case RIGHT:
            sprite.setTextureRect(sf::IntRect(0,64,48,32));
            break;
    }
}

void Dude::render( sf::RenderWindow& window ) {
    window.draw(sprite);
}
