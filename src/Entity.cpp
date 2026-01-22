#include "Entity.hpp"

// Implementacja konstruktora
Entity::Entity(
    sf::Vector2f position,
    sf::Vector2f size,
    const CombatStats& stats
)
// Wywo³anie konstruktora klasy bazowej Movable (ustawia pozycjê i rozmiar)
    : Movable(position, size),
    // Inicjalizacja statystyk bojowych
    combatStats(stats)
{
}

// Zwraca aktualne HP z wewnêtrznej struktury
int Entity::getHP() const {
    return combatStats.hp;
}

// NOWE: Zwraca wartoœæ ataku z wewnêtrznej struktury.
// Dziêki temu GameScreen mo¿e pobraæ enemy->getAttack() przy kolizji.
int Entity::getAttack() const {
    return combatStats.attack;
}

// Podstawowa logika otrzymywania obra¿eñ
void Entity::takeDamage(int dmg) {
    combatStats.hp -= dmg;

    // Zabezpieczenie, ¿eby HP nie spad³o poni¿ej zera
    if (combatStats.hp < 0) {
        combatStats.hp = 0;
    }
}

// Zwraca referencjê do obiektu statystyk
const CombatStats& Entity::getStats() const {
    return combatStats;
}