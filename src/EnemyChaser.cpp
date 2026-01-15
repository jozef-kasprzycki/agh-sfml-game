#include "EnemyChaser.hpp"
#include "TextureManager.hpp"

EnemyChaser::EnemyChaser(
    sf::Vector2f position,
    sf::Vector2f size
)
    : EnemyBase(position, size, 50)
{
    setTexture(TextureManager::get("../assets/enemy.png"));
    max_speed = 250.f;
    min_speed = 0.f;
}
