#pragma once
#include <SFML/Graphics.hpp>

class Obstacle {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f size;

public:
    Obstacle();

    Obstacle(
        sf::Vector2f position,
        sf::Vector2f size
    );


    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
};


