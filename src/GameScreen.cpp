#include "GameScreen.hpp"
#include "LevelLoader.hpp"
#include <iostream>
#include "Projectile.hpp"

// Helpery
sf::Vector2f GameScreen::getRandomPositionNoCollisionObstacle(const sf::FloatRect& forbidden, const sf::Vector2f& size) {
    static std::random_device rd; static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(0.f, 1000.f - size.x);
    std::uniform_real_distribution<float> distY(0.f, 600.f - size.y);
    sf::FloatRect candidate;
    do { candidate.left = distX(gen); candidate.top = distY(gen); candidate.width = size.x; candidate.height = size.y; } while (candidate.intersects(forbidden));
    return { candidate.left, candidate.top };
}

int GameScreen::getRandomObstacleCount() { return 3; }

sf::Vector2f GameScreen::getRandomPositionNoCollisionMultiple(const sf::FloatRect& playerBounds, const std::vector<Obstacle>& obstacles, const sf::Vector2f& size) {
    static std::random_device rd; static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(0.f, 1000.f - size.x);
    std::uniform_real_distribution<float> distY(0.f, 600.f - size.y);
    sf::FloatRect candidate;
    bool collision;
    do {
        collision = false;
        candidate = { distX(gen), distY(gen), size.x, size.y };
        if (candidate.intersects(playerBounds)) collision = true;
        for (const auto& obstacle : obstacles) {
            if (candidate.intersects(obstacle.getGlobalBounds())) { collision = true; break; }
        }
    } while (collision);
    return { candidate.left, candidate.top };
}

GameScreen::GameScreen() : collisionManager() {
    // Gracz tworzony raz
    player = std::make_unique<PlayerBasic>(
        sf::Vector2f(0.f, 0.f),
        sf::Vector2f(50.f, 50.f),
        100
    );

    // £adujemy pierwszy poziom
    loadLevel("../levels/level_01.json");
}

void GameScreen::loadLevel(const std::string& path) {
    std::cout << "Loading level: " << path << std::endl;

    obstacles.clear();
    enemies_chasers.clear();
    doors.clear();
    collisionManager = CollisionManager();

    levelData = LevelLoader::loadFromFile(path);

    background = std::make_unique<Background>(levelData.size);
    background->set(levelData.background);
    player->setPosition(levelData.playerStart);

    for (const auto& obs : levelData.obstacles) {
        obstacles.emplace_back(
            obs.bounds.getPosition(),
            obs.bounds.getSize(),
            obs.texture_path
        );
        collisionManager.addObstacle(obs.bounds);
    }

    for (const auto& d : levelData.doors) {
        doors.push_back(std::make_unique<Door>(
            d.bounds.getPosition(),
            d.bounds.getSize(),
            d.next_level_path
        ));
    }

    for (const auto& enemy : levelData.enemies) {
        if (enemy.type == "chaser") {
            enemies_chasers.push_back(
                std::make_unique<EnemyChaser>(
                    enemy.bounds.getPosition(),
                    enemy.bounds.getSize()
                )
            );
        }
        else if (enemy.type == "bomber") {
            std::cout << "Spawn bomber at " << enemy.bounds.left << "\n";
        }
    }
}

void GameScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
    }
}

void GameScreen::update(float delta) {
    if (!pendingLevelLoad.empty()) {
        if (pendingLevelLoad == "WIN") {
            finished = true;
            isWin = true;
        }
        else {
            loadLevel(pendingLevelLoad);
            pendingLevelLoad.clear();
        }
        return;
    }

    player->update(delta);
    sf::Vector2f pd = player->getSpeedVector() * delta;
    collisionManager.tryMove(*player, pd);

    if (player->isShooting() && player->canShoot()) {
        sf::Vector2f dir = player->getShootDirection();
        projectileManager.spawn(std::make_unique<Projectile>(
            player->getPosition() + sf::Vector2f(20, 20),
            sf::Vector2f(10.f, 10.f),
            dir * player->getProjectileSpeed(),
            25,
            ProjectileOwner::Player
        ));
        player->resetCooldown();
    }

    for (const auto& door : doors) {
        if (player->getGlobalBounds().intersects(door->getGlobalBounds())) {
            pendingLevelLoad = door->getNextLevel();
        }
    }

    for (auto& enemy : enemies_chasers) {
        enemy->behave(delta, player->getPosition());
        sf::Vector2f ed = enemy->getSpeedVector() * delta;
        collisionManager.tryMove(*enemy, ed);
        enemy->update(delta);
    }

    // UPDATE POCISKÓW - TERAZ PRZEKAZUJEMY PRZESZKODY
    projectileManager.update(delta, enemies_chasers, *player, obstacles);

    enemies_chasers.erase(std::remove_if(enemies_chasers.begin(), enemies_chasers.end(),
        [](const std::unique_ptr<EnemyBase>& e) { return e->getHP() <= 0; }), enemies_chasers.end());

    if (player->getHP() <= 0) {
        finished = true;
        isWin = false;
    }
}

void GameScreen::render(sf::RenderWindow& window) {
    window.clear();
    background->draw(window);

    for (const auto& door : doors) {
        door->draw(window);
    }

    player->draw(window);

    for (auto& obstacle : obstacles) {
        obstacle.draw(window);
    }

    for (auto& enemy : enemies_chasers) {
        enemy->draw(window);
    }

    projectileManager.render(window);
    window.display();
}

bool GameScreen::isFinished() const { return finished; }
std::string GameScreen::getNextScreen() const { return isWin ? "gameover_win" : "gameover_lose"; }