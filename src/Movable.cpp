#include "Movable.hpp"
#include <cmath>

Movable::Movable(
    sf::Vector2f position,
    sf::Vector2f size
)
    : GameObj(position, size),
      speed_vector(0.f, 0.f),
      max_speed(0.f),
      min_speed(0.f)
{}

void Movable::move(float x, float y) {

    if (
        x < 0.f && getPosition().x + x > 0.f ||
        x > 0.f && getPosition().x + getSize().x + x < 1000.f
        )
        setPosition(sf::Vector2f(getPosition().x + x, getPosition().y));
    else {
        if (std::abs(speed_vector.x) > min_speed)
            speed_vector.x *= -0.8;
    }

    if (
        y < 0.f && getPosition().y + y > 0.f ||
        y > 0.f && getPosition().y + getSize().y + y < 600.f
        )
        setPosition(sf::Vector2f(getPosition().x, getPosition().y + y));
    else {
        if (std::abs(speed_vector.y) > min_speed)
            speed_vector.y *= -0.8;
    }
}

void Movable::stop() {
    speed_vector = { 0.f, 0.f };
}