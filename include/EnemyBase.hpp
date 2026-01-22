#pragma once
#include "Entity.hpp"
#include "EnemyStateMachine.hpp"
#include <SFML/System/Vector2.hpp>

class EnemyBase : public Entity {
protected:
    float detectionRadius;
    float chaseRadius;

    float detectionRadiusFactor;
    float chaseRadiusFactor;

    sf::Vector2f chaseOffset;

    EnemyStateMachine stateMachine;

public:
    // Konstruktor przyjmuje int hp (dla zgodnoœci z EnemyChaser)
    EnemyBase(
        sf::Vector2f position,
        sf::Vector2f size,
        int hp
    );

    void update(float delta) override;
    virtual void behave(float delta, const sf::Vector2f& playerPos);

    float getDetectionRadius() const;
    float getChaseRadius() const;
    float getMaxSpeed() const;

    sf::Vector2f getChaseTarget(const sf::Vector2f& playerPos) const;

    void stopSoft();
    void steerTowards(const sf::Vector2f& desiredVelocity, float delta);

    EnemyStateMachine& getStateMachine();
};