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

void Entity::update(float delta) {
    // PUSTE! Nie wywo³ujemy tu updateMovement(delta), 
    // poniewa¿ ruch obs³uguje CollisionManager w GameScreen.
}

int Entity::getHP() const {
    return combatStats.hp;
}

int Entity::getAttack() const {
    return combatStats.attack;
}

bool Entity::isAlive() const {
    return combatStats.hp > 0;
}

void Entity::takeDamage(int dmg) {
    combatStats.hp -= dmg;
}