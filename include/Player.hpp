#pragma once
#include "Movable.hpp"
#include <SFML/Graphics.hpp>

class Player : public Movable {
private:
    sf::Texture texture;
	int hp;
    // ...wartości charakterysytyczne
    // tylko dla postaci gracza...

public:
    Player(
        sf::Vector2f position,
        sf::Vector2f size
    );

    void update(float delta);

    // ?
    friend class CollisionManager;
};