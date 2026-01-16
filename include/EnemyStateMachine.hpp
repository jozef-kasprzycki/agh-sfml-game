#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

class EnemyBase;
class EnemyState;

class EnemyStateMachine {
private:
    std::unique_ptr<EnemyState> current;

public:
    //EnemyStateMachine() = default;
    EnemyStateMachine();
    ~EnemyStateMachine();

    void changeState(EnemyBase& enemy, std::unique_ptr<EnemyState> next);

    void update(
        EnemyBase& enemy,
        float delta,
        const sf::Vector2f& playerPos
    );
};
