#include "Obstacle.hpp"
#include "TextureManager.hpp"
#include <iostream>


Obstacle::Obstacle(sf::Vector2f position, sf::Vector2f size)
    : GameObj(position, size)
{
    setTexture(TextureManager::get("../assets/obstacle.png"));
}