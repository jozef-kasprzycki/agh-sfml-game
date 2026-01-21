#pragma once
#include "Entity.hpp"
#include "EnemyStateMachine.hpp"
#include <SFML/System/Vector2.hpp>

class EnemyBase : public Entity {
protected:
    float detectionRadius;
    float chaseRadius;

    // losowoœæ per instancja
    float detectionRadiusFactor;
    float chaseRadiusFactor;

    EnemyStateMachine stateMachine;

public:
    EnemyBase(
        sf::Vector2f position,
        sf::Vector2f size
        // int hp - usuniêto, bo w .cpp te¿ go nie ma
    );

    // RUCH
    void update(float delta) override;

    // AI / FSM
    virtual void behave(float delta, const sf::Vector2f& playerPos);

    float getDetectionRadius() const;
    float getChaseRadius() const;
    float getMaxSpeed() const;

    void stopSoft();
    void steerTowards(const sf::Vector2f& desiredVelocity, float delta);

    EnemyStateMachine& getStateMachine();
};