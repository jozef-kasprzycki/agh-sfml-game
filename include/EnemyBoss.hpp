#pragma once
#include "EnemyBase.hpp"

enum class BossPhase {
    Moving,     // Tylko ruch (odpoczynek)
    SpiralFire, // Strzelanie dooko³a
    RapidFire   // Szybki ogieñ w gracza
};

class EnemyBoss : public EnemyBase {
private:
    BossPhase currentPhase;
    float phaseTimer;       // Czas trwania obecnej fazy
    float shootTimer;       // Czas do kolejnego strza³u wewn¹trz fazy
    float spiralAngle;      // K¹t dla ataku spiralnego

public:
    EnemyBoss(sf::Vector2f position, sf::Vector2f size);

    void update(float delta) override;

    // Nadpisujemy tryShoot, aby realizowaæ skomplikowane wzorce
    std::unique_ptr<Projectile> tryShoot(float delta, const sf::Vector2f& playerPos) override;
};