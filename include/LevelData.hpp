#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

// Struktura zawierające wszystkie informacje nt
// każdego poziomu, do kórej ładowane są dane z pliku
// w LevelLoader 

struct LevelData {
    sf::Vector2u size;
    sf::Vector2f playerStart;
    std::vector<sf::FloatRect> obstacles;
};
