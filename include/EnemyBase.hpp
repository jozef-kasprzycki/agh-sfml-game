#pragma once
#include "Entity.hpp"
#include "EnemyStateMachine.hpp"
#include <SFML/System/Vector2.hpp>

// Bazowa klasa przeciwnika – wspólna fizyka + AI
class EnemyBase : public Entity {
protected:
    float detectionRadius;
    float chaseRadius;

    // losowoœæ per instancja
    float detectionRadiusFactor;
    float chaseRadiusFactor;

    // Indywidualny offset celu poœcigu, ¿eby enemy
    // nie celowa³y dok³adnie w ten sam punkt
    sf::Vector2f chaseOffset;

    EnemyStateMachine stateMachine;

public:
    EnemyBase(
        sf::Vector2f position,
        sf::Vector2f size
        // int hp - usuniêto, bo w .cpp te¿ go nie ma
    );

    // RUCH
    void update(float delta) override;

    virtual void behave(float delta, const sf::Vector2f& playerPos);

    float getDetectionRadius() const;
    float getChaseRadius() const;
    float getMaxSpeed() const;

    // Zwraca indywidualny punkt poœcigu wokó³ gracza
    sf::Vector2f getChaseTarget(const sf::Vector2f& playerPos) const;

    void stopSoft();
    void steerTowards(const sf::Vector2f& desiredVelocity, float delta);

    EnemyStateMachine& getStateMachine();
};