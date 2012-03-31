#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "Common.h"
#include "Renderable.h"
#include "Entity.h"
#include <vector>

class World {
    private:
        int lastUpdateTime;
        sf::Clock clock;
        sf::RenderWindow& window;
        sf::Vector2f resolution;
        sf::FloatRect screen;
        std::vector<std::shared_ptr<Entity>> entities;

    public:
        World(sf::RenderWindow& window);
        ~World();

        const sf::Vector2f& getResolution() const;
        const sf::FloatRect& getScreen() const;
        void addEntity(const std::shared_ptr<Entity>& entity);
        const std::shared_ptr<Entity>& entityAt(size_t index) const;
        std::shared_ptr<Entity>& entityAt(size_t index);
        size_t getEntityCount() const;
        void loop();

    private:
        void render();
        void update();
        void step();
};

#endif
