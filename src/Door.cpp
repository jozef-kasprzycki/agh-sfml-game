#include "Door.hpp"
#include "TextureManager.hpp"

Door::Door(sf::Vector2f position, sf::Vector2f size, const std::string& nextLevel)
    : GameObj(position, size), nextLevelPath(nextLevel)
{
    // Upewnij siê, ¿e masz plik doors.png w assets, lub podmieñ na obstacle_rect.png tymczasowo
    setTexture(TextureManager::get("../assets/doors.png"));
}

const std::string& Door::getNextLevel() const {
    return nextLevelPath;
}