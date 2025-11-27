#include "Player.hpp"
#include <iostream>

Player::Player(){

    if (!texture.loadFromFile("../assets/agh.png")){
        std::cerr << "Blad pliku!\n";
    }
    sprite.setTexture(texture);
    speed = 700;
}

void Player::update(float delta){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        move(0, -delta*speed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        move(0, delta*speed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        move(-delta*speed, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        move(delta*speed, 0);
}