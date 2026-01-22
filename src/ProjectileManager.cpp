#include "ProjectileManager.hpp"
#include <algorithm>

void ProjectileManager::spawn(std::unique_ptr<Projectile> p) {
    projectiles.push_back(std::move(p));
}

// TUTAJ BY£ B£¥D: Musi byæ 4. argument (obstacles), tak jak w pliku .hpp
void ProjectileManager::update(
    float delta,
    std::vector<std::unique_ptr<EnemyBase>>& enemies,
    PlayerBase& player,
    const std::vector<Obstacle>& obstacles
) {
    for (auto& p : projectiles) {
        p->update(delta);
        bool hit = false;

        // 1. Kolizja: Pocisk Gracza -> Przeciwnik
        if (p->getOwner() == ProjectileOwner::Player) {
            for (auto& enemy : enemies) {
                if (enemy->getGlobalBounds().intersects(p->getGlobalBounds())) {
                    enemy->takeDamage(p->getDamage());
                    hit = true;
                    break;
                }
            }
        }

        // 2. Kolizja: Pocisk -> Przeszkoda (Œciana)
        if (!hit) {
            for (const auto& obs : obstacles) {
                if (p->getGlobalBounds().intersects(obs.getGlobalBounds())) {
                    hit = true;
                    break;
                }
            }
        }

        // Jeœli trafi³, wyrzuæ poza mapê
        if (hit) {
            p->setPosition({ -1000.f, -1000.f });
        }
    }

    // Usuwanie zu¿ytych pocisków
    projectiles.erase(
        std::remove_if(
            projectiles.begin(),
            projectiles.end(),
            [](const std::unique_ptr<Projectile>& p) {
                return p->isExpired() || p->getPosition().x < -900.f;
            }
        ),
        projectiles.end()
    );
}

void ProjectileManager::render(sf::RenderWindow& window) {
    for (auto& p : projectiles)
        p->draw(window);
}