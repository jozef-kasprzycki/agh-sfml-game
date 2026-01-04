#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Obstacle.hpp"

class Game {
private:
	sf::RenderWindow window;
	sf::Clock clock;

    Player player;
    Obstacle obstacle;

    void processEvents();
    void update(float delta);
    void render();

public:
    Game();
    void run();
};

