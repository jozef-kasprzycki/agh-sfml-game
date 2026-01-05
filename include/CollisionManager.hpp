#pragma once
#include <SFML/Graphics.hpp>
#include "Movable.hpp"

class CollisionManager {
public:
    static void resolveCollision(
        Movable& movable,
        const sf::FloatRect& obstacleBounds
    );
};