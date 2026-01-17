#include "StartScreen.hpp"

StartScreen::StartScreen() {
    if (!font.loadFromFile("../assets/font.ttf")) { // adjust path
        // handle error
    }
    text.setFont(font);
    text.setString("Press Space to Start");
    text.setCharacterSize(24);
    text.setPosition(400, 300);
}

void StartScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            finished = true;
        }
    }
}

void StartScreen::update(float delta) {
    // nothing
}

void StartScreen::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(text);
    window.display();
}

bool StartScreen::isFinished() const {
    return finished;
}

std::string StartScreen::getNextScreen() const {
    return "menu";
}