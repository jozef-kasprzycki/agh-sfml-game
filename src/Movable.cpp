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
    // game area is 1000x600

    if (
        x < 0 && sprite.getPosition().x - x >= 0 ||
        x > 0 && sprite.getPosition().x + size.x + x <= 1000
    )
        sprite.move(x, 0);

    if (
        y < 0 && sprite.getPosition().y - y >= 0 ||
        y > 0 && sprite.getPosition().y + size.y + y <= 600
    )
        sprite.move(0, y);
}