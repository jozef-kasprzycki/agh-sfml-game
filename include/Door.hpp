#pragma once
#include "GameObj.hpp"
#include <string>

class Door : public GameObj {
private:
    std::string nextLevelPath;

public:
    Door(sf::Vector2f position, sf::Vector2f size, const std::string& nextLevel);

    const std::string& getNextLevel() const;
};