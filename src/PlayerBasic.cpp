#include "PlayerBasic.hpp"
#include "TextureManager.hpp"
#include <SFML/Window/Keyboard.hpp>

PlayerBasic::PlayerBasic(
    sf::Vector2f position,
    sf::Vector2f size,
    int hp
)
// Tworzymy statystyki: HP=z argumentu, Atak=10, FireRate=0.2s, BulletSpeed=900
    : PlayerBase(position, size, CombatStats(hp, 10, 0.2f, 900.f))
{
    setTexture(TextureManager::get("../assets/player2.png"));
}

void PlayerBasic::handleInput() {
    inputDirection = { 0.f, 0.f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) inputDirection.y = -1.f;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) inputDirection.y = 1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) inputDirection.x = -1.f;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) inputDirection.x = 1.f;

    shootDirection = { 0.f, 0.f };
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    shootDirection = { 0.f, -1.f };
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  shootDirection = { 0.f,  1.f };
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  shootDirection = { -1.f, 0.f };
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) shootDirection = { 1.f, 0.f };
}