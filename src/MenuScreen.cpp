#include "MenuScreen.hpp"
#include "TextureManager.hpp"

MenuScreen::MenuScreen() {
    backgroundTexture = TextureManager::get("../assets/menu_bg.png");
    backgroundSprite.setTexture(backgroundTexture);

    if (!font.loadFromFile("../assets/font.ttf")) {
        // handle error
    }
    text.setFont(font);
    text.setString("Menu: Press Enter to Play");
    text.setCharacterSize(24);
    text.setPosition(400, 300);
}

void MenuScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
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
    return "game";
}