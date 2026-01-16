#pragma once
#include "EnemyState.hpp"

class EnemyChaseState : public EnemyState {
public:
    void update(
        EnemyBase& enemy,
        EnemyStateMachine& machine,
        float delta,
        const sf::Vector2f& playerPos
    ) override;
};
