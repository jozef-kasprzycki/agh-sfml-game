#pragma once

struct CombatStats {
    int max_hp = 100;
    int hp = 100;
    int attack = 10;

    float fireRate = 0.5f;
    float projectileSpeed = 600.f;

    // NOWE STATYSTYKI
    float critChance = 0.05f;   // 5% szansy domyœlnie
    float critDamage = 1.75f;   // 175% obra¿eñ domyœlnie

    CombatStats() = default;

    // Zaktualizowany konstruktor
    CombatStats(int h, int a, float fr, float ps, float cc = 0.05f, float cd = 1.75f)
        : max_hp(h), hp(h), attack(a), fireRate(fr), projectileSpeed(ps), critChance(cc), critDamage(cd) {
    }
};