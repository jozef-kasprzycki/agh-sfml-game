#include "EnemyGunner.hpp"
#include "TextureManager.hpp"
#include "EnemyGunnerWanderState.hpp"
#include <cmath>

EnemyGunner::EnemyGunner(sf::Vector2f position, sf::Vector2f size)
// HP=30, Attack=15, FireRate=2.0s, ProjectileSpeed=400
    : EnemyBase(position, size, 30)
{
    // Nadpisujemy statystyki bojowe w combatStats (odziedziczone po Entity)
    combatStats.fireRate = 2.0f;
    combatStats.projectileSpeed = 400.f;
    combatStats.attack = 15;

    // Wolny ruch
    max_speed = 100.f;
    min_speed = 100.f; // Chcemy sta³¹ prêdkoœæ

    try {
        setTexture(TextureManager::get("../assets/enemy.png"));
    }
    catch (...) {
        // Fallback w razie braku tekstury
    }

    // Gunner od razu wchodzi w stan Wander
    stateMachine.changeState(*this, std::make_unique<EnemyGunnerWanderState>());
}

std::unique_ptr<Projectile> EnemyGunner::tryShoot(float delta, const sf::Vector2f& playerPos) {
    if (currentCooldown <= 0.f) {
        // Oblicz kierunek do gracza
        sf::Vector2f dir = playerPos - getPosition();
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        if (len > 0.f) dir /= len;

        // Reset cooldownu
        currentCooldown = combatStats.fireRate;

        // Zwróæ pocisk
        return std::make_unique<Projectile>(
            getPosition() + sf::Vector2f(getSize().x / 2.f, getSize().y / 2.f),
            sf::Vector2f(10.f, 10.f),
            dir * combatStats.projectileSpeed,
            combatStats.attack,
            false, // isCritical = false (wrogowie na razie nie krytykuj¹)
            ProjectileOwner::Enemy
        );
    }
    return nullptr;
}