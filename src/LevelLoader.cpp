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
    level.name = j["name"];
    level.size.x = j["size"]["width"];
    level.size.y = j["size"]["height"];
    level.background = j["background"];

    level.playerStart.x = j["player"]["position"][0];
    level.playerStart.y = j["player"]["position"][1];

    // Przeszkody
    for (const auto& o : j["obstacles"]) {
        ObstacleData obs;
        obs.bounds = sf::FloatRect(
            o["x"].get<float>(), o["y"].get<float>(),
            o["w"].get<float>(), o["h"].get<float>()
        );
        obs.texture_path = o["texture_path"].get<std::string>();
        level.obstacles.push_back(obs);
    }

    // Wrogowie
    for (const auto& o : j["enemies"]) {
        EnemyData enemy;
        enemy.bounds = sf::FloatRect(
            o["x"].get<float>(), o["y"].get<float>(),
            o["w"].get<float>(), o["h"].get<float>()
        );
        enemy.type = o["type"].get<std::string>();
        level.enemies.push_back(enemy);
    }

    // Drzwi (NOWE)
    if (j.contains("doors")) {
        for (const auto& d : j["doors"]) {
            DoorData door;
            door.bounds = sf::FloatRect(
                d["x"].get<float>(), d["y"].get<float>(),
                d["w"].get<float>(), d["h"].get<float>()
            );
            door.next_level_path = d["next_level"].get<std::string>();
            level.doors.push_back(door);
        }
    }

    return level;
}