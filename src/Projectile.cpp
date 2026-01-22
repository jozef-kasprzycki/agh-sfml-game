#include "Projectile.hpp"
#include "TextureManager.hpp"
#include <cmath>

Projectile::Projectile(
    sf::Vector2f position,
    sf::Vector2f size,
    sf::Vector2f velocity,
    int damage,
    bool isCritical,
    ProjectileOwner owner
)
    : Movable(position, size),
    damage(damage),
    isCritical(isCritical),
    owner(owner),
    lifetime(3.f)
{
    // Jeœli krytyk, mo¿na zmieniæ teksturê lub kolor (np. na ¿ó³ty)
    setTexture(TextureManager::get("../assets/bullet.png"));
    if (isCritical) {
        setColor(sf::Color(255, 200, 0)); // Z³oty odcieñ pocisku
    }

    speed_vector = velocity;
    max_speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
}

void Projectile::update(float delta) {
    lifetime -= delta;
    updateMovement(delta);
}

int Projectile::getDamage() const {
    return damage;
}

bool Projectile::getIsCritical() const {
    return isCritical;
}

ProjectileOwner Projectile::getOwner() const {
    return owner;
}

bool Projectile::isExpired() const {
    return lifetime <= 0.f;
}