#include "EnemyStateMachine.hpp"
#include "EnemyState.hpp"
#include "EnemyBase.hpp"

EnemyStateMachine::EnemyStateMachine() = default;
EnemyStateMachine::~EnemyStateMachine() = default;

void EnemyStateMachine::changeState(
    EnemyBase& enemy,
    std::unique_ptr<EnemyState> next
) {
    if (current)
        current->onExit(enemy);

    current = std::move(next);

    if (current)
        current->onEnter(enemy);
}

void EnemyStateMachine::update(
    EnemyBase& enemy,
    float delta,
    const sf::Vector2f& playerPos
) {
    if (current)
        current->update(enemy, *this, delta, playerPos);
}
