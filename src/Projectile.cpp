#include "Projectile.hpp"
#include "TextureManager.hpp"
#include <cmath>

Projectile::Projectile(
    sf::Vector2f position,
    sf::Vector2f size,
    sf::Vector2f velocity,
    int damage,
    ProjectileOwner owner
)
    : Movable(position, size),
    damage(damage),
    owner(owner),
    lifetime(3.f) // Czas ¿ycia pocisku: 3 sekundy
{
    setTexture(TextureManager::get("../assets/bullet.png")); // Upewnij siê, ¿e masz ten plik lub zmieñ na inn¹
    speed_vector = velocity;
    max_speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
}

void Projectile::update(float delta) {
    lifetime -= delta;
    // Pocisk porusza siê "na œlepo" (bez kolizji ze œcianami w tym prostym wariancie)
    updateMovement(delta);
}

int Projectile::getDamage() const {
    return damage;
}

ProjectileOwner Projectile::getOwner() const {
    return owner;
}

bool Projectile::isExpired() const {
    return lifetime <= 0.f;
}