#pragma once
#include "GameObj.hpp"
#include <SFML/Graphics.hpp>

class Movable : public GameObj {
protected:
    sf::Vector2f speed_vector; // {px/s, px/s}
    float max_speed; // px/s
    float min_speed; // px/s

    // Ogranicza d³ugoœæ wektora prêdkoœci do max_speed
    void limitSpeed();

public:
    Movable(
        sf::Vector2f position,
        sf::Vector2f size
    );

    virtual ~Movable() = default;

    // Dostêp do prêdkoœci
    sf::Vector2f getSpeedVector() const;

    // Ustawianie / modyfikacja prêdkoœci
    void setSpeed(const sf::Vector2f& speed);
    void addSpeed(const sf::Vector2f& deltaSpeed);

    // Aktualizacja pozycji na podstawie deltaTime
    void updateMovement(float delta);

    // Reakcje fizyczne
    void bounceX();
    void bounceY();
    void stop();

    // Ruch bezpoœredni (np. przez CollisionManager)
    void move(sf::Vector2f);

    // ?
    //friend class CollisionManager;
};
