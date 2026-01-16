#include "LevelLoader.hpp"
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

LevelData LevelLoader::loadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Nie mozna otworzyc pliku poziomu: " + path);
    }

    json j;
    file >> j;

    LevelData level;

    // Tytuł poziomu
    level.name = j["name"];

    // Rozmiar mapy
    level.size.x = j["size"]["width"];
    level.size.y = j["size"]["height"];

    // Tekstura tła
    level.background = j["background"];

    // Pozycja gracza
    level.playerStart.x = j["player"]["position"][0];
    level.playerStart.y = j["player"]["position"][1];

    // Przeszkody
    struct ObstacleData obs_temp_data;

    for (const auto& o : j["obstacles"]) {
        obs_temp_data.bounds = sf::FloatRect(
                o["x"].get<float>(),
                o["y"].get<float>(),
                o["w"].get<float>(),
                o["h"].get<float>()
            );
        obs_temp_data.texture_path = o["texture_path"].get<std::string>();
        level.obstacles.push_back(obs_temp_data);
        
    }

    struct EnemyData enemy_temp_data;

    for (const auto& o : j["enemies"]) {
        enemy_temp_data.bounds = sf::FloatRect(
                o["x"].get<float>(),
                o["y"].get<float>(),
                o["w"].get<float>(),
                o["h"].get<float>()
            );
        enemy_temp_data.type = o["type"].get<std::string>();
        level.enemies.push_back(enemy_temp_data);
        
    }

    return level;
}
