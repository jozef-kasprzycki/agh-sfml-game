#pragma once
#include "Screen.hpp"
#include <memory>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <functional>

class ScreenManager {
private:
    std::unique_ptr<Screen> currentScreen;

    // Tego brakowa³o - mapa, która przechowuje instrukcje jak tworzyæ dany ekran
    std::map<std::string, std::function<std::unique_ptr<Screen>()>> screens;

public:
    ScreenManager();
    void run(sf::RenderWindow& window);
};