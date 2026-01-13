#include "PlayerBase.hpp"
#include <iostream>

PlayerBase::PlayerBase(
    sf::Vector2f position,
    sf::Vector2f size,
    int hp
)
    : Entity(position, size, hp),
    hp(hp),
    inputDirection(0.f, 0.f)
{
    max_speed = 600.f;
    min_speed = 100.f;
}

void PlayerBase::takeDamage(int dmg) {
    hp -= dmg;
    std::cout << "\nPlayer hitted, hp=" << hp;
}

void PlayerBase::update(float delta) {
    handleInput();
    applyMovementPhysics(delta);
}

void PlayerBase::applyMovementPhysics(float delta) {
    //* Y axis
    if (inputDirection.y < 0.f) { // W
        if (speed_vector.y > -max_speed)
            speed_vector.y -= max_speed * delta;
        animate(1); // Animacja poruszania się w górę
    }
    else if (inputDirection.y > 0.f) { // S
        if (speed_vector.y < max_speed)
            speed_vector.y += max_speed * delta;
        animate(2); // W dół
    }
    else if (speed_vector.y > min_speed) {
        speed_vector.y -= max_speed * delta;
    }
    else if (speed_vector.y < -min_speed) {
        speed_vector.y += max_speed * delta;
    }
    else {
        speed_vector.y = 0.f;
        animate(0); // Stojąca 
    }

    //* X axis
    if (inputDirection.x < 0.f) { // A
        if (speed_vector.x > -max_speed)
            speed_vector.x -= max_speed * delta;
        animate(4); // W prawo
    }
    else if (inputDirection.x > 0.f) { // D
        if (speed_vector.x < max_speed)
            speed_vector.x += max_speed * delta;
        animate(3); // W lewo
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