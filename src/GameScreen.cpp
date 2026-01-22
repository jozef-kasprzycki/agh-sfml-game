#include <bits/stdc++.h>
#include <iostream>
#include <random> 
#include "GameScreen.hpp"
#include "LevelLoader.hpp"
#include "Projectile.hpp"
#include "EnemyGunner.hpp" 
#include "EnemyBoss.hpp" 


// --- ZMIENNE STATYCZNE ---
bool GameScreen::isAdminMode = false;

void GameScreen::setAdminMode(bool admin) {
    isAdminMode = admin;
}
// -------------------------

// Helpery
sf::Vector2f GameScreen::getRandomPositionNoCollisionObstacle(const sf::FloatRect& forbidden, const sf::Vector2f& size) {
    static std::random_device rd; static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(0.f, 1000.f - size.x);
    std::uniform_real_distribution<float> distY(0.f, 600.f - size.y);
    sf::FloatRect candidate;
    do { candidate.left = distX(gen); candidate.top = distY(gen); candidate.width = size.x; candidate.height = size.y; } while (candidate.intersects(forbidden));
    return { candidate.left, candidate.top };
}

int GameScreen::getRandomObstacleCount() { return 3; }

sf::Vector2f GameScreen::getRandomPositionNoCollisionMultiple(const sf::FloatRect& playerBounds, const std::vector<Obstacle>& obstacles, const sf::Vector2f& size) {
    static std::random_device rd; static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(0.f, 1000.f - size.x);
    std::uniform_real_distribution<float> distY(0.f, 600.f - size.y);
    sf::FloatRect candidate;
    bool collision;
    do {
        collision = false;
        candidate = { distX(gen), distY(gen), size.x, size.y };
        if (candidate.intersects(playerBounds)) collision = true;
        for (const auto& obstacle : obstacles) {
            if (candidate.intersects(obstacle.getGlobalBounds())) { collision = true; break; }
        }
    } while (collision);
    return { candidate.left, candidate.top };
}

GameScreen::GameScreen() : collisionManager() {

    // ---- STYLE dla tekstów ----

    if (!font.loadFromFile("../assets/font.ttf")) 
        std::cerr << "Blad ladowania czcionki!\n";
    
    // Style dla info w roku ekranu
    leftCornerInfo.setFont(font);
    leftCornerInfo.setCharacterSize(24);
    leftCornerInfo.setPosition(10,10);
    leftCornerInfo.setOutlineColor(sf::Color::Black);
    
    // Style dla powiadomień wyświetlanych na środku
    centerInfo.setFont(font);
    centerInfo.setCharacterSize(24);
    centerInfo.setPosition(500, 300);
    centerInfo.setOutlineColor(sf::Color::Black);
    centerInfo.setFillColor(sf::Color::Red);
    centerInfoInterval = 0.5;

    // Tekst ekranu pauzy
    pauseText.setFont(font);
    pauseText.setString("PAUSED\nPress Enter to Resume\nPress Space to Quit");
    pauseText.setCharacterSize(40);
    pauseText.setFillColor(sf::Color::White);
    // Centrowanie tekstu (dostosowane do d�u�szego napisu)
    sf::FloatRect textRect = pauseText.getLocalBounds();
    pauseText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    pauseText.setPosition(500.f, 300.f);

    // Maskownica ekranu w czasie pauzy
    pauseOverlay.setSize(sf::Vector2f(1000.f, 600.f));
    pauseOverlay.setFillColor(sf::Color(0, 0, 0, 150));

    textManager = std::make_unique<TextManager>(font);

    player = std::make_unique<PlayerBasic>(sf::Vector2f(0.f, 0.f), sf::Vector2f(50.f, 50.f), 100);
    player->setGodMode(isAdminMode);

    loadLevel("../levels/level_01.json");
    timeElapsedSec = 0.f;
}

void GameScreen::loadLevel(const std::string& path) {
    std::cout << "Loading level: " << path << std::endl;
    obstacles.clear();
    enemies_chasers.clear();
    doors.clear();
    collisionManager = CollisionManager();

    levelData = LevelLoader::loadFromFile(path);

    background = std::make_unique<Background>(levelData.size);
    background->set(levelData.background);
    player->setPosition(levelData.playerStart);

    if (isAdminMode) 
        player->setColor(sf::Color(255, 215, 0));
    else 
        player->setColor(sf::Color::White);

    for (const auto& obs : levelData.obstacles) {
        obstacles.emplace_back(obs.bounds.getPosition(), obs.bounds.getSize(), obs.texture_path);
        collisionManager.addObstacle(obs.bounds);
    }
    for (const auto& d : levelData.doors) {
        doors.push_back(std::make_unique<Door>(d.bounds.getPosition(), d.bounds.getSize(), d.next_level_path));
    }

    for (const auto& enemy : levelData.enemies) {
        if (enemy.type == "chaser") {
            enemies_chasers.push_back(std::make_unique<EnemyChaser>(enemy.bounds.getPosition(), enemy.bounds.getSize()));
        }
        else if (enemy.type == "gunner") {
            enemies_chasers.push_back(std::make_unique<EnemyGunner>(enemy.bounds.getPosition(), enemy.bounds.getSize()));
        }
        else if (enemy.type == "boss") {
            enemies_chasers.push_back(std::make_unique<EnemyBoss>(enemy.bounds.getPosition(), enemy.bounds.getSize()));
        }
        else if (enemy.type == "bomber") {
            std::cout << "Spawn bomber (placeholder)\n";
        }
    }

    centerScreenNotifications.push_back({"Game started!", INFO, 2, 0});
}

void GameScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                isPaused = !isPaused;
            }
            else if (isPaused) {
                // Obs�uga klawiszy w trakcie pauzy
                if (event.key.code == sf::Keyboard::Enter) {
                    isPaused = false; // Wznowienie
                }
                else if (event.key.code == sf::Keyboard::Space) {
                    // ZMIANA: Wyj�cie do menu
                    nextScreenID = "menu"; // Ustawiamy cel
                    finished = true;       // Ko�czymy ten ekran
                }
            }
        }
    }
}

void GameScreen::update(float delta) {
    if (isPaused) return;
    timeElapsedSec += delta;

    if (!pendingLevelLoad.empty()) {
        if (pendingLevelLoad == "WIN") { finished = true; isWin = true; }
        else { loadLevel(pendingLevelLoad); pendingLevelLoad.clear(); }
        return;
    }

    player->update(delta);
    sf::Vector2f movement = player->getSpeedVector() * delta;
    collisionManager.tryMove(*player, movement);

    if (player->isShooting() && player->canShoot()) {
        sf::Vector2f dir = player->getShootDirection();

        const auto& stats = player->getStats();
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> chance(0.0f, 1.0f);

        bool isCrit = chance(gen) < stats.critChance;
        int finalDmg = stats.attack;
        if (isCrit) {
            finalDmg = static_cast<int>(stats.attack * stats.critDamage);
        }

        projectileManager.spawn(std::make_unique<Projectile>(
            player->getPosition() + sf::Vector2f(20, 20),
            sf::Vector2f(10.f, 10.f),
            dir * stats.projectileSpeed,
            finalDmg,
            isCrit,
            ProjectileOwner::Player
        ));
        player->resetCooldown();
    }

    if (enemies_chasers.empty()) {
        for (const auto& door : doors) {
            if (player->getGlobalBounds().intersects(door->getGlobalBounds())) {
                pendingLevelLoad = door->getNextLevel();
            }
        }
    }

    for (auto& enemy : enemies_chasers) {
        enemy->behave(delta, player->getPosition());
        sf::Vector2f ed = enemy->getSpeedVector() * delta;
        collisionManager.tryMove(*enemy, ed);
        enemy->update(delta);

        auto bullet = enemy->tryShoot(delta, player->getPosition());
        if (bullet) {
            projectileManager.spawn(std::move(bullet));
        }

        if (player->getGlobalBounds().intersects(enemy->getGlobalBounds())) {
            if (!player->isInvincible()) {
                int dmg = enemy->getAttack();
                int hpBefore = player->getHP();
                player->takeDamage(dmg);
                centerScreenNotifications.push_back({"You took " + std::to_string(dmg) + " damage!", WARNING, 2, 0});

                if (player->getHP() < hpBefore) {
                    textManager->addText(std::to_string(dmg), player->getPosition(), sf::Color::Red);

                    sf::Vector2f recoil = player->getPosition() - enemy->getPosition();
                    float len = std::sqrt(recoil.x * recoil.x + recoil.y * recoil.y);
                    if (len > 0) recoil /= len;
                    sf::Vector2f recoilMove = recoil * 20.f;
                    collisionManager.tryMove(*player, recoilMove);
                }
            }
        }
    }

    // Aktualizacja powiadomień wyświetanych na środku ekranu
    // iterując po liście powiadomień i dodając do wyświetlania 
    // te nieprzeterminowane 
    centerInfo.setString("");

    for (auto& notification : centerScreenNotifications){
        notification.elapsedTime += delta;
        if (notification.elapsedTime < notification.lifetime)
            centerInfo.setString(centerInfo.getString() + "\n" + notification.text);
    }

    // Wyśrodkowanie napisu
    centerInfo.setOrigin(
        centerInfo.getGlobalBounds().width/2, 
        centerInfo.getGlobalBounds().height/2
    );

    // Wyświatlanie info w rogu ekranu:
    // fps, czas, hp
    leftCornerInfo.setString(
        std::to_string((int)(1/delta)) + " FPS\nTime: " 
        + std::to_string((int)timeElapsedSec) + " sec."
        + "\nHP: " + std::to_string(player->getHP())
    );
    projectileManager.update(delta, enemies_chasers, *player, obstacles, *textManager);
    textManager->update(delta);

    enemies_chasers.erase(std::remove_if(enemies_chasers.begin(), enemies_chasers.end(),
        [](const std::unique_ptr<EnemyBase>& e) { return e->getHP() <= 0; }), enemies_chasers.end());

    if (player->getHP() <= 0) { finished = true; isWin = false; }
}

void GameScreen::render(sf::RenderWindow& window) {
    window.clear();
    background->draw(window);

    if (enemies_chasers.empty()) {
        for (const auto& door : doors) door->draw(window);
    }

    player->draw(window);
    for (auto& obstacle : obstacles) obstacle.draw(window);
    for (auto& enemy : enemies_chasers) enemy->draw(window);
    projectileManager.render(window);
    textManager->render(window);

    if (isPaused) {
        window.draw(pauseOverlay);
        window.draw(pauseText);
    }

    window.draw(leftCornerInfo);
    window.draw(centerInfo);

    window.display();
}

bool GameScreen::isFinished() const { return finished; }

// ZMIANA: Zwraca r�cznie ustawiony ekran (menu) lub standardowy (win/lose)
std::string GameScreen::getNextScreen() const {
    if (!nextScreenID.empty()) {
        return nextScreenID;
    }
    return isWin ? "gameover_win" : "gameover_lose";
}