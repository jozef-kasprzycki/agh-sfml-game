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
    std::string texture_path;
    // Jeszcze jakieś pola w przyszłości
};

struct LevelData {
    sf::Vector2u size;
    sf::Vector2f playerStart;
    std::vector<struct ObstacleData> obstacles;
    std::vector<struct EnemyData> enemies;
};
