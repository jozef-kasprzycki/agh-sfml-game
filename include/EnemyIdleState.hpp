#pragma once
#include "EnemyState.hpp"

class EnemyIdleState : public EnemyState {
public:
    void update(
        EnemyBase& enemy,
        EnemyStateMachine& machine,
        float delta,
        const sf::Vector2f& playerPos
    ) override;
};
