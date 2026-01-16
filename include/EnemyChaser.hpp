#pragma once
#include "EnemyBase.hpp"

// Wróg, który œciga gracza gdy jest w zasiêgu
class EnemyChaser : public EnemyBase {
public:
    EnemyChaser(
        sf::Vector2f position,
        sf::Vector2f size
    );
};