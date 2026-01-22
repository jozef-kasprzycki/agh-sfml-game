#include <SFML/Graphics.hpp>
#include "SettingsScreen.hpp"
#include "TextureManager.hpp"
#include <iostream>

SettingsScreen::SettingsScreen() {
    backgroundTexture = TextureManager::get("../assets/settings_bg.png");
    backgroundSprite.setTexture(backgroundTexture);

    if (!font.loadFromFile("../assets/font.ttf")) 
        std::cerr << "Blad ladowania czcionki!\n";
    text.setFont(font);
    text.setString("1 - wylacz muzyke\n2 - wlacz muzyke\nEsc - powrot do menu");
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOrigin(
        text.getGlobalBounds().width / 2,
        text.getGlobalBounds().height / 2
    );
    text.setPosition(500, 300);
}

void SettingsScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed){
            if (event.key.code == sf::Keyboard::Num1) {
                setBackgroundMusic(false);
            } else if (event.key.code == sf::Keyboard::Num2) {
                setBackgroundMusic(true);
            } else if (event.key.code == sf::Keyboard::Escape) {
                finished = true;
            }
        }
    }
}

void SettingsScreen::update(float delta) {
    // nothing
}

void SettingsScreen::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(text);
    window.display();
}

bool SettingsScreen::isFinished() const {
    return finished;
}

std::string SettingsScreen::getNextScreen() const {
    return next_screen;
}