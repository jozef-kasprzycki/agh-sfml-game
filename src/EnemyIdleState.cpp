#include "EnemyIdleState.hpp"
#include "EnemyBase.hpp"
#include "EnemyStateMachine.hpp"
#include "EnemyChaseState.hpp"
#include <cmath>

void EnemyIdleState::update(
    EnemyBase& enemy,
    EnemyStateMachine& machine,
    float,
    const sf::Vector2f& playerPos
) {
    sf::Vector2f diff = playerPos - enemy.getPosition();
    float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);

    // ³agodne hamowanie
    enemy.stopSoft();

    if (dist < enemy.getDetectionRadius()) {
        machine.changeState(
            enemy,
            std::make_unique<EnemyChaseState>()
        );
    }
}
