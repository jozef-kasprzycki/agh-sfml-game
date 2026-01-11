#include "PlayerBase.hpp"
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
}

void PlayerBase::handleMovement(float delta) {

    //* Y axis
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (speed_vector.y > -max_speed)
            speed_vector.y -= max_speed * delta;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if (speed_vector.y < max_speed)
            speed_vector.y += max_speed * delta;
    }
    else if (speed_vector.y > min_speed) {
        speed_vector.y -= max_speed * delta;
    }
    else if (speed_vector.y < -min_speed) {
        speed_vector.y += max_speed * delta;
    }
    else {
        speed_vector.y = 0.f;
    }

    //* X axis
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if (speed_vector.x > -max_speed)
            speed_vector.x -= max_speed * delta;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (speed_vector.x < max_speed)
            speed_vector.x += max_speed * delta;
    }
    else if (speed_vector.x > min_speed) {
        speed_vector.x -= max_speed * delta;
    }
    else if (speed_vector.x < -min_speed) {
        speed_vector.x += max_speed * delta;
    }
    else {
        speed_vector.x = 0.f;
    }
}

void PlayerBase::update(float delta) {
    handleMovement(delta);
}
