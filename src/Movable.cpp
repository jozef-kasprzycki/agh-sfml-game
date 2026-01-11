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
    /*
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
