#include "Enemy.hpp"
#include <iostream>
#include <cmath>

sf::Texture Enemy::sharedTexture;

Enemy::Enemy(sf::Vector2f position, sf::Vector2f size) : Movable(position, size) {

    if (!sharedTexture.loadFromFile("../assets/enemy.png")) {
        std::cerr << "Blad ladowania enemy.png\n";
    }

    setTexture(sharedTexture);
}

void Enemy::update(float delta, const sf::Vector2f& playerPosition) {
    sf::Vector2f enemyPos = getPosition();

    sf::Vector2f direction = playerPosition - enemyPos;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0.f) {
        direction.x /= length;
        direction.y /= length;
    }

    float enemySpeed = 400.f; // px/s � �atwe do tuningu

    if (length <= 500)
        speed_vector = direction * enemySpeed;
    else{
        speed_vector.x *= 0.2;
        speed_vector.y *= 0.2;
    }

    //move(sf::Vector2f(speed_vector.x * delta, speed_vector.y * delta));
}