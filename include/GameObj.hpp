#pragma once
#include <SFML/Graphics.hpp>

class GameObj {
private:
    sf::Sprite sprite;
    sf::Vector2f targetSize;
    // Animacje
    int framesNum;
    std::vector<sf::IntRect> frames;
    std::size_t currentFrame = 0;
    float frameDuration = 0.12f; // czas na klatkę (s)
    float frameElapsed = 0.f;

protected:
    void setTexture(sf::Texture &texture);
    void setScale(const sf::Vector2f& targetSize);
    void animate(int);

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