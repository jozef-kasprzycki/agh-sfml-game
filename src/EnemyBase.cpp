#include "EnemyBase.hpp"

EnemyBase::EnemyBase(
    sf::Vector2f position,
    sf::Vector2f size,
    int hp
)
    : Entity(position, size, hp),
    detectionRadius(500.f),
    chaseRadius(300.f)
{
    max_speed = 300.f;
    min_speed = 10.f;
}
