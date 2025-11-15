#pragma once
#include <SFML/Graphics.hpp>

class Game {
private:
	sf::RenderWindow window;
	sf::Clock clock; 

    void processEvents();
    void update(float delta);
    void render();

public:
    Game();
    void run();
};

