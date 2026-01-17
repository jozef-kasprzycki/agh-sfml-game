#include "GameScreen.hpp"
#include "LevelLoader.hpp"
#include <iostream>

// Helper functions copied from Game.cpp
sf::Vector2f GameScreen::getRandomPositionNoCollisionObstacle(
    const sf::FloatRect& forbidden,
    const sf::Vector2f& size
) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distX(0.f, 1000.f - size.x);
    std::uniform_real_distribution<float> distY(0.f, 600.f - size.y);

    sf::FloatRect candidate;

    do {
        candidate.left = distX(gen);
        candidate.top = distY(gen);
        candidate.width = size.x;
        candidate.height = size.y;
    } while (candidate.intersects(forbidden));

    return { candidate.left, candidate.top };
}

int GameScreen::getRandomObstacleCount() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 5);
    return dist(gen);
}

sf::Vector2f GameScreen::getRandomPositionNoCollisionMultiple(
    const sf::FloatRect& playerBounds,
    const std::vector<Obstacle>& obstacles,
    const sf::Vector2f& size
) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distX(0.f, 1000.f - size.x);
    std::uniform_real_distribution<float> distY(0.f, 600.f - size.y);

    sf::FloatRect candidate;

    bool collision;
    do {
        collision = false;

        candidate = {
            distX(gen),
            distY(gen),
            size.x,
            size.y
        };

        if (candidate.intersects(playerBounds))
            collision = true;

        for (const auto& obstacle : obstacles) {
            if (candidate.intersects(obstacle.getGlobalBounds())) {
                collision = true;
                break;
            }
        }

    } while (collision);

    return { candidate.left, candidate.top };
}

GameScreen::GameScreen() : collisionManager() {
    player = std::make_unique<PlayerBasic>(
        sf::Vector2f(10.f, 10.f),
        sf::Vector2f(50.f, 50.f),
        100
    );
    
    level = LevelLoader::loadFromFile("../levels/level_01.json");
    
    background = std::make_unique<Background>(level.size);
    background->set(level.background);
    player->setPosition(level.playerStart);

    for (const auto& obs : level.obstacles) {
        obstacles.emplace_back(
            obs.bounds.getPosition(), 
            obs.bounds.getSize(),
            obs.texture_path
        );
        
        collisionManager.addObstacle(obs.bounds);
    }

    const sf::Vector2f enemySize(50.f, 50.f);

    sf::Vector2f enemyPos = getRandomPositionNoCollisionMultiple(
        player->getGlobalBounds(),
        obstacles,
        enemySize
    );

    enemies_chasers.push_back(
        std::make_unique<EnemyChaser>(enemyPos, enemySize)
    );

    for (const auto& enemy : level.enemies) {
        if (enemy.type == "chaser") {
            enemies_chasers.push_back(
                std::make_unique<EnemyChaser>(                
                    enemy.bounds.getPosition(), 
                    enemy.bounds.getSize()
                )
            );
        } else if (enemy.type == "bomber") {
            std::cout << "bomber\n";
        } else {
            std::cout << enemy.type << " is invalid enemy name.\n";
        }
    }
}

void GameScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void GameScreen::update(float delta) {
    player->update(delta);
    sf::Vector2f pd = player->getSpeedVector() * delta;
    collisionManager.tryMove(*player, pd);

    for (auto& enemy : enemies_chasers) {
        enemy->behave(delta, player->getPosition());
        sf::Vector2f ed = enemy->getSpeedVector() * delta;
        collisionManager.tryMove(*enemy, ed);
        enemy->update(delta);
    }

    // Win/loss logic
    if (player->getHP() <= 0) {
        finished = true;
        isWin = false;
    } else if (enemies_chasers.empty()) {
        finished = true;
        isWin = true;
    }
}

void GameScreen::render(sf::RenderWindow& window) {
    window.clear();
    
    background->draw(window);
    player->draw(window);

    for (auto& obstacle : obstacles) {
        obstacle.draw(window);
    }

    for (auto& enemy : enemies_chasers) {
        enemy->draw(window);
    }

    window.display();
}

bool GameScreen::isFinished() const {
    return finished;
}

std::string GameScreen::getNextScreen() const {
    return isWin ? "gameover_win" : "gameover_lose";
}