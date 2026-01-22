#include "SoundManager.hpp"

SoundManager::SoundManager() : isMusicPaused(false) {}

SoundManager::~SoundManager() {
    stopBackgroundMusic();
}

bool SoundManager::loadBackgroundMusic(const std::string& filepath) {
    if (!backgroundMusic.openFromFile(filepath)) {
        return false; // Failed to load music
    }
    backgroundMusic.setLoop(true);
    isMusicPaused = true;
    return true;
}

void SoundManager::stopBackgroundMusic() {
    backgroundMusic.stop();
    isMusicPaused = false;
}

void SoundManager::resumeBackgroundMusic() {
    if (isMusicPaused) {
        backgroundMusic.play();
        isMusicPaused = false;
    }
}