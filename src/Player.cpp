#include "Player.hpp"
#include <iostream>

Player::Player() {

    if (!texture.loadFromFile("../assets/player.png")) {
        std::cerr << "Blad pliku!\n";
    }

    sprite.setTexture(texture);
    sprite.setPosition(100.f, 100.f);

    size = sf::Vector2f(50.f, 50.f);

    auto texSize = texture.getSize();
    sprite.setScale(
        size.x / texSize.x,
        size.y / texSize.y
    );

    max_speed = 600.f;
    min_speed = 100.f;
}


void Player::update(float delta) {
    std::cout
        << "Player position: "
        << sprite.getPosition().x
        << ", "
        << sprite.getPosition().y
        << "     \r";

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

    move(speed_vector.x * delta, speed_vector.y * delta);
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

void Player::stop() {
    speed_vector = { 0.f, 0.f };
}
