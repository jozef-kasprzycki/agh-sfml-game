#include "AuthScreen.hpp"
#include "GameScreen.hpp" 
#include <iostream>

AuthScreen::AuthScreen()
    : userManager("../../data/users.json"),
    currentState(AuthState::Menu)
{
    if (!font.loadFromFile("../assets/font.ttf")) {
        // Obs³uga b³êdu
    }

    titleText.setFont(font);
    titleText.setCharacterSize(40);
    titleText.setPosition(100.f, 50.f);
    titleText.setString("WELCOME TO THE GAME");

    infoText.setFont(font);
    infoText.setCharacterSize(25);
    infoText.setPosition(100.f, 150.f);
    infoText.setString("1. Create New Character\n2. Login\n3. Exit");

    inputText.setFont(font);
    inputText.setCharacterSize(30);
    inputText.setPosition(100.f, 300.f);
    inputText.setFillColor(sf::Color::Yellow);

    errorText.setFont(font);
    errorText.setCharacterSize(20);
    errorText.setPosition(100.f, 400.f);
    errorText.setFillColor(sf::Color::Red);
}

void AuthScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::TextEntered) {
            handleTextInput(event.text.unicode);
        }
    }
}

void AuthScreen::handleTextInput(sf::Uint32 unicode) {
    if (unicode == 8) {
        if (!currentInput.empty()) currentInput.pop_back();
    }
    else if (unicode == 13) {
        processEnter();
    }
    else if (unicode < 128 && unicode > 31) {
        currentInput += static_cast<char>(unicode);
    }
}

void AuthScreen::processEnter() {
    errorText.setString("");

    switch (currentState) {
    case AuthState::Menu:
        if (currentInput == "1") {
            currentState = AuthState::RegInputUser;
            infoText.setString("REGISTER: Enter Username:");
        }
        else if (currentInput == "2") {
            currentState = AuthState::LoginInputUser;
            infoText.setString("LOGIN: Enter Username:");
        }
        else if (currentInput == "3") {
            std::exit(0);
        }
        currentInput.clear();
        break;

    case AuthState::LoginInputUser:
        if (userManager.userExists(currentInput)) {
            tempUsername = currentInput;
            currentState = AuthState::LoginInputPass;
            infoText.setString("LOGIN: Enter Password:");
            currentInput.clear();
        }
        else {
            errorText.setString("User does not exist!");
        }
        break;

    case AuthState::LoginInputPass:
        if (userManager.login(tempUsername, currentInput)) {
            GameScreen::setAdminMode(tempUsername == "Admin");
            finished = true;
        }
        else {
            errorText.setString("Invalid password! Press Enter to restart.");
            currentState = AuthState::Menu;
            infoText.setString("1. Create New Character\n2. Login\n3. Exit");
        }
        currentInput.clear();
        break;

    case AuthState::RegInputUser:
        if (userManager.userExists(currentInput)) {
            errorText.setString("User already exists!");
            currentInput.clear();
        }
        else {
            tempUsername = currentInput;
            currentState = AuthState::RegInputPass;
            infoText.setString("REGISTER: Enter Password:");
            currentInput.clear();
        }
        break;

    case AuthState::RegInputPass:
        tempPassword = currentInput;
        currentState = AuthState::RegConfirmPass;
        infoText.setString("REGISTER: Confirm Password:");
        currentInput.clear();
        break;

    case AuthState::RegConfirmPass:
        if (currentInput == tempPassword) {
            userManager.registerUser(tempUsername, tempPassword);
            errorText.setString("Account created! You can now Login.");
            currentState = AuthState::Menu;
            infoText.setString("1. Create New Character\n2. Login\n3. Exit");
        }
        else {
            errorText.setString("Passwords do not match! Try again.");
            currentState = AuthState::RegInputUser;
            infoText.setString("REGISTER: Enter Username:");
        }
        currentInput.clear();
        break;
    }
}

void AuthScreen::update(float delta) {
    if (currentState == AuthState::LoginInputPass ||
        currentState == AuthState::RegInputPass ||
        currentState == AuthState::RegConfirmPass)
    {
        std::string masked(currentInput.length(), '*');
        inputText.setString(masked);
    }
    else {
        inputText.setString(currentInput);
    }
}

void AuthScreen::render(sf::RenderWindow& window) {
    window.clear(sf::Color(20, 20, 30));
    window.draw(titleText);
    window.draw(infoText);
    window.draw(inputText);
    window.draw(errorText);
    window.display();
}

bool AuthScreen::isFinished() const {
    return finished;
}

std::string AuthScreen::getNextScreen() const {
    return "menu";
}