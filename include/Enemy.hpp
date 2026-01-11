#pragma once
#include <SFML/Graphics.hpp>
#include "Movable.hpp"
#include "Player.hpp"

class Enemy : public Movable {
private:
    //static sf::Texture sharedTexture;

public:
    Enemy(
        sf::Vector2f position,
        sf::Vector2f size
    );

    void update(float delta, Player& player);
};