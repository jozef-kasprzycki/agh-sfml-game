#pragma once
#include <SFML/Graphics.hpp>

class GameObj {
private:
    sf::Sprite sprite;

protected:
    void setTexture(sf::Texture &texture);
    void setScale(const sf::Vector2f& targetSize);

public:
    GameObj(
        sf::Vector2f position,
        sf::Vector2f size
    );

    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    sf::FloatRect getGlobalBounds() const;

    void setPosition(sf::Vector2f pos);
    void setTextureRect(sf::IntRect rect);

    void draw(sf::RenderWindow& window);
};