#pragma once
#include <SFML/Graphics.hpp>
#include "CollisionManager.hpp"
#include "Player.hpp"
#include "Obstacle.hpp"
#include "Enemy.hpp"
#include <vector>

class Game {
private:
    sf::RenderWindow window;
    sf::Clock clock;

    CollisionManager collisionManager;
    Player player;

    std::vector<Obstacle> obstacles;
    std::vector<Enemy> enemies;

    void processEvents();
    void update(float delta);
    void render();

public:
    Game();
    void run();
};
