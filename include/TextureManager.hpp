#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TextureManager {
private:
    static std::unordered_map<std::string, sf::Texture> textures;

public:
    static sf::Texture& get(const std::string& path);
};
