#include "EnemyGunnerWanderState.hpp"
#include "EnemyBase.hpp"
#include <random>
#include <cmath>

void EnemyGunnerWanderState::update(
    EnemyBase& enemy,
    EnemyStateMachine& machine,
    float delta,
    const sf::Vector2f& playerPos
) {
    // Gunner ma siê poruszaæ ze sta³¹ prêdkoœci¹
    float desiredSpeed = enemy.getMaxSpeed();

    // Sprawdzamy czy siê porusza
    sf::Vector2f vel = enemy.getSpeedVector();
    float speedSq = vel.x * vel.x + vel.y * vel.y;

    // Jeœli prawie stoi (np. po spawnie) lub po mocnym zderzeniu -> losuj kierunek
    if (speedSq < 100.f) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> angleDist(0.f, 2.f * 3.1415926f);

        float angle = angleDist(gen);
        sf::Vector2f newDir(std::cos(angle), std::sin(angle));
        enemy.setSpeed(newDir * desiredSpeed);
    }
    else {
        // Utrzymuj sta³¹ prêdkoœæ (jeœli CollisionManager j¹ zmniejszy³ przy odbiciu, przywróæ)
        enemy.maintainSpeed(desiredSpeed);
    }
}