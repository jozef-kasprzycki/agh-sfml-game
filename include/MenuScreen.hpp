#pragma once
#include "Screen.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class MenuScreen : public Screen {
private:
    sf::Font font;
    sf::Text text;

    // Doda³em te pola, bo u¿ywasz ich w .cpp
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    bool finished = false;
    std::string next_screen = "game";
public:
    MenuScreen();
    void handleEvents(sf::RenderWindow& window) override;
    void update(float delta) override;
    void render(sf::RenderWindow& window) override;
    bool isFinished() const override;
    std::string getNextScreen() const override;
};