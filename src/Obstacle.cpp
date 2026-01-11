#include "Obstacle.hpp"
#include "TextureManager.hpp"
#include <iostream>

//sf::Texture Obstacle::sharedTexture; // definicja statycznej tekstury

Obstacle::Obstacle(sf::Vector2f position, sf::Vector2f size)
    : GameObj(position, size)
{
    setTexture(TextureManager::get("../assets/obstacle.png"));
}
