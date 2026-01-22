#pragma once
#include "PlayerBase.hpp"

class PlayerBasic : public PlayerBase {
protected:
    void handleInput() override;

public:
    PlayerBasic(
        sf::Vector2f position,
        sf::Vector2f size,
        int hp
    );
};