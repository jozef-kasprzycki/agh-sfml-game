#pragma once
#include "Screen.hpp"
#include <memory>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <functional>
#include "SoundManager.hpp"

class ScreenManager {
private:
    std::unique_ptr<Screen> currentScreen;

    // Tego brakowa�o - mapa, kt�ra przechowuje instrukcje jak tworzy� dany ekran
    std::map<std::string, std::function<std::unique_ptr<Screen>()>> screens;
    SoundManager soundManager;

public:
    ScreenManager();
    void run(sf::RenderWindow& window);
};