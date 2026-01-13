#pragma once
#include <SFML/Graphics.hpp>
#include "GameObj.hpp"
class Obstacle : public GameObj {
private:

public:
    Obstacle(
        sf::Vector2f position,
        sf::Vector2f size,
        const std::string& texture_path
    );

    Obstacle(const Obstacle&) = delete;
    Obstacle& operator=(const Obstacle&) = delete;

    Obstacle(Obstacle&&) = default;
    Obstacle& operator=(Obstacle&&) = default;
};