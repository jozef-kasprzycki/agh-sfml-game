#include "FloatingText.hpp"

FloatingText::FloatingText(const sf::Font& font, const std::string& msg, sf::Vector2f pos, sf::Color color)
    : lifetime(1.0f), maxLifetime(1.0f), velocity(0.f, -50.f) // Unoszenie siê w górê
{
    text.setFont(font);
    text.setString(msg);
    text.setCharacterSize(20);
    text.setFillColor(color);
    text.setPosition(pos);

    // Wycentrowanie tekstu wzglêdem punktu
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}

bool FloatingText::update(float delta) {
    lifetime -= delta;

    // Przesuwanie
    text.move(velocity * delta);

    // Zanikanie (Fade out)
    sf::Color c = text.getFillColor();
    c.a = static_cast<sf::Uint8>(255 * (lifetime / maxLifetime));
    text.setFillColor(c);

    return lifetime > 0.f;
}

void FloatingText::render(sf::RenderWindow& window) {
    window.draw(text);
}