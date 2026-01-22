#include "Screen.hpp"

bool Screen::backgroundMusicEnabled() const
{
    return backgroundMusic;
}

void Screen::setBackgroundMusic(bool enabled)
{
    backgroundMusic = enabled;
}
