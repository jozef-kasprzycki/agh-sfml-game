#pragma once
#include "Movable.hpp"
#include "CombatStats.hpp"

// Klasa bazowa dla wszystkich "¿ywych" obiektów w grze (Gracz, Przeciwnicy, Boss).
// Dziedziczy po Movable, wiêc ma fizykê ruchu i pozycjê.
class Entity : public Movable {
protected:
    // Struktura trzymaj¹ca statystyki bojowe (HP, atak, szybkoœæ strzelania itp.)
    CombatStats combatStats;

public:
    // Konstruktor przyjmuj¹cy pozycjê, rozmiar oraz zestaw statystyk
    Entity(
        sf::Vector2f position,
        sf::Vector2f size,
        const CombatStats& stats
    );

    // Wirtualny destruktor (wymagany przy dziedziczeniu)
    virtual ~Entity() = default;

    // Zwraca aktualn¹ iloœæ punktów ¿ycia
    int getHP() const;

    // NOWE: Zwraca si³ê ataku (potrzebne do obliczania obra¿eñ przy kolizji)
    int getAttack() const;

    // Metoda do zadawania obra¿eñ tej jednostce
    // Jest wirtualna, aby klasy pochodne (np. Player) mog³y dodaæ w³asn¹ logikê (np. nieœmiertelnoœæ)
    virtual void takeDamage(int dmg);

    // Zwraca pe³n¹ strukturê statystyk (np. do odczytu szybkoœci pocisków)
    const CombatStats& getStats() const;

    // Metoda abstrakcyjna - ka¿da jednostka musi zdefiniowaæ w³asn¹ logikê aktualizacji
    virtual void update(float delta) = 0;
};