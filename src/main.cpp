#include <SFML/Graphics.hpp>
#include "ScreenManager.hpp"

int main() {
    // Tworzymy okno w main
    sf::RenderWindow window(sf::VideoMode(1000, 600), "AGH SFML Game");
    window.setFramerateLimit(60);

    // Inicjalizujemy managera
    ScreenManager screenManager;

    // Przekazujemy okno do funkcji run - TO NAPRAWIA B£¥D C2660
    screenManager.run(window);

    return 0;
}