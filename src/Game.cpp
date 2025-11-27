#include "Game.hpp"

Game::Game()
    : window(sf::VideoMode(1000, 600), "AGH SFML Game"),
    player()
{}

void Game::run() {
    while (window.isOpen()) {
        float delta = clock.restart().asSeconds();
        processEvents();
        update(delta);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update(float delta) {
	// Aktualizacja klas przyjmujących czas jako paramter
    player.update(delta);
}

void Game::render() {
    window.clear();
    // Dodać renderowanie różnych elementów gry
    player.draw(window);

    window.display();
}