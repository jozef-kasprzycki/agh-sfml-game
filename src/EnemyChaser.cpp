#include "EnemyChaser.hpp"
#include "TextureManager.hpp"
#include <cmath>

EnemyChaser::EnemyChaser(
    sf::Vector2f position,
    sf::Vector2f size
)
    : EnemyBase(position, size, 50)
{
    setTexture(TextureManager::get("../assets/enemy.png"));
}

void EnemyChaser::behave(float delta, const sf::Vector2f& playerPos) {
    sf::Vector2f dir = playerPos - getPosition();
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    if (length > detectionRadius)
        return;

    if (length != 0.f)
        dir /= length;

    speed_vector += dir * (600.f * delta);

    float speed = std::sqrt(
        speed_vector.x * speed_vector.x +
        speed_vector.y * speed_vector.y
    );

    if (speed > max_speed)
        speed_vector *= (max_speed / speed);
}

void EnemyChaser::update(float delta) {
    updateMovement(delta);
}