#pragma once
#include "Entity.hpp"
#include "EnemyStateMachine.hpp"
#include "Projectile.hpp" // Potrzebne do zwracania unique_ptr<Projectile>
#include <SFML/System/Vector2.hpp>
#include <memory>

class EnemyBase : public Entity {
protected:
    float detectionRadius;
    float chaseRadius;
    float detectionRadiusFactor;
    float chaseRadiusFactor;
    sf::Vector2f chaseOffset;
    EnemyStateMachine stateMachine;

    // Cooldown strzelania dla wroga
    float currentCooldown;

public:
    EnemyBase(
        sf::Vector2f position,
        sf::Vector2f size,
        int hp
    );

    void update(float delta) override;
    virtual void behave(float delta, const sf::Vector2f& playerPos);

    // Nowa metoda: próba strza³u. Zwraca unique_ptr z pociskiem lub nullptr
    virtual std::unique_ptr<Projectile> tryShoot(float delta, const sf::Vector2f& playerPos);

    float getDetectionRadius() const;
    float getChaseRadius() const;
    float getMaxSpeed() const;

    sf::Vector2f getChaseTarget(const sf::Vector2f& playerPos) const;

    void stopSoft();
    void steerTowards(const sf::Vector2f& desiredVelocity, float delta);

    // Wymuszenie sta³ej prêdkoœci (dla Gunnera)
    void maintainSpeed(float speed);

    EnemyStateMachine& getStateMachine();
};