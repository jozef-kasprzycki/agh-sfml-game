#pragma once
//#include <SFML/Graphics.hpp>

#include "Movable.hpp"

class Player : public Movable {
public:
    Player();

    void update(float delta);
};
