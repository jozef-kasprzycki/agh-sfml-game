#include "Enemy.hpp"
#include "Player.hpp"
#include <iostream>
#include <cmath>


Enemy::Enemy(sf::Vector2f position, sf::Vector2f size) : Movable(position, size){
    

    if (!sharedTexture.loadFromFile("../assets/enemy.png")) {
        std::cerr << "Blad ladowania enemy.png\n";
    }

    setTexture(sharedTexture);

    max_speed = 300;
    min_speed = 10;
}

void Enemy::update(float delta, Player& player) {
    directionVector = player.getPosition() - getPosition();
    lengthToPlayer = std::sqrt(
        std::pow(directionVector.x, 2) +
        std::pow(directionVector.y, 2)
    );

    // If we're very close to the player, stop to avoid jitter
    if (lengthToPlayer > 500) {
        speed_vector = sf::Vector2f(0.f, 0.f);
        return;
    }

    if (player.getGlobalBounds().intersects(getGlobalBounds())){
        // Zetknięcie player'a i enemy
        player.getHitted();
    }

    // Unit direction toward player
    sf::Vector2f dir = directionVector / lengthToPlayer;

    // Apply acceleration to the speed vector (only change speed_vector, do not move here)
    speed_vector += dir * (600 * delta);

    // Clamp speed magnitude to max_speed
    float speed = std::sqrt(speed_vector.x * speed_vector.x + speed_vector.y * speed_vector.y);
    if (speed > max_speed) {
        speed_vector = speed_vector * (max_speed / speed);
    }
}