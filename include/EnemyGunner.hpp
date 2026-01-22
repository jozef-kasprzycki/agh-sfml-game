#pragma once
#include "EnemyBase.hpp"

class EnemyGunner : public EnemyBase {
public:
    EnemyGunner(
        sf::Vector2f position,
        sf::Vector2f size
    );

    // Nadpisujemy tryShoot, ¿eby faktycznie strzela³
    std::unique_ptr<Projectile> tryShoot(float delta, const sf::Vector2f& playerPos) override;
};