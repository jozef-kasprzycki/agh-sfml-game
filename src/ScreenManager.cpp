#include "ScreenManager.hpp"
#include "StartScreen.hpp"
#include "MenuScreen.hpp"
#include "GameScreen.hpp"
#include "GameOverScreen.hpp"

ScreenManager::ScreenManager()
    : window(sf::VideoMode(1000, 600), "AGH SFML Game")
{
    currentScreen = std::make_unique<StartScreen>();
}

void ScreenManager::run() {
    while (window.isOpen()) {
        float delta = clock.restart().asSeconds();
        currentScreen->handleEvents(window);
        currentScreen->update(delta);
        currentScreen->render(window);

        if (currentScreen->isFinished()) {
            std::string next = currentScreen->getNextScreen();
            if (next == "menu") {
                currentScreen = std::make_unique<MenuScreen>();
            } else if (next == "game") {
                currentScreen = std::make_unique<GameScreen>();
            } else if (next == "gameover_win") {
                currentScreen = std::make_unique<GameOverScreen>(true);
            } else if (next == "gameover_lose") {
                currentScreen = std::make_unique<GameOverScreen>(false);
            } else if (next == "start") {
                currentScreen = std::make_unique<StartScreen>();
            }
            // Add more if needed
        }
    }
}