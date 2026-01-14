#include "EnemyChaser.hpp"
#include "TextureManager.hpp"
#include <cmath>

EnemyChaser::EnemyChaser(
    sf::Vector2f position,
    sf::Vector2f size
)
    : EnemyBase(position, size, 50)
{
    setTexture(TextureManager::get("../assets/enemy.png"));

    max_speed = 250.f;     // maksymalna prędkość
    min_speed = 0.f;       // wróg może się całkiem zatrzymać
}

void EnemyChaser::behave(float delta, const sf::Vector2f& playerPos) {
    sf::Vector2f toPlayer = playerPos - getPosition();
    float distance = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);

    // Gracz za daleko → łagodne hamowanie
    if (distance > detectionRadius) {
        // płynne wytracanie prędkości (brak teleportów)
        speed_vector *= 0.90f;
        return;
    }

    // Normalizacja kierunku
    if (distance > 0.f)
        toPlayer /= distance;

    // Prędkość docelowa (arrive)
    float desiredSpeed = max_speed;

    // Im bliżej gracza, tym wolniej (brak szarpania)
    if (distance < chaseRadius) {
        desiredSpeed = max_speed * (distance / chaseRadius);
    }

    sf::Vector2f desiredVelocity = toPlayer * desiredSpeed;

    // Steering – płynne dochodzenie do prędkości
    const float steeringStrength = 6.f; // im większe, tym bardziej agresywny wróg

    speed_vector += (desiredVelocity - speed_vector) * steeringStrength * delta;
}

void EnemyChaser::update(float delta) {
    updateMovement(delta);
}
