#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Obstacle.hpp"
#include <vector>

class Game {
private:
    sf::RenderWindow window;
    sf::Clock clock;

    Player player;

    std::vector<Obstacle> obstacles;

    void processEvents();
    void update(float delta);
    void render();

public:
    Game();
    void run();
};
