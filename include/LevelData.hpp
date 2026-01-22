#pragma once
#include <SFML/Graphics.hpp>
#include "Obstacle.hpp"
#include <vector>
#include <iostream>

// Struktura zawierające wszystkie informacje nt
// każdego poziomu, do kórej ładowane są dane z pliku
// w LevelLoader 

struct ObstacleData {
    sf::FloatRect bounds;
    std::string texture_path;
};

struct EnemyData {
    sf::FloatRect bounds;
    std::string type;
    // Jeszcze jakieś pola w przyszłości:
    // float max_hp;
    // float givenDamage;
    // float damageRate;
};

struct LevelData {
    std::string name;
    sf::Vector2u size;
    std::string background;
    sf::Vector2f playerStart;
    std::vector<struct ObstacleData> obstacles;
    std::vector<struct EnemyData> enemies;
    std::string next_level_filename;
};
