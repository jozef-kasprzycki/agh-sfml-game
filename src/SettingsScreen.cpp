#include "SettingsScreen.hpp"
#include "TextureManager.hpp"

SettingsScreen::SettingsScreen() {
    backgroundTexture = TextureManager::get("../assets/settings_bg.png");
    backgroundSprite.setTexture(backgroundTexture);

    // Settings staff
}

void SettingsScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
        {
            finished = true;
        }
    }
}

void SettingsScreen::update(float delta) {
    // nothing
}

void SettingsScreen::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite);
    window.display();
}

bool SettingsScreen::isFinished() const {
    return finished;
}

std::string SettingsScreen::getNextScreen() const {
    return next_screen;
}