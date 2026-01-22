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
#include "TextManager.hpp" // NOWE

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

    // NOWE
    // TextManager musi byæ zainicjalizowany PO za³adowaniu czcionki,
    // wiêc wskaŸnik lub std::optional, albo po prostu inicjalizacja w ciele konstruktora
    // U¿yjmy unique_ptr dla bezpieczeñstwa kolejnoœci inicjalizacji
    std::unique_ptr<TextManager> textManager;

    struct LevelData levelData;

    bool finished = false;
    bool isWin = false;
    bool isPaused = false;

    sf::Font font;
    sf::Text pauseText;
    sf::RectangleShape pauseOverlay;

    std::string pendingLevelLoad;

    sf::Vector2f getRandomPositionNoCollisionObstacle(const sf::FloatRect& forbidden, const sf::Vector2f& size);
    int getRandomObstacleCount();
    sf::Vector2f getRandomPositionNoCollisionMultiple(const sf::FloatRect& playerBounds, const std::vector<Obstacle>& obstacles, const sf::Vector2f& size);

    void loadLevel(const std::string& path);

    static bool isAdminMode;

public:
    GameScreen();

    // Metoda statyczna do ustawiania trybu (wo³ana z AuthScreen)
    static void setAdminMode(bool admin);

    void handleEvents(sf::RenderWindow& window) override;
    void update(float delta) override;
    void render(sf::RenderWindow& window) override;
    bool isFinished() const override;
    std::string getNextScreen() const override;
};