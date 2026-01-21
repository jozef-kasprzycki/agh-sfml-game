#pragma once

struct CombatStats {
    int max_hp = 100;
    int hp = 100;
    int attack = 10;

    CombatStats() = default;

    // Konstruktor (hp, attack)
    CombatStats(int h, int a) : max_hp(h), hp(h), attack(a) {}
};