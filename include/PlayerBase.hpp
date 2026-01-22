#pragma once
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

class PlayerBase : public Entity {
protected:
    float currentCooldown;
    float invincibilityTimer;

    // NOWE: Tryb boga (Admin)
    bool godMode = false;

    sf::Vector2f inputDirection;
    sf::Vector2f shootDirection;

    void applyMovementPhysics(float delta);
    virtual void handleInput() = 0;

public:
    PlayerBase(
        sf::Vector2f position,
        sf::Vector2f size,
        const CombatStats& stats
    );

    virtual ~PlayerBase() = default;

    void update(float delta) override;

    void takeDamage(int dmg) override;

    bool isShooting() const;
    sf::Vector2f getShootDirection() const;
    bool canShoot() const;
    void resetCooldown();
    float getProjectileSpeed() const;

    bool isInvincible() const;

    // NOWE
    void setGodMode(bool enabled); //Nazwa: Admin Has³o: Admin
};