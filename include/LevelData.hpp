#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

struct ObstacleData {
    sf::FloatRect bounds;
    std::string texture_path;
};

struct EnemyData {
    sf::FloatRect bounds;
    std::string type;
};

// Nowa struktura dla drzwi
struct DoorData {
    sf::FloatRect bounds;
    std::string next_level_path;
};

struct LevelData {
    std::string name;
    sf::Vector2u size;
    std::string background;
    sf::Vector2f playerStart;

    std::vector<ObstacleData> obstacles;
    std::vector<EnemyData> enemies;
    std::vector<DoorData> doors; // Lista drzwi
};