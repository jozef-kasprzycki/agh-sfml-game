#pragma once
#include "Movable.hpp"

enum class ProjectileOwner {
    Player,
    Enemy
};

class Projectile : public Movable {
protected:
    int damage;
    bool isCritical; // NOWE
    ProjectileOwner owner;
    float lifetime;

public:
    Projectile(
        sf::Vector2f position,
        sf::Vector2f size,
        sf::Vector2f velocity,
        int damage,
        bool isCritical, // NOWE
        ProjectileOwner owner
    );

    void update(float delta);
    int getDamage() const;
    bool getIsCritical() const; // NOWE
    ProjectileOwner getOwner() const;
    bool isExpired() const;
};