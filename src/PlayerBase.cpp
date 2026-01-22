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
    invincibilityTimer(0.f)
{
    max_speed = 600.f;
    min_speed = 100.f;
}

void PlayerBase::takeDamage(int dmg) {
    if (invincibilityTimer > 0.f) return;

    Entity::takeDamage(dmg);
    std::cout << "\nPlayer hit! HP=" << getHP() << std::endl;

    invincibilityTimer = 1.0f;
    setColor(sf::Color(255, 0, 0, 128));
}

void PlayerBase::update(float delta) {
    handleInput();
    applyMovementPhysics(delta);

    if (currentCooldown > 0.f) {
        currentCooldown -= delta;
    }

    if (invincibilityTimer > 0.f) {
        invincibilityTimer -= delta;

        if (invincibilityTimer <= 0.f) {
            invincibilityTimer = 0.f;
            setColor(sf::Color::White);
        }
        else {
            if (invincibilityTimer < 0.9f) {
                setColor(sf::Color(255, 255, 255, 128));
            }
        }
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

bool PlayerBase::isInvincible() const {
    return invincibilityTimer > 0.f;
}

void PlayerBase::applyMovementPhysics(float delta) {
    // --- 1. FIZYKA RUCHU (Obliczenia wektorów) ---

    // Oœ Y
    if (inputDirection.y < 0.f) { // W
        if (speed_vector.y > -max_speed)
            speed_vector.y -= max_speed * delta;
    }
    else if (inputDirection.y > 0.f) { // S
        if (speed_vector.y < max_speed)
            speed_vector.y += max_speed * delta;
    }
    else if (speed_vector.y > min_speed) {
        speed_vector.y -= max_speed * delta;
    }
    else if (speed_vector.y < -min_speed) {
        speed_vector.y += max_speed * delta;
    }
    else {
        speed_vector.y = 0.f;
    }

    // Oœ X
    if (inputDirection.x < 0.f) { // A
        if (speed_vector.x > -max_speed)
            speed_vector.x -= max_speed * delta;
    }
    else if (inputDirection.x > 0.f) { // D
        if (speed_vector.x < max_speed)
            speed_vector.x += max_speed * delta;
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

    // --- 2. LOGIKA ANIMACJI (Kierunek patrzenia) ---
    // Priorytet ma strzelanie. Jeœli strzelamy, patrzymy tam gdzie celujemy.
    // Jeœli nie strzelamy, patrzymy tam gdzie idziemy.

    int animRow = 0; // Domyœlnie dó³/idle (0)

    if (isShooting()) {
        // Priorytet: Strzelanie
        if (shootDirection.y < -0.1f)      animRow = 1; // Góra
        else if (shootDirection.y > 0.1f)  animRow = 2; // Dó³
        else if (shootDirection.x < -0.1f) animRow = 4; // Lewo
        else if (shootDirection.x > 0.1f)  animRow = 3; // Prawo
    }
    else {
        // Fallback: Ruch
        if (inputDirection.y < 0.f)      animRow = 1; // Góra
        else if (inputDirection.y > 0.f) animRow = 2; // Dó³
        else if (inputDirection.x < 0.f) animRow = 4; // Lewo
        else if (inputDirection.x > 0.f) animRow = 3; // Prawo
        else {
            // Jeœli stoi w miejscu i nie strzela -> 0 (Idle)
            // Mo¿na tu ewentualnie dodaæ zapamiêtywanie ostatniego kierunku,
            // ale na razie resetujemy do frontu.
            animRow = 0;
        }
    }

    animate(animRow);
}