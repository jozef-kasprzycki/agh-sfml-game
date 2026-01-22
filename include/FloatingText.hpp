#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class FloatingText {
private:
    sf::Text text;
    float lifetime;       // Czas ¿ycia w sekundach
    float maxLifetime;
    sf::Vector2f velocity; // Prêdkoœæ unoszenia siê

public:
    FloatingText(const sf::Font& font, const std::string& msg, sf::Vector2f pos, sf::Color color);

    // Zwraca false, jeœli tekst powinien zostaæ usuniêty
    bool update(float delta);
    void render(sf::RenderWindow& window);
};