#pragma once
#include "Screen.hpp"
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
#include <string>
#include <random>

class GameScreen : public Screen {
private:
    CollisionManager collisionManager;
    std::unique_ptr<PlayerBase> player;
    std::vector<Obstacle> obstacles;
    std::vector<std::unique_ptr<EnemyBase>> enemies_chasers;
    std::unique_ptr<Background> background;
    struct LevelData level;
    bool finished = false;
    bool isWin = false;

    sf::Vector2f getRandomPositionNoCollisionObstacle(const sf::FloatRect& forbidden, const sf::Vector2f& size);
    int getRandomObstacleCount();
    sf::Vector2f getRandomPositionNoCollisionMultiple(const sf::FloatRect& playerBounds, const std::vector<Obstacle>& obstacles, const sf::Vector2f& size);

public:
    GameScreen();
    void handleEvents(sf::RenderWindow& window) override;
    void update(float delta) override;
    void render(sf::RenderWindow& window) override;
    bool isFinished() const override;
    std::string getNextScreen() const override;
};