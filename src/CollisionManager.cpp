#include "CollisionManager.hpp"
#include "Obstacle.hpp"
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

CollisionManager::CollisionManager(){std::cout << "collisionManager constructed.\n";}
CollisionManager::CollisionManager(std::vector<sf::FloatRect> obstacles) : obstacles(obstacles) {}

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

    for (const auto& obs : obstacles) {
        if (!to_move.intersects(obs)) continue;

        // nakładanie w każdej osi (liczone od to_move)
        float overlapLeft   = (to_move.left + to_move.width) - obs.left;
        float overlapRight  = (obs.left + obs.width) - to_move.left;
        float overlapTop    = (to_move.top + to_move.height) - obs.top;
        float overlapBottom = (obs.top + obs.height) - to_move.top;

        float overlapX = std::min(overlapLeft, overlapRight);
        float overlapY = std::min(overlapTop, overlapBottom);
        const float EPS = 1e-4f;

        if (overlapX + EPS < overlapY) {
            // kolizja w osi X -> odbicie tylko X
            movable.bounceX();
            // ustaw korekcję ruchu w osi X tak, by nie przenikać przeszkody
            if (posDelta.x > 0.f) {
                posDelta.x = obs.left - (movable.getGlobalBounds().left + movable.getGlobalBounds().width);
            } else {
                posDelta.x = (obs.left + obs.width) - movable.getGlobalBounds().left;
            }
        } else {
            // kolizja w osi Y -> odbicie tylko Y
            movable.bounceY();
            if (posDelta.y > 0.f) {
                posDelta.y = obs.top - (movable.getGlobalBounds().top + movable.getGlobalBounds().height);
            } else {
                posDelta.y = (obs.top + obs.height) - movable.getGlobalBounds().top;
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