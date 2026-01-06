#include "Enemy.hpp"
#include <iostream>
#include <cmath>

sf::Texture Enemy::sharedTexture;

Enemy::Enemy(sf::Vector2f position, sf::Vector2f size) : Movable(position, size) {
    // sprite.Resize(size);

    if (sharedTexture.getSize().x == 0) {
        if (!sharedTexture.loadFromFile("../assets/enemy.png")) {
            std::cerr << "Blad ladowania enemy.png\n";
        }
    }

    setTexture(sharedTexture);
    setPosition(position);

    auto texSize = sharedTexture.getSize();
    if (texSize.x > 0 && texSize.y > 0) {
        setScale(
            sf::Vector2f(
                size.x / texSize.x,
                size.y / texSize.y
            )
        );
    }

    speed_vector = { 0.f, 0.f };
    max_speed = 0.f;
    min_speed = 0.f;
}

void Enemy::update(float delta, const sf::Vector2f& playerPosition) {
    sf::Vector2f enemyPos = getPosition();

    sf::Vector2f direction = playerPosition - enemyPos;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0.f) {
        direction.x /= length;
        direction.y /= length;
    }

    float enemySpeed = 200.f; // px/s � �atwe do tuningu

    speed_vector = direction * enemySpeed;

    move(speed_vector.x * delta, speed_vector.y * delta);
}