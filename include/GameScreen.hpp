#pragma once
#include "Screen.hpp"
#include "CollisionManager.hpp"
#include "PlayerBase.hpp"
#include "PlayerBasic.hpp"
#include "Obstacle.hpp"
#include "EnemyBase.hpp"
#include "EnemyChaser.hpp"
#include "LevelData.hpp"
#include  "Backgorund.hpp"
#include "ProjectileManager.hpp"
#include "Door.hpp" // NOWE

#include <vector>
#include <memory>
#include <string>
#include <random>

class GameScreen : public Screen {
private:
    CollisionManager collisionManager;
    std::unique_ptr<PlayerBase> player;
    std::unique_ptr<Background> background;

    // Kontenery obiektów
    std::vector<Obstacle> obstacles;
    std::vector<std::unique_ptr<EnemyBase>> enemies_chasers;
    std::vector<std::unique_ptr<Door>> doors; // NOWE

    ProjectileManager projectileManager;
    struct LevelData levelData;

    bool finished = false;
    bool isWin = false;

    // Zmienna przechowuj¹ca œcie¿kê do nastêpnego poziomu
    // Jeœli nie pusta -> znaczy ¿e w nastêpnej klatce ³adujemy poziom
    std::string pendingLevelLoad;

    // Helpery
    sf::Vector2f getRandomPositionNoCollisionObstacle(const sf::FloatRect& forbidden, const sf::Vector2f& size);
    int getRandomObstacleCount();
    sf::Vector2f getRandomPositionNoCollisionMultiple(const sf::FloatRect& playerBounds, const std::vector<Obstacle>& obstacles, const sf::Vector2f& size);

    // NOWE: Metoda ³aduj¹ca poziom
    void loadLevel(const std::string& path);

public:
    GameScreen();
    void handleEvents(sf::RenderWindow& window) override;
    void update(float delta) override;
    void render(sf::RenderWindow& window) override;
    bool isFinished() const override;
    std::string getNextScreen() const override;
};