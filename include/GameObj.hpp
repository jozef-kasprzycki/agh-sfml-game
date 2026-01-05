#pragma once
#include <SFML/Graphics.hpp>

class GameObj {
private:
    sf::Sprite sprite;

public:
    GameObj(
        sf::Vector2f position,
        sf::Vector2f size,
        sf::Texture texture
    );

    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    sf::FloatRect getGlobalBounds() const;

    void setPosition(sf::Vector2f);
    void setTextureRect(sf::IntRect);

    void draw(sf::RenderWindow& window);
};