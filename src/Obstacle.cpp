#include "Obstacle.hpp"
#include "TextureManager.hpp"
#include <iostream>


Obstacle::Obstacle(sf::Vector2f position, sf::Vector2f size, const std::string& texture_path)
    : GameObj(position, size)
{
    setTexture(TextureManager::get(texture_path));
}