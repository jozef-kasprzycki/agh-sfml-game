#include "EnemyBase.hpp"
#include "EnemyIdleState.hpp"

EnemyBase::EnemyBase(
    sf::Vector2f position,
    sf::Vector2f size,
    int hp
)
    : Entity(position, size, hp),
    detectionRadius(500.f),
    chaseRadius(300.f)
{
    max_speed = 300.f;
    min_speed = 10.f;

    stateMachine.changeState(*this, std::make_unique<EnemyIdleState>());
}

void EnemyBase::update(float delta) {
    updateMovement(delta);
}

void EnemyBase::behave(float delta, const sf::Vector2f& playerPos) {
    stateMachine.update(*this, delta, playerPos);
}

float EnemyBase::getDetectionRadius() const { return detectionRadius; }
float EnemyBase::getChaseRadius() const { return chaseRadius; }
float EnemyBase::getMaxSpeed() const { return max_speed; }

void EnemyBase::steerTowards(const sf::Vector2f& desiredVelocity, float delta) {
    const float steeringStrength = 6.f;
    speed_vector +=
        (desiredVelocity - speed_vector) * steeringStrength * delta;
}

void EnemyBase::stopSoft() {
    speed_vector *= 0.90f;
}

EnemyStateMachine& EnemyBase::getStateMachine() {
    return stateMachine;
}
