#include "Movable.hpp"

Movable::Movable()
    : speed_vector(0.f, 0.f),
    max_speed(0.f),
    min_speed(0.f),
    size(0.f, 0.f)
{
}


//Movable::Movable(
//    sf::Vector2f position,
//    sf::Texture& texture
//) {
//    sprite.setTexture(texture);
//    sprite.setPosition(position);
//}

void Movable::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Movable::getBounds() const {
    return sprite.getGlobalBounds();
}

void Movable::move(float x, float y) {
    // game area is 1000x600
    // (0,0)    (1000,0)
    // (0,600)  (1000,600)

    //sf::Vector2f to_move(0.f, 0.f);

    if (
        x < 0.f && sprite.getPosition().x + x > 0.f ||
        x > 0.f && sprite.getPosition().x + size.x + x < 1000.f
        )
        sprite.move(x, 0);
    else {
        if (std::abs(speed_vector.x) > min_speed)
            speed_vector.x *= -0.8;
    }

    if (
        y < 0.f && sprite.getPosition().y + y > 0.f ||
        y > 0.f && sprite.getPosition().y + size.y + y < 600.f
        )
        sprite.move(0, y);
    else {
        if (std::abs(speed_vector.y) > min_speed)
            speed_vector.y *= -0.8;
    }
}