module;
#include <string>
#include <set>
#include <regex>
#include <ranges>
#include <map>
#include <fstream>
#include <sstream>
#include <functional> // for std::hash

export module AuthModule;

export enum class SignInResult {
	SUCCESS,
	USERNAME_TAKEN,
	INVALID_USERNAME,
	INVALID_PASSWORD
};

export enum class LogInResult {
	SUCCESS,
	USER_NOT_FOUND,
	INCORRECT_PASSWORD
};

export class Authorization {
private:
	std::set<std::string> existingUsernames;
	std::map<std::string, std::string> storedPasswords;
	const std::string usersFile = "users.txt";

	// Simple hash function for passwords (for demonstration; use a proper cryptographic hash in production)
	std::string hashPassword(const std::string& password) {
		std::hash<std::string> hasher;
		return std::to_string(hasher(password));
	}

	// Load users from file
	void loadUsers() {
		std::ifstream file(usersFile);
		if (!file.is_open()) {
			return; // File doesn't exist yet, which is fine
		}

		std::string line;
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			std::string username, hashedPassword;
			if (std::getline(iss, username, ':') && std::getline(iss, hashedPassword)) {
				existingUsernames.insert(username);
				storedPasswords[username] = hashedPassword;
			}
		}
		file.close();
	}

	// Save a new user to file
	bool saveUser(const std::string& username, const std::string& hashedPassword) {
		std::ofstream file(usersFile, std::ios::app); // Append mode
		if (!file.is_open()) {
			return false;
		}
		file << username << ":" << hashedPassword << "\n";
		file.close();
		return true;
	}

public:
	Authorization() {
		loadUsers(); // Load existing users at initialization
	}

	SignInResult signIn(const std::string& username, const std::string& password) {
		if (std::ranges::find(existingUsernames, username) != existingUsernames.end()) {
			return SignInResult::USERNAME_TAKEN;
		}
		std::regex usernameRegex("^[a-zA-Z0-9]{3,20}$");
		if (!std::regex_match(username, usernameRegex)) {
			return SignInResult::INVALID_USERNAME;
		}
		std::regex passwordRegex("^[A-Za-z\\d]{8,}$");

		if (!std::regex_match(password, passwordRegex)) {
			return SignInResult::INVALID_PASSWORD;
		}

		std::string hashedPassword = hashPassword(password);
		if (!saveUser(username, hashedPassword)) {
			return SignInResult::INVALID_USERNAME; // Fallback error if file write fails
		}

		existingUsernames.insert(username);
		storedPasswords[username] = hashedPassword;
		return SignInResult::SUCCESS;
	}

	LogInResult logIn(const std::string& username, const std::string& password) {
		if (std::ranges::find(existingUsernames, username) == existingUsernames.end()) {
			return LogInResult::USER_NOT_FOUND;
		}
		std::string hashedPassword = hashPassword(password);
		if (storedPasswords.find(username)->second != hashedPassword) {
			return LogInResult::INCORRECT_PASSWORD;
		}
		return LogInResult::SUCCESS;
	}
};