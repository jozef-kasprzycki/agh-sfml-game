#include "EnemyBoss.hpp"
#include "TextureManager.hpp"
#include "EnemyIdleState.hpp" // U¿ywamy podstawowego stanu dla ruchu
#include <cmath>

EnemyBoss::EnemyBoss(sf::Vector2f position, sf::Vector2f size)
// HP: 500 (Boss), Atak: 20 (boli), FireRate: sterowane rêcznie w update
    : EnemyBase(position, size, 500),
    currentPhase(BossPhase::Moving),
    phaseTimer(0.f),
    shootTimer(0.f),
    spiralAngle(0.f)
{
    // Nadpisanie statystyk w combatStats
    combatStats.projectileSpeed = 350.f; // Wolniejsze pociski ni¿ gracza, ale du¿o

    // Bardzo wolny ruch
    max_speed = 80.f;
    min_speed = 20.f;

    // Zak³adamy, ¿e masz boss.png. Jeœli nie, u¿yje enemy.png jako fallback, ale przeskaluje
    // Wskazówka: Upewnij siê, ¿e plik boss.png istnieje w assets!
    try {
        setTexture(TextureManager::get("../assets/boss.png"));
    }
    catch (...) {
        setTexture(TextureManager::get("../assets/enemy.png")); // Fallback
    }

    // U¿ywamy standardowej maszyny stanów do ruchu (bêdzie powoli szed³ do gracza)
    stateMachine.changeState(*this, std::make_unique<EnemyIdleState>());
}

void EnemyBoss::update(float delta) {
    // 1. Obs³uga ruchu (z klasy bazowej)
    updateMovement(delta);

    // 2. Obs³uga faz Bossa
    phaseTimer += delta;

    switch (currentPhase) {
    case BossPhase::Moving:
        // Przez 3 sekundy tylko idzie w stronê gracza (odpoczynek dla gracza)
        if (phaseTimer > 3.0f) {
            currentPhase = BossPhase::SpiralFire;
            phaseTimer = 0.f;
            max_speed = 20.f; // Zwalnia prawie do zera podczas ataku
        }
        break;

    case BossPhase::SpiralFire:
        // Przez 4 sekundy strzela dooko³a
        if (phaseTimer > 4.0f) {
            currentPhase = BossPhase::RapidFire;
            phaseTimer = 0.f;
        }
        break;

    case BossPhase::RapidFire:
        // Przez 3 sekundy strzela w gracza
        if (phaseTimer > 3.0f) {
            currentPhase = BossPhase::Moving;
            phaseTimer = 0.f;
            max_speed = 80.f; // Wraca do normalnej prêdkoœci
        }
        break;
    }
}

std::unique_ptr<Projectile> EnemyBoss::tryShoot(float delta, const sf::Vector2f& playerPos) {
    shootTimer -= delta;

    if (shootTimer <= 0.f) {
        sf::Vector2f spawnPos = getPosition() + sf::Vector2f(getSize().x / 2.f, getSize().y / 2.f);

        if (currentPhase == BossPhase::SpiralFire) {
            // Atak 1: Spirala
            // Bardzo szybki fire rate (co 0.1s)
            shootTimer = 0.05f;

            // Zwiêkszamy k¹t
            spiralAngle += 15.f * delta * 20.f; // Obrót

            float rad = spiralAngle * 3.14159f / 180.f;
            sf::Vector2f dir(std::cos(rad), std::sin(rad));

            return std::make_unique<Projectile>(
                spawnPos,
                sf::Vector2f(15.f, 15.f), // Wiêksze pociski
                dir * 300.f, // Wolne, ale du¿o
                15, // Obra¿enia
                ProjectileOwner::Enemy
            );
        }
        else if (currentPhase == BossPhase::RapidFire) {
            // Atak 2: Minigun w gracza
            shootTimer = 0.15f;

            sf::Vector2f dir = playerPos - getPosition();
            float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            if (len > 0) dir /= len;

            // Lekki rozrzut (zeby nie by³a to idealna linia)
            float spread = (rand() % 20 - 10) / 100.f;
            dir.x += spread;
            dir.y += spread;

            return std::make_unique<Projectile>(
                spawnPos,
                sf::Vector2f(10.f, 10.f),
                dir * 600.f, // Szybkie
                10,
                ProjectileOwner::Enemy
            );
        }
    }

    return nullptr;
}