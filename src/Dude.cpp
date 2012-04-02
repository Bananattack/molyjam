#include "World.h"
#include "Dude.h"

Dude::Dude() :
    is_jumping(false),
    can_jump(false),
    release_jump_button(false) {

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
    if(world.getPlayer().get() == this) {
        world.getView().setCenter(sprite.getPosition());
    }
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

    if(!move(world, sf::Vector2f(velocity.x, 0))) {
        velocity.x = 0;
    }

    if(jump) {
        if(can_jump) {
            if(!release_jump_button) {
                can_jump = false;
                release_jump_button = true;
//              is_jumping = true;
                velocity.y = -JUMP_ACCEL;
            }
        } else {
            velocity.y += GRAVITY * 0.3f;
        }
    } else {
        if(release_jump_button) {
            release_jump_button = false;
        }
        velocity.y += GRAVITY;
    }

    velocity.y = std::min(velocity.y, MAX_FALL);
    if(!move(world, sf::Vector2f(0, velocity.y))) {
        can_jump = true;
    }

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

bool Dude::acquireBounds(sf::FloatRect& bounds) {
    bounds = sprite.getGlobalBounds();
    return true;
}

bool Dude::move(World& world, sf::Vector2f offset) {
    bool collided = false;
    sprite.move(offset);

    sf::FloatRect bounds = sprite.getGlobalBounds();
    for(auto it = world.walls.begin(), end = world.walls.end(); it != end; ++it) {
        sf::FloatRect wall;
        if((*it)->acquireBounds(wall) && bounds.intersects(wall)) {
            if(offset.x != 0) {
                if(offset.x < 0) {
                    sprite.move(wall.width, 0);
                } else {
                    sprite.move(-bounds.width, 0);
                } 
            }
            if(offset.y != 0) {
                if(offset.y < 0) {
                    sprite.move(0, wall.height);
                } else {
                    sprite.move(0, -bounds.height);
                }
            }
            collided = true;
        }
    }
    return collided;
}
