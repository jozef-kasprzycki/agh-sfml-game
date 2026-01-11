#pragma once
#include <SFML/Graphics.hpp>
#include "GameObj.hpp"
class Obstacle : public GameObj {
private:
    //static sf::Texture sharedTexture; // WSP�LNA TEKSTURA

public:
    Obstacle(
        sf::Vector2f position,
        sf::Vector2f size
    );

    Obstacle(const Obstacle&) = delete;
    Obstacle& operator=(const Obstacle&) = delete;

    Obstacle(Obstacle&&) = default;
    Obstacle& operator=(Obstacle&&) = default;
};