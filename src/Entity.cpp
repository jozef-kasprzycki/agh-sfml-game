#include "Entity.hpp"

Entity::Entity(
    sf::Vector2f position,
    sf::Vector2f size,
    const CombatStats& stats
)
    : Movable(position, size),
    combatStats(stats)
{
}

int Entity::getHP() const {
    return combatStats.hp;
}

void Entity::takeDamage(int dmg) {
    combatStats.hp -= dmg;
    if (combatStats.hp < 0) combatStats.hp = 0;
}

const CombatStats& Entity::getStats() const {
    return combatStats;
}