#include "Game.hpp"
#include "CollisionManager.hpp"
#include <random>

//funkcja zwraca losową pozycję, która nie koliduje z Playerem i zapewnia, że obiekt mieści się w oknie gry
//tworzy tymczasowy hitbox (candidate) i sprawdza kolizję z forbidden (hitbox Playera)
sf::Vector2f getRandomPositionNoCollision(
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

Game::Game()
    : window(sf::VideoMode(1000, 600), "AGH SFML Game"),
    player({ 200.f, 200.f }, { 50.f, 50.f }, 100)
{
    const sf::Vector2f obstacleSize(50.f, 50.f);

    obstacles.emplace_back(sf::Vector2f(400, 300), obstacleSize);
    collisionManager.addObstacle(obstacles.back().getGlobalBounds());

    enemies.emplace_back(
        getRandomPositionNoCollision(player.getGlobalBounds(), { 50.f, 50.f }),
        sf::Vector2f(50.f, 50.f)
    );
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
    player.update(delta);

    sf::Vector2f playerDelta = player.getSpeedVector() * delta;
    collisionManager.tryMove(player, playerDelta);

    for (auto& enemy : enemies) {
        enemy.behave(delta, player.getPosition());

        sf::Vector2f enemyDelta = enemy.getSpeedVector() * delta; 
        collisionManager.tryMove(enemy, enemyDelta);              

        if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
            player.takeDamage(1); // ❌ resolveCollision USUNIĘTE
        }
    }
}

void Game::render() {
    window.clear();

    for (auto& obstacle : obstacles)
        obstacle.draw(window);

    for (auto& enemy : enemies)
        enemy.draw(window);

    player.draw(window);
    window.display();
}