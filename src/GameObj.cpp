#include "GameObj.hpp"
#include <SFML/Graphics.hpp> // ensure FloatRect & Transformable are available

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

void GameObj::setTexture(sf::Texture &texture){
    sprite.setTexture(texture);
    auto b = sprite.getLocalBounds();
    if (b.width > 0 && b.height > 0) {
        sprite.setScale(targetSize.x / b.width, targetSize.y / b.height);
    }
}

void GameObj::setTextureRect(sf::IntRect rect) {
    sprite.setTextureRect(rect);
}

void GameObj::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void GameObj::setScale(const sf::Vector2f& targetSize) {
	// forward scale to SFML transform so rendering uses it
	sprite.setScale(targetSize);
}