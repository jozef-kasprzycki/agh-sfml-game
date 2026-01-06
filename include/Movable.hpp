#pragma once
#include "GameObj.hpp"
#include <SFML/Graphics.hpp>

class Movable : public GameObj {
protected:
    sf::Vector2f speed_vector; // {px/s, px/s}
    float max_speed; // px/s
    float min_speed; // px/s

public:
    Movable(
        sf::Vector2f position,
        sf::Vector2f size
    );

    void move(float x, float y);
    void stop();

    // ?
	friend class CollisionManager;
};