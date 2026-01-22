#include "TextManager.hpp"

TextManager::TextManager(const sf::Font& fontRef) : font(fontRef) {}

void TextManager::addText(const std::string& msg, sf::Vector2f pos, sf::Color color) {
    texts.push_back(std::make_unique<FloatingText>(font, msg, pos, color));
}

void TextManager::update(float delta) {
    // 1. Aktualizuj i oznacz do usuniêcia
    for (size_t i = 0; i < texts.size(); ) {
        if (!texts[i]->update(delta)) {
            // Jeœli tekst wygas³, usuñ go (swap & pop dla wydajnoœci lub erase)
            texts.erase(texts.begin() + i);
        }
        else {
            ++i;
        }
    }
}

void TextManager::render(sf::RenderWindow& window) {
    for (auto& text : texts) {
        text->render(window);
    }
}