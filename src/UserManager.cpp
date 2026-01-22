#include "UserManager.hpp"
#include <fstream>
#include <iostream>
#include <filesystem> // NOWE: Biblioteka do operacji na plikach

// Alias dla wygody
namespace fs = std::filesystem;
using json = nlohmann::json;

UserManager::UserManager(const std::string& path) : filePath(path) {
    load();

    // Upewnij siê, ¿e Admin zawsze istnieje w pamiêci
    if (!userExists("Admin")) {
        users.push_back({ "Admin", "Admin" });
        // Zapisz od razu, ¿eby utworzyæ plik/folder przy pierwszym uruchomieniu
        save();
    }
}

void UserManager::load() {
    // SprawdŸ czy plik w ogóle istnieje
    if (!fs::exists(filePath)) {
        return; // Nie ma pliku, wiêc nie ma co ³adowaæ (zaczynamy na czysto)
    }

    std::ifstream file(filePath);
    if (file.is_open()) {
        json j;
        try {
            file >> j;
            if (j.contains("users")) {
                for (const auto& u : j["users"]) {
                    users.push_back({ u["username"], u["password"] });
                }
            }
        }
        catch (...) {
            std::cerr << "Error parsing users.json, file might be corrupted.\n";
        }
    }
}

void UserManager::save() {
    // --- NOWA LOGIKA TWORZENIA FOLDERU ---
    // Pobieramy œcie¿kê do pliku jako obiekt filesystem
    fs::path path(filePath);

    // Jeœli œcie¿ka ma folder (parent path), sprawdŸ czy on istnieje
    if (path.has_parent_path()) {
        if (!fs::exists(path.parent_path())) {
            // Folder nie istnieje (np. "data"), tworzymy go
            try {
                fs::create_directories(path.parent_path());
                std::cout << "Created directory: " << path.parent_path() << std::endl;
            }
            catch (const fs::filesystem_error& e) {
                std::cerr << "Error creating directory: " << e.what() << std::endl;
                return; // Nie uda siê zapisaæ bez folderu
            }
        }
    }
    // -------------------------------------

    json j;
    j["users"] = json::array();
    for (const auto& u : users) {
        j["users"].push_back({ { "username", u.username }, { "password", u.password } });
    }

    std::ofstream file(filePath);
    if (file.is_open()) {
        file << j.dump(4);
    }
    else {
        std::cerr << "Could not open file for writing: " << filePath << std::endl;
    }
}

bool UserManager::login(const std::string& user, const std::string& pass) {
    for (const auto& u : users) {
        if (u.username == user && u.password == pass) {
            return true;
        }
    }
    return false;
}

bool UserManager::registerUser(const std::string& user, const std::string& pass) {
    if (userExists(user)) return false;

    users.push_back({ user, pass });
    save(); // To wywo³anie teraz automatycznie stworzy folder i plik
    return true;
}

bool UserManager::userExists(const std::string& user) {
    for (const auto& u : users) {
        if (u.username == user) return true;
    }
    return false;
}