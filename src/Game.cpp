#include "Game.hpp"
#include "CollisionManager.hpp"
#include "LevelLoader.hpp"
//#include <iostream>
#include <random>

//funkcja zwraca losową pozycję, która nie koliduje z Playerem i zapewnia, że obiekt mieści się w oknie gry
//tworzy tymczasowy hitbox (candidate) i sprawdza kolizję z forbidden (hitbox Playera)
sf::Vector2f getRandomPositionNoCollisionObstacle(
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

int getRandomObstacleCount() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 5);
    return dist(gen);
}

sf::Vector2f getRandomPositionNoCollisionMultiple(
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


Game::Game()
    : window(sf::VideoMode(1000, 600), "AGH SFML Game"),
    collisionManager()
{
    LevelData level = LevelLoader::loadFromFile("../levels/level_01.json");
    window.setSize(level.size);

    player = std::make_unique<PlayerBasic>(
        sf::Vector2f(10.f, 10.f),
        sf::Vector2f(50.f, 50.f),
        100
    );

    player->setPosition(level.playerStart);

    for (const auto& obs : level.obstacles) {
        obstacles.emplace_back(
            obs.bounds.getPosition(), 
            obs.bounds.getSize(),
            obs.texture_path
        );
        
        collisionManager.addObstacle(obs.bounds);
    }

    for (const auto& enemy : level.enemies) {
        if (enemy.type == "chaser") {
            enemies_chasers.emplace_back(
                enemy.bounds.getPosition(), 
                enemy.bounds.getSize()
            );
        } else if (enemy.type == "bomber") { // bomber - cokolwiek
            std::cout << "bomber\n";
        } else {
            std::cout << enemy.type << " is invalid enemy name.\n";
        }
    }
}

void Game::run() {
    while (window.isOpen()) {
        float delta = clock.restart().asSeconds();
        processEvents();
        update(delta);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update(float delta) {
    // Aktualizacja klas przyjmujących czas jako paramter
    player->update(delta);
    sf::Vector2f pd = player->getSpeedVector() * delta;
    collisionManager.tryMove(*player, pd);


    /*
    for (const auto& obstacle : obstacles) {
        if (player.getGlobalBounds().intersects(obstacle.getGlobalBounds())) {
            CollisionManager::resolveCollision(
                player,
                obstacle.getGlobalBounds()
            );
        }
    }
        */

    for (auto& enemy : enemies_chasers) {

        //pogoń za środkiem gracza
        //sf::FloatRect pb = player->getGlobalBounds();

        enemy.behave(delta, player->getPosition());
        sf::Vector2f ed = enemy.getSpeedVector() * delta;
        collisionManager.tryMove(enemy, ed);

        //enemy.update(delta, player.getBounds().getPosition());
    }
}

void Game::render() {
    //window.clear();
    window.clear(sf::Color(30, 30, 30)); //sprawdza widoczność player i obstacle
    //window.clear(sf::Color::White); //sprawdza czy nie ma przezroczystości
    // Dodać renderowanie różnych elementów gry

    //renderowanie przeszkód
    for (auto& obstacle : obstacles) {
        obstacle.draw(window);
    }

    //renderowanie wrogów
    for (auto& enemy : enemies_chasers) {
        enemy.draw(window);
    }

    player->draw(window);
    window.display();
}
