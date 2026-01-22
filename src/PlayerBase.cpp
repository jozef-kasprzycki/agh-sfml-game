#include "PlayerBase.hpp"
#include <iostream>

PlayerBase::PlayerBase(
    sf::Vector2f position,
    sf::Vector2f size,
    const CombatStats& stats
)
    : Entity(position, size, stats),
    inputDirection(0.f, 0.f),
    shootDirection(0.f, 0.f),
    currentCooldown(0.f)
{
    max_speed = 600.f;
    min_speed = 100.f;
}

void PlayerBase::takeDamage(int dmg) {
    Entity::takeDamage(dmg);
    std::cout << "\nPlayer hit, hp=" << getHP();
}

void PlayerBase::update(float delta) {
    handleInput();
    applyMovementPhysics(delta);

    if (currentCooldown > 0.f) {
        currentCooldown -= delta;
    }
}

bool PlayerBase::canShoot() const {
    return currentCooldown <= 0.f;
}

void PlayerBase::resetCooldown() {
    currentCooldown = combatStats.fireRate;
}

float PlayerBase::getProjectileSpeed() const {
    return combatStats.projectileSpeed;
}

bool PlayerBase::isShooting() const {
    return shootDirection.x != 0.f || shootDirection.y != 0.f;
}

sf::Vector2f PlayerBase::getShootDirection() const {
    return shootDirection;
}

void PlayerBase::applyMovementPhysics(float delta) {
    // * Y axis
    if (inputDirection.y < 0.f) { // W
        if (speed_vector.y > -max_speed)
            speed_vector.y -= max_speed * delta;
        animate(1);
    }
    else if (inputDirection.y > 0.f) { // S
        if (speed_vector.y < max_speed)
            speed_vector.y += max_speed * delta;
        animate(2);
    }
    else if (speed_vector.y > min_speed) {
        speed_vector.y -= max_speed * delta;
    }
    else if (speed_vector.y < -min_speed) {
        speed_vector.y += max_speed * delta;
    }
    else {
        speed_vector.y = 0.f;
        animate(0);
    }

    // * X axis
    if (inputDirection.x < 0.f) { // A
        if (speed_vector.x > -max_speed)
            speed_vector.x -= max_speed * delta;
        animate(4);
    }
    else if (inputDirection.x > 0.f) { // D
        if (speed_vector.x < max_speed)
            speed_vector.x += max_speed * delta;
        animate(3);
    }
    else if (speed_vector.x > min_speed) {
        speed_vector.x -= max_speed * delta;
    }
    else if (speed_vector.x < -min_speed) {
        speed_vector.x += max_speed * delta;
    }
    else {
        speed_vector.x = 0.f;
    }
}