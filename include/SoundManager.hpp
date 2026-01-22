#pragma once

#include <SFML/Audio.hpp>
#include <string>

class SoundManager {
private:
    sf::Music backgroundMusic;
    bool isMusicPaused;

public:
    SoundManager();
    ~SoundManager();

    // Load and play background music in a loop
    bool loadBackgroundMusic(const std::string& filepath);

    // Stop the background music
    void stopBackgroundMusic();

    // Resume the background music
    void resumeBackgroundMusic();

};
