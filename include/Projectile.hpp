#pragma once
#include "Movable.hpp"

enum class ProjectileOwner {
    Player,
    Enemy
};

class Projectile : public Movable {
protected:
    int damage;
    ProjectileOwner owner;
    float lifetime;

public:
    Projectile(
        sf::Vector2f position,
        sf::Vector2f size,
        sf::Vector2f velocity,
        int damage,
        ProjectileOwner owner
    );

    // Zwyk³a metoda, bez override, bo Movable nie ma virtual update
    void update(float delta);

    int getDamage() const;
    ProjectileOwner getOwner() const;
    bool isExpired() const;
};