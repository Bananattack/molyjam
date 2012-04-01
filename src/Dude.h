#ifndef DUDE_H_INCLUDED
#define DUDE_H_INCLUDED

#include "Common.h"
#include "Entity.h"

class Dude : public Entity {
    public:
        Dude() : is_jumping(false), can_jump(false) {
            if(!spritesheet.loadFromFile("res/sprites.png")) {
                die_horribly();
            }
            sprite.setTexture(spritesheet);
            sprite.setTextureRect(sf::IntRect(0,0,64,64));
            sprite.setPosition(400,300);
        }

        virtual ~Dude(){
        }

        virtual void step(World& world){
            sf::Vector2f pos = sprite.getPosition();

            //dampen x vel
            velocity.y += 0.981f;
            velocity.x *= 0.2f;

            bool jump = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
            bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
            bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);


            if( jump ) {
                if( is_jumping ) {
                    //
                } else if( can_jump ) {
                    is_jumping = true;
                    can_jump = false;
                    velocity.y = -16.0f;
                }
            } else if( is_jumping ) {
                is_jumping = false;
                velocity.y += 0.981f;
            }

            if( left && !right ) {
                velocity.x = -8.0f;
            } else if( right && !left ) {
                velocity.x = 8.0f;
            }

            if( std::min( velocity.y, 0.01f ) <= 0.01f && jump ) {
                velocity.y = -16.0f;
            } else if( !jump ) {
                velocity.y = 0;
            }

            velocity.y += 0.981f;
            pos += velocity;
            if( pos.y > 600 ) {
                pos.y = 600;
                can_jump = true;
            }

            sprite.setPosition( pos );

        }

        virtual void render(sf::RenderWindow& window) {
            window.draw(sprite);
        }
    private:
        sf::Texture spritesheet;
        sf::Sprite sprite;
        sf::Vector2f velocity;
        bool is_jumping, can_jump;
};

#endif/*DUDE_H_INCLUDED*/
