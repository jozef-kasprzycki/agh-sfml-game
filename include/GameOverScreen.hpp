#pragma once
#include "Screen.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class GameOverScreen : public Screen {
private:
    sf::Font font;
    sf::Text text;
    bool finished = false;
    bool isWin;
public:
    GameOverScreen(bool win);
    void handleEvents(sf::RenderWindow& window) override;
    void update(float delta) override;
    void render(sf::RenderWindow& window) override;
    bool isFinished() const override;
    std::string getNextScreen() const override;
};