#include "TextureManager.hpp"
#include <iostream>

std::unordered_map<std::string, sf::Texture> TextureManager::textures;

sf::Texture& TextureManager::get(const std::string& path) {
    auto it = textures.find(path);
    if (it != textures.end()) {
        return it->second;
    }

    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        std::cerr << "Blad ladowania tekstury: " << path << "\n";
    }

    textures.emplace(path, std::move(texture));
    return textures[path];
}
