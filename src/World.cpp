#include <cctype>
#include <sstream>
#include "Background.h"
#include "World.h"

namespace {    

    sf::Font getFont() {
        sf::Font font;
        font.loadFromFile("res/font.ttf");
        return font;
    }

    static sf::Font fontx = getFont();
    bool gameover = false;
}
namespace {
    static const int MAX_FRAME_GAP = 3;
}

World::World( sf::RenderWindow& window) :
    lastUpdateTime(0),
    window(window),
    resolution(window.getSize()),
    view(sf::Vector2f(0, 0), resolution),
    deadline(0),
    goal(rand() % 26 + 'a'),
    score(0),
    deadlineText("test", fontx, 160),
    scoreText("", fontx, 160),
    goalText("", fontx, 160),
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
    float fudgeFactor = resolution.y * 2.5;
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

void World::loop() {
    while(window.isOpen()) {
        render();
        update();
    }
}

void World::render() {
    if( gameover ) {
        window.clear();
        static sf::Text losermessage("You were defeated by\n     the letter", fontx, 100);
        losermessage.setPosition(100,0);
        window.draw(losermessage);

        static sf::Text losermessage2("", fontx, 300);
        losermessage2.setPosition(200,200);
        std::ostringstream os;
        os << char(toupper(goal));
        losermessage2.setString(os.str());
        window.draw(losermessage2);


        static sf::Text losermessage3("Press Escape to play again!", fontx, 100);
        losermessage3.setPosition(0,500);
        window.draw(losermessage3);

        window.display();
        return;
    }
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
    //window.display();

    window.setView(window.getDefaultView());


    {
        std::ostringstream os;
        os << int(deadline - clock.getElapsedTime().asSeconds());
        deadlineText.setPosition(sf::Vector2f(30, 30));
        deadlineText.setColor(sf::Color(255, 0, 0));
        deadlineText.setString(os.str());
        window.draw(deadlineText);
    }
    {
        std::ostringstream os;
        os << char(toupper(goal));
        goalText.setPosition(sf::Vector2f(30, -80));
        goalText.setColor(sf::Color(255, 0, 0));
        goalText.setString(os.str());
        window.draw(goalText);
    }
    {
        std::ostringstream os;
        os << score;
        goalText.setPosition(sf::Vector2f(600, -80));
        goalText.setColor(sf::Color(255, 255, 255));
        goalText.setString(os.str());
        window.draw(goalText);
    }

    window.display();
}

void World::renderList(const std::vector<EntityPtr>& entities) {
    for(auto it = entities.begin(), end = entities.end(); it != end; ++it) {
        (*it)->render(window);
    }
}

void World::nextLetter(int bonus) {
    if( bonus == 0 && deadline != 0 ) {
        gameover = true;
    }
    deadline = clock.getElapsedTime().asSeconds() + 11;
    goal = rand() % 26 + 'a';
    score += bonus;
}

void World::update() {
    int time = clock.getElapsedTime().asMilliseconds() / 16.6666667f ;
    int frames = std::min(time - lastUpdateTime, MAX_FRAME_GAP);
    if(frames > 0) {
        for(int i = 0; i < frames; ++i) {
            step();
            if(deadline < clock.getElapsedTime().asSeconds()) {
                 nextLetter(0);
            }
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
