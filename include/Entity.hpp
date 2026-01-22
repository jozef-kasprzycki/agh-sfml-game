#pragma once
#include "Movable.hpp"
#include "CombatStats.hpp"

// Bazowa klasa dla wszystkich "¿ywych" obiektów w grze
class Entity : public Movable {
protected:
    CombatStats combatStats;

public:
    Entity(
        sf::Vector2f position,
        sf::Vector2f size,
        const CombatStats& stats
    );

    virtual ~Entity() = default;

    int getHP() const;
    virtual void takeDamage(int dmg);

    // Dostêp do statystyk
    const CombatStats& getStats() const;

    virtual void update(float delta) = 0;
};