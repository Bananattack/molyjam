#include "Background.h"
#include "World.h"

namespace {
    static const int MAX_FRAME_GAP = 3;
}

World::World( sf::RenderWindow& window ) :
    lastUpdateTime(0),
    window(window),
    resolution(window.getSize()),
    view(sf::Vector2f(0, 0), resolution),
    background(new Background())
{
    view.setCenter(resolution * 0.5f);
    window.setView(view);
}

World::~World() {
}

int World::getLastUpdateTime() const {
    return lastUpdateTime;
}

const sf::Vector2f& World::getResolution() const {
    return resolution;
}

sf::View& World::getView() {
    return view;
}

sf::FloatRect World::calculateCameraBounds() const {
    float fudgeFactor = resolution.y * 1.5;
    sf::Vector2f fudgeVector(fudgeFactor, fudgeFactor);
    sf::Vector2f position = view.getCenter() - (view.getSize() / 2.0f) - fudgeVector;
    return sf::FloatRect(position, view.getSize() + fudgeVector * 2.0f);
}

const EntityPtr& World::getPlayer() const {
    return player;
}

void World::setPlayer(const EntityPtr& entity) {
    player = entity;
}

void World::addWall(const EntityPtr& entity) {
    walls.push_back(entity);
}

void World::addWord(const EntityPtr& entity) {
    words.push_back(entity);
}

void World::addCitizen(const EntityPtr& entity) {
    citizens.push_back(entity);
}

void World::checkWallCollision(const EntityPtr& entity, std::function<bool(EntityPtr, EntityPtr)> onCollide) {
    return checkCollisionList(entity, walls, onCollide);
}

void World::checkWordCollision(const EntityPtr& entity, std::function<bool(EntityPtr, EntityPtr)> onCollide) {
    return checkCollisionList(entity, words, onCollide);
}

void World::checkCollisionList(const EntityPtr& entity, const std::vector<EntityPtr>& entities, std::function<bool(EntityPtr, EntityPtr)> onCollide) {
    sf::FloatRect self;
    if(entity && entity->acquireBounds(self)) {
        for(auto it = entities.begin(), end = entities.end(); it != end; ++it) {
            sf::FloatRect target;
            if((*it)->acquireBounds(target) && self.intersects(target)) {
                if(!onCollide(entity, *it)) {
                    break;
                }
            }
        }
    }
}

void World::loop() {
    while(window.isOpen()) {
        render();
        update();
    }
}

void World::render() {
    window.setView(view);
    window.clear();
    if(background) {
        background->render(window);
    }
    renderList(citizens);
    if(player) {
        player->render(window);
    }
    renderList(words);
    renderList(walls);
    window.display();
}

void World::renderList(const std::vector<EntityPtr>& entities) {
    for(auto it = entities.begin(), end = entities.end(); it != end; ++it) {
        (*it)->render(window);
    }
}

void World::update() {
    int time = clock.getElapsedTime().asMilliseconds() / 16.6666667f ;
    int frames = std::min(time - lastUpdateTime, MAX_FRAME_GAP);
    if(frames > 0) {
        for(int i = 0; i < frames; ++i) {
            step();
        }
        lastUpdateTime = time;
    }
}

void World::step() {
    sf::Event event;
    while(window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            window.close();
        }

        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            window.close();
        }
    }
    stepList(words);
    if(player) {
        player->step(*this);
    }
    stepList(citizens);
}

void World::stepList(const std::vector<EntityPtr>& entities) {
    for(auto it = entities.begin(), end = entities.end(); it != end; ++it) {
        (*it)->step(*this);
    }
}