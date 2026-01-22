#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Projectile.hpp"
#include "EnemyBase.hpp"
#include "PlayerBase.hpp"
#include "Obstacle.hpp" // Dodano include

class ProjectileManager {
private:
    std::vector<std::unique_ptr<Projectile>> projectiles;

public:
    void spawn(std::unique_ptr<Projectile>);

    // Zaktualizowana sygnatura - dodano obstacles
    void update(
        float delta,
        std::vector<std::unique_ptr<EnemyBase>>& enemies,
        PlayerBase& player,
        const std::vector<Obstacle>& obstacles
    );

    void render(sf::RenderWindow& window);
};