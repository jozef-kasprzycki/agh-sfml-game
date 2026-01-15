#include "EnemyChaseState.hpp"
#include "EnemyBase.hpp"
#include "EnemyStateMachine.hpp"
#include "EnemyIdleState.hpp"
#include <cmath>

void EnemyChaseState::update(
    EnemyBase& enemy,
    EnemyStateMachine& machine,
    float delta,
    const sf::Vector2f& playerPos
) {
    sf::Vector2f toPlayer = playerPos - enemy.getPosition();
    float dist = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);

    // histereza – wyjœcie dopiero POZA detectionRadius
    if (dist > enemy.getDetectionRadius() * 1.1f) {
        machine.changeState(
            enemy,
            std::make_unique<EnemyIdleState>()
        );
        return;
    }

    if (dist > 0.f)
        toPlayer /= dist;

    float desiredSpeed = enemy.getMaxSpeed();
    if (dist < enemy.getChaseRadius()) {
        desiredSpeed *= (dist / enemy.getChaseRadius());
    }

    enemy.steerTowards(toPlayer * desiredSpeed, delta);
}
