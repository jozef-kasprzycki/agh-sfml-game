#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Projectile.hpp"
#include "EnemyBase.hpp"
#include "PlayerBase.hpp"
#include "Obstacle.hpp"
#include "TextManager.hpp" // NOWE

class ProjectileManager {
private:
    std::vector<std::unique_ptr<Projectile>> projectiles;

public:
    void spawn(std::unique_ptr<Projectile>);

    void update(
        float delta,
        std::vector<std::unique_ptr<EnemyBase>>& enemies,
        PlayerBase& player,
        const std::vector<Obstacle>& obstacles,
        TextManager& textManager // NOWE
    );

    void render(sf::RenderWindow& window);
};