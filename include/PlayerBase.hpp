#pragma once
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

// Bazowa klasa gracza – wspólna logika ruchu, hp itd.
class PlayerBase : public Entity {
protected:
    void handleMovement(float delta);

public:
    PlayerBase(
        sf::Vector2f position,
        sf::Vector2f size,
        int hp
    );

    void update(float delta) override;
};
