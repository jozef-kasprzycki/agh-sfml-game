#include "ProjectileManager.hpp"
#include <algorithm>
#include <string>

void ProjectileManager::spawn(std::unique_ptr<Projectile> p) {
    projectiles.push_back(std::move(p));
}

void ProjectileManager::update(
    float delta,
    std::vector<std::unique_ptr<EnemyBase>>& enemies,
    PlayerBase& player,
    const std::vector<Obstacle>& obstacles,
    TextManager& textManager // NOWE
) {
    for (auto& p : projectiles) {
        p->update(delta);
        bool hit = false;

        // 1. Kolizja: Pocisk Gracza -> Przeciwnik
        if (p->getOwner() == ProjectileOwner::Player) {
            for (auto& enemy : enemies) {
                if (enemy->getGlobalBounds().intersects(p->getGlobalBounds())) {
                    int dmg = p->getDamage();
                    bool crit = p->getIsCritical();

                    enemy->takeDamage(dmg);

                    // SPAWN CYFERKI
                    sf::Color color = crit ? sf::Color::Yellow : sf::Color::White;
                    std::string txt = std::to_string(dmg) + (crit ? "!" : "");
                    textManager.addText(txt, enemy->getPosition(), color);

                    hit = true;
                    break;
                }
            }
        }
        else {
            // Pocisk wroga -> Gracz
            if (p->getGlobalBounds().intersects(player.getGlobalBounds())) {
                if (!player.isInvincible()) {
                    int dmg = p->getDamage();
                    player.takeDamage(dmg);

                    // Cyferka nad graczem (czerwona)
                    textManager.addText(std::to_string(dmg), player.getPosition(), sf::Color::Red);
                }
                hit = true;
            }
        }

        if (!hit) {
            for (const auto& obs : obstacles) {
                if (p->getGlobalBounds().intersects(obs.getGlobalBounds())) {
                    hit = true;
                    break;
                }
            }
        }

        if (hit) {
            p->setPosition({ -1000.f, -1000.f });
        }
    }

    // Neutralizacja pocisków
    for (size_t i = 0; i < projectiles.size(); ++i) {
        if (projectiles[i]->getPosition().x < -900.f) continue;
        for (size_t j = i + 1; j < projectiles.size(); ++j) {
            if (projectiles[j]->getPosition().x < -900.f) continue;

            auto& p1 = projectiles[i];
            auto& p2 = projectiles[j];

            if (p1->getOwner() != p2->getOwner()) {
                if (p1->getGlobalBounds().intersects(p2->getGlobalBounds())) {
                    p1->setPosition({ -1000.f, -1000.f });
                    p2->setPosition({ -1000.f, -1000.f });

                    // Efekt zderzenia pocisków? (opcjonalnie tekst "Clash")
                    // textManager.addText("x", p1->getPosition(), sf::Color::Cyan);
                }
            }
        }
    }

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