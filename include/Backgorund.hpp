#pragma once 
#include "GameObj.hpp"

class Background : public GameObj {
public:
    Background(const sf::Vector2u size);
    void set(const std::string& texture_name);
};