#include "Player.hpp"
#include <iostream>

Player::Player(){

    if (!texture.loadFromFile("../assets/agh.png")){
        std::cerr << "Blad pliku!\n";
    }
    sprite.setTexture(texture);

    max_speed = 700;
    min_speed = 50;
}

void Player::update(float delta){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        if (std::abs(speed_vector.y) < max_speed) 
            speed_vector.y -= max_speed*delta;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        if (std::abs(speed_vector.y) < max_speed) 
            speed_vector.y += max_speed*delta;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        if (std::abs(speed_vector.x) < max_speed) 
            speed_vector.x -= max_speed*delta;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        if (std::abs(speed_vector.x) < max_speed) 
            speed_vector.x += max_speed*delta;
    }
    
    // Dodać spowolnienie

    move(speed_vector.x * delta, speed_vector.y * delta);
}