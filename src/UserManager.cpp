#include "UserManager.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

UserManager::UserManager(const std::string& path) : filePath(path) {
    load();
    // Upewnij siê, ¿e Admin zawsze istnieje
    if (!userExists("Admin")) {
        users.push_back({ "Admin", "Admin" });
        save();
    }
}

void UserManager::load() {
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
            std::cerr << "Error parsing users.json, starting fresh.\n";
        }
    }
}

void UserManager::save() {
    json j;
    j["users"] = json::array();
    for (const auto& u : users) {
        j["users"].push_back({ { "username", u.username }, { "password", u.password } });
    }

    std::ofstream file(filePath);
    file << j.dump(4);
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
    save();
    return true;
}

bool UserManager::userExists(const std::string& user) {
    for (const auto& u : users) {
        if (u.username == user) return true;
    }
    return false;
}