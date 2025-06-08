/**
 * @file AuthModule.cpp
 * @brief Implementacja klasy Authorization.
 */

module;
#include <string>
#include <set>
#include <regex>
#include <ranges>
#include <map>
#include <fstream>
#include <sstream>
#include <functional> // std::hash

module AuthModule;

std::string Authorization::hashPassword(const std::string& password) {
	std::hash<std::string> hasher;
	return std::to_string(hasher(password));
}

void Authorization::loadUsers() {
	std::ifstream file(usersFile);
	if (!file.is_open()) {
		return;
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

bool Authorization::saveUser(const std::string& username, const std::string& hashedPassword) {
	std::ofstream file(usersFile, std::ios::app); //Append mode
	if (!file.is_open()) {
		return false;
	}
	file << username << ":" << hashedPassword << "\n";
	file.close();
	return true;
}

SignInResult Authorization::signIn(const std::string& username, const std::string& password) {
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
		return SignInResult::INVALID_USERNAME;
	}

	existingUsernames.insert(username);
	storedPasswords[username] = hashedPassword;
	return SignInResult::SUCCESS;

}

LogInResult	Authorization::logIn(const std::string& username, const std::string& password) {
	if (std::ranges::find(existingUsernames, username) == existingUsernames.end()) {
		return LogInResult::USER_NOT_FOUND;
	}

	std::string hashedPassword = hashPassword(password);
	if (storedPasswords.find(username)->second != hashedPassword) {
		return LogInResult::INCORRECT_PASSWORD;
	}

	return LogInResult::SUCCESS;

}