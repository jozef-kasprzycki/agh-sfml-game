#pragma once
#include <SFML/Graphics.hpp>
#include "SoundManager.hpp"

class Screen {
protected:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    bool backgroundMusic;
public:
    virtual ~Screen() = default;
    virtual void handleEvents(sf::RenderWindow& window) = 0;
    virtual void update(float delta) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual bool isFinished() const = 0;
    virtual std::string getNextScreen() const = 0;
    bool backgroundMusicEnabled() const;
    void setBackgroundMusic(bool enabled);
};