#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

class World {
    private:
        static const int MAX_FRAME_GAP = 3;

        int lastUpdateTime;
        sf::Clock clock;
        sf::RenderWindow& window;
        sf::Vector2f resolution;
        sf::FloatRect screen;
        std::vector<std::shared_ptr<Entity>> entities;

    public:
        World(sf::RenderWindow& window)
            : lastUpdateTime(0),
            window(window),
            resolution(window.getSize()),
            screen(sf::Vector2f(0, 0), resolution) { }

        ~World() { }

        const sf::Vector2f& getResolution() const {
            return resolution;
        }

        const sf::FloatRect& getScreen() const {
            return screen;
        }

        void addEntity(std::shared_ptr<Entity>& entity) {
            entities.push_back(entity);
        }

        const std::shared_ptr<Entity>& entityAt(size_t index) const {
            return entities[index];
        }

        std::shared_ptr<Entity>& entityAt(size_t index) {
            return entities[index];
        }

        size_t getEntityCount() const {
            return entities.size();
        }

        void loop() {
            while(window.isOpen()) {
                render();
                update();
            }
        }

    private:
        void render() {
            window.clear();
            for(auto it = entities.begin(), end = entities.end(); it != end; ++it) {
                (*it)->render(window);
            }
            window.display();
        }

        void update() {
            int time = clock.getElapsedTime().asMilliseconds() / 10;
            int frames = std::min(time - lastUpdateTime, MAX_FRAME_GAP);
            if(frames > 0) {
                for(int i = 0; i < frames; ++i) {
                    step();
                }
                lastUpdateTime = time;
            } else {
                sf::sleep(sf::milliseconds(5));
            }
        }

        void step() {
            sf::Event event;
            while(window.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            for(auto it = entities.begin(), end = entities.end(); it != end; ++it) {
                (*it)->step(*this);
            }
        }
};

#endif