#include "Obstacle.hpp"
#include <iostream>

sf::Texture Obstacle::sharedTexture; // definicja statycznej tekstury

Obstacle::Obstacle()
    : size(50.f, 50.f)
{
    if (sharedTexture.getSize().x == 0) { // ³adujemy tylko raz
        if (!sharedTexture.loadFromFile("../assets/obstacle.png")) {
            std::cerr << "Blad ladowania obstacle.png\n";
        }
    }

    sprite.setTexture(sharedTexture);
    sprite.setPosition(0.f, 0.f);

    auto texSize = sharedTexture.getSize();
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
    if (sharedTexture.getSize().x == 0) { 
        if (!sharedTexture.loadFromFile("../assets/obstacle.png")) {
            std::cerr << "Blad ladowania obstacle.png\n";
        }
    }

    sprite.setTexture(sharedTexture);
    sprite.setPosition(position);

    auto texSize = sharedTexture.getSize();
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
