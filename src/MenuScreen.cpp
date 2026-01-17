#include "MenuScreen.hpp"
#include "TextureManager.hpp"
#include <iostream> // temp
MenuScreen::MenuScreen() {
    backgroundTexture = TextureManager::get("../assets/menu_bg.png");
    backgroundSprite.setTexture(backgroundTexture);

    if (!font.loadFromFile("../assets/font.ttf")) {
        // handle error
    }
    text.setFont(font);
    text.setString("Menu: \n\tPress Enter to Play\n\tPress S to go to Settings\n\tPress Esc to quit");
    text.setCharacterSize(24);
    text.setPosition(350, 250);
}

void MenuScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            next_screen = "game";
            finished = true;
        } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
        {
            exit(0);
        } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) 
        {
            // Open Settings screen (ekran ustawień jeszcze nie istnieje)
            std::cout << "Opening settings!\n"; // temp
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