#include "Backgorund.hpp"
#include "TextureManager.hpp"

Background::Background(const sf::Vector2u size)
    : GameObj(
        sf::Vector2f(0, 0),
        sf::Vector2f(size)
    )
{}

void Background::set(const std::string& texture_name){
    setTexture(TextureManager::get(texture_name));
}