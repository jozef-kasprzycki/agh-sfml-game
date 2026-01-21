#include "EnemyChaseState.hpp"
#include "EnemyIdleState.hpp"
#include "EnemyBase.hpp"
#include <cmath>

void EnemyChaseState::update(
    EnemyBase& enemy,
    EnemyStateMachine& machine,
    float delta,
    const sf::Vector2f& playerPos
) {
    // Ka¿dy enemy œciga swój w³asny punkt wokó³ gracza
    sf::Vector2f target = enemy.getChaseTarget(playerPos);
    sf::Vector2f toTarget = target - enemy.getPosition();

    float dist = std::sqrt(
        toTarget.x * toTarget.x +
        toTarget.y * toTarget.y
    );

    // Wyjœcie z poœcigu z histerez¹
    if (dist > enemy.getDetectionRadius() * 1.1f) {
        machine.changeState(
            enemy,
            std::make_unique<EnemyIdleState>()
        );
        return;
    }

    if (dist > 0.f)
        toTarget /= dist;

    float desiredSpeed = enemy.getMaxSpeed();

    // Zwolnienie przy zbli¿aniu siê do celu
    if (dist < enemy.getChaseRadius()) {
        desiredSpeed *= (dist / enemy.getChaseRadius());
    }

    enemy.steerTowards(toTarget * desiredSpeed, delta);
}