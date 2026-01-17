#pragma once
#include <SFML/Graphics.hpp>

class Screen {
public:
    virtual ~Screen() = default;
    virtual void handleEvents(sf::RenderWindow& window) = 0;
    virtual void update(float delta) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual bool isFinished() const = 0;
    virtual std::string getNextScreen() const = 0;
};