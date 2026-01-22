#include "EnemyChaser.hpp"
#include "TextureManager.hpp"
#include <random>

EnemyChaser::EnemyChaser(
    sf::Vector2f position,
    sf::Vector2f size
)
// TU BYŁ BŁĄD: Brakowało trzeciego argumentu (hp)
    : EnemyBase(position, size, 50)
{
    setTexture(TextureManager::get("../assets/enemy.png"));

    // minimalna losowość prędkości
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> speedDist(0.95f, 1.05f);

    // Nadpisujemy prędkość w statystykach CombatStats (opcjonalne, ale dobre dla spójności)
    // Dostęp do combatStats mamy przez dziedziczenie po Entity (jest protected)
    combatStats.fireRate = 0.f; // Chaser nie strzela

    // Prędkość ruchu jest w Movable::max_speed (nie w CombatStats)
    max_speed = 250.f * speedDist(gen);
    min_speed = 0.f;
}