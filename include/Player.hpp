#pragma once
#include <SFML/Graphics.hpp>

#include "Movable.hpp"

class Player : public Movable {

private:
	sf::Texture texture;

public:
    Player();

    void update(float delta);
    sf::FloatRect getBounds() const;
    void stop();
};