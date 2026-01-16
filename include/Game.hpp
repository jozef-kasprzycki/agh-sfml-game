#pragma once
#include <SFML/Graphics.hpp>
#include "CollisionManager.hpp"
#include "PlayerBase.hpp"
#include "PlayerBasic.hpp"
#include "Obstacle.hpp"
#include "EnemyBase.hpp"
#include "EnemyChaser.hpp"
#include "LevelData.hpp"
#include "Backgorund.hpp"
#include <vector>
#include <memory>

class Game {
private:
    sf::RenderWindow window;
    sf::Clock clock;

    CollisionManager collisionManager;
    std::unique_ptr<PlayerBase> player;

    std::vector<Obstacle> obstacles;
    std::vector<std::unique_ptr<EnemyBase>> enemies_chasers;
    std::unique_ptr<Background> background;
    
    struct LevelData level;

    void processEvents();
    void update(float delta);
    void render();

public:
    Game();
    void run();
};