#include "PlayerBase.hpp"
#include "TextureManager.hpp" 
#include <SFML/Window/Keyboard.hpp>

PlayerBase::PlayerBase(
    sf::Vector2f position,
    sf::Vector2f size,
    int hp
)
    : Entity(position, size, hp)
{
    max_speed = 600.f;
    min_speed = 100.f;

    setTexture(TextureManager::get("../assets/player.png"));
}

void PlayerBase::handleMovement(float delta) {
   
}

void PlayerBase::update(float delta) {
    handleMovement(delta);
}