#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "Common.h"
#include "Renderable.h"
#include "Entity.h"
#include <vector>
#include <functional>

class World {
    private:
        int lastUpdateTime;
        sf::Clock clock;
        sf::RenderWindow& window;
        sf::Vector2f resolution;
        sf::View view;
        EntityPtr player;
        RenderablePtr background;

        sf::Font font;
        int deadline;
        char goal;
        int score;

        sf::Text deadlineText;
        sf::Text goalText;
        sf::Text scoreText;

    public:
        std::vector<EntityPtr> walls;
        std::vector<EntityPtr> words;
        std::vector<EntityPtr> citizens;

        World(sf::RenderWindow& window, sf::Font font);
        ~World();

        sf::RenderWindow& getWindow() const { return window; }
        int getLastUpdateTime() const;
        const sf::Vector2f& getResolution() const;
        sf::View& getView();
        sf::FloatRect calculateCameraBounds() const;

        const EntityPtr& getPlayer() const;
        void setPlayer(const EntityPtr& entity);
        void addWord(const EntityPtr& entity);
        void addWall(const EntityPtr& entity);
        void addCitizen(const EntityPtr& entity);

        void loop();

    private:
        void render();
        void update();
        void step();

        void renderList(const std::vector<EntityPtr>& entities);
        void stepList(const std::vector<EntityPtr>& entities);
};

#endif
