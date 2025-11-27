#pragma once
#include <SFML/Graphics.hpp>

class Movable {
protected:
    sf::Sprite sprite;
    sf::Texture texture;

    float speed;

public:
    Movable();
    Movable(
        sf::Vector2f position,
        sf::Texture& texture
    );

    void draw(sf::RenderWindow& window);
    void move(float x, float y);

};