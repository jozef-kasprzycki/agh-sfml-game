#include "Obstacle.hpp"
#include <iostream>

Obstacle::Obstacle()
    : size(50.f, 50.f)
{
    if (!texture.loadFromFile("../assets/obstacle.png")) {
        std::cerr << "Blad ladowania obstacle.png\n";
    }

    sprite.setTexture(texture);
    sprite.setPosition(0.f, 0.f);

    auto texSize = texture.getSize();
    if (texSize.x > 0 && texSize.y > 0) {
        sprite.setScale(
            size.x / texSize.x,
            size.y / texSize.y
        );
    }
}

Obstacle::Obstacle(sf::Vector2f position, sf::Vector2f size)
    : size(size)
{
    if (!texture.loadFromFile("../assets/obstacle.png")) {
        std::cerr << "Blad ladowania obstacle.png\n";
    }

    sprite.setTexture(texture);
    sprite.setPosition(position);

    auto texSize = texture.getSize();
    if (texSize.x > 0 && texSize.y > 0) {
        sprite.setScale(
            size.x / texSize.x,
            size.y / texSize.y
        );
    }
}

void Obstacle::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Obstacle::getBounds() const {
    return sprite.getGlobalBounds();
}
