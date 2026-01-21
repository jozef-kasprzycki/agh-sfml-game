#include "EnemyChaser.hpp"
#include "TextureManager.hpp"
#include <random>

EnemyChaser::EnemyChaser(
    sf::Vector2f position,
    sf::Vector2f size
)
    : EnemyBase(position, size) // Usunięto ", 50" - HP jest ustawiane wewnątrz EnemyBase
{
    setTexture(TextureManager::get("../assets/enemy.png"));

    // minimalna losowość prędkości
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> speedDist(0.95f, 1.05f);

    max_speed = 250.f * speedDist(gen);
    min_speed = 0.f;
}