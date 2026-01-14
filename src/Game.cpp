#include "Game.hpp"
#include "CollisionManager.hpp"
#include "LevelLoader.hpp"
#include <iostream>
#include <random>

//funkcja zwraca losową pozycję, która nie koliduje z Playerem i zapewnia, że obiekt mieści się w oknie gry
//tworzy tymczasowy hitbox (candidate) i sprawdza kolizję z forbidden (hitbox Playera)
sf::Vector2f getRandomPositionNoCollisionObstacle(
    const sf::FloatRect& forbidden,
    const sf::Vector2f& size
) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distX(0.f, 1000.f - size.x);
    std::uniform_real_distribution<float> distY(0.f, 600.f - size.y);

    sf::FloatRect candidate;

    do {
        candidate.left = distX(gen);
        candidate.top = distY(gen);
        candidate.width = size.x;
        candidate.height = size.y;
    } while (candidate.intersects(forbidden));

    return { candidate.left, candidate.top };
}

int getRandomObstacleCount() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 5);
    return dist(gen);
}

sf::Vector2f getRandomPositionNoCollisionMultiple(
    const sf::FloatRect& playerBounds,
    const std::vector<Obstacle>& obstacles,
    const sf::Vector2f& size
) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distX(0.f, 1000.f - size.x);
    std::uniform_real_distribution<float> distY(0.f, 600.f - size.y);

    sf::FloatRect candidate;

    bool collision;
    do {
        collision = false;

        candidate = {
            distX(gen),
            distY(gen),
            size.x,
            size.y
        };

        if (candidate.intersects(playerBounds))
            collision = true;

        for (const auto& obstacle : obstacles) {
            if (candidate.intersects(obstacle.getGlobalBounds())) {
                collision = true;
                break;
            }
        }

    } while (collision);

    return { candidate.left, candidate.top };
}


Game::Game()
    : window(sf::VideoMode(1000, 600), "AGH SFML Game"),
    collisionManager()
{
    /*
        Konstruktor klasy gry; wykonywany raz, w momencie 
        uruchomienia gry. Tutaj są odczytywane informacje 
        na temat poziomu gry, a następnie inicjowane wszystkie 
        obiekty gry.
    */

    // Pobieranie danych o poziomie z pliku
    LevelData level = LevelLoader::loadFromFile("../levels/level_01.json");
    window.setSize(level.size);

    /*
        Definicja obiektu gracza (inicjalizacja) i przechowywanie
        jako wskaźnik
    */
    player = std::make_unique<PlayerBasic>(
        sf::Vector2f(10.f, 10.f),
        sf::Vector2f(50.f, 50.f),
        100
    );

    player->setPosition(level.playerStart);

    /*
        Inicjalizacja przeszkód w liście przeszkód oraz dodanie
        ich współrzędnych do CollisionManagera
    */
    for (const auto& obs : level.obstacles) {
        obstacles.emplace_back(
            obs.bounds.getPosition(), 
            obs.bounds.getSize(),
            obs.texture_path
        );
        
        collisionManager.addObstacle(obs.bounds);
    }

    const sf::Vector2f enemySize(50.f, 50.f);

    sf::Vector2f enemyPos = getRandomPositionNoCollisionMultiple(
        player->getGlobalBounds(),
        obstacles,
        enemySize
    );

    enemies.emplace_back(enemyPos, enemySize);
}

void Game::run() {
    /*
        Główna pętla gry. Każde wykonanie to jedna klatka.
    */

    while (window.isOpen()) {
        float delta = clock.restart().asSeconds();
        processEvents();
        update(delta);
        render();
    }
}

void Game::processEvents() {
    /*
        Funkcja sprawdzająca "eventy", takie jak 
        naciśnięcie krzyżyka (zamknięcie okienka).
    */

    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update(float delta) {
    /*
            Funkcja wywoływana co każdą klatkę (w 
        głównej pętli gry). Jako argument przyjmuje 
        parametr `delta`, czyli czas renderu klatki.
            Wywołuje funkcję update(delta), którą 
        posiadają wszystkie klasy dziedziczące z 
        klasy Entity, czyli "żywych" (zmiennych w
        czasie) obiektów gry.
    */

    player->update(delta);
    sf::Vector2f pd = player->getSpeedVector() * delta;
    collisionManager.tryMove(*player, pd);
    std::cout << 1/delta << " FPS       z\n";

    for (auto& enemy : enemies) {
        // Pogoń za graczem każdego enemy

        enemy.behave(delta, player->getPosition());
        sf::Vector2f ed = enemy.getSpeedVector() * delta;
        collisionManager.tryMove(enemy, ed);
    }
}

void Game::render() {
    // Czyszczenie poprzedniego ekranu
    window.clear();

    // Renderowanie przeszkód
    for (auto& obstacle : obstacles) {
        obstacle.draw(window);
    }

    // Renderowanie gracza    
    player->draw(window);
    
    // Renderowanie wrogów
    for (auto& enemy : enemies) {
        enemy.draw(window);
    }

    // Wyświetlanie okna
    window.display();
}
