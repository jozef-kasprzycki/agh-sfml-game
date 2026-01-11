#include "Entity.hpp"

Entity::Entity(
    sf::Vector2f position,
    sf::Vector2f size,
    int hp
)
    : Movable(position, size),
    hp(hp)
{
}

int Entity::getHP() const {
    return hp;
}

void Entity::takeDamage(int dmg) {
    hp -= dmg;
    if (hp < 0) hp = 0;
}
