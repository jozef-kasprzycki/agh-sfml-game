#include "PlayerBasic.hpp"
#include "TextureManager.hpp"
#include <SFML/Window/Keyboard.hpp>

PlayerBasic::PlayerBasic(
    sf::Vector2f position,
    sf::Vector2f size,
    int hp
)
    : PlayerBase(position, size, hp)
{
    setTexture(TextureManager::get("../assets/player.png"));
}

void PlayerBasic::handleInput() {
    inputDirection = { 0.f, 0.f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        inputDirection.y = -1.f;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        inputDirection.y = 1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        inputDirection.x = -1.f;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        inputDirection.x = 1.f;
}