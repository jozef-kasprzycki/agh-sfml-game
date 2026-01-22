#include "MenuScreen.hpp"
#include "TextureManager.hpp"
#include "GameScreen.hpp" // Potrzebne do resetowania Admina przy wylogowaniu
#include <iostream> 

MenuScreen::MenuScreen() {
    // Zakładam, że TextureManager działa poprawnie
    try {
        backgroundTexture = TextureManager::get("../assets/menu_bg.png");
        backgroundSprite.setTexture(backgroundTexture);
    }
    catch (...) {
        // Fallback jeśli brak tła
    }

    if (!font.loadFromFile("../assets/font.ttf")) {
        // handle error
    }
    text.setFont(font);
    // Zmieniłem tekst "quit" na "Log Out", żeby pasował do akcji
    text.setString("Menu: \n\tPress Enter to Play\n\tPress S to go to Settings\n\tPress Esc to Log Out");
    text.setCharacterSize(24);
    text.setPosition(350, 250);
}

void MenuScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            next_screen = "game";
            finished = true;
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            // ZMIANA: Zamiast exit(0), wracamy do ekranu logowania
            GameScreen::setAdminMode(false); // Resetujemy uprawnienia admina
            next_screen = "auth";            // Ustawiamy ID ekranu logowania
            finished = true;                 // Kończymy ten ekran
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
        {
            std::cout << "Opening settings!\n";
            next_screen = "settings";
            finished = true;
        }
    }
}

void MenuScreen::update(float delta) {
    // nothing
}

void MenuScreen::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(text);
    window.display();
}

bool MenuScreen::isFinished() const {
    return finished;
}

std::string MenuScreen::getNextScreen() const {
    return next_screen;
}