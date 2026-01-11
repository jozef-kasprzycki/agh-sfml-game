#include "Player.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

Player::Player(sf::Vector2f position, sf::Vector2f size) 
    : Movable(position, size)
{
    max_speed = 600.f;
    min_speed = 100.f;
    hp = 100;

    if (!texture.loadFromFile("../assets/player.png")) { EXIT_FAILURE; }
    setTexture(texture);
}

void Player::getHitted(){
    hp--;
    std::cout << "\nPlayer hitted, hp=" << hp;
}

void Player::update(float delta) {
    // std::cout
    //     << "Player position: "
    //     << getPosition().x
    //     << ", "
    //     << getPosition().y
    //     << "     \r";

    //* Y axis
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (speed_vector.y > -max_speed)
            speed_vector.y -= max_speed * delta;

        // TODO: animacja poruszania się w górę
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if (speed_vector.y < max_speed)
            speed_vector.y += max_speed * delta;

        // TODO: animacja poruszania się w dół
    }
    else if (speed_vector.y > min_speed) {
        speed_vector.y -= max_speed * delta;

        // TODO: animacja hamowania/ślizgu 
    }
    else if (speed_vector.y < -min_speed) {
        speed_vector.y += max_speed * delta;

        // TODO: animacja hamowania/ślizgu
    }
    else {
        speed_vector.y = 0.f;
    }

    //* X axis
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if (speed_vector.x > -max_speed)
            speed_vector.x -= max_speed * delta;

        // TODO: animacja poruszania się lewo
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (speed_vector.x < max_speed)
            speed_vector.x += max_speed * delta;

        // TODO: animacja poruszania się w prawo
    }
    else if (speed_vector.x > min_speed) {
        speed_vector.x -= max_speed * delta;

        // TODO: animacja hamowania/ślizgu 
    }
    else if (speed_vector.x < -min_speed) {
        speed_vector.x += max_speed * delta;

        // TODO: animacja hamowania/ślizgu
    }
    else {
        speed_vector.x = 0.f;
    }

    //move(sf::Vector2f(speed_vector.x * delta, speed_vector.y * delta));
}
