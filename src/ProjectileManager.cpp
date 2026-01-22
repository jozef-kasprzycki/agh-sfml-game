#include "ProjectileManager.hpp"
#include <algorithm>

void ProjectileManager::spawn(std::unique_ptr<Projectile> p) {
    projectiles.push_back(std::move(p));
}

void ProjectileManager::update(
    float delta,
    std::vector<std::unique_ptr<EnemyBase>>& enemies,
    PlayerBase& player,
    const std::vector<Obstacle>& obstacles
) {
    // 1. Aktualizacja i kolizje podstawowe (œciany, trafienia w postacie)
    for (auto& p : projectiles) {
        p->update(delta);
        bool hit = false;

        if (p->getOwner() == ProjectileOwner::Player) {
            // Pocisk gracza -> wrogowie
            for (auto& enemy : enemies) {
                if (enemy->getGlobalBounds().intersects(p->getGlobalBounds())) {
                    enemy->takeDamage(p->getDamage());
                    hit = true;
                    break;
                }
            }
        }
        else {
            // Pocisk wroga -> gracz
            if (p->getGlobalBounds().intersects(player.getGlobalBounds())) {
                player.takeDamage(p->getDamage());
                hit = true;
            }
        }

        // Kolizja ze œcianami
        if (!hit) {
            for (const auto& obs : obstacles) {
                if (p->getGlobalBounds().intersects(obs.getGlobalBounds())) {
                    hit = true;
                    break;
                }
            }
        }

        if (hit) {
            p->setPosition({ -1000.f, -1000.f }); // Oznacz do usuniêcia
        }
    }

    // 2. Neutralizacja pocisków (Player Bullet vs Enemy Bullet)
    // N^2 complexity, ale przy ma³ej liczbie pocisków jest OK
    for (size_t i = 0; i < projectiles.size(); ++i) {
        if (projectiles[i]->getPosition().x < -900.f) continue; // Ju¿ usuniêty

        for (size_t j = i + 1; j < projectiles.size(); ++j) {
            if (projectiles[j]->getPosition().x < -900.f) continue; // Ju¿ usuniêty

            auto& p1 = projectiles[i];
            auto& p2 = projectiles[j];

            // Sprawdzamy czy to wrogie sobie pociski
            if (p1->getOwner() != p2->getOwner()) {
                if (p1->getGlobalBounds().intersects(p2->getGlobalBounds())) {
                    // Zderzenie pocisków -> oba znikaj¹
                    p1->setPosition({ -1000.f, -1000.f });
                    p2->setPosition({ -1000.f, -1000.f });
                }
            }
        }
    }

    // 3. Usuwanie
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