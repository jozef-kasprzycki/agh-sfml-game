#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

struct UserAccount {
    std::string username;
    std::string password;
};

class UserManager {
private:
    std::string filePath;
    std::vector<UserAccount> users;

    void load();
    void save();

public:
    UserManager(const std::string& path);

    bool login(const std::string& user, const std::string& pass);
    bool registerUser(const std::string& user, const std::string& pass);
    bool userExists(const std::string& user);
};