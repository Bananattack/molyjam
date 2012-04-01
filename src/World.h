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
        sf::View view;
        std::vector<EntityPtr> walls;
        std::vector<EntityPtr> words;
        std::vector<EntityPtr> citizens;
        EntityPtr player;
        RenderablePtr background;

    public:
        World(sf::RenderWindow& window);
        ~World();

        int getLastUpdateTime() const;
        const sf::Vector2f& getResolution() const;
        const sf::FloatRect& getScreen() const;

        void setPlayer(const EntityPtr& entity);
        void addWord(const EntityPtr& entity);
        void addWall(const EntityPtr& entity);
        void addCitizen(const EntityPtr& entity);

        EntityPtr& touchingWall(const EntityPtr& entity) const;
        EntityPtr& touchingWord(const EntityPtr& entity) const;
        EntityPtr& touchingCitzen(const EntityPtr& entity) const;

        void loop();

    private:
        void render();
        void update();
        void step();

        void renderList(const std::vector<EntityPtr>& entities);
        void stepList(const std::vector<EntityPtr>& entities);
};

#endif
