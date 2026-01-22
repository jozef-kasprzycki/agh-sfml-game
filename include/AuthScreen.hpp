#pragma once
#include "Screen.hpp"
#include "UserManager.hpp"
#include <SFML/Graphics.hpp>
#include <string>

enum class AuthState {
    Menu,           // Wybór: 1. Login, 2. Register
    LoginInputUser, // Wpisz login
    LoginInputPass, // Wpisz has³o
    RegInputUser,   // Rejestracja: login
    RegInputPass,   // Rejestracja: has³o
    RegConfirmPass  // Rejestracja: potwierdŸ has³o
};

class AuthScreen : public Screen {
private:
    sf::Font font;
    sf::Text titleText;
    sf::Text infoText;
    sf::Text inputText;
    sf::Text errorText;

    UserManager userManager;
    AuthState currentState;

    std::string currentInput;
    std::string tempUsername;
    std::string tempPassword;

    bool finished = false;

    void handleTextInput(sf::Uint32 unicode);
    void processEnter();

public:
    AuthScreen();
    void handleEvents(sf::RenderWindow& window) override;
    void update(float delta) override;
    void render(sf::RenderWindow& window) override;
    bool isFinished() const override;
    std::string getNextScreen() const override;
};