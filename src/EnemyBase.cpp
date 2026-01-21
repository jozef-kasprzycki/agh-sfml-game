#include "EnemyBase.hpp"
#include "EnemyIdleState.hpp"
#include <random>
#include <cmath>

EnemyBase::EnemyBase(
    sf::Vector2f position,
    sf::Vector2f size
)
    : Entity(position,
        size,
        CombatStats(50, 10)
    ),
    detectionRadius(500.f),
    chaseRadius(300.f)
{
    max_speed = 300.f;
    min_speed = 10.f;

    // Losowe modyfikatory zasiêgów (per instancja)
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> detectDist(0.9f, 1.1f);
    std::uniform_real_distribution<float> chaseDist(0.9f, 1.1f);

    detectionRadiusFactor = detectDist(gen);
    chaseRadiusFactor = chaseDist(gen);

    // Ka¿dy enemy dostaje w³asny offset celu poœcigu
    // wokó³ gracza, ¿eby nie skleja³y siê w jeden punkt
    std::uniform_real_distribution<float> angleDist(0.f, 2.f * 3.1415926f);
    std::uniform_real_distribution<float> radiusDist(20.f, 60.f);

    float angle = angleDist(gen);
    float radius = radiusDist(gen);

    chaseOffset = {
        std::cos(angle) * radius,
        std::sin(angle) * radius
    };

    stateMachine.changeState(*this, std::make_unique<EnemyIdleState>());
}

void EnemyBase::update(float delta) {
    // Usuniêto updateMovement(delta);
    // Ruch jest aplikowany w GameScreen::update przez CollisionManager
}

void EnemyBase::behave(float delta, const sf::Vector2f& playerPos) {
    stateMachine.update(*this, delta, playerPos);
}

float EnemyBase::getDetectionRadius() const {
    return detectionRadius * detectionRadiusFactor;
}

float EnemyBase::getChaseRadius() const {
    return chaseRadius * chaseRadiusFactor;
}

float EnemyBase::getMaxSpeed() const {
    return max_speed;
}

// Zamiast œcigaæ dok³adnie œrodek gracza,
// enemy œciga swój indywidualny punkt wokó³ niego
sf::Vector2f EnemyBase::getChaseTarget(const sf::Vector2f& playerPos) const {
    return playerPos + chaseOffset;
}

void EnemyBase::stopSoft() {
    speed_vector *= 0.85f;
}

void EnemyBase::steerTowards(
    const sf::Vector2f& desiredVelocity,
    float delta
) {
    sf::Vector2f steering = desiredVelocity - speed_vector;
    speed_vector += steering * delta * 5.f;
    limitSpeed();
}

EnemyStateMachine& EnemyBase::getStateMachine() {
    return stateMachine;
}