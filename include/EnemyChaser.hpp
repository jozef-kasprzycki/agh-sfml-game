#pragma once
#include "EnemyBase.hpp"

class EnemyChaser : public EnemyBase {
public:
    EnemyChaser(
        sf::Vector2f position,
        sf::Vector2f size
    );
};
