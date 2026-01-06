#pragma once
#include <SFML/Graphics.hpp>

class GameObj {
private:
    sf::Sprite sprite;

public:
    GameObj(
        sf::Vector2f position,
        sf::Vector2f size
    );

    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    sf::FloatRect getGlobalBounds() const;

    void setPosition(sf::Vector2f pos);
    void setTexture(sf::Texture &texture);
    void setTextureRect(sf::IntRect rect);

    void draw(sf::RenderWindow& window);
};