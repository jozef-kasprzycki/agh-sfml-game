#include "Movable.hpp"

Movable::Movable(){}

Movable::Movable(
    sf::Vector2f position, 
    sf::Texture& texture
){
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Movable::draw(sf::RenderWindow& window){
    window.draw(sprite);
}

void Movable::move(float x, float y){
    sprite.move(x,y);
}