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
    currentCooldown(0.f),
    invincibilityTimer(0.f) // Startujemy bez nietykalnoœci
{
    max_speed = 600.f;
    min_speed = 100.f;
}

void PlayerBase::takeDamage(int dmg) {
    // Jeœli jest nietykalny, ignorujemy obra¿enia
    if (invincibilityTimer > 0.f) return;

    // Jeœli nie, przyjmujemy damage
    Entity::takeDamage(dmg);
    std::cout << "\nPlayer hit! HP=" << getHP() << std::endl;

    // Aktywujemy nietykalnoœæ na 1.0 sekundy
    invincibilityTimer = 1.0f;

    // Wizualny efekt uderzenia (czerwony)
    setColor(sf::Color(255, 0, 0, 128));
}

void PlayerBase::update(float delta) {
    handleInput();
    applyMovementPhysics(delta);

    if (currentCooldown > 0.f) {
        currentCooldown -= delta;
    }

    // Obs³uga nietykalnoœci
    if (invincibilityTimer > 0.f) {
        invincibilityTimer -= delta;

        // Jeœli czas siê skoñczy³
        if (invincibilityTimer <= 0.f) {
            invincibilityTimer = 0.f;
            setColor(sf::Color::White); // Wróæ do normy
        }
        else {
            // Migotanie lub pó³przeŸroczystoœæ (tutaj: pó³przeŸroczystoœæ)
            // Jeœli min¹³ moment "czerwonego uderzenia" (np. 0.1s), ustaw na bia³y-przeŸroczysty
            if (invincibilityTimer < 0.9f) {
                setColor(sf::Color(255, 255, 255, 128));
            }
        }
    }
}

bool PlayerBase::isInvincible() const {
    return invincibilityTimer > 0.f;
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
    // Bez zmian...
    if (inputDirection.y < 0.f) {
        if (speed_vector.y > -max_speed) speed_vector.y -= max_speed * delta;
        animate(1);
    }
    else if (inputDirection.y > 0.f) {
        if (speed_vector.y < max_speed) speed_vector.y += max_speed * delta;
        animate(2);
    }
    else if (speed_vector.y > min_speed) { speed_vector.y -= max_speed * delta; }
    else if (speed_vector.y < -min_speed) { speed_vector.y += max_speed * delta; }
    else { speed_vector.y = 0.f; animate(0); }

    if (inputDirection.x < 0.f) {
        if (speed_vector.x > -max_speed) speed_vector.x -= max_speed * delta;
        animate(4);
    }
    else if (inputDirection.x > 0.f) {
        if (speed_vector.x < max_speed) speed_vector.x += max_speed * delta;
        animate(3);
    }
    else if (speed_vector.x > min_speed) { speed_vector.x -= max_speed * delta; }
    else if (speed_vector.x < -min_speed) { speed_vector.x += max_speed * delta; }
    else { speed_vector.x = 0.f; }
}