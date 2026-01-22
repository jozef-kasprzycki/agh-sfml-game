#include "EnemyBase.hpp"
#include "EnemyIdleState.hpp"
#include <random>
#include <cmath>

EnemyBase::EnemyBase(
    sf::Vector2f position,
    sf::Vector2f size,
    int hp
)
    : Entity(position, size, CombatStats(hp, 10, 1.0f, 0.f)),
    detectionRadius(500.f),
    chaseRadius(300.f),
    currentCooldown(0.f)
{
    max_speed = 300.f;
    min_speed = 10.f;

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> detectDist(0.9f, 1.1f);
    std::uniform_real_distribution<float> chaseDist(0.9f, 1.1f);

    detectionRadiusFactor = detectDist(gen);
    chaseRadiusFactor = chaseDist(gen);

    std::uniform_real_distribution<float> angleDist(0.f, 2.f * 3.1415926f);
    std::uniform_real_distribution<float> radiusDist(20.f, 60.f);

    float angle = angleDist(gen);
    float radius = radiusDist(gen);

    chaseOffset = sf::Vector2f(
        std::cos(angle) * radius,
        std::sin(angle) * radius
    );

    stateMachine.changeState(*this, std::make_unique<EnemyIdleState>());
}

void EnemyBase::update(float delta) {
    updateMovement(delta);

    // Aktualizacja cooldownu
    if (currentCooldown > 0.f) {
        currentCooldown -= delta;
    }
}

// Domyœlna implementacja - zwraca nullptr (brak strza³u)
// EnemyGunner to nadpisze
std::unique_ptr<Projectile> EnemyBase::tryShoot(float delta, const sf::Vector2f& playerPos) {
    return nullptr;
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

sf::Vector2f EnemyBase::getChaseTarget(const sf::Vector2f& playerPos) const {
    return playerPos + chaseOffset;
}

void EnemyBase::stopSoft() {
    speed_vector *= 0.85f;
}

void EnemyBase::steerTowards(const sf::Vector2f& desiredVelocity, float delta) {
    sf::Vector2f steering = desiredVelocity - speed_vector;
    speed_vector += steering * delta * 5.f;
    limitSpeed();
}

void EnemyBase::maintainSpeed(float targetSpeed) {
    float currentSq = speed_vector.x * speed_vector.x + speed_vector.y * speed_vector.y;
    if (currentSq > 0.001f) {
        float scale = targetSpeed / std::sqrt(currentSq);
        speed_vector *= scale;
    }
}

EnemyStateMachine& EnemyBase::getStateMachine() {
    return stateMachine;
}