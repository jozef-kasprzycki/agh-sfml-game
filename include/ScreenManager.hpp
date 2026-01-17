#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Screen.hpp"

class ScreenManager {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    std::unique_ptr<Screen> currentScreen;

public:
    ScreenManager();
    void run();
};