module;
#include "raylib.h"
#include <regex>
#include <filesystem>
#include <ranges>
#include <string>
#include <fstream>
#include <concepts>

export module AuthModule;

template<typename T>
concept StringLike = requires(T t) {
    { t.empty() } -> std::convertible_to<bool>;
    { t.size() } -> std::convertible_to<size_t>;
    { std::string(t) } -> std::convertible_to<std::string>;
};

export class AuthManager {
private:
    static constexpr const char* USERS_FILE = "users.txt";
    std::regex usernameRegex{ R"([a-zA-Z0-9]{3,20})" };
    std::regex passwordRegex{ R"((?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{8,})" };

    struct User {
        std::string username;
        std::string password;
    };

    std::vector<User> loadUsers() {
        std::vector<User> users;
        if (std::filesystem::exists(USERS_FILE)) {
            std::ifstream file(USERS_FILE);
            std::string line;
            while (std::getline(file, line)) {
                auto parts = line | std::ranges::views::split(':') | std::ranges::to<std::vector<std::string>>();
                if (parts.size() == 2) {
                    users.push_back({ parts[0], parts[1] });
                }
            }
            file.close();
        }
        return users;
    }

    void saveUser(const User& user) {
        std::ofstream file(USERS_FILE, std::ios::app);
        file << user.username << ":" << user.password << "\n";
        file.close();
    }

public:
    bool signIn(StringLike auto& username, StringLike auto& password) {
        if (!std::regex_match(std::string(username), usernameRegex) || !std::regex_match(std::string(password), passwordRegex)) {
            DrawText("Invalid username or password format!", 100, 100, 20, RED);
            return false;
        }

        auto users = loadUsers();
        auto it = std::ranges::find_if(users, [&username](const User& u) { return u.username == std::string(username); });
        if (it != users.end()) {
            DrawText("Username already exists!", 100, 150, 20, RED);
            return false;
        }

        saveUser({ std::string(username), std::string(password) });
        DrawText("Sign In successful!", 100, 200, 20, GREEN);
        return true;
    }

    bool logIn(StringLike auto& username, StringLike auto& password) {
        auto users = loadUsers();
        auto it = std::ranges::find_if(users, [&username, &password](const User& u) {
            return u.username == std::string(username) && u.password == std::string(password);
            });
        if (it != users.end()) {
            DrawText("Log In successful!", 100, 200, 20, GREEN);
            return true;
        }
        DrawText("Invalid username or password!", 100, 150, 20, RED);
        return false;
    }
};