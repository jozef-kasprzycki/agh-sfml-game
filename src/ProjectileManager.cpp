#include "ProjectileManager.hpp"
#include <algorithm>

void ProjectileManager::spawn(std::unique_ptr<Projectile> p) {
    projectiles.push_back(std::move(p));
}

void ProjectileManager::update(
    float delta,
    std::vector<std::unique_ptr<EnemyBase>>& enemies,
    PlayerBase& player
) {
    for (auto& p : projectiles) {
        p->update(delta);

        // Kolizja: Pocisk Gracza -> Przeciwnik
        if (p->getOwner() == ProjectileOwner::Player) {
            for (auto& enemy : enemies) {
                if (enemy->getGlobalBounds().intersects(p->getGlobalBounds())) {
                    enemy->takeDamage(p->getDamage());
                    p->setPosition({ -1000.f, -1000.f }); // Wyrzuæ poza mapê (oznaczenie do usuniêcia)
                }
            }
        }
        // Kolizja: Pocisk Przeciwnika -> Gracz (opcjonalnie na przysz³oœæ)
        /*
        else if (p->getOwner() == ProjectileOwner::Enemy) {
             if (player.getGlobalBounds().intersects(p->getGlobalBounds())) {
                 player.takeDamage(p->getDamage());
                 p->setPosition({ -1000.f, -1000.f });
             }
        }
        */
    }

    // Usuwanie zu¿ytych pocisków (czas min¹³ LUB wylecia³y poza mapê po trafieniu)
    projectiles.erase(
        std::remove_if(
            projectiles.begin(),
            projectiles.end(),
            [](const std::unique_ptr<Projectile>& p) {
                // Usuñ jeœli czas min¹³ lub jest bardzo daleko (poza ekranem po trafieniu)
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