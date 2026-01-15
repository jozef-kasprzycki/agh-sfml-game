#pragma once
#include <string>
#include "LevelData.hpp"

class LevelLoader {
public:
    static LevelData loadFromFile(const std::string& path);
};
