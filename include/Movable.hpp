#pragma once
#include <SFML/Graphics.hpp>

class Movable {
protected:
    sf::Sprite sprite;
    sf::Texture texture;

    sf::Vector2f speed_vector;
    float max_speed;
    float min_speed;

public:
    Movable();
    Movable(
        sf::Vector2f position,
        sf::Texture& texture
    );

    void draw(sf::RenderWindow& window);
    void move(float x, float y);

};