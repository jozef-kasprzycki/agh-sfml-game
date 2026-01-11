#pragma once
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

// Bazowa klasa gracza – fizyka + hp
class PlayerBase : public Entity {
protected:
    int hp;

    // Kierunek ruchu przekazywany przez klasê pochodn¹
    sf::Vector2f inputDirection; // {-1, 0, 1}

    // Wspólna fizyka ruchu gracza (przyspieszanie + hamowanie)
    void applyMovementPhysics(float delta);

    // Ka¿dy gracz ustawia inputDirection
    virtual void handleInput() = 0;

public:
    PlayerBase(
        sf::Vector2f position,
        sf::Vector2f size,
        int hp
    );

    virtual ~PlayerBase() = default;

    void update(float delta) override;

    void takeDamage(int dmg);
};
