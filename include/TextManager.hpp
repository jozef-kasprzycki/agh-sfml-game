#pragma once
#include "FloatingText.hpp"
#include <vector>
#include <memory>

class TextManager {
private:
    std::vector<std::unique_ptr<FloatingText>> texts;
    const sf::Font& font; // Referencja do czcionki za³adowanej w GameScreen

public:
    TextManager(const sf::Font& fontRef);

    void addText(const std::string& msg, sf::Vector2f pos, sf::Color color);
    void update(float delta);
    void render(sf::RenderWindow& window);
};