#include "Obstacle.hpp"
#include <iostream>

sf::Texture Obstacle::sharedTexture; // definicja statycznej tekstury

Obstacle::Obstacle(sf::Vector2f position, sf::Vector2f size)
    : GameObj(position, size)
{
    if (!sharedTexture.loadFromFile("../assets/obstacle.png")) {
        std::cerr << "Blad ladowania obstacle.png\n";
    }

    setTexture(sharedTexture);
}
