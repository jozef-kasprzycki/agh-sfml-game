#include "CollisionManager.hpp"
#include <cmath>
#include <algorithm>

void CollisionManager::resolveCollision(
    Movable& movable,
    const sf::FloatRect& obstacleBounds
) {
    sf::FloatRect m = movable.getBounds();

    float overlapLeft = (m.left + m.width) - obstacleBounds.left;
    float overlapRight = (obstacleBounds.left + obstacleBounds.width) - m.left;
    float overlapTop = (m.top + m.height) - obstacleBounds.top;
    float overlapBottom = (obstacleBounds.top + obstacleBounds.height) - m.top;

    bool collisionX = std::min(overlapLeft, overlapRight) <
        std::min(overlapTop, overlapBottom);

    if (collisionX) {
        movable.speed_vector.x *= -0.8f; // odbicie X
    }
    else {
        movable.speed_vector.y *= -0.8f; // odbicie Y
    }
}