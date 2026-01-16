#pragma once
#include <SFML/Graphics.hpp>

class EnemyBase;
class EnemyStateMachine;

class EnemyState {
public:
    virtual ~EnemyState() = default;

    virtual void onEnter(EnemyBase&) {}
    virtual void onExit(EnemyBase&) {}

    virtual void update(
        EnemyBase& enemy,
        EnemyStateMachine& machine,
        float delta,
        const sf::Vector2f& playerPos
    ) = 0;
};
