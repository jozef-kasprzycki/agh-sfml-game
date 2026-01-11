#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "PlayerBase.hpp"
#include "EnemyChaser.hpp"
#include "Obstacle.hpp"

class Game {
private:
    sf::RenderWindow window;
    sf::Clock clock;

    PlayerBase player;
    std::vector<EnemyChaser> enemies;
    std::vector<Obstacle> obstacles;

    void processEvents();
    void update(float delta);
    void render();

public:
    Game();
    void run();
};