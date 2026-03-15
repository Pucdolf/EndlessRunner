module;

#include<iostream>
#include <pqxx/pqxx>
#include <memory>


module DatabaseManagerModule;
import DatabaseManagerModule;

DatabaseManager::DatabaseManager() {
	std::cout << "Initializing DatabaseManager singleton" << std::endl;
}

DatabaseManager::~DatabaseManager() {
	std::cout << "Shutting down DatabaseManager and closing connections" << std::endl;
	close();
}

DatabaseManager& DatabaseManager::getInstance() {
	static DatabaseManager instance;
	return instance;
}

bool DatabaseManager::connect() {
	try {
		std::string connStr = "host=localhost port=5432 user=admin password=password123 dbname=dinorush";
		connection = std::make_unique<pqxx::connection>(connStr);

		if (connection && connection->is_open()) {
			std::cout << "[Database] Connected to database successfully!" << std::endl;
			initTables();
			return true;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "[Database] Connection error: " << e.what() << std::endl;
	}
	return false;
}

void DatabaseManager::close() {
	if (connection) {
		if (connection->is_open()) {
			connection->close();
		}
		connection.reset();
		std::cout << "[Database] Connection closed." << std::endl;
	}
}

void DatabaseManager::initTables() {
	pqxx::work W(*connection);

	//users
	W.exec(R"(
		CREATE TABLE IF NOT EXISTS users (
			id SERIAL PRIMARY KEY,
			username TEXT UNIQUE NOT NULL,
			password_hash TEXT NOT NULL,	
			created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
		);
	)");

	//scores
	W.exec(R"(
		CREATE TABLE IF NOT EXISTS scores (
			id SERIAL PRIMARY KEY,
			user_id INTEGER REFERENCES users(id) ON DELETE CASCADE,
			score INTEGER NOT NULL,
			achieved_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
			);
		)");

	//user_settings
	W.exec(R"(
		CREATE TABLE IF NOT EXISTS user_settings (
			user_id INTEGER PRIMARY KEY REFERENCES users(id) ON DELETE CASCADE,
			selected_dino_id INTEGER DEFAULT 0,
			total_games_played INTEGER DEFAULT 0,
			high_score INTEGER DEFAULT 0,
		);
	)");

	W.commit();

}

