#pragma once
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

// Bazowa klasa gracza – fizyka + hp
class PlayerBase : public Entity {
protected:
    int hp;

    // Kierunek ruchu
    sf::Vector2f inputDirection; // {-1, 0, 1}

    // Kierunek strza³u (Nowoœæ)
    sf::Vector2f shootDirection;

    // Wspólna fizyka ruchu gracza
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

    // Gettery do strzelania (Nowoœæ)
    bool isShooting() const;
    sf::Vector2f getShootDirection() const;
};