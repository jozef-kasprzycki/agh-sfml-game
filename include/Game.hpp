#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"

class Game {
private:
	sf::RenderWindow window;
	sf::Clock clock;
    Player player;

    void processEvents();
    void update(float delta);
    void render();

public:
    Game();
    void run();
};

