#pragma once
#include "Screen.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class SettingsScreen : public Screen {
private:
    // ...
    bool finished = false;
    std::string next_screen = "menu";
public:
    SettingsScreen();
    void handleEvents(sf::RenderWindow& window) override;
    void update(float delta) override;
    void render(sf::RenderWindow& window) override;
    bool isFinished() const override;
    std::string getNextScreen() const override;
};