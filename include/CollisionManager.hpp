#pragma once
#include <SFML/Graphics.hpp>
#include "Obstacle.hpp"
#include "Movable.hpp" // W przyszłości usunąć
#include <vector>

class CollisionManager {
private:
    std::vector<sf::FloatRect> obstacles;

public:
    void addObstacle(const sf::FloatRect& rect);

    void tryMove(
        Movable&,
        sf::Vector2f&
    );
    
    // static void resolveCollision(
    //     Movable& movable,
    //     const sf::FloatRect& obstacleBounds
    // );
};