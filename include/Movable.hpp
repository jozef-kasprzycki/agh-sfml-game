#pragma once
#include <SFML/Graphics.hpp>

class Movable {
protected:
    sf::Sprite sprite;
    sf::Texture texture;

    sf::Vector2f size;

    sf::Vector2f speed_vector; // {px/s, px/s}
    float max_speed; // px/s
    float min_speed; // px/s

public:
    Movable();
    Movable(
        sf::Vector2f position,
        sf::Texture& texture
    );

    void draw(sf::RenderWindow& window);
    void move(float x, float y);

};