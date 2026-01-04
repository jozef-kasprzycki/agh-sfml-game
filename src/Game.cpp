#include "Game.hpp"
#include <iostream>
#include <random>

//funkcja zwraca losową pozycję, która nie koliduje z Playerem i zapewnia, że obiekt mieści się w oknie gry
//tworzy tymczasowy hitbox (candidate) i sprawdza kolizję z forbidden (hitbox Playera)
sf::Vector2f getRandomPositionNoCollision(
    const sf::FloatRect& forbidden,
    const sf::Vector2f& size
) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distX(0.f, 1000.f - size.x);
    std::uniform_real_distribution<float> distY(0.f, 600.f - size.y);

    sf::FloatRect candidate;

    do {
        candidate.left = distX(gen);
        candidate.top = distY(gen);
        candidate.width = size.x;
        candidate.height = size.y;
    } while (candidate.intersects(forbidden));

    return { candidate.left, candidate.top };
}

Game::Game()
    : window(sf::VideoMode(1000, 600), "AGH SFML Game"),
    player(),
    obstacle(
        getRandomPositionNoCollision(player.getBounds(), { 50.f, 50.f }),
        { 50.f, 50.f }
    )
{

}


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

    if (player.getBounds().intersects(obstacle.getBounds())) {
        //std::cout << "Kolizja z przeszkoda!\n"; //wydruk testowy
		player.stop(); // zatrzymanie gracza po kolizji
    }
}

void Game::render() {
    window.clear();
	//window.clear(sf::Color(30, 30, 30)); //sprawdza widoczność player i obstacle
    //window.clear(sf::Color::White); //sprawdza czy nie ma przezroczystości
    // Dodać renderowanie różnych elementów gry


    obstacle.draw(window);
    player.draw(window);

    window.display();
}