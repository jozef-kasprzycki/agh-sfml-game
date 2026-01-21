#pragma once
#include "Movable.hpp"
#include "CombatStats.hpp"

// Bazowa klasa dla wszystkich "¿ywych" obiektów w grze
// (Player, Enemy, Boss, NPC itd.)
class Entity : public Movable {
public:
    Entity(sf::Vector2f pos, sf::Vector2f size, const CombatStats& stats);

    virtual void update(float delta);
    virtual ~Entity() = default;

    int getHP() const;
    int getAttack() const;
    void takeDamage(int dmg);
    bool isAlive() const;

protected:
    CombatStats combatStats;
};