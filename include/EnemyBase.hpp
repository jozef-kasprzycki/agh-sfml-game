#pragma once
#include "Entity.hpp"

// Bazowa klasa dla wszystkich wrogów
class EnemyBase : public Entity {
protected:
    float detectionRadius;
    float chaseRadius;

public:
    EnemyBase(
        sf::Vector2f position,
        sf::Vector2f size,
        int hp
    );

    virtual void behave(float delta, const sf::Vector2f& playerPos) = 0;
};
