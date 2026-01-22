#include <iostream>
#include "ScreenManager.hpp"
#include "MenuScreen.hpp"
#include "GameScreen.hpp"
#include "GameOverScreen.hpp"
#include "SettingsScreen.hpp"
#include "AuthScreen.hpp" // Wa�ne: do��czamy nowy ekran
#include "SoundManager.hpp"

ScreenManager::ScreenManager() {
    // Rejestrujemy funkcje tworz�ce ekrany (lambda)
    screens["auth"] = []() { return std::make_unique<AuthScreen>(); };
    screens["menu"] = []() { return std::make_unique<MenuScreen>(); };
    screens["game"] = []() { return std::make_unique<GameScreen>(); };
    screens["gameover_win"] = []() { return std::make_unique<GameOverScreen>(true); };
    screens["gameover_lose"] = []() { return std::make_unique<GameOverScreen>(false); };
    screens["settings"] = []() { return std::make_unique<SettingsScreen>(); };

    // Na start uruchamiamy ekran logowania
    currentScreen = screens["auth"]();
}

void ScreenManager::run(sf::RenderWindow& window) {
    sf::Clock clock;
    if (!soundManager.loadBackgroundMusic("../assets/nowa_era.mp3"))
        std::cerr << "Failed to load background music." << std::endl;

    soundManager.resumeBackgroundMusic();

    while (window.isOpen()) {
        float delta = clock.restart().asSeconds();

        currentScreen->handleEvents(window);
        currentScreen->update(delta);
        currentScreen->render(window);

        if (currentScreen->isFinished()) {
            std::string next = currentScreen->getNextScreen();

            // Sprawdzamy czy mamy taki ekran w mapie
            if (screens.find(next) != screens.end()) {
                currentScreen = screens[next](); // Tworzymy now� instancj� ekranu
            }
        }
    }
}
