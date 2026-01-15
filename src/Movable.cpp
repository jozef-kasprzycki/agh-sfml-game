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
{
}

sf::Vector2f Movable::getSpeedVector() const {
    return speed_vector;
}

void Movable::setSpeed(const sf::Vector2f& speed) {
    speed_vector = speed;
    limitSpeed();
}

void Movable::addSpeed(const sf::Vector2f& deltaSpeed) {
    speed_vector += deltaSpeed;
    limitSpeed();
}

void Movable::limitSpeed() {
    float length = std::sqrt(
        speed_vector.x * speed_vector.x +
        speed_vector.y * speed_vector.y
    );

    if (max_speed > 0.f && length > max_speed) {
        speed_vector *= (max_speed / length);
    }
}

void Movable::updateMovement(float delta) {
    move(sf::Vector2f(
        speed_vector.x * delta,
        speed_vector.y * delta
    ));
}

void Movable::bounceX() {
    speed_vector.x *= -0.5;
}

void Movable::bounceY() {
    speed_vector.y *= -0.5;
}

void Movable::move(sf::Vector2f delta) {
    setPosition(sf::Vector2f(
        getPosition().x + delta.x,
        getPosition().y + delta.y
    ));
}   