#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

class World {
    private:
        sf::RenderWindow& window;

    public:
        sf::Vector2f resolution;
        sf::FloatRect screen;
        std::vector<std::shared_ptr<Entity>> entities;

        World(sf::RenderWindow& window)
            : window(window),
            resolution(window.getSize()),
            screen(sf::Vector2f(0, 0), resolution) {

        }

        ~World() { }

        void addEntity(const std::shared_ptr<Entity>& entity) {
            entities.push_back(entity);
        }

        void render() {
            window.clear();
            for(size_t i = 0; i != entities.size(); ++i) {
                entities[i]->render(window);
            }
            window.display();
        }

        void update(float dt) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            for(size_t i = 0; i != entities.size(); ++i) {
                entities[i]->update(*this, dt);
            }
        }

        void loop() {
            while (window.isOpen()) {
                render();
                update(1.0); // TODO.
            }
        }
};

#endif