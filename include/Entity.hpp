#pragma once
#include "Movable.hpp"

// Bazowa klasa dla wszystkich "¿ywych" obiektów w grze
// (Player, Enemy, Boss, NPC itd.)
class Entity : public Movable {
protected:
    int hp;

public:
    Entity(
        sf::Vector2f position,
        sf::Vector2f size,
        int hp
    );

    virtual ~Entity() = default;

    int getHP() const;
    virtual void takeDamage(int dmg);

    // Ka¿da encja MUSI mieæ update
    virtual void update(float delta) = 0;
};
