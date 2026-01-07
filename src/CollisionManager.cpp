#include "CollisionManager.hpp"
#include "Obstacle.hpp"
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

void CollisionManager::addObstacle(const sf::FloatRect& rect) {
    obstacles.push_back(rect);
}

void CollisionManager::tryMove(
    Movable& movable,
    sf::Vector2f& posDelta
) {
    sf::FloatRect to_move = movable.getGlobalBounds();
    to_move.left += posDelta.x;
    to_move.top  += posDelta.y;

    // Sprawdzanie granic mapy:
    if (to_move.top < 0.f || to_move.top + to_move.height > 600.f) {
        movable.bounceY();
        posDelta.y = 0;
    }

    if (to_move.left < 0.f || to_move.left + to_move.width > 1000.f) {
        movable.bounceX();
        posDelta.x = 0;
    }

    // Sprawdzanie przeszkód 

    for (auto& obs : obstacles) {
        if (to_move.intersects(obs)){
            if (to_move.top < obs.top + obs.height || to_move.top + to_move.height > obs.top){
                movable.bounceY();
                posDelta.y = 0;
                std::cout << "Zderzenie Y z przeszkoda\n";
            }
            if (to_move.left < obs.left + obs.width || to_move.left + to_move.width > obs.left){
                movable.bounceX();
                posDelta.x = 0;
                std::cout << "Zderzenie X z przeszkoda\n";
            }
        }
    }

    movable.move(posDelta);

}

// void CollisionManager::resolveCollision(
//     Movable& movable,
//     const sf::FloatRect& obstacleBounds
// ) {
//     sf::FloatRect m = movable.getGlobalBounds();

//     float overlapLeft = (m.left + m.width) - obstacleBounds.left;
//     float overlapRight = (obstacleBounds.left + obstacleBounds.width) - m.left;
//     float overlapTop = (m.top + m.height) - obstacleBounds.top;
//     float overlapBottom = (obstacleBounds.top + obstacleBounds.height) - m.top;

//     bool collisionX = std::min(overlapLeft, overlapRight) <
//         std::min(overlapTop, overlapBottom);

//     if (collisionX) {
//         movable.speed_vector.x *= -0.8f; // odbicie X
//     }
//     else {
//         movable.speed_vector.y *= -0.8f; // odbicie Y
//     }
// }