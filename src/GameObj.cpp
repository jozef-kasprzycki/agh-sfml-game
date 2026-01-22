#include "GameObj.hpp"
#include <SFML/Graphics.hpp>

GameObj::GameObj(sf::Vector2f position, sf::Vector2f size)
    : targetSize(size)
{
    sprite.setPosition(position);
}

sf::Vector2f GameObj::getPosition() {
    return sprite.getPosition();
}

sf::Vector2f GameObj::getSize() {
    auto bounds = sprite.getLocalBounds();
    auto scale = sprite.getScale();
    return sf::Vector2f(bounds.width * scale.x, bounds.height * scale.y);
}

sf::FloatRect GameObj::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

void GameObj::setPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
}

void GameObj::setTexture(sf::Texture& texture) {
    sprite.setTexture(texture);
    for (int i = 0; i < 5; ++i)
        frames.push_back(sf::IntRect(i * targetSize.x, 0, targetSize.x, targetSize.y));

    setTextureRect(frames[0]);
}

void GameObj::animate(int frameNum) {
    setTextureRect(frames[frameNum]);
}

void GameObj::setTextureRect(sf::IntRect rect) {
    sprite.setTextureRect(rect);
}

// NOWE
void GameObj::setColor(const sf::Color& color) {
    sprite.setColor(color);
}

void GameObj::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void GameObj::setScale(const sf::Vector2f& targetSize) {
    sprite.setScale(targetSize);
}