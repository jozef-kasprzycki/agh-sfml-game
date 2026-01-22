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
#include "ProjectileManager.hpp"
#include "Door.hpp"
#include "TextManager.hpp" 

#include <vector>
#include <memory>
#include <string>
#include <random>

class GameScreen : public Screen {
private:
    CollisionManager collisionManager;
    std::unique_ptr<PlayerBase> player;
    std::unique_ptr<Background> background;

    std::vector<Obstacle> obstacles;
    std::vector<std::unique_ptr<EnemyBase>> enemies_chasers;
    std::vector<std::unique_ptr<Door>> doors;

    ProjectileManager projectileManager;

    std::unique_ptr<TextManager> textManager;

    struct LevelData levelData;

    bool finished = false;
    bool isWin = false;

    // Zmienne pauzy
    bool isPaused = false;
    sf::Font font;
    sf::Text pauseText;
    sf::RectangleShape pauseOverlay;

    // NOWE: Zmienna przechowuj¹ca ID nastêpnego ekranu (jeœli jest pusta, u¿ywamy logiki win/lose)
    std::string nextScreenID;

    std::string pendingLevelLoad;
    static bool isAdminMode;

    sf::Vector2f getRandomPositionNoCollisionObstacle(const sf::FloatRect& forbidden, const sf::Vector2f& size);
    int getRandomObstacleCount();
    sf::Vector2f getRandomPositionNoCollisionMultiple(const sf::FloatRect& playerBounds, const std::vector<Obstacle>& obstacles, const sf::Vector2f& size);

    void loadLevel(const std::string& path);

public:
    GameScreen();
    static void setAdminMode(bool admin);

    void handleEvents(sf::RenderWindow& window) override;
    void update(float delta) override;
    void render(sf::RenderWindow& window) override;
    bool isFinished() const override;
    std::string getNextScreen() const override;
};