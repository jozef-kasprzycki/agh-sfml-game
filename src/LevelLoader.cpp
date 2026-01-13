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

    // Rozmiar mapy
    level.size.x = j["size"]["width"];
    level.size.y = j["size"]["height"];

    // Pozycja gracza
    level.playerStart.x = j["player"]["position"][0];
    level.playerStart.y = j["player"]["position"][1];

    // Przeszkody
    for (const auto& o : j["obstacles"]) {
        level.obstacles.emplace_back(
            o["x"],
            o["y"],
            o["w"],
            o["h"]
        );
    }

    return level;
}
