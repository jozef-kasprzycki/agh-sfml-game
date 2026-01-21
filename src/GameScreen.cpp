#include <bits/stdc++.h>
#include <iostream>
#include "GameScreen.hpp"
#include "LevelLoader.hpp"

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

    // Corner info: informacje typu FPS z boku ekranu
    if (!font.loadFromFile("../assets/font.ttf")) 
        { std::cerr << "Blad ladowania czcionki!\n"; }
        
    // Style dla info w roku ekranu
    leftCornerInfo.setFont(font);
    leftCornerInfo.setCharacterSize(24);
    leftCornerInfo.setPosition(10,10);
    leftCornerInfo.setOutlineColor(sf::Color::Black);
    
    // Style dla powiadomień wyświetlanych na środku
    centerInfo.setFont(font);
    centerInfo.setCharacterSize(24);
    centerInfo.setPosition(500, 300);
    centerInfo.setOutlineColor(sf::Color::Black);
    centerInfo.setFillColor(sf::Color::Red);
    centerInfoInterval = 0.5;

    timeElapsedSec = 0;

    centerScreenNotifications.push_back({"Game started!", INFO, 2, 0});
    centerScreenNotifications.push_back({"Game is going!", WARNING, 6, 0});
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
    timeElapsedSec += delta;

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

    // Tutaj należy dodać konstrukcje warunkowe
    // które dodają powidomienia, które są 
    // wyświetlane na środku ekranu.

    //if(player->getInjured()){
    //     ...
    //     centerScreenNotifications.append(...)
    // }

    // Aktualizacja powiadomień wyświetanych na środku ekranu
    // iterując po liście powiadomień i dodając do wyświetlania 
    // te nieprzeterminowane 
    centerInfo.setString("");

    for (auto& notification : centerScreenNotifications){
        notification.elapsedTime += delta;
        if (notification.elapsedTime < notification.lifetime)
            centerInfo.setString(centerInfo.getString() + "\n" + notification.text);
    }

    // Wyśrodkowanie napisu
    centerInfo.setOrigin(
        centerInfo.getGlobalBounds().width/2, 
        centerInfo.getGlobalBounds().height/2
    );

    // Wyświatlanie info w rogu ekranu:
    // fps, czas, hp
    leftCornerInfo.setString(
        std::to_string((int)(1/delta)) + " FPS\nTime: " 
        + std::to_string((int)timeElapsedSec) + " sec."
        + "\nHP: " + std::to_string(player->getHP())
    );
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

    window.draw(leftCornerInfo);
    window.draw(centerInfo);

    window.display();
}

bool GameScreen::isFinished() const {
    return finished;
}

std::string GameScreen::getNextScreen() const {
    return isWin ? "gameover_win" : "gameover_lose";
}