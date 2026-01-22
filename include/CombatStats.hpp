#pragma once

struct CombatStats {
    int max_hp = 100;
    int hp = 100;
    int attack = 10;

    // Nowe statystyki
    float fireRate = 0.5f;         // Czas odnowienia (s)
    float projectileSpeed = 600.f; // Prêdkoœæ pocisku (px/s)

    CombatStats() = default;

    // Konstruktor
    CombatStats(int h, int a, float fr, float ps)
        : max_hp(h), hp(h), attack(a), fireRate(fr), projectileSpeed(ps) {
    }
};