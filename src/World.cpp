#include "Background.h"
#include "World.h"

namespace {
    static const int MAX_FRAME_GAP = 3;
}

World::World( sf::RenderWindow& window ) :
    lastUpdateTime(0),
    window(window),
    resolution(window.getSize()),
    screen(sf::Vector2f(0, 0), resolution),
    view(screen),
    background(new Background()) {
}

World::~World() {
}

int World::getLastUpdateTime() const {
    return lastUpdateTime;
}

const sf::Vector2f& World::getResolution() const {
    return resolution;
}

const sf::FloatRect& World::getScreen() const {
    return screen;
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

void World::loop() {
    while(window.isOpen()) {
        render();
        update();
    }
}
void World::render() {
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