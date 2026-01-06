#include "Game.hpp"
#include "CollisionManager.hpp"
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
            if (candidate.intersects(obstacle.getBounds())) {
                collision = true;
                break;
            }
        }

    } while (collision);

    return { candidate.left, candidate.top };
}


Game::Game()
    : window(sf::VideoMode(1000, 600), "AGH SFML Game"),
    player(sf::Vector2f(10.f, 10.f), sf::Vector2f(50, 50))
{
    const sf::Vector2f obstacleSize(50.f, 50.f);

    int obstacleCount = getRandomObstacleCount();

    for (int i = 0; i < obstacleCount; ++i) {
        sf::Vector2f pos = getRandomPositionNoCollisionObstacle(
            player.getGlobalBounds(),
            obstacleSize
        );

        obstacles.emplace_back(pos, obstacleSize);
    }

    const sf::Vector2f enemySize(50.f, 50.f);

    sf::Vector2f enemyPos = getRandomPositionNoCollisionMultiple(
        player.getGlobalBounds(),
        obstacles,
        enemySize
    );

    enemies.emplace_back(enemyPos, enemySize);

    sf::Texture playerTexture;
    playerTexture.loadFromFile("../assets/player.png");
    player.setTexture(playerTexture);
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
    player.update(delta);

    for (const auto& obstacle : obstacles) {
        if (player.getGlobalBounds().intersects(obstacle.getBounds())) {
            CollisionManager::resolveCollision(
                player,
                obstacle.getBounds()
            );
        }
    }

    for (auto& enemy : enemies) {

		//pogoń za środkiem gracza
        sf::FloatRect pb = player.getGlobalBounds();
        sf::Vector2f playerCenter(
            pb.left + pb.width / 2.f,
            pb.top + pb.height / 2.f
        );
        enemy.update(delta, playerCenter);


        //enemy.update(delta, player.getBounds().getPosition());


        if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
            CollisionManager::resolveCollision(
                player,
                enemy.getGlobalBounds()
            );
        }
    }

}

void Game::render() {
    window.clear();
    //window.clear(sf::Color(30, 30, 30)); //sprawdza widoczność player i obstacle
    //window.clear(sf::Color::White); //sprawdza czy nie ma przezroczystości
    // Dodać renderowanie różnych elementów gry

    //renderowanie przeszkód
    for (auto& obstacle : obstacles) {
        obstacle.draw(window);
    }


	//renderowanie wrogów
    for (auto& enemy : enemies) {
        enemy.draw(window);
    }


    player.draw(window);
    window.display();
}
