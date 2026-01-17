#include "GameOverScreen.hpp"

GameOverScreen::GameOverScreen(bool win) : isWin(win) {
    if (!backgroundTexture.loadFromFile("../assets/gameover_bg.png")) {
        // handle error
    }
    backgroundSprite.setTexture(backgroundTexture);

    if (!font.loadFromFile("../assets/font.ttf")) {
        // handle error
    }
    text.setFont(font);
    text.setString(isWin ? "You Win! Press R to Restart" : "Game Over. Press R to Restart");
    text.setCharacterSize(24);
    text.setPosition(400, 300);
}

void GameOverScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
            finished = true;
        }
    }
}

void GameOverScreen::update(float delta) {
    // nothing
}

void GameOverScreen::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(text);
    window.display();
}

bool GameOverScreen::isFinished() const {
    return finished;
}

std::string GameOverScreen::getNextScreen() const {
    return "menu";
}