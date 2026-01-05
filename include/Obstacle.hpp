#pragma once
#include <SFML/Graphics.hpp>

class Obstacle {
private:
    sf::Sprite sprite;
    sf::Vector2f size;

    static sf::Texture sharedTexture; // WSPÓLNA TEKSTURA

public:
    Obstacle();

    Obstacle(
        sf::Vector2f position,
        sf::Vector2f size
    );

    Obstacle(const Obstacle&) = delete;
    Obstacle& operator=(const Obstacle&) = delete;

    Obstacle(Obstacle&&) = default;
    Obstacle& operator=(Obstacle&&) = default;

    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
};